// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CStochDirectMethod.h,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/11/25 17:50:12 $
// End CVS Header

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
  CTrajectoryMethod::createTrajectoryMethod(CCopasiMethod::SubType subType,
      CTrajectoryProblem * pProblem);

private:
  class CReactionDependencies
  {
  public:
    // Operations
    CReactionDependencies();
    CReactionDependencies(const CReactionDependencies & src);
    ~CReactionDependencies();
    CReactionDependencies & operator = (const CReactionDependencies & rhs);

    // Attributes
    // Information needed to update the systems state
    CVector< C_FLOAT64 > mSpeciesMultiplier;
    CVector< C_FLOAT64 * > mMethodSpecies;
    CVector< C_FLOAT64 * > mModelSpecies;

    std::vector< Refresh * > mCalculations;

    // List of reactions which propensity depends on the state changes.
    CVector< size_t > mDependentReactions;

    // Information needed to calculate the propensity of the current reaction
    CVector< C_FLOAT64 > mSubstrateMultiplier;
    CVector< C_FLOAT64 * > mMethodSubstrates;
    CVector< C_FLOAT64 * > mModelSubstrates;

    C_FLOAT64 * mpParticleFlux;
  };

protected:
  /**
   * Default constructor.
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CStochDirectMethod(const CCopasiContainer * pParent = NULL);
  C_INT32 calculateAmu(C_INT32 index);
  C_FLOAT64 doSingleStep(C_FLOAT64 curTime, C_FLOAT64 end_time);

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
   *  Chooses a stochastic method adequate for the problem
   */
  static CStochDirectMethod * createStochDirectMethod();

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
  void initVariable(int mNumSpecies, int mNumReactionss);

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
  C_INT32 mMaxSteps;

  // area of length of rows of dependent reaction (see dpgTable)
  // C_INT32 *dpgLen;
  // rows of indexes of reaction propensities which need to be recalculated if a reaction fires
  // C_INT32 *dpgTable;

  // area of length of rows of substrates changed by a reaction
  // C_INT32 *steLen;
  // rows of indexes of substrates changed by a reaction
  // C_INT32 *steTable;
  // rows of stoichiometry of substrates changed by a reaction
  // C_FLOAT64 *steVec;

  // area of length of rows of species changed by a reaction
  // C_INT32 *chgLen;
  // rows of indexes of species changed by a reaction
  // C_INT32 *chgTable;
  // rows of stoichiometry of species changed by a reaction
  // C_FLOAT64 *chgVec;

  // Area of particle numbers of the species
  // C_FLOAT64 *species;

  // Vector of refresh sequences which need to be calculate when a reaction fires.
  // std::vector< std::vector< Refresh * > > mCalculations;

  C_FLOAT64 mNextReactionTime;
  unsigned C_INT32 mNextReactionIndex;
  bool mDoCorrection;

  // Area of propensities of the reactions
  CVector< C_FLOAT64 > mAmu;
  CState mSpecies;
  CVector< CReactionDependencies > mReactionDependencies;

  // Area of pointers to the model's particle fluxes of the reactions
  // C_FLOAT64 **rcRt;

  // Total propensity (sum over mAmu[i])
  C_FLOAT64 mA0;

  bool mMaxStepsReached;
};

#endif // COPASI_CStochDirectMethod
