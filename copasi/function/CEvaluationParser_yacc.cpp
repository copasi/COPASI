/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationParser_yacc.cpp,v $
   $Revision: 1.19 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/05/05 17:08:36 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef lint
static char const
yyrcsid[] = "$FreeBSD: src/usr.bin/yacc/skeleton.c,v 1.28 2000/01/17 02:04:06 bde Exp $";
#endif
#include <stdlib.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
static int yygrowstack();
#define yyparse CEvaluationParserBase::yyparse
#define yyerror CEvaluationParsererror
#define yychar CEvaluationParserchar
#define yyval CEvaluationParserval
#define yylval CEvaluationParserlval
#define yydebug CEvaluationParserdebug
#define yynerrs CEvaluationParsernerrs
#define yyerrflag CEvaluationParsererrflag
#define yyss CEvaluationParserss
#define yyssp CEvaluationParserssp
#define yyvs CEvaluationParservs
#define yyvsp CEvaluationParservsp
#define yylhs CEvaluationParserlhs
#define yylen CEvaluationParserlen
#define yydefred CEvaluationParserdefred
#define yydgoto CEvaluationParserdgoto
#define yysindex CEvaluationParsersindex
#define yyrindex CEvaluationParserrindex
#define yygindex CEvaluationParsergindex
#define yytable CEvaluationParsertable
#define yycheck CEvaluationParsercheck
#define yyname CEvaluationParsername
#define yyrule CEvaluationParserrule
#define yysslim CEvaluationParsersslim
#define yystacksize CEvaluationParserstacksize
#define YYPREFIX "CEvaluationParser"
#line 5 "CEvaluationParser.ypp"
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

#line 62 "CEvaluationParser_yacc.cpp"
#define YYERRCODE 256
#define TOKEN_NUMBER 257
#define TOKEN_VARIABLE 258
#define TOKEN_CALL 259
#define TOKEN_FUNCTION 260
#define TOKEN_SIGN 261
#define TOKEN_OPERATOR_POWER 262
#define TOKEN_OPERATOR_MULTIPLY 263
#define TOKEN_OPERATOR_MODULUS 264
#define TOKEN_OPERATOR_PLUS 265
#define TOKEN_LOGICAL_CHOICE 266
#define TOKEN_LOGICAL_VALUE 267
#define TOKEN_LOGICAL_NOT 268
#define TOKEN_LOGICAL_OR 269
#define TOKEN_LOGICAL_XOR 270
#define TOKEN_LOGICAL_AND 271
#define TOKEN_LOGICAL_EQ 272
#define TOKEN_LOGICAL_NE 273
#define TOKEN_LOGICAL_GT 274
#define TOKEN_LOGICAL_GE 275
#define TOKEN_LOGICAL_LT 276
#define TOKEN_LOGICAL_LE 277
#define TOKEN_STRUCTURE_OPEN 278
#define TOKEN_STRUCTURE_VECTOR_OPEN 279
#define TOKEN_STRUCTURE_COMMA 280
#define TOKEN_STRUCTURE_CLOSE 281
#define TOKEN_STRUCTURE_VECTOR_CLOSE 282
const short CEvaluationParserlhs[] =
  {
    -1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
    3, 4, 4, 4, 4, 2, 2, 2, 5, 5,
    5,
  };
const short CEvaluationParserlen[] =
  {
    2,
    1, 1, 3, 3, 3, 3, 3, 4, 2, 8,
    1, 1, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 2, 2,
    2, 2, 2, 3, 3, 2, 3, 3, 1, 3,
    3,
  };
const short CEvaluationParserdefred[] =
  {
    0,
    1, 2, 0, 0, 0, 0, 0, 0, 11, 0,
    36, 0, 9, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 12, 0, 0, 0, 0, 7,
    0, 0, 0, 0, 30, 0, 33, 40, 37, 41,
    38, 0, 31, 8, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    35, 28, 0, 0, 0, 18, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 20, 0, 0, 0,
    10,
  };
const short CEvaluationParserdgoto[] =
  {
    28,
    29, 9, 22, 23, 10,
  };
