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

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243)
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
#endif  // WIN32

#include <limits>

#include <vector>
#include <numeric>
#include <limits>
#include <set>
#include <string>
#include <cmath>

#include "copasi/copasi.h"

#include "CTrajAdaptiveSA.h"
#include "CTrajectoryProblem.h"

#include "copasi/core/CDataVector.h"
#include "copasi/function/CFunction.h"
#include "copasi/randomGenerator/CRandom.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/math/CMathReaction.h"
#include "copasi/model/CModel.h"

CTrajAdaptiveSA::CTrajAdaptiveSA(const CDataContainer * pParent,
                                 const CTaskEnum::Method & methodType,
                                 const CTaskEnum::Task & taskType):
  CTrajectoryMethod(pParent, methodType, taskType),
  mMaxReactionFiring(0),
  mReactionFiring(0),
  mPartitionedReactionFiring(0),
  mAvgDX(0),
  mSigDX(0),
  mpMethodSpecies(NULL),
  mpRandomGenerator(NULL),
  mNumReactions(0),
  mNumReactionSpecies(0),
  mMaxSteps(1000000),
  mNextReactionTime(0.0),
  mNextReactionIndex(C_INVALID_INDEX),
  mAmu(0),
  mPartitionedAmu(0),
  mMethodState(),
  mPartitionedDependencies(0),
  mA0(0.0),
  mMaxStepsReached(false)
{
  initializeParameter();
}

CTrajAdaptiveSA::CTrajAdaptiveSA(const CTrajAdaptiveSA & src,
                                 const CDataContainer * pParent):
  CTrajectoryMethod(src, pParent),
  mMaxReactionFiring(src.mMaxReactionFiring),
  mReactionFiring(src.mReactionFiring),
  mPartitionedReactionFiring(src.mPartitionedReactionFiring),
  mAvgDX(src.mAvgDX),
  mSigDX(src.mSigDX),
  mpMethodSpecies(src.mpMethodSpecies),
  mpRandomGenerator(NULL),
  mNumReactions(src.mNumReactions),
  mNumReactionSpecies(src.mNumReactionSpecies),
  mMaxSteps(src.mMaxSteps),
  mNextReactionTime(src.mNextReactionTime),
  mNextReactionIndex(src.mNextReactionIndex),
  mReactions(),
  mPropensityObjects(),
  mAmu(),
  mPartitionedAmu(src.mPartitionedAmu),
  mMethodState(src.mMethodState),
  mPartitionedDependencies(src.mPartitionedDependencies),
  mA0(src.mA0),
  mMaxStepsReached(src.mMaxStepsReached)
{
  initializeParameter();
}

CTrajAdaptiveSA::~CTrajAdaptiveSA()
{}

void CTrajAdaptiveSA::initializeParameter()
{
  assertParameter("Epsilon", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) EPS);
  assertParameter("Max Internal Steps", CCopasiParameter::Type::INT, (C_INT32) 1000000);
  assertParameter("Use Random Seed", CCopasiParameter::Type::BOOL, false);
  assertParameter("Random Seed", CCopasiParameter::Type::UINT, (unsigned C_INT32) 1);
}

bool CTrajAdaptiveSA::elevateChildren()
{
  initializeParameter();
  return true;
}

CTrajectoryMethod::Status CTrajAdaptiveSA::step(const double & deltaT,
    const bool & /* final */)
{
  // do several steps
  C_FLOAT64 Time = *mpContainerStateTime;
  C_FLOAT64 EndTime = Time + deltaT;

  size_t Steps = 0;

  while (Time < EndTime)
    {
      if (mSSAStepCounter > 0)
        {
          Time += doSingleSSAStep(Time, EndTime);
          mSSAStepCounter--;
        }
      else
        {
          Time += doSingleTauLeapStep(Time, EndTime);
        }

      if (++Steps > mMaxSteps)
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 12);
        }

      if (mpProblem->getAutomaticStepSize()) break;
    }

  *mpContainerStateTime = Time;

  return NORMAL;
}

