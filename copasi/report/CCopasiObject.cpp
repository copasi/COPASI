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

const unsigned C_INT32 CCopasiObject::Container = 1;
const unsigned C_INT32 CCopasiObject::Vector = 2;
const unsigned C_INT32 CCopasiObject::Matrix = 4;
const unsigned C_INT32 CCopasiObject::NameVector = 8;

CCopasiObject::CCopasiObject():
    mObjectName(), mObjectType(), mpObjectParent(NULL), mObjectFlag(0)
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
          tmp << "[" << mObjectName << "]";
        else if (mpObjectParent->isVector())
          tmp << "[" << mpObjectParent->getIndex(this) << "]";

        tmp << "," << mObjectType << "=" << mObjectName;
        CN = tmp.str();
      }
    else
      {
        CN = CCopasiObjectName::escape(mObjectType)
             + "=" + CCopasiObjectName::escape(mObjectName);
      }

    return CN;
  }

CCopasiObject *
CCopasiObject::getObject(const CCopasiObjectName & C_UNUSED(cn)) const
  {return NULL;}

const std::string & CCopasiObject::getName() const {return mObjectName;}

const std::string & CCopasiObject::getObjectName() const {return mObjectName;}

const std::string & CCopasiObject::getObjectType() const {return mObjectType;}

CCopasiObject * CCopasiObject::getObjectParent() const {return mpObjectParent;}

unsigned C_INT32
CCopasiObject::getIndex(const CCopasiObject * C_UNUSED(pObject)) const
  {return C_INVALID_INDEX;}

void * CCopasiObject::getReference() {return this;}

bool CCopasiObject::isContainer() {return (0 < (mObjectFlag & Container));}

bool CCopasiObject::isVector() {return (0 < (mObjectFlag & Vector));}

bool CCopasiObject::isMatrix() {return (0 < (mObjectFlag & Matrix));}

bool CCopasiObject::isNameVector() {return (0 < (mObjectFlag & NameVector));}
