// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/qtUtilities.cpp,v $
//   $Revision: 1.17.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/12 19:12:58 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qstring.h>
#include <qfileinfo.h>

#include "copasi.h"
#include "qtUtilities.h"
#include "CQMessageBox.h"
#include "utilities/CCopasiParameterGroup.h"
#include "utilities/CDirEntry.h"

#ifdef DEBUG_UI
#include <QtDebug>
#endif

QString getParameterValue(const CCopasiParameterGroup * group,
                          const size_t & index,
                          CCopasiParameter::Type * type)
{
  if (index >= group->size())
    return QString::fromLatin1("INVALID");

  if (type) *type = group->getType(index);

  switch (group->getType(index))
    {
      case CCopasiParameter::DOUBLE:
        return QString::number(* group->getValue(index).pDOUBLE);
        break;

      case CCopasiParameter::UDOUBLE:
        return QString::number(* group->getValue(index).pDOUBLE);
        break;

      case CCopasiParameter::INT:
        return QString::number(* group->getValue(index).pINT);
        break;

      case CCopasiParameter::UINT:
        return QString::number(* group->getValue(index).pUINT);
        break;

      case CCopasiParameter::BOOL:
        return QString::number(* group->getValue(index).pBOOL);
        break;

      case CCopasiParameter::STRING:
        return
          FROM_UTF8(* group->getValue(index).pSTRING);
        break;

      case CCopasiParameter::KEY:
        return
          FROM_UTF8(* group->getValue(index).pKEY);
        break;

      case CCopasiParameter::CN:
        return
          FROM_UTF8(* group->getValue(index).pCN);
        break;

      case CCopasiParameter::GROUP:
        return FROM_UTF8((group->getName(index)));
        break;

      case CCopasiParameter::INVALID:
        return QString::fromUtf8("INVALID");
        break;

      default:
        break;
    }

  return QString::fromLatin1("INVALID");
}

QString getParameterValue(const CCopasiParameterGroup * group,
                          const std::string & name,
                          CCopasiParameter::Type * type)
{return getParameterValue(group, group->getIndex(name), type);}

bool setParameterValue(CCopasiParameterGroup * group,
                       const size_t & index,
                       const QString & value)
{
  if (index >= group->size())
    return false;

  if (getParameterValue(group, index) == value) return true;

  bool ok;

  C_FLOAT64 DOUBLE;
  C_INT32 INT;
  unsigned C_INT32 UINT;
  bool BOOL;
  std::string STRING;
  CCopasiObjectName CN;

  switch (group->getType(index))
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        DOUBLE = value.toDouble(&ok);

        if (!ok) return false;

        return group->setValue(index, DOUBLE);
        break;

      case CCopasiParameter::INT:
        INT = value.toInt(&ok);

        if (!ok) return false;

        return group->setValue(index, INT);
        break;

      case CCopasiParameter::UINT:
        UINT = value.toUInt(&ok);

        if (!ok) return false;

        return group->setValue(index, UINT);
        break;

      case CCopasiParameter::BOOL:;
        UINT = value.toUShort(&ok);

        if (!ok) return false;

        if (UINT == 1) BOOL = true;
        else if (UINT == 0) BOOL = false;
        else return false;

        return group->setValue(index, BOOL);
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
        STRING = TO_UTF8(value);
        return group->setValue(index, STRING);
        break;

      case CCopasiParameter::CN:
        CN = std::string(TO_UTF8(value));
        return group->setValue(index, CN);
        break;

      case CCopasiParameter::GROUP:
      case CCopasiParameter::INVALID:
        return false;
        break;

      default:
        break;
    }

  return false;
}

bool setParameterValue(CCopasiParameterGroup * group,
                       const std::string & name,
                       const QString & value)
{return setParameterValue(group, group->getIndex(name), value);}

C_INT32 checkSelection(const QString & file)
{

#ifdef DEBUG_UI
  qDebug() << "Filename on checkSelection = " << file;
#endif

  if (QFileInfo(file).exists())
    {
      if (CDirEntry::isWritable(TO_UTF8(file)))
        return CQMessageBox::question(NULL, "File exists!",
                                      "Overwrite existing file " + file + "?",
                                      QMessageBox::Ok | QMessageBox::Cancel,
                                      QMessageBox::Cancel);
      else
        {
          CQMessageBox::information(NULL, "File read-only",
                                    "The file is read-only. Please select another file!",
                                    QMessageBox::Ok, QMessageBox::Ok);
          return QMessageBox::Cancel;
        }
    }
  else
    return QMessageBox::Ok;
}

void vectorOfStrings2QStringList(std::vector<std::string> vs, QStringList & qsl)
{
  qsl.clear();
  size_t i, imax = vs.size();

  for (i = 0; i < imax; ++i) qsl += FROM_UTF8(vs[i]);
}
