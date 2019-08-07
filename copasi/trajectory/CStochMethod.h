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

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CStochMethod
#define COPASI_CStochMethod

#include "copasi/core/CVector.h"
#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/utilities/CDependencyGraph.h"

class CTrajectoryProblem;
class CMathReaction;
class CRandom;

class CStochMethod : public CTrajectoryMethod
{
protected:

  /**
   * Initialization.
   */
  virtual void initMethod() = 0;

  /**
   * Do one iteration of the simulation
   * @return Current simulation time or -1 if error.
   */
  virtual C_FLOAT64 doSingleStep(C_FLOAT64 time, C_FLOAT64 endtime) = 0;

  /**
   * Generate the index of a putative reaction.
   * @return The reaction index
   */
  size_t generateReactionIndex();

  /**
   * Generate the putative time taken before any reaction takes place
   * @return The time before the reaction
   */
  C_FLOAT64 generateReactionTime();

  /**
   * Generate the putative time taken before a special reaction takes place
   * @return The time before the reaction
   */
  C_FLOAT64 generateReactionTime(size_t reaction_index);

  /**
  * Set up the dependency graph and the balances
  */
  void setupDependencyGraph();

private:

  /**
   *  This checks if a model is suitable for stochastic simulation.
   *  It returns a suggestion which method to use
   *  @param model The model to check
   *  @return 1: direct method, 2: next reaction method, -1: no stochastic simulation possible
   */
  static C_INT32 checkModel(CModel * pmodel);

  /**
   * Default constructor.
   */
  CStochMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: stochastic)
   * @param const CTaskEnum::Task & taskType (default: timeCourse)
   */
  CStochMethod(const CDataContainer * pParent,
               const CTaskEnum::Method & methodType = CTaskEnum::Method::stochastic,
               const CTaskEnum::Task & taskType = CTaskEnum::Task::timeCourse);

  /**
   * Copy constructor.
   * @param const CStochMethod & src,
   * @param const CDataContainer * pParent (Default: NULL)
   */
  CStochMethod(const CStochMethod & src,
               const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CStochMethod();

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
   * Intialize the method parameter
   */
  void initializeParameter();

protected:
  /**
   * The random number generator
   */
  CRandom *mpRandomGenerator;

  /**
   * The sum of the propensities
   */
  C_FLOAT64 mA0;

  size_t mNumReactions;

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
   * max number of single stochastic steps to do in one step()
   */
  size_t mMaxSteps;

  /**
   * Flag indicating whether the max step are reached.
   */
  bool mMaxStepsReached;

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
   *   The Ordered reaction
   */
  size_t mFirstReactionSpeciesIndex;

  /**
   * The dependency graph for the next reaction method.
   */
  CDependencyGraph mDG;
};

//#include "CStochDirectMethod.h"
//#include "CStochNextReactionMethod.h"

#endif // COPASI_CStochMethod
