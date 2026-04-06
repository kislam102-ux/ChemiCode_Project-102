/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 6 "grammar/parser.y"

#include <stdio.h>
#include <stdlib.h>

#include "include/symtab.h"
#include "include/semantic.h"

#line 79 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_STRING = 4,                     /* STRING  */
  YYSYMBOL_INVALID = 5,                    /* INVALID  */
  YYSYMBOL_NUMBER = 6,                     /* NUMBER  */
  YYSYMBOL_TYPE_ELEMENT = 7,               /* TYPE_ELEMENT  */
  YYSYMBOL_TYPE_COMPOUND = 8,              /* TYPE_COMPOUND  */
  YYSYMBOL_TYPE_ORGANIC = 9,               /* TYPE_ORGANIC  */
  YYSYMBOL_TYPE_CONFIG = 10,               /* TYPE_CONFIG  */
  YYSYMBOL_TYPE_MOLARITY = 11,             /* TYPE_MOLARITY  */
  YYSYMBOL_TYPE_REACTION = 12,             /* TYPE_REACTION  */
  YYSYMBOL_TYPE_CONTEXT = 13,              /* TYPE_CONTEXT  */
  YYSYMBOL_TYPE_DOUBLE = 14,               /* TYPE_DOUBLE  */
  YYSYMBOL_KW_SECTION = 15,                /* KW_SECTION  */
  YYSYMBOL_BLOCK_INORGANIC = 16,           /* BLOCK_INORGANIC  */
  YYSYMBOL_BLOCK_ORGANIC = 17,             /* BLOCK_ORGANIC  */
  YYSYMBOL_BLOCK_QUANTUM = 18,             /* BLOCK_QUANTUM  */
  YYSYMBOL_BLOCK_ENVIRONMENT = 19,         /* BLOCK_ENVIRONMENT  */
  YYSYMBOL_BLOCK_PROTOCOL = 20,            /* BLOCK_PROTOCOL  */
  YYSYMBOL_BLOCK_HAZARD_CHECK = 21,        /* BLOCK_HAZARD_CHECK  */
  YYSYMBOL_KW_IF = 22,                     /* KW_IF  */
  YYSYMBOL_KW_ELSE = 23,                   /* KW_ELSE  */
  YYSYMBOL_KW_WHILE = 24,                  /* KW_WHILE  */
  YYSYMBOL_KW_TITRATE = 25,                /* KW_TITRATE  */
  YYSYMBOL_KW_UNTIL = 26,                  /* KW_UNTIL  */
  YYSYMBOL_FN_REACT = 27,                  /* FN_REACT  */
  YYSYMBOL_FN_BALANCE = 28,                /* FN_BALANCE  */
  YYSYMBOL_FN_PRINT = 29,                  /* FN_PRINT  */
  YYSYMBOL_FN_RENDER = 30,                 /* FN_RENDER  */
  YYSYMBOL_FN_GET_MASS = 31,               /* FN_GET_MASS  */
  YYSYMBOL_FN_GET_FORMULA = 32,            /* FN_GET_FORMULA  */
  YYSYMBOL_FN_GET_CONFIG = 33,             /* FN_GET_CONFIG  */
  YYSYMBOL_FN_GET_VALENCE_ELECTRON = 34,   /* FN_GET_VALENCE_ELECTRON  */
  YYSYMBOL_FN_GET_QUANTUM_NUMBERS = 35,    /* FN_GET_QUANTUM_NUMBERS  */
  YYSYMBOL_FN_GET_ENTHALPY = 36,           /* FN_GET_ENTHALPY  */
  YYSYMBOL_FN_IS_SATURATED = 37,           /* FN_IS_SATURATED  */
  YYSYMBOL_FN_IS_ISOMER = 38,              /* FN_IS_ISOMER  */
  YYSYMBOL_FN_IS_METAL = 39,               /* FN_IS_METAL  */
  YYSYMBOL_FN_FIND_SERIES = 40,            /* FN_FIND_SERIES  */
  YYSYMBOL_FN_PRECIPITATE = 41,            /* FN_PRECIPITATE  */
  YYSYMBOL_ENV_TEMPERATURE = 42,           /* ENV_TEMPERATURE  */
  YYSYMBOL_ENV_PRESSURE = 43,              /* ENV_PRESSURE  */
  YYSYMBOL_ARROW = 44,                     /* ARROW  */
  YYSYMBOL_FATARROW = 45,                  /* FATARROW  */
  YYSYMBOL_EQ = 46,                        /* EQ  */
  YYSYMBOL_NE = 47,                        /* NE  */
  YYSYMBOL_AND = 48,                       /* AND  */
  YYSYMBOL_OR = 49,                        /* OR  */
  YYSYMBOL_50_ = 50,                       /* '<'  */
  YYSYMBOL_51_ = 51,                       /* '>'  */
  YYSYMBOL_52_ = 52,                       /* '+'  */
  YYSYMBOL_53_ = 53,                       /* '-'  */
  YYSYMBOL_54_ = 54,                       /* '*'  */
  YYSYMBOL_55_ = 55,                       /* '/'  */
  YYSYMBOL_UMINUS = 56,                    /* UMINUS  */
  YYSYMBOL_57_ = 57,                       /* '!'  */
  YYSYMBOL_58_ = 58,                       /* '{'  */
  YYSYMBOL_59_ = 59,                       /* '}'  */
  YYSYMBOL_60_ = 60,                       /* ';'  */
  YYSYMBOL_61_ = 61,                       /* '('  */
  YYSYMBOL_62_ = 62,                       /* ')'  */
  YYSYMBOL_63_ = 63,                       /* '='  */
  YYSYMBOL_64_ = 64,                       /* ','  */
  YYSYMBOL_YYACCEPT = 65,                  /* $accept  */
  YYSYMBOL_program = 66,                   /* program  */
  YYSYMBOL_sections = 67,                  /* sections  */
  YYSYMBOL_section = 68,                   /* section  */
  YYSYMBOL_section_name = 69,              /* section_name  */
  YYSYMBOL_block = 70,                     /* block  */
  YYSYMBOL_stmt_list = 71,                 /* stmt_list  */
  YYSYMBOL_stmt = 72,                      /* stmt  */
  YYSYMBOL_declaration = 73,               /* declaration  */
  YYSYMBOL_type_name = 74,                 /* type_name  */
  YYSYMBOL_assignment = 75,                /* assignment  */
  YYSYMBOL_environment_stmt = 76,          /* environment_stmt  */
  YYSYMBOL_environment_name = 77,          /* environment_name  */
  YYSYMBOL_reaction_stmt = 78,             /* reaction_stmt  */
  YYSYMBOL_species_list = 79,              /* species_list  */
  YYSYMBOL_species = 80,                   /* species  */
  YYSYMBOL_expr = 81,                      /* expr  */
  YYSYMBOL_function_call = 82,             /* function_call  */
  YYSYMBOL_function_name = 83,             /* function_name  */
  YYSYMBOL_arg_list_opt = 84,              /* arg_list_opt  */
  YYSYMBOL_arg_list = 85                   /* arg_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   259

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  142

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    57,     2,     2,     2,     2,     2,     2,
      61,    62,    54,    52,    64,    53,     2,    55,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    60,
      50,    63,    51,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,     2,    59,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    56
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    50,    50,    58,    59,    63,    67,    74,    75,    76,
      77,    78,    79,    83,    84,    88,    89,    93,    94,    95,
      96,    97,    98,   102,   106,   110,   114,   115,   121,   130,
     134,   141,   142,   143,   144,   145,   146,   147,   148,   152,
     159,   166,   167,   171,   175,   182,   183,   187,   188,   198,
     199,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   226,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   251,   252,   256,   257
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER", "STRING",
  "INVALID", "NUMBER", "TYPE_ELEMENT", "TYPE_COMPOUND", "TYPE_ORGANIC",
  "TYPE_CONFIG", "TYPE_MOLARITY", "TYPE_REACTION", "TYPE_CONTEXT",
  "TYPE_DOUBLE", "KW_SECTION", "BLOCK_INORGANIC", "BLOCK_ORGANIC",
  "BLOCK_QUANTUM", "BLOCK_ENVIRONMENT", "BLOCK_PROTOCOL",
  "BLOCK_HAZARD_CHECK", "KW_IF", "KW_ELSE", "KW_WHILE", "KW_TITRATE",
  "KW_UNTIL", "FN_REACT", "FN_BALANCE", "FN_PRINT", "FN_RENDER",
  "FN_GET_MASS", "FN_GET_FORMULA", "FN_GET_CONFIG",
  "FN_GET_VALENCE_ELECTRON", "FN_GET_QUANTUM_NUMBERS", "FN_GET_ENTHALPY",
  "FN_IS_SATURATED", "FN_IS_ISOMER", "FN_IS_METAL", "FN_FIND_SERIES",
  "FN_PRECIPITATE", "ENV_TEMPERATURE", "ENV_PRESSURE", "ARROW", "FATARROW",
  "EQ", "NE", "AND", "OR", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "UMINUS", "'!'", "'{'", "'}'", "';'", "'('", "')'", "'='", "','",
  "$accept", "program", "sections", "section", "section_name", "block",
  "stmt_list", "stmt", "declaration", "type_name", "assignment",
  "environment_stmt", "environment_name", "reaction_stmt", "species_list",
  "species", "expr", "function_call", "function_name", "arg_list_opt",
  "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-36)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-16)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -36,     2,   238,   -36,     3,   -36,   -36,   -36,   -36,   -36,
     -36,   -36,   -32,   -32,     0,   -36,   -36,   -14,    43,   -36,
     -11,    -5,   -36,     6,   -36,   -36,   -36,   -36,   -36,   -36,
     -36,   -36,     8,    28,   -32,   -36,   -36,   -36,   -36,   -36,
     -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,
     -36,   -36,   -36,   -36,   -36,    30,    88,    60,    61,    59,
      63,   -29,   -36,    67,    68,   -36,   103,   -36,   103,   103,
      98,   -36,    65,   -36,   -36,   103,   -36,    58,    58,    58,
     -36,   103,   -36,   -36,   -36,   -36,   -36,   103,   103,   103,
     130,   -36,    46,    64,    86,   103,   130,   -36,    99,    99,
     -36,   130,    90,    89,   -36,   -36,   157,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   -32,   -32,   103,
     130,   -36,   103,   -36,   -35,   -35,   197,   187,   -35,   -35,
       9,     9,   -36,   -36,   127,   -36,   174,   130,   -32,    94,
     -36,   -36
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,     0,     7,     8,     9,    10,    11,
      12,     4,     0,     0,     0,     6,     5,     0,     0,    14,
       0,    47,    48,     0,    31,    32,    33,    34,    35,    36,
      37,    38,     0,     0,     0,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      41,    42,    13,    26,    16,     0,     0,     0,     0,     0,
       0,     0,    45,     0,     0,    28,     0,    27,     0,     0,
       0,    17,    29,    18,    19,     0,    21,     0,     0,     0,
      20,    84,    51,    50,    49,    52,    53,     0,     0,     0,
      39,    54,     0,     0,     0,     0,    40,    47,    43,    44,
      46,    86,     0,    85,    66,    67,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      30,    68,     0,    55,    60,    61,    64,    65,    62,    63,
      56,    57,    58,    59,    22,    24,     0,    87,     0,     0,
      23,    25
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -36,   -36,   -36,   -36,   -36,   -13,   -36,   -36,   -36,   -36,
     -36,   -36,   -36,   -36,    10,    78,    80,   140,   -36,   -36,
     -36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    11,    12,    15,    18,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    90,    91,    64,   102,
     103
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      16,    17,     3,   -15,   -15,   -15,    13,   -15,   -15,   -15,
     -15,   -15,   -15,   -15,   -15,    77,    78,   113,   114,   115,
     116,    70,   -15,    79,   -15,   -15,    14,   -15,   -15,   -15,
     -15,   -15,   -15,   -15,   -15,   -15,   -15,   -15,   -15,   -15,
     -15,   -15,   -15,   -15,    20,    19,    21,    22,    23,    65,
      24,    25,    26,    27,    28,    29,    30,    31,    66,   -15,
     -15,    97,    22,   115,   116,    32,    67,    33,    34,    68,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    98,    99,    69,
      71,    72,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,    52,    53,   134,   135,    82,    83,   117,    84,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
      73,    74,    75,    76,    94,   140,   118,    80,    95,    81,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    85,    86,   119,    92,    93,
     138,    79,   121,   122,   141,    96,    87,   100,    63,     0,
      88,   101,     0,     0,    89,     0,     0,   104,   105,   106,
       0,     0,     0,     0,     0,   120,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,     0,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,     0,     0,   136,
       0,     0,   137,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,     0,     0,     0,     0,     0,     0,   123,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
       0,     0,     0,   107,   108,   109,   139,   111,   112,   113,
     114,   115,   116,   107,   108,     0,     0,   111,   112,   113,
     114,   115,   116,     4,     5,     6,     7,     8,     9,    10
};

static const yytype_int16 yycheck[] =
{
      13,     1,     0,     3,     4,     5,     3,     7,     8,     9,
      10,    11,    12,    13,    14,    44,    45,    52,    53,    54,
      55,    34,    22,    52,    24,    25,    58,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,     1,    59,     3,     4,     5,    60,
       7,     8,     9,    10,    11,    12,    13,    14,    63,    59,
      60,     3,     4,    54,    55,    22,    60,    24,    25,    61,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    77,    78,    61,
      60,     3,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    59,    60,   117,   118,     3,     4,    62,     6,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      60,    60,    63,    60,    26,   138,    62,    60,    63,    61,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    61,    68,    69,
      23,    52,    62,    64,    60,    75,    53,    79,    18,    -1,
      57,    81,    -1,    -1,    61,    -1,    -1,    87,    88,    89,
      -1,    -1,    -1,    -1,    -1,    95,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    -1,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,    -1,    -1,   119,
      -1,    -1,   122,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    46,    47,    48,    62,    50,    51,    52,
      53,    54,    55,    46,    47,    -1,    -1,    50,    51,    52,
      53,    54,    55,    15,    16,    17,    18,    19,    20,    21
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    66,    67,     0,    15,    16,    17,    18,    19,    20,
      21,    68,    69,     3,    58,    70,    70,     1,    71,    59,
       1,     3,     4,     5,     7,     8,     9,    10,    11,    12,
      13,    14,    22,    24,    25,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    59,    60,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    82,    83,    60,    63,    60,    61,    61,
      70,    60,     3,    60,    60,    63,    60,    44,    45,    52,
      60,    61,     3,     4,     6,    42,    43,    53,    57,    61,
      81,    82,    81,    81,    26,    63,    81,     3,    79,    79,
      80,    81,    84,    85,    81,    81,    81,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    62,    62,    61,
      81,    62,    64,    62,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    70,    70,    81,    81,    23,    62,
      70,    60
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    65,    66,    67,    67,    68,    68,    69,    69,    69,
      69,    69,    69,    70,    70,    71,    71,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    73,
      73,    74,    74,    74,    74,    74,    74,    74,    74,    75,
      76,    77,    77,    78,    78,    79,    79,    80,    80,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    82,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    84,    84,    85,    85
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     1,     1,     1,
       1,     1,     1,     3,     3,     0,     2,     2,     2,     2,
       2,     2,     5,     7,     5,     7,     1,     2,     2,     2,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     1,     3,     3,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: sections  */
