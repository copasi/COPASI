// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CNewtonMethod.h,v $
//   $Revision: 1.28.6.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/10/23 14:11:18 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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

class CTrajectoryTask;

class CNewtonMethod : public CSteadyStateMethod
  {
    friend CSteadyStateMethod *
    CSteadyStateMethod::createSteadyStateMethod(CCopasiMethod::SubType subType);

    // Attributes
  private:
    enum NewtonResultCode
    {
      found = 0,
      notFound,
      iterationLimitExceeded,
      dampingLimitExceeded,
      singularJacobian,
      negativeValueFound,
      stepSuccesful
    };

    //these member variables contain configuration information, mostly they
    //are initialized from the CCopasiParameters
    bool mUseNewton;
    bool mUseIntegration;
    bool mUseBackIntegration;
    bool mAcceptNegative;
    bool mForceNewton;
    bool mKeepProtocol;
    C_INT32 mIterationLimit;
    C_FLOAT64 mMaxDurationForward;
    C_FLOAT64 mMaxDurationBackward;

    C_INT mDimension;
    C_FLOAT64 * mpX;
    CVector< C_FLOAT64 > mAtol;
    CVector< C_FLOAT64 > mH;
    CVector< C_FLOAT64 > mXold;
    CVector< C_FLOAT64 > mdxdt;
    C_INT * mIpiv;

    CTrajectoryTask * mpTrajectory;

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
     * This methods must be called to elevate subgroups to
     * derived objects. The default implementation does nothing.
     * @return bool success
     */
    virtual bool elevateChildren();

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

    /**
     * Initialize the method must be called before process
     * @param const CSteadyStateProblem * pProblem
     * @return bool success
     */
    virtual bool initialize(const CSteadyStateProblem * pProblem);

  private:
    /**
     * Intialize the method parameter
     */
    void initializeParameter();

    /**
     * This instructs the method to calculate a the steady state
     * starting with the initialState given.
     * The steady state is returned in the object pointed to by steadyState.
     * @param CState * steadyState
     * @param const CState * initialState
     * @return CNewtonMethod::NewtonReturnCode newtonReturnCode
     */
    CNewtonMethod::NewtonResultCode processNewton();

    /**
     * Do one newton step and subsequent damping. The value of the targetfunction
     * before the step is provided by the calling method in currentValue, the value after the step
     * is returned in currentValue.
     * The step starts from the state in mpX (pointing to the independent variables of mpSteadyState).
     * After the method returns mpX contains either the old state or the state after the step
     * (if the step was succesful). mdxdt can be expected to be up to date.
     * Possible return values are:  dampingLimitExceeded, singularJacobian, stepSuccesful
     */
    CNewtonMethod::NewtonResultCode doNewtonStep(C_FLOAT64 & currentValue);

    CNewtonMethod::NewtonResultCode doIntegration(bool forward);

    void calculateDerivativesX();

    bool containsNaN() const;

    void cleanup();
  };
#endif // COPASI_CNewtonMethod
