// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQUNITVALIDATOR_H
#define CQUNITVALIDATOR_H

#include <QTextEdit>

#include "copasi/UI/CQValidator.h"
#include "copasi/utilities/CUnit.h"

// The class for checking that an input string can be
// parsed to create a CUnit.

class CQValidatorUnit: public CQValidator< QLineEdit >
{
  Q_OBJECT
public:
  CQValidatorUnit(QLineEdit *parent, const char * name = 0);
  virtual State validate(QString & input, int & pos) const;

  void setConstraint(const std::string & constraint);

private:
  CUnit mConstraint;
};

#endif
