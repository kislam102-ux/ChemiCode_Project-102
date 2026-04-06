%code requires {
#include "include/main.h"
#include "include/semantic.h"
}

%{
#include <stdio.h>
#include <stdlib.h>

#include "include/symtab.h"
#include "include/semantic.h"
%}

%define parse.error verbose

%union {
    char *text;
    ChemValue *value;
    AstNode *node;
    AstArg *args;
    int ival;
}

%token <text> IDENTIFIER STRING INVALID
%token <value> NUMBER

%token TYPE_ELEMENT TYPE_COMPOUND TYPE_ORGANIC TYPE_CONFIG TYPE_MOLARITY TYPE_REACTION TYPE_CONTEXT TYPE_DOUBLE
%token KW_SECTION BLOCK_INORGANIC BLOCK_ORGANIC BLOCK_QUANTUM BLOCK_ENVIRONMENT BLOCK_PROTOCOL BLOCK_HAZARD_CHECK
%token KW_IF KW_ELSE KW_WHILE KW_TITRATE KW_UNTIL
%token FN_REACT FN_BALANCE FN_PRINT FN_RENDER FN_GET_MASS FN_GET_FORMULA FN_GET_CONFIG FN_GET_VALENCE_ELECTRON
%token FN_GET_QUANTUM_NUMBERS FN_GET_ENTHALPY FN_IS_SATURATED FN_IS_ISOMER FN_IS_METAL FN_FIND_SERIES FN_PRECIPITATE
%token ENV_TEMPERATURE ENV_PRESSURE
%token ARROW FATARROW EQ NE AND OR

%left OR
%left AND
%left EQ NE '<' '>'
%left '+' '-'
%left '*' '/'
%right UMINUS '!'

%type <node> program sections section block stmt stmt_list declaration assignment environment_stmt reaction_stmt expr function_call species species_list
%type <args> arg_list arg_list_opt
%type <ival> type_name function_name
%type <text> section_name environment_name

%%

program
    : sections
      {
          chem_ast_set_root($1);
          $$ = $1;
      }
    ;

sections
    : /* empty */               { $$ = NULL; }
    | sections section          { $$ = chem_ast_append($1, $2); }
    ;

section
    : KW_SECTION IDENTIFIER block
      {
          $$ = chem_ast_make_section($2, $3);
      }
    | section_name block
      {
          $$ = chem_ast_make_section($1, $2);
      }
    ;

section_name
    : BLOCK_INORGANIC            { $$ = chem_strdup("INORGANIC"); }
    | BLOCK_ORGANIC              { $$ = chem_strdup("ORGANIC"); }
    | BLOCK_QUANTUM              { $$ = chem_strdup("QUANTUM"); }
    | BLOCK_ENVIRONMENT          { $$ = chem_strdup("ENVIRONMENT"); }
    | BLOCK_PROTOCOL             { $$ = chem_strdup("PROTOCOL"); }
    | BLOCK_HAZARD_CHECK         { $$ = chem_strdup("HAZARD_CHECK"); }
    ;

block
    : '{' stmt_list '}'          { $$ = $2; }
    | '{' error '}'              { yyerrok; $$ = NULL; }
    ;

stmt_list
    : /* empty */                { $$ = NULL; }
    | stmt_list stmt             { $$ = chem_ast_append($1, $2); }
    ;

stmt
    : declaration ';'            { $$ = $1; }
    | assignment ';'             { $$ = $1; }
    | environment_stmt ';'       { $$ = $1; }
    | function_call ';'          { $$ = chem_ast_make_expr_stmt($1); }
    | reaction_stmt ';'          { $$ = $1; }
    | KW_IF '(' expr ')' block
      {
          $$ = chem_ast_make_if($3, $5, NULL);
      }
    | KW_IF '(' expr ')' block KW_ELSE block
      {
          $$ = chem_ast_make_if($3, $5, $7);
      }
    | KW_WHILE '(' expr ')' block
      {
          $$ = chem_ast_make_while($3, $5);
      }
    | KW_TITRATE block KW_UNTIL '(' expr ')' ';'
      {
          $$ = chem_ast_make_titrate($2, $5);
      }
    | ';'                        { $$ = NULL; }
    | INVALID ';'
      {
          chem_report_error("Invalid token '%s' recovered at line %d", $1, yylineno);
          free($1);
          $$ = NULL;
      }
    | error ';'
      {
          chem_report_error("Recovered from syntax error near line %d", yylineno);
          yyerrok;
          $$ = NULL;
      }
    ;

declaration
    : type_name IDENTIFIER
      {
          $$ = chem_ast_make_decl((ChemDeclType)$1, $2, NULL);
      }
    | type_name IDENTIFIER '=' expr
      {
          $$ = chem_ast_make_decl((ChemDeclType)$1, $2, $4);
      }
    ;

type_name
    : TYPE_ELEMENT               { $$ = DECL_ELEMENT; }
    | TYPE_COMPOUND              { $$ = DECL_COMPOUND; }
    | TYPE_ORGANIC               { $$ = DECL_ORGANIC; }
    | TYPE_CONFIG                { $$ = DECL_CONFIG; }
    | TYPE_MOLARITY              { $$ = DECL_MOLARITY; }
    | TYPE_REACTION              { $$ = DECL_REACTION; }
    | TYPE_CONTEXT               { $$ = DECL_CONTEXT; }
    | TYPE_DOUBLE                { $$ = DECL_DOUBLE; }
    ;

