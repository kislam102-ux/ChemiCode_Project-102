/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "grammar/parser.y"

#include "include/main.h"
#include "include/semantic.h"

#line 54 "parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    STRING = 259,                  /* STRING  */
    INVALID = 260,                 /* INVALID  */
    NUMBER = 261,                  /* NUMBER  */
    TYPE_ELEMENT = 262,            /* TYPE_ELEMENT  */
    TYPE_COMPOUND = 263,           /* TYPE_COMPOUND  */
    TYPE_ORGANIC = 264,            /* TYPE_ORGANIC  */
    TYPE_CONFIG = 265,             /* TYPE_CONFIG  */
    TYPE_MOLARITY = 266,           /* TYPE_MOLARITY  */
    TYPE_REACTION = 267,           /* TYPE_REACTION  */
    TYPE_CONTEXT = 268,            /* TYPE_CONTEXT  */
    TYPE_DOUBLE = 269,             /* TYPE_DOUBLE  */
    KW_SECTION = 270,              /* KW_SECTION  */
    BLOCK_INORGANIC = 271,         /* BLOCK_INORGANIC  */
    BLOCK_ORGANIC = 272,           /* BLOCK_ORGANIC  */
    BLOCK_QUANTUM = 273,           /* BLOCK_QUANTUM  */
    BLOCK_ENVIRONMENT = 274,       /* BLOCK_ENVIRONMENT  */
    BLOCK_PROTOCOL = 275,          /* BLOCK_PROTOCOL  */
    BLOCK_HAZARD_CHECK = 276,      /* BLOCK_HAZARD_CHECK  */
    KW_IF = 277,                   /* KW_IF  */
    KW_ELSE = 278,                 /* KW_ELSE  */
    KW_WHILE = 279,                /* KW_WHILE  */
    KW_TITRATE = 280,              /* KW_TITRATE  */
    KW_UNTIL = 281,                /* KW_UNTIL  */
    FN_REACT = 282,                /* FN_REACT  */
    FN_BALANCE = 283,              /* FN_BALANCE  */
    FN_PRINT = 284,                /* FN_PRINT  */
    FN_RENDER = 285,               /* FN_RENDER  */
    FN_GET_MASS = 286,             /* FN_GET_MASS  */
    FN_GET_FORMULA = 287,          /* FN_GET_FORMULA  */
    FN_GET_CONFIG = 288,           /* FN_GET_CONFIG  */
    FN_GET_VALENCE_ELECTRON = 289, /* FN_GET_VALENCE_ELECTRON  */
    FN_GET_QUANTUM_NUMBERS = 290,  /* FN_GET_QUANTUM_NUMBERS  */
    FN_GET_ENTHALPY = 291,         /* FN_GET_ENTHALPY  */
    FN_IS_SATURATED = 292,         /* FN_IS_SATURATED  */
    FN_IS_ISOMER = 293,            /* FN_IS_ISOMER  */
    FN_IS_METAL = 294,             /* FN_IS_METAL  */
    FN_FIND_SERIES = 295,          /* FN_FIND_SERIES  */
    FN_PRECIPITATE = 296,          /* FN_PRECIPITATE  */
    ENV_TEMPERATURE = 297,         /* ENV_TEMPERATURE  */
    ENV_PRESSURE = 298,            /* ENV_PRESSURE  */
    ARROW = 299,                   /* ARROW  */
    FATARROW = 300,                /* FATARROW  */
    EQ = 301,                      /* EQ  */
    NE = 302,                      /* NE  */
    AND = 303,                     /* AND  */
    OR = 304,                      /* OR  */
    UMINUS = 305                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "grammar/parser.y"

    char *text;
    ChemValue *value;
    AstNode *node;
    AstArg *args;
    int ival;

#line 129 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
