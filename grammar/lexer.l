%option noyywrap
%option yylineno
%option nounput
%option noinput

%{
#include "include/main.h"
#include "parser.tab.h"
#include "include/semantic.h"
%}

DIGIT      [0-9]
ID_START   [A-Za-z_]
ID_REST    [A-Za-z0-9_]
NUMBER     {DIGIT}+(\.{DIGIT}+)?

%%

"//".*                         ;
[ \t\r\n]+                     ;

"Element"                      { return TYPE_ELEMENT; }
"Compound"                     { return TYPE_COMPOUND; }
"Organic"                      { return TYPE_ORGANIC; }
"Config"                       { return TYPE_CONFIG; }
"Molarity"                     { return TYPE_MOLARITY; }
"Reaction"                     { return TYPE_REACTION; }
"Context"                      { return TYPE_CONTEXT; }
"Double"                       { return TYPE_DOUBLE; }

"SECTION"                      { return KW_SECTION; }
"INORGANIC"                    { return BLOCK_INORGANIC; }
"ORGANIC"                      { return BLOCK_ORGANIC; }
"QUANTUM"                      { return BLOCK_QUANTUM; }
"ENVIRONMENT"                  { return BLOCK_ENVIRONMENT; }
"PROTOCOL"                     { return BLOCK_PROTOCOL; }
"HAZARD_CHECK"                 { return BLOCK_HAZARD_CHECK; }

"IF"                           { return KW_IF; }
"ELSE"                         { return KW_ELSE; }
"WHILE"                        { return KW_WHILE; }
"TITRATE"                      { return KW_TITRATE; }
"UNTIL"                        { return KW_UNTIL; }

"REACT"                        { return FN_REACT; }
"BALANCE"                      { return FN_BALANCE; }
"PRINT"                        { return FN_PRINT; }
"RENDER"                       { return FN_RENDER; }
"GET_MASS"                     { return FN_GET_MASS; }
"GET_FORMULA"                  { return FN_GET_FORMULA; }
"GET_CONFIG"                   { return FN_GET_CONFIG; }
"GET_VALENCE_ELECTRON"         { return FN_GET_VALENCE_ELECTRON; }
"GET_QUANTUM_NUMBERS"          { return FN_GET_QUANTUM_NUMBERS; }
"GET_ENTHALPY"                 { return FN_GET_ENTHALPY; }
"IS_SATURATED"                 { return FN_IS_SATURATED; }
"IS_ISOMER"                    { return FN_IS_ISOMER; }
"IS_METAL"                     { return FN_IS_METAL; }
"FIND_SERIES"                  { return FN_FIND_SERIES; }
"PRECIPITATE"                  { return FN_PRECIPITATE; }

"Temperature"                  { return ENV_TEMPERATURE; }
"Pressure"                     { return ENV_PRESSURE; }

"->"                           { return ARROW; }
"=>"                           { return FATARROW; }
"=="                           { return EQ; }
"!="                           { return NE; }
"&&"                           { return AND; }
"||"                           { return OR; }

{NUMBER}                       {
                                  yylval.value = chem_make_number(strtod(yytext, NULL));
                                  return NUMBER;
                               }

\"([^\\\"]|\\.)*\"             {
                                  yylval.text = chem_strdup(yytext);
                                  return STRING;
                               }

{ID_START}{ID_REST}*           {
                                  yylval.text = chem_strdup(yytext);
                                  return IDENTIFIER;
                               }

"="                            { return '='; }
"+"                            { return '+'; }
"-"                            { return '-'; }
"*"                            { return '*'; }
"/"                            { return '/'; }
"<"                            { return '<'; }
">"                            { return '>'; }
"!"                            { return '!'; }
";"                            { return ';'; }
","                            { return ','; }
"{"                            { return '{'; }
"}"                            { return '}'; }
"("                            { return '('; }
")"                            { return ')'; }
"["                            { return '['; }
"]"                            { return ']'; }

.                              {
                                  chem_report_lex_error(yytext, yylineno);
                                  yylval.text = chem_strdup(yytext);
                                  return INVALID;
                               }

%%
