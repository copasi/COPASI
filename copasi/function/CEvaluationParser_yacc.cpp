// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

/* A Bison parser, made by GNU Bison 3.5.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5"

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

#line 101 "CEvaluationParser_yacc.cpp"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_CEVALUATIONPARSER_CEVALUATIONPARSER_TAB_HPP_INCLUDED
# define YY_CEVALUATIONPARSER_CEVALUATIONPARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int CEvaluationParserdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
enum yytokentype
{
  TOKEN_NUMBER = 258,
  TOKEN_VARIABLE = 259,
  TOKEN_UNIT = 260,
  TOKEN_CALL = 261,
  TOKEN_FUNCTION = 262,
  TOKEN_FUNCTION_2 = 263,
  TOKEN_SIGN = 264,
  TOKEN_OPERATOR_POWER = 265,
  TOKEN_OPERATOR_MULTIPLY = 266,
  TOKEN_OPERATOR_MODULUS = 267,
  TOKEN_OPERATOR_REMAINDER = 268,
  TOKEN_OPERATOR_PLUS = 269,
  TOKEN_LOGICAL_CHOICE = 270,
  TOKEN_LOGICAL_VALUE = 271,
  TOKEN_LOGICAL_NOT = 272,
  TOKEN_LOGICAL_OR = 273,
  TOKEN_LOGICAL_XOR = 274,
  TOKEN_LOGICAL_AND = 275,
  TOKEN_LOGICAL_EQ = 276,
  TOKEN_LOGICAL_NE = 277,
  TOKEN_LOGICAL_GT = 278,
  TOKEN_LOGICAL_GE = 279,
  TOKEN_LOGICAL_LT = 280,
  TOKEN_LOGICAL_LE = 281,
  TOKEN_STRUCTURE_OPEN = 282,
  TOKEN_STRUCTURE_VECTOR_OPEN = 283,
  TOKEN_STRUCTURE_COMMA = 284,
  TOKEN_STRUCTURE_CLOSE = 285,
  TOKEN_STRUCTURE_VECTOR_CLOSE = 286
};
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE CEvaluationParserlval;

#endif /* !YY_CEVALUATIONPARSER_CEVALUATIONPARSER_TAB_HPP_INCLUDED  */

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
  _Pragma ("GCC diagnostic push")                                     \
  _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
  _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#  define YYSTACK_FREE(Ptr) do {/* empty */; } while (0)
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
void *malloc(YYSIZE_T);  /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
    {\
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
    {\
      YYPTRDIFF_T yyi;                      \
      for (yyi = 0; yyi < (Count); yyi++)   \
        (Dst)[yyi] = (Src)[yyi];            \
    }                                       \
  while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  31
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   527

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  9
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  162

#define YYUNDEFTOK  2
#define YYMAXUTOK   286

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
  25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
  0,    87,    87,    92,    97,   103,   108,   113,   121,   131,
  136,   142,   149,   156,   163,   170,   177,   184,   189,   195,
  202,   208,   217,   227,   237,   247,   258,   270,   275,   283,
  293,   303,   313,   324,   335,   342,   350,   357,   365,   373,
  380,   388,   395,   403,   411,   418,   425,   432,   439,   446,
  453,   460,   465,   471,   479,   484,   490,   496,   502,   506,
  511,   515,   520,   525,   530,   536,   540,   545,   550,   555
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_NUMBER", "TOKEN_VARIABLE",
  "TOKEN_UNIT", "TOKEN_CALL", "TOKEN_FUNCTION", "TOKEN_FUNCTION_2",
  "TOKEN_SIGN", "TOKEN_OPERATOR_POWER", "TOKEN_OPERATOR_MULTIPLY",
  "TOKEN_OPERATOR_MODULUS", "TOKEN_OPERATOR_REMAINDER",
  "TOKEN_OPERATOR_PLUS", "TOKEN_LOGICAL_CHOICE", "TOKEN_LOGICAL_VALUE",
  "TOKEN_LOGICAL_NOT", "TOKEN_LOGICAL_OR", "TOKEN_LOGICAL_XOR",
  "TOKEN_LOGICAL_AND", "TOKEN_LOGICAL_EQ", "TOKEN_LOGICAL_NE",
  "TOKEN_LOGICAL_GT", "TOKEN_LOGICAL_GE", "TOKEN_LOGICAL_LT",
  "TOKEN_LOGICAL_LE", "TOKEN_STRUCTURE_OPEN",
  "TOKEN_STRUCTURE_VECTOR_OPEN", "TOKEN_STRUCTURE_COMMA",
  "TOKEN_STRUCTURE_CLOSE", "TOKEN_STRUCTURE_VECTOR_CLOSE", "$accept",
  "result", "d_or_b", "exp", "bool", "vector", "vstart", "call", "cstart", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
  0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
  265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
  275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
  285,   286
};
# endif

