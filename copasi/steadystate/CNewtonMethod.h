/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CNewtonMethod.h,v $
   $Revision: 1.19 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/02 11:52:02 $
   End CVS Header */

/**
 *  CNewtonMethod class.
 *  This class implements the enhanced Newton method which attempts to find the
 *  the steady state.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CNewtonMethod
#define COPASI_CNewtonMethod

#include "utilities/CMatrix.h"
#include "utilities/CVector.h"
#include "model/CState.h"

class CNewtonMethod : public CSteadyStateMethod
  {
    friend CSteadyStateMethod *
    CSteadyStateMethod::createSteadyStateMethod(CCopasiMethod::SubType subType);

    // Attributes
  private:
    enum NewtonReturnCode
    {
      found = 0,
      notFound,
      iterationLimitExceeded,
      dampingLimitExceeded,
      singularJacobian
    };

    bool mUseNewton;
    bool mUseIntegration;
    bool mUseBackIntegration;
    bool mAcceptNegative;
    C_INT32 mIterationLimit;

    C_FLOAT64 mFactor;
    C_FLOAT64 mResolution;
    C_FLOAT64 mScaledResolution;
    C_INT mDimension;
    //C_FLOAT64 mMaxrate;
    CVector< C_FLOAT64 > * mX;
    CVector< C_FLOAT64 > mH;
    CVector< C_FLOAT64 > mXold;
    CVector< C_FLOAT64 > mdxdt;
    //CMatrix< C_FLOAT64 > mJacobianX;
    C_INT * mIpiv;

    //CStateX mStateX;
    CStateX mInitialStateX;

    // Operations
  private:
    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CNewtonMethod(const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Copy constructor.
     * @param "const CNewtonMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CNewtonMethod(const CNewtonMethod & src,
                  const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CNewtonMethod();

    /**
     * Load a list of parameters
     * @param "CReadConfig &" configBuffer
     * @param "CReadConfig::Mode" mode Default(CReadConfig::SEARCH)
     */
    virtual void load(CReadConfig & configBuffer,
                      CReadConfig::Mode mode = CReadConfig::SEARCH);

    /**
     * This instructs the method to calculate a the steady state
     * starting with the initialState given.
     * The steady state is returned in the object pointed to by steadyState.
     * @param CState & steadyState
     * @param const CState & initialState
     * @return CSteadyStateMethod::ReturnCode returnCode
     */
    virtual CSteadyStateMethod::ReturnCode processInternal();

    bool isSteadyState(C_FLOAT64 value);

    /**
     * This is the function that is supposed to be near zero if a steady 
     * state is detected.
     * @param const CVector< C_FLOAT64 > & particlefluxes
     */
    C_FLOAT64 targetFunction(const CVector< C_FLOAT64 > & particlefluxes) const;

    /**
     * Check if the method is suitable for this problem
     * @return bool suitability of the method
     */
    virtual bool isValidProblem(const CCopasiProblem * pProblem);

  private:
    /**
     * This instructs the method to calculate a the steady state
     * starting with the initialState given.
     * The steady state is returned in the object pointed to by steadyState.
     * @param CState * steadyState
     * @param const CState * initialState
     * @return CNewtonMethod::NewtonReturnCode newtonReturnCode
     */
    CNewtonMethod::NewtonReturnCode processNewton();

    bool allPositive() const;
    bool containsNaN() const;

    CNewtonMethod::NewtonReturnCode
    returnNewton(const CNewtonMethod::NewtonReturnCode & returnCode);

    void cleanup();
  };
#endif // COPASI_CNewtonMethod