const short CEvaluationParsersindex[] =
  {
    -155,
    0, 0, -274, -225, -155, -194, -155, -4, 0, -180,
    0, -155, 0, -216, -123, -155, -155, -155, -155, -191,
    -143, -261, -280, -119, 0, -216, -216, -92, 100, 0,
    -186, -186, -202, -131, 0, -4, 0, 0, 0, 0,
    0, -180, 0, 0, -226, -147, -19, -216, -216, -155,
    -155, -155, -155, -216, -216, -216, -216, -216, -155, -4,
    0, 0, -87, -184, -71, 0, -4, -4, -4, -4,
    -163, -116, -226, -87, -184, -71, 0, -111, -155, -115,
    0,
  };
const short CEvaluationParserrindex[] =
  {
    0,
    0, 0, -165, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 21, 35, 49, 0, -270, 0, 0, 0, 0,
    0, 0, 0, 0, 84, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, -248,
    0, 0, -198, 63, -73, 0, -60, -55, -42, -37,
    -252, -266, 87, 67, 80, -24, 0, 0, 0, 0,
    0,
  };
const short CEvaluationParsergindex[] =
  {
    6,
    -18, 0, -15, 0, 0,
  };
#define YYTABLESIZE 380
const short CEvaluationParsertable[] =
  {
    42,
    6, 43, 26, 26, 37, 8, 11, 45, 47, 32,
    13, 32, 15, 26, 26, 21, 25, 24, 40, 41,
    5, 31, 32, 33, 34, 36, 61, 25, 25, 64,
    66, 34, 46, 34, 4, 71, 72, 73, 75, 77,
    1, 2, 3, 4, 5, 57, 58, 60, 3, 6,
    25, 26, 12, 63, 65, 67, 68, 69, 70, 16,
    17, 27, 74, 76, 78, 1, 2, 3, 4, 5,
    13, 13, 13, 13, 6, 16, 1, 2, 3, 4,
    5, 13, 13, 14, 80, 6, 7, 20, 58, 0,
    35, 39, 39, 39, 39, 39, 0, 7, 20, 0,
    39, 1, 2, 3, 4, 5, 55, 56, 57, 58,
    6, 0, 39, 39, 16, 17, 18, 19, 16, 17,
    18, 19, 7, 0, 48, 49, 50, 51, 52, 53,
    16, 17, 18, 30, 0, 0, 38, 39, 16, 17,
    18, 19, 16, 17, 18, 19, 16, 17, 18, 19,
    16, 17, 18, 19, 56, 57, 58, 30, 0, 0,
    0, 44, 0, 0, 0, 81, 0, 0, 79, 16,
    17, 18, 19, 0, 16, 17, 18, 19, 0, 48,
    49, 50, 51, 52, 53, 49, 50, 51, 52, 53,
    16, 17, 18, 19, 0, 17, 17, 17, 17, 17,
    0, 0, 50, 51, 52, 53, 17, 17, 21, 21,
    21, 21, 21, 22, 22, 22, 22, 22, 0, 21,
    21, 0, 0, 0, 22, 22, 23, 23, 23, 23,
    23, 24, 24, 24, 24, 24, 0, 23, 23, 0,
    0, 0, 24, 24, 19, 19, 19, 19, 19, 54,
    55, 56, 57, 58, 0, 19, 19, 16, 17, 18,
    19, 62, 0, 6, 6, 6, 0, 0, 0, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 0, 0,
    6, 6, 6, 5, 5, 5, 0, 0, 0, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 4, 4,
    5, 5, 5, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 0, 3, 4, 4, 4, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 0, 0, 3, 3,
    3, 14, 14, 14, 14, 15, 15, 15, 15, 0,
    0, 0, 14, 14, 0, 0, 15, 15, 16, 16,
    16, 16, 29, 29, 29, 27, 27, 27, 0, 16,
    16, 0, 0, 29, 29, 0, 27, 27, 54, 55,
    56, 57, 58, 0, 0, 0, 0, 0, 0, 59,
  };
