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

/**
 *   CTrajectoryMethodDsaLsodar
 *
 *   This class implements an hybrid algorithm for the simulation of a
 *   biochemical system over time.
 */

/* DEFINE ********************************************************************/

#ifdef WIN32
#if _MSC_VER < 1600
#define min _cpp_min
#define max _cpp_max
#endif // _MSC_VER
#endif // WIN32

#include <limits.h>

#include "copasi/copasi.h"

#include "CTrajectoryMethodDsaLsodar.h"
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
#include "copasi/utilities/CVersion.h"

CTrajectoryMethodDsaLsodar::CPartition::CPartition():
  mSpeciesToReactions(),
  mLowerThreshold(),
  mUpperThreshold(),
  mFirstReactionSpeciesIndex(C_INVALID_INDEX),
  mNumReactionSpecies(0),
  mStochasticReactions(0),
  mDeterministicReactions(0),
  mStochasticSpecies(0),
  mHasStochastic(false),
  mHasDeterministic(false),
  mNumLowSpecies(0),
  mpContainer(NULL),
  mpFirstReactionValue(NULL)
{}

CTrajectoryMethodDsaLsodar::CPartition::CPartition(const CTrajectoryMethodDsaLsodar::CPartition & src):
  mSpeciesToReactions(src.mSpeciesToReactions),
  mLowerThreshold(src.mLowerThreshold),
  mUpperThreshold(src.mUpperThreshold),
  mFirstReactionSpeciesIndex(C_INVALID_INDEX),
  mNumReactionSpecies(src.mNumReactionSpecies),
  mStochasticReactions(src.mStochasticReactions),
  mDeterministicReactions(src.mDeterministicReactions),
  mStochasticSpecies(src.mStochasticSpecies),
  mHasStochastic(src.mHasStochastic),
  mHasDeterministic(src.mHasDeterministic),
  mNumLowSpecies(src.mNumLowSpecies),
  mpContainer(src.mpContainer),
  mpFirstReactionValue(src.mpFirstReactionValue)
{}

CTrajectoryMethodDsaLsodar::CPartition::~CPartition()
{}

void CTrajectoryMethodDsaLsodar::CPartition::intialize(const CMathContainer * pContainer,
    const C_FLOAT64 & lowerThreshold,
    const C_FLOAT64 & upperThreshold)
{
  mpContainer = pContainer;
  mLowerThreshold = lowerThreshold;
  mUpperThreshold = upperThreshold;

  mFirstReactionSpeciesIndex = mpContainer->getCountFixedEventTargets() + 1 /* Time */ + mpContainer->getCountODEs();
  mpFirstReactionValue = mpContainer->getState(false).array() + mFirstReactionSpeciesIndex;
  mNumReactionSpecies = mpContainer->getCountIndependentSpecies() + mpContainer->getCountDependentSpecies();

  const CVector< CMathReaction > & reactions = mpContainer->getReactions();

  mStochasticReactions.resize(reactions.size());
  mStochasticReactions = NULL;

  mDeterministicReactions.resize(reactions.size());
  mDeterministicReactions = NULL;

  mNumLowSpecies.resize(reactions.size());
  mNumLowSpecies = 0;

  mStochasticSpecies.resize(mNumReactionSpecies);
  mStochasticSpecies = false;

  mHasStochastic = false;
  mHasDeterministic = false;

  mSpeciesToReactions.clear();
  const CMathReaction * pReaction = reactions.array();
  const CMathReaction * pReactionEnd = pReaction + reactions.size();

  for (size_t Index = 0; pReaction != pReactionEnd; ++pReaction, ++Index)
    {
      const CMathReaction::SpeciesBalance * itBalance = pReaction->getNumberBalance().array();
      const CMathReaction::SpeciesBalance * endBalance = itBalance + pReaction->getNumberBalance().size();

      for (; itBalance != endBalance; ++itBalance)
        {
          mSpeciesToReactions.insert(std::pair< size_t, size_t * >(itBalance->first - mpFirstReactionValue,
                                     mNumLowSpecies.array() + Index));
        }
    }

  // Create the initial partition by first counting species with low particle number per reaction
  const C_FLOAT64 * pValue = mpContainer->getState(false).array() + mFirstReactionSpeciesIndex;
  const C_FLOAT64 * pValueEnd = pValue + mNumReactionSpecies;
  bool * pStochasticSpecies = mStochasticSpecies.array();

  C_FLOAT64 CriticalValue = (mLowerThreshold + mUpperThreshold) * 0.5;

  size_t Index = mFirstReactionSpeciesIndex;

  for (; pValue != pValueEnd; ++pValue, ++Index, ++pStochasticSpecies)
    {
      if (*pValue < CriticalValue)
        {
          *pStochasticSpecies = true;
          std::pair< speciesToReactionsMap::const_iterator, speciesToReactionsMap::const_iterator > Range
            = mSpeciesToReactions.equal_range(Index);

          for (; Range.first != Range.second; ++Range.first)
            {
              (*Range.first->second)++;
            }
        }
    }

  // Reactions for which the count of species with low numbers is non zero
  // are treated stochastically.
  const size_t * pLow = mNumLowSpecies.array();
  const size_t * pLowEnd = pLow + mNumLowSpecies.size();
  pReaction = reactions.array();
  const CMathReaction ** ppStochastic = mStochasticReactions.array();
  const CMathReaction ** ppDeterministic = mDeterministicReactions.array();

  for (; pLow != pLowEnd; ++pLow, ++pReaction, ++ppStochastic, ++ppDeterministic)
    {
      if (*pLow != 0)
        {
          *ppStochastic = pReaction;
          mHasStochastic = true;
        }
      else
        {
          *ppDeterministic = pReaction;
          mHasDeterministic = true;
        }
    }
}

