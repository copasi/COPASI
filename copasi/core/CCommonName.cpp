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
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"

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
  const CCommonName & objName)
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
  if (!mpCN->compare("CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Simulation Counter"))
    mpCN->assign("CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Function Evaluations");
  else if (!mpCN->compare("CN=Root,CN=Information,Timer=Current Date/Dime"))
    mpCN->assign("CN=Root,CN=Information,Timer=Current Date/Time");
}

// static
CCommonNameComponent::shared_ptr CCommonName::createComponent(const std::string & cn)
{
  CCommonName CN(cn);

  struct ComponentData {
    std::string type = "";
    std::string name = "";
    std::string partialCN = "";
  };

  std::vector< ComponentData > Objects;
  Objects.reserve(10);

  while (!CN.empty())
    {
      CCommonName ParentCN;
      ComponentData Data;
      std::string Type;
      std::string Name;

      CN.split(ParentCN, Data.type, Data.name, &Data.partialCN);
      Objects.push_back(Data);

      // String and Separator are always resolved locally;
      if (Type == "String"
          || Type == "Separator")
        break;

      CN = ParentCN;
    }

  CCommonNameComponent::shared_ptr pComponent = nullptr;
  CCommonNameComponent::shared_ptr pParent = nullptr;

  for (auto it = Objects.rbegin(); it != Objects.rend(); ++it)
    {
      pComponent = CCommonNameComponent::create(it->partialCN, it->type, it->name, pParent);
      pParent = pComponent;
    }

  if (!pComponent)
    pComponent = CCommonNameComponent::create(cn, "", "", nullptr);

  return pComponent;
}

CCommonName::CCommonName()
  : mpComponent()
  , mpCN(std::make_shared< std::string >())
{}

CCommonName::CCommonName(const CCommonNameComponent::shared_ptr & pComponent)
  : mpComponent(pComponent)
  , mpCN(pComponent ? pComponent->getCN() : std::make_shared< std::string >())
{}

CCommonName::CCommonName(const std::string & name)
  : mpComponent()
  , mpCN(std::make_shared< std::string >(name))
{
  fixSpelling();
}

CCommonName::CCommonName(const CCommonName & src)
  : mpComponent(src.mpComponent)
  , mpCN(src.mpCN)
{}

CCommonName::~CCommonName()
{}

CCommonName & CCommonName::operator=(const CCommonName & rhs)
{
  if (this != &rhs)
    {
      mpComponent = rhs.mpComponent;
      mpCN = rhs.mpCN;
    }

  return *this;
}

CCommonName & CCommonName::operator=(const std::string & rhs)
{
  if (mpCN->compare(rhs) != 0)
    {
      mpComponent = nullptr;
      mpCN = std::make_shared< std::string >(rhs);
    }

  return *this;
}

CCommonName & CCommonName::operator=(const CCommonNameComponent::shared_ptr & rhs)
{
  if (mpComponent != rhs)
    {
      mpComponent = rhs;
      mpCN = mpComponent ? mpComponent->getCN() : std::make_shared< std::string >();
    }

  return *this;
}

bool CCommonName::operator ==(const CCommonName & rhs) const
{
  return *mpCN == *rhs.mpCN;
}

bool CCommonName::operator !=(const CCommonName & rhs) const
{
  return *mpCN != *rhs.mpCN;
}

bool CCommonName::operator <(const CCommonName & rhs) const
{
  return *mpCN < *rhs.mpCN;
}

