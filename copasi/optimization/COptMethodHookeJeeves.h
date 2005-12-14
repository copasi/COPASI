/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodHookeJeeves.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/12/14 00:06:52 $
   End CVS Header */

/**
 * COptMethodHookeJeeves class
 */

#ifndef COPASI_COptMethodHookeJeeves
#define COPASI_COptMethodHookeJeeves

#include "COptMethod.h"
#include "utilities/CVector.h"

class CRandom;

class COptMethodHookeJeeves : public COptMethod
  {
    friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

    // Operations
  public:
    /**
     * Copy Constructor
     * @param const COptMethodHookeJeeves & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptMethodHookeJeeves(const COptMethodHookeJeeves & src,
                          const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~COptMethodHookeJeeves();

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
    COptMethodHookeJeeves(const CCopasiContainer * pParent = NULL);

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
     * Evaluate the fitness of one individual
     * @return bool continue
     */
    bool evaluate();

    /**
     * Finds the best value in the neighborhood of mNew and updates mNew
     * @return C_FLOAT64 bestValue
     */
    C_FLOAT64 COptMethodHookeJeeves::bestNearby();

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
     * The length of steps taken
     */
    C_FLOAT64 mRho;

    /**
     * The maximum number of iterations
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
     * The current individual
     */
    CVector< C_FLOAT64 > mIndividual;

    /**
     * The last individual
     */
    CVector< C_FLOAT64 > mBefore;

    /**
     * The new individual
     */
    CVector< C_FLOAT64 > mNew;

    /**
     * The step taken
     */
    CVector< C_FLOAT64 > mDelta;

    /**
     * The value of the last evaluation.
     */
    C_FLOAT64 mEvaluationValue;

    /**
     * The best value found so far
     */
    C_FLOAT64 mBestValue;

    /**
     * Flag indicating whether the computation shall continue
     */
    bool mContinue;
  };

#endif  // COPASI_COptMethodHookeJeeves
