/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationParser_yacc.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/24 15:44:37 $
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
#line 27 "CEvaluationParser_yacc.cpp"
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
    0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1,
  };
const short yylen[] =
  {
    2,
    1, 3, 3, 3, 3, 3, 4, 2, 8, 0,
    2, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 2,
  };
const short yydefred[] =
  {
    0,
    1, 0, 0, 0, 0, 0, 0, 8, 0, 0,
    0, 0, 0, 0, 0, 10, 0, 0, 0, 0,
    6, 0, 0, 0, 0, 7, 11, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 23, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 19, 0, 0, 0, 9,
  };
const short yydgoto[] =
  {
    19,
    20, 27,
  };
const short yysindex[] =
  {
    -251,
    0, -276, -251, -261, -251, -258, -251, 0, -205, -188,
    -251, -251, -251, -251, -175, 0, -205, -205, -156, -79,
    0, -243, -243, -178, -198, 0, 0, -74, -194, -96,
    -251, -251, -251, -251, -251, -251, -205, -205, -205, -205,
    -205, -251, 0, -258, -258, -258, -258, -258, -258, -213,
    -137, -121, -247, 0, -165, -251, -169, 0,
  };
const short yyrindex[] =
  {
    0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 19, 36, 49, 0, 0, -111, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -147, -142, -130, -125, -113, -108, -249,
    -167, -230, -91, 0, 0, 0, 0, 0,
  };
const short yygindex[] =
  {
    9,
    -7, 0,
  };
#define YYTABLESIZE 327
const short yytable[] =
  {
    7,
    5, 11, 12, 13, 14, 1, 2, 3, 6, 28,
    30, 8, 4, 10, 9, 15, 11, 20, 4, 22,
    23, 24, 25, 41, 5, 0, 29, 20, 20, 50,
    51, 52, 53, 54, 0, 3, 22, 22, 22, 44,
    45, 46, 47, 48, 49, 0, 22, 22, 2, 0,
    55, 1, 2, 3, 38, 39, 40, 41, 4, 16,
    17, 11, 12, 13, 57, 11, 12, 13, 14, 0,
    18, 11, 12, 13, 14, 31, 32, 33, 34, 35,
    36, 11, 12, 21, 11, 12, 13, 14, 0, 21,
    11, 12, 13, 14, 11, 12, 13, 14, 0, 21,
    21, 0, 26, 11, 12, 13, 14, 0, 58, 21,
    21, 56, 0, 31, 32, 33, 34, 35, 36, 12,
    12, 12, 12, 12, 13, 13, 13, 13, 13, 12,
    12, 39, 40, 41, 13, 13, 14, 14, 14, 14,
    14, 15, 15, 15, 15, 15, 14, 14, 40, 41,
    0, 15, 15, 16, 16, 16, 16, 16, 17, 17,
    17, 17, 17, 16, 16, 24, 24, 0, 17, 17,
    37, 38, 39, 40, 41, 18, 18, 18, 18, 0,
    0, 43, 0, 0, 0, 18, 18, 37, 38, 39,
    40, 41, 37, 38, 39, 40, 41, 42, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
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
    0, 260, 261, 262, 263, 257, 258, 259, 0, 17,
    18, 3, 264, 5, 276, 7, 260, 267, 0, 11,
    12, 13, 14, 271, 276, -1, 18, 277, 278, 37,
    38, 39, 40, 41, -1, 0, 267, 268, 269, 31,
    32, 33, 34, 35, 36, -1, 277, 278, 0, -1,
    42, 257, 258, 259, 268, 269, 270, 271, 264, 265,
    266, 260, 261, 262, 56, 260, 261, 262, 263, -1,
    276, 260, 261, 262, 263, 270, 271, 272, 273, 274,
    275, 260, 261, 278, 260, 261, 262, 263, -1, 278,
    260, 261, 262, 263, 260, 261, 262, 263, -1, 267,
    268, -1, 278, 260, 261, 262, 263, -1, 278, 277,
    278, 277, -1, 270, 271, 272, 273, 274, 275, 267,
    268, 269, 270, 271, 267, 268, 269, 270, 271, 277,
    278, 269, 270, 271, 277, 278, 267, 268, 269, 270,
    271, 267, 268, 269, 270, 271, 277, 278, 270, 271,
    -1, 277, 278, 267, 268, 269, 270, 271, 267, 268,
    269, 270, 271, 277, 278, 277, 278, -1, 277, 278,
    267, 268, 269, 270, 271, 267, 268, 269, 270, -1,
    -1, 278, -1, -1, -1, 277, 278, 267, 268, 269,
    270, 271, 267, 268, 269, 270, 271, 277, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
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
    "$$1 :",
    "bool : TOKEN_LOGICAL_VALUE $$1",
    "bool : exp TOKEN_LOGICAL_EQ exp",
    "bool : exp TOKEN_LOGICAL_NE exp",
    "bool : exp TOKEN_LOGICAL_GT exp",
    "bool : exp TOKEN_LOGICAL_GE exp",
    "bool : exp TOKEN_LOGICAL_LT exp",
    "bool : exp TOKEN_LOGICAL_LE exp",
    "bool : bool TOKEN_LOGICAL_EQ bool",
    "bool : bool TOKEN_LOGICAL_NE bool",
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
#line 217 "CEvaluationParser.ypp"

#line 243 "CEvaluationParser_yacc.cpp" 
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
#line 69 "CEvaluationParser.ypp"
    {mpRootNode = yyvsp[0];}
        break;
      case 2:
#line 71 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 3:
#line 78 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 4:
#line 85 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 5:
#line 92 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 6:
#line 99 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          mpRootNode = yyval;
        }
        break;
      case 7:
#line 104 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -3];
          yyval->addChild(yyvsp[ -1]);
          mpRootNode = yyval;
        }
        break;
      case 8:
#line 110 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 9:
#line 116 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -7];
          yyval->addChild(yyvsp[ -6]);
          yyval->addChild(yyvsp[ -4]);
          yyval->addChild(yyvsp[ -2]);
          mpRootNode = yyval;
        }
        break;
      case 10:
#line 124 "CEvaluationParser.ypp"
      {mpRootNode = yyvsp[0];}
        break;
      case 11:
#line 125 "CEvaluationParser.ypp"
      {}
        break;
      case 12:
#line 127 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 13:
#line 134 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 14:
#line 141 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 15:
#line 148 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 16:
#line 155 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 17:
#line 162 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 18:
#line 169 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 19:
#line 176 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 20:
#line 183 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 21:
#line 190 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 22:
#line 197 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 23:
#line 204 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          mpRootNode = yyval;
        }
        break;
      case 24:
#line 209 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
#line 633 "CEvaluationParser_yacc.cpp"
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
