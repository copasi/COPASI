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

/**
 * COptMethodGASR class
 */

#ifndef COPASI_COptMethodGASR
#define COPASI_COptMethodGASR

#include <limits>

#include "copasi/core/CVector.h"
#include "copasi/optimization/COptPopulationMethod.h"

class CRandom;
class CPermutation;

class COptMethodGASR : public COptPopulationMethod
{
  // Operations
public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: GeneticAlgorithmSR)
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  COptMethodGASR(const CDataContainer * pParent,
                 const CTaskEnum::Method & methodType = CTaskEnum::Method::GeneticAlgorithmSR,
                 const CTaskEnum::Task & taskType = CTaskEnum::Task::optimization);

  /**
   * Copy Constructor
   * @param const COptMethodGASR & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  COptMethodGASR(const COptMethodGASR & src,
                 const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~COptMethodGASR();

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
   * @param const CDataContainer * pParent (default: NULL)
   */
  COptMethodGASR(const CDataContainer * pParent = NO_PARENT);

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
   * Swap individuals from and to
   * @param size_t from
   * @param size_t to
   * @return bool success
   */
  bool swap(size_t from, size_t to);

  /**
   * fm one individual
   * @param CVector< C_FLOAT64 > & individual
   * @return bool success
   */
  bool mutate(CVector< C_FLOAT64 > & individual);

  /**
   * @param const CVector< C_FLOAT64 > & parent1
   * @param const CVector< C_FLOAT64 > & parent2
   * @param CVector< C_FLOAT64 > & child1
   * @param CVector< C_FLOAT64 > & child2
   */
  bool crossover(const CVector< C_FLOAT64 > & parent1,
                 const CVector< C_FLOAT64 > & parent2,
                 CVector< C_FLOAT64 > & child1,
                 CVector< C_FLOAT64 > & child2);

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
   * Initialise the population
   * @param size_t first
   * @param size_t last (default: population size)
   * @return bool success
   */
  bool creation(size_t first, size_t last = std::numeric_limits<size_t>::max());

  /**
   * For Stochastic Ranking, evaluate the distance ofparameters to boundaries
   * @return C_FLOAT64 phiVal
   */
  C_FLOAT64 phi(size_t indvNum);

  // Attributes
private:

  /**
   * Probability value used for SR ****
   */
  C_FLOAT64 mPf;

  /**
   * For Stochastic Ranking.  Used for array of Phi values for the individuals
   */
  CVector < C_FLOAT64 > mPhi;

  /**
   * Vector used to initialize the crossover point to false
   */
  CVector< bool > mCrossOverFalse;

  /**
   * Vector of crossover points.
   */
  CVector< bool > mCrossOver;

  /**
   * A permutation of integers used to create the informants;
   */
  CPermutation * mpPermutation;

  /**
   * number of wins of each individual in the tournament
   */
  CVector< size_t > mWins;

  /**
   * variance for mutations
   */
  C_FLOAT64 mMutationVarians;

  /**
  * if no improvement was made after # stalled generations
  * stop
  */
  unsigned C_INT32 mStopAfterStalledGenerations;

  /**
   * The value of the last evaluation.
   */
  C_FLOAT64 mEvaluationValue;

  /**
   * The best value so far.
   */
  C_FLOAT64 mBestValue;
  size_t mBestIndex;
};

#endif  // COPASI_COptMethodGASR
