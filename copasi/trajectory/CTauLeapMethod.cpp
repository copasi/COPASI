// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

/**
 *   CTauLeapMethod
 *
 *   This class implements the tau-Leap method for the simulation of a
 *   biochemical system over time (see Gillespie (2001): Approximate
 *   accelerated stochastic simulation of chemically reacting systems.
 *   J. Chemical Physics, 115:1716-1733).
 *
 *   File name: CTauLeapMethod.cpp
 *   Author: Juergen Pahle
 *   Email: juergen.pahle@eml-r.villa-bosch.de
 *
 *   Last change: 20, April 2004
 *
 *   (C) European Media Lab 2004.
 */

/* DEFINE ********************************************************************/

#include "copasi.h"

#include "CTauLeapMethod.h"
#include "CTrajectoryProblem.h"
#include "CHybridMethod.h" // CHybridBalance, todo: beautify this
#include "math/CMathContainer.h"
#include "model/CModel.h"
#include "model/CMetab.h"
#include "model/CReaction.h"
#include "model/CState.h"
#include "model/CChemEq.h"
#include "model/CChemEqElement.h"
#include "model/CCompartment.h"
#include "utilities/CCopasiVector.h"
#include "utilities/CMatrix.h"
#include "utilities/CDependencyGraph.h"
#include "utilities/CIndexedPriorityQueue.h"
#include "randomGenerator/CRandom.h"

/**
 *   Default constructor.
 */
CTauLeapMethod::CTauLeapMethod(const CCopasiContainer * pParent):
  CTrajectoryMethod(CCopasiMethod::tauLeap, pParent),
  mNumReactions(0),
  mNumReactionSpecies(0),
  mReactions(),
  mPropensityObjects(),
  mAmu(),
  mA0(0.0),
  mK(),
  mAvgDX(),
  mSigDX(),
  mEpsilon(),
  mMaxSteps(),
  mUseRandomSeed(false),
  mRandomSeed(),
  mpRandomGenerator(NULL),
  mFirstReactionSpeciesIndex(C_INVALID_INDEX)
{
  mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
  initializeParameter();
}

CTauLeapMethod::CTauLeapMethod(const CTauLeapMethod & src,
                               const CCopasiContainer * pParent):
  CTrajectoryMethod(src, pParent),
  mNumReactions(0),
  mNumReactionSpecies(0),
  mReactions(),
  mPropensityObjects(),
  mAmu(),
  mA0(0.0),
  mK(),
  mAvgDX(),
  mSigDX(),
  mEpsilon(),
  mMaxSteps(),
  mUseRandomSeed(false),
  mRandomSeed(),
  mpRandomGenerator(NULL),
  mFirstReactionSpeciesIndex(C_INVALID_INDEX)
{
  mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
  initializeParameter();
}

/**
 *   Destructor.
 */
CTauLeapMethod::~CTauLeapMethod()
{
  cleanup();
  DESTRUCTOR_TRACE;
}

void CTauLeapMethod::initializeParameter()
{
  CCopasiParameter *pParm;

  assertParameter("Epsilon", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.001);
  assertParameter("Max Internal Steps", CCopasiParameter::UINT, (unsigned C_INT32) 10000);
  assertParameter("Use Random Seed", CCopasiParameter::BOOL, false);
  assertParameter("Random Seed", CCopasiParameter::UINT, (unsigned C_INT32) 1);

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("TAULEAP.Tau")) != NULL)
    {
      removeParameter("TAULEAP.Tau");

      if ((pParm = getParameter("TAULEAP.UseRandomSeed")) != NULL)
        {
          setValue("Use Random Seed", *pParm->getValue().pBOOL);
          removeParameter("TAULEAP.UseRandomSeed");
        }

      if ((pParm = getParameter("TAULEAP.RandomSeed")) != NULL)
        {
          setValue("Random Seed", *pParm->getValue().pUINT);
          removeParameter("TAULEAP.RandomSeed");
        }
    }
}

bool CTauLeapMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

CTrajectoryMethod::Status CTauLeapMethod::step(const double & deltaT)
{
  // do several steps
  C_FLOAT64 Time = *mpContainerStateTime;
  C_FLOAT64 EndTime = Time + deltaT;

  size_t Steps = 0;

  while (Time < EndTime)
    {
      // We do not need to update the the method state since the only independent state
      // values are species of type reaction which are all controlled by the method.

      Time += doSingleStep(EndTime - Time);
      *mpContainerStateTime = Time;
      mpContainer->updateSimulatedValues(false);

      if (++Steps > mMaxSteps)
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 12);
        }
    }

  return NORMAL;
}

