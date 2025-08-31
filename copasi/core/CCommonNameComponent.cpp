// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/core/CCommonNameComponent.h"
#include "copasi/core/CCommonName.h"
#include "copasi/utilities/CCopasiParameter.h"

// static
const std::map< std::string, std::string > CCommonNameComponent::VectorName2ObjectType = {
  {"Compartments", "Compartment"},
  {"Metabolites", "Metabolite"},
  {"Reduced Model Metabolites", "Metabolite"},
  {"Reactions", "Reaction"},
  {"Events", "Event"},
  {"Values", "ModelValue"},
  {"ParameterSets", "ModelParameterSet"},
  {"Moieties", "Moiety"},
  {"ListOflayouts", "Layout"},
  {"TaskList", "Task"},
  {"ReportDefinitions", "ReportDefinition"},
  {"OutputDefinitions", "PlotItem"},
  {"Functions", "Function"},
  {"ModelList", "CN"},
  {"Units list", "Unit"}};

CCommonNameComponent::CCommonNameComponent(const CDataObject * pObject)
  : mPartialCN()
  , mType(pObject->getObjectType())
  , mName(pObject->getObjectName())
  , mpParent((pObject->getObjectParent() != nullptr
              && pObject->getObjectType() != "CN")
               ? pObject->getObjectParent()->getCNComponent()
               : nullptr)
  , mpObject(pObject)
{
  updatePartialCN();
}

CCommonNameComponent::CCommonNameComponent(const std::string & type,
                                           const std::string & name,
                                           const std::shared_ptr< CCommonNameComponent > & parent)
    : mPartialCN()
    , mType(type)
    , mName(name)
    , mpParent(parent)
    , mpObject(nullptr)
  {
    updatePartialCN();
  }

CCommonNameComponent::~CCommonNameComponent()
{
  assert(mpObject == nullptr);
}

// static
CCommonNameComponent::shared_ptr CCommonNameComponent::create(const CDataObject * pObject)
{
  assert(pObject != nullptr);
  return shared_ptr(new CCommonNameComponent(pObject));
}

// static
CCommonNameComponent::shared_ptr CCommonNameComponent::create(const std::string & type,
                                                              const std::string & name,
                                                              const std::shared_ptr< CCommonNameComponent > & parent)
{
  return shared_ptr(new CCommonNameComponent(type, name, parent));
}

std::string CCommonNameComponent::operator()() const
{
  return getCN();
}

std::vector< CCommonNameComponent::shared_ptr > CCommonNameComponent::getComponentList() const
{
  std::vector< shared_ptr > Components;

  shared_ptr pComponent = const_cast< CCommonNameComponent * >(this)->shared_from_this();

  while (pComponent != nullptr)
    {
      Components.push_back(pComponent);
      pComponent = pComponent->mpParent;
    }

  return Components;
}

void CCommonNameComponent::signalObjectDeleted()
{
  *const_cast< CDataObject ** >(&mpObject) = nullptr;
}

void CCommonNameComponent::signalObjectNameChanged()
{
  if (mpObject != nullptr)
    mName = mpObject->getObjectName();

  updatePartialCN();
}

void CCommonNameComponent::signalObjectParentChanged()
{
  if (mpObject != nullptr)
    {
      // We must never set the object parent to null since this would break persistence.
      if (mpObject->getObjectParent() != nullptr
          && mpParent != mpObject->getObjectParent()->getCNComponent())
        {
          mpParent = mpObject->getObjectParent()->getCNComponent();
          updatePartialCN();
        }
    }
}

std::string CCommonNameComponent::getCN() const
{
  std::string CN = (mpParent != nullptr
                    && mPartialCN != "CN=Root")
                     ? mpParent->getCN()
                     : "";

  if (CN.empty())
    return mPartialCN;

  if (mPartialCN.front() == '[')
    return CN + mPartialCN;

  return CN + "," + mPartialCN;
}

const std::string & CCommonNameComponent::getPartialCN() const
{
  return mPartialCN;
}

const CDataObject * CCommonNameComponent::getObject()
{
  return mpObject;
}

bool CCommonNameComponent::isResolved() const
{
  return mpObject != nullptr;
}

bool CCommonNameComponent::hasAncestor(const CDataContainer * pAncestor) const
{
  if (pAncestor == nullptr
      || mpObject == nullptr)
    return false;

  if (mpObject == pAncestor)
    return true;

  shared_ptr p = mpParent;

  while (p != nullptr)
    {
      if (p->getObject() == pAncestor)
        return true;

      p = p->mpParent;
    }

  return false;
}

bool CCommonNameComponent::mayHaveAncestor(const CDataContainer * pAncestor) const
{
  if (pAncestor == nullptr)
    return false;

  std::string CN = getCN();
  std::string AncestorCN = pAncestor->getCNComponent()->getCN();

  return CN.find(AncestorCN) == 0;
}

void CCommonNameComponent::updatePartialCN() {
  // Root object
  if (mType == "CN")
    {
      mPartialCN = "CN=Root";
      return;
    }

  // Vector element
  if (mType == getObjectTypeFromParent())
    {
      if (mpParent == nullptr
          || mpParent->mpObject == nullptr)
        {
          // We rely on the current form of the CN
          if (mPartialCN.front() == '[')
            {
              // We might have an index or a name
              if (mPartialCN.find_first_not_of("0123456789]") == std::string::npos)
                mPartialCN = "[" + CCommonName::escape(mName) + "]";
              // else we have an index and must rely on it
            }
          else
            mPartialCN = CCommonName::escape(mType) + "=" + CCommonName::escape(mName);
        }
      else if (mpParent->mpObject->hasFlag(CDataObject::NameVector))
        mPartialCN = "[" + CCommonName::escape(mName) + "]";
      else
        {
          size_t Index = static_cast< const CDataContainer * >(mpParent->mpObject)->getIndex(mpObject);

          if (Index != C_INVALID_INDEX)
            mPartialCN = "[" + std::to_string(Index) + "]";
          else
            mPartialCN = CCommonName::escape(mType) + "=" + CCommonName::escape(mName);
        }

      return;
    }

  // Special case for parameters in parameter groups
  if ((mType == "Parameter"
       || mType == "ParameterGroup")
      && (mpParent != nullptr
          && mpParent->mpObject != nullptr
          && dynamic_cast< const CCopasiParameterGroup * >(mpParent->mpObject) != nullptr))
    {
      mPartialCN = CCommonName::escape(mType) + "="
        + CCommonName::escape(static_cast< const CCopasiParameterGroup * >(mpParent->mpObject)->getUniqueParameterName(static_cast< const CCopasiParameter * >(mpObject)));
      return;
    }

  // Special case for element references
  if (mType == "ElementReference")
    {
      mPartialCN = mName;
      return;
    }

  // Default case
  mPartialCN = CCommonName::escape(mType) + "=" + CCommonName::escape(mName);
  return;
}

std::string CCommonNameComponent::getObjectTypeFromParent() const
{
  if (mpParent != nullptr
      && mpParent->mType == "Vector")
    {
      auto it = VectorName2ObjectType.find(mpParent->mName);

      if (it != VectorName2ObjectType.end())
        return it->second;
    }

  return "";
}
