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

CCopasiContainer::CCopasiContainer() {}

CCopasiContainer::CCopasiContainer(const std::string & name,
                                   const CCopasiContainer * pParent,
                                   const std::string & type,
                                   const unsigned C_INT32 & flag):
    CCopasiObject(name, pParent, type, flag)
{}

CCopasiContainer::CCopasiContainer(const CCopasiContainer & src,
                                   const CCopasiContainer * pParent):
    CCopasiObject(src, pParent)
{}

CCopasiContainer::~CCopasiContainer()
{
  std::vector< CCopasiObject * > Objects(mObjects);
  std::vector< CCopasiObject * >::iterator it = Objects.begin();
  std::vector< CCopasiObject * >::iterator end = Objects.end();

  for (; it < end; it++)
    if ((*it)->isReference()) pdelete(*it);
}

const CCopasiObject * CCopasiContainer::getObject(const CCopasiObjectName & cn) const
  {
    if (cn == "") return this;

    std::string Name = cn.getObjectName();
    std::string Type = cn.getObjectType();

    if (mObjectName == Name && mObjectType == Type)
      return getObject(cn.getRemainder());

    std::vector< CCopasiObject * >::const_iterator it = mObjects.begin();
    std::vector< CCopasiObject * >::const_iterator end = mObjects.end();

    while (it != end &&
           (*it)->getObjectName() != Name &&
           (*it)->getObjectType() != Type) it++;

    if (it == end) return NULL;

    if ((*it)->isContainer()) return (*it)->getObject(cn.getRemainder());

    const CCopasiObject * pObject = NULL;

    if ((*it)->isNameVector() || (*it)->isVector())
      {
        pObject = (*it)->getObject("[" + cn.getName() + "]");

        if ((*it)->getObjectType() == "Reference" || !pObject)
          return pObject;
        else
          return pObject->getObject(cn.getRemainder());
      }

    if ((*it)->isMatrix())
      {
        pObject = (*it)->getObject("[" + cn.getName() + "]" +
                                   "[" + cn.getName(1) + "]");

        if ((*it)->getObjectType() == "Reference" || !pObject)
          return pObject;
        else
          return pObject->getObject(cn.getRemainder());
      }

    if ((*it)->isReference()) return *it;

    return (*it)->getObject(cn.getRemainder());
  }

const std::vector< CCopasiObject * > & CCopasiContainer::getObjects() const
  {
    return mObjects;
  }

void CCopasiContainer::initObjects() {}

void CCopasiContainer::add(CCopasiObject * pObject)
{
  //   std::cout << getCN() << " adds " << pObject->getObjectType() << "="
  //             << pObject->getObjectName() << std::endl;
  mObjects.push_back(pObject);
}

void CCopasiContainer::remove(CCopasiObject * pObject)
{
  std::vector< CCopasiObject * >::iterator it = mObjects.begin();
  std::vector< CCopasiObject * >::iterator end = mObjects.end();

  while (it < end && *it != pObject) it++;

  if (it != end)
    {
      //       std::cout << getCN() << " removes " << pObject->getObjectType() << "="
      //             << pObject->getObjectName() << std::endl;
      mObjects.erase(it, it + 1);
    }
}

CCopasiContainer CRootContainer::mRoot("Root");

CRootContainer::CRootContainer() {}

CRootContainer::~CRootContainer() {}

CCopasiContainer & CRootContainer::ref() {return mRoot;}
