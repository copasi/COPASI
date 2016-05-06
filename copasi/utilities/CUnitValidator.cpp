// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/utilities/CUnitValidator.h"

CUnitValidator::CUnitValidator()
{
}

CUnitValidator::CUnitValidator(const CMathContainer & math,
                               const CFunction & function,
                               const std::vector < CUnitValidator::~CUnit > & variableUnits):
  mpMathContainer(&math),
  mpTree(&function),
  mVariableUnits(variableUnits)
{
}

CUnitValidator::CUnitValidator(const CMathContainer * math, const CExpression * expression):
  mpMathContainer(&math),
  mpTree(&expression),
  mVariableUnits(variableUnits)
{
}

CUnitValidator::CUnitValidator(const CUnitValidator &src)
{
}

bool CUnitValidator::validateUnit(CUnit & unit)
{
}
