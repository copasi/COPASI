// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTrajAdaptiveSA.cpp,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/11/09 14:46:55 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243)
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
#endif  // WIN32

#include <limits.h>

#include <mathematics.h>
#include <vector>
#include <numeric>
#include <limits>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "copasi.h"
#include "CTrajAdaptiveSA.h"
#include "utilities/CCopasiVector.h"
#include "function/CFunction.h"
#include "randomGenerator/CRandom.h"
#include "CTrajectoryProblem.h"
#include "model/CState.h"
#include "model/CCompartment.h"
#include "model/CModel.h"

#define mtxIdx(row,col,intv)  ((row)+(col)*(intv))
CTrajAdaptiveSA::CReactionDependencies::CReactionDependencies():
    mMethodSpeciesIndex(0),
    mSpeciesMultiplier(0),
    mMethodSpecies(0),
    mModelSpecies(0),
    mCalculations(),
    mDependentReactions(0),
    mSubstrateMultiplier(0),
    mMethodSubstrates(0),
    mModelSubstrates(0),
    mpParticleFlux(NULL)
{}

CTrajAdaptiveSA::CReactionDependencies::CReactionDependencies(const CReactionDependencies & src):
    mMethodSpeciesIndex(src.mMethodSpeciesIndex),
    mSpeciesMultiplier(src.mSpeciesMultiplier),
    mMethodSpecies(src.mMethodSpecies),
    mModelSpecies(src.mModelSpecies),
    mCalculations(src.mCalculations),
    mDependentReactions(src.mDependentReactions),
    mSubstrateMultiplier(src.mSubstrateMultiplier),
    mMethodSubstrates(src.mMethodSubstrates),
    mModelSubstrates(src.mModelSubstrates),
    mpParticleFlux(src.mpParticleFlux)
{}

CTrajAdaptiveSA::CReactionDependencies::~CReactionDependencies()
{}

CTrajAdaptiveSA::CReactionDependencies & CTrajAdaptiveSA::CReactionDependencies::operator = (const CTrajAdaptiveSA::CReactionDependencies & rhs)
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

  return * this;
}

// static
CTrajAdaptiveSA * CTrajAdaptiveSA::createTauLeapMethod()
{
  CTrajAdaptiveSA * pMethod = NULL;

  pMethod = new CTrajAdaptiveSA();

  return pMethod;
}

CTrajAdaptiveSA::CTrajAdaptiveSA(const CCopasiContainer * pParent):
    CTrajectoryMethod(CCopasiMethod::adaptiveSA, pParent),
    mMaxReactionFiring(0),
    mReactionFiring(0),
    mPartitionedReactionFiring(0),
    mAvgDX(0),
    mSigDX(0),
    mpMethodSpecies(NULL),
    mSpeciesAfterTau(0),
    mpRandomGenerator(CRandom::createGenerator(CRandom::mt19937)),
    mpModel(NULL),
    mNumReactions(0),
    mNumSpecies(0),
    mMaxSteps(1000000),
    mNextReactionTime(0.0),
    mNextReactionIndex(C_INVALID_INDEX),
    mDoCorrection(true),
    mAmu(0),
    mPartitionedAmu(0),
    mMethodState(),
    mReactionDependencies(0),
    mPartitionedDependencies(0),
    mA0(0.0),
    mMaxStepsReached(false)
{
  initializeParameter();
}

CTrajAdaptiveSA::CTrajAdaptiveSA(const CTrajAdaptiveSA & src,
                                 const CCopasiContainer * pParent):
    CTrajectoryMethod(src, pParent),
    mMaxReactionFiring(src.mMaxReactionFiring),
    mReactionFiring(src.mReactionFiring),
    mPartitionedReactionFiring(src.mPartitionedReactionFiring),
    mAvgDX(src.mAvgDX),
    mSigDX(src.mSigDX),
    mpMethodSpecies(src.mpMethodSpecies),
    mSpeciesAfterTau(src.mSpeciesAfterTau),
    mpRandomGenerator(CRandom::createGenerator(CRandom::mt19937)),
    mpModel(src.mpModel),
    mNumReactions(src.mNumReactions),
    mNumSpecies(src.mNumSpecies),
    mMaxSteps(src.mMaxSteps),
    mNextReactionTime(src.mNextReactionTime),
    mNextReactionIndex(src.mNextReactionIndex),
    mDoCorrection(src.mDoCorrection),
    mAmu(src.mAmu),
    mPartitionedAmu(src.mPartitionedAmu),
    mMethodState(src.mMethodState),
    mReactionDependencies(src.mReactionDependencies),
    mPartitionedDependencies(src.mPartitionedDependencies),
    mA0(src.mA0),
    mMaxStepsReached(src.mMaxStepsReached)
{
  initializeParameter();
}

