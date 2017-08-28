// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 *   CTrajectoryMethodDsaLsodar
 *
 *   This class implements an hybrid algorithm to simulate a biochemical
 *   system over time.
 *
 *   File name: CTrajectoryMethodDsaLsodar.h
 *   Author: Stefan Hoops
 *
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
#ifndef COPASI_CTrajectoryMethodDsaLsodar
#define COPASI_CTrajectoryMethodDsaLsodar

/* INCLUDES ******************************************************************/

#include "copasi/trajectory/CLsodaMethod.h"

#include "copasi/core/CDataVector.h"
#include "copasi/model/CState.h"

class CReaction;
class CMetab;
class CRandom;
class CMathReaction;

class CTrajectoryMethodDsaLsodar : public CLsodaMethod
{
private:

  class CPartition
  {
  public:
    typedef std::multimap< size_t, size_t * > speciesToReactionsMap;

    // Operations
    /**
     * Default constructor
     */
    CPartition();

    /**
     * Copy constructor
     * @param const CPartition & src
     */
    CPartition(const CPartition & src);

    /**
     * Destructor
     */
    ~CPartition();

    void intialize(const CMathContainer * pContainer,
                   const C_FLOAT64 & lowerThreshold,
                   const C_FLOAT64 & upperThreshold);

    bool rePartition(const CVectorCore< C_FLOAT64 > & state);

  public:
    // Attributes
    /**
     * A map from a species index to the indexes of the reactions it participates in
     */
    speciesToReactionsMap mSpeciesToReactions;

    /**
     * The threshold for switching to stochastic treatment
     */
    C_FLOAT64 mLowerThreshold;

    /**
     * The threshold for switching to deterministic treatment
     */
    C_FLOAT64 mUpperThreshold;

    /**
     * The index of the first species determined by reactions in the state
     */
    size_t mFirstReactionSpeciesIndex;

    /**
     * The number of species determined by reactions
     */
    size_t mNumReactionSpecies;

    /**
     * A vector containing pointers to stochastic reaction dependencies
     */
    CVector< const CMathReaction * > mStochasticReactions;

    /**
     * A vector containing pointers to stochastic reaction dependencies
     */
    CVector< const CMathReaction * > mDeterministicReactions;

    /**
     * A vector indicating whether a species is treated stochastically or not.
     */
    CVector< bool > mStochasticSpecies;

    /**
     * A Boolean flag indicating whether the system has stochastic reactions
     */
    bool mHasStochastic;

    /**
     * A Boolean flag indicating whether the system has deterministic reactions
     */
    bool mHasDeterministic;

    /**
     * A vector containing the number of low species for each reaction
     */
    CVector< size_t > mNumLowSpecies;

    /**
     * A pointer to the math container;
     */
    const CMathContainer * mpContainer;

    /**
     * A pointer to the first species determined by reactions
     */
    const C_FLOAT64 * mpFirstReactionValue;
  };

private:
  /**
   * Default constructor.
   */
  CTrajectoryMethodDsaLsodar();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: DsaLsodar)
   * @param const CTaskEnum::Task & taskType (default: timeCourse)
   */
  CTrajectoryMethodDsaLsodar(const CDataContainer * pParent,
                             const CTaskEnum::Method & methodType = CTaskEnum::Method::DsaLsodar,
                             const CTaskEnum::Task & taskType = CTaskEnum::Task::timeCourse);

  /**
   * Copy constructor
   * @param const CTrajectoryMethodDsaLsodar & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CTrajectoryMethodDsaLsodar(const CTrajectoryMethodDsaLsodar & src,
                             const CDataContainer * pParent);

  /**
   *   Destructor.
   */
  ~CTrajectoryMethodDsaLsodar();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  /**
   * Inform the trajectory method that the state has changed outside
   * its control
   * @param const CMath::StateChange & change
   */
  virtual void stateChange(const CMath::StateChange & change);

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
   *  starting with the initialState given.
   */
  virtual void start();

  /**
   *  This evaluates the derivatives
   */
  virtual void evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

  /**
   *  This evaluates the roots
   */
  virtual void evalR(const C_FLOAT64 * t, const C_FLOAT64 * y, const C_INT * nr, C_FLOAT64 * r);

  /**
  * Check if the method is suitable for this problem
  * @return bool suitability of the method
  */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

  /* PROTECTED METHODS *******************************************************/

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
  virtual C_FLOAT64 doSingleStep(C_FLOAT64 currentTime, C_FLOAT64 endTime);

  /* DETERMINISTIC STUFF *****************************************************/

  /**
   *   Integrates the deterministic reactions of the system over the
   *   specified time interval.
   *   @param const C_FLOAT64 & deltaT.
   */
  void integrateDeterministicPart(const C_FLOAT64 & deltaT);

  /* STOCHASTIC STUFF ********************************************************/

  /**
   *   Executes the specified reaction in the system once.
   *   @param const size_t & index
   */
  void fireReaction(const size_t & index);

  /**
   * Calculate the propensities of all stochastic reactions
   */
  void calculatePropensities();

  /**
   * Calculate the total propensity
   */
  void calculateTotalPropensity();

  /* PRIVATE METHODS *********************************************************/

private:
  /**
   * Initialize the method parameter
   */
  void initializeParameter();

  /* VARIABLES ***************************************************************/
protected:
  /**
   * Pointer to the method parameter "Max Internal Steps"
   */
  unsigned C_INT32 * mpMaxSteps;

  /**
   * Pointer to the method parameter "Lower Limit"
   */
  C_FLOAT64 * mpLowerLimit;

  /**
   * Pointer to the method parameter "Upper Limit"
   */
  C_FLOAT64 * mpUpperLimit;

  /**
   * Pointer to the method parameter "Partitioning Interval"
   */
  unsigned C_INT32 * mpPartitioningInterval;

  /**
   * Pointer to the method parameter "Partitioning Stepsize"
   */
  C_FLOAT64 * mpPartitioningSteps;

  /**
   *   The random number generator.
   */
  CRandom * mpRandomGenerator;

  /**
   * Index of the first species determined by reactions in CState
   */
  size_t mFirstReactionSpeciesIndex;

  bool mMaxStepsReached;

  /**
   *   Number of elementary steps after the last partitioning.
   */
  size_t mStepsAfterPartitionSystem;

  /**
   * The particle and reaction numbers
   */
  size_t mNumReactions;

  /**
   * The time the next reaction fires
   */
  C_FLOAT64 mNextReactionTime;

  /**
   * The index of the next reaction which fires
   */
  size_t mNextReactionIndex;

  /**
   * A vector referencing the math container's reactions
   */
  CVectorCore< CMathReaction > mReactions;

  /**
   * A vector referencing the math container's propensity objects
   */
  CVectorCore< CMathObject > mPropensityObjects;

  /**
   * A vector referencing the math container's propensity values
   */
  CVectorCore< C_FLOAT64 > mAmu;

  /**
   * A vector containing the update sequence required to update all propensity values.
   */
  CVector< CCore::CUpdateSequence > mUpdateSequences;

  /**
   * Total propensity (sum over mAmu[i])
   */
  C_FLOAT64 mA0;

  /**
   * The partition of the system
   */
  CPartition mPartition;

  /**
   * The return status of LSODA integration
   */
  CTrajectoryMethod::Status mStatus;
};
#endif // COPASI_CTrajectoryMethodDsaLsodar
