// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationParser_yacc.cpp,v $
//   $Revision: 1.21 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/09 14:46:43 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef lint
static const char yysccsid[] = "@(#)yaccpar 1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20050813

#define YYEMPTY (-1)
#define yyclearin    (yychar = YYEMPTY)
#define yyerrok      (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

extern int yyparse(void);

static int yygrowstack(void);
#define yyparse yyparse
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

#undef yyparse
#define yyparse CEvaluationParserBase::yyparse
#line 67 "CEvaluationParser_yacc.cpp"
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
#define YYERRCODE 256
short CEvaluationParserlhs[] = {-1,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                 3, 3, 4, 4, 4, 4, 2, 2, 2, 5,
                                 5, 5,
                               };
short CEvaluationParserlen[] = {2,
                                 1, 1, 3, 3, 3, 3, 3, 4, 2, 8,
                                 1, 1, 8, 3, 3, 3, 3, 3, 3, 3,
                                 3, 3, 3, 3, 3, 3, 3, 3, 3, 2,
                                 2, 2, 2, 2, 3, 3, 2, 3, 3, 1,
                                 3, 3,
                               };
short CEvaluationParserdefred[] = {0,
                                    1, 2, 0, 0, 0, 0, 0, 0, 11, 0,
                                    37, 0, 9, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 12, 0, 0, 0, 0,
                                    7, 0, 0, 0, 0, 31, 0, 34, 41, 38,
                                    42, 39, 0, 32, 8, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 36, 0, 29, 0, 0, 0, 19, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 21,
                                    0, 0, 0, 0, 0, 0, 0, 10, 0, 13,
                                  };
short CEvaluationParserdgoto[] = {29,
                                   30, 9, 22, 23, 10,
                                 };
short CEvaluationParsersindex[] = {-131,
                                    0, 0, -279, -246, -131, -234, -131, -210, 0, -172,
                                    0, -131, 0, -144, -259, -131, -131, -131, -131, -186,
                                    -120, -264, -273, -217, -228, 0, -144, -144, -67, 136,
                                    0, -196, -196, -225, -181, 0, -210, 0, 0, 0,
                                    0, 0, -172, 0, 0, -144, -216, -124, 81, -144,
                                    -144, -131, -131, -131, -131, -144, -144, -144, -144, -144,
                                    -131, -210, 0, 148, 0, -62, -189, -46, 0, -210,
                                    -210, -210, -210, -194, -162, -216, -62, -189, -46, 0,
                                    -86, -144, -131, -90, 153, -100, -144, 0, 86, 0,
                                  };
short CEvaluationParserrindex[] = {0,
                                    0, 0, -158, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 1, 21, 35, 49, 0, -268, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 120, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, -185, 0, 0, 0, 94, 99, -48, 0, -35,
                                    -30, -13, 63, -250, -114, 133, 112, 116, 68, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  };
short CEvaluationParsergindex[] = {8,
                                    -17, 0, -20, 0, 0,
                                  };
