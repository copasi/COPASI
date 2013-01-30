// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/* A Bison parser, made by GNU Bison 2.6.5.  */

/* Bison implementation for Yacc-like parsers in C

      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.6.5"

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
#define yylval          CEvaluationParserlval
#define yychar          CEvaluationParserchar
#define yydebug         CEvaluationParserdebug
#define yynerrs         CEvaluationParsernerrs

/* Copy the first part of user declarations.  */
/* Line 360 of yacc.c  */
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

#include "copasi.h"
#include "CEvaluationNode.h"
#include "CEvaluationLexer.h"

#undef yyparse
#define yyparse CEvaluationParserBase::yyparse

void setBooleanRequired(CEvaluationNode * pNode, const bool & booleanRequired)
{
  if (CEvaluationNode::type(pNode->getType()) == CEvaluationNode::CALL)
    {
      static_cast<CEvaluationNodeCall *>(pNode)->setBooleanRequired(booleanRequired);
    }
}

/* Line 360 of yacc.c  */
#line 107 "CEvaluationParser_yacc.cpppp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "CEvaluationParser.tab.hpp".  */
#ifndef YY_CEVALUATIONPARSER_CEVALUATIONPARSER_TAB_HPP_INCLUDED
# define YY_CEVALUATIONPARSER_CEVALUATIONPARSER_TAB_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int CEvaluationParserdebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
/* Put the tokens into the symbol table, so that GDB and other debuggers
   know about them.  */
enum yytokentype
{
  TOKEN_NUMBER = 258,
  TOKEN_VARIABLE = 259,
  TOKEN_CALL = 260,
  TOKEN_FUNCTION = 261,
  TOKEN_FUNCTION_2 = 262,
  TOKEN_SIGN = 263,
  TOKEN_OPERATOR_POWER = 264,
  TOKEN_OPERATOR_MULTIPLY = 265,
  TOKEN_OPERATOR_MODULUS = 266,
  TOKEN_OPERATOR_PLUS = 267,
  TOKEN_LOGICAL_CHOICE = 268,
  TOKEN_LOGICAL_VALUE = 269,
  TOKEN_LOGICAL_NOT = 270,
  TOKEN_LOGICAL_OR = 271,
  TOKEN_LOGICAL_XOR = 272,
  TOKEN_LOGICAL_AND = 273,
  TOKEN_LOGICAL_EQ = 274,
  TOKEN_LOGICAL_NE = 275,
  TOKEN_LOGICAL_GT = 276,
  TOKEN_LOGICAL_GE = 277,
  TOKEN_LOGICAL_LT = 278,
  TOKEN_LOGICAL_LE = 279,
  TOKEN_STRUCTURE_OPEN = 280,
  TOKEN_STRUCTURE_VECTOR_OPEN = 281,
  TOKEN_STRUCTURE_COMMA = 282,
  TOKEN_STRUCTURE_CLOSE = 283,
  TOKEN_STRUCTURE_VECTOR_CLOSE = 284
};
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE CEvaluationParserlval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
#else
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
#else
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_CEVALUATIONPARSER_CEVALUATIONPARSER_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 379 of yacc.c  */
#line 202 "CEvaluationParser_yacc.cpppp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID(int yyi)
#else
static int
YYID(yyi)
int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
/* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do {/* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc(YYSIZE_T);  /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free(void *);  /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
   || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
  ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
   + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)       \
  do                  \
    {\
      YYSIZE_T yynewbytes;            \
      YYCOPY (&yyptr->Stack_alloc, Stack, yysize);      \
      Stack = &yyptr->Stack_alloc;          \
      yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
      yyptr += yynewbytes / sizeof (*yyptr);        \
    }                 \
  while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
  __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
  do                                        \
    {\
      YYSIZE_T yyi;                         \
      for (yyi = 0; yyi < (Count); yyi++)   \
        (Dst)[yyi] = (Src)[yyi];            \
    }                                       \
  while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   409

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  8
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNRULES -- Number of states.  */
#define YYNSTATES  129

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