void CTrajAdaptiveSA::start()
{
  CTrajectoryMethod::start();

  /* get configuration data */

  mpRandomGenerator = &mpContainer->getRandomGenerator();

  bool useRandomSeed = getValue< bool >("Use Random Seed");
  unsigned C_INT32 randomSeed = getValue< unsigned C_INT32 >("Random Seed");

  if (useRandomSeed) mpRandomGenerator->initialize(randomSeed);

  mMaxSteps = getValue< C_INT32 >("Max Internal Steps");
  mEpsilon = getValue< C_FLOAT64 >("Epsilon");

  //initialize the vector of ints that contains the particle numbers
  //for the discrete simulation. This also floors all particle numbers in the model.

  // Size the arrays
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
  CObjectInterface::ObjectSet Requested;

  for (; pPropensityObject != pPropensityObjectEnd; ++pPropensityObject)
    {
      Requested.insert(pPropensityObject);
    }

  CObjectInterface::ObjectSet Changed;
  CMathObject * pTimeObject = mpContainer->getMathObject(mpContainerStateTime);
  pPropensityObject = mPropensityObjects.array();

  for (; pReaction  != pReactionEnd; ++pReaction, ++pUpdateSequence, ++pPropensityObject)
    {
      Changed = pReaction->getChangedObjects();

      // The time is always updated
      Changed.insert(pTimeObject);

      pUpdateSequence->clear();
      mpContainer->getTransientDependencies().getUpdateSequence(*pUpdateSequence, CCore::SimulationContext::Default, Changed, Requested);
    }

  mNumReactionSpecies = mpContainer->getCountIndependentSpecies() + mpContainer->getCountDependentSpecies();
  mFirstReactionSpeciesIndex = mpContainer->getCountFixedEventTargets() + 1 /* Time */ + mpContainer->getCountODEs();

  mPartitionedDependencies.resize(mNumReactions);
  mMaxReactionFiring.resize(mNumReactions);
  mPartitionedAmu.resize(mNumReactions);
  mReactionFiring.resize(mNumReactions);
  mPartitionedReactionFiring.resize(mNumReactions);

  mAmu = 0.0;

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

  pPropensityObject = mPropensityObjects.array();
  C_FLOAT64 * pAmu = mAmu.array();
  mA0 = 0.0;

  // Update the propensity
  for (; pPropensityObject != pPropensityObjectEnd; ++pPropensityObject, ++pAmu)
    {
      pPropensityObject->calculateValue();
      mA0 += *pAmu;
    }

  mMaxStepsReached = false;
  mNextReactionTime = *mpContainerStateTime;
  mNextReactionIndex = C_INVALID_INDEX;

  mSSAStepCounter = 0;

  return;
}

// virtual
bool CTrajAdaptiveSA::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CTrajectoryMethod::isValidProblem(pProblem)) return false;

  const CTrajectoryProblem * pTP = dynamic_cast<const CTrajectoryProblem *>(pProblem);

  if (pTP->getDuration() < 0.0)
    {
      //back integration not possible
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 9);
      return false;
    }

  if (mpContainer->getReactions().size() < 1)
    {
      //at least one reaction necessary
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 17);
      return false;
    }

  // check for ODEs
  if (mpContainer->getCountODEs() > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 28);
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
      CCopasiMessage(CCopasiMessage::EXCEPTION, message.c_str());
      return false;
    }

  if (getValue< C_INT32 >("Max Internal Steps") <= 0)
    {
      //max steps should be at least 1
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 15);
      return false;
    }

  return true;
}

