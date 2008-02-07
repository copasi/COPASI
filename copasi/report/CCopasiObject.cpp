// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiObject.cpp,v $
//   $Revision: 1.69.4.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/07 16:42:35 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * Class CCopasiObject
 *
 * This class is the base class for all global accessible objects in copasi.
 *
 * Copyright Stefan Hoops 2002
 */

#include <sstream>
#include <algorithm>

#include "copasi.h"
#include "CCopasiObjectName.h"
#include "CCopasiObject.h"
#include "CCopasiContainer.h"
#include "CRenameHandler.h"
#include "utilities/CCopasiVector.h"
#include "model/CModelValue.h"
#include "model/CModel.h"

//static
const C_FLOAT64 CCopasiObject::DummyValue = 0.0;

//static
const CRenameHandler * CCopasiObject::smpRenameHandler = NULL;

//static
UpdateMethod CCopasiObject::mDefaultUpdateMethod;

CCopasiObject::CCopasiObject():
    mObjectName("No Name"),
    mObjectType("Unknown Type"),
    mpObjectParent(NULL),
    mObjectFlag(0),
    mpUpdateMethod(&this->mDefaultUpdateMethod),
    mpRefresh(NULL)
{}

CCopasiObject::CCopasiObject(const std::string & name,
                             const CCopasiContainer * pParent,
                             const std::string & type,
                             const unsigned C_INT32 & flag):
    mObjectName((name == "") ? "No Name" : name),
    mObjectType(type),
    mpObjectParent(const_cast<CCopasiContainer *>(pParent)),
    mObjectFlag(flag),
    mpUpdateMethod(&this->mDefaultUpdateMethod),
    mpRefresh(NULL)
{
  if (mpObjectParent != NULL)
    if (mpObjectParent->isContainer()) mpObjectParent->add(this);
}

CCopasiObject::CCopasiObject(const CCopasiObject & src,
                             const CCopasiContainer * pParent):
mObjectName(src.mObjectName),
mObjectType(src.mObjectType),
mpObjectParent(const_cast<CCopasiContainer *>(pParent)),
mObjectFlag(src.mObjectFlag),
mpUpdateMethod(&this->mDefaultUpdateMethod),
mpRefresh(NULL)
{if (mpObjectParent != NULL) mpObjectParent->add(this);}

CCopasiObject::~CCopasiObject()
{
  if (mpObjectParent)
    mpObjectParent->remove(this);

  if (mpUpdateMethod != &mDefaultUpdateMethod)
    pdelete(mpUpdateMethod);

  pdelete(mpRefresh);
}

void CCopasiObject::print(std::ostream * ostream) const {(*ostream) << (*this);}

CCopasiObjectName CCopasiObject::getCN() const
  {
    CCopasiObjectName CN;

    if (mpObjectParent)
      {
        std::stringstream tmp;
        tmp << mpObjectParent->getCN();

        if (mpObjectParent->isNameVector())
          tmp << "[" << CCopasiObjectName::escape(mObjectName) << "]";
        else if (mpObjectParent->isVector())
          tmp << "[" << static_cast<const CCopasiVector< CCopasiObject > *>(mpObjectParent)->getIndex(this) << "]";
        else
          tmp << "," << CCopasiObjectName::escape(mObjectType)
          << "=" << CCopasiObjectName::escape(mObjectName);

        CN = tmp.str();
      }
    else
      {
        CN = CCopasiObjectName::escape(mObjectType)
             + "=" + CCopasiObjectName::escape(mObjectName);
      }

    return CN;
  }

const CCopasiObject *
CCopasiObject::getObject(const CCopasiObjectName & C_UNUSED(cn)) const
  {return NULL;}

bool CCopasiObject::setObjectName(const std::string & name)
{
  if (name == mObjectName) return true;

  std::string Name = (name == "") ? "No Name" : name;

  if (mpObjectParent &&
      mpObjectParent->isNameVector() &&
      mpObjectParent->getObject("[" + CCopasiObjectName::escape(Name) + "]"))
    return false;

  if (smpRenameHandler && mpObjectParent)
    {
      std::string oldCN = this->getCN();
      mObjectName = Name;
      std::string newCN = this->getCN();
      smpRenameHandler->handle(oldCN, newCN);

      //TODO performance considerations.
      //Right now after every rename the CNs are checked. In some cases
      //we may know that this is not necessary
    }
  else
  {mObjectName = Name;}

  if (mpObjectParent)
    {
      mpObjectParent->CCopasiContainer::remove(this);
      mpObjectParent->CCopasiContainer::add(this, false);
    }

  return true;
}

