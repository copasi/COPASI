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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *   CHybridMethod
 *
 *   This class implements an hybrid algorithm to simulate a biochemical
 *   system over time.
 *
 *   File name: CHybridMethod.h
 *   Author: Juergen Pahle
 *   Email: juergen.pahle@eml-r.villa-bosch.de
 *
 *   Last change: 15, December 2004
 *
 *   (C) European Media Lab 2003.
 */
/**
 *   Partition the system into a deterministic part and a stochastic part.
 *   That is, every reaction is either classified deterministic or
 *   stochastic. Deterministic reactions involve only those metabolites (on
 *   substrate and product side), which have a high particle number.
 *   Therefore it is legal to integrate this part of the system with e.g. a
 *   numerical integrator. The concentration and relative particle number
 *   change should be low enough, so that the probabilities of all the
 *   reactions in the system show only little changes. The stochastic
 *   reactions must be simulated with an exact stochastic method (e.g. next
 *   reaction method (Gibson)), because their firing changes the reaction
 *   probabilities in the system significantly.
 */
#ifndef COPASI_CHybridMethod
#define COPASI_CHybridMethod

/* INCLUDES ******************************************************************/
#include "copasi/trajectory/CTrajectoryMethod.h"
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "copasi/utilities/CVersion.h"
#include "copasi/utilities/CDependencyGraph.h"
#include "copasi/utilities/CIndexedPriorityQueue.h"
#include "copasi/core/CDataVector.h"
#include "copasi/core/CMatrix.h"

/* DEFINE ********************************************************************/
#define MAX_STEPS                    1000000
#define INT_EPSILON                  0.1
#define LOWER_STOCH_LIMIT            800 //800
#define UPPER_STOCH_LIMIT            1000 //1000
#define RUNGE_KUTTA_STEPSIZE         0.001
#define PARTITIONING_INTERVAL        1
#define OUTPUT_COUNTER               100
//#define DEFAULT_OUTPUT_FILE          "hybrid.output"
#define SUBTYPE                      1
#define USE_RANDOM_SEED              false
#define RANDOM_SEED                  1

/* CLASSES *******************************************************************/

class CMetab;
class CTrajectoryProblem;
class CVersion;
class CMathReaction;
class CRandom;
class CIndexedPriorityQueue;
class CDependencyGraph;

/**
 *   Element of the array mReactionFlags. The deterministic reactions are
 *   organized in a linked list to be able to iterate over them quickly.
 */
class CHybridStochFlag
{
public:
  size_t mIndex;
  size_t mValue;
  CHybridStochFlag * mpPrev;
  CHybridStochFlag * mpNext;

  // insert operator
  friend std::ostream & operator<<(std::ostream & os, const CHybridStochFlag & d);
};

/**
 *   Internal representation of the balances of each reaction. The index of
 *   each metabolite in the reaction is provided.
 */
class CHybridBalance
{
public:
  size_t mIndex;
  C_INT32 mMultiplicity;

  // insert operator
  friend std::ostream & operator<<(std::ostream & os, const CHybridBalance & d);
};

class CHybridMethod : public CTrajectoryMethod
{
private:
  /**
   * Constructor.
   */
  CHybridMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: hybrid)
   * @param const CTaskEnum::Task & taskType (default: timeCourse)
   */
  CHybridMethod(const CDataContainer * pParent,
                const CTaskEnum::Method & methodType = CTaskEnum::Method::hybrid,
                const CTaskEnum::Task & taskType = CTaskEnum::Task::timeCourse);

  /**
   * Copy constructor.
   * @param "const CHybridMethod &" src
   * @param const CDataContainer * pParent
   */
  CHybridMethod(const CHybridMethod & src,
                const CDataContainer * pParent);

  /**
   *   Destructor.
   */
  ~CHybridMethod();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  /**
   *  This instructs the method to calculate a time step of deltaT
   *  starting with the current state, i.e., the result of the previous
   *  step.
   *  The new state (after deltaT) is expected in the current state.
   *  The return value is the actual timestep taken.
   *  @param const double & deltaT
   *  @param const bool & final (default: false)
   *  @return Status status
   */
  virtual Status step(const double & deltaT, const bool & final = false);

  /**
   *  This instructs the method to prepare for integration
   */
  virtual void start();

  /**
  * Check if the method is suitable for this problem
  * @return bool suitability of the method
  */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

  /* PROTECTED METHODS *******************************************************/

