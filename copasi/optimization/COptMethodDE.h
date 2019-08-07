// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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
 * COptMethodDE class
 */

#ifndef COPASI_COptMethodDE
#define COPASI_COptMethodDE
#include <limits>

#include "copasi/core/CVector.h"
#include "copasi/optimization/COptPopulationMethod.h"

class CRandom;
class CPermutation;

class COptMethodDE : public COptPopulationMethod
{
  // Operations
public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: DifferentialEvolution)
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  COptMethodDE(const CDataContainer * pParent,
               const CTaskEnum::Method & methodType = CTaskEnum::Method::DifferentialEvolution,
               const CTaskEnum::Task & taskType = CTaskEnum::Task::optimization);

  /**
   * Copy Constructor
   * @param const COptMethodDE & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  COptMethodDE(const COptMethodDE & src,
               const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~COptMethodDE();

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

private:
  /**
   * Default Constructor
   */
  COptMethodDE();

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
   * @param const CVector< C_FLOAT64 > & individual
   * @return bool continue
   */
  bool evaluate(const CVector< C_FLOAT64 > & individual);

  /**
   * Replicate the individuals with crossover
   * @return bool continue
   */
  bool replicate();

  /**
   * Find the best individual at this generation
   * @return size_t fittest
   */
  size_t fittest();

  void boost();
  /**
   * Initialise the population
   * @param size_t first
   * @param size_t last (default: population size)
   * @return bool continue
   */
  bool creation(size_t first, size_t last = std::numeric_limits<size_t>::max());

  // Attributes
private:
  /**
   * A permutation of integers used to for replication;
   */
  CPermutation * mpPermutation;

  /**
    * The value of the last evaluation.
    */
  C_FLOAT64 mEvaluationValue;

  /**
   * variance for mutations
   */
  C_FLOAT64 mMutationVarians;

  /**
  * if no improvement was made after # stalled generations
  * stop
  */
  unsigned C_INT32 mStopAfterStalledGenerations;

  C_FLOAT64 mBestValue;
  size_t mBestIndex;
};

#endif  // COPASI_COptMethodDE
