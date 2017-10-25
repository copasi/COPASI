// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CCopasiParameterGroup class.
 *  This class is used to describe parameters. This class is intended
 *  to be used with integration or optimization methods or reactions.
 *
 *  Created for COPASI by Stefan Hoops 2002
 */

#include <sstream>

#include "copasi.h"

#include "CCopasiParameterGroup.h"

#include "undo/CData.h"
#include "CCopasiMessage.h"

#include "utilities/utility.h"

CCopasiParameterGroup::name_iterator::name_iterator():
  mpGroup(NULL),
  mNameEnd(true),
  mName(),
  mObjectEnd(true),
  mObject(),
  mParameterEnd(true),
  mParameter()
{}

CCopasiParameterGroup::name_iterator::name_iterator(const CCopasiParameterGroup & group,
    const bool & begin):
  mpGroup(&group),
  mNameEnd(true),
  mName(),
  mObjectEnd(true),
  mObject(),
  mParameterEnd(true),
  mParameter()
{
  if (mpGroup != NULL &&
      mpGroup->mObjects.begin() != mpGroup->mObjects.end())
    {
      if (begin)
        {
          mNameEnd = false;
          mName = reinterpret_cast< objectMap::data * >(const_cast< objectMap * >(&mpGroup->mObjects))->begin();

          if (!mName->second.empty())
            {
              mObjectEnd = false;
              mObject = mName->second.begin();

              if (mName->second.size() > 1)
                {
                  mParameterEnd = false;
                  mParameter = mpGroup->beginIndex();

                  while (mParameter != mpGroup->endIndex() &&
                         (*mParameter)->getObjectName() != mName->first)
                    ++mParameter;

                  if (mParameter == mpGroup->endIndex())
                    mParameterEnd = true;
                }
            }
        }
    }
}

CCopasiParameterGroup::name_iterator::name_iterator(const CCopasiParameterGroup::name_iterator & src):
  mpGroup(src.mpGroup),
  mNameEnd(src.mNameEnd),
  mName(src.mName),
  mObjectEnd(src.mObjectEnd),
  mObject(src.mObject),
  mParameterEnd(src.mParameterEnd),
  mParameter(src.mParameter)
{}

CCopasiParameterGroup::name_iterator::~name_iterator()
{}

CDataObject * CCopasiParameterGroup::name_iterator::operator*() const
{
  if (!mParameterEnd)
    return *mParameter;

  if (!mObjectEnd)
    return *mObject;

  return NULL;
}

CDataObject * CCopasiParameterGroup::name_iterator::operator->() const
{
  if (!mParameterEnd)
    return *mParameter;

  if (!mObjectEnd)
    return *mObject;

  return NULL;
}

CCopasiParameterGroup::name_iterator & CCopasiParameterGroup::name_iterator::operator++()
{
  // We first advance through all parameters
  if (!mParameterEnd)
    {
      ++mParameter;

      // We skip parameters which name is not matching
      while (mParameter != mpGroup->endIndex() &&
             (*mParameter)->getObjectName() != mName->first)
        ++mParameter;

      if (mParameter != mpGroup->endIndex())
        return *this;

      mParameterEnd = true;
    }
  else if (!mObjectEnd)
    {
      ++mObject;

      if (mObject == mName->second.end())
        mObjectEnd = true;
    }

  if (!mObjectEnd)
    {
      // We need to skip the parameters which have been handled above;
      while (mObject != mName->second.end() &&
             dynamic_cast< CCopasiParameter * >(*mObject) != NULL)
        ++mObject;

      if (mObject != mName->second.end())
        return *this;

      mObjectEnd = true;
    }

  if (!mNameEnd)
    {
      ++mName;

      if (mName != reinterpret_cast< objectMap::data * >(const_cast< objectMap * >(&mpGroup->mObjects))->end())
        {
          mObjectEnd = false;
          mObject = mName->second.begin();

          if (mName->second.size() > 1)
            {
              mParameterEnd = false;
              mParameter = mpGroup->beginIndex();

              while (mParameter != mpGroup->endIndex() &&
                     (*mParameter)->getObjectName() != mName->first)
                ++mParameter;

              if (mParameter == mpGroup->endIndex())
                mParameterEnd = true;
            }
        }
      else
        {
          mNameEnd = true;
        }
    }

  return *this;
}

