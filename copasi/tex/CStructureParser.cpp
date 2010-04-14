// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tex/CStructureParser.cpp,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/04/14 17:28:44 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Written by pwilly on 09.07.08

/**
 * NOTE: We use index 1 and 2 to refer to the first and to the second part, resp.,
 * of some elements. These elements are mfrac, msub, and msup.
 */

#include "CStructureParser.h"

#include <qstring.h>
#include <qregexp.h>
#include <Q3ValueList>

#include <iostream>
#include "UI/qtUtilities.h"

CStructureParser::CStructureParser(int n)
{
  sumColumns = n;
}

bool CStructureParser::startDocument()
{
  indent = "";
  tex = "";

  indexColumns = -1;

  if (!sumColumns)
    needToWriteColumnAllignment = false;
  else
    needToWriteColumnAllignment = true;

  return TRUE;
}

bool CStructureParser::startElement(const QString& /* str1 */, const QString& /* str2 */,
                                    const QString& qName,
                                    const QXmlAttributes& attr)
{
  tagName = qName;

  Q3ValueList<QString>::iterator itL;

  if (qName == "mtable")
    texHead = "\\begin{array}";

  if (qName == "mtr")
    indexColumns = 0;

  if (qName == "mtd")
    {
      if (indexColumns > 0 && indexColumns < sumColumns - 1)
        tex += " \\; &";

      if (indexColumns == 0 && needToWriteColumnAllignment)
        texHead += "{";

      if (indexColumns < sumColumns && needToWriteColumnAllignment)
        {
          if (attr.count())
            {
              if (attr.value("columnalign") == "left")
                texHead += "l";
              else if (attr.value("columnalign") == "center")
                texHead += "c";
              else if (attr.value("columnalign") == "right")
                texHead += "r";
            }
          else
            texHead += "c";
        }

      if (indexColumns == sumColumns - 1)
        {
          if (needToWriteColumnAllignment)
            texHead += "}";

          needToWriteColumnAllignment = false;
        }
    }

  if (qName == "mfrac") // find a mfrac element
    {
      // increment index, if any
      if (!mListOfUncompletedTags.isEmpty())
        {
          QString &last = mListOfUncompletedTags.last();  // must be not empty

          // <mfrac> direct after <mfrac>
          if (last.contains("mfrac"))
            {
              QStringList strList = QStringList::split("_", last);
              QString &lastUncompletedTags = strList.first();
              QString &idxStr = strList.last();
              int idx = idxStr.toInt();
              idx++;

              // update with incrementally index
              last = lastUncompletedTags + "_" + QString::number(idx);

              tex += "{";
            }
        }

      mListOfUncompletedTags.push_back("mfrac_0");
      tex += "\\frac";
    }

  if (qName == "mfenced")
    {
      mListOfUncompletedTags.push_back("mfenced");
      tex += "\\left(";
    }

  if (qName == "msub")
    {
      QString &last = mListOfUncompletedTags.last();  // must be not empty

      // <msub> direct after <mfrac>
      if (last.contains("mfrac"))
        {
          QStringList strList = QStringList::split("_", last);
          QString &lastUncompletedTags = strList.first();
          QString &idxStr = strList.last();
          int idx = idxStr.toInt();
          idx++;

          // update with incrementally index
          last = lastUncompletedTags + "_" + QString::number(idx);

          tex += "{";
        }

      // <msub> direct after <mfenced>
      if (last.contains("mfenced") && (!tex.endsWith("(") && !tex.endsWith("(")))
        {
          tex += ", \\, ";
        }

      mListOfUncompletedTags.push_back("msub_0");
    }

  if (qName == "msup")
    {
      QString &last = mListOfUncompletedTags.last();  // must be not empty

      // <msup> direct after <mfrac>
      if (last.contains("mfrac"))
        {
          QStringList strList = QStringList::split("_", last);
          QString &lastUncompletedTags = strList.first();
          QString &idxStr = strList.last();
          int idx = idxStr.toInt();
          idx++;

          // update with incrementally index
          last = lastUncompletedTags + "_" + QString::number(idx);

          tex += "{";
        }

      // <msup> direct after <mfenced>
      if (last.contains("mfenced") && (!tex.endsWith("(") && !tex.endsWith("(")))
        {
          tex += ", \\, ";
        }

      mListOfUncompletedTags.push_back("msup_0");
    }

  if (qName == "mrow")
    {
      // increment index, if any
      if (!mListOfUncompletedTags.isEmpty())
        {
          QString &last = mListOfUncompletedTags.last();  // can be empty

          if (last.contains("mfrac") || last.contains("msub") || last.contains("msup"))
            {
              QStringList strList = QStringList::split("_", last);
              QString &lastUncompletedTags = strList.first();
              QString &idxStr = strList.last();
              int idx = idxStr.toInt();
              idx++;

              // update with incrementally index
              last = lastUncompletedTags + "_" + QString::number(idx);

              if (lastUncompletedTags.contains("msub") && idx == 2)
                tex += "_";

              if (lastUncompletedTags.contains("msup") && idx == 2)
                tex += "^";
            }
        }

      mListOfUncompletedTags.push_back("mrow");
      tex += " {";
    }

  if (qName == "mi" || qName == "mo" || qName == "mn")
    {
      // increment index, if any
      if (!mListOfUncompletedTags.isEmpty())
        {
          QString &last = mListOfUncompletedTags.last();  // can be empty

          if (last.contains("mfrac") || last.contains("msub") || last.contains("msup"))
            {
              QStringList strList = QStringList::split("_", last);
              QString &lastUncompletedTags = strList.first();
              QString &idxStr = strList.last();
              int idx = idxStr.toInt();
              idx++;

              // update with incrementally index
              last = lastUncompletedTags + "_" + QString::number(idx);

              if (lastUncompletedTags.contains("msub") && idx == 2)
                tex += "_";

              if (lastUncompletedTags.contains("msup") && idx == 2)
                tex += "^";
            }

          if (last.contains("mfenced") && (!tex.endsWith("(") && !tex.endsWith("(")))
            {
              tex += ", \\, ";
            }
        }
    }

  indent += "    ";

  return TRUE;
}

