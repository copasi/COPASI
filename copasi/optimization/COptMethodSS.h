// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 * COptMethodSS class
 */

#ifndef COPASI_COptMethodSS
#define COPASI_COptMethodSS
#include <limits>

#include "optimization/COptMethod.h"
#include "optimization/COptProblem.h"
#include "utilities/CVector.h"

class CRandom;
//class COptMethodPraxis;

class COptMethodSS : public COptMethod
{
  friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

  // Operations
public:
  /**
   * Copy Constructor
   * @param const COptMethodSS & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  COptMethodSS(const COptMethodSS & src,
               const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  virtual ~COptMethodSS();

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
  COptMethodSS(const CCopasiContainer * pParent = NULL);

  /**
   * Serialize the pool for debug
   * @param size_t first
   * @param size_t last (default: pool size)
   * @return bool success
   */
  bool serializepool(size_t first, size_t last);

  /**
   * Serialize the refset for debug
   * @param size_t first
   * @param size_t last (default: population size)
   * @return bool success
   */
  bool serializerefset(C_INT32 first, C_INT32 last);

  /**
   * Serialize a vector to the refset file ,for debug
   * @param x the vector
   * @param xval function value for that vector
   * @return bool success
   */
  bool serializevector(CVector< C_FLOAT64 > x, C_FLOAT64 xval);

  /**
   * write informative messages about the refset
   * @param size_t type
   * @return bool success
   */
  bool inforefset(C_INT32 type, C_INT32 element);

  /**
   * Serialize the children for debug
   * @param size_t first
   * @param size_t last (default: population size)
   * @return bool success
   */
  bool serializechildren(size_t first, size_t last);

  /**
    * Serialize the probability table for debug
    * @return bool success
    */
  bool serializeprob(void);

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
   * Find a local minimum
   * @param CVector< C_FLOAT64 > & solution
   * @param C_FLOAT64 & fval
   * @return bool continue
   */
  bool localmin(CVector< C_FLOAT64 > & solution, C_FLOAT64 & fval);

  /**
   * minimize the best child if within criteria
   * @return bool continue
   */
  bool childLocalMin(void);

  /**
   * Initialise the population
   * @return bool continue
   */
  bool creation(void);

  /**
   * create new individuals with the combination method
   * @return bool continue
   */
  bool combination(void);

  /**
   * sort the RefSet array between position lower and upper
   */
  void sortRefSet(C_INT32 lower, C_INT32 upper);

  /**
   * randomize an element of the RefSet
   */
  bool randomize(C_INT32 i);

  /**
   * check if two vectors in RefSet are close
   */
  bool closerRefSet(C_INT32 i, C_INT32 j, C_FLOAT64 dist);

  /**
   * check if two child vectors are close
   * (one vector in mChild, the other in mPool, where previous child are stored)
   */
  bool closerChild(C_INT32 i, C_INT32 j, C_FLOAT64 dist);

  // Attributes
private:
  /**
   * Number of generations.
   */
  unsigned C_INT32 mIterations;

  /**
   * Size of the population (b in Rodriguez-Fernandez et al).
   */
  C_INT32 mPopulationSize;

  /**
   * Number of parameters.
   */
  unsigned C_INT32 mVariableSize;

  /**
   * Number of iterations between local searches.
   */
  unsigned C_INT32 mLocalFreq;

  /**
   * Counts iterations between local searches.
   */
  unsigned C_INT32 mLocalIter;

  /**
   * Number of local minimizations stored
   */
  unsigned C_INT32 mLocalStored;

  /**
   * True if there were children produced
   */
  bool mChildrenGenerated;

  /**
  * Array of candidate solutions in the RefSet.
  */
  std::vector< CVector < C_FLOAT64 > * > mRefSet;

  /**
   * Array of objective function values of the RefSet.
   */
  CVector< C_FLOAT64 > mRefSetVal;

  /**
   * Array of integers to count number of iterations that
   * candidate solutions have not changed in the RefSet.
   */
  CVector< C_INT32 > mStuck;

  /**
   * Array of children for the candidate solutions in the RefSet.
   */
  std::vector< CVector < C_FLOAT64 > * > mChild;

  /**
   * Array of objective function values of the Children.
   */
  CVector< C_FLOAT64 > mChildVal;

  /**
   * Pool of candidate solutions to be incorporated in RefSet
   * (S in Rodriguez-Fernandez et al.).
   */
  std::vector< CVector < C_FLOAT64 > * > mPool;

  /**
   * Function values of candidate solutions in the Pool.
   */
  CVector< C_FLOAT64 > mPoolVal;

  /**
   * Size of the Pool.
   */
  size_t mPoolSize;

  /**
   * Array to store frequencies.
   */
  std::vector< CVector < C_INT32 > * > mFreq;

  /**
   * Array to store probabilities.
   */
  CVector <C_FLOAT64> mProb;

  /**
    * The value of the last evaluation.
    */
  C_FLOAT64 mEvaluationValue;

  /**
    * Counter for iterations.
    */
  unsigned C_INT32 mIteration;

  /**
   * The best value so far
   */
  C_FLOAT64 mBestValue;

  /**
   * index of the best value so far
   */
  size_t mBestIndex;

  /**
   * Threshold to decide a solution is too close to another
   */
  C_FLOAT64 mCloseValue;

  /**
   * Handle to the process report item "Current Iteration".
   */
  size_t mhIterations;

  /**
   * a pointer to the randomnumber generator.
   */
  CRandom * mpRandom;

  /**
   * a pointer to an opt problem used for local minimization
   */
  COptProblem * mpOptProblemLocal;

  /**
   * a pointer to an opt method used for local minimization
   */
  COptMethod * mpLocalMinimizer;
};

#endif  // COPASI_COptMethodSS
