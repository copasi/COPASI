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

public:

  // constructors
  /**
   * Default constructor
   */
  CUnitValidator();

  /**
   * Function constructor
   * @param
   */
  CUnitValidator(const CMathContainer & math,
                 const CFunction & function,
                 const std::vector< CUnit > & variableUnits = std::vector< CUnit >());

  /**
   * Expression constructor
   * @param
   */
  CUnitValidator(const CMathContainer & math, const CExpression & expression);

  /**
   * Copy constructor
   * @param const CUnitValidator & src
   */
  CUnitValidator(const CUnitValidator & src);

  ~CUnit();

  bool validateUnit(CUnit & unit = CUnit(CBaseUnit::undefined));

private:

  CMathContainer * mpMathContainer;
  CEvaluationTree * mpTree;
  std::vector< CUnit > mVariableUnits;
  std::map < CEvaluationNode * , CUnit > nodeUnits;
};

#endif // CUNIT_VALIDATOR_H
