// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTrajectoryMethodDsaLsodar.cpp,v $
//   $Revision: 1.2.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/11/05 12:24:35 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
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
#define min _cpp_min
#define max _cpp_max
#endif // WIN32

#include <limits.h>

#include "mathematics.h" // pow(), floor()

#include "copasi.h"

#include "CTrajectoryMethodDsaLsodar.h"
#include "CTrajectoryProblem.h"
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

CTrajectoryMethodDsaLsodar::CReactionDependencies::CReactionDependencies():
    mSpeciesMultiplier(0),
    mMethodSpecies(0),
    mModelSpecies(0),
    mCalculations(),
    mDependentReactions(0),
    mSubstrateMultiplier(0),
    mMethodSubstrates(0),
    mModelSubstrates(0),
    mpParticleFlux(NULL),
    mSpeciesIndex(0)
{}

CTrajectoryMethodDsaLsodar::CReactionDependencies::CReactionDependencies(const CReactionDependencies & src):
    mSpeciesMultiplier(src.mSpeciesMultiplier),
    mMethodSpecies(src.mMethodSpecies),
    mModelSpecies(src.mModelSpecies),
    mCalculations(src.mCalculations),
    mDependentReactions(src.mDependentReactions),
    mSubstrateMultiplier(src.mSubstrateMultiplier),
    mMethodSubstrates(src.mMethodSubstrates),
    mModelSubstrates(src.mModelSubstrates),
    mpParticleFlux(src.mpParticleFlux),
    mSpeciesIndex(src.mSpeciesIndex)
{}

CTrajectoryMethodDsaLsodar::CReactionDependencies::~CReactionDependencies()
{}

CTrajectoryMethodDsaLsodar::CReactionDependencies & CTrajectoryMethodDsaLsodar::CReactionDependencies::operator = (const CTrajectoryMethodDsaLsodar::CReactionDependencies & rhs)
{
  mSpeciesMultiplier = rhs.mSpeciesMultiplier;
  mMethodSpecies = rhs.mMethodSpecies;
  mModelSpecies = rhs.mModelSpecies;
  mCalculations = rhs.mCalculations;
  mDependentReactions = rhs.mDependentReactions;
  mSubstrateMultiplier = rhs.mSubstrateMultiplier;
  mMethodSubstrates = rhs.mMethodSubstrates;
  mModelSubstrates = rhs.mModelSubstrates;
  mpParticleFlux = rhs.mpParticleFlux;
  mSpeciesIndex = rhs.mSpeciesIndex;

  return * this;
}

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
    mLowSpecies(0)
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
    mLowSpecies(src.mLowSpecies)
{}

CTrajectoryMethodDsaLsodar::CPartition::~CPartition()
{}

void CTrajectoryMethodDsaLsodar::CPartition::intialize(std::vector< CReactionDependencies > & reactions,
    const speciesToReactionsMap & speciesToReactions,
    const C_FLOAT64 & lowerThreshold,
    const C_FLOAT64 & upperThreshold,
    const CState & state)
{
  mSpeciesToReactions = speciesToReactions;
  mLowerThreshold = lowerThreshold;
  mUpperThreshold = upperThreshold;

  mFirstReactionSpeciesIndex = mSpeciesToReactions.begin()->first;
  mNumReactionSpecies = mSpeciesToReactions.rbegin()->first - mFirstReactionSpeciesIndex + 1;

  mStochasticReactions.resize(reactions.size());
  mStochasticReactions = NULL;

  mDeterministicReactions.resize(reactions.size());
  mDeterministicReactions = NULL;

  mNumLowSpecies.resize(reactions.size());
  mNumLowSpecies = 0;

  mStochasticSpecies.resize(mNumReactionSpecies);
  mStochasticSpecies = false;

  mLowSpecies.resize(mNumReactionSpecies);
  mLowSpecies = false;

  mHasStochastic = false;
  mHasDeterministic = false;

  // Create the initial partition by first counting species with low particle number per reaction
  const C_FLOAT64 * pValue = state.beginIndependent() - 1 + mFirstReactionSpeciesIndex;
  const C_FLOAT64 * pValueEnd = pValue + mNumReactionSpecies;
  bool * pLowSpecies = mLowSpecies.array();

  C_FLOAT64 CriticalValue = (mLowerThreshold + mUpperThreshold) * 0.5;

  size_t Index = mFirstReactionSpeciesIndex;

  for (; pValue != pValueEnd; ++pValue, ++Index, ++pLowSpecies)
    {
      if (*pValue < CriticalValue)
        {
          *pLowSpecies = true;
          std::pair< speciesToReactionsMap::const_iterator, speciesToReactionsMap::const_iterator > Range
          = mSpeciesToReactions.equal_range(Index);

          for (; Range.first != Range.second; ++Range.first)
            {
              mNumLowSpecies[Range.first->second]++;
            }
        }
    }

  // Reactions for which the count of species with low numbers is non zero
  // are treated stochastically.
  const size_t * pLow = mNumLowSpecies.array();
  const size_t * pLowEnd = pLow + mNumLowSpecies.size();
  std::vector< CReactionDependencies >::iterator itReaction = reactions.begin();
  CReactionDependencies ** ppStochastic = mStochasticReactions.array();
  CReactionDependencies ** ppDeterministic = mDeterministicReactions.array();

  for (; pLow != pLowEnd; ++pLow, ++itReaction, ++ppStochastic, ++ppDeterministic)
    {
      if (*pLow != 0)
        {
          *ppStochastic = &(*itReaction);
          mHasStochastic = true;
        }
      else
        {
          *ppDeterministic = &(*itReaction);
          mHasDeterministic = true;
        }
    }

  determineStochasticSpecies();
}

