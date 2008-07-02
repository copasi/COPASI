/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CEFMAlgorithm.h,v $
  $Revision: 1.14 $
  $Name:  $
  $Author: tjohann $
  $Date: 2008/07/02 08:06:12 $
  End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include "elementaryFluxModes/CEFMMethod.h"
#include "elementaryFluxModes/CFluxMode.h"

#include "utilities/CMatrix.h"

class CTableauMatrix;

class CEFMAlgorithm: public CEFMMethod
  {
    friend CEFMMethod * CEFMMethod::createMethod(CCopasiMethod::SubType subType);

  protected:
    /**
     * Default constructor
     * @param const CCopasiContainer * pParent (Default: NULL)
     */
    CEFMAlgorithm(const CCopasiContainer * pParent = NULL);

    /**
     * Constructor to be called by derived methods
     * @param const CCopasiMethod::SubType subType
     * @param const CCopasiContainer * pParent (Default: NULL)
     */
    CEFMAlgorithm(const CCopasiMethod::SubType subType,
                  const CCopasiContainer * pParent = NULL);

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

    /**
     * Do the actual calculation
     */
    void calculateFluxModes();

    virtual bool initialize();

  private:
    void initObjects();

    /**
     * Initialize arrays and pointer called by calculate.
     * @return bool success
     */
    void calculateNextTableau();

    void buildFluxModes(std::vector < CFluxMode > & fluxModes);

    // Attributes
  protected:
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
