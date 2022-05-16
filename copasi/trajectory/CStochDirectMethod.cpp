// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/copasi.h"
#include "CStochDirectMethod.h"
#include "copasi/core/CDataVector.h"
#include "copasi/function/CFunction.h"
#include "copasi/randomGenerator/CRandom.h"
#include "CTrajectoryMethod.h"
#include "CTrajectoryProblem.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/model/CState.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CModel.h"

CStochDirectMethod::CStochDirectMethod(const CDataContainer * pParent,
                                       const CTaskEnum::Method & methodType,
                                       const CTaskEnum::Task & taskType):
  CTrajectoryMethod(pParent, methodType, taskType),
  mpRandomGenerator(NULL),
  mNumReactions(0),
  mMaxSteps(1000000),
  mNextReactionTime(0.0),
  mNextReactionIndex(C_INVALID_INDEX),
  mA0(0.0),
  mReactions(),
  mPropensityObjects(),
  mPropensityIdx(),
  mAmu(),
  mUpdateSequences(),
  mUpdateTimeDependentRoots(),
  mHaveTimeDependentRoots(false),
  mpRootValueCalculator(NULL),
  mMaxStepsReached(false),
  mTargetTime(0.0),
  mNumRoot(0),
  mRootsA(),
  mRootsB(),
  mRootsNonZero(),
  mpRootValueOld(NULL),
  mpRootValueNew(NULL),
  mLastRootTime(-std::numeric_limits< C_FLOAT64 >::infinity())
{
  initializeParameter();
}

CStochDirectMethod::CStochDirectMethod(const CStochDirectMethod & src,
                                       const CDataContainer * pParent):
  CTrajectoryMethod(src, pParent),
  mpRandomGenerator(NULL),
  mNumReactions(0),
  mMaxSteps(1000000),
  mNextReactionTime(0.0),
  mNextReactionIndex(C_INVALID_INDEX),
  mA0(0.0),
  mReactions(),
  mPropensityObjects(),
  mPropensityIdx(),
  mAmu(),
  mUpdateSequences(),
  mUpdateTimeDependentRoots(),
  mHaveTimeDependentRoots(false),
  mpRootValueCalculator(NULL),
  mMaxStepsReached(false),
  mTargetTime(src.mTargetTime),
  mNumRoot(src.mNumRoot),
  mRootsA(src.mRootsA),
  mRootsB(src.mRootsB),
  mRootsNonZero(src.mRootsNonZero),
  mpRootValueOld(NULL),
  mpRootValueNew(NULL)
{
  initializeParameter();
}

CStochDirectMethod::~CStochDirectMethod()
{
  if (mRootsFound.array() != NULL)
    {
      delete [] mRootsFound.array();
    }
}

void CStochDirectMethod::initializeParameter()
{
  assertParameter("Max Internal Steps", CCopasiParameter::Type::INT, (C_INT32) 1000000);
  assertParameter("Use Random Seed", CCopasiParameter::Type::BOOL, false);
  assertParameter("Random Seed", CCopasiParameter::Type::UINT, (unsigned C_INT32) 1);

  mpRootValueCalculator = new CBrent::EvalTemplate< CStochDirectMethod >(this, &CStochDirectMethod::rootValue);
}

bool CStochDirectMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

CTrajectoryMethod::Status CStochDirectMethod::step(const double & deltaT,
    const bool & /* final */)
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

      if (mpProblem->getAutomaticStepSize())
        {
          break;
        }

      if (++mSteps > mMaxSteps)
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 12);
        }
    }

  return NORMAL;
}

