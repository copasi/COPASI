// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQUNITVALIDATOR_H
#define CQUNITVALIDATOR_H

#include <QtGui/QTextEdit>
#include "copasi/UI/CQValidator.h"
#include "copasi/utilities/CUnitParser.h"


// The class for checking that an input string can be
// parsed to create a CUnit.

class CQValidatorUnit: public CQValidator< QLineEdit >
{
  Q_OBJECT
public:
  CQValidatorUnit(QLineEdit *parent, const char * name = 0);
  virtual State validate(QString & input, int & pos) const;
};

#endif