CTrajAdaptiveSA::~CTrajAdaptiveSA()
{
  pdelete(mpRandomGenerator);
}

void CTrajAdaptiveSA::initializeParameter()
{
  assertParameter("Epsilon", CCopasiParameter::DOUBLE, (C_FLOAT64) EPS);
  assertParameter("Max Internal Steps", CCopasiParameter::INT, (C_INT32) 1000000);
  assertParameter("Use Random Seed", CCopasiParameter::BOOL, false);
  assertParameter("Random Seed", CCopasiParameter::UINT, (unsigned C_INT32) 1);
}

bool CTrajAdaptiveSA::elevateChildren()
{
  initializeParameter();
  return true;
}

CTrajectoryMethod::Status CTrajAdaptiveSA::step(const double & deltaT)
{
  // do several steps
  C_FLOAT64 Time = mpCurrentState->getTime();
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
    }

  *mpCurrentState = mpProblem->getModel()->getState();
  mpCurrentState->setTime(Time);

  return NORMAL;
}

void CTrajAdaptiveSA::start(const CState * initialState)
{
  /* get configuration data */
  mMaxSteps = * getValue("Max Internal Steps").pINT;
  mEpsilon = * getValue("Epsilon").pDOUBLE;

  bool useRandomSeed = * getValue("Use Random Seed").pBOOL;
  unsigned C_INT32 randomSeed = * getValue("Random Seed").pUINT;

  if (useRandomSeed) mpRandomGenerator->initialize(randomSeed);

  //mpCurrentState is initialized. This state is not used internally in the
  //stochastic solver, but it is used for returning the result after each step.
  *mpCurrentState = *initialState;

  mpModel = mpProblem->getModel();
  assert(mpModel);

  if (mpModel->getModelType() == CModel::deterministic)
    mDoCorrection = true;
  else
    mDoCorrection = false;

  //initialize the vector of ints that contains the particle numbers
  //for the discrete simulation. This also floors all particle numbers in the model.

  mNumReactions = mpModel->getReactions().size();
  mNumSpecies = mpModel->getMetabolitesX().size();

  mPartitionedDependencies.resize(mNumReactions);
  mMaxReactionFiring.resize(mNumReactions);
  mPartitionedAmu.resize(mNumReactions);
  mReactionFiring.resize(mNumReactions);
  mPartitionedReactionFiring.resize(mNumReactions);

  mReactionDependencies.resize(mNumReactions);
  mAmu.resize(mNumReactions);
  mAmu = 0.0;

  mNumReactionSpecies = mpModel->getNumIndependentReactionMetabs() + mpModel->getNumDependentReactionMetabs();

  mSpeciesAfterTau.resize(mNumReactionSpecies);

  mAvgDX.resize(mNumReactionSpecies);
  mSigDX.resize(mNumReactionSpecies);

  // Initialize the
  // Create a local copy of the state where the particle number are rounded to integers
  mMethodState = mpModel->getState();

  const CStateTemplate & StateTemplate = mpModel->getStateTemplate();

  CModelEntity *const* ppEntity = StateTemplate.beginIndependent();
  CModelEntity *const* endEntity = StateTemplate.endFixed();
  C_FLOAT64 * pValue = mMethodState.beginIndependent();

  mFirstReactionSpeciesIndex = 0;
  size_t Index = 1;

  C_FLOAT64 * pSpeciesAfterTau = mSpeciesAfterTau.array();

  for (; ppEntity != endEntity; ++ppEntity, ++pValue, ++Index)
    {
      if (dynamic_cast< const CMetab * >(*ppEntity) != NULL)
        {
          *pValue = floor(*pValue + 0.5);

          if ((*ppEntity)->getStatus() == CModelEntity::REACTIONS)
            {
              *pSpeciesAfterTau = *pValue;
              pSpeciesAfterTau++;

              if (mFirstReactionSpeciesIndex == 0)
                {
                  mFirstReactionSpeciesIndex = Index;
                  mpMethodSpecies = pValue;
                }
            }
        }
    }

  // Update the model state so that the species are all represented by integers.
  mpModel->setState(mMethodState);
  mpModel->updateSimulatedValues(false); //for assignments

  // TODO handle species of type ASSIGNMENT.
  // These need to be checked whether they are sufficiently close to an integer

  C_FLOAT64 * pMethodStateValue = mMethodState.beginIndependent() - 1;

  // Build the reaction dependencies
  size_t NumReactions = 0;

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

      itDependencies->mMethodSpeciesIndex.resize(Balances.size());
      itDependencies->mSpeciesMultiplier.resize(Balances.size());
      itDependencies->mMethodSpecies.resize(Balances.size());
      itDependencies->mModelSpecies.resize(Balances.size());

      std::set< const CCopasiObject * > changed;

      CCopasiVector< CChemEqElement >::const_iterator itBalance = Balances.begin();
      CCopasiVector< CChemEqElement >::const_iterator endBalance = Balances.end();

      size_t Index = 0;

      for (; itBalance != endBalance; ++itBalance)
        {
          const CMetab * pMetab = (*itBalance)->getMetabolite();

          if (pMetab->getStatus() == CModelEntity::REACTIONS)
            {
              itDependencies->mMethodSpeciesIndex[Index] = StateTemplate.getIndex(pMetab) - mFirstReactionSpeciesIndex;
              itDependencies->mSpeciesMultiplier[Index] = floor((*itBalance)->getMultiplicity() + 0.5);
              itDependencies->mMethodSpecies[Index] = pMethodStateValue + StateTemplate.getIndex(pMetab);
              itDependencies->mModelSpecies[Index] = (C_FLOAT64 *) pMetab->getValueReference()->getValuePointer();

              changed.insert(pMetab->getValueReference());

              Index++;
            }
        }

      // Correct allocation for metabolites which are not determined by reactions
      itDependencies->mMethodSpeciesIndex.resize(Index, true);
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

          itDependencies->mSubstrateMultiplier[Index] = floor((*itSubstrate)->getMultiplicity() + 0.5);
          itDependencies->mMethodSubstrates[Index] = pMethodStateValue + StateTemplate.getIndex(pMetab);
          itDependencies->mModelSubstrates[Index] = (C_FLOAT64 *) pMetab->getValueReference()->getValuePointer();
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
      ++NumReactions;
    }

  mNumReactions = NumReactions;

  mReactionDependencies.resize(mNumReactions);
  mAmu.resize(mNumReactions, true);

  mA0 = 0;
  size_t i;

  for (i = 0; i < mNumReactions; i++)
    {
      mA0 += calculateAmu(i);
    }

  mMaxStepsReached = false;
  mNextReactionTime = mpCurrentState->getTime();
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

  if (pTP->getModel()->getTotSteps() < 1)
    {
      //at least one reaction necessary
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 17);
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
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 18);
              return false;
            }
          else if (dynamic_cast<const CCompartment *>(*ppEntity) != NULL)
            {
              // compartment ode rule found
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 21);
              return false;
            }
          else
            {
              // species ode rule found
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 20);
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
      CCopasiMessage(CCopasiMessage::EXCEPTION, message.c_str());
      return false;
    }

  if (* getValue("Max Internal Steps").pINT <= 0)
    {
      //max steps should be at least 1
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 15);
      return false;
    }

  return true;
}

