/**
 *  CNewtonMethod class.
 *  This class implements the enhanced Newton method which attempts to find the
 *  the steady state.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CNewtonMethod
#define COPASI_CNewtonMethod

class CStateX;

class CNewtonMethod : private CSteadyStateMethod
  {
    friend CSteadyStateMethod *
    CSteadyStateMethod::createSteadyStateMethod(CSteadyStateMethod::Type type);

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
    C_INT32 mIterationLimit;

    C_FLOAT64 mFactor;
    C_FLOAT64 mResolution;
    C_INT32 mDimension;
    C_FLOAT64 mMaxrate;
    C_FLOAT64 * mX;
    C_FLOAT64 * mH;
    C_FLOAT64 * mXold;
    C_FLOAT64 * mdxdt;
    C_FLOAT64 * mJacobian;
    C_INT32 * mIpiv;

    // Operations
  private:
    /**
     *  Default constructor.
     */
    CNewtonMethod();

  public:
    /**
     *  Copy constructor.
     *  @param "const CNewtonMethod &" src
     */
    CNewtonMethod(const CNewtonMethod & src);

    /**
     *  Destructor.
     */
    ~CNewtonMethod();

    /**
     * This instructs the method to calculate a the steady state
     * starting with the initialState given.
     * The steady state is returned in the object pointed to by steadyState.
     * @param CState & steadyState
     * @param const CState & initialState
     * @return CSteadyStateMethod::ReturnCode returnCode
     */
    virtual CSteadyStateMethod::ReturnCode
    process(CState & steadyState,
            const CState & initialState);

  private:
    /**
     * This instructs the method to calculate a the steady state
     * starting with the initialState given.
     * The steady state is returned in the object pointed to by steadyState.
     * @param CState * steadyState
     * @param const CState * initialState
     * @return CNewtonMethod::NewtonReturnCode newtonReturnCode
     */
    CNewtonMethod::NewtonReturnCode processNewton(CState * steadyState,
        CState * initialState);

    CNewtonMethod::NewtonReturnCode
    returnNewton(const CNewtonMethod::NewtonReturnCode & returnCode,
                 CState * steadyState,
                 CState * initialState);

    bool isSteadyState();

    void cleanup();
  };
#endif // COPASI_CNewtonMethod
