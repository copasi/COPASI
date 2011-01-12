// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiParameter.cpp,v $
//   $Revision: 1.35.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/12 19:13:20 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CCopasiParameter class.
 *  This class is used to describe method paramters. This class is intended
 *  to be used with integration or optimization methods.
 *
 *  Created for Copasi by Stefan Hoops 2002
 */

#include <string>

#include "copasi.h"
#include "CCopasiParameter.h"
#include "CCopasiParameterGroup.h"
#include "CCopasiMessage.h"
#include "report/CKeyFactory.h"
#include "report/CCopasiObjectReference.h"
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
    mValue()
{mValue.pVOID = NULL;}

CCopasiParameter::CCopasiParameter(const CCopasiParameter & src,
                                   const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(CCopasiRootContainer::getKeyFactory()->add(src.getObjectType(), this)),
    mType(src.mType),
    mSize(0),
    mValue(createValue(src.mValue))
{}

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
    mValue()
{
  CCopasiParameter::Value value;
  value.pVOID = const_cast<void *>(pValue);
  mValue = createValue(value);
}

CCopasiParameter::~CCopasiParameter()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
  deleteValue();
}

CCopasiParameter & CCopasiParameter::operator = (const CCopasiParameter & rhs)
{
  if (getObjectName() != rhs.getObjectName())
    setObjectName(rhs.getObjectName());

  switch (rhs.mType)
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:

        if (mType != DOUBLE &&
            mType != UDOUBLE)
          {
            deleteValue();
            mType = rhs.mType;
            createValue(rhs.mValue);
          }
        else
          {
            mType = rhs.mType;
            *mValue.pDOUBLE = *rhs.mValue.pDOUBLE;
          }

        break;

      case CCopasiParameter::INT:
      case CCopasiParameter::UINT:

        if (mType != INT &&
            mType != UINT)
          {
            deleteValue();
            mType = rhs.mType;
            createValue(rhs.mValue);
          }
        else
          {
            mType = rhs.mType;
            *mValue.pINT = *rhs.mValue.pINT;
          }

        break;

      case CCopasiParameter::BOOL:

        if (mType != BOOL)
          {
            deleteValue();
            mType = BOOL;
            createValue(rhs.mValue);
          }
        else
          {
            *mValue.pBOOL = *rhs.mValue.pBOOL;
          }

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
            deleteValue();
            mType = rhs.mType;
            createValue(rhs.mValue);
          }
        else
          {
            mType = rhs.mType;
            *mValue.pSTRING = *rhs.mValue.pSTRING;
          }

        break;

      case CCopasiParameter::CN:

        if (mType != CN)
          {
            deleteValue();
            mType = CN;
            createValue(rhs.mValue);
          }
        else
          {
            *mValue.pCN = *rhs.mValue.pCN;
          }

        break;

      case CCopasiParameter::GROUP:

        if (mType != GROUP)
          {
            deleteValue();
            mType = GROUP;
            createValue(rhs.mValue);
          }

        *static_cast<CCopasiParameterGroup *>(this) =
          *static_cast<const CCopasiParameterGroup *>(&rhs);

        break;

      case CCopasiParameter::INVALID:

        if (mType != INVALID)
          {
            deleteValue();
            mType = INVALID;
            createValue(rhs.mValue);
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

const CCopasiParameter::Value & CCopasiParameter::getValue() const {return mValue;}

CCopasiParameter::Value & CCopasiParameter::getValue() {return mValue;}

const CCopasiParameter::Type & CCopasiParameter::getType() const
{return mType;}

bool CCopasiParameter::isValidValue(const C_FLOAT64 & value) const
{
  if ((mType != CCopasiParameter::DOUBLE &&
       mType != CCopasiParameter::UDOUBLE) ||
      (mType == CCopasiParameter::UDOUBLE &&
       value < 0.0)) return false;

  return true;
}

bool CCopasiParameter::isValidValue(const C_INT32 & C_UNUSED(value)) const
{
  if (mType != CCopasiParameter::INT) return false;

  return true;
}

bool CCopasiParameter::isValidValue(const unsigned C_INT32 & C_UNUSED(value)) const
{
  if (mType != CCopasiParameter::UINT) return false;

  return true;
}

bool CCopasiParameter::isValidValue(const bool & C_UNUSED(value)) const
{
  if (mType != CCopasiParameter::BOOL) return false;

  return true;
}

bool CCopasiParameter::isValidValue(const std::string & value) const
{
  if (mType == CCopasiParameter::KEY)
    return CKeyFactory::isValidKey(value);

  if (mType != CCopasiParameter::STRING &&
      mType != CCopasiParameter::FILE &&
      mType != CCopasiParameter::EXPRESSION) return false;

  return true;
}

bool CCopasiParameter::isValidValue(const CCopasiObjectName & C_UNUSED(value)) const
{
  if (mType != CCopasiParameter::CN) return false;

  return true;
}

bool CCopasiParameter::isValidValue(const CCopasiParameterGroup::parameterGroup & C_UNUSED(value)) const
{
  if (mType != CCopasiParameter::GROUP) return false;

  return true;
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
        os << * o.mValue.pDOUBLE;
        break;

      case CCopasiParameter::INT:
        os << * o.mValue.pINT;
        break;

      case CCopasiParameter::UINT:
        os << * o.mValue.pUINT;
        break;

      case CCopasiParameter::BOOL:
        os << * o.mValue.pBOOL;
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
        os << * o.mValue.pSTRING;
        break;

      case CCopasiParameter::CN:
        os << * o.mValue.pCN;
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
        return *lhs.mValue.pDOUBLE == *rhs.mValue.pDOUBLE;
        break;

      case CCopasiParameter::INT:
        return *lhs.mValue.pINT == *rhs.mValue.pINT;
        break;

      case CCopasiParameter::UINT:
        return *lhs.mValue.pUINT == *rhs.mValue.pUINT;
        break;

      case CCopasiParameter::BOOL:
        return *lhs.mValue.pBOOL == *rhs.mValue.pBOOL;
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
        return *lhs.mValue.pSTRING == *rhs.mValue.pSTRING;
        break;

      case CCopasiParameter::CN:
        return *lhs.mValue.pCN == *rhs.mValue.pCN;
        break;

      case CCopasiParameter::GROUP:
        return *static_cast<const CCopasiParameterGroup *>(&lhs) ==
               *static_cast<const CCopasiParameterGroup *>(&rhs);
        break;

      case CCopasiParameter::INVALID:
      default:
        return !memcmp(lhs.mValue.pVOID, rhs.mValue.pVOID, lhs.mSize);
        break;
    }
}

