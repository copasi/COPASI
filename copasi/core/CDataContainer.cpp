// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/*!
    \file CDataContainer.cpp
    \brief Implementation file of class CDataContainer
 */

/**
 * Class CDataContainer
 *
 * This class is the is used to group CDataObjects logically. It inself is
 * an object. Contained objects are still globally accessible.
 *
 * Copyright Stefan Hoops 2002
 */

#include "copasi/copasi.h"

#include "CDataContainer.h"
#include "CDataVector.h"
#include "CRootContainer.h"

#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/core/CDataTimer.h"
#include "copasi/core/CDataString.h"

#include "copasi/utilities/CUnit.h"

CDataContainer::CObjectMap::iterator::iterator():
  mpMap(NULL),
  mNameEnd(true),
  mName(),
  mObjectEnd(true),
  mObject()
{}

CDataContainer::CObjectMap::iterator::iterator(const CObjectMap & map,
    const bool & begin):
  mpMap(&map),
  mNameEnd(true),
  mName(),
  mObjectEnd(true),
  mObject()
{
  if (mpMap != NULL &&
      mpMap->begin() != mpMap->end())
    {
      if (begin)
        {
          mNameEnd = false;
          mName = const_cast< std::map< std::string, std::set< CDataObject * > > * >(mpMap)->begin();

          if (!mName->second.empty())
            {
              mObjectEnd = false;
              mObject = mName->second.begin();
            }
        }
    }
}

CDataContainer::CObjectMap::iterator::iterator(const CDataContainer::CObjectMap::iterator & src):
  mpMap(src.mpMap),
  mNameEnd(src.mNameEnd),
  mName(src.mName),
  mObjectEnd(src.mObjectEnd),
  mObject(src.mObject)
{}

CDataContainer::CObjectMap::iterator::~iterator()
{}

CDataObject * CDataContainer::CObjectMap::iterator::operator*() const
{
  if (!mObjectEnd)
    return *mObject;

  return NULL;
}

CDataObject * CDataContainer::CObjectMap::iterator::operator->() const
{
  if (!mObjectEnd)
    return *mObject;

  return NULL;
}

CDataContainer::CObjectMap::iterator & CDataContainer::CObjectMap::iterator::operator++()
{
  mObject++;

  if (mObject == mName->second.end() || mObjectEnd)
    {
      if (mName != mpMap->end() && !mNameEnd)
        {
          mName++;
        }

      if (mName != mpMap->end() && !mNameEnd)
        {
          mObjectEnd = false;
          mObject = mName->second.begin();
        }
      else
        {
          mNameEnd = true;
          mObjectEnd = true;
        }
    }

  return *this;
}

CDataContainer::CObjectMap::iterator CDataContainer::CObjectMap::iterator::operator++(int)
{
  iterator Current(*this);
  operator++();

  return Current;
}

bool CDataContainer::CObjectMap::iterator::operator != (const iterator & rhs) const
{
  return (mpMap != rhs.mpMap ||
          mNameEnd != rhs.mNameEnd ||
          mObjectEnd != rhs.mObjectEnd ||
          (!mNameEnd && mName != rhs.mName) ||
          (!mObjectEnd && mObject != rhs.mObject));
}

CDataContainer::CObjectMap::const_iterator::const_iterator():
  mpMap(NULL),
  mNameEnd(true),
  mName(),
  mObjectEnd(true),
  mObject()
{}

CDataContainer::CObjectMap::const_iterator::const_iterator(const CObjectMap & map,
    const bool & begin):
  mpMap(&map),
  mNameEnd(true),
  mName(),
  mObjectEnd(true),
  mObject()
{
  if (mpMap != NULL &&
      mpMap->begin() != mpMap->end())
    {
      if (begin)
        {
          mNameEnd = false;
          mName = const_cast< std::map< std::string, std::set< CDataObject * > > * >(mpMap)->begin();

          if (!mName->second.empty())
            {
              mObjectEnd = false;
              mObject = mName->second.begin();
            }
        }
    }
}

