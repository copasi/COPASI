// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEqParser_yacc.cpp,v $
//   $Revision: 1.10.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/04/21 13:18:33 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/* A Bison parser, made by GNU Bison 2.0.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse yyparse
#define yyerror CChemEqParsererror
#define yylval  CChemEqParserlval
#define yychar  CChemEqParserchar
#define yydebug CChemEqParserdebug
#define yynerrs CChemEqParsernerrs

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
/* Put the tokens into the symbol table, so that GDB and other debuggers
   know about them.  */
enum yytokentype
{
  TOKEN_NUMBER = 258,
  TOKEN_MULTIPLY = 259,
  TOKEN_PLUS = 260,
  TOKEN_NAME = 261,
  TOKEN_BEGIN_PRODUCTS = 262,
  TOKEN_BEGIN_MODIFIERS = 263,
  TOKEN_BEGIN_COMPARTMENT = 264,
  TOKEN_END_COMPARTMENT = 265
};
#endif
#define TOKEN_NUMBER 258
#define TOKEN_MULTIPLY 259
#define TOKEN_PLUS 260
#define TOKEN_NAME 261
#define TOKEN_BEGIN_PRODUCTS 262
#define TOKEN_BEGIN_MODIFIERS 263
#define TOKEN_BEGIN_COMPARTMENT 264
#define TOKEN_END_COMPARTMENT 265

/* Copy the first part of user declarations.  */
#line 4 "CChemEqParser.ypp"

#define YYSTYPE CChemEqParserBase::Data *

#ifdef yylval
# undef yylval
#endif
#define yylval mpData

#ifdef yyerror
# undef yyerror
#endif
#define yyerror(__str) \
  if (yychar != YYERRCODE) correctErrorPosition(); \
  CCopasiMessage(CCopasiMessage::ERROR, MCFunction + 1, mPosition)

#include "copasi.h"
#include "CChemEqParser.h"

#include "utilities/CCopasiMessage.h"
#include "utilities/utility.h"

#undef yyparse
#define yyparse CChemEqParserBase::yyparse

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

/* Copy the second part of user declarations.  */

/* Line 213 of yacc.c.  */
#line 141 "CChemEqParser_yacc.cpp"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
/* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do {/* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */

#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
   || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
  ((N) * (sizeof (short int) + sizeof (YYSTYPE))     \
   + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
  __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)    \
  do          \
    {\
      register YYSIZE_T yyi;    \
      for (yyi = 0; yyi < (Count); yyi++) \
        (To)[yyi] = (From)[yyi];    \
    }         \
  while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)          \
  do                  \
    {\
      YYSIZE_T yynewbytes;            \
      YYCOPY (&yyptr->Stack, Stack, yysize);        \
      Stack = &yyptr->Stack;            \
      yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
      yyptr += yynewbytes / sizeof (*yyptr);        \
    }                 \
  while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
typedef signed char yysigned_char;
#else
typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   27

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  11
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  8
/* YYNRULES -- Number of rules. */
#define YYNRULES  19
/* YYNRULES -- Number of states. */
#define YYNSTATES  30

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   265

#define YYTRANSLATE(YYX)            \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
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
  5,     6,     7,     8,     9,    10
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
  0,     0,     3,     7,    11,    14,    17,    20,    22,    24,
  28,    31,    35,    38,    41,    43,    46,    48,    51,    55
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
  12,     0,    -1,    13,    14,    15,    -1,    13,     7,    15,
  -1,    13,    14,    -1,    13,     7,    -1,    14,    15,    -1,
  14,    -1,    16,    -1,    13,     5,    16,    -1,     7,    16,
  -1,    14,     5,    16,    -1,     8,    16,    -1,    15,    16,
  -1,    17,    -1,    17,    18,    -1,     6,    -1,     3,     6,
  -1,     3,     4,     6,    -1,     9,     6,    10,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
  0,    47,    47,    50,    55,    58,    63,    67,    71,    78,
  87,    97,   106,   114,   122,   127,   135,   140,   146,   154
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_NUMBER", "TOKEN_MULTIPLY",
  "TOKEN_PLUS", "TOKEN_NAME", "TOKEN_BEGIN_PRODUCTS",
  "TOKEN_BEGIN_MODIFIERS", "TOKEN_BEGIN_COMPARTMENT",
  "TOKEN_END_COMPARTMENT", "$accept", "reaction", "substrates", "products",
  "modifiers", "reactant", "prereactant", "compartment", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
  0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
  265
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
  0,    11,    12,    12,    12,    12,    12,    12,    13,    13,
  14,    14,    15,    15,    16,    16,    17,    17,    17,    18
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
  0,     2,     3,     3,     2,     2,     2,     1,     1,     3,
  2,     3,     2,     2,     1,     2,     1,     2,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
  0,     0,    16,     0,     0,     0,     7,     8,    14,     0,
  17,    10,     1,     0,     5,     4,     0,     0,     6,     0,
  15,    18,     9,     3,     2,    11,    12,    13,     0,    19
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
  -1,     4,     5,     6,    18,    27,     8,    20
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -8
static const yysigned_char yypact[] =
{
  2,    14,    -8,     4,    11,    16,     7,    -8,    -7,    13,
  -8,    -8,    -8,     4,    -2,     7,     4,     4,     4,    20,
  -8,    -8,    -8,     4,     4,    -8,    -8,    -8,    12,    -8
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
  -8,    -8,    -8,    22,    10,     0,    -8,    -8
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
  7,     1,    19,    11,     2,     1,    17,     1,     2,     3,
  2,    12,    16,    22,    11,    17,    25,    26,     9,    21,
  10,    13,    29,    14,    23,    24,    28,    15
};

