// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// This class is used to determine and set appropriate
// units in expressions and functions, etc.

#ifndef CUNIT_VALIDATOR_H
#define CUNIT_VALIDATOR_H

#include "copasi/utilities/CUnit.h"
#include "math/CMathContainer.h"
#include "function/CFunction.h"
#include "function/CExpression.h"

class CUnitValidator
{
private:
  // constructors
  /**
   * Default constructor
   */
  CUnitValidator();

public:

  /**
   * Function constructor
   * @param
   */
  CUnitValidator(const CMathContainer & math,
                 const CEvaluationTree & tree,
                 const std::vector< CUnit > & variableUnits = std::vector< CUnit >());

  /**
   * Copy constructor
   * @param const CUnitValidator & src
   */
  CUnitValidator(const CUnitValidator & src);

  ~CUnitValidator();

  bool validateUnits(const CUnit & unit = CUnit(CBaseUnit::undefined));

  const std::vector< CUnit > & getVariableUnits() const;
  const CUnit & getUnit() const;

private:
  void getUnits();

  void setUnits(const CUnit & unit);

  const CMathContainer & mMathContainer;
  const CEvaluationTree & mTree;
  std::vector< CUnit > mVariableUnits;
  std::map < CEvaluationNode * , CUnit > mNodeUnits;
};

#endif // CUNIT_VALIDATOR_H