assignment
    : IDENTIFIER '=' expr
      {
          $$ = chem_ast_make_assign($1, $3);
      }
    ;

environment_stmt
    : environment_name '=' expr
      {
          $$ = chem_ast_make_env_assign($1, $3);
      }
    ;

environment_name
    : ENV_TEMPERATURE            { $$ = chem_strdup("Temperature"); }
    | ENV_PRESSURE               { $$ = chem_strdup("Pressure"); }
    ;

reaction_stmt
    : species_list ARROW species_list
      {
          $$ = chem_ast_make_reaction($1, $3, 1);
      }
    | species_list FATARROW species_list
      {
          $$ = chem_ast_make_reaction($1, $3, 2);
      }
    ;

species_list
    : species                    { $$ = $1; }
    | species_list '+' species   { $$ = chem_ast_make_binary(OP_SPECIES_JOIN, $1, $3); }
    ;

species
    : IDENTIFIER                 { $$ = chem_ast_make_var($1, 0); }
    | STRING
      {
          char *tmp = chem_trim_quotes($1);
          free($1);
          $$ = chem_ast_make_literal(chem_make_string(tmp));
          free(tmp);
      }
    ;

expr
    : NUMBER                     { $$ = chem_ast_make_literal($1); }
    | STRING
      {
          char *tmp = chem_trim_quotes($1);
          free($1);
          $$ = chem_ast_make_literal(chem_make_string(tmp));
          free(tmp);
      }
    | IDENTIFIER                 { $$ = chem_ast_make_var($1, 0); }
    | ENV_TEMPERATURE            { $$ = chem_ast_make_var(chem_strdup("Temperature"), 1); }
    | ENV_PRESSURE               { $$ = chem_ast_make_var(chem_strdup("Pressure"), 1); }
    | function_call              { $$ = $1; }
    | '(' expr ')'               { $$ = $2; }
    | expr '+' expr              { $$ = chem_ast_make_binary(OP_ADD, $1, $3); }
    | expr '-' expr              { $$ = chem_ast_make_binary(OP_SUB, $1, $3); }
    | expr '*' expr              { $$ = chem_ast_make_binary(OP_MUL, $1, $3); }
    | expr '/' expr              { $$ = chem_ast_make_binary(OP_DIV, $1, $3); }
    | expr EQ expr               { $$ = chem_ast_make_binary(OP_EQ, $1, $3); }
    | expr NE expr               { $$ = chem_ast_make_binary(OP_NE, $1, $3); }
    | expr '<' expr              { $$ = chem_ast_make_binary(OP_LT, $1, $3); }
    | expr '>' expr              { $$ = chem_ast_make_binary(OP_GT, $1, $3); }
    | expr AND expr              { $$ = chem_ast_make_binary(OP_AND, $1, $3); }
    | expr OR expr               { $$ = chem_ast_make_binary(OP_OR, $1, $3); }
    | '-' expr %prec UMINUS      { $$ = chem_ast_make_unary(OP_NEG, $2); }
    | '!' expr                   { $$ = chem_ast_make_unary(OP_NOT, $2); }
    ;

function_call
    : function_name '(' arg_list_opt ')'
      {
          $$ = chem_ast_make_funcall((ChemFunctionKind)$1, $3);
      }
    ;

function_name
    : FN_REACT                   { $$ = FN_KIND_REACT; }
    | FN_BALANCE                 { $$ = FN_KIND_BALANCE; }
    | FN_PRINT                   { $$ = FN_KIND_PRINT; }
    | FN_RENDER                  { $$ = FN_KIND_RENDER; }
    | FN_GET_MASS                { $$ = FN_KIND_GET_MASS; }
    | FN_GET_FORMULA             { $$ = FN_KIND_GET_FORMULA; }
    | FN_GET_CONFIG              { $$ = FN_KIND_GET_CONFIG; }
    | FN_GET_VALENCE_ELECTRON    { $$ = FN_KIND_GET_VALENCE_ELECTRON; }
    | FN_GET_QUANTUM_NUMBERS     { $$ = FN_KIND_GET_QUANTUM_NUMBERS; }
    | FN_GET_ENTHALPY            { $$ = FN_KIND_GET_ENTHALPY; }
    | FN_IS_SATURATED            { $$ = FN_KIND_IS_SATURATED; }
    | FN_IS_ISOMER               { $$ = FN_KIND_IS_ISOMER; }
    | FN_IS_METAL                { $$ = FN_KIND_IS_METAL; }
    | FN_FIND_SERIES             { $$ = FN_KIND_FIND_SERIES; }
    | FN_PRECIPITATE             { $$ = FN_KIND_PRECIPITATE; }
    ;

arg_list_opt
    : /* empty */                { $$ = NULL; }
    | arg_list                   { $$ = $1; }
    ;

arg_list
    : expr                       { $$ = chem_ast_arg_append(NULL, $1); }
    | arg_list ',' expr          { $$ = chem_ast_arg_append($1, $3); }
    ;

%%
