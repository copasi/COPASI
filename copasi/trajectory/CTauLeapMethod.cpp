// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTauLeapMethod.cpp,v $
//   $Revision: 1.29 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/04/05 14:31:15 $
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

#include "mathematics.h" // pow(), floor()

#include "copasi.h"

#include "CTauLeapMethod.h"
#include "CTrajectoryProblem.h"
#include "CHybridMethod.h" // CHybridBalance, todo: beautify this
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

CTauLeapMethod::CReactionDependencies::CReactionDependencies():
    mSpeciesMultiplier(0),
    mMethodSpeciesIndex(0),
    mMethodSpecies(0),
    mModelSpecies(0),
    mSubstrateMultiplier(0),
    mMethodSubstrates(0),
    mModelSubstrates(0),
    mpParticleFlux(NULL)
{}

CTauLeapMethod::CReactionDependencies::CReactionDependencies(const CReactionDependencies & src):
    mSpeciesMultiplier(src.mSpeciesMultiplier),
    mMethodSpeciesIndex(src.mMethodSpeciesIndex),
    mMethodSpecies(src.mMethodSpecies),
    mModelSpecies(src.mModelSpecies),
    mSubstrateMultiplier(src.mSubstrateMultiplier),
    mMethodSubstrates(src.mMethodSubstrates),
    mModelSubstrates(src.mModelSubstrates),
    mpParticleFlux(src.mpParticleFlux)
{}

CTauLeapMethod::CReactionDependencies::~CReactionDependencies()
{}

CTauLeapMethod::CReactionDependencies & CTauLeapMethod::CReactionDependencies::operator = (const CTauLeapMethod::CReactionDependencies & rhs)
{
  mSpeciesMultiplier = rhs.mSpeciesMultiplier;
  mMethodSpeciesIndex = rhs.mMethodSpeciesIndex;
  mMethodSpecies = rhs.mMethodSpecies;
  mModelSpecies = rhs.mModelSpecies;
  mSubstrateMultiplier = rhs.mSubstrateMultiplier;
  mMethodSubstrates = rhs.mMethodSubstrates;
  mModelSubstrates = rhs.mModelSubstrates;
  mpParticleFlux = rhs.mpParticleFlux;

  return * this;
}

/* PUBLIC METHODS ************************************************************/

/**
 *   Creates a TauLeapMethod adequate for the problem.
 *   (only regular TauLeapMethod so far)
 */
CTauLeapMethod *CTauLeapMethod::createTauLeapMethod()
{
  C_INT32 result = 1; // regular TauLeap method as default

  CTauLeapMethod * method = NULL;

  switch (result)
    {
        // Error: TauLeap simulation impossible
        /*    case - 3:      // non-integer stoichiometry
        CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 1);
        break;
        case - 2:      // reversible reaction exists
        CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 2);
        break;
        case - 1:      // more than one compartment involved
        CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 3);
        break;*/
        // Everything all right: Hybrid simulation possible
      case 1:
      default:
        method = new CTauLeapMethod();
        break;
    }

  return method;
}

/**
 *   Default constructor.
 */
CTauLeapMethod::CTauLeapMethod(const CCopasiContainer * pParent):
    CTrajectoryMethod(CCopasiMethod::tauLeap, pParent)
{
  mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
  initializeParameter();
}

CTauLeapMethod::CTauLeapMethod(const CTauLeapMethod & src,
                               const CCopasiContainer * pParent):
    CTrajectoryMethod(src, pParent)
{
  mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
  initializeParameter();
}

/**
 *   Destructor.
 */
CTauLeapMethod::~CTauLeapMethod()
{
  cleanup();
  DESTRUCTOR_TRACE;
}

void CTauLeapMethod::initializeParameter()
{
  CCopasiParameter *pParm;

  assertParameter("Epsilon", CCopasiParameter::DOUBLE, (C_FLOAT64) EPS);
  assertParameter("Max Internal Steps", CCopasiParameter::UINT, (unsigned C_INT32) 10000);
  assertParameter("Use Random Seed", CCopasiParameter::BOOL, false);
  assertParameter("Random Seed", CCopasiParameter::UINT, (unsigned C_INT32) 1);

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("TAULEAP.Tau")) != NULL)
    {
      removeParameter("TAULEAP.Tau");

      if ((pParm = getParameter("TAULEAP.UseRandomSeed")) != NULL)
        {
          setValue("Use Random Seed", *pParm->getValue().pBOOL);
          removeParameter("TAULEAP.UseRandomSeed");
        }

      if ((pParm = getParameter("TAULEAP.RandomSeed")) != NULL)
        {
          setValue("Random Seed", *pParm->getValue().pUINT);
          removeParameter("TAULEAP.RandomSeed");
        }
    }
}

bool CTauLeapMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

