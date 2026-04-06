# ChemiCode Project

ChemiCode is a C-based mini language project built with Flex and Bison.  
It parses and executes `.chem` source files and can also print an intermediate representation (IR).

## Project Structure

- `grammar/` - lexer and parser definitions
- `src/` - compiler/runtime source code
- `include/` - header files
- `test.chem` - sample input program
- `build.bat` / `build.sh` - build scripts

## Requirements

- Windows PowerShell or terminal
- GCC
- Flex
- Bison

## Build and Run (Windows / PowerShell)

Open terminal in project root:

```powershell
cd "e:\3-2 projects\passes\ChemiCode_Project-102"
```

Build:

```powershell
.\build.bat
```

Run with default output (IR + execution output saved to `output.txt`):

```powershell
.\chemicode.exe test.chem
```

Run with IR only:

```powershell
.\chemicode.exe --ir test.chem
```

Run with final/runtime output only (no IR):

```powershell
.\chemicode.exe --run-only test.chem
```

Choose a custom output file:

```powershell
.\chemicode.exe --out results.txt test.chem
```

Show help:

```powershell
.\chemicode.exe --help
```

## Build and Run (Git Bash / Linux-style shell)

```bash
cd "/e/3-2 projects/passes/ChemiCode_Project-102"
chmod +x build.sh
./chemicode.exe test.chem
```
.\chemicode.exe test.chem
.\chemicode.exe --ir test.chem
.\chemicode.exe --run-only test.chem
.\chemicode.exe --out results.txt test.chem

## Notes

- If `-lfl` is not available, `build.bat` automatically retries without it.
- The sample program file is `test.chem`; replace it with your own `.chem` file path as needed.
