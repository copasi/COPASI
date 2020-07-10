// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

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

#include "copasi/copasi.h"

#include "copasi/utilities/CCopasiParameter.h"

#include "copasi/undo/CData.h"
#include "copasi/utilities/CCopasiParameterGroup.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/undo/CUndoData.h"

// static
const CEnumAnnotation< std::string, CCopasiParameter::Type > CCopasiParameter::TypeName(
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
  "expression"
});

// static
const CEnumAnnotation< std::string, CCopasiParameter::Type > CCopasiParameter::XMLType(
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
  "expression"
});

// static
CCopasiParameter * CCopasiParameter::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  CCopasiParameter * pNew = NULL;

  CCopasiParameter::Type Type = CCopasiParameter::TypeName.toEnum(data.getProperty(CData::PARAMETER_TYPE).toString());

  if (CCopasiParameter::Type::GROUP != Type)
    {
      pNew = new CCopasiParameter(data.getProperty(CData::OBJECT_NAME).toString(), Type);
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

  Data.addProperty(CData::PARAMETER_TYPE, CCopasiParameter::TypeName[mType]);

  switch (mType)
    {
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        Data.addProperty(CData::PARAMETER_VALUE, * static_cast< C_FLOAT64 * >(mpValue));
        break;

      case CCopasiParameter::Type::INT:
        Data.addProperty(CData::PARAMETER_VALUE, * static_cast< C_INT32 * >(mpValue));
        break;

      case CCopasiParameter::Type::UINT:
        Data.addProperty(CData::PARAMETER_VALUE, * static_cast< unsigned C_INT32 * >(mpValue));
        break;

      case CCopasiParameter::Type::BOOL:
        Data.addProperty(CData::PARAMETER_VALUE, * static_cast< bool * >(mpValue));
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:
      case CCopasiParameter::Type::CN:
        Data.addProperty(CData::PARAMETER_VALUE, * static_cast< std::string * >(mpValue));
        break;

      case CCopasiParameter::Type::GROUP:
      case CCopasiParameter::Type::INVALID:
        break;
    }

  return Data;
}

// virtual
bool CCopasiParameter::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = CDataContainer::applyData(data, changes);

  Type DataType = mType;

  if (data.isSetProperty(CData::PARAMETER_TYPE))
    {
      DataType = CCopasiParameter::TypeName.toEnum(data.getProperty(CData::PARAMETER_TYPE).toString());
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
      assignValue(data.getProperty(CData::PARAMETER_VALUE).raw());
    }

  return success;
}

// virtual
void CCopasiParameter::createUndoData(CUndoData & undoData,
                                      const CUndoData::Type & type,
                                      const CData & oldData,
                                      const CCore::Framework & framework) const
{
  CDataContainer::createUndoData(undoData, type, oldData, framework);

  if (type != CUndoData::Type::CHANGE)
    {
      return;
    }

  undoData.addProperty(CData::PARAMETER_TYPE, oldData.getProperty(CData::PARAMETER_TYPE), CCopasiParameter::TypeName[mType]);

  switch (mType)
    {
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        undoData.addProperty(CData::PARAMETER_VALUE, oldData.getProperty(CData::PARAMETER_VALUE), * static_cast< C_FLOAT64 * >(mpValue));
        break;

      case CCopasiParameter::Type::INT:
        undoData.addProperty(CData::PARAMETER_VALUE, oldData.getProperty(CData::PARAMETER_VALUE), * static_cast< C_INT32 * >(mpValue));
        break;

      case CCopasiParameter::Type::UINT:
        undoData.addProperty(CData::PARAMETER_VALUE, oldData.getProperty(CData::PARAMETER_VALUE), * static_cast< unsigned C_INT32 * >(mpValue));
        break;

      case CCopasiParameter::Type::BOOL:
        undoData.addProperty(CData::PARAMETER_VALUE, oldData.getProperty(CData::PARAMETER_VALUE), * static_cast< bool * >(mpValue));
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:
      case CCopasiParameter::Type::CN:
        undoData.addProperty(CData::PARAMETER_VALUE, oldData.getProperty(CData::PARAMETER_VALUE), * static_cast< std::string * >(mpValue));
        break;

      case CCopasiParameter::Type::GROUP:
      case CCopasiParameter::Type::INVALID:
        break;
    }

  return;
}

