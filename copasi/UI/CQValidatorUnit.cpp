// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "sstream"
#include "CQValidatorUnit.h"

#include "copasi/copasi.h"
#include "qtUtilities.h"

#include "copasi/utilities/CCopasiException.h"
#include "copasi/utilities/CUnitParser.h"

CQValidatorUnit::CQValidatorUnit(QLineEdit * parent, const char * name):
  CQValidator< QLineEdit >(parent, &QLineEdit::text, name),
  mConstraint()
{}

void CQValidatorUnit::setConstraint(const std::string & constraint)
{
  mConstraint = constraint;
}

QValidator::State CQValidatorUnit::validate(QString & input, int & pos) const
{
  if (input.isEmpty())
    return CQValidator< QLineEdit >::validate(input, pos);

  State CurrentState = Invalid;

  bool success = false;
  std::istringstream buffer(TO_UTF8(input));
  CUnitParser Parser(&buffer);

  try
    {
      success = (Parser.yyparse() == 0);
    }

  catch (CCopasiException & /*exception*/)
    {
      success = false;
    }

  if (success &&
      !mConstraint.getExpression().empty())
    {
      CUnit Unit(TO_UTF8(input));
      success = mConstraint.isEquivalent(Unit) || Unit.isDimensionless();
    }

  if (success)
    {
      return CQValidator< QLineEdit >::validate(input, pos);
    }
  else
    {
      setColor(Invalid);
      CurrentState = Intermediate;
    }

  return CurrentState;
}
