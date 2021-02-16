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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * COptMethodHookeJeeves class
 */

#ifndef COPASI_COptMethodHookeJeeves
#define COPASI_COptMethodHookeJeeves

#include "copasi/core/CVector.h"
#include "copasi/optimization/COptMethod.h"

class CRandom;

class COptMethodHookeJeeves : public COptMethod
{
  // Operations

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: HookeJeeves)
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  COptMethodHookeJeeves(const CDataContainer * pParent,
                        const CTaskEnum::Method & methodType = CTaskEnum::Method::HookeJeeves,
                        const CTaskEnum::Task & taskType = CTaskEnum::Task::optimization);

  /**
   * Copy Constructor
   * @param const COptMethodHookeJeeves & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  COptMethodHookeJeeves(const COptMethodHookeJeeves & src,
                        const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~COptMethodHookeJeeves();

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
   * @param const CDataContainer * pParent (default: NULL)
   */
  COptMethodHookeJeeves(const CDataContainer * pParent = NO_PARENT);

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
   * Evaluate the fitness of one individual
   * @return bool continue
   */
  bool evaluate();

  /**
   * Finds the best value in the neighborhood of mNew and updates mNew
   * @return C_FLOAT64 bestValue
   */
  C_FLOAT64 bestNearby();

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
   * The length of steps taken
   */
  C_FLOAT64 mRho;

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
   * The current individual
   */
  CVector< C_FLOAT64 > mIndividual;

  /**
   * The last individual
   */
  CVector< C_FLOAT64 > mBefore;

  /**
   * The new individual
   */
  CVector< C_FLOAT64 > mNew;

  /**
   * The step taken
   */
  CVector< C_FLOAT64 > mDelta;

  /**
   * The value of the last evaluation.
   */
  C_FLOAT64 mEvaluationValue;

  /**
   * The best value found so far
   */
  C_FLOAT64 mBestValue;

  /**
   * Flag indicating whether the computation shall continue
   */
  bool mContinue;
};

#endif  // COPASI_COptMethodHookeJeeves