CCopasiParameter::CCopasiParameter():
  CDataContainer("NoName", NULL, "Parameter"),
  mKey(CRootContainer::getKeyFactory()->add("Parameter", this)),
  mType(CCopasiParameter::Type::INVALID),
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
                 ((type == CCopasiParameter::Type::DOUBLE || type == CCopasiParameter::Type::UDOUBLE) ? CDataObject::ValueDbl :
                  ((type == CCopasiParameter::Type::INT || type == CCopasiParameter::Type::UINT) ? CDataObject::ValueInt :
                   ((type == CCopasiParameter::Type::STRING || type == CCopasiParameter::Type::CN || type == CCopasiParameter::Type::KEY || type == CCopasiParameter::Type::FILE || type == CCopasiParameter::Type::EXPRESSION) ? CDataObject::ValueString :
                    (type == CCopasiParameter::Type::BOOL) ? CDataObject::ValueBool : CDataObject::Container)))),
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
  pdelete(mpValueReference);
}

// virtual
bool CCopasiParameter::setObjectParent(const CDataContainer * pParent)
{
  if (pParent != NULL &&
      dynamic_cast< const CCopasiParameter * >(pParent) != NULL)
    {
      if (static_cast< const CCopasiParameter * >(pParent)->isUnsupported())
        mUserInterfaceFlag |= eUserInterfaceFlag::unsupported;
      else
        mUserInterfaceFlag &= ~UserInterfaceFlag(eUserInterfaceFlag::unsupported);
    }

  return CDataContainer::setObjectParent(pParent);
}

CCopasiParameter & CCopasiParameter::operator = (const CCopasiParameter & rhs)
{
  // Check for assignment to itself
  if (this == &rhs) return *this;

  if (getObjectName() != rhs.getObjectName())
    {
      setObjectName(rhs.getObjectName());
      mUserInterfaceFlag = rhs.mUserInterfaceFlag;
      assignDefault(rhs.mpDefault);
    }

  mValidity = rhs.mValidity;

  if (mType != rhs.mType)
    {
      deleteValue(mType, mpValue);
      deleteValue(mType, mpDefault);
      deleteValidValues(mType, mpValidValues);

      mType = rhs.mType;
    }

  assignValue(rhs.mpValue);
  assignValidValues(rhs.mpValidValues);

  if (mType == CCopasiParameter::Type::GROUP)
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
  if ((mType != CCopasiParameter::Type::DOUBLE &&
       mType != CCopasiParameter::Type::UDOUBLE) ||
      (mType == CCopasiParameter::Type::UDOUBLE &&
       value < 0.0)) return false;

  return inValidValues(value);
}

bool CCopasiParameter::isValidValue(const C_INT32 & value) const
{
  if (mType != CCopasiParameter::Type::INT) return false;

  return inValidValues(value);
}

bool CCopasiParameter::isValidValue(const unsigned C_INT32 & value) const
{
  if (mType != CCopasiParameter::Type::UINT) return false;

  return inValidValues(value);
}

bool CCopasiParameter::isValidValue(const bool & value) const
{
  if (mType != CCopasiParameter::Type::BOOL) return false;

  return inValidValues(value);
}

bool CCopasiParameter::isValidValue(const std::string & value) const
{
  if (mType == CCopasiParameter::Type::KEY)
    return CKeyFactory::isValidKey(value);

  if (mType != CCopasiParameter::Type::STRING &&
      mType != CCopasiParameter::Type::FILE &&
      mType != CCopasiParameter::Type::EXPRESSION) return false;

  return inValidValues(value);
}

