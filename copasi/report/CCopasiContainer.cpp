/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiContainer.cpp,v $
   $Revision: 1.24 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/01/09 16:02:39 $
   End CVS Header */

/**
 * Class CCopasiContainer
 *
 * This class is the is used to group CCopasiObjects logically. It inself is 
 * an object. Contained objects are still globally accessible.
 *
 * Copyright Stefan Hoops 2002
 */

#include "copasi.h"
#include "CCopasiObjectName.h"
#include "CCopasiContainer.h"
#include "CCopasiObjectReference.h"
#include "CCopasiStaticString.h"
#include "utilities/CCopasiVector.h"

CCopasiContainer * CCopasiContainer::Root = NULL;

void CCopasiContainer::init() {CCopasiContainer::Root = new CCopasiContainer();}

CCopasiObject * CCopasiContainer::ObjectFromName(const std::vector< CCopasiContainer * > & listOfContainer,
    const CCopasiObjectName & objName)
{
  const CCopasiObject * pObject = NULL;
  CCopasiContainer* pContainer;
  CCopasiObjectName Name;
  unsigned C_INT32 containerIndex;

  //favor to search the list of container first
  for (containerIndex = 0;
       containerIndex < listOfContainer.size() && !pObject;
       containerIndex++)
    {
      pContainer = listOfContainer[containerIndex];

      for (Name = objName, pObject = NULL;
           (Name.getRemainder() != ""
            || Name.getObjectType() == "String") &&
           !pObject;
           Name = Name.getRemainder())
        pObject = pContainer->getObject(Name);
    }

  // if not found search the root
  if (!pObject)
    pObject = CCopasiContainer::Root->getObject(objName);

  return const_cast<CCopasiObject *>(pObject);
}

CCopasiContainer::CCopasiContainer() :
    CCopasiObject("Root", NULL, "CN", CCopasiObject::Container),
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
    if (it->second->getObjectParent() == this)
      {
        it->second->setObjectParent(NULL);
        pdelete(it->second);
      }
}

const std::string CCopasiContainer::getObjectUniqueName() const
  {
    // return getObjectName();
    return CCopasiObject::getObjectUniqueName();
  }

const CCopasiObject * CCopasiContainer::getObject(const CCopasiObjectName & cn) const
  {
    if (cn == "")
      return this;

    std::string Name = cn.getObjectName();
    std::string Type = cn.getObjectType();

    if (getObjectName() == Name && getObjectType() == Type)
      return getObject(cn.getRemainder());

    std::pair< objectMap::const_iterator, objectMap::const_iterator > range =
      mObjects.equal_range(Name);

    objectMap::const_iterator it = range.first;

    while (it != range.second && it->second->getObjectType() != Type) ++it;

    if (it == range.second)
      {
        if (Type == "String")
          return new CCopasiStaticString(Name, this);
        else
          return NULL;
      }

    const CCopasiObject * pObject = NULL;

    if (it->second->isNameVector() || it->second->isVector())
      {
        pObject = it->second->getObject("[" + cn.getName() + "]");

        if (it->second->getObjectType() == "Reference" || !pObject)
          return pObject;
        else
          return pObject->getObject(cn.getRemainder());
      }

    if (it->second->isContainer())
      return it->second->getObject(cn.getRemainder());

    if (it->second->isMatrix())
      {
        pObject = it->second->getObject("[" + cn.getName() + "]" +
                                        "[" + cn.getName(1) + "]");

        if (it->second->getObjectType() == "Reference" || !pObject)
          return pObject;
        else
          return pObject->getObject(cn.getRemainder());
      }

    if (it->second->isReference() || it->second->isStaticString())
      return it->second;

    return it->second->getObject(cn.getRemainder());
  }

const CCopasiContainer::objectMap & CCopasiContainer::getObjects() const
{return mObjects;}

void CCopasiContainer::initObjects() {}

bool CCopasiContainer::add(CCopasiObject * pObject,
                           const bool & adopt)
{
  /* We check wheter we are already containing that object. */
  std::pair< objectMap::iterator, objectMap::iterator > range =
    mObjects.equal_range(pObject->getObjectName());
  objectMap::iterator it;

  for (it = range.first; it != range.second; ++it)
    if (it->second == pObject) break;

  if (it != range.second) return false;

  /* This object is not contained, so we can add it. */
  mObjects.insert
  (std::pair<std::string, CCopasiObject * >(pObject->getObjectName(),
      pObject));

  if (adopt) pObject->setObjectParent(this);
  return true;
}

bool CCopasiContainer::remove(CCopasiObject * pObject)
{
  objectMap::iterator it = mObjects.begin();
  objectMap::iterator end = mObjects.end();
  /*
    std::pair< objectMap::iterator, objectMap::iterator > range =
      mObjects.equal_range(pObject->getObjectName());
    objectMap::iterator it;
  */
  for (; it != end; ++it)
    if (it->second == pObject) break;

  if (it == end) return false;

  mObjects.erase(it);

  return true;
}
