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


/* Substitute the variable and function names.  */
#define yyparse         yyparse
#define yyerror         CEvaluationParsererror
#define yydebug         CEvaluationParserdebug
#define yynerrs         CEvaluationParsernerrs
#define yylval          CEvaluationParserlval
#define yychar          CEvaluationParserchar

/* First part of user prologue.  */
#line 4 "CEvaluationParser.ypp"

#define YYSTYPE CEvaluationNode *

#ifdef yylval
# undef yylval
#endif
#define yylval  mpNode

#ifdef yyerror
# undef yyerror
#endif
#define yyerror(__str) \
  if (yychar != YYERRCODE) correctErrorPosition(); \
  CCopasiMessage(CCopasiMessage::ERROR, MCFunction + 1, mPosition)

#include "copasi/copasi.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationLexer.h"

#undef yyparse
#define yyparse CEvaluationParserBase::yyparse


#line 102 "CEvaluationParser_yacc.cpp"

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

#include "CEvaluationParser_yacc.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN_NUMBER = 3,               /* TOKEN_NUMBER  */
  YYSYMBOL_TOKEN_VARIABLE = 4,             /* TOKEN_VARIABLE  */
  YYSYMBOL_TOKEN_UNIT = 5,                 /* TOKEN_UNIT  */
  YYSYMBOL_TOKEN_CALL = 6,                 /* TOKEN_CALL  */
  YYSYMBOL_TOKEN_FUNCTION = 7,             /* TOKEN_FUNCTION  */
  YYSYMBOL_TOKEN_FUNCTION_1 = 8,           /* TOKEN_FUNCTION_1  */
  YYSYMBOL_TOKEN_FUNCTION_2 = 9,           /* TOKEN_FUNCTION_2  */
  YYSYMBOL_TOKEN_SIGN = 10,                /* TOKEN_SIGN  */
  YYSYMBOL_TOKEN_OPERATOR_POWER = 11,      /* TOKEN_OPERATOR_POWER  */
  YYSYMBOL_TOKEN_OPERATOR_MULTIPLY = 12,   /* TOKEN_OPERATOR_MULTIPLY  */
  YYSYMBOL_TOKEN_OPERATOR_MODULUS = 13,    /* TOKEN_OPERATOR_MODULUS  */
  YYSYMBOL_TOKEN_OPERATOR_REMAINDER = 14,  /* TOKEN_OPERATOR_REMAINDER  */
  YYSYMBOL_TOKEN_OPERATOR_PLUS = 15,       /* TOKEN_OPERATOR_PLUS  */
  YYSYMBOL_TOKEN_LOGICAL_CHOICE = 16,      /* TOKEN_LOGICAL_CHOICE  */
  YYSYMBOL_TOKEN_LOGICAL_VALUE = 17,       /* TOKEN_LOGICAL_VALUE  */
  YYSYMBOL_TOKEN_LOGICAL_NOT = 18,         /* TOKEN_LOGICAL_NOT  */
  YYSYMBOL_TOKEN_LOGICAL_OR = 19,          /* TOKEN_LOGICAL_OR  */
  YYSYMBOL_TOKEN_LOGICAL_XOR = 20,         /* TOKEN_LOGICAL_XOR  */
  YYSYMBOL_TOKEN_LOGICAL_AND = 21,         /* TOKEN_LOGICAL_AND  */
  YYSYMBOL_TOKEN_LOGICAL_EQ = 22,          /* TOKEN_LOGICAL_EQ  */
  YYSYMBOL_TOKEN_LOGICAL_NE = 23,          /* TOKEN_LOGICAL_NE  */
  YYSYMBOL_TOKEN_LOGICAL_GT = 24,          /* TOKEN_LOGICAL_GT  */
  YYSYMBOL_TOKEN_LOGICAL_GE = 25,          /* TOKEN_LOGICAL_GE  */
  YYSYMBOL_TOKEN_LOGICAL_LT = 26,          /* TOKEN_LOGICAL_LT  */
  YYSYMBOL_TOKEN_LOGICAL_LE = 27,          /* TOKEN_LOGICAL_LE  */
  YYSYMBOL_TOKEN_STRUCTURE_OPEN = 28,      /* TOKEN_STRUCTURE_OPEN  */
  YYSYMBOL_TOKEN_STRUCTURE_VECTOR_OPEN = 29, /* TOKEN_STRUCTURE_VECTOR_OPEN  */
  YYSYMBOL_TOKEN_STRUCTURE_COMMA = 30,     /* TOKEN_STRUCTURE_COMMA  */
  YYSYMBOL_TOKEN_STRUCTURE_CLOSE = 31,     /* TOKEN_STRUCTURE_CLOSE  */
  YYSYMBOL_TOKEN_STRUCTURE_VECTOR_CLOSE = 32, /* TOKEN_STRUCTURE_VECTOR_CLOSE  */
  YYSYMBOL_YYACCEPT = 33,                  /* $accept  */
  YYSYMBOL_result = 34,                    /* result  */
  YYSYMBOL_d_or_b = 35,                    /* d_or_b  */
  YYSYMBOL_exp = 36,                       /* exp  */
  YYSYMBOL_bool = 37,                      /* bool  */
  YYSYMBOL_function = 38,                  /* function  */
  YYSYMBOL_fcont = 39,                     /* fcont  */
  YYSYMBOL_vector = 40,                    /* vector  */
  YYSYMBOL_vstart = 41,                    /* vstart  */
  YYSYMBOL_call = 42,                      /* call  */
  YYSYMBOL_ccont = 43                      /* ccont  */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  35
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   576

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  11
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  173

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   287


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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    89,    89,    94,    99,   105,   110,   115,   123,   133,
     138,   144,   151,   158,   165,   172,   179,   186,   191,   195,
     201,   208,   214,   223,   233,   243,   253,   264,   276,   281,
     289,   299,   309,   319,   330,   341,   348,   356,   363,   371,
     379,   386,   394,   401,   409,   417,   424,   431,   438,   445,
     452,   459,   466,   471,   477,   485,   489,   494,   500,   505,
     511,   516,   522,   528,   534,   538,   543,   547,   552,   557,
     562,   568,   572,   577,   582,   587
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_NUMBER",
  "TOKEN_VARIABLE", "TOKEN_UNIT", "TOKEN_CALL", "TOKEN_FUNCTION",
  "TOKEN_FUNCTION_1", "TOKEN_FUNCTION_2", "TOKEN_SIGN",
  "TOKEN_OPERATOR_POWER", "TOKEN_OPERATOR_MULTIPLY",
  "TOKEN_OPERATOR_MODULUS", "TOKEN_OPERATOR_REMAINDER",
  "TOKEN_OPERATOR_PLUS", "TOKEN_LOGICAL_CHOICE", "TOKEN_LOGICAL_VALUE",
  "TOKEN_LOGICAL_NOT", "TOKEN_LOGICAL_OR", "TOKEN_LOGICAL_XOR",
  "TOKEN_LOGICAL_AND", "TOKEN_LOGICAL_EQ", "TOKEN_LOGICAL_NE",
  "TOKEN_LOGICAL_GT", "TOKEN_LOGICAL_GE", "TOKEN_LOGICAL_LT",
  "TOKEN_LOGICAL_LE", "TOKEN_STRUCTURE_OPEN",
  "TOKEN_STRUCTURE_VECTOR_OPEN", "TOKEN_STRUCTURE_COMMA",
  "TOKEN_STRUCTURE_CLOSE", "TOKEN_STRUCTURE_VECTOR_CLOSE", "$accept",
  "result", "d_or_b", "exp", "bool", "function", "fcont", "vector",
  "vstart", "call", "ccont", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-52)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-55)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     257,   -52,   -52,   -28,   -10,    -8,    -4,   284,    -2,   -52,
     257,   257,    57,     5,   461,   176,   -52,   284,   -52,   227,
     -52,   211,   284,   284,    24,   284,   -52,    50,   257,   122,
     461,     7,   150,   312,   104,   -52,   257,   257,   284,   273,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   257,
     257,   257,   257,   257,     1,   200,   -21,   291,   481,   181,
     -24,   -52,    52,   318,    61,   257,   339,    28,   517,   -52,
     -52,   466,    58,   483,   -52,    50,   -52,    50,   117,   229,
     212,   559,   559,   559,   559,   559,   559,   288,    12,     7,
     171,    58,   130,   -52,   -52,   -52,   -52,   559,   -52,   -52,
     -52,   -52,   -52,   -52,   -52,   -52,   -52,   243,   -52,   -52,
     -52,   -52,   284,   124,   529,   257,   257,   559,   -52,   360,
     284,   284,   133,   407,   534,   144,   427,   546,   -52,    54,
     432,    60,   452,   257,   284,   257,   257,   284,   257,   284,
     284,    47,   333,   276,    56,   375,    66,   494,    82,   354,
     499,    72,   381,    87,   512,    75,   386,    80,   396,   -52,
     -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,
     -52,   -52,   -52
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     9,     6,    71,     0,     0,     0,     0,     0,    28,
       0,     0,     0,    10,     2,     3,    18,     0,     5,     0,
      66,     0,     0,     0,     0,     0,    10,    21,     0,    10,
       0,    53,    10,     0,     0,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    10,     0,     0,     0,
       0,    55,     0,     0,     0,     0,     0,    10,     0,    17,
      52,    36,    39,    41,    44,    16,    14,    15,    12,    13,
      11,    35,    40,    46,    45,    48,    47,    49,    50,    51,
      10,    37,    10,    42,    59,    57,    60,    62,    63,    72,
      67,    73,    68,    74,    69,    75,    70,     0,    61,    58,
      56,    19,     0,    10,     0,     0,     0,    64,    65,     0,
       0,     0,    10,     0,     0,    10,     0,     0,    20,    10,
       0,    10,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    10,     0,     0,    10,     0,    10,     0,    10,     0,
       0,    10,     0,    10,     0,    10,     0,    10,     0,     8,
      26,    33,    27,    25,    34,    32,     7,    23,    30,    24,
      22,    31,    29
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -52,   -52,    49,     0,    43,   -52,   -52,   -51,   -52,   -52,
     -52
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    12,    26,    30,    15,    16,    17,    59,    60,    18,
      19
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      14,    36,    37,    20,    98,    -4,   107,    27,   108,    99,
     100,    33,    38,    39,    40,    41,    42,    54,    21,    57,
      22,    62,    63,    64,    23,    66,    28,    36,    37,    52,
      53,    94,    95,    51,    52,    53,    71,    73,    75,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    13,
      36,    37,    65,    31,    34,    97,   118,    35,   115,    29,
      32,    38,    58,    38,    39,    40,    41,    42,    56,    36,
      37,    68,    38,    39,    40,    41,    42,    67,   159,    72,
      74,    53,   109,   110,   139,    32,    32,   162,    36,    37,
     140,   112,    87,    88,    89,    91,    93,   164,    32,    32,
      32,    90,    92,   169,    36,    37,   159,   117,   114,    36,
      37,   166,   119,   166,   113,   123,   126,     0,   171,     0,
     130,   132,   -54,    49,    50,    51,    52,    53,    38,    39,
     -43,    41,     0,   142,   145,    70,   149,   152,     0,   156,
     158,   -54,   -54,   -54,    36,    37,    36,    37,     0,   -43,
     -43,   -43,   -54,   -54,   120,    36,    37,     0,   124,   127,
     -43,   -43,     0,   133,   122,   125,    36,    37,     0,   129,
     131,   -38,    36,    37,   136,     0,   143,     0,   147,   150,
       0,   154,   141,   144,   146,   148,   151,   153,   155,   157,
     -38,   -38,   -38,     0,    37,    49,    50,    51,    52,    53,
       0,   -38,   -38,     1,     2,     0,     3,     4,     5,     6,
       7,   105,   106,     0,     1,     2,    24,     3,     4,     5,
       6,     7,     0,    38,    39,    40,    41,    24,    25,    55,
       1,     2,    96,     3,     4,     5,     6,     7,     0,    25,
      38,    39,    61,     8,     9,    10,     1,     2,     0,     3,
       4,     5,     6,     7,     0,    11,    55,     0,     0,    24,
       1,     2,     0,     3,     4,     5,     6,     7,     0,     0,
       0,    25,    55,     8,     9,    10,     1,     2,    76,     3,
       4,     5,     6,     7,     0,    11,     0,     1,     2,    24,
       3,     4,     5,     6,     7,    49,    50,    51,    52,    53,
      24,    25,    38,    39,    40,    41,    42,   161,    50,    51,
      52,    53,    25,    43,    44,    45,    46,    47,    48,     0,
       0,   101,   102,    38,    39,    40,    41,    42,     0,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
       0,     0,     0,    69,    38,    39,    40,    41,    42,   111,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     0,     0,     0,   160,    38,    39,    40,    41,    42,
      69,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,     0,     0,     0,   167,    38,    39,    40,    41,
      42,   128,    38,    39,    40,    41,    42,    38,    39,    40,
      41,    42,     0,     0,     0,     0,   163,    38,    39,    40,
      41,    42,   170,     0,     0,     0,     0,   160,    38,    39,
      40,    41,    42,     0,     0,     0,     0,   167,     0,    43,
      44,    45,    46,    47,    48,     0,     0,   134,    38,    39,
      40,    41,    42,    38,    39,    40,    41,    42,     0,    43,
      44,    45,    46,    47,    48,     0,     0,   137,     0,     0,
       0,     0,   134,    38,    39,    40,    41,    42,     0,     0,
       0,     0,    38,    39,    40,    41,    42,    38,    39,    40,
      41,    42,   137,    43,    44,    45,    46,    47,    48,    44,
      45,    46,    47,    48,    38,    39,    40,    41,    42,     0,
      49,    50,    51,    52,    53,     0,     0,    45,    46,    47,
      48,   103,   104,    49,    50,    51,    52,    53,    49,    50,
      51,    52,    53,     0,     0,   165,     0,     0,     0,     0,
     168,    49,    50,    51,    52,    53,    49,    50,    51,    52,
      53,     0,     0,   172,     0,     0,     0,   116,    49,    50,
      51,    52,    53,    49,    50,    51,    52,    53,     0,   121,
       0,     0,     0,     0,   135,    49,    50,    51,    52,    53,
      38,    39,    40,    41,    42,     0,   138
};

