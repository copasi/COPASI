// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <assert.h>

#include <sbml/packages/render/sbml/LocalStyle.h>

#include "CLLocalStyle.h"
#include "CLGraphicalObject.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"

// static
CLLocalStyle * CLLocalStyle::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CLLocalStyle(NO_PARENT);
}

// virtual
CData CLLocalStyle::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CLLocalStyle::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

/**
 * Constructor.
 */
CLLocalStyle::CLLocalStyle(CDataContainer* pParent): CLStyle("LocalStyle", pParent)
{
  this->mKey = CRootContainer::getKeyFactory()->add("LocalStyle", this);
}

/**
 * Copy Constructor.
 */
CLLocalStyle::CLLocalStyle(const CLLocalStyle& source, CDataContainer* pParent):
  CLStyle(source, pParent),
  mKeyList(source.mKeyList)
{
  this->mKey = CRootContainer::getKeyFactory()->add("LocalStyle", this);
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLLocalStyle::CLLocalStyle(const LocalStyle& source, CDataContainer* pParent):
  CLStyle(source, "LocalStyle", pParent)
{
  this->mKey = CRootContainer::getKeyFactory()->add("LocalStyle", this);
  CLStyle::readIntoSet(CLStyle::createStringFromSet(source.getIdList()), this->mKeyList);
}

/**
 * Returns the number of keys in the key set.
 */
size_t CLLocalStyle::getNumKeys() const
{
  return this->mKeyList.size();
}

/**
 * Sets the key list.
 */
void CLLocalStyle::setKeyList(const std::set<std::string>& keyList)
{
  this->mKeyList = keyList;
}

/**
 * Returns the key list.
 */
const std::set<std::string>& CLLocalStyle::getKeyList() const
{
  return this->mKeyList;
}

/**
 * Checks if a certain key is in the set or not.
 */
bool CLLocalStyle::isKeyInSet(const std::string& key) const
{
  return (this->mKeyList.find(key) != this->mKeyList.end());
}

/**
 * Adds another key to the set.
 */
void CLLocalStyle::addKey(const std::string& key)
{
  this->mKeyList.insert(key);
}

bool CLLocalStyle::isInKeyList(const std::string & key) const
{
  return isKeyInSet(key);
}

/**
 * Removes an key from the set.
 */
void CLLocalStyle::removeKey(const std::string& key)
{
  this->mKeyList.erase(key);
}

int CLLocalStyle::appliesTo(const CLGraphicalObject * pObject) const
{
  if (!pObject)
    return 0;

  if (isKeyInSet(pObject->getKey()))
    return 3;

  return CLStyle::appliesTo(pObject);
}

/**
 * Converts this object to the corresponding SBML object.
 */
LocalStyle* CLLocalStyle::toSBML(unsigned int level, unsigned int version) const
{
  LocalStyle* pLS = new LocalStyle(level, version);
  this->addSBMLAttributes(pLS);
  std::set<std::string> s;
  CLStyle::readIntoSet(CLStyle::createStringFromSet(this->mKeyList), s);
  pLS->setIdList(s);
  return pLS;
}
