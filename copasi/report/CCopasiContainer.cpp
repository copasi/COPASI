// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*!
    \file CCopasiContainer.cpp
    \brief Implementation file of class CCopasiContainer
 */

/**
 * Class CCopasiContainer
 *
 * This class is the is used to group CCopasiObjects logically. It inself is
 * an object. Contained objects are still globally accessible.
 *
 * Copyright Stefan Hoops 2002
 */

#include "copasi/copasi.h"
#include "copasi/report/CCopasiObjectName.h"
#include "copasi/report/CCopasiContainer.h"
#include "copasi/report/CCopasiObjectReference.h"
#include "copasi/report/CCopasiStaticString.h"
#include "copasi/report/CCopasiTimer.h"

#include "copasi/utilities/CCopasiVector.h"
#include "copasi/utilities/CUnit.h"
#include "copasi/report/CCopasiRootContainer.h"

#define  END_NAME (std::map< std::string, std::set< CCopasiObject * > >::iterator(NULL))
#define  END_OBJECT (std::set< CCopasiObject * >::iterator(NULL))

CCopasiContainer::CObjectMap::iterator::iterator():
  mpMap(NULL),
  mName(END_NAME),
  mObject(END_OBJECT)
{}

CCopasiContainer::CObjectMap::iterator::iterator(const CObjectMap & map,
    const bool & begin):
  mpMap(&map),
  mName(END_NAME),
  mObject(END_OBJECT)
{
  if (mpMap != NULL &&
      mpMap->begin() != mpMap->end())
    {
      if (begin)
        {
          mName = const_cast< std::map< std::string, std::set< CCopasiObject * > > * >(mpMap)->begin();

          if (!mName->second.empty())
            {
              mObject = mName->second.begin();
            }
        }
    }
}

CCopasiContainer::CObjectMap::iterator::iterator(const CCopasiContainer::CObjectMap::iterator & src):
  mpMap(src.mpMap),
  mName(src.mName),
  mObject(src.mObject)
{}

CCopasiContainer::CObjectMap::iterator::~iterator()
{}

CCopasiObject * CCopasiContainer::CObjectMap::iterator::operator*() const
{
  return *mObject;
}

CCopasiObject * CCopasiContainer::CObjectMap::iterator::operator->() const
{
  return *mObject;
}

CCopasiContainer::CObjectMap::iterator & CCopasiContainer::CObjectMap::iterator::operator++()
{
  mObject++;

  if (mObject == mName->second.end() || mObject == END_OBJECT)
    {
      if (mName != mpMap->end() && mName != END_NAME)
        {
          mName++;
        }

      if (mName != mpMap->end() && mName != END_NAME)
        {
          mObject = mName->second.begin();
        }
      else
        {
          mName = END_NAME;
          mObject = END_OBJECT;
        }
    }

  return *this;
}

CCopasiContainer::CObjectMap::iterator CCopasiContainer::CObjectMap::iterator::operator++(int)
{
  iterator Current(*this);
  operator++();

  return Current;
}

bool CCopasiContainer::CObjectMap::iterator::operator != (const iterator & rhs) const
{
  return (mpMap != rhs.mpMap ||
          mName != rhs.mName ||
          mObject != rhs.mObject);
}

CCopasiContainer::CObjectMap::const_iterator::const_iterator():
  mpMap(NULL),
  mName(END_NAME),
  mObject(END_OBJECT)
{}

CCopasiContainer::CObjectMap::const_iterator::const_iterator(const CObjectMap & map,
    const bool & begin):
  mpMap(&map),
  mName(END_NAME),
  mObject(END_OBJECT)
{
  if (mpMap != NULL &&
      mpMap->begin() != mpMap->end())
    {
      if (begin)
        {
          mName = const_cast< std::map< std::string, std::set< CCopasiObject * > > * >(mpMap)->begin();

          if (!mName->second.empty())
            {
              mObject = mName->second.begin();
            }
        }
    }
}

CCopasiContainer::CObjectMap::const_iterator::const_iterator(const CCopasiContainer::CObjectMap::const_iterator & src):
  mpMap(src.mpMap),
  mName(src.mName),
  mObject(src.mObject)
{}

CCopasiContainer::CObjectMap::const_iterator::~const_iterator()
{}

CCopasiObject * CCopasiContainer::CObjectMap::const_iterator::operator*() const
{
  return *mObject;
}

CCopasiObject * CCopasiContainer::CObjectMap::const_iterator::operator->() const
{
  return *mObject;
}

CCopasiContainer::CObjectMap::const_iterator & CCopasiContainer::CObjectMap::const_iterator::operator++()
{
  mObject++;

  if (mObject == mName->second.end() || mObject == END_OBJECT)
    {
      if (mName != mpMap->end() && mName != END_NAME)
        {
          mName++;
        }

      if (mName != mpMap->end() && mName != END_NAME)
        {
          mObject = mName->second.begin();
        }
      else
        {
          mName = END_NAME;
          mObject = END_OBJECT;
        }
    }

  return *this;
}

CCopasiContainer::CObjectMap::const_iterator CCopasiContainer::CObjectMap::const_iterator::operator++(int)
{
  const_iterator Current(*this);
  operator++();

  return Current;
}

bool CCopasiContainer::CObjectMap::const_iterator::operator != (const const_iterator & rhs) const
{
  return (mpMap != rhs.mpMap ||
          mName != rhs.mName ||
          mObject != rhs.mObject);
}

CCopasiContainer::CObjectMap::CObjectMap():
  CCopasiContainer::CObjectMap::data()
{}

