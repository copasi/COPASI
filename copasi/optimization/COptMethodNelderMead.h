/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodNelderMead.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/29 13:38:55 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * COptMethodNelderMead class
 */

#ifndef COPASI_COptMethodNelderMead
#define COPASI_COptMethodNelderMead

#include <vector>
#include "utilities/CMatrix.h"
#include "COptMethod.h"

class CRandom;

class COptMethodNelderMead : public COptMethod
  {
    friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

    // Operations
  public:
    /**
     * Copy Constructor
     * @param const COptMethodNelderMead & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptMethodNelderMead(const COptMethodNelderMead & src,
                         const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~COptMethodNelderMead();

    /**
     * Execute the optimization algorithm calling simulation routine
     * when needed. It is noted that this procedure can give feedback
     * of its progress by the callback function set with SetCallback.
     * @ return success;
     */
    virtual bool optimise();

  private:
    /**
     * Default Constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptMethodNelderMead(const CCopasiContainer * pParent = NULL);

    /**
     * Initialize contained objects.
     */
    void initObjects();

    /**
     * Initialize arrays and pointer.
     * @return bool success
     */
    virtual bool initialize();

    /**
     * Cleanup arrays and pointers.
     * @return bool success
     */
    virtual bool cleanup();

    /**
     * Evaluate the objective function
     * @return bool continue
     */
    const C_FLOAT64 & evaluate();

    // Attributes
  private:

    /**
     * The maximum number of iterations
     */
    unsigned C_INT32 mIterationLimit;

    /**
     * The tolerance
     */
    C_FLOAT64 mTolerance;

    /**
     * The scale
     */
    C_FLOAT64 mScale;

    /**
     * The number of iterations
     */
    unsigned C_INT32 mIteration;

    /**
     * Handle to the process report item "Current Iteration"
     */
    unsigned C_INT32 mhIteration;

    /**
     * number of parameters
     */
    unsigned C_INT32 mVariableSize;

    /**
     * The simplex
     */
    CMatrix< C_FLOAT64 > mSimplex;

    /**
     * Array of values of objective function for each corner of the simplex
     */
    CVector< C_FLOAT64 > mValue;

    /**
     * The centroid of the simplex
     */
    CVector <C_FLOAT64 > mCentroid;

    /**
     * The current solution guess
     */
    CVector< C_FLOAT64 > mCurrent;

    /**
     * The step taken
     */
    CVector< C_FLOAT64 > mStep;

    /**
     * The best value found so far
     */
    C_FLOAT64 mBestValue;

    /**
     * The result of a function evaluation
     */
    C_FLOAT64 mEvaluationValue;

    /**
     * Flag indicating whether the computation shall continue
     */
    bool mContinue;
  };

#endif  // COPASI_COptMethodNelderMead
