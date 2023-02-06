// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/copasi.h"
#include "CCommonName.h"
#include "copasi/utilities/utility.h"
#include "copasi/undo/CData.h"

using std::string;

// static
std::string CCommonName::nameFromCN(const CCommonName & cn)
{
  CCommonName ParentCN;
  std::string ObjectType;
  std::string ObjectName;

  cn.split(ParentCN, ObjectType, ObjectName);

  return ObjectName;
}

// static
std::string CCommonName::compartmentNameFromCN(const CCommonName & cn)
{
  CCommonName CN(cn);
  CCommonName ParentCN;
  std::string ObjectType;
  std::string ObjectName;

  do
    {
      CN.split(ParentCN, ObjectType, ObjectName);
      CN = ParentCN;
    }
  while (!CN.empty() && ObjectType != "Compartment");

  return ObjectName;
}

void CCommonName::fixSpelling()
{
  if (!compare("CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Simulation Counter"))
    assign("CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Function Evaluations");
  else if (!compare("CN=Root,CN=Information,Timer=Current Date/Dime"))
    assign("CN=Root,CN=Information,Timer=Current Date/Time");
}

CCommonName::CCommonName():
  string()
{}

CCommonName::CCommonName(const char * name):
  string(name)
{
  fixSpelling();
}

CCommonName::CCommonName(const std::string & name):
  string(name)
{
  fixSpelling();
}

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
  objectType = Primary.getObjectType();

  if (objectName.empty())
    {
      objectName = Primary.getObjectName();
    }
  // We may have a vector and based on it's name we can determine the type
  else if (Primary.getObjectType() == "Vector")
    {
      objectType = Primary.getObjectName();

      // Vector:                    ObjectType:
      // Compartments               Compartment
      // Metabolites                Metabolite
      // Reduced Model Metabolites  Metabolite
      // Reactions                  Reaction
      // Events                     Event
      // Values                     ModelValue
      // ParameterSets              ModelParameterSet
      // Moieties                   Moiety
      // ListOflayouts              Layout
      // TaskList                   Task
      // ReportDefinitions          ReportDefinition
      // OutputDefinitions          PlotItem
      // Functions                  Function
      // ModelList                  CN
      // Units list                 Unit
      if (objectType == "Compartments") objectType = "Compartment";
      else if (objectType == "Metabolites") objectType = "Metabolite";
      else if (objectType == "Reduced Model Metabolites") objectType = "Metabolite";
      else if (objectType == "Reactions") objectType = "Reaction";
      else if (objectType == "Events") objectType = "Event";
      else if (objectType == "Values") objectType = "ModelValue";
      else if (objectType == "ParameterSets") objectType = "ModelParameterSet";
      else if (objectType == "Moieties") objectType = "Moiety";
      else if (objectType == "ListOflayouts") objectType = "Layout";
      else if (objectType == "TaskList") objectType = "Task";
      else if (objectType == "ReportDefinitions") objectType = "ReportDefinition";
      else if (objectType == "OutputDefinitions") objectType = "PlotItem";
      else if (objectType == "Functions") objectType = "Function";
      else if (objectType == "ModelList") objectType = "CN";
      else if (objectType == "Units list") objectType = "Unit";
      else objectType.clear();

      parentCN += "," + escape(Primary.getObjectType()) + "=" + escape(Primary.getObjectName());
    }
  // We have an array
  else
    {
      objectType.clear(); // We don't know
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
std::string CCommonName::construct(const CCommonName & parent, const std::string & objectType, const std::string & objectName)
{
  CCommonName CN(parent);

  CCommonName ParentParentCN;
  std::string ParentObjectName;
  std::string ParentObjectType;

  CN.split(ParentParentCN, ParentObjectType, ParentObjectName);

  if (ParentObjectType == "Vector" ||
      objectType.empty())
    {
      CN += "[" + CCommonName::escape(objectName) + "]";
    }
  else
    {
      CN += "," + CCommonName::escape(objectType) + "=" + CCommonName::escape(objectName);
    }

  return CN;
}

// static
std::string CCommonName::fromData(const CData & data)
{
  CCommonName Parent = data.getProperty(CData::OBJECT_PARENT_CN).toString();
  std::string ObjectType = data.getProperty(CData::OBJECT_TYPE).toString();
  std::string ObjectName = data.getProperty(CData::OBJECT_NAME).toString();

  return construct(Parent, ObjectType, ObjectName);
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
