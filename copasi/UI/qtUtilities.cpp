/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/qtUtilities.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/12 16:53:33 $
   End CVS Header */

#include <qstring.h>

#include "copasi.h"
#include "qtUtilities.h"
#include "utilities/CCopasiParameterGroup.h"

QString getParameterValue(const CCopasiParameterGroup * group,
                          const unsigned C_INT32 & index,
                          CCopasiParameter::Type * type)
{
  if (type) *type = group->getType(index);

  switch (group->getType(index))
    {
    case CCopasiParameter::DOUBLE:
    case CCopasiParameter::UDOUBLE:
      return QString::number(* (C_FLOAT64 *) group->getValue(index));
      break;

    case CCopasiParameter::INT:
      return QString::number(* (C_INT32 *) group->getValue(index));
      break;

    case CCopasiParameter::UINT:
      return QString::number(* (unsigned C_INT32 *) group->getValue(index));
      break;

    case CCopasiParameter::BOOL:
      return QString::number(* (bool *) group->getValue(index));
      break;

    case CCopasiParameter::STRING:
      return
      QString::fromLatin1((* (std::string *) group->getValue(index)).c_str());
      break;

    case CCopasiParameter::GROUP:
      return QString::fromLatin1(group->getName(index).c_str());
      break;

    case CCopasiParameter::INVALID:
      return QString::fromLatin1("INVALID");
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
  if (getParameterValue(group, index) == value) return true;

  bool ok;

  C_FLOAT64 DOUBLE;
  C_INT32 INT;
  unsigned C_INT32 UINT;
  bool BOOL;
  std::string STRING;

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
      STRING = value.latin1();
      return group->setValue(index, STRING);
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