CCopasiParameterGroup::name_iterator CCopasiParameterGroup::name_iterator::operator++(int)
{
  name_iterator Current(*this);
  operator++();

  return Current;
}

bool CCopasiParameterGroup::name_iterator::operator != (const CCopasiParameterGroup::name_iterator & rhs) const
{
  return (mpGroup != rhs.mpGroup ||
          mNameEnd != rhs.mNameEnd ||
          mObjectEnd != rhs.mObjectEnd ||
          mParameterEnd != rhs.mParameterEnd ||
          (!mNameEnd && mName != rhs.mName) ||
          (!mObjectEnd && mObject != rhs.mObject) ||
          (!mParameterEnd && mParameter != rhs.mParameter));
}

CCopasiParameterGroup::CCopasiParameterGroup():
  CCopasiParameter("NoName", GROUP),
  mpElementTemplates(NULL)
{}

CCopasiParameterGroup::CCopasiParameterGroup(const CCopasiParameterGroup & src,
    const CDataContainer * pParent):
  CCopasiParameter(src, pParent),
  mpElementTemplates(src.mpElementTemplates != NULL ? new CCopasiParameterGroup(*src.mpElementTemplates, this) : NULL)
{
  operator=(src);
}

CCopasiParameterGroup::CCopasiParameterGroup(const std::string & name,
    const CDataContainer * pParent,
    const std::string & objectType):
  CCopasiParameter(name, CCopasiParameter::GROUP, NULL, pParent, objectType),
  mpElementTemplates(NULL)
{}

CCopasiParameterGroup::~CCopasiParameterGroup()
{}

// virtual
CData CCopasiParameterGroup::toData() const
{
  CData Data = CCopasiParameter::toData();

  std::vector< CData > Value;

  elements::const_iterator it = static_cast< elements * >(mpValue)->begin();
  elements::const_iterator end = static_cast< elements * >(mpValue)->end();

  for (; it != end; ++it)
    {
      Value.push_back((*it)->toData());
    }

  Data.addProperty(CData::PARAMETER_VALUE, Value);

  return Data;
}

// virtual
bool CCopasiParameterGroup::applyData(const CData & data)
{
  bool success = CCopasiParameter::applyData(data);

  // This only inserts new parameters modification of existing parameters or their deletion
  // is handled by accessing them directly.
  if (data.isSetProperty(CData::PARAMETER_VALUE))
    {
      const std::vector< CData > & Value = data.getProperty(CData::PARAMETER_VALUE).toDataVector();

      std::vector< CData >::const_iterator it = Value.begin();
      std::vector< CData >::const_iterator end = Value.end();

      for (; it != end; ++it)
        {
          CCopasiParameter * pNew = CCopasiParameter::fromData(*it);
          success &= pNew->applyData(*it);

          static_cast< elements * >(mpValue)->push_back(pNew);
          CCopasiParameter::add(pNew, true);
        }
    }

  return success;
}

// virtual
CDataObject * CCopasiParameterGroup::insert(const CData & data)
{
  CCopasiParameter * pNew = CCopasiParameter::fromData(data);

  elements * pElements = static_cast< elements * >(mpValue);
  pElements->insert(pElements->begin() + std::min((size_t) data.getProperty(CData::OBJECT_INDEX).toUint(), pElements->size()), pNew);

  CCopasiParameter::add(pNew, true);

  return pNew;
}

