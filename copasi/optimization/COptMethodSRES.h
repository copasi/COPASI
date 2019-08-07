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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_COptMethodSRES
#define COPASI_COptMethodSRES

#include "copasi/core/CVector.h"
#include "copasi/optimization/COptPopulationMethod.h"

class CRandom;

/**
 * COptMethodSRES class
 */

class COptMethodSRES : public COptPopulationMethod
{
  // Operations
public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: SRES)
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  COptMethodSRES(const CDataContainer * pParent,
                 const CTaskEnum::Method & methodType = CTaskEnum::Method::SRES,
                 const CTaskEnum::Task & taskType = CTaskEnum::Task::optimization);

  /**
   * Copy Constructor
   * @param const COptMethodSRES & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  COptMethodSRES(const COptMethodSRES & src,
                 const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~COptMethodSRES();

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
  COptMethodSRES();

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
   * Replicate the individuals with crossover
   * @return bool continue
   */
  bool replicate();

  /**
   * Mutate the new generation
   */
  bool mutate();

  /**
   * Select surviving population
   * @return success
   */
  void select();

  /**
   * Find the best individual at this generation
   * @return size_t fittest
   */
  size_t fittest();

  /**
   * Initialise the population
   * @param size_t first
   * @return bool continue
   */
  bool creation(size_t first);

  /**
   * For Stochastic Ranking, evaluate the distance of parameters to boundaries
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
   * for array of variances w/ variance values for the parameters
   */
  std::vector< CVector < C_FLOAT64 > * > mVariance;

  /**
   * A vector of maximal variances
   */
  CVector < C_FLOAT64 > mMaxVariance;

  /**
  * if no improvement was made after # stalled generations
  * stop
  */
  unsigned C_INT32 mStopAfterStalledGenerations;

  /**
   * The value of the last evaluation.
   */
  C_FLOAT64 mEvaluationValue;

  C_FLOAT64 mBestValue;

  double mTau;    // parameter for updating variances

  double mTauPrime;    // parameter for updating variances
};

#endif  // COPASI_COptMethodSRES
