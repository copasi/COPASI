// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CHEMEQVAL
#define CHEMEQVAL

#include <QtGui/QValidator>
#include "model/CChemEqInterface.h"

class ChemEqValidator : public QValidator
{
public:
  ChemEqValidator(QObject * parent, const char * name = 0)
    : QValidator(parent, name)
  {}

  virtual State validate(QString & input, int & C_UNUSED(pos)) const
  {
    std::string eq = TO_UTF8(input);

    if (CChemEqInterface::isValidEq(eq))
      return Acceptable;
    else
      return Intermediate;
  }
};

#endif