#define YYPACT_NINF (-50)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-54)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
  208,   -50,   -50,   -27,     3,    24,   236,    62,   -50,   208,
  208,    53,     2,   402,     7,   -50,   179,   -50,   236,   236,
  89,   236,   -50,    63,   208,    46,   402,    41,    58,   275,
  345,   -50,   208,   208,   236,   223,   236,   236,   236,   236,
  236,   236,   236,   236,   236,   208,   208,   208,   208,   208,
  130,   122,   254,   422,    70,    -9,     1,    73,   208,   101,
  98,   471,   -50,   -50,   407,    99,   424,   -50,    63,   -50,
  63,    -6,   136,    47,   513,   513,   513,   513,   513,   513,
  335,    75,    41,    52,    99,    88,   -50,   -50,   513,   -50,
  -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   194,   -50,
  -50,   236,   170,   476,   208,   208,   513,   -50,   260,   236,
  236,   212,   348,   488,   226,   368,   493,   -50,    95,   373,
  103,   393,   208,   236,   208,   208,   236,   208,   236,   236,
  -13,   296,   435,   100,   281,    26,   440,   154,   317,   453,
  105,   302,   183,   458,   110,   323,   123,   338,   -50,   -50,
  -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,
  -50,   -50
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
  0,     9,     6,    65,     0,     0,     0,     0,    27,     0,
  0,     0,    10,     2,     3,     5,     0,    60,     0,     0,
  0,     0,    10,    20,     0,    10,     0,    52,    10,     0,
  0,     1,     0,     0,     0,     0,     0,     0,     0,     0,
  0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
  0,    10,     0,     0,     0,     0,     0,     0,     0,     0,
  10,     0,    17,    51,    35,    38,    40,    43,    16,    14,
  15,    12,    13,    11,    34,    39,    45,    44,    47,    46,
  48,    49,    50,    10,    36,    10,    41,    54,    56,    57,
  66,    61,    67,    62,    68,    63,    69,    64,     0,    55,
  18,     0,    10,     0,     0,     0,    58,    59,     0,     0,
  0,    10,     0,     0,    10,     0,     0,    19,    10,     0,
  10,     0,     0,     0,     0,     0,     0,     0,     0,     0,
  10,     0,     0,    10,     0,    10,     0,    10,     0,     0,
  10,     0,    10,     0,    10,     0,    10,     0,     8,    25,
  32,    26,    24,    33,    31,     7,    22,    29,    23,    21,
  30,    28
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
  -50,   -50,    45,     0,   132,   -49,   -50,   -50,   -50
  };

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
  -1,    11,    22,    26,    14,    54,    55,    15,    16
  };

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
  13,    89,    -4,    17,    34,    35,    23,    37,    32,    33,
  29,    34,    35,    36,    37,    38,    52,   148,    56,    57,
  98,    59,    99,    32,    33,    45,    46,    47,    48,    49,
  18,   100,    64,    66,    68,    70,    71,    72,    73,    74,
  75,    76,    77,    78,    79,    12,   -53,    32,    33,   107,
  88,    19,   -37,    31,    25,    28,   153,    34,    35,    36,
  37,    51,    48,    49,   -53,   -53,   -53,    32,    33,    60,
  -37,   -37,   -37,    34,    33,   -53,   -53,    28,    28,    32,
  33,   -37,   -37,    34,    35,    36,    37,    38,   -42,    24,
  28,    28,    28,    83,    85,    47,    48,    49,   106,    96,
  97,   108,   101,   102,   112,   115,   -42,   -42,   -42,   119,
  121,    34,    35,    36,    37,    38,    58,   -42,   -42,    32,
  33,    49,   131,   134,   128,   138,   141,   104,   145,   147,
  151,    62,   129,     1,     2,   158,     3,     4,     5,     6,
  148,    27,    30,    32,    33,    20,    34,    35,    53,   111,
  114,    90,    91,   155,   118,   120,    61,    21,    50,     0,
  0,    87,     0,     0,    65,    67,     0,   130,   133,   135,
  137,   140,   142,   144,   146,    32,    33,    80,    81,    82,
  84,    86,     1,     2,   155,     3,     4,     5,     6,     0,
  103,    32,    33,     0,     7,     8,     9,     1,     2,   109,
  3,     4,     5,     6,    32,    33,    10,    50,     0,    20,
  0,     1,     2,   160,     3,     4,     5,     6,     0,     0,
  0,    21,    50,     7,     8,     9,     1,     2,    69,     3,
  4,     5,     6,    32,    33,    10,   113,   116,    20,     1,
  2,   122,     3,     4,     5,     6,     0,    32,    33,     0,
  21,    20,     0,     0,   132,   125,   136,   139,     0,   143,
  0,     0,     0,    21,    34,    35,    36,    37,    38,     0,
  34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
  44,     0,     0,    92,    93,    34,    35,    36,    37,    38,
  117,    34,    35,    36,    37,    38,    39,    40,    41,    42,
  43,    44,     0,     0,     0,    62,    34,    35,    36,    37,
  38,   152,    34,    35,    36,    37,    38,    39,    40,    41,
  42,    43,    44,     0,     0,     0,   149,    34,    35,    36,
  37,    38,   159,    34,    35,    36,    37,    38,    39,    40,
  41,    42,    43,    44,     0,     0,     0,   156,    34,    35,
  36,    37,    38,   149,    46,    47,    48,    49,    34,    35,
  36,    37,    38,    45,    46,    47,    48,    49,   156,    39,
  40,    41,    42,    43,    44,    63,     0,   123,    34,    35,
  36,    37,    38,    34,    35,    36,    37,    38,     0,    39,
  40,    41,    42,    43,    44,     0,     0,   126,     0,     0,
  0,     0,   123,    34,    35,    36,    37,    38,     0,     0,
  0,     0,    34,    35,    36,    37,    38,    34,    35,    36,
  37,    38,   126,    39,    40,    41,    42,    43,    44,    40,
  41,    42,    43,    44,    34,    35,    36,    37,    38,     0,
  45,    46,    47,    48,    49,     0,     0,    41,    42,    43,
  44,    94,    95,    45,    46,    47,    48,    49,    45,    46,
  47,    48,    49,     0,     0,   150,     0,     0,     0,     0,
  154,    45,    46,    47,    48,    49,    45,    46,    47,    48,
  49,     0,     0,   157,     0,     0,     0,     0,   161,    45,
  46,    47,    48,    49,    45,    46,    47,    48,    49,     0,
  105,     0,     0,     0,     0,   110,    45,    46,    47,    48,
  49,    45,    46,    47,    48,    49,     0,   124,     0,     0,
  0,     0,   127,    34,    35,    36,    37,    38
};

