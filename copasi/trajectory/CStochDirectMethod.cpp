// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CStochDirectMethod.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/11/20 18:26:47 $
// End CVS Header

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

#define mtxIdx(row,col,intv)  ((row)+(col)*(intv))

CStochDirectMethod *
CStochDirectMethod::createStochDirectMethod()
{
  CStochDirectMethod * pMethod = NULL;

  pMethod = new CStochDirectMethod();

  return pMethod;
}

CStochDirectMethod::CStochDirectMethod(const CCopasiContainer * pParent):
    CTrajectoryMethod(CCopasiMethod::directMethod, pParent)
{
  initializeParameter();
  isPrinted = false;
  dpgLen = dpgTable = steLen = NULL;
  steTable =  chgLen = chgTable = NULL;
  species = steVec = chgVec = NULL;
  mAmu = NULL;
  rcRt = NULL;
  calculations = NULL;
  mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
}

CStochDirectMethod::CStochDirectMethod(const CStochDirectMethod & src,
                                       const CCopasiContainer * pParent):
    CTrajectoryMethod(src, pParent)
{
  initializeParameter();
  isPrinted = false;
  dpgLen = dpgTable = steLen = NULL;
  steTable =  chgLen = chgTable = NULL;
  species = steVec = chgVec = NULL;
  mAmu = NULL;
  rcRt = NULL;
  calculations = NULL;
  mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
}

CStochDirectMethod::~CStochDirectMethod()
{
  delete mpRandomGenerator;
  pfree(dpgLen);
  pfree(dpgTable);
  pfree(steLen);
  pfree(steTable);
  pfree(chgLen);
  pfree(chgTable);
  pfree(species);
  pfree(steVec);
  pfree(chgVec);
  pfree(mAmu);
  pfree(rcRt);
  //delete calculations; // Can't free
  mpRandomGenerator = NULL;
}

void CStochDirectMethod::initializeParameter()
{
  CCopasiParameter *pParm;

  assertParameter("Max Internal Steps", CCopasiParameter::INT, (C_INT32) 1000000);
  assertParameter("Subtype", CCopasiParameter::UINT, (unsigned C_INT32) 2);
  assertParameter("Use Random Seed", CCopasiParameter::BOOL, false);
  assertParameter("Random Seed", CCopasiParameter::UINT, (unsigned C_INT32) 1);

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("STOCH.MaxSteps")) != NULL)
    {
      setValue("Max Internal Steps", *pParm->getValue().pINT);
      removeParameter("STOCH.MaxSteps");

      if ((pParm = getParameter("STOCH.Subtype")) != NULL)
        {
          setValue("Subtype", *pParm->getValue().pUINT);
          removeParameter("STOCH.Subtype");
        }

      if ((pParm = getParameter("STOCH.UseRandomSeed")) != NULL)
        {
          setValue("Use Random Seed", *pParm->getValue().pBOOL);
          removeParameter("STOCH.UseRandomSeed");
        }

      if ((pParm = getParameter("STOCH.RandomSeed")) != NULL)
        {
          setValue("Random Seed", *pParm->getValue().pUINT);
          removeParameter("STOCH.RandomSeed");
        }
    }
}

bool CStochDirectMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

