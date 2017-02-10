// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi.h"

#include "CData.h"

// static
const std::string CData::PropertyName[] =
{
  "Expression",
  "Initial Expression",
  "Initial Volume",
  "Simulation Type",
  "Spatial Dimensions",
  "Add Noise",
  "Noise Expression",
  "Object Name",
  "Object Parent CN",
  "Object Type",
  "Object Flag",
  "Object Index",
  "Evaluation Tree Type",
  "Task Type",
  "Plot Type",
  "Plot Item Type",
  "Parameter Type",
  ""
};

CData::CData():
  std::map< std::string, CDataValue >()
{}

CData::CData(const CData & src):
  std::map< std::string, CDataValue >(src)
{}

CData::~CData()
{}

CData & CData::operator = (const CData & rhs)
{
  if (this != &rhs)
    {
      std::map< std::string, CDataValue >::operator =(rhs);
    }

  return *this;
}

const CDataValue & CData::getProperty(const std::string & name) const
{
  static const CDataValue NotFound(CDataValue::INVALID);

  std::map< std::string, CDataValue >::const_iterator found = find(name);

  if (found != end())
    {
      return found->second;
    }

  return NotFound;
}

const CDataValue & CData::getProperty(const Property & property) const
{
  return getProperty(PropertyName[property]);
}

CDataValue & CData::getProperty(const std::string & name)
{
  static CDataValue NotFound(CDataValue::INVALID);

  std::map< std::string, CDataValue >::iterator found = find(name);

  if (found != end())
    {
      return found->second;
    }

  return NotFound;
}

CDataValue & CData::getProperty(const Property & property)
{
  return getProperty(PropertyName[property]);
}

bool CData::setProperty(const std::string & name, const CDataValue & value)
{
  std::map< std::string, CDataValue >::iterator found = find(name);

  if (found != end())
    {
      found->second = value;
      return true;
    }

  return false;
}

bool CData::setProperty(const Property & property, const CDataValue & value)
{
  return setProperty(PropertyName[property], value);
}

bool CData::addProperty(const std::string & name, const CDataValue & value)
{
  std::map< std::string, CDataValue >::const_iterator found = find(name);

  if (found != end())
    {
      return false;
    }

  insert(std::make_pair(name, value));
  return true;
}

bool CData::addProperty(const Property & property, const CDataValue & value)
{
  return addProperty(PropertyName[property], value);
}

bool CData::removeProperty(const std::string & name)
{
  std::map< std::string, CDataValue >::iterator found = find(name);

  if (found != end())
    {
      erase(found);
      return true;
    }

  return false;
}

bool CData::removeProperty(const Property & property)
{
  return removeProperty(PropertyName[property]);
}

bool CData::empty() const
{
  return std::map< std::string, CDataValue >::empty();
}
