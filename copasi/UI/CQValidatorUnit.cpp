// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "sstream"
#include "qtUtilities.h"
#include "CQValidatorUnit.h"

CQValidatorUnit::CQValidatorUnit(QLineEdit * parent, const char * name):
  CQValidator< QLineEdit >(parent, &QLineEdit::text, name)
{
}

QValidator::State CQValidatorUnit::validate(QString & input, int & pos) const
{
  State CurrentState = Invalid;

  bool success = false;
  std::istringstream buffer(TO_UTF8(input));
  CUnitParser Parser(&buffer);
  success = (Parser.yyparse() == 0);

  if (success)
    {
      setColor(Acceptable);
      CurrentState = Acceptable;
    }

  if (CurrentState != Acceptable)
    {
      setColor(Invalid);
      CurrentState = Intermediate;
    }

  return CurrentState;
}
