#ifndef CHEMICODE_SYMTAB_H
#define CHEMICODE_SYMTAB_H

#include "main.h"

void symtab_init(void);
void symtab_free(void);
void symtab_enter_scope(void);
void symtab_exit_scope(void);
int symtab_current_scope(void);

Symbol *symtab_lookup(const char *name);
Symbol *symtab_lookup_current_scope(const char *name);
int symtab_declare(const char *name, ChemDeclType decl_type, const ChemValue *value);
int symtab_assign(const char *name, const ChemValue *value);
void symtab_dump(FILE *out);

#endif
