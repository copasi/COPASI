/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationParser_yacc.cpp,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/24 19:19:28 $
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
#define TOKEN_FUNCTION 258
#define TOKEN_SIGN 259
#define TOKEN_OPERATOR_POWER 260
#define TOKEN_OPERATOR_MULTIPLY 261
#define TOKEN_OPERATOR_MODULUS 262
#define TOKEN_OPERATOR_PLUS 263
#define TOKEN_LOGICAL_CHOICE 264
#define TOKEN_LOGICAL_VALUE 265
#define TOKEN_LOGICAL_NOT 266
#define TOKEN_LOGICAL_OR 267
#define TOKEN_LOGICAL_XOR 268
#define TOKEN_LOGICAL_AND 269
#define TOKEN_LOGICAL_EQ 270
#define TOKEN_LOGICAL_NE 271
#define TOKEN_LOGICAL_GT 272
#define TOKEN_LOGICAL_GE 273
#define TOKEN_LOGICAL_LT 274
#define TOKEN_LOGICAL_LE 275
#define TOKEN_STRUCTURE_OPEN 276
#define TOKEN_STRUCTURE_COMMA 277
#define TOKEN_STRUCTURE_CLOSE 278
const short yylhs[] =
  {
    -1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1,
  };
const short yylen[] =
  {
    2,
    1, 3, 3, 3, 3, 3, 4, 2, 8, 1,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 2,
  };
const short yydefred[] =
  {
    0,
    1, 0, 0, 0, 0, 0, 0, 8, 0, 0,
    0, 0, 0, 0, 0, 10, 0, 0, 0, 0,
    6, 0, 0, 0, 0, 7, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 26, 0, 0, 0, 16, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 18, 0, 0, 0,
    9,
  };
const short yydgoto[] =
  {
    19,
    20,
  };
const short yysindex[] =
  {
    -255,
    0, -276, -255, -266, -255, -3, -255, 0, -199, -170,
    -255, -255, -255, -255, -166, 0, -199, -199, -140, -26,
    0, -245, -245, -248, -198, 0, -15, -189, -69, -199,
    -199, -255, -255, -255, -255, -199, -199, -199, -199, -199,
    -255, 0, -135, -254, -119, 0, -3, -3, -3, -3,
    -263, -191, -238, -135, -254, -119, 0, -158, -255, -162,
    0,
  };
const short yyrindex[] =
  {
    0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 19, 36, 49, 0, -209, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -62, -57, -120, 0, -108, -103, -91, -86,
    -247, -240, -29, -45, -41, -74, 0, 0, 0, 0,
    0,
  };
const short yygindex[] =
  {
    11,
    17,
  };
#define YYTABLESIZE 327
const short yytable[] =
  {
    7,
    5, 1, 2, 3, 37, 38, 39, 40, 4, 9,
    6, 11, 12, 8, 11, 10, 40, 15, 4, 23,
    5, 22, 23, 24, 25, 0, 24, 24, 28, 23,
    23, 39, 40, 27, 29, 3, 24, 24, 0, 0,
    43, 45, 47, 48, 49, 50, 44, 46, 2, 54,
    56, 58, 51, 52, 53, 55, 57, 1, 2, 3,
    0, 11, 12, 13, 4, 16, 17, 27, 27, 60,
    11, 12, 13, 14, 0, 0, 18, 38, 39, 40,
    30, 31, 32, 33, 34, 35, 0, 0, 21, 11,
    12, 13, 14, 11, 12, 13, 14, 11, 12, 13,
    14, 11, 12, 13, 14, 0, 0, 21, 0, 0,
    0, 26, 0, 0, 0, 61, 0, 0, 59, 11,
    12, 13, 14, 0, 11, 12, 13, 14, 0, 30,
    31, 32, 33, 34, 35, 31, 32, 33, 34, 35,
    11, 12, 13, 14, 0, 0, 15, 15, 15, 15,
    15, 0, 32, 33, 34, 35, 15, 15, 19, 19,
    19, 19, 19, 20, 20, 20, 20, 20, 19, 19,
    0, 0, 0, 20, 20, 21, 21, 21, 21, 21,
    22, 22, 22, 22, 22, 21, 21, 0, 0, 0,
    22, 22, 17, 17, 17, 17, 17, 36, 37, 38,
    39, 40, 17, 17, 11, 11, 11, 11, 42, 12,
    12, 12, 12, 0, 11, 11, 0, 0, 0, 12,
    12, 13, 13, 13, 13, 14, 14, 14, 14, 0,
    0, 13, 13, 0, 0, 14, 14, 25, 25, 25,
    36, 37, 38, 39, 40, 0, 0, 25, 25, 0,
    41, 36, 37, 38, 39, 40, 11, 12, 13, 14,
    0, 5, 5, 5, 0, 0, 0, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 0, 5, 5, 4,
    4, 4, 0, 0, 0, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 0, 4, 4, 3, 3, 0,
    0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 2, 3, 3, 0, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 0, 2, 2,
  };
