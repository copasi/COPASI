/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/ChemEqValidator.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/20 18:55:47 $
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

    virtual State validate (QString & input, int & pos) const
      {
        std::string eq = (const char *)input.utf8();
        if (CChemEqInterface::isValidEq(eq))
          return Acceptable;
        else
          return Intermediate;
      }
  };

#endif
