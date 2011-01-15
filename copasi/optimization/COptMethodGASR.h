/* Begin CVS Header
 $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodGASR.h,v $
 $Revision: 1.10.4.2 $
 $Name:  $
 $Author: gauges $
 $Date: 2011/01/15 14:01:32 $
 End CVS Header */

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * COptMethodGASR class
 */

#ifndef COPASI_COptMethodGASR
#define COPASI_COptMethodGASR

#include <limits>

#include "optimization/COptMethod.h"
#include "utilities/CVector.h"

class CRandom;

class COptMethodGASR : public COptMethod
{
  friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

  // Operations
public:
  /**
   * Copy Constructor
   * @param const COptMethodGASR & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  COptMethodGASR(const COptMethodGASR & src,
                 const CCopasiContainer * pParent = NULL);

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

private:
  /**
   * Default Constructor
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  COptMethodGASR(const CCopasiContainer * pParent = NULL);

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
   * Shuffle the parents for breading
   * @return bool success
   */
  bool shuffle();

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
   * number of generations
   */
  unsigned C_INT32 mGenerations;

  /**
   * Handle to the process report item "Current Generation"
   */
  size_t mhGenerations;

  /**
   * size of the population
   */
  unsigned C_INT32 mPopulationSize;

  /**
   * a pointer to the randomnumber generator.
   */
  CRandom * mpRandom;

  /**
   * Probability value used for SR ****
   */
  C_FLOAT64 mPf;

  /**
   * number of parameters
   */
  size_t mVariableSize;

  /**
   * for array of individuals w/ candidate values for the parameters
   */
  std::vector< CVector < C_FLOAT64 > * > mIndividual;

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
   * array of values of objective function f/ individuals
   */
  CVector< C_FLOAT64 > mValue;

  /**
   * indexes for shuffling the population
   */
  CVector< size_t > mShuffle;

  /**
   * number of wins of each individual in the tournament
   */
  CVector< size_t > mWins;

  /**
   * variance for mutations
   */
  C_FLOAT64 mMutationVarians;

  /**
   * The value of the last evaluation.
   */
  C_FLOAT64 mEvaluationValue;

  /**
   * The best value so far.
   */
  C_FLOAT64 mBestValue;
  size_t mBestIndex;
  unsigned C_INT32 mGeneration;
};

#endif  // COPASI_COptMethodGASR