const short CEvaluationParsercheck[] =
  {
    280,
    0, 282, 269, 270, 20, 0, 281, 26, 27, 280,
    5, 282, 7, 280, 281, 10, 269, 12, 280, 281,
    0, 16, 17, 18, 19, 20, 42, 280, 281, 48,
    49, 280, 27, 282, 0, 54, 55, 56, 57, 58,
    257, 258, 259, 260, 261, 272, 273, 42, 0, 266,
    267, 268, 278, 48, 49, 50, 51, 52, 53, 262,
    263, 278, 57, 58, 59, 257, 258, 259, 260, 261,
    269, 270, 271, 272, 266, 262, 257, 258, 259, 260,
    261, 280, 281, 278, 79, 266, 278, 279, 273, -1,
    282, 257, 258, 259, 260, 261, -1, 278, 279, -1,
    266, 257, 258, 259, 260, 261, 270, 271, 272, 273,
    266, -1, 278, 279, 262, 263, 264, 265, 262, 263,
    264, 265, 278, -1, 272, 273, 274, 275, 276, 277,
    262, 263, 264, 281, -1, -1, 280, 281, 262, 263,
    264, 265, 262, 263, 264, 265, 262, 263, 264, 265,
    262, 263, 264, 265, 271, 272, 273, 281, -1, -1,
    -1, 281, -1, -1, -1, 281, -1, -1, 280, 262,
    263, 264, 265, -1, 262, 263, 264, 265, -1, 272,
    273, 274, 275, 276, 277, 273, 274, 275, 276, 277,
    262, 263, 264, 265, -1, 269, 270, 271, 272, 273,
    -1, -1, 274, 275, 276, 277, 280, 281, 269, 270,
    271, 272, 273, 269, 270, 271, 272, 273, -1, 280,
    281, -1, -1, -1, 280, 281, 269, 270, 271, 272,
    273, 269, 270, 271, 272, 273, -1, 280, 281, -1,
    -1, -1, 280, 281, 269, 270, 271, 272, 273, 269,
    270, 271, 272, 273, -1, 280, 281, 262, 263, 264,
    265, 281, -1, 263, 264, 265, -1, -1, -1, 269,
    270, 271, 272, 273, 274, 275, 276, 277, -1, -1,
    280, 281, 282, 263, 264, 265, -1, -1, -1, 269,
    270, 271, 272, 273, 274, 275, 276, 277, 264, 265,
    280, 281, 282, 269, 270, 271, 272, 273, 274, 275,
    276, 277, -1, 265, 280, 281, 282, 269, 270, 271,
    272, 273, 274, 275, 276, 277, -1, -1, 280, 281,
    282, 269, 270, 271, 272, 269, 270, 271, 272, -1,
    -1, -1, 280, 281, -1, -1, 280, 281, 269, 270,
    271, 272, 269, 270, 271, 269, 270, 271, -1, 280,
    281, -1, -1, 280, 281, -1, 280, 281, 269, 270,
    271, 272, 273, -1, -1, -1, -1, -1, -1, 280,
  };
#define YYFINAL 8
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 282
#if YYDEBUG
const char * const CEvaluationParsername[] =
  {
    "end-of-file", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "TOKEN_NUMBER", "TOKEN_VARIABLE",
    "TOKEN_CALL", "TOKEN_FUNCTION", "TOKEN_SIGN", "TOKEN_OPERATOR_POWER",
    "TOKEN_OPERATOR_MULTIPLY", "TOKEN_OPERATOR_MODULUS", "TOKEN_OPERATOR_PLUS",
    "TOKEN_LOGICAL_CHOICE", "TOKEN_LOGICAL_VALUE", "TOKEN_LOGICAL_NOT",
    "TOKEN_LOGICAL_OR", "TOKEN_LOGICAL_XOR", "TOKEN_LOGICAL_AND", "TOKEN_LOGICAL_EQ",
    "TOKEN_LOGICAL_NE", "TOKEN_LOGICAL_GT", "TOKEN_LOGICAL_GE", "TOKEN_LOGICAL_LT",
    "TOKEN_LOGICAL_LE", "TOKEN_STRUCTURE_OPEN", "TOKEN_STRUCTURE_VECTOR_OPEN",
    "TOKEN_STRUCTURE_COMMA", "TOKEN_STRUCTURE_CLOSE", "TOKEN_STRUCTURE_VECTOR_CLOSE",
  };