protected:
  /**
   *   Cleans up memory, etc.
   */
  void cleanup();

  /* VIRTUAL METHODS *********************************************************/

  /**
   *  Simulates the system over the next interval of time. The current time
   *  and the end time of the current step() are given as arguments.
   *
   *  @param  currentTime A C_FLOAT64 specifying the current time
   *  @param  endTime A C_FLOAT64 specifying the end time of the step()
   *  @return A C_FLOAT giving the new time
   */
  C_FLOAT64 doSingleStep(C_FLOAT64 currentTime, C_FLOAT64 endTime);

  /* DETERMINISTIC STUFF *****************************************************/

  /**
   *   Integrates the deterministic reactions of the system over the
   *   specified time interval.
   *
   *   @param ds A C_FLOAT64 specifying the stepsize.
   */
  virtual void integrateDeterministicPart(C_FLOAT64 ds) = 0;

  /**
   *   Calculates the derivative of the system and writes it into the vector
   *   deriv. Length of deriv must be mNumVariableMetabs.
   *   CAUTION: Only deterministic reactions are taken into account. That is,
   *   this is only the derivative of the deterministic part of the system.
   *
   *   @param CVectorCore< C_FLOAT64 > & deriv
   */
  void calculateDerivative(CVectorCore< C_FLOAT64 > & deriv);

  /* STOCHASTIC STUFF ********************************************************/

  /**
   *   Find the reaction index and the reaction time of the stochastic (!)
   *   reaction with the lowest reaction time.
   *
   *   @param ds A reference to a C_FLOAT64. The putative reaction time for
   *             the first stochastic reaction is written into this variable.
   *   @param rIndex A reference to a size_t. The index of the first
   *                 stochastic reaction is written into this variable.
   */
  void getStochTimeAndIndex(C_FLOAT64 & ds, size_t & rIndex);

  /**
   *   Updates the priority queue.
   *
   *   @param rIndex A size_t giving the index of the fired reaction
   *   @param time A C_FLOAT64 holding the time taken by this reaction
   */
  void updatePriorityQueue(size_t rIndex, C_FLOAT64 time);

  /**
   *   Generates a putative reaction time for the given reaction.
   *
   *   @param rIndex A size_t specifying the index of the reaction
   *   @return A C_FLOAT64 holding the calculated reaction time
   */
  C_FLOAT64 generateReactionTime(size_t rIndex);

  /**
   *   Updates the putative reaction time of a stochastic reaction in the
   *   priority queue. The corresponding amu and amu_old must be set prior to
   *   the call of this method.
   *
   *   @param rIndex A size_t specifying the index of the reaction
   *   @param time A C_FLOAT64 specifying the current time
   */
  void updateTauMu(size_t rIndex, C_FLOAT64 time);

  /* TESTING THE MODEL AND SETTING UP THINGS *********************************/

  /**
   *   Test the model if it is proper to perform stochastic simulations on.
   *   Several properties are tested (e.g. integer stoichometry, all
   *   reactions take place in one compartment only, irreversibility...).
   *
   *   @param model The model to be checked
   *   @return 1, if hybrid simulation is possible; <0, if an error occured.
   */
  static C_INT32 checkModel(CModel * model);

  /**
   *   Sets up the dependency graph
   */
  void setupDependencyGraph();

  /**
   *   Creates for each metabolite a set of reaction indices. If the
   *   metabolite participates in a reaction as substrate, product or
   *   modifier this reaction is added to the corresponding set.
   */
  void setupMetab2React();

  /**
   *   Creates an initial partitioning of the system. Deterministic and
   *   stochastic reactions are determined. The array mStochReactions is
   *   initialized.
   */
  void setupPartition();

  /**
   *   Sets up the priority queue.
   *
   *   @param startTime The time at which the simulation starts.
   */
  void setupPriorityQueue();

  /* HELPER METHODS **********************************************************/

  /**
   *   Updates the partitioning of the system depending on the particle
   *   numbers present.
   */
  void partitionSystem();

  /**
   *   Inserts a new deterministic reaction into the linked list in the
   *   vector mReactionFlags.
   *
   *   @param rIndex A size_t giving the index of the reaction to be
   *                 inserted into the list of deterministic reactions.
   */
  void insertDeterministicReaction(size_t rIndex);

  /**
   *   Removes a deterministic reaction from the linked list in the
   *   vector mReactionFlags.
   *
   *   @param rIndex A size_t giving the index of the reaction to be
   *                 removed from the list of deterministic reactions.
   */
  void removeDeterministicReaction(size_t rIndex);

  /* PRIVATE METHODS *********************************************************/

