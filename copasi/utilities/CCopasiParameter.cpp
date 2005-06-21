/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiParameter.cpp,v $
   $Revision: 1.20 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/21 13:15:28 $
   End CVS Header */

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
    NULL
  };

CCopasiParameter::CCopasiParameter():
    CCopasiContainer("NoName", NULL, "Parameter"),
    mKey(GlobalKeys.add("Parameter", this)),
    mType(INVALID),
    mSize(0),
    mValue()
{mValue.pVOID = NULL;}

CCopasiParameter::CCopasiParameter(const CCopasiParameter & src,
                                   const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add(src.getObjectType(), this)),
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
                       ((type == STRING || type == CN || type == KEY) ? CCopasiObject::ValueString :
                        (type == BOOL) ? CCopasiObject::ValueBool : 0)))),
    mKey(GlobalKeys.add(objectType, this)),
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
  GlobalKeys.remove(mKey);
  deleteValue();
}

const std::string & CCopasiParameter::getKey() const {return mKey;}

bool CCopasiParameter::setValue(const std::vector< CCopasiParameter * > & value)
{
  fatalError();
  return false;
}

const void * CCopasiParameter::getValue() const {return mValue.pVOID;}

void * CCopasiParameter::getValue() {return mValue.pVOID;}

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

    if (mType != CCopasiParameter::STRING) return false;
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

void * CCopasiParameter::getReference() const
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
    case CCopasiParameter::INVALID:
      mValue.pVOID = NULL;
      mSize = 0;
      break;
    }

  return mValue;
}

void CCopasiParameter::deleteValue()
{
  if (!mValue.pVOID) return;

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
      delete mValue.pSTRING;
      break;

    case CCopasiParameter::CN:
      delete mValue.pCN;
      break;

    default:
      fatalError();
      break;
    }

  mValue.pVOID = NULL;
  return;
}
