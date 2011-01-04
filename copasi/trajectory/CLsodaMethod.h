/* Begin CVS Header
 $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CLsodaMethod.h,v $
 $Revision: 1.27.2.2 $
 $Name:  $
 $Author: shoops $
 $Date: 2011/01/04 13:53:09 $
 End CVS Header */

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CLsodaMethod
#define COPASI_CLsodaMethod

#include <sstream>

#include "copasi/utilities/CVector.h"
#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/odepack++/CLSODA.h"
#include "copasi/odepack++/CLSODAR.h"
#include "copasi/model/CState.h"

class CModel;

class CLsodaMethod : public CTrajectoryMethod
{
  friend CTrajectoryMethod *
  CTrajectoryMethod::createMethod(CCopasiMethod::SubType subType);

public:
  struct Data
  {
    C_INT dim;
    CLsodaMethod * pMethod;
  };

  // Attributes
protected:
  enum RootMasking
  {
    NONE = 0,
    ALL,
    DISCRETE
  };

  /**
   * A pointer to the value of "Integrate Reduced Model"
   */
  bool * mpReducedModel;

private:
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

protected:
  /**
   *  A pointer to the current state in complete model view.
   */
  CState mMethodState;

private:
  /**
   * mData.dim is the dimension of the ODE system.
   * mData.pMethod contains CLsodaMethod * this to be used in the static method EvalF
   */
  Data mData;

  /**
   *  Pointer to the array with left hand side values.
   */
  C_FLOAT64 * mY;

  /**
   * Vector containing the derivatives after calling eval
   */
  CVector< C_FLOAT64 > mYdot;

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

private:
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
   * The way LSODA calculates the jacobian
   */
  C_INT mJType;

protected:
  /**
   * A pointer to the model
   */
  CModel * mpModel;

  /**
   * A Boolean value indication whether we have no ODEs
   */
  bool mNoODE;

private:
  /**
   * A dummy variable if we do not have any ODEs
   */
  C_FLOAT64 mDummy;

  /**
   * A mask which hides all roots being constant and zero.
   */
  CVector< bool > mRootMask;

  /**
   * A which indicates whether roots change only discretely.
   */
  CVector< bool > mDiscreteRoots;

protected:
  /**
   * A Boolean flag indicating whether we should try masking roots
   */
  RootMasking mRootMasking;

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

  // Operations
protected:
  /**
   * Default constructor.
   * @param const CCopasiMethod::SubType & subType (default: deterministic)
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CLsodaMethod(const CCopasiMethod::SubType & subType = deterministic,
               const CCopasiContainer * pParent = NULL);

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
   * Inform the trajectory method that the state has changed outside
   * its control
   */
  virtual void stateChanged();

  /**
   *  This instructs the method to calculate a time step of deltaT
   *  starting with the current state, i.e., the result of the previous
   *  step.
   *  The new state (after deltaT) is expected in the current state.
   *  The return value is the actual time step taken.
   *  @param "const double &" deltaT
   *  @return Status status
   */
  virtual Status step(const double & deltaT);

  /**
   *  This instructs the method to prepare for integration
   *  starting with the initialState given.
   *  @param "const CState *" initialState
   */
  virtual void start(const CState * initialState);


  static void EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

  /**
   *  This evaluates the derivatives
   */
  virtual void evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

  static void EvalR(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y,
                    const C_INT * nr, C_FLOAT64 * r);
  /**
   *  This evaluates the roots
   */
  virtual void evalR(const C_FLOAT64 * t, const C_FLOAT64 * y, const C_INT * nr, C_FLOAT64 * r);

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

protected:
  /**
   * Destroy the mask which hides all roots being constant and zero.
   */
  void destroyRootMask();
};
#endif // COPASI_CLsodaMethod
