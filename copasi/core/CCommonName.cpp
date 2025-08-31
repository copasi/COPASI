// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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
#include "copasi/core/CCommonName.h"

#include "copasi/math/CMathContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
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

// static
CObjectInterface * CCommonName::GetObjectFromCN(const CObjectInterface::ContainerList & listOfContainer,
  CCommonName & objName)
{
  bool CheckDataModel = true;
  const CDataModel * pDataModel = nullptr;
  CObjectInterface * pObject = nullptr;

  for (const CDataContainer * pContainer : listOfContainer)
    {
      if (pDataModel == nullptr)
        pDataModel = pContainer->getObjectDataModel();

      if (dynamic_cast< const CDataModel * >(pContainer) != nullptr)
        CheckDataModel = false;

      if ((pObject = const_cast< CObjectInterface * >(objName.resolve(pContainer))) != nullptr)
        break;
    }

  if (pObject == nullptr
      && CheckDataModel
      && pDataModel != nullptr)
    pObject = const_cast< CObjectInterface * >(objName.resolve(pDataModel));

  return pObject;
}

void CCommonName::fixSpelling()
{
  if (!compare("CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Simulation Counter"))
    assign("CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Function Evaluations");
  else if (!compare("CN=Root,CN=Information,Timer=Current Date/Dime"))
    assign("CN=Root,CN=Information,Timer=Current Date/Time");
}

void CCommonName::createComponent()
{
  CCommonName CN(*this);
  std::vector< std::pair< std::string, std::string > > Objects;
  Objects.reserve(10);

  while (!CN.empty())
    {
      CCommonName ParentCN;
      std::string Type;
      std::string Name;

      CN.split(ParentCN, Type, Name);
      Objects.push_back(std::make_pair(Type, Name));
      CN = ParentCN;
    }

  CCommonNameComponent::shared_ptr pComponent = nullptr;
  CCommonNameComponent::shared_ptr pParent = nullptr;

  for (auto it = Objects.rbegin(); it != Objects.rend(); ++it)
    {
      pComponent = CCommonNameComponent::create(it->first, it->second, pParent);
      pParent = pComponent;
    }

  mpComponent = pComponent;
}

CCommonName::CCommonName()
  : string()
  , mpComponent(nullptr)
{}

CCommonName::CCommonName(const CCommonNameComponent::shared_ptr & pComponent)
  : std::string(pComponent ? pComponent->getCN() : "")
  , mpComponent(pComponent)
{};

CCommonName::CCommonName(const char * name)
  : string(name)
  , mpComponent(nullptr)
{
  fixSpelling();
}

CCommonName::CCommonName(const std::string & name)
  : string(name)
  , mpComponent(nullptr)
{
  fixSpelling();
}

CCommonName::CCommonName(const CCommonName & src)
  : string(src)
  , mpComponent(src.mpComponent)
{}

CCommonName::~CCommonName()
{}

const CObjectInterface * CCommonName::resolve(const CDataContainer * pContainer)
{
  if (mpComponent == nullptr)
    createComponent();

  if (pContainer == nullptr)
    return nullptr;

  if (mpComponent->isResolved()
      && mpComponent->hasAncestor(pContainer))
    return mpComponent->getObject();

  if (!mpComponent->mayHaveAncestor(pContainer))
    return nullptr;

  std::vector< CCommonNameComponent::shared_ptr > Components = mpComponent->getComponentList();
  CCommonNameComponent::shared_ptr resolved = nullptr;

  for (auto it = Components.rbegin(); it != Components.rend(); ++it)
    {
      // Find the container component matching this component
      if (resolved == nullptr)
        {
          if (pContainer->getCNComponent()->getPartialCN() == (*it)->getPartialCN())
            resolved = pContainer->getCNComponent();

          continue;
        }

      const CObjectInterface * pObject = resolved->getObject()->getObject((*it)->getPartialCN());

      if (pObject == nullptr)
        {
          resolved = nullptr;
          break;
        }

      resolved = pObject->getCNComponent();
    }

  if (resolved == nullptr)
    return nullptr;

  // We have resolved the full common name
  mpComponent = resolved;
  std::string::operator=(mpComponent->getCN());

  const CObjectInterface * pObject = mpComponent->getObject();

  // Special case for MathContainers to allow resolving to MathObjects
  if (dynamic_cast< const CMathContainer * >(pContainer) != nullptr
      && (pObject = dynamic_cast< const CMathContainer * >(pContainer)->getMathObject(pObject)) != nullptr)
    return pObject;

  return mpComponent->getObject();
}

bool CCommonName::isResolved() const
{
  return mpComponent != nullptr && mpComponent->isResolved();
}

const CObjectInterface * CCommonName::getObject() const
{
  return mpComponent ? mpComponent->getObject() : nullptr;
}

void CCommonName::setObject(const CObjectInterface * pObject)
{
  if (dynamic_cast< const CDataObject * >(pObject) != nullptr)
    mpComponent = pObject->getCNComponent();
  else if (mpComponent != nullptr)
    mpComponent->signalObjectDeleted();

  refresh();
}

void CCommonName::refresh()
{
  if (mpComponent != nullptr)
    std::string::operator=(mpComponent->getCN());
}

bool CCommonName::hasAncestor(const CDataContainer * pObject) const
{
  if (pObject == nullptr)
    return false;

  const_cast< CCommonName * >(this)->refresh();

  return find(pObject->getCNComponent()->getCN()) == 0;
}

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

  objectType = Primary.getObjectType();

  // We have an array
  if (Primary.getObjectType() == "Array")
    {
      std::string Index;
      size_t pos = 0;

      while ((Index = Primary.getElementName(pos++, false)) != "")
        objectName += "[" + Index + "]";

      if (objectName.empty())
        objectName = Primary.getObjectName();
      else
        {
          objectType = "ElementReference";
          parentCN += "," + escape(Primary.getObjectType()) + "=" + escape(Primary.getObjectName());
        }
    }
  // We may have a vector and based on it's name we can determine the type
  else if (Primary.getObjectType() == "Vector")
    {
      objectName = Primary.getElementName(0, false);

      if (objectName.empty())
        objectName = Primary.getObjectName();
      else
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
          if (objectType == "Compartments")
            objectType = "Compartment";
          else if (objectType == "Metabolites")
            objectType = "Metabolite";
          else if (objectType == "Reduced Model Metabolites")
            objectType = "Metabolite";
          else if (objectType == "Reactions")
            objectType = "Reaction";
          else if (objectType == "Events")
            objectType = "Event";
          else if (objectType == "Values")
            objectType = "ModelValue";
          else if (objectType == "ParameterSets")
            objectType = "ModelParameterSet";
          else if (objectType == "Moieties")
            objectType = "Moiety";
          else if (objectType == "ListOflayouts")
            objectType = "Layout";
          else if (objectType == "TaskList")
            objectType = "Task";
          else if (objectType == "ReportDefinitions")
            objectType = "ReportDefinition";
          else if (objectType == "OutputDefinitions")
            objectType = "PlotItem";
          else if (objectType == "Functions")
            objectType = "Function";
          else if (objectType == "ModelList")
            objectType = "CN";
          else if (objectType == "Units list")
            objectType = "Unit";
          else
            objectType.clear();

          parentCN += "," + escape(Primary.getObjectType()) + "=" + escape(Primary.getObjectName());
        }
    }
  else
    {
      objectName = Primary.getObjectName();
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
