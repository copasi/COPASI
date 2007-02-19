// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/Attic/CTimeScaleSeparationMethod.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: isurovts $
//   $Date: 2007/02/19 13:47:34 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CTimeScaleSeparationMethod
#define COPASI_CTimeScaleSeparationMethod

#include <sstream>
#include "utilities/CVector.h"
#include "utilities/CMatrix.h"

#include "trajectory/CTrajectoryMethod.h"

#include "odepack++/CLSODA.h"

class CModel;
class CState;

class CTimeScaleSeparationMethod : public CTrajectoryMethod
  {
    friend CTrajectoryMethod *
    CTrajectoryMethod::createTrajectoryMethod(CCopasiMethod::SubType subType,
        CTrajectoryProblem * pProblem);

  public:
    struct Data
      {
        C_INT dim;
        CTimeScaleSeparationMethod * pMethod;
      };

    // Attributes
  private:
    /**
     *  A pointer to the current state in complete model view.
     */
    CState * mpState;

    /**
     * mData.dim is the dimension of the ODE system.
     */
    Data mData;

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
     *  Jacobian matrix
     */
    CMatrix <C_FLOAT64> mJacobian;

    /**
     *
     */
    CMatrix <C_FLOAT64> mQ;

    /**
     *
     */
    CMatrix <C_FLOAT64> mR;

    /**
     *
     */
    CMatrix <C_FLOAT64> mTd;

    /**
     *
     */
    CMatrix <C_FLOAT64> mTdInverse;

    /**
     *
     */
    CMatrix <C_FLOAT64> mQz;

    /**
     *
     */
    CVector<C_FLOAT64> mCfast;

    /**
     *
     */
    CMatrix<C_FLOAT64> mVslow;

    /**
     *
     */
    CMatrix<C_FLOAT64> mVslow_metab;

    /**
     *
     */
    CVector<C_FLOAT64> mVslow_space;

    /**
     *
     */
    C_INT mSlow;

    /**
     *  LSODA state.
     */
    C_INT mLsodaStatus;

    /**
     * Whether to use the reduced model
     */
    bool mReducedModel;

    /**
     * Relative tolerance.
     */
    C_FLOAT64 mRtol;

    /**
     * A vector of absolute tolerances.
     */
    CVector< C_FLOAT64 > mAtol;

    /**
     * Stream to capture LSODA error messages
     */
    std::ostringstream mErrorMsg;

    /**
     * The LSODA integrator
     */
    CLSODA mLSODA;

    /**
     * The state of the integrator
     */
    C_INT mState;

    /**
     * LSODA C_FLOAT64 work area
     */
    CVector< C_FLOAT64 > mDWork;

    /**
     * LSODA C_INT work area
     */
    CVector< C_INT > mIWork;

    /**
     * The way LSODA calculates the jacobian
     */
    C_INT mJType;

    /**
     * A pointer to the model
     */
    CModel * mpModel;

    /**
     *  Tolerance for Deuflhard criterium
     */
    C_FLOAT64 mDtol;

    /**
     *
     */
    C_FLOAT64 mEPS;

    // Operations
  private:
    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTimeScaleSeparationMethod(const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Copy constructor.
     * @param "const CTimeScaleSeparationMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTimeScaleSeparationMethod(const CTimeScaleSeparationMethod & src,
                               const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CTimeScaleSeparationMethod();

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
     **/
    virtual void integrationStep(const double & deltaT);

    /**
     *  This instructs the method to prepare for integration
     *  starting with the initialState given.
     *  @param "const CState *" initialState
     */
    virtual void start(const CState * initialState);

    /**
     * Calculate the individual absolute tolerance
     */
    void initializeAtol();

    static void EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

    /**
     *  This evaluates the derivatives
     */
    void evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

    /**
     *
     */
    void schur();

    /**
     *
     */
    void sylvester (C_INT slow, C_INT & info);

    /**
     *
     */
    void evalsort(C_FLOAT64 * reval, const C_INT & dim_x);

    /**
     *
     **/
    void map_index(C_FLOAT64 *eval_r, C_INT *index, const C_INT & dim);

    /**
     *
     **/
    void update_nid(C_INT *index, C_INT *nid, const C_INT & dim);

    /**
     *
     **/
    void update_pid(C_INT *index, C_INT *pid, const C_INT & dim);

    /**
     *
     **/
    void calculateDerivativesX(C_FLOAT64 * X1, C_FLOAT64 * Y1);

    /**
     *
     **/
    void newton(C_FLOAT64 *ys, C_INT & slow, C_INT & info);

    /**
     *
     **/

    void deuflhard(C_INT & slow, C_INT & info);

    /**
     *
     **/
    void mat_anal_mod(C_INT & slow);

    /**
     *
     **/
    void mat_anal_metab(C_INT & slow);

    /**
     *
     **/
    void mat_anal_mod_space(C_INT & slow);

  private:
    /**
     * Intialize the method parameter
     */
    void initializeParameter();
  };
#endif // COPASI_CTimeScaleSeparationMethod
