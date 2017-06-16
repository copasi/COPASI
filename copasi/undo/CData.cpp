// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi.h"

#include "CData.h"

#include "utilities/utility.h"

// static
const CEnumAnnotation< std::string, CData::Property > CData::PropertyName(
{
  // EXPRESSION = 0,
  "Expression",
  // INITIAL_EXPRESSION,
  "Initial Expression",
  // INITIAL_VALUE,
  "Initial Value",
  // SIMULATION_TYPE,
  "Simulation Type",
  // SPATIAL_DIMENSION,
  "Spatial Dimensions",
  // ADD_NOISE,
  "Add Noise",
  // NOISE_EXPRESSION,
  "Noise Expression",
  // OBJECT_NAME,
  "Object Name",
  // OBJECT_PARENT_CN,
  "Object Parent CN",
  // OBJECT_TYPE,
  "Object Type",
  // OBJECT_FLAG,
  "Object Flag",
  // OBJECT_INDEX,
  "Object Index",
  // OBJECT_REFERENCES,
  "Object References",
  // OBJECT_REFERENCE,
  "Object Reference",
  // OBJECT_REFERENCE_CN,
  "Object Reference CN",
  // OBJECT_REFERENCE_INDEX,
  "Object Reference Index",
  // OBJECT_POINTER,
  "Object Pointer",
  // EVALUATION_TREE_TYPE,
  "Evaluation Tree Type",
  // TASK_TYPE,
  "Task Type",
  // PLOT_TYPE,
  "Plot Type",
  // PLOT_ITEM_TYPE,
  "Plot Item Type",
  // PARAMETER_TYPE,
  "Parameter Type",
  // PARAMETER_VALUE,
  "Parameter Value",
  // UNIT,
  "Unit",
  // VOLUME_UNIT,
  "Volume Unit",
  // AREA_UNIT,
  "Area Unit",
  // LENGTH_UNIT,
  "Length Unit",
  // TIME_UNIT,
  "Time Unit",
  // QUANTITY_UNIT,
  "Quantity Unit",
  // MODEL_TYPE,
  "Model Type",
  // AVOGADRO_NUMBER,
  "Avogadro's Number",
  // DIMENSIONALITY,
  "Dimensionality",
  // ARRAY_ELEMENT_INDEX,
  "Array Element Index",
  // COMMENT,
  "Comment",
  // REPORT_SEPARATOR,
  "Report Separator",
  // REPORT_IS_TABLE,
  "Report is Table",
  // REPORT_SHOW_TITLE,
  "Report show Title",
  // REPORT_PRECISION,
  "Report Precision",
  // MIRIAM_PREDICATE,
  "MIRIAM Predicate",
  // MIRIAM_RESOURCE,
  "MIRIAM Resource",
  // MIRIAM_ID,
  "MIRIAM Id",
  // DATE,
  "Date",
  // GIVEN_NAME,
  "Given Name",
  // FAMILY_NAME,
  "Family Name",
  // EMAIL,
  "Email",
  // ORGANIZATION,
  "Organization"
});

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

bool CData::operator == (const CData & rhs) const
{
  return *static_cast< const std::map< std::string, CDataValue > * >(this) == *static_cast< const std::map< std::string, CDataValue > * >(&rhs);
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
  std::map< std::string, CDataValue >::iterator found = find(name);

  if (found != end())
    {
      found->second = value;
      return false;
    }

  insert(std::make_pair(name, value));
  return true;
}

bool CData::addProperty(const Property & property, const CDataValue & value)
{
  return addProperty(PropertyName[property], value);
}

bool CData::appendData(const CData & data)
{
  bool success = true;

  const_iterator it = data.begin();
  const_iterator end = data.end();

  for (; it != end; ++it)
    {
      operator[](it->first) = it->second;
    }

  return success;
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

bool CData::isSetProperty(const std::string & name) const
{
  return find(name) != end();
}

bool CData::isSetProperty(const Property & property) const
{
  return isSetProperty(PropertyName[property]);
}

bool CData::empty() const
{
  return std::map< std::string, CDataValue >::empty();
}

CData::const_iterator CData::begin() const
{
  return std::map< std::string, CDataValue >::begin();
}

CData::const_iterator CData::end() const
{
  return std::map< std::string, CDataValue >::end();
}

std::ostream & operator << (std::ostream & os, const CData & o)
{
  std::map< std::string, CDataValue >::const_iterator it = o.begin();
  std::map< std::string, CDataValue >::const_iterator end = o.end();

  for (; it != end; ++it)
    os << it->first << ": " << it->second << std::endl;

  return os;
}