// virtual
const CObjectInterface * CCopasiParameterGroup::getObject(const CCommonName & cn) const
{
  const CObjectInterface * pObjectInterface = CDataContainer::getObject(cn);

  if (pObjectInterface != NULL)
    {
      return pObjectInterface;
    }

  std::string UniqueName = cn.getObjectName();

  std::string::size_type pos = UniqueName.find_last_of('[');
  std::string Name = UniqueName.substr(0, pos);
  size_t Index = strToUnsignedInt(UniqueName.substr(pos + 1).c_str());
  size_t counter = C_INVALID_INDEX;

  index_iterator it = beginIndex();
  index_iterator end = endIndex();

  for (; it != end; ++it)
    {
      if ((*it)->getObjectName() == Name)
        {
          counter++;

          if (counter == Index)
            {
              return (*it)->getObject(cn.getRemainder());
            }
        }
    }

  return NULL;
}

bool CCopasiParameterGroup::elevateChildren() {return true;}

CCopasiParameterGroup & CCopasiParameterGroup::operator = (const CCopasiParameterGroup & rhs)
{
  // Check for assignment to itself
  if (this == &rhs) return *this;

  if (getObjectName() != rhs.getObjectName())
    setObjectName(rhs.getObjectName());

  mUserInterfaceFlag = rhs.mUserInterfaceFlag;
  mValidity = rhs.mValidity;

  name_iterator itRHS(rhs, true);
  name_iterator endRHS(rhs, false);

  name_iterator itLHS(*this, true);
  name_iterator endLHS(*this, false);

  std::vector< CCopasiParameter * > ToBeRemoved;
  std::map< size_t,  CCopasiParameter * > ToBeAdded;

  CCopasiParameter * pLHS;
  CCopasiParameter * pRHS;

  while (itRHS != endRHS && itLHS != endLHS)
    {
      // We only assign parameters
      if ((pRHS = dynamic_cast< CCopasiParameter * >(*itRHS)) == NULL)
        {
          ++itRHS;
          continue;
        }

      // We only assign parameters
      if ((pLHS = dynamic_cast< CCopasiParameter * >(*itLHS)) == NULL)
        {
          ++itLHS;
          continue;
        }

      const std::string & NameLHS = pLHS->getObjectName();
      const std::string & NameRHS = pRHS->getObjectName();

      // The LHS parameter is missing on the RHS thus we need to remove it
      if (NameLHS < NameRHS)
        {
          ToBeRemoved.push_back(pLHS);
          ++itLHS;
          continue;
        }

      // The RHS parameter is missing on the LHS thus we need to add it
      if (NameLHS > NameRHS)
        {
          ToBeAdded.insert(std::make_pair(rhs.getIndex(pRHS), pRHS));
          ++itRHS;
          continue;
        }

      // The names are equal it suffices to use the assignment operator of the parameter
      *pLHS = *pRHS;
      ++itLHS;
      ++itRHS;
    }

  // All remaining parameters of the LHS need to be removed
  while (itLHS != endLHS)
    {
      // We only assign parameters
      if ((pLHS = dynamic_cast< CCopasiParameter * >(*itLHS)) != NULL)
        ToBeRemoved.push_back(pLHS);

      ++itLHS;
    }

  // All remaining parameter of the RHS need to be added
  while (itRHS != endRHS)
    {
      // We only assign parameters
      if ((pRHS = dynamic_cast< CCopasiParameter * >(*itRHS)) != NULL)
        ToBeAdded.insert(std::make_pair(rhs.getIndex(pRHS), pRHS));

      ++itRHS;
    }

  // We remove the parameters
  std::vector< CCopasiParameter * >::const_iterator itToBeRemoved = ToBeRemoved.begin();
  std::vector< CCopasiParameter * >::const_iterator endToBeRemoved = ToBeRemoved.end();

  for (; itToBeRemoved != endToBeRemoved; ++itToBeRemoved)
    this->removeParameter(*itToBeRemoved);

  // We add the missing parameters
  CCopasiParameter * pParameter;
  std::map< size_t,  CCopasiParameter * >::const_iterator itToBeAdded = ToBeAdded.begin();
  std::map< size_t,  CCopasiParameter * >::const_iterator endToBeAdded = ToBeAdded.end();

  for (; itToBeAdded != endToBeAdded; ++itToBeAdded)
    {
      if (itToBeAdded->second->getType() == GROUP)
        pParameter = new CCopasiParameterGroup(* static_cast< CCopasiParameterGroup * >(itToBeAdded->second), NO_PARENT);
      else
        pParameter = new CCopasiParameter(*itToBeAdded->second, NO_PARENT);

      CCopasiParameter::add(pParameter, true);

      // Add the parameter to the proper location
      elements * pElements = static_cast< elements * >(mpValue);
      pElements->insert(pElements->begin() + std::min(itToBeAdded->first, pElements->size()), pParameter);
    }

  return *this;
}

