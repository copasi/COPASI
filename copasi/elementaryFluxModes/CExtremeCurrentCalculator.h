/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/Attic/CExtremeCurrentCalculator.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: tjohann $
   $Date: 2006/09/12 12:23:44 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_EXTREME_CURRENT_CALCULATOR
#define COPASI_EXTREME_CURRENT_CALCULATOR

#include "CEFMMethod.h"
#include "CFluxMode.h"

#include "elementaryFluxModes/CEFMAlgorithm.h"

class CExtremeCurrentCalculator : public CEFMAlgorithm
  {
    friend CEFMMethod * CEFMMethod::createMethod(CCopasiMethod::SubType subType);
    //friend bool CEFMAlgorithm::calculate();

  public:
    CExtremeCurrentCalculator(const CCopasiContainer * pParent = NULL);

    CExtremeCurrentCalculator(const CExtremeCurrentCalculator & src,
                              const CCopasiContainer * pParent = NULL);

  protected:
    virtual bool initialize();

    // Attributes
    //private:
    /**
    * A pointer to the model
     */
    //CModel * mpModel;

    /**
     * Matrix conatining the reorderd stoichiometry matrix.
     */
    //std::vector< std::vector< C_FLOAT64 > > mStoi;

    /**
     * The number of reversible reactions.
     */
    //unsigned C_INT32 mReversible;

    /**
     * A pointer to the current tableau matrix
     */
    //CTableauMatrix * mpCurrentTableau;

    /**
     * A pointer to the next tableaun matrix
     */
    //CTableauMatrix * mpNextTableau;

    /**
     * The current step used for process report.
     */
    //unsigned C_INT32 mStep;

    /**
     * The max step used for process report.
     */
    //unsigned C_INT32 mMaxStep;

    /**
     * Handle to the process report item "Current Step"
     */
    //unsigned C_INT32 mhSteps;
  };

#endif // COPASI_EXTREME_CURRENT_CALCULATOR
