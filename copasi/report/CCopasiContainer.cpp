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
  std::vector< CCopasiObject * >::iterator it = mObjects.begin();
  std::vector< CCopasiObject * >::iterator end = mObjects.end();

  for (; it < end; it++)
    if ((*it)->isReference()) pdelete(*it);
}

CCopasiObject * CCopasiContainer::getObject(const CCopasiObjectName & cn)
{
  if (cn == "") return this;

  std::vector< CCopasiObject * >::iterator it = mObjects.begin();
  std::vector< CCopasiObject * >::iterator end = mObjects.end();

  std::string Name = cn.getObjectName();
  std::string Type = cn.getObjectType();

  for (; it < end; it++)
    if ((*it)->getObjectName() == Name && (*it)->getObjectType() == Type) break;

  if (it == end) return NULL;

  if ((*it)->isContainer()) return (*it)->getObject(cn.getRemainder());

  CCopasiObject * pObject = NULL;

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

void CCopasiContainer::initObjects() {}

void CCopasiContainer::add(CCopasiObject * object)
{mObjects.push_back(object);}

CCopasiContainer CRootContainer::mRoot("Root");

CRootContainer::CRootContainer() {}

CRootContainer::~CRootContainer() {}

CCopasiContainer & CRootContainer::ref() {return mRoot;}