static const yytype_int16 yycheck[] =
{
  0,    50,     0,    30,    10,    11,     6,    13,    21,    22,
  10,    10,    11,    12,    13,    14,    16,    30,    18,    19,
  29,    21,    31,    21,    22,    18,    19,    20,    21,    22,
  27,    30,    32,    33,    34,    35,    36,    37,    38,    39,
  40,    41,    42,    43,    44,     0,     0,    21,    22,    98,
  50,    27,     0,     0,     9,    10,    30,    10,    11,    12,
  13,    16,    21,    22,    18,    19,    20,    21,    22,    24,
  18,    19,    20,    10,    22,    29,    30,    32,    33,    21,
  22,    29,    30,    10,    11,    12,    13,    14,     0,    27,
  45,    46,    47,    48,    49,    20,    21,    22,    98,    29,
  30,   101,    29,    58,   104,   105,    18,    19,    20,   109,
  110,    10,    11,    12,    13,    14,    27,    29,    30,    21,
  22,    22,   122,   123,    29,   125,   126,    29,   128,   129,
  30,    30,    29,     3,     4,    30,     6,     7,     8,     9,
  30,     9,    10,    21,    22,    15,    10,    11,    16,   104,
  105,    29,    30,    30,   109,   110,    24,    27,    28,    -1,
  -1,    31,    -1,    -1,    32,    33,    -1,   122,   123,   124,
  125,   126,   127,   128,   129,    21,    22,    45,    46,    47,
  48,    49,     3,     4,    30,     6,     7,     8,     9,    -1,
  58,    21,    22,    -1,    15,    16,    17,     3,     4,    29,
  6,     7,     8,     9,    21,    22,    27,    28,    -1,    15,
  -1,     3,     4,    30,     6,     7,     8,     9,    -1,    -1,
  -1,    27,    28,    15,    16,    17,     3,     4,     5,     6,
  7,     8,     9,    21,    22,    27,   104,   105,    15,     3,
  4,    29,     6,     7,     8,     9,    -1,    21,    22,    -1,
  27,    15,    -1,    -1,   122,    29,   124,   125,    -1,   127,
  -1,    -1,    -1,    27,    10,    11,    12,    13,    14,    -1,
  10,    11,    12,    13,    14,    21,    22,    23,    24,    25,
  26,    -1,    -1,    29,    30,    10,    11,    12,    13,    14,
  30,    10,    11,    12,    13,    14,    21,    22,    23,    24,
  25,    26,    -1,    -1,    -1,    30,    10,    11,    12,    13,
  14,    30,    10,    11,    12,    13,    14,    21,    22,    23,
  24,    25,    26,    -1,    -1,    -1,    30,    10,    11,    12,
  13,    14,    30,    10,    11,    12,    13,    14,    21,    22,
  23,    24,    25,    26,    -1,    -1,    -1,    30,    10,    11,
  12,    13,    14,    30,    19,    20,    21,    22,    10,    11,
  12,    13,    14,    18,    19,    20,    21,    22,    30,    21,
  22,    23,    24,    25,    26,    30,    -1,    29,    10,    11,
  12,    13,    14,    10,    11,    12,    13,    14,    -1,    21,
  22,    23,    24,    25,    26,    -1,    -1,    29,    -1,    -1,
  -1,    -1,    29,    10,    11,    12,    13,    14,    -1,    -1,
  -1,    -1,    10,    11,    12,    13,    14,    10,    11,    12,
  13,    14,    29,    21,    22,    23,    24,    25,    26,    22,
  23,    24,    25,    26,    10,    11,    12,    13,    14,    -1,
  18,    19,    20,    21,    22,    -1,    -1,    23,    24,    25,
  26,    29,    30,    18,    19,    20,    21,    22,    18,    19,
  20,    21,    22,    -1,    -1,    30,    -1,    -1,    -1,    -1,
  30,    18,    19,    20,    21,    22,    18,    19,    20,    21,
  22,    -1,    -1,    30,    -1,    -1,    -1,    -1,    30,    18,
  19,    20,    21,    22,    18,    19,    20,    21,    22,    -1,
  29,    -1,    -1,    -1,    -1,    29,    18,    19,    20,    21,
  22,    18,    19,    20,    21,    22,    -1,    29,    -1,    -1,
  -1,    -1,    29,    10,    11,    12,    13,    14
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
  0,     3,     4,     6,     7,     8,     9,    15,    16,    17,
  27,    33,    34,    35,    36,    39,    40,    30,    27,    27,
  15,    27,    34,    35,    27,    34,    35,    36,    34,    35,
  36,     0,    21,    22,    10,    11,    12,    13,    14,    21,
  22,    23,    24,    25,    26,    18,    19,    20,    21,    22,
  28,    34,    35,    36,    37,    38,    35,    35,    27,    35,
  34,    36,    30,    30,    35,    36,    35,    36,    35,     5,
  35,    35,    35,    35,    35,    35,    35,    35,    35,    35,
  36,    36,    36,    34,    36,    34,    36,    31,    35,    37,
  29,    30,    29,    30,    29,    30,    29,    30,    29,    31,
  30,    29,    34,    36,    29,    29,    35,    37,    35,    29,
  29,    34,    35,    36,    34,    35,    36,    30,    34,    35,
  34,    35,    29,    29,    29,    29,    29,    29,    29,    29,
  34,    35,    36,    34,    35,    34,    36,    34,    35,    36,
  34,    35,    34,    36,    34,    35,    34,    35,    30,    30,
  30,    30,    30,    30,    30,    30,    30,    30,    30,    30,
  30,    30
};

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
  0,    32,    33,    33,    33,    34,    34,    34,    34,    35,
  35,    35,    35,    35,    35,    35,    35,    35,    35,    35,
  35,    35,    35,    35,    35,    35,    35,    36,    36,    36,
  36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
  36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
  36,    36,    36,    36,    37,    37,    38,    38,    38,    38,
  39,    39,    39,    39,    39,    40,    40,    40,    40,    40
};

/* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
  0,     2,     1,     1,     1,     1,     1,     8,     8,     1,
  1,     3,     3,     3,     3,     3,     3,     3,     4,     6,
  2,     8,     8,     8,     8,     8,     8,     1,     8,     8,
  8,     8,     8,     8,     3,     3,     3,     3,     3,     3,
  3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
  3,     3,     2,     2,     2,     2,     2,     2,     3,     3,
  2,     3,     3,     3,     3,     1,     3,     3,     3,     3
};

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
  do {\
      if (yydebug)                                  \
        YYFPRINTF Args;                             \
    } while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
  do {\
      if (yydebug)                                                            \
        {\
          YYFPRINTF (stderr, "%s ", Title);                                   \
          yy_symbol_print (stderr,                                            \
                           Type, Value); \
          YYFPRINTF (stderr, "\n");                                           \
        }                                                                     \
    } while (0)

/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print(FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE(yyoutput);

  if (!yyvaluep)
    return;

# ifdef YYPRINT

  if (yytype < YYNTOKENS)
    YYPRINT(yyo, yytoknum[yytype], *yyvaluep);

# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE(yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print(FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF(yyo, "%s %s (",
            yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print(yyo, yytype, yyvaluep);
  YYFPRINTF(yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print(yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF(stderr, "Stack now");

  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF(stderr, " %d", yybot);
    }

  YYFPRINTF(stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
  do {\
      if (yydebug)                                                  \
        yy_stack_print ((Bottom), (Top));                           \
    } while (0)

/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print(yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF(stderr, "Reducing stack by rule %d (line %d):\n",
            yyrule - 1, yylno);

  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF(stderr, "   $%d = ", yyi + 1);
      yy_symbol_print(stderr,
                      yystos[yyssp[yyi + 1 - yynrhs]],
                      &yyvsp[(yyi + 1) - (yynrhs)]
                     );
      YYFPRINTF(stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
  do {\
      if (yydebug)                          \
        yy_reduce_print (yyssp, yyvsp, Rule); \
    } while (0)

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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen(const char *yystr)
{
  YYPTRDIFF_T yylen;

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
static char *
yystpcpy(char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr(char *yyres, const char *yystr)
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

do_not_strip_quotes:;
    }

  if (yyres)
    return yystpcpy(yyres, yystr) - yyres;
  else
    return yystrlen(yystr);
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
yysyntax_error(YYPTRDIFF_T *yymsg_alloc, char **yymsg,
               yy_state_t *yyssp, int yytoken)
{
  enum {YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr(YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr(YY_NULLPTR, yytname[yyx]);

                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
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
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen(yyformat) - 2 * yycount) + 1;

    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct(const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE(yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";

  YY_SYMBOL_PRINT(yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE(yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;

/*----------.
| yyparse.  |
`----------*/