static const yytype_int16 yycheck[] =
{
       0,    22,    23,    31,    55,     0,    30,     7,    32,    30,
      31,    11,    11,    12,    13,    14,    15,    17,    28,    19,
      28,    21,    22,    23,    28,    25,    28,    22,    23,    22,
      23,    30,    31,    21,    22,    23,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,     0,
      22,    23,    28,    10,    11,    55,   107,     0,    30,    10,
      11,    11,    19,    11,    12,    13,    14,    15,    19,    22,
      23,    28,    11,    12,    13,    14,    15,    28,    31,    36,
      37,    23,    30,    31,    30,    36,    37,    31,    22,    23,
      30,    30,    49,    50,    51,    52,    53,    31,    49,    50,
      51,    52,    53,    31,    22,    23,    31,   107,    65,    22,
      23,    31,   112,    31,    65,   115,   116,    -1,    31,    -1,
     120,   121,     0,    19,    20,    21,    22,    23,    11,    12,
       0,    14,    -1,   133,   134,    31,   136,   137,    -1,   139,
     140,    19,    20,    21,    22,    23,    22,    23,    -1,    19,
      20,    21,    30,    31,    30,    22,    23,    -1,   115,   116,
      30,    31,    -1,    30,   115,   116,    22,    23,    -1,   120,
     121,     0,    22,    23,    30,    -1,   133,    -1,   135,   136,
      -1,   138,   133,   134,   135,   136,   137,   138,   139,   140,
      19,    20,    21,    -1,    23,    19,    20,    21,    22,    23,
      -1,    30,    31,     3,     4,    -1,     6,     7,     8,     9,
      10,    30,    31,    -1,     3,     4,    16,     6,     7,     8,
       9,    10,    -1,    11,    12,    13,    14,    16,    28,    29,
       3,     4,    32,     6,     7,     8,     9,    10,    -1,    28,
      11,    12,    31,    16,    17,    18,     3,     4,    -1,     6,
       7,     8,     9,    10,    -1,    28,    29,    -1,    -1,    16,
       3,     4,    -1,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    28,    29,    16,    17,    18,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    28,    -1,     3,     4,    16,
       6,     7,     8,     9,    10,    19,    20,    21,    22,    23,
      16,    28,    11,    12,    13,    14,    15,    31,    20,    21,
      22,    23,    28,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    11,    12,    13,    14,    15,    -1,    11,
      12,    13,    14,    15,    22,    23,    24,    25,    26,    27,
      -1,    -1,    -1,    31,    11,    12,    13,    14,    15,    31,
      11,    12,    13,    14,    15,    22,    23,    24,    25,    26,
      27,    -1,    -1,    -1,    31,    11,    12,    13,    14,    15,
      31,    11,    12,    13,    14,    15,    22,    23,    24,    25,
      26,    27,    -1,    -1,    -1,    31,    11,    12,    13,    14,
      15,    31,    11,    12,    13,    14,    15,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    31,    11,    12,    13,
      14,    15,    31,    -1,    -1,    -1,    -1,    31,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    31,    -1,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    11,    12,
      13,    14,    15,    11,    12,    13,    14,    15,    -1,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    30,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    11,    12,    13,    14,    15,    11,    12,    13,
      14,    15,    30,    22,    23,    24,    25,    26,    27,    23,
      24,    25,    26,    27,    11,    12,    13,    14,    15,    -1,
      19,    20,    21,    22,    23,    -1,    -1,    24,    25,    26,
      27,    30,    31,    19,    20,    21,    22,    23,    19,    20,
      21,    22,    23,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      31,    19,    20,    21,    22,    23,    19,    20,    21,    22,
      23,    -1,    -1,    31,    -1,    -1,    -1,    30,    19,    20,
      21,    22,    23,    19,    20,    21,    22,    23,    -1,    30,
      -1,    -1,    -1,    -1,    30,    19,    20,    21,    22,    23,
      11,    12,    13,    14,    15,    -1,    30
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     6,     7,     8,     9,    10,    16,    17,
      18,    28,    34,    35,    36,    37,    38,    39,    42,    43,
      31,    28,    28,    28,    16,    28,    35,    36,    28,    35,
      36,    37,    35,    36,    37,     0,    22,    23,    11,    12,
      13,    14,    15,    22,    23,    24,    25,    26,    27,    19,
      20,    21,    22,    23,    36,    29,    35,    36,    37,    40,
      41,    31,    36,    36,    36,    28,    36,    35,    37,    31,
      31,    36,    37,    36,    37,    36,     5,    36,    36,    36,
      36,    36,    36,    36,    36,    36,    36,    37,    37,    37,
      35,    37,    35,    37,    30,    31,    32,    36,    40,    30,
      31,    30,    31,    30,    31,    30,    31,    30,    32,    30,
      31,    31,    30,    35,    37,    30,    30,    36,    40,    36,
      30,    30,    35,    36,    37,    35,    36,    37,    31,    35,
      36,    35,    36,    30,    30,    30,    30,    30,    30,    30,
      30,    35,    36,    37,    35,    36,    35,    37,    35,    36,
      37,    35,    36,    35,    37,    35,    36,    35,    36,    31,
      31,    31,    31,    31,    31,    31,    31,    31,    31,    31,
      31,    31,    31
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    33,    34,    34,    34,    35,    35,    35,    35,    36,
      36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
      36,    36,    36,    36,    36,    36,    36,    36,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    38,    38,    38,    39,    39,
      40,    40,    41,    41,    41,    41,    42,    42,    42,    42,
      42,    43,    43,    43,    43,    43
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     8,     8,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     1,     4,
       6,     2,     8,     8,     8,     8,     8,     8,     1,     8,
       8,     8,     8,     8,     8,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     3,     4,     3,     4,     3,
       2,     2,     2,     2,     3,     3,     2,     3,     3,     3,
       3,     1,     3,     3,     3,     3
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
int yydebug = YYDEBUG;
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
  case 2: /* result: exp  */
#line 90 "CEvaluationParser.ypp"
          {
            mValueType = CEvaluationNode::ValueType::Number;
            mpRootNode = yyval; 
          }
#line 1324 "CEvaluationParser_yacc.cpp"
    break;

  case 3: /* result: bool  */
#line 95 "CEvaluationParser.ypp"
          {
            mValueType = CEvaluationNode::ValueType::Boolean;
            mpRootNode = yyval; 
          }
#line 1333 "CEvaluationParser_yacc.cpp"
    break;

  case 4: /* result: d_or_b  */
#line 100 "CEvaluationParser.ypp"
          {
            mValueType = CEvaluationNode::ValueType::Unknown;
            mpRootNode = yyval; 
          }
#line 1342 "CEvaluationParser_yacc.cpp"
    break;

  case 5: /* d_or_b: call  */
#line 106 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[0];
            mpRootNode = yyval; 
          }
