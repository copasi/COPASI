// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tex/CMathMLToTeX.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/07/25 08:09:00 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Written by pwilly on 07.07.08

#include <iostream.h>

//#include <qstring.h>
#include <qstringlist.h>
#include <qregexp.h>

//#include <qxml.h>
#include "CStructureParser.h"
//#include <qdom.h>

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

  text.replace("xor", "xee");
  text.replace("floor", "flee");

  text.replace("or", "\\vee");

  text.replace("xee", "xor");
  text.replace("flee", "floor");
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

  text.replace("sec", "\\sec");

  text.replace("sooh", "sech");
  text.replace("arcso", "arcsec");
  text.replace("arsoh", "arcsech");

  // csc, csch, arccsc, arccsch

  text.replace("arccsch", "arcoh");
  text.replace("arccsc", "arcce");
  text.replace("csch", "cooh");

  text.replace("csc", "\\csc");

  text.replace("cooh", "csch");
  text.replace("arcce", "arccsc");
  text.replace("arcoh", "arccsch");

  // cot, coth, arccot, arccoth

  text.replace("arccoth", "arctoh");
  text.replace("arccot", "arcto");
  text.replace("coth", "tooh");

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
      if (text.contains("<mtable>") > 1)
        {
          std::cout << "The MathML contains <mtable> more than one. Needs more handling." << std::endl;
          text = "The MathML contains <mtable> more than one. Needs more handling.";
          return;
        }

      mNode(text);
    }
}

/// normal equation node
void CMathMLToTeX::mNode(QString &text)
{
  std::cout << "BEFORE: Text:\n" << text << std::endl;

  CStructureParser xmlParser(0);
  QXmlSimpleReader xmlReader;

  xmlReader.setContentHandler(&xmlParser);

  QXmlInputSource xmlSource;
  xmlSource.setData(text);

  xmlReader.parse(xmlSource);

  text = xmlParser.getTeX();

  std::cout << "AFTER: Text:\n" << text << std::endl;
}

/// converting <mtable> ... </mtable>
void CMathMLToTeX::mtableNode(QString &text)
{
  int sumCols = 0;
  if (text.contains("<mtr>"))
    {
      int posA = text.find("<mtr>");
      int posB = text.find("</mtr>");
      QString mtrText = text.mid(posA, posB - posA + 6);

      sumCols = mtrText.contains("<mtd");
    }

  CStructureParser xmlParser(sumCols);
  QXmlSimpleReader xmlReader;

  xmlReader.setContentHandler(&xmlParser);

  QXmlInputSource xmlSource;
  xmlSource.setData(text);

  xmlReader.parse(xmlSource);

  text = xmlParser.getTeX();
}
