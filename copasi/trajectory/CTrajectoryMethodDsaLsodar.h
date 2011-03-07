// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTrajectoryMethodDsaLsodar.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:34:14 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/utilities/CCopasiVector.h"
#include "copasi/model/CState.h"

class CReaction;
class CMetab;
class CRandom;

class CTrajectoryMethodDsaLsodar : public CLsodaMethod
{
  friend CTrajectoryMethod *
  CTrajectoryMethod::createMethod(CCopasiMethod::SubType subType);

  /* PUBLIC METHODS **********************************************************/
  class CReactionDependencies
  {
  public:
    // Operations
    /**
     * Default constructor
     */
    CReactionDependencies();

    /**
     * Copy constructor
     * @param const CReactionDependencies & src
     */
    CReactionDependencies(const CReactionDependencies & src);

    /**
     * Destructor
     */
    ~CReactionDependencies();

    /**
     * Assignment operator
     * @param const CReactionDependencies & rhs
     * @return CReactionDependencies &
     */
    CReactionDependencies & operator = (const CReactionDependencies & rhs);

    // Attributes

    /**
     * Vector of multiplier to calculate the new state
     */
    CVector< C_FLOAT64 > mSpeciesMultiplier;

    /**
     * Vector of pointers to method internal species values to calculate the new state.
     */
    CVector< C_FLOAT64 * > mMethodSpecies;

    /**
     * Vector of pointers to model species values to calculate the new state.
     */
    CVector< C_FLOAT64 * > mModelSpecies;

    /**
     * Vector of refresh methods which need to be executed to update all values required for simulation
     */
    std::vector< Refresh * > mCalculations;

    /**
     * A vector of indexes of reaction which propensities have to be recalculated.
     */
    CVector< size_t > mDependentReactions;

    /**
     * Vector of multiplier to calculate the new propensity.
     */
    CVector< C_FLOAT64 > mSubstrateMultiplier;

    /**
     * Vector of pointers to method internal species values to calculate the new propensity.
     */
    CVector< C_FLOAT64 * > mMethodSubstrates;

    /**
     * Vector of pointers to model species values to calculate the new propensity.
     */
    CVector< C_FLOAT64 * > mModelSubstrates;

    /**
     * A pointer to the particle flux of the reaction.
     */
    C_FLOAT64 * mpParticleFlux;

    /**
     * A vector containing the index of each species participating in the reaction as
     * a substrate and/or product.
     */
    CVector< size_t > mSpeciesIndex;
  };

  class CPartition
  {
  public:
    typedef std::multimap< size_t, size_t > speciesToReactionsMap;

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

    void intialize(std::vector< CReactionDependencies > & reactions,
                   const speciesToReactionsMap & speciesToReactions,
                   const C_FLOAT64 & lowerThreshold,
                   const C_FLOAT64 & upperThreshold,
                   const CState & state);

    bool rePartition(const CState & state);

    void determineStochasticSpecies();

  private:
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

  public:
    /**
     * A vector containing pointers to stochastic reaction dependencies
     */
    CVector< CReactionDependencies * > mStochasticReactions;

    /**
     * A vector containing pointers to stochastic reaction dependencies
     */
    CVector< CReactionDependencies * > mDeterministicReactions;

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

  private:
    /**
     * A vector containing the number of low species for each reaction
     */
    CVector< size_t > mNumLowSpecies;

    /**
     * A vector containing the current treatment of the species
     */
    CVector< bool > mLowSpecies;
  };

protected:
  /**
   * Default constructor.
   * @param const CCopasiMethod::SubType & subType (default: DsaLsodar)
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CTrajectoryMethodDsaLsodar(const CCopasiMethod::SubType & subType = DsaLsodar,
                             const CCopasiContainer * pParent = NULL);

public:
  /**
   * Copy constructor
   * @param const CTrajectoryMethodDsaLsodar & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CTrajectoryMethodDsaLsodar(const CTrajectoryMethodDsaLsodar & src,
                             const CCopasiContainer * pParent = NULL);

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
   */
  virtual void stateChanged();

  /**
   *  This instructs the method to calculate a time step of deltaT
   *  starting with the current state, i.e., the result of the previous
   *  step.
   *  The new state (after deltaT) is expected in the current state.
   *  The return value is the actual time step taken.
   *  @param "const double &" deltaT
   *  @return Status status
   */
  virtual Status step(const double & deltaT);

  /**
   *  This instructs the method to prepare for integration
   *  starting with the initialState given.
   *  @param "const CState *" initialState
   */
  virtual void start(const CState * initialState);

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
   * Calculates an amu value for a given reaction.
   * @param const size_t & index
   */
  void calculateAmu(const size_t & index);

  /**
   * Calculate the propensities of all stochastic reactions
   */
  void calculatePropensities();

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
   * A boolean flag indicating whether correction for higher order reactions need to be applied
   */
  bool mDoCorrection;

  /**
   * A vector of reaction propensities
   */
  CVector< C_FLOAT64 > mAmu;

  /**
   * Total propensity (sum over mAmu[i])
   */
  C_FLOAT64 mA0;

  /**
   * A vector containing dependency information to minimize the required updates.
   */
  std::vector< CReactionDependencies > mReactionDependencies;

  /**
   * The partition of the system
   */
  CPartition mPartition;
};

#include "CHybridNextReactionRKMethod.h"

#endif // COPASI_CTrajectoryMethodDsaLsodar
