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
#include "utilities/CCopasiVector.h"

CCopasiContainer * CCopasiContainer::Root = NULL;

void CCopasiContainer::init() {CCopasiContainer::Root = new CCopasiContainer();}

CCopasiContainer::CCopasiContainer() :
    CCopasiObject("Root", NULL, "CN", CCopasiObject::Container),
    mObjects()
{}

CCopasiContainer::CCopasiContainer(const std::string & name,
                                   const CCopasiContainer * pParent,
                                   const std::string & type,
                                   const unsigned C_INT32 & flag):
    CCopasiObject(name, pParent, type, flag | CCopasiObject::Container),
    mObjects()
{}

CCopasiContainer::CCopasiContainer(const CCopasiContainer & src,
                                   const CCopasiContainer * pParent):
    CCopasiObject(src, pParent),
    mObjects()
{}

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
    if (cn == "") return this;

    std::string Name = cn.getObjectName();
    std::string Type = cn.getObjectType();

    if (getObjectName() == Name && getObjectType() == Type)
      return getObject(cn.getRemainder());

    std::pair< objectMap::const_iterator, objectMap::const_iterator > range =
      mObjects.equal_range(Name);

    if (range.first == range.second) return false;

    /* We just pick the first one since in real containers the name should be */
    /* unique. The exeption is CCopasiContainer but in those the name is not  */
    /* meaningful anyway. */
    objectMap::const_iterator it = range.first;

    if (it->second->getObjectType() != Type) return NULL;

    const CCopasiObject * pObject = NULL;

    if (it->second->isNameVector() || it->second->isVector())
      {
        pObject = it->second->getObject("[" + cn.getName() + "]");

        if (it->second->getObjectType() == "Reference" || !pObject)
          return pObject;
        else
          return pObject->getObject(cn.getRemainder());
      }

    if (it->second->isContainer()) return it->second->getObject(cn.getRemainder());

    if (it->second->isMatrix())
      {
        pObject = it->second->getObject("[" + cn.getName() + "]" +
                                        "[" + cn.getName(1) + "]");

        if (it->second->getObjectType() == "Reference" || !pObject)
          return pObject;
        else
          return pObject->getObject(cn.getRemainder());
      }

    if (it->second->isReference()) return it->second;

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

  if (it != range.second)
    {
      std::cout << "multiple add: " << pObject->getCN() << ", "
      << (void *) pObject << std::endl;
      return false;
    }

  /* This object is not contained, so we can add it. */
  mObjects.insert
  (std::pair<std::string, CCopasiObject * >(pObject->getObjectName(),
      pObject));

  if (adopt) pObject->setObjectParent(this);
  return true;
}

bool CCopasiContainer::remove(CCopasiObject * pObject)
{
  std::pair< objectMap::iterator, objectMap::iterator > range =
    mObjects.equal_range(pObject->getObjectName());
  objectMap::iterator it;

  for (it = range.first; it != range.second; ++it)
    if (it->second == pObject) break;

  if (it == range.second) return false;

  mObjects.erase(it);

  return true;
}