C_FLOAT64 CTrajAdaptiveSA::doSingleTauLeapStep(const C_FLOAT64 & curTime, const C_FLOAT64 & endTime)
{
  CMathReaction * pReaction = mReactions.array();
  CMathReaction * pReactionEnd = pReaction + mReactions.size();
  size_t * pMaxReactionFiring = mMaxReactionFiring.array();

  for (; pReaction != pReactionEnd; ++pReaction, ++pMaxReactionFiring)
    {
      *pMaxReactionFiring = std::numeric_limits< size_t >::max(); // Assigned a maximum value

      const CMathReaction::SpeciesBalance * it = pReaction->getNumberBalance().array();
      const CMathReaction::SpeciesBalance * end = it + pReaction->getNumberBalance().size();

      for (; it != end; ++it)
        {
          if (it->second < 0)
            {
              size_t TmpMax;

              if ((TmpMax = (size_t) fabs(*it->first / it->second)) < *pMaxReactionFiring)
                {
                  *pMaxReactionFiring = TmpMax;
                }
            }
        }
    }

  size_t NonCriticalReactions = 0;
  size_t InsertCritical = mNumReactions - 1;

  pReaction = mReactions.array();
  pMaxReactionFiring = mMaxReactionFiring.array();
  C_FLOAT64 * pReactionFiring = mReactionFiring.array();
  const C_FLOAT64 * pAmu = mAmu.array();

  for (; pReaction != pReactionEnd; ++pReaction, ++pMaxReactionFiring, ++pAmu, ++pReactionFiring)
    {
      *pReactionFiring = 0;

      if (*pAmu == 0 ||
          *pMaxReactionFiring > UPPER_LIMIT)
        {
          mPartitionedDependencies[NonCriticalReactions] = pReaction;
          mPartitionedAmu[NonCriticalReactions] = pAmu;
          mPartitionedReactionFiring[NonCriticalReactions] = pReactionFiring;
          NonCriticalReactions++;
        }
      else
        {
          mPartitionedDependencies[InsertCritical] = pReaction;
          mPartitionedAmu[InsertCritical] = pAmu;
          mPartitionedReactionFiring[InsertCritical] = pReactionFiring;
          InsertCritical--;
        }
    }

  mAvgDX = 0.0;
  mSigDX = 0.0;

  CMathReaction **ppOrderedReactions = mPartitionedDependencies.array();
  const C_FLOAT64 ** ppOrderedAmu = mPartitionedAmu.array();
  const C_FLOAT64 ** ppOrderedAmuEnd = ppOrderedAmu + NonCriticalReactions;
  const C_FLOAT64 * pFirstSpecies = mContainerState.array() + mFirstReactionSpeciesIndex;

  for (; ppOrderedAmu != ppOrderedAmuEnd; ++ppOrderedReactions, ++ppOrderedAmu)
    {
      const CMathReaction::SpeciesBalance * it = (*ppOrderedReactions)->getNumberBalance().array();
      const CMathReaction::SpeciesBalance * end = it + (*ppOrderedReactions)->getNumberBalance().size();

      for (; it != end; ++it)
        {
          mAvgDX[it->first - pFirstSpecies] += **ppOrderedAmu * it->second;
          mSigDX[it->first - pFirstSpecies] += **ppOrderedAmu * it->second * it->second;
        }
    }

  C_FLOAT64 MaxTau;

  if (NonCriticalReactions == 0)
    {
      MaxTau = 0;
    }
  else
    {
      const C_FLOAT64 * pSpecies = mContainerState.array() + mFirstReactionSpeciesIndex;
      const C_FLOAT64 * pSpeciesEnd = pSpecies + mNumReactionSpecies;
      C_FLOAT64 * pAvgDX = mAvgDX.array();
      C_FLOAT64 * pSigDX = mSigDX.array();

      C_FLOAT64 ex, t1, t2;
      t1 = t2 = std::numeric_limits< C_FLOAT64 >::infinity();

      for (; pSpecies != pSpeciesEnd; ++pSpecies, ++pAvgDX, ++pSigDX)
        {
          C_FLOAT64 t3, t4, t5, t6;

          ex = (*pSpecies * mEpsilon) + 1.0;
          t3 = fabs(*pAvgDX);
          t4 = *pSigDX;
          t5 = ex / t3;
          t6 = ex * ex / t4;

          if (t3 != 0 && t5 < t1) t1 = t5;

          if (t4 != 0 && t6 < t2) t2 = t6;
        }

      if (t1 < t2)
        MaxTau = t1;
      else
        MaxTau = t2;
    }

  if (MaxTau < (SSA_MULTIPLE / mA0) ||
      MaxTau == std::numeric_limits< C_FLOAT64 >::infinity())
    {
      mSSAStepCounter = SSA_UPPER_NUM;

      return 0;
    }

  C_FLOAT64 AmuCritical = 0;
  ppOrderedAmu = mPartitionedAmu.array() + NonCriticalReactions;
  ppOrderedAmuEnd = mPartitionedAmu.array() + mNumReactions;

  for (; ppOrderedAmu != ppOrderedAmuEnd; ++ppOrderedAmu)
    {
      AmuCritical += **ppOrderedAmu;
    }

  C_FLOAT64 CriticalReactionTau;

  if (NonCriticalReactions == mNumReactions || AmuCritical == 0)
    CriticalReactionTau = std::numeric_limits< C_FLOAT64 >::infinity();
  else
    CriticalReactionTau = -log(mpRandomGenerator->getRandomOO()) / AmuCritical;

  bool isUpdated = false;

  C_FLOAT64 Tau;

  while (!isUpdated)
    {
      Tau = MaxTau;

      if (CriticalReactionTau < Tau || Tau == 0) Tau = CriticalReactionTau;

      if ((endTime - curTime) < Tau) Tau = (endTime - curTime);

      // Calculate the firing of non critical reactions
      ppOrderedAmu = mPartitionedAmu.array();
      ppOrderedAmuEnd = mPartitionedAmu.array() + NonCriticalReactions;

      C_FLOAT64 **ppOrderedReactionFiring = mPartitionedReactionFiring.array();

      for (; ppOrderedAmu != ppOrderedAmuEnd; ++ppOrderedAmu, ++ppOrderedReactionFiring)
        {
          C_FLOAT64 Lambda = **ppOrderedAmu * Tau;

          if (Lambda < 0.0)
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 10);
          else if (Lambda > 2.0e9)
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 26);

          **ppOrderedReactionFiring = mpRandomGenerator->getRandomPoisson(Lambda);
        }

      size_t CriticalReactionIndex = C_INVALID_INDEX;

      if (CriticalReactionTau <= Tau)
        {
          // Determine the critical reaction which fires.
          C_FLOAT64 sum = 0;
          C_FLOAT64 rand = mpRandomGenerator->getRandomOO() * AmuCritical;

          ppOrderedAmu = mPartitionedAmu.array() + NonCriticalReactions;
          ppOrderedAmuEnd = mPartitionedAmu.array() + mNumReactions;

          CriticalReactionIndex = NonCriticalReactions;

          for (; (sum < rand) && (ppOrderedAmu != ppOrderedAmuEnd); ++ppOrderedAmu, ++CriticalReactionIndex)
            {
              sum += **ppOrderedAmu;
            }

          CriticalReactionIndex--;
        }

      ppOrderedReactions = mPartitionedDependencies.array();
      CMathReaction **ppOrderedReactionsEnd = ppOrderedReactions + NonCriticalReactions;
      ppOrderedReactionFiring = mPartitionedReactionFiring.array();

      // Before we fire any reaction we save state so that we can undo for the case that
      // we encountered negative particle numbers.
      mMethodState = mpContainer->getState(false);

      for (; ppOrderedReactions != ppOrderedReactionsEnd; ++ppOrderedReactions, ++ppOrderedReactionFiring)
        {
          (*ppOrderedReactions)->fireMultiple(**ppOrderedReactionFiring);
          **ppOrderedReactionFiring = 0.0;
        }

      if (CriticalReactionIndex != C_INVALID_INDEX)
        {
          mPartitionedDependencies[CriticalReactionIndex]->fire();
        }

      const C_FLOAT64 * pSpecies = mContainerState.array() + mFirstReactionSpeciesIndex;
      const C_FLOAT64 * pSpeciesEnd = pSpecies + mNumReactionSpecies;

      for (; pSpecies != pSpeciesEnd; ++pSpecies)
        {
          if (*pSpecies < 0)
            break;
        }

      if (pSpecies != pSpeciesEnd)
        {
          isUpdated = false;
          MaxTau = MaxTau / 2.0;

          mpContainer->setState(mMethodState);
        }
      else
        {
          isUpdated = true;
        }
    }

  // Update the model time (for explicitly time dependent models)
  *mpContainerStateTime = curTime + Tau;
  mpContainer->updateSimulatedValues(false);

  mA0 = 0;

  CMathObject * pPropensity = mPropensityObjects.array();
  CMathObject * pPropensityEnd = pPropensity + mNumReactions;
  pAmu = mAmu.array();

  for (; pPropensity != pPropensityEnd; ++pPropensity, ++pAmu)
    {
      pPropensity->calculateValue();
      mA0 += *pAmu;
    }

  return Tau;
}

C_FLOAT64 CTrajAdaptiveSA::doSingleSSAStep(const C_FLOAT64 & curTime, const C_FLOAT64 & endTime)
{
  if (mNextReactionIndex == C_INVALID_INDEX)
    {
      if (mA0 == 0)
        {
          *mpContainerStateTime = endTime;
          return endTime - curTime;
        }

      // We need to throw an exception if mA0 is NaN
      if (std::isnan(mA0))
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

  *mpContainerStateTime = mNextReactionTime;

  if (mNextReactionTime >= endTime)
    {
      return endTime - curTime;
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

  return mNextReactionTime - curTime;
}
