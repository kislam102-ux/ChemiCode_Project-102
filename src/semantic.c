#include "../include/semantic.h"
#include "../include/symtab.h"

typedef struct {
    double temperature;
    double pressure;
} ChemEnvironment;

static ChemEnvironment g_env = {298.15, 1.0};
static AstNode *g_root = NULL;
static int g_error_count = 0;
static int g_ir_temp_counter = 0;
static int g_ir_label_counter = 0;

static AstNode *ast_new(AstKind kind) {
    AstNode *node = (AstNode *)calloc(1, sizeof(AstNode));
    if (!node) {
        fprintf(stderr, "Out of memory allocating AST node\n");
        exit(EXIT_FAILURE);
    }
    node->kind = kind;
    return node;
}

static AstArg *arg_new(AstNode *expr) {
    AstArg *arg = (AstArg *)calloc(1, sizeof(AstArg));
    if (!arg) {
        fprintf(stderr, "Out of memory allocating AST arg\n");
        exit(EXIT_FAILURE);
    }
    arg->expr = expr;
    return arg;
}

static int chem_string_equals_ci(const char *a, const char *b) {
    if (!a || !b) return 0;
    while (*a && *b) {
        int ca = tolower((unsigned char)*a);
        int cb = tolower((unsigned char)*b);
        if (ca != cb) return 0;
        ++a;
        ++b;
    }
    return *a == '\0' && *b == '\0';
}

static unsigned long chem_string_hash(const char *s) {
    unsigned long h = 1469598103934665603ULL;
    while (s && *s) {
        h ^= (unsigned char)(*s++);
        h *= 1099511628211ULL;
    }
    return h;
}

static char *chem_string_lower(const char *src) {
    char *buf = chem_strdup(src ? src : "");
    for (size_t i = 0; buf[i] != '\0'; ++i) {
        buf[i] = (char)tolower((unsigned char)buf[i]);
    }
    return buf;
}

static int chem_try_parse_numeric_string(const char *s, double *out) {
    if (!s) return 0;
    char *endptr = NULL;
    double value = strtod(s, &endptr);
    if (endptr && endptr != s && *endptr == '\0') {
        if (out) *out = value;
        return 1;
    }
    return 0;
}

static const char *chem_known_formula(const char *name) {
    if (!name) return NULL;
    if (chem_string_equals_ci(name, "sodium")) return "Na";
    if (chem_string_equals_ci(name, "chloride")) return "Cl";
    if (chem_string_equals_ci(name, "water")) return "H2O";
    if (chem_string_equals_ci(name, "salt")) return "NaCl";
    if (chem_string_equals_ci(name, "benzene")) return "C6H6";
    if (chem_string_equals_ci(name, "ethane")) return "C2H6";
    if (chem_string_equals_ci(name, "ethene")) return "C2H4";
    if (chem_string_equals_ci(name, "butane")) return "C4H10";
    if (chem_string_equals_ci(name, "isobutane")) return "C4H10";
    if (chem_string_equals_ci(name, "methane")) return "CH4";
    if (chem_string_equals_ci(name, "ethyne")) return "C2H2";
    if (chem_string_equals_ci(name, "oxygen")) return "O2";
    if (chem_string_equals_ci(name, "hydrogen")) return "H2";
    if (chem_string_equals_ci(name, "sodium chloride")) return "NaCl";
    return NULL;
}

typedef struct {
    const char *symbol;
    double mass;
    int valence;
    const char *config;
    int is_metal;
    const char *series;
} ElementInfo;

static const ElementInfo *chem_lookup_element(const char *s) {
    static const ElementInfo table[] = {
        {"H", 1.008, 1, "1s1", 0, "nonmetal"},
        {"C", 12.011, 4, "1s2 2s2 2p2", 0, "nonmetal"},
        {"N", 14.007, 5, "1s2 2s2 2p3", 0, "nonmetal"},
        {"O", 15.999, 6, "1s2 2s2 2p4", 0, "nonmetal"},
        {"Na", 22.990, 1, "[Ne] 3s1", 1, "alkali metal"},
        {"Cl", 35.45, 7, "[Ne] 3s2 3p5", 0, "halogen"},
        {"K", 39.098, 1, "[Ar] 4s1", 1, "alkali metal"},
        {"Ca", 40.078, 2, "[Ar] 4s2", 1, "alkaline earth metal"},
        {"Fe", 55.845, 2, "[Ar] 3d6 4s2", 1, "transition metal"},
        {"Cu", 63.546, 1, "[Ar] 3d10 4s1", 1, "transition metal"},
        {"Zn", 65.38, 2, "[Ar] 3d10 4s2", 1, "transition metal"},
        {NULL, 0.0, 0, NULL, 0, NULL}
    };
    for (int i = 0; table[i].symbol; ++i) {
        if (chem_string_equals_ci(s, table[i].symbol)) return &table[i];
    }
    return NULL;
}

static const char *chem_normalize_formula(const char *value) {
    const char *known = chem_known_formula(value);
    return known ? known : value;
}

static double chem_mass_from_formula(const char *formula) {
    double total = 0.0;
    size_t i = 0;
    while (formula && formula[i] != '\0') {
        if (!isupper((unsigned char)formula[i])) {
            ++i;
            continue;
        }

        char symbol[4] = {0};
        int si = 0;
        symbol[si++] = formula[i++];
        if (islower((unsigned char)formula[i]) && si < 3) {
            symbol[si++] = formula[i++];
        }
        symbol[si] = '\0';

        int count = 0;
        while (isdigit((unsigned char)formula[i])) {
            count = count * 10 + (formula[i] - '0');
            ++i;
        }
        if (count == 0) count = 1;

        const ElementInfo *info = chem_lookup_element(symbol);
        if (info) total += info->mass * (double)count;
        else total += 10.0 * (double)count;
    }
    return total;
}

