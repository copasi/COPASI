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

const unsigned C_INT32 CCopasiObject::Container = 0x1;
const unsigned C_INT32 CCopasiObject::Vector = 0x2;
const unsigned C_INT32 CCopasiObject::Matrix = 0x4;
const unsigned C_INT32 CCopasiObject::NameVector = 0x8;
const unsigned C_INT32 CCopasiObject::Reference = 0x10;
const unsigned C_INT32 CCopasiObject::ValueInt = 0x20;
const unsigned C_INT32 CCopasiObject::ValueDbl = 0x40;

const C_FLOAT64 CCopasiObject::DummyValue = 0.0;

CCopasiObject::CCopasiObject():
    mObjectName(),
    mObjectType(),
    mpObjectParent(NULL),
    mObjectFlag(0)
{}

CCopasiObject::CCopasiObject(const std::string & name,
                             const CCopasiContainer * pParent,
                             const std::string & type,
                             const unsigned C_INT32 & flag):
    mObjectName(name),
    mObjectType(type),
    mpObjectParent(const_cast<CCopasiContainer *>(pParent)),
    mObjectFlag(flag)
{}

CCopasiObject::CCopasiObject(const CCopasiObject & src,
                             const CCopasiContainer * pParent):
    mObjectName(src.mObjectName),
    mObjectType(src.mObjectType),
    mpObjectParent(const_cast<CCopasiContainer *>(pParent ? pParent : src.mpObjectParent)),
    mObjectFlag(src.mObjectFlag)
{}

CCopasiObject::~CCopasiObject() {}

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

const std::string & CCopasiObject::getName() const {return mObjectName;}

const void * CCopasiObject::getObjectValueAddress() const {return &DummyValue; /*TODO or throw exception? */}

const std::string & CCopasiObject::getObjectName() const {return mObjectName;}

const std::string & CCopasiObject::getObjectType() const {return mObjectType;}

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

void * CCopasiObject::getReference() {return this;}

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

bool CCopasiObject::hasValueInt() const
  {return (0 < (mObjectFlag & ValueInt));}

bool CCopasiObject::hasValueDbl() const
  {return (0 < (mObjectFlag & ValueDbl));}
