/**
 *  CMethodParameter class.
 *  This class is used to describe method paramters. This class is intended
 *  to be used with integration or optimization methods.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#include <string>

#include "copasi.h"
#include "CMethodParameter.h"
#include "CReadConfig.h"
#include "CWriteConfig.h"
#include "CCopasiMessage.h"

const std::string CMethodParameter::TypeName[] =
  {
    "float",
    "integer",
    "unsigned integer",
    "bool"
  };

CMethodParameter::CMethodParameter(const std::string & name,
                                   const CCopasiContainer * pParent,
                                   const std::string & objectType):
    CCopasiContainer(name, pParent, objectType),
    mName(mObjectName),
    mValue(0),
    mType(CMethodParameter::DOUBLE)
{}

CMethodParameter::CMethodParameter(const CMethodParameter & src,
                                   const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mName(mObjectName),
    mValue(src.mValue),
    mType(src.mType)
{}

CMethodParameter::CMethodParameter(const std::string & name,
                                   const double & value,
                                   const CMethodParameter::Type & type,
                                   const CCopasiContainer * pParent,
                                   const std::string & objectType):
    CCopasiContainer(name, pParent, objectType),
    mName(mObjectName),
    mValue(value),
    mType(type)
{assert(isValidValue(value));}

CMethodParameter::~CMethodParameter() {}

void CMethodParameter::setName(const std::string & name) {mName = name;}

const std::string & CMethodParameter::getName() const {return mName;}

bool CMethodParameter::setValue(const double & value)
{
  if (isValidValue(value))
    {
      mValue = value;
      return true;
    }
  else
    return false;
}

bool CMethodParameter::setValue(const C_INT32 & value)
{
  if (mType == CMethodParameter::INT)
    {
      mValue = (C_INT32) value;
      return true;
    }
  else
    return false;
}

bool CMethodParameter::setValue(const unsigned C_INT32 & value)
{
  if (mType == CMethodParameter::UINT)
    {
      mValue = (unsigned C_INT32) value;
      return true;
    }
  else
    return false;
}

bool CMethodParameter::setValue(const bool & value)
{
  if (mType == CMethodParameter::BOOL)
    {
      mValue = (bool) value;
      return true;
    }
  else
    return false;
}

const double & CMethodParameter::getValue() const {return mValue;}

void CMethodParameter::setType(const CMethodParameter::Type & type)
{mType = type;}

const CMethodParameter::Type & CMethodParameter::getType() const
  {return mType;}

bool CMethodParameter::isValidValue(const C_FLOAT64 & value) const
  {
    switch (mType)
      {
      case CMethodParameter::DOUBLE:
        return true;
        break;

      case CMethodParameter::INT:
        if ((C_FLOAT64) LONG_MIN <= value &&
            (C_FLOAT64) LONG_MAX >= value)
          return true;
        break;

      case CMethodParameter::UINT:
        if (0.0 <= value && value <= (C_FLOAT64) ULONG_MAX)
          return true;
        break;

      case CMethodParameter::BOOL:
        if (0.0 == value || 1.0 == value)
          return true;
        break;

      default:
        break;
      }

    return false;
  }

void CMethodParameter::load(CReadConfig & configBuffer)
{
  configBuffer.getVariable("MethodParameterName", "string", &mName);
  configBuffer.getVariable("MethodParameterValue", "C_FLOAT64", &mValue);

  if (!isValidValue(mValue))
    CCopasiMessage(CCopasiMessage::ERROR, MCMethodParameter + 1,
                   mValue, mName.c_str(), TypeName[mType].c_str());

  return;
}

void CMethodParameter::save(CWriteConfig & configBuffer) const
  {
    configBuffer.setVariable("MethodParameterName", "string", &mName);
    configBuffer.setVariable("MethodParameterValue", "C_FLOAT64", &mValue);

    return;
  }
void CMethodParameter::cleanup() {}
