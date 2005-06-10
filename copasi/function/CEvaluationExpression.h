/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/Attic/CEvaluationExpression.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/10 17:50:36 $
   End CVS Header */

#ifndef COPASI_CEvaluationExpression
#define COPASI_CEvaluationExpression

#include "CEvaluationTree.h"
#include "report/CCopasiContainer.h"

class CEvaluationExpression:
      public CCopasiContainer,
      protected CEvaluationTree
  {};

#endif // COPASI_CEvaluationExpression