CDataContainer::CObjectMap::const_iterator::const_iterator(const CDataContainer::CObjectMap::const_iterator & src):
  mpMap(src.mpMap),
  mNameEnd(src.mNameEnd),
  mName(src.mName),
  mObjectEnd(src.mObjectEnd),
  mObject(src.mObject)
{}

CDataContainer::CObjectMap::const_iterator::~const_iterator()
{}

CDataObject * CDataContainer::CObjectMap::const_iterator::operator*() const
{
  return *mObject;
}

CDataObject * CDataContainer::CObjectMap::const_iterator::operator->() const
{
  return *mObject;
}

CDataContainer::CObjectMap::const_iterator & CDataContainer::CObjectMap::const_iterator::operator++()
{
  mObject++;

  if (mObject == mName->second.end() || mObjectEnd)
    {
      if (mName != mpMap->end() && !mNameEnd)
        {
          mName++;
        }

      if (mName != mpMap->end() && !mNameEnd)
        {
          mObjectEnd = false;
          mObject = mName->second.begin();
        }
      else
        {
          mNameEnd = true;
          mObjectEnd = true;
        }
    }

  return *this;
}

CDataContainer::CObjectMap::const_iterator CDataContainer::CObjectMap::const_iterator::operator++(int)
{
  const_iterator Current(*this);
  operator++();

  return Current;
}

bool CDataContainer::CObjectMap::const_iterator::operator != (const const_iterator & rhs) const
{
  return (mpMap != rhs.mpMap ||
          mNameEnd != rhs.mNameEnd ||
          mObjectEnd != rhs.mObjectEnd ||
          (!mNameEnd && mName != rhs.mName) ||
          (!mObjectEnd && mObject != rhs.mObject));
}

CDataContainer::CObjectMap::CObjectMap():
  CDataContainer::CObjectMap::data()
{}

CDataContainer::CObjectMap::CObjectMap(const CDataContainer::CObjectMap & src):
  CDataContainer::CObjectMap::data(src)
{}

CDataContainer::CObjectMap::~CObjectMap()
{}

std::pair< std::set< CDataObject * >::iterator, bool > CDataContainer::CObjectMap::insert(CDataObject * pObject)
{
  if (pObject == NULL)
    {
      return std::make_pair(std::set< CDataObject * >::iterator(), false);
    }

  std::map< std::string, std::set< CDataObject * > >::iterator itMap = data::find(pObject->getObjectName());

  if (itMap == data::end())
    {
      itMap = data::insert(std::make_pair(pObject->getObjectName(), std::set< CDataObject * >())).first;
    }

  return itMap->second.insert(pObject);
}

bool CDataContainer::CObjectMap::erase(CDataObject * pObject)
{
  if (pObject == NULL) return false;

  std::map< std::string, std::set< CDataObject * > >::iterator itMap = data::find(pObject->getObjectName());

  if (itMap != data::end())
    {
      bool success = (itMap->second.erase(pObject) > 0);

      if (itMap->second.empty())
        {
          data::erase(itMap);
        }

      return success;
    }

  return false;
}

void CDataContainer::CObjectMap::clear()
{
  data::clear();
}

bool CDataContainer::CObjectMap::contains(CDataObject * pObject) const
{
  if (pObject == NULL) return false;

  std::map< std::string, std::set< CDataObject * > >::const_iterator itMap = data::find(pObject->getObjectName());

  if (itMap != data::end())
    {
      return (itMap->second.find(pObject) != itMap->second.end());
    }

  return false;
}

void CDataContainer::CObjectMap::objectRenamed(CDataObject * pObject, const std::string & oldName)
{
  if (pObject != NULL)
    {
      // We cannot use erase since the object has already been renamed.
      std::map< std::string, std::set< CDataObject * > >::iterator itMap = data::find(oldName);

      if (itMap != data::end())
        {
          bool success = (itMap->second.erase(pObject) > 0);

          if (itMap->second.empty())
            {
              data::erase(itMap);
            }
        }

      insert(pObject);
    }
}

