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

#include "optimization/FminBrent.h"

CStochDirectMethod::CStochDirectMethod(const CCopasiContainer * pParent):
  CTrajectoryMethod(CCopasiMethod::directMethod, pParent),
  mpRandomGenerator(NULL),
  mNumReactions(0),
  mMaxSteps(1000000),
  mNextReactionTime(0.0),
  mNextReactionIndex(C_INVALID_INDEX),
  mA0(0.0),
  mReactions(),
  mPropensityObjects(),
  mAmu(),
  mUpdateSequences(),
  mUpdateTimeDependentRoots(),
  mHaveTimeDependentRoots(false),
  mpRootValueCalculator(NULL),
  mMaxStepsReached(false)
{
  initializeParameter();
}

CStochDirectMethod::CStochDirectMethod(const CStochDirectMethod & src,
                                       const CCopasiContainer * pParent):
  CTrajectoryMethod(src, pParent),
  mpRandomGenerator(NULL),
  mNumReactions(0),
  mMaxSteps(1000000),
  mNextReactionTime(0.0),
  mNextReactionIndex(C_INVALID_INDEX),
  mA0(0.0),
  mReactions(),
  mPropensityObjects(),
  mAmu(),
  mUpdateSequences(),
  mUpdateTimeDependentRoots(),
  mHaveTimeDependentRoots(false),
  mpRootValueCalculator(NULL),
  mMaxStepsReached(false)
{
  initializeParameter();
}

CStochDirectMethod::~CStochDirectMethod()
{}

void CStochDirectMethod::initializeParameter()
{
  assertParameter("Max Internal Steps", CCopasiParameter::INT, (C_INT32) 1000000);
  assertParameter("Use Random Seed", CCopasiParameter::BOOL, false);
  assertParameter("Random Seed", CCopasiParameter::UINT, (unsigned C_INT32) 1);

  mpRootValueCalculator = new FDescentTemplate< CStochDirectMethod >(this, &CStochDirectMethod::rootValue);
}

bool CStochDirectMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