#define YYTABLESIZE 433
short CEvaluationParsertable[] = {38,
                                   6, 11, 16, 17, 18, 19, 43, 8, 44, 47,
                                   49, 33, 13, 33, 15, 41, 42, 21, 26, 24,
                                   5, 31, 63, 32, 33, 34, 35, 37, 64, 26,
                                   26, 12, 67, 69, 4, 48, 16, 17, 74, 75,
                                   76, 78, 80, 14, 16, 17, 18, 19, 3, 46,
                                   62, 16, 17, 18, 19, 59, 60, 66, 68, 70,
                                   71, 72, 73, 45, 85, 16, 77, 79, 81, 89,
                                   1, 2, 3, 4, 5, 57, 58, 59, 60, 6,
                                   16, 17, 18, 60, 1, 2, 3, 4, 5, 84,
                                   86, 7, 20, 6, 35, 36, 35, 0, 40, 40,
                                   40, 40, 40, 0, 0, 7, 20, 40, 58, 59,
                                   60, 0, 1, 2, 3, 4, 5, 0, 0, 40,
                                   40, 25, 26, 27, 0, 1, 2, 3, 4, 5,
                                   0, 0, 0, 28, 6, 0, 0, 16, 17, 18,
                                   19, 16, 17, 18, 19, 0, 7, 50, 51, 52,
                                   53, 54, 55, 0, 27, 27, 31, 0, 0, 39,
                                   40, 16, 17, 18, 19, 27, 27, 0, 0, 0,
                                   0, 16, 17, 18, 19, 16, 17, 18, 19, 0,
                                   88, 50, 51, 52, 53, 54, 55, 0, 0, 83,
                                   0, 0, 0, 83, 16, 17, 18, 19, 0, 16,
                                   17, 18, 19, 0, 50, 51, 52, 53, 54, 55,
                                   51, 52, 53, 54, 55, 16, 17, 18, 19, 0,
                                   18, 18, 18, 18, 18, 0, 0, 52, 53, 54,
                                   55, 18, 18, 22, 22, 22, 22, 22, 23, 23,
                                   23, 23, 23, 0, 22, 22, 0, 0, 0, 23,
                                   23, 0, 0, 0, 0, 24, 24, 24, 24, 24,
                                   0, 0, 0, 6, 6, 6, 24, 24, 0, 6,
                                   6, 6, 6, 6, 6, 6, 6, 6, 0, 0,
                                   6, 6, 6, 5, 5, 5, 0, 0, 0, 5,
                                   5, 5, 5, 5, 5, 5, 5, 5, 4, 4,
                                   5, 5, 5, 4, 4, 4, 4, 4, 4, 4,
                                   4, 4, 0, 3, 4, 4, 4, 3, 3, 3,
                                   3, 3, 3, 3, 3, 3, 0, 0, 3, 3,
                                   3, 25, 25, 25, 25, 25, 20, 20, 20, 20,
                                   20, 0, 25, 25, 0, 0, 0, 20, 20, 56,
                                   57, 58, 59, 60, 56, 57, 58, 59, 60, 0,
                                   0, 65, 14, 14, 14, 14, 90, 15, 15, 15,
                                   15, 0, 0, 14, 14, 0, 0, 0, 15, 15,
                                   16, 16, 16, 16, 17, 17, 17, 17, 30, 30,
                                   30, 16, 16, 0, 0, 17, 17, 0, 0, 30,
                                   30, 28, 28, 28, 56, 57, 58, 59, 60, 0,
                                   0, 0, 28, 28, 0, 61, 56, 57, 58, 59,
                                   60, 56, 57, 58, 59, 60, 0, 82, 0, 0,
                                   0, 0, 87,
                                 };
