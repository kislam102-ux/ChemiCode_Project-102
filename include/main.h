#ifndef CHEMICODE_MAIN_H
#define CHEMICODE_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

typedef struct ChemValue ChemValue;
typedef struct AstNode AstNode;
typedef struct AstArg AstArg;
typedef struct Symbol Symbol;

typedef enum {
    CHEM_VALUE_NUMBER = 1,
    CHEM_VALUE_STRING = 2,
    CHEM_VALUE_BOOL   = 3
} ChemValueType;

struct ChemValue {
    ChemValueType type;
    double number;
    char *string;
    int boolean;
};

typedef enum {
    DECL_ELEMENT = 1,
    DECL_COMPOUND,
    DECL_ORGANIC,
    DECL_CONFIG,
    DECL_MOLARITY,
    DECL_REACTION,
    DECL_CONTEXT,
    DECL_DOUBLE
} ChemDeclType;

typedef enum {
    AST_SECTION = 1,
    AST_DECL,
    AST_ASSIGN,
    AST_ENV_ASSIGN,
    AST_EXPR_STMT,
    AST_REACTION,
    AST_IF,
    AST_WHILE,
    AST_TITRATE,
    AST_LITERAL,
    AST_VAR,
    AST_BINARY,
    AST_UNARY,
    AST_FUNCALL
} AstKind;

typedef enum {
    OP_ADD = 1,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_EQ,
    OP_NE,
    OP_LT,
    OP_GT,
    OP_AND,
    OP_OR,
    OP_NEG,
    OP_NOT,
    OP_SPECIES_JOIN
} ChemOperator;

typedef enum {
    FN_KIND_REACT = 1,
    FN_KIND_BALANCE,
    FN_KIND_PRINT,
    FN_KIND_RENDER,
    FN_KIND_GET_MASS,
    FN_KIND_GET_FORMULA,
    FN_KIND_GET_CONFIG,
    FN_KIND_GET_VALENCE_ELECTRON,
    FN_KIND_GET_QUANTUM_NUMBERS,
    FN_KIND_GET_ENTHALPY,
    FN_KIND_IS_SATURATED,
    FN_KIND_IS_ISOMER,
    FN_KIND_IS_METAL,
    FN_KIND_FIND_SERIES,
    FN_KIND_PRECIPITATE
} ChemFunctionKind;

struct AstArg {
    AstNode *expr;
    AstArg *next;
};

struct AstNode {
    AstKind kind;
    AstNode *next;
    union {
        struct {
            char *name;
            AstNode *body;
        } section;

        struct {
            ChemDeclType decl_type;
            char *name;
            AstNode *init;
        } decl;

        struct {
            char *name;
            AstNode *expr;
        } assign;

        struct {
            char *name;
            AstNode *expr;
        } env_assign;

        struct {
            AstNode *expr;
        } expr_stmt;

        struct {
            AstNode *lhs;
            AstNode *rhs;
            int arrow_type;
        } reaction;

        struct {
            AstNode *cond;
            AstNode *then_branch;
            AstNode *else_branch;
        } if_stmt;

        struct {
            AstNode *cond;
            AstNode *body;
        } while_stmt;

        struct {
            AstNode *body;
            AstNode *until_cond;
        } titrate_stmt;

        struct {
            ChemValue *value;
        } literal;

        struct {
            char *name;
            int is_environment;
        } var;

        struct {
            ChemOperator op;
            AstNode *left;
            AstNode *right;
        } binary;

        struct {
            ChemOperator op;
            AstNode *operand;
        } unary;

        struct {
            ChemFunctionKind fn;
            AstArg *args;
        } call;
    } as;
};

struct Symbol {
    char *name;
    ChemDeclType decl_type;
    ChemValue *value;
    int scope_level;
    Symbol *next;
};

extern FILE *yyin;
extern int yylineno;

int yyparse(void);
int yylex(void);
void yyerror(const char *msg);

char *chem_strdup(const char *src);
char *chem_concat2(const char *a, const char *b);
char *chem_concat3(const char *a, const char *b, const char *c);
char *chem_trim_quotes(const char *src);

#endif
