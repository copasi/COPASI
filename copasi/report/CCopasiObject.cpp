/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiObject.cpp,v $
   $Revision: 1.38 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/11/18 15:35:29 $
   End CVS Header */

/**
 * Class CCopasiObject
 *
 * This class is the base class for all global accessible objects in copasi.
 *
 * Copyright Stefan Hoops 2002
 */

#include <sstream>

#include "copasi.h"
#include "CCopasiObjectName.h"
#include "CCopasiObject.h"
#include "CCopasiContainer.h"

const C_FLOAT64 CCopasiObject::DummyValue = 0.0;

CCopasiObject::CCopasiObject():
    mObjectName("No Name"),
    mObjectType("Unknown Type"),
    mpObjectParent(NULL),
    mObjectFlag(0)
{}

CCopasiObject::CCopasiObject(const std::string & name,
                             const CCopasiContainer * pParent,
                             const std::string & type,
                             const unsigned C_INT32 & flag):
    mObjectName((name == "") ? "No Name" : name),
    mObjectType(type),
    mpObjectParent(const_cast<CCopasiContainer *>(pParent)),
    mObjectFlag(flag)
{
  if (mpObjectParent)
    if (mpObjectParent->isContainer()) mpObjectParent->add(this);
}

CCopasiObject::CCopasiObject(const CCopasiObject & src,
                             const CCopasiContainer * pParent):
mObjectName(src.mObjectName),
mObjectType(src.mObjectType),
mpObjectParent(const_cast<CCopasiContainer *>(pParent)),
mObjectFlag(src.mObjectFlag)
{if (mpObjectParent) mpObjectParent->add(this);}

CCopasiObject::~CCopasiObject()
{
  if (mpObjectParent)
    mpObjectParent->remove(this);
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
          tmp << "[" << mpObjectParent->getIndex(this) << "]";
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

//const std::string & CCopasiObject::getName() const {return mObjectName;}

const std::string
CCopasiObject::getObjectUniqueNameEx(const bool & isParent) const
  {
    if (isParent && isVector())
      return mpObjectParent->getObjectUniqueNameEx();

    if (mpObjectParent && 0 < (mObjectFlag & NonUniqueName))
      return mObjectName + "{" + mpObjectParent->getObjectUniqueNameEx() + "}";

    return mObjectName;
  }

const std::string CCopasiObject::getObjectUniqueName() const
{return getObjectUniqueNameEx(false);}

bool CCopasiObject::setObjectName(const std::string & name)
{
  if (name == mObjectName) return true;

  if (mpObjectParent && mpObjectParent->isNameVector())
    {
      CCopasiObjectName NewObject = CCopasiObjectName::escape(getObjectType() + "=" + name);

      if (mpObjectParent->getObject(NewObject))
        return false;
    }

  mObjectName = (name == "") ? "No Name" : name;

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
      }

    if (ret.length() >= 2)
      if ((ret.substr(ret.length() - 2) == "[]") && (!isReference()))
        {
          ret.insert(ret.length() - 1, getObjectName());
          if (isNameVector() || isVector())
            ret += "[]";
          return ret;
        }

    if (ret.length() != 0)
      ret += ".";

    if (isNameVector() || isVector())
      ret += getObjectName() + "[]";
    else if (isReference())
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

unsigned C_INT32
CCopasiObject::getIndex(const CCopasiObject * C_UNUSED(pObject)) const
{return C_INVALID_INDEX;}

unsigned C_INT32
CCopasiObject::getIndex(const std::string & C_UNUSED(name)) const
  {return C_INVALID_INDEX;}

void * CCopasiObject::getReference() const
  {return const_cast<CCopasiObject *>(this);}

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

bool CCopasiObject::isStaticString() const
  {return (0 < (mObjectFlag & StaticString));}

const std::string & CCopasiObject::getKey() const
  {
    static std::string DefaultKey("");
    std::cout << "*********** CCopasiObject::getKey() should never be called! *********" << std::endl;
    return DefaultKey;
  }

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