void chem_semantic_init(void) {
    g_env.temperature = 298.15;
    g_env.pressure = 1.0;
    g_root = NULL;
    g_error_count = 0;
    g_ir_temp_counter = 0;
    g_ir_label_counter = 0;
}

void chem_semantic_shutdown(void) {
    chem_ast_free(g_root);
    g_root = NULL;
}

void chem_reset_runtime_state(void) {
    g_env.temperature = 298.15;
    g_env.pressure = 1.0;
}

void chem_report_error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "[ChemiCode][Error] ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    ++g_error_count;
}

void chem_report_warning(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "[ChemiCode][Warn] ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
}

void chem_report_lex_error(const char *token_text, int line) {
    chem_report_error("Unknown token '%s' at line %d", token_text ? token_text : "", line);
}

int chem_error_count(void) {
    return g_error_count;
}

int chem_has_errors(void) {
    return g_error_count > 0;
}

const char *chem_decl_type_name(ChemDeclType type) {
    switch (type) {
        case DECL_ELEMENT: return "Element";
        case DECL_COMPOUND: return "Compound";
        case DECL_ORGANIC: return "Organic";
        case DECL_CONFIG: return "Config";
        case DECL_MOLARITY: return "Molarity";
        case DECL_REACTION: return "Reaction";
        case DECL_CONTEXT: return "Context";
        case DECL_DOUBLE: return "Double";
        default: return "Unknown";
    }
}

int chem_decl_type_is_numeric(ChemDeclType type) {
    return type == DECL_DOUBLE || type == DECL_MOLARITY;
}

ChemValue *chem_default_value_for_type(ChemDeclType type) {
    if (chem_decl_type_is_numeric(type)) return chem_make_number(0.0);
    return chem_make_string("");
}

ChemValue *chem_coerce_value(ChemDeclType type, const ChemValue *value, int *ok) {
    int success = 1;
    ChemValue *out = NULL;
    if (!value) {
        out = chem_default_value_for_type(type);
    } else if (chem_decl_type_is_numeric(type)) {
        if (value->type == CHEM_VALUE_NUMBER || value->type == CHEM_VALUE_BOOL) {
            out = chem_make_number(chem_to_number(value));
        } else {
            double parsed = 0.0;
            if (chem_try_parse_numeric_string(value->string, &parsed)) {
                out = chem_make_number(parsed);
            } else {
                success = 0;
            }
        }
    } else {
        if (value->type == CHEM_VALUE_STRING) {
            out = chem_make_string(value->string);
        } else {
            out = chem_make_string(chem_to_cstr(value));
        }
    }

    if (ok) *ok = success;
    return out;
}

ChemValue *chem_make_number(double value) {
    ChemValue *out = (ChemValue *)calloc(1, sizeof(ChemValue));
    if (!out) {
        fprintf(stderr, "Out of memory in chem_make_number\n");
        exit(EXIT_FAILURE);
    }
    out->type = CHEM_VALUE_NUMBER;
    out->number = value;
    out->boolean = (value != 0.0);
    return out;
}

ChemValue *chem_make_string(const char *value) {
    ChemValue *out = (ChemValue *)calloc(1, sizeof(ChemValue));
    if (!out) {
        fprintf(stderr, "Out of memory in chem_make_string\n");
        exit(EXIT_FAILURE);
    }
    out->type = CHEM_VALUE_STRING;
    out->string = chem_strdup(value ? value : "");
    out->boolean = out->string[0] != '\0';
    return out;
}

ChemValue *chem_make_bool(int value) {
    ChemValue *out = (ChemValue *)calloc(1, sizeof(ChemValue));
    if (!out) {
        fprintf(stderr, "Out of memory in chem_make_bool\n");
        exit(EXIT_FAILURE);
    }
    out->type = CHEM_VALUE_BOOL;
    out->boolean = value ? 1 : 0;
    out->number = out->boolean ? 1.0 : 0.0;
    out->string = chem_strdup(out->boolean ? "true" : "false");
    return out;
}

ChemValue *chem_copy_value(const ChemValue *value) {
    if (!value) return chem_make_string("");
    switch (value->type) {
        case CHEM_VALUE_NUMBER: return chem_make_number(value->number);
        case CHEM_VALUE_BOOL: return chem_make_bool(value->boolean);
        case CHEM_VALUE_STRING: return chem_make_string(value->string ? value->string : "");
        default: return chem_make_string("");
    }
}

void chem_free_value(ChemValue *value) {
    if (!value) return;
    free(value->string);
    free(value);
}

double chem_to_number(const ChemValue *value) {
    double parsed = 0.0;
    if (!value) return 0.0;
    if (value->type == CHEM_VALUE_NUMBER) return value->number;
    if (value->type == CHEM_VALUE_BOOL) return value->boolean ? 1.0 : 0.0;
    if (value->type == CHEM_VALUE_STRING && chem_try_parse_numeric_string(value->string, &parsed)) return parsed;
    return (double)(chem_string_hash(chem_to_cstr(value)) % 1000U) / 10.0;
}

int chem_to_bool(const ChemValue *value) {
    if (!value) return 0;
    if (value->type == CHEM_VALUE_BOOL) return value->boolean;
    if (value->type == CHEM_VALUE_NUMBER) return value->number != 0.0;
    if (value->type == CHEM_VALUE_STRING) return value->string && value->string[0] != '\0';
    return 0;
}

const char *chem_to_cstr(const ChemValue *value) {
    static char buf[128];
    if (!value) return "";
    if (value->type == CHEM_VALUE_STRING) return value->string ? value->string : "";
    if (value->type == CHEM_VALUE_BOOL) return value->boolean ? "true" : "false";
    snprintf(buf, sizeof(buf), "%.6g", value->number);
    return buf;
}

static ChemValue *chem_make_cmp(int ok) {
    return chem_make_bool(ok ? 1 : 0);
}