void CCopasiParameterGroup::print(std::ostream * ostream) const
{*ostream << *this;}

std::ostream &operator<<(std::ostream &os, const CCopasiParameterGroup & o)
{
  os << "<<< Parameter Group: " << o.getObjectName() << std::endl;

  CCopasiParameterGroup::elements::const_iterator it = o.beginIndex();
  CCopasiParameterGroup::elements::const_iterator end = o.endIndex();

  for (; it != end; ++it)
    {
      (*it)->print(&os);
      os << std::endl;
    }

  os << ">>> Parameter Group: " << o.getObjectName() << std::endl;
  return os;
}

bool operator==(const CCopasiParameterGroup & lhs,
                const CCopasiParameterGroup & rhs)
{
  if (lhs.getObjectName() != rhs.getObjectName()) return false;

  if (lhs.size() != rhs.size()) return false;

  CCopasiParameterGroup::elements::const_iterator itLhs = lhs.beginIndex();
  CCopasiParameterGroup::elements::const_iterator endLhs = lhs.endIndex();
  CCopasiParameterGroup::elements::const_iterator itRhs = rhs.beginIndex();

  for (; itLhs != endLhs; ++itLhs, ++itRhs)
    if (!(**itLhs == **itRhs)) return false;

  return true;
}

bool CCopasiParameterGroup::addParameter(const CCopasiParameter & parameter)
{
  if (parameter.getType() == CCopasiParameter::GROUP)
    {
      CCopasiParameterGroup * pGroup =
        new CCopasiParameterGroup(*dynamic_cast<const CCopasiParameterGroup *>(&parameter), NO_PARENT);
      addParameter(pGroup);
    }
  else
    {
      CCopasiParameter * pParameter = new CCopasiParameter(parameter, NO_PARENT);
      addParameter(pParameter);
    }

  return true;
}

void CCopasiParameterGroup::addParameter(CCopasiParameter * pParameter)
{
  if (pParameter == NULL) return;

  pParameter->setUserInterfaceFlag(mUserInterfaceFlag & pParameter->getUserInterfaceFlag());

  CDataContainer::add(pParameter, true);
  static_cast< elements * >(mpValue)->push_back(pParameter);
}

CCopasiParameterGroup & CCopasiParameterGroup::getElementTemplates()
{
  if (mpElementTemplates == NULL)
    {
      mpElementTemplates = new CCopasiParameterGroup("Element Templates", this);
    }

  return *mpElementTemplates;
}

const CCopasiParameterGroup & CCopasiParameterGroup::getElementTemplates() const
{
  assert(mpElementTemplates != NULL);

  return *mpElementTemplates;
}

bool CCopasiParameterGroup::haveTemplate() const
{
  return (mpElementTemplates != NULL && mpElementTemplates->size() > 0);
}

// virtual
void CCopasiParameterGroup::setUserInterfaceFlag(const CCopasiParameter::UserInterfaceFlag & flag)
{
  CCopasiParameter::setUserInterfaceFlag(flag);

  elements::iterator it = beginIndex();
  elements::iterator end = endIndex();

  for (; it != end; ++it)
    {
      (*it)->setUserInterfaceFlag(mUserInterfaceFlag);
    }
}

CCopasiParameterGroup::index_iterator CCopasiParameterGroup::beginIndex() const
{return static_cast< elements * >(mpValue)->begin();}

CCopasiParameterGroup::index_iterator CCopasiParameterGroup::endIndex() const
{return static_cast< elements * >(mpValue)->end();}

