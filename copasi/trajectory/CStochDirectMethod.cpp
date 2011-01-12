// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CStochDirectMethod.cpp,v $
//   $Revision: 1.18.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/12 19:06:53 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
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
#include "CStochDirectMethod.h"
#include "utilities/CCopasiVector.h"
#include "function/CFunction.h"
#include "randomGenerator/CRandom.h"
#include "CTrajectoryMethod.h"
#include "CTrajectoryProblem.h"
#include "model/CState.h"
#include "model/CCompartment.h"
#include "model/CModel.h"

CStochDirectMethod::CReactionDependencies::CReactionDependencies():
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

CStochDirectMethod::CReactionDependencies::CReactionDependencies(const CReactionDependencies & src):
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

CStochDirectMethod::CReactionDependencies::~CReactionDependencies()
{}

CStochDirectMethod::CReactionDependencies & CStochDirectMethod::CReactionDependencies::operator = (const CStochDirectMethod::CReactionDependencies & rhs)
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

CStochDirectMethod::CStochDirectMethod(const CCopasiContainer * pParent):
    CTrajectoryMethod(CCopasiMethod::directMethod, pParent),
    mpRandomGenerator(CRandom::createGenerator(CRandom::mt19937)),
    mpModel(NULL),
    mNumReactions(0),
    mMaxSteps(1000000),
    mNextReactionTime(0.0),
    mNextReactionIndex(C_INVALID_INDEX),
    mDoCorrection(true),
    mAmu(0),
    mA0(0.0),
    mMethodState(),
    mReactionDependencies(0),
    mMaxStepsReached(false)
{
  initializeParameter();
}

CStochDirectMethod::CStochDirectMethod(const CStochDirectMethod & src,
                                       const CCopasiContainer * pParent):
    CTrajectoryMethod(src, pParent),
    mpRandomGenerator(CRandom::createGenerator(CRandom::mt19937)),
    mpModel(src.mpModel),
    mNumReactions(src.mNumReactions),
    mMaxSteps(src.mMaxSteps),
    mNextReactionTime(src.mNextReactionTime),
    mNextReactionIndex(src.mNextReactionIndex),
    mDoCorrection(src.mDoCorrection),
    mAmu(src.mAmu),
    mA0(src.mA0),
    mMethodState(src.mMethodState),
    mReactionDependencies(src.mReactionDependencies),
    mMaxStepsReached(src.mMaxStepsReached)
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
  C_FLOAT64 Time = mpCurrentState->getTime();
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

  *mpCurrentState = mpProblem->getModel()->getState();
  mpCurrentState->setTime(Time);

  return NORMAL;
}

void CStochDirectMethod::start(const CState * initialState)
{
  /* get configuration data */
  mMaxSteps = * getValue("Max Internal Steps").pINT;

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

  mReactionDependencies.resize(mNumReactions);
  mAmu.resize(mNumReactions);
  mAmu = 0.0;

  // Create a local copy of the state where the particle number are rounded to integers
  mMethodState = mpModel->getState();

  const CStateTemplate & StateTemplate = mpModel->getStateTemplate();

  CModelEntity *const* ppEntity = StateTemplate.beginIndependent();
  CModelEntity *const* endEntity = StateTemplate.endFixed();
  C_FLOAT64 * pValue = mMethodState.beginIndependent();

  for (; ppEntity != endEntity; ++ppEntity, ++pValue)
    {
      if (dynamic_cast< const CMetab * >(*ppEntity) != NULL)
        {
          *pValue = floor(*pValue + 0.5);
        }
    }

  // Update the model state so that the species are all represented by integers.
  mpModel->setState(mMethodState);
  mpModel->updateSimulatedValues(false); //for assignments

  // TODO CRITICAL Handle species of type ASSIGNMENT.
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
              itDependencies->mSpeciesMultiplier[Index] = floor((*itBalance)->getMultiplicity() + 0.5);
              itDependencies->mMethodSpecies[Index] = pMethodStateValue + StateTemplate.getIndex(pMetab);
              itDependencies->mModelSpecies[Index] = (C_FLOAT64 *) pMetab->getValueReference()->getValuePointer();

              changed.insert(pMetab->getValueReference());

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

  size_t i;

  for (i = 0; i < mNumReactions; i++)
    {
      calculateAmu(i);
    }

  mA0 = 0;

  for (i = 0; i < mNumReactions; i++)
    {
      mA0 += mAmu[i];
    }

  mMaxStepsReached = false;

  mNextReactionTime = mpCurrentState->getTime();
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

      mNextReactionTime = curTime - log(mpRandomGenerator->getRandomOO()) / mA0;

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
    }

  if (mNextReactionTime >= endTime)
    {
      return endTime - curTime;
    }

  CReactionDependencies & Dependencies = mReactionDependencies[mNextReactionIndex];

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

  for (; pDependentReaction != endDependentReactions; ++pDependentReaction)
    {
      calculateAmu(*pDependentReaction);
    }

  // calculate the total propensity
  C_FLOAT64 * pAmu = mAmu.array();
  C_FLOAT64 * endAmu = pAmu + mNumReactions;

  mA0 = 0.0;

  for (; pAmu != endAmu; ++pAmu)
    {
      mA0 += *pAmu;
    }

  mNextReactionIndex = C_INVALID_INDEX;

  return mNextReactionTime - curTime;
}

void CStochDirectMethod::calculateAmu(const size_t & index)
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