bool CTrajectoryMethodDsaLsodar::CPartition::rePartition(const CVectorCore< C_FLOAT64 > & state)
{
  // Modify the partition if species values move beyond the threshold
  const C_FLOAT64 * pValue = state.array() + mFirstReactionSpeciesIndex;
  const C_FLOAT64 * pValueEnd = pValue + mNumReactionSpecies;
  bool * pStochasticSpecies = mStochasticSpecies.array();

  bool PartitionChanged = false;

  size_t Index = 0;

  for (; pValue != pValueEnd; ++pValue, ++Index, ++pStochasticSpecies)
    {
      if (!*pStochasticSpecies && *pValue < mLowerThreshold)
        {
          *pStochasticSpecies = true;
          PartitionChanged = true;

          std::pair< speciesToReactionsMap::const_iterator, speciesToReactionsMap::const_iterator > Range
            = mSpeciesToReactions.equal_range(Index);

          for (; Range.first != Range.second; ++Range.first)
            {
              (*Range.first->second)++;
            }
        }
      else if (*pStochasticSpecies && *pValue > mUpperThreshold)
        {
          *pStochasticSpecies = false;
          PartitionChanged = true;

          std::pair< speciesToReactionsMap::const_iterator, speciesToReactionsMap::const_iterator > Range
            = mSpeciesToReactions.equal_range(Index);

          for (; Range.first != Range.second; ++Range.first)
            {
              (*Range.first->second)--;
            }
        }
    }

  if (!PartitionChanged)
    {
      return false;
    }

  PartitionChanged = false;

  // Reactions for which the count of species with low numbers is non zero
  // are treated stochastically.
  const size_t * pLow = mNumLowSpecies.array();
  const size_t * pLowEnd = pLow + mNumLowSpecies.size();
  const CMathReaction ** ppStochastic = mStochasticReactions.array();
  const CMathReaction ** ppDeterministic = mDeterministicReactions.array();
  mHasStochastic = false;
  mHasDeterministic = false;

  for (; pLow != pLowEnd; ++pLow, ++ppStochastic, ++ppDeterministic)
    {
      if (*pLow != 0)
        {
          mHasStochastic = true;

          if (*ppDeterministic != NULL)
            {
              PartitionChanged = true;
              *ppStochastic = *ppDeterministic;
              *ppDeterministic = NULL;
            }
        }
      else
        {
          mHasDeterministic = true;

          if (*ppStochastic != NULL)
            {
              PartitionChanged = true;
              *ppDeterministic = *ppStochastic;
              *ppStochastic = NULL;
            }
        }
    }

  if (PartitionChanged)
    {
      // determineStochasticSpecies();
    }

  return PartitionChanged;
}

/**
 *   Default constructor.
 */