CTrajectoryMethod::Status CStochDirectMethod::step(const double & deltaT)
{
  C_FLOAT64 EndTime = *mpContainerStateTime + deltaT;

  if (mTargetTime != EndTime)
    {
      // We have a new end time and reset the root counter.
      mTargetTime = EndTime;
      mSteps = 0;
    }

  while (*mpContainerStateTime < EndTime)
    {
      // The Container State Time is updated during the reaction firing or root interpolation
      doSingleStep(*mpContainerStateTime, EndTime);

      if (mStatus == ROOT ||
          (mNumRoot > 0 && checkRoots()))
        {
          return ROOT;
        }

      if (++mSteps > mMaxSteps)
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

  mpRandomGenerator = &mpContainer->getRandomGenerator();

  bool useRandomSeed = * getValue("Use Random Seed").pBOOL;
  unsigned C_INT32 randomSeed = * getValue("Random Seed").pUINT;

  if (useRandomSeed) mpRandomGenerator->initialize(randomSeed);

  //mpCurrentState is initialized. This state is not used internally in the
  //stochastic solver, but it is used for returning the result after each step.
  mContainerState = initialState;

  //========Initialize Roots Related Arguments========
  mNumRoot = mpContainer->getRoots().size();
  mRootsFound.resize(mNumRoot);
  mRootsA.resize(mNumRoot);
  mRootsB.resize(mNumRoot);
  mpRootValueNew = &mRootsA;
  mpRootValueOld = &mRootsB;
  mRootsNonZero.resize(mNumRoot);
  mRootsNonZero = 0.0;

  CMathObject * pRootObject = mpContainer->getMathObject(mpContainer->getRoots().array());
  CMathObject * pRootObjectEnd = pRootObject + mNumRoot;

  CObjectInterface::ObjectSet Requested;

  for (; pRootObject != pRootObjectEnd; ++pRootObject)
    {
      Requested.insert(pRootObject);
    }

  CObjectInterface::ObjectSet Changed;

  // Determine whether we have time dependent roots;

  CObjectInterface * pTimeObject = mpContainer->getMathObject(mpContainerStateTime);
  Changed.insert(pTimeObject);

  mpContainer->getTransientDependencies().getUpdateSequence(mUpdateTimeDependentRoots, CMath::Default, Changed, Requested);
  mHaveTimeDependentRoots = (mUpdateTimeDependentRoots.size() > 0);

  // Build the reaction dependencies
  mReactions.initialize(mpContainer->getReactions());
  mNumReactions = mReactions.size();
  mAmu.initialize(mpContainer->getPropensities());
  mPropensityObjects.initialize(mAmu.size(), mpContainer->getMathObject(mAmu.array()));
  mUpdateSequences.resize(mNumReactions);

  CMathReaction * pReaction = mReactions.array();
  CMathReaction * pReactionEnd = pReaction + mNumReactions;
  CObjectInterface::UpdateSequence * pUpdateSequence = mUpdateSequences.array();
  CMathObject * pPropensityObject = mPropensityObjects.array();
  CMathObject * pPropensityObjectEnd = pPropensityObject + mPropensityObjects.size();

  for (; pPropensityObject != pPropensityObjectEnd; ++pPropensityObject)
    {
      Requested.insert(pPropensityObject);
    }

  pPropensityObject = mPropensityObjects.array();

  for (; pReaction  != pReactionEnd; ++pReaction, ++pUpdateSequence, ++pPropensityObject)
    {
      Changed = pReaction->getChangedObjects();

      // The time is always updated
      Changed.insert(pTimeObject);

      pUpdateSequence->clear();
      mpContainer->getTransientDependencies().getUpdateSequence(*pUpdateSequence, CMath::Default, Changed, Requested);
    }

  mMaxStepsReached = false;

  mNextReactionTime = *mpContainerStateTime;
  mNextReactionIndex = C_INVALID_INDEX;

  stateChange(CMath::State);

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

  // check for ODEs
  if (pTP->getModel()->getMathContainer().getCountODEs() > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 28);
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

  return true;
}

C_FLOAT64 CStochDirectMethod::doSingleStep(C_FLOAT64 startTime, const C_FLOAT64 & endTime)
{
  if (mNextReactionIndex == C_INVALID_INDEX)
    {
      if (mA0 == 0)
        {
          *mpContainerStateTime = endTime;
          return endTime - startTime;
        }

      // We need to throw an exception if mA0 is NaN
      if (isnan(mA0))
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 27);
        }

      mNextReactionTime = startTime - log(mpRandomGenerator->getRandomOO()) / mA0;

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

  *mpContainerStateTime = mNextReactionTime;

  // Check whether any time dependent root changes sign in curTime, mNextReactionTime.
  // If we need to interpolate return with that time value without firing any reaction

  if (mHaveTimeDependentRoots)
    {
      mpContainer->applyUpdateSequence(mUpdateTimeDependentRoots);

      if (checkRoots())
        {
          // Interpolate to find the first root
          C_FLOAT64 RootTime;
          C_FLOAT64 RootValue;
          Brent(startTime, mNextReactionTime, mpRootValueCalculator, &RootTime, &RootValue, 1e-6 * startTime, 0);

          if (RootTime > endTime)
            {
              *mpContainerStateTime = endTime;
              mpContainer->applyUpdateSequence(mUpdateTimeDependentRoots);
              *mpRootValueNew = mpContainer->getRoots();
              mStatus = NORMAL;

              return endTime - startTime;
            }

          *mpContainerStateTime = RootTime;
          mpContainer->applyUpdateSequence(mUpdateTimeDependentRoots);
          *mpRootValueNew = mpContainer->getRoots();

          // Mark the appropriate root
          C_INT * pRootFound = mRootsFound.array();
          C_INT * pRootFoundEnd = pRootFound + mNumRoot;
          C_FLOAT64 * pRootValue = mpRootValueNew->array();

          for (; pRootFound != pRootFoundEnd; ++pRootFound, ++pRootValue)
            {
              if (*pRootValue == RootValue || *pRootValue == -RootValue)
                {
                  *pRootFound = CMath::ToggleBoth;
                }
              else
                {
                  *pRootFound = CMath::NoToggle;
                }
            }

          mStatus = ROOT;

          return RootTime - startTime;
        }
    }

  if (mNextReactionTime >= endTime)
    {
      *mpContainerStateTime = endTime;
      mStatus = NORMAL;
      return endTime - startTime;
    }

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
  mStatus = NORMAL;

  return mNextReactionTime - startTime;
}

