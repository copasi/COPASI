/**
 *  CParameter class.
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
#include "report/CKeyFactory.h"

const std::string CParameter::TypeName[] =
  {
    "float",
    "integer",
    "unsigned integer",
    "bool"
  };

CParameter::CParameter(const std::string & name,
                       const CCopasiContainer * pParent,
                       const std::string & objectType):
    CCopasiContainer(name, pParent, objectType, CCopasiObject::Container | CCopasiObject::ValueDbl),
    mKey(CKeyFactory::add("Constant", this)),
    mValue(0),
    mType(CParameter::DOUBLE)
{}

CParameter::CParameter(const CParameter & src,
                       const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(CKeyFactory::add("Constant", this)),
    mValue(src.mValue),
    mType(src.mType)
{}

CParameter::CParameter(const std::string & name,
                       const double & value,
                       const CParameter::Type & type,
                       const CCopasiContainer * pParent,
                       const std::string & objectType):
    CCopasiContainer(name, pParent, objectType, CCopasiObject::Container | CCopasiObject::ValueDbl),
    mKey(CKeyFactory::add("Constant", this)),
    mValue(value),
    mType(type)
{assert(isValidValue(value));}

CParameter::~CParameter()
{
  CKeyFactory::remove(mKey);
}

std::string CParameter::getKey() const {return mKey;}

bool CParameter::setName(const std::string & name) {return setObjectName(name);}

const std::string & CParameter::getName() const {return getObjectName();}

bool CParameter::setValue(const double & value)
{
  if (isValidValue(value))
    {
      mValue = value;
      return true;
    }
  else
    return false;
}

bool CParameter::setValue(const C_INT32 & value)
{
  if (mType == CParameter::INT)
    {
      mValue = (C_INT32) value;
      return true;
    }
  else
    return false;
}

bool CParameter::setValue(const unsigned C_INT32 & value)
{
  if (mType == CParameter::UINT)
    {
      mValue = (unsigned C_INT32) value;
      return true;
    }
  else
    return false;
}

bool CParameter::setValue(const bool & value)
{
  if (mType == CParameter::BOOL)
    {
      mValue = (bool) value;
      return true;
    }
  else
    return false;
}

const double & CParameter::getValue() const {return mValue;}

const void * CParameter::getObjectValueAddress() const {return &mValue;}

void CParameter::setType(const CParameter::Type & type)
{mType = type;}

const CParameter::Type & CParameter::getType() const
  {return mType;}

bool CParameter::isValidValue(const C_FLOAT64 & value) const
  {
    switch (mType)
      {
      case CParameter::DOUBLE:
        return true;
        break;

      case CParameter::INT:
        if ((C_FLOAT64) LONG_MIN <= value &&
            (C_FLOAT64) LONG_MAX >= value)
          return true;
        break;

      case CParameter::UINT:
        if (0.0 <= value && value <= (C_FLOAT64) ULONG_MAX)
          return true;
        break;

      case CParameter::BOOL:
        if (0.0 == value || 1.0 == value)
          return true;
        break;

      default:
        break;
      }

    return false;
  }

void CParameter::load(CReadConfig & configBuffer)
{
  std::string tmp;
  configBuffer.getVariable("MethodParameterName", "string", &tmp);
  setObjectName(tmp);

  configBuffer.getVariable("MethodParameterValue", "C_FLOAT64", &mValue);

  if (!isValidValue(mValue))
    CCopasiMessage(CCopasiMessage::ERROR, MCParameter + 1,
                   mValue, getObjectName().c_str(), TypeName[mType].c_str());

  return;
}

void CParameter::save(CWriteConfig & configBuffer) const
  {
    std::string tmp = getObjectName();
    configBuffer.setVariable("MethodParameterName", "string", &tmp);
    configBuffer.setVariable("MethodParameterValue", "C_FLOAT64", &mValue);

    return;
  }
void CParameter::cleanup() {}