ChemValue *chem_value_add(const ChemValue *lhs, const ChemValue *rhs) {
    if (!lhs || !rhs) return chem_make_number(0.0);
    if (lhs->type == CHEM_VALUE_STRING || rhs->type == CHEM_VALUE_STRING) {
        char *joined = chem_concat2(chem_to_cstr(lhs), chem_to_cstr(rhs));
        ChemValue *out = chem_make_string(joined);
        free(joined);
        return out;
    }
    return chem_make_number(chem_to_number(lhs) + chem_to_number(rhs));
}

ChemValue *chem_value_sub(const ChemValue *lhs, const ChemValue *rhs) {
    return chem_make_number(chem_to_number(lhs) - chem_to_number(rhs));
}

ChemValue *chem_value_mul(const ChemValue *lhs, const ChemValue *rhs) {
    return chem_make_number(chem_to_number(lhs) * chem_to_number(rhs));
}

ChemValue *chem_value_div(const ChemValue *lhs, const ChemValue *rhs) {
    double denom = chem_to_number(rhs);
    if (denom == 0.0) {
        chem_report_error("Division by zero encountered");
        return chem_make_number(0.0);
    }
    return chem_make_number(chem_to_number(lhs) / denom);
}

ChemValue *chem_value_eq(const ChemValue *lhs, const ChemValue *rhs) {
    if (lhs->type == CHEM_VALUE_STRING || rhs->type == CHEM_VALUE_STRING) {
        return chem_make_cmp(strcmp(chem_to_cstr(lhs), chem_to_cstr(rhs)) == 0);
    }
    return chem_make_cmp(chem_to_number(lhs) == chem_to_number(rhs));
}

ChemValue *chem_value_ne(const ChemValue *lhs, const ChemValue *rhs) {
    ChemValue *eq = chem_value_eq(lhs, rhs);
    ChemValue *out = chem_make_bool(!chem_to_bool(eq));
    chem_free_value(eq);
    return out;
}

ChemValue *chem_value_lt(const ChemValue *lhs, const ChemValue *rhs) {
    return chem_make_cmp(chem_to_number(lhs) < chem_to_number(rhs));
}

ChemValue *chem_value_gt(const ChemValue *lhs, const ChemValue *rhs) {
    return chem_make_cmp(chem_to_number(lhs) > chem_to_number(rhs));
}

ChemValue *chem_value_and(const ChemValue *lhs, const ChemValue *rhs) {
    return chem_make_bool(chem_to_bool(lhs) && chem_to_bool(rhs));
}

ChemValue *chem_value_or(const ChemValue *lhs, const ChemValue *rhs) {
    return chem_make_bool(chem_to_bool(lhs) || chem_to_bool(rhs));
}

ChemValue *chem_value_neg(const ChemValue *value) {
    return chem_make_number(-chem_to_number(value));
}

ChemValue *chem_value_not(const ChemValue *value) {
    return chem_make_bool(!chem_to_bool(value));
}

ChemValue *chem_value_species_join(const ChemValue *lhs, const ChemValue *rhs) {
    char *tmp = chem_concat3(chem_to_cstr(lhs), " + ", chem_to_cstr(rhs));
    ChemValue *out = chem_make_string(tmp);
    free(tmp);
    return out;
}

void chem_fprint(FILE *out, const ChemValue *value) {
    if (!out) out = stdout;
    if (!value) {
        fprintf(out, "<null>\n");
        return;
    }
    switch (value->type) {
        case CHEM_VALUE_NUMBER:
            fprintf(out, "%.6g\n", value->number);
            break;
        case CHEM_VALUE_BOOL:
            fprintf(out, "%s\n", value->boolean ? "true" : "false");
            break;
        case CHEM_VALUE_STRING:
            fprintf(out, "%s\n", value->string ? value->string : "");
            break;
        default:
            fprintf(out, "<unknown>\n");
            break;
    }
}

void chem_print(const ChemValue *value) {
    chem_fprint(stdout, value);
}

void chem_render(const ChemValue *value) {
    printf("[Render] %s\n", chem_to_cstr(value));
}

ChemValue *chem_get_formula(const ChemValue *value) {
    const char *canonical = chem_normalize_formula(chem_to_cstr(value));
    return chem_make_string(canonical);
}

ChemValue *chem_get_mass(const ChemValue *value) {
    ChemValue *formula = chem_get_formula(value);
    double mass = chem_mass_from_formula(chem_to_cstr(formula));
    chem_free_value(formula);
    if (mass <= 0.0) mass = chem_to_number(value);
    return chem_make_number(mass);
}

ChemValue *chem_get_config(const ChemValue *value) {
    const char *s = chem_normalize_formula(chem_to_cstr(value));
    const ElementInfo *info = chem_lookup_element(s);
    if (info) return chem_make_string(info->config);

    char buf[256];
    snprintf(buf, sizeof(buf), "config[%s]=heuristic", chem_to_cstr(value));
    return chem_make_string(buf);
}

ChemValue *chem_get_valence_electron(const ChemValue *value) {
    const char *s = chem_normalize_formula(chem_to_cstr(value));
    const ElementInfo *info = chem_lookup_element(s);
    if (info) return chem_make_number((double)info->valence);
    return chem_make_number((double)((chem_string_hash(s) % 8U) + 1U));
}

ChemValue *chem_get_quantum_numbers(const ChemValue *value) {
    const char *s = chem_normalize_formula(chem_to_cstr(value));
    unsigned long h = chem_string_hash(s);
    char buf[256];
    snprintf(buf, sizeof(buf), "(n=%lu,l=%lu,m=%ld,s=%s)",
             (h % 4U) + 1U,
             h % 3U,
             (long)((h % 5U) - 2L),
             ((h % 2U) == 0U) ? "+1/2" : "-1/2");
    return chem_make_string(buf);
}