int
yyparse(void)
{
  yy_state_fast_t yystate;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;

  /* The stacks and their tools:
     'yyss': related to states.
     'yyvs': related to semantic values.

     Refer to the stacks through separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yy_state_t yyssa[YYINITDEPTH];
  yy_state_t *yyss;
  yy_state_t *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs;
  YYSTYPE *yyvsp;

  YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
  YYDPRINTF((stderr, "Entering state %d\n", yystate));
  YY_ASSERT(0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST(yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;

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
        yyoverflow(YY_("memory exhausted"),
                   &yyss1, yysize * YYSIZEOF(*yyssp),
                   &yyvs1, yysize * YYSIZEOF(*yyvsp),
                   &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */

      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;

      yystacksize *= 2;

      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST(union yyalloc *,
                  YYSTACK_ALLOC(YY_CAST(YYSIZE_T, YYSTACK_BYTES(yystacksize))));

        if (! yyptr)
          goto yyexhaustedlab;

        YYSTACK_RELOCATE(yyss_alloc, yyss);
        YYSTACK_RELOCATE(yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE

        if (yyss1 != yyssa)
          YYSTACK_FREE(yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF((stderr, "Stack size increased to %ld\n",
                 YY_CAST(long, yystacksize)));
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

  if (yypact_value_is_default(yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF((stderr, "Reading a token: "));
      yychar = yylex();
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
  yyval = yyvsp[1 - yylen];

  YY_REDUCE_PRINT(yyn);

  switch (yyn)
    {
      case 2:
#line 88 "CEvaluationParser.ypp"
        {
          mValueType = CEvaluationNode::ValueType::Number;
          mpRootNode = yyval;
        }

#line 1531 "CEvaluationParser_yacc.cpp"
        break;

      case 3:
#line 93 "CEvaluationParser.ypp"
        {
          mValueType = CEvaluationNode::ValueType::Boolean;
          mpRootNode = yyval;
        }

#line 1540 "CEvaluationParser_yacc.cpp"
        break;

      case 4:
#line 98 "CEvaluationParser.ypp"
        {
          mValueType = CEvaluationNode::ValueType::Unknown;
          mpRootNode = yyval;
        }

#line 1549 "CEvaluationParser_yacc.cpp"
        break;

      case 5:
#line 104 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[0];
          mpRootNode = yyval;
        }

#line 1558 "CEvaluationParser_yacc.cpp"
        break;

      case 6:
#line 109 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[0];
          mpRootNode = yyval;
        }

#line 1567 "CEvaluationParser_yacc.cpp"
        break;

      case 7:
#line 114 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-7];
          yyval->addChild(yyvsp[-5]);
          yyval->addChild(yyvsp[-3]);
          yyval->addChild(yyvsp[-1]);
          mpRootNode = yyval;
        }

#line 1579 "CEvaluationParser_yacc.cpp"
        break;

      case 8:
#line 122 "CEvaluationParser.ypp"
        {
          yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Boolean);
          yyval = yyvsp[-7];
          yyval->addChild(yyvsp[-5]);
          yyval->addChild(yyvsp[-3]);
          yyval->addChild(yyvsp[-1]);
          mpRootNode = yyval;
        }

#line 1592 "CEvaluationParser_yacc.cpp"
        break;

      case 9:
#line 132 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[0];
          mpRootNode = yyval;
        }

#line 1601 "CEvaluationParser_yacc.cpp"
        break;

      case 10:
#line 137 "CEvaluationParser.ypp"
        {
          yyvsp[0]->setValueType(CEvaluationNode::ValueType::Number);
          yyval = yyvsp[0];
          mpRootNode = yyval;
        }

#line 1611 "CEvaluationParser_yacc.cpp"
        break;

      case 11:
#line 143 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 1622 "CEvaluationParser_yacc.cpp"
        break;

      case 12:
#line 150 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 1633 "CEvaluationParser_yacc.cpp"
        break;

      case 13:
#line 157 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 1644 "CEvaluationParser_yacc.cpp"
        break;

      case 14:
#line 164 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 1655 "CEvaluationParser_yacc.cpp"
        break;

      case 15:
#line 171 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 1666 "CEvaluationParser_yacc.cpp"
        break;

      case 16:
#line 178 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 1677 "CEvaluationParser_yacc.cpp"
        break;

      case 17:
#line 185 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          mpRootNode = yyval;
        }

