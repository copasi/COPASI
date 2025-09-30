// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/core/CCommonNameComponent.h"
#include "copasi/core/CCommonName.h"
#include "copasi/utilities/CCopasiParameter.h"
#include "copasi/utilities/utility.h"

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

// static
std::string CCommonNameComponent::ObjectTypeFromVectorName(const std::string & name)
{
  auto it = VectorName2ObjectType.find(name);

  if (it != VectorName2ObjectType.end())
    return it->second;

  return " "; // This is an invalid type
}

CCommonNameComponent::CCommonNameComponent(const CDataObject * pObject)
  : mPartialCN()
  , mType(pObject->getObjectType())
  , mName(pObject->getObjectName())
  , mpParent((pObject->getObjectParent() != nullptr
              && pObject->getObjectType() != "CN")
               ? pObject->getObjectParent()->getCNComponent()
               : nullptr)
  , mpObject(pObject)
  , mChildren()
{
  updatePartialCN();

  if (mpParent)
    mpParent->addChild(this);
}

CCommonNameComponent::CCommonNameComponent(const std::string & partialCN,
                                           const std::string & type,
                                           const std::string & name,
                                           const std::shared_ptr< CCommonNameComponent > & parent)
  : mPartialCN(partialCN)
  , mType(type)
  , mName(name)
  , mpParent(parent)
  , mpObject(nullptr)
  , mChildren()
{
  updatePartialCN();

  if (mpParent)
    mpParent->addChild(this);
}

CCommonNameComponent::~CCommonNameComponent()
{
  assert(mpObject == nullptr);

  if (mpParent)
    mpParent->removeChild(this);
}

// static
CCommonNameComponent::shared_ptr CCommonNameComponent::create(const CDataObject * pObject)
{
  assert(pObject != nullptr);
  return shared_ptr(new CCommonNameComponent(pObject));
}

// static
CCommonNameComponent::shared_ptr CCommonNameComponent::create(const std::string & partialCN,
                                                              const std::string & type,
                                                              const std::string & name,
                                                              const std::shared_ptr< CCommonNameComponent > & parent)
{
  std::string Name = name;

  // String and Separator must not be sanitized.
  if (type != "String"
      && type != "Separator")
    CDataObject::sanitizeObjectName(Name);

  std::string Type = type;
  CDataObject::sanitizeObjectName(Type);

  return shared_ptr(new CCommonNameComponent(partialCN, Type, Name, parent));
}

std::vector< CCommonNameComponent::shared_ptr > CCommonNameComponent::getComponentList() const
{
  std::vector< shared_ptr > Components;

  shared_ptr pComponent = const_cast< CCommonNameComponent * >(this)->shared_from_this();

  while (pComponent)
    {
      Components.push_back(pComponent);
      pComponent = pComponent->mpParent;
    }

  return Components;
}

void CCommonNameComponent::addChild(const CCommonNameComponent * pChild)
{
#pragma omp critical (common_name_component_children)
  mChildren.insert(pChild);
}

void CCommonNameComponent::removeChild(const CCommonNameComponent * pChild)
{
#pragma omp critical (common_name_component_children)
  mChildren.erase(pChild);
}

void CCommonNameComponent::signalObjectDeleted()
{
  *const_cast< CDataObject ** >(&mpObject) = nullptr;
}

void CCommonNameComponent::signalChanged()
{
  // We must not use getCN() which would return the stored value if it exists
  // It is assumed that an existing CN is correct. This is the time to update.
  cn_ptr pCN = mpCN.lock();

  if (!pCN)
    pCN = std::make_shared< std::string >();

  *pCN = getParentCN();
  appendPartialCN(pCN);

  mpCN = pCN;

#pragma omp critical (common_name_component_children)
  for (auto & pChild : mChildren)
    pChild->signalParentCNChanged(pCN);
}

void CCommonNameComponent::signalObjectNameChanged()
{
  if (mpObject != nullptr)
    mName = mpObject->getObjectName();

  if (updatePartialCN())
    signalChanged();
}

void CCommonNameComponent::signalObjectParentChanged()
{
  if (mpObject != nullptr)
    {
      // We must never set the object parent to null since this would break persistence.
      if (mpObject->getObjectParent() != nullptr
          && mpParent != mpObject->getObjectParent()->getCNComponent())
        {
          if (mpParent)
            mpParent->removeChild(this);

          mpParent = mpObject->getObjectParent()->getCNComponent();

          if (mpParent)
            mpParent->addChild(this);

          updatePartialCN();
          signalChanged();
        }
    }
}

CCommonNameComponent::cn_ptr CCommonNameComponent::getCN() const
{
  cn_ptr pCN = mpCN.lock();

  if (pCN)
    return pCN;

  pCN = std::make_shared< std::string >();
  mpCN = pCN;

  *pCN = getParentCN();
  appendPartialCN(pCN);

  // Just retrieving the CN does not change children's CN

  return pCN;
}

const std::string & CCommonNameComponent::getPartialCN() const
{
  return mPartialCN;
}

const std::string & CCommonNameComponent::getObjectName() const
{
  return mName;
}

const std::string & CCommonNameComponent::getObjectType() const
{
  return mType;
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

  while (p)
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

  // String and Separator may have any ancestor.
  if (mType == "String"
      || mType == "Separator")
    return true;

  cn_ptr pCN = getCN();
  std::string AncestorCN = pAncestor->getCNComponent()->getPartialCN();

  return pCN->find(AncestorCN) != std::string::npos;
}

bool CCommonNameComponent::isValid() const
{
  return isResolved()
         || mpParent
         || (!mType.empty()
             && !mName.empty());
}

std::string CCommonNameComponent::getParentCN() const
{
  return mpParent
         && mPartialCN != "CN=Root"
         && mType != "String"
         && mType != "Separator"
           ? *mpParent->getCN()
           : "";
}

