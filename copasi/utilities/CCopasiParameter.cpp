/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiParameter.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/31 22:01:12 $
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

const std::string CCopasiParameter::TypeName[] =
  {
    "float",
    "integer",
    "unsigned integer",
    "bool",
    "group",
    "string",
    ""
  };

const char* CCopasiParameter::XMLType[] =
  {
    "float",
    "integer",
    "unsignedInteger",
    "bool",
    "group",
    "string",
    NULL
  };

CCopasiParameter::CCopasiParameter():
    CCopasiContainer("NoName", NULL, "Parameter"),
    mType(INVALID)
{}

CCopasiParameter::CCopasiParameter(const CCopasiParameter & src,
                                   const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(CKeyFactory::add(src.getObjectType(), this)),
    mType(src.mType),
    mSize(0),
    mpValue(createValue(src.mpValue))
{}

CCopasiParameter::CCopasiParameter(const std::string & name,
                                   const CCopasiParameter::Type & type,
                                   const void * pValue,
                                   const CCopasiContainer * pParent,
                                   const std::string & objectType):
    CCopasiContainer(name, pParent, objectType,
                     CCopasiObject::Container |
                     (type == DOUBLE) ? CCopasiObject::ValueDbl :
                     (type == INT || type == UINT) ? CCopasiObject::ValueInt :
                     (type == BOOL) ? CCopasiObject::ValueBool : 0),
    mKey(CKeyFactory::add(objectType, this)),
    mType(type),
    mSize(0),
    mpValue(createValue(pValue))
{}

CCopasiParameter::~CCopasiParameter()
{
  CKeyFactory::remove(mKey);
  deleteValue();
}

std::string CCopasiParameter::getKey() const {return mKey;}

bool CCopasiParameter::setName(const std::string & name) {return setObjectName(name);}

const std::string & CCopasiParameter::getName() const {return getObjectName();}

const void * CCopasiParameter::getValue() const {return mpValue;}

void * CCopasiParameter::getValue() {return mpValue;}

const CCopasiParameter::Type & CCopasiParameter::getType() const
  {return mType;}

void * CCopasiParameter::createValue(const void * pValue)
{
  if (pValue) assert(isValidValue(pValue));

  switch (mType)
    {
    case CCopasiParameter::DOUBLE:
        mpValue = new C_FLOAT64;
      if (pValue) * (C_FLOAT64 *) mpValue = * (C_FLOAT64 *) pValue;
      mSize = sizeof(C_FLOAT64);
      break;

    case CCopasiParameter::INT:
      mpValue = new C_INT32;
      if (pValue) * (C_INT32 *) mpValue = * (C_INT32 *) pValue;
      mSize = sizeof(C_INT32);
      break;

    case CCopasiParameter::UINT:
      mpValue = new unsigned C_INT32;
      if (pValue)
        * (unsigned C_INT32 *) mpValue = * (unsigned C_INT32 *) pValue;
      mSize = sizeof(unsigned C_INT32);
      break;

    case CCopasiParameter::BOOL:
      mpValue = new bool;
      if (pValue) * (bool *) mpValue = * (bool *) pValue;
      mSize = sizeof(bool);
      break;

    case CCopasiParameter::STRING:
      if (pValue)
        mpValue = new std::string(* (std::string *) pValue);
      else mpValue = new std::string;
      mSize = sizeof(std::string);
      break;

    default:
      mpValue = NULL;
      mSize = 0;
      break;
    }

  return mpValue;
}

void CCopasiParameter::deleteValue()
{
  if (!mpValue) return;

  switch (mType)
    {
    case CCopasiParameter::DOUBLE:
      delete (C_FLOAT64 *) mpValue;
      break;

    case CCopasiParameter::INT:
      delete (C_INT32 *) mpValue;
      break;

    case CCopasiParameter::UINT:
      delete (unsigned C_INT32 *) mpValue;
      break;

    case CCopasiParameter::BOOL:
      delete (bool *) mpValue;
      break;

    case CCopasiParameter::STRING:
      delete (std::string *) mpValue;
      break;

    default:
      fatalError();
      break;
    }

  mpValue = NULL;
  return;
}
