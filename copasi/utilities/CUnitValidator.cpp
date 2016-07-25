// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/utilities/CUnitValidator.h"

//CUnitValidator::CUnitValidator():
//  mMathContainer(),
//  mTree(),
//  mVariableUnits()
//{
//}

CUnitValidator::CUnitValidator(const CMathContainer & math,
                               const CEvaluationTree & function,
                               const std::vector < CUnit > & variableUnits):
  mMathContainer(math),
  mTree(function),
  mVariableUnits(variableUnits)
{
}

CUnitValidator::CUnitValidator(const CUnitValidator &src):
  mMathContainer(src.mMathContainer),
  mTree(src.mTree),
  mVariableUnits(src.mVariableUnits)
{
}

CUnitValidator::~CUnitValidator()
{
}

bool CUnitValidator::validateUnits(const CUnit & unit)
{
  return false;
}