#line 1351 "CEvaluationParser_yacc.cpp"
    break;

  case 6: /* d_or_b: TOKEN_VARIABLE  */
#line 111 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[0];
            mpRootNode = yyval; 
          }
#line 1360 "CEvaluationParser_yacc.cpp"
    break;

  case 7: /* d_or_b: TOKEN_LOGICAL_CHOICE TOKEN_STRUCTURE_OPEN bool TOKEN_STRUCTURE_COMMA d_or_b TOKEN_STRUCTURE_COMMA d_or_b TOKEN_STRUCTURE_CLOSE  */
#line 116 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-7];
            yyval->addChild(yyvsp[-5]); 
            yyval->addChild(yyvsp[-3]); 
            yyval->addChild(yyvsp[-1]); 
            mpRootNode = yyval; 
          }
#line 1372 "CEvaluationParser_yacc.cpp"
    break;

  case 8: /* d_or_b: TOKEN_LOGICAL_CHOICE TOKEN_STRUCTURE_OPEN d_or_b TOKEN_STRUCTURE_COMMA d_or_b TOKEN_STRUCTURE_COMMA d_or_b TOKEN_STRUCTURE_CLOSE  */
#line 124 "CEvaluationParser.ypp"
          {
            yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval = yyvsp[-7];
            yyval->addChild(yyvsp[-5]); 
            yyval->addChild(yyvsp[-3]); 
            yyval->addChild(yyvsp[-1]); 
            mpRootNode = yyval; 
          }
