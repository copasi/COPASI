// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CCopasiParameter class.
 *  This class is used to describe method parameters. This class is intended
 *  to be used with integration or optimization methods.
 *
 *  Created for COPASI by Stefan Hoops 2002
 */

#include <string>

#include "copasi/copasi.h"
#include "copasi/utilities/CCopasiParameter.h"
#include "copasi/utilities/CCopasiParameterGroup.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CCopasiObjectReference.h"
#include "copasi/report/CCopasiRootContainer.h"

const std::string CCopasiParameter::TypeName[] =
{
  "float",
  "unsigned float",
  "integer",
  "unsigned integer",
  "bool",
  "group",
  "string",
  "common name",
  "key",
  "file",
  "expression",
  ""
};

const char* CCopasiParameter::XMLType[] =
{
  "float",
  "unsignedFloat",
  "integer",
  "unsignedInteger",
  "bool",
  "group",
  "string",
  "cn",
  "key",
  "file",
  "expression",
  NULL
};

CCopasiParameter::CCopasiParameter():
  CCopasiContainer("NoName", NULL, "Parameter"),
  mKey(CCopasiRootContainer::getKeyFactory()->add("Parameter", this)),
  mType(INVALID),
  mSize(0),
  mpValue(NULL),
  mpValueReference(NULL),
  mpValidValues(NULL),
  mUserInterfaceFlag(all)
{}

CCopasiParameter::CCopasiParameter(const CCopasiParameter & src,
                                   const CCopasiContainer * pParent):
  CCopasiContainer(src, pParent),
  mKey(CCopasiRootContainer::getKeyFactory()->add(src.getObjectType(), this)),
  mType(src.mType),
  mSize(0),
  mpValue(NULL),
  mpValueReference(NULL),
  mpValidValues(NULL),
  mUserInterfaceFlag(src.mUserInterfaceFlag)
{
  createValue(src.mpValue);
  createValidValues(src.mpValidValues);
}

CCopasiParameter::CCopasiParameter(const std::string & name,
                                   const CCopasiParameter::Type & type,
                                   const void * pValue,
                                   const CCopasiContainer * pParent,
                                   const std::string & objectType):
  CCopasiContainer(name, pParent, objectType,
                   CCopasiObject::Container |
                   ((type == DOUBLE || type == UDOUBLE) ? CCopasiObject::ValueDbl :
                    ((type == INT || type == UINT) ? CCopasiObject::ValueInt :
                     ((type == STRING || type == CN || type == KEY || type == FILE || type == EXPRESSION) ? CCopasiObject::ValueString :
                      (type == BOOL) ? CCopasiObject::ValueBool : 0)))),
  mKey(CCopasiRootContainer::getKeyFactory()->add(objectType, this)),
  mType(type),
  mSize(0),
  mpValue(NULL),
  mpValueReference(NULL),
  mpValidValues(NULL),
  mUserInterfaceFlag(all)
{
  createValue(pValue);
}

CCopasiParameter::~CCopasiParameter()
{
  if (CCopasiRootContainer::getRoot())
    CCopasiRootContainer::getKeyFactory()->remove(mKey);

  deleteValue(mType, mpValue);
  deleteValidValues(mType, mpValidValues);
}

