// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

// Written by pwilly on 07.07.08

#include <iostream>

#include <QStringList>
#include <QRegExp>

#include "CStructureParser.h"

#include "CMathMLToTeX.h"

/// replace other operators (eg. .)
void CMathMLToTeX::replaceOtherOperators(QString &text)
{
  text.replace("&CenterDot;", "\\cdot");
}

/// replace logic operators (eg. <=, <, >=, >, and, or)
void CMathMLToTeX::replaceLogicOperators(QString &text)
{
  text.replace("&gt;=", "\\ge");
  text.replace("&gt;", ">");
  text.replace("&lt;=", "\\le");
  text.replace("&lt;", "\\lt");
  text.replace("&NotEqual;", "\\ne");
  text.replace("and", "\\wedge");

  text.replace(" or ", "\\vee");
}

/// replace mathematical operators (eg. inf, log)
void CMathMLToTeX::replaceMathOperators(QString &text)
{
  text.replace("log", "\\log");
  text.replace("ln", "\\ln");
  text.replace("&infin;", "\\infty");
  text.replace("&pi;", "\\pi");
  text.replace("%", "\\%");
}

/// replace trigonometrical operators (eg. inf, log)
void CMathMLToTeX::replaceTrigoOperators(QString &text)
{
  // sin, sinh, asin, arcsinh

  text.replace("arcsinh", "arsoh");
  text.replace("arcsin", "arcso");
  text.replace("sinh", "sooh");

  if (text.length() == 3)  // exactly 'sin' word
    text.replace("sin", "\\sin");

  text.replace("sooh", "sinh");
  text.replace("sinh", "\\sinh");

  text.replace("arcso", "arcsin");
  text.replace("arcsin", "\\arcsin");

  text.replace("arsoh", "arcsinh");

  // cos, cosh, acos, arccosh

  text.replace("arccosh", "arcoh");
  text.replace("arccos", "arcce");
  text.replace("cosh", "cooh");

  if (text.length() == 3)  // exactly 'cos' word
    text.replace("cos", "\\cos");

  text.replace("cooh", "cosh");
  text.replace("cosh", "\\cosh");

  text.replace("arcce", "arccos");
  text.replace("arccos", "\\arccos");

  text.replace("arcoh", "arccosh");

  // tan, tanh, atan, arctanh

  text.replace("arctanh", "artoh");
  text.replace("arctan", "arcto");
  text.replace("tanh", "tooh");

  if (text.length() == 3)  // exactly 'tan' word
    text.replace("tan", "\\tan");

  text.replace("tooh", "tanh");
  text.replace("tanh", "\\tanh");

  text.replace("arcto", "arctan");
  text.replace("arctan", "\\arctan");

  text.replace("artoh", "arctanh");

  // sec, sech, arcsec, arcsech

  text.replace("arcsech", "arsoh");
  text.replace("arcsec", "arcso");
  text.replace("sech", "sooh");

  if (text.length() == 3)  // exactly 'sec' word
    text.replace("sec", "\\sec");

  text.replace("sooh", "sech");
  text.replace("arcso", "arcsec");
  text.replace("arsoh", "arcsech");

  // csc, csch, arccsc, arccsch

  text.replace("arccsch", "arcoh");
  text.replace("arccsc", "arcce");
  text.replace("csch", "cooh");

  if (text.length() == 3)  // exactly 'csc' word
    text.replace("csc", "\\csc");

  text.replace("cooh", "csch");
  text.replace("arcce", "arccsc");
  text.replace("arcoh", "arccsch");

  // cot, coth, arccot, arccoth

  text.replace("arccoth", "arctoh");
  text.replace("arccot", "arcto");
  text.replace("coth", "tooh");

  if (text.length() == 3)  // exactly 'cot' word
    text.replace("cot", "\\cot");

  text.replace("tooh", "coth");
  text.replace("coth", "\\coth");

  text.replace("arcto", "arccot");
  text.replace("arctoh", "arccoth");
}

/// convert to TeX
void CMathMLToTeX::convert(QString &text)
{
  replaceOtherOperators(text);
  replaceLogicOperators(text);
  replaceMathOperators(text);
  replaceTrigoOperators(text);

  if (text.contains("mtable"))
    mtableNode(text);
  else
    {
      if (text.count("<mtable>") > 1)
        {
          text = "The MathML contains <mtable> more than one. Needs more handling.";
          return;
        }

      mNode(text);
    }
}

/// normal equation node
void CMathMLToTeX::mNode(QString &text)
{
  CStructureParser xmlParser(0);
  QXmlSimpleReader xmlReader;

  xmlReader.setContentHandler(&xmlParser);

  QXmlInputSource xmlSource;
  xmlSource.setData(text);

  xmlReader.parse(xmlSource);

  text = xmlParser.getTeX();
}

/// converting <mtable> ... </mtable>
void CMathMLToTeX::mtableNode(QString &text)
{
  int sumCols = 0;

  if (text.contains("<mtr>"))
    {
      int posA = text.indexOf("<mtr>");
      int posB = text.indexOf("</mtr>");
      QString mtrText = text.mid(posA, posB - posA + 6);

      sumCols = mtrText.count("<mtd");
    }

  CStructureParser xmlParser(sumCols);
  QXmlSimpleReader xmlReader;

  xmlReader.setContentHandler(&xmlParser);

  QXmlInputSource xmlSource;
  xmlSource.setData(text);

  xmlReader.parse(xmlSource);

  text = xmlParser.getTeX();
}