bool CCopasiParameterGroup::addParameter(const std::string & name,
    const CCopasiParameter::Type type)
{
  CCopasiParameter * pParameter;

  if (type == GROUP)
    pParameter = new CCopasiParameterGroup(name);
  else
    pParameter = new CCopasiParameter(name, type);

  addParameter(pParameter);

  return true;
}

bool CCopasiParameterGroup::addGroup(const std::string & name)
{
  addParameter(new CCopasiParameterGroup(name));
  return true;
}

CCopasiParameterGroup * CCopasiParameterGroup::assertGroup(const std::string & name)
{
  CCopasiParameterGroup * pGrp = getGroup(name);

  if (pGrp) return pGrp;

  removeParameter(name);

  addGroup(name);
  return getGroup(name);
}

bool CCopasiParameterGroup::removeParameter(const std::string & name)
{
  return removeParameter(getParameter(name));
}

bool CCopasiParameterGroup::removeParameter(const size_t & index)
{
  if (index < size())
    {
      return removeParameter(static_cast< elements * >(mpValue)->at(index));
    }

  return false;
}

bool CCopasiParameterGroup::removeParameter(CCopasiParameter * pParameter)
{
  if (pParameter != NULL &&
      pParameter->getObjectParent() == this)
    {
      delete pParameter;
      return true;
    }

  return false;
}

// virtual
bool CCopasiParameterGroup::remove(CDataObject * pObject)
{
  bool success = CCopasiParameter::remove(pObject);

  if (success)
    {
      CCopasiParameter * pParameter = static_cast< CCopasiParameter * >(pObject);

      index_iterator it = static_cast< elements * >(mpValue)->begin();
      index_iterator end = static_cast< elements * >(mpValue)->end();

      for (; it != end; ++it)
        if (*it == pParameter)
          {
            static_cast< elements * >(mpValue)->erase(it, it + 1);
            break;
          }
    }

  return success;
}

CCopasiParameter * CCopasiParameterGroup::getParameter(std::string name)
{
  sanitizeObjectName(name);
  objectMap::range range = getObjects().equal_range(name);

  if (range.first == range.second) return NULL;

  return dynamic_cast<CCopasiParameter *>(const_cast< CDataObject * >(*range.first));
}

const CCopasiParameter * CCopasiParameterGroup::getParameter(std::string name) const
{
  sanitizeObjectName(name);
  objectMap::range range = getObjects().equal_range(name);

  if (range.first == range.second) return NULL;

  return dynamic_cast<CCopasiParameter *>(*range.first);
}

CCopasiParameter * CCopasiParameterGroup::getParameter(const size_t & index)
{
  if (index < size())
    return *(static_cast< elements * >(mpValue)->begin() + index);

  return NULL;
}

const CCopasiParameter * CCopasiParameterGroup::getParameter(const size_t & index) const
{
  if (index < size())
    return *(static_cast< elements * >(mpValue)->begin() + index);

  return NULL;
}

CCopasiParameterGroup * CCopasiParameterGroup::getGroup(const std::string & name)
{return dynamic_cast<CCopasiParameterGroup *>(getParameter(name));}

const CCopasiParameterGroup * CCopasiParameterGroup::getGroup(const std::string & name) const
{return dynamic_cast<const CCopasiParameterGroup *>(getParameter(name));}

CCopasiParameterGroup * CCopasiParameterGroup::getGroup(const size_t & index)
{return dynamic_cast<CCopasiParameterGroup *>(getParameter(index));}

const CCopasiParameterGroup * CCopasiParameterGroup::getGroup(const size_t & index) const
{return dynamic_cast<const CCopasiParameterGroup *>(getParameter(index));}

CCopasiParameter::Type CCopasiParameterGroup::getType(const std::string & name) const
{
  CCopasiParameter * pParameter =
    const_cast< CCopasiParameterGroup * >(this)->getParameter(name);

  if (pParameter) return pParameter->getType();

  return CCopasiParameter::INVALID;
}

CCopasiParameter::Type CCopasiParameterGroup::getType(const size_t & index) const
{
  CCopasiParameter * pParameter =
    const_cast< CCopasiParameterGroup * >(this)->getParameter(index);

  if (pParameter) return pParameter->getType();

  return CCopasiParameter::INVALID;
}

