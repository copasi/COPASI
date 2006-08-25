/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEqParser_yacc.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/25 18:13:23 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
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
#define yyparse yyparse
#define yyerror CChemEqParsererror
#define yychar CChemEqParserchar
#define yyval CChemEqParserval
#define yylval CChemEqParserlval
#define yydebug CChemEqParserdebug
#define yynerrs CChemEqParsernerrs
#define yyerrflag CChemEqParsererrflag
#define yyss CChemEqParserss
#define yyssp CChemEqParserssp
#define yyvs CChemEqParservs
#define yyvsp CChemEqParservsp
#define yylhs CChemEqParserlhs
#define yylen CChemEqParserlen
#define yydefred CChemEqParserdefred
#define yydgoto CChemEqParserdgoto
#define yysindex CChemEqParsersindex
#define yyrindex CChemEqParserrindex
#define yygindex CChemEqParsergindex
#define yytable CChemEqParsertable
#define yycheck CChemEqParsercheck
#define yyname CChemEqParsername
#define yyrule CChemEqParserrule
#define yysslim CChemEqParsersslim
#define yystacksize CChemEqParserstacksize
#define YYPREFIX "CChemEqParser"
#line 5 "CChemEqParser.ypp"

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

#undef yyparse
#define yyparse CChemEqParserBase::yyparse
#line 66 "CChemEqParser_yacc.cpp"
#define YYERRCODE 256
#define TOKEN_NUMBER 257
#define TOKEN_MULTIPLY 258
#define TOKEN_PLUS 259
#define TOKEN_NAME 260
#define TOKEN_BEGIN_PRODUCTS 261
#define TOKEN_BEGIN_MODIFIERS 262
#define TOKEN_BEGIN_COMPARTMENT 263
#define TOKEN_END_COMPARTMENT 264
const short CChemEqParserlhs[] =
  {
    -1,
    0, 0, 0, 0, 0, 0, 1, 1, 2, 2,
    3, 3, 4, 4, 5, 5, 5, 6,
  };
const short CChemEqParserlen[] =
  {
    2,
    3, 3, 2, 2, 2, 1, 1, 3, 2, 3,
    2, 2, 1, 2, 1, 2, 3, 3,
  };
const short CChemEqParserdefred[] =
  {
    0,
    0, 15, 0, 0, 0, 0, 7, 0, 0, 16,
    9, 0, 0, 0, 0, 0, 0, 0, 14, 17,
    8, 0, 0, 10, 11, 12, 0, 18,
  };
const short CChemEqParserdgoto[] =
  {
    4,
    5, 6, 17, 26, 8, 19,
  };
const short CChemEqParsersindex[] =
  {
    -250,
    -239, 0, -248, 0, -237, -246, 0, -263, -256, 0,
    0, -248, -254, -246, -248, -248, -248, -240, 0, 0,
    0, -248, -248, 0, 0, 0, -241, 0,
  };
const short CChemEqParserrindex[] =
  {
    0,
    0, 0, 0, 0, 0, 27, 0, 1, 0, 0,
    0, 0, 28, 29, 0, 0, 30, 0, 0, 0,
    0, 31, 32, 0, 0, 0, 0, 0,
  };
const short CChemEqParsergindex[] =
  {
    0,
    0, 33, 12, 2, 0, 0,
  };
#define YYTABLESIZE 263
const short CChemEqParsertable[] =
  {
    18,
    13, 7, 1, 20, 11, 2, 1, 16, 1, 2,
    3, 2, 15, 21, 11, 16, 24, 25, 9, 27,
    10, 12, 28, 13, 22, 23, 6, 4, 3, 5,
    2, 1, 0, 0, 0, 0, 0, 14, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 13, 0, 13,
    13, 13, 13,
  };
const short CChemEqParsercheck[] =
  {
    263,
    0, 0, 257, 260, 3, 260, 257, 262, 257, 260,
    261, 260, 259, 12, 13, 262, 15, 16, 258, 260,
    260, 259, 264, 261, 13, 14, 0, 0, 0, 0,
    0, 0, -1, -1, -1, -1, -1, 5, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, 257, -1, 259,
    260, 261, 262,
  };
#define YYFINAL 4
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 264
#if YYDEBUG
const char * const CChemEqParsername[] =
  {
    "end-of-file", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "TOKEN_NUMBER", "TOKEN_MULTIPLY",
    "TOKEN_PLUS", "TOKEN_NAME", "TOKEN_BEGIN_PRODUCTS", "TOKEN_BEGIN_MODIFIERS",
    "TOKEN_BEGIN_COMPARTMENT", "TOKEN_END_COMPARTMENT",
  };
