// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CRadau5Method
#define COPASI_CRadau5Method

#include <sstream>

#include "copasi/core/CVector.h"
#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/model/CState.h"

#include "copasi/odepack++/CRadau5.h"

class CModel;

class CRadau5Method : public CTrajectoryMethod
{
public:
  struct Data
  {
    C_INT dim;
    CRadau5Method * pMethod;
  };

  // Attributes
protected:
  enum eRootMasking
  {
    NONE = 0,
    ALL,
    DISCRETE
  };

private:

  struct State
  {
    CVector< C_FLOAT64 > ContainerState;
    CVector< C_FLOAT64 > DWork;
    CVector< C_INT > IWork;
    CVector< C_INT > RootsFound;
    CVector< bool > RootMask;
    eRootMasking RootMasking;
    CTrajectoryMethod::Status Status;
    CInternalSolver::State LsodaState;
  };

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
   * A pointer to the value of "Initial Step Size guess"
   */
  C_FLOAT64 * mpInitialStepSize;

protected:
  /**
   * mData.dim is the dimension of the ODE system.
   * mData.pMethod contains CRadau5Method * this to be used in the static method EvalF
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

  /**
   * Number of roots
   */
  C_INT mNumRoots;

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
   * The last state having a root
   */
  State mLastRootState;

  /* step size*/
  double H;

  /* scalar tolerances */
  C_INT ITOL;

  /* Jacobian flags */
  C_INT IJAC;
  C_INT MLJAC;
  C_INT MUJAC;

  /* differential equation is in explicit form*/
  C_INT IMAS;
  C_INT MLMAS;
  C_INT MUMAS;

  /* Output flag */
  C_INT IOUT = 0;

  /* length of work arrays */
  C_INT LWORK;
  C_INT LIWORK;

  /* optional parameters-- not used yet*/
  double rpar;
  C_INT idid;
  C_INT ipar;

  /* dummy function -- to pass for mass and EvalJ*/
  static void EvalM(C_INT *, double *, C_INT *, double *, C_INT *);

private:
  /**
   * A vector of absolute tolerances.
   */
  CVector< C_FLOAT64 > mAtol;

  /**
   * A pointer to the absolute tolerances excluding fixed event targets.
   */
  C_FLOAT64 * mpAtol;

  /**
   * A pointer to the relative tolerances excluding fixed event targets.
   */
  CVector< C_FLOAT64 > mRtol;

  /**
   * Stream to capture LSODA error messages
   */
  std::ostringstream mErrorMsg;

  /**
   * The RADAU5 integrator
   */
  CRadau5 mRADAU;

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

private:
  /**
   * A mask which hides all roots being constant and zero.
   */
  CVector< bool > mRootMask;

  /**
   * A which indicates whether roots change only discretely.
   */
  CVectorCore< bool > mDiscreteRoots;

protected:
  /**
   * A Boolean flag indicating whether we should try masking roots
   */
  eRootMasking mRootMasking;

private:
  /**
   * Store the targeted end time to determine whether the internal
   * step limit is exceeded.
   */
  C_FLOAT64 mTargetTime;

  /**
   * Root counter to determine whether the internal
   * step limit is exceeded.
   */
  unsigned C_INT32 mRootCounter;

  /**
   * A Boolean indicating whether we are in peekAhead mode
   */
  bool mPeekAheadMode;

  State mSavedState;
  // Operations
private:
  /**
   * Constructor.
   */
  CRadau5Method();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: RADAU5)
   * @param const CTaskEnum::Task & taskType (default: timeCourse)
   */
  CRadau5Method(const CDataContainer * pParent,
                const CTaskEnum::Method & methodType = CTaskEnum::Method::RADAU5,
                const CTaskEnum::Task & taskType = CTaskEnum::Task::timeCourse);

  /**
   * Copy constructor.
   * @param "const CRadau5Method &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CRadau5Method(const CRadau5Method & src,
                const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CRadau5Method();

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
   *  The return value is the actual timestep taken.
   *  @param const double & deltaT
   *  @param const bool & final (default: false)
   *  @return Status status
   */
  virtual Status step(const double & deltaT, const bool & final = false);

  /**
   *  This instructs the method to prepare for integration
   */
  virtual void start();

  /**
   *  This evaluates the derivatives
   */
  static void EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot, C_FLOAT64 *, C_INT *);

  virtual void evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

  /**
   *  This evaluates the roots
   */
  static void EvalR(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y,
                    const C_INT * nr, C_FLOAT64 * r);

  virtual void evalR(const C_FLOAT64 * t, const C_FLOAT64 * y, const C_INT * nr, C_FLOAT64 * r);

  /**
   *  This evaluates the Jacobian
   */
  static void EvalJ(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y,
                    double * ml, const C_INT * mu, C_FLOAT64 * pd, const C_INT * nRowPD);

  virtual void evalJ(const C_FLOAT64 * t, const C_FLOAT64 * y,
                     double * ml, const C_INT * mu, C_FLOAT64 * pd, const C_INT * nRowPD);

  /**
   *  This helps to output when automatic step size is selected
   */
  static void solout(C_INT * nr, double * xold, double * x, double * y, double * cont,
                     C_INT * lrc, C_INT * n, double * rpar, C_INT * ipar, C_INT * irtrn);

  virtual void output(const double *t);

private:
  /**
   * Initialize the method parameter
   */
  void initializeParameter();

  /**
   * Mask roots which are constant and zero.
   * @param CVectorCore< C_FLOAT64 > & rootValues
   */
  void maskRoots(CVectorCore< C_FLOAT64 > & rootValues);

  /**
   * Create a mask which hides all roots being constant and zero.
   */
  void createRootMask();

  /**
   * Set the root mask type and update the root mask accordingly
   */
  void setRootMaskType(const eRootMasking & maskType);

  /**
   * Peek ahead to detect simultaneous roots.
   */
  CTrajectoryMethod::Status peekAhead();

  bool hasStateChanged(const CVectorCore< C_FLOAT64 > & startState) const;
  void saveState(State & state, const CTrajectoryMethod::Status & status) const;
  void resetState(State & state);

protected:
  /**
   * Destroy the mask which hides all roots being constant and zero.
   */
  void destroyRootMask();
};
#endif // COPASI_CRadau5Method
