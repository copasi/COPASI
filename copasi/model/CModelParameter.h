// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelParameter.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/10/21 17:45:15 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CModelParameter
#define COPASI_CModelParameter

#include "copasi/report/CCopasiObjectName.h"

class CModelParameterGroup;
class CCopasiObject;
class CExpression;

class CModelParameter
{
public:
  enum Type
  {
    Model,
    Compartment,
    Species,
    ModelValue,
    ReactionParameter,
    Group,
    Set,
    unknown
  };

  enum CompareResult
  {
    Obsolete,
    Missing,
    Modified,
    Identical
  };

public:
  /**
   * Constructor
   */
  CModelParameter(CModelParameterGroup * pParent, const CModelParameter::Type & type);

  /**
   * Copy constructor
   */
  CModelParameter(const CModelParameter & src, CModelParameterGroup * pParent);

public:
  /**
   * Destructor
   */
  virtual ~CModelParameter();

  CModelParameterGroup * getParent() const;

  const Type & getType() const;

  void setCN(const CCopasiObjectName & cn);

  const CCopasiObjectName & getCN() const;

  void setValue(const C_FLOAT64 & value);

  const C_FLOAT64 & getValue() const;

  void setInitialExpression(const std::string & initialExpression);

  std::string getInitialExpression() const;

  void setCompareResult(const CompareResult & compareResult);

  const CompareResult & getCompareResult() const;

  size_t getIndex() const;

  bool isReadOnly() const;

  CCopasiObject * getObject() const;

  bool isInitialExpressionValid() const;

  virtual void compile();

  virtual const CompareResult & diff(const CModelParameter & other);

  virtual bool updateModel();

protected:
  CModelParameterGroup * mpParent;

  Type mType;

  CRegisteredObjectName mCN;

  C_FLOAT64 mValue;

  CExpression * mpInitialExpression;

  CompareResult mCompareResult;

  CCopasiObject * mpObject;

  bool mIsInitialExpressionValid;
};

#endif // COPASI_CModelParameter