const char * const CChemEqParserrule[] =
  {
    "$accept : reaction",
    "reaction : substrates products modifiers",
    "reaction : substrates TOKEN_BEGIN_PRODUCTS modifiers",
    "reaction : substrates products",
    "reaction : substrates TOKEN_BEGIN_PRODUCTS",
    "reaction : products modifiers",
    "reaction : products",
    "substrates : reactant",
    "substrates : substrates TOKEN_PLUS reactant",
    "products : TOKEN_BEGIN_PRODUCTS reactant",
    "products : products TOKEN_PLUS reactant",
    "modifiers : TOKEN_BEGIN_MODIFIERS reactant",
    "modifiers : modifiers reactant",
    "reactant : prereactant",
    "reactant : prereactant compartment",
    "prereactant : TOKEN_NAME",
    "prereactant : TOKEN_NUMBER TOKEN_NAME",
    "prereactant : TOKEN_NUMBER TOKEN_MULTIPLY TOKEN_NAME",
    "compartment : TOKEN_BEGIN_COMPARTMENT TOKEN_NAME TOKEN_END_COMPARTMENT",
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
#line 164 "CChemEqParser.ypp"

#line 235 "CChemEqParser_yacc.cpp"
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
#line 47 "CChemEqParser.ypp"
      {
      }
      break;
    case 2:
#line 50 "CChemEqParser.ypp"
      {
        mReversibility = (yyvsp[ -1]->name == "=") ? true : false;
          pdelete(yyvsp[ -1]);
        }
        break;
      case 3:
#line 55 "CChemEqParser.ypp"
        {
        }
        break;
      case 4:
#line 58 "CChemEqParser.ypp"
        {
          mReversibility = (yyvsp[0]->name == "=") ? true : false;
          pdelete(yyvsp[0]);
        }
        break;
      case 5:
#line 63 "CChemEqParser.ypp"
        {
        }
        break;
      case 6:
#line 67 "CChemEqParser.ypp"
        {
        }
        break;
      case 7:
#line 71 "CChemEqParser.ypp"
        {
          mSubstrateNames.push_back(yyvsp[0]->name);
          mSubstrateMult.push_back(yyvsp[0]->multiplicity);
          mSubstrateCompartments.push_back(yyvsp[0]->compartment);
          pdelete(yyvsp[0]);
        }
        break;
      case 8:
#line 78 "CChemEqParser.ypp"
        {
          mSubstrateNames.push_back(yyvsp[0]->name);
          mSubstrateMult.push_back(yyvsp[0]->multiplicity);
          mSubstrateCompartments.push_back(yyvsp[0]->compartment);
          pdelete(yyvsp[ -1]);
          pdelete(yyvsp[0]);
        }
        break;
      case 9:
#line 87 "CChemEqParser.ypp"
        {
          mReversibility = (yyvsp[ -1]->name == "=") ? true : false;

          mProductNames.push_back(yyvsp[0]->name);
          mProductMult.push_back(yyvsp[0]->multiplicity);
          mProductCompartments.push_back(yyvsp[0]->compartment);
          pdelete(yyvsp[ -1]);
          pdelete(yyvsp[0]);
        }
        break;
      case 10:
#line 97 "CChemEqParser.ypp"
        {
          mProductNames.push_back(yyvsp[0]->name);
          mProductMult.push_back(yyvsp[0]->multiplicity);
          mProductCompartments.push_back(yyvsp[0]->compartment);
          pdelete(yyvsp[ -1]);
          pdelete(yyvsp[0]);
        }
        break;
      case 11:
#line 106 "CChemEqParser.ypp"
        {
          mModifierNames.push_back(yyvsp[0]->name);
          mModifierMult.push_back(yyvsp[0]->multiplicity);
          mModifierCompartments.push_back(yyvsp[0]->compartment);
          pdelete(yyvsp[ -1]);
          pdelete(yyvsp[0]);
        }
        break;
      case 12:
#line 114 "CChemEqParser.ypp"
        {
          mModifierNames.push_back(yyvsp[0]->name);
          mModifierMult.push_back(yyvsp[0]->multiplicity);
          mModifierCompartments.push_back(yyvsp[0]->compartment);
          pdelete(yyvsp[0]);
        }
        break;
      case 13:
#line 122 "CChemEqParser.ypp"
        {
          yyval = yyvsp[0];
          yyval->multiplicity = 1.0;
          yyval->compartment = "";
        }
        break;
      case 14:
#line 128 "CChemEqParser.ypp"
        {
          yyval = yyvsp[ -1];
          yyval->multiplicity = 1.0;
          yyval->compartment = yyvsp[0]->name;
          pdelete(yyvsp[0]);
        }
        break;
      case 15:
#line 137 "CChemEqParser.ypp"
        {
          yyval = yyvsp[0];
          yyval->multiplicity = 1.0;
        }
        break;
      case 16:
#line 142 "CChemEqParser.ypp"
        {
          yyval = yyvsp[0];
          yyval->multiplicity = strtod(yyvsp[ -1]->name.c_str(), NULL);
          pdelete(yyvsp[ -1]);
        }
        break;
      case 17:
#line 148 "CChemEqParser.ypp"
        {
          yyval = yyvsp[0];
          yyval->multiplicity = strtod(yyvsp[ -2]->name.c_str(), NULL);
          pdelete(yyvsp[ -2]);
          pdelete(yyvsp[ -1]);
        }
        break;
      case 18:
#line 156 "CChemEqParser.ypp"
        {
          yyval = yyvsp[ -1];
          pdelete(yyvsp[ -2]);
          pdelete(yyvsp[0]);
        }
        break;
#line 573 "CChemEqParser_yacc.cpp"
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
