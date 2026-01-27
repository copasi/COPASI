// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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
 * COptMethodNelderMead class
 */

#ifndef COPASI_COptMethodNelderMead
#define COPASI_COptMethodNelderMead

#include <vector>

#include "copasi/core/CMatrix.h"
#include "copasi/optimization/COptMethod.h"

class CRandom;

class COptMethodNelderMead : public COptMethod
{
  // Operations
public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: NelderMead)
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  COptMethodNelderMead(const CDataContainer * pParent,
                       const CTaskEnum::Method & methodType = CTaskEnum::Method::NelderMead,
                       const CTaskEnum::Task & taskType = CTaskEnum::Task::optimization);

  /**
   * Copy Constructor
   * @param const COptMethodNelderMead & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  COptMethodNelderMead(const COptMethodNelderMead & src,
                       const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~COptMethodNelderMead();

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
  COptMethodNelderMead();

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
   * The maximum number of iterations
   */
  unsigned C_INT32 mIterationLimit;

  /**
   * The tolerance
   */
  C_FLOAT64 mTolerance;

  /**
   * The scale
   */
  C_FLOAT64 mScale;

  /**
   * The number of iterations
   */
  unsigned C_INT32 mIteration;

  /**
   * Handle to the process report item "Current Iteration"
   */
  size_t mhIteration;

  /**
   * number of parameters
   */
  size_t mVariableSize;

  /**
   * The simplex
   */
  CMatrix< C_FLOAT64 > mSimplex;

  /**
   * Array of values of objective function for each corner of the simplex
   */
  CVector< C_FLOAT64 > mValue;

  /**
   * The centroid of the simplex
   */
  CVector <C_FLOAT64 > mCentroid;

  /**
   * The current solution guess
   */
  CVector< C_FLOAT64 > mCurrent;

  /**
   * The step taken
   */
  CVector< C_FLOAT64 > mStep;

  /**
   * The result of a function evaluation
   */
  C_FLOAT64 mEvaluationValue;
};

#endif  // COPASI_COptMethodNelderMead
