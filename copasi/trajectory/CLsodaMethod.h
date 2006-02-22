/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CLsodaMethod.h,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/02/22 15:12:21 $
   End CVS Header */

#ifndef COPASI_CLsodaMethod
#define COPASI_CLsodaMethod

#include <sstream>
#include "utilities/CVector.h"

#include "odepack++/CLSODA.h"

class CModel;
class CState;
class CStateX;

class CLsodaMethod : public CTrajectoryMethod
  {
    friend CTrajectoryMethod *
    CTrajectoryMethod::createTrajectoryMethod(CCopasiMethod::SubType subType,
        CTrajectoryProblem * pProblem);

    // Attributes
  private:
    /**
     *  A pointer to the current state in complete model view.
     */
    CState * mpStateC;

    /**
     *  A pointer to the current state in reduced model view.
     */
    CStateX * mpStateR;

    /**
     * A pointer to the evaluation function to be used during integration
     */
    void (CLsodaMethod::*mpEval)(const C_FLOAT64 t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

    /**
     * mDim[0] is the dimension of the ODE system.
     * mDim[1] contains CLsodaMethod * this to be used in the static method EvalF
     * Note: this works only if sizeof(C_INT) == ptr_size;
     */
    C_INT mDim[2];

    /**
     *  Pointer to the array with left hand side values.
     */
    C_FLOAT64 * mY;

    /**
     * Vector containig the derivatives after calling eval
     */
    CVector< C_FLOAT64 > mYdot;

    /**
     *  Current time.
     */
    C_FLOAT64 mTime;

    /**
     *  Requested end time.
     */
    C_FLOAT64 mEndt;

    /**
     *  LSODA state.
     */
    C_INT mLsodaStatus;

    /**
     *
     */
    bool mReducedModel;

    /**
     *  Relative tolerance.
     */
    C_FLOAT64 mRtol;

    /**
     *
     */
    bool mDefaultAtol;

    /**
     *  Absolute tolerance.
     */
    C_FLOAT64 mAtol;

    /**
     *  Maximum order for BDF method.
     */ 
    //    C_INT32 mBDF;

    /**
     *  Maximum order for Adams method.
     */ 
    //    C_INT32 mAdams;

    /**
     *  Maximum number of steps for one call of lsoda.
     */ 
    //    C_INT32 mMaxSteps;

    /**
     *
     */
    std::ostringstream mErrorMsg;

    CLSODA mLSODA;
    C_INT mState;
    CVector< C_FLOAT64 > mDWork;
    CVector< C_INT > mIWork;
    C_INT mJType;

    // Operations
  private:
    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CLsodaMethod(const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Copy constructor.
     * @param "const CLsodaMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CLsodaMethod(const CLsodaMethod & src,
                 const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CLsodaMethod();

    /**
     *  This instructs the method to calculate a time step of deltaT
     *  starting with the current state, i.e., the result of the previous
     *  step.
     *  The new state (after deltaT) is expected in the current state.
     *  The return value is the actual timestep taken.
     *  @param "const double &" deltaT
     */
    virtual void step(const double & deltaT);

    /**
     *  This instructs the method to prepare for integration
     *  starting with the initialState given.
     *  @param "const CState *" initialState
     */
    virtual void start(const CState * initialState);

    /**
     * Calculate the default absolute tolerance
     * @param const CModel * pModel
     * @return C_FLOAT64 defaultAtol
     */
    C_FLOAT64 getDefaultAtol(const CModel * pModel) const;

    void evalF(const double * t, const double * y, double * ydot);

    static void EvalF(const C_INT * n, const double * t, const double * y, double * ydot);

  private:
    /**
     *  This evaluates the derivatives for the complete model
     */
    void evalC(const C_FLOAT64 t,
               const C_FLOAT64 * y,
               C_FLOAT64 * ydot);

    /**
     *  This evaluates the derivatives for the reduced model
     */
    void evalR(const C_FLOAT64 t,
               const C_FLOAT64 * y,
               C_FLOAT64 * ydot);
  };
#endif // COPASI_CLsodaMethod
