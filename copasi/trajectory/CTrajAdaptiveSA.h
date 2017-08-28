// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

class CTrajectoryProblem;
class CRandom;
class CMathReaction;

class CTrajAdaptiveSA : public CTrajectoryMethod
{
private:
  /**
   * Default constructor.
   */
  CTrajAdaptiveSA();

protected:
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
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: adaptiveSA)
   * @param const CTaskEnum::Task & taskType (default: timeCourse)
   */
  CTrajAdaptiveSA(const CDataContainer * pParent,
                  const CTaskEnum::Method & methodType = CTaskEnum::Method::adaptiveSA,
                  const CTaskEnum::Task & taskType = CTaskEnum::Task::timeCourse);

  /**
   * Copy constructor.
   * @param const CTrajAdaptiveSA & src,
   * @param const CDataContainer * pParent (Default: NULL)
   */
  CTrajAdaptiveSA(const CTrajAdaptiveSA & src,
                  const CDataContainer * pParent);

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
   * The particle and reaction numbers
   */
  size_t mNumReactions;

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
   *   Number of variable metabolites.
   */
  size_t mNumReactionSpecies;

  /**
   * A reference to the math container's reactions
   */
  CVectorCore< CMathReaction > mReactions;

  /**
   * A reference to the math container's propensity objects
   */
  CVectorCore< CMathObject > mPropensityObjects;

  /**
   * A reference to the math container's propensity values
   */
  CVectorCore< C_FLOAT64 > mAmu;

  /**
   * A vector containing the update sequence required to update all propensity values.
   */
  CVector< CCore::CUpdateSequence > mUpdateSequences;

  /**
   *   The ordered propensity function
   */
  CVector< const C_FLOAT64 * > mPartitionedAmu;

  /**
   * The method internal state which contains particle rounded particle numbers.
   */
  CVector <C_FLOAT64 > mMethodState;

  /**
   *   The Ordered reaction
   */
  CVector< CMathReaction * > mPartitionedDependencies;

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