C_FLOAT64 CTrajAdaptiveSA::doSingleTauLeapStep(const C_FLOAT64 & curTime, const C_FLOAT64 & endTime)
{
  std::vector< CReactionDependencies >::const_iterator itDependencies = mReactionDependencies.begin();
  std::vector< CReactionDependencies >::const_iterator endDependencies = mReactionDependencies.end();
  size_t * pMaxReactionFiring = mMaxReactionFiring.array();

  for (; itDependencies != endDependencies; ++itDependencies, ++pMaxReactionFiring)
    {
      C_FLOAT64 *const* ppModelSpecies = itDependencies->mModelSpecies.array();
      const C_FLOAT64 * pMultiplicity = itDependencies->mSpeciesMultiplier.array();
      const C_FLOAT64 * pMultiplicityEnd = pMultiplicity + itDependencies->mSpeciesMultiplier.size();

      *pMaxReactionFiring = std::numeric_limits< size_t >::max(); // Assigned a maximum value

      for (; pMultiplicity != pMultiplicityEnd; pMultiplicity++, ppModelSpecies++)
        {
          if (*pMultiplicity < 0)
            {
              size_t TmpMax;

              if ((TmpMax = (size_t)(**ppModelSpecies / *pMultiplicity)) < *pMaxReactionFiring)
                {
                  *pMaxReactionFiring = TmpMax;
                }
            }
        }
    }

  size_t NonCriticalReactions = 0;
  size_t InsertCritical = mNumReactions - 1;

  pMaxReactionFiring = mMaxReactionFiring.array();
  const C_FLOAT64 * pAmu = mAmu.array();

  itDependencies = mReactionDependencies.begin();
  C_FLOAT64 * pReactionFiring = mReactionFiring.array();

  for (; itDependencies != endDependencies; ++itDependencies, ++pAmu, ++pMaxReactionFiring, ++pReactionFiring)
    {
      *pReactionFiring = 0;

      if (*pAmu == 0 ||
          *pMaxReactionFiring > UPPER_LIMIT)
        {
          mPartitionedDependencies[NonCriticalReactions] = &(*itDependencies);
          mPartitionedAmu[NonCriticalReactions] = pAmu;
          mPartitionedReactionFiring[NonCriticalReactions] = pReactionFiring;
          NonCriticalReactions++;
        }
      else
        {
          mPartitionedDependencies[InsertCritical] = &(*itDependencies);
          mPartitionedAmu[InsertCritical] = pAmu;
          mPartitionedReactionFiring[InsertCritical] = pReactionFiring;
          InsertCritical--;
        }
    }

  mAvgDX = 0.0;
  mSigDX = 0.0;

  const CReactionDependencies **ppOrderedReactions = mPartitionedDependencies.array();
  const C_FLOAT64 ** ppOrderedAmu = mPartitionedAmu.array();
  const C_FLOAT64 ** ppOrderedAmuEnd = ppOrderedAmu + NonCriticalReactions;

  for (; ppOrderedAmu != ppOrderedAmuEnd; ++ppOrderedReactions, ++ppOrderedAmu)
    {
      const C_FLOAT64 * pMultiplicity = (*ppOrderedReactions)->mSpeciesMultiplier.array();
      const C_FLOAT64 * pMultiplicityEnd = pMultiplicity + (*ppOrderedReactions)->mSpeciesMultiplier.size();
      const size_t * pIndex = (*ppOrderedReactions)->mMethodSpeciesIndex.array();

      for (; pMultiplicity != pMultiplicityEnd; pMultiplicity++, pIndex++)
        {
          mAvgDX[*pIndex] += **ppOrderedAmu * *pMultiplicity;
          mSigDX[*pIndex] += **ppOrderedAmu * *pMultiplicity * *pMultiplicity;
        }
    }

  C_FLOAT64 MaxTau;

  if (NonCriticalReactions == 0)
    {
      MaxTau = 0;
    }
  else
    {
      C_FLOAT64 ex, t1, t2;
      t1 = t2 = std::numeric_limits< C_FLOAT64 >::infinity();

      for (size_t i = 0; i < mNumReactionSpecies; i++)
        {
          C_FLOAT64 t3, t4, t5, t6;

          ex = (*(mpMethodSpecies + i) * mEpsilon) + 1.0;
          t3 = fabs(mAvgDX[i]);
          t4 = mSigDX[i];
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
      mpModel->setState(mMethodState);
      mpModel->updateSimulatedValues(false);

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

      C_FLOAT64 * pSpeciesAfterTau = mSpeciesAfterTau.array();
      C_FLOAT64 * pSpeciesAfterTauEnd = pSpeciesAfterTau + mNumReactionSpecies;
      C_FLOAT64 * pMethodSpecies = mpMethodSpecies;

      for (; pSpeciesAfterTau != pSpeciesAfterTauEnd; ++pSpeciesAfterTau, ++pMethodSpecies)
        {
          *pSpeciesAfterTau = *pMethodSpecies;
        }

      ppOrderedReactions = mPartitionedDependencies.array();
      const CReactionDependencies **ppOrderedReactionsEnd = ppOrderedReactions + NonCriticalReactions;
      ppOrderedReactionFiring = mPartitionedReactionFiring.array();

      for (; ppOrderedReactions != ppOrderedReactionsEnd; ++ppOrderedReactions, ++ppOrderedReactionFiring)
        {
          const C_FLOAT64 * pMultiplicity = (*ppOrderedReactions)->mSpeciesMultiplier.array();
          const C_FLOAT64 * pMultiplicityEnd = pMultiplicity + (*ppOrderedReactions)->mSpeciesMultiplier.size();
          const size_t *pIndex = (*ppOrderedReactions)->mMethodSpeciesIndex.array();

          for (; pMultiplicity != pMultiplicityEnd;  pMultiplicity++, pIndex++)
            {
              mSpeciesAfterTau[*pIndex] += (*pMultiplicity * **ppOrderedReactionFiring);
            }

          **ppOrderedReactionFiring = 0.0;
        }

      if (CriticalReactionIndex != C_INVALID_INDEX)
        {
          const CReactionDependencies * pCriticalReaction = mPartitionedDependencies[CriticalReactionIndex];

          const C_FLOAT64 * pMultiplicity = pCriticalReaction->mSpeciesMultiplier.array();
          const C_FLOAT64 * pMultiplicityEnd = pMultiplicity + pCriticalReaction->mSpeciesMultiplier.size();
          const size_t *pIndex = pCriticalReaction->mMethodSpeciesIndex.array();

          for (; pMultiplicity != pMultiplicityEnd;  pMultiplicity++, pIndex++)
            {
              mSpeciesAfterTau[*pIndex] += *pMultiplicity;
            }
        }

      pSpeciesAfterTau = mSpeciesAfterTau.array();

      for (; pSpeciesAfterTau != pSpeciesAfterTauEnd; ++pSpeciesAfterTau)
        {
          if (*pSpeciesAfterTau < 0)
            break;
        }

      if (pSpeciesAfterTau != pSpeciesAfterTauEnd)
        {
          isUpdated = false;
          MaxTau = MaxTau / 2.0;
        }
      else
        {
          isUpdated = true;

          pSpeciesAfterTau = mSpeciesAfterTau.array();
          pMethodSpecies = mpMethodSpecies;

          for (; pSpeciesAfterTau != pSpeciesAfterTauEnd; ++pSpeciesAfterTau, ++pMethodSpecies)
            {
              *pMethodSpecies = *pSpeciesAfterTau;
            }
        }
    }

  mpModel->setState(mMethodState);
  mpModel->updateSimulatedValues(false);

  mA0 = 0;
  size_t i;

  for (i = 0; i < mNumReactions; i++)
    {
      mA0 += calculateAmu(i);
    }

  return Tau;
}

C_FLOAT64 CTrajAdaptiveSA::doSingleSSAStep(const C_FLOAT64 & curTime, const C_FLOAT64 & endTime)
{
  if (mNextReactionIndex == C_INVALID_INDEX)
    {
      if (mA0 == 0)
        {
          return endTime - curTime;
        }

      mNextReactionTime = curTime - log(mpRandomGenerator->getRandomOO()) / mA0;
    }

  if (mNextReactionTime >= endTime)
    {
      return endTime - curTime;
    }

  // We are sure that we have at least 1 reaction
  mNextReactionIndex = 0;

  C_FLOAT64 sum = 0.0;
  C_FLOAT64 rand = mpRandomGenerator->getRandomOO() * mA0;

  C_FLOAT64 * pAmu = mAmu.array();
  C_FLOAT64 * endAmu = pAmu + mNumReactions;

  for (; (sum < rand) && (pAmu != endAmu); ++pAmu, ++mNextReactionIndex)
    {
      sum += *pAmu;
    }

  mNextReactionIndex--;

  CReactionDependencies & Dependencies = mReactionDependencies[mNextReactionIndex];

  // Update the method internal and model species numbers
  C_FLOAT64 ** ppModelSpecies = Dependencies.mModelSpecies.array();
  C_FLOAT64 ** ppLocalSpecies = Dependencies.mMethodSpecies.array();
  C_FLOAT64 * pMultiplicity = Dependencies.mSpeciesMultiplier.array();
  C_FLOAT64 * pMultiplicityEnd = pMultiplicity + Dependencies.mSpeciesMultiplier.size();
  //if(mAmu.array()[mNextReactionIndex]==0) //Important check
  //  printf("Error 0\n");

  for (; pMultiplicity != pMultiplicityEnd; ++pMultiplicity, ++ppLocalSpecies, ++ppModelSpecies)
    {
      **ppLocalSpecies += *pMultiplicity;
      **ppModelSpecies = **ppLocalSpecies;
    }

  // Calculate all values which depend on the firing reaction
  std::vector< Refresh * >::const_iterator itCalcualtion =  Dependencies.mCalculations.begin();
  std::vector< Refresh * >::const_iterator endCalcualtion =  Dependencies.mCalculations.end();

  while (itCalcualtion != endCalcualtion)
    {
      (**itCalcualtion++)();
    }

  // calculate the propensities which depend on the firing reaction
  size_t * pDependentReaction = Dependencies.mDependentReactions.array();
  size_t * endDependentReactions = pDependentReaction + Dependencies.mDependentReactions.size();

  for (; pDependentReaction != endDependentReactions; ++pDependentReaction)
    {
      calculateAmu(*pDependentReaction);
    }

  // calculate the total propensity
  pAmu = mAmu.array();

  mA0 = 0.0;

  for (; pAmu != endAmu; ++pAmu)
    {
      mA0 += *pAmu;
    }

  mNextReactionIndex = C_INVALID_INDEX;

  return mNextReactionTime - curTime;
}

const C_FLOAT64 & CTrajAdaptiveSA::calculateAmu(const size_t & index)
{
  const CReactionDependencies & Dependencies = mReactionDependencies[index];
  C_FLOAT64 & Amu = mAmu[index];

  Amu = *Dependencies.mpParticleFlux;

  if (!mDoCorrection)
    {
      return Amu;
    }

  C_FLOAT64 SubstrateMultiplier = 1.0;
  C_FLOAT64 SubstrateDevisor = 1.0;
  C_FLOAT64 Multiplicity;
  C_FLOAT64 LowerBound;
  C_FLOAT64 Number;

  bool ApplyCorrection = false;

  const C_FLOAT64 * pMultiplicity = Dependencies.mSubstrateMultiplier.array();
  const C_FLOAT64 * pEndMultiplicity = pMultiplicity + Dependencies.mSubstrateMultiplier.size();
  C_FLOAT64 *const* ppLocalSubstrate = Dependencies.mMethodSubstrates.array();
  C_FLOAT64 *const* ppModelSubstrate = Dependencies.mModelSubstrates.array();

  for (; pMultiplicity != pEndMultiplicity; ++pMultiplicity, ++ppLocalSubstrate, ++ppModelSubstrate)
    {
      Multiplicity = *pMultiplicity;

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
    }
  else if (ApplyCorrection)
    {
      Amu *= SubstrateMultiplier / SubstrateDevisor;
    }

  return Amu;
}