ChemValue *chem_get_enthalpy(const ChemValue *value) {
    const char *s = chem_to_cstr(value);
    if (chem_string_equals_ci(s, "Combustion")) return chem_make_number(-393.5);
    if (chem_string_equals_ci(s, "Neutralization")) return chem_make_number(-57.3);
    return chem_make_number(((double)(chem_string_hash(s) % 500U) / 10.0) - 100.0);
}

ChemValue *chem_is_saturated(const ChemValue *value) {
    char *lower = chem_string_lower(chem_to_cstr(value));
    int saturated = 1;
    if (strstr(lower, "ene") || strstr(lower, "yne") || strchr(lower, '=')) {
        saturated = 0;
    }
    free(lower);
    return chem_make_bool(saturated);
}

ChemValue *chem_is_isomer(const ChemValue *lhs, const ChemValue *rhs) {
    ChemValue *f1 = chem_get_formula(lhs);
    ChemValue *f2 = chem_get_formula(rhs);
    int eq = strcmp(chem_to_cstr(f1), chem_to_cstr(f2)) == 0 &&
             strcmp(chem_to_cstr(lhs), chem_to_cstr(rhs)) != 0;
    chem_free_value(f1);
    chem_free_value(f2);
    return chem_make_bool(eq);
}

ChemValue *chem_is_metal(const ChemValue *value) {
    const char *s = chem_normalize_formula(chem_to_cstr(value));
    const ElementInfo *info = chem_lookup_element(s);
    return chem_make_bool(info ? info->is_metal : 0);
}

ChemValue *chem_find_series(const ChemValue *value) {
    char *lower = chem_string_lower(chem_to_cstr(value));
    const char *normalized = chem_normalize_formula(chem_to_cstr(value));
    const ElementInfo *info = chem_lookup_element(normalized);
    ChemValue *out = NULL;

    if (info) {
        out = chem_make_string(info->series);
    } else if (strstr(lower, "benz")) {
        out = chem_make_string("aromatic");
    } else if (strstr(lower, "ane")) {
        out = chem_make_string("alkane");
    } else if (strstr(lower, "ene")) {
        out = chem_make_string("alkene");
    } else if (strstr(lower, "yne")) {
        out = chem_make_string("alkyne");
    } else {
        out = chem_make_string("unclassified");
    }

    free(lower);
    return out;
}

ChemValue *chem_precipitate(const ChemValue *lhs, const ChemValue *rhs) {
    const char *a = chem_to_cstr(lhs);
    const char *b = chem_to_cstr(rhs);
    if ((chem_string_equals_ci(a, "AgNO3") && chem_string_equals_ci(b, "NaCl")) ||
        (chem_string_equals_ci(a, "NaCl") && chem_string_equals_ci(b, "AgNO3"))) {
        return chem_make_string("AgCl(s) precipitate");
    }
    char buf[256];
    snprintf(buf, sizeof(buf), "No confirmed precipitate for %s + %s", a, b);
    return chem_make_string(buf);
}

ChemValue *chem_react(const ChemValue *lhs, const ChemValue *rhs) {
    const char *a = chem_to_cstr(lhs);
    const char *b = chem_to_cstr(rhs);
    if ((chem_string_equals_ci(a, "HCl") && chem_string_equals_ci(b, "NaOH")) ||
        (chem_string_equals_ci(a, "NaOH") && chem_string_equals_ci(b, "HCl"))) {
        return chem_make_string("NaCl + H2O");
    }
    if ((chem_string_equals_ci(a, "AgNO3") && chem_string_equals_ci(b, "NaCl")) ||
        (chem_string_equals_ci(a, "NaCl") && chem_string_equals_ci(b, "AgNO3"))) {
        return chem_make_string("AgCl + NaNO3");
    }
    char buf[256];
    snprintf(buf, sizeof(buf), "%s + %s -> simulated_products", a, b);
    return chem_make_string(buf);
}

ChemValue *chem_balance(const ChemValue *reaction) {
    const char *s = chem_to_cstr(reaction);
    if (chem_string_equals_ci(s, "HCl + NaOH -> NaCl + H2O")) {
        return chem_make_string("1 HCl + 1 NaOH -> 1 NaCl + 1 H2O");
    }
    char buf[512];
    snprintf(buf, sizeof(buf), "balanced[%s]", s);
    return chem_make_string(buf);
}

void chem_set_environment(const char *name, const ChemValue *value) {
    double numeric = chem_to_number(value);
    if (strcmp(name, "Temperature") == 0) {
        g_env.temperature = numeric;
        printf("[Environment] Temperature set to %.3f K\n", g_env.temperature);
    } else if (strcmp(name, "Pressure") == 0) {
        g_env.pressure = numeric;
        printf("[Environment] Pressure set to %.3f atm\n", g_env.pressure);
    } else {
        chem_report_warning("Unknown environment setting '%s' ignored", name);
    }
}

ChemValue *chem_get_environment(const char *name) {
    if (strcmp(name, "Temperature") == 0) return chem_make_number(g_env.temperature);
    if (strcmp(name, "Pressure") == 0) return chem_make_number(g_env.pressure);
    return chem_make_number(0.0);
}

/* AST Constructors */
AstNode *chem_ast_append(AstNode *list, AstNode *node) {
    if (!node) return list;
    if (!list) return node;
    AstNode *cur = list;
    while (cur->next) cur = cur->next;
    cur->next = node;
    return list;
}

AstArg *chem_ast_arg_append(AstArg *list, AstNode *expr) {
    AstArg *node = arg_new(expr);
    if (!list) return node;
    AstArg *cur = list;
    while (cur->next) cur = cur->next;
    cur->next = node;
    return list;
}

AstNode *chem_ast_make_section(char *name, AstNode *body) {
    AstNode *node = ast_new(AST_SECTION);
    node->as.section.name = name;
    node->as.section.body = body;
    return node;
}

