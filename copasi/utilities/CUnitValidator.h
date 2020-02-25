// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

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
   * @param const std::vector< CUnit > & variableUnits (default: std::vector< CUnit >)
   */
  CUnitValidator(const CMathContainer & math,
                 const CEvaluationTree & tree);

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
   * @param const std::vector< CUnit > & variableUnits (default: std::vector< CUnit >)
   * @return bool valid
   */
  bool validateUnits(const CUnit & unit = CUnit(CBaseUnit::undefined),
                     const std::vector< CUnit > & variableUnits = std::vector< CUnit >());

  /**
   * Validate the units in the tree and check whether the result matches the optional argument
   * @param const CUnit & unit (default: CBaseUnit::undefined)
   * @return bool valid
   */
  bool validateUnits(const CValidatedUnit & unit,
                     const std::vector< CValidatedUnit > & variableUnits);

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
   * Retrieve the validated unit of the object units
   * @param const CObjectInterface * pObject
   * @return const CValidatedUnit & objectUnit
   */
  const CValidatedUnit & getObjectUnit(const CObjectInterface * pObject) const;

  /**
   * Retrieve the validated unit
   * @return const CValidatedUnit & unit
   */
  const CValidatedUnit & getUnit() const;

private:
  bool validate();
  void getUnits();
  bool setUnits();

  CMathContainer & mMathContainer;
  const CEvaluationTree & mTree;
  CValidatedUnit mTargetUnit;
  std::vector< CValidatedUnit > mProvidedVariableUnits;
  std::vector< CValidatedUnit > mVariableUnits;
  std::map < CObjectInterface *, CValidatedUnit > mObjectUnits;
  std::map < CEvaluationNode *, CValidatedUnit > mNodeUnits;
};

#endif // CUNIT_VALIDATOR_H