/**
 * Check whether a root has been found
 */
bool CStochDirectMethod::checkRoots()
{
  bool hasRoots = false;

  // Swap old an new for the next call.
  CVector< C_FLOAT64 > * pTmp = mpRootValueOld;
  mpRootValueOld = mpRootValueNew;
  mpRootValueNew = pTmp;

  *mpRootValueNew = mpContainer->getRoots();

  C_FLOAT64 *pRootValueOld = mpRootValueOld->array();
  C_FLOAT64 *pRootValueNew = mpRootValueNew->array();
  C_FLOAT64 *pRootNonZero = mRootsNonZero.array();

  C_INT *pRootFound    = mRootsFound.array();
  C_INT *pRootFoundEnd    = pRootFound + mRootsFound.size();

  const bool * pIsDiscrete = mpContainer->getRootIsDiscrete().array();
  const bool * pIsTimeDependent = mpContainer->getRootIsTimeDependent().array();

  for (; pRootFound != pRootFoundEnd; pRootValueOld++, pRootValueNew++, pRootFound++, pRootNonZero++)
    {
      if (*pRootValueOld * *pRootValueNew < 0.0 ||
          (*pRootValueNew == 0.0 && *pIsTimeDependent && !*pIsDiscrete))
        {
          // These root changes are not caused by the time alone as those are handled in do single step.
          hasRoots = true;
          *pRootFound = CMath::ToggleBoth;
        }
      else if (*pRootValueNew == 0.0 &&
               *pRootValueOld != 0.0)
        {
          hasRoots = true;
          *pRootFound = CMath::ToggleEquality; // toggle only equality
          *pRootNonZero = *pRootValueOld;
        }
      else if (*pRootValueNew != 0.0 &&
               *pRootValueOld == 0.0 &&
               *pRootValueNew * *pRootNonZero < 0.0)
        {
          hasRoots = true;
          *pRootFound = CMath::ToggleInequality; // toggle only inequality
        }
      else
        {
          *pRootFound = CMath::NoToggle;
        }
    }

  return hasRoots;
}

/**
 * Update model state after one events happened
 */
void CStochDirectMethod::stateChange(const CMath::StateChange & change)
{
  if (change & (CMath::ContinuousSimulation | CMath::State))
    {
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

      CMathObject * pPropensityObject = mPropensityObjects.array();
      CMathObject * pPropensityObjectEnd = pPropensityObject + mPropensityObjects.size();
      C_FLOAT64 * pAmu = mAmu.array();
      mA0 = 0.0;

      // Update the propensity
      for (; pPropensityObject != pPropensityObjectEnd; ++pPropensityObject, ++pAmu)
        {
          pPropensityObject->calculate();
          mA0 += *pAmu;
        }

      mNextReactionIndex = C_INVALID_INDEX;
      *mpRootValueNew = mpContainer->getRoots();
    }

  mMaxStepsReached = false;
}

C_FLOAT64 CStochDirectMethod::rootValue(const C_FLOAT64 & time)
{
  *mpContainerStateTime = time;
  mpContainer->applyUpdateSequence(mUpdateTimeDependentRoots);

  const C_FLOAT64 * pRoot = mpContainer->getRoots().array();
  const C_FLOAT64 * pRootEnd = pRoot + mNumRoot;
  const C_FLOAT64 * pRootOld = mpRootValueOld->array();
  const C_FLOAT64 * pRootNew = mpRootValueNew->array();

  C_FLOAT64 MaxRootValue = - std::numeric_limits< C_FLOAT64 >::infinity();

  for (; pRoot != pRootEnd; ++pRoot, ++pRootOld, ++pRootNew)
    {
      // We are only looking for roots which change sign in [pOld, pNew]
      if (*pRootOld * *pRootNew < 0)
        {
          C_FLOAT64 RootValue = (*pRootNew > 0) ? *pRoot : -*pRoot;

          if (RootValue > MaxRootValue)
            {
              MaxRootValue = RootValue;
            }
        }
    }

  return MaxRootValue;
}
