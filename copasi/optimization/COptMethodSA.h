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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * COptMethodSA class
 */

#ifndef COPASI_COptMethodSA
#define COPASI_COptMethodSA

#include <vector>

#include "copasi/core/CMatrix.h"
#include "copasi/optimization/COptMethod.h"

class CRandom;

class COptMethodSA : public COptMethod
{
  // Operations
public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: SimulatedAnnealing)
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  COptMethodSA(const CDataContainer * pParent,
               const CTaskEnum::Method & methodType = CTaskEnum::Method::SimulatedAnnealing,
               const CTaskEnum::Task & taskType = CTaskEnum::Task::optimization);

  /**
   * Copy Constructor
   * @param const COptMethodSA & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  COptMethodSA(const COptMethodSA & src,
               const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~COptMethodSA();

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
  COptMethodSA();

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

  // Attributes
private:

  /**
   * The current temperature
   */
  C_FLOAT64 mTemperature;

  /**
   * Handle to the process report item "Current Temperature"
   */
  size_t mhTemperature;

  /**
   * The cooling factor
   */
  C_FLOAT64 mCoolingFactor;

  /**
   * The tolerance
   */
  C_FLOAT64 mTolerance;

  /**
   * a pointer to the randomnumber generator.
   */
  CRandom * mpRandom {NULL};

  /**
   * number of parameters
   */
  size_t mVariableSize;

  /**
   * The best value found so far
   */
  C_FLOAT64 mBestValue;

  /**
   * The result of a function evaluation
   */
  C_FLOAT64 mEvaluationValue;

  /**
   * Flag indicating whether the computation shall continue
   */
  bool mContinue;

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

#endif  // COPASI_COptMethodSA
