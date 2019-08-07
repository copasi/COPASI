// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 * COptMethodSS class
 */

#ifndef COPASI_COptMethodSS
#define COPASI_COptMethodSS
#include <limits>

#include "copasi/core/CVector.h"
#include "copasi/optimization/COptPopulationMethod.h"
#include "copasi/optimization/COptProblem.h"

class CRandom;

class COptMethodSS : public COptPopulationMethod
{
  // Operations
public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: ScatterSearch)
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  COptMethodSS(const CDataContainer * pParent,
               const CTaskEnum::Method & methodType = CTaskEnum::Method::ScatterSearch,
               const CTaskEnum::Task & taskType = CTaskEnum::Task::optimization);

  /**
   * Copy Constructor
   * @param const COptMethodSS & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  COptMethodSS(const COptMethodSS & src,
               const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~COptMethodSS();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

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
   */
  COptMethodSS();

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

  // mIterations -> mGenerations
  // mRefSet -> mIndividuals
  // mRefSetVal -> mValues

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
  * if no improvement was made after # stalled generations
  * stop
  */
  unsigned C_INT32 mStopAfterStalledGenerations;

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
   * a pointer to an opt problem used for local minimization
   */
  COptProblem * mpOptProblemLocal {NULL};

  /**
   * a pointer to an opt method used for local minimization
   */
  COptMethod * mpLocalMinimizer {NULL};
};

#endif  // COPASI_COptMethodSS