const char * const CEvaluationParserrule[] =
  {
    "$accept : exp",
    "exp : TOKEN_NUMBER",
    "exp : TOKEN_VARIABLE",
    "exp : exp TOKEN_OPERATOR_PLUS exp",
    "exp : exp TOKEN_OPERATOR_MODULUS exp",
    "exp : exp TOKEN_OPERATOR_MULTIPLY exp",
    "exp : exp TOKEN_OPERATOR_POWER exp",
    "exp : TOKEN_STRUCTURE_OPEN exp TOKEN_STRUCTURE_CLOSE",
    "exp : TOKEN_FUNCTION TOKEN_STRUCTURE_OPEN exp TOKEN_STRUCTURE_CLOSE",
    "exp : TOKEN_SIGN exp",
    "exp : TOKEN_LOGICAL_CHOICE TOKEN_STRUCTURE_OPEN bool TOKEN_STRUCTURE_COMMA exp TOKEN_STRUCTURE_COMMA exp TOKEN_STRUCTURE_CLOSE",
    "exp : call",
    "bool : TOKEN_LOGICAL_VALUE",
    "bool : exp TOKEN_LOGICAL_EQ exp",
    "bool : exp TOKEN_LOGICAL_EQ bool",
    "bool : bool TOKEN_LOGICAL_EQ exp",
    "bool : bool TOKEN_LOGICAL_EQ bool",
    "bool : exp TOKEN_LOGICAL_NE exp",
    "bool : exp TOKEN_LOGICAL_NE bool",
    "bool : bool TOKEN_LOGICAL_NE exp",
    "bool : bool TOKEN_LOGICAL_NE bool",
    "bool : exp TOKEN_LOGICAL_GT exp",
    "bool : exp TOKEN_LOGICAL_GE exp",
    "bool : exp TOKEN_LOGICAL_LT exp",
    "bool : exp TOKEN_LOGICAL_LE exp",
    "bool : bool TOKEN_LOGICAL_OR bool",
    "bool : bool TOKEN_LOGICAL_XOR bool",
    "bool : bool TOKEN_LOGICAL_AND bool",
    "bool : TOKEN_STRUCTURE_OPEN bool TOKEN_STRUCTURE_CLOSE",
    "bool : TOKEN_LOGICAL_NOT bool",
    "vector : TOKEN_STRUCTURE_VECTOR_OPEN TOKEN_STRUCTURE_VECTOR_CLOSE",
    "vector : vstart TOKEN_STRUCTURE_VECTOR_CLOSE",
    "vstart : TOKEN_STRUCTURE_VECTOR_OPEN exp",
    "vstart : TOKEN_STRUCTURE_VECTOR_OPEN vector",
    "vstart : vstart TOKEN_STRUCTURE_COMMA exp",
    "vstart : vstart TOKEN_STRUCTURE_COMMA vector",
    "call : TOKEN_CALL TOKEN_STRUCTURE_CLOSE",
    "call : cstart exp TOKEN_STRUCTURE_CLOSE",
    "call : cstart vector TOKEN_STRUCTURE_CLOSE",
    "cstart : TOKEN_CALL",
    "cstart : cstart exp TOKEN_STRUCTURE_COMMA",
    "cstart : cstart vector TOKEN_STRUCTURE_COMMA",
  };
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
#if YYDEBUG
#include <stdio.h>
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug = YYDEBUG;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
#line 332 "CEvaluationParser.ypp"