CCopasiParameter & CCopasiParameter::operator = (const CCopasiParameter & rhs)
{
  // Check for assignment to itself
  if (this == &rhs) return *this;

  if (getObjectName() != rhs.getObjectName())
    setObjectName(rhs.getObjectName());

  switch (rhs.mType)
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:

        if (mType != DOUBLE &&
            mType != UDOUBLE)
          {
            deleteValue(mType, mpValue);
            deleteValidValues(mType, mpValidValues);
            mType = rhs.mType;
          }
        else
          {
            mType = rhs.mType;
          }

        assignValue(rhs.mpValue);
        assignValidValues(rhs.mpValidValues);
        break;

      case CCopasiParameter::INT:
      case CCopasiParameter::UINT:

        if (mType != INT &&
            mType != UINT)
          {
            deleteValue(mType, mpValue);
            deleteValidValues(mType, mpValidValues);
            mType = rhs.mType;
          }
        else
          {
            mType = rhs.mType;
          }

        assignValue(rhs.mpValue);
        assignValidValues(rhs.mpValidValues);
        break;

      case CCopasiParameter::BOOL:

        if (mType != BOOL)
          {
            deleteValue(mType, mpValue);
            deleteValidValues(mType, mpValidValues);
            mType = BOOL;
          }

        assignValue(rhs.mpValue);
        assignValidValues(rhs.mpValidValues);
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:

        if (mType != STRING &&
            mType != KEY &&
            mType != FILE &&
            mType != EXPRESSION)
          {
            deleteValue(mType, mpValue);
            deleteValidValues(mType, mpValidValues);
            mType = rhs.mType;
          }
        else
          {
            mType = rhs.mType;
          }

        assignValue(rhs.mpValue);
        assignValidValues(rhs.mpValidValues);
        break;

      case CCopasiParameter::CN:

        if (mType != CN)
          {
            deleteValue(mType, mpValue);
            deleteValidValues(mType, mpValidValues);
            mType = CN;
          }

        assignValue(rhs.mpValue);
        assignValidValues(rhs.mpValidValues);
        break;

      case CCopasiParameter::GROUP:

        if (mType != GROUP)
          {
            deleteValue(mType, mpValue);
            mType = GROUP;
            createValue(rhs.mpValue);
          }

        *static_cast<CCopasiParameterGroup *>(this) = *static_cast<const CCopasiParameterGroup *>(&rhs);

        break;

      case CCopasiParameter::INVALID:

        if (mType != INVALID)
          {
            deleteValue(mType, mpValue);
            mType = INVALID;
            createValue(rhs.mpValue);
          }

        break;
    }

  return *this;
}

const std::string & CCopasiParameter::getKey() const {return mKey;}

bool CCopasiParameter::setValue(const std::vector< CCopasiParameter * > & /* value */)
{
  fatalError();
  return false;
}

CCopasiObject * CCopasiParameter::getValueReference() const
{
  return mpValueReference;
}

const CCopasiParameter::Type & CCopasiParameter::getType() const
{return mType;}

bool CCopasiParameter::isValidValue(const C_FLOAT64 & value) const
{
  if ((mType != CCopasiParameter::DOUBLE &&
       mType != CCopasiParameter::UDOUBLE) ||
      (mType == CCopasiParameter::UDOUBLE &&
       value < 0.0)) return false;

  return inValidValues(value);
}

bool CCopasiParameter::isValidValue(const C_INT32 & value) const
{
  if (mType != CCopasiParameter::INT) return false;

  return inValidValues(value);
}

bool CCopasiParameter::isValidValue(const unsigned C_INT32 & value) const
{
  if (mType != CCopasiParameter::UINT) return false;

  return inValidValues(value);
}

bool CCopasiParameter::isValidValue(const bool & value) const
{
  if (mType != CCopasiParameter::BOOL) return false;

  return inValidValues(value);
}

bool CCopasiParameter::isValidValue(const std::string & value) const
{
  if (mType == CCopasiParameter::KEY)
    return CKeyFactory::isValidKey(value);

  if (mType != CCopasiParameter::STRING &&
      mType != CCopasiParameter::FILE &&
      mType != CCopasiParameter::EXPRESSION) return false;

  return inValidValues(value);
}

bool CCopasiParameter::isValidValue(const CCopasiObjectName & /* value */) const
{
  if (mType != CCopasiParameter::CN) return false;

  return true;
}

bool CCopasiParameter::isValidValue(const CCopasiParameterGroup::elements & /* value */) const
{
  if (mType != CCopasiParameter::GROUP) return false;

  return true;
}

bool CCopasiParameter::hasValidValues() const
{
  return mpValidValues != NULL;
}

void CCopasiParameter::print(std::ostream * ostream) const
{*ostream << *this;}

std::ostream &operator<<(std::ostream &os, const CCopasiParameter & o)
{
  os << "    " << o.getObjectName() << ": ";

  switch (o.mType)
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        os << * static_cast< C_FLOAT64 * >(o.mpValue);
        break;

      case CCopasiParameter::INT:
        os << * static_cast< C_INT32 * >(o.mpValue);
        break;

      case CCopasiParameter::UINT:
        os << * static_cast< unsigned C_INT32 * >(o.mpValue);
        break;

      case CCopasiParameter::BOOL:
        os << * static_cast< bool * >(o.mpValue);
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
        os << * static_cast< std::string * >(o.mpValue);
        break;

      case CCopasiParameter::CN:
        os << * static_cast< CRegisteredObjectName * >(o.mpValue);
        break;

      case CCopasiParameter::GROUP:
      case CCopasiParameter::INVALID:
        break;
    }

  return os;
}

