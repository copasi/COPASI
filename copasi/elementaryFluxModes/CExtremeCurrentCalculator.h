/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/Attic/CExtremeCurrentCalculator.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 07:04:06 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_EXTREME_CURRENT_CALCULATOR
#define COPASI_EXTREME_CURRENT_CALCULATOR

#include "elementaryFluxModes/CEFMAlgorithm.h"

class CExtremeCurrentCalculator : public CEFMAlgorithm
  {
    friend CEFMMethod * CEFMMethod::createMethod(CCopasiMethod::SubType subType);

  public:
    CExtremeCurrentCalculator(const CCopasiContainer * pParent = NULL);

    CExtremeCurrentCalculator(const CExtremeCurrentCalculator & src,
                              const CCopasiContainer * pParent = NULL);

  protected:
    virtual bool initialize();
  };

#endif // COPASI_EXTREME_CURRENT_CALCULATOR
