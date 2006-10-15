/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodSA.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 07:43:32 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * COptMethodSA class
 */

#ifndef COPASI_COptMethodSA
#define COPASI_COptMethodSA

#include <vector>
#include "utilities/CMatrix.h"
#include "optimization/COptMethod.h"

class CRandom;

class COptMethodSA : public COptMethod
  {
    friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

    // Operations
  public:
    /**
     * Copy Constructor
     * @param const COptMethodSA & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptMethodSA(const COptMethodSA & src,
                 const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~COptMethodSA();

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
    COptMethodSA(const CCopasiContainer * pParent = NULL);

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
     * The current temperature
     */
    C_FLOAT64 mTemperature;

    /**
     * Handle to the process report item "Current Temperature"
     */
    unsigned C_INT32 mhTemperature;

    /**
     * The cooling factor
     */
    C_FLOAT64 mCoolingFactor;

    /**
     * The tolerance
     */
    C_FLOAT64 mTolerance;

    /**
     * a pointer to the randomnumber generator.
     */
    CRandom * mpRandom;

    /**
     * number of parameters
     */
    unsigned C_INT32 mVariableSize;

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

    /**
     * The current solution guess
     */
    CVector< C_FLOAT64 > mCurrent;

    /**
     * The result of a function evaluation for mCurrent
     */
    C_FLOAT64 mCurrentValue;

    /**
     * The step taken
     */
    CVector< C_FLOAT64 > mStep;

    /**
     * The number of accepted steps
     */
    CVector< unsigned C_INT32 > mAccepted;
  };

#endif  // COPASI_COptMethodSA