void CCommonNameComponent::signalParentCNChanged(CCommonNameComponent::cn_ptr pParentCN) const
{
  cn_ptr pCN = mpCN.lock();

  if (!pCN)
    pCN = std::make_shared< std::string >();

  *pCN = *pParentCN;
  appendPartialCN(pCN);

  for (auto & pChild : mChildren)
    pChild->signalParentCNChanged(pCN);
}

void CCommonNameComponent::appendPartialCN(cn_ptr pParentCN) const
{
  if (pParentCN->empty())
    *pParentCN = mPartialCN;
  else if (mPartialCN.size()
           && mPartialCN.front() == '[')
    *pParentCN += mPartialCN;
  else
    *pParentCN += "," + mPartialCN;
}

bool CCommonNameComponent::updatePartialCN() {
  std::string OldPartialCN = mPartialCN;

  // Root object
  if (mType == "CN")
    {
      mPartialCN = "CN=Root";
    }
  // Vector element
  else if (mType == getObjectTypeFromParent())
    {
      if (!mpParent
          || mpParent->mpObject == nullptr)
        {
          // We rely on the current form of the CN
          if (mPartialCN.size()
              && mPartialCN.front() == '[')
            {
              // We might have an index or a name
              if (mPartialCN.find_first_not_of("0123456789]", 1) == std::string::npos)
                mPartialCN = "[" + escape(mName) + "]";
              // else we have an index and must rely on it, i.e., nothing to do
            }
          else
            mPartialCN = escape(mType) + "=" + escape(mName);
        }
      else if (mpParent->mpObject->hasFlag(CDataObject::NameVector))
        mPartialCN = "[" + escape(mName) + "]";
      else
        {
          size_t Index = static_cast< const CDataContainer * >(mpParent->mpObject)->getIndex(mpObject);

          if (Index != C_INVALID_INDEX)
            mPartialCN = "[" + std::to_string(Index) + "]";
          else
            mPartialCN = escape(mType) + "=" + escape(mName);
        }
    }
  // Special case for parameters in parameter groups
  else if ((mType == "Parameter"
       || mType == "ParameterGroup")
      && (mpParent
          && mpParent->mpObject != nullptr
          && dynamic_cast< const CCopasiParameterGroup * >(mpParent->mpObject) != nullptr))
    {
      mPartialCN = escape(mType) + "="
        + escape(static_cast< const CCopasiParameterGroup * >(mpParent->mpObject)->getUniqueParameterName(static_cast< const CCopasiParameter * >(mpObject)));
    }
  // Special case for element references
  else if (mType == "ElementReference")
    {
      mPartialCN = mName;
    }
  // Objects with no name are an edge case where CN contains values
  else if (mName.empty())
    {
      mPartialCN = mType;
    }
  // Default case
  else
    mPartialCN = escape(mType) + "=" + escape(mName);

  if (mpObject != nullptr
      && mPartialCN == "Property=DisplayName")
    mpObject->getObjectDisplayName();

  return OldPartialCN != mPartialCN;
}

std::string CCommonNameComponent::getObjectTypeFromParent() const
{
  if (mpParent
      && mpParent->mType == "Vector")
    return ObjectTypeFromVectorName(mpParent->mName);

  return " "; // This is an invalid type.
}

// static
std::string::size_type CCommonNameComponent::findNext(const std::string & cn,
                                                      const std::string & toFind,
                                                      const std::string::size_type & pos)
{
  std::string::size_type where = cn.find_first_of(toFind, pos);

  std::string::size_type tmp;

  while (where
         && where != std::string::npos)
    {
      tmp = cn.find_last_not_of("\\", where - 1);

      if ((where - tmp) % 2)
        return where;

      where = cn.find_first_of(toFind, where + 1);
    }

  return where;
}

// static
std::string::size_type CCommonNameComponent::findPrevious(const std::string & cn,
                                                          const std::string & toFind,
                                                          const std::string::size_type & pos)
{
  std::string::size_type where = cn.find_last_of(toFind, pos);

  std::string::size_type tmp;

  while (where
         && where != std::string::npos)
    {
      tmp = cn.find_last_not_of("\\", where - 1);

      if ((where - tmp) % 2)
        return where;

      where = cn.find_last_of(toFind, where - 1);
    }

  return where;
}

// static
size_t CCommonNameComponent::getElementIndex(const std::string & cn,
                                             const size_t & pos)
{
  size_t Index = C_INVALID_INDEX;

  if (strToIndex(getElementName(cn, pos), Index))
    return Index;

  return C_INVALID_INDEX;
}

// static
std::string CCommonNameComponent::getElementName(const std::string & cn,
                                                 const size_t & pos,
                                                 const bool & unescape)
{
  std::string::size_type open = findNext(cn, "[");

  for (size_t i = 0; i < pos && open != std::string::npos; i++)
    open = findNext(cn, "[", open + 1);

  std::string::size_type close = findNext(cn, "]", open + 1);

  if (open == std::string::npos
      || close == std::string::npos)
    return "";

  if (unescape)
    return CCommonNameComponent::unescape(cn.substr(open + 1, close - open - 1));

  return cn.substr(open + 1, close - open - 1);
}

std::string CCommonNameComponent::escape(const std::string & name)
{
  static const std::string toBeEscaped("\\[]=,>");

  std::string Escaped(name);
  std::string::size_type pos = Escaped.find_first_of(toBeEscaped);

  while (pos != std::string::npos)
    {
      Escaped.insert(pos, "\\");
      pos += 2;
      pos = Escaped.find_first_of(toBeEscaped, pos);
    }

  return Escaped;
}

std::string CCommonNameComponent::unescape(const std::string & name)
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
