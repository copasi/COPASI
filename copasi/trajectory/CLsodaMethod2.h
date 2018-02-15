// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CLsodaMethod2
#define COPASI_CLsodaMethod2

#include <sstream>

#include "copasi/core/CVector.h"
#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/odepack++/CLSODA.h"
#include "copasi/trajectory/CRootFinder.h"

class CModel;

class CLsodaMethod2 : public CTrajectoryMethod
{
public:
  struct Data
  {
    C_INT dim;
    CLsodaMethod2 * pMethod;
  };

private:

  struct State
  {
    CVector< C_FLOAT64 > ContainerState;
    CVector< C_FLOAT64 > DWork;
    CVector< C_INT > IWork;
    CVector< C_INT > RootsFound;
    CInternalSolver::State LsodaState;
    CTrajectoryMethod::Status Status;
  };
private:
  /**
   * Constructor.
   */
  CLsodaMethod2();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: LSODA2)
   * @param const CTaskEnum::Task & taskType (default: timeCourse)
   */
  CLsodaMethod2(const CDataContainer * pParent,
                const CTaskEnum::Method & methodType = CTaskEnum::Method::LSODA2,
                const CTaskEnum::Task & taskType = CTaskEnum::Task::timeCourse);

  /**
   * Copy constructor.
   * @param "const CLsodaMethod2 &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CLsodaMethod2(const CLsodaMethod2 & src,
                const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CLsodaMethod2();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  /**
   * Inform the trajectory method that the state has changed outside
   * its control
   * @param const CMath::StateChange & change
   */
  virtual void stateChange(const CMath::StateChange & change);

  /**
   *  This instructs the method to calculate a time step of deltaT
   *  starting with the current state, i.e., the result of the previous
   *  step.
   *  The new state (after deltaT) is expected in the current state.
   *  The return value is the actual time step taken.
   *  @param "const double &" deltaT
   *  @return Status status
   */
  virtual CTrajectoryMethod::Status step(const double & deltaT);

  /**
   *  This instructs the method to prepare for integration
   */
  virtual void start();

  /**
   *  This evaluates the derivatives
   */
  static void EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

  virtual void evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

  /**
   *  This evaluates the roots
   */
  void evalRoot(const double & time, CVectorCore< C_FLOAT64 > & rootValues);

  /**
   *  This evaluates the Jacobian
   */
  static void EvalJ(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y,
                    const C_INT * ml, const C_INT * mu, C_FLOAT64 * pd, const C_INT * nRowPD);

  virtual void evalJ(const C_FLOAT64 * t, const C_FLOAT64 * y,
                     const C_INT * ml, const C_INT * mu, C_FLOAT64 * pd, const C_INT * nRowPD);

private:
  /**
   * Initialize the method parameter
   */
  void initializeParameter();

  /**
   * Peek ahead to detect simultaneous roots.
   */
  CTrajectoryMethod::Status peekAhead();

  void saveState();
  void resetState();

protected:
  /**
   * Create a mask which hides all roots being constant and zero.
   */
  void createRootMask();

  /**
   * Destroy the mask which hides all roots being constant and zero.
   */
  void destroyRootMask();

  // Method Parameter
  /**
   * A pointer to the value of "Relative Tolerance"
   */
  C_FLOAT64 * mpRelativeTolerance;

  /**
   * A pointer to the value of "Absolute Tolerance"
   */
  C_FLOAT64 * mpAbsoluteTolerance;

  /**
   * A pointer to the value of "Max Internal Steps"
   */
  unsigned C_INT32 * mpMaxInternalSteps;

  /**
   * A pointer to the value of "Max Internal Step Size"
   */
  C_FLOAT64 * mpMaxInternalStepSize;

protected:
  /**
   * mData.dim is the dimension of the ODE system.
   * mData.pMethod contains CLsodaMethod2 * this to be used in the static method EvalF
   */
  Data mData;

private:
  /**
   * Pointer to the array with left hand side values of the math container.
   */
  C_FLOAT64 * mpY;

  /**
   * Pointer to the array with right hand side values of the math container.
   */
  const C_FLOAT64 * mpYdot;

protected:
  /**
   *  Current time.
   */
  C_FLOAT64 mTime;

  /**
   *  LSODA state.
   */
  C_INT mLsodaStatus;

  /**
   * The state after the last successful integration step
   */
  CVector< C_FLOAT64 > mLastSuccessState;

  /**
   * A vector of absolute tolerances.
   */
  CVector< C_FLOAT64 > mAtol;

  /**
   * A pointer to the absolute tolerances excluding fixed event targets.
   */
  C_FLOAT64 * mpAtol;

  /**
   * Stream to capture LSODA error messages
   */
  std::ostringstream mErrorMsg;

  /**
   * The LSODA integrator
   */
  CLSODA mLSODA;

  /**
   * The task instructions to the integrator
   */
  C_INT mTask;

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
   * The roots of the math container
   */
  CVectorCore< C_FLOAT64 > mContainerRoots;

  /**
   * Number of roots
   */
  C_INT mNumRoots;

  /**
   * The root finder
   */
  CRootFinder mRootFinder;

  /**
   * A functor pointing to the call back method provided to the root finder.
   * The points to void CLsoda2::evalRoot(const double & time, CVectorCore< C_FLOAT64 > & rootValues)
   */
  CRootFinder::Eval * mpRootValueCalculator;

  /**
   * The current root values of the root finder (may include additional internal roots)
   */
  CVectorCore< C_FLOAT64 > mRoots;

  /**
   * A vector containing the root mask
   */
  CVector< C_INT > mRootMask;

  /**
   * The current root masking mode
   */
  CRootFinder::RootMasking mRootMasking;

private:
  /**
   * Store the targeted end time to determine whether the internal
   * step limit is exceeded.
   */
  C_FLOAT64 mTargetTime;

  /**
   * A Boolean indicating whether we are in peekAhead mode
   */
  bool mPeekAheadMode;

  State mSavedState;
  // Operations
};
#endif // COPASI_CLsodaMethod2
