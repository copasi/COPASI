// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/copasi.h"

#include "CTauLeapMethod.h"
#include "CTrajectoryProblem.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CState.h"
#include "copasi/model/CChemEq.h"
#include "copasi/model/CChemEqElement.h"
#include "copasi/model/CCompartment.h"
#include "copasi/core/CDataVector.h"
#include "copasi/core/CMatrix.h"
#include "copasi/utilities/CDependencyGraph.h"
#include "copasi/utilities/CIndexedPriorityQueue.h"
#include "copasi/randomGenerator/CRandom.h"

/* DEFINE ********************************************************************/
#define TAU                    0.01
#define EPS                    0.03
#define USE_RANDOM_SEED        false
#define RANDOM_SEED            1
#define INT_EPSILON            0.1

/**
 *   Default constructor.
 */
CTauLeapMethod::CTauLeapMethod(const CDataContainer * pParent,
                               const CTaskEnum::Method & methodType,
                               const CTaskEnum::Task & taskType):
  CTrajectoryMethod(pParent, methodType, taskType),
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
  initializeParameter();
}

CTauLeapMethod::CTauLeapMethod(const CTauLeapMethod & src,
                               const CDataContainer * pParent):
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
  initializeParameter();
}

/**
 *   Destructor.
 */
CTauLeapMethod::~CTauLeapMethod()
{}

void CTauLeapMethod::initializeParameter()
{
  CCopasiParameter *pParm;

  assertParameter("Epsilon", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) 0.001);
  assertParameter("Max Internal Steps", CCopasiParameter::Type::UINT, (unsigned C_INT32) 10000);
  assertParameter("Use Random Seed", CCopasiParameter::Type::BOOL, false);
  assertParameter("Random Seed", CCopasiParameter::Type::UINT, (unsigned C_INT32) 1);

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("TAULEAP.Tau")) != NULL)
    {
      removeParameter("TAULEAP.Tau");

      if ((pParm = getParameter("TAULEAP.UseRandomSeed")) != NULL)
        {
          setValue("Use Random Seed", pParm->getValue< bool >());
          removeParameter("TAULEAP.UseRandomSeed");
        }

      if ((pParm = getParameter("TAULEAP.RandomSeed")) != NULL)
        {
          setValue("Random Seed", pParm->getValue< unsigned C_INT32 >());
          removeParameter("TAULEAP.RandomSeed");
        }
    }
}

bool CTauLeapMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

CTrajectoryMethod::Status CTauLeapMethod::step(const double & deltaT,
    const bool & /* final */)
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

      if (mpProblem->getAutomaticStepSize()) break;
    }

  return NORMAL;
}

void CTauLeapMethod::start()
{
  CTrajectoryMethod::start();

  /* get configuration data */

  mpRandomGenerator = &mpContainer->getRandomGenerator();

  bool useRandomSeed = getValue< bool >("Use Random Seed");
  unsigned C_INT32 randomSeed = getValue< unsigned C_INT32 >("Random Seed");

  if (useRandomSeed) mpRandomGenerator->initialize(randomSeed);

  mEpsilon = getValue< C_FLOAT64 >("Epsilon");
  mUseRandomSeed = getValue< bool >("Use Random Seed");
  mRandomSeed = getValue< unsigned C_INT32 >("Random Seed");
  mMaxSteps = getValue< unsigned C_INT32 >("Max Internal Steps");

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
  const C_FLOAT64 * pFirstSpecies = mContainerState.array() + mFirstReactionSpeciesIndex;

  for (; pAmu != pAmuEnd; ++pAmu, ++pReaction)
    {
      const CMathReaction::Balance & Balance = pReaction->getNumberBalance();
      const CMathReaction::SpeciesBalance * it = Balance.array();
      const CMathReaction::SpeciesBalance * end = it + Balance.size();

      for (; it != end; ++it)
        {
          mAvgDX[it->first - pFirstSpecies] += it->second **pAmu;
          mSigDX[it->first - pFirstSpecies] += it->second * it->second **pAmu;
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
  mA0 = 0;

  CMathObject * pPropensity = mPropensityObjects.array();
  CMathObject * pPropensityEnd = pPropensity + mNumReactions;
  C_FLOAT64 * pAmu = mAmu.array();

  for (; pPropensity != pPropensityEnd; ++pPropensity, ++pAmu)
    {
      pPropensity->calculateValue();
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

  if (mpContainer->getReactions().size() < 1)
    {
      //at least one reaction necessary
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 17);
      return false;
    }

  //check for ODE rules
  if (mpContainer->getCountODEs() > 0)
    {
      //ode rule found
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 28);
      return false;
    }

  //events are not supported at the moment
  if (mpContainer->getEvents().size() > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 23, CTaskEnum::MethodName[getSubType()].c_str());
      return false;
    }

  //TODO: rewrite CModel::suitableForStochasticSimulation() to use
  //      CCopasiMessage
  std::string message = mpContainer->getModel().suitableForStochasticSimulation();

  if (message != "")
    {
      //model not suitable, message describes the problem
      CCopasiMessage(CCopasiMessage::ERROR, message.c_str());
      return false;
    }

  return true;
}
