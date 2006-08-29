/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CEFMAlgorithm.h,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/29 20:15:14 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CEFMAlgorithm class.
 *  Used to calculate elementary flux modes
 *
 *  Created for Copasi by Stefan Hoops 2002-05-08
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CEFMAlgorithm
#define COPASI_CEFMAlgorithm

#include "CEFMMethod.h"
#include "CFluxMode.h"

#include "utilities/CMatrix.h"

class CTableauMatrix;

class CEFMAlgorithm: public CEFMMethod
  {
    friend CEFMMethod * CEFMMethod::createMethod(CCopasiMethod::SubType subType);

  private:
    /**
     * Default constructor
     * @param const CCopasiContainer * pParent (Default: NULL)
     */
    CEFMAlgorithm(const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Copy Constructor
     * @param const CEFMAlgorithm & src
     */
    CEFMAlgorithm(const CEFMAlgorithm & src,
                  const CCopasiContainer * pParent = NULL);

    /**
    *  Destructor
    */
    ~CEFMAlgorithm();

    /**
     * Execute the optimization algorithm calling simulation routine
     * when needed. It is noted that this procedure can give feedback
     * of its progress by the callback function set with SetCallback.
     * @ return success;
     */
    virtual bool calculate();

  private:
    void initObjects();

    /**
     * Initialize arrays and pointer called by calculate.
     * @return bool success
     */
    bool initialize();

    void calculateNextTableau();

    void buildFluxModes(std::vector < CFluxMode > & fluxModes);

    // Attributes
  private:
    /**
     * A pointer to the model
     */
    CModel * mpModel;

    /**
     * Matrix conatining the reorderd stoichiometry matrix.
     */
    std::vector< std::vector< C_FLOAT64 > > mStoi;

    /**
     * The number of reversible reactions.
     */
    unsigned C_INT32 mReversible;

    /**
     * A pointer to the current tableau matrix
     */
    CTableauMatrix * mpCurrentTableau;

    /**
     * A pointer to the next tableaun matrix
     */
    CTableauMatrix * mpNextTableau;

    /**
     * The current step used for process report.
     */
    unsigned C_INT32 mStep;

    /**
     * The max step used for process report.
     */
    unsigned C_INT32 mMaxStep;

    /**
     * Handle to the process report item "Current Step"
     */
    unsigned C_INT32 mhSteps;
  };

#endif // COPASI_CEFMAlgorithm
