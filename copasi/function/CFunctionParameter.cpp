/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunctionParameter.cpp,v $
   $Revision: 1.24 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/19 09:32:27 $
   End CVS Header */

/**
 * CFunctionParameter
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CFunctionParameter.h"
#include "report/CKeyFactory.h"

const std::string CFunctionParameter::DataTypeName[] =
  {"Integer", "Double", "Vector of Integer", "Vector of Double", ""};

const char * CFunctionParameter::RoleName[] =
  {"substrate", "product", "modifier", "constant", "other", NULL};

CFunctionParameter::CFunctionParameter(const std::string & name,
                                       const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Variable"),
    mKey(GlobalKeys.add("FunctionParameter", this)),
    mType((CFunctionParameter::DataType) - 1),
    mUsage("unknown")
{CONSTRUCTOR_TRACE;}

CFunctionParameter::CFunctionParameter(const CFunctionParameter & src,
                                       const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("FunctionParameter", this)),
    mType(src.mType),
    mUsage(src.mUsage)
{CONSTRUCTOR_TRACE;}

CFunctionParameter::CFunctionParameter(const std::string &name,
                                       const enum CFunctionParameter::DataType &type,
                                       const std::string &usage,
                                       const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Variable"),
    mKey(GlobalKeys.add("FunctionParameter", this)),
    mType(type),
    mUsage(usage)
{CONSTRUCTOR_TRACE;}

CFunctionParameter::~CFunctionParameter()
{
  GlobalKeys.remove(mKey);
  DESTRUCTOR_TRACE;
}

void CFunctionParameter::cleanup() {}

void CFunctionParameter::load(CReadConfig & configbuffer,
                              CReadConfig::Mode mode)
{
  std::string tmp;
  configbuffer.getVariable("FunctionParameter", "string", &tmp, mode);
  setObjectName(tmp);
  configbuffer.getVariable("DataType", "C_INT32", &mType);
  configbuffer.getVariable("Usage", "string", &mUsage);
}

void CFunctionParameter::save(CWriteConfig & configbuffer)
{
  std::string tmp = getObjectName();
  configbuffer.setVariable("FunctionParameter", "string", &tmp);
  configbuffer.setVariable("DataType", "C_INT32", &mType);
  configbuffer.setVariable("Usage", "string", &mUsage);
}

bool CFunctionParameter::setName(const std::string & name) {return setObjectName(name);}

const std::string & CFunctionParameter::getKey() const {return mKey;}

//const std::string & CFunctionParameter::getName() const {return getObjectName();}

void CFunctionParameter::setUsage(const std::string & usage) {mUsage = usage;}

const std::string & CFunctionParameter::getUsage() const {return mUsage;}

void CFunctionParameter::setType(const CFunctionParameter::DataType & type)
{mType = type;}

const CFunctionParameter::DataType &

CFunctionParameter::getType() const
  {
    return mType;
  }