bool operator==(const CCopasiParameter & lhs, const CCopasiParameter & rhs)
{
  if (lhs.getObjectName() != rhs.getObjectName()) return false;

  if (lhs.mType != rhs.mType) return false;

  switch (lhs.mType)
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        return compareValues< C_FLOAT64 >(lhs, rhs);
        break;

      case CCopasiParameter::INT:
        return compareValues< C_INT32 >(lhs, rhs);
        break;

      case CCopasiParameter::UINT:
        return compareValues< unsigned C_INT32 >(lhs, rhs);
        break;

      case CCopasiParameter::BOOL:
        return compareValues< bool >(lhs, rhs);
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
        return compareValues< std::string >(lhs, rhs);
        break;

      case CCopasiParameter::CN:
        return compareValues< CRegisteredObjectName >(lhs, rhs);
        break;

      case CCopasiParameter::GROUP:
        return *static_cast<const CCopasiParameterGroup *>(&lhs) ==
               *static_cast<const CCopasiParameterGroup *>(&rhs);
        break;

      case CCopasiParameter::INVALID:
      default:
        if (lhs.mSize != rhs.mSize) return false;

        return memcmp(lhs.mpValue, rhs.mpValue, lhs.mSize) == 0;
        break;
    }

  return false;
}

// virtual
CCopasiObjectName CCopasiParameter::getCN() const
{
  CCopasiContainer * pObjectParent = getObjectParent();
  CCopasiParameterGroup * pGroup;

  if (pObjectParent != NULL &&
      (pGroup = dynamic_cast< CCopasiParameterGroup * >(pObjectParent)) != NULL)
    {
      return pObjectParent->getCN() + "," + CCopasiObjectName::escape(getObjectType()) + "=" + CCopasiObjectName::escape(pGroup->getUniqueParameterName(this));
    }

  return CCopasiObject::getCN();
}

void * CCopasiParameter::getValuePointer() const
{return const_cast<void *>(mpValue);}

void * CCopasiParameter::getValidValuesPointer() const
{return const_cast<void *>(mpValidValues);}

void CCopasiParameter::createValue(const void * pValue)
{
  deleteValue(mType, mpValue);
  pdelete(mpValueReference);

  switch (mType)
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        mpValue = new C_FLOAT64;
        mSize = sizeof(C_FLOAT64);
        mpValueReference = addObjectReference("Value", *static_cast< C_FLOAT64 * >(mpValue), CCopasiObject::ValueDbl);
        assignValue(pValue);
        break;

      case CCopasiParameter::INT:
        mpValue = new C_INT32;
        mSize = sizeof(C_INT32);
        mpValueReference = addObjectReference("Value", *static_cast< C_INT32 * >(mpValue), CCopasiObject::ValueInt);
        assignValue(pValue);
        break;

      case CCopasiParameter::UINT:
        mpValue = new unsigned C_INT32;
        mSize = sizeof(unsigned C_INT32);
        mpValueReference = addObjectReference("Value", *static_cast< unsigned C_INT32 * >(mpValue), CCopasiObject::ValueInt);
        assignValue(pValue);
        break;

      case CCopasiParameter::BOOL:
        mpValue = new bool;
        mSize = sizeof(bool);
        mpValueReference = addObjectReference("Value", *static_cast< bool * >(mpValue), CCopasiObject::ValueBool);
        assignValue(pValue);
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
        mpValue = new std::string;
        mSize = sizeof(std::string);
        mpValueReference = addObjectReference("Value", *static_cast< std::string * >(mpValue), CCopasiObject::ValueString);
        assignValue(pValue);
        break;

      case CCopasiParameter::CN:
        mpValue = new CRegisteredObjectName;
        mSize = sizeof(CRegisteredObjectName);
        mpValueReference = addObjectReference("Value", *static_cast< CRegisteredObjectName * >(mpValue), CCopasiObject::ValueString);
        assignValue(pValue);
        break;

      case CCopasiParameter::GROUP:
        mpValue = new CCopasiParameterGroup::elements;
        mSize = sizeof(CCopasiParameterGroup::elements);
        break;

      case CCopasiParameter::INVALID:
        mpValue = NULL;
        mSize = 0;
        break;
    }
}

