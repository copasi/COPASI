// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CTrajAdaptiveSA
#define COPASI_CTrajAdaptiveSA

//#define ANALYZ_HYBRID

#include <set>
#include <vector>

#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/trajectory/CStochMethod.h"
#include "copasi/model/CState.h"

#define EPS             0.03
#define UPPER_LIMIT 20
#define SSA_MULTIPLE  10
#define SSA_UPPER_NUM 100

class CModel;
class CMetab;
class CTrajectoryProblem;
class CRandom;

class CTrajAdaptiveSA : public CTrajectoryMethod
{
  friend CTrajectoryMethod *
  CTrajectoryMethod::createMethod(CCopasiMethod::SubType subType);

private:
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
     *  Species Index
     */
    CVector< size_t > mMethodSpeciesIndex;

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
  };

protected:
  /**
   * Default constructor.
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CTrajAdaptiveSA(const CCopasiContainer * pParent = NULL);

  /**
   * Calculate the propensity of the indexed reaction
   * @param const size_t & index
   */
  const C_FLOAT64 & calculateAmu(const size_t & index);

  /**
   * Fire the next reaction if it fire before the endTime
   * @param const C_FLOAT64 & curTime
   * @param const C_FLOAT64 & endTime
   * @return C_FLOAT64 timeAfterStep
   */
  C_FLOAT64 doSingleSSAStep(const C_FLOAT64 & curTime, const C_FLOAT64 & endTime);

  /**
    * Fire the next reaction if it fire before the endTime
    * @param const C_FLOAT64 & curTime
    * @param const C_FLOAT64 & endTime
    * @return C_FLOAT64 timeAfterStep
    */
  C_FLOAT64 doSingleTauLeapStep(const C_FLOAT64 & curTime, const C_FLOAT64 & endTime);

public:
  /**
   * Copy constructor.
   * @param const CTrajAdaptiveSA & src,
   * @param const CCopasiContainer * pParent (Default: NULL)
   */
  CTrajAdaptiveSA(const CTrajAdaptiveSA & src,
                  const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor.
   */
  ~CTrajAdaptiveSA();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  /**
   *  Chooses a stochastic method adequate for the problem
   */
  static CTrajAdaptiveSA * createTauLeapMethod();

  /**
   *  This instructs the method to calculate a time step of deltaT
   *  starting with the current state, i.e., the result of the previous
   *  step.
   *  The new state (after deltaT) is expected in the current state.
   *  The return value is the actual timestep taken.
   *  @param "const double &" deltaT
   *  @return Status status
   */
  virtual Status step(const double & deltaT);

  /**
   *  This instructs the method to prepare for integration
   *  starting with the initialState given.
   *  @param CVectorCore< C_FLOAT64 > & initialState
   */
  virtual void start(CVectorCore< C_FLOAT64 > & initialState);

  /**
  * Check if the method is suitable for this problem
  * @return bool suitability of the method
  */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

private:
  /**
   * Initialize the method parameter
   */
  void initializeParameter();

  /********************************************************************************************
     The following variables are created for hybrid tauLeap method
  ********************************************************************************************/
  /**
   *   The tolerance ratio x(t+t')< eps*x(t)
   */
  C_FLOAT64 mEpsilon;

  /**
   *   The counter to count the time of doing single SSA
   */
  C_FLOAT64 mSSAStepCounter;

  /**
   *   The upper fires of the j-th reactions
   */
  CVector< size_t > mMaxReactionFiring;

  /**
   *   The number of fires
   */
  CVector< C_FLOAT64 > mReactionFiring;
  CVector< C_FLOAT64 * > mPartitionedReactionFiring;

  /**
   *   The mean and variance of species
   */
  CVector< C_FLOAT64 > mAvgDX;
  CVector< C_FLOAT64 > mSigDX;

  /**
   *   The species pointer for average, variance, and population (ordered)
   */
  // CVector< C_FLOAT64 * > mOrderedSpeciesMean;
  // CVector< C_FLOAT64 * > mOrderedSpeciesVariance;
  // CVector< C_FLOAT64 * > mOrderedSpecies;
  C_FLOAT64 * mpMethodSpecies;

  /**
   *   The temporary species
   */
  CVector< C_FLOAT64 > mSpeciesAfterTau;

  /**
   * Vector of refresh methods which need to be executed to update all values required for simulation
  */
  std::vector< Refresh * > mTauCalculations;

  /**
   *   The Ordered reaction
   */
  size_t mFirstReactionSpeciesIndex;

#ifdef ANALYZ_HYBRID
  /**
  *   Counters for statisitcs of hybrid method
  */
  C_INT32 SSAStepCnt, SLTStepCnt, HYDStepCnt;
  C_FLOAT32 SSAStepTime, SLTStepTime, HYDStepTime;
#endif

protected:

  /**
   * The random number generator
   */
  CRandom *mpRandomGenerator;

  /**
   * A pointer to the instance of CModel being used.
   */
  CModel *mpModel;

  /**
   * The particle and reaction numbers
   */
  size_t mNumReactions, mNumSpecies;

  /**
   * max number of single stochastic steps to do in one step()
   */
  unsigned C_INT32 mMaxSteps;

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
   *   Number of variable metabolites.
   */
  size_t mNumReactionSpecies;

  /**
   * A vector of reaction propensities
   */
  CVector< C_FLOAT64 > mAmu;

  /**
   *   The ordered propensity function
   */
  CVector< const C_FLOAT64 * > mPartitionedAmu;

  /**
   * The method internal state which contains particle rounded particle numbers.
   */
  CState mMethodState;

  /**
   * A vector containing dependency information to minimize the required updates.
   */
  std::vector< CReactionDependencies >  mReactionDependencies;

  /**
   *   The Ordered reaction
   */
  CVector< const CReactionDependencies * > mPartitionedDependencies;

  /**
   * Total propensity (sum over mAmu[i])
   */
  C_FLOAT64 mA0;

  /**
   * A boolean flag indicating whether the maximum steps have been reached. This
   * is used to avoid multiple messages.
   */
  bool mMaxStepsReached;
};

#endif // COPASI_CTrajAdaptiveSA