const short yycheck[] =
  {
    276,
    0, 257, 258, 259, 268, 269, 270, 271, 264, 276,
    0, 260, 261, 3, 260, 5, 271, 7, 0, 267,
    276, 11, 12, 13, 14, -1, 267, 268, 18, 277,
    278, 270, 271, 17, 18, 0, 277, 278, -1, -1,
    30, 31, 32, 33, 34, 35, 30, 31, 0, 39,
    40, 41, 36, 37, 38, 39, 40, 257, 258, 259,
    -1, 260, 261, 262, 264, 265, 266, 277, 278, 59,
    260, 261, 262, 263, -1, -1, 276, 269, 270, 271,
    270, 271, 272, 273, 274, 275, -1, -1, 278, 260,
    261, 262, 263, 260, 261, 262, 263, 260, 261, 262,
    263, 260, 261, 262, 263, -1, -1, 278, -1, -1,
    -1, 278, -1, -1, -1, 278, -1, -1, 277, 260,
    261, 262, 263, -1, 260, 261, 262, 263, -1, 270,
    271, 272, 273, 274, 275, 271, 272, 273, 274, 275,
    260, 261, 262, 263, -1, -1, 267, 268, 269, 270,
    271, -1, 272, 273, 274, 275, 277, 278, 267, 268,
    269, 270, 271, 267, 268, 269, 270, 271, 277, 278,
    -1, -1, -1, 277, 278, 267, 268, 269, 270, 271,
    267, 268, 269, 270, 271, 277, 278, -1, -1, -1,
    277, 278, 267, 268, 269, 270, 271, 267, 268, 269,
    270, 271, 277, 278, 267, 268, 269, 270, 278, 267,
    268, 269, 270, -1, 277, 278, -1, -1, -1, 277,
    278, 267, 268, 269, 270, 267, 268, 269, 270, -1,
    -1, 277, 278, -1, -1, 277, 278, 267, 268, 269,
    267, 268, 269, 270, 271, -1, -1, 277, 278, -1,
    277, 267, 268, 269, 270, 271, 260, 261, 262, 263,
    -1, 261, 262, 263, -1, -1, -1, 267, 268, 269,
    270, 271, 272, 273, 274, 275, -1, 277, 278, 261,
    262, 263, -1, -1, -1, 267, 268, 269, 270, 271,
    272, 273, 274, 275, -1, 277, 278, 262, 263, -1,
    -1, -1, 267, 268, 269, 270, 271, 272, 273, 274,
    275, 263, 277, 278, -1, 267, 268, 269, 270, 271,
    272, 273, 274, 275, -1, 277, 278,
  };
#define YYFINAL 6
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 278
#if YYDEBUG
const char * const yyname[] =
  {
    "end-of-file", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "TOKEN_NUMBER", "TOKEN_FUNCTION",
    "TOKEN_SIGN", "TOKEN_OPERATOR_POWER", "TOKEN_OPERATOR_MULTIPLY",
    "TOKEN_OPERATOR_MODULUS", "TOKEN_OPERATOR_PLUS", "TOKEN_LOGICAL_CHOICE",
    "TOKEN_LOGICAL_VALUE", "TOKEN_LOGICAL_NOT", "TOKEN_LOGICAL_OR",
    "TOKEN_LOGICAL_XOR", "TOKEN_LOGICAL_AND", "TOKEN_LOGICAL_EQ", "TOKEN_LOGICAL_NE",
    "TOKEN_LOGICAL_GT", "TOKEN_LOGICAL_GE", "TOKEN_LOGICAL_LT", "TOKEN_LOGICAL_LE",
    "TOKEN_STRUCTURE_OPEN", "TOKEN_STRUCTURE_COMMA", "TOKEN_STRUCTURE_CLOSE",
  };
const char * const yyrule[] =
  {
    "$accept : exp",
    "exp : TOKEN_NUMBER",
    "exp : exp TOKEN_OPERATOR_PLUS exp",
    "exp : exp TOKEN_OPERATOR_MODULUS exp",
    "exp : exp TOKEN_OPERATOR_MULTIPLY exp",
    "exp : exp TOKEN_OPERATOR_POWER exp",
    "exp : TOKEN_STRUCTURE_OPEN exp TOKEN_STRUCTURE_CLOSE",
    "exp : TOKEN_FUNCTION TOKEN_STRUCTURE_OPEN exp TOKEN_STRUCTURE_CLOSE",
    "exp : TOKEN_SIGN exp",
    "exp : TOKEN_LOGICAL_CHOICE TOKEN_STRUCTURE_OPEN bool TOKEN_STRUCTURE_COMMA exp TOKEN_STRUCTURE_COMMA exp TOKEN_STRUCTURE_CLOSE",
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
int yydebug = 1;
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
#line 251 "CEvaluationParser.ypp"

#line 250 "CEvaluationParser_yacc.cpp" 
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
#line 71 "CEvaluationParser.ypp"
      {
        mpRootNode = yyvsp[0];
        }
        break;
      case 2:
#line 75 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 3:
#line 82 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 4:
#line 89 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 5:
#line 96 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 6:
#line 103 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          mpRootNode = yyval;
        }
        break;
      case 7:
#line 108 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -3];
          yyval->addChild(yyvsp[ -1]);
          mpRootNode = yyval;
        }
        break;
      case 8:
#line 114 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 9:
#line 120 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -7];
          yyval->addChild(yyvsp[ -5]);
          yyval->addChild(yyvsp[ -3]);
          yyval->addChild(yyvsp[ -1]);
          mpRootNode = yyval;
        }
        break;
      case 10:
#line 129 "CEvaluationParser.ypp"
        {
          mpRootNode = yyvsp[0];
        }
        break;
      case 11:
#line 133 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 12:
#line 140 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
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
          mpRootNode = yyval;
        }
        break;
      case 27:
#line 243 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
#line 676 "CEvaluationParser_yacc.cpp"
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