std::pair< std::set< CDataObject * >::const_iterator, std::set< CDataObject * >::const_iterator > CDataContainer::CObjectMap::equal_range(const std::string & name) const
{
  std::map< std::string, std::set< CDataObject * > >::const_iterator itMap = data::find(name);

  if (itMap != data::end())
    {
      return std::make_pair(itMap->second.begin(), itMap->second.end());
    }

  static std::set< CDataObject * > Set;
  return std::make_pair(Set.begin(), Set.end());
}

CDataContainer::CObjectMap::iterator CDataContainer::CObjectMap::begin()
{
  return iterator(*this, true);
}

CDataContainer::CObjectMap::iterator CDataContainer::CObjectMap::end()
{
  return iterator(*this, false);
}

CDataContainer::CObjectMap::const_iterator CDataContainer::CObjectMap::begin() const
{
  return const_iterator(*this, true);
}

CDataContainer::CObjectMap::const_iterator CDataContainer::CObjectMap::end() const
{
  return const_iterator(*this, false);
}

const CObjectInterface::ContainerList CDataContainer::EmptyList;

// static
CDataContainer * CDataContainer::fromData(const CData & data)
{
  return new CDataContainer(data.getProperty(CData::OBJECT_NAME).toString(),
                            NO_PARENT,
                            data.getProperty(CData::OBJECT_TYPE).toString(),
                            CFlags< Flag >(data.getProperty(CData::OBJECT_FLAG).toString()));
}

// virtual
CData CDataContainer::toData() const
{
  return CDataObject::toData();
}

// virtual
bool CDataContainer::applyData(const CData & data)
{
  return CDataObject::applyData(data);
}

CDataContainer::CDataContainer() :
  CDataObject(),
  mObjects()
{addObjectReference("Name", *const_cast<std::string *>(&getObjectName()));}

CDataContainer::CDataContainer(const std::string & name,
                               const CDataContainer * pParent,
                               const std::string & type,
                               const CFlags< Flag > & flag):
  CDataObject(name, pParent, type, flag | CDataObject::Container),
  mObjects()
{addObjectReference("Name", *const_cast<std::string *>(&getObjectName()));}

CDataContainer::CDataContainer(const CDataContainer & src,
                               const CDataContainer * pParent):
  CDataObject(src, pParent),
  mObjects()
{addObjectReference("Name", *const_cast<std::string *>(&getObjectName()));}

CDataContainer::~CDataContainer()
{
  objectMap::iterator it = mObjects.begin();
  objectMap::iterator end = mObjects.end();

  for (; it != end; ++it)
    if (*it != NULL &&
        (*it)->getObjectParent() == this)
      {
        (*it)->setObjectParent(NULL);

        if (*it != NULL) delete(*it);
      }
}

