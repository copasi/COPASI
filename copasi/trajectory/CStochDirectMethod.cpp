// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243)
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
#endif  // WIN32

#include <limits.h>

#include <vector>
#include <numeric>
#include <limits>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>

#include "copasi.h"
#include "CStochDirectMethod.h"
#include "utilities/CCopasiVector.h"
#include "function/CFunction.h"
#include "randomGenerator/CRandom.h"
#include "CTrajectoryMethod.h"
#include "CTrajectoryProblem.h"
#include "math/CMathContainer.h"
#include "model/CState.h"
#include "model/CCompartment.h"
#include "model/CModel.h"

CStochDirectMethod::CStochDirectMethod(const CCopasiContainer * pParent):
  CTrajectoryMethod(CCopasiMethod::directMethod, pParent),
  mpRandomGenerator(CRandom::createGenerator(CRandom::mt19937)),
  mNumReactions(0),
  mMaxSteps(1000000),
  mNextReactionTime(0.0),
  mNextReactionIndex(C_INVALID_INDEX),
  mA0(0.0),
  mReactions(),
  mPropensityObjects(),
  mAmu(),
  mUpdateSequences(),
  mMaxStepsReached(false)
{
  initializeParameter();
}

CStochDirectMethod::CStochDirectMethod(const CStochDirectMethod & src,
                                       const CCopasiContainer * pParent):
  CTrajectoryMethod(src, pParent),
  mpRandomGenerator(CRandom::createGenerator(CRandom::mt19937)),
  mNumReactions(0),
  mMaxSteps(1000000),
  mNextReactionTime(0.0),
  mNextReactionIndex(C_INVALID_INDEX),
  mA0(0.0),
  mReactions(),
  mPropensityObjects(),
  mAmu(),
  mUpdateSequences(),
  mMaxStepsReached(false)
{
  initializeParameter();
}

CStochDirectMethod::~CStochDirectMethod()
{
  pdelete(mpRandomGenerator);
}

void CStochDirectMethod::initializeParameter()
{
  assertParameter("Max Internal Steps", CCopasiParameter::INT, (C_INT32) 1000000);
  assertParameter("Use Random Seed", CCopasiParameter::BOOL, false);
  assertParameter("Random Seed", CCopasiParameter::UINT, (unsigned C_INT32) 1);
}

bool CStochDirectMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

CTrajectoryMethod::Status CStochDirectMethod::step(const double & deltaT)
{
  // do several steps
  C_FLOAT64 Time = *mpContainerStateTime;
  C_FLOAT64 EndTime = Time + deltaT;

  size_t Steps = 0;

  while (Time < EndTime)
    {
      Time += doSingleStep(Time, EndTime);

      if (++Steps > mMaxSteps)
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 12);
        }
    }

  mContainerState = mpContainer->getState();

  return NORMAL;
}

void CStochDirectMethod::start(CVectorCore< C_FLOAT64 > & initialState)
{
  /* get configuration data */
  mMaxSteps = * getValue("Max Internal Steps").pINT;

  bool useRandomSeed = * getValue("Use Random Seed").pBOOL;
  unsigned C_INT32 randomSeed = * getValue("Random Seed").pUINT;

  if (useRandomSeed) mpRandomGenerator->initialize(randomSeed);

  //mpCurrentState is initialized. This state is not used internally in the
  //stochastic solver, but it is used for returning the result after each step.
  mContainerState = initialState;

  // Create a local copy of the state where the particle number species determined
  // by reactions are rounded to integers.
  C_FLOAT64 * pValue = mContainerState.array() + mpContainer->getCountFixedEventTargets() + 1 /* Time */ + mpContainer->getCountODEs();
  C_FLOAT64 * pValueEnd = pValue + mpContainer->getCountIndependentSpecies() + mpContainer->getCountDependentSpecies();

  for (; pValue != pValueEnd; ++pValue)
    {
      *pValue = floor(*pValue + 0.5);
    }

  // The container state is now up to date we just need to calculate all values needed for simulation.
  mpContainer->updateSimulatedValues(false); //for assignments

  CObjectInterface * pTimeObject = mpContainer->getMathObject(mpContainer->getModel().getValueReference());

  // Build the reaction dependencies
  mReactions.initialize(mpContainer->getReactions());
  mNumReactions = mReactions.size();
  mAmu.initialize(mpContainer->getPropensities());
  mPropensityObjects.initialize(mAmu.size(), mpContainer->getMathObject(mAmu.array()));
  mUpdateSequences.resize(mNumReactions);

  C_FLOAT64 * pAmu = mAmu.array();
  mA0 = 0.0;

  CMathReaction * pReaction = mReactions.array();
  CMathReaction * pReactionEnd = pReaction + mNumReactions;
  CObjectInterface::UpdateSequence * pUpdateSequence;
  CMathObject * pPropensityObject = mPropensityObjects.array();
  CMathObject * pPropensityObjectEnd = pPropensityObject + mPropensityObjects.size();

  CObjectInterface::ObjectSet Requested;

  for (; pPropensityObject != pPropensityObjectEnd; ++pPropensityObject)
    {
      Requested.insert(pPropensityObject);
    }

  pPropensityObject = mPropensityObjects.array();

  for (; pReaction  != pReactionEnd; ++pReaction, ++pUpdateSequence, ++pPropensityObject, ++pAmu)
    {
      // Update the propensity
      pPropensityObject->calculate();
      mA0 += *pAmu;

      CObjectInterface::ObjectSet Changed;

      // The time is always updated
      Changed.insert(pTimeObject);

      CMathReaction::Balance::const_iterator itBalance = pReaction->getBalance().begin();
      CMathReaction::Balance::const_iterator endBalance = pReaction->getBalance().end();

      for (; itBalance != endBalance; ++itBalance)
        {
          Changed.insert(itBalance->first);
        }

      pUpdateSequence->clear();
      mpContainer->getTransientDependencies().getUpdateSequence(CMath::Default, Changed, Requested, *pUpdateSequence);
    }

  mMaxStepsReached = false;

  mNextReactionTime = *mpContainerStateTime;
  mNextReactionIndex = C_INVALID_INDEX;

  return;
}