static const unsigned char yycheck[] =
{
  0,     3,     9,     3,     6,     3,     8,     3,     6,     7,
  6,     0,     5,    13,    14,     8,    16,    17,     4,     6,
  6,     5,    10,     7,    14,    15,     6,     5
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
  0,     3,     6,     7,    12,    13,    14,    16,    17,     4,
  6,    16,     0,     5,     7,    14,     5,     8,    15,     9,
  18,     6,    16,    15,    15,    16,    16,    16,     6,    10
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok   (yyerrstatus = 0)
#define yyclearin (yychar = YYEMPTY)
#define YYEMPTY   (-2)
#define YYEOF   0

#define YYACCEPT  goto yyacceptlab
#define YYABORT   goto yyabortlab
#define YYERROR   goto yyerrorlab

/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL    goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)          \
  do                \
    if (yychar == YYEMPTY && yylen == 1)        \
      {\
        yychar = (Token);           \
        yylval = (Value);           \
        yytoken = YYTRANSLATE (yychar);       \
        YYPOPSTACK;           \
        goto yybackup;            \
      }               \
    else                \
      {\
        yyerror ("syntax error: cannot back up");\
        YYERROR;              \
      }               \
  while (0)

#define YYTERROR  1
#define YYERRCODE 256

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)        \
  do                  \
    if (N)                \
      {\
        (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;  \
        (Current).first_column = YYRHSLOC (Rhs, 1).first_column;  \
        (Current).last_line    = YYRHSLOC (Rhs, N).last_line;   \
        (Current).last_column  = YYRHSLOC (Rhs, N).last_column; \
      }               \
    else                \
      {\
        (Current).first_line   = (Current).last_line   =    \
                                 YYRHSLOC (Rhs, 0).last_line;        \
        (Current).first_column = (Current).last_column =    \
                                 YYRHSLOC (Rhs, 0).last_column;        \
      }               \
  while (0)
#endif

/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)      \
  fprintf (File, "%d.%d-%d.%d",      \
           (Loc).first_line, (Loc).first_column, \
           (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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
    } while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)    \
  do {\
      if (yydebug)              \
        {\
          YYFPRINTF (stderr, "%s ", Title);       \
          yysymprint (stderr,           \
                      Type, Value); \
          YYFPRINTF (stderr, "\n");         \
        }               \
    } while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print(short int *bottom, short int *top)