#line 1385 "CEvaluationParser_yacc.cpp"
    break;

  case 9: /* exp: TOKEN_NUMBER  */
#line 134 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[0];
            mpRootNode = yyval; 
          }
#line 1394 "CEvaluationParser_yacc.cpp"
    break;

  case 10: /* exp: d_or_b  */
#line 139 "CEvaluationParser.ypp"
          {
            yyvsp[0]->setValueType(CEvaluationNode::ValueType::Number);
            yyval = yyvsp[0];
            mpRootNode = yyval; 
          }
#line 1404 "CEvaluationParser_yacc.cpp"
    break;

  case 11: /* exp: exp TOKEN_OPERATOR_PLUS exp  */
#line 145 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1415 "CEvaluationParser_yacc.cpp"
    break;

  case 12: /* exp: exp TOKEN_OPERATOR_MODULUS exp  */
#line 152 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1426 "CEvaluationParser_yacc.cpp"
    break;

  case 13: /* exp: exp TOKEN_OPERATOR_REMAINDER exp  */
#line 159 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1437 "CEvaluationParser_yacc.cpp"
    break;

  case 14: /* exp: exp TOKEN_OPERATOR_MULTIPLY TOKEN_UNIT  */
#line 166 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1448 "CEvaluationParser_yacc.cpp"
    break;

  case 15: /* exp: exp TOKEN_OPERATOR_MULTIPLY exp  */
