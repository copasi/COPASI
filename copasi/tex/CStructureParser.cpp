// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tex/CStructureParser.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/07/29 13:41:56 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Written by pwilly on 09.07.08

#include "CStructureParser.h"

#include <qstring.h>
#include <qregexp.h>

#include <iostream>
//#include <qvaluelist.h>

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

bool CStructureParser::startElement(const QString& str1, const QString& str2,
                                    const QString& qName,
                                    const QXmlAttributes& attr)
{
  tagName = qName;

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

  if (qName == "mfrac")
    {
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
      QString &last = mListOfUncompletedTags.last();

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
      QString &last = mListOfUncompletedTags.last();

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

      QString &last = mListOfUncompletedTags.last();

      // increase the index
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

      mListOfUncompletedTags.push_back("mrow");
      tex += " {";
    }

  if (qName == "mi" || qName == "mn")
    {
      QString &last = mListOfUncompletedTags.last();

      if (last.contains("mfenced") && (!tex.endsWith("(") && !tex.endsWith("(")))
        {
          tex += ", \\, ";
        }
    }

  if (qName == "mi" || qName == "mo" || qName == "mn")
    {
      QString &last = mListOfUncompletedTags.last();

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
  std::cout << std::endl << "on End Element of " << qName << std::endl;

  std::cout << "BEFORE: List of Uncompleted Tags: " << std::endl;
  QValueList<QString>::iterator itL;
  for (itL = mListOfUncompletedTags.begin(); itL != mListOfUncompletedTags.end(); ++itL)
    std::cout << *itL << std::endl;
  std::cout << std::endl;

  indent.remove((uint)0, 4);

  if (qName == "mtable")
    texTail = "\\end{array}";

  if (qName == "mfrac")
    {
      if (mListOfUncompletedTags.last().contains("mfrac"))
        mListOfUncompletedTags.pop_back();
      else
        std::cout << "WARNING on L" << __LINE__ << std::endl;
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
      std::cout << std::endl << "on End Element of mrow, mListOfUncompletedTags = " << mListOfUncompletedTags.last() << std::endl;

      if (mListOfUncompletedTags.last() == "mrow")
        mListOfUncompletedTags.pop_back();
      else
        std::cout << "WARNING on L" << __LINE__ << std::endl;

      tex += " } ";

      std::cout << "on endElement of mrow, tex = " << tex << std::endl;
    }

  if (qName == "mfenced")
    {
      if (mListOfUncompletedTags.last() == "mfenced")
        mListOfUncompletedTags.pop_back();
      else
        std::cout << "WARNING on L" << __LINE__ << std::endl;

      tex += "\\right)";

      QString &last = mListOfUncompletedTags.last();

      // </msub> direct after </mfenced>
      if (last.contains("msub"))
        {
          QStringList strList = QStringList::split("_", last);
          QString &lastUncompletedTags = strList.first();
          QString &idxStr = strList.last();
          int idx = idxStr.toInt();
          std::cout << last << " --> split: " << lastUncompletedTags << " & " << idx << std::endl;
          idx++;

          // update with incrementally index
          last = lastUncompletedTags + "_" + QString::number(idx);

          std::cout << "mfenced L" << __LINE__ << std::endl;
          std::cout << mListOfUncompletedTags.last() << std::endl;

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
          std::cout << last << " --> split: " << lastUncompletedTags << " & " << idx << std::endl;
          idx++;

          // update with incrementally index
          last = lastUncompletedTags + "_" + QString::number(idx);

          std::cout << "mfenced L" << __LINE__ << std::endl;
          std::cout << mListOfUncompletedTags.last() << std::endl;

          if (lastUncompletedTags.contains("msup") && idx == 2)
            tex += "^";
        }
    }

  if (qName == "msub")
    {
      if (mListOfUncompletedTags.last().contains("msub"))
        mListOfUncompletedTags.pop_back();
      else
        std::cout << "WARNING on L" << __LINE__ << std::endl;

      // </mfrac> direct after </msub>
      if (mListOfUncompletedTags.last().contains("mfrac"))
        tex += " }";
    }

  if (qName == "msup")
    {
      if (mListOfUncompletedTags.last().contains("msup"))
        mListOfUncompletedTags.pop_back();
      else
        std::cout << "WARNING on L" << __LINE__ << std::endl;

      // </mfrac> direct after </msup>
      if (mListOfUncompletedTags.last().contains("mfrac"))
        tex += " }";
    }

  std::cout << "AFTER: List of Uncompleted Tags: " << std::endl;
  for (itL = mListOfUncompletedTags.begin(); itL != mListOfUncompletedTags.end(); ++itL)
    std::cout << *itL << std::endl;
  std::cout << std::endl;

  return TRUE;
}

bool CStructureParser::ignorableWhitespace (const QString& str)
{
  return TRUE;
}

bool CStructureParser::skippedEntity (const QString& str)
{
  return TRUE;
}

QString CStructureParser::getTeX()
{
  if (texHead)
    return "$$\n" + texHead + "\n" + tex + texTail + "\n$$";
  else
    return "$$\n" + tex + "\n$$";
}
