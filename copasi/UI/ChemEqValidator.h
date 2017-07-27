// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QValidator>
#include <copasi/UI/qtUtilities.h>
#include <copasi/model/CChemEqInterface.h>

class ChemEqValidator : public QValidator
{
public:
  ChemEqValidator(QObject * parent)
    : QValidator(parent)
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