const CObjectInterface * CCommonName::resolve(const CDataContainer * pContainer) const
{
  if (mpCN->empty()
      || pContainer == nullptr)
    return nullptr;

  if (mpComponent == nullptr)
    {
      mpComponent = createComponent(*mpCN);

      if (mpComponent == nullptr)
        return nullptr;

      mpCN = mpComponent->getCN();
    }

  if (!mpComponent->mayHaveAncestor(pContainer))
    {
      // We may have a math container
      if (dynamic_cast< const CMathContainer * >(pContainer) != nullptr)
        {
          const CMathContainer * pMathContainer = static_cast< const CMathContainer * >(pContainer);
          const CObjectInterface * pObject = resolve(&pMathContainer->getModel());
          const CObjectInterface * pMathObject = pMathContainer->getMathObject(pObject);

          return (pMathObject != nullptr) ? pMathObject : pObject;
        }

      if (mpComponent->getPartialCN() == "Reference=Avogadro Constant")
        {
          const CModel * pModel = dynamic_cast< const CModel * >(pContainer);

          if (pModel == nullptr)
            {
              const CDataModel * pDataModel = pContainer->getObjectDataModel();

              if (pDataModel != nullptr)
                pModel = pDataModel->getModel();
            }

          if (pModel != nullptr)
            {
              const CObjectInterface * pObject = pModel->getObject(mpComponent->getPartialCN());

              if (pObject != nullptr)
                {
                  mpComponent = pObject->getCNComponent();
                  mpCN = mpComponent->getCN();
                }

              return pObject;
            }
        }

      return nullptr;
    }

  const CObjectInterface * pObject = mpComponent->getObject();

  if (!mpComponent->isResolved()
      || !mpComponent->hasAncestor(pContainer))
    {
      const std::string & ContainerPartialCN = pContainer->getCNComponent()->getPartialCN();
      std::vector< CCommonNameComponent::shared_ptr > Components = mpComponent->getComponentList();
      CCommonNameComponent::shared_ptr resolved = nullptr;

      for (auto it = Components.rbegin(); it != Components.rend(); ++it)
        {
          // Find the container component matching this component
          if (!resolved)
            {
              if (ContainerPartialCN == (*it)->getPartialCN())
                // This may lead to a structural change of the CN, e.g., an absolute CN may become relative
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

      if (!resolved)
        {
          // This handles static strings and separators
          const CObjectInterface * pObject = pContainer->getObject(mpComponent->getPartialCN());

          if (pObject != nullptr)
            resolved = pObject->getCNComponent();
        }

      // We need to handle the root container objects like functions and unit definitions
      if (!resolved)
        {
          const CDataContainer * pRoot = CRootContainer::getRoot();

          if (pRoot != pContainer)
            return CCommonName::resolve(pRoot);
        }

      // We have resolved the full common name
      if (resolved)
        {
          pObject = resolved->getObject();

          if (mpCN->find(*resolved->getCN()) == 0)
            {
              mpComponent = resolved;
              mpCN = mpComponent->getCN();
            }
        }
    }

  if (pObject == nullptr
      && mpComponent->isValid())
    std::cout << *mpCN << std::endl;

  return pObject;
}

CCommonNameComponent::shared_ptr CCommonName::findAncestorCandidate(const CDataContainer * pContainer) const
{
  if (pContainer == nullptr)
    return nullptr;

  const std::string & ContainerPartialCN = pContainer->getCNComponent()->getPartialCN();
  std::vector< CCommonNameComponent::shared_ptr > Components = mpComponent->getComponentList();

  for (auto it = Components.rbegin(); it != Components.rend(); ++it)
    if (ContainerPartialCN == (*it)->getPartialCN())
      return pContainer->getCNComponent();

  return nullptr;
}

bool CCommonName::isResolved() const
{
  return mpComponent != nullptr && mpComponent->isResolved();
}

bool CCommonName::hasAncestor(const CDataContainer * pContainer) const
{
  if (mpComponent)
    return mpComponent->hasAncestor(pContainer);

  return false;
}

bool CCommonName::mayHaveAncestor(const CDataContainer * pContainer) const
{
  if (mpComponent)
    return mpComponent->mayHaveAncestor(pContainer);

  return findAncestorCandidate(pContainer) != nullptr;
}

bool CCommonName::isValid() const
{
  if (mpComponent == nullptr)
    mpComponent = createComponent(*mpCN);

  if (mpComponent)
    return mpComponent->isValid();

  return false;
}

const CObjectInterface * CCommonName::getObject() const
{
  return mpComponent ? mpComponent->getObject() : nullptr;
}

void CCommonName::refresh() const
{
  if (mpComponent)
    mpCN = mpComponent->getCN();
}

// explicit
CCommonName::operator std::string() const
{
  return *mpCN;
}

bool CCommonName::empty() const
{
  return mpCN->empty();
}

bool CCommonName::operator ==(const std::string & rhs) const
{
  return *mpCN == rhs;
}

bool CCommonName::operator !=(const std::string & rhs) const
{
  return *mpCN != rhs;
}

CCommonName & CCommonName::operator +=(const std::string & rhs)
{
  if (!rhs.empty())
    {
      mpComponent = nullptr;
      mpCN = std::make_shared< std::string >(*mpCN + rhs);
    }

  return *this;
}

std::string CCommonName::operator +(const std::string & rhs) const
{
  return *mpCN + rhs;
}

std::string::size_type CCommonName::size() const
{
  return mpCN->size();
}

void CCommonName::clear()
{
  mpComponent = nullptr;
  mpCN->clear();
}

const char* CCommonName::c_str() const
{
  return mpCN->c_str();
}

std::string CCommonName::getPrimary() const
{
  return mpCN->substr(0, findNext(","));
}

std::string CCommonName::getRemainder() const
{
  if (mpCN->empty())
    return "";

  std::string Separator = ",";

  if (mpCN->at(0) != '[')
    Separator += "[";

  std::string::size_type pos = findNext(Separator);

  if (pos == std::string::npos)
    return "";

  if (mpCN->at(pos) == ',') pos++;

  return mpCN->substr(pos);
}

std::string CCommonName::getObjectType() const
{
  std::string Primary(getPrimary());

  return unescape(Primary.substr(0, CCommonNameComponent::findNext(Primary, "=")));
}

std::string CCommonName::getObjectName() const
{
  std::string Primary = getPrimary();
  std::string::size_type pos = CCommonNameComponent::findNext(Primary, "=");

  if (pos == std::string::npos) return "";

  std::string tmp = Primary.substr(pos + 1);

  if (getObjectType() != "String")
    tmp = tmp.substr(0, CCommonNameComponent::findNext(tmp, "["));

  return unescape(tmp);
}

size_t CCommonName::getElementIndex(const size_t & pos) const
{
  return CCommonNameComponent::getElementIndex(*mpCN, pos);
}

std::string CCommonName::getElementName(const size_t & pos,
                                        const bool & unescape) const
{
  return CCommonNameComponent::getElementName(*mpCN, pos, unescape);
}

void CCommonName::split(CCommonName & parentCN, std::string & objectType, std::string & objectName, std::string * pPartialCN) const
{
  std::string::size_type LastComma = findPrevious(",");
  CCommonName Primary;

  if (LastComma != std::string::npos)
    {
      parentCN = mpCN->substr(0, LastComma);
      Primary = mpCN->substr(LastComma + 1);
    }
  else
    {
      parentCN = "";
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

          if (!parentCN.empty())
            parentCN += ",";

          parentCN +=  escape(Primary.getObjectType()) + "=" + escape(Primary.getObjectName());
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
          objectType = CCommonNameComponent::ObjectTypeFromVectorName(Primary.getObjectName());

          if (!parentCN.empty())
            parentCN += ",";

          parentCN += escape(Primary.getObjectType()) + "=" + escape(Primary.getObjectName());
        }
    }
  else
    {
      objectName = Primary.getObjectName();
    }

  if (pPartialCN != nullptr)
    {
      pPartialCN->assign(mpCN->substr(parentCN.size()));

      if (pPartialCN->size()
          && pPartialCN->front() == ',')
        pPartialCN->assign(pPartialCN->substr(1));
    }

  return;
}

// static
std::string CCommonName::escape(const std::string & name)
{
  return CCommonNameComponent::escape(name);
}

// static
std::string CCommonName::unescape(const std::string & name)
{
  return CCommonNameComponent::unescape(name);
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
      CN += "[" + escape(objectName) + "]";
    }
  else
    {
      CN += "," + escape(objectType) + "=" + escape(objectName);
    }

  return *CN.mpCN;
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
  return CCommonNameComponent::findNext(*mpCN, toFind, pos);
}

std::string::size_type CCommonName::findPrevious(const std::string & toFind,
    const std::string::size_type & pos) const
{
  return CCommonNameComponent::findPrevious(*mpCN, toFind, pos);
}

bool operator ==(const std::string & lhs, const CCommonName & rhs)
{
  return rhs.operator ==(lhs);
}

bool operator !=(const std::string & lhs, const CCommonName & rhs)
{
  return rhs.operator !=(lhs);
}

std::string operator +(const std::string & lhs, const CCommonName & rhs)
{
  return lhs + std::string(rhs);
}

std::ostream & operator <<(std::ostream & os, const CCommonName & cn)
{
  os << std::string(cn);

  return os;
}
