// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
  * COptMethodLevenbergMarquardt class
  */

#ifndef COPASI_COptMethodLevenbergMarquardt
#define COPASI_COptMethodLevenbergMarquardt

#include <vector>

#include "copasi/core/CMatrix.h"
#include "copasi/optimization/COptMethod.h"

class CRandom;

class COptMethodLevenbergMarquardt : public COptMethod
{
  // Operations
public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: LevenbergMarquardt)
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  COptMethodLevenbergMarquardt(const CDataContainer * pParent,
                               const CTaskEnum::Method & methodType = CTaskEnum::Method::LevenbergMarquardt,
                               const CTaskEnum::Task & taskType = CTaskEnum::Task::optimization);

  /**
   * Copy Constructor
   * @param const COptMethodLevenbergMarquardt & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  COptMethodLevenbergMarquardt(const COptMethodLevenbergMarquardt & src,
                               const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~COptMethodLevenbergMarquardt();

  /**
   * Execute the optimization algorithm calling simulation routine
   * when needed. It is noted that this procedure can give feedback
   * of its progress by the callback function set with SetCallback.
   * @ return success;
   */
  virtual bool optimise();

  /**
   * Returns the maximum verbosity at which the method can log.
   */
  virtual unsigned C_INT32 getMaxLogVerbosity() const;

  virtual C_FLOAT64 getBestValue() const;

  virtual C_FLOAT64 getCurrentValue() const;

  virtual const CVector< C_FLOAT64 > * getBestParameters() const;

  virtual const CVector< C_FLOAT64 > * getCurrentParameters() const;

private:
  /**
   * Default Constructor
   */
  COptMethodLevenbergMarquardt();

  /**
   * Initialize contained objects.
   */
  void initObjects();

  /**
   * Initialize arrays and pointer.
   * @return bool success
   */
  virtual bool initialize();

  /**
   * Cleanup arrays and pointers.
   * @return bool success
   */
  virtual bool cleanup();

  /**
   * Evaluate the objective function
   * @return bool continue
   */
  const C_FLOAT64 & evaluate();

  /**
   * Calculate the gradient of the objective at the current parameters
   */
  void gradient();

  /**
   * Calculate the Hessian of the objective at the current point
   */
  void hessian();

  // Attributes
private:

  /**
     * The maximum number of iterations
     */
  unsigned C_INT32 mIterationLimit;

  /**
   * The tolerance
   */
  C_FLOAT64 mTolerance;

  /**
   * The modulation factor
   */
  C_FLOAT64 mModulation;

  /**
   * The number of iterations
   */
  unsigned C_INT32 mIteration;

  /**
   * Count of algorithm leaving parameter space
   */
  unsigned C_INT32 mParameterOutOfBounds;

  /**
   * Handle to the process report item "Current Iteration"
   */
  size_t mhIteration;

  /**
   * number of parameters
   */
  size_t mVariableSize;

  /**
   * The current solution guess
   */
  CVector< C_FLOAT64 > mCurrent;

  /**
   * The last individual
   */
  CVector< C_FLOAT64 > mBest;

  /**
   * The gradient
   */
  CVector< C_FLOAT64 > mGradient;

  /**
   * The step taken
   */
  CVector< C_FLOAT64 > mStep;

  /**
   * The Hessian matrix
   */
  CMatrix<C_FLOAT64> mHessian;

  /**
   * The Hessian matrix modified according to Levenberg-Marquardt
   */
  CMatrix<C_FLOAT64> mHessianLM;

  /**
   * Vector for temporary values
   */
  CVector< C_FLOAT64 > mTemp;

  /**
   * The best value found so far
   */
  C_FLOAT64 mBestValue;

  /**
   * The result of a function evaluation
   */
  C_FLOAT64 mEvaluationValue;

  /**
  * if no improvement was made after # stalled iterations
  * stop
  */
  unsigned C_INT32 mStopAfterStalledIterations;


  /**
   * Flag indicating whether the computation shall continue
   */
  bool mContinue;

  /**
   * Indicate whether we have access to the residuals, i.e., it is a
   * fitting problem we are working on.
   */
  bool mHaveResiduals;

  /**
   * The transpose jacobian of the residuals.
   */
  CMatrix< C_FLOAT64 > mResidualJacobianT;

  C_FLOAT64 mInitialLamda;
  C_FLOAT64 mLambdaUp;
  C_FLOAT64 mLambdaDown;

};

#endif  // COPASI_COptMethodLevenbergMarquardt