void CCopasiParameter::createValidValues(const void * pValidValues)
{
  deleteValidValues(mType, mpValidValues);

  if (pValidValues == NULL) return;

  switch (mType)
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        mpValidValues = new std::vector< std::pair< C_FLOAT64, C_FLOAT64 > >;
        assignValidValues(pValidValues);
        break;

      case CCopasiParameter::INT:
        mpValidValues = new std::vector< std::pair< C_INT32, C_INT32 > >;
        assignValidValues(pValidValues);
        break;

      case CCopasiParameter::UINT:
        mpValidValues = new std::vector< std::pair< unsigned C_INT32, unsigned C_INT32 > >;
        assignValidValues(pValidValues);
        break;

      case CCopasiParameter::BOOL:
        mpValidValues = new std::vector< std::pair< bool, bool > >;
        assignValidValues(pValidValues);
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
        mpValidValues = new std::vector< std::pair< std::string, std::string > >;
        assignValidValues(pValidValues);
        break;

      case CCopasiParameter::CN:
        mpValidValues = new std::vector< std::pair< CRegisteredObjectName, CRegisteredObjectName > >;
        assignValidValues(pValidValues);
        break;

      case CCopasiParameter::GROUP:
      case CCopasiParameter::INVALID:
        break;
    }
}

void CCopasiParameter::assignValue(const void * pValue)
{
  if (pValue == NULL) return;

  if (mpValue == NULL) return createValue(pValue);

  switch (mType)
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        *static_cast< C_FLOAT64 * >(mpValue) = *static_cast< const C_FLOAT64 * >(pValue);
        break;

      case CCopasiParameter::INT:
        *static_cast< C_INT32 * >(mpValue) = *static_cast< const C_INT32 * >(pValue);
        break;

      case CCopasiParameter::UINT:
        *static_cast< unsigned C_INT32 * >(mpValue) = *static_cast< const unsigned C_INT32 * >(pValue);
        break;

      case CCopasiParameter::BOOL:
        *static_cast< bool * >(mpValue) = *static_cast< const bool * >(pValue);
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
        *static_cast< std::string * >(mpValue) = *static_cast< const std::string * >(pValue);
        break;

      case CCopasiParameter::CN:
        *static_cast< CRegisteredObjectName * >(mpValue) = *static_cast< const CRegisteredObjectName * >(pValue);
        break;

      case CCopasiParameter::GROUP:
      case CCopasiParameter::INVALID:
        break;
    }
}

void CCopasiParameter::assignValidValues(const void * pValidValues)
{
  if (pValidValues == NULL) return;

  if (mpValidValues == NULL) return createValidValues(pValidValues);

  switch (mType)
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        *static_cast<std::vector< std::pair< C_FLOAT64, C_FLOAT64 > > * >(mpValidValues) =
          *static_cast< const std::vector< std::pair< C_FLOAT64, C_FLOAT64 > > * >(pValidValues);
        break;

      case CCopasiParameter::INT:
        *static_cast<std::vector< std::pair< C_INT32, C_INT32 > > * >(mpValidValues) =
          *static_cast< const std::vector< std::pair< C_INT32, C_INT32 > > * >(pValidValues);
        break;

      case CCopasiParameter::UINT:
        *static_cast<std::vector< std::pair< unsigned C_INT32, unsigned C_INT32 > > * >(mpValidValues) =
          *static_cast< const std::vector< std::pair< unsigned C_INT32, unsigned C_INT32 > > * >(pValidValues);
        break;

      case CCopasiParameter::BOOL:
        *static_cast<std::vector< std::pair< bool, bool > > * >(mpValidValues) =
          *static_cast< const std::vector< std::pair< bool, bool > > * >(pValidValues);
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
        *static_cast<std::vector< std::pair< std::string, std::string > > * >(mpValidValues) =
          *static_cast< const std::vector< std::pair< std::string, std::string > > * >(pValidValues);
        break;

      case CCopasiParameter::CN:
        *static_cast<std::vector< std::pair< CRegisteredObjectName, CRegisteredObjectName > > * >(mpValidValues) =
          *static_cast< const std::vector< std::pair< CRegisteredObjectName, CRegisteredObjectName > > * >(pValidValues);
        break;

      case CCopasiParameter::GROUP:
      case CCopasiParameter::INVALID:
        break;
    }
}