/*virtual*/
std::string CCopasiObject::getObjectDisplayName(bool regular /*=true*/, bool richtext /*=false*/) const
  {
    std::string ret = "";

    if (mpObjectParent)
      {
        ret = mpObjectParent->getObjectDisplayName(regular, richtext);
        if (ret == "(CN)Root") ret = "";
        if (ret.substr(0, 7) == "(Model)") ret = "";
      }

    if (ret.length() >= 2)
      if ((ret.substr(ret.length() - 2) == "[]") && (!isReference()))
        {
          ret.insert(ret.length() - 1, getObjectName());
          if (isNameVector() || isVector() || getObjectType() == "ParameterGroup")
            ret += "[]";
          return ret;
        }

    if ((ret.length() != 0) && (ret[ret.length() - 1] != '.'))
      ret += ".";

    if (isNameVector() || isVector() || getObjectType() == "ParameterGroup")
      ret += getObjectName() + "[]";
    else if (isReference()
             || getObjectType() == "Parameter"
             || getObjectType() == getObjectName())
      ret += getObjectName();
    else
      ret += "(" + getObjectType() + ")" + getObjectName();

    return ret;
  }

const std::string & CCopasiObject::getObjectName() const {return mObjectName;}

const std::string & CCopasiObject::getObjectType() const {return mObjectType;}

bool CCopasiObject::setObjectParent(const CCopasiContainer * pParent)
{
  mpObjectParent = const_cast<CCopasiContainer *>(pParent);

  return true;
}

CCopasiContainer * CCopasiObject::getObjectParent() const {return mpObjectParent;}

CCopasiContainer *
CCopasiObject::getObjectAncestor(const std::string & type) const
  {
    CCopasiContainer * p = getObjectParent();

    while (p)
      {
        if (p->getObjectType() == type) return p;
        p = p->getObjectParent();
      }

    return NULL;
  }

void CCopasiObject::setDirectDependencies(const std::set< const CCopasiObject * > & directDependencies)
{mDependencies = directDependencies;}

const std::set< const CCopasiObject * > & CCopasiObject::getDirectDependencies() const
  {return mDependencies;}

void CCopasiObject::addDirectDependency(const CCopasiObject * pObject)
{
  mDependencies.insert(pObject);
  return;
}

void CCopasiObject::getAllDependencies(std::set< const CCopasiObject * > & dependencies) const
  {
    std::set< const CCopasiObject * >::const_iterator it = mDependencies.begin();
    std::set< const CCopasiObject * >::const_iterator end = mDependencies.end();

    std::pair<std::set< const CCopasiObject * >::iterator, bool> Inserted;

    for (; it != end; ++it)
      {
        // Dual purpose insert
        Inserted = dependencies.insert(*it);

        // The direct dependency *it was among the dependencies
        // we assume also its dependencies have been added already.
        if (!Inserted.second) continue;

        // Add all the dependencies of the direct dependency *it.
        (*it)->getAllDependencies(dependencies);
      }
  }

bool CCopasiObject::dependsOn(std::set< const CCopasiObject * > & candidates) const
  {
    std::set< const CCopasiObject * > verified;
    return hasCircularDependencies(candidates, verified);
  }

bool CCopasiObject::hasCircularDependencies(std::set< const CCopasiObject * > & candidates,
    std::set< const CCopasiObject * > & verified) const
  {
    std::set< const CCopasiObject * >::const_iterator it = mDependencies.begin();
    std::set< const CCopasiObject * >::const_iterator end = mDependencies.end();

    std::pair<std::set< const CCopasiObject * >::iterator, bool> Inserted;

    // The element has been checked and does not need to be checked again.
    verified.insert(this);

    // Dual purpose insert
    Inserted = candidates.insert(this);

    // Check whether the insert was successfull, if not
    // the object "this" was among the candidates. Thus we have a dedected
    // a circular dependency
    if (!Inserted.second) return true;

    bool hasCircularDependencies = false;

    for (; it != end; ++it)
      if (verified.count(*it) == 0 &&
          (*it)->hasCircularDependencies(candidates, verified))
        {
          hasCircularDependencies = true;
          break;
        }

    // Remove the inserted object this from the candidates to avoid any
    // side effects.
    candidates.erase(Inserted.first);

    return hasCircularDependencies;
  }

