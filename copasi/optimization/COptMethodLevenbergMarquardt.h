/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodLevenbergMarquardt.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: mendes $ 
   $Date: 2006/04/05 12:15:07 $
   End CVS Header */

/**
  * COptMethodLevenbergMarquardt class
  */

#ifndef COPASI_COptMethodLevenbergMarquardt
 #define COPASI_COptMethodLevenbergMarquardt

#include <vector>
#include "utilities/CMatrix.h"
#include "COptMethod.h"

class CRandom;

class COptMethodLevenbergMarquardt : public COptMethod
  {
    friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

    // Operations
  public:
    /**
     * Copy Constructor
     * @param const COptMethodLevenbergMarquardt & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptMethodLevenbergMarquardt(const COptMethodLevenbergMarquardt & src,
                                 const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~COptMethodLevenbergMarquardt();

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
    COptMethodLevenbergMarquardt(const CCopasiContainer * pParent = NULL);

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
    bool evaluate();

    /**
     * Calculate the gradient of the objective at the current parameters
     */
    void gradient();

    /**
     * Calculate the gradient of the objective at the point p
     */
    void gradientP(const CVector< C_FLOAT64 > &point);

    /**
     * Calculate the Hessian of the objective at the point p
     */
    void hessian(CVector< C_FLOAT64 > &point);

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
     * The current solution guess
     */
    CVector< C_FLOAT64 > mCurrent;

    /**
     * The last individual
     */
    CVector< C_FLOAT64 > mOld;

    /**
     * The gradient
     */
    CVector< C_FLOAT64 > mGradient;

    /**
     * The step taken
     */
    CVector< C_FLOAT64 > mStep;

    /**
     * The Hessian matrix
     */
    CMatrix<C_FLOAT64> mHessian;

    /**
     * Vector for temporary values
     */
    CVector< C_FLOAT64 > mTemp;

    /**
     * The last best value
     */
    C_FLOAT64 mOldValue;

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

#endif  // COPASI_COptMethodLevenbergMarquardt
