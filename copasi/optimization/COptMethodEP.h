// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#ifndef COPASI_COptMethodEP
#define COPASI_COptMethodEP

#include "copasi/core/CVector.h"
#include "copasi/optimization/COptPopulationMethod.h"

class CRandom;

class COptMethodEP: public COptPopulationMethod
{
  // Operations
private:

  /**
   * Default Constructor
   */
  COptMethodEP(const CDataContainer * pParent = NO_PARENT);

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
  bool evaluate(const CVector< C_FLOAT64 > & individual);

  /**
   * Initialize contained objects.
   */
  void initObjects();

  /**
   * Mutate one individual
   * @param CVector< C_FLOAT64 > & individual
   * @return bool success
   */
  bool mutate(size_t i);

  /**
   * Swap individuals from and to
   * @param size_t from
   * @param size_t to
   * @return bool success
   */
  bool swap(size_t from, size_t to);

  /**
   * Replicate the individuals with crossover
   * @return bool continue
   */
  bool replicate();

  /**
   * Select surviving population
   * @return bool success
   */
  bool select();

  /**
   * Find the best individual at this generation
   * @return size_t fittest
   */
  size_t fittest();

  /**
   * Initialize the population
   * @param size_t first
   * @param size_t last (default: population size)
   * @return bool continue
   */
  bool creation();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: EvolutionaryProgram)
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  COptMethodEP(const CDataContainer * pParent,
               const CTaskEnum::Method & methodType = CTaskEnum::Method::EvolutionaryProgram,
               const CTaskEnum::Task & taskType = CTaskEnum::Task::optimization);

  /**
   * Copy Constructor
   * @param const COptMethodEP & src
   */
  COptMethodEP(const COptMethodEP& src,
               const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~COptMethodEP();

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

private :
  // variables

  size_t mBestIndex;

  double tau1;    // parameter for updating variances

  double tau2;    // parameter for updating variances

  /**
   * number of wins of each individual in the tournament
   */
  CVector< size_t > mLosses;

  /**
   * The best value found so far.
   */
  C_FLOAT64 mBestValue;

  /**
   * The value of the last evaluation.
   */
  C_FLOAT64 mEvaluationValue;

  /**
  * if no improvement was made after # stalled generations
  * stop
  */
  unsigned C_INT32 mStopAfterStalledGenerations;

  /**
   * for array of variances w/ variance values for the parameters
   */
  std::vector< CVector < C_FLOAT64 > * > mVariance;

  /**
   * Pivot vector used for sorting
   */
  CVector<size_t> mPivot;
};

#endif  // COPASI_COptMethodEP
