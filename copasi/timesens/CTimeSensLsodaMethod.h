// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CTimeSensLsodaMethod
#define COPASI_CTimeSensLsodaMethod

#include <sstream>

#include "copasi/core/CVector.h"
#include "copasi/timesens/CTimeSensMethod.h"
#include "copasi/odepack++/CLSODA.h"
#include "copasi/odepack++/CLSODAR.h"
#include "copasi/model/CState.h"

class CModel;

class CTimeSensLsodaMethod : public CTimeSensMethod
{
public:
  struct Data
  {
    C_INT dim;
    CTimeSensLsodaMethod * pMethod;
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
    CTimeSensMethod::Status Status;
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
   * A pointer to the value of "Max Internal Step Size"
   */
  C_FLOAT64 * mpMaxInternalStepSize;

protected:
  /**
   * mData.dim is the dimension of the ODE system.
   * mData.pMethod contains CTimeSensLsodaMethod * this to be used in the static method EvalF
   */
  Data mData;

private:
  /**
   * Pointer to the array with left hand side values of the math container.
   */
  //C_FLOAT64 * mpY;

  /**
   * the vector that contains the extended system
   */
  CVector< C_FLOAT64 > mVariables;

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

private:
  /**
   * A vector of absolute tolerances.
   */
  CVector< C_FLOAT64 > mAtol;

  /**
   * A pointer to the absolute tolerances excluding fixed event targets.
   */
  //C_FLOAT64 * mpAtol;

  /**
   * Stream to capture LSODA error messages
   */
  std::ostringstream mErrorMsg;

  /**
   * The LSODA integrator
   */
  CLSODA mLSODA;

  /**
   * The LSODA integrator
   */
  CLSODAR mLSODAR;

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
  CTimeSensLsodaMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: deterministic)
   * @param const CTaskEnum::Task & taskType (default: timeCourse)
   */
  CTimeSensLsodaMethod(const CDataContainer * pParent,
               const CTaskEnum::Method & methodType = CTaskEnum::Method::deterministic,
               const CTaskEnum::Task & taskType = CTaskEnum::Task::timeCourse);

  /**
   * Copy constructor.
   * @param "const CTimeSensLsodaMethod &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CTimeSensLsodaMethod(const CTimeSensLsodaMethod & src,
               const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CTimeSensLsodaMethod();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  bool elevateChildren() override;

  /**
   * Inform the trajectory method that the state has changed outside
   * its control
   * @param const CMath::StateChange & change
   */
  void stateChange(const CMath::StateChange & change) override;

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
  Status step(const double & deltaT, const bool & final = false) override;

  /**
   *  This instructs the method to prepare for integration
   */
  void start() override;

  /**
   *  This evaluates the derivatives
   */
  static void EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

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
                    const C_INT * ml, const C_INT * mu, C_FLOAT64 * pd, const C_INT * nRowPD);

  virtual void evalJ(const C_FLOAT64 * t, const C_FLOAT64 * y,
                     const C_INT * ml, const C_INT * mu, C_FLOAT64 * pd, const C_INT * nRowPD);

  /**
   * copies the sensitivity values from the state vector to the (annotated) result matrix
   */
  void copySensitivitiesToResultMatrix() override;

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
  CTimeSensMethod::Status peekAhead();

  bool hasStateChanged(const CVectorCore< C_FLOAT64 > & startState) const;
  void saveState(State & state, const CTimeSensMethod::Status & status) const;
  void resetState(State & state);

protected:
  /**
   * Destroy the mask which hides all roots being constant and zero.
   */
  void destroyRootMask();
};
#endif // COPASI_CTimeSensLsodaMethod