#define YYTRANSLATE(YYX)            \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
  25,    26,    27,    28,    29
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
  0,     0,     3,     5,     7,     9,    11,    15,    19,    23,
  27,    31,    36,    43,    46,    55,    64,    66,    68,    77,
  86,    90,    94,    98,   102,   106,   110,   114,   118,   122,
  126,   130,   134,   138,   142,   146,   150,   154,   158,   162,
  166,   170,   174,   178,   182,   186,   189,   192,   195,   198,
  201,   204,   208,   212,   215,   219,   223,   225,   229
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
  31,     0,    -1,    32,    -1,    33,    -1,     3,    -1,     4,
  -1,    32,    12,    32,    -1,    32,    11,    32,    -1,    32,
  10,    32,    -1,    32,     9,    32,    -1,    25,    32,    28,
  -1,     6,    25,    32,    28,    -1,     7,    25,    32,    27,
  32,    28,    -1,     8,    32,    -1,    13,    25,    33,    27,
  32,    27,    32,    28,    -1,    13,    25,    36,    27,    32,
  27,    32,    28,    -1,    36,    -1,    14,    -1,    13,    25,
  33,    27,    33,    27,    33,    28,    -1,    13,    25,    36,
  27,    33,    27,    33,    28,    -1,    32,    19,    32,    -1,
  36,    19,    33,    -1,    33,    19,    36,    -1,    33,    19,
  33,    -1,    32,    20,    32,    -1,    36,    20,    33,    -1,
  33,    20,    36,    -1,    33,    20,    33,    -1,    32,    21,
  32,    -1,    32,    22,    32,    -1,    32,    23,    32,    -1,
  32,    24,    32,    -1,    33,    16,    33,    -1,    36,    16,
  33,    -1,    33,    16,    36,    -1,    36,    16,    36,    -1,
  33,    17,    33,    -1,    36,    17,    33,    -1,    33,    17,
  36,    -1,    36,    17,    36,    -1,    33,    18,    33,    -1,
  36,    18,    33,    -1,    33,    18,    36,    -1,    36,    18,
  36,    -1,    25,    33,    28,    -1,    15,    33,    -1,    15,
  36,    -1,    26,    29,    -1,    35,    29,    -1,    26,    32,
  -1,    26,    34,    -1,    35,    27,    32,    -1,    35,    27,
  34,    -1,     5,    28,    -1,    37,    32,    28,    -1,    37,
  34,    28,    -1,     5,    -1,    37,    32,    27,    -1,    37,
  34,    27,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
  0,    92,    92,    97,   103,   107,   111,   118,   125,   132,
  139,   144,   150,   157,   163,   171,   179,   185,   189,   197,
  205,   212,   220,   228,   235,   242,   250,   258,   265,   272,
  279,   286,   293,   300,   308,   316,   325,   332,   340,   348,
  357,   364,   372,   380,   389,   394,   400,   408,   413,   419,
  425,   431,   435,   440,   444,   449,   455,   459,   464
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_NUMBER", "TOKEN_VARIABLE",
  "TOKEN_CALL", "TOKEN_FUNCTION", "TOKEN_FUNCTION_2", "TOKEN_SIGN",
  "TOKEN_OPERATOR_POWER", "TOKEN_OPERATOR_MULTIPLY",
  "TOKEN_OPERATOR_MODULUS", "TOKEN_OPERATOR_PLUS", "TOKEN_LOGICAL_CHOICE",
  "TOKEN_LOGICAL_VALUE", "TOKEN_LOGICAL_NOT", "TOKEN_LOGICAL_OR",
  "TOKEN_LOGICAL_XOR", "TOKEN_LOGICAL_AND", "TOKEN_LOGICAL_EQ",
  "TOKEN_LOGICAL_NE", "TOKEN_LOGICAL_GT", "TOKEN_LOGICAL_GE",
  "TOKEN_LOGICAL_LT", "TOKEN_LOGICAL_LE", "TOKEN_STRUCTURE_OPEN",
  "TOKEN_STRUCTURE_VECTOR_OPEN", "TOKEN_STRUCTURE_COMMA",
  "TOKEN_STRUCTURE_CLOSE", "TOKEN_STRUCTURE_VECTOR_CLOSE", "$accept",
  "result", "exp", "bool", "vector", "vstart", "call", "cstart", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
  0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
  265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
  275,   276,   277,   278,   279,   280,   281,   282,   283,   284
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
  0,    30,    31,    31,    32,    32,    32,    32,    32,    32,
  32,    32,    32,    32,    32,    32,    32,    33,    33,    33,
  33,    33,    33,    33,    33,    33,    33,    33,    33,    33,
  33,    33,    33,    33,    33,    33,    33,    33,    33,    33,
  33,    33,    33,    33,    33,    33,    33,    34,    34,    35,
  35,    35,    35,    36,    36,    36,    37,    37,    37
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
  0,     2,     1,     1,     1,     1,     3,     3,     3,     3,
  3,     4,     6,     2,     8,     8,     1,     1,     8,     8,
  3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
  3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
  3,     3,     3,     3,     3,     2,     2,     2,     2,     2,
  2,     3,     3,     2,     3,     3,     1,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
  0,     4,     5,    56,     0,     0,     0,     0,    17,     0,
  0,     0,     2,     3,    16,     0,    53,     0,     0,     0,
  0,    13,    16,     0,     0,    45,    16,     0,     0,     1,
  0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
  0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
  0,     0,     0,     0,     0,     0,     0,     0,     0,    16,
  10,    44,     9,     8,     7,     6,    20,    24,    28,    29,
  30,    31,    32,    16,    36,    16,    40,    16,    23,    16,
  27,    16,    33,    16,    37,    16,    41,    16,    21,    25,
  47,    49,    50,    57,    54,    58,    55,     0,    48,    11,
  0,     0,    16,     0,     0,    51,    52,     0,     0,     0,
  0,     0,     0,     0,    12,     0,     0,     0,     0,     0,
  0,     0,     0,     0,     0,    14,    18,    15,    19
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
  -1,    11,    24,    13,    52,    53,    22,    15
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -48
static const yytype_int16 yypact[] =
{
  241,   -48,   -48,   -26,   -14,    -9,   254,     2,   -48,   241,
  241,    59,   333,   147,   175,   225,   -48,   254,   254,    42,
  254,    63,   -48,   241,   333,    74,     1,   261,   282,   -48,
  254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
  241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
  214,     3,    94,    31,    64,    -5,   241,   121,   343,   348,
  -48,   -48,    63,    63,   188,    23,   117,   117,   117,   117,
  117,   117,   217,    79,    19,   119,    74,   125,    80,   196,
  -48,     8,   217,   157,    19,   162,    74,   183,    80,   -48,
  -48,   117,   -48,   -48,   -48,   -48,   -48,   225,   -48,   -48,
  254,   360,   365,   241,   241,   117,   -48,   197,   254,   254,
  295,   377,   314,   382,   -48,    43,    53,   254,   241,   254,
  241,   265,   311,   285,   330,   -48,   -48,   -48,   -48
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
  -48,   -48,    51,    68,   -47,   -48,     0,   -48
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -47
static const yytype_int16 yytable[] =
{
  14,   -46,    16,    92,    30,    31,    32,    33,   -26,    26,
  14,    17,    30,    31,    32,    33,    18,   -46,   -46,   -46,
  48,    49,   100,    59,   -26,   -26,   -26,    23,   -46,   -46,
  93,    94,    30,    31,    32,   -26,   -26,    42,    43,    44,
  73,    75,    77,    79,    81,    83,    85,    87,    14,    14,
  106,    12,    30,    31,    32,    33,   102,    21,    97,    29,
  98,    27,    30,    31,    32,    33,    51,    56,    54,    55,
  117,    57,    30,    30,    31,    32,    33,    25,    28,   -34,
  119,    62,    63,    64,    65,    66,    67,    68,    69,    70,
  71,    58,    99,    43,    44,   -34,    46,    47,    48,    49,
  44,    91,     0,    14,    14,     0,   -34,   -34,    72,    74,
  76,    78,    80,    82,    84,    86,    88,    89,    14,   -38,
  14,    95,    96,     0,   101,   -42,    30,    31,    32,    33,
  30,    31,    32,    33,     0,   -38,   -38,    47,    48,    49,
  0,   -42,   -42,   -42,    48,    49,   -38,   -38,   105,    60,
  0,   107,   -42,   -42,   110,   112,     0,   -35,     0,   115,
  116,     0,   -39,    40,    41,    42,    43,    44,   121,     0,
  123,   111,   113,   -35,    46,    47,    48,    49,   -39,   -39,
  47,    48,    49,   -43,   -35,   -35,   122,     0,   124,   -39,
  -39,    45,    46,    47,    48,    49,   -22,    30,    31,   -43,
  -43,   -43,    48,    49,     0,     0,    30,    31,    32,    33,
  -43,   -43,   -22,   -22,   -22,     0,    49,     1,     2,     3,
  4,     5,     6,   -22,   -22,   114,     0,    19,     1,     2,
  3,     4,     5,     6,    41,    42,    43,    44,    19,    20,
  50,     0,     0,    90,     1,     2,     3,     4,     5,     6,
  20,    50,     0,     0,     7,     8,     9,     1,     2,     3,
  4,     5,     6,     0,     0,     0,    10,    19,     0,     0,
  30,    31,    32,    33,    30,    31,    32,    33,     0,    20,
  34,    35,    36,    37,    38,    39,     0,     0,     0,    60,
  0,     0,     0,   125,    30,    31,    32,    33,    40,    41,
  42,    43,    44,     0,    30,    31,    32,    33,     0,     0,
  61,     0,     0,   127,    34,    35,    36,    37,    38,    39,
  0,     0,   117,    30,    31,    32,    33,    40,    41,    42,
  43,    44,     0,    34,    35,    36,    37,    38,    39,   126,
  0,   119,    30,    31,    32,    33,    40,    41,    42,    43,
  44,     0,    34,    35,    36,    37,    38,    39,   128,    40,
  41,    42,    43,    44,    45,    46,    47,    48,    49,     0,
  103,     0,     0,     0,     0,   104,    40,    41,    42,    43,
  44,    45,    46,    47,    48,    49,     0,   108,     0,     0,
  0,     0,   109,    40,    41,    42,    43,    44,    40,    41,
  42,    43,    44,     0,   118,     0,     0,     0,     0,   120
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-48)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
  0,     0,    28,    50,     9,    10,    11,    12,     0,     9,
  10,    25,     9,    10,    11,    12,    25,    16,    17,    18,
  19,    20,    27,    23,    16,    17,    18,    25,    27,    28,
  27,    28,     9,    10,    11,    27,    28,    18,    19,    20,
  40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
  97,     0,     9,    10,    11,    12,    56,     6,    27,     0,
  29,    10,     9,    10,    11,    12,    15,    25,    17,    18,
  27,    20,     9,     9,    10,    11,    12,     9,    10,     0,
  27,    30,    31,    32,    33,    34,    35,    36,    37,    38,
  39,    23,    28,    19,    20,    16,    17,    18,    19,    20,
  20,    50,    -1,   103,   104,    -1,    27,    28,    40,    41,
  42,    43,    44,    45,    46,    47,    48,    49,   118,     0,
  120,    27,    28,    -1,    56,     0,     9,    10,    11,    12,
  9,    10,    11,    12,    -1,    16,    17,    18,    19,    20,
  -1,    16,    17,    18,    19,    20,    27,    28,    97,    28,
  -1,   100,    27,    28,   103,   104,    -1,     0,    -1,   108,
  109,    -1,     0,    16,    17,    18,    19,    20,   117,    -1,
  119,   103,   104,    16,    17,    18,    19,    20,    16,    17,
  18,    19,    20,     0,    27,    28,   118,    -1,   120,    27,
  28,    16,    17,    18,    19,    20,     0,     9,    10,    16,
  17,    18,    19,    20,    -1,    -1,     9,    10,    11,    12,
  27,    28,    16,    17,    18,    -1,    20,     3,     4,     5,
  6,     7,     8,    27,    28,    28,    -1,    13,     3,     4,
  5,     6,     7,     8,    17,    18,    19,    20,    13,    25,
  26,    -1,    -1,    29,     3,     4,     5,     6,     7,     8,
  25,    26,    -1,    -1,    13,    14,    15,     3,     4,     5,
  6,     7,     8,    -1,    -1,    -1,    25,    13,    -1,    -1,
  9,    10,    11,    12,     9,    10,    11,    12,    -1,    25,
  19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    28,
  -1,    -1,    -1,    28,     9,    10,    11,    12,    16,    17,
  18,    19,    20,    -1,     9,    10,    11,    12,    -1,    -1,
  28,    -1,    -1,    28,    19,    20,    21,    22,    23,    24,
  -1,    -1,    27,     9,    10,    11,    12,    16,    17,    18,
  19,    20,    -1,    19,    20,    21,    22,    23,    24,    28,
  -1,    27,     9,    10,    11,    12,    16,    17,    18,    19,
  20,    -1,    19,    20,    21,    22,    23,    24,    28,    16,
  17,    18,    19,    20,    16,    17,    18,    19,    20,    -1,
  27,    -1,    -1,    -1,    -1,    27,    16,    17,    18,    19,
  20,    16,    17,    18,    19,    20,    -1,    27,    -1,    -1,
  -1,    -1,    27,    16,    17,    18,    19,    20,    16,    17,
  18,    19,    20,    -1,    27,    -1,    -1,    -1,    -1,    27
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
  0,     3,     4,     5,     6,     7,     8,    13,    14,    15,
  25,    31,    32,    33,    36,    37,    28,    25,    25,    13,
  25,    32,    36,    25,    32,    33,    36,    32,    33,     0,
  9,    10,    11,    12,    19,    20,    21,    22,    23,    24,
  16,    17,    18,    19,    20,    16,    17,    18,    19,    20,
  26,    32,    34,    35,    32,    32,    25,    32,    33,    36,
  28,    28,    32,    32,    32,    32,    32,    32,    32,    32,
  32,    32,    33,    36,    33,    36,    33,    36,    33,    36,
  33,    36,    33,    36,    33,    36,    33,    36,    33,    33,
  29,    32,    34,    27,    28,    27,    28,    27,    29,    28,
  27,    33,    36,    27,    27,    32,    34,    32,    27,    27,
  32,    33,    32,    33,    28,    32,    32,    27,    27,    27,
  27,    32,    33,    32,    33,    28,    28,    28,    28
};