#line 1686 "CEvaluationParser_yacc.cpp"
        break;

      case 18:
#line 190 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-3];
          yyval->addChild(yyvsp[-1]);
          mpRootNode = yyval;
        }

#line 1696 "CEvaluationParser_yacc.cpp"
        break;

      case 19:
#line 196 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-5];
          yyval->addChild(yyvsp[-3]);
          yyval->addChild(yyvsp[-1]);
          mpRootNode = yyval;
        }

#line 1707 "CEvaluationParser_yacc.cpp"
        break;

      case 20:
#line 203 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 1717 "CEvaluationParser_yacc.cpp"
        break;

      case 21:
#line 209 "CEvaluationParser.ypp"
        {
          yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Number);
          yyval = yyvsp[-7];
          yyval->addChild(yyvsp[-5]);
          yyval->addChild(yyvsp[-3]);
          yyval->addChild(yyvsp[-1]);
          mpRootNode = yyval;
        }

#line 1730 "CEvaluationParser_yacc.cpp"
        break;

      case 22:
#line 218 "CEvaluationParser.ypp"
        {
          yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Number);
          yyval = yyvsp[-7];
          yyval->addChild(yyvsp[-5]);
          yyvsp[-3]->setValueType(CEvaluationNode::ValueType::Number);
          yyval->addChild(yyvsp[-3]);
          yyval->addChild(yyvsp[-1]);
          mpRootNode = yyval;
        }

#line 1744 "CEvaluationParser_yacc.cpp"
        break;

      case 23:
#line 228 "CEvaluationParser.ypp"
        {
          yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Number);
          yyval = yyvsp[-7];
          yyval->addChild(yyvsp[-5]);
          yyval->addChild(yyvsp[-3]);
          yyvsp[-1]->setValueType(CEvaluationNode::ValueType::Number);
          yyval->addChild(yyvsp[-1]);
          mpRootNode = yyval;
        }

#line 1758 "CEvaluationParser_yacc.cpp"
        break;

      case 24:
