// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// This class is used to determine and set appropriate
// units in expressions and functions, etc.

#ifndef CUNIT_VALIDATOR_H
#define CUNIT_VALIDATOR_H

#include "copasi/utilities/CValidatedUnit.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/function/CFunction.h"
#include "copasi/function/CExpression.h"

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
   * @param const CMathContainer & math
   * @param const CEvaluationTree & tree
   * @param const std::vector< CUnit > & variableUnits = std::vector< CUnit >()
   */
  CUnitValidator(const CMathContainer & math,
                 const CEvaluationTree & tree,
                 const std::vector< CUnit > & variableUnits = std::vector< CUnit >());

  /**
   * Function constructor
   * @param const CMathContainer & math
   * @param const CEvaluationTree & tree
   * @param const std::vector< CValidatedUnit > & variableUnits = std::vector< CValidatedUnit >()
   */
  CUnitValidator(const CMathContainer & math,
                 const CEvaluationTree & tree,
                 const std::vector< CValidatedUnit > & variableUnits = std::vector< CValidatedUnit >());

  /**
   * Copy constructor
   * @param const CUnitValidator & src
   */
  CUnitValidator(const CUnitValidator & src);

  /**
   * Destructor
   */
  ~CUnitValidator();

  /**
   * Validate the units in the tree and check whether the result matches the optional argument
   * @param const CUnit & unit (default: CBaseUnit::undefined)
   * @return bool valid
   */
  bool validateUnits(const CUnit & unit = CUnit(CBaseUnit::undefined));

  /**
   * Retrieve the validated variable units
   * @return const std::vector< CValidatedUnit > &variableUnits
   */
  const std::vector< CValidatedUnit > & getVariableUnits() const;

  /**
   * Retrieve the validated object units
   * @return const std::map< CObjectInterface *, CValidatedUnit > & objectUnits
   */
  const std::map< CObjectInterface *, CValidatedUnit > & getObjectUnits() const;

  /**
   * Retrieve the validated unit
   * @return const CValidatedUnit & unit
   */
  const CValidatedUnit & getUnit() const;

private:
  void getUnits();

  bool setUnits(const CUnit & unit);

  const CMathContainer & mMathContainer;
  const CEvaluationTree & mTree;
  std::vector< CValidatedUnit > mVariableUnits;
  std::map < CObjectInterface *, CValidatedUnit > mObjectUnits;
  std::map < CEvaluationNode * , CValidatedUnit > mNodeUnits;
};

#endif // CUNIT_VALIDATOR_H
