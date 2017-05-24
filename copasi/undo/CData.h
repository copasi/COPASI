// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CData
#define COPASI_CData

#include <map>
#include <array>

#include "copasi/undo/CDataValue.h"

class CData : private std::map< std::string, CDataValue >
{
public:
  enum Property
  {
    EXPRESSION = 0,
    INITIAL_EXPRESSION,
    INITIAL_VALUE,
    SIMULATION_TYPE,
    SPATIAL_DIMENSION,
    ADD_NOISE,
    NOISE_EXPRESSION,
    OBJECT_NAME,
    OBJECT_PARENT_CN,
    OBJECT_TYPE,
    OBJECT_FLAG,
    OBJECT_INDEX,
    OBJECT_REFERENCES,
    OBJECT_REFERENCE,
    OBJECT_REFERENCE_CN,
    OBJECT_REFERENCE_INDEX,
    OBJECT_POINTER,
    EVALUATION_TREE_TYPE,
    TASK_TYPE,
    PLOT_TYPE,
    PLOT_ITEM_TYPE,
    PARAMETER_TYPE,
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
    COMMENT,
    REPORT_SEPARATOR,
    REPORT_IS_TABLE,
    REPORT_SHOW_TITLE,
    REPORT_PRECISION,
    __SIZE
  };

  static const std::array< const std::string, static_cast< size_t >(Property::__SIZE) > PropertyName;

  typedef CDataValue::Type Type;

  friend std::ostream & operator << (std::ostream & os, const CData & o);

  CData();

  CData(const CData & src);

  ~CData();

  CData & operator = (const CData & rhs);

  const CDataValue & getProperty(const std::string & name) const;

  const CDataValue & getProperty(const Property & property) const;

  CDataValue & getProperty(const std::string & name);

  CDataValue & getProperty(const Property & property);

  bool setProperty(const std::string & name, const CDataValue & value);

  bool setProperty(const Property & property, const CDataValue & value);

  bool addProperty(const std::string & name, const CDataValue & value);

  bool addProperty(const Property & property, const CDataValue & value);

  bool appendData(const CData & data);

  bool removeProperty(const std::string & name);

  bool removeProperty(const Property & property);

  bool isSetProperty(const std::string & name) const;

  bool isSetProperty(const Property & property) const;

  bool empty() const;
};

#endif // CData
