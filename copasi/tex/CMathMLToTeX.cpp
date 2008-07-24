// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tex/CMathMLToTeX.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/07/24 10:56:46 $
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
  /*
    QDomDocument doc;
    doc.setContent(text);
    QDomElement element = doc.documentElement();
    QDomNode node = element.firstChild();

    while(!node.isNull())
    {
      QDomElement e = node.toElement();
   std::cout << "name node: " << node.nodeName() << std::endl;

   if (!e.isNull())
   {
        std::cout << "name e: " << e.nodeName() << std::endl;
     std::cout << e.isAttr() << " - " << e.isDocumentFragment() << " - " << e.isDocument() << std::endl;
     std::cout << e.isDocumentType() << " - " << e.isEntityReference() << " - " << e.isText() << std::endl;
     std::cout << e.isEntity() << " - " << e.isNotation() << " - " << e.isProcessingInstruction() << std::endl;
     std::cout << e.isCharacterData() << " - " << e.isComment () << std::endl;
     std::cout << e.tagName() << std::endl;
     std::cout << e.attributeNS() << std::endl;
     std::cout << "-- " << e.text() << std::endl;
   }
   std::cout << "---" << std::endl;
   node = node.nextSibling();
    }
  */
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

  /*
    if (text.contains("<msub>"))
    {
      QString msubText;

      QRegExp rx("<msub>.*</msub>");
   rx.setMinimal(true);
   rx.search(text);
   if (rx.pos(0) != -1)
        msubText = rx.cap(0);
   msubNode(msubText);

      QRegExp rx2("<msub>[^<]+</msub>");
   rx2.setMinimal(true);
   rx2.search(text);
   if (rx2.pos(0) != -1)
     msubText = rx2.cap(0);
   msubNode(msubText);
   if (rx2.pos(1) != -1)
     msubText = rx2.cap(1);
   msubNode(msubText);
  */
  /*
      int posA = text.find("<msub>");
   int posB = text.find("</msub>");
   QString msubText = text.mid(posA, posB-posA+7);
   msubNode(msubText);
   text.replace(posA, posB-posA+7, msubText);
  */
  //}
  /*
    if (text.contains("<mrow>"))
    {
      QString msubText;

      QRegExp rx("<mrow>.*</mrow>");
   rx.setMinimal(true);
   rx.search(text);
   if (rx.pos(0) != -1)
     msubText = rx.cap(0);
   msubNode(msubText);
    }
  */

  //  QDomElement dE =
  /*
    QString allignment;
    if (text.contains("<mtr>"))
    {
      int posA = text.find("<mtr>");
   int posB = text.find("</mtr>");
   QString mtrText = text.mid(posA, posB-posA+6);

   mtrNode(mtrText, allignment);

   text.replace(posA, posB-posA+6, mtrText);
    }

    QStringList strList = QStringList::split('\n', text);

  //  strList.gres("<mtable>", QString(QChar(0x005C)) + "begin{array}{" + allignment + "}");
    strList.gres("<mtable>", "\\begin{array}{" + allignment + "}");
    strList.gres("</mtable>", QString(QChar(0x005C)) + "end{array}");

    text = strList.join("\n");
  */
}

/// converting <mtr> ... </mtr>
void CMathMLToTeX::mtrNode(QString &text, QString &allignment)
{
  std::cout << "mtrNode(" << text << ")" << std::endl;

  /*
    if (text.contains("<mtd"))
    {
      int posA = text.find("<mtd");
   int posB = text.find("</mtd>");
   QString mtdText = text.mid(posA, posB-posA+6);

   if (mtdText.contains("columnalign"))
   {
     if (mtdText.find("left") >= 0)
       allignment += "l";
     if (mtdText.find("right") >= 0)
       allignment += "r";
     else
    allignment += "c";
   }
   else
     allignment += "l";

   mtdNode(mtdText);
   text.replace(posA, posB-posA+6, mtdText);
    }
  */
  std::cout << "==> " << text << std::endl;
}

/// converting <mtd> ... </mtd>
void CMathMLToTeX::mtdNode(QString &text)
{
  std::cout << "mtdNode(" << text << ")" << std::endl;

  if (text.contains("<mfrac>"))
    {
      int posA = text.find("<mfrac>");
      int posB = text.find("</mfrac>");
      QString mfracText = text.mid(posA, posB - posA + 8);
      mfracNode(mfracText);
      text.replace(posA, posB - posA + 8, mfracText);
    }

  //  text.remove("<mtd>");
  //  text.remove("</mtd>");
  std::cout << "==> " << text << std::endl;
}

