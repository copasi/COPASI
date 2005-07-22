/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationParser_yacc.cpp,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/07/22 19:14:49 $
   End CVS Header */

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
#define YYPREFIX "yy"
#line 5 "CEvaluationParser.ypp"
#define YYSTYPE CEvaluationNode *
#define yylval  mpNode
#define yyerror(__str) \
  if (yychar != YYERRCODE) correctErrorPosition(); \
  CCopasiMessage(CCopasiMessage::ERROR, MCFunction + 1, mPosition)

#include "copasi.h"
#include "CEvaluationNode.h"
#include "CEvaluationLexer.h"

#line 28 "CEvaluationParser_yacc.cpp"
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
const short yylhs[] =
  {
    -1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
    3, 4, 4, 4, 4, 2, 2, 2, 2, 5,
    5, 5,
  };
const short yylen[] =
  {
    2,
    1, 1, 3, 3, 3, 3, 3, 4, 2, 8,
    1, 1, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 2, 2,
    2, 2, 2, 3, 3, 6, 4, 4, 4, 4,
    3, 3,
  };
const short yydefred[] =
  {
    0,
    1, 2, 0, 0, 0, 0, 0, 0, 11, 0,
    0, 0, 9, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 12, 0, 0, 0, 0,
    7, 0, 0, 0, 0, 30, 0, 33, 41, 0,
    42, 0, 0, 31, 0, 37, 8, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 38, 39, 0, 35, 0, 28, 0, 0,
    0, 18, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 20, 0, 36, 0, 0, 10,
  };
const short yydgoto[] =
  {
    29,
    30, 9, 22, 23, 10,
  };
const short yysindex[] =
  {
    -147,
    0, 0, -276, -271, -147, -266, -147, 92, 0, -213,
    -229, -147, 0, -160, -259, -147, -147, -147, -147, -186,
    -136, -264, -230, -267, -116, 0, -160, -160, -89, 80,
    0, -195, -195, -225, -124, 0, 92, 0, 0, -249,
    0, -172, -213, 0, -164, 0, 0, -215, -140, -21,
    -160, -160, -147, -147, -147, -147, -160, -160, -160, -160,
    -160, -147, 0, 0, 92, 0, -151, 0, -84, -187,
    -68, 0, 92, 92, 92, 92, 91, -105, -152, -84,
    -187, -68, 0, -108, 0, -147, -112, 0,
  };
const short yyrindex[] =
  {
    0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 21, 35, 49, 0, -191, 0, 0, 0,
    0, 0, 0, 0, -176, 0, 0, -138, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -55, 0, 0, 0, -193, -13,
    -110, 0, -70, -57, -52, -39, -250, -165, -26, 63,
    67, -34, 0, 0, 0, 0, 0, 0,
  };
const short yygindex[] =
  {
    8,
    -18, 0, -20, 0, 0,
  };
#define YYTABLESIZE 364
const short yytable[] =
  {
    38,
    6, 11, 16, 17, 18, 19, 12, 8, 48, 50,
    45, 14, 13, 46, 15, 41, 42, 21, 25, 25,
    5, 31, 66, 32, 33, 34, 35, 37, 24, 25,
    25, 63, 70, 72, 4, 49, 16, 17, 77, 78,
    79, 81, 83, 1, 2, 3, 4, 5, 3, 43,
    65, 44, 6, 57, 58, 59, 60, 61, 69, 71,
    73, 74, 75, 76, 7, 20, 16, 80, 82, 84,
    1, 2, 3, 4, 5, 13, 13, 13, 13, 6,
    40, 40, 40, 40, 40, 61, 13, 13, 32, 40,
    32, 7, 20, 87, 0, 36, 1, 2, 3, 4,
    5, 40, 40, 26, 26, 6, 26, 27, 64, 1,
    2, 3, 4, 5, 26, 26, 67, 28, 6, 60,
    61, 16, 17, 18, 19, 16, 17, 18, 19, 85,
    7, 51, 52, 53, 54, 55, 56, 16, 17, 18,
    31, 29, 29, 39, 40, 16, 17, 18, 19, 16,
    17, 18, 19, 16, 17, 18, 19, 0, 17, 17,
    17, 17, 17, 0, 47, 59, 60, 61, 88, 17,
    17, 86, 16, 17, 18, 19, 0, 16, 17, 18,
    19, 0, 51, 52, 53, 54, 55, 56, 52, 53,
    54, 55, 56, 16, 17, 18, 19, 0, 21, 21,
    21, 21, 21, 0, 0, 53, 54, 55, 56, 21,
    21, 22, 22, 22, 22, 22, 23, 23, 23, 23,
    23, 0, 22, 22, 34, 0, 34, 23, 23, 24,
    24, 24, 24, 24, 19, 19, 19, 19, 19, 0,
    24, 24, 27, 27, 27, 19, 19, 57, 58, 59,
    60, 61, 0, 27, 27, 14, 14, 14, 14, 68,
    0, 0, 0, 6, 6, 6, 14, 14, 0, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 0, 0,
    6, 6, 6, 5, 5, 5, 0, 0, 0, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 4, 4,
    5, 5, 5, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 0, 3, 4, 4, 4, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 0, 0, 3, 3,
    3, 15, 15, 15, 15, 16, 16, 16, 16, 0,
    0, 0, 15, 15, 0, 0, 16, 16, 57, 58,
    59, 60, 61, 16, 17, 18, 19, 0, 0, 62,
    58, 59, 60, 61,
  };