CTrajectoryMethod::Status CStochDirectMethod::step(const double & deltaT)
{
  // write the current state to the model:
  //mpProblem->getModel()->setState(mpCurrentState); //?

  // check for possible overflows:
  unsigned C_INT32 i;
  unsigned C_INT32 imax;
  unsigned C_INT32 mMaxIntBeforeStep = (1 << 30);

  // :TODO: Bug 774: This assumes that the number of variable metabs is the number
  // of metabs determined by reaction. In addition they are expected at the beginning of the
  // MetabolitesX which is not the case if we have metabolites of type ODE.
  for (i = 0, imax = mpProblem->getModel()->getNumVariableMetabs(); i < imax; i++)
    if (mpProblem->getModel()->getMetabolitesX()[i]->getValue() >= mMaxIntBeforeStep)
      {
        CCopasiMessage(CCopasiMessage::EXCEPTION, "at least one particle number got to big.");
        // TODO:throw exception or something like that
      }

  // do several steps:
  C_FLOAT64 Time = mpCurrentState->getTime();
  C_FLOAT64 EndTime = Time + deltaT;

  for (i = 0; ((i < (unsigned C_INT32) mMaxSteps) && (Time < EndTime)); i++)
    {
      Time += doSingleStep(Time, EndTime);
    }

  *mpCurrentState = mpProblem->getModel()->getState();
  mpCurrentState->setTime(EndTime);

  if ((i >= (unsigned C_INT32) mMaxSteps) && (!mMaxStepsReached))
    {
      mMaxStepsReached = true; //only report this message once
      CCopasiMessage(CCopasiMessage::WARNING, "maximum number of reaction events was reached in at least one simulation step.\nThat means time intervals in the output may not be what you requested.");
    }

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

  unsigned C_INT32 i, j, k, l;

  //initialize the vector of ints that contains the particle numbers
  //for the discrete simulation. This also floors all particle numbers in the model.

  mNumReactions = mpModel->getReactions().size();
  mNumSpecies = mpModel->getMetabolitesX().size();

  pfree(dpgLen);
  pfree(dpgTable);
  pfree(steLen);
  pfree(steTable);
  pfree(chgLen);
  pfree(chgTable);
  pfree(species);
  pfree(steVec);
  pfree(chgVec);
  pfree(mAmu);
  pfree(rcRt);
  //delete calculations; // Can't free

  if (species == NULL)  species = (C_FLOAT64 *)malloc(sizeof(C_FLOAT64) * mNumSpecies);

  if (dpgLen == NULL)  dpgLen = (C_INT32 *)malloc(sizeof(C_INT32) * mNumReactions);

  if (dpgTable == NULL)  dpgTable = (C_INT32 *)malloc(sizeof(C_INT32) * mNumReactions * mNumReactions);

  if (steLen == NULL)  steLen = (C_INT32 *)malloc(sizeof(C_INT32) * mNumReactions);

  if (steTable == NULL)  steTable = (C_INT32 *)malloc(sizeof(C_INT32) * mNumReactions * mNumSpecies);

  if (chgLen == NULL)  chgLen = (C_INT32 *)malloc(sizeof(C_INT32) * mNumReactions);

  if (chgTable == NULL)  chgTable = (C_INT32 *)malloc(sizeof(C_INT32) * mNumReactions * mNumSpecies);

  if (steVec == NULL)  steVec = (C_FLOAT64 *)malloc(sizeof(C_FLOAT64) * mNumReactions * mNumSpecies);

  if (chgVec == NULL)  chgVec = (C_FLOAT64 *)malloc(sizeof(C_FLOAT64) * mNumReactions * mNumSpecies);

  if (mAmu == NULL)  mAmu = (C_FLOAT64 *)malloc(sizeof(C_FLOAT64) * mNumReactions);

  if (rcRt == NULL)  rcRt = (C_FLOAT64 **)malloc(sizeof(C_FLOAT64 *) * mNumReactions);

  if (calculations == NULL)  calculations = new std::vector< Refresh * >[mNumReactions];

  if (species == NULL)
    {
      fprintf(stderr, "CStochDirectMethod::start Error --- Can't allocate species memory\n");
      exit(1);
    }

  if (dpgLen == NULL)
    {
      fprintf(stderr, "CStochDirectMethod::start Error --- Can't allocate species length vector memory\n");
      exit(1);
    }

  if (dpgTable == NULL)
    {
      fprintf(stderr, "CStochDirectMethod::start Error --- Can't allocate species table memory\n");
      exit(1);
    }

  if (steLen == NULL)
    {
      fprintf(stderr, "CStochDirectMethod::start Error --- Can't allocate state length vector memory\n");
      exit(1);
    }

  if (steTable == NULL)
    {
      fprintf(stderr, "CStochDirectMethod::start Error --- Can't allocate state table memory\n");
      exit(1);
    }

  if (chgLen == NULL)
    {
      fprintf(stderr, "CStochDirectMethod::start Error --- Can't allocate state change length vector memory\n");
      exit(1);
    }

  if (chgTable == NULL)
    {
      fprintf(stderr, "CStochDirectMethod::start Error --- Can't allocate state change table memory\n");
      exit(1);
    }

  if (steVec == NULL)
    {
      fprintf(stderr, "CStochDirectMethod::start Error --- Can't allocate status vector memory\n");
      exit(1);
    }

  if (chgVec == NULL)
    {
      fprintf(stderr, "CStochDirectMethod::start Error --- Can't allocate status change vector memory\n");
      exit(1);
    }

  if (mAmu == NULL)
    {
      fprintf(stderr, "CStochDirectMethod::start Error --- Can't allocate propensity vector memory\n");
      exit(1);
    }

  if (rcRt == NULL)
    {
      fprintf(stderr, "CStochDirectMethod::start Error --- Can't allocate reaction rate vector memory\n");
      exit(1);
    }

  for (i = 0; i < mNumSpecies; i++)
    {
      species[i] = 0.0;
    }

  for (i = 0; i < mNumReactions; i++)
    {
      mAmu[i] = 0.0;
      dpgLen[i] = steLen[i] = chgLen[i] = 0;
    }

  for (i = 0; i < (mNumReactions*mNumSpecies); i++)
    {
      steTable[i] = chgTable[i] = -1;
    }

  for (i = 0; i < (mNumReactions*mNumReactions); i++)
    {
      dpgTable[i] = -1;
    }

  for (i = 0; i < mNumSpecies; i++)
    for (j = 0; j < mNumReactions; j++)
      steVec[mtxIdx(i, j, mNumSpecies)] = chgVec[mtxIdx(i, j, mNumSpecies)] = 0.0;

  for (i = 0; i < mNumSpecies; i++)
    species[i] = floor(mpModel->getMetabolitesX()[i]->getValue());

  for (i = 0; i < mNumReactions; i++)
    {
      const CCopasiVector<CChemEqElement> * bbb;

      rcRt[i] = (double *)mpModel->getReactions()[i]->getParticleFluxReference()->getValuePointer();

      std::set< const CCopasiObject * > changed;
      bbb = &mpModel->getReactions()[i]->getChemEq().getBalances();

      //std::cout << std::endl << i << " : ";
      //TODO clear old local balances and substrates
      for (j = l = 0; j < bbb->size(); j++)
        {
          assert((*bbb)[j]->getMetabolite());

          if (((*bbb)[j]->getMetabolite()->getStatus()) != CModelEntity::FIXED)
            {
              k = mpModel->getMetabolitesX().getIndex((*bbb)[j]->getMetabolite());
              chgTable[mtxIdx(l, i, mNumSpecies)] = k;
              chgVec[mtxIdx(k, i, mNumSpecies)] = floor((*bbb)[j]->getMultiplicity() + 0.5);
              changed.insert((*bbb)[j]->getMetabolite()->getValueReference());
              l++;
            }
        }

      chgLen[i] = l;

      bbb = &mpModel->getReactions()[i]->getChemEq().getSubstrates();

      //std::cout << std::endl << i << " : ";
      steLen[i] = bbb->size();

      for (j = 0; j < bbb->size(); j++)
        {
          assert((*bbb)[j]->getMetabolite());
          k = mpModel->getMetabolitesX().getIndex((*bbb)[j]->getMetabolite());
          steTable[mtxIdx(j, i, mNumSpecies)] = k;
          steVec[mtxIdx(k, i, mNumSpecies)] = floor((*bbb)[j]->getMultiplicity() + 0.5);
        }

      std::set< const CCopasiObject * > dependend;

      for (j = 0; j < mNumReactions; j++)
        {
          if (mpModel->getReactions()[j]->getParticleFluxReference()->dependsOn(changed))
            {
              dependend.insert(mpModel->getReactions()[j]->getParticleFluxReference());
              l = dpgLen[i];
              dpgTable[mtxIdx(i, l, mNumReactions)] = j;
              dpgLen[i] = l + 1;
            }
        }

      calculations[i] = CCopasiObject::buildUpdateSequence(dependend, changed);
    }

  for (i = 0; i < mNumReactions; i++)
    {
      calculateAmu(i);
    }

  mA0 = 0;

  for (i = 0; i < mNumReactions; i++)
    {
      mA0 += mAmu[i];
    }

  mpModel->updateSimulatedValues(false); //for assignments
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

  if (pTP->getModel()->getQuantityUnitEnum() == CModel::dimensionlessQuantity)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 22);
      return false;
    }

  return true;
}