#line 173 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1459 "CEvaluationParser_yacc.cpp"
    break;

  case 16: /* exp: exp TOKEN_OPERATOR_POWER exp  */
#line 180 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1470 "CEvaluationParser_yacc.cpp"
    break;

  case 17: /* exp: TOKEN_STRUCTURE_OPEN exp TOKEN_STRUCTURE_CLOSE  */
#line 187 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            mpRootNode = yyval; 
          }
#line 1479 "CEvaluationParser_yacc.cpp"
    break;

  case 18: /* exp: function  */
#line 192 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[0];
          }
#line 1487 "CEvaluationParser_yacc.cpp"
    break;

  case 19: /* exp: TOKEN_FUNCTION_1 TOKEN_STRUCTURE_OPEN exp TOKEN_STRUCTURE_CLOSE  */
#line 196 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-3];
            yyval->addChild(yyvsp[-1]);
            mpRootNode = yyval; 
          }
#line 1497 "CEvaluationParser_yacc.cpp"
    break;

  case 20: /* exp: TOKEN_FUNCTION_2 TOKEN_STRUCTURE_OPEN exp TOKEN_STRUCTURE_COMMA exp TOKEN_STRUCTURE_CLOSE  */
#line 202 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-5];
            yyval->addChild(yyvsp[-3]);
            yyval->addChild(yyvsp[-1]);
            mpRootNode = yyval; 
          }
#line 1508 "CEvaluationParser_yacc.cpp"
    break;

  case 21: /* exp: TOKEN_SIGN exp  */
#line 209 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1518 "CEvaluationParser_yacc.cpp"
    break;

  case 22: /* exp: TOKEN_LOGICAL_CHOICE TOKEN_STRUCTURE_OPEN bool TOKEN_STRUCTURE_COMMA exp TOKEN_STRUCTURE_COMMA exp TOKEN_STRUCTURE_CLOSE  */
#line 215 "CEvaluationParser.ypp"
          {
            yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Number); 
            yyval = yyvsp[-7];
            yyval->addChild(yyvsp[-5]); 
            yyval->addChild(yyvsp[-3]); 
            yyval->addChild(yyvsp[-1]); 
            mpRootNode = yyval; 
          }
#line 1531 "CEvaluationParser_yacc.cpp"
    break;

  case 23: /* exp: TOKEN_LOGICAL_CHOICE TOKEN_STRUCTURE_OPEN bool TOKEN_STRUCTURE_COMMA d_or_b TOKEN_STRUCTURE_COMMA exp TOKEN_STRUCTURE_CLOSE  */
#line 224 "CEvaluationParser.ypp"
          {
            yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Number); 
            yyval = yyvsp[-7];
            yyval->addChild(yyvsp[-5]); 
            yyvsp[-3]->setValueType(CEvaluationNode::ValueType::Number); 
            yyval->addChild(yyvsp[-3]);
            yyval->addChild(yyvsp[-1]); 
            mpRootNode = yyval; 
          }
#line 1545 "CEvaluationParser_yacc.cpp"
    break;

  case 24: /* exp: TOKEN_LOGICAL_CHOICE TOKEN_STRUCTURE_OPEN bool TOKEN_STRUCTURE_COMMA exp TOKEN_STRUCTURE_COMMA d_or_b TOKEN_STRUCTURE_CLOSE  */
