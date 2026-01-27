// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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

/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the variable and function names.  */
#define yyparse yyparse
#define yyerror CEvaluationParsererror
#define yydebug CEvaluationParserdebug
#define yynerrs CEvaluationParsernerrs

#define yylval CEvaluationParserlval
#define yychar CEvaluationParserchar

/* Copy the first part of user declarations.  */

#define YYSTYPE CEvaluationNode *

#ifdef yylval
#  undef yylval
#endif
#define yylval mpNode

#ifdef yyerror
#  undef yyerror
#endif
#define yyerror(__str) \
  if (yychar != YYERRCODE) \
    correctErrorPosition(); \
  CCopasiMessage(CCopasiMessage::ERROR, MCFunction + 1, mPosition)

#include "copasi/copasi.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationLexer.h"

#undef yyparse
#define yyparse CEvaluationParserBase::yyparse

#ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#  else
#    define YY_NULLPTR 0
#  endif
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
#  undef YYERROR_VERBOSE
#  define YYERROR_VERBOSE 1
#else
#  define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "CEvaluationParser_yacc.hpp".  */
#ifndef YY_CEVALUATIONPARSER_CEVALUATIONPARSER_TAB_HPP_INCLUDED
#  define YY_CEVALUATIONPARSER_CEVALUATIONPARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#  ifndef YYDEBUG
#    define YYDEBUG 1
#  endif
#  if YYDEBUG
extern int CEvaluationParserdebug;
#  endif

/* Token type.  */
#  ifndef YYTOKENTYPE
#    define YYTOKENTYPE
enum yytokentype
{
  TOKEN_NUMBER = 258,
  TOKEN_VARIABLE = 259,
  TOKEN_UNIT = 260,
  TOKEN_CALL = 261,
  TOKEN_FUNCTION = 262,
  TOKEN_FUNCTION_1 = 263,
  TOKEN_FUNCTION_2 = 264,
  TOKEN_SIGN = 265,
  TOKEN_OPERATOR_POWER = 266,
  TOKEN_OPERATOR_MULTIPLY = 267,
  TOKEN_OPERATOR_MODULUS = 268,
  TOKEN_OPERATOR_REMAINDER = 269,
  TOKEN_OPERATOR_PLUS = 270,
  TOKEN_LOGICAL_CHOICE = 271,
  TOKEN_LOGICAL_VALUE = 272,
  TOKEN_LOGICAL_NOT = 273,
  TOKEN_LOGICAL_OR = 274,
  TOKEN_LOGICAL_XOR = 275,
  TOKEN_LOGICAL_AND = 276,
  TOKEN_LOGICAL_EQ = 277,
  TOKEN_LOGICAL_NE = 278,
  TOKEN_LOGICAL_GT = 279,
  TOKEN_LOGICAL_GE = 280,
  TOKEN_LOGICAL_LT = 281,
  TOKEN_LOGICAL_LE = 282,
  TOKEN_STRUCTURE_OPEN = 283,
  TOKEN_STRUCTURE_VECTOR_OPEN = 284,
  TOKEN_STRUCTURE_COMMA = 285,
  TOKEN_STRUCTURE_CLOSE = 286,
  TOKEN_STRUCTURE_VECTOR_CLOSE = 287
};
#  endif

/* Value type.  */
#  if !defined YYSTYPE && !defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
#    define YYSTYPE_IS_TRIVIAL  1
#    define YYSTYPE_IS_DECLARED 1
#  endif

extern YYSTYPE CEvaluationParserlval;

#endif /* !YY_CEVALUATIONPARSER_CEVALUATIONPARSER_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#ifdef short
#  undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
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
#  ifdef __SIZE_TYPE__
#    define YYSIZE_T __SIZE_TYPE__
#  elif defined size_t
#    define YYSIZE_T size_t
#  elif !defined YYSIZE_T
#    include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#    define YYSIZE_T size_t
#  else
#    define YYSIZE_T unsigned int
#  endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
#  if defined YYENABLE_NLS && YYENABLE_NLS
#    if ENABLE_NLS
#      include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#      define YY_(Msgid) dgettext("bison-runtime", Msgid)
#    endif
#  endif
#  ifndef YY_
#    define YY_(Msgid) Msgid
#  endif
#endif

#ifndef YY_ATTRIBUTE
#  if (defined __GNUC__ \
       && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__))) \
    || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#    define YY_ATTRIBUTE(Spec) __attribute__(Spec)
#  else
#    define YY_ATTRIBUTE(Spec) /* empty */
#  endif
#endif

#ifndef YY_ATTRIBUTE_PURE
#  define YY_ATTRIBUTE_PURE YY_ATTRIBUTE((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
#  define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE((__unused__))
#endif

#if !defined _Noreturn \
  && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