std::string CCopasiParameterGroup::getKey(const std::string & name) const
{
  CCopasiParameter * pParameter =
    const_cast< CCopasiParameterGroup * >(this)->getParameter(name);

  if (pParameter) return pParameter->getKey();

  return "Not Found";
}

std::string CCopasiParameterGroup::getKey(const size_t & index) const
{
  CCopasiParameter * pParameter =
    const_cast< CCopasiParameterGroup * >(this)->getParameter(index);

  if (pParameter) return pParameter->getKey();

  return "Not Found";
}

const std::string & CCopasiParameterGroup::getName(const size_t & index) const
{
  static std::string Invalid("Invalid Index");

  CCopasiParameter * pParameter =
    const_cast< CCopasiParameterGroup * >(this)->getParameter(index);

  if (pParameter) return pParameter->getObjectName();

  return Invalid;
}

bool CCopasiParameterGroup::swap(const size_t & iFrom,
                                 const size_t & iTo)
{
  index_iterator from = beginIndex() + iFrom;
  index_iterator to = beginIndex() + iTo;

  return swap(from, to);
}

bool CCopasiParameterGroup::swap(index_iterator & from,
                                 index_iterator & to)
{
  if (from < beginIndex() || endIndex() <= from ||
      to < beginIndex() || endIndex() <= to)
    return false;

  CCopasiParameter *tmp = *from;
  *from = *to;
  *to = tmp;

  return true;
}

size_t CCopasiParameterGroup::size(const CCopasiParameter::UserInterfaceFlag & flag) const
{
  if (flag == CCopasiParameter::UserInterfaceFlag::All)
    {
      return static_cast< elements * >(mpValue)->size();
    }

  elements::const_iterator it = beginIndex();
  elements::const_iterator end = endIndex();

  size_t size = 0;

  for (; it != end; ++it)
    if (flag & (*it)->getUserInterfaceFlag())
      ++size;

  return size;
}

void CCopasiParameterGroup::clear()
{
  if (mpValue != NULL)
    {
      elements Elements = *static_cast< elements * >(mpValue);
      static_cast< elements * >(mpValue)->clear();

      index_iterator it = Elements.begin();
      index_iterator end = Elements.end();

      for (; it != end; ++it)
        {
          pdelete(*it);
        }
    }
}

size_t CCopasiParameterGroup::getIndex(const std::string & name) const
{
  index_iterator it = static_cast< elements * >(mpValue)->begin();
  index_iterator end = static_cast< elements * >(mpValue)->end();

  for (size_t i = 0; it != end; ++it, ++i)
    if (name == (*it)->getObjectName())
      return i;

  return C_INVALID_INDEX;
}

// virtual
size_t CCopasiParameterGroup::getIndex(const CDataObject * pObject) const
{
  if (dynamic_cast< const CCopasiParameter * >(pObject))
    {
      index_iterator it = static_cast< elements * >(mpValue)->begin();
      index_iterator end = static_cast< elements * >(mpValue)->end();
      size_t i = 0;

      for (; it != end; ++it, ++i)
        if (pObject == *it)
          return i;
    }

  return CCopasiParameter::getIndex(pObject);
}

std::string CCopasiParameterGroup::getUniqueParameterName(const CCopasiParameter * pParameter) const
{
  size_t counter = C_INVALID_INDEX;
  size_t Index = C_INVALID_INDEX;

  std::string Name = pParameter->getObjectName();

  index_iterator it = static_cast< elements * >(mpValue)->begin();
  index_iterator end = static_cast< elements * >(mpValue)->end();

  for (; it != end; ++it)
    {
      if ((*it)->getObjectName() == Name)
        {
          counter++;

          if (*it == pParameter)
            {
              Index = counter;
            }
        }
    }

  if (counter == 0 || Index == C_INVALID_INDEX)
    {
      return Name;
    }

  std::stringstream UniqueName;
  UniqueName << Name << "[" << Index << "]";

  return UniqueName.str();
}
