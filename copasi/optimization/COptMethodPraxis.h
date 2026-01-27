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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
  * COptMethodPraxis class
  */

#ifndef COPASI_COptMethodPraxis
#define COPASI_COptMethodPraxis

#include <vector>

#include "copasi/core/CMatrix.h"
#include "copasi/optimization/COptMethod.h"

#include "copasi/optimization/CPraxis.h"

class FPraxis;
class CPraxis;

class COptMethodPraxis: public COptMethod
{
  // Operations
public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: Praxis)
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  COptMethodPraxis(const CDataContainer * pParent,
                   const CTaskEnum::Method & methodType = CTaskEnum::Method::Praxis,
                   const CTaskEnum::Task & taskType = CTaskEnum::Task::optimization);

  /**
   * Copy Constructor
   * @param const COptMethodPraxis & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  COptMethodPraxis(const COptMethodPraxis & src,
                   const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~COptMethodPraxis();

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
   * @param const CDataContainer * pParent (default: NULL)
   */
  COptMethodPraxis(const CDataContainer * pParent = NO_PARENT);

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

  /**
   * The tolerance
   */
  C_FLOAT64 mTolerance;

  /**
   * The count of tries within the tolerance of the best value
   */
  size_t mCountWithinTolerance;

  /**
   * The number of iterations
   */
  unsigned C_INT32 mIteration;

  /**
   * Handle to the process report item "Current Iteration"
   */
  unsigned C_INT32 mhIteration;

  /**
   * number of parameters
   */
  C_INT32 mVariableSize;

  /**
   * The current solution guess
   */
  CVector< C_FLOAT64 > mCurrent;

  /**
   * The last individual
   */
  CVector< C_FLOAT64 > mBest;

  /**
   * The result of a function evaluation
   */
  C_FLOAT64 mEvaluationValue;

  /**
   * Functor pointing to the Praxis method.
   */
  FPraxis * mpPraxis;

  /**
   * CPraxis function.
   */
  CPraxis mPraxis;

  const C_FLOAT64 & evaluateFunction(C_FLOAT64 *, C_INT32 &);
};

#endif  // COPASI_COptMethodPraxis