const short yycheck[] =
  {
    20,
    0, 278, 262, 263, 264, 265, 278, 0, 27, 28,
    278, 278, 5, 281, 7, 280, 281, 10, 269, 12,
    0, 281, 43, 16, 17, 18, 19, 20, 258, 280,
    281, 281, 51, 52, 0, 28, 262, 263, 57, 58,
    59, 60, 61, 257, 258, 259, 260, 261, 0, 280,
    43, 282, 266, 269, 270, 271, 272, 273, 51, 52,
    53, 54, 55, 56, 278, 279, 262, 60, 61, 62,
    257, 258, 259, 260, 261, 269, 270, 271, 272, 266,
    257, 258, 259, 260, 261, 273, 280, 281, 280, 266,
    282, 278, 279, 86, -1, 282, 257, 258, 259, 260,
    261, 278, 279, 269, 270, 266, 267, 268, 281, 257,
    258, 259, 260, 261, 280, 281, 281, 278, 266, 272,
    273, 262, 263, 264, 265, 262, 263, 264, 265, 281,
    278, 272, 273, 274, 275, 276, 277, 262, 263, 264,
    281, 280, 281, 280, 281, 262, 263, 264, 265, 262,
    263, 264, 265, 262, 263, 264, 265, -1, 269, 270,
    271, 272, 273, -1, 281, 271, 272, 273, 281, 280,
    281, 280, 262, 263, 264, 265, -1, 262, 263, 264,
    265, -1, 272, 273, 274, 275, 276, 277, 273, 274,
    275, 276, 277, 262, 263, 264, 265, -1, 269, 270,
    271, 272, 273, -1, -1, 274, 275, 276, 277, 280,
    281, 269, 270, 271, 272, 273, 269, 270, 271, 272,
    273, -1, 280, 281, 280, -1, 282, 280, 281, 269,
    270, 271, 272, 273, 269, 270, 271, 272, 273, -1,
    280, 281, 269, 270, 271, 280, 281, 269, 270, 271,
    272, 273, -1, 280, 281, 269, 270, 271, 272, 281,
    -1, -1, -1, 263, 264, 265, 280, 281, -1, 269,
    270, 271, 272, 273, 274, 275, 276, 277, -1, -1,
    280, 281, 282, 263, 264, 265, -1, -1, -1, 269,
    270, 271, 272, 273, 274, 275, 276, 277, 264, 265,
    280, 281, 282, 269, 270, 271, 272, 273, 274, 275,
    276, 277, -1, 265, 280, 281, 282, 269, 270, 271,
    272, 273, 274, 275, 276, 277, -1, -1, 280, 281,
    282, 269, 270, 271, 272, 269, 270, 271, 272, -1,
    -1, -1, 280, 281, -1, -1, 280, 281, 269, 270,
    271, 272, 273, 262, 263, 264, 265, -1, -1, 280,
    270, 271, 272, 273,
  };
#define YYFINAL 8
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 282
#if YYDEBUG
const char * const yyname[] =
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
const char * const yyrule[] =
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
    "call : TOKEN_CALL TOKEN_STRUCTURE_OPEN TOKEN_VARIABLE TOKEN_STRUCTURE_OPEN TOKEN_STRUCTURE_CLOSE TOKEN_STRUCTURE_CLOSE",
    "call : TOKEN_CALL TOKEN_STRUCTURE_OPEN TOKEN_VARIABLE TOKEN_STRUCTURE_CLOSE",
    "call : cstart exp TOKEN_STRUCTURE_CLOSE TOKEN_STRUCTURE_CLOSE",
    "call : cstart vector TOKEN_STRUCTURE_CLOSE TOKEN_STRUCTURE_CLOSE",
    "cstart : TOKEN_CALL TOKEN_STRUCTURE_OPEN TOKEN_VARIABLE TOKEN_STRUCTURE_OPEN",
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
#line 361 "CEvaluationParser.ypp"

#line 288 "CEvaluationParser_yacc.cpp" 
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
yyYaccParser::yyparse (YYPARSE_PARAM_ARG)
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
#line 76 "CEvaluationParser.ypp"
      {
        mpRootNode = yyvsp[0];
        }
        break;
      case 2:
#line 80 "CEvaluationParser.ypp"
        {
          mpRootNode = yyvsp[0];
        }
        break;
      case 3:
#line 84 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 4:
#line 91 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 5:
#line 98 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 6:
#line 105 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 7:
#line 112 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          mpRootNode = yyval;
        }
        break;
      case 8:
#line 117 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -3];
          yyval->addChild(yyvsp[ -1]);
          mpRootNode = yyval;
        }
        break;
      case 9:
#line 123 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 10:
#line 129 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -7];
          yyval->addChild(yyvsp[ -5]);
          yyval->addChild(yyvsp[ -3]);
          yyval->addChild(yyvsp[ -1]);
          mpRootNode = yyval;
        }
        break;
      case 11:
#line 137 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[0];
          mpRootNode = yyval;
        }
        break;
      case 12:
#line 143 "CEvaluationParser.ypp"
        {
          mpRootNode = yyvsp[0];
        }
        break;
      case 13:
#line 147 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 14:
#line 154 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 15:
#line 161 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 16:
#line 168 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 17:
#line 175 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 18:
#line 182 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 19:
#line 189 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 20:
#line 196 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 21:
#line 203 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 22:
#line 210 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 23:
#line 217 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 24:
#line 224 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 25:
#line 231 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 26:
#line 238 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 27:
#line 245 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 28:
#line 252 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          mpRootNode = yyval;
        }
        break;
      case 29:
#line 257 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 30:
#line 264 "CEvaluationParser.ypp"
        {
          yyval = new CEvaluationNodeVector();
          mpNodeList->push_back(yyval);
        }
        break;
      case 31:
#line 269 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
        }
        break;
      case 32:
#line 275 "CEvaluationParser.ypp"
        {
          yyval = new CEvaluationNodeVector();
          mpNodeList->push_back(yyval);
          yyval->addChild(yyvsp[0]);
        }
        break;
      case 33:
#line 281 "CEvaluationParser.ypp"
        {
          yyval = new CEvaluationNodeVector();
          mpNodeList->push_back(yyval);
          yyval->addChild(yyvsp[0]);
        }
        break;
      case 34:
#line 287 "CEvaluationParser.ypp"
        {
          yyval->addChild(yyvsp[0]);
        }
        break;
      case 35:
#line 291 "CEvaluationParser.ypp"
        {
          yyval->addChild(yyvsp[0]);
        }
        break;
      case 36:
#line 296 "CEvaluationParser.ypp"
        {
          yyval = new CEvaluationNodeCall(CEvaluationNodeCall::FUNCTION, "call");
          ((CEvaluationNodeCall *)(yyval))->setEvaluationTreeName(yyvsp[ -3]->getData());

          /* Correct the node list: */
          /* 1) set the pointer for token call correctly.*/
          /* 2) remove the token variable node.*/
          std::vector<CEvaluationNode *>::iterator it = mpNodeList->begin();
          while (*it != yyvsp[ -3]) ++it;
          *(it - 2) = yyval;
          pdelete(*it)
          mpNodeList->erase(it);
        }
        break;
      case 37:
#line 310 "CEvaluationParser.ypp"
        {
          yyval = new CEvaluationNodeCall(CEvaluationNodeCall::EXPRESSION, "call");
          ((CEvaluationNodeCall *)(yyval))->setEvaluationTreeName(yyvsp[ -1]->getData());

          /* Correct the node list: */
          /* 1) set the pointer for token call correctly.*/
          /* 2) remove the token variable node.*/
          std::vector<CEvaluationNode *>::iterator it = mpNodeList->begin();
          while (*it != yyvsp[ -1]) ++it;
          *(it - 2) = yyval;
          pdelete(*it)
          mpNodeList->erase(it);
        }
        break;
      case 38:
#line 324 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -3];
          ((CEvaluationNodeCall *)(yyval))->addChild(yyvsp[ -2]);
        }
        break;
      case 39:
#line 329 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -3];
          ((CEvaluationNodeCall *)(yyval))->addChild(yyvsp[ -2]);
        }
        break;
      case 40:
#line 335 "CEvaluationParser.ypp"
        {
          yyval = new CEvaluationNodeCall(CEvaluationNodeCall::FUNCTION, "call");
          ((CEvaluationNodeCall *)(yyval))->setEvaluationTreeName(yyvsp[ -1]->getData());

          /* Correct the node list: */
          /* 1) set the pointer for token call correctly.*/
          /* 2) remove the token variable node.*/
          std::vector<CEvaluationNode *>::iterator it = mpNodeList->begin();
          while (*it != yyvsp[ -1]) ++it;
          *(it - 2) = yyval;
          pdelete(*it)
          mpNodeList->erase(it);
        }
        break;
      case 41:
#line 349 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -2];
          ((CEvaluationNodeCall *)(yyval))->addChild(yyvsp[ -1]);
        }
        break;
      case 42:
#line 354 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -2];
          ((CEvaluationNodeCall *)(yyval))->addChild(yyvsp[ -1]);
        }
        break;
#line 844 "CEvaluationParser_yacc.cpp"
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