void CTauLeapMethod::start(CVectorCore< C_FLOAT64 > & initialState)
{
  /* get configuration data */

  bool useRandomSeed = * getValue("Use Random Seed").pBOOL;
  unsigned C_INT32 randomSeed = * getValue("Random Seed").pUINT;

  if (useRandomSeed) mpRandomGenerator->initialize(randomSeed);

  mEpsilon = * getValue("Epsilon").pDOUBLE;
  mUseRandomSeed = * getValue("Use Random Seed").pBOOL;
  mRandomSeed = * getValue("Random Seed").pUINT;
  mMaxSteps = * getValue("Max Internal Steps").pUINT;

  mContainerState = initialState;

  // Size the arrays
  mReactions.initialize(mpContainer->getReactions());
  mNumReactions = mReactions.size();
  mAmu.initialize(mpContainer->getPropensities());
  mPropensityObjects.initialize(mAmu.size(), mpContainer->getMathObject(mAmu.array()));

  mK.resize(mNumReactions);

  mNumReactionSpecies = mpContainer->getCountIndependentSpecies() + mpContainer->getCountDependentSpecies();
  mFirstReactionSpeciesIndex = mpContainer->getCountFixedEventTargets() + 1 /* Time */ + mpContainer->getCountODEs();

  mAvgDX.resize(mNumReactionSpecies);
  mSigDX.resize(mNumReactionSpecies);

  C_FLOAT64 * pSpecies = mContainerState.array() + mFirstReactionSpeciesIndex;
  C_FLOAT64 * pSpeciesEnd = pSpecies + mNumReactionSpecies;

  for (; pSpecies != pSpeciesEnd; ++pSpecies)
    {
      *pSpecies = floor(*pSpecies + 0.5);
    }

  // The container state is now up to date we just need to calculate all values needed for simulation.
  mpContainer->updateSimulatedValues(false); //for assignments

  return;
}

/* PROTECTED METHODS *********************************************************/

/**
 *  Initializes the solver and sets the model to be used.
 *
 *  @param model A reference to an instance of a CModel
 */

/**
 *  Cleans up memory, etc.
 */
void CTauLeapMethod::cleanup()
{
  delete mpRandomGenerator;
  mpRandomGenerator = NULL;

  return;
}

/**
 *  Simulates the system over the next interval of time. The timestep
 *  is given as argument.
 *
 *  @param  ds A C_FLOAT64 specifying the timestep
 */
C_FLOAT64 CTauLeapMethod::doSingleStep(C_FLOAT64 ds)
{
  C_FLOAT64 Lambda, Tmp, Tau, Tau1, Tau2;

  updatePropensities();

  mAvgDX = 0.0;
  mSigDX = 0.0;

  CMathReaction * pReaction = mReactions.array();
  const C_FLOAT64 * pAmu = mAmu.array();
  const C_FLOAT64 * pAmuEnd = pAmu + mNumReactions;
  const CObjectInterface * pFirstSpecies = mpContainer->getMathObject(mContainerState.array() + mFirstReactionSpeciesIndex);

  for (; pAmu != pAmuEnd; ++pAmu, ++pReaction)
    {
      const CMathReaction::Balance & Balance = pReaction->getBalance();
      CMathReaction::Balance::const_iterator it = Balance.begin();
      CMathReaction::Balance::const_iterator end = Balance.begin();

      for (; it != end; ++it)
        {
          mAvgDX[it->first - pFirstSpecies] += it->second * *pAmu;
          mSigDX[it->first - pFirstSpecies] += it->second * it->second * *pAmu;
        }
    }

  Tau1 = Tau2 = std::numeric_limits< C_FLOAT64 >::infinity();

  const C_FLOAT64 * pSpecies = mContainerState.array() + mFirstReactionSpeciesIndex;
  const C_FLOAT64 * pSpeciesEnd = pSpecies + mNumReactionSpecies;
  C_FLOAT64 * pAvgDX = mAvgDX.array();
  C_FLOAT64 * pSigDX = mSigDX.array();

  for (; pSpecies != pSpeciesEnd; ++pSpecies, ++pAvgDX, ++pSigDX)
    {
      if ((Tmp = mEpsilon * fabs(*pSpecies)) < 1.0)
        Tmp = 1.0;

      *pAvgDX = Tmp / fabs(*pAvgDX);
      *pSigDX = (Tmp * Tmp) / fabs(*pSigDX);

      if (Tau1 > *pAvgDX)
        Tau1 = *pAvgDX;

      if (Tau2 > *pSigDX)
        Tau2 = *pSigDX;
    }

  Tau = std::min(Tau1, Tau2);

  if (ds < Tau)
    Tau = ds;

  pAmu = mAmu.array();
  C_FLOAT64 * pK = mK.array();
  C_FLOAT64 * pKEnd = pK + mNumReactions;

  for (; pAmu != pAmuEnd; ++pAmu, ++pK)
    {
      Lambda = *pAmu * Tau;

      if (Lambda < 0.0)
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 10);
      else if (Lambda > 2.0e9)
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 26);

      *pK = mpRandomGenerator->getRandomPoisson(Lambda);
    }

  while (!updateSystem())
    {
      Tau *= 0.5;
      pK = mK.array();

      for (; pK != pKEnd; ++pK)
        {
          *pK *= 0.5;

          if (*pK < floor(*pK + 0.75))
            {
              *pK += mpRandomGenerator->getRandomCC() < 0.5 ? - 0.5 : 0.5;
            }
        }
    }

  return Tau;
}

