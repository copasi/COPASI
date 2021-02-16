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

#ifndef COPASI_COptMethodSteepestDescent
#define COPASI_COptMethodSteepestDescent

#include "copasi/core/CVector.h"
#include "copasi/optimization/COptMethod.h"

class FDescent;

class COptMethodSteepestDescent: public COptMethod
{
  // Operations
private:
  /**
   * Default constructor.
   */
  COptMethodSteepestDescent();

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
   * Evaluate the objective function for the current parameters
   * @return const C_FLOAT64 & objectiveValue
   */
  const C_FLOAT64 & evaluate();

  /**
   * Calculate the gradient of the objective at the current parameters
   */
  void gradient();

  /**
   * Descent int the direction of the gradient with step x
   * and evaluate the objective function
   * @param const C_FLOAT64 & x
   * @return const C_FLOAT64 objectiveValue
   */
  C_FLOAT64 descentLine(const C_FLOAT64 & x);

  /**
      * Initialize contained objects.
      */
  void initObjects();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: SteepestDescent)
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  COptMethodSteepestDescent(const CDataContainer * pParent,
                            const CTaskEnum::Method & methodType = CTaskEnum::Method::SteepestDescent,
                            const CTaskEnum::Task & taskType = CTaskEnum::Task::optimization);

  /**
   * Copy Constructor
   * @param const COptMethodSteepestDescent & src
   */
  COptMethodSteepestDescent(const COptMethodSteepestDescent& src,
                            const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~COptMethodSteepestDescent();

  /**
   * Execute the optimization algorithm calling simulation routine
   * when needed. It is noted that this procedure can give feedback
   * of its progress by the callback function set with SetCallback.
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

private :

  // variables

  /**
   * The maximum number of iterations.
   */
  unsigned C_INT32 mIterations;

  /**
   * The tolerance
   */
  C_FLOAT64 mTolerance;   // length of steps taken

  /**
   * Indicates whether there the executions shall continue
   */
  bool mContinue;

  /**
   * The best value found so far.
   */
  C_FLOAT64 mBestValue;

  /**
      * array of values of objective function f/ individuals
      */
  C_FLOAT64 mValue;

  /**
   * number of parameters
   */
  size_t mVariableSize;

  /**
   * A vector of parameters of the current individual
   */
  CVector < C_FLOAT64 > mIndividual;

  /**
   * The gradient vector for the objective function
   */
  CVector < C_FLOAT64 > mGradient;

  /**
   * Functor pointing to the descent method.
   */
  FDescent * mpDescent;

  /**
      * The current iteration
      */
  unsigned C_INT32 mCurrentIteration;
};

#endif  // COPASI_COptMethodSteepestDescent