const CObjectInterface * CDataContainer::getObject(const CCommonName & cn) const
{
  if (cn == "")
    {
      if (hasFlag(Root))
        return NULL;
      else
        return this;
    }

  if (cn == "Property=DisplayName")
    {
      return CDataObject::getObject(cn);
    }

  std::string Name = cn.getObjectName();
  std::string Type = cn.getObjectType();

  if (getObjectName() == Name && getObjectType() == Type)
    return getObject(cn.getRemainder());

  //check if the first part of the cn matches one of the children (by name and type)
  objectMap::range range = mObjects.equal_range(Name);

  while (range.first != range.second && (*range.first)->getObjectType() != Type) ++range.first;

  if (range.first == range.second) //not found in the list of children
    {
      if (Type == "String")
        return new CDataString(Name, this);
      else if (Type == "Separator")
        return new CCopasiReportSeparator(Name, this);
      else
        return NULL;
    }

  const CObjectInterface * pObject = NULL;

  if ((*range.first)->hasFlag(NameVector) || (*range.first)->hasFlag(Vector))
    {
      if (cn.getElementName(0, false) == "")
        return *range.first;

      pObject = (*range.first)->getObject("[" + cn.getElementName(0, false) + "]");

      if ((*range.first)->getObjectType() == "Reference" ||
          !pObject ||
          cn.getRemainder() == "")
        return pObject;
      else
        return pObject->getObject(cn.getRemainder());
    }

  //handle objects where the array flag is set. Currently this applies to the
  //CArrayAnnotation object. Since this is also a container, we have to do this
  //before handling general containers.
  if ((*range.first)->hasFlag(Array))
    {
      //we need to call the getObject() method of the child array with the
      //remainder of the cn, with the indices in square brackets, or with an empty string

      //if there are no indices there could still be a remainder (since the array can also be
      //a container)
      if (cn.getElementName(0, false) == "") //no indices
        return (*range.first)->getObject(cn.getRemainder());

      return (*range.first)->getObject(cn);
    }

  //handle generic containers.
  if ((*range.first)->hasFlag(Container))
    return (*range.first)->getObject(cn.getRemainder());

  if ((*range.first)->hasFlag(Matrix))
    {
      if (cn.getElementName(0, false) == "")
        return *range.first;

      pObject = (*range.first)->getObject("[" + cn.getElementName(0, false) + "]" +                   //TODO really?
                                          "[" + cn.getElementName(1, false) + "]");

      if ((*range.first)->getObjectType() == "Reference" || !pObject)
        return pObject;
      else
        return pObject->getObject(cn.getRemainder());
    }

  return (*range.first)->getObject(cn.getRemainder());
}

const CDataContainer::objectMap & CDataContainer::getObjects() const
{return mObjects;}

const CDataObject * CDataContainer::getValueObject() const
{
  void * ptr = getValuePointer();

  if (ptr == NULL) return NULL;

  objectMap::const_iterator it = mObjects.begin();
  objectMap::const_iterator end = mObjects.end();

  for (; it != end; ++it)
    if (ptr == (*it)->getValuePointer()) return *it;

  return NULL;
}

void CDataContainer::initObjects() {}

// virtual
bool CDataContainer::add(CDataObject * pObject,
                         const bool & adopt)
{
  if (pObject == NULL)
    {
      return false;
    }

  /* We check whether we are already containing that object. */

  if (mObjects.contains(pObject)) return false;

  /* This object is not contained, so we can add it. */
  mObjects.insert(pObject);

  if (adopt)
    pObject->setObjectParent(this);
  else
    pObject->addReference(this);

  validityChanged(pObject->getValidity());

  return true;
}

// virtual
bool CDataContainer::remove(CDataObject * pObject)
{
  if (pObject != NULL)
    {
      validityRemoved(pObject->getValidity());
      pObject->removeReference(this);
    }

  return mObjects.erase(pObject);
}

// virtual
size_t CDataContainer::getIndex(const CDataObject * pObject) const
{
  return 0;
}

void CDataContainer::getDescendants(CDataObject::DataObjectSet & descendants, const bool & recursive) const
{
  const CDataContainer * pContainer;
  objectMap::const_iterator it = mObjects.begin();
  objectMap::const_iterator end = mObjects.end();

  for (; it != end; ++it)
    if ((*it)->getObjectParent() == this)
      {
        descendants.insert(*it);

        if (recursive &&
            (pContainer = dynamic_cast< const CDataContainer * >(*it)) != NULL)
          {
            pContainer->getDescendants(descendants, recursive);
          }
      }
}

void CDataContainer::objectRenamed(CDataObject * pObject, const std::string & oldName)
{
  mObjects.objectRenamed(pObject, oldName);
}

// virtual
const std::string CDataContainer::getUnits() const
{return "?";}

// virtual
std::string CDataContainer::getChildObjectUnits(const CDataObject * /* pObject */) const
{return "?";}

// virtual
CDataObject * CDataContainer::insert(const CData & data)
{
  return NULL;
}