CTrajectoryMethodDsaLsodar::CTrajectoryMethodDsaLsodar(const CDataContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType):
  CLsodaMethod(pParent, methodType, taskType)
{
  mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
  initializeParameter();
}

CTrajectoryMethodDsaLsodar::CTrajectoryMethodDsaLsodar(const CTrajectoryMethodDsaLsodar & src,
    const CDataContainer * pParent):
  CLsodaMethod(src, pParent)
{
  mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
  initializeParameter();
}

/**
 *   Destructor.
 */
CTrajectoryMethodDsaLsodar::~CTrajectoryMethodDsaLsodar()
{
  cleanup();
  DESTRUCTOR_TRACE;
}

void CTrajectoryMethodDsaLsodar::initializeParameter()
{
  mpMaxSteps = assertParameter("Max Internal Steps", CCopasiParameter::Type::UINT, (unsigned C_INT32) 1000000);
  mpLowerLimit = assertParameter("Lower Limit", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 800.0);
  mpUpperLimit = assertParameter("Upper Limit", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1000.0);
  mpPartitioningInterval = assertParameter("Partitioning Interval", CCopasiParameter::Type::UINT, (unsigned C_INT32) 1);
  mpPartitioningSteps = assertParameter("Partitioning Stepsize", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 0.001);
}

// virtual
bool CTrajectoryMethodDsaLsodar::elevateChildren()
{
  bool success = CLsodaMethod::elevateChildren();

  initializeParameter();
  return success;
}

// virtual
void CTrajectoryMethodDsaLsodar::stateChange(const CMath::StateChange & change)
{
  CLsodaMethod::stateChange(change);

  calculatePropensities();
  calculateTotalPropensity();

  mNextReactionTime = std::numeric_limits< C_FLOAT64 >::infinity();
  mNextReactionIndex = C_INVALID_INDEX;
}

// virtual
CTrajectoryMethod::Status CTrajectoryMethodDsaLsodar::step(const double & deltaT,
    const bool & /* final */)
{
  // do several steps:
  C_FLOAT64 Time = *mpContainerStateTime;
  C_FLOAT64 EndTime = Time + deltaT;

  C_FLOAT64 Tolerance = 100.0 * (fabs(EndTime) * std::numeric_limits< C_FLOAT64 >::epsilon() + std::numeric_limits< C_FLOAT64 >::min());

  size_t Steps = 0;

  while (fabs(Time - EndTime) > Tolerance)
    {
      Time += doSingleStep(Time, EndTime);
      *mpContainerStateTime = Time;

      if (mStatus != CTrajectoryMethod::NORMAL)
        {
          break;
        }

      if (++Steps > *mpMaxSteps)
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 12);
        }
    }

  return mStatus;
}

// virtual
C_FLOAT64 CTrajectoryMethodDsaLsodar::doSingleStep(C_FLOAT64 curTime, C_FLOAT64 endTime)
{
  C_FLOAT64 DeltaT = 0.0;
  bool FireReaction = false;

  // if there are stochastic reactions
  if (mPartition.mHasStochastic) // there is at least one stochastic reaction
    {
      if (mNextReactionIndex == C_INVALID_INDEX)
        {
          if (mA0 != 0)
            {
              mNextReactionTime = curTime - log(mpRandomGenerator->getRandomOO()) / mA0;

              // We are sure that we have at least 1 reaction
              mNextReactionIndex = 0;

              C_FLOAT64 sum = 0.0;
              C_FLOAT64 rand = mpRandomGenerator->getRandomOO() * mA0;

              C_FLOAT64 * pAmu = mAmu.array();
              C_FLOAT64 * endAmu = pAmu + mNumReactions;
              const CMathReaction **ppStochastic = mPartition.mStochasticReactions.array();

              // Only consider stochastic reactions
              for (; (sum <= rand) && (pAmu != endAmu); ++pAmu, ++mNextReactionIndex, ++ppStochastic)
                {
                  if (*ppStochastic != NULL)
                    {
                      sum += *pAmu;
                    }
                }

              assert(mNextReactionIndex > 0);

              mNextReactionIndex--;
            }
          else
            {
              mNextReactionTime = std::numeric_limits< C_FLOAT64 >::infinity();
              mNextReactionIndex = C_INVALID_INDEX;
            }
        }

      if (mNextReactionTime <= endTime)
        {
          FireReaction = true;
          DeltaT = mNextReactionTime - curTime;
        }
      else
        {
          DeltaT = std::min(*mpPartitioningSteps, endTime - curTime);
        }
    }
  else
    {
      DeltaT = std::min(*mpPartitioningSteps, endTime - curTime);
    }

  // Even if all reactions are treated stochastically we need to integrate the
  // deterministic system to find time dependent events.
  integrateDeterministicPart(DeltaT);

  if (mStatus == CTrajectoryMethod::NORMAL)
    {
      if (FireReaction)
        {
          fireReaction(mNextReactionIndex);
        }

      if (mStepsAfterPartitionSystem >= *mpPartitioningInterval)
        {
          if (mPartition.rePartition(mContainerState))
            {
              stateChange(CMath::eStateChange::ContinuousSimulation);
            }

          mStepsAfterPartitionSystem = 0;
        }
    }

  ++mStepsAfterPartitionSystem;

  return DeltaT;
}

