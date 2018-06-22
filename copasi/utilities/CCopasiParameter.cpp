// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

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

#include "copasi.h"

#include "utilities/CCopasiParameter.h"

#include "copasi/undo/CData.h"
#include "utilities/CCopasiParameterGroup.h"
#include "utilities/CCopasiMessage.h"
#include "report/CKeyFactory.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/core/CRootContainer.h"

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

// static
CCopasiParameter * CCopasiParameter::fromData(const CData & data)
{
  CCopasiParameter * pNew = NULL;

  if (CCopasiParameter::GROUP != (Type) data.getProperty(CData::PARAMETER_TYPE).toUint())
    {
      pNew = new CCopasiParameter(data.getProperty(CData::OBJECT_NAME).toString(),
                                  (CCopasiParameter::Type) data.getProperty(CData::PARAMETER_TYPE).toUint());
    }
  else
    {
      pNew = new CCopasiParameterGroup(data.getProperty(CData::OBJECT_NAME).toString());
    }

  return pNew;
}

// virtual
CData CCopasiParameter::toData() const
{
  CData Data = CDataContainer::toData();

  Data.addProperty(CData::PARAMETER_TYPE, (unsigned C_INT32) mType);

  switch (mType)
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        Data.addProperty(CData::PARAMETER_VALUE, * static_cast< C_FLOAT64 * >(mpValue));
        break;

      case CCopasiParameter::INT:
        Data.addProperty(CData::PARAMETER_VALUE, * static_cast< C_INT32 * >(mpValue));
        break;

      case CCopasiParameter::UINT:
        Data.addProperty(CData::PARAMETER_VALUE, * static_cast< unsigned C_INT32 * >(mpValue));
        break;

      case CCopasiParameter::BOOL:
        Data.addProperty(CData::PARAMETER_VALUE, * static_cast< bool * >(mpValue));
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
      case CCopasiParameter::CN:
        Data.addProperty(CData::PARAMETER_VALUE, * static_cast< std::string * >(mpValue));
        break;

      case CCopasiParameter::GROUP:
      case CCopasiParameter::INVALID:
        break;
    }

  return Data;
}

// virtual
bool CCopasiParameter::applyData(const CData & data)
{
  bool success = CDataContainer::applyData(data);

  Type DataType = mType;

  if (data.isSetProperty(CData::PARAMETER_TYPE))
    {
      DataType = (Type) data.getProperty(CData::PARAMETER_TYPE).toUint();
    }

  if (mType != DataType)
    {
      deleteValue(mType, mpValue);
      deleteValue(mType, mpDefault);
      deleteValidValues(mType, mpValidValues);

      mType = DataType;
      createValue();
    }

  if (data.isSetProperty(CData::PARAMETER_VALUE))
    {
      assignValue(&data.getProperty(CData::PARAMETER_VALUE));
    }

  return success;
}

CCopasiParameter::CCopasiParameter():
  CDataContainer("NoName", NULL, "Parameter"),
  mKey(CRootContainer::getKeyFactory()->add("Parameter", this)),
  mType(INVALID),
  mpValue(NULL),
  mpValueReference(NULL),
  mpValidValues(NULL),
  mpDefault(NULL),
  mUserInterfaceFlag(UserInterfaceFlag::All)
{}

CCopasiParameter::CCopasiParameter(const CCopasiParameter & src,
                                   const CDataContainer * pParent):
  CDataContainer(src, pParent),
  mKey(CRootContainer::getKeyFactory()->add(src.getObjectType(), this)),
  mType(src.mType),
  mpValue(NULL),
  mpValueReference(NULL),
  mpValidValues(NULL),
  mpDefault(NULL),
  mUserInterfaceFlag(src.mUserInterfaceFlag)
{
  assignValue(src.mpValue);
  assignDefault(src.mpDefault);
  assignValidValues(src.mpValidValues);
}

CCopasiParameter::CCopasiParameter(const std::string & name,
                                   const CCopasiParameter::Type & type,
                                   const void * pValue,
                                   const CDataContainer * pParent,
                                   const std::string & objectType):
  CDataContainer(name, pParent, objectType,
                 ((type == DOUBLE || type == UDOUBLE) ? CDataObject::ValueDbl :
                  ((type == INT || type == UINT) ? CDataObject::ValueInt :
                   ((type == STRING || type == CN || type == KEY || type == FILE || type == EXPRESSION) ? CDataObject::ValueString :
                    (type == BOOL) ? CDataObject::ValueBool : CDataObject::Container)))),
  mKey(CRootContainer::getKeyFactory()->add(objectType, this)),
  mType(type),
  mpValue(NULL),
  mpValueReference(NULL),
  mpValidValues(NULL),
  mpDefault(NULL),
  mUserInterfaceFlag(UserInterfaceFlag::All)
{
  assignValue(pValue);
}

CCopasiParameter::~CCopasiParameter()
{
  if (CRootContainer::getRoot())
    CRootContainer::getKeyFactory()->remove(mKey);

  deleteValue(mType, mpValue);
  deleteValue(mType, mpDefault);
  deleteValidValues(mType, mpValidValues);
}