CTrajectoryMethod::Status CTauLeapMethod::step(const double & deltaT)
{

  // do several steps
  C_FLOAT64 time = mpCurrentState->getTime();
  C_FLOAT64 endTime = time + deltaT;

  unsigned C_INT32 Steps = 0;

  while (time < endTime)
    {
      time += doSingleStep(endTime - time);

      if (++Steps > mMaxSteps)
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 12);
        }
    }

  *mpCurrentState = mpProblem->getModel()->getState();
  mpCurrentState->setTime(time);

  return NORMAL;
}

void CTauLeapMethod::start(const CState * initialState)
{
  /* get configuration data */

  bool useRandomSeed = * getValue("Use Random Seed").pBOOL;
  unsigned C_INT32 randomSeed = * getValue("Random Seed").pUINT;

  if (useRandomSeed) mpRandomGenerator->initialize(randomSeed);

  mEpsilon = * getValue("Epsilon").pDOUBLE;
  mUseRandomSeed = * getValue("Use Random Seed").pBOOL;
  mRandomSeed = * getValue("Random Seed").pUINT;
  mMaxSteps = * getValue("Max Internal Steps").pUINT;

  *mpCurrentState = *initialState;

  mpModel = mpProblem->getModel();
  assert(mpModel);

  if (mpModel->getModelType() == CModel::deterministic)
    mDoCorrection = true;
  else
    mDoCorrection = false;

  // Size the arrays
  mNumReactions = mpModel->getReactions().size();

  mReactionDependencies.resize(mNumReactions);
  mK.resize(mNumReactions);
  mAmu.resize(mNumReactions);
  mAmu = 0.0;

  mNumReactionSpecies = mpModel->getNumIndependentReactionMetabs() + mpModel->getNumDependentReactionMetabs();

  mAvgDX.resize(mNumReactionSpecies);
  mSigDX.resize(mNumReactionSpecies);

  // Create a local copy of the state where the particle number are rounded to integers
  mMethodState = mpModel->getState();

  const CStateTemplate & StateTemplate = mpModel->getStateTemplate();

  CModelEntity *const* ppEntity = StateTemplate.beginIndependent();
  CModelEntity *const* endEntity = StateTemplate.endFixed();
  C_FLOAT64 * pValue = mMethodState.beginIndependent();

  mFirstReactionSpeciesIndex = 0;
  size_t Index = 1;

  for (; ppEntity != endEntity; ++ppEntity, ++pValue, ++Index)
    {
      if (dynamic_cast< const CMetab * >(*ppEntity) != NULL)
        {
          *pValue = floor(*pValue + 0.5);

          if (mFirstReactionSpeciesIndex == 0 &&
              (*ppEntity)->getStatus() == CModelEntity::REACTIONS)
            {
              mFirstReactionSpeciesIndex = Index;
            }
        }
    }

  // Update the model state so that the species are all represented by integers.
  mpModel->setState(mMethodState);
  mpModel->updateSimulatedValues(false); //for assignments

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

      CCopasiVector< CChemEqElement >::const_iterator itBalance = Balances.begin();
      CCopasiVector< CChemEqElement >::const_iterator endBalance = Balances.end();

      Index = 0;

      for (; itBalance != endBalance; ++itBalance)
        {
          const CMetab * pMetab = (*itBalance)->getMetabolite();

          if (pMetab->getStatus() == CModelEntity::REACTIONS)
            {
              itDependencies->mMethodSpeciesIndex[Index] = StateTemplate.getIndex(pMetab) - mFirstReactionSpeciesIndex;
              itDependencies->mSpeciesMultiplier[Index] = floor((*itBalance)->getMultiplicity() + 0.5);
              itDependencies->mMethodSpecies[Index] = pMethodStateValue + StateTemplate.getIndex(pMetab);
              itDependencies->mModelSpecies[Index] = (C_FLOAT64 *) pMetab->getValueReference()->getValuePointer();

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
          itDependencies->mMethodSubstrates[Index] = mMethodState.beginIndependent() + (StateTemplate.getIndex(pMetab) - 1);
          itDependencies->mModelSubstrates[Index] = (C_FLOAT64 *) pMetab->getValueReference()->getValuePointer();
        }

      ++itDependencies;
      ++NumReactions;
    }

  mNumReactions = NumReactions;

  mReactionDependencies.resize(mNumReactions);
  mAmu.resize(mNumReactions, true);
  mK.resize(mNumReactions, true);

  return;
}

/* PROTECTED METHODS *********************************************************/

/**
 *  Initializes the solver and sets the model to be used.
 *
 *  @param model A reference to an instance of a CModel
 */

/**
 *  Cleans up memory, etc.
 */