// virtual
void CTrajectoryMethodDsaLsodar::start()
{
  CLsodaMethod::start();

  mReactions.initialize(mpContainer->getReactions());
  mNumReactions = mReactions.size();
  mAmu.initialize(mpContainer->getPropensities());
  mPropensityObjects.initialize(mNumReactions, mpContainer->getMathObject(mAmu.array()));
  mUpdateSequences.resize(mNumReactions);
  mFirstReactionSpeciesIndex = mpContainer->getCountFixedEventTargets() + 1 /* Time */ + mpContainer->getCountODEs();

  // Create a local copy of the state where the particle number species determined
  // by reactions are rounded to integers.
  C_FLOAT64 * pValue = mContainerState.array() + mFirstReactionSpeciesIndex;
  C_FLOAT64 * pValueEnd = pValue + mpContainer->getCountIndependentSpecies() + mpContainer->getCountDependentSpecies();

  for (; pValue != pValueEnd; ++pValue)
    {
      *pValue = floor(*pValue + 0.5);
    }

  // The container state is now up to date we just need to calculate all values needed for simulation.
  mpContainer->updateSimulatedValues(false);

  CMathObject * pTimeObject = mpContainer->getMathObject(mpContainer->getModel().getValueReference());

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
  CCore::CUpdateSequence * pUpdateSequence = mUpdateSequences.array();
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
      pPropensityObject->calculateValue();
      mA0 += *pAmu;

      CObjectInterface::ObjectSet Changed;

      // The time is always updated
      Changed.insert(pTimeObject);

      const CMathReaction::SpeciesBalance * itBalance = pReaction->getNumberBalance().array();
      const CMathReaction::SpeciesBalance * endBalance = itBalance + pReaction->getNumberBalance().size();

      for (; itBalance != endBalance; ++itBalance)
        {
          Changed.insert(mpContainer->getMathObject(itBalance->first));
        }

      pUpdateSequence->clear();
      mpContainer->getTransientDependencies().getUpdateSequence(*pUpdateSequence, CCore::SimulationContext::Default, Changed, Requested);
    }

  mPartition.intialize(mpContainer, *mpLowerLimit, *mpUpperLimit);

  return;
}

// virtual
void CTrajectoryMethodDsaLsodar::evalF(const C_FLOAT64 * t, const C_FLOAT64 * /* y */, C_FLOAT64 * ydot)
{
  *mpContainerStateTime = *t;
  mpContainer->updateSimulatedValues(false);
  memcpy(ydot, mpContainer->getRate(false).array(), mData.dim * sizeof(C_FLOAT64));

  // We cannot use the species rates from the container as they are calculated
  // by summing over all reactions.
  CVectorCore< C_FLOAT64 > SpeciesRates(mPartition.mNumReactionSpecies, ydot + mPartition.mFirstReactionSpeciesIndex);
  SpeciesRates = 0.0;

  const CMathReaction ** ppReaction = mPartition.mDeterministicReactions.array();
  const CMathReaction ** ppReactionEnd = ppReaction + mNumReactions;

  for (; ppReaction != ppReactionEnd; ++ppReaction)
    {
      // Skip the stochastic reactions
      if (*ppReaction == NULL)
        {
          continue;
        }

      const CMathReaction::SpeciesBalance * itBalance = (*ppReaction)->getNumberBalance().array();

      const CMathReaction::SpeciesBalance * endBalance = itBalance + (*ppReaction)->getNumberBalance().size();

      C_FLOAT64 * pParticleFlux = (C_FLOAT64 *)(*ppReaction)->getParticleFluxObject()->getValuePointer();

      for (; itBalance != endBalance; ++ itBalance)
        {
          SpeciesRates[itBalance->first - mPartition.mpFirstReactionValue] += itBalance->second + 0.5 * *pParticleFlux;
        }
    }

  return;
}