#line 238 "CEvaluationParser.ypp"
        {
          yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Number);
          yyval = yyvsp[-7];
          yyvsp[-5]->setValueType(CEvaluationNode::ValueType::Boolean);
          yyval->addChild(yyvsp[-5]);
          yyval->addChild(yyvsp[-3]);
          yyval->addChild(yyvsp[-1]);
          mpRootNode = yyval;
        }

#line 1772 "CEvaluationParser_yacc.cpp"
        break;

      case 25:
#line 248 "CEvaluationParser.ypp"
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

#line 1787 "CEvaluationParser_yacc.cpp"
        break;

      case 26:
#line 259 "CEvaluationParser.ypp"
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

#line 1802 "CEvaluationParser_yacc.cpp"
        break;

      case 27:
#line 271 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[0];
          mpRootNode = yyval;
        }

#line 1811 "CEvaluationParser_yacc.cpp"
        break;

      case 28:
#line 276 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-7];
          yyval->addChild(yyvsp[-5]);
          yyval->addChild(yyvsp[-3]);
          yyval->addChild(yyvsp[-1]);
          mpRootNode = yyval;
        }

#line 1823 "CEvaluationParser_yacc.cpp"
        break;

      case 29:
#line 284 "CEvaluationParser.ypp"
        {
          yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Boolean);
          yyval = yyvsp[-7];
          yyval->addChild(yyvsp[-5]);
          yyvsp[-3]->setValueType(CEvaluationNode::ValueType::Boolean);
          yyval->addChild(yyvsp[-3]);
          yyval->addChild(yyvsp[-1]);
          mpRootNode = yyval;
        }

#line 1837 "CEvaluationParser_yacc.cpp"
        break;

      case 30:
#line 294 "CEvaluationParser.ypp"
        {
          yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Boolean);
          yyval = yyvsp[-7];
          yyval->addChild(yyvsp[-5]);
          yyval->addChild(yyvsp[-3]);
          yyvsp[-1]->setValueType(CEvaluationNode::ValueType::Boolean);
          yyval->addChild(yyvsp[-1]);
          mpRootNode = yyval;
        }

#line 1851 "CEvaluationParser_yacc.cpp"
        break;

      case 31:
#line 304 "CEvaluationParser.ypp"
        {
          yyvsp[-7]->setValueType(CEvaluationNode::ValueType::Boolean);
          yyval = yyvsp[-7];
          yyvsp[-5]->setValueType(CEvaluationNode::ValueType::Boolean);
          yyval->addChild(yyvsp[-5]);
          yyval->addChild(yyvsp[-3]);
          yyval->addChild(yyvsp[-1]);
          mpRootNode = yyval;
        }

#line 1865 "CEvaluationParser_yacc.cpp"
        break;

      case 32:
#line 314 "CEvaluationParser.ypp"
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

#line 1880 "CEvaluationParser_yacc.cpp"
        break;

      case 33:
#line 325 "CEvaluationParser.ypp"
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

#line 1895 "CEvaluationParser_yacc.cpp"
        break;

      case 34:
#line 336 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 1906 "CEvaluationParser_yacc.cpp"
        break;

      case 35:
#line 343 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyvsp[-2]->setValueType(CEvaluationNode::ValueType::Number);
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 1918 "CEvaluationParser_yacc.cpp"
        break;

      case 36:
#line 351 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 1929 "CEvaluationParser_yacc.cpp"
        break;

      case 37:
#line 358 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyvsp[0]->setValueType(CEvaluationNode::ValueType::Boolean);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 1941 "CEvaluationParser_yacc.cpp"
        break;

      case 38:
#line 366 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyvsp[-2]->setValueType(CEvaluationNode::ValueType::Boolean);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 1953 "CEvaluationParser_yacc.cpp"
        break;

      case 39:
#line 374 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 1964 "CEvaluationParser_yacc.cpp"
        break;

      case 40:
#line 381 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyvsp[-2]->setValueType(CEvaluationNode::ValueType::Number);
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 1976 "CEvaluationParser_yacc.cpp"
        break;

      case 41:
#line 389 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 1987 "CEvaluationParser_yacc.cpp"
        break;

      case 42:
#line 396 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyvsp[0]->setValueType(CEvaluationNode::ValueType::Boolean);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 1999 "CEvaluationParser_yacc.cpp"
        break;

      case 43:
#line 404 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyvsp[-2]->setValueType(CEvaluationNode::ValueType::Boolean);
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 2011 "CEvaluationParser_yacc.cpp"
        break;

      case 44:
#line 412 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 2022 "CEvaluationParser_yacc.cpp"
        break;

      case 45:
#line 419 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 2033 "CEvaluationParser_yacc.cpp"
        break;

      case 46:
#line 426 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 2044 "CEvaluationParser_yacc.cpp"
        break;

      case 47:
#line 433 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 2055 "CEvaluationParser_yacc.cpp"
        break;

      case 48:
#line 440 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 2066 "CEvaluationParser_yacc.cpp"
        break;

      case 49:
#line 447 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 2077 "CEvaluationParser_yacc.cpp"
        break;

      case 50:
#line 454 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[-2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 2088 "CEvaluationParser_yacc.cpp"
        break;

      case 51:
#line 461 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          mpRootNode = yyval;
        }

#line 2097 "CEvaluationParser_yacc.cpp"
        break;

      case 52:
#line 466 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 2107 "CEvaluationParser_yacc.cpp"
        break;

      case 53:
#line 472 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
          yyvsp[0]->setValueType(CEvaluationNode::ValueType::Boolean);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }

#line 2118 "CEvaluationParser_yacc.cpp"
        break;

      case 54:
#line 480 "CEvaluationParser.ypp"
        {
          yyval = new CEvaluationNodeVector();
          mpNodeList->push_back(yyval);
        }

#line 2127 "CEvaluationParser_yacc.cpp"
        break;

      case 55:
#line 485 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
        }

#line 2135 "CEvaluationParser_yacc.cpp"
        break;

      case 56:
#line 491 "CEvaluationParser.ypp"
        {
          yyval = new CEvaluationNodeVector();
          mpNodeList->push_back(yyval);
          yyval->addChild(yyvsp[0]);
        }

#line 2145 "CEvaluationParser_yacc.cpp"
        break;

      case 57:
#line 497 "CEvaluationParser.ypp"
        {
          yyval = new CEvaluationNodeVector();
          mpNodeList->push_back(yyval);
          yyval->addChild(yyvsp[0]);
        }

#line 2155 "CEvaluationParser_yacc.cpp"
        break;

      case 58:
#line 503 "CEvaluationParser.ypp"
        {
          yyval->addChild(yyvsp[0]);
        }

#line 2163 "CEvaluationParser_yacc.cpp"
        break;

      case 59:
#line 507 "CEvaluationParser.ypp"
        {
          yyval->addChild(yyvsp[0]);
        }

#line 2171 "CEvaluationParser_yacc.cpp"
        break;

      case 60:
#line 512 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-1];
        }

#line 2179 "CEvaluationParser_yacc.cpp"
        break;

      case 61:
#line 516 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-2];
          yyval->addChild(yyvsp[-1]);
        }

#line 2188 "CEvaluationParser_yacc.cpp"
        break;

      case 62:
#line 521 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-2];
          yyval->addChild(yyvsp[-1]);
        }

#line 2197 "CEvaluationParser_yacc.cpp"
        break;

      case 63:
#line 526 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-2];
          yyval->addChild(yyvsp[-1]);
        }

#line 2206 "CEvaluationParser_yacc.cpp"
        break;

      case 64:
#line 531 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-2];
          yyval->addChild(yyvsp[-1]);
        }

#line 2215 "CEvaluationParser_yacc.cpp"
        break;

      case 65:
#line 537 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[0];
        }

#line 2223 "CEvaluationParser_yacc.cpp"
        break;

      case 66:
#line 541 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-2];
          yyval->addChild(yyvsp[-1]);
        }

#line 2232 "CEvaluationParser_yacc.cpp"
        break;

      case 67:
#line 546 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-2];
          yyval->addChild(yyvsp[-1]);
        }

#line 2241 "CEvaluationParser_yacc.cpp"
        break;

      case 68:
#line 551 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-2];
          yyval->addChild(yyvsp[-1]);
        }

#line 2250 "CEvaluationParser_yacc.cpp"
        break;

      case 69:
#line 556 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[-2];
          yyval->addChild(yyvsp[-1]);
        }

#line 2259 "CEvaluationParser_yacc.cpp"
        break;

#line 2263 "CEvaluationParser_yacc.cpp"

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

            yymsg = YY_CAST(char *, YYSTACK_ALLOC(YY_CAST(YYSIZE_T, yymsg_alloc)));

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

  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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

  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
yyreturn:

  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE(yychar);
      yydestruct("Cleanup: discarding lookahead",
                 yytoken, &yylval);
    }

  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 562 "CEvaluationParser.ypp"