/// converting <mfrac> ... </mfrac>
void CMathMLToTeX::mfracNode(QString &text)
{
  std::cout << "mfracNode(" << text << ")" << std::endl;

  // must exists two <mrow> ... </mrow>
  if (text.contains("<mrow>"))
    {
      int posA = text.find("<mrow>");
      int posB = text.find("</mrow>");
      QString mrowText = text.mid(posA, posB - posA + 7);
      mrowNode(mrowText);
      text.replace(posA, posB - posA + 7, mrowText);
    }

  std::cout << text << std::endl;
  //  moNode(text);
}

/// converting <mrow> ... </mrow>
void CMathMLToTeX::mrowNode(QString &text)
{
  std::cout << "mrowNode(" << text << ")" << std::endl;

  if (text.contains("<mo>"))
    {
      QRegExp rx("<mo>([^<]*)</mo>");
      rx.search(text);
      QString rxStr = rx.cap(1);

      std::cout << rx.numCaptures() << std::endl;
      std::cout << rx.pos(0) << std::endl;
      std::cout << rx.cap(0) << std::endl;
      std::cout << rx.pos(1) << std::endl;
      std::cout << rxStr << std::endl;
      moNode(rxStr);
      text.replace(rx, rxStr);

      std::cout << "mo: " << text << std::endl;
    }

  if (text.contains("<mfenced>"))
    {
      int posA = text.find("<mfenced>");
      int posB = text.find("</mfenced>");
      QString mfencedText = text.mid(posA, posB - posA + 10);
      mfencedNode(mfencedText);
      text.replace(posA, posB - posA + 10, mfencedText);

      std::cout << "mfenced: " << text << std::endl;
    }

  if (text.contains("<msub>"))
    {
      int posA = text.find("<msub>");
      int posB = text.find("</msub>");
      QString msubText = text.mid(posA, posB - posA + 7);
      msubNode(msubText);
      text.replace(posA, posB - posA + 7, msubText);

      std::cout << "msub: " << text << std::endl;
    }

  if (text.contains("<mi>"))
    text.replace(QRegExp("<mi>([^<]*)</mi>"), "\\1");

  std::cout << text << std::endl;
}

/// converting <mfenced> ... </mfenced>
void CMathMLToTeX::mfencedNode(QString &text)
{
  std::cout << "mfencedNode(" << text << ")" << std::endl;

  if (text.contains("<mrow>"))
    {
      int posA = text.find("<mrow>");
      int posB = text.find("</mrow>");
      QString mrowText = text.mid(posA, posB - posA + 7);
      mrowNode(mrowText);
      text.replace(posA, posB - posA + 7, mrowText);
    }

  std::cout << text << std::endl;
}

/// converting <mi> ... </mi>
void CMathMLToTeX::miNode(QString &text)
{}

/// converting <mo> ... </mo>
void CMathMLToTeX::moNode(QString &text)
{
  std::cout << "moNode(" << text << ")" << std::endl;

  if (text == "[")
    text.replace(text, QString(QChar(0x005C)) + "left[");
  else if (text == "]")
    text.replace(text, QString(QChar(0x005C)) + "right]");
  else if (text == "&CenterDot;")
    text.replace(text, QString(QChar(0x005C)) + "cdot");
  else
    text.replace(text, QString(QChar(0x005C)) + "mathrm{" + text + "}");

  std::cout << "==> " << text << std::endl;

  /*
    QRegExp rx("<mo>([^<]*)</mo>");

    int pos = 0;
    while (pos >= 0) {
      rx.search(text, pos);
      std::cout << "rx.cap(1) = "<< rx.cap(1) << std::endl;
   pos += rx.matchedLength();
    }
    text.replace(rx, rx.cap(1));
  //  text.replace(QRegExp("<mo>([^<]*)</mo>"), "\\1");
    std::cout << "--------" << std::endl;
    std::cout << text << std::endl;
  */
}

/// converting <msub> ... </msub>
void CMathMLToTeX::msubNode(QString &text)
{
  std::cout << "msubNode(" << text << ")" << std::endl;
  /*
    // the first
    if (text.contains("<mi>"))
    {
      int posA = text.find("<mi>");
   int posB = text.find("</mi>");
   QString mfracText = text.mid(posA, posB-posA+8);
   text.replace(posA, posB-posA+8, mfracText + "_");
    }

    // the second
    if (text.contains("<mi>"))
    {
      int posA = text.find("<mi>");
   int posB = text.find("</mi>");
   QString mfracText = text.mid(posA, posB-posA+8);
   text.replace(posA, posB-posA+8, "{" + QString(QChar(0x005C)) + "mathrm{" + mfracText + "}}");
    }

    std::cout << "==> " << text << std::endl;
  */
}