AstNode *chem_ast_make_decl(ChemDeclType decl_type, char *name, AstNode *init) {
    AstNode *node = ast_new(AST_DECL);
    node->as.decl.decl_type = decl_type;
    node->as.decl.name = name;
    node->as.decl.init = init;
    return node;
}

AstNode *chem_ast_make_assign(char *name, AstNode *expr) {
    AstNode *node = ast_new(AST_ASSIGN);
    node->as.assign.name = name;
    node->as.assign.expr = expr;
    return node;
}

AstNode *chem_ast_make_env_assign(char *name, AstNode *expr) {
    AstNode *node = ast_new(AST_ENV_ASSIGN);
    node->as.env_assign.name = name;
    node->as.env_assign.expr = expr;
    return node;
}

AstNode *chem_ast_make_expr_stmt(AstNode *expr) {
    AstNode *node = ast_new(AST_EXPR_STMT);
    node->as.expr_stmt.expr = expr;
    return node;
}

AstNode *chem_ast_make_reaction(AstNode *lhs, AstNode *rhs, int arrow_type) {
    AstNode *node = ast_new(AST_REACTION);
    node->as.reaction.lhs = lhs;
    node->as.reaction.rhs = rhs;
    node->as.reaction.arrow_type = arrow_type;
    return node;
}

AstNode *chem_ast_make_if(AstNode *cond, AstNode *then_branch, AstNode *else_branch) {
    AstNode *node = ast_new(AST_IF);
    node->as.if_stmt.cond = cond;
    node->as.if_stmt.then_branch = then_branch;
    node->as.if_stmt.else_branch = else_branch;
    return node;
}

AstNode *chem_ast_make_while(AstNode *cond, AstNode *body) {
    AstNode *node = ast_new(AST_WHILE);
    node->as.while_stmt.cond = cond;
    node->as.while_stmt.body = body;
    return node;
}

AstNode *chem_ast_make_titrate(AstNode *body, AstNode *until_cond) {
    AstNode *node = ast_new(AST_TITRATE);
    node->as.titrate_stmt.body = body;
    node->as.titrate_stmt.until_cond = until_cond;
    return node;
}

AstNode *chem_ast_make_literal(ChemValue *value) {
    AstNode *node = ast_new(AST_LITERAL);
    node->as.literal.value = value;
    return node;
}

AstNode *chem_ast_make_var(char *name, int is_environment) {
    AstNode *node = ast_new(AST_VAR);
    node->as.var.name = name;
    node->as.var.is_environment = is_environment;
    return node;
}

AstNode *chem_ast_make_binary(ChemOperator op, AstNode *left, AstNode *right) {
    AstNode *node = ast_new(AST_BINARY);
    node->as.binary.op = op;
    node->as.binary.left = left;
    node->as.binary.right = right;
    return node;
}

AstNode *chem_ast_make_unary(ChemOperator op, AstNode *operand) {
    AstNode *node = ast_new(AST_UNARY);
    node->as.unary.op = op;
    node->as.unary.operand = operand;
    return node;
}

AstNode *chem_ast_make_funcall(ChemFunctionKind fn, AstArg *args) {
    AstNode *node = ast_new(AST_FUNCALL);
    node->as.call.fn = fn;
    node->as.call.args = args;
    return node;
}

void chem_ast_set_root(AstNode *root) {
    g_root = root;
}

AstNode *chem_ast_root(void) {
    return g_root;
}

static void chem_ast_arg_free(AstArg *arg) {
    while (arg) {
        AstArg *next = arg->next;
        chem_ast_free(arg->expr);
        free(arg);
        arg = next;
    }
}

void chem_ast_free(AstNode *root) {
    while (root) {
        AstNode *next = root->next;
        switch (root->kind) {
            case AST_SECTION:
                free(root->as.section.name);
                chem_ast_free(root->as.section.body);
                break;
            case AST_DECL:
                free(root->as.decl.name);
                chem_ast_free(root->as.decl.init);
                break;
            case AST_ASSIGN:
                free(root->as.assign.name);
                chem_ast_free(root->as.assign.expr);
                break;
            case AST_ENV_ASSIGN:
                free(root->as.env_assign.name);
                chem_ast_free(root->as.env_assign.expr);
                break;
            case AST_EXPR_STMT:
                chem_ast_free(root->as.expr_stmt.expr);
                break;
            case AST_REACTION:
                chem_ast_free(root->as.reaction.lhs);
                chem_ast_free(root->as.reaction.rhs);
                break;
            case AST_IF:
                chem_ast_free(root->as.if_stmt.cond);
                chem_ast_free(root->as.if_stmt.then_branch);
                chem_ast_free(root->as.if_stmt.else_branch);
                break;
            case AST_WHILE:
                chem_ast_free(root->as.while_stmt.cond);
                chem_ast_free(root->as.while_stmt.body);
                break;
            case AST_TITRATE:
                chem_ast_free(root->as.titrate_stmt.body);
                chem_ast_free(root->as.titrate_stmt.until_cond);
                break;
            case AST_LITERAL:
                chem_free_value(root->as.literal.value);
                break;
            case AST_VAR:
                free(root->as.var.name);
                break;
            case AST_BINARY:
                chem_ast_free(root->as.binary.left);
                chem_ast_free(root->as.binary.right);
                break;
            case AST_UNARY:
                chem_ast_free(root->as.unary.operand);
                break;
            case AST_FUNCALL:
                chem_ast_arg_free(root->as.call.args);
                break;
            default:
                break;
        }
        free(root);
        root = next;
    }
}

static ChemValue *eval_expr(AstNode *node);

static int arg_count(AstArg *args) {
    int n = 0;
    while (args) { ++n; args = args->next; }
    return n;
}