// virtual
void CTrajectoryMethodDsaLsodar::evalR(const C_FLOAT64 * /* t */, const C_FLOAT64 * /* y */, const C_INT * /* nr */, C_FLOAT64 * /* r */)
{
}

/* PROTECTED METHODS *********************************************************/

/**
 *  Cleans up memory, etc.
 */
void CTrajectoryMethodDsaLsodar::cleanup()
{
  pdelete(mpRandomGenerator);

  return;
}

/* DETERMINISTIC STUFF *******************************************************/

void  CTrajectoryMethodDsaLsodar::integrateDeterministicPart(const C_FLOAT64 & deltaT)
{
  mStatus = CLsodaMethod::step(deltaT);
  mpContainer->updateSimulatedValues(*mpReducedModel);
  calculatePropensities();

  return;
}

/* STOCHASTIC STUFF **********************************************************/

/**
 *   Executes the specified reaction in the system once.
 *
 *   @param index A size_t specifying the index of the reaction, which
 *                 will be fired.
 *   @param time   The current time
 */
void CTrajectoryMethodDsaLsodar::fireReaction(const size_t & index)
{
  mReactions[index].fire();
  mpContainer->applyUpdateSequence(mUpdateSequences[index]);

  calculateTotalPropensity();

  mNextReactionTime = std::numeric_limits< C_FLOAT64 >::infinity();
  mNextReactionIndex = C_INVALID_INDEX;

  CLsodaMethod::stateChange(CMath::eStateChange::ContinuousSimulation);

  return;
}

void CTrajectoryMethodDsaLsodar::calculatePropensities()
{
  // It suffices to recalculate the propensities for stochastic reactions.
  CMathObject * pPropensity = mPropensityObjects.array();
  CMathObject * pPropensityEnd = pPropensity + mNumReactions;
  const CMathReaction **ppStochastic = mPartition.mStochasticReactions.array();

  for (; pPropensity != pPropensityEnd; ++pPropensity, ++ppStochastic)
    {
      if (*ppStochastic != NULL)
        {
          pPropensity->calculateValue();
        }
    }

  return;
}

void CTrajectoryMethodDsaLsodar::calculateTotalPropensity()
{
  // calculate the total propensity
  C_FLOAT64 * pAmu = mAmu.array();
  C_FLOAT64 * endAmu = pAmu + mNumReactions;
  const CMathReaction ** ppStochastic = mPartition.mStochasticReactions.array();

  mA0 = 0.0;

  for (; pAmu != endAmu; ++pAmu, ++ppStochastic)
    {
      // We must only consider the propensities for stochastic reactions
      if (*ppStochastic != NULL)
        {
          mA0 += *pAmu;
        }
    }
}
/* TESTING THE MODEL AND SETTING UP THINGS ***********************************/

//virtual
bool CTrajectoryMethodDsaLsodar::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CTrajectoryMethod::isValidProblem(pProblem)) return false;

  const CTrajectoryProblem * pTP = dynamic_cast<const CTrajectoryProblem *>(pProblem);

  if (pTP->getDuration() < 0.0)
    {
      //back integration not possible
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 9);
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

  /* Lower Limit, Upper Limit */
  *mpLowerLimit = getValue< C_FLOAT64 >("Lower Limit");
  *mpUpperLimit = getValue< C_FLOAT64 >("Upper Limit");

  if (*mpLowerLimit > *mpUpperLimit)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 4, *mpLowerLimit, *mpUpperLimit);
      return false;
    }

  /* Partitioning Interval */
  // nothing to be done here so far

  /* Use Random Seed */
  // should be checked in the widget later on

  /* Random Seed */
  // nothing to be done here

  return true;
}