//static
std::vector< Refresh * >
CCopasiObject::buildUpdateSequence(const std::set< const CCopasiObject * > & objects,
                                   const std::set< const CCopasiObject * > & uptoDateObjects)
{
  std::set< const CCopasiObject * > DependencySet;
  std::set< const CCopasiObject * > VerifiedSet;

  std::set< const CCopasiObject * >::const_iterator itSet;
  std::set< const CCopasiObject * >::const_iterator endSet = objects.end();
  std::pair<std::set< const CCopasiObject * >::iterator, bool> InsertedObject;

  assert (objects.count(NULL) == 0);

  // Check whether we have any circular dependencies
  for (itSet = objects.begin(); itSet != endSet; ++itSet)
    if ((*itSet)->hasCircularDependencies(DependencySet, VerifiedSet))
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCObject + 1, (*itSet)->getCN().c_str());

  // Build the complete set of dependencies
  for (itSet = objects.begin(); itSet != endSet; ++itSet)
    {
      // At least the object itself needs to be up to date.
      InsertedObject = DependencySet.insert(*itSet);

      // Add all its dependencies
      if (InsertedObject.second)
        (*itSet)->getAllDependencies(DependencySet);
    }

  // Remove all objects which do not have any refresh method as they will
  // be ignored anyway, i.e., no need to sort them.
  for (itSet = DependencySet.begin(), endSet = DependencySet.end(); itSet != endSet;)
    if (((*itSet)->getRefresh()) == NULL)
      {
        const CCopasiObject * pObject = *itSet;
        ++itSet;
        DependencySet.erase(pObject);
      }
    else
      ++itSet;

  // Remove the items in the ignore list
  itSet = uptoDateObjects.begin();
  endSet = uptoDateObjects.end();

  for (; itSet != endSet; ++itSet)
    DependencySet.erase(*itSet);

  // Create a properly sorted list.
  std::list< const CCopasiObject * > SortedList =
    sortObjectsByDependency(DependencySet.begin(), DependencySet.end());

  std::list< const CCopasiObject * >::iterator itList;
  std::list< const CCopasiObject * >::iterator endList;

  // Build the vector of pointers to refresh methods
  Refresh * pRefresh;

  std::vector< Refresh * > UpdateVector;
  std::vector< Refresh * >::const_iterator itUpdate;
  std::vector< Refresh * >::const_iterator endUpdate;

  itList = SortedList.begin();
  endList = SortedList.end();

  for (; itList != endList; ++itList)
    {
      pRefresh = (*itList)->getRefresh();
      itUpdate = UpdateVector.begin();
      endUpdate = UpdateVector.end();

      while (itUpdate != endUpdate && !(*itUpdate)->isEqual(pRefresh)) ++itUpdate;

      if (itUpdate == endUpdate)
        UpdateVector.push_back(pRefresh);
    }

  return UpdateVector;
}

// static
bool CCopasiObject::compare(const CCopasiObject * lhs, const CCopasiObject * rhs)
{
  if (lhs != rhs)
    {
      std::set< const CCopasiObject * > Candidates;
      std::set< const CCopasiObject * > VerifiedSet;

      Candidates.insert(lhs);

      if (rhs->hasCircularDependencies(Candidates, VerifiedSet))
        return true;
    }

  return false;
}

void * CCopasiObject::getValuePointer() const
  {
    return NULL;
  }

const CCopasiObject * CCopasiObject::getValueObject() const
  {
    return NULL;
  }

bool CCopasiObject::isContainer() const
  {return (0 < (mObjectFlag & Container));}

bool CCopasiObject::isVector() const
  {return (0 < (mObjectFlag & Vector));}

bool CCopasiObject::isMatrix() const
  {return (0 < (mObjectFlag & Matrix));}

bool CCopasiObject::isNameVector() const
  {return (0 < (mObjectFlag & NameVector));}

bool CCopasiObject::isReference() const
  {return (0 < (mObjectFlag & Reference));}

bool CCopasiObject::isValueBool() const
  {return (0 < (mObjectFlag & ValueBool));}

bool CCopasiObject::isValueInt() const
  {return (0 < (mObjectFlag & ValueInt));}

bool CCopasiObject::isValueDbl() const
  {return (0 < (mObjectFlag & ValueDbl));}

bool CCopasiObject::isNonUniqueName() const
  {return (0 < (mObjectFlag & NonUniqueName));}

bool CCopasiObject::isStaticString() const
  {return (0 < (mObjectFlag & StaticString));}

bool CCopasiObject::isValueString() const
  {return (0 < (mObjectFlag & ValueString));}

bool CCopasiObject::isSeparator() const
  {return (0 < (mObjectFlag & Separator));}

const std::string & CCopasiObject::getKey() const
  {
    static std::string DefaultKey("");
    //std::cout << "*********** CCopasiObject::getKey() should never be called! *********" << std::endl;
    return DefaultKey;
  }

void CCopasiObject::setObjectValue(const C_FLOAT64 & value)
{(*mpUpdateMethod)(value);}

void CCopasiObject::setObjectValue(const C_INT32 & value)
{(*mpUpdateMethod)(value);}

void CCopasiObject::setObjectValue(const bool & value)
{(*mpUpdateMethod)(value);}

UpdateMethod * CCopasiObject::getUpdateMethod() const
  {return mpUpdateMethod;}

bool CCopasiObject::hasUpdateMethod() const
  {return mpUpdateMethod != &mDefaultUpdateMethod;}

void CCopasiObject::clearRefresh()
{pdelete(mpRefresh);}

Refresh * CCopasiObject::getRefresh() const
  {return mpRefresh;}

std::ostream &operator<<(std::ostream &os, const CCopasiObject & o)
{
  os << "Name:      " << o.getObjectName() << std::endl;
  os << "Type:      " << o.getObjectType() << std::endl;
  os << "Container: " << o.isContainer() << std::endl;
  os << "Vector:    " << o.isVector() << std::endl;
  os << "VectorN:   " << o.isNameVector() << std::endl;
  os << "Matrix:    " << o.isMatrix() << std::endl;
  os << "Reference: " << o.isReference() << std::endl;
  os << "Bool:      " << o.isValueBool() << std::endl;
  os << "Int:       " << o.isValueInt() << std::endl;
  os << "Dbl:       " << o.isValueDbl() << std::endl;

  return os;
}