void CStochDirectMethod::start()
{
  CTrajectoryMethod::start();

  /* get configuration data */
  mMaxSteps = getValue< C_INT32 >("Max Internal Steps");

  mpRandomGenerator = &mpContainer->getRandomGenerator();

  if (getValue< bool >("Use Random Seed"))
    {
      mpRandomGenerator->initialize(getValue< unsigned C_INT32 >("Random Seed"));
    }

  //mpCurrentState is initialized. This state is not used internally in the
  //stochastic solver, but it is used for returning the result after each step.

  //========Initialize Roots Related Arguments========
  mNumRoot = mpContainer->getRoots().size();

  if (mRootsFound.array() != NULL)
    {
      delete [] mRootsFound.array();
    }

  mRootsFound.initialize(mNumRoot, new C_INT[mNumRoot]);
  mRootsA.resize(mNumRoot);
  mRootsB.resize(mNumRoot);
  mpRootValueNew = &mRootsA;
  mpRootValueOld = &mRootsB;
  mRootsNonZero.resize(mNumRoot);
  mRootsNonZero = 0.0;
  mLastRootTime = -std::numeric_limits< C_FLOAT64 >::infinity();

  CMathObject * pRootObject = mpContainer->getMathObject(mpContainer->getRoots().array());
  CMathObject * pRootObjectEnd = pRootObject + mNumRoot;

  CObjectInterface::ObjectSet Requested;

  for (; pRootObject != pRootObjectEnd; ++pRootObject)
    {
      Requested.insert(pRootObject);
    }

  CObjectInterface::ObjectSet Changed;

  // Determine whether we have time dependent roots;

  CMathObject * pTimeObject = mpContainer->getMathObject(mpContainerStateTime);
  Changed.insert(pTimeObject);

  mpContainer->getTransientDependencies().getUpdateSequence(mUpdateTimeDependentRoots, CCore::SimulationContext::Default, Changed, Requested);
  mHaveTimeDependentRoots = (mUpdateTimeDependentRoots.size() > 0);

  // Build the reaction dependencies
  mReactions.initialize(mpContainer->getReactions());
  mNumReactions = mReactions.size();
  mAmu.initialize(mpContainer->getPropensities());
  mPropensityObjects.initialize(mAmu.size(), mpContainer->getMathObject(mAmu.array()));
  mUpdateSequences.resize(mNumReactions);

  CMathReaction * pReaction = mReactions.array();
  CMathReaction * pReactionEnd = pReaction + mNumReactions;
  CCore::CUpdateSequence * pUpdateSequence = mUpdateSequences.array();
  CMathObject * pPropensityObject = mPropensityObjects.array();
  CMathObject * pPropensityObjectEnd = pPropensityObject + mPropensityObjects.size();

  for (; pPropensityObject != pPropensityObjectEnd; ++pPropensityObject)
    {
      Requested.insert(pPropensityObject);
    }

  mPropensityIdx.resize(mNumReactions);
  size_t i = 0;

  for (; pReaction  != pReactionEnd; ++pReaction, ++pUpdateSequence, ++i)
    {
      Changed = pReaction->getChangedObjects();
      mPropensityIdx[i] = i;
      // The time is always updated
      Changed.insert(pTimeObject);

      pUpdateSequence->clear();
      mpContainer->getTransientDependencies().getUpdateSequence(*pUpdateSequence, CCore::SimulationContext::Default, Changed, Requested);
    }

  mMaxStepsReached = false;

  mTargetTime = *mpContainerStateTime;
  mNextReactionTime = *mpContainerStateTime;
  mNextReactionIndex = C_INVALID_INDEX;

  stateChange(CMath::eStateChange::State);

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
  if (mpContainer->getCountODEs() > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 28);
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

  if (getValue< C_INT32 >("Max Internal Steps") <= 0)
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
      if (std::isnan(mA0))
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 27);
        }

      mNextReactionTime = startTime - log(mpRandomGenerator->getRandomOO()) / mA0;

      // We are sure that we have at least 1 reaction
      C_FLOAT64 rand = mpRandomGenerator->getRandomOO() * mA0;
      size_t * idxProp = mPropensityIdx.begin();
      C_FLOAT64 sum = 0.0;

      for (size_t i = 0; i != mNumReactions; ++idxProp, ++i)
        {
          sum += mAmu[*idxProp];

          if (sum > rand) break;

          if (i != 0 && mAmu[*idxProp] > mAmu[*(idxProp - 1)])
            std::swap(*idxProp, *(idxProp - 1));
        }

      if (idxProp == mPropensityIdx.end())
        --idxProp;

      mNextReactionIndex = *(idxProp);
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
          CBrent::findRoot(startTime, mNextReactionTime, mpRootValueCalculator, &RootTime, &RootValue, 1e-9);

          if (RootTime > endTime)
            {
              *mpContainerStateTime = endTime;
              mpContainer->applyUpdateSequence(mUpdateTimeDependentRoots);
              *mpRootValueNew = mpContainer->getRoots();
              mStatus = NORMAL;

              return endTime - startTime;
            }

          // If the last root time is equal to the current one we have already dealt with it and can proceed.
          // This is a save assumptions since reaction events advance the time and discrete events reset mLastRootTime.
          if (mLastRootTime < RootTime)
            {
              mLastRootTime = RootTime;
              *mpContainerStateTime = RootTime;
              mpContainer->applyUpdateSequence(mUpdateTimeDependentRoots);
              *mpRootValueNew = mpContainer->getRoots();

              // Mark the appropriate root
              C_INT * pRootFound = mRootsFound.array();
              C_INT * pRootFoundEnd = pRootFound + mNumRoot;
              C_FLOAT64 * pRootValue = mpRootValueNew->array();

              for (; pRootFound != pRootFoundEnd; ++pRootFound, ++pRootValue)
                if (*pRootValue == RootValue || *pRootValue == -RootValue)
                  {
                    *pRootFound = static_cast< C_INT >(CMath::RootToggleType::ToggleBoth);
                  }
                else
                  {
                    *pRootFound = static_cast< C_INT >(CMath::RootToggleType::NoToggle);
                  }

              mStatus = ROOT;

              return RootTime - startTime;
            }
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

  for (; pRootFound != pRootFoundEnd; pRootValueOld++, pRootValueNew++, pRootFound++, pRootNonZero++, pIsDiscrete++, pIsTimeDependent++)
    {
      if (*pRootValueOld **pRootValueNew < 0.0 ||
          (*pRootValueNew == 0.0 && *pIsTimeDependent && !*pIsDiscrete))
        {
          // These root changes are not caused by the time alone as those are handled in do single step.
          hasRoots = true;
          *pRootFound = static_cast< C_INT >(CMath::RootToggleType::ToggleBoth);
        }
      else if (*pRootValueNew == 0.0 &&
               *pRootValueOld != 0.0)
        {
          hasRoots = true;
          *pRootFound = static_cast< C_INT >(CMath::RootToggleType::ToggleEquality); // toggle only equality
          *pRootNonZero = *pRootValueOld;
        }
      else if (*pRootValueNew != 0.0 &&
               *pRootValueOld == 0.0 &&
               *pRootValueNew **pRootNonZero < 0.0)
        {
          hasRoots = true;
          *pRootFound = static_cast< C_INT >(CMath::RootToggleType::ToggleInequality); // toggle only inequality
        }
      else
        {
          *pRootFound = static_cast< C_INT >(CMath::RootToggleType::NoToggle);
        }
    }

  return hasRoots;
}

/**
 * Update model state after one events happened
 */
void CStochDirectMethod::stateChange(const CMath::StateChange & change)
{
  if (change & (CMath::StateChange(CMath::eStateChange::FixedEventTarget) | CMath::eStateChange::State | CMath::eStateChange::ContinuousSimulation | CMath::eStateChange::EventSimulation))
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
          pPropensityObject->calculateValue();
          mA0 += *pAmu;
        }

      mNextReactionIndex = C_INVALID_INDEX;
      *mpRootValueNew = mpContainer->getRoots();
      mLastRootTime = -std::numeric_limits< C_FLOAT64 >::infinity();
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
  C_FLOAT64 RootValue;

  for (; pRoot != pRootEnd; ++pRoot, ++pRootOld, ++pRootNew)
    {
      // We are only looking for roots which change sign in [pOld, pNew]
      if (*pRootOld **pRootNew < 0 || *pRootNew == 0)
        {
          // Assure that the RootValue is increasing between old and new for each
          // candidate root.
          RootValue = (*pRootNew >= *pRootOld) ? *pRoot : -*pRoot;

          if (RootValue > MaxRootValue)
            {
              MaxRootValue = RootValue;
            }
        }
    }

  return MaxRootValue;
}