#line 234 "CEvaluationParser.ypp"
          {
            yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Number); 
            yyval = yyvsp[-7];
            yyval->addChild(yyvsp[-5]); 
            yyval->addChild(yyvsp[-3]); 
            yyvsp[-1]->setValueType(CEvaluationNode::ValueType::Number); 
            yyval->addChild(yyvsp[-1]); 
            mpRootNode = yyval; 
          }
#line 1559 "CEvaluationParser_yacc.cpp"
    break;

  case 25: /* exp: TOKEN_LOGICAL_CHOICE TOKEN_STRUCTURE_OPEN d_or_b TOKEN_STRUCTURE_COMMA exp TOKEN_STRUCTURE_COMMA exp TOKEN_STRUCTURE_CLOSE  */
#line 244 "CEvaluationParser.ypp"
          {
            yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Number); 
            yyval = yyvsp[-7];
            yyvsp[-5]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval->addChild(yyvsp[-5]); 
            yyval->addChild(yyvsp[-3]); 
            yyval->addChild(yyvsp[-1]); 
            mpRootNode = yyval; 
          }
#line 1573 "CEvaluationParser_yacc.cpp"
    break;

  case 26: /* exp: TOKEN_LOGICAL_CHOICE TOKEN_STRUCTURE_OPEN d_or_b TOKEN_STRUCTURE_COMMA d_or_b TOKEN_STRUCTURE_COMMA exp TOKEN_STRUCTURE_CLOSE  */
#line 254 "CEvaluationParser.ypp"
          {
            yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Number); 
            yyval = yyvsp[-7];
            yyvsp[-5]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval->addChild(yyvsp[-5]); 
            yyvsp[-3]->setValueType(CEvaluationNode::ValueType::Number); 
            yyval->addChild(yyvsp[-3]); 
            yyval->addChild(yyvsp[-1]); 
            mpRootNode = yyval; 
          }
#line 1588 "CEvaluationParser_yacc.cpp"
    break;

  case 27: /* exp: TOKEN_LOGICAL_CHOICE TOKEN_STRUCTURE_OPEN d_or_b TOKEN_STRUCTURE_COMMA exp TOKEN_STRUCTURE_COMMA d_or_b TOKEN_STRUCTURE_CLOSE  */
#line 265 "CEvaluationParser.ypp"
          {
            yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Number); 
            yyval = yyvsp[-7];
            yyvsp[-5]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval->addChild(yyvsp[-5]); 
            yyval->addChild(yyvsp[-3]); 
            yyvsp[-1]->setValueType(CEvaluationNode::ValueType::Number); 
            yyval->addChild(yyvsp[-1]); 
            mpRootNode = yyval; 
          }
#line 1603 "CEvaluationParser_yacc.cpp"
    break;

  case 28: /* bool: TOKEN_LOGICAL_VALUE  */
#line 277 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[0];
            mpRootNode = yyval; 
          }
#line 1612 "CEvaluationParser_yacc.cpp"
    break;

  case 29: /* bool: TOKEN_LOGICAL_CHOICE TOKEN_STRUCTURE_OPEN bool TOKEN_STRUCTURE_COMMA bool TOKEN_STRUCTURE_COMMA bool TOKEN_STRUCTURE_CLOSE  */
#line 282 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-7];
            yyval->addChild(yyvsp[-5]); 
            yyval->addChild(yyvsp[-3]); 
            yyval->addChild(yyvsp[-1]); 
            mpRootNode = yyval; 
          }
#line 1624 "CEvaluationParser_yacc.cpp"
    break;

  case 30: /* bool: TOKEN_LOGICAL_CHOICE TOKEN_STRUCTURE_OPEN bool TOKEN_STRUCTURE_COMMA d_or_b TOKEN_STRUCTURE_COMMA bool TOKEN_STRUCTURE_CLOSE  */
#line 290 "CEvaluationParser.ypp"
          {
            yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Boolean); 
            yyval = yyvsp[-7];
            yyval->addChild(yyvsp[-5]); 
            yyvsp[-3]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval->addChild(yyvsp[-3]); 
            yyval->addChild(yyvsp[-1]); 
            mpRootNode = yyval; 
          }
#line 1638 "CEvaluationParser_yacc.cpp"
    break;

  case 31: /* bool: TOKEN_LOGICAL_CHOICE TOKEN_STRUCTURE_OPEN bool TOKEN_STRUCTURE_COMMA bool TOKEN_STRUCTURE_COMMA d_or_b TOKEN_STRUCTURE_CLOSE  */
#line 300 "CEvaluationParser.ypp"
          {
            yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Boolean); 
            yyval = yyvsp[-7];
            yyval->addChild(yyvsp[-5]); 
            yyval->addChild(yyvsp[-3]); 
            yyvsp[-1]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval->addChild(yyvsp[-1]); 
            mpRootNode = yyval; 
          }
#line 1652 "CEvaluationParser_yacc.cpp"
    break;

  case 32: /* bool: TOKEN_LOGICAL_CHOICE TOKEN_STRUCTURE_OPEN d_or_b TOKEN_STRUCTURE_COMMA bool TOKEN_STRUCTURE_COMMA bool TOKEN_STRUCTURE_CLOSE  */
#line 310 "CEvaluationParser.ypp"
          {
            yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval = yyvsp[-7];
            yyvsp[-5]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval->addChild(yyvsp[-5]); 
            yyval->addChild(yyvsp[-3]); 
            yyval->addChild(yyvsp[-1]); 
            mpRootNode = yyval; 
          }
