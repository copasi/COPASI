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

CMethodParameter::CMethodParameter(const std::string & name,
                                   const double & value) :
    mName(name),
    mValue(value)
{}

CMethodParameter::CMethodParameter(const CMethodParameter & src) :
    mName(src.mName),
    mValue(src.mValue)
{}

CMethodParameter::~CMethodParameter() {}

void CMethodParameter::setName(const std::string & name) {mName = name;}

const std::string & CMethodParameter::getName() const {return mName;}

void CMethodParameter::setValue(const double & value) {mValue = value;}

const double & CMethodParameter::getValue() const {return mValue;}

void CMethodParameter::load(CReadConfig & configBuffer)
{
  configBuffer.getVariable("MethodParameterName", "string", &mName);
  configBuffer.getVariable("MethodParameterValue", "C_FLOAT64", &mValue);

  return;
}

void CMethodParameter::save(CWriteConfig & configBuffer) const
{
  configBuffer.setVariable("MethodParameterName", "string", &mName);
  configBuffer.setVariable("MethodParameterValue", "C_FLOAT64", &mValue);

  return;
}
void CMethodParameter::cleanup() {}