CCopasiParameter & CCopasiParameter::operator = (const CCopasiParameter & rhs)
{
  // Check for assignment to itself
  if (this == &rhs) return *this;

  if (getObjectName() != rhs.getObjectName())
    setObjectName(rhs.getObjectName());

  mUserInterfaceFlag = rhs.mUserInterfaceFlag;
  mValidity = rhs.mValidity;

  if (mType != rhs.mType)
    {
      deleteValue(mType, mpValue);
      deleteValue(mType, mpDefault);
      deleteValidValues(mType, mpValidValues);

      mType = rhs.mType;
    }

  assignValue(rhs.mpValue);
  assignDefault(rhs.mpDefault);
  assignValidValues(rhs.mpValidValues);

  if (mType == CCopasiParameter::GROUP)
    {
      *static_cast<CCopasiParameterGroup *>(this) = *static_cast<const CCopasiParameterGroup *>(&rhs);
    }

  return *this;
}

const std::string & CCopasiParameter::getKey() const {return mKey;}

bool CCopasiParameter::setValue(const std::vector< CCopasiParameter * > & /* value */)
{
  fatalError();
  return false;
}

bool CCopasiParameter::setDefault(const std::vector< CCopasiParameter * > & /* defaultValue*/)
{
  fatalError();
  return false;
}

CDataObject * CCopasiParameter::getValueReference() const
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

bool CCopasiParameter::isValidValue(const CCommonName & /* value */) const
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
        os << * static_cast< CRegisteredCommonName * >(o.mpValue);
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
        return compareValues< CRegisteredCommonName >(lhs, rhs);
        break;

      case CCopasiParameter::GROUP:
        return *static_cast<const CCopasiParameterGroup *>(&lhs) ==
               *static_cast<const CCopasiParameterGroup *>(&rhs);
        break;

      case CCopasiParameter::INVALID:
      default:
        break;
    }

  return false;
}

// virtual
CCommonName CCopasiParameter::getCN() const
{
  CDataContainer * pObjectParent = getObjectParent();
  CCopasiParameterGroup * pGroup;

  if (pObjectParent != NULL &&
      (pGroup = dynamic_cast< CCopasiParameterGroup * >(pObjectParent)) != NULL)
    {
      return pObjectParent->getCN() + "," + CCommonName::escape(getObjectType()) + "=" + CCommonName::escape(pGroup->getUniqueParameterName(this));
    }

  return CDataObject::getCN();
}

void * CCopasiParameter::getValuePointer() const
{return const_cast<void *>(mpValue);}

void * CCopasiParameter::getValidValuesPointer() const
{return const_cast<void *>(mpValidValues);}

void CCopasiParameter::createValue()
{
  deleteValue(mType, mpValue);
  pdelete(mpValueReference);

  allocateValue(mType, mpValue);

  switch (mType)
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        mpValueReference = addObjectReference("Value", *static_cast< C_FLOAT64 * >(mpValue), CDataObject::ValueDbl);
        break;

      case CCopasiParameter::INT:
        mpValueReference = addObjectReference("Value", *static_cast< C_INT32 * >(mpValue), CDataObject::ValueInt);
        break;

      case CCopasiParameter::UINT:
        mpValueReference = addObjectReference("Value", *static_cast< unsigned C_INT32 * >(mpValue), CDataObject::ValueInt);
        break;

      case CCopasiParameter::BOOL:
        mpValueReference = addObjectReference("Value", *static_cast< bool * >(mpValue), CDataObject::ValueBool);
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
        mpValueReference = addObjectReference("Value", *static_cast< std::string * >(mpValue), CDataObject::ValueString);
        break;

      case CCopasiParameter::CN:
        mpValueReference = addObjectReference("Value", *static_cast< CRegisteredCommonName * >(mpValue), CDataObject::ValueString);
        break;

      case CCopasiParameter::GROUP:
        break;

      case CCopasiParameter::INVALID:
        break;
    }
}

void CCopasiParameter::assignValue(const void * pValue)
{
  if (mpValue == NULL)
    {
      createValue();
    }

  assignValue(mType, mpValue, pValue);
}

void CCopasiParameter::assignValidValues(const void * pValidValues)
{
  if (pValidValues == NULL)
    {
      deleteValidValues(mType, mpValidValues);

      return;
    }

  if (mpValidValues == NULL)
    {
      allocateValidValues(mType, mpValidValues);
    }

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
        *static_cast<std::vector< std::pair< CRegisteredCommonName, CRegisteredCommonName > > * >(mpValidValues) =
          *static_cast< const std::vector< std::pair< CRegisteredCommonName, CRegisteredCommonName > > * >(pValidValues);
        break;

      case CCopasiParameter::GROUP:
      case CCopasiParameter::INVALID:
        break;
    }
}

void CCopasiParameter::assignDefault(const void * pDefault)
{
  if (pDefault == NULL)
    {
      deleteValue(mType, mpDefault);

      return;
    }

  if (mpDefault == NULL)
    {
      allocateValue(mType, mpDefault);
    }

  assignValue(mType, mpDefault, pDefault);
}