void CTauLeapMethod::updatePropensities()
{
  //mA0Old = mA0;
  mA0 = 0;

  CMathObject * pPropensity = mPropensityObjects.array();
  CMathObject * pPropensityEnd = pPropensity + mNumReactions;
  C_FLOAT64 * pAmu = mAmu.array();

  for (; pPropensity != pPropensityEnd; ++pPropensity, ++pAmu)
    {
      pPropensity->calculate();
      mA0 += *pAmu;
    }

  return;
}

/**
 *   Updates the system according to the probabilistic
 *   number of firings mK[i] of each reaction i
 */
bool CTauLeapMethod::updateSystem()
{
  // Save the current state in case we need to role back.
  CVector< C_FLOAT64 > OldState = mContainerState;

  CMathReaction * pReaction = mReactions.array();
  CMathReaction * pReactionEnd = pReaction + mNumReactions;
  const C_FLOAT64 * pK = mK.array();

  const C_FLOAT64 * pKEnd = pK + mNumReactions;

  for (; pReaction != pReactionEnd; ++pK, ++pReaction)
    {
      pReaction->fireMultiple(*pK);
    }

  const C_FLOAT64 * pSpecies = mContainerState.array() + mFirstReactionSpeciesIndex;

  const C_FLOAT64 * pSpeciesEnd = pSpecies + mNumReactionSpecies;

  for (; pSpecies != pSpeciesEnd; ++pSpecies)
    {
      if (*pSpecies < -0.5)
        {
          // We need to undo the changes
          mContainerState = OldState;
          return false;
        }
    }

  return true;
}

//virtual
bool CTauLeapMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CTrajectoryMethod::isValidProblem(pProblem)) return false;

  const CTrajectoryProblem * pTP = dynamic_cast<const CTrajectoryProblem *>(pProblem);

  if (pTP->getDuration() < 0.0)
    {
      //back integration not possible
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 9);
      return false;
    }

  if (pTP->getModel()->getTotSteps() < 1)
    {
      //at least one reaction necessary
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 17);
      return false;
    }

  //check for ODE rules
  size_t i, imax = pTP->getModel()->getNumModelValues();

  for (i = 0; i < imax; ++i)
    {
      if (pTP->getModel()->getModelValues()[i]->getStatus() == CModelEntity::ODE)
        {
          //ode rule found
          CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 18);
          return false;
        }
    }

  imax = pTP->getModel()->getNumMetabs();

  for (i = 0; i < imax; ++i)
    {
      if (pTP->getModel()->getMetabolites()[i]->getStatus() == CModelEntity::ODE)
        {
          //ode rule found
          CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 20);
          return false;
        }
    }

  imax = pTP->getModel()->getCompartments().size();

  for (i = 0; i < imax; ++i)
    {
      if (pTP->getModel()->getCompartments()[i]->getStatus() == CModelEntity::ODE)
        {
          //ode rule found
          CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 21);
          return false;
        }
    }

  //TODO: rewrite CModel::suitableForStochasticSimulation() to use
  //      CCopasiMessage
  std::string message = pTP->getModel()->suitableForStochasticSimulation();

  if (message != "")
    {
      //model not suitable, message describes the problem
      CCopasiMessage(CCopasiMessage::ERROR, message.c_str());
      return false;
    }

  //events are not supported at the moment
  if (pTP->getModel()->getEvents().size() > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 23);
      return false;
    }

  return true;
}
