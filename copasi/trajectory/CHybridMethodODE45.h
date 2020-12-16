// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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
 *   CHybridMethodODE45
 *
 *   This class implements an hybrid algorithm to simulate a biochemical
 *   system over time.
 *
 *   File name: CHybridMethodODE45.h
 *   Author: Shuo Wang
 *   Email: shuowang.learner@gmail.com
 *
 *   Last change: 11, Aug 2014
 *
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

#ifndef COPASI_CHybridMethodODE45
#define COPASI_CHybridMethodODE45

/* INCLUDES ******************************************************************/
#include <set>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <new>

#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/utilities/CVersion.h"
#include "copasi/core/CMatrix.h"
#include "copasi/core/CDataVector.h"
#include "copasi/trajectory/CRungeKutta.h"

/* DEFINE ********************************************************************/
#define INT_EPSILON                  0.1
#define SUBTYPE                      1
#define USE_RANDOM_SEED              false
#define RANDOM_SEED                  1

//Simulation Part
#define SLOW                         false
#define FAST                         true

//Event Flag
#define SLOW_REACT                  -1

class CMathReaction;

/**
 * A class to record whether a metab is slow or fast
 * @param fastReactions is applied to store which reactions this
 *        metab participates
 * @param flag, if set is empty -> false, else, -> true
 */

class CHybridMethodODE45 : public CTrajectoryMethod
{
public:
  struct Data
  {
    size_t dim;
    CHybridMethodODE45 * pMethod;
  };

protected:
  enum RootMasking
  {
    NONE = 0,
    ALL,
    DISCRETE
  };

  enum IntergrationType
  {
    DETERMINISTIC,
    HYBRID
  };

  enum PartitioningStrategyType
  {
    AllDeterministic = 0,
    UserSpecified,
    AllStochastic
  };

  static std::string PartitioningStrategy[];

  //================Function for Class================

  //================Function for Class================
protected:
  /**
   * Default Constructor
   */
  CHybridMethodODE45();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: hybridODE45)
   * @param const CTaskEnum::Task & taskType (default: timeCourse)
   */
  CHybridMethodODE45(const CDataContainer * pParent,
                     const CTaskEnum::Method & methodType = CTaskEnum::Method::hybridODE45,
                     const CTaskEnum::Task & taskType = CTaskEnum::Task::timeCourse);

  /**
   * Copy constructor
   * @param const CHybridMethodODE45 & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CHybridMethodODE45(const CHybridMethodODE45 & src,
                     const CDataContainer * pParent);
  /**
   * Destructor.
   */
  ~CHybridMethodODE45();

  //================Function for System================
public:

  /**
   * Check if the method is suitable for this problem
   * @return bool suitability of the method
   */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

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
   * Inform the trajectory method that the state has changed outside
   * its control
   * @param const CMath::StateChange & change
   */
  virtual void stateChange(const CMath::StateChange & change);

  /**
   *  This instructs the method to prepare for integration
   *  starting with the initialState given.
   */
  virtual void start();

private:
  /**
   * Intialize the method parameter
   */
  void initializeParameter();

  //================Function for Model================
public:

protected:
  /**
   * Check whether a function is fast or not.
   */
  void partitionSystem();

  /**
   * Setup mMethod, switching between Deterministic Method and
   * Hybrid Method
   */
  void determineIntegrationType();

  //================Function for ODE45================
public:

