// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include <sstream>

#include "copasi/copasi.h"

#include "CData.h"

#include "copasi/utilities/utility.h"
#include "copasi/utilities/Cmd5.h"

// static
const CEnumAnnotation< std::string, CData::Property > CData::PropertyName(
{
  "Expression", // EXPRESSION
  "Initial Expression", // INITIAL_EXPRESSION
  "Initial Value", // INITIAL_VALUE
  "Initial Intensive Value", // INITIAL_INTENSIVE_VALUE
  "Simulation Type", // SIMULATION_TYPE
  "Spatial Dimensions", // SPATIAL_DIMENSION
  "Add Noise", // ADD_NOISE
  "Noise Expression", // NOISE_EXPRESSION
  "Chemical Equation", // CHEMICAL_EQUATION
  "Kinetic Law", // KINETIC_LAW
  "Kinetic Law Unit Type", // KINETIC_LAW_UNIT_TYPE
  "Kinetic Law Variable Mapping", // KINETIC_LAW_VARIABLE_MAPPING
  "Local Reaction Parameters", // LOCAL_REACTION_PARAMETERS
  "Scaling Compartment", // SCALING_COMPARTMENT
  "Object UUID", // OBJECT_UUID
  "Object Name", // OBJECT_NAME
  "Object Parent CN", // OBJECT_PARENT_CN
  "Object Type", // OBJECT_TYPE
  "Object Flag", // OBJECT_FLAG
  "Object Hash", // OBJECT_HASH,
  "Object Index", // OBJECT_INDEX
  "Object References", // OBJECT_REFERENCES
  "Object Reference", // OBJECT_REFERENCE
  "Object Reference CN", // OBJECT_REFERENCE_CN
  "Object Reference Index", // OBJECT_REFERENCE_INDEX
  "Object Pointer", // OBJECT_POINTER
  "Evaluation Tree Type", // EVALUATION_TREE_TYPE
  "Task Type", // TASK_TYPE
  "Task Scheduled", // TASK_SCHEDULED
  "Task Update Model", // TASK_UPDATE_MODEL
  "Task Report", // TASK_REPORT
  "Task Report Target", // TASK_REPORT_TARGET
  "Task Report Append", // TASK_REPORT_APPEND
  "Task Report Confirm Overwrite", // TASK_REPORT_CONFIRM_OVERWRITE
  "Problem", // PROBLEM
  "Method", // METHOD
  "Method Type", // METHOD_TYPE
  "Plot Type", // PLOT_TYPE
  "Plot Item Type", // PLOT_ITEM_TYPE
  "Parameter Type", // PARAMETER_TYPE
  "Parameter Role", // PARAMETER_ROLE
  "Parameter Used", //  PARAMETER_USED
  "Parameter Value", // PARAMETER_VALUE
  "Unit", // UNIT
  "Volume Unit", // VOLUME_UNIT
  "Area Unit", // AREA_UNIT
  "Length Unit", // LENGTH_UNIT
  "Time Unit", // TIME_UNIT
  "Quantity Unit", // QUANTITY_UNIT
  "Model Type", // MODEL_TYPE
  "Avogadro's Number", // AVOGADRO_NUMBER
  "Dimensionality", // DIMENSIONALITY
  "Array Element Index", // ARRAY_ELEMENT_INDEX
  "Report Separator", // REPORT_SEPARATOR
  "Report is Table", // REPORT_IS_TABLE
  "Report show Title", // REPORT_SHOW_TITLE
  "Report Precision", // REPORT_PRECISION
  "Notes", // NOTES
  "MIRIAM RDF/XML", // MIRIAM_RDF_XML
  "MIRIAM Predicate", // MIRIAM_PREDICATE
  "MIRIAM Resource", // MIRIAM_RESOURCE
  "MIRIAM Description", // MIRIAM_DESCRIPTION
  "MIRIAM Id", // MIRIAM_ID
  "Date", // DATE
  "Given Name", // GIVEN_NAME
  "Family Name", // FAMILY_NAME
  "Email", // EMAIL
  "Organization", // ORGANIZATION
  "Framework", // FRAMEWORK
  "Value", // VALUE
  "Delay Assignment", // DELAY_ASSIGNMENT
  "Fire at Initial Time", // FIRE_AT_INITIALTIME
  "Persistent Trigger", // PERSISTENT_TRIGGER
  "Trigger Expression", // TRIGGER_EXPRESSION
  "Delay Expression", // DELAY_EXPRESSION
  "Priority Expression", // PRIORITY_EXPRESSION
  "Assignments", // ASSIGNMENTS
  "Vector Content" // VECTOR_CONTENT
  "Unit symbol", // UNIT_SYMBOL
  "Unit expression", // UNIT_EXPRESSION
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

bool CData::operator != (const CData & rhs) const
{
  return *static_cast< const std::map< std::string, CDataValue > * >(this) != *static_cast< const std::map< std::string, CDataValue > * >(&rhs);
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

void CData::clear()
{
  std::map< std::string, CDataValue >::clear();
}

std::string CData::hash() const
{
  std::stringstream Data;
  Data << *this;

  return Cmd5::digest(Data);
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

std::istream & operator >> (std::istream & is, const CData & i)
{
  // TODO CRITICAL Implement me!
  return is;
}
