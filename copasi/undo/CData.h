// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CData
#define COPASI_CData

#include <map>

#include "copasi/core/CCore.h"
#include "copasi/core/CEnumAnnotation.h"
#include "copasi/undo/CDataValue.h"

class CData : private std::map< std::string, CDataValue >
{
public:
  enum Property
  {
    EXPRESSION = 0,
    INITIAL_EXPRESSION,
    INITIAL_VALUE,
    INITIAL_INTENSIVE_VALUE,
    SIMULATION_TYPE,
    SPATIAL_DIMENSION,
    ADD_NOISE,
    NOISE_EXPRESSION,
    CHEMICAL_EQUATION,
    KINETIC_LAW,
    KINETIC_LAW_UNIT_TYPE,
    KINETIC_LAW_VARIABLE_MAPPING,
    LOCAL_REACTION_PARAMETERS,
    SCALING_COMPARTMENT,
    OBJECT_UUID,
    OBJECT_NAME,
    OBJECT_PARENT_CN,
    OBJECT_TYPE,
    OBJECT_FLAG,
    OBJECT_HASH,
    OBJECT_INDEX,
    OBJECT_REFERENCES,
    OBJECT_REFERENCE,
    OBJECT_REFERENCE_CN,
    OBJECT_REFERENCE_INDEX,
    OBJECT_POINTER,
    EVALUATION_TREE_TYPE,
    TASK_TYPE,
    TASK_SCHEDULED,
    TASK_UPDATE_MODEL,
    TASK_REPORT,
    TASK_REPORT_TARGET,
    TASK_REPORT_APPEND,
    TASK_REPORT_CONFIRM_OVERWRITE,
    PROBLEM,
    METHOD,
    METHOD_TYPE,
    PLOT_TYPE,
    PLOT_ITEM_TYPE,
    PARAMETER_TYPE,
    PARAMETER_ROLE,
    PARAMETER_USED,
    PARAMETER_VALUE,
    UNIT,
    VOLUME_UNIT,
    AREA_UNIT,
    LENGTH_UNIT,
    TIME_UNIT,
    QUANTITY_UNIT,
    MODEL_TYPE,
    AVOGADRO_NUMBER,
    DIMENSIONALITY,
    ARRAY_ELEMENT_INDEX,
    REPORT_SEPARATOR,
    REPORT_IS_TABLE,
    REPORT_SHOW_TITLE,
    REPORT_PRECISION,
    NOTES,
    MIRIAM_RDF_XML,
    MIRIAM_PREDICATE,
    MIRIAM_RESOURCE,
    MIRIAM_DESCRIPTION,
    MIRIAM_ID,
    DATE,
    GIVEN_NAME,
    FAMILY_NAME,
    EMAIL,
    ORGANIZATION,
    FRAMEWORK,
    VALUE,
    DELAY_ASSIGNMENT,
    FIRE_AT_INITIALTIME,
    PERSISTENT_TRIGGER,
    TRIGGER_EXPRESSION,
    DELAY_EXPRESSION,
    PRIORITY_EXPRESSION,
    ASSIGNMENTS,
    VECTOR_CONTENT,
    UNIT_SYMBOL,
    UNIT_EXPRESSION
  };

private:
  constexpr static CEnumAnnotationInstance _PropertyName{
    Property::OBJECT_NAME,
    MapNode{Property::EXPRESSION, "Expression"},
    MapNode{Property::INITIAL_EXPRESSION, "Initial Expression"},
    MapNode{Property::INITIAL_VALUE, "Initial Value"},
    MapNode{Property::INITIAL_INTENSIVE_VALUE, "Initial Intensive Value"},
    MapNode{Property::SIMULATION_TYPE, "Simulation Type"},
    MapNode{Property::SPATIAL_DIMENSION, "Spatial Dimensions"},
    MapNode{Property::ADD_NOISE, "Add Noise"},
    MapNode{Property::NOISE_EXPRESSION, "Noise Expression"},
    MapNode{Property::CHEMICAL_EQUATION, "Chemical Equation"},
    MapNode{Property::KINETIC_LAW, "Kinetic Law"},
    MapNode{Property::KINETIC_LAW_UNIT_TYPE, "Kinetic Law Unit Type"},
    MapNode{Property::KINETIC_LAW_VARIABLE_MAPPING, "Kinetic Law Variable Mapping"},
    MapNode{Property::LOCAL_REACTION_PARAMETERS, "Local Reaction Parameters"},
    MapNode{Property::SCALING_COMPARTMENT, "Scaling Compartment"},
    MapNode{Property::OBJECT_UUID, "Object UUID"},
    MapNode{Property::OBJECT_NAME, "Object Name"},
    MapNode{Property::OBJECT_PARENT_CN, "Object Parent CN"},
    MapNode{Property::OBJECT_TYPE, "Object Type"},
    MapNode{Property::OBJECT_FLAG, "Object Flag"},
    MapNode{Property::OBJECT_HASH, "Object Hash"},
    MapNode{Property::OBJECT_INDEX, "Object Index"},
    MapNode{Property::OBJECT_REFERENCES, "Object References"},
    MapNode{Property::OBJECT_REFERENCE, "Object Reference"},
    MapNode{Property::OBJECT_REFERENCE_CN, "Object Reference CN"},
    MapNode{Property::OBJECT_REFERENCE_INDEX, "Object Reference Index"},
    MapNode{Property::OBJECT_POINTER, "Object Pointer"},
    MapNode{Property::EVALUATION_TREE_TYPE, "Evaluation Tree Type"},
    MapNode{Property::TASK_TYPE, "Task Type"},
    MapNode{Property::TASK_SCHEDULED, "Task Scheduled"},
    MapNode{Property::TASK_UPDATE_MODEL, "Task Update Model"},
    MapNode{Property::TASK_REPORT, "Task Report"},
    MapNode{Property::TASK_REPORT_TARGET, "Task Report Target"},
    MapNode{Property::TASK_REPORT_APPEND, "Task Report Append"},
    MapNode{Property::TASK_REPORT_CONFIRM_OVERWRITE, "Task Report Confirm Overwrite"},
    MapNode{Property::PROBLEM, "Problem"},
    MapNode{Property::METHOD, "Method"},
    MapNode{Property::METHOD_TYPE, "Method Type"},
    MapNode{Property::PLOT_TYPE, "Plot Type"},
    MapNode{Property::PLOT_ITEM_TYPE, "Plot Item Type"},
    MapNode{Property::PARAMETER_TYPE, "Parameter Type"},
    MapNode{Property::PARAMETER_ROLE, "Parameter Role"},
    MapNode{Property::PARAMETER_USED, "Parameter Used"},
    MapNode{Property::PARAMETER_VALUE, "Parameter Value"},
    MapNode{Property::UNIT, "Unit"},
    MapNode{Property::VOLUME_UNIT, "Volume Unit"},
    MapNode{Property::AREA_UNIT, "Area Unit"},
    MapNode{Property::LENGTH_UNIT, "Length Unit"},
    MapNode{Property::TIME_UNIT, "Time Unit"},
    MapNode{Property::QUANTITY_UNIT, "Quantity Unit"},
    MapNode{Property::MODEL_TYPE, "Model Type"},
    MapNode{Property::AVOGADRO_NUMBER, "Avogadro's Number"},
    MapNode{Property::DIMENSIONALITY, "Dimensionality"},
    MapNode{Property::ARRAY_ELEMENT_INDEX, "Array Element Index"},
    MapNode{Property::REPORT_SEPARATOR, "Report Separator"},
    MapNode{Property::REPORT_IS_TABLE, "Report is Table"},
    MapNode{Property::REPORT_SHOW_TITLE, "Report show Title"},
    MapNode{Property::REPORT_PRECISION, "Report Precision"},
    MapNode{Property::NOTES, "Notes"},
    MapNode{Property::MIRIAM_RDF_XML, "MIRIAM RDF/XML"},
    MapNode{Property::MIRIAM_PREDICATE, "MIRIAM Predicate"},
    MapNode{Property::MIRIAM_RESOURCE, "MIRIAM Resource"},
    MapNode{Property::MIRIAM_DESCRIPTION, "MIRIAM Description"},
    MapNode{Property::MIRIAM_ID, "MIRIAM Id"},
    MapNode{Property::DATE, "Date"},
    MapNode{Property::GIVEN_NAME, "Given Name"},
    MapNode{Property::FAMILY_NAME, "Family Name"},
    MapNode{Property::EMAIL, "Email"},
    MapNode{Property::ORGANIZATION, "Organization"},
    MapNode{Property::FRAMEWORK, "Framework"},
    MapNode{Property::VALUE, "Value"},
    MapNode{Property::DELAY_ASSIGNMENT, "Delay Assignment"},
    MapNode{Property::FIRE_AT_INITIALTIME, "Fire at Initial Time"},
    MapNode{Property::PERSISTENT_TRIGGER, "Persistent Trigger"},
    MapNode{Property::TRIGGER_EXPRESSION, "Trigger Expression"},
    MapNode{Property::DELAY_EXPRESSION, "Delay Expression"},
    MapNode{Property::PRIORITY_EXPRESSION, "Priority Expression"},
    MapNode{Property::ASSIGNMENTS, "Assignments"},
    MapNode{Property::VECTOR_CONTENT, "Vector Content"},
    MapNode{Property::UNIT_SYMBOL, "Unit symbol"},
    MapNode{Property::UNIT_EXPRESSION, "Unit expression"}};

public:
  constexpr static CEnumAnnotation< Property, std::string_view > PropertyName{_PropertyName};

  typedef CDataValue::Type Type;
  typedef std::map< std::string, CDataValue >::const_iterator const_iterator;

  friend std::ostream & operator << (std::ostream & os, const CData & o);
  friend std::istream & operator >> (std::istream & is, const CData & i);

  CData();

  CData(const CData & src);

  ~CData();

  CData & operator = (const CData & rhs);

  bool operator == (const CData & rhs) const;

  bool operator != (const CData & rhs) const;

  const CDataValue & getProperty(const std::string & name) const;

  const CDataValue & getProperty(const Property & property) const;

  CDataValue & getProperty(const std::string & name);

  CDataValue & getProperty(const Property & property);

  bool addProperty(const std::string & name, const CDataValue & value);

  bool addProperty(const Property & property, const CDataValue & value);

  bool appendData(const CData & data);

  bool removeProperty(const std::string & name);

  bool removeProperty(const Property & property);

  bool isSetProperty(const std::string & name) const;

  bool isSetProperty(const Property & property) const;

  bool empty() const;

  void clear();

  std::string hash() const;

  const_iterator begin() const;

  const_iterator end() const;
};

#endif // CData