CCopasiContainer::CObjectMap::CObjectMap(const CCopasiContainer::CObjectMap & src):
  CCopasiContainer::CObjectMap::data(src)
{}

CCopasiContainer::CObjectMap::~CObjectMap()
{}

std::pair< std::set< CCopasiObject * >::iterator, bool > CCopasiContainer::CObjectMap::insert(CCopasiObject * pObject)
{
  if (pObject == NULL)
    {
      return std::make_pair(END_OBJECT, false);
    }

  std::map< std::string, std::set< CCopasiObject * > >::iterator itMap = data::find(pObject->getObjectName());

  if (itMap == data::end())
    {
      itMap = data::insert(std::make_pair(pObject->getObjectName(), std::set< CCopasiObject * >())).first;
    }

  return itMap->second.insert(pObject);
}

bool CCopasiContainer::CObjectMap::erase(CCopasiObject * pObject)
{
  if (pObject == NULL) return false;

  std::map< std::string, std::set< CCopasiObject * > >::iterator itMap = data::find(pObject->getObjectName());

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

void CCopasiContainer::CObjectMap::clear()
{
  data::clear();
}

bool CCopasiContainer::CObjectMap::contains(CCopasiObject * pObject) const
{
  if (pObject == NULL) return false;

  std::map< std::string, std::set< CCopasiObject * > >::const_iterator itMap = data::find(pObject->getObjectName());

  if (itMap != data::end())
    {
      return (itMap->second.find(pObject) != itMap->second.end());
    }

  return false;
}

std::pair< std::set< CCopasiObject * >::const_iterator, std::set< CCopasiObject * >::const_iterator > CCopasiContainer::CObjectMap::equal_range(const std::string & name) const
{
  std::map< std::string, std::set< CCopasiObject * > >::const_iterator itMap = data::find(name);

  if (itMap != data::end())
    {
      return std::make_pair(itMap->second.begin(), itMap->second.end());
    }

  return std::make_pair(END_OBJECT, END_OBJECT);
}

CCopasiContainer::CObjectMap::iterator CCopasiContainer::CObjectMap::begin()
{
  return iterator(*this, true);
}

CCopasiContainer::CObjectMap::iterator CCopasiContainer::CObjectMap::end()
{
  return iterator(*this, false);
}

CCopasiContainer::CObjectMap::const_iterator CCopasiContainer::CObjectMap::begin() const
{
  return const_iterator(*this, true);
}

CCopasiContainer::CObjectMap::const_iterator CCopasiContainer::CObjectMap::end() const
{
  return const_iterator(*this, false);
}

const CObjectInterface::ContainerList CCopasiContainer::EmptyList;

CCopasiContainer::CCopasiContainer() :
  CCopasiObject(),
  mObjects()
{addObjectReference("Name", *const_cast<std::string *>(&getObjectName()));}

CCopasiContainer::CCopasiContainer(const std::string & name,
                                   const CCopasiContainer * pParent,
                                   const std::string & type,
                                   const unsigned C_INT32 & flag):
  CCopasiObject(name, pParent, type, flag | CCopasiObject::Container),
  mObjects()
{addObjectReference("Name", *const_cast<std::string *>(&getObjectName()));}

CCopasiContainer::CCopasiContainer(const CCopasiContainer & src,
                                   const CCopasiContainer * pParent):
  CCopasiObject(src, pParent),
  mObjects()
{addObjectReference("Name", *const_cast<std::string *>(&getObjectName()));}

CCopasiContainer::~CCopasiContainer()
{
  objectMap::iterator it = mObjects.begin();
  objectMap::iterator end = mObjects.end();

  for (; it != end; it++)
    if (*it != NULL &&
        (*it)->getObjectParent() == this)
      {
        (*it)->setObjectParent(NULL);

        if (*it != NULL) delete(*it);
      }
}

const CObjectInterface * CCopasiContainer::getObject(const CCopasiObjectName & cn) const
{
  if (cn == "")
    {
      if (isRoot())
        return NULL;
      else
        return this;
    }

  if (cn == "Property=DisplayName")
    {
      return CCopasiObject::getObject(cn);
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
        return new CCopasiStaticString(Name, this);
      else if (Type == "Separator")
        return new CCopasiReportSeparator(Name, this);
      else
        return NULL;
    }

  const CObjectInterface * pObject = NULL;

  if ((*range.first)->isNameVector() || (*range.first)->isVector())
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
  if ((*range.first)->isArray())
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
  if ((*range.first)->isContainer())
    return (*range.first)->getObject(cn.getRemainder());

  if ((*range.first)->isMatrix())
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

const CCopasiContainer::objectMap & CCopasiContainer::getObjects() const
{return mObjects;}

const CCopasiObject * CCopasiContainer::getValueObject() const
{
  void * ptr = getValuePointer();

  if (ptr == NULL) return NULL;

  objectMap::const_iterator it = mObjects.begin();
  objectMap::const_iterator end = mObjects.end();

  for (; it != end; ++it)
    if (ptr == (*it)->getValuePointer()) return *it;

  return NULL;
}

void CCopasiContainer::initObjects() {}

bool CCopasiContainer::add(CCopasiObject * pObject,
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

  if (adopt) pObject->setObjectParent(this);

  return true;
}

bool CCopasiContainer::remove(CCopasiObject * pObject)
{
  return mObjects.erase(pObject);
}

// virtual
const std::string CCopasiContainer::getUnits() const
{return "";}

// virtual
std::string CCopasiContainer::getChildObjectUnits(const CCopasiObject * /* pObject */) const
{return "";}
