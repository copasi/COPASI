/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunctionParameter.cpp,v $
   $Revision: 1.30 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/12/07 10:55:59 $
   End CVS Header */

/**
 * CFunctionParameter
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#include "copasi.h"
#include "CFunctionParameter.h"
#include "report/CKeyFactory.h"

//static
const std::string CFunctionParameter::DataTypeName[] =
  {"Integer", "Double", "Vector of Integer", "Vector of Double", ""};

//static
const std::string CFunctionParameter::RoleNameXML[] =
  {"substrate", "product", "modifier", "constant", "volume", "variable", ""};

//static
const std::string CFunctionParameter::RoleNameDisplay[] =
  {"Substrate", "Product", "Modifier", "Parameter", "Volume", "Variable", ""};

//static
CFunctionParameter::Role CFunctionParameter::xmlRole2Enum(const std::string & xmlrole)
{
  C_INT32 i;
  for (i = 0; (RoleNameXML[i] != "") && (RoleNameXML[i] != xmlrole); ++i);

  if (RoleNameXML[i] == "")
    return VARIABLE; //default for invalid xml string
  else
    return (Role)i;
}

CFunctionParameter::CFunctionParameter(const std::string & name,
                                       const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Variable"),
    mKey(GlobalKeys.add("FunctionParameter", this)),
    mType((CFunctionParameter::DataType) - 1),
    mUsage(VARIABLE)
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
                                       Role usage,
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

const std::string & CFunctionParameter::getKey() const {return mKey;}

void CFunctionParameter::setUsage(Role usage) {mUsage = usage;}

CFunctionParameter::Role CFunctionParameter::getUsage() const {return mUsage;}

void CFunctionParameter::setType(const CFunctionParameter::DataType & type)
{mType = type;}

const CFunctionParameter::DataType &

CFunctionParameter::getType() const
  {
    return mType;
  }