C_FLOAT64 CStochDirectMethod::doSingleStep(C_FLOAT64 curTime, C_FLOAT64 endTime)
{

  unsigned C_INT32 i, j, l;

  if (mNextReactionIndex == C_INVALID_INDEX)
    {
      if (mA0 == 0)
        {
          return endTime - curTime;
        }

      mNextReactionTime = curTime - 1.0 * log(mpRandomGenerator->getRandomOO()) / mA0;

      // We are sure that we have at least 1 reaction
      mNextReactionIndex = 0;
      C_FLOAT64 sum = 0.0;
      C_FLOAT64 rand = mpRandomGenerator->getRandomOO() * mA0;

      for (; (sum < rand) && (mNextReactionIndex < mNumReactions); ++mNextReactionIndex)
        {
          sum += mAmu[mNextReactionIndex];
        }

      mNextReactionIndex--;
    }

  if (mNextReactionTime >= endTime)
    {
      return endTime - curTime;
    }

  l = chgLen[mNextReactionIndex];

  for (i = 0; i < l; i++)
    {
      j = chgTable[mtxIdx(i, mNextReactionIndex, mNumSpecies)];
      species[j] += chgVec[mtxIdx(j, mNextReactionIndex, mNumSpecies)];
      mpModel->getMetabolitesX()[j]->setValue(species[j]);
    }

  std::vector< Refresh * >::const_iterator itCalcualtion =  calculations[mNextReactionIndex].begin();
  std::vector< Refresh * >::const_iterator endCalcualtion =  calculations[mNextReactionIndex].end();

  while (itCalcualtion != endCalcualtion)
    {
      (**itCalcualtion++)();
    }

  l = dpgLen[mNextReactionIndex];

  for (i = 0; i < l; i++)
    {
      calculateAmu(dpgTable[mtxIdx(mNextReactionIndex, i, mNumReactions)]);
    }

  mA0 = 0.0;

  for (i = 0; i < mNumReactions; i++)
    mA0 += mAmu[i];

  mNextReactionIndex = C_INVALID_INDEX;

  return mNextReactionTime - curTime;
}

