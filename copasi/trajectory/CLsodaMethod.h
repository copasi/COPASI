/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CLsodaMethod.h,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/05/04 20:56:50 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CLsodaMethod
#define COPASI_CLsodaMethod

#include <sstream>
#include "utilities/CVector.h"

#include "CTrajectoryMethod.h"

#include "odepack++/CLSODA.h"

class CModel;
class CState;

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
    CState * mpState;

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
     * This methods must be called to elevate subgroups to
     * derived objects. The default implementation does nothing.
     * @return bool success
     */
    virtual bool elevateChildren();

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

    static void EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

    /**
     *  This evaluates the derivatives for the complete model
     */
    void evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

  private:
    /**
     * Intialize the method parameter
     */
    void initializeParameter();
  };
#endif // COPASI_CLsodaMethod