bool CCopasiParameter::isValidValue(const CCommonName & /* value */) const
{
  if (mType != CCopasiParameter::Type::CN) return false;

  return true;
}

bool CCopasiParameter::isValidValue(const CCopasiParameterGroup::elements & /* value */) const
{
  if (mType != CCopasiParameter::Type::GROUP) return false;

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
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        os << * static_cast< C_FLOAT64 * >(o.mpValue);
        break;

      case CCopasiParameter::Type::INT:
        os << * static_cast< C_INT32 * >(o.mpValue);
        break;

      case CCopasiParameter::Type::UINT:
        os << * static_cast< unsigned C_INT32 * >(o.mpValue);
        break;

      case CCopasiParameter::Type::BOOL:
        os << * static_cast< bool * >(o.mpValue);
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:
        os << * static_cast< std::string * >(o.mpValue);
        break;

      case CCopasiParameter::Type::CN:
        os << * static_cast< CRegisteredCommonName * >(o.mpValue);
        break;

      case CCopasiParameter::Type::GROUP:
      case CCopasiParameter::Type::INVALID:
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
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        return compareValues< C_FLOAT64 >(lhs, rhs);
        break;

      case CCopasiParameter::Type::INT:
        return compareValues< C_INT32 >(lhs, rhs);
        break;

      case CCopasiParameter::Type::UINT:
        return compareValues< unsigned C_INT32 >(lhs, rhs);
        break;

      case CCopasiParameter::Type::BOOL:
        return compareValues< bool >(lhs, rhs);
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:
        return compareValues< std::string >(lhs, rhs);
        break;

      case CCopasiParameter::Type::CN:
        return compareValues< CRegisteredCommonName >(lhs, rhs);
        break;

      case CCopasiParameter::Type::GROUP:
        return *static_cast<const CCopasiParameterGroup *>(&lhs) ==
               *static_cast<const CCopasiParameterGroup *>(&rhs);
        break;

      case CCopasiParameter::Type::INVALID:
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
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        mpValueReference = addObjectReference("Value", *static_cast< C_FLOAT64 * >(mpValue), CDataObject::ValueDbl);
        break;

      case CCopasiParameter::Type::INT:
        mpValueReference = addObjectReference("Value", *static_cast< C_INT32 * >(mpValue), CDataObject::ValueInt);
        break;

      case CCopasiParameter::Type::UINT:
        mpValueReference = addObjectReference("Value", *static_cast< unsigned C_INT32 * >(mpValue), CDataObject::ValueInt);
        break;

      case CCopasiParameter::Type::BOOL:
        mpValueReference = addObjectReference("Value", *static_cast< bool * >(mpValue), CDataObject::ValueBool);
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:
        mpValueReference = addObjectReference("Value", *static_cast< std::string * >(mpValue), CDataObject::ValueString);
        break;

      case CCopasiParameter::Type::CN:
        mpValueReference = addObjectReference("Value", *static_cast< CRegisteredCommonName * >(mpValue), CDataObject::ValueString);
        break;

      case CCopasiParameter::Type::GROUP:
        break;

      case CCopasiParameter::Type::INVALID:
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
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        *static_cast<std::vector< std::pair< C_FLOAT64, C_FLOAT64 > > * >(mpValidValues) =
          *static_cast< const std::vector< std::pair< C_FLOAT64, C_FLOAT64 > > * >(pValidValues);
        break;

      case CCopasiParameter::Type::INT:
        *static_cast<std::vector< std::pair< C_INT32, C_INT32 > > * >(mpValidValues) =
          *static_cast< const std::vector< std::pair< C_INT32, C_INT32 > > * >(pValidValues);
        break;

      case CCopasiParameter::Type::UINT:
        *static_cast<std::vector< std::pair< unsigned C_INT32, unsigned C_INT32 > > * >(mpValidValues) =
          *static_cast< const std::vector< std::pair< unsigned C_INT32, unsigned C_INT32 > > * >(pValidValues);
        break;

      case CCopasiParameter::Type::BOOL:
        *static_cast<std::vector< std::pair< bool, bool > > * >(mpValidValues) =
          *static_cast< const std::vector< std::pair< bool, bool > > * >(pValidValues);
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:
        *static_cast<std::vector< std::pair< std::string, std::string > > * >(mpValidValues) =
          *static_cast< const std::vector< std::pair< std::string, std::string > > * >(pValidValues);
        break;

      case CCopasiParameter::Type::CN:
        *static_cast<std::vector< std::pair< CRegisteredCommonName, CRegisteredCommonName > > * >(mpValidValues) =
          *static_cast< const std::vector< std::pair< CRegisteredCommonName, CRegisteredCommonName > > * >(pValidValues);
        break;

      case CCopasiParameter::Type::GROUP:
      case CCopasiParameter::Type::INVALID:
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
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        pValue = new C_FLOAT64;
        break;

      case CCopasiParameter::Type::INT:
        pValue = new C_INT32;
        break;

      case CCopasiParameter::Type::UINT:
        pValue = new unsigned C_INT32;
        break;

      case CCopasiParameter::Type::BOOL:
        pValue = new bool;
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:
        pValue = new std::string;
        break;

      case CCopasiParameter::Type::CN:
        pValue = new CRegisteredCommonName;
        break;

      case CCopasiParameter::Type::GROUP:
        pValue = new CCopasiParameterGroup::elements;
        break;

      case CCopasiParameter::Type::INVALID:
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
         type == CCopasiParameter::Type::GROUP ||
         type == CCopasiParameter::Type::INVALID);

  switch (type)
    {
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        *static_cast< C_FLOAT64 * >(pTarget) = *static_cast< const C_FLOAT64 * >(pSource);
        break;

      case CCopasiParameter::Type::INT:
        *static_cast< C_INT32 * >(pTarget) = *static_cast< const C_INT32 * >(pSource);
        break;

      case CCopasiParameter::Type::UINT:
        *static_cast< unsigned C_INT32 * >(pTarget) = *static_cast< const unsigned C_INT32 * >(pSource);
        break;

      case CCopasiParameter::Type::BOOL:
        *static_cast< bool * >(pTarget) = *static_cast< const bool * >(pSource);
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:
        *static_cast< std::string * >(pTarget) = *static_cast< const std::string * >(pSource);
        break;

      case CCopasiParameter::Type::CN:
        *static_cast< CRegisteredCommonName * >(pTarget) = *static_cast< const CRegisteredCommonName * >(pSource);
        break;

      case CCopasiParameter::Type::GROUP:
      case CCopasiParameter::Type::INVALID:
        break;
    }
}