void CTauLeapMethod::cleanup()
{
  delete mpRandomGenerator;
  mpRandomGenerator = NULL;
  mpModel = NULL;
  return;
}

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

  std::vector< CReactionDependencies >::const_iterator itReaction = mReactionDependencies.begin();
  const C_FLOAT64 * pAmu = mAmu.array();
  const C_FLOAT64 * pAmuEnd = pAmu + mNumReactions;

  for (; pAmu != pAmuEnd; ++pAmu, ++itReaction)
    {
      const C_FLOAT64 * pMultiplicity = itReaction->mSpeciesMultiplier.array();
      const C_FLOAT64 * pMultiplicityEnd = pMultiplicity + itReaction->mSpeciesMultiplier.size();
      const size_t * pIndex = itReaction->mMethodSpeciesIndex.array();

      for (; pMultiplicity != pMultiplicityEnd; ++pMultiplicity, ++pIndex)
        {
          mAvgDX[*pIndex] += *pMultiplicity * *pAmu;
          mSigDX[*pIndex] += *pMultiplicity * *pMultiplicity * *pAmu;
        }
    }

  Tau1 = Tau2 = std::numeric_limits< C_FLOAT64 >::infinity();

  const C_FLOAT64 * pNumber = mMethodState.beginIndependent() + mFirstReactionSpeciesIndex - 1;
  const C_FLOAT64 * pNumberEnd = pNumber + mNumReactionSpecies;
  C_FLOAT64 * pAvgDX = mAvgDX.array();
  C_FLOAT64 * pSigDX = mSigDX.array();

  for (; pNumber != pNumberEnd; ++pNumber, ++pAvgDX, ++pSigDX)
    {
      if ((Tmp = mEpsilon * fabs(*pNumber)) < 1.0)
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
      if ((Lambda = *pAmu * Tau) < 0.0)
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 10);

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
  //mA0Old = mA0;
  mA0 = 0;

  for (size_t i = 0; i < mNumReactions; i++)
    {
      mA0 += calculateAmu(i);
    }

  return;
}

const C_FLOAT64 &  CTauLeapMethod::calculateAmu(const size_t & index)
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

  const C_FLOAT64 * pMultiplier = Dependencies.mSubstrateMultiplier.array();
  const C_FLOAT64 * endMultiplier = pMultiplier + Dependencies.mSubstrateMultiplier.size();
  C_FLOAT64 *const* ppLocalSubstrate = Dependencies.mMethodSubstrates.array();
  C_FLOAT64 *const* ppModelSubstrate = Dependencies.mModelSubstrates.array();

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
    }
  else if (ApplyCorrection)
    {
      Amu *= SubstrateMultiplier / SubstrateDevisor;
    }

  return Amu;
}

/**
 *   Updates the system according to the probabilistic
 *   number of firings mK[i] of each reaction i
 */
bool CTauLeapMethod::updateSystem()
{
  std::vector< CReactionDependencies >::const_iterator itReaction = mReactionDependencies.begin();

  CState OldState(mMethodState);

  const C_FLOAT64 * pK = mK.array();
  const C_FLOAT64 * pKEnd = pK + mNumReactions;

  for (; pK != pKEnd; ++pK, ++itReaction)
    {
      const C_FLOAT64 * pMultiplicity = itReaction->mSpeciesMultiplier.array();
      const C_FLOAT64 * pMultiplicityEnd = pMultiplicity + itReaction->mSpeciesMultiplier.size();
      C_FLOAT64 * const * pSpecies = itReaction->mMethodSpecies.array();

      for (; pMultiplicity != pMultiplicityEnd; ++pMultiplicity, ++pSpecies)
        {
          **pSpecies += *pK * *pMultiplicity;
        }
    }

  const C_FLOAT64 * pSpecies = mMethodState.beginIndependent() + mFirstReactionSpeciesIndex - 1;

  const C_FLOAT64 * pSpeciesEnd = pSpecies + mNumReactionSpecies;

  for (; pSpecies != pSpeciesEnd; ++pSpecies)
    {
      if (*pSpecies < -0.5)
        {
          // We need to undo the changes
          mMethodState = OldState;
          return false;
        }
    }

  mpModel->setState(mMethodState);
  mpModel->updateSimulatedValues(false);

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

  if (pTP->getModel()->getTotSteps() < 1)
    {
      //at least one reaction necessary
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 17);
      return false;
    }

  //check for ODE rules
  C_INT32 i, imax = pTP->getModel()->getNumModelValues();

  for (i = 0; i < imax; ++i)
    {
      if (pTP->getModel()->getModelValues()[i]->getStatus() == CModelEntity::ODE)
        {
          //ode rule found
          CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 18);
          return false;
        }
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

  //events are not supported at the moment
  if (pTP->getModel()->getEvents().size() > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 23);
      return false;
    }

  return true;
}