// static
void CCopasiParameter::deleteValue(const Type & type, void *& pValue)
{
  if (pValue == NULL) return;

  switch (type)
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        delete static_cast< C_FLOAT64 * >(pValue);
        break;

      case CCopasiParameter::INT:
        delete static_cast< C_INT32 * >(pValue);
        break;

      case CCopasiParameter::UINT:
        delete static_cast< unsigned C_INT32 * >(pValue);
        break;

      case CCopasiParameter::BOOL:
        delete static_cast< bool * >(pValue);
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
        delete static_cast< std::string * >(pValue);
        break;

      case CCopasiParameter::CN:
        delete static_cast< CRegisteredObjectName * >(pValue);
        break;

      case CCopasiParameter::GROUP:
        delete static_cast< CCopasiParameterGroup::elements * >(pValue);
        break;

      case CCopasiParameter::INVALID:
        break;

      default:
        fatalError();
        break;
    }

  pValue = NULL;

  return;
}

// static
void CCopasiParameter::deleteValidValues(const Type & type, void *& pValidValues)
{
  if (pValidValues == NULL) return;

  switch (type)
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        delete static_cast< std::vector< std::pair < C_FLOAT64, C_FLOAT64 > > * >(pValidValues);
        break;

      case CCopasiParameter::INT:
        delete static_cast< std::vector< std::pair < C_INT32, C_INT32 > > * >(pValidValues);
        break;

      case CCopasiParameter::UINT:
        delete static_cast< std::vector< std::pair < unsigned C_INT32, unsigned C_INT32 > > * >(pValidValues);
        break;

      case CCopasiParameter::BOOL:
        delete static_cast< std::vector< std::pair < bool, bool > > * >(pValidValues);
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
        delete static_cast< std::vector< std::pair < std::string, std::string > > * >(pValidValues);
        break;

      case CCopasiParameter::CN:
        delete static_cast< std::vector< std::pair < CRegisteredObjectName, CRegisteredObjectName > > * >(pValidValues);
        break;

      case CCopasiParameter::GROUP:
      case CCopasiParameter::INVALID:
        break;

      default:
        fatalError();
        break;
    }

  pValidValues = NULL;

  return;
}

// virtual
std::string CCopasiParameter::getObjectDisplayName() const
{
  // if one of the ancestors is a reaction and the parameter is not a group
  // it is (hopefully) a kinetic parameter

  CCopasiObject* tmp = this->getObjectAncestor("Reaction");

  if (tmp && getType() != GROUP)
    {
      return tmp->getObjectDisplayName() + "." + getObjectName();
    }

  CCopasiContainer * pObjectParent = getObjectParent();
  CCopasiParameterGroup * pGroup;

  if (pObjectParent != NULL &&
      (pGroup = dynamic_cast< CCopasiParameterGroup * >(pObjectParent)) != NULL)
    {
      std::string DisplayName = pGroup->getObjectDisplayName();

      if (DisplayName.length() >= 2 &&
          (DisplayName.substr(DisplayName.length() - 2) == "[]"))
        {
          DisplayName.insert(DisplayName.length() - 1, pGroup->getUniqueParameterName(this));
        }
      else
        {
          if ((DisplayName.length() != 0) && (DisplayName[DisplayName.length() - 1] != '.'))
            {
              DisplayName += ".";
            }

          DisplayName += pGroup->getUniqueParameterName(this);
        }

      if (getType() == GROUP)
        {
          DisplayName += "[]";
        }

      return DisplayName;
    }

  return CCopasiObject::getObjectDisplayName();
}

// virtual
void CCopasiParameter::setUserInterfaceFlag(const CCopasiParameter::UserInterfaceFlag & flag)
{
  mUserInterfaceFlag = flag;
}

const CCopasiParameter::UserInterfaceFlag & CCopasiParameter::getUserInterfaceFlag() const
{
  return mUserInterfaceFlag;
}

bool CCopasiParameter::isEditable() const
{
  return mUserInterfaceFlag & editable;
}

bool CCopasiParameter::isBasic() const
{
  return mUserInterfaceFlag & basic;
}
