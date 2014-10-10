// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"

#include "CTrajectoryMethodDsaLsodar.h"
#include "CTrajectoryProblem.h"
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
CTrajectoryMethodDsaLsodar::CTrajectoryMethodDsaLsodar(const CCopasiMethod::SubType & subType,
    const CCopasiContainer * pParent):
  CLsodaMethod(CCopasiTask::timeCourse, subType, pParent)
{
  mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
  initializeParameter();
}

CTrajectoryMethodDsaLsodar::CTrajectoryMethodDsaLsodar(const CTrajectoryMethodDsaLsodar & src,
    const CCopasiContainer * pParent):
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
  CCopasiParameter *pParm;

  mpMaxSteps =
    assertParameter("Max Internal Steps", CCopasiParameter::UINT, (C_INT32) 1000000)->getValue().pUINT;
  mpLowerLimit =
    assertParameter("Lower Limit", CCopasiParameter::UDOUBLE, (C_FLOAT64) 800.0)->getValue().pUDOUBLE;
  mpUpperLimit =
    assertParameter("Upper Limit", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1000.0)->getValue().pUDOUBLE;
  mpPartitioningInterval =
    assertParameter("Partitioning Interval", CCopasiParameter::UINT, (unsigned C_INT32) 1)->getValue().pUINT;
  mpPartitioningSteps =
    assertParameter("Partitioning Stepsize", CCopasiParameter::UDOUBLE, (C_FLOAT64) 0.001)->getValue().pUDOUBLE;

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("HYBRID.MaxSteps")) != NULL)
    {
      setValue("Max Internal Steps", *pParm->getValue().pUINT);
      removeParameter("HYBRID.MaxSteps");

      if ((pParm = getParameter("HYBRID.LowerStochLimit")) != NULL)
        {
          setValue("Lower Limit", *pParm->getValue().pDOUBLE);
          removeParameter("HYBRID.LowerStochLimit");
        }

      if ((pParm = getParameter("HYBRID.UpperStochLimit")) != NULL)
        {
          setValue("Upper Limit", *pParm->getValue().pDOUBLE);
          removeParameter("HYBRID.UpperStochLimit");
        }

      if ((pParm = getParameter("HYBRID.PartitioningInterval")) != NULL)
        {
          setValue("Partitioning Interval", *pParm->getValue().pUINT);
          removeParameter("HYBRID.PartitioningInterval");
        }

      if ((pParm = getParameter("UseRandomSeed")) != NULL)
        {
          removeParameter("UseRandomSeed");
        }

      if ((pParm = getParameter("")) != NULL)
        {
          removeParameter("");
        }
    }
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
CTrajectoryMethod::Status CTrajectoryMethodDsaLsodar::step(const double & deltaT)
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
              stateChange(CMath::ContinuousSimulation);
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

      const CMathReaction::SpeciesBalance * itBalance = pReaction->getNumberBalance().array();
      const CMathReaction::SpeciesBalance * endBalance = itBalance + pReaction->getNumberBalance().size();

      for (; itBalance != endBalance; ++itBalance)
        {
          Changed.insert(mpContainer->getMathObject(itBalance->first));
        }

      pUpdateSequence->clear();
      mpContainer->getTransientDependencies().getUpdateSequence(*pUpdateSequence, CMath::Default, Changed, Requested);
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

  CLsodaMethod::stateChange(CMath::ContinuousSimulation);

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
          pPropensity->calculate();
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
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 23);
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

  /* Max Internal Steps */
  if (* getValue("Max Internal Steps").pINT <= 0)
    {
      //max steps should be at least 1
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 15);
      return false;
    }

  /* Lower Limit, Upper Limit */
  *mpLowerLimit = * getValue("Lower Limit").pDOUBLE;
  *mpUpperLimit = * getValue("Upper Limit").pDOUBLE;

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
