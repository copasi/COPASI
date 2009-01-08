/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/ChemEqValidator.h,v $
  $Revision: 1.4 $
  $Name:  $
  $Author: shoops $
  $Date: 2009/01/08 16:07:44 $
  End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CHEMEQVAL
#define CHEMEQVAL

#include <qvalidator.h>
#include "model/CChemEqInterface.h"

class ChemEqValidator : public QValidator
  {
  public:
    ChemEqValidator(QObject * parent, const char * name = 0)
        : QValidator(parent, name)
    {}

    virtual State validate (QString & input, int & C_UNUSED(pos)) const
      {
        std::string eq = TO_UTF8(input);
        if (CChemEqInterface::isValidEq(eq))
          return Acceptable;
        else
          return Intermediate;
      }
  };

#endif
