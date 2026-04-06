#include "../include/main.h"
#include "../include/symtab.h"
#include "../include/semantic.h"

typedef enum {
    OUTPUT_BOTH = 0,
    OUTPUT_IR_ONLY,
    OUTPUT_RUN_ONLY
} OutputMode;

static void print_usage(const char *prog) {
    printf("Usage: %s [--ir | --run-only] [--out output_file] [input_file]\n", prog);
    printf("  --ir        Show only intermediate representation (no execution)\n");
    printf("  --run-only  Execute program without printing intermediate representation\n");
    printf("  --out       Save program output to the specified file (default: output.txt)\n");
}

int main(int argc, char **argv) {
    const char *input_path = "test.chem";
    const char *output_path = "output.txt";
    OutputMode mode = OUTPUT_BOTH;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--ir") == 0) {
            mode = OUTPUT_IR_ONLY;
        } else if (strcmp(argv[i], "--run-only") == 0) {
            mode = OUTPUT_RUN_ONLY;
        } else if (strcmp(argv[i], "--out") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "ChemiCode: missing output file after '--out'\n");
                print_usage(argv[0]);
                return EXIT_FAILURE;
            }
            output_path = argv[++i];
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return EXIT_SUCCESS;
        } else if (argv[i][0] == '-') {
            fprintf(stderr, "ChemiCode: unknown option '%s'\n", argv[i]);
            print_usage(argv[0]);
            return EXIT_FAILURE;
        } else {
            input_path = argv[i];
        }
    }

    yyin = fopen(input_path, "r");
    if (!yyin) {
        fprintf(stderr, "ChemiCode: could not open input file '%s'\n", input_path);
        return EXIT_FAILURE;
    }

    if (!freopen(output_path, "w", stdout)) {
        fprintf(stderr, "ChemiCode: could not open output file '%s'\n", output_path);
        fclose(yyin);
        return EXIT_FAILURE;
    }

    yylineno = 1;
    symtab_init();
    chem_semantic_init();

    printf("=== ChemiCode Compiler Start ===\n");
    printf("Input file: %s\n", input_path);
    printf("Output file: %s\n", output_path);

    int parse_result = yyparse();

    if (parse_result == 0 && mode != OUTPUT_RUN_ONLY) {
        printf("\n=== Intermediate Representation ===\n");
        chem_dump_ir(stdout, chem_ast_root());
        printf("=== End Intermediate Representation ===\n\n");
    }

    int exec_result = 0;
    if (parse_result == 0 && !chem_has_errors() && mode != OUTPUT_IR_ONLY) {
        exec_result = chem_execute_program(chem_ast_root());
    }

    printf("\n=== ChemiCode Compiler End ===\n");
    if (parse_result == 0 && exec_result == 0 && !chem_has_errors()) {
        printf("Compilation status: SUCCESS\n");
        symtab_dump(stdout);
    } else {
        printf("Compilation status: FAILED (%d error(s))\n", chem_error_count());
        symtab_dump(stdout);
    }

    fclose(yyin);
    fclose(stdout);
    chem_semantic_shutdown();
    symtab_free();

    return (parse_result == 0 && exec_result == 0 && !chem_has_errors()) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void yyerror(const char *msg) {
    chem_report_error("Parse error at line %d: %s", yylineno, msg);
}
