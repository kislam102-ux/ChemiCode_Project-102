#include "../include/symtab.h"
#include "../include/semantic.h"

#define SYMTAB_BUCKETS 211

static Symbol *g_table[SYMTAB_BUCKETS];
static int g_scope_level = 0;

static unsigned long sym_hash(const char *s) {
    unsigned long h = 5381UL;
    int c = 0;
    while ((c = (unsigned char)*s++) != 0) {
        h = ((h << 5) + h) + (unsigned long)c;
    }
    return h % SYMTAB_BUCKETS;
}

void symtab_init(void) {
    for (int i = 0; i < SYMTAB_BUCKETS; ++i) {
        g_table[i] = NULL;
    }
    g_scope_level = 0;
}

static void sym_free_node(Symbol *node) {
    if (!node) return;
    free(node->name);
    chem_free_value(node->value);
    free(node);
}

void symtab_free(void) {
    for (int i = 0; i < SYMTAB_BUCKETS; ++i) {
        Symbol *cur = g_table[i];
        while (cur) {
            Symbol *next = cur->next;
            sym_free_node(cur);
            cur = next;
        }
        g_table[i] = NULL;
    }
    g_scope_level = 0;
}

void symtab_enter_scope(void) {
    ++g_scope_level;
}

void symtab_exit_scope(void) {
    for (int i = 0; i < SYMTAB_BUCKETS; ++i) {
        Symbol *cur = g_table[i];
        Symbol *prev = NULL;
        while (cur) {
            Symbol *next = cur->next;
            if (cur->scope_level == g_scope_level) {
                if (prev) prev->next = next;
                else g_table[i] = next;
                sym_free_node(cur);
            } else {
                prev = cur;
            }
            cur = next;
        }
    }
    if (g_scope_level > 0) {
        --g_scope_level;
    }
}

int symtab_current_scope(void) {
    return g_scope_level;
}

Symbol *symtab_lookup_current_scope(const char *name) {
    if (!name) return NULL;
    unsigned long idx = sym_hash(name);
    Symbol *cur = g_table[idx];
    while (cur) {
        if (cur->scope_level == g_scope_level && strcmp(cur->name, name) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

Symbol *symtab_lookup(const char *name) {
    if (!name) return NULL;
    unsigned long idx = sym_hash(name);
    Symbol *cur = g_table[idx];
    Symbol *best = NULL;
    while (cur) {
        if (strcmp(cur->name, name) == 0) {
            if (!best || cur->scope_level > best->scope_level) {
                best = cur;
            }
        }
        cur = cur->next;
    }
    return best;
}

int symtab_declare(const char *name, ChemDeclType decl_type, const ChemValue *value) {
    if (!name) return 0;
    if (symtab_lookup_current_scope(name)) {
        chem_report_error("Semantic error: symbol '%s' already declared in current scope", name);
        return 0;
    }

    int ok = 1;
    ChemValue *coerced = NULL;
    if (value) {
        coerced = chem_coerce_value(decl_type, value, &ok);
    } else {
        coerced = chem_default_value_for_type(decl_type);
    }

    if (!ok || !coerced) {
        chem_report_error("Type error: cannot initialize %s '%s' with supplied value",
                          chem_decl_type_name(decl_type), name);
        chem_free_value(coerced);
        return 0;
    }

    unsigned long idx = sym_hash(name);
    Symbol *node = (Symbol *)calloc(1, sizeof(Symbol));
    if (!node) {
        fprintf(stderr, "Out of memory in symtab_declare\n");
        exit(EXIT_FAILURE);
    }

    node->name = chem_strdup(name);
    node->decl_type = decl_type;
    node->value = coerced;
    node->scope_level = g_scope_level;
    node->next = g_table[idx];
    g_table[idx] = node;
    return 1;
}

int symtab_assign(const char *name, const ChemValue *value) {
    Symbol *sym = symtab_lookup(name);
    if (!sym) {
        chem_report_error("Semantic error: symbol '%s' not declared before assignment", name);
        return 0;
    }

    int ok = 1;
    ChemValue *coerced = chem_coerce_value(sym->decl_type, value, &ok);
    if (!ok || !coerced) {
        chem_report_error("Type error: cannot assign value to %s '%s'",
                          chem_decl_type_name(sym->decl_type), name);
        chem_free_value(coerced);
        return 0;
    }

    chem_free_value(sym->value);
    sym->value = coerced;
    return 1;
}

void symtab_dump(FILE *out) {
    if (!out) out = stdout;
    fprintf(out, "\n=== Symbol Table Dump ===\n");
    fprintf(out, "Current visible scope depth: %d\n", g_scope_level);
    for (int i = 0; i < SYMTAB_BUCKETS; ++i) {
        Symbol *cur = g_table[i];
        while (cur) {
            fprintf(out, "scope=%d name=%s type=%s value=",
                    cur->scope_level, cur->name, chem_decl_type_name(cur->decl_type));
            chem_fprint(out, cur->value);
            cur = cur->next;
        }
    }
    fprintf(out, "=== End Symbol Table Dump ===\n");
}
