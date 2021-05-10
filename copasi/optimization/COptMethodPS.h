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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * COptMethodPS class
 */

#ifndef COPASI_COptMethodPS
#define COPASI_COptMethodPS

#include "copasi/core/CMatrix.h"
#include "copasi/core/CVector.h"
#include "copasi/optimization/COptPopulationMethod.h"

class CRandom;
class CPermutation;

class COptMethodPS : public COptPopulationMethod
{
  // Operations
public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: ParticleSwarm)
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  COptMethodPS(const CDataContainer * pParent,
               const CTaskEnum::Method & methodType = CTaskEnum::Method::ParticleSwarm,
               const CTaskEnum::Task & taskType = CTaskEnum::Task::optimization);

  /**
   * Copy Constructor
   * @param const COptMethodPS & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  COptMethodPS(const COptMethodPS & src,
               const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~COptMethodPS();

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
  COptMethodPS(const CDataContainer * pParent = NO_PARENT);

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
   * @return C_FLOAT64 value
   */
  C_FLOAT64 evaluate();

  /**
   * Move the indexed individual in the swarm
   * @param const size_t & index
   * @return bool continue
   */
  bool move(const size_t & index);

  /**
   * Create the indexed individual in the swarm
   * @param const size_t & index
   * @return bool continue
   */
  bool create(const size_t & index);

  /**
   * create the informant for each individual
   */
  void buildInformants();

  bool reachedStdDeviation();

  /**
   * Calculate the swarm variance of the function value
   * @return C_FLOAT64 variance
   */
  C_FLOAT64 calcFValVariance() const;

  /**
   * Calculate the swarm variance of a given parameter
   * @param const size_t & variable
   * @return C_FLOAT64 variance
   */
  C_FLOAT64 calcVariableVariance(const size_t & variable) const;

  /**
   * Create a status dump string containing html tables of parameter and variance information
   * @return std::string statusDump
   */
  std::string dumpStatus() const;

  // Attributes
private:

  // mIterationLimit -> mGenerations
  // mSwarmsize -> population
  // mIteration -> mCurrentGeneration

  /**
   * The variance acceptable for the solution
   */
  C_FLOAT64 mVariance;

  /**
   * Matrix of individual velocities
   */
  CMatrix< C_FLOAT64 > mVelocities;

  /**
   * The best value
   */
  C_FLOAT64 mBestValue;

  /**
   * Vector of individual best values.
   */
  CVector< C_FLOAT64 > mBestValues;

  /**
   * Matrix of best positions for each individual
   */
  CMatrix< C_FLOAT64 > mBestPositions;

  /**
   * The improvemets during one iteration
   */
  std::map< size_t, C_FLOAT64 > mImprovements;

  /**
   * A permutation of integers used to create the informants;
   */
  CPermutation * mpPermutation;

  /**
   * Vector containing the set of informants for each individual.
   */
  std::vector< std::set< size_t > > mInformants;

  /**
   * The minimal number of individuals informed by each individual
   */
  size_t mNumInformedMin;

  /**
   * The number of individual informed by each individual
   */
  size_t mNumInformed;

  /**
   * Index of the best solution found so far.
   */
  size_t mBestIndex;

  /**
  * if no improvement was made after # stalled iterations
  * stop
  */
  unsigned C_INT32 mStopAfterStalledIterations;

  /**
   * Indicates whether calculation shall continue
   */
  bool mContinue;
};

#endif  // COPASI_COptMethodPS