short CEvaluationParsercheck[] = {20,
                                   0, 281, 262, 263, 264, 265, 280, 0, 282, 27,
                                   28, 280, 5, 282, 7, 280, 281, 10, 269, 12,
                                   0, 281, 43, 16, 17, 18, 19, 20, 46, 280,
                                   281, 278, 50, 51, 0, 28, 262, 263, 56, 57,
                                   58, 59, 60, 278, 262, 263, 264, 265, 0, 278,
                                   43, 262, 263, 264, 265, 272, 273, 50, 51, 52,
                                   53, 54, 55, 281, 82, 262, 59, 60, 61, 87,
                                   257, 258, 259, 260, 261, 270, 271, 272, 273, 266,
                                   262, 263, 264, 273, 257, 258, 259, 260, 261, 82,
                                   83, 278, 279, 266, 280, 282, 282, -1, 257, 258,
                                   259, 260, 261, -1, -1, 278, 279, 266, 271, 272,
                                   273, -1, 257, 258, 259, 260, 261, -1, -1, 278,
                                   279, 266, 267, 268, -1, 257, 258, 259, 260, 261,
                                   -1, -1, -1, 278, 266, -1, -1, 262, 263, 264,
                                   265, 262, 263, 264, 265, -1, 278, 272, 273, 274,
                                   275, 276, 277, -1, 269, 270, 281, -1, -1, 280,
                                   281, 262, 263, 264, 265, 280, 281, -1, -1, -1,
                                   -1, 262, 263, 264, 265, 262, 263, 264, 265, -1,
                                   281, 272, 273, 274, 275, 276, 277, -1, -1, 280,
                                   -1, -1, -1, 280, 262, 263, 264, 265, -1, 262,
                                   263, 264, 265, -1, 272, 273, 274, 275, 276, 277,
                                   273, 274, 275, 276, 277, 262, 263, 264, 265, -1,
                                   269, 270, 271, 272, 273, -1, -1, 274, 275, 276,
                                   277, 280, 281, 269, 270, 271, 272, 273, 269, 270,
                                   271, 272, 273, -1, 280, 281, -1, -1, -1, 280,
                                   281, -1, -1, -1, -1, 269, 270, 271, 272, 273,
                                   -1, -1, -1, 263, 264, 265, 280, 281, -1, 269,
                                   270, 271, 272, 273, 274, 275, 276, 277, -1, -1,
                                   280, 281, 282, 263, 264, 265, -1, -1, -1, 269,
                                   270, 271, 272, 273, 274, 275, 276, 277, 264, 265,
                                   280, 281, 282, 269, 270, 271, 272, 273, 274, 275,
                                   276, 277, -1, 265, 280, 281, 282, 269, 270, 271,
                                   272, 273, 274, 275, 276, 277, -1, -1, 280, 281,
                                   282, 269, 270, 271, 272, 273, 269, 270, 271, 272,
                                   273, -1, 280, 281, -1, -1, -1, 280, 281, 269,
                                   270, 271, 272, 273, 269, 270, 271, 272, 273, -1,
                                   -1, 281, 269, 270, 271, 272, 281, 269, 270, 271,
                                   272, -1, -1, 280, 281, -1, -1, -1, 280, 281,
                                   269, 270, 271, 272, 269, 270, 271, 272, 269, 270,
                                   271, 280, 281, -1, -1, 280, 281, -1, -1, 280,
                                   281, 269, 270, 271, 269, 270, 271, 272, 273, -1,
                                   -1, -1, 280, 281, -1, 280, 269, 270, 271, 272,
                                   273, 269, 270, 271, 272, 273, -1, 280, -1, -1,
                                   -1, -1, 280,
                                 };
#define YYFINAL 8
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 282
#if YYDEBUG
char *CEvaluationParsername[] = {
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
char *CEvaluationParserrule[] = {
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
                                  "bool : TOKEN_LOGICAL_CHOICE TOKEN_STRUCTURE_OPEN bool TOKEN_STRUCTURE_COMMA bool TOKEN_STRUCTURE_COMMA bool TOKEN_STRUCTURE_CLOSE",
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

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;

/* variables for the parser stack */
static short *yyss;
static short *yysslim;
static YYSTYPE *yyvs;
static int yystacksize;
#line 342 "CEvaluationParser.ypp"

#line 347 "CEvaluationParser_yacc.cpp"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
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
  newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
  if (newss == 0)
    return - 1;

  yyss = newss;
  yyssp = newss + i;
  newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
  if (newvs == 0)
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
int
yyparse(void)
{
  register int yym, yyn, yystate;
#if YYDEBUG
  register const char *yys;

  if ((yys = getenv("YYDEBUG")) != 0)
    {
      yyn = *yys;
      if (yyn >= '0' && yyn <= '9')
        yydebug = yyn - '0';
    }
#endif

  yynerrs = 0;
  yyerrflag = 0;
  yychar = YYEMPTY;

  if (yyss == NULL && yygrowstack()) goto yyoverflow;
  yyssp = yyss;
  yyvsp = yyvs;
  *yyssp = yystate = 0;

yyloop:
  if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
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
      yychar = YYEMPTY;
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

  yyerror("syntax error");

#ifdef lint
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
      yychar = YYEMPTY;
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
#line 83 "CEvaluationParser.ypp"
      {
        mpRootNode = yyvsp[0];
      }
      break;
    case 2:
#line 87 "CEvaluationParser.ypp"
      {
        mpRootNode = yyvsp[0];
      }
      break;
    case 3:
#line 91 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 4:
#line 98 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 5:
#line 105 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 6:
#line 112 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 7:
#line 119 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        mpRootNode = yyval;
      }
      break;
    case 8:
#line 124 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -3];
        yyval->addChild(yyvsp[ -1]);
        mpRootNode = yyval;
      }
      break;
    case 9:
#line 130 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 10:
#line 136 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -7];
        yyval->addChild(yyvsp[ -5]);
        yyval->addChild(yyvsp[ -3]);
        yyval->addChild(yyvsp[ -1]);
        mpRootNode = yyval;
      }
      break;
    case 11:
#line 144 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[0];
        mpRootNode = yyval;
      }
      break;
    case 12:
#line 150 "CEvaluationParser.ypp"
      {
        mpRootNode = yyvsp[0];
      }
      break;
    case 13:
#line 154 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -7];
        yyval->addChild(yyvsp[ -5]);
        yyval->addChild(yyvsp[ -3]);
        yyval->addChild(yyvsp[ -1]);
        mpRootNode = yyval;
      }
      break;
    case 14:
#line 162 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 15:
#line 169 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 16:
#line 176 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 17:
#line 183 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 18:
#line 190 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 19:
#line 197 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 20:
#line 204 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 21:
#line 211 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 22:
#line 218 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 23:
#line 225 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 24:
#line 232 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 25:
#line 239 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 26:
#line 246 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 27:
#line 253 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 28:
#line 260 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[ -2]);
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 29:
#line 267 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        mpRootNode = yyval;
      }
      break;
    case 30:
#line 272 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
        yyval->addChild(yyvsp[0]);
        mpRootNode = yyval;
      }
      break;
    case 31:
#line 279 "CEvaluationParser.ypp"
      {
        yyval = new CEvaluationNodeVector();
        mpNodeList->push_back(yyval);
      }
      break;
    case 32:
#line 284 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
      }
      break;
    case 33:
#line 290 "CEvaluationParser.ypp"
      {
        yyval = new CEvaluationNodeVector();
        mpNodeList->push_back(yyval);
        yyval->addChild(yyvsp[0]);
      }
      break;
    case 34:
#line 296 "CEvaluationParser.ypp"
      {
        yyval = new CEvaluationNodeVector();
        mpNodeList->push_back(yyval);
        yyval->addChild(yyvsp[0]);
      }
      break;
    case 35:
#line 302 "CEvaluationParser.ypp"
      {
        yyval->addChild(yyvsp[0]);
      }
      break;
    case 36:
#line 306 "CEvaluationParser.ypp"
      {
        yyval->addChild(yyvsp[0]);
      }
      break;
    case 37:
#line 311 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -1];
      }
      break;
    case 38:
#line 315 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -2];
        yyval->addChild(yyvsp[ -1]);
      }
      break;
    case 39:
#line 320 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -2];
        yyval->addChild(yyvsp[ -1]);
      }
      break;
    case 40:
#line 326 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[0];
      }
      break;
    case 41:
#line 330 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -2];
        yyval->addChild(yyvsp[ -1]);
      }
      break;
    case 42:
#line 335 "CEvaluationParser.ypp"
      {
        yyval = yyvsp[ -2];
        yyval->addChild(yyvsp[ -1]);
      }
      break;
#line 860 "CEvaluationParser_yacc.cpp"
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