// virtual
bool CStochDirectMethod::isValidProblem(const CCopasiProblem * pProblem)
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

  // check for ODEs
  const CStateTemplate & StateTemplate = pTP->getModel()->getStateTemplate();
  CModelEntity *const* ppEntity = StateTemplate.beginIndependent();
  CModelEntity *const* ppEntityEnd = StateTemplate.endIndependent();

  for (; ppEntity != ppEntityEnd; ++ppEntity)
    {
      if ((*ppEntity)->getStatus() == CModelEntity::ODE)
        {
          if (dynamic_cast<const CModelValue *>(*ppEntity) != NULL)
            {
              // global quantity ode rule found
              CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 18);
              return false;
            }
          else if (dynamic_cast<const CCompartment *>(*ppEntity) != NULL)
            {
              // compartment ode rule found
              CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 21);
              return false;
            }
          else
            {
              // species ode rule found
              CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 20);
              return false;
            }
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

  if (* getValue("Max Internal Steps").pINT <= 0)
    {
      //max steps should be at least 1
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 15);
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

C_FLOAT64 CStochDirectMethod::doSingleStep(const C_FLOAT64 & curTime, const C_FLOAT64 & endTime)
{
  if (mNextReactionIndex == C_INVALID_INDEX)
    {
      if (mA0 == 0)
        {
          return endTime - curTime;
        }

      // We need to throw an exception if mA0 is NaN
      if (isnan(mA0))
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 27);
        }

      mNextReactionTime = curTime - log(mpRandomGenerator->getRandomOO()) / mA0;

      // We are sure that we have at least 1 reaction
      mNextReactionIndex = 0;

      C_FLOAT64 sum = 0.0;
      C_FLOAT64 rand = mpRandomGenerator->getRandomOO() * mA0;

      const C_FLOAT64 * pAmu = mAmu.array();
      const C_FLOAT64 * pAmuEnd = pAmu + mNumReactions;

      for (; (sum < rand) && (pAmu != pAmuEnd); ++pAmu, ++mNextReactionIndex)
        {
          sum += *pAmu;
        }

      mNextReactionIndex--;
    }

  if (mNextReactionTime >= endTime)
    {
      return endTime - curTime;
    }

  *mpContainerStateTime = mNextReactionTime;
  mReactions[mNextReactionIndex].fire();
  mpContainer->applyUpdateSequence(mUpdateSequences[mNextReactionIndex]);

  // calculate the total propensity
  mA0 = 0.0;

  const C_FLOAT64 * pAmu = mAmu.array();
  const C_FLOAT64 * pAmuEnd = pAmu + mNumReactions;

  for (; pAmu != pAmuEnd; ++pAmu)
    {
      mA0 += *pAmu;
    }

  mNextReactionIndex = C_INVALID_INDEX;

  return mNextReactionTime - curTime;
}