// static
void CCopasiParameter::deleteValue(const Type & type, void *& pValue)
{
  if (pValue == NULL) return;

  switch (type)
    {
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        delete static_cast< C_FLOAT64 * >(pValue);
        break;

      case CCopasiParameter::Type::INT:
        delete static_cast< C_INT32 * >(pValue);
        break;

      case CCopasiParameter::Type::UINT:
        delete static_cast< unsigned C_INT32 * >(pValue);
        break;

      case CCopasiParameter::Type::BOOL:
        delete static_cast< bool * >(pValue);
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:
        delete static_cast< std::string * >(pValue);
        break;

      case CCopasiParameter::Type::CN:
        delete static_cast< CRegisteredCommonName * >(pValue);
        break;

      case CCopasiParameter::Type::GROUP:
        delete static_cast< CCopasiParameterGroup::elements * >(pValue);
        break;

      case CCopasiParameter::Type::INVALID:
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
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        pValidValues = new std::vector< std::pair< C_FLOAT64, C_FLOAT64 > >;
        break;

      case CCopasiParameter::Type::INT:
        pValidValues = new std::vector< std::pair< C_INT32, C_INT32 > >;
        break;

      case CCopasiParameter::Type::UINT:
        pValidValues = new std::vector< std::pair< unsigned C_INT32, unsigned C_INT32 > >;
        break;

      case CCopasiParameter::Type::BOOL:
        pValidValues = new std::vector< std::pair< bool, bool > >;
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:
        pValidValues = new std::vector< std::pair< std::string, std::string > >;
        break;

      case CCopasiParameter::Type::CN:
        pValidValues = new std::vector< std::pair< CRegisteredCommonName, CRegisteredCommonName > >;
        break;

      case CCopasiParameter::Type::GROUP:
      case CCopasiParameter::Type::INVALID:
        break;
    }
}