static ChemValue *eval_call(ChemFunctionKind fn, AstArg *args) {
    ChemValue *v1 = NULL;
    ChemValue *v2 = NULL;
    int argc = arg_count(args);

    if (args) v1 = eval_expr(args->expr);
    if (args && args->next) v2 = eval_expr(args->next->expr);

    ChemValue *result = NULL;
    switch (fn) {
        case FN_KIND_PRINT:
            if (argc != 1) chem_report_error("PRINT expects exactly 1 argument");
            else chem_print(v1);
            result = v1 ? chem_copy_value(v1) : chem_make_string("");
            break;
        case FN_KIND_RENDER:
            if (argc != 1) chem_report_error("RENDER expects exactly 1 argument");
            else chem_render(v1);
            result = v1 ? chem_copy_value(v1) : chem_make_string("");
            break;
        case FN_KIND_REACT:
            if (argc != 2) chem_report_error("REACT expects exactly 2 arguments");
            result = (argc == 2) ? chem_react(v1, v2) : chem_make_string("");
            break;
        case FN_KIND_BALANCE:
            if (argc != 1) chem_report_error("BALANCE expects exactly 1 argument");
            result = (argc == 1) ? chem_balance(v1) : chem_make_string("");
            break;
        case FN_KIND_GET_MASS:
            if (argc != 1) chem_report_error("GET_MASS expects exactly 1 argument");
            result = (argc == 1) ? chem_get_mass(v1) : chem_make_number(0.0);
            break;
        case FN_KIND_GET_FORMULA:
            if (argc != 1) chem_report_error("GET_FORMULA expects exactly 1 argument");
            result = (argc == 1) ? chem_get_formula(v1) : chem_make_string("");
            break;
        case FN_KIND_GET_CONFIG:
            if (argc != 1) chem_report_error("GET_CONFIG expects exactly 1 argument");
            result = (argc == 1) ? chem_get_config(v1) : chem_make_string("");
            break;
        case FN_KIND_GET_VALENCE_ELECTRON:
            if (argc != 1) chem_report_error("GET_VALENCE_ELECTRON expects exactly 1 argument");
            result = (argc == 1) ? chem_get_valence_electron(v1) : chem_make_number(0.0);
            break;
        case FN_KIND_GET_QUANTUM_NUMBERS:
            if (argc != 1) chem_report_error("GET_QUANTUM_NUMBERS expects exactly 1 argument");
            result = (argc == 1) ? chem_get_quantum_numbers(v1) : chem_make_string("");
            break;
        case FN_KIND_GET_ENTHALPY:
            if (argc != 1) chem_report_error("GET_ENTHALPY expects exactly 1 argument");
            result = (argc == 1) ? chem_get_enthalpy(v1) : chem_make_number(0.0);
            break;
        case FN_KIND_IS_SATURATED:
            if (argc != 1) chem_report_error("IS_SATURATED expects exactly 1 argument");
            result = (argc == 1) ? chem_is_saturated(v1) : chem_make_bool(0);
            break;
        case FN_KIND_IS_ISOMER:
            if (argc != 2) chem_report_error("IS_ISOMER expects exactly 2 arguments");
            result = (argc == 2) ? chem_is_isomer(v1, v2) : chem_make_bool(0);
            break;
        case FN_KIND_IS_METAL:
            if (argc != 1) chem_report_error("IS_METAL expects exactly 1 argument");
            result = (argc == 1) ? chem_is_metal(v1) : chem_make_bool(0);
            break;
        case FN_KIND_FIND_SERIES:
            if (argc != 1) chem_report_error("FIND_SERIES expects exactly 1 argument");
            result = (argc == 1) ? chem_find_series(v1) : chem_make_string("");
            break;
        case FN_KIND_PRECIPITATE:
            if (argc != 2) chem_report_error("PRECIPITATE expects exactly 2 arguments");
            result = (argc == 2) ? chem_precipitate(v1, v2) : chem_make_string("");
            break;
        default:
            chem_report_error("Unknown function call");
            result = chem_make_string("");
            break;
    }

    chem_free_value(v1);
    chem_free_value(v2);
    return result;
}

static ChemValue *eval_expr(AstNode *node) {
    if (!node) return chem_make_string("");
    switch (node->kind) {
        case AST_LITERAL:
            return chem_copy_value(node->as.literal.value);
        case AST_VAR:
            if (node->as.var.is_environment) {
                return chem_get_environment(node->as.var.name);
            } else {
                Symbol *sym = symtab_lookup(node->as.var.name);
                if (!sym) {
                    chem_report_error("Use of undeclared variable '%s'", node->as.var.name);
                    return chem_make_string("");
                }
                return chem_copy_value(sym->value);
            }
        case AST_UNARY: {
            ChemValue *operand = eval_expr(node->as.unary.operand);
            ChemValue *result = NULL;
            if (node->as.unary.op == OP_NEG) result = chem_value_neg(operand);
            else if (node->as.unary.op == OP_NOT) result = chem_value_not(operand);
            else result = chem_make_string("");
            chem_free_value(operand);
            return result;
        }
        case AST_BINARY: {
            ChemValue *lhs = eval_expr(node->as.binary.left);
            ChemValue *rhs = eval_expr(node->as.binary.right);
            ChemValue *result = NULL;
            switch (node->as.binary.op) {
                case OP_ADD: result = chem_value_add(lhs, rhs); break;
                case OP_SUB: result = chem_value_sub(lhs, rhs); break;
                case OP_MUL: result = chem_value_mul(lhs, rhs); break;
                case OP_DIV: result = chem_value_div(lhs, rhs); break;
                case OP_EQ: result = chem_value_eq(lhs, rhs); break;
                case OP_NE: result = chem_value_ne(lhs, rhs); break;
                case OP_LT: result = chem_value_lt(lhs, rhs); break;
                case OP_GT: result = chem_value_gt(lhs, rhs); break;
                case OP_AND: result = chem_value_and(lhs, rhs); break;
                case OP_OR: result = chem_value_or(lhs, rhs); break;
                case OP_SPECIES_JOIN: result = chem_value_species_join(lhs, rhs); break;
                default: result = chem_make_string(""); break;
            }
            chem_free_value(lhs);
            chem_free_value(rhs);
            return result;
        }
        case AST_FUNCALL:
            return eval_call(node->as.call.fn, node->as.call.args);
        default:
            chem_report_error("Internal error: invalid expression node");
            return chem_make_string("");
    }
}

