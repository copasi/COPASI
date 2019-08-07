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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CTauLeapMethod
#define COPASI_CTauLeapMethod

/* INCLUDES ******************************************************************/
#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/core/CDataVector.h"
#include "copasi/model/CState.h"

/* CLASSES *******************************************************************/
class CTrajectoryProblem;
class CRandom;
class CMathReaction;

class CTauLeapMethod : public CTrajectoryMethod
{
  /* PUBLIC METHODS ************************************************************/

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: tauLeap)
   * @param const CTaskEnum::Task & taskType (default: timeCourse)
   */
  CTauLeapMethod(const CDataContainer * pParent,
                 const CTaskEnum::Method & methodType = CTaskEnum::Method::tauLeap,
                 const CTaskEnum::Task & taskType = CTaskEnum::Task::timeCourse);

  /**
   * Copy constructor
   * @param const CTauLeapMethod & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CTauLeapMethod(const CTauLeapMethod & src,
                 const CDataContainer * pParent);

  /**
   *   Destructor.
   */
  ~CTauLeapMethod();

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

  /* PROTECTED METHODS *********************************************************/

private:
  /**
   * Default constructor.
   */
  CTauLeapMethod();

protected:
  /**
   *  Simulates the system over the next interval of time. The timestep
   *  is given as argument.
   *
   *  @param  ds A C_FLOAT64 specifying the timestep
   */
  C_FLOAT64 doSingleStep(C_FLOAT64 ds);

  /**
   * Calculate the propensities for all reactions
   */
  void updatePropensities();

  /**
   *   Updates the system according to the probabilistic
   *   number of firings mK[i] of each reaction i
   */
  bool updateSystem();

  /* VARIABLES *****************************************************************/

private:
  /**
   * Initialize the method parameter
   */
  void initializeParameter();

protected:

  /**
   *   Number of reactions.
   */
  size_t mNumReactions;

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
   * Total propensity (sum over mAmu[i])
   */
  C_FLOAT64 mA0;

  /**
   *   The k-values of the reactions, that is the
   *   probabilistic number of firings within one leap.
   */
  CVector< C_FLOAT64 > mK;

  /**
   *   For tau-selection method
   */
  CVector< C_FLOAT64> mAvgDX;

  /**
   *   For tau-selection method
   */
  CVector< C_FLOAT64> mSigDX;

  /**
   *   The tolerance ratio x(t+t')< eps*x(t)
   */
  C_FLOAT64 mEpsilon;

  /**
   * The maximum number of tau leap steps allowed for an integrations step
   */
  unsigned C_INT32 mMaxSteps;

  /**
   *   Specifies if the mRandomSeed should be used.
   *   otherwise a randomly chosen seed is used.
   */
  bool mUseRandomSeed;

  /**
   *   The random seed to use.
   */
  unsigned C_INT32 mRandomSeed;

  /**
   *   The random number generator.
   */
  CRandom * mpRandomGenerator;

  /**
   * index of first species in a CState
   */
  size_t mFirstReactionSpeciesIndex;
};

#endif // COPASI_CTauLeapMethod
