// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunctionParameter.cpp,v $
//   $Revision: 1.33.22.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/11/10 20:22:41 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CFunctionParameter
 *
 * Created for COPASI by Stefan Hoops
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
  {"substrate", "product", "modifier", "constant", "volume", "time", "variable", ""};

//static
const std::string CFunctionParameter::RoleNameDisplay[] =
  {"Substrate", "Product", "Modifier", "Parameter", "Volume", "Time", "Variable", ""};

//static
CFunctionParameter::Role CFunctionParameter::xmlRole2Enum(const std::string & xmlrole)
{
  C_INT32 i;
  for (i = 0; (RoleNameXML[i] != "") && (RoleNameXML[i] != xmlrole); ++i);

  if (RoleNameXML[i] == "")
    return VARIABLE; //default for invalid XML string
  else
    return (Role)i;
}

CFunctionParameter::CFunctionParameter(const std::string & name,
                                       const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Variable"),
    mKey(GlobalKeys.add("FunctionParameter", this)),
    mType((CFunctionParameter::DataType) - 1),
    mUsage(VARIABLE),
    mIsUsed(true)
{CONSTRUCTOR_TRACE;}

CFunctionParameter::CFunctionParameter(const CFunctionParameter & src,
                                       const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("FunctionParameter", this)),
    mType(src.mType),
    mUsage(src.mUsage),
    mIsUsed(src.mIsUsed)
{CONSTRUCTOR_TRACE;}

CFunctionParameter::CFunctionParameter(const std::string &name,
                                       const enum CFunctionParameter::DataType &type,
                                       Role usage,
                                       const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Variable"),
    mKey(GlobalKeys.add("FunctionParameter", this)),
    mType(type),
    mUsage(usage),
    mIsUsed(true)
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

void CFunctionParameter::setIsUsed(const bool & isUsed)
{mIsUsed = isUsed;}

/**
 * Retrieve whether the parameter is used within a function
 * @return const bool & isUsed
 */
const bool & CFunctionParameter::isUsed() const
  {return mIsUsed;}

std::ostream& operator<<(std::ostream &os, const CFunctionParameter & d)
{
  //os << "CFunctionParameter: "
  os << d.getObjectName();
  if (d.mType != 1) os << " mType " << d.mType;
  os << " [" << CFunctionParameter::RoleNameDisplay[d.mUsage] << "]";

  return os;
}