#line 323 "CEvaluationParser_yacc.cpp"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack()
{
  int newsize, i;
  short *newss;
  YYSTYPE *newvs;

  if ((newsize = yystacksize) == 0)
    newsize = YYINITSTACKSIZE;
  else if (newsize >= YYMAXDEPTH)
    return - 1;
  else if ((newsize *= 2) > YYMAXDEPTH)
    newsize = YYMAXDEPTH;
  i = yyssp - yyss;
  newss = yyss ? (short *)realloc(yyss, newsize * sizeof * newss) :
          (short *)malloc(newsize * sizeof * newss);
  if (newss == NULL)
    return - 1;
  yyss = newss;
  yyssp = newss + i;
  newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof * newvs) :
          (YYSTYPE *)malloc(newsize * sizeof * newvs);
  if (newvs == NULL)
    return - 1;
  yyvs = newvs;
  yyvsp = newvs + i;
  yystacksize = newsize;
  yysslim = yyss + newsize - 1;
  return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#ifndef YYPARSE_PARAM
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG void
#define YYPARSE_PARAM_DECL
#else /* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* ANSI-C/C++ */
#else /* YYPARSE_PARAM */
#ifndef YYPARSE_PARAM_TYPE
#define YYPARSE_PARAM_TYPE void *
#endif
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG YYPARSE_PARAM_TYPE YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL YYPARSE_PARAM_TYPE YYPARSE_PARAM;
#endif /* ANSI-C/C++ */
#endif /* ! YYPARSE_PARAM */

int
yyparse (YYPARSE_PARAM_ARG)
YYPARSE_PARAM_DECL
{
  register int yym, yyn, yystate;
#if YYDEBUG
  register const char *yys;

  if ((yys = getenv("YYDEBUG")))
  {
    yyn = *yys;
    if (yyn >= '0' && yyn <= '9')
        yydebug = yyn - '0';
    }
#endif

  yynerrs = 0;
  yyerrflag = 0;
  yychar = (-1);

  if (yyss == NULL && yygrowstack()) goto yyoverflow;
  yyssp = yyss;
  yyvsp = yyvs;
  *yyssp = yystate = 0;

  yyloop:
  if ((yyn = yydefred[yystate])) goto yyreduce;
    if (yychar < 0)
      {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
          if (yydebug)
            {
              yys = 0;
              if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
              if (!yys) yys = "illegal-symbol";
              printf("%sdebug: state %d, reading %d (%s)\n",
                     YYPREFIX, yystate, yychar, yys);
            }
#endif
        }
  if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
      yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
  {
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, shifting to state %d\n",
               YYPREFIX, yystate, yytable[yyn]);
#endif
      if (yyssp >= yysslim && yygrowstack())
        {
          goto yyoverflow;
        }
      *++yyssp = yystate = yytable[yyn];
      *++yyvsp = yylval;
      yychar = (-1);
      if (yyerrflag > 0) --yyerrflag;
      goto yyloop;
    }
  if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
      yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
  {
    yyn = yytable[yyn];
      goto yyreduce;
    }
  if (yyerrflag) goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
  goto yynewerror;
#endif
  yynewerror:
  yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
  goto yyerrlab;
#endif
  yyerrlab:
  ++yynerrs;
  yyinrecovery:
  if (yyerrflag < 3)
    {
      yyerrflag = 3;
      for (;;)
          {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
              {
#if YYDEBUG
                if (yydebug)
                  printf("%sdebug: state %d, error recovery shifting\
                         to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                  {
                    goto yyoverflow;
                  }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
              }
            else
              {
#if YYDEBUG
                if (yydebug)
                  printf("%sdebug: error recovery discarding state %d\n",
                         YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
              }
          }
      }
    else
      {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
          {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                   YYPREFIX, yystate, yychar, yys);
          }
#endif
        yychar = (-1);
        goto yyloop;
      }
  yyreduce:
#if YYDEBUG
  if (yydebug)
  printf("%sdebug: state %d, reducing by rule %d (%s)\n",
         YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
  yym = yylen[yyn];
  yyval = yyvsp[1 - yym];
  switch (yyn)
    {
    case 1:
#line 81 "CEvaluationParser.ypp"
      {
        mpRootNode = yyvsp[0];
        }
        break;
      case 2:
#line 85 "CEvaluationParser.ypp"
        {
          mpRootNode = yyvsp[0];
        }
        break;
      case 3:
#line 89 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 4:
#line 96 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 5:
#line 103 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 6:
#line 110 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 7:
#line 117 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          mpRootNode = yyval;
        }
        break;
      case 8:
#line 122 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -3];
          yyval->addChild(yyvsp[ -1]);
          mpRootNode = yyval;
        }
        break;
      case 9:
#line 128 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 10:
#line 134 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -7];
          yyval->addChild(yyvsp[ -5]);
          yyval->addChild(yyvsp[ -3]);
          yyval->addChild(yyvsp[ -1]);
          mpRootNode = yyval;
        }
        break;
      case 11:
#line 142 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[0];
          mpRootNode = yyval;
        }
        break;
      case 12:
#line 148 "CEvaluationParser.ypp"
        {
          mpRootNode = yyvsp[0];
        }
        break;
      case 13:
#line 152 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 14:
#line 159 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 15:
#line 166 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 16:
#line 173 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 17:
#line 180 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 18:
#line 187 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 19:
#line 194 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 20:
#line 201 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 21:
#line 208 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 22:
#line 215 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 23:
#line 222 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 24:
#line 229 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 25:
#line 236 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 26:
#line 243 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 27:
#line 250 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 28:
#line 257 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          mpRootNode = yyval;
        }
        break;
      case 29:
#line 262 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 30:
#line 269 "CEvaluationParser.ypp"
        {
          yyval = new CEvaluationNodeVector();
          mpNodeList->push_back(yyval);
        }
        break;
      case 31:
#line 274 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
        }
        break;
      case 32:
#line 280 "CEvaluationParser.ypp"
        {
          yyval = new CEvaluationNodeVector();
          mpNodeList->push_back(yyval);
          yyval->addChild(yyvsp[0]);
        }
        break;
      case 33:
#line 286 "CEvaluationParser.ypp"
        {
          yyval = new CEvaluationNodeVector();
          mpNodeList->push_back(yyval);
          yyval->addChild(yyvsp[0]);
        }
        break;
      case 34:
#line 292 "CEvaluationParser.ypp"
        {
          yyval->addChild(yyvsp[0]);
        }
        break;
      case 35:
#line 296 "CEvaluationParser.ypp"
        {
          yyval->addChild(yyvsp[0]);
        }
        break;
      case 36:
#line 301 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
        }
        break;
      case 37:
#line 305 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -2];
          yyval->addChild(yyvsp[ -1]);
        }
        break;
      case 38:
#line 310 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -2];
          yyval->addChild(yyvsp[ -1]);
        }
        break;
      case 39:
#line 316 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[0];
        }
        break;
      case 40:
#line 320 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -2];
          yyval->addChild(yyvsp[ -1]);
        }
        break;
      case 41:
#line 325 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -2];
          yyval->addChild(yyvsp[ -1]);
        }
        break;
#line 843 "CEvaluationParser_yacc.cpp"
      }
  yyssp -= yym;
  yystate = *yyssp;
  yyvsp -= yym;
  yym = yylhs[yyn];
  if (yystate == 0 && yym == 0)
  {
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state 0 to\
               state %d\n", YYPREFIX, YYFINAL);
#endif
      yystate = YYFINAL;
      *++yyssp = YYFINAL;
      *++yyvsp = yyval;
      if (yychar < 0)
        {
          if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
          if (yydebug)
            {
              yys = 0;
              if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
              if (!yys) yys = "illegal-symbol";
              printf("%sdebug: state %d, reading %d (%s)\n",
                     YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
      if (yychar == 0) goto yyaccept;
      goto yyloop;
    }
  if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
      yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
  yystate = yytable[yyn];
  else
    yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
      printf("%sdebug: after reduction, shifting from state %d \
             to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
      if (yyssp >= yysslim && yygrowstack())
        {
          goto yyoverflow;
        }
  *++yyssp = yystate;
  *++yyvsp = yyval;
  goto yyloop;
  yyoverflow:
  yyerror("yacc stack overflow");
  yyabort:
  return (1);
  yyaccept:
  return (0);
}
