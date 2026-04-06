#ifndef CHEMICODE_SEMANTIC_H
#define CHEMICODE_SEMANTIC_H

#include "main.h"

void chem_semantic_init(void);
void chem_semantic_shutdown(void);
void chem_reset_runtime_state(void);

void chem_report_error(const char *fmt, ...);
void chem_report_warning(const char *fmt, ...);
void chem_report_lex_error(const char *token_text, int line);
int chem_error_count(void);
int chem_has_errors(void);

const char *chem_decl_type_name(ChemDeclType type);
int chem_decl_type_is_numeric(ChemDeclType type);
ChemValue *chem_default_value_for_type(ChemDeclType type);
ChemValue *chem_coerce_value(ChemDeclType type, const ChemValue *value, int *ok);

/* Values */
ChemValue *chem_make_number(double value);
ChemValue *chem_make_string(const char *value);
ChemValue *chem_make_bool(int value);
ChemValue *chem_copy_value(const ChemValue *value);
void chem_free_value(ChemValue *value);
double chem_to_number(const ChemValue *value);
int chem_to_bool(const ChemValue *value);
const char *chem_to_cstr(const ChemValue *value);

/* Expression helpers */
ChemValue *chem_value_add(const ChemValue *lhs, const ChemValue *rhs);
ChemValue *chem_value_sub(const ChemValue *lhs, const ChemValue *rhs);
ChemValue *chem_value_mul(const ChemValue *lhs, const ChemValue *rhs);
ChemValue *chem_value_div(const ChemValue *lhs, const ChemValue *rhs);
ChemValue *chem_value_eq(const ChemValue *lhs, const ChemValue *rhs);
ChemValue *chem_value_ne(const ChemValue *lhs, const ChemValue *rhs);
ChemValue *chem_value_lt(const ChemValue *lhs, const ChemValue *rhs);
ChemValue *chem_value_gt(const ChemValue *lhs, const ChemValue *rhs);
ChemValue *chem_value_and(const ChemValue *lhs, const ChemValue *rhs);
ChemValue *chem_value_or(const ChemValue *lhs, const ChemValue *rhs);
ChemValue *chem_value_neg(const ChemValue *value);
ChemValue *chem_value_not(const ChemValue *value);
ChemValue *chem_value_species_join(const ChemValue *lhs, const ChemValue *rhs);

/* Built-ins */
void chem_fprint(FILE *out, const ChemValue *value);
void chem_print(const ChemValue *value);
void chem_render(const ChemValue *value);
ChemValue *chem_get_mass(const ChemValue *value);
ChemValue *chem_get_formula(const ChemValue *value);
ChemValue *chem_get_config(const ChemValue *value);
ChemValue *chem_get_valence_electron(const ChemValue *value);
ChemValue *chem_get_quantum_numbers(const ChemValue *value);
ChemValue *chem_get_enthalpy(const ChemValue *value);
ChemValue *chem_is_saturated(const ChemValue *value);
ChemValue *chem_is_isomer(const ChemValue *lhs, const ChemValue *rhs);
ChemValue *chem_is_metal(const ChemValue *value);
ChemValue *chem_find_series(const ChemValue *value);
ChemValue *chem_precipitate(const ChemValue *lhs, const ChemValue *rhs);
ChemValue *chem_react(const ChemValue *lhs, const ChemValue *rhs);
ChemValue *chem_balance(const ChemValue *reaction);

/* Environment */
void chem_set_environment(const char *name, const ChemValue *value);
ChemValue *chem_get_environment(const char *name);

/* AST helpers */
AstNode *chem_ast_append(AstNode *list, AstNode *node);
AstArg *chem_ast_arg_append(AstArg *list, AstNode *expr);

AstNode *chem_ast_make_section(char *name, AstNode *body);
AstNode *chem_ast_make_decl(ChemDeclType decl_type, char *name, AstNode *init);
AstNode *chem_ast_make_assign(char *name, AstNode *expr);
AstNode *chem_ast_make_env_assign(char *name, AstNode *expr);
AstNode *chem_ast_make_expr_stmt(AstNode *expr);
AstNode *chem_ast_make_reaction(AstNode *lhs, AstNode *rhs, int arrow_type);
AstNode *chem_ast_make_if(AstNode *cond, AstNode *then_branch, AstNode *else_branch);
AstNode *chem_ast_make_while(AstNode *cond, AstNode *body);
AstNode *chem_ast_make_titrate(AstNode *body, AstNode *until_cond);

AstNode *chem_ast_make_literal(ChemValue *value);
AstNode *chem_ast_make_var(char *name, int is_environment);
AstNode *chem_ast_make_binary(ChemOperator op, AstNode *left, AstNode *right);
AstNode *chem_ast_make_unary(ChemOperator op, AstNode *operand);
AstNode *chem_ast_make_funcall(ChemFunctionKind fn, AstArg *args);

void chem_ast_set_root(AstNode *root);
AstNode *chem_ast_root(void);
void chem_ast_free(AstNode *root);

void chem_dump_ir(FILE *out, AstNode *root);
int chem_execute_program(AstNode *root);

#endif