private:
  /**
   * Intialize the method parameter
   */
  void initializeParameter();

private:

  /* VARIABLES ***************************************************************/

public:

protected:

  /**
   *   Status of the metabolites. Particle number can be high or low.
   */
  enum metabStatus {LOW = 0, HIGH};

  /**
   *   Dimension of the system. Total number of metabolites.
   */
  size_t mNumVariableMetabs;

  /**
   *   index of the first metab in CState
   */
  size_t mFirstMetabIndex;
  const C_FLOAT64 * mpFirstMetabValue;

  /**
   *   Max number of doSingleStep() per step()
   */
  unsigned C_INT32 mMaxSteps;

  bool mMaxStepsReached;

  /**
   *   Specifies if the mRandomSeed should be used.
   *   otherwise a randomly chosen seed is used.
   */
  bool mUseRandomSeed;

  /**
   *  The random seed to use.
   */
  unsigned C_INT32 mRandomSeed;

  /**
   * maximal increase of a particle number in one step.
   */
  size_t mMaxBalance;

  /**
   * This is set to maxint - mMaxSteps*mMaxBalance
   */
  size_t mMaxIntBeforeStep;

  /**
   *   A pointer to the reactions of the model.
   */
  CVectorCore < CMathReaction > mReactions;

  /**
   *   Vectors to hold the system state and intermediate results
   */
  CVectorCore< C_FLOAT64 > mCurrentState;

  CVectorCore< C_FLOAT64 > mSpeciesRates;
  size_t mRateOffset;

  /**
   * A vector containing the update sequence required to update all propensity values.
   */
  CVector< CCore::CUpdateSequence > mUpdateSequences;

  /**
   *   Vector to hold information about how many metabolites of a reaction
   *   have low particle numbers. If no metabolite of one reaction has
   *   low particle numbers this reaction will be simulated det.
   */
  std::vector <CHybridStochFlag> mReactionFlags;
  CHybridStochFlag * mFirstReactionFlag;

  /**
   *   Vector holding information on the status of metabolites. They can
   *   have low or high particle numbers.
   */
  CVector< metabStatus > mMetabFlags;

  /**
  *   Limit for particle numbers. If a particle number is < StochLimit the
  *   corresponding reactions must be simulated stochastically.
  */
  C_FLOAT64 mLowerStochLimit;
  C_FLOAT64 mUpperStochLimit;

  /**
   *   The system gets repartitioned after this number of elementary steps.
   */
  unsigned C_INT32 mPartitioningInterval;

  /**
   *   Number of elementary steps after the last partitioning.
   */
  size_t mStepsAfterPartitionSystem;

  /**
   *   Vector of relations between metabolites to reactions.
   */
  std::vector <std::set <size_t> > mMetab2React;

  /**
   *   The propensities of the stochastic reactions.
   */
  std::vector <C_FLOAT64> mAmu;
  std::vector <C_FLOAT64> mAmuOld;

  /**
   *   The random number generator.
   */
  CRandom * mpRandomGenerator;

  /**
   *   The graph of reactions and their dependent reactions. When a reaction is
   *   executed, the propensities for each of its dependents must be updated.
   */
  CDependencyGraph mDG;

  /**
   *   The set of putative stochastic (!) reactions and associated times at
   *   which each reaction occurs. This is represented as a priority queue,
   *   sorted by the reaction time. This heap changes dynamically as
   *   stochastic reactions become deterministic (delete this reaction from
   *   the queue) or vice versa (insert a new reaction into the queue).
   */
  CIndexedPriorityQueue mPQ;

private:
};

#endif // COPASI_CHybridMethod