void * CCopasiParameter::getValuePointer() const
{return const_cast<void *>(mValue.pVOID);}

CCopasiParameter::Value CCopasiParameter::createValue(const Value & value)
{
  switch (mType)
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        mValue.pDOUBLE = new C_FLOAT64;

        if (value.pDOUBLE) * mValue.pDOUBLE = * value.pDOUBLE;

        mSize = sizeof(C_FLOAT64);
        addObjectReference("Value", * mValue.pDOUBLE, CCopasiObject::ValueDbl);
        break;

      case CCopasiParameter::INT:
        mValue.pINT = new C_INT32;

        if (value.pINT) * mValue.pINT = * value.pINT;

        mSize = sizeof(C_INT32);
        addObjectReference("Value", * mValue.pINT, CCopasiObject::ValueInt);
        break;

      case CCopasiParameter::UINT:
        mValue.pUINT = new unsigned C_INT32;

        if (value.pUINT) * mValue.pUINT = * value.pUINT;

        mSize = sizeof(unsigned C_INT32);
        addObjectReference("Value", * mValue.pUINT, CCopasiObject::ValueInt);
        break;

      case CCopasiParameter::BOOL:
        mValue.pBOOL = new bool;

        if (value.pBOOL) * mValue.pBOOL = * value.pBOOL;

        mSize = sizeof(bool);
        addObjectReference("Value", * mValue.pBOOL, CCopasiObject::ValueBool);
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:

        if (value.pSTRING)
          mValue.pSTRING = new std::string(* value.pSTRING);
        else
          mValue.pSTRING = new std::string;

        mSize = sizeof(std::string);
        addObjectReference("Value", * mValue.pSTRING, CCopasiObject::ValueString);
        break;

      case CCopasiParameter::CN:

        if (value.pCN)
          mValue.pCN = new CRegisteredObjectName(* value.pCN);
        else
          mValue.pCN = new CRegisteredObjectName;

        mSize = sizeof(CRegisteredObjectName);
        addObjectReference("Value", * mValue.pCN, CCopasiObject::ValueString);
        break;

      case CCopasiParameter::GROUP:
        mValue.pGROUP = new std::vector< CCopasiParameter * >;
        mSize = sizeof(std::vector< CCopasiParameter * >);
        break;

      case CCopasiParameter::INVALID:
        mValue.pVOID = NULL;
        mSize = 0;
        break;
    }

  return mValue;
}

void CCopasiParameter::deleteValue()
{
  if (mValue.pVOID == NULL) return;

  switch (mType)
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        delete mValue.pDOUBLE;
        break;

      case CCopasiParameter::INT:
        delete mValue.pINT;
        break;

      case CCopasiParameter::UINT:
        delete mValue.pUINT;
        break;

      case CCopasiParameter::BOOL:
        delete mValue.pBOOL;
        break;

      case CCopasiParameter::STRING:
      case CCopasiParameter::KEY:
      case CCopasiParameter::FILE:
      case CCopasiParameter::EXPRESSION:
        delete mValue.pSTRING;
        break;

      case CCopasiParameter::CN:
        delete mValue.pCN;
        break;

      case CCopasiParameter::GROUP:
        delete mValue.pGROUP;
        break;

      case CCopasiParameter::INVALID:
        break;

      default:
        fatalError();
        break;
    }

  mValue.pVOID = NULL;
  return;
}

std::string CCopasiParameter::getObjectDisplayName(bool regular, bool richtext) const
{
  // if one of the ancestors is a reaction and the parameter is not a group
  // it is (hopefully) a kinetic parameter

  CCopasiObject* tmp = this->getObjectAncestor("Reaction");

  if (tmp && getType() != GROUP)
    {
      return tmp->getObjectDisplayName() + "." + getObjectName();
    }

  return CCopasiObject::getObjectDisplayName(regular, richtext);
}
