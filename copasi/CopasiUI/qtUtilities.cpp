/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/qtUtilities.cpp,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/28 20:25:35 $
   End CVS Header */

#include <qstring.h>
#include <qfileinfo.h>
#include <qmessagebox.h>

#include "copasi.h"
#include "qtUtilities.h"
#include "utilities/CCopasiParameterGroup.h"
#include "utilities/CDirEntry.h"

QString getParameterValue(const CCopasiParameterGroup * group,
                          const unsigned C_INT32 & index,
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
    }

  return QString::fromLatin1("INVALID");
}

QString getParameterValue(const CCopasiParameterGroup * group,
                          const std::string & name,
                          CCopasiParameter::Type * type)
{return getParameterValue(group, group->getIndex(name), type);}

bool setParameterValue(CCopasiParameterGroup * group,
                       const unsigned C_INT32 & index,
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
      STRING = value.utf8();
      return group->setValue(index, STRING);
      break;

    case CCopasiParameter::CN:
      CN = (std::string) value.utf8();
      return group->setValue(index, CN);
      break;

    case CCopasiParameter::GROUP:
    case CCopasiParameter::INVALID:
      return false;
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
  if (QFileInfo(file).exists())
    {
      if (CDirEntry::isWritable((const char *)file.utf8()))
        return QMessageBox::question(NULL, "File exists!",
                                     "Overwrite existing file " + file + "?",
                                     QMessageBox::Yes,
                                     QMessageBox::No | QMessageBox::Default,
                                     QMessageBox::Cancel | QMessageBox::Escape);
      else
        {
          QMessageBox::information(NULL, "File read-only",
                                   "The file is read-only. Please select another file!",
                                   QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape,
                                   QMessageBox::NoButton,
                                   QMessageBox::NoButton);
          return QMessageBox::No;
        }
    }
  else
    return QMessageBox::Yes;
}