C_INT32 CStochDirectMethod::calculateAmu(C_INT32 index)
{
  C_FLOAT64 amu , substrate_factor;
  C_FLOAT64 num_ident, lower_bound, number;
  int j, k, l, flag;

  amu = substrate_factor = 1.0;
  l = steLen[index];

  for (j = flag = 0; j < l; j++)
    {
      k = steTable[mtxIdx(j, index, mNumSpecies)];
      num_ident = steVec[mtxIdx(k, index, mNumSpecies)];

      if (num_ident > 1)
        {
          flag = 1;
          number = species[k];
          lower_bound = number - num_ident;
          substrate_factor = substrate_factor * pow((double) number, (int)(num_ident - 1));  //optimization
          number--;

          while (number > lower_bound)
            {
              amu *= number;
              number--;
            }
        }
    }

  if ((amu == 0) || (substrate_factor == 0))   // at least one substrate particle number is zero
    {
      mAmu[index] = 0;
      return 0;
    }

  // rate_factor is the rate function divided by substrate_factor.
  // It would be more efficient if this was generated directly, since in effect we
  // are multiplying and then dividing by the same thing (substrate_factor)!
  //C_FLOAT64 rate_factor = mpModel->getReactions()[index]->calculateParticleFlux();
  if (flag)
    {
      amu *= *rcRt[index] / substrate_factor;
      mAmu[index] = amu;
    }
  else
    {
      mAmu[index] = *rcRt[index];
    }

  return 0;
}