// static
void CCopasiParameter::allocateValue(const Type & type, void *& pValue)
{
  // We do not overwrite existing data
  if (pValue != NULL) return;

  switch (type)
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        pValue = new C_FLOAT64;
        break;

      case CCopasiParameter::INT:
        pValue = new C_INT32;
        break;

      case CCopasiParameter::UINT:
        pValue = new unsigned C_INT32;
        break;

      case CCopasiParameter::BOOL:
        pValue = new bool;
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
        pValue = new std::string;
        break;

      case CCopasiParameter::CN:
        pValue = new CRegisteredCommonName;
        break;

      case CCopasiParameter::GROUP:
        pValue = new CCopasiParameterGroup::elements;
        break;

      case CCopasiParameter::INVALID:
        pValue = NULL;
        break;
    }

  return;
}

// static
void CCopasiParameter::assignValue(const Type & type, void *& pTarget, const void * pSource)
{
  if (pSource == NULL) return;

  // sanity checks
  assert(pTarget != NULL ||
         type == CCopasiParameter::GROUP ||
         type == CCopasiParameter::INVALID);

  switch (type)
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        *static_cast< C_FLOAT64 * >(pTarget) = *static_cast< const C_FLOAT64 * >(pSource);
        break;

      case CCopasiParameter::INT:
        *static_cast< C_INT32 * >(pTarget) = *static_cast< const C_INT32 * >(pSource);
        break;

      case CCopasiParameter::UINT:
        *static_cast< unsigned C_INT32 * >(pTarget) = *static_cast< const unsigned C_INT32 * >(pSource);
        break;

      case CCopasiParameter::BOOL:
        *static_cast< bool * >(pTarget) = *static_cast< const bool * >(pSource);
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
        *static_cast< std::string * >(pTarget) = *static_cast< const std::string * >(pSource);
        break;

      case CCopasiParameter::CN:
        *static_cast< CRegisteredCommonName * >(pTarget) = *static_cast< const CRegisteredCommonName * >(pSource);
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
        delete static_cast< CRegisteredCommonName * >(pValue);
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
void CCopasiParameter::allocateValidValues(const Type & type, void *& pValidValues)
{
  // We do not overwrite existing data
  if (pValidValues != NULL) return;

  switch (type)
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        pValidValues = new std::vector< std::pair< C_FLOAT64, C_FLOAT64 > >;
        break;

      case CCopasiParameter::INT:
        pValidValues = new std::vector< std::pair< C_INT32, C_INT32 > >;
        break;

      case CCopasiParameter::UINT:
        pValidValues = new std::vector< std::pair< unsigned C_INT32, unsigned C_INT32 > >;
        break;

      case CCopasiParameter::BOOL:
        pValidValues = new std::vector< std::pair< bool, bool > >;
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
        pValidValues = new std::vector< std::pair< std::string, std::string > >;
        break;

      case CCopasiParameter::CN:
        pValidValues = new std::vector< std::pair< CRegisteredCommonName, CRegisteredCommonName > >;
        break;

      case CCopasiParameter::GROUP:
      case CCopasiParameter::INVALID:
        break;
    }
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
        delete static_cast< std::vector< std::pair < CRegisteredCommonName, CRegisteredCommonName > > * >(pValidValues);
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

  CDataObject* tmp = this->getObjectAncestor("Reaction");

  if (tmp && getType() != GROUP)
    {
      return tmp->getObjectDisplayName() + "." + getObjectName();
    }

  CDataContainer * pObjectParent = getObjectParent();
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

  return CDataObject::getObjectDisplayName();
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
  return mUserInterfaceFlag.isSet(editable);
}

bool CCopasiParameter::isBasic() const
{
  return mUserInterfaceFlag.isSet(basic);
}

bool CCopasiParameter::isDefault() const
{
  if (mpDefault == NULL) return true;

  switch (mType)
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        return *static_cast< const C_FLOAT64 * >(mpValue) == *static_cast< const C_FLOAT64 * >(mpDefault);
        break;

      case CCopasiParameter::INT:
        return *static_cast< const C_INT32 * >(mpValue) == *static_cast< const C_INT32 * >(mpDefault);
        break;

      case CCopasiParameter::UINT:
        return *static_cast< const unsigned C_INT32 * >(mpValue) == *static_cast< const unsigned C_INT32 * >(mpDefault);
        break;

      case CCopasiParameter::BOOL:
        return *static_cast< const bool * >(mpValue) == *static_cast< const bool * >(mpDefault);
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
        return *static_cast< const std::string * >(mpValue) == *static_cast< const std::string * >(mpDefault);
        break;

      case CCopasiParameter::CN:
        return *static_cast< const CRegisteredCommonName * >(mpValue) == *static_cast< const CRegisteredCommonName * >(mpDefault);
        break;

      case CCopasiParameter::GROUP:
        return *static_cast< const CCopasiParameterGroup::elements * >(mpValue) == *static_cast< const CCopasiParameterGroup::elements * >(mpDefault);
        break;

      case CCopasiParameter::INVALID:
      default:
        return true;
        break;
    }

  return true;
}
