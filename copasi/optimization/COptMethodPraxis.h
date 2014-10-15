// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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
#include "utilities/CMatrix.h"
#include "optimization/COptMethod.h"

#include "CPraxis.h"

class FPraxis;
class CPraxis;

class COptMethodPraxis: public COptMethod
{
  // Operations
public:
  /**
   * Specific constructor
   * @param const CCopasiContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: Praxis)
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  COptMethodPraxis(const CCopasiContainer * pParent,
                   const CTaskEnum::Method & methodType = CTaskEnum::Praxis,
                   const CTaskEnum::Task & taskType = CTaskEnum::optimization);

  /**
   * Copy Constructor
   * @param const COptMethodPraxis & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  COptMethodPraxis(const COptMethodPraxis & src,
                   const CCopasiContainer * pParent = NULL);

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
  virtual bool optimise();

private:
  /**
   * Default Constructor
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  COptMethodPraxis(const CCopasiContainer * pParent = NULL);

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
   * The tolerance
   */
  C_FLOAT64 mTolerance;

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
  C_INT mVariableSize;

  /**
   * The current solution guess
   */
  CVector< C_FLOAT64 > mCurrent;

  /**
   * The last individual
   */
  CVector< C_FLOAT64 > mBest;

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
   * Functor pointing to the Praxis method.
   */
  FPraxis * mpPraxis;

  /**
   * CPraxis function.
   */
  CPraxis * mpCPraxis;

  const C_FLOAT64 & evaluateFunction(C_FLOAT64 *, C_INT *);

  /**
   * Evaluate the objective function
   * @return bool continue
   */
  const C_FLOAT64 & evaluate();
};

#endif  // COPASI_COptMethodPraxis
