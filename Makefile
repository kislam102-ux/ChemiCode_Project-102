CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -pedantic -Iinclude
LEX := flex
YACC := bison
TARGET := chemicode

SRC := src/main.c src/symtab.c src/semantic.c src/utils.c parser.tab.c lexer.yy.c

all: $(TARGET)

parser.tab.c parser.tab.h: grammar/parser.y
	$(YACC) -d -Wall -Wcounterexamples -o parser.tab.c grammar/parser.y

lexer.yy.c: grammar/lexer.l parser.tab.h
	$(LEX) -o lexer.yy.c grammar/lexer.l

$(TARGET): parser.tab.c parser.tab.h lexer.yy.c $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -lfl

run: $(TARGET)
	./$(TARGET) test.chem

clean:
	rm -f $(TARGET) chemicode.exe parser.tab.c parser.tab.h lexer.yy.c

.PHONY: all run clean