#line 1666 "CEvaluationParser_yacc.cpp"
    break;

  case 33: /* bool: TOKEN_LOGICAL_CHOICE TOKEN_STRUCTURE_OPEN d_or_b TOKEN_STRUCTURE_COMMA d_or_b TOKEN_STRUCTURE_COMMA bool TOKEN_STRUCTURE_CLOSE  */
#line 320 "CEvaluationParser.ypp"
          {
            yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval = yyvsp[-7];
            yyvsp[-5]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval->addChild(yyvsp[-5]); 
            yyvsp[-3]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval->addChild(yyvsp[-3]); 
            yyval->addChild(yyvsp[-1]); 
            mpRootNode = yyval; 
          }
#line 1681 "CEvaluationParser_yacc.cpp"
    break;

  case 34: /* bool: TOKEN_LOGICAL_CHOICE TOKEN_STRUCTURE_OPEN d_or_b TOKEN_STRUCTURE_COMMA bool TOKEN_STRUCTURE_COMMA d_or_b TOKEN_STRUCTURE_CLOSE  */
#line 331 "CEvaluationParser.ypp"
          {
            yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval = yyvsp[-7];
            yyvsp[-5]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval->addChild(yyvsp[-5]); 
            yyval->addChild(yyvsp[-3]); 
            yyvsp[-1]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval->addChild(yyvsp[-1]); 
            mpRootNode = yyval; 
          }
#line 1696 "CEvaluationParser_yacc.cpp"
    break;

  case 35: /* bool: exp TOKEN_LOGICAL_EQ exp  */
#line 342 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1707 "CEvaluationParser_yacc.cpp"
    break;

  case 36: /* bool: d_or_b TOKEN_LOGICAL_EQ exp  */
#line 349 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyvsp[-2]->setValueType(CEvaluationNode::ValueType::Number);
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1719 "CEvaluationParser_yacc.cpp"
    break;

  case 37: /* bool: bool TOKEN_LOGICAL_EQ bool  */
#line 357 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1730 "CEvaluationParser_yacc.cpp"
    break;

  case 38: /* bool: bool TOKEN_LOGICAL_EQ d_or_b  */
#line 364 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyvsp[0]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1742 "CEvaluationParser_yacc.cpp"
    break;

  case 39: /* bool: d_or_b TOKEN_LOGICAL_EQ bool  */
#line 372 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyvsp[-2]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1754 "CEvaluationParser_yacc.cpp"
    break;

  case 40: /* bool: exp TOKEN_LOGICAL_NE exp  */
#line 380 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1765 "CEvaluationParser_yacc.cpp"
    break;

  case 41: /* bool: d_or_b TOKEN_LOGICAL_NE exp  */
#line 387 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyvsp[-2]->setValueType(CEvaluationNode::ValueType::Number);
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1777 "CEvaluationParser_yacc.cpp"
    break;

  case 42: /* bool: bool TOKEN_LOGICAL_NE bool  */
#line 395 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1788 "CEvaluationParser_yacc.cpp"
    break;

  case 43: /* bool: bool TOKEN_LOGICAL_NE d_or_b  */
#line 402 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyvsp[0]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1800 "CEvaluationParser_yacc.cpp"
    break;

  case 44: /* bool: d_or_b TOKEN_LOGICAL_NE bool  */
#line 410 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyvsp[-2]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1812 "CEvaluationParser_yacc.cpp"
    break;

  case 45: /* bool: exp TOKEN_LOGICAL_GE exp  */
#line 418 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1823 "CEvaluationParser_yacc.cpp"
    break;

  case 46: /* bool: exp TOKEN_LOGICAL_GT exp  */
#line 425 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1834 "CEvaluationParser_yacc.cpp"
    break;

  case 47: /* bool: exp TOKEN_LOGICAL_LE exp  */
#line 432 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1845 "CEvaluationParser_yacc.cpp"
    break;

  case 48: /* bool: exp TOKEN_LOGICAL_LT exp  */
#line 439 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1856 "CEvaluationParser_yacc.cpp"
    break;

  case 49: /* bool: bool TOKEN_LOGICAL_OR bool  */
#line 446 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1867 "CEvaluationParser_yacc.cpp"
    break;

  case 50: /* bool: bool TOKEN_LOGICAL_XOR bool  */
#line 453 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1878 "CEvaluationParser_yacc.cpp"
    break;

  case 51: /* bool: bool TOKEN_LOGICAL_AND bool  */
#line 460 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[-2]); 
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1889 "CEvaluationParser_yacc.cpp"
    break;

  case 52: /* bool: TOKEN_STRUCTURE_OPEN bool TOKEN_STRUCTURE_CLOSE  */
#line 467 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            mpRootNode = yyval; 
          }
#line 1898 "CEvaluationParser_yacc.cpp"
    break;

  case 53: /* bool: TOKEN_LOGICAL_NOT bool  */
#line 472 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1908 "CEvaluationParser_yacc.cpp"
    break;

  case 54: /* bool: TOKEN_LOGICAL_NOT d_or_b  */
#line 478 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
            yyvsp[0]->setValueType(CEvaluationNode::ValueType::Boolean);
            yyval->addChild(yyvsp[0]);
            mpRootNode = yyval; 
          }
#line 1919 "CEvaluationParser_yacc.cpp"
    break;

  case 55: /* function: TOKEN_FUNCTION TOKEN_STRUCTURE_OPEN TOKEN_STRUCTURE_CLOSE  */
#line 486 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-2];
          }
#line 1927 "CEvaluationParser_yacc.cpp"
    break;

  case 56: /* function: TOKEN_FUNCTION TOKEN_STRUCTURE_OPEN exp TOKEN_STRUCTURE_CLOSE  */