static int exec_block(AstNode *stmts, int create_scope);

static int exec_stmt(AstNode *node) {
    if (!node) return 0;

    switch (node->kind) {
        case AST_SECTION:
            printf("[Section Enter] %s\n", node->as.section.name ? node->as.section.name : "<anonymous>");
            exec_block(node->as.section.body, 1);
            printf("[Section Exit] %s\n", node->as.section.name ? node->as.section.name : "<anonymous>");
            return 0;
        case AST_DECL: {
            ChemValue *value = node->as.decl.init ? eval_expr(node->as.decl.init) : NULL;
            symtab_declare(node->as.decl.name, node->as.decl.decl_type, value);
            chem_free_value(value);
            return 0;
        }
        case AST_ASSIGN: {
            ChemValue *value = eval_expr(node->as.assign.expr);
            symtab_assign(node->as.assign.name, value);
            chem_free_value(value);
            return 0;
        }
        case AST_ENV_ASSIGN: {
            ChemValue *value = eval_expr(node->as.env_assign.expr);
            chem_set_environment(node->as.env_assign.name, value);
            chem_free_value(value);
            return 0;
        }
        case AST_EXPR_STMT: {
            ChemValue *tmp = eval_expr(node->as.expr_stmt.expr);
            chem_free_value(tmp);
            return 0;
        }
        case AST_REACTION: {
            ChemValue *lhs = eval_expr(node->as.reaction.lhs);
            ChemValue *rhs = eval_expr(node->as.reaction.rhs);
            const char *arrow = (node->as.reaction.arrow_type == 2) ? "=>" : "->";
            printf("[Reaction] %s %s %s\n", chem_to_cstr(lhs), arrow, chem_to_cstr(rhs));
            chem_free_value(lhs);
            chem_free_value(rhs);
            return 0;
        }
        case AST_IF: {
            ChemValue *cond = eval_expr(node->as.if_stmt.cond);
            int truth = chem_to_bool(cond);
            chem_free_value(cond);
            if (truth) return exec_block(node->as.if_stmt.then_branch, 1);
            if (node->as.if_stmt.else_branch) return exec_block(node->as.if_stmt.else_branch, 1);
            return 0;
        }
        case AST_WHILE: {
            int guard = 0;
            while (1) {
                ChemValue *cond = eval_expr(node->as.while_stmt.cond);
                int truth = chem_to_bool(cond);
                chem_free_value(cond);
                if (!truth) break;
                if (++guard > 100000) {
                    chem_report_error("WHILE loop exceeded safe iteration limit");
                    break;
                }
                exec_block(node->as.while_stmt.body, 1);
            }
            return 0;
        }
        case AST_TITRATE: {
            int guard = 0;
            do {
                if (++guard > 100000) {
                    chem_report_error("TITRATE loop exceeded safe iteration limit");
                    break;
                }
                exec_block(node->as.titrate_stmt.body, 1);
                ChemValue *cond = eval_expr(node->as.titrate_stmt.until_cond);
                int done = chem_to_bool(cond);
                chem_free_value(cond);
                if (done) break;
            } while (1);
            return 0;
        }
        default:
            chem_report_error("Internal error: invalid statement node");
            return 1;
    }
}

static int exec_block(AstNode *stmts, int create_scope) {
    if (create_scope) symtab_enter_scope();
    for (AstNode *cur = stmts; cur; cur = cur->next) {
        exec_stmt(cur);
    }
    if (create_scope) symtab_exit_scope();
    return chem_has_errors() ? 1 : 0;
}

int chem_execute_program(AstNode *root) {
    chem_reset_runtime_state();
    for (AstNode *cur = root; cur; cur = cur->next) {
        exec_stmt(cur);
    }
    return chem_has_errors() ? 1 : 0;
}

/* IR Dump */
static const char *op_name(ChemOperator op) {
    switch (op) {
        case OP_ADD: return "ADD";
        case OP_SUB: return "SUB";
        case OP_MUL: return "MUL";
        case OP_DIV: return "DIV";
        case OP_EQ: return "EQ";
        case OP_NE: return "NE";
        case OP_LT: return "LT";
        case OP_GT: return "GT";
        case OP_AND: return "AND";
        case OP_OR: return "OR";
        case OP_NEG: return "NEG";
        case OP_NOT: return "NOT";
        case OP_SPECIES_JOIN: return "SPECIES_JOIN";
        default: return "UNKNOWN_OP";
    }
}

static const char *fn_name(ChemFunctionKind fn) {
    switch (fn) {
        case FN_KIND_REACT: return "REACT";
        case FN_KIND_BALANCE: return "BALANCE";
        case FN_KIND_PRINT: return "PRINT";
        case FN_KIND_RENDER: return "RENDER";
        case FN_KIND_GET_MASS: return "GET_MASS";
        case FN_KIND_GET_FORMULA: return "GET_FORMULA";
        case FN_KIND_GET_CONFIG: return "GET_CONFIG";
        case FN_KIND_GET_VALENCE_ELECTRON: return "GET_VALENCE_ELECTRON";
        case FN_KIND_GET_QUANTUM_NUMBERS: return "GET_QUANTUM_NUMBERS";
        case FN_KIND_GET_ENTHALPY: return "GET_ENTHALPY";
        case FN_KIND_IS_SATURATED: return "IS_SATURATED";
        case FN_KIND_IS_ISOMER: return "IS_ISOMER";
        case FN_KIND_IS_METAL: return "IS_METAL";
        case FN_KIND_FIND_SERIES: return "FIND_SERIES";
        case FN_KIND_PRECIPITATE: return "PRECIPITATE";
        default: return "UNKNOWN_FN";
    }
}

