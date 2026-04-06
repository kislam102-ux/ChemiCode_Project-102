@echo off
setlocal

if not exist grammar (
    echo Please run this from the ChemiCode_Project root directory.
    exit /b 1
)

set "FLEX_CMD=flex"
set "BISON_CMD=bison"
set "GCC_CMD=gcc"

where "%FLEX_CMD%" >nul 2>nul
if errorlevel 1 (
    if exist "C:\msys64\usr\bin\flex.exe" (
        set "FLEX_CMD=C:\msys64\usr\bin\flex.exe"
    ) else (
        echo flex was not found in PATH or C:\msys64\usr\bin\flex.exe
        exit /b 1
    )
)

where "%BISON_CMD%" >nul 2>nul
if errorlevel 1 (
    if exist "C:\msys64\usr\bin\bison.exe" (
        set "BISON_CMD=C:\msys64\usr\bin\bison.exe"
    ) else (
        echo bison was not found in PATH or C:\msys64\usr\bin\bison.exe
        exit /b 1
    )
)

where "%GCC_CMD%" >nul 2>nul
if errorlevel 1 (
    if exist "C:\msys64\mingw64\bin\gcc.exe" (
        set "GCC_CMD=C:\msys64\mingw64\bin\gcc.exe"
    ) else (
        echo gcc was not found in PATH or C:\msys64\mingw64\bin\gcc.exe
        exit /b 1
    )
)

echo [1/3] Generating parser with Bison...
"%BISON_CMD%" -d -Wall -Wcounterexamples -o parser.tab.c grammar\parser.y
if errorlevel 1 exit /b 1

echo [2/3] Generating lexer with Flex...
"%FLEX_CMD%" -o lexer.yy.c grammar\lexer.l
if errorlevel 1 exit /b 1

echo [3/3] Building ChemiCode with GCC...
"%GCC_CMD%" -std=c11 -Wall -Wextra -pedantic -Iinclude -o chemicode.exe ^
    src\main.c src\symtab.c src\semantic.c src\utils.c ^
    parser.tab.c lexer.yy.c -lfl
if errorlevel 1 (
    echo libfl not found; retrying build without -lfl...
    "%GCC_CMD%" -std=c11 -Wall -Wextra -pedantic -Iinclude -o chemicode.exe ^
        src\main.c src\symtab.c src\semantic.c src\utils.c ^
        parser.tab.c lexer.yy.c
    if errorlevel 1 exit /b 1
)

echo Build complete.
echo Run with: chemicode.exe test.chem
endlocal
