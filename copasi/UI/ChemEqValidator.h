/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/ChemEqValidator.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/10/15 17:12:26 $
   End CVS Header */

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
