// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CStochDirectMethod.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/11/19 19:01:52 $
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
#include "CStochMethod.h"
#include "copasi/utilities/CDependencyGraph.h"

class CModel;
class CMetab;
class CTrajectoryProblem;
class CRandom;

class CStochDirectMethod : public CTrajectoryMethod
{
  friend CTrajectoryMethod *
  CTrajectoryMethod::createTrajectoryMethod(CCopasiMethod::SubType subType,
      CTrajectoryProblem * pProblem);

protected:
  /**
   * Default constructor.
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CStochDirectMethod(const CCopasiContainer * pParent = NULL);
  void printKinetics();
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
  static CStochDirectMethod *
  createStochDirectMethod(CTrajectoryProblem * pProblem = NULL);

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
   * Intialize the method parameter
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
   * The graph of reactions and their dependent reactions. When a reaction is
   * executed, the propensities for each of its dependents must be updated.
   */
  //CDependencyGraph mDG;

  /**
   * The balances of the reactions as integers
   */
  //std::vector < std::vector <CStochBalance> > mLocalBalances;

  /**
   * the substrates of each reaction with their multiplicities
   */
  //std::vector < std::vector <CStochBalance> > mLocalSubstrates;

  /**
   * The particle and reaction numbers
   */

  unsigned C_INT32 mNumReactions, mNumSpecies;

  /**
   * index of first metab in a CState
   */
  unsigned C_INT32 mFirstMetabIndex;

  /**
   * tests if the model contains a global value with an assignment rule that is
   * used in calculations
   */
  static bool modelHasAssignments(const CModel* pModel);
  bool mHasAssignments;

  /**
  * max number of single stochastic steps to do in one step()
  */
  C_INT32 mMaxSteps;

  bool isPrinted;

  C_INT32 *dpgLen, *dpgTable; //Table mapping species to reactions
  C_INT32 *steLen, *steTable; //Table mapping species states in reactions to species
  C_INT32 *chgLen, *chgTable; //Table mapping state change in reactions to species
  C_FLOAT64 *species; //species populations
  C_FLOAT64 *steVec;  //species states vector
  C_FLOAT64 *chgVec;  //state change vector
  std::vector< Refresh * > *calculations;

  C_FLOAT64 simTime;
  C_FLOAT64 *mAmu, **rcRt;
  C_FLOAT64 mA0;
  bool mMaxStepsReached;
};

#endif // COPASI_CStochDirectMethod