#define yyerrok   (yyerrstatus = 0)
#define yyclearin (yychar = YYEMPTY)
#define YYEMPTY   (-2)
#define YYEOF   0

#define YYACCEPT  goto yyacceptlab
#define YYABORT   goto yyabortlab
#define YYERROR   goto yyerrorlab

/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL    goto yyerrlab
#if defined YYFAIL
/* This is here to suppress warnings from the GCC cpp's
   -Wunused-macros.  Normally we don't worry about that warning, but
   some users do, and we want to make it easy for users to remove
   YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {\
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {\
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;              \
      }               \
  while (YYID (0))

/* Error token number */
#define YYTERROR  1
#define YYERRCODE 256

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)      \
  do {\
      if (yydebug)          \
        YYFPRINTF Args;       \
    } while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)        \
  do {\
      if (yydebug)                  \
        {\
          YYFPRINTF (stderr, "%s ", Title);           \
          yy_symbol_print (stderr,              \
                           Type, Value); \
          YYFPRINTF (stderr, "\n");             \
        }                   \
    } while (YYID (0))

/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print(FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print(yyoutput, yytype, yyvaluep)
FILE *yyoutput;
int yytype;
YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE(yyo);

  if (!yyvaluep)
    return;

# ifdef YYPRINT

  if (yytype < YYNTOKENS)
    YYPRINT(yyoutput, yytoknum[yytype], *yyvaluep);

# else
  YYUSE(yyoutput);
# endif

  switch (yytype)
    {
      default:
        break;
    }
}

