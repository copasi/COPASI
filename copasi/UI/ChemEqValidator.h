/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/ChemEqValidator.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:42 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
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
        std::string eq = (const char *)input.utf8();
        if (CChemEqInterface::isValidEq(eq))
          return Acceptable;
        else
          return Intermediate;
      }
  };

#endif