// static
void CCopasiParameter::deleteValidValues(const Type & type, void *& pValidValues)
{
  if (pValidValues == NULL) return;

  switch (type)
    {
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        delete static_cast< std::vector< std::pair < C_FLOAT64, C_FLOAT64 > > * >(pValidValues);
        break;

      case CCopasiParameter::Type::INT:
        delete static_cast< std::vector< std::pair < C_INT32, C_INT32 > > * >(pValidValues);
        break;

      case CCopasiParameter::Type::UINT:
        delete static_cast< std::vector< std::pair < unsigned C_INT32, unsigned C_INT32 > > * >(pValidValues);
        break;

      case CCopasiParameter::Type::BOOL:
        delete static_cast< std::vector< std::pair < bool, bool > > * >(pValidValues);
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:
        delete static_cast< std::vector< std::pair < std::string, std::string > > * >(pValidValues);
        break;

      case CCopasiParameter::Type::CN:
        delete static_cast< std::vector< std::pair < CRegisteredCommonName, CRegisteredCommonName > > * >(pValidValues);
        break;

      case CCopasiParameter::Type::GROUP:
      case CCopasiParameter::Type::INVALID:
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

  if (tmp && getType() != CCopasiParameter::Type::GROUP)
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

      if (getType() == CCopasiParameter::Type::GROUP)
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
  return mUserInterfaceFlag.isSet(eUserInterfaceFlag::editable);
}

bool CCopasiParameter::isBasic() const
{
  return mUserInterfaceFlag.isSet(eUserInterfaceFlag::basic);
}

bool CCopasiParameter::isUnsupported() const
{
  return mUserInterfaceFlag.isSet(eUserInterfaceFlag::unsupported);
}

bool CCopasiParameter::isDefault() const
{
  if (mpDefault == NULL) return true;

  switch (mType)
    {
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        return *static_cast< const C_FLOAT64 * >(mpValue) == *static_cast< const C_FLOAT64 * >(mpDefault);
        break;

      case CCopasiParameter::Type::INT:
        return *static_cast< const C_INT32 * >(mpValue) == *static_cast< const C_INT32 * >(mpDefault);
        break;

      case CCopasiParameter::Type::UINT:
        return *static_cast< const unsigned C_INT32 * >(mpValue) == *static_cast< const unsigned C_INT32 * >(mpDefault);
        break;

      case CCopasiParameter::Type::BOOL:
        return *static_cast< const bool * >(mpValue) == *static_cast< const bool * >(mpDefault);
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:
        return *static_cast< const std::string * >(mpValue) == *static_cast< const std::string * >(mpDefault);
        break;

      case CCopasiParameter::Type::CN:
        return *static_cast< const CRegisteredCommonName * >(mpValue) == *static_cast< const CRegisteredCommonName * >(mpDefault);
        break;

      case CCopasiParameter::Type::GROUP:
        return *static_cast< const CCopasiParameterGroup::elements * >(mpValue) == *static_cast< const CCopasiParameterGroup::elements * >(mpDefault);
        break;

      case CCopasiParameter::Type::INVALID:
      default:
        return true;
        break;
    }

  return true;
}
