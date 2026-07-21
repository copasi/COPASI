// Copyright (C) 2025 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/core/CCommonNameComponent.h"
#include "copasi/core/CCommonName.h"
#include "copasi/core/CArrayElementReference.h"
#include "copasi/utilities/CCopasiParameter.h"
#include "copasi/utilities/utility.h"

// static
const std::map< std::string, std::string > CCommonNameComponent::VectorName2ObjectType = {
  {"Compartments", "Compartment"},
  {"Events", "Event"},
  {"Fitted Points", "Fitted Point"},
  {"Functions", "Function"},
  {"ListOfLayouts", "Layout"},
  {"ListOflayouts", "Layout"},
  {"Metabolites", "Metabolite"},
  {"ModelList", "CN"},
  {"Moieties", "Moiety"},
  {"OutputDefinitions", "PlotItem"},
  {"ParameterSets", "ModelParameterSet"},
  {"Reactions", "Reaction"},
  {"Reduced Model Metabolites", "Metabolite"},
  {"ReportDefinitions", "ReportDefinition"},
  {"TaskList", "Task"},
  {"Units list", "Unit"},
  {"Values", "ModelValue"}
};

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
  , mpCN()
  , mChildren()
  , mDependents()
  , mPrerequisites()
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
  , mpCN()
  , mChildren()
  , mDependents()
  , mPrerequisites()
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

  clearPrerequisites();
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

  std::string PartialCN = partialCN;

  if (Type == "Property")
    {
      Type = "Reference";
      PartialCN = Type +  "="  + Name;
    }

  return shared_ptr(new CCommonNameComponent(PartialCN, Type, Name, parent));
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
  std::string NewCN = buildStringCN();

  cn_ptr pCN = mpCN.lock();

  if (pCN)
    *pCN = NewCN;

#pragma omp critical (common_name_component_children)
  for (auto & pChild : mChildren)
    pChild->signalParentCNChanged(NewCN);

#pragma omp critical (common_name_component_dependent)
  for (auto & pDependent : mDependents)
    pDependent->signalPrerequisiteChanged(const_cast< CCommonNameComponent * >(this)->shared_from_this());
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
  cn_ptr pCN;

  if (! (pCN = mpCN.lock()))
#pragma omp critical (common_name_component_cn)
    if (! (pCN = mpCN.lock()))
      {
        pCN = std::make_shared< std::string >();
        *pCN = buildStringCN();
        mpCN = pCN;
      }

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

bool CCommonNameComponent::hasAncestor(const CDataObject *  pAncestor) const
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

bool CCommonNameComponent::mayHaveAncestor(const CDataObject *  pAncestor) const
{
  if (pAncestor == nullptr)
    return false;

  // String and Separator may have any ancestor.
  if (mType == "String"
      || mType == "Separator")
    return true;

  const std::string & Type = pAncestor->getObjectType();
  const std::string & Name = pAncestor->getObjectName();
  std::shared_ptr< const CCommonNameComponent > p = shared_from_this();

  while (p)
    {
      if (p->getObjectType() == Type
          && p->getObjectName() == Name)
        return true;

      p = p->mpParent;
    }

  return false;
}

bool CCommonNameComponent::isValid() const
{
  return isResolved()
         || mpParent
         || (!mType.empty()
             && !mName.empty())
         || (mPartialCN.size() > 2
             && mPartialCN.front() == '['
             && mPartialCN.back() == ']');
}

size_t CCommonNameComponent::size() const
{
  size_t Size = 0;
  std::shared_ptr< const CCommonNameComponent > pComponent = shared_from_this();

  while (pComponent)
    {
      ++Size;
      pComponent = pComponent->mpParent;
    }

  return Size;
}

std::string CCommonNameComponent::buildStringCN() const
{
  std::vector< CCommonNameComponent::shared_ptr > Components = getComponentList();
  std::string CN;

  for (auto it = Components.rbegin(); it != Components.rend(); ++it)
    {
      if ((*it)->mPartialCN == "CN=Root"
          || (*it)->mType == "String"
          || (*it)->mType == "Separator")
        CN.clear();

      CN = append(CN, (*it)->mPartialCN);
    }

  return CN;
}

void CCommonNameComponent::signalParentCNChanged(const std::string & parentCN) const
{
  std:: string NewCN = append(parentCN, mPartialCN);

  cn_ptr pCN = mpCN.lock();

  if (pCN)
    *pCN = NewCN;

  for (auto & pChild : mChildren)
    pChild->signalParentCNChanged(NewCN);
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

void CCommonNameComponent::addPrerequisite(shared_ptr pPrerequisite)
{
  if (pPrerequisite)
    {
      mPrerequisites.push_back(pPrerequisite);
      pPrerequisite->addDependent(this);
    }
}

void CCommonNameComponent::clearPrerequisites()
{
  for (auto & pPrerequisite: mPrerequisites)
    if (pPrerequisite)
      pPrerequisite->removeDependent(this);

  mPrerequisites.clear();
}

void CCommonNameComponent::addDependent(const CCommonNameComponent * pDependent)
{
#pragma omp critical (common_name_component_dependent)
  mDependents.insert(pDependent);
}

void CCommonNameComponent::removeDependent(const CCommonNameComponent * pDependent)
{
#pragma omp critical (common_name_component_dependent)
  mDependents.erase(pDependent);
}

void CCommonNameComponent::signalPrerequisiteChanged(shared_ptr /* prerequisite */) const
{
  if (mType == "ElementReference"
      && mpObject != nullptr)
    {
      const CArrayElementReference * pObject = dynamic_cast< const CArrayElementReference * >(mpObject);
      pObject->updateObjectName();
    }
}

std::string CCommonNameComponent::getObjectTypeFromParent() const
{
  if (mpParent
      && mpParent->mType == "Vector")
    return ObjectTypeFromVectorName(mpParent->mName);

  return " "; // This is an invalid type.
}

// static
std::string CCommonNameComponent::append(const std::string & parentCN, const std::string & partialCN)
{
  std::string CN = parentCN;

  if (parentCN.empty()
      || partialCN.find("String=") == 0)
    CN = partialCN;
  else if ((parentCN.size()
            && parentCN.back() == ',')
           || (partialCN.size()
               && (partialCN.front() == ','
                   || partialCN.front() == '[')))
    CN += partialCN;
  else
    CN += "," + partialCN;

  return CN;
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
