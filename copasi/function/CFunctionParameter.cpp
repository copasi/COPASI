// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CFunctionParameter
 *
 * Created for COPASI by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#include "copasi/copasi.h"

#include "CFunctionParameter.h"

#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/undo/CData.h"

// static
const CEnumAnnotation< std::string, CFunctionParameter::Role > CFunctionParameter::RoleNameXML(
{
  "substrate",
  "product",
  "modifier",
  "constant",
  "volume",
  "time",
  "variable"
});

// static
const CEnumAnnotation< std::string, CFunctionParameter::Role > CFunctionParameter::RoleNameDisplay(
{
  "Substrate",
  "Product",
  "Modifier",
  "Parameter",
  "Volume",
  "Time",
  "Variable"
});

// static
const CEnumAnnotation< std::string, CFunctionParameter::DataType > CFunctionParameter::DataTypeName(
{
  "Integer",
  "Double",
  "Vector of Integer",
  "Vector of Double"
});

// static
CFunctionParameter * CFunctionParameter::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CFunctionParameter(data.getProperty(CData::OBJECT_NAME).toString(),
                                NO_PARENT);
}

// virtual
CData CFunctionParameter::toData() const
{
  CData Data = CDataContainer::toData();

  Data.addProperty(CData::PARAMETER_TYPE, CFunctionParameter::DataTypeName[mType]);
  Data.addProperty(CData::PARAMETER_ROLE, CFunctionParameter::RoleNameXML[mUsage]);
  Data.addProperty(CData::PARAMETER_USED, mIsUsed);

  return Data;
}

// virtual
bool CFunctionParameter::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = CDataContainer::applyData(data, changes);

  if (data.isSetProperty(CData::PARAMETER_TYPE))
    {
      mType = DataTypeName.toEnum(data.getProperty(CData::PARAMETER_TYPE).toString());
    }

  if (data.isSetProperty(CData::PARAMETER_ROLE))
    {
      mUsage = RoleNameXML.toEnum(data.getProperty(CData::PARAMETER_ROLE).toString());
    }

  if (data.isSetProperty(CData::PARAMETER_USED))
    {
      mIsUsed = data.getProperty(CData::PARAMETER_USED).toBool();
    }

  return success;
}

CFunctionParameter::CFunctionParameter(const std::string & name,
                                       const CDataContainer * pParent):
  CDataContainer(name, pParent, "Variable"),
  mKey(CRootContainer::getKeyFactory()->add("FunctionParameter", this)),
  mType((CFunctionParameter::DataType) - 1),
  mUsage(CFunctionParameter::Role::VARIABLE),
  mIsUsed(true)
{}

CFunctionParameter::CFunctionParameter(const CFunctionParameter & src,
                                       const CDataContainer * pParent):
  CDataContainer(src, pParent),
  mKey(CRootContainer::getKeyFactory()->add("FunctionParameter", this)),
  mType(src.mType),
  mUsage(src.mUsage),
  mIsUsed(src.mIsUsed)
{}

CFunctionParameter::CFunctionParameter(const std::string &name,
                                       const CFunctionParameter::DataType &type,
                                       Role usage,
                                       const CDataContainer * pParent) :
  CDataContainer(name, pParent, "Variable"),
  mKey(CRootContainer::getKeyFactory()->add("FunctionParameter", this)),
  mType(type),
  mUsage(usage),
  mIsUsed(true)
{}

CFunctionParameter::~CFunctionParameter()
{
  CRootContainer::getKeyFactory()->remove(mKey);
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

const std::string & CFunctionParameter::getKey() const
{
  return mKey;
}

void CFunctionParameter::setUsage(Role usage)
{
  mUsage = usage;
}

CFunctionParameter::Role CFunctionParameter::getUsage() const
{
  return mUsage;
}

void CFunctionParameter::setType(const CFunctionParameter::DataType & type)
{
  mType = type;
}

const CFunctionParameter::DataType &

CFunctionParameter::getType() const
{
  return mType;
}

void CFunctionParameter::setIsUsed(const bool & isUsed)
{
  mIsUsed = isUsed;
}

const bool & CFunctionParameter::isUsed() const
{
  return mIsUsed;
}

std::ostream& operator<<(std::ostream &os, const CFunctionParameter & d)
{
  //os << "CFunctionParameter: "
  os << d.getObjectName();

  os << " mType " << static_cast< size_t >(d.mType);

  os << " [" << CFunctionParameter::RoleNameDisplay[d.mUsage] << "]";

  return os;
}