#else
static void
yy_stack_print(bottom, top)
short int *bottom;
short int *top;
#endif
{
  YYFPRINTF(stderr, "Stack now");

  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF(stderr, " %d", *bottom);

  YYFPRINTF(stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)        \
  do {\
      if (yydebug)              \
        yy_stack_print ((Bottom), (Top));       \
    } while (0)

/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print(int yyrule)
#else
static void
yy_reduce_print(yyrule)
int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF(stderr, "Reducing stack by rule %d (line %u), ",
            yyrule - 1, yylno);

  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF(stderr, "%s ", yytname [yyrhs[yyi]]);

  YYFPRINTF(stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)    \
  do {\
      if (yydebug)        \
        yy_reduce_print (Rule);   \
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen(const char *yystr)
#   else
yystrlen(yystr)
const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy(char *yydest, const char *yysrc)
#   else
yystpcpy(yydest, yysrc)
char *yydest;
const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint(FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint(yyoutput, yytype, yyvaluep)
FILE *yyoutput;
int yytype;
YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    YYFPRINTF(yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF(yyoutput, "nterm %s (", yytname[yytype]);

# ifdef YYPRINT

  if (yytype < YYNTOKENS)
    YYPRINT(yyoutput, yytoknum[yytype], *yyvaluep);

# endif

  switch (yytype)
    {
      default:
        break;
    }

  YYFPRINTF(yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
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
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (!yymsg)
    yymsg = "Deleting";

  YY_SYMBOL_PRINT(yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
# else
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
#else
#endif
#endif /* ! YYPARSE_PARAM */

/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse(void *YYPARSE_PARAM)
# else
int yyparse(YYPARSE_PARAM)
void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse(void)
#else
int
yyparse()

#endif
#endif
{

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;   /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  yyvsp[0] = yylval;

  goto yysetstate;

  /*------------------------------------------------------------.
  | yynewstate -- Push a new state, which is found in yystate.  |
  `------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack. Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        short int *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow("parser stack overflow",
                   &yyss1, yysize * sizeof(*yyssp),
                   &yyvs1, yysize * sizeof(*yyvsp),

                   &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else

      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyoverflowlab;

      yystacksize *= 2;

      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        short int *yyss1 = yyss;
        union yyalloc *yyptr =
              (union yyalloc *) YYSTACK_ALLOC(YYSTACK_BYTES(yystacksize));

        if (! yyptr)
          goto yyoverflowlab;

        YYSTACK_RELOCATE(yyss);
        YYSTACK_RELOCATE(yyvs);

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

  goto yybackup;

  /*-----------.
  | yybackup.  |
  `-----------*/
yybackup:

  /* Do appropriate processing given the current state.  */
  /* Read a look-ahead token if we need one and don't already have one.  */
  /* yyresume: */

  /* First try to decide what to do without reference to look-ahead token.  */

  yyn = yypact[yystate];

  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
        goto yyerrlab;

      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
  yyval = yyvsp[1-yylen];

  YY_REDUCE_PRINT(yyn);

  switch (yyn)
    {
      case 2:
#line 48 "CChemEqParser.ypp"
        {
        }
        break;

      case 3:
#line 51 "CChemEqParser.ypp"
        {
          mReversibility = ((yyvsp[-1])->name == "=") ? true : false;
          pdelete((yyvsp[-1]));
        }
        break;

      case 4:
#line 56 "CChemEqParser.ypp"
        {
        }
        break;

      case 5:
#line 59 "CChemEqParser.ypp"
        {
          mReversibility = ((yyvsp[0])->name == "=") ? true : false;
          pdelete((yyvsp[0]));
        }
        break;

      case 6:
#line 64 "CChemEqParser.ypp"
        {
        }
        break;

      case 7:
#line 68 "CChemEqParser.ypp"
        {
        }
        break;

      case 8:
#line 72 "CChemEqParser.ypp"
        {
          mSubstrateNames.push_back((yyvsp[0])->name);
          mSubstrateMult.push_back((yyvsp[0])->multiplicity);
          mSubstrateCompartments.push_back((yyvsp[0])->compartment);
          pdelete((yyvsp[0]));
        }
        break;

      case 9:
#line 79 "CChemEqParser.ypp"
        {
          mSubstrateNames.push_back((yyvsp[0])->name);
          mSubstrateMult.push_back((yyvsp[0])->multiplicity);
          mSubstrateCompartments.push_back((yyvsp[0])->compartment);
          pdelete((yyvsp[-1]));
          pdelete((yyvsp[0]));
        }
        break;

      case 10:
#line 88 "CChemEqParser.ypp"
        {
          mReversibility = ((yyvsp[-1])->name == "=") ? true : false;

          mProductNames.push_back((yyvsp[0])->name);
          mProductMult.push_back((yyvsp[0])->multiplicity);
          mProductCompartments.push_back((yyvsp[0])->compartment);
          pdelete((yyvsp[-1]));
          pdelete((yyvsp[0]));
        }
        break;

      case 11:
#line 98 "CChemEqParser.ypp"
        {
          mProductNames.push_back((yyvsp[0])->name);
          mProductMult.push_back((yyvsp[0])->multiplicity);
          mProductCompartments.push_back((yyvsp[0])->compartment);
          pdelete((yyvsp[-1]));
          pdelete((yyvsp[0]));
        }
        break;

      case 12:
#line 107 "CChemEqParser.ypp"
        {
          mModifierNames.push_back((yyvsp[0])->name);
          mModifierMult.push_back((yyvsp[0])->multiplicity);
          mModifierCompartments.push_back((yyvsp[0])->compartment);
          pdelete((yyvsp[-1]));
          pdelete((yyvsp[0]));
        }
        break;

      case 13:
#line 115 "CChemEqParser.ypp"
        {
          mModifierNames.push_back((yyvsp[0])->name);
          mModifierMult.push_back((yyvsp[0])->multiplicity);
          mModifierCompartments.push_back((yyvsp[0])->compartment);
          pdelete((yyvsp[0]));
        }
        break;

      case 14:
#line 123 "CChemEqParser.ypp"
        {
          (yyval) = (yyvsp[0]);
          (yyval)->compartment = "";
        }
        break;

      case 15:
#line 128 "CChemEqParser.ypp"
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->compartment = (yyvsp[0])->name;
          pdelete((yyvsp[0]));
        }
        break;

      case 16:
#line 136 "CChemEqParser.ypp"
        {
          (yyval) = (yyvsp[0]);
          (yyval)->multiplicity = 1.0;
        }
        break;

      case 17:
#line 141 "CChemEqParser.ypp"
        {
          (yyval) = (yyvsp[0]);
          (yyval)->multiplicity = strToDouble((yyvsp[-1])->name.c_str(), NULL);
          pdelete((yyvsp[-1]));
        }
        break;

      case 18:
#line 147 "CChemEqParser.ypp"
        {
          (yyval) = (yyvsp[0]);
          (yyval)->multiplicity = strToDouble((yyvsp[-2])->name.c_str(), NULL);
          pdelete((yyvsp[-2]));
          pdelete((yyvsp[-1]));
        }
        break;

      case 19:
#line 155 "CChemEqParser.ypp"
        {
          (yyval) = (yyvsp[-1]);
          pdelete((yyvsp[-2]));
          pdelete((yyvsp[0]));
        }
        break;
    }

  /* Line 1037 of yacc.c.  */
#line 1218 "CChemEqParser_yacc.cpp"
  
  yyvsp -= yylen;
  yyssp -= yylen;

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

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
        {
          YYSIZE_T yysize = 0;
          int yytype = YYTRANSLATE(yychar);
          const char* yyprefix;
          char *yymsg;
          int yyx;

          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;

          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yycount = 0;

          yyprefix = ", expecting ";

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
              {
                yysize += yystrlen(yyprefix) + yystrlen(yytname [yyx]);
                yycount += 1;

                if (yycount == 5)
                  {
                    yysize = 0;
                    break;
                  }
              }

          yysize += (sizeof("syntax error, unexpected ")
                     + yystrlen(yytname[yytype]));
          yymsg = (char *) YYSTACK_ALLOC(yysize);

          if (yymsg != 0)
            {
              char *yyp = yystpcpy(yymsg, "syntax error, unexpected ");
              yyp = yystpcpy(yyp, yytname[yytype]);

              if (yycount < 5)
                {
                  yyprefix = ", expecting ";

                  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
                    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
                      {
                        yyp = yystpcpy(yyp, yyprefix);
                        yyp = yystpcpy(yyp, yytname[yyx]);
                        yyprefix = " or ";
                      }
                }

              yyerror(yymsg);
              YYSTACK_FREE(yymsg);
            }
          else
            yyerror("syntax error; also virtual memory exhausted");
        }
      else
#endif /* YYERROR_VERBOSE */
        yyerror("syntax error");
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
      error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
          then the rest of the stack, then return failure.  */
          if (yychar == YYEOF)
            for (;;)
              {

                YYPOPSTACK;

                if (yyssp == yyss)
                  YYABORT;

                yydestruct("Error: popping",
                           yystos[*yyssp], yyvsp);
              }
        }
      else
        {
          yydestruct("Error: discarding", yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;

  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__

  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
    goto yyerrorlab;

#endif

  yyvsp -= yylen;
  yyssp -= yylen;
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

      if (yyn != YYPACT_NINF)
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

      yydestruct("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT(yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  /* Shift the error token. */
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
  yydestruct("Error: discarding lookahead",
             yytoken, &yylval);
  yychar = YYEMPTY;
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
  /*----------------------------------------------.
  | yyoverflowlab -- parser overflow comes here.  |
  `----------------------------------------------*/
yyoverflowlab:
  yyerror("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow

  if (yyss != yyssa)
    YYSTACK_FREE(yyss);

#endif
  return yyresult;
}

#line 162 "CChemEqParser.ypp"
