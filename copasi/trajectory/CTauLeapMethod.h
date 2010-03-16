/* Begin CVS Header
 $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTauLeapMethod.h,v $
 $Revision: 1.14 $
 $Name:  $
 $Author: shoops $
 $Date: 2010/03/16 18:57:04 $
 End CVS Header */

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_CTauLeapMethod
#define COPASI_CTauLeapMethod

/* INCLUDES ******************************************************************/
#include "trajectory/CTrajectoryMethod.h"
#include "utilities/CCopasiVector.h"
#include "copasi/model/CState.h"

/* DEFINE ********************************************************************/
#define TAU                    0.01
#define EPS                    0.03
#define USE_RANDOM_SEED        false
#define RANDOM_SEED            1
#define INT_EPSILON            0.1

/* CLASSES *******************************************************************/
class CTrajectoryProblem;
class CState;
class CReaction;
class CHybridBalance;
class CModel;
class CMetab;
class CRandom;

class CTauLeapMethod : public CTrajectoryMethod
{
  friend CTrajectoryMethod *
  CTrajectoryMethod::createTrajectoryMethod(CCopasiMethod::SubType subType,
      CTrajectoryProblem * pProblem);

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
     * Vector of indexes of the species for method internal calculations
     */
    CVector< size_t > mMethodSpeciesIndex;

    /**
     * Vector of pointers to method internal species values to calculate the new state.
     */
    CVector< C_FLOAT64 * > mMethodSpecies;

    /**
     * Vector of pointers to model species values to calculate the new state.
     */
    CVector< C_FLOAT64 * > mModelSpecies;

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

  /* PUBLIC METHODS ************************************************************/

public:
  /**
   * Copy constructor
   * @param const CTauLeapMethod & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CTauLeapMethod(const CTauLeapMethod & src,
                 const CCopasiContainer * pParent = NULL);

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
   *   Creates a CTauLeapMethod adequate for the problem.
   */
  static CTauLeapMethod * createTauLeapMethod();

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

  /* PROTECTED METHODS *********************************************************/

protected:
  /**
   * Default constructor.
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CTauLeapMethod(const CCopasiContainer * pParent = NULL);

  /**
   *   Cleans up memory, etc.
   */
  void cleanup();

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
   * Calculate one of the propensities
   * @param const size_t & index
   * @return const C_FLOAT64 & amu
   */
  const C_FLOAT64 & calculateAmu(const size_t & index);

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
   *   Pointer to the model.
   */
  CModel * mpModel;

  /**
   * The method internal state which contains particle rounded particle numbers.
   */
  CState mMethodState;

  /**
   *   Number of reactions.
   */
  unsigned C_INT32 mNumReactions;

  /**
   * A vector containing dependency information to minimize the required updates.
   */
  std::vector< CReactionDependencies > mReactionDependencies;

  /**
   *   Number of variable metabolites.
   */
  unsigned C_INT32 mNumReactionSpecies;

  /**
   * A vector of reaction propensities
   */
  CVector< C_FLOAT64 > mAmu;

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
   * indicates if the correction N^2 -> N*(N-1) should be performed
   */
  bool mDoCorrection;

  /**
   * index of first species in a CState
   */
  size_t mFirstReactionSpeciesIndex;
};

#endif // COPASI_CTauLeapMethod
