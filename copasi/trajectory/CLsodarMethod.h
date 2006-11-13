/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/Attic/CLsodarMethod.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/11/13 14:50:36 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CLsodarMethod
#define COPASI_CLsodarMethod

#include <sstream>
#include "utilities/CVector.h"

#include "trajectory/CTrajectoryMethod.h"

#include "odepack++/CLSODAR.h"

class CModel;
class CState;

class CLsodarMethod : public CTrajectoryMethod
  {
    friend CTrajectoryMethod *
    CTrajectoryMethod::createTrajectoryMethod(CCopasiMethod::SubType subType,
        CTrajectoryProblem * pProblem);

  public:
    struct Data
      {
        C_INT dim;
        CLsodarMethod * pMethod;
      };

    // Attributes
  private:
    /**
     *  A pointer to the current state in complete model view.
     */
    CState * mpState;

    /**
     * mData.dim is the dimension of the ODE system.
     * mData.pMethod contains CLsodarMethod * this to be used in the static method EvalF
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
     * Number of roots
     */
    C_INT mNumRoots;

    /**
     * Vector containing information on the current roots
     */
    CVector< C_INT > mRoots;

    /**
     *  Current time.
     */
    C_FLOAT64 mTime;

    /**
     *  LSODA state.
     */
    C_INT mLsodarStatus;

    /**
     * Whether to use the reduced model
     */
    bool mReducedModel;

    /**
     *  Relative tolerance.
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
    CLSODAR mLSODAR;

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
     * The way LSODAR calculates the jacobian
     */
    C_INT mJType;

    /**
     * A pointer to the model
     */
    CModel * mpModel;

    // Operations
  private:
    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CLsodarMethod(const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Copy constructor.
     * @param "const CLsodarMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CLsodarMethod(const CLsodarMethod & src,
                  const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CLsodarMethod();

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
     * Calculate the individual absolute tolerance
     */
    void initializeAtol();

    static void EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

    /**
     *  This evaluates the derivatives
     */
    void evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

    static void EvalR(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y,
                      const C_INT * nr, const double * r);
    /**
     *  This evaluates the roots
     */
    void evalR(const C_FLOAT64 * t, const C_FLOAT64 * y, const C_INT * nr, const double * r);

  private:
    /**
     * Intialize the method parameter
     */
    void initializeParameter();
  };
#endif // COPASI_CLsodarMethod
