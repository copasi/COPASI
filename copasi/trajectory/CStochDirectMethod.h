// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CStochDirectMethod.h,v $
//   $Revision: 1.18 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:34:13 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CStochDirectMethod
#define COPASI_CStochDirectMethod

#include <set>
#include <vector>

#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/trajectory/CStochMethod.h"
#include "copasi/utilities/CDependencyGraph.h"
#include "copasi/model/CState.h"

class CModel;
class CMetab;
class CTrajectoryProblem;
class CRandom;

class CStochDirectMethod : public CTrajectoryMethod
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
  CStochDirectMethod(const CCopasiContainer * pParent = NULL);

  /**
   * Calculate the propensity of the indexed reaction
   * @param const size_t & index
   */
  void calculateAmu(const size_t & index);

  /**
   * Fire the next reaction if it fire before the endTime
   * @param const C_FLOAT64 & curTime
   * @param const C_FLOAT64 & endTime
   * @return C_FLOAT64 timeAfterStep
   */
  C_FLOAT64 doSingleStep(const C_FLOAT64 & curTime, const C_FLOAT64 & endTime);

public:
  /**
   * Copy constructor.
   * @param const CStochDirectMethod & src,
   * @param const CCopasiContainer * pParent (Default: NULL)
   */
  CStochDirectMethod(const CStochDirectMethod & src,
                     const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor.
   */
  ~CStochDirectMethod();

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
  * Check if the method is suitable for this problem
  * @return bool suitability of the method
  */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

private:
  /**
   * Initialize the method parameter
   */
  void initializeParameter();

  /**
   * Check whether finds a root
   */
  bool checkRoots();

  /**
   * Reset model status if State changed
   */
  void stateChanged();

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
   * The method internal state which contains particle rounded particle numbers.
   */
  CState mMethodState;

  /**
   * A vector containing dependency information to minimize the required updates.
   */
  std::vector< CReactionDependencies > mReactionDependencies;

  /**
   * A boolean flag indicating whether the maximum steps have been reached. This
   * is used to avoid multiple messages.
   */
  bool mMaxStepsReached;


  //========Arguments for Roots========
  /**
   * A double value recording time at which step() stops
   */
   C_FLOAT64 mTimeRecord;
  
  /**
   * An integer, referring number of roots
   */
  size_t mNumRoot;

  /**
   * A copasi vector recording root values
   */
  CVectorCore< C_FLOAT64 > *mpRootValueOld;
  CVectorCore< C_FLOAT64 > *mpRootValueNew;

  /**
   * A C_FLOAT64 pointer for usage of calculating new root values
   */
  C_FLOAT64 *mpRootNew;

  /**
   * A C_FLOAT64 pointer for usage of calculating new root values
   */
  C_FLOAT64 *mpRootOld;

};

#endif // COPASI_CStochDirectMethod