#  if defined _MSC_VER && 1200 <= _MSC_VER
#    define _Noreturn __declspec(noreturn)
#  else
#    define _Noreturn YY_ATTRIBUTE((__noreturn__))
#  endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if !defined lint || defined __GNUC__
#  define YYUSE(E) ((void) (E))
#else
#  define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma("GCC diagnostic push") \
      _Pragma("GCC diagnostic ignored \"-Wuninitialized\"") \
        _Pragma("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
#  define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma("GCC diagnostic pop")
#else
#  define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
#  define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
#  define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if !defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

#  ifdef YYSTACK_USE_ALLOCA
#    if YYSTACK_USE_ALLOCA
#      ifdef __GNUC__
#        define YYSTACK_ALLOC __builtin_alloca
#      elif defined __BUILTIN_VA_ARG_INCR
#        include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#      elif defined _AIX
#        define YYSTACK_ALLOC __alloca
#      elif defined _MSC_VER
#        include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#        define alloca _alloca
#      else
#        define YYSTACK_ALLOC alloca
#        if !defined _ALLOCA_H && !defined EXIT_SUCCESS
#          include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
/* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#          ifndef EXIT_SUCCESS
#            define EXIT_SUCCESS 0
#          endif
#        endif
#      endif
#    endif
#  endif

#  ifdef YYSTACK_ALLOC
/* Pacify GCC's 'empty if-body' warning.  */
#    define YYSTACK_FREE(Ptr) \
      do \
        {/* empty */ \
          ; \
      } while (0)
#    ifndef YYSTACK_ALLOC_MAXIMUM
/* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#      define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#    endif
#  else
#    define YYSTACK_ALLOC YYMALLOC
#    define YYSTACK_FREE  YYFREE
#    ifndef YYSTACK_ALLOC_MAXIMUM
#      define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#    endif
#    if (defined __cplusplus && !defined EXIT_SUCCESS \
         && !((defined YYMALLOC || defined malloc) \
              && (defined YYFREE || defined free)))
#      include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#      ifndef EXIT_SUCCESS
#        define EXIT_SUCCESS 0
#      endif
#    endif
#    ifndef YYMALLOC
#      define YYMALLOC malloc
#      if !defined malloc && !defined EXIT_SUCCESS
void * malloc(YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#      endif
#    endif
#    ifndef YYFREE
#      define YYFREE free
#      if !defined free && !defined EXIT_SUCCESS
void free(void *); /* INFRINGES ON USER NAME SPACE */
#      endif
#    endif
#  endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */

#if (!defined yyoverflow \
     && (!defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
#  define YYSTACK_GAP_MAXIMUM (sizeof(union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
#  define YYSTACK_BYTES(N) \
    ((N) * (sizeof(yytype_int16) + sizeof(YYSTYPE)) \
     + YYSTACK_GAP_MAXIMUM)

#  define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
#  define YYSTACK_RELOCATE(Stack_alloc, Stack) \
    do \
      {\
        YYSIZE_T yynewbytes; \
        YYCOPY(&yyptr->Stack_alloc, Stack, yysize); \
        Stack = &yyptr->Stack_alloc; \
        yynewbytes = yystacksize * sizeof(*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof(*yyptr); \
    } while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
#  ifndef YYCOPY
#    if defined __GNUC__ && 1 < __GNUC__
#      define YYCOPY(Dst, Src, Count) \
        __builtin_memcpy(Dst, Src, (Count) * sizeof(*(Src)))
#    else
#      define YYCOPY(Dst, Src, Count) \
        do \
          {\
            YYSIZE_T yyi; \
            for (yyi = 0; yyi < (Count); yyi++) \
              (Dst)[yyi] = (Src)[yyi]; \
        } while (0)
#    endif
#  endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL 35
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST 576

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS 33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS 11
/* YYNRULES -- Number of rules.  */
#define YYNRULES 75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES 173

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK 2
#define YYMAXUTOK  287

#define YYTRANSLATE(YYX) \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
  {
    0, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 1, 2, 3, 4,
    5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
  {
    0, 91, 91, 96, 101, 107, 112, 117, 125, 135,
    140, 146, 153, 160, 167, 174, 181, 188, 193, 197,
    203, 210, 216, 225, 235, 245, 255, 266, 278, 283,
    291, 301, 311, 321, 332, 343, 350, 358, 365, 373,
    381, 388, 396, 403, 411, 419, 426, 433, 440, 447,
    454, 461, 468, 473, 479, 487, 491, 496, 502, 507,
    513, 518, 524, 530, 536, 540, 545, 549, 554, 559,
    564, 570, 574, 579, 584, 589};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char * const yytname[] =
  {
    "$end", "error", "$undefined", "TOKEN_NUMBER", "TOKEN_VARIABLE",
    "TOKEN_UNIT", "TOKEN_CALL", "TOKEN_FUNCTION", "TOKEN_FUNCTION_1",
    "TOKEN_FUNCTION_2", "TOKEN_SIGN", "TOKEN_OPERATOR_POWER",
    "TOKEN_OPERATOR_MULTIPLY", "TOKEN_OPERATOR_MODULUS",
    "TOKEN_OPERATOR_REMAINDER", "TOKEN_OPERATOR_PLUS",
    "TOKEN_LOGICAL_CHOICE", "TOKEN_LOGICAL_VALUE", "TOKEN_LOGICAL_NOT",
    "TOKEN_LOGICAL_OR", "TOKEN_LOGICAL_XOR", "TOKEN_LOGICAL_AND",
    "TOKEN_LOGICAL_EQ", "TOKEN_LOGICAL_NE", "TOKEN_LOGICAL_GT",
    "TOKEN_LOGICAL_GE", "TOKEN_LOGICAL_LT", "TOKEN_LOGICAL_LE",
    "TOKEN_STRUCTURE_OPEN", "TOKEN_STRUCTURE_VECTOR_OPEN",
    "TOKEN_STRUCTURE_COMMA", "TOKEN_STRUCTURE_CLOSE",
    "TOKEN_STRUCTURE_VECTOR_CLOSE", "$accept", "result", "d_or_b", "exp",
    "bool", "function", "fcont", "vector", "vstart", "call", "ccont", YY_NULLPTR};
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
  {
    0, 256, 257, 258, 259, 260, 261, 262, 263, 264,
    265, 266, 267, 268, 269, 270, 271, 272, 273, 274,
    275, 276, 277, 278, 279, 280, 281, 282, 283, 284,
    285, 286, 287};
#endif

#define YYPACT_NINF -52

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-52)))

#define YYTABLE_NINF -55

#define yytable_value_is_error(Yytable_value) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
  {
    257, -52, -52, -28, -10, -8, -4, 284, -2, -52,
    257, 257, 57, 5, 461, 176, -52, 284, -52, 227,
    -52, 211, 284, 284, 24, 284, -52, 50, 257, 122,
    461, 7, 150, 312, 104, -52, 257, 257, 284, 273,
    284, 284, 284, 284, 284, 284, 284, 284, 284, 257,
    257, 257, 257, 257, 1, 200, -21, 291, 481, 181,
    -24, -52, 52, 318, 61, 257, 339, 28, 517, -52,
    -52, 466, 58, 483, -52, 50, -52, 50, 117, 229,
    212, 559, 559, 559, 559, 559, 559, 288, 12, 7,
    171, 58, 130, -52, -52, -52, -52, 559, -52, -52,
    -52, -52, -52, -52, -52, -52, -52, 243, -52, -52,
    -52, -52, 284, 124, 529, 257, 257, 559, -52, 360,
    284, 284, 133, 407, 534, 144, 427, 546, -52, 54,
    432, 60, 452, 257, 284, 257, 257, 284, 257, 284,
    284, 47, 333, 276, 56, 375, 66, 494, 82, 354,
    499, 72, 381, 87, 512, 75, 386, 80, 396, -52,
    -52, -52, -52, -52, -52, -52, -52, -52, -52, -52,
    -52, -52, -52};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
  {
    0, 9, 6, 71, 0, 0, 0, 0, 0, 28,
    0, 0, 0, 10, 2, 3, 18, 0, 5, 0,
    66, 0, 0, 0, 0, 0, 10, 21, 0, 10,
    0, 53, 10, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 10, 0, 0, 0,
    0, 55, 0, 0, 0, 0, 0, 10, 0, 17,
    52, 36, 39, 41, 44, 16, 14, 15, 12, 13,
    11, 35, 40, 46, 45, 48, 47, 49, 50, 51,
    10, 37, 10, 42, 59, 57, 60, 62, 63, 72,
    67, 73, 68, 74, 69, 75, 70, 0, 61, 58,
    56, 19, 0, 10, 0, 0, 0, 64, 65, 0,
    0, 0, 10, 0, 0, 10, 0, 0, 20, 10,
    0, 10, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 10, 0, 0, 10, 0, 10, 0, 10, 0,
    0, 10, 0, 10, 0, 10, 0, 10, 0, 8,
    26, 33, 27, 25, 34, 32, 7, 23, 30, 24,
    22, 31, 29};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
  {
    -52, -52, 49, 0, 43, -52, -52, -51, -52, -52,
    -52};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
  {
    -1, 12, 26, 30, 15, 16, 17, 59, 60, 18,
    19};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
  {
    14, 36, 37, 20, 98, -4, 107, 27, 108, 99,
    100, 33, 38, 39, 40, 41, 42, 54, 21, 57,
    22, 62, 63, 64, 23, 66, 28, 36, 37, 52,
    53, 94, 95, 51, 52, 53, 71, 73, 75, 77,
    78, 79, 80, 81, 82, 83, 84, 85, 86, 13,
    36, 37, 65, 31, 34, 97, 118, 35, 115, 29,
    32, 38, 58, 38, 39, 40, 41, 42, 56, 36,
    37, 68, 38, 39, 40, 41, 42, 67, 159, 72,
    74, 53, 109, 110, 139, 32, 32, 162, 36, 37,
    140, 112, 87, 88, 89, 91, 93, 164, 32, 32,
    32, 90, 92, 169, 36, 37, 159, 117, 114, 36,
    37, 166, 119, 166, 113, 123, 126, 0, 171, 0,
    130, 132, -54, 49, 50, 51, 52, 53, 38, 39,
    -43, 41, 0, 142, 145, 70, 149, 152, 0, 156,
    158, -54, -54, -54, 36, 37, 36, 37, 0, -43,
    -43, -43, -54, -54, 120, 36, 37, 0, 124, 127,
    -43, -43, 0, 133, 122, 125, 36, 37, 0, 129,
    131, -38, 36, 37, 136, 0, 143, 0, 147, 150,
    0, 154, 141, 144, 146, 148, 151, 153, 155, 157,
    -38, -38, -38, 0, 37, 49, 50, 51, 52, 53,
    0, -38, -38, 1, 2, 0, 3, 4, 5, 6,
    7, 105, 106, 0, 1, 2, 24, 3, 4, 5,
    6, 7, 0, 38, 39, 40, 41, 24, 25, 55,
    1, 2, 96, 3, 4, 5, 6, 7, 0, 25,
    38, 39, 61, 8, 9, 10, 1, 2, 0, 3,
    4, 5, 6, 7, 0, 11, 55, 0, 0, 24,
    1, 2, 0, 3, 4, 5, 6, 7, 0, 0,
    0, 25, 55, 8, 9, 10, 1, 2, 76, 3,
    4, 5, 6, 7, 0, 11, 0, 1, 2, 24,
    3, 4, 5, 6, 7, 49, 50, 51, 52, 53,
    24, 25, 38, 39, 40, 41, 42, 161, 50, 51,
    52, 53, 25, 43, 44, 45, 46, 47, 48, 0,
    0, 101, 102, 38, 39, 40, 41, 42, 0, 38,
    39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
    0, 0, 0, 69, 38, 39, 40, 41, 42, 111,
    38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
    48, 0, 0, 0, 160, 38, 39, 40, 41, 42,
    69, 38, 39, 40, 41, 42, 43, 44, 45, 46,
    47, 48, 0, 0, 0, 167, 38, 39, 40, 41,
    42, 128, 38, 39, 40, 41, 42, 38, 39, 40,
    41, 42, 0, 0, 0, 0, 163, 38, 39, 40,
    41, 42, 170, 0, 0, 0, 0, 160, 38, 39,
    40, 41, 42, 0, 0, 0, 0, 167, 0, 43,
    44, 45, 46, 47, 48, 0, 0, 134, 38, 39,
    40, 41, 42, 38, 39, 40, 41, 42, 0, 43,
    44, 45, 46, 47, 48, 0, 0, 137, 0, 0,
    0, 0, 134, 38, 39, 40, 41, 42, 0, 0,
    0, 0, 38, 39, 40, 41, 42, 38, 39, 40,
    41, 42, 137, 43, 44, 45, 46, 47, 48, 44,
    45, 46, 47, 48, 38, 39, 40, 41, 42, 0,
    49, 50, 51, 52, 53, 0, 0, 45, 46, 47,
    48, 103, 104, 49, 50, 51, 52, 53, 49, 50,
    51, 52, 53, 0, 0, 165, 0, 0, 0, 0,
    168, 49, 50, 51, 52, 53, 49, 50, 51, 52,
    53, 0, 0, 172, 0, 0, 0, 116, 49, 50,
    51, 52, 53, 49, 50, 51, 52, 53, 0, 121,
    0, 0, 0, 0, 135, 49, 50, 51, 52, 53,
    38, 39, 40, 41, 42, 0, 138};

static const yytype_int16 yycheck[] =
  {
    0, 22, 23, 31, 55, 0, 30, 7, 32, 30,
    31, 11, 11, 12, 13, 14, 15, 17, 28, 19,
    28, 21, 22, 23, 28, 25, 28, 22, 23, 22,
    23, 30, 31, 21, 22, 23, 36, 37, 38, 39,
    40, 41, 42, 43, 44, 45, 46, 47, 48, 0,
    22, 23, 28, 10, 11, 55, 107, 0, 30, 10,
    11, 11, 19, 11, 12, 13, 14, 15, 19, 22,
    23, 28, 11, 12, 13, 14, 15, 28, 31, 36,
    37, 23, 30, 31, 30, 36, 37, 31, 22, 23,
    30, 30, 49, 50, 51, 52, 53, 31, 49, 50,
    51, 52, 53, 31, 22, 23, 31, 107, 65, 22,
    23, 31, 112, 31, 65, 115, 116, -1, 31, -1,
    120, 121, 0, 19, 20, 21, 22, 23, 11, 12,
    0, 14, -1, 133, 134, 31, 136, 137, -1, 139,
    140, 19, 20, 21, 22, 23, 22, 23, -1, 19,
    20, 21, 30, 31, 30, 22, 23, -1, 115, 116,
    30, 31, -1, 30, 115, 116, 22, 23, -1, 120,
    121, 0, 22, 23, 30, -1, 133, -1, 135, 136,
    -1, 138, 133, 134, 135, 136, 137, 138, 139, 140,
    19, 20, 21, -1, 23, 19, 20, 21, 22, 23,
    -1, 30, 31, 3, 4, -1, 6, 7, 8, 9,
    10, 30, 31, -1, 3, 4, 16, 6, 7, 8,
    9, 10, -1, 11, 12, 13, 14, 16, 28, 29,
    3, 4, 32, 6, 7, 8, 9, 10, -1, 28,
    11, 12, 31, 16, 17, 18, 3, 4, -1, 6,
    7, 8, 9, 10, -1, 28, 29, -1, -1, 16,
    3, 4, -1, 6, 7, 8, 9, 10, -1, -1,
    -1, 28, 29, 16, 17, 18, 3, 4, 5, 6,
    7, 8, 9, 10, -1, 28, -1, 3, 4, 16,
    6, 7, 8, 9, 10, 19, 20, 21, 22, 23,
    16, 28, 11, 12, 13, 14, 15, 31, 20, 21,
    22, 23, 28, 22, 23, 24, 25, 26, 27, -1,
    -1, 30, 31, 11, 12, 13, 14, 15, -1, 11,
    12, 13, 14, 15, 22, 23, 24, 25, 26, 27,
    -1, -1, -1, 31, 11, 12, 13, 14, 15, 31,
    11, 12, 13, 14, 15, 22, 23, 24, 25, 26,
    27, -1, -1, -1, 31, 11, 12, 13, 14, 15,
    31, 11, 12, 13, 14, 15, 22, 23, 24, 25,
    26, 27, -1, -1, -1, 31, 11, 12, 13, 14,
    15, 31, 11, 12, 13, 14, 15, 11, 12, 13,
    14, 15, -1, -1, -1, -1, 31, 11, 12, 13,
    14, 15, 31, -1, -1, -1, -1, 31, 11, 12,
    13, 14, 15, -1, -1, -1, -1, 31, -1, 22,
    23, 24, 25, 26, 27, -1, -1, 30, 11, 12,
    13, 14, 15, 11, 12, 13, 14, 15, -1, 22,
    23, 24, 25, 26, 27, -1, -1, 30, -1, -1,
    -1, -1, 30, 11, 12, 13, 14, 15, -1, -1,
    -1, -1, 11, 12, 13, 14, 15, 11, 12, 13,
    14, 15, 30, 22, 23, 24, 25, 26, 27, 23,
    24, 25, 26, 27, 11, 12, 13, 14, 15, -1,
    19, 20, 21, 22, 23, -1, -1, 24, 25, 26,
    27, 30, 31, 19, 20, 21, 22, 23, 19, 20,
    21, 22, 23, -1, -1, 31, -1, -1, -1, -1,
    31, 19, 20, 21, 22, 23, 19, 20, 21, 22,
    23, -1, -1, 31, -1, -1, -1, 30, 19, 20,
    21, 22, 23, 19, 20, 21, 22, 23, -1, 30,
    -1, -1, -1, -1, 30, 19, 20, 21, 22, 23,
    11, 12, 13, 14, 15, -1, 30};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
  {
    0, 3, 4, 6, 7, 8, 9, 10, 16, 17,
    18, 28, 34, 35, 36, 37, 38, 39, 42, 43,
    31, 28, 28, 28, 16, 28, 35, 36, 28, 35,
    36, 37, 35, 36, 37, 0, 22, 23, 11, 12,
    13, 14, 15, 22, 23, 24, 25, 26, 27, 19,
    20, 21, 22, 23, 36, 29, 35, 36, 37, 40,
    41, 31, 36, 36, 36, 28, 36, 35, 37, 31,
    31, 36, 37, 36, 37, 36, 5, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 37, 37, 37,
    35, 37, 35, 37, 30, 31, 32, 36, 40, 30,
    31, 30, 31, 30, 31, 30, 31, 30, 32, 30,
    31, 31, 30, 35, 37, 30, 30, 36, 40, 36,
    30, 30, 35, 36, 37, 35, 36, 37, 31, 35,
    36, 35, 36, 30, 30, 30, 30, 30, 30, 30,
    30, 35, 36, 37, 35, 36, 35, 37, 35, 36,
    37, 35, 36, 35, 37, 35, 36, 35, 36, 31,
    31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
    31, 31, 31};

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
  {
    0, 33, 34, 34, 34, 35, 35, 35, 35, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 37, 37,
    37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
    37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
    37, 37, 37, 37, 37, 38, 38, 38, 39, 39,
    40, 40, 41, 41, 41, 41, 42, 42, 42, 42,
    42, 43, 43, 43, 43, 43};

/* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
  {
    0, 2, 1, 1, 1, 1, 1, 8, 8, 1,
    1, 3, 3, 3, 3, 3, 3, 3, 1, 4,
    6, 2, 8, 8, 8, 8, 8, 8, 1, 8,
    8, 8, 8, 8, 8, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 2, 2, 3, 4, 3, 4, 3,
    2, 2, 2, 2, 3, 3, 2, 3, 3, 3,
    3, 1, 3, 3, 3, 3};

#define yyerrok   (yyerrstatus = 0)
#define yyclearin (yychar = YYEMPTY)
#define YYEMPTY   (-2)
#define YYEOF     0

#define YYACCEPT goto yyacceptlab
#define YYABORT  goto yyabortlab
#define YYERROR  goto yyerrorlab

#define YYRECOVERING() (!!yyerrstatus)

#define YYBACKUP(Token, Value) \
  do \
    if (yychar == YYEMPTY) \
      {\
        yychar = (Token); \
        yylval = (Value); \
        YYPOPSTACK(yylen); \
        yystate = *yyssp; \
        goto yybackup; \
      } \
    else \
      {\
        yyerror(YY_("syntax error: cannot back up")); \
        YYERROR; \
      } \
  while (0)

/* Error token number */
#define YYTERROR  1
#define YYERRCODE 256

/* Enable debugging if requested.  */
#if YYDEBUG

#  ifndef YYFPRINTF
#    include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#    define YYFPRINTF fprintf
#  endif

#  define YYDPRINTF(Args) \
    do \
      {\
        if (yydebug) \
          YYFPRINTF Args; \
    } while (0)

/* This macro is provided for backward compatibility. */
#  ifndef YY_LOCATION_PRINT
#    define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif

#  define YY_SYMBOL_PRINT(Title, Type, Value, Location) \
    do \
      {\
        if (yydebug) \
          {\
            YYFPRINTF(stderr, "%s ", Title); \
            yy_symbol_print(stderr, \
                            Type, Value); \
            YYFPRINTF(stderr, "\n"); \
          } \
    } while (0)

/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print(FILE * yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE * yyo = yyoutput;
  YYUSE(yyo);
  if (!yyvaluep)
    return;
#  ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT(yyoutput, yytoknum[yytype], *yyvaluep);
#  endif
  YYUSE(yytype);
}

/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print(FILE * yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF(yyoutput, "%s %s (",
            yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print(yyoutput, yytype, yyvaluep);
  YYFPRINTF(yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print(yytype_int16 * yybottom, yytype_int16 * yytop)
{
  YYFPRINTF(stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF(stderr, " %d", yybot);
    }
  YYFPRINTF(stderr, "\n");
}

#  define YY_STACK_PRINT(Bottom, Top) \
    do \
      {\
        if (yydebug) \
          yy_stack_print((Bottom), (Top)); \
    } while (0)

/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print(yytype_int16 * yyssp, YYSTYPE * yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF(stderr, "Reducing stack by rule %d (line %lu):\n",
            yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF(stderr, "   $%d = ", yyi + 1);
      yy_symbol_print(stderr,
                      yystos[yyssp[yyi + 1 - yynrhs]],
                      &(yyvsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF(stderr, "\n");
    }
}

#  define YY_REDUCE_PRINT(Rule) \
    do \
      {\
        if (yydebug) \
          yy_reduce_print(yyssp, yyvsp, Rule); \
    } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug = YYDEBUG;
#else /* !YYDEBUG */
#  define YYDPRINTF(Args)
#  define YY_SYMBOL_PRINT(Title, Type, Value, Location)
#  define YY_STACK_PRINT(Bottom, Top)
#  define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
#  define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
#  define YYMAXDEPTH 10000
#endif

#if YYERROR_VERBOSE

#  ifndef yystrlen
#    if defined __GLIBC__ && defined _STRING_H
#      define yystrlen strlen
#    else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen(const char * yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#    endif
#  endif

#  ifndef yystpcpy
#    if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#      define yystpcpy stpcpy
#    else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy(char * yydest, const char * yysrc)
{
  char * yyd = yydest;
  const char * yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#    endif
#  endif

#  ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr(char * yyres, const char * yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const * yyp = yystr;

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

  if (!yyres)
    return yystrlen(yystr);

  return yystpcpy(yyres, yystr) - yyres;
}
#  endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error(YYSIZE_T * yymsg_alloc, char ** yymsg, yytype_int16 * yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr(YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum
  {
    YYERROR_VERBOSE_ARGS_MAXIMUM = 5
  };
  /* Internationalized format string. */
  const char * yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const * yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr(YY_NULLPTR, yytname[yyx]);
                  if (!(yysize <= yysize1
                        && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
#  define YYCASE_(N, S) \
  case N: \
    yyformat = S; \
    break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#  undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen(yyformat);
    if (!(yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
    char * yyp = *yymsg;
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

static void
yydestruct(const char * yymsg, int yytype, YYSTYPE * yyvaluep)
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

int yyparse(void)
{
  int yystate;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;

  /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 * yyss;
  yytype_int16 * yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE * yyvs;
  YYSTYPE * yyvsp;

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
  char * yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N) (yyvsp -= (N), yyssp -= (N))

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
        YYSTYPE * yyvs1 = yyvs;
        yytype_int16 * yyss1 = yyss;

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
#  ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
#  else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 * yyss1 = yyss;
        union yyalloc * yyptr =
          (union yyalloc *) YYSTACK_ALLOC(YYSTACK_BYTES(yystacksize));
        if (!yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE(yyss_alloc, yyss);
        YYSTACK_RELOCATE(yyvs_alloc, yyvs);
#    undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE(yyss1);
      }
#  endif
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

      {
        mValueType = CEvaluationNode::ValueType::Number;
        mpRootNode = (yyval);
      }

      break;

    case 3:

      {
        mValueType = CEvaluationNode::ValueType::Boolean;
        mpRootNode = (yyval);
      }

      break;

    case 4:

      {
        mValueType = CEvaluationNode::ValueType::Unknown;
        mpRootNode = (yyval);
      }

      break;

    case 5:

      {
        (yyval) = (yyvsp[0]);
        mpRootNode = (yyval);
      }

      break;

    case 6:

      {
        (yyval) = (yyvsp[0]);
        mpRootNode = (yyval);
      }

      break;

    case 7:

      {
        (yyval) = (yyvsp[-7]);
        (yyval)->addChild((yyvsp[-5]));
        (yyval)->addChild((yyvsp[-3]));
        (yyval)->addChild((yyvsp[-1]));
        mpRootNode = (yyval);
      }

      break;

    case 8:

      {
        (yyvsp[-7])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval) = (yyvsp[-7]);
        (yyval)->addChild((yyvsp[-5]));
        (yyval)->addChild((yyvsp[-3]));
        (yyval)->addChild((yyvsp[-1]));
        mpRootNode = (yyval);
      }

      break;

    case 9:

      {
        (yyval) = (yyvsp[0]);
        mpRootNode = (yyval);
      }

      break;

    case 10:

      {
        (yyvsp[0])->setValueType(CEvaluationNode::ValueType::Number);
        (yyval) = (yyvsp[0]);
        mpRootNode = (yyval);
      }

      break;

    case 11:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 12:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 13:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 14:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 15:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 16:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 17:

      {
        (yyval) = (yyvsp[-1]);
        mpRootNode = (yyval);
      }

      break;

    case 18:

      {
        (yyval) = (yyvsp[0]);
      }

      break;

    case 19:

      {
        (yyval) = (yyvsp[-3]);
        (yyval)->addChild((yyvsp[-1]));
        mpRootNode = (yyval);
      }

      break;

    case 20:

      {
        (yyval) = (yyvsp[-5]);
        (yyval)->addChild((yyvsp[-3]));
        (yyval)->addChild((yyvsp[-1]));
        mpRootNode = (yyval);
      }

      break;

    case 21:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 22:

      {
        (yyvsp[-7])->setValueType(CEvaluationNode::ValueType::Number);
        (yyval) = (yyvsp[-7]);
        (yyval)->addChild((yyvsp[-5]));
        (yyval)->addChild((yyvsp[-3]));
        (yyval)->addChild((yyvsp[-1]));
        mpRootNode = (yyval);
      }

      break;

    case 23:

      {
        (yyvsp[-7])->setValueType(CEvaluationNode::ValueType::Number);
        (yyval) = (yyvsp[-7]);
        (yyval)->addChild((yyvsp[-5]));
        (yyvsp[-3])->setValueType(CEvaluationNode::ValueType::Number);
        (yyval)->addChild((yyvsp[-3]));
        (yyval)->addChild((yyvsp[-1]));
        mpRootNode = (yyval);
      }

      break;

    case 24:

      {
        (yyvsp[-7])->setValueType(CEvaluationNode::ValueType::Number);
        (yyval) = (yyvsp[-7]);
        (yyval)->addChild((yyvsp[-5]));
        (yyval)->addChild((yyvsp[-3]));
        (yyvsp[-1])->setValueType(CEvaluationNode::ValueType::Number);
        (yyval)->addChild((yyvsp[-1]));
        mpRootNode = (yyval);
      }

      break;

    case 25:

      {
        (yyvsp[-7])->setValueType(CEvaluationNode::ValueType::Number);
        (yyval) = (yyvsp[-7]);
        (yyvsp[-5])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval)->addChild((yyvsp[-5]));
        (yyval)->addChild((yyvsp[-3]));
        (yyval)->addChild((yyvsp[-1]));
        mpRootNode = (yyval);
      }

      break;

    case 26:

      {
        (yyvsp[-7])->setValueType(CEvaluationNode::ValueType::Number);
        (yyval) = (yyvsp[-7]);
        (yyvsp[-5])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval)->addChild((yyvsp[-5]));
        (yyvsp[-3])->setValueType(CEvaluationNode::ValueType::Number);
        (yyval)->addChild((yyvsp[-3]));
        (yyval)->addChild((yyvsp[-1]));
        mpRootNode = (yyval);
      }

      break;

    case 27:

      {
        (yyvsp[-7])->setValueType(CEvaluationNode::ValueType::Number);
        (yyval) = (yyvsp[-7]);
        (yyvsp[-5])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval)->addChild((yyvsp[-5]));
        (yyval)->addChild((yyvsp[-3]));
        (yyvsp[-1])->setValueType(CEvaluationNode::ValueType::Number);
        (yyval)->addChild((yyvsp[-1]));
        mpRootNode = (yyval);
      }

      break;

    case 28:

      {
        (yyval) = (yyvsp[0]);
        mpRootNode = (yyval);
      }

      break;

    case 29:

      {
        (yyval) = (yyvsp[-7]);
        (yyval)->addChild((yyvsp[-5]));
        (yyval)->addChild((yyvsp[-3]));
        (yyval)->addChild((yyvsp[-1]));
        mpRootNode = (yyval);
      }

      break;

    case 30:

      {
        (yyvsp[-7])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval) = (yyvsp[-7]);
        (yyval)->addChild((yyvsp[-5]));
        (yyvsp[-3])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval)->addChild((yyvsp[-3]));
        (yyval)->addChild((yyvsp[-1]));
        mpRootNode = (yyval);
      }

      break;

    case 31:

      {
        (yyvsp[-7])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval) = (yyvsp[-7]);
        (yyval)->addChild((yyvsp[-5]));
        (yyval)->addChild((yyvsp[-3]));
        (yyvsp[-1])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval)->addChild((yyvsp[-1]));
        mpRootNode = (yyval);
      }

      break;

    case 32:

      {
        (yyvsp[-7])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval) = (yyvsp[-7]);
        (yyvsp[-5])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval)->addChild((yyvsp[-5]));
        (yyval)->addChild((yyvsp[-3]));
        (yyval)->addChild((yyvsp[-1]));
        mpRootNode = (yyval);
      }

      break;

    case 33:

      {
        (yyvsp[-7])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval) = (yyvsp[-7]);
        (yyvsp[-5])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval)->addChild((yyvsp[-5]));
        (yyvsp[-3])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval)->addChild((yyvsp[-3]));
        (yyval)->addChild((yyvsp[-1]));
        mpRootNode = (yyval);
      }

      break;

    case 34:

      {
        (yyvsp[-7])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval) = (yyvsp[-7]);
        (yyvsp[-5])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval)->addChild((yyvsp[-5]));
        (yyval)->addChild((yyvsp[-3]));
        (yyvsp[-1])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval)->addChild((yyvsp[-1]));
        mpRootNode = (yyval);
      }

      break;

    case 35:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 36:

      {
        (yyval) = (yyvsp[-1]);
        (yyvsp[-2])->setValueType(CEvaluationNode::ValueType::Number);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 37:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 38:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyvsp[0])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 39:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyvsp[-2])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 40:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 41:

      {
        (yyval) = (yyvsp[-1]);
        (yyvsp[-2])->setValueType(CEvaluationNode::ValueType::Number);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 42:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 43:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyvsp[0])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 44:

      {
        (yyval) = (yyvsp[-1]);
        (yyvsp[-2])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 45:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 46:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 47:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 48:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 49:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 50:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 51:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[-2]));
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 52:

      {
        (yyval) = (yyvsp[-1]);
        mpRootNode = (yyval);
      }

      break;

    case 53:

      {
        (yyval) = (yyvsp[-1]);
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 54:

      {
        (yyval) = (yyvsp[-1]);
        (yyvsp[0])->setValueType(CEvaluationNode::ValueType::Boolean);
        (yyval)->addChild((yyvsp[0]));
        mpRootNode = (yyval);
      }

      break;

    case 55:

      {
        (yyval) = (yyvsp[-2]);
      }

      break;

    case 56:

      {
        (yyval) = (yyvsp[-3]);
        (yyval)->addChild((yyvsp[-1]));
      }

      break;

    case 57:

      {
        (yyval) = (yyvsp[-2]);
        (yyval)->addChild((yyvsp[-1]));
      }

      break;

    case 58:

      {
        (yyval) = (yyvsp[-3]);
        (yyval)->addChild((yyvsp[-1]));
      }

      break;

    case 59:

      {
        (yyval) = (yyvsp[-2]);
        (yyval)->addChild((yyvsp[-1]));
      }

      break;

    case 60:

      {
        (yyval) = new CEvaluationNodeVector();
        mpNodeList->push_back((yyval));
      }

      break;

    case 61:

      {
        (yyval) = (yyvsp[-1]);
      }

      break;

    case 62:

      {
        (yyval) = new CEvaluationNodeVector();
        mpNodeList->push_back((yyval));
        (yyval)->addChild((yyvsp[0]));
      }

      break;

    case 63:

      {
        (yyval) = new CEvaluationNodeVector();
        mpNodeList->push_back((yyval));
        (yyval)->addChild((yyvsp[0]));
      }

      break;

    case 64:

      {
        (yyval)->addChild((yyvsp[0]));
      }

      break;

    case 65:

      {
        (yyval)->addChild((yyvsp[0]));
      }

      break;

    case 66:

      {
        (yyval) = (yyvsp[-1]);
      }

      break;

    case 67:

      {
        (yyval) = (yyvsp[-2]);
        (yyval)->addChild((yyvsp[-1]));
      }

      break;

    case 68:

      {
        (yyval) = (yyvsp[-2]);
        (yyval)->addChild((yyvsp[-1]));
      }

      break;

    case 69:

      {
        (yyval) = (yyvsp[-2]);
        (yyval)->addChild((yyvsp[-1]));
      }

      break;

    case 70:

      {
        (yyval) = (yyvsp[-2]);
        (yyval)->addChild((yyvsp[-1]));
      }

      break;

    case 71:

      {
        (yyval) = (yyvsp[0]);
      }

      break;

    case 72:

      {
        (yyval) = (yyvsp[-2]);
        (yyval)->addChild((yyvsp[-1]));
      }

      break;

    case 73:

      {
        (yyval) = (yyvsp[-2]);
        (yyval)->addChild((yyvsp[-1]));
      }

      break;

    case 74:

      {
        (yyval) = (yyvsp[-2]);
        (yyval)->addChild((yyvsp[-1]));
      }

      break;

    case 75:

      {
        (yyval) = (yyvsp[-2]);
        (yyval)->addChild((yyvsp[-1]));
      }

      break;

    default:
      break;
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
#if !YYERROR_VERBOSE
      yyerror(YY_("syntax error"));
#else
#  define YYSYNTAX_ERROR yysyntax_error(&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const * yymsgp = YY_("syntax error");
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
#  undef YYSYNTAX_ERROR
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
  yyerrstatus = 3; /* Each real token shifted decrements this.  */

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