/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print(FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print(yyoutput, yytype, yyvaluep)
FILE *yyoutput;
int yytype;
YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF(yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF(yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print(yyoutput, yytype, yyvaluep);
  YYFPRINTF(yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print(yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print(yybottom, yytop)
yytype_int16 *yybottom;
yytype_int16 *yytop;
#endif
{
  YYFPRINTF(stderr, "Stack now");

  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF(stderr, " %d", yybot);
    }

  YYFPRINTF(stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)        \
  do {\
      if (yydebug)              \
        yy_stack_print ((Bottom), (Top));       \
    } while (YYID (0))

/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print(YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print(yyvsp, yyrule)
YYSTYPE *yyvsp;
int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF(stderr, "Reducing stack by rule %d (line %lu):\n",
            yyrule - 1, yylno);

  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF(stderr, "   $%d = ", yyi + 1);
      yy_symbol_print(stderr, yyrhs[yyprhs[yyrule] + yyi],
                      &(yyvsp[(yyi + 1) - (yynrhs)])
                     );
      YYFPRINTF(stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)    \
  do {\
      if (yydebug)        \
        yy_reduce_print (yyvsp, Rule); \
    } while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug = YYDEBUG;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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

#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen(const char *yystr)
#else
static YYSIZE_T
yystrlen(yystr)
const char *yystr;
#endif
{
  YYSIZE_T yylen;

  for (yylen = 0; yystr[yylen]; yylen++)
    continue;

  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy(char *yydest, const char *yysrc)
#else
static char *
yystpcpy(yydest, yysrc)
char *yydest;
const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr(char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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

              /* Fall through.  */
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

do_not_strip_quotes:;
    }

  if (! yyres)
    return yystrlen(yystr);

  return yystpcpy(yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error(YYSIZE_T *yymsg_alloc, char **yymsg,
               yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr(YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum {YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];

      if (!yypact_value_is_default(yyn))
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error(yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }

                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr(YY_NULL, yytname[yyx]);

                if (!(yysize <= yysize1
                      && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;

                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
case N:                               \
  yyformat = S;                       \
  break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen(yyformat);

  if (!(yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;

  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;

      if (!(yysize <= *yymsg_alloc
            && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;

      return 1;
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
          yyp += yytnamerr(yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct(const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct(yymsg, yytype, yyvaluep)
const char *yymsg;
int yytype;
YYSTYPE *yyvaluep;
#endif
{
  YYUSE(yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";

  YY_SYMBOL_PRINT(yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}

/* The lookahead symbol.  */
int yychar;

#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;

/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse(void *YYPARSE_PARAM)
#else
int
yyparse(YYPARSE_PARAM)
void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse(void)
#else
int
yyparse()

#endif
#endif
{
  int yystate;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;

  /* The stacks and their tools:
     `yyss': related to states.
     `yyvs': related to semantic values.

     Refer to the stacks through separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs;
  YYSTYPE *yyvsp;

  YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

  /*------------------------------------------------------------.
  | yynewstate -- Push a new state, which is found in yystate.  |
  `------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow(YY_("memory exhausted"),
                   &yyss1, yysize * sizeof(*yyssp),
                   &yyvs1, yysize * sizeof(*yyvsp),
                   &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else

      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;

      yystacksize *= 2;

      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
            (union yyalloc *) YYSTACK_ALLOC(YYSTACK_BYTES(yystacksize));

        if (! yyptr)
          goto yyexhaustedlab;

        YYSTACK_RELOCATE(yyss_alloc, yyss);
        YYSTACK_RELOCATE(yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE

        if (yyss1 != yyssa)
          YYSTACK_FREE(yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF((stderr, "Stack size increased to %lu\n",
                 (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF((stderr, "Entering state %d\n", yystate));

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

  if (yypact_value_is_default(yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE(yychar);
      YY_SYMBOL_PRINT("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;

  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;

  yyn = yytable[yyn];

  if (yyn <= 0)
    {
      if (yytable_value_is_error(yyn))
        goto yyerrlab;

      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1 - yylen];

  YY_REDUCE_PRINT(yyn);

  switch (yyn)
    {
      case 2:
        /* Line 1778 of yacc.c  */
#line 93 "CEvaluationParser.ypp"
        {
          mBoolean = false;
          mpRootNode = (yyval);
        }
        break;

      case 3:
        /* Line 1778 of yacc.c  */
#line 98 "CEvaluationParser.ypp"
        {
          mBoolean = true;
          mpRootNode = (yyval);
        }
        break;

      case 4:
        /* Line 1778 of yacc.c  */
#line 104 "CEvaluationParser.ypp"
        {
          mpRootNode = (yyvsp[(1) - (1)]);
        }
        break;

      case 5:
        /* Line 1778 of yacc.c  */
#line 108 "CEvaluationParser.ypp"
        {
          mpRootNode = (yyvsp[(1) - (1)]);
        }
        break;

      case 6:
        /* Line 1778 of yacc.c  */
#line 112 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 7:
        /* Line 1778 of yacc.c  */
#line 119 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 8:
        /* Line 1778 of yacc.c  */
#line 126 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 9:
        /* Line 1778 of yacc.c  */
#line 133 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 10:
        /* Line 1778 of yacc.c  */
#line 140 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(2) - (3)]);
          mpRootNode = (yyval);
        }
        break;

      case 11:
        /* Line 1778 of yacc.c  */
#line 145 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(1) - (4)]);
          (yyval)->addChild((yyvsp[(3) - (4)]));
          mpRootNode = (yyval);
        }
        break;

      case 12:
        /* Line 1778 of yacc.c  */
#line 151 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(1) - (6)]);
          (yyval)->addChild((yyvsp[(3) - (6)]));
          (yyval)->addChild((yyvsp[(5) - (6)]));
          mpRootNode = (yyval);
        }
        break;

      case 13:
        /* Line 1778 of yacc.c  */
#line 158 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(1) - (2)]);
          (yyval)->addChild((yyvsp[(2) - (2)]));
          mpRootNode = (yyval);
        }
        break;

      case 14:
        /* Line 1778 of yacc.c  */
#line 164 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(1) - (8)]);
          (yyval)->addChild((yyvsp[(3) - (8)]));
          (yyval)->addChild((yyvsp[(5) - (8)]));
          (yyval)->addChild((yyvsp[(7) - (8)]));
          mpRootNode = (yyval);
        }
        break;

      case 15:
        /* Line 1778 of yacc.c  */
#line 172 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(1) - (8)]);
          (yyval)->addChild((yyvsp[(3) - (8)]));
          (yyval)->addChild((yyvsp[(5) - (8)]));
          (yyval)->addChild((yyvsp[(7) - (8)]));
          mpRootNode = (yyval);
        }
        break;

      case 16:
        /* Line 1778 of yacc.c  */
#line 180 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(1) - (1)]);
          mpRootNode = (yyval);
        }
        break;

      case 17:
        /* Line 1778 of yacc.c  */
#line 186 "CEvaluationParser.ypp"
        {
          mpRootNode = (yyvsp[(1) - (1)]);
        }
        break;

      case 18:
        /* Line 1778 of yacc.c  */
#line 190 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(1) - (8)]);
          (yyval)->addChild((yyvsp[(3) - (8)]));
          (yyval)->addChild((yyvsp[(5) - (8)]));
          (yyval)->addChild((yyvsp[(7) - (8)]));
          mpRootNode = (yyval);
        }
        break;

      case 19:
        /* Line 1778 of yacc.c  */
#line 198 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(1) - (8)]);
          (yyval)->addChild((yyvsp[(3) - (8)]));
          (yyval)->addChild((yyvsp[(5) - (8)]));
          (yyval)->addChild((yyvsp[(7) - (8)]));
          mpRootNode = (yyval);
        }
        break;

      case 20:
        /* Line 1778 of yacc.c  */
#line 206 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 21:
        /* Line 1778 of yacc.c  */
#line 213 "CEvaluationParser.ypp"
        {
          setBooleanRequired((yyvsp[(1) - (3)]), true);
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 22:
        /* Line 1778 of yacc.c  */
#line 221 "CEvaluationParser.ypp"
        {
          setBooleanRequired((yyvsp[(3) - (3)]), true);
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 23:
        /* Line 1778 of yacc.c  */
#line 229 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 24:
        /* Line 1778 of yacc.c  */
#line 236 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 25:
        /* Line 1778 of yacc.c  */
#line 243 "CEvaluationParser.ypp"
        {
          setBooleanRequired((yyvsp[(1) - (3)]), true);
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 26:
        /* Line 1778 of yacc.c  */
#line 251 "CEvaluationParser.ypp"
        {
          setBooleanRequired((yyvsp[(3) - (3)]), true);
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 27:
        /* Line 1778 of yacc.c  */
#line 259 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 28:
        /* Line 1778 of yacc.c  */
#line 266 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 29:
        /* Line 1778 of yacc.c  */
#line 273 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 30:
        /* Line 1778 of yacc.c  */
#line 280 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 31:
        /* Line 1778 of yacc.c  */
#line 287 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 32:
        /* Line 1778 of yacc.c  */
#line 294 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 33:
        /* Line 1778 of yacc.c  */
#line 301 "CEvaluationParser.ypp"
        {
          setBooleanRequired((yyvsp[(1) - (3)]), true);
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 34:
        /* Line 1778 of yacc.c  */
#line 309 "CEvaluationParser.ypp"
        {
          setBooleanRequired((yyvsp[(3) - (3)]), true);
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 35:
        /* Line 1778 of yacc.c  */
#line 317 "CEvaluationParser.ypp"
        {
          setBooleanRequired((yyvsp[(1) - (3)]), true);
          setBooleanRequired((yyvsp[(3) - (3)]), true);
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 36:
        /* Line 1778 of yacc.c  */
#line 326 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 37:
        /* Line 1778 of yacc.c  */
#line 333 "CEvaluationParser.ypp"
        {
          setBooleanRequired((yyvsp[(1) - (3)]), true);
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 38:
        /* Line 1778 of yacc.c  */
#line 341 "CEvaluationParser.ypp"
        {
          setBooleanRequired((yyvsp[(3) - (3)]), true);
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 39:
        /* Line 1778 of yacc.c  */
#line 349 "CEvaluationParser.ypp"
        {
          setBooleanRequired((yyvsp[(1) - (3)]), true);
          setBooleanRequired((yyvsp[(3) - (3)]), true);
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 40:
        /* Line 1778 of yacc.c  */
#line 358 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 41:
        /* Line 1778 of yacc.c  */
#line 365 "CEvaluationParser.ypp"
        {
          setBooleanRequired((yyvsp[(1) - (3)]), true);
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 42:
        /* Line 1778 of yacc.c  */
#line 373 "CEvaluationParser.ypp"
        {
          setBooleanRequired((yyvsp[(3) - (3)]), true);
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 43:
        /* Line 1778 of yacc.c  */
#line 381 "CEvaluationParser.ypp"
        {
          setBooleanRequired((yyvsp[(1) - (3)]), true);
          setBooleanRequired((yyvsp[(3) - (3)]), true);
          (yyval) = (yyvsp[(2) - (3)]);
          (yyval)->addChild((yyvsp[(1) - (3)]));
          (yyval)->addChild((yyvsp[(3) - (3)]));
          mpRootNode = (yyval);
        }
        break;

      case 44:
        /* Line 1778 of yacc.c  */
#line 390 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(2) - (3)]);
          mpRootNode = (yyval);
        }
        break;

      case 45:
        /* Line 1778 of yacc.c  */
#line 395 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(1) - (2)]);
          (yyval)->addChild((yyvsp[(2) - (2)]));
          mpRootNode = (yyval);
        }
        break;

      case 46:
        /* Line 1778 of yacc.c  */
#line 401 "CEvaluationParser.ypp"
        {
          setBooleanRequired((yyvsp[(2) - (2)]), true);
          (yyval) = (yyvsp[(1) - (2)]);
          (yyval)->addChild((yyvsp[(2) - (2)]));
          mpRootNode = (yyval);
        }
        break;

      case 47:
        /* Line 1778 of yacc.c  */
#line 409 "CEvaluationParser.ypp"
        {
          (yyval) = new CEvaluationNodeVector();
          mpNodeList->push_back((yyval));
        }
        break;

      case 48:
        /* Line 1778 of yacc.c  */
#line 414 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(1) - (2)]);
        }
        break;

      case 49:
        /* Line 1778 of yacc.c  */
#line 420 "CEvaluationParser.ypp"
        {
          (yyval) = new CEvaluationNodeVector();
          mpNodeList->push_back((yyval));
          (yyval)->addChild((yyvsp[(2) - (2)]));
        }
        break;

      case 50:
        /* Line 1778 of yacc.c  */
#line 426 "CEvaluationParser.ypp"
        {
          (yyval) = new CEvaluationNodeVector();
          mpNodeList->push_back((yyval));
          (yyval)->addChild((yyvsp[(2) - (2)]));
        }
        break;

      case 51:
        /* Line 1778 of yacc.c  */
#line 432 "CEvaluationParser.ypp"
        {
          (yyval)->addChild((yyvsp[(3) - (3)]));
        }
        break;

      case 52:
        /* Line 1778 of yacc.c  */
#line 436 "CEvaluationParser.ypp"
        {
          (yyval)->addChild((yyvsp[(3) - (3)]));
        }
        break;

      case 53:
        /* Line 1778 of yacc.c  */
#line 441 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(1) - (2)]);
        }
        break;

      case 54:
        /* Line 1778 of yacc.c  */
#line 445 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(1) - (3)]);
          (yyval)->addChild((yyvsp[(2) - (3)]));
        }
        break;

      case 55:
        /* Line 1778 of yacc.c  */
#line 450 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(1) - (3)]);
          (yyval)->addChild((yyvsp[(2) - (3)]));
        }
        break;

      case 56:
        /* Line 1778 of yacc.c  */
#line 456 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(1) - (1)]);
        }
        break;

      case 57:
        /* Line 1778 of yacc.c  */
#line 460 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(1) - (3)]);
          (yyval)->addChild((yyvsp[(2) - (3)]));
        }
        break;

      case 58:
        /* Line 1778 of yacc.c  */
#line 465 "CEvaluationParser.ypp"
        {
          (yyval) = (yyvsp[(1) - (3)]);
          (yyval)->addChild((yyvsp[(2) - (3)]));
        }
        break;

        /* Line 1778 of yacc.c  */
#line 2145 "CEvaluationParser_yacc.cpppp"

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
  YY_SYMBOL_PRINT("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK(yylen);
  yylen = 0;
  YY_STACK_PRINT(yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;

  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE(yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror(YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;

        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE(yymsg);

            yymsg = (char *) YYSTACK_ALLOC(yymsg_alloc);

            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }

        yyerror(yymsgp);

        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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
          yydestruct("Error: discarding",
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
    goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK(yylen);
  yylen = 0;
  YY_STACK_PRINT(yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;  /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];

      if (!yypact_value_is_default(yyn))
        {
          yyn += YYTERROR;

          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];

              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yydestruct("Error: popping",
                 yystos[yystate], yyvsp);
      YYPOPSTACK(1);
      yystate = *yyssp;
      YY_STACK_PRINT(yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Shift the error token.  */
  YY_SYMBOL_PRINT("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;

  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
  /*-------------------------------------------------.
  | yyexhaustedlab -- memory exhaustion comes here.  |
  `-------------------------------------------------*/
yyexhaustedlab:
  yyerror(YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:

  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE(yychar);
      yydestruct("Cleanup: discarding lookahead",
                 yytoken, &yylval);
    }

  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK(yylen);
  YY_STACK_PRINT(yyss, yyssp);

  while (yyssp != yyss)
    {
      yydestruct("Cleanup: popping",
                 yystos[*yyssp], yyvsp);
      YYPOPSTACK(1);
    }

#ifndef yyoverflow

  if (yyss != yyssa)
    YYSTACK_FREE(yyss);

#endif
#if YYERROR_VERBOSE

  if (yymsg != yymsgbuf)
    YYSTACK_FREE(yymsg);

#endif
  /* Make sure YYID is used.  */
  return YYID(yyresult);
}

/* Line 2041 of yacc.c  */
#line 471 "CEvaluationParser.ypp"
