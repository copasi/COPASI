/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/qtUtilities.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/07 16:59:55 $
   End CVS Header */

#ifndef COPASI_qtUtilities
#define COPASI_qtUtilities

#include "utilities/CCopasiParameter.h"

class CCopasiParameterGroup;

QString getParameterValue(const CCopasiParameterGroup * group,
                          const unsigned C_INT32 & index,
                          CCopasiParameter::Type * type = NULL);

bool setParameterValue(CCopasiParameterGroup * group,
                       const unsigned C_INT32 & index,
                       const QString & value);
#endif // COPASI_qtUtilities
