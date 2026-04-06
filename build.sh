#!/bin/bash
cd "$(dirname "$0")"
echo "Building ChemiCode..."
echo "Step 1: Generating parser..."
bison -d -Wall -Wcounterexamples -o parser.tab.c grammar/parser.y
if [ $? -ne 0 ]; then echo "Bison failed"; exit 1; fi

echo "Step 2: Generating lexer..."
flex -o lexer.yy.c grammar/lexer.l
if [ $? -ne 0 ]; then echo "Flex failed"; exit 1; fi

echo "Step 3: Compiling with GCC..."
gcc -std=c11 -Wall -Wextra -pedantic -Iinclude -o chemicode.exe src/main.c src/symtab.c src/semantic.c src/utils.c parser.tab.c lexer.yy.c -lfl
if [ $? -ne 0 ]; then echo "GCC failed"; exit 1; fi

echo "Build complete! Run with: ./chemicode.exe test.chem"