bool CStructureParser::characters(const QString& str)
{
  QRegExp rx("\\w");
  QString strAux = str.stripWhiteSpace();
  int pos = rx.search(strAux);

  if (pos != -1)
    {
      // handling word character within <mrow> ... </mrow>
      if (tagName == "mrow")
        {
          if (strAux.length() > 1)
            tex += "{\\text{" + strAux + "}}";
          else  // exactly only one character
            tex += "{" + strAux + "}";
        }

      // handling word character within <mi> ... </mi>
      if (tagName == "mi")
        {
          if (strAux.contains("\\"))    // for, eg., \sin, \cos
            tex += strAux;
          else if (strAux.length() > 1)
            {
              if (strAux == "sech" || strAux == "csch" || strAux == "arcsec" || strAux == "arccsc"
                  || strAux == "arccot" || strAux == "arcsinh" || strAux == "arccosh" || strAux == "arctanh"
                  || strAux == "arcsech" || strAux == "arccsch" || strAux == "arccoth")
                tex += "{\\mathrm{" + strAux + " \\: }}";
              else
                tex += "{\\mathrm{" + strAux + "}}";
            }
          else  // exactly only one character
            tex += "{" + strAux + "}";
        }

      // handling word character within <mo> ... </mo>
      if (tagName == "mo")
        {
          if (strAux.contains("\\"))    // for, eg.,\cdot, \ge, \le, \ne
            {
              if (strAux == "\\log")
                tex += " \\, " + strAux;
              else if (strAux == "\\lt")
                tex += " \\, < \\, ";
              else
                tex += " \\, " + strAux + " \\, ";
            }
          else if (strAux.contains("xor"))
            tex += "\\; \\mathrm{" + strAux + "} \\; ";
          else if (strAux == "e")
            tex += strAux;
          else
            tex += "\\mathrm{" + strAux + "}";
        }

      // handling word character within <mn> ... </mn>
      if (tagName == "mn")
        tex += "{" + strAux + "}";
    }
  // handling non-word character
  else if (strAux == "=" || strAux == "!" || strAux == "|")
    tex += strAux;
  else if (strAux == "-" || strAux == "+" || strAux == ">" || strAux.contains("%"))
    tex += " \\, " + strAux + " \\, ";

  return TRUE;
}

