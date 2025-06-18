// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 * COptMethodCoranaWalk class
 */

#ifndef COPASI_COptMethodCoranaWalk
#define COPASI_COptMethodCoranaWalk

#include <vector>

#include "copasi/core/CMatrix.h"
#include "copasi/optimization/COptMethod.h"

class CRandom;

class COptMethodCoranaWalk : public COptMethod
{
  // Operations
public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: CoranaWalk)
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  COptMethodCoranaWalk(const CDataContainer * pParent,
                       const CTaskEnum::Method & methodType = CTaskEnum::Method::CoranaWalk,
                       const CTaskEnum::Task & taskType = CTaskEnum::Task::optimization);

  /**
   * Copy Constructor
   * @param const COptMethodCoranaWalk & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  COptMethodCoranaWalk(const COptMethodCoranaWalk & src,
                       const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~COptMethodCoranaWalk();

  /**
   * Execute the optimization algorithm calling simulation routine
   * when needed. It is noted that this procedure can give feedback
   * of its progress by the callback function set with SetCallback.
   * @ return success;
   */
  bool optimise() override;

  /**
   * Returns the maximum verbosity at which the method can log.
   */
  unsigned C_INT32 getMaxLogVerbosity() const override;

  C_FLOAT64 getCurrentValue() const override;

  const CVector< C_FLOAT64 > * getBestParameters() const override;

  const CVector< C_FLOAT64 > * getCurrentParameters() const override;

private:
  /**
   * Default Constructor
   */
  COptMethodCoranaWalk();

  /**
   * Initialize contained objects.
   */
  void initObjects();

  /**
   * Initialize arrays and pointer.
   * @return bool success
   */
  bool initialize() override;

  /**
   * Cleanup arrays and pointers.
   * @return bool success
   */
  bool cleanup() override;

  // Attributes
private:

  /**
   * The current temperature
   */
  C_FLOAT64 mTemperature;

  /**
   * Handle to the process report item "iterations"
   */
  size_t mhIterations;

  /**
   * number of iterations
   */
  unsigned C_INT32 mIterations;

  /**
   * The current iteration
   */
  unsigned C_INT32 mCurrentIteration;

  /**
   * a pointer to the randomnumber generator.
   */
  CRandom * mpRandom {NULL};

  /**
   * number of parameters
   */
  size_t mVariableSize;

  /**
   * The result of a function evaluation
   */
  C_FLOAT64 mEvaluationValue;

  /**
   * The current solution guess
   */
  CVector< C_FLOAT64 > mCurrent;

  /**
   * The result of a function evaluation for mCurrent
   */
  C_FLOAT64 mCurrentValue;

  /**
   * The step taken
   */
  CVector< C_FLOAT64 > mStep;

  /**
   * The number of accepted steps
   */
  CVector< size_t > mAccepted;
};

#endif  // COPASI_COptMethodCoranaWalk
