// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * Class CCommonName
 *
 * This class is the class for handling Copasi object names.
 *
 * Copyright Stefan Hoops 2002
 */

#include <sstream>

#include "copasi.h"
#include "CCommonName.h"
#include "copasi/utilities/utility.h"
#include "copasi/undo/CData.h"

using std::string;

CCommonName::CCommonName():
  string()
{}

CCommonName::CCommonName(const std::string & name):
  string(name)
{}

CCommonName::CCommonName(const CCommonName & src):
  string(src)
{}

CCommonName::~CCommonName()
{}

CCommonName CCommonName::getPrimary() const
{return substr(0, findNext(","));}

CCommonName CCommonName::getRemainder() const
{
  if (empty()) return CCommonName();

  std::string Separator = ",";

  if (at(0) != '[')
    {
      Separator += "[";
    }

  std::string::size_type pos = findNext(Separator);

  if (pos == std::string::npos) return CCommonName();

  if (at(pos) == ',') pos++;

  return substr(pos);
}

std::string CCommonName::getObjectType() const
{
  CCommonName Primary(getPrimary());

  return CCommonName::unescape(Primary.substr(0, Primary.findNext("=")));
}

std::string CCommonName::getObjectName() const
{
  CCommonName Primary = getPrimary();
  std::string::size_type pos = Primary.findNext("=");

  if (pos == std::string::npos) return "";

  CCommonName tmp = Primary.substr(pos + 1);

  if (getObjectType() != "String")
    {
      tmp = tmp.substr(0, tmp.findNext("["));
    }

  return CCommonName::unescape(tmp);
}

size_t CCommonName::getElementIndex(const size_t & pos) const
{
  size_t Index = C_INVALID_INDEX;

  if (strToIndex(getElementName(pos), Index))
    {
      return Index;
    }

  return C_INVALID_INDEX;
}

std::string CCommonName::getElementName(const size_t & pos,
                                        const bool & unescape) const
{
  CCommonName Primary = getPrimary();

  std::string::size_type open = Primary.findNext("[");
  size_t i;

  for (i = 0; i < pos && open != std::string::npos; i++)
    open = Primary.findNext("[", open + 1);

  std::string::size_type close = Primary.findNext("]", open + 1);

  if (open == std::string::npos || close == std::string::npos) return "";

  if (unescape)
    return CCommonName::unescape(Primary.substr(open + 1,
                                 close - open - 1));

  return Primary.substr(open + 1, close - open - 1);
}

void CCommonName::split(CCommonName & parentCN, std::string & objectType, std::string & objectName) const
{
  std::string::size_type LastComma = findPrevious(",");
  CCommonName Primary;

  if (LastComma != std::string::npos)
    {
      parentCN = substr(0, LastComma);
      Primary = substr(LastComma + 1);
    }
  else
    {
      parentCN.clear();
      Primary = *this;
    }

  objectName = Primary.getElementName(0);

  if (objectName.empty())
    {
      objectType = Primary.getObjectType();
      objectName = Primary.getObjectName();
    }
  else
    {
      objectType.clear();
      parentCN += "," + escape(Primary.getObjectType()) + "=" + escape(Primary.getObjectName());
    }

  return;
}

std::string CCommonName::escape(const std::string & name)
{
#define toBeEscaped "\\[]=,>"
  std::string Escaped(name);
  std::string::size_type pos = Escaped.find_first_of(toBeEscaped);

  while (pos != std::string::npos)
    {
      Escaped.insert(pos, "\\");
      pos += 2;
      pos = Escaped.find_first_of(toBeEscaped, pos);
    }

  return Escaped;
#undef toBeEscaped
}

std::string CCommonName::unescape(const std::string & name)
{
  std::string Unescaped(name);
  std::string::size_type pos = Unescaped.find("\\");

  while (pos != std::string::npos)
    {
      Unescaped.erase(pos, 1);
      pos++;
      pos = Unescaped.find("\\", pos);
    }

  return Unescaped;
}

// static
std::string CCommonName::fromData(const CData & data)
{
  CCommonName CN = data.getProperty(CData::OBJECT_PARENT_CN).toString();
  std::string ObjectType = data.getProperty(CData::OBJECT_TYPE).toString();

  CCommonName ParentParentCN;
  std::string ParentObjectName;
  std::string ParentObjectType;

  CN.split(ParentParentCN, ParentObjectType, ParentObjectName);

  if (ParentObjectType == "Vector" ||
      ObjectType.empty())
    {
      CN += "[" + CCommonName::escape(data.getProperty(CData::OBJECT_NAME).toString()) + "]";
    }
  else
    {
      CN += "," + CCommonName::escape(ObjectType) + "=" + CCommonName::escape(data.getProperty(CData::OBJECT_NAME).toString());
    }

  return CN;
}

std::string::size_type
CCommonName::findNext(const std::string & toFind,
                      const std::string::size_type & pos) const
{
  std::string::size_type where = find_first_of(toFind, pos);

  std::string::size_type tmp;

  while (where && where != std::string::npos)
    {
      tmp = find_last_not_of("\\", where - 1);

      if ((where - tmp) % 2)
        return where;

      where = find_first_of(toFind, where + 1);
    }

  return where;
}

std::string::size_type CCommonName::findPrevious(const std::string & toFind,
    const std::string::size_type & pos) const
{
  std::string::size_type where = find_last_of(toFind, pos);

  std::string::size_type tmp;

  while (where && where != std::string::npos)
    {
      tmp = find_last_not_of("\\", where - 1);

      if ((where - tmp) % 2)
        return where;

      where = find_last_of(toFind, where - 1);
    }

  return where;
}