bool CStructureParser::endElement(const QString&, const QString&, const QString& qName)
{
  Q3ValueList<QString>::iterator itL;

  indent.remove((uint)0, 4);

  if (qName == "mtable")
    texTail = "\\end{array}";

  if (qName == "mfrac")
    {
      if (mListOfUncompletedTags.last().contains("mfrac"))  // must be not empty
        mListOfUncompletedTags.pop_back();

      if (!mListOfUncompletedTags.isEmpty())
        {
          // </mfrac> direct after </mfrac>
          if (mListOfUncompletedTags.last().contains("mfrac"))  // must be not empty
            tex += " }";
        }
    }

  if (qName == "mtr")
    tex += "\\\\ \n && \\\\ \n";

  if (qName == "mtd")
    {
      if (indexColumns > 0 && indexColumns < sumColumns - 1)
        tex += "& \\; ";

      indexColumns++;
    }

  if (qName == "mrow")
    {
      if (mListOfUncompletedTags.last() == "mrow")  // must not be empty
        mListOfUncompletedTags.pop_back();

      tex += " } ";
    }

  if (qName == "mfenced")
    {
      if (mListOfUncompletedTags.last() == "mfenced") // must be not empty
        mListOfUncompletedTags.pop_back();

      tex += "\\right)";

      QString &last = mListOfUncompletedTags.last();  // must be not empty

      // </msub> direct after </mfenced>
      if (last.contains("msub"))
        {
          QStringList strList = QStringList::split("_", last);
          QString &lastUncompletedTags = strList.first();
          QString &idxStr = strList.last();
          int idx = idxStr.toInt();
          idx++;

          // update with incrementally index
          last = lastUncompletedTags + "_" + QString::number(idx);

          if (lastUncompletedTags.contains("msub") && idx == 2)
            tex += "_";
        }

      // </msup> direct after </mfenced>
      if (last.contains("msup"))
        {
          QStringList strList = QStringList::split("_", last);
          QString &lastUncompletedTags = strList.first();
          QString &idxStr = strList.last();
          int idx = idxStr.toInt();
          idx++;

          // update with incrementally index
          last = lastUncompletedTags + "_" + QString::number(idx);

          if (lastUncompletedTags.contains("msup") && idx == 2)
            tex += "^";
        }
    }

  if (qName == "msub")
    {
      if (mListOfUncompletedTags.last().contains("msub")) // must be not empty
        mListOfUncompletedTags.pop_back();

      // </mfrac> direct after </msub>
      if (mListOfUncompletedTags.last().contains("mfrac"))  // must ne not empty
        tex += " }";
    }

  if (qName == "msup")
    {
      if (mListOfUncompletedTags.last().contains("msup")) // must be not empty
        mListOfUncompletedTags.pop_back();

      // </mfrac> direct after </msup>
      if (mListOfUncompletedTags.last().contains("mfrac"))  // must be not empty
        tex += " }";
    }

  return TRUE;
}

bool CStructureParser::ignorableWhitespace(const QString& /* str */)
{
  return TRUE;
}

bool CStructureParser::skippedEntity(const QString& /* str */)
{
  return TRUE;
}

QString CStructureParser::getTeX()
{
  QString texIntro;

  texIntro = "\% Attention: \n";
  texIntro += "\% We provide only the LaTeX code of the Differential Equations. \n";
  texIntro += "\% You need to include it in your TeX document. \n";
  texIntro += "\% Some manual adjustments may be needed for too wide equations. \n\n";

  if (!texHead.isNull())
    return texIntro + "$$\n" + texHead + "\n" + tex + texTail + "\n$$";
  else
    return texIntro + "$$\n" + tex + "\n$$";
}
