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
bool CCopasiParameter::applyData(const CData & data, CUndoData::ChangeSet & changes)
{
  bool success = CDataContainer::applyData(data, changes);

  Type DataType = mType;

  if (data.isSetProperty(CData::PARAMETER_TYPE))
    {
      DataType = CCopasiParameter::TypeName.toEnum(data.getProperty(CData::PARAMETER_TYPE).toString());
    }

  const CDataValue * pValue = NULL;

  if (data.isSetProperty(CData::PARAMETER_VALUE))
    {
      pValue = &data.getProperty(CData::PARAMETER_VALUE);
    }

  switch (DataType)
    {
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:

        if (mType != CCopasiParameter::Type::DOUBLE &&
            mType != CCopasiParameter::Type::UDOUBLE)
          {
            deleteValue(mType, mpValue);
            deleteValidValues(mType, mpValidValues);
            mType = DataType;
            createValue(NULL);
          }
        else
          {
            mType = DataType;
          }

        if (pValue != NULL)
          {
            *static_cast< C_FLOAT64 * >(mpValue) = pValue->toDouble();
          }

        break;

      case CCopasiParameter::Type::INT:
      case CCopasiParameter::Type::UINT:

        if (mType != CCopasiParameter::Type::INT &&
            mType != CCopasiParameter::Type::UINT)
          {
            deleteValue(mType, mpValue);
            deleteValidValues(mType, mpValidValues);
            mType = DataType;
            createValue(NULL);
          }
        else
          {
            mType = DataType;
          }

        if (pValue != NULL)
          {
            *static_cast< C_INT32 * >(mpValue) = pValue->toInt();
          }

        break;

      case CCopasiParameter::Type::BOOL:

        if (mType != CCopasiParameter::Type::BOOL)
          {
            deleteValue(mType, mpValue);
            deleteValidValues(mType, mpValidValues);
            mType = CCopasiParameter::Type::BOOL;
            createValue(NULL);
          }

        if (pValue != NULL)
          {
            *static_cast< bool * >(mpValue) = pValue->toBool();
          }

        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:

        if (mType != CCopasiParameter::Type::STRING &&
            mType != CCopasiParameter::Type::KEY &&
            mType != CCopasiParameter::Type::FILE &&
            mType != CCopasiParameter::Type::EXPRESSION)
          {
            deleteValue(mType, mpValue);
            deleteValidValues(mType, mpValidValues);
            mType = DataType;
            createValue(NULL);
          }
        else
          {
            mType = DataType;
          }

        if (pValue != NULL)
          {
            *static_cast< std::string * >(mpValue) = pValue->toString();
          }

        break;

      case CCopasiParameter::Type::CN:

        if (mType != CCopasiParameter::Type::CN)
          {
            deleteValue(mType, mpValue);
            deleteValidValues(mType, mpValidValues);
            mType = CCopasiParameter::Type::CN;
            createValue(NULL);
          }

        if (pValue != NULL)
          {
            *static_cast< CRegisteredCommonName * >(mpValue) = pValue->toString();
          }

        break;

      case CCopasiParameter::Type::GROUP:

        if (mType != CCopasiParameter::Type::GROUP)
          {
            deleteValue(mType, mpValue);
            mType = CCopasiParameter::Type::GROUP;
            createValue(NULL);
          }

        break;

      case CCopasiParameter::Type::INVALID:

        if (mType != CCopasiParameter::Type::INVALID)
          {
            deleteValue(mType, mpValue);
            mType = CCopasiParameter::Type::INVALID;
            createValue(NULL);
          }

        break;
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
  mSize(0),
  mpValue(NULL),
  mpValueReference(NULL),
  mpValidValues(NULL),
  mUserInterfaceFlag(UserInterfaceFlag::All)
{}

CCopasiParameter::CCopasiParameter(const CCopasiParameter & src,
                                   const CDataContainer * pParent):
  CDataContainer(src, pParent),
  mKey(CRootContainer::getKeyFactory()->add(src.getObjectType(), this)),
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
                                   const CDataContainer * pParent,
                                   const std::string & objectType):
  CDataContainer(name, pParent, objectType,
                 ((type == CCopasiParameter::Type::DOUBLE || type == CCopasiParameter::Type::UDOUBLE) ? CDataObject::ValueDbl :
                  ((type == CCopasiParameter::Type::INT || type == CCopasiParameter::Type::UINT) ? CDataObject::ValueInt :
                   ((type == CCopasiParameter::Type::STRING || type == CCopasiParameter::Type::CN || type == CCopasiParameter::Type::KEY || type == CCopasiParameter::Type::FILE || type == CCopasiParameter::Type::EXPRESSION) ? CDataObject::ValueString :
                    (type == CCopasiParameter::Type::BOOL) ? CDataObject::ValueBool : CDataObject::Container)))),
  mKey(CRootContainer::getKeyFactory()->add(objectType, this)),
  mType(type),
  mSize(0),
  mpValue(NULL),
  mpValueReference(NULL),
  mpValidValues(NULL),
  mUserInterfaceFlag(UserInterfaceFlag::All)
{
  createValue(pValue);
}

CCopasiParameter::~CCopasiParameter()
{
  if (CRootContainer::getRoot())
    CRootContainer::getKeyFactory()->remove(mKey);

  deleteValue(mType, mpValue);
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

  switch (rhs.mType)
    {
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:

        if (mType != CCopasiParameter::Type::DOUBLE &&
            mType != CCopasiParameter::Type::UDOUBLE)
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

      case CCopasiParameter::Type::INT:
      case CCopasiParameter::Type::UINT:

        if (mType != CCopasiParameter::Type::INT &&
            mType != CCopasiParameter::Type::UINT)
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

      case CCopasiParameter::Type::BOOL:

        if (mType != CCopasiParameter::Type::BOOL)
          {
            deleteValue(mType, mpValue);
            deleteValidValues(mType, mpValidValues);
            mType = CCopasiParameter::Type::BOOL;
          }

        assignValue(rhs.mpValue);
        assignValidValues(rhs.mpValidValues);
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:

        if (mType != CCopasiParameter::Type::STRING &&
            mType != CCopasiParameter::Type::KEY &&
            mType != CCopasiParameter::Type::FILE &&
            mType != CCopasiParameter::Type::EXPRESSION)
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

      case CCopasiParameter::Type::CN:

        if (mType != CCopasiParameter::Type::CN)
          {
            deleteValue(mType, mpValue);
            deleteValidValues(mType, mpValidValues);
            mType = CCopasiParameter::Type::CN;
          }

        assignValue(rhs.mpValue);
        assignValidValues(rhs.mpValidValues);
        break;

      case CCopasiParameter::Type::GROUP:

        if (mType != CCopasiParameter::Type::GROUP)
          {
            deleteValue(mType, mpValue);
            mType = CCopasiParameter::Type::GROUP;
            createValue(rhs.mpValue);
          }

        *static_cast<CCopasiParameterGroup *>(this) = *static_cast<const CCopasiParameterGroup *>(&rhs);

        break;

      case CCopasiParameter::Type::INVALID:

        if (mType != CCopasiParameter::Type::INVALID)
          {
            deleteValue(mType, mpValue);
            mType = CCopasiParameter::Type::INVALID;
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
        if (lhs.mSize != rhs.mSize) return false;

        return memcmp(lhs.mpValue, rhs.mpValue, lhs.mSize) == 0;
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

void CCopasiParameter::createValue(const void * pValue)
{
  deleteValue(mType, mpValue);
  pdelete(mpValueReference);

  switch (mType)
    {
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        mpValue = new C_FLOAT64;
        mSize = sizeof(C_FLOAT64);
        mpValueReference = addObjectReference("Value", *static_cast< C_FLOAT64 * >(mpValue), CDataObject::ValueDbl);
        assignValue(pValue);
        break;

      case CCopasiParameter::Type::INT:
        mpValue = new C_INT32;
        mSize = sizeof(C_INT32);
        mpValueReference = addObjectReference("Value", *static_cast< C_INT32 * >(mpValue), CDataObject::ValueInt);
        assignValue(pValue);
        break;

      case CCopasiParameter::Type::UINT:
        mpValue = new unsigned C_INT32;
        mSize = sizeof(unsigned C_INT32);
        mpValueReference = addObjectReference("Value", *static_cast< unsigned C_INT32 * >(mpValue), CDataObject::ValueInt);
        assignValue(pValue);
        break;

      case CCopasiParameter::Type::BOOL:
        mpValue = new bool;
        mSize = sizeof(bool);
        mpValueReference = addObjectReference("Value", *static_cast< bool * >(mpValue), CDataObject::ValueBool);
        assignValue(pValue);
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:
        mpValue = new std::string;
        mSize = sizeof(std::string);
        mpValueReference = addObjectReference("Value", *static_cast< std::string * >(mpValue), CDataObject::ValueString);
        assignValue(pValue);
        break;

      case CCopasiParameter::Type::CN:
        mpValue = new CRegisteredCommonName;
        mSize = sizeof(CRegisteredCommonName);
        mpValueReference = addObjectReference("Value", *static_cast< CRegisteredCommonName * >(mpValue), CDataObject::ValueString);
        assignValue(pValue);
        break;

      case CCopasiParameter::Type::GROUP:
        mpValue = new CCopasiParameterGroup::elements;
        mSize = sizeof(CCopasiParameterGroup::elements);
        break;

      case CCopasiParameter::Type::INVALID:
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
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        mpValidValues = new std::vector< std::pair< C_FLOAT64, C_FLOAT64 > >;
        assignValidValues(pValidValues);
        break;

      case CCopasiParameter::Type::INT:
        mpValidValues = new std::vector< std::pair< C_INT32, C_INT32 > >;
        assignValidValues(pValidValues);
        break;

      case CCopasiParameter::Type::UINT:
        mpValidValues = new std::vector< std::pair< unsigned C_INT32, unsigned C_INT32 > >;
        assignValidValues(pValidValues);
        break;

      case CCopasiParameter::Type::BOOL:
        mpValidValues = new std::vector< std::pair< bool, bool > >;
        assignValidValues(pValidValues);
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:
        mpValidValues = new std::vector< std::pair< std::string, std::string > >;
        assignValidValues(pValidValues);
        break;

      case CCopasiParameter::Type::CN:
        mpValidValues = new std::vector< std::pair< CRegisteredCommonName, CRegisteredCommonName > >;
        assignValidValues(pValidValues);
        break;

      case CCopasiParameter::Type::GROUP:
      case CCopasiParameter::Type::INVALID:
        break;
    }
}

void CCopasiParameter::assignValue(const void * pValue)
{
  if (pValue == NULL) return;

  if (mpValue == NULL) return createValue(pValue);

  switch (mType)
    {
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:
        *static_cast< C_FLOAT64 * >(mpValue) = *static_cast< const C_FLOAT64 * >(pValue);
        break;

      case CCopasiParameter::Type::INT:
        *static_cast< C_INT32 * >(mpValue) = *static_cast< const C_INT32 * >(pValue);
        break;

      case CCopasiParameter::Type::UINT:
        *static_cast< unsigned C_INT32 * >(mpValue) = *static_cast< const unsigned C_INT32 * >(pValue);
        break;

      case CCopasiParameter::Type::BOOL:
        *static_cast< bool * >(mpValue) = *static_cast< const bool * >(pValue);
        break;

      case CCopasiParameter::Type::STRING:
      case CCopasiParameter::Type::KEY:
      case CCopasiParameter::Type::FILE:
      case CCopasiParameter::Type::EXPRESSION:
        *static_cast< std::string * >(mpValue) = *static_cast< const std::string * >(pValue);
        break;

      case CCopasiParameter::Type::CN:
        *static_cast< CRegisteredCommonName * >(mpValue) = *static_cast< const CRegisteredCommonName * >(pValue);
        break;

      case CCopasiParameter::Type::GROUP:
      case CCopasiParameter::Type::INVALID:
        break;
    }
}

void CCopasiParameter::assignValidValues(const void * pValidValues)
{
  if (pValidValues == NULL) return;

  if (mpValidValues == NULL) return createValidValues(pValidValues);

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