bool CTrajectoryMethodDsaLsodar::CPartition::rePartition(const CState & state)
{
  // Modify the partition if species values move beyond the threshold
  const C_FLOAT64 * pValue = state.beginIndependent() - 1 + mFirstReactionSpeciesIndex;
  const C_FLOAT64 * pValueEnd = pValue + mNumReactionSpecies;
  bool * pLowSpecies = mLowSpecies.array();

  bool PartitionChanged = false;

  size_t Index = 0;

  for (; pValue != pValueEnd; ++pValue, ++Index, ++pLowSpecies)
    {
      if (!*pLowSpecies && *pValue < mLowerThreshold)
        {
          *pLowSpecies = true;
          PartitionChanged = true;

          mStochasticSpecies[Index] = true;

          std::pair< speciesToReactionsMap::const_iterator, speciesToReactionsMap::const_iterator > Range
          = mSpeciesToReactions.equal_range(Index + mFirstReactionSpeciesIndex);

          for (; Range.first != Range.second; ++Range.first)
            {
              mNumLowSpecies[Range.first->second]++;
            }
        }
      else if (*pLowSpecies && *pValue > mUpperThreshold)
        {
          *pLowSpecies = false;
          PartitionChanged = true;

          mStochasticSpecies[Index] = true;

          std::pair< speciesToReactionsMap::const_iterator, speciesToReactionsMap::const_iterator > Range
          = mSpeciesToReactions.equal_range(Index);

          for (; Range.first != Range.second; ++Range.first)
            {
              mNumLowSpecies[Range.first->second]--;
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
  CReactionDependencies ** ppStochastic = mStochasticReactions.array();
  CReactionDependencies ** ppDeterministic = mDeterministicReactions.array();
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

void CTrajectoryMethodDsaLsodar::CPartition::determineStochasticSpecies()
{
  // All species which participate in stochastic reactions are treated stochastically
  CReactionDependencies **ppReaction = mStochasticReactions.array();
  CReactionDependencies **ppReactionEnd = ppReaction + mStochasticReactions.size();

  mStochasticSpecies = false;

  for (; ppReaction != ppReactionEnd; ++ppReaction)
    {
      if (*ppReaction != NULL)
        {
          size_t * pSpeciesIndex = (*ppReaction)->mSpeciesIndex.array();
          size_t * pSpeciesIndexEnd = pSpeciesIndex + (*ppReaction)->mSpeciesIndex.size();

          for (; pSpeciesIndex != pSpeciesIndexEnd; ++pSpeciesIndex)
            {
              mStochasticSpecies[*pSpeciesIndex - mFirstReactionSpeciesIndex] = true;
            }
        }
    }
}


/**
 *   Default constructor.
 */
CTrajectoryMethodDsaLsodar::CTrajectoryMethodDsaLsodar(const CCopasiMethod::SubType & subType,
    const CCopasiContainer * pParent):
    CLsodaMethod(subType, pParent)
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
void CTrajectoryMethodDsaLsodar::stateChanged()
{
  *mpCurrentState = mMethodState;
  CLsodaMethod::stateChanged();
}

// virtual
CTrajectoryMethod::Status CTrajectoryMethodDsaLsodar::step(const double & deltaT)
{
  // do several steps:
  C_FLOAT64 Time = mpCurrentState->getTime();
  C_FLOAT64 EndTime = Time + deltaT;

  C_FLOAT64 Tolerance = 100.0 * (fabs(EndTime) * std::numeric_limits< C_FLOAT64 >::epsilon() + DBL_MIN);

  size_t Steps = 0;

  while (fabs(Time - EndTime) > Tolerance)
    {
      Time += doSingleStep(Time, EndTime);

      if (++Steps > *mpMaxSteps)
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 12);
        }
    }

  mMethodState.setTime(EndTime); // make sure the end time is exactly the time reach to next interval
  *mpCurrentState = mMethodState;

  return NORMAL;
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
              CReactionDependencies **ppStochastic = mPartition.mStochasticReactions.array();

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

  // if there are deterministic reactions
  if (mPartition.mHasDeterministic) // there is at least one deterministic reaction
    {
      integrateDeterministicPart(DeltaT);
      calculatePropensities();

      // Now the model state and mMethodState are identical and the propensities are
      // calculated accordingly.
    }

  if (FireReaction)
    {
      mpModel->setTime(mNextReactionTime);
      mMethodState.setTime(mNextReactionTime);

      fireReaction(mNextReactionIndex);

      mNextReactionTime = std::numeric_limits< C_FLOAT64 >::infinity();
      mNextReactionIndex = C_INVALID_INDEX;

      // Now the model state and mMethodState are identical and the propensities are
      // calculated accordingly.
    }

  if (++mStepsAfterPartitionSystem >= *mpPartitioningInterval)
    {
      if (mPartition.rePartition(*mpCurrentState))
        {
          calculatePropensities();
        }

      mStepsAfterPartitionSystem = 0;
    }

  return DeltaT;
}

// virtual
void CTrajectoryMethodDsaLsodar::start(const CState * initialState)
{
  CLsodaMethod::start(initialState);

  if (mpModel->getModelType() == CModel::deterministic)
    mDoCorrection = true;
  else
    mDoCorrection = false;

  //initialize the vector of ints that contains the particle numbers
  //for the discrete simulation. This also floors all particle numbers in the model.

  mNumReactions = mpModel->getReactions().size();

  mReactionDependencies.resize(mNumReactions);
  mAmu.resize(mNumReactions);
  mAmu = 0.0;

  const CStateTemplate & StateTemplate = mpModel->getStateTemplate();

  CModelEntity *const* ppEntity = StateTemplate.beginIndependent();
  CModelEntity *const* endEntity = StateTemplate.endFixed();
  C_FLOAT64 * pValue = mMethodState.beginIndependent();

  mFirstReactionSpeciesIndex = 0;
  size_t IndexSpecies = 1;

  for (; ppEntity != endEntity; ++ppEntity, ++pValue, ++IndexSpecies)
    {
      if (dynamic_cast< const CMetab * >(*ppEntity) != NULL)
        {
          *pValue = floor(*pValue + 0.5);

          if (mFirstReactionSpeciesIndex == 0 &&
              (*ppEntity)->getStatus() == CModelEntity::REACTIONS)
            {
              mFirstReactionSpeciesIndex = IndexSpecies;
            }
        }
    }

  // Update the model state so that the species are all represented by integers.
  mpModel->setState(mMethodState);
  mpModel->updateSimulatedValues(false); //for assignments

  // TODO CRITICAL Handle species of type ASSIGNMENT.
  // These need to be checked whether they are sufficiently close to an integer

  // Build the reaction dependencies
  C_FLOAT64 * pMethodStateValue = mMethodState.beginIndependent() - 1;
  size_t IndexReactions = 0;
  std::multimap< size_t, size_t> SpeciesToReactions;

  CCopasiVector< CReaction >::const_iterator it = mpModel->getReactions().begin();
  CCopasiVector< CReaction >::const_iterator end = mpModel->getReactions().end();
  std::vector< CReactionDependencies >::iterator itDependencies = mReactionDependencies.begin();

  for (; it  != end; ++it)
    {
      const CCopasiVector<CChemEqElement> & Balances = (*it)->getChemEq().getBalances();
      const CCopasiVector<CChemEqElement> & Substrates = (*it)->getChemEq().getSubstrates();

      // This reactions does not change anything we ignore it
      if (Balances.size() == 0 && Substrates.size() == 0)
        {
          continue;
        }

      itDependencies->mpParticleFlux = (C_FLOAT64 *)(*it)->getParticleFluxReference()->getValuePointer();

      itDependencies->mSpeciesMultiplier.resize(Balances.size());
      itDependencies->mMethodSpecies.resize(Balances.size());
      itDependencies->mModelSpecies.resize(Balances.size());

      std::set< size_t > SpeciesIndexSet;

      std::set< const CCopasiObject * > changed;

      CCopasiVector< CChemEqElement >::const_iterator itBalance = Balances.begin();
      CCopasiVector< CChemEqElement >::const_iterator endBalance = Balances.end();

      size_t Index = 0;

      for (; itBalance != endBalance; ++itBalance)
        {
          const CMetab * pMetab = (*itBalance)->getMetabolite();

          if (pMetab->getStatus() == CModelEntity::REACTIONS)
            {
              size_t SpeciesIndex = StateTemplate.getIndex(pMetab);

              itDependencies->mSpeciesMultiplier[Index] = floor((*itBalance)->getMultiplicity() + 0.5);
              itDependencies->mMethodSpecies[Index] = pMethodStateValue + SpeciesIndex;
              itDependencies->mModelSpecies[Index] = (C_FLOAT64 *) pMetab->getValueReference()->getValuePointer();

              changed.insert(pMetab->getValueReference());

              SpeciesToReactions.insert(std::make_pair(SpeciesIndex, IndexReactions));
              SpeciesIndexSet.insert(SpeciesIndex);

              Index++;
            }
        }

      // Correct allocation for metabolites which are not determined by reactions
      itDependencies->mSpeciesMultiplier.resize(Index, true);
      itDependencies->mMethodSpecies.resize(Index, true);
      itDependencies->mModelSpecies.resize(Index, true);

      itDependencies->mSubstrateMultiplier.resize(Substrates.size());
      itDependencies->mMethodSubstrates.resize(Substrates.size());
      itDependencies->mModelSubstrates.resize(Substrates.size());

      CCopasiVector< CChemEqElement >::const_iterator itSubstrate = Substrates.begin();
      CCopasiVector< CChemEqElement >::const_iterator endSubstrate = Substrates.end();

      Index = 0;

      for (; itSubstrate != endSubstrate; ++itSubstrate, ++Index)
        {
          const CMetab * pMetab = (*itSubstrate)->getMetabolite();

          size_t SpeciesIndex = StateTemplate.getIndex(pMetab);

          itDependencies->mSubstrateMultiplier[Index] = floor((*itSubstrate)->getMultiplicity() + 0.5);
          itDependencies->mMethodSubstrates[Index] = pMethodStateValue + SpeciesIndex;
          itDependencies->mModelSubstrates[Index] = (C_FLOAT64 *) pMetab->getValueReference()->getValuePointer();

          if (pMetab->getStatus() == CModelEntity::REACTIONS)
            {
              SpeciesIndexSet.insert(SpeciesIndex);
            }
        }


      itDependencies->mSpeciesIndex.resize(SpeciesIndexSet.size());
      size_t * pSpeciesIndex = itDependencies->mSpeciesIndex.array();
      std::set< size_t >::const_iterator itSet = SpeciesIndexSet.begin();
      std::set< size_t >::const_iterator endSet = SpeciesIndexSet.end();


      for (; itSet != endSet; ++itSet, ++pSpeciesIndex)
        {
          *pSpeciesIndex = *itSet;
        }

      std::set< const CCopasiObject * > dependend;

      CCopasiVector< CReaction >::const_iterator itReaction = mpModel->getReactions().begin();
      itDependencies->mDependentReactions.resize(mNumReactions);

      Index = 0;
      size_t Count = 0;

      for (; itReaction != end; ++itReaction, ++Index)
        {
          if ((*itReaction)->getParticleFluxReference()->dependsOn(changed))
            {
              dependend.insert((*itReaction)->getParticleFluxReference());
              itDependencies->mDependentReactions[Count] = Index;

              Count++;
            }
        }

      itDependencies->mDependentReactions.resize(Count, true);

      itDependencies->mCalculations = CCopasiObject::buildUpdateSequence(dependend, changed);

      ++itDependencies;
      ++IndexReactions;
    }

  mNumReactions = IndexReactions;

  mReactionDependencies.resize(mNumReactions);
  mAmu.resize(mNumReactions, true);

  mPartition.intialize(mReactionDependencies, SpeciesToReactions,
                       *mpLowerLimit, *mpUpperLimit, mMethodState);

  mNextReactionTime = std::numeric_limits< C_FLOAT64 >::infinity();
  mNextReactionIndex = C_INVALID_INDEX;

  calculatePropensities();

  return;
}

// virtual
void CTrajectoryMethodDsaLsodar::evalF(const C_FLOAT64 * t, const C_FLOAT64 * /* y */, C_FLOAT64 * ydot)
{
  // If we have no ODEs add a constant one.
  if (mNoODE)
    {
      *ydot = 1.0;
      return;
    }

  mMethodState.setTime(*t);

  mpModel->setState(mMethodState);
  mpModel->updateSimulatedValues(*mpReducedModel);

  if (*mpReducedModel)
    mpModel->calculateDerivativesX(ydot);
  else
    mpModel->calculateDerivatives(ydot);

  // Mask derivatives of stochastic species;
  bool * pStochastic = mPartition.mStochasticSpecies.array();
  bool * pStochasticEnd = pStochastic + mPartition.mStochasticSpecies.size();
  C_FLOAT64 * pYdot = ydot + mFirstReactionSpeciesIndex - 1;

  for (; pStochastic != pStochasticEnd; ++pStochastic, ++pYdot)
    {
      if (*pStochastic)
        {
          *pYdot = 0;
        }
    }

  return;
}

// virtual
void CTrajectoryMethodDsaLsodar::evalR(const C_FLOAT64 * t, const C_FLOAT64 * y, const C_INT * nr, C_FLOAT64 * r)
{

}

/* PROTECTED METHODS *********************************************************/


/**
 *  Cleans up memory, etc.
 */
void CTrajectoryMethodDsaLsodar::cleanup()
{
  delete mpRandomGenerator;
  mpRandomGenerator = NULL;
  mpModel = NULL;
  return;
}

/* DETERMINISTIC STUFF *******************************************************/

void CTrajectoryMethodDsaLsodar::integrateDeterministicPart(const C_FLOAT64 & deltaT)
{
  CLsodaMethod::step(deltaT);

  mpModel->setState(mMethodState);
  mpModel->updateSimulatedValues(*mpReducedModel);

  return;
}

/* STOCHASTIC STUFF **********************************************************/

/**
 *   Executes the specified reaction in the system once.
 *
 *   @param index A C_INT32 specifying the index of the reaction, which
 *                 will be fired.
 *   @param time   The current time
 */
void CTrajectoryMethodDsaLsodar::fireReaction(const size_t & index)
{
  CReactionDependencies & Dependencies = mReactionDependencies[index];

  // Update the method internal and model species numbers
  C_FLOAT64 ** ppModelSpecies = Dependencies.mModelSpecies.array();
  C_FLOAT64 ** ppLocalSpecies = Dependencies.mMethodSpecies.array();
  C_FLOAT64 * pMultiplier = Dependencies.mSpeciesMultiplier.array();
  C_FLOAT64 * endMultiplier = pMultiplier + Dependencies.mSpeciesMultiplier.size();

  for (; pMultiplier != endMultiplier; ++pMultiplier, ++ppLocalSpecies, ++ppModelSpecies)
    {
      **ppLocalSpecies += *pMultiplier;
      **ppModelSpecies = **ppLocalSpecies;
    }

  // Calculate all values which depend on the firing reaction
  std::vector< Refresh * >::const_iterator itCalcualtion =  Dependencies.mCalculations.begin();
  std::vector< Refresh * >::const_iterator endCalcualtion =  Dependencies.mCalculations.end();

  while (itCalcualtion != endCalcualtion)
    {
      (**itCalcualtion++)();
    }

  // We do not need to update the the method state since the only independent state
  // values are species of type reaction which are all controlled by the method.

  // calculate the propensities which depend on the firing reaction
  size_t * pDependentReaction = Dependencies.mDependentReactions.array();
  size_t * endDependentReactions = pDependentReaction + Dependencies.mDependentReactions.size();

  // It suffices to recalculate the propensities for stochastic reactions.
  for (; pDependentReaction != endDependentReactions; ++pDependentReaction)
    {
      if (mPartition.mStochasticReactions[*pDependentReaction] != NULL)
        {
          calculateAmu(*pDependentReaction);
        }
    }

  // calculate the total propensity
  C_FLOAT64 * pAmu = mAmu.array();
  C_FLOAT64 * endAmu = pAmu + mNumReactions;

  mA0 = 0.0;

  // We must only consider the propensities for stochastic reactions
  CReactionDependencies ** ppStochastic = mPartition.mStochasticReactions.array();

  for (; pAmu != endAmu; ++pAmu, ++ppStochastic)
    {
      if (*ppStochastic != NULL)
        {
          mA0 += *pAmu;
        }
    }

  mTime = mMethodState.getTime();
  mLsodaStatus = 1;

  destroyRootMask();
  mRootMasking = NONE;

  return;
}

void CTrajectoryMethodDsaLsodar::calculateAmu(const size_t & index)
{
  CReactionDependencies & Dependencies = mReactionDependencies[index];
  C_FLOAT64 & Amu = mAmu[index];

  Amu = *Dependencies.mpParticleFlux;

  if (!mDoCorrection)
    {
      return;
    }

  C_FLOAT64 SubstrateMultiplier = 1.0;
  C_FLOAT64 SubstrateDevisor = 1.0;
  C_FLOAT64 Multiplicity;
  C_FLOAT64 LowerBound;
  C_FLOAT64 Number;

  bool ApplyCorrection = false;

  C_FLOAT64 * pMultiplier = Dependencies.mSubstrateMultiplier.array();
  C_FLOAT64 * endMultiplier = pMultiplier + Dependencies.mSubstrateMultiplier.size();
  C_FLOAT64 ** ppLocalSubstrate = Dependencies.mMethodSubstrates.array();
  C_FLOAT64 ** ppModelSubstrate = Dependencies.mModelSubstrates.array();

  for (; pMultiplier != endMultiplier; ++pMultiplier, ++ppLocalSubstrate, ++ppModelSubstrate)
    {
      Multiplicity = *pMultiplier;

      // TODO We should check the error introduced through rounding.
      **ppLocalSubstrate = floor(**ppModelSubstrate + 0.5);

      if (Multiplicity > 1.01)
        {
          ApplyCorrection = true;

          Number = **ppLocalSubstrate;

          LowerBound = Number - Multiplicity;
          SubstrateDevisor *= pow(Number, Multiplicity - 1.0);  //optimization
          Number -= 1.0;

          while (Number > LowerBound)
            {
              SubstrateMultiplier *= Number;
              Number -= 1.0;
            }
        }
    }

  // at least one substrate particle number is zero
  if (SubstrateMultiplier < 0.5 || SubstrateDevisor < 0.5)
    {
      Amu = 0.0;
      return;
    }

  // rate_factor is the rate function divided by substrate_factor.
  // It would be more efficient if this was generated directly, since in effect we
  // are multiplying and then dividing by the same thing (substrate_factor)!
  //C_FLOAT64 rate_factor = mpModel->getReactions()[index]->calculateParticleFlux();
  if (ApplyCorrection)
    {
      Amu *= SubstrateMultiplier / SubstrateDevisor;
    }

  return;
}

void CTrajectoryMethodDsaLsodar::calculatePropensities()
{  // It suffices to recalculate the propensities for stochastic reactions.
  CReactionDependencies **ppStochastic = mPartition.mStochasticReactions.array();

  for (size_t Index = 0; Index != this->mNumReactions; ++Index, ++ppStochastic)
    {
      if (*ppStochastic != NULL)
        {
          calculateAmu(Index);
        }
    }

  mpModel->setState(mMethodState);
  mpModel->updateSimulatedValues(false); //for assignments

  // calculate the total propensity
  C_FLOAT64 * pAmu = mAmu.array();
  C_FLOAT64 * endAmu = pAmu + mNumReactions;

  mA0 = 0.0;

  // We must only consider the propensities for stochastic reactions
  ppStochastic = mPartition.mStochasticReactions.array();

  for (; pAmu != endAmu; ++pAmu, ++ppStochastic)
    {
      if (*ppStochastic != NULL)
        {
          mA0 += *pAmu;
          assert(mA0 >= 0.0);
        }
    }

  return;
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

  //check for rules
  C_INT32 i, imax = pTP->getModel()->getNumModelValues();

  for (i = 0; i < imax; ++i)
    {
      if (pTP->getModel()->getModelValues()[i]->getStatus() == CModelEntity::ODE)
        {
          //ode rule found
          CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 18);
          return false;
        }

      /*      if (pTP->getModel()->getModelValues()[i]->getStatus()==CModelEntity::ASSIGNMENT)
              if (pTP->getModel()->getModelValues()[i]->isUsed())
                {
                  //used assignment found
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 19);
                  return false;
                }*/
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

  //events are not supported at the moment
  if (pTP->getModel()->getEvents().size() > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 23);
      return false;
    }

  return true;
}