#line 51 "grammar/parser.y"
      {
          chem_ast_set_root((yyvsp[0].node));
          (yyval.node) = (yyvsp[0].node);
      }
#line 1551 "parser.tab.c"
    break;

  case 3: /* sections: %empty  */
#line 58 "grammar/parser.y"
                                { (yyval.node) = NULL; }
#line 1557 "parser.tab.c"
    break;

  case 4: /* sections: sections section  */
#line 59 "grammar/parser.y"
                                { (yyval.node) = chem_ast_append((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1563 "parser.tab.c"
    break;

  case 5: /* section: KW_SECTION IDENTIFIER block  */
#line 64 "grammar/parser.y"
      {
          (yyval.node) = chem_ast_make_section((yyvsp[-1].text), (yyvsp[0].node));
      }
#line 1571 "parser.tab.c"
    break;

  case 6: /* section: section_name block  */
#line 68 "grammar/parser.y"
      {
          (yyval.node) = chem_ast_make_section((yyvsp[-1].text), (yyvsp[0].node));
      }
#line 1579 "parser.tab.c"
    break;

  case 7: /* section_name: BLOCK_INORGANIC  */
#line 74 "grammar/parser.y"
                                 { (yyval.text) = chem_strdup("INORGANIC"); }
#line 1585 "parser.tab.c"
    break;

  case 8: /* section_name: BLOCK_ORGANIC  */
#line 75 "grammar/parser.y"
                                 { (yyval.text) = chem_strdup("ORGANIC"); }
#line 1591 "parser.tab.c"
    break;

  case 9: /* section_name: BLOCK_QUANTUM  */
#line 76 "grammar/parser.y"
                                 { (yyval.text) = chem_strdup("QUANTUM"); }
#line 1597 "parser.tab.c"
    break;

  case 10: /* section_name: BLOCK_ENVIRONMENT  */
#line 77 "grammar/parser.y"
                                 { (yyval.text) = chem_strdup("ENVIRONMENT"); }
#line 1603 "parser.tab.c"
    break;

  case 11: /* section_name: BLOCK_PROTOCOL  */
#line 78 "grammar/parser.y"
                                 { (yyval.text) = chem_strdup("PROTOCOL"); }
#line 1609 "parser.tab.c"
    break;

  case 12: /* section_name: BLOCK_HAZARD_CHECK  */
#line 79 "grammar/parser.y"
                                 { (yyval.text) = chem_strdup("HAZARD_CHECK"); }
#line 1615 "parser.tab.c"
    break;

  case 13: /* block: '{' stmt_list '}'  */
#line 83 "grammar/parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 1621 "parser.tab.c"
    break;

  case 14: /* block: '{' error '}'  */
#line 84 "grammar/parser.y"
                                 { yyerrok; (yyval.node) = NULL; }
#line 1627 "parser.tab.c"
    break;

  case 15: /* stmt_list: %empty  */
#line 88 "grammar/parser.y"
                                 { (yyval.node) = NULL; }
#line 1633 "parser.tab.c"
    break;

  case 16: /* stmt_list: stmt_list stmt  */
#line 89 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_append((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1639 "parser.tab.c"
    break;

  case 17: /* stmt: declaration ';'  */
#line 93 "grammar/parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 1645 "parser.tab.c"
    break;

  case 18: /* stmt: assignment ';'  */
#line 94 "grammar/parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 1651 "parser.tab.c"
    break;

  case 19: /* stmt: environment_stmt ';'  */
#line 95 "grammar/parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 1657 "parser.tab.c"
    break;

  case 20: /* stmt: function_call ';'  */
#line 96 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_expr_stmt((yyvsp[-1].node)); }
#line 1663 "parser.tab.c"
    break;

  case 21: /* stmt: reaction_stmt ';'  */
#line 97 "grammar/parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 1669 "parser.tab.c"
    break;

  case 22: /* stmt: KW_IF '(' expr ')' block  */
#line 99 "grammar/parser.y"
      {
          (yyval.node) = chem_ast_make_if((yyvsp[-2].node), (yyvsp[0].node), NULL);
      }
#line 1677 "parser.tab.c"
    break;

  case 23: /* stmt: KW_IF '(' expr ')' block KW_ELSE block  */
#line 103 "grammar/parser.y"
      {
          (yyval.node) = chem_ast_make_if((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
      }
#line 1685 "parser.tab.c"
    break;

  case 24: /* stmt: KW_WHILE '(' expr ')' block  */
#line 107 "grammar/parser.y"
      {
          (yyval.node) = chem_ast_make_while((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 1693 "parser.tab.c"
    break;

  case 25: /* stmt: KW_TITRATE block KW_UNTIL '(' expr ')' ';'  */
#line 111 "grammar/parser.y"
      {
          (yyval.node) = chem_ast_make_titrate((yyvsp[-5].node), (yyvsp[-2].node));
      }
#line 1701 "parser.tab.c"
    break;

  case 26: /* stmt: ';'  */
#line 114 "grammar/parser.y"
                                 { (yyval.node) = NULL; }
#line 1707 "parser.tab.c"
    break;

  case 27: /* stmt: INVALID ';'  */
#line 116 "grammar/parser.y"
      {
          chem_report_error("Invalid token '%s' recovered at line %d", (yyvsp[-1].text), yylineno);
          free((yyvsp[-1].text));
          (yyval.node) = NULL;
      }
#line 1717 "parser.tab.c"
    break;

  case 28: /* stmt: error ';'  */
#line 122 "grammar/parser.y"
      {
          chem_report_error("Recovered from syntax error near line %d", yylineno);
          yyerrok;
          (yyval.node) = NULL;
      }
#line 1727 "parser.tab.c"
    break;

  case 29: /* declaration: type_name IDENTIFIER  */
#line 131 "grammar/parser.y"
      {
          (yyval.node) = chem_ast_make_decl((ChemDeclType)(yyvsp[-1].ival), (yyvsp[0].text), NULL);
      }
#line 1735 "parser.tab.c"
    break;

  case 30: /* declaration: type_name IDENTIFIER '=' expr  */
#line 135 "grammar/parser.y"
      {
          (yyval.node) = chem_ast_make_decl((ChemDeclType)(yyvsp[-3].ival), (yyvsp[-2].text), (yyvsp[0].node));
      }
#line 1743 "parser.tab.c"
    break;

  case 31: /* type_name: TYPE_ELEMENT  */
#line 141 "grammar/parser.y"
                                 { (yyval.ival) = DECL_ELEMENT; }
#line 1749 "parser.tab.c"
    break;

  case 32: /* type_name: TYPE_COMPOUND  */
#line 142 "grammar/parser.y"
                                 { (yyval.ival) = DECL_COMPOUND; }
#line 1755 "parser.tab.c"
    break;

  case 33: /* type_name: TYPE_ORGANIC  */
#line 143 "grammar/parser.y"
                                 { (yyval.ival) = DECL_ORGANIC; }
#line 1761 "parser.tab.c"
    break;

  case 34: /* type_name: TYPE_CONFIG  */
#line 144 "grammar/parser.y"
                                 { (yyval.ival) = DECL_CONFIG; }
#line 1767 "parser.tab.c"
    break;

  case 35: /* type_name: TYPE_MOLARITY  */
#line 145 "grammar/parser.y"
                                 { (yyval.ival) = DECL_MOLARITY; }
#line 1773 "parser.tab.c"
    break;

  case 36: /* type_name: TYPE_REACTION  */
#line 146 "grammar/parser.y"
                                 { (yyval.ival) = DECL_REACTION; }
#line 1779 "parser.tab.c"
    break;

  case 37: /* type_name: TYPE_CONTEXT  */
#line 147 "grammar/parser.y"
                                 { (yyval.ival) = DECL_CONTEXT; }
#line 1785 "parser.tab.c"
    break;

  case 38: /* type_name: TYPE_DOUBLE  */
#line 148 "grammar/parser.y"
                                 { (yyval.ival) = DECL_DOUBLE; }
#line 1791 "parser.tab.c"
    break;

  case 39: /* assignment: IDENTIFIER '=' expr  */
#line 153 "grammar/parser.y"
      {
          (yyval.node) = chem_ast_make_assign((yyvsp[-2].text), (yyvsp[0].node));
      }
#line 1799 "parser.tab.c"
    break;

  case 40: /* environment_stmt: environment_name '=' expr  */
#line 160 "grammar/parser.y"
      {
          (yyval.node) = chem_ast_make_env_assign((yyvsp[-2].text), (yyvsp[0].node));
      }
#line 1807 "parser.tab.c"
    break;

  case 41: /* environment_name: ENV_TEMPERATURE  */
#line 166 "grammar/parser.y"
                                 { (yyval.text) = chem_strdup("Temperature"); }
#line 1813 "parser.tab.c"
    break;

  case 42: /* environment_name: ENV_PRESSURE  */
#line 167 "grammar/parser.y"
                                 { (yyval.text) = chem_strdup("Pressure"); }
#line 1819 "parser.tab.c"
    break;

  case 43: /* reaction_stmt: species_list ARROW species_list  */
#line 172 "grammar/parser.y"
      {
          (yyval.node) = chem_ast_make_reaction((yyvsp[-2].node), (yyvsp[0].node), 1);
      }
#line 1827 "parser.tab.c"
    break;

  case 44: /* reaction_stmt: species_list FATARROW species_list  */
#line 176 "grammar/parser.y"
      {
          (yyval.node) = chem_ast_make_reaction((yyvsp[-2].node), (yyvsp[0].node), 2);
      }
#line 1835 "parser.tab.c"
    break;

  case 45: /* species_list: species  */
#line 182 "grammar/parser.y"
                                 { (yyval.node) = (yyvsp[0].node); }
#line 1841 "parser.tab.c"
    break;

  case 46: /* species_list: species_list '+' species  */
#line 183 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_binary(OP_SPECIES_JOIN, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1847 "parser.tab.c"
    break;

  case 47: /* species: IDENTIFIER  */
#line 187 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_var((yyvsp[0].text), 0); }
#line 1853 "parser.tab.c"
    break;

  case 48: /* species: STRING  */
#line 189 "grammar/parser.y"
      {
          char *tmp = chem_trim_quotes((yyvsp[0].text));
          free((yyvsp[0].text));
          (yyval.node) = chem_ast_make_literal(chem_make_string(tmp));
          free(tmp);
      }
#line 1864 "parser.tab.c"
    break;

  case 49: /* expr: NUMBER  */
#line 198 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_literal((yyvsp[0].value)); }
#line 1870 "parser.tab.c"
    break;

  case 50: /* expr: STRING  */
#line 200 "grammar/parser.y"
      {
          char *tmp = chem_trim_quotes((yyvsp[0].text));
          free((yyvsp[0].text));
          (yyval.node) = chem_ast_make_literal(chem_make_string(tmp));
          free(tmp);
      }
#line 1881 "parser.tab.c"
    break;

  case 51: /* expr: IDENTIFIER  */
#line 206 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_var((yyvsp[0].text), 0); }
#line 1887 "parser.tab.c"
    break;

  case 52: /* expr: ENV_TEMPERATURE  */
#line 207 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_var(chem_strdup("Temperature"), 1); }
#line 1893 "parser.tab.c"
    break;

  case 53: /* expr: ENV_PRESSURE  */
#line 208 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_var(chem_strdup("Pressure"), 1); }
#line 1899 "parser.tab.c"
    break;

  case 54: /* expr: function_call  */
#line 209 "grammar/parser.y"
                                 { (yyval.node) = (yyvsp[0].node); }
#line 1905 "parser.tab.c"
    break;

  case 55: /* expr: '(' expr ')'  */
#line 210 "grammar/parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 1911 "parser.tab.c"
    break;

  case 56: /* expr: expr '+' expr  */
#line 211 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_binary(OP_ADD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1917 "parser.tab.c"
    break;

  case 57: /* expr: expr '-' expr  */
#line 212 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_binary(OP_SUB, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1923 "parser.tab.c"
    break;

  case 58: /* expr: expr '*' expr  */
#line 213 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_binary(OP_MUL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1929 "parser.tab.c"
    break;

  case 59: /* expr: expr '/' expr  */
#line 214 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_binary(OP_DIV, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1935 "parser.tab.c"
    break;

  case 60: /* expr: expr EQ expr  */
#line 215 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_binary(OP_EQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1941 "parser.tab.c"
    break;

  case 61: /* expr: expr NE expr  */
#line 216 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_binary(OP_NE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1947 "parser.tab.c"
    break;

  case 62: /* expr: expr '<' expr  */
#line 217 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_binary(OP_LT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1953 "parser.tab.c"
    break;

  case 63: /* expr: expr '>' expr  */
#line 218 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_binary(OP_GT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1959 "parser.tab.c"
    break;

  case 64: /* expr: expr AND expr  */
#line 219 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_binary(OP_AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1965 "parser.tab.c"
    break;

  case 65: /* expr: expr OR expr  */
#line 220 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_binary(OP_OR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1971 "parser.tab.c"
    break;

  case 66: /* expr: '-' expr  */
#line 221 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_unary(OP_NEG, (yyvsp[0].node)); }
#line 1977 "parser.tab.c"
    break;

  case 67: /* expr: '!' expr  */
#line 222 "grammar/parser.y"
                                 { (yyval.node) = chem_ast_make_unary(OP_NOT, (yyvsp[0].node)); }
#line 1983 "parser.tab.c"
    break;

  case 68: /* function_call: function_name '(' arg_list_opt ')'  */
#line 227 "grammar/parser.y"
      {
          (yyval.node) = chem_ast_make_funcall((ChemFunctionKind)(yyvsp[-3].ival), (yyvsp[-1].args));
      }
#line 1991 "parser.tab.c"
    break;

  case 69: /* function_name: FN_REACT  */
#line 233 "grammar/parser.y"
                                 { (yyval.ival) = FN_KIND_REACT; }
#line 1997 "parser.tab.c"
    break;

  case 70: /* function_name: FN_BALANCE  */
#line 234 "grammar/parser.y"
                                 { (yyval.ival) = FN_KIND_BALANCE; }
#line 2003 "parser.tab.c"
    break;

  case 71: /* function_name: FN_PRINT  */
#line 235 "grammar/parser.y"
                                 { (yyval.ival) = FN_KIND_PRINT; }
#line 2009 "parser.tab.c"
    break;

  case 72: /* function_name: FN_RENDER  */
#line 236 "grammar/parser.y"
                                 { (yyval.ival) = FN_KIND_RENDER; }
#line 2015 "parser.tab.c"
    break;

  case 73: /* function_name: FN_GET_MASS  */
#line 237 "grammar/parser.y"
                                 { (yyval.ival) = FN_KIND_GET_MASS; }
#line 2021 "parser.tab.c"
    break;

  case 74: /* function_name: FN_GET_FORMULA  */
#line 238 "grammar/parser.y"
                                 { (yyval.ival) = FN_KIND_GET_FORMULA; }
#line 2027 "parser.tab.c"
    break;

  case 75: /* function_name: FN_GET_CONFIG  */
#line 239 "grammar/parser.y"
                                 { (yyval.ival) = FN_KIND_GET_CONFIG; }
#line 2033 "parser.tab.c"
    break;

  case 76: /* function_name: FN_GET_VALENCE_ELECTRON  */
#line 240 "grammar/parser.y"
                                 { (yyval.ival) = FN_KIND_GET_VALENCE_ELECTRON; }
#line 2039 "parser.tab.c"
    break;

  case 77: /* function_name: FN_GET_QUANTUM_NUMBERS  */
#line 241 "grammar/parser.y"
                                 { (yyval.ival) = FN_KIND_GET_QUANTUM_NUMBERS; }
#line 2045 "parser.tab.c"
    break;

  case 78: /* function_name: FN_GET_ENTHALPY  */
#line 242 "grammar/parser.y"
                                 { (yyval.ival) = FN_KIND_GET_ENTHALPY; }
#line 2051 "parser.tab.c"
    break;

  case 79: /* function_name: FN_IS_SATURATED  */
#line 243 "grammar/parser.y"
                                 { (yyval.ival) = FN_KIND_IS_SATURATED; }
#line 2057 "parser.tab.c"
    break;

  case 80: /* function_name: FN_IS_ISOMER  */
#line 244 "grammar/parser.y"
                                 { (yyval.ival) = FN_KIND_IS_ISOMER; }
#line 2063 "parser.tab.c"
    break;

  case 81: /* function_name: FN_IS_METAL  */
#line 245 "grammar/parser.y"
                                 { (yyval.ival) = FN_KIND_IS_METAL; }
#line 2069 "parser.tab.c"
    break;

  case 82: /* function_name: FN_FIND_SERIES  */
#line 246 "grammar/parser.y"
                                 { (yyval.ival) = FN_KIND_FIND_SERIES; }
#line 2075 "parser.tab.c"
    break;

  case 83: /* function_name: FN_PRECIPITATE  */
#line 247 "grammar/parser.y"
                                 { (yyval.ival) = FN_KIND_PRECIPITATE; }
#line 2081 "parser.tab.c"
    break;

  case 84: /* arg_list_opt: %empty  */
#line 251 "grammar/parser.y"
                                 { (yyval.args) = NULL; }
#line 2087 "parser.tab.c"
    break;

  case 85: /* arg_list_opt: arg_list  */
#line 252 "grammar/parser.y"
                                 { (yyval.args) = (yyvsp[0].args); }
#line 2093 "parser.tab.c"
    break;

  case 86: /* arg_list: expr  */
#line 256 "grammar/parser.y"
                                 { (yyval.args) = chem_ast_arg_append(NULL, (yyvsp[0].node)); }
#line 2099 "parser.tab.c"
    break;

  case 87: /* arg_list: arg_list ',' expr  */
#line 257 "grammar/parser.y"
                                 { (yyval.args) = chem_ast_arg_append((yyvsp[-2].args), (yyvsp[0].node)); }
#line 2105 "parser.tab.c"
    break;


#line 2109 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 260 "grammar/parser.y"

