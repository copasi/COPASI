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
    CCopasiObject("Root", NULL, "CN", CCopasiObject::Container)
{}

CCopasiContainer::CCopasiContainer(const std::string & name,
                                   const CCopasiContainer * pParent,
                                   const std::string & type,
                                   const unsigned C_INT32 & flag):
    CCopasiObject(name, pParent, type, flag | CCopasiObject::Container)
{}

CCopasiContainer::CCopasiContainer(const CCopasiContainer & src,
                                   const CCopasiContainer * pParent):
    CCopasiObject(src, pParent),
    mObjects()
{}

CCopasiContainer::~CCopasiContainer()
{
  std::map< const std::string, CCopasiObject * >::iterator it = mObjects.begin();
  std::map< const std::string, CCopasiObject * >::iterator end = mObjects.end();

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

    std::map< const std::string, CCopasiObject * >::const_iterator it =
      mObjects.find(Name);

    if (it == mObjects.end()) return NULL;
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

const std::map< const std::string, CCopasiObject * > & CCopasiContainer::getObjects() const
  {
    return mObjects;
  }

void CCopasiContainer::initObjects() {}

bool CCopasiContainer::add(CCopasiObject * pObject)
{
  if (mObjects.find(pObject->getObjectName()) != mObjects.end()) return false;

  mObjects[pObject->getObjectName()] = pObject;
  return true;
}

bool CCopasiContainer::remove(CCopasiObject * pObject)
{
  std::map< const std::string, CCopasiObject * >::iterator it =
    mObjects.find(pObject->getObjectName());
  if (it == mObjects.end()) return false;

  mObjects.erase(it);
  return false;
}

#ifdef XXXX
CCopasiContainer CRootContainer::mRoot("Root");

CRootContainer::CRootContainer() {}

CRootContainer::~CRootContainer() {}

CCopasiContainer & CRootContainer::ref() {return mRoot;}
#endif // XXXX
