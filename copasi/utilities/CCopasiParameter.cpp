/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiParameter.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/21 20:32:46 $
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
#include "CCopasiMessage.h"
#include "report/CKeyFactory.h"

const std::string CCopasiParameter::TypeName[] =
  {
    "float",
    "integer",
    "unsigned integer",
    "bool",
    "group"
  };

CCopasiParameter::CCopasiParameter(const std::string & name,
                                   const CCopasiContainer * pParent,
                                   const std::string & objectType):
    CCopasiContainer(name, pParent, objectType, CCopasiObject::Container | CCopasiObject::ValueDbl),
    mKey(CKeyFactory::add("Constant", this)),
    mType(CCopasiParameter::DOUBLE),
    mpValue(createValue())
{}

CCopasiParameter::CCopasiParameter(const CCopasiParameter & src,
                                   const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(CKeyFactory::add("Constant", this)),
    mType(src.mType),
    mpValue(createValue(src.mpValue))
{}

CCopasiParameter::CCopasiParameter(const std::string & name,
                                   const void * pValue,
                                   const CCopasiParameter::Type & type,
                                   const CCopasiContainer * pParent,
                                   const std::string & objectType):
    CCopasiContainer(name, pParent, objectType, CCopasiObject::Container | CCopasiObject::ValueDbl),
    mKey(CKeyFactory::add("Constant", this)),
    mType(type),
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

bool CCopasiParameter::setValue(const double & value)
{
  if (isValidValue(&value))
    {
      * (C_FLOAT64 *) mpValue = value;
      return true;
    }
  else
    return false;
}

bool CCopasiParameter::setValue(const C_INT32 & value)
{
  if (mType == CCopasiParameter::INT)
    {
      * (C_INT32 *) mpValue = value;
      return true;
    }
  else
    return false;
}

bool CCopasiParameter::setValue(const unsigned C_INT32 & value)
{
  if (mType == CCopasiParameter::UINT)
    {
      * (unsigned C_INT32 *) mpValue = value;
      return true;
    }
  else
    return false;
}

bool CCopasiParameter::setValue(const bool & value)
{
  if (mType == CCopasiParameter::BOOL)
    {
      * (bool *) mpValue = value;
      return true;
    }
  else
    return false;
}

const void * CCopasiParameter::getValue() const {return mpValue;}

void CCopasiParameter::setType(const CCopasiParameter::Type & type)
{mType = type;}

const CCopasiParameter::Type & CCopasiParameter::getType() const
  {return mType;}

bool CCopasiParameter::isValidValue(const void *pValue) const
  {
    switch (mType)
      {
      case CCopasiParameter::DOUBLE:
        return true;
        break;

      case CCopasiParameter::INT:
        if (LONG_MIN <= * (C_INT32 *) pValue &&
            LONG_MAX >= * (C_INT32 *) pValue)
          return true;
        break;

      case CCopasiParameter::UINT:
        if (* (unsigned C_INT32 *) pValue <= ULONG_MAX)
          return true;
        break;

      case CCopasiParameter::BOOL:
        if (true == * (bool *) pValue ||
            false == * (bool *) pValue)
          return true;
        break;

      case CCopasiParameter::GROUP:
        if (((CCopasiContainer *)pValue)->getObjectType() == "ParameterGroup")
          return true;
        break;

      default:
        break;
      }

    return false;
  }

void CCopasiParameter::cleanup() {}

void * CCopasiParameter::createValue(const void * pValue)
{
  if (pValue) assert(isValidValue(pValue));

  switch (mType)
    {
    case CCopasiParameter::DOUBLE:
      mpValue = new C_FLOAT64;
      if (pValue) * (C_FLOAT64 *) mpValue = * (C_FLOAT64 *) pValue;
      break;

    case CCopasiParameter::INT:
      mpValue = new C_INT32;
      if (pValue) * (C_INT32 *) mpValue = * (C_INT32 *) pValue;
      break;

    case CCopasiParameter::UINT:
      mpValue = new unsigned C_INT32;
      if (pValue)
        * (unsigned C_INT32 *) mpValue = * (unsigned C_INT32 *) pValue;
      break;

    case CCopasiParameter::BOOL:
      mpValue = new bool;
      if (pValue) * (bool *) mpValue = * (bool *) pValue;
      break;

    case CCopasiParameter::GROUP:
      //      if (pValue) mpValue = new CCopasiParameterGroup(*pValue);
      //      else mpValue = new CCopasiParameterGroup;
      break;

    default:
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

    case CCopasiParameter::GROUP:
      //      delete (CCopasiParameterGroup *) mpValue;
      break;

    default:
      break;
    }

  return;
}