#line 490 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-3];
            yyval->addChild(yyvsp[-1]);
          }
#line 1936 "CEvaluationParser_yacc.cpp"
    break;

  case 57: /* function: fcont exp TOKEN_STRUCTURE_CLOSE  */
#line 495 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-2];
            yyval->addChild(yyvsp[-1]);
          }
#line 1945 "CEvaluationParser_yacc.cpp"
    break;

  case 58: /* fcont: TOKEN_FUNCTION TOKEN_STRUCTURE_OPEN exp TOKEN_STRUCTURE_COMMA  */
#line 501 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-3];
            yyval->addChild(yyvsp[-1]);
          }
#line 1954 "CEvaluationParser_yacc.cpp"
    break;

  case 59: /* fcont: fcont exp TOKEN_STRUCTURE_COMMA  */
#line 506 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-2];
            yyval->addChild(yyvsp[-1]);
          }
#line 1963 "CEvaluationParser_yacc.cpp"
    break;

  case 60: /* vector: TOKEN_STRUCTURE_VECTOR_OPEN TOKEN_STRUCTURE_VECTOR_CLOSE  */
#line 512 "CEvaluationParser.ypp"
          {
            yyval = new CEvaluationNodeVector();
            mpNodeList->push_back(yyval);
          }
#line 1972 "CEvaluationParser_yacc.cpp"
    break;

  case 61: /* vector: vstart TOKEN_STRUCTURE_VECTOR_CLOSE  */
#line 517 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
          }
#line 1980 "CEvaluationParser_yacc.cpp"
    break;

  case 62: /* vstart: TOKEN_STRUCTURE_VECTOR_OPEN exp  */
#line 523 "CEvaluationParser.ypp"
          {
            yyval = new CEvaluationNodeVector();
            mpNodeList->push_back(yyval);
            yyval->addChild(yyvsp[0]);
          }
#line 1990 "CEvaluationParser_yacc.cpp"
    break;

  case 63: /* vstart: TOKEN_STRUCTURE_VECTOR_OPEN vector  */
#line 529 "CEvaluationParser.ypp"
          {
            yyval = new CEvaluationNodeVector();
            mpNodeList->push_back(yyval);
            yyval->addChild(yyvsp[0]);
          }
#line 2000 "CEvaluationParser_yacc.cpp"
    break;

  case 64: /* vstart: vstart TOKEN_STRUCTURE_COMMA exp  */
#line 535 "CEvaluationParser.ypp"
          {
            yyval->addChild(yyvsp[0]);
          }
#line 2008 "CEvaluationParser_yacc.cpp"
    break;

  case 65: /* vstart: vstart TOKEN_STRUCTURE_COMMA vector  */
#line 539 "CEvaluationParser.ypp"
          {
            yyval->addChild(yyvsp[0]);
          }
#line 2016 "CEvaluationParser_yacc.cpp"
    break;

  case 66: /* call: TOKEN_CALL TOKEN_STRUCTURE_CLOSE  */
#line 544 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-1];
          }
#line 2024 "CEvaluationParser_yacc.cpp"
    break;

  case 67: /* call: ccont d_or_b TOKEN_STRUCTURE_CLOSE  */
#line 548 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-2];
            yyval->addChild(yyvsp[-1]); 
          }
#line 2033 "CEvaluationParser_yacc.cpp"
    break;

  case 68: /* call: ccont exp TOKEN_STRUCTURE_CLOSE  */
#line 553 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-2];
            yyval->addChild(yyvsp[-1]); 
          }
#line 2042 "CEvaluationParser_yacc.cpp"
    break;

  case 69: /* call: ccont bool TOKEN_STRUCTURE_CLOSE  */
#line 558 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-2];
            yyval->addChild(yyvsp[-1]); 
          }
#line 2051 "CEvaluationParser_yacc.cpp"
    break;

  case 70: /* call: ccont vector TOKEN_STRUCTURE_CLOSE  */
#line 563 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-2];
            yyval->addChild(yyvsp[-1]); 
          }
#line 2060 "CEvaluationParser_yacc.cpp"
    break;

  case 71: /* ccont: TOKEN_CALL  */
#line 569 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[0];
          }
#line 2068 "CEvaluationParser_yacc.cpp"
    break;

  case 72: /* ccont: ccont d_or_b TOKEN_STRUCTURE_COMMA  */
#line 573 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-2];
            yyval->addChild(yyvsp[-1]); 
          }
#line 2077 "CEvaluationParser_yacc.cpp"
    break;

  case 73: /* ccont: ccont exp TOKEN_STRUCTURE_COMMA  */
#line 578 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-2];
            yyval->addChild(yyvsp[-1]); 
          }
#line 2086 "CEvaluationParser_yacc.cpp"
    break;

  case 74: /* ccont: ccont bool TOKEN_STRUCTURE_COMMA  */
#line 583 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-2];
            yyval->addChild(yyvsp[-1]); 
          }
#line 2095 "CEvaluationParser_yacc.cpp"
    break;

  case 75: /* ccont: ccont vector TOKEN_STRUCTURE_COMMA  */
#line 588 "CEvaluationParser.ypp"
          {
            yyval = yyvsp[-2];
            yyval->addChild(yyvsp[-1]); 
          }
#line 2104 "CEvaluationParser_yacc.cpp"
    break;


#line 2108 "CEvaluationParser_yacc.cpp"

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
      yyerror (YY_("syntax error"));
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

  return yyresult;
}

#line 594 "CEvaluationParser.ypp"


