// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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
    UNIT_EXPRESSION,
    __SIZE
  };

  static const CEnumAnnotation< std::string, Property > PropertyName;

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
