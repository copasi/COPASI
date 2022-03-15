// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CNewtonMethod class.
 *  This class implements the enhanced Newton method which attempts to find the
 *  the steady state.
 *
 *  Created for COPASI by Stefan Hoops 2002
 */

#ifndef COPASI_CNewtonMethod
#define COPASI_CNewtonMethod

#include "copasi/core/CMatrix.h"
#include "copasi/core/CVector.h"

class CTrajectoryTask;

class CNewtonMethod : public CSteadyStateMethod
{
public:
  enum struct eTargetCriterion
  {
    DistanceAndRate,
    Distance,
    Rate,
    __SIZE
  };

  static const CEnumAnnotation< std::string, eTargetCriterion > TargetCriterion;

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
  unsigned C_INT32 mIterationLimit;
  C_FLOAT64 mMaxDurationForward;
  C_FLOAT64 mMaxDurationBackward;

  size_t mDimension;
  C_FLOAT64 * mpX;
  CVector< C_FLOAT64 > mH;
  CVector< C_FLOAT64 > mXold;
  CVectorCore< C_FLOAT64 > mdxdt;

  CTrajectoryTask * mpTrajectory;

  CVector< C_FLOAT64 > mStartState;

  CCore::CUpdateSequence mUpdateConcentrations;
  eTargetCriterion mTargetCriterion;
  C_FLOAT64 mTargetDistance;
  C_FLOAT64 mTargetRate;

  // Operations
private:
  /**
   * Default constructor.
   */
  CNewtonMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: Newton)
   * @param const CTaskEnum::Task & taskType (default: steadyState)
   */
  CNewtonMethod(const CDataContainer * pParent,
                const CTaskEnum::Method & methodType = CTaskEnum::Method::Newton,
                const CTaskEnum::Task & taskType = CTaskEnum::Task::steadyState);

  /**
  * Copy constructor.
  * @param "const CNewtonMethod &" src
  * @param const CDataContainer * pParent (default: NULL)
  */
  CNewtonMethod(const CNewtonMethod & src,
                const CDataContainer * pParent);

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

  bool isSteadyState(const C_FLOAT64 & value) const;

  /**
   * This is the function that is supposed to be near zero if a steady
   * state is detected.
   */
  C_FLOAT64 targetFunction();

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
   * Initialize the method parameter
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

  std::string targetValueToString() const;

  /**
   * This is the function that is supposed to be near zero if a steady
   * state is detected.
   */
  C_FLOAT64 targetFunctionRate();

  /**
   * This is the function that is supposed to be near zero if a steady
   * state is detected.
   */
  C_FLOAT64 targetFunctionDistance();

  void calculateDerivativesX();

  bool containsNaN() const;

  void cleanup();
};
#endif // COPASI_CNewtonMethod
