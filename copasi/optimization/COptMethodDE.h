// Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 * COptMethodDE class
 */

#ifndef COPASI_COptMethodDE
#define COPASI_COptMethodDE
#include <limits>

#include "optimization/COptMethod.h"
#include "utilities/CVector.h"

class CRandom;
class CPermutation;

class COptMethodDE : public COptMethod
{
  friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

  // Operations
public:
  /**
   * Copy Constructor
   * @param const COptMethodDE & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  COptMethodDE(const COptMethodDE & src,
               const CCopasiContainer * pParent = NULL);

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

private:
  /**
   * Default Constructor
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  COptMethodDE(const CCopasiContainer * pParent = NULL);

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
   * number of parameters
   */
  size_t mVariableSize;

  /**
   * for array of individuals w/ candidate values for the parameters
   */
  std::vector< CVector < C_FLOAT64 > * > mIndividual;

  /**
   * A permutation of integers used to for replication;
   */
  CPermutation * mpPermutation;

  /**
    * The value of the last evaluation.
    */
  C_FLOAT64 mEvaluationValue;

  /**
   * array of values of objective function f/ individuals
   */
  CVector< C_FLOAT64 > mValue;

  /**
   * variance for mutations
   */
  C_FLOAT64 mMutationVarians;

  C_FLOAT64 mBestValue;
  size_t mBestIndex;
  unsigned C_INT32 mGeneration;
};

#endif  // COPASI_COptMethodDE
