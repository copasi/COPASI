/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationParser_yacc.cpp,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/24 15:54:16 $
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
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1,
  };
const short yylen[] =
  {
    2,
    1, 3, 3, 3, 3, 3, 4, 2, 8, 1,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 2,
  };
const short yydefred[] =
  {
    0,
    1, 0, 0, 0, 0, 0, 0, 8, 0, 0,
    0, 0, 0, 0, 0, 10, 0, 0, 0, 0,
    6, 0, 0, 0, 0, 7, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 22, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 18, 0, 0, 0, 9,
  };
const short yydgoto[] =
  {
    19,
    20,
  };
const short yysindex[] =
  {
    -251,
    0, -276, -251, -261, -251, -258, -251, 0, -211, -200,
    -251, -251, -251, -251, -181, 0, -211, -211, -155, -83,
    0, -234, -234, -223, -185, 0, -78, -204, -107, -251,
    -251, -251, -251, -251, -251, -211, -211, -211, -211, -211,
    -251, 0, -258, -258, -258, -258, -258, -258, -157, -136,
    -253, -199, 0, -173, -251, -177, 0,
  };
const short yyrindex[] =
  {
    0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 19, 36, 49, 0, -226, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -175, -146, -141, -129, -124, -112, -243, -168,
    -95, -100, 0, 0, 0, 0, 0,
  };
const short yygindex[] =
  {
    9,
    -7,
  };
#define YYTABLESIZE 327
const short yytable[] =
  {
    7,
    5, 11, 12, 13, 14, 1, 2, 3, 6, 27,
    29, 8, 4, 10, 9, 15, 39, 40, 4, 22,
    23, 24, 25, 19, 5, 11, 28, 0, 49, 50,
    51, 52, 53, 19, 19, 3, 11, 12, 43, 44,
    45, 46, 47, 48, 0, 1, 2, 3, 2, 54,
    23, 23, 4, 16, 17, 11, 12, 13, 14, 11,
    12, 13, 14, 56, 18, 30, 31, 32, 33, 34,
    35, 40, 0, 21, 11, 12, 13, 21, 11, 12,
    13, 14, 11, 12, 13, 14, 11, 12, 13, 14,
    0, 11, 11, 11, 11, 11, 26, 0, 20, 20,
    57, 11, 11, 55, 11, 12, 13, 14, 20, 20,
    37, 38, 39, 40, 30, 31, 32, 33, 34, 35,
    12, 12, 12, 12, 12, 13, 13, 13, 13, 13,
    12, 12, 38, 39, 40, 13, 13, 14, 14, 14,
    14, 14, 15, 15, 15, 15, 15, 14, 14, 0,
    0, 0, 15, 15, 16, 16, 16, 16, 16, 36,
    37, 38, 39, 40, 16, 16, 17, 17, 17, 17,
    42, 21, 21, 21, 0, 0, 17, 17, 0, 0,
    0, 21, 21, 36, 37, 38, 39, 40, 36, 37,
    38, 39, 40, 41, 0, 0, 0, 0, 0, 0,
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
    18, 3, 264, 5, 276, 7, 270, 271, 0, 11,
    12, 13, 14, 267, 276, 260, 18, -1, 36, 37,
    38, 39, 40, 277, 278, 0, 260, 261, 30, 31,
    32, 33, 34, 35, -1, 257, 258, 259, 0, 41,
    277, 278, 264, 265, 266, 260, 261, 262, 263, 260,
    261, 262, 263, 55, 276, 270, 271, 272, 273, 274,
    275, 271, -1, 278, 260, 261, 262, 278, 260, 261,
    262, 263, 260, 261, 262, 263, 260, 261, 262, 263,
    -1, 267, 268, 269, 270, 271, 278, -1, 267, 268,
    278, 277, 278, 277, 260, 261, 262, 263, 277, 278,
    268, 269, 270, 271, 270, 271, 272, 273, 274, 275,
    267, 268, 269, 270, 271, 267, 268, 269, 270, 271,
    277, 278, 269, 270, 271, 277, 278, 267, 268, 269,
    270, 271, 267, 268, 269, 270, 271, 277, 278, -1,
    -1, -1, 277, 278, 267, 268, 269, 270, 271, 267,
    268, 269, 270, 271, 277, 278, 267, 268, 269, 270,
    278, 267, 268, 269, -1, -1, 277, 278, -1, -1,
    -1, 277, 278, 267, 268, 269, 270, 271, 267, 268,
    269, 270, 271, 277, -1, -1, -1, -1, -1, -1,
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
    "bool : TOKEN_LOGICAL_VALUE",
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
#line 219 "CEvaluationParser.ypp"

#line 242 "CEvaluationParser_yacc.cpp" 
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
#line 125 "CEvaluationParser.ypp"
        {
          mpRootNode = yyvsp[0];
        }
        break;
      case 11:
#line 129 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 12:
#line 136 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 13:
#line 143 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 14:
#line 150 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 15:
#line 157 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 16:
#line 164 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 17:
#line 171 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 18:
#line 178 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 19:
#line 185 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 20:
#line 192 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 21:
#line 199 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[ -2]);
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
      case 22:
#line 206 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          mpRootNode = yyval;
        }
        break;
      case 23:
#line 211 "CEvaluationParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->addChild(yyvsp[0]);
          mpRootNode = yyval;
        }
        break;
#line 630 "CEvaluationParser_yacc.cpp"
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
