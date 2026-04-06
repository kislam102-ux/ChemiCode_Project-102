# ChemiCode

ChemiCode is a domain-specific mini language for chemistry-oriented programs, implemented in C with Flex and Bison. It parses `.chem` source files, performs semantic analysis, emits an intermediate representation (IR), and executes supported language constructs through a small runtime.

This project is designed as a compiler-style academic build that combines:

- lexical analysis with Flex
- parsing with Bison
- semantic checking and AST processing in C
- IR generation for inspection and debugging
- execution of chemistry-themed statements and built-in functions

## Highlights

- Custom `.chem` language with section-based program structure
- Typed declarations for `Element`, `Compound`, `Organic`, `Reaction`, `Context`, `Config`, `Molarity`, and `Double`
- Control flow support including `IF / ELSE`, `WHILE`, and `TITRATE ... UNTIL`
- Environment-aware values such as `Temperature` and `Pressure`
- Built-in chemistry functions like `REACT`, `BALANCE`, `GET_MASS`, `GET_FORMULA`, `GET_CONFIG`, and `PRECIPITATE`
- Intermediate representation dump for tracing how source code is compiled
- Output redirection to a file for clean result capture

## Project Structure

```text
ChemiCode_Project-102/
|-- grammar/
|   |-- lexer.l
|   `-- parser.y
|-- include/
|   |-- main.h
|   |-- semantic.h
|   `-- symtab.h
|-- src/
|   |-- main.c
|   |-- semantic.c
|   |-- symtab.c
|   `-- utils.c
|-- samples/
|   `-- sections/
|-- test.chem
|-- output.txt
|-- Makefile
|-- build.bat
`-- build.sh
```

## Requirements

To build ChemiCode from source, install:

- GCC
- Flex
- Bison

On Windows, the provided `build.bat` also checks common MSYS2 install paths:

- `C:\msys64\usr\bin\flex.exe`
- `C:\msys64\usr\bin\bison.exe`
- `C:\msys64\mingw64\bin\gcc.exe`

## Build

### Windows

```powershell
.\build.bat
```

### Linux / macOS

```bash
chmod +x build.sh
./build.sh
```

### Makefile

```bash
make
```

## Usage

By default, the compiler reads `test.chem`, writes output to `output.txt`, prints the IR, and executes the program.

```bash
./chemicode
```

You can also provide your own file:

```bash
./chemicode samples/sections/organic.chem
```

Useful command-line options:

```text
--ir          Show only the intermediate representation
--run-only    Execute the program without printing IR
--out FILE    Write output to a custom file
-h, --help    Show usage information
```

Examples:

```bash
./chemicode --ir test.chem
./chemicode --run-only test.chem
./chemicode --out result.txt test.chem
```

## Language Overview

ChemiCode programs are organized into named or predefined sections such as:

- `SECTION <name>`
- `ENVIRONMENT`
- `INORGANIC`
- `ORGANIC`
- `QUANTUM`
- `PROTOCOL`
- `HAZARD_CHECK`

Supported language features include:

- variable declarations and assignments
- numeric and string values
- arithmetic and logical expressions
- reaction-style statements using `->`
- built-in chemistry utility functions
- conditional execution and loops

Example:

```chem
ENVIRONMENT {
    Temperature = 310.15;
    Pressure = 1.20;
}

INORGANIC {
    Element sodium = "Na";
    Compound salt = "NaCl";

    PRINT(GET_FORMULA(salt));
    PRINT(GET_MASS(salt));
}
```

## Example Output

Running the default sample produces:

- compiler start/end markers
- an intermediate representation dump
- execution results for supported functions and statements
- a final compilation status summary

Output is written to `output.txt` unless another file is provided with `--out`.

## Key Source Files

- [`grammar/parser.y`](/e:/3-2%20projects/passes/ChemiCode_Project-102/grammar/parser.y) defines the grammar and parsing rules
- [`grammar/lexer.l`](/e:/3-2%20projects/passes/ChemiCode_Project-102/grammar/lexer.l) defines lexical tokens
- [`src/main.c`](/e:/3-2%20projects/passes/ChemiCode_Project-102/src/main.c) handles CLI options, parsing, IR output, and execution flow
- [`src/semantic.c`](/e:/3-2%20projects/passes/ChemiCode_Project-102/src/semantic.c) implements semantic analysis and runtime behavior
- [`src/symtab.c`](/e:/3-2%20projects/passes/ChemiCode_Project-102/src/symtab.c) manages symbol table operations

## Development Notes

- Generated parser and lexer files may appear as `parser.tab.c`, `parser.tab.h`, and `lexer.yy.c`
- The executable may be produced as `chemicode` or `chemicode.exe`, depending on platform
- `test.chem` serves as the default integration sample for parsing and execution

## Authors

ChemiCode was developed as a compiler/language project for chemistry-inspired programming workflows.

## License

No license file is currently included in this repository. Add one if you plan to distribute or reuse the project publicly.