protected:

  /**
   * Integrates the deterministic reactions of the system over the
   * specified time interval.
   *
   * @param ds A C_FLOAT64 specifying the stepsize.
   */
  void integrateDeterministicPart(C_FLOAT64 ds);

  /**
   * Dummy Function for calculating derivative of ODE systems
   */
  static void EvalF(const size_t * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

  /**
   * Dummy Function for calculating roots value
   */
  static void EvalR(const size_t * n, const C_FLOAT64 * t, const C_FLOAT64 * y,
                    const size_t * nr, C_FLOAT64 * r);

  /**
   * This evaluates the derivatives for the complete model
   */
  void evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

  /**
   * This evaluates the roots value of the system
   */
  void evalR(const C_FLOAT64 * t, const C_FLOAT64 * y, const size_t *nr, C_FLOAT64 *r);

protected:
  /**
   * Simulates the system over the next interval of time. The current time
   * and the end time of the current step() are given as arguments.
   *
   * @param  endTime A C_FLOAT64 specifying the end time of the step()
   * @return A C_FLOAT giving the new time
   */
  C_FLOAT64 doSingleStep(C_FLOAT64 endTime);

  /**
   * Fire slow reaction and update populations and propensities
   * when Hybrid Method is used
   */
  void fireReaction();

  bool checkRoots();

  //================Function for Stoichastic Part================
protected:

  /**
   * Function return a reaction index which is a slow reaction firing
   * at the event time.
   * @return CMathReaction * pReaction
   */
  CMathReaction * getReactionToFire();
  //================Function for Root==============

private:
  void maskRoots(CVectorCore<C_FLOAT64> & rootValues);

  void createRootMask();

  void destroyRootMask();

  //================Help Functions================
protected:
  /**
   * Test the model if it is proper to perform stochastic simulations on.
   * Several properties are tested (e.g. integer stoichometry, all reactions
   * take place in one compartment only, irreversibility...).
   *
   * @return 0, if everything is ok; <0, if an error occured.
   */
  C_INT32 checkModel(CModel * model);

//Attributes:
  //================Model Related================
private:
  //~~~~~~~~Reaction Related~~~~~~~~
  /**
   * Vector containing pointers to the slow of the model.
   */
  CVector< CMathReaction * >  mSlowReactions;

  size_t mFirstReactionSpeciesIndex;
  size_t mCountReactionSpecies;

  /**
   * Bool value
   */
  bool mHasStoiReaction;
  bool mHasDetermReaction;

  /**
   * An Integer showes the method now CHybridMethod used
   * 0 == Stochastic
   * 1 == Deterministic
   * 2 == Hybrid
   */
  IntergrationType mIntegrationType;

  //================Attributes for State================
  /**
   *  A pointer to the current state in complete model view.
   */
  CVector< C_FLOAT64 > mLastSuccessState;

  /**
   * Time Record
   */
  C_FLOAT64 mTargetTime;

  //=================Attributes for ODE45 Solver================
  /**
   * mODE45
   */
  CRungeKutta mODE45;

  CRungeKutta::RKMethodStatus mRKMethodStatus;

  /**
   * Record whether ODE solver has been initialized
   */
  bool mODEInitalized;

  /**
   *   Max number of doSingleStep() per step()
   */
  size_t mRootCounter;
  bool   mMaxStepsReached;

  /**
   * maximal increase of a particle number in one step.
   */
  size_t mMaxBalance;

  /**
   * mData.dim is the dimension of the ODE system.
   * mData.pMethod contains CLsodaMethod * this to be used
   * in the static method EvalF
   */
  Data mData;

  /**
   * Vector of integration variables
   */
  CVector< C_FLOAT64 > mY;
  const C_FLOAT64 * mpYdot;
  size_t mCountContainerVariables;
  CCore::CUpdateSequence mSpeciesRateUpdateSequence;

  /**
   * The variables handling the integrated propensities of the stochastic reactions.
   */
  CVectorCore< C_FLOAT64 > mAmuVariables;
  CVector< C_FLOAT64 * > mAmuPointers;
  C_FLOAT64 mA0;
  CVector< C_INT > mMethodRootsFound;
  C_INT * mpHybridRoot;

  CVectorCore< C_FLOAT64 > mContainerFluxes;
  CVector< C_FLOAT64 > mSavedFluxes;
  CVector< C_FLOAT64 * > mFluxPointers;

  CCore::CUpdateSequence mPropensitiesUpdateSequence;

  //================Attributes for Root================
  /**
   * Status of Root and Slow Event
   */
  bool mEventProcessing;
  bool mFireReaction;

  /**
   * A mask which hides all roots being constant and zero.
   */
  CVector< bool > mRootMask;

  /**
   * A which indicates whether roots change only discretely.
   */
  CVectorCore< bool >  mDiscreteRoots;

  /**
   * Root counter to determine whether the internal
   * step limit is exceeded.
   */
  //size_t mRootCounter;

protected:
  /**
   * A Boolean flag indicating whether we should try masking roots
   */
  RootMasking mRootMasking;

  //=================Root Dealing Part for Stochastic Part================
private:

  /**
   * Value of Roots before a reaction event
   */
  CVector< C_FLOAT64 > mRootValuesLeft;

  /**
   * Value of Roots after a reaction event
   */
  CVectorCore< C_FLOAT64 > mRootValuesRight;

  /**
   * 2 Vector for storing root value
   */
  CVector< C_FLOAT64 > mRootsNonZero;

  //================Stochastic Related================
  /**
   * The random number generator.
   */
  CRandom * mpRandomGenerator;

  //========System Related========
  /**
   * File output stream to write data.
   */
  std::ofstream mOutputFile;

  /**
   * Output filename.
   */
  std::string mOutputFileName;

  /**
   * Output counter.
   */
  size_t mOutputCounter;

  unsigned C_INT32 * mpMaxInternalSteps;
  C_FLOAT64 * mpRelativeTolerance;
  C_FLOAT64 * mpAbsoluteTolerance;
  std::string * mpPartitioningStrategy;
  bool * mpUseRandomSeed;
  unsigned C_INT32 * mpRandomSeed;
  CCopasiParameterGroup * mpFastReactions;
};

#endif // COPASI_CHybridMethodODE45