static int next_temp(void) { return ++g_ir_temp_counter; }
static int next_label(void) { return ++g_ir_label_counter; }

static int dump_expr_ir(FILE *out, AstNode *node) {
    if (!node) return -1;
    switch (node->kind) {
        case AST_LITERAL: {
            int t = next_temp();
            fprintf(out, "  t%d = CONST %s\n", t, chem_to_cstr(node->as.literal.value));
            return t;
        }
        case AST_VAR: {
            int t = next_temp();
            fprintf(out, "  t%d = LOAD %s%s\n", t,
                    node->as.var.is_environment ? "ENV." : "",
                    node->as.var.name);
            return t;
        }
        case AST_UNARY: {
            int x = dump_expr_ir(out, node->as.unary.operand);
            int t = next_temp();
            fprintf(out, "  t%d = %s t%d\n", t, op_name(node->as.unary.op), x);
            return t;
        }
        case AST_BINARY: {
            int l = dump_expr_ir(out, node->as.binary.left);
            int r = dump_expr_ir(out, node->as.binary.right);
            int t = next_temp();
            fprintf(out, "  t%d = %s t%d, t%d\n", t, op_name(node->as.binary.op), l, r);
            return t;
        }
        case AST_FUNCALL: {
            int first = -1;
            int idx = 0;
            for (AstArg *arg = node->as.call.args; arg; arg = arg->next) {
                int t = dump_expr_ir(out, arg->expr);
                if (first == -1) first = t;
                fprintf(out, "  ARG %d = t%d\n", idx++, t);
            }
            int t = next_temp();
            fprintf(out, "  t%d = CALL %s %d\n", t, fn_name(node->as.call.fn), idx);
            return t;
        }
        default:
            return -1;
    }
}

static void dump_stmt_ir(FILE *out, AstNode *node) {
    if (!node) return;
    switch (node->kind) {
        case AST_SECTION:
            fprintf(out, "SECTION %s BEGIN\n", node->as.section.name);
            for (AstNode *cur = node->as.section.body; cur; cur = cur->next) {
                dump_stmt_ir(out, cur);
            }
            fprintf(out, "SECTION %s END\n", node->as.section.name);
            break;
        case AST_DECL: {
            fprintf(out, "  DECL %s %s\n",
                    chem_decl_type_name(node->as.decl.decl_type),
                    node->as.decl.name);
            if (node->as.decl.init) {
                int t = dump_expr_ir(out, node->as.decl.init);
                fprintf(out, "  STORE %s, t%d\n", node->as.decl.name, t);
            }
            break;
        }
        case AST_ASSIGN: {
            int t = dump_expr_ir(out, node->as.assign.expr);
            fprintf(out, "  STORE %s, t%d\n", node->as.assign.name, t);
            break;
        }
        case AST_ENV_ASSIGN: {
            int t = dump_expr_ir(out, node->as.env_assign.expr);
            fprintf(out, "  STORE ENV.%s, t%d\n", node->as.env_assign.name, t);
            break;
        }
        case AST_EXPR_STMT: {
            dump_expr_ir(out, node->as.expr_stmt.expr);
            break;
        }
        case AST_REACTION: {
            int l = dump_expr_ir(out, node->as.reaction.lhs);
            int r = dump_expr_ir(out, node->as.reaction.rhs);
            fprintf(out, "  REACTION t%d %s t%d\n", l,
                    node->as.reaction.arrow_type == 2 ? "=>" : "->", r);
            break;
        }
        case AST_IF: {
            int else_label = next_label();
            int end_label = next_label();
            int c = dump_expr_ir(out, node->as.if_stmt.cond);
            fprintf(out, "  IF_FALSE t%d GOTO L%d\n", c, else_label);
            for (AstNode *cur = node->as.if_stmt.then_branch; cur; cur = cur->next) {
                dump_stmt_ir(out, cur);
            }
            fprintf(out, "  GOTO L%d\n", end_label);
            fprintf(out, "L%d:\n", else_label);
            for (AstNode *cur = node->as.if_stmt.else_branch; cur; cur = cur->next) {
                dump_stmt_ir(out, cur);
            }
            fprintf(out, "L%d:\n", end_label);
            break;
        }
        case AST_WHILE: {
            int start = next_label();
            int end = next_label();
            fprintf(out, "L%d:\n", start);
            int c = dump_expr_ir(out, node->as.while_stmt.cond);
            fprintf(out, "  IF_FALSE t%d GOTO L%d\n", c, end);
            for (AstNode *cur = node->as.while_stmt.body; cur; cur = cur->next) {
                dump_stmt_ir(out, cur);
            }
            fprintf(out, "  GOTO L%d\n", start);
            fprintf(out, "L%d:\n", end);
            break;
        }
        case AST_TITRATE: {
            int start = next_label();
            fprintf(out, "L%d: ; TITRATE\n", start);
            for (AstNode *cur = node->as.titrate_stmt.body; cur; cur = cur->next) {
                dump_stmt_ir(out, cur);
            }
            int c = dump_expr_ir(out, node->as.titrate_stmt.until_cond);
            fprintf(out, "  IF_FALSE t%d GOTO L%d\n", c, start);
            break;
        }
        default:
            break;
    }
}

void chem_dump_ir(FILE *out, AstNode *root) {
    g_ir_temp_counter = 0;
    g_ir_label_counter = 0;
    for (AstNode *cur = root; cur; cur = cur->next) {
        dump_stmt_ir(out, cur);
    }
}
