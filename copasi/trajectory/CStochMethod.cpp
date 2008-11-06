// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CStochMethod.cpp,v $
//   $Revision: 1.68.8.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/11/06 08:12:23 $
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

#include "copasi.h"
#include "CStochMethod.h"
#include "CStochDirectMethod.h"
#include "CStochNextReactionMethod.h"
#include "utilities/CCopasiVector.h"
#include "function/CFunction.h"
#include "randomGenerator/CRandom.h"
#include "CTrajectoryMethod.h"
#include "CTrajectoryProblem.h"
#include "model/CState.h"
#include "model/CCompartment.h"
#include "model/CModel.h"

C_INT32 CStochMethod::checkModel(CModel * C_UNUSED(pmodel))
{
  // Here several checks will be performed to validate the model
  return 2; // suggest next reaction method
}

CStochMethod *
CStochMethod::createStochMethod(CTrajectoryProblem * pProblem)
{
  C_INT32 result = 2; // next reaction method as default
  if (pProblem && pProblem->getModel())
    {
      result = checkModel(pProblem->getModel());
    }

  CStochMethod * method = NULL;

  if (result < 0)
    {
      //error. stochastic simulation not possible
    }
  else if (result == 1)
    {
      method = new CStochDirectMethod();
    }
  else if (result == 2)
    {
      method = new CStochNextReactionMethod();
    }
  else
    {
      //should not happen
    }

  return method;
}

CStochMethod::CStochMethod(const CCopasiContainer * pParent):
    CTrajectoryMethod(CCopasiMethod::stochastic, pParent)
{
  initializeParameter();
  mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
}

CStochMethod::CStochMethod(const CStochMethod & src,
                           const CCopasiContainer * pParent):
    CTrajectoryMethod(src, pParent)
{
  initializeParameter();
  mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
}

CStochMethod::~CStochMethod()
{
  delete mpRandomGenerator;
  mpRandomGenerator = NULL;
}

void CStochMethod::initializeParameter()
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

bool CStochMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

void CStochMethod::step(const double & deltaT)
{
  // write the current state to the model:
  //mpProblem->getModel()->setState(mpCurrentState); //?

  // check for possible overflows:
  unsigned C_INT32 i;
  unsigned C_INT32 imax;

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
  C_FLOAT64 time = mpCurrentState->getTime();
  C_FLOAT64 endtime = time + deltaT;

  for (i = 0; ((i < (unsigned C_INT32) mMaxSteps) && (time < endtime)); i++)
    {
      time = doSingleStep(time, endtime);
    }
  mpCurrentState->setTime(time);

  if ((i >= (unsigned C_INT32) mMaxSteps) && (!mMaxStepsReached))
    {
      mMaxStepsReached = true; //only report this message once
      CCopasiMessage(CCopasiMessage::WARNING, "maximum number of reaction events was reached in at least one simulation step.\nThat means time intervals in the output may not be what you requested.");
    }

  // get back the particle numbers:

  /* Set the variable Metabolites */
  C_FLOAT64 * Dbl = mpCurrentState->beginIndependent();
  for (i = 0, imax = mpProblem->getModel()->getNumVariableMetabs(); i < imax; i++, Dbl++)
    *Dbl = mpProblem->getModel()->getMetabolitesX()[i]->getValue();

  return;
}

void CStochMethod::start(const CState * initialState)
{
  /* get configuration data */
  mMaxSteps = * getValue("Max Internal Steps").pINT;

  bool useRandomSeed = * getValue("Use Random Seed").pBOOL;
  unsigned C_INT32 randomSeed = * getValue("Random Seed").pUINT;
  if (useRandomSeed) mpRandomGenerator->initialize(randomSeed);

  *mpCurrentState = *initialState; //TODO seem to be identical

  mpModel = mpProblem->getModel();
  assert(mpModel);

  if (mpModel->getModelType() == CModel::deterministic)
    mDoCorrection = true;
  else
    mDoCorrection = false;

  mHasAssignments = modelHasAssignments(mpModel);

  unsigned C_INT32 i, imax;

  //fix variable particel numbers to be integer
  mNumNumbers = mpCurrentState->getNumVariable();
  mNumbers.resize(mNumNumbers);
  C_FLOAT64 * Dbl = mpCurrentState->beginIndependent();
  CModelEntity*const* obj = mpModel->getStateTemplate().beginIndependent();
  for (i = 0; i < mNumNumbers; ++i, Dbl++, ++obj)
    {
      mNumbers[i] = (C_INT64) * Dbl;
      *Dbl = floor(*Dbl);
      //std::cout << (*obj)->getObjectName() << std::endl;
      //obj can later be used to handle variables differently
    }

  //make sure fixed particle numbers are integer
  imax = mpCurrentState->getNumFixed();
  for (i = 0; i < imax; ++i, Dbl++, ++obj)
    {
      //std::cout << (*obj)->getObjectName() << std::endl;
      if (dynamic_cast<const CMetab*>(*obj))
        *Dbl = floor(*Dbl);
    }

  //update model to integer particle numbers and calculate initial propensities
  mpModel->setState(*mpCurrentState);

  mpModel->updateSimulatedValues(false); //for assignments
  //mpModel->updateNonSimulatedValues(); //for assignments

  mNumReactions = mpModel->getReactions().size();

  mAmu.clear(); mAmuOld.clear();
  for (i = 0; i < mNumReactions; i++)
    {
      mAmu.push_back(0);
      mAmuOld.push_back(0);
    }

  setupDependencyGraphAndBalances();
  //std::cout << mDG;
  updatePropensities();

  //debug
  //for (i=0; i<mAmu.size(); ++i) std::cout << mAmu[i] << " ";
  //std::cout << std::endl;

  // call init of the specific simulation method
  initMethod(mpCurrentState->getTime());

  mMaxStepsReached = false;
  return;
}

C_INT32 CStochMethod::updatePropensities()
{
  //mA0Old = mA0;
  mA0 = 0;
  //std::cout << "        updatePropensities: ";

  for (unsigned C_INT32 i = 0; i < mNumReactions; i++)
    {
      mAmuOld[i] = mAmu[i];
      calculateAmu(i);
      //std::cout << mAmu[i] << " ";
      mA0 += mAmu[i];
    }

  //std::cout << std::endl;
  return 0;
}

C_INT32 CStochMethod::calculateAmu(C_INT32 index)
{
  if (!mDoCorrection)
    {
      mAmu[index] = mpModel->getReactions()[index]->calculateParticleFlux();
      return 0;
    }

  // We need the product of the cmu and hmu for this step.
  // We calculate this in one go, as there are fewer steps to
  // perform and we eliminate some possible rounding errors.
  C_FLOAT64 amu = 1; // initially
  //C_INT32 total_substrates = 0;
  C_INT32 num_ident = 0;
  C_INT64 number = 0;
  C_INT64 lower_bound;
  // substrate_factor - The substrates, raised to their multiplicities,
  // multiplied with one another. If there are, e.g. m substrates of type m,
  // and n of type N, then substrate_factor = M^m * N^n.
  C_FLOAT64 substrate_factor = 1;
  // First, find the reaction associated with this index.
  // Keep a pointer to this.
  // Iterate through each substrate in the reaction
  const std::vector<CStochBalance> & substrates = mLocalSubstrates[index];

  int flag = 0;

  for (unsigned C_INT32 i = 0; i < substrates.size(); i++)
    {
      num_ident = substrates[i].mMultiplicity;
      //std::cout << "Num ident = " << num_ident << std::endl;
      //total_substrates += num_ident;

      if (num_ident > 1)
        {
          flag = 1;
          number = mNumbers[substrates[i].mIndex];
          lower_bound = number - num_ident;
          //std::cout << "Number = " << number << "  Lower bound = " << lower_bound << std::endl;
          substrate_factor = substrate_factor * pow((double) number, (int) (num_ident - 1)); //optimization
          //std::cout << "Substrate factor = " << substrate_factor << std::endl;

          number--; //optimization
          while (number > lower_bound)
            {
              amu *= number;
              number--;
            }
        }
    }

  if ((amu == 0) || (substrate_factor == 0))  // at least one substrate particle number is zero
    {
      mAmu[index] = 0;
      return 0;
    }

  // rate_factor is the rate function divided by substrate_factor.
  // It would be more efficient if this was generated directly, since in effect we
  // are multiplying and then dividing by the same thing (substrate_factor)!
  C_FLOAT64 rate_factor = mpModel->getReactions()[index]->calculateParticleFlux();

  if (flag)
    {
      //cout << "Rate factor = " << rate_factor << endl;
      amu *= rate_factor / substrate_factor;
      mAmu[index] = amu;
    }
  else
    {
      mAmu[index] = rate_factor;
    }

  //debug
  /*  if (mAmu[index]<0)
      {
        std::cout << "negative amu" << std::endl;
      }*/
  // a more efficient way to calculate mass action kinetics could be included

  //std::cout << "Index = " << index << "  Amu = " << amu << std::endl;
  return 0;
}

C_INT32 CStochMethod::updateSystemState(C_INT32 rxn)
{
  // Change the particle numbers according to which step took place.
  // First, get the vector of balances in the reaction we've got.
  // (This vector expresses the number change of each metabolite
  // in the reaction.) Then step through each balance, using its
  // multiplicity to calculate a new value for the associated
  // metabolite. Finally, update the metabolite.

  const std::vector<CStochBalance> & bals = mLocalBalances[rxn];

  std::vector<CStochBalance>::const_iterator bi;
  CMetab* pTmpMetab;
  for (bi = bals.begin(); bi != bals.end(); bi++)
    {
      mNumbers[bi->mIndex] = mNumbers[bi->mIndex] + bi->mMultiplicity;
      pTmpMetab = mpModel->getMetabolitesX()[bi->mIndex];
      pTmpMetab->setValue(mNumbers[bi->mIndex]);
      pTmpMetab->refreshConcentration();

      //debug
      //if (mNumbers[bi->mIndex]<0)
      //  std::cout << "number negative" << std::endl;
    }

  if (mHasAssignments)
    {
      // this is less efficient but can deal with assignments.
      //TODO: handle dependencies for assignments also.
      mpModel->updateSimulatedValues(false);
      updatePropensities();
    }
  else
    {
      const std::set<unsigned C_INT32> & dep_nodes = mDG.getDependents(rxn);

      std::set<unsigned C_INT32>::const_iterator it;
      unsigned int ii;
      for (it = dep_nodes.begin(); it != dep_nodes.end(); it++)
        {
          ii = *it;
          mAmuOld[ii] = mAmu[ii];
          calculateAmu(ii);
        }

      //mA0Old = mA0;

      mA0 = 0;
      mA0 = std::accumulate(mAmu.begin(), mAmu.end(), mA0);
    }

  return 0;
}

C_INT32 CStochMethod::generateReactionIndex()
{
  C_FLOAT64 rand1 = mpRandomGenerator->getRandomOO() * mA0;
  C_FLOAT64 sum = 0;
  unsigned C_INT32 index = 0;

  while (index < (mpModel->getReactions().size() - 1))
    {
      sum += mAmu[index] /* /mA0 */;
      if (rand1 <= sum)
      {return index;}
      index++;
    }

  return index;
}

C_FLOAT64 CStochMethod::generateReactionTime()
{
  if (mA0 == 0) return 2.0 * DBL_MAX;
  C_FLOAT64 rand2 = mpRandomGenerator->getRandomOO();
  return - 1 * log(rand2) / mA0;
}

C_FLOAT64 CStochMethod::generateReactionTime(C_INT32 reaction_index)
{
  if (mAmu[reaction_index] == 0) return 2.0 * DBL_MAX;
  C_FLOAT64 rand2 = mpRandomGenerator->getRandomOO();
  return - 1 * log(rand2) / mAmu[reaction_index];
}

void CStochMethod::setupDependencyGraphAndBalances()
{
  mDG.clear();
  std::vector< std::set<std::string>* > DependsOn;
  std::vector< std::set<std::string>* > Affects;
  unsigned C_INT32 i, j;
  // Do for each reaction:

  for (i = 0; i < mNumReactions; i++)
    {
      // Get the set of metabolites  which affect the value of amu for this
      // reaction i.e. the set on which amu depends. This may be  more than
      // the set of substrates, since the kinetics can involve other
      // reactants, e.g. catalysts. We thus need to step through the
      // rate function and pick out every reactant which can vary.
      DependsOn.push_back(getDependsOn(i));
      // Get the set of metabolites which are affected when this reaction takes place
      Affects.push_back(getAffects(i));
    }

  // For each possible pair of reactions i and j, if the intersection of
  // Affects(i) with DependsOn(j) is non-empty, add a dependency edge from i to j.
  mDG.resize(mNumReactions);
  for (i = 0; i < mNumReactions; i++)
    {
      for (j = 0; j < mNumReactions; j++)
        {
          // Determine whether the intersection of these two sets is non-empty
          // Could also do this with set_intersection generic algorithm, but that
          // would require operator<() to be defined on the set elements.

          std::set<std::string>::iterator iter = Affects[i]->begin();

          for (; iter != Affects[i]->end(); iter++)
            {
              if (DependsOn[j]->count(*iter))
                {
                  // The set intersection is non-empty
                  mDG.addDependent(i, j);
                  break;
                }
            }
        }

      // Ensure that self edges are included
      //mDG.addDependent(i, i);
    }

  // Create local copy of balances and substrates list
  CStochBalance bb;
  C_INT32 maxBalance = 0;

  mLocalBalances.clear();
  mLocalBalances.resize(mNumReactions);
  mLocalSubstrates.clear();
  mLocalSubstrates.resize(mNumReactions);

  for (i = 0; i < mNumReactions; i++)
    {
      const CCopasiVector<CChemEqElement> * bbb;

      bbb = &mpModel->getReactions()[i]->getChemEq().getBalances();
      //std::cout << std::endl << i << " : ";
      //TODO clear old local balances and substrates
      for (j = 0; j < bbb->size(); j++)
        {
          //bb.mIndex = mpModel->getMetabolites().getIndex((*bbb)[j]->getMetabolite().getObjectName(());
          //bb.mIndex = mpModel->findMetabByKey((*bbb)[j]->getMetaboliteKey());
          assert((*bbb)[j]->getMetabolite());
          bb.mIndex = mpModel->getMetabolitesX().getIndex((*bbb)[j]->getMetabolite());
          bb.mMultiplicity = static_cast<C_INT32>(floor((*bbb)[j]->getMultiplicity() + 0.5));

          if (((*bbb)[j]->getMetabolite()->getStatus()) != CModelEntity::FIXED)
            {
              if (bb.mMultiplicity > maxBalance) maxBalance = bb.mMultiplicity;
              mLocalBalances[i].push_back(bb);
              //std::cout << bb.mMetabAddr->getObjectName(() << "  ";
            }
        }

      bbb = &mpModel->getReactions()[i]->getChemEq().getSubstrates();
      //std::cout << std::endl << i << " : ";
      for (j = 0; j < bbb->size(); j++)
        {
          //bb.mIndex = mpModel->getMetabolites().getIndex((*bbb)[j]->getMetabolite().getObjectName(());
          //bb.mIndex = mpModel->findMetabByKey((*bbb)[j]->getMetaboliteKey());
          assert((*bbb)[j]->getMetabolite());
          bb.mIndex = mpModel->getMetabolitesX().getIndex((*bbb)[j]->getMetabolite());
          bb.mMultiplicity = static_cast<C_INT32>(floor((*bbb)[j]->getMultiplicity() + 0.5));

          if (1)
            {
              mLocalSubstrates[i].push_back(bb);
              //std::cout << bb.mMetabAddr->getObjectName(() << "  ";
            }
        }
    }
  mMaxBalance = maxBalance;
  //std::cout << "maxbalance" << mMaxBalance << std::endl;
  //mMaxIntBeforeStep= numeric_limits<C_INT32>::max() - mMaxSteps*mMaxBalance;
  mMaxIntBeforeStep =        /*INT_MAX*/ LLONG_MAX - 1 - mMaxSteps * mMaxBalance;

  // Delete the memory allocated in getDependsOn() and getAffects()
  // since this is allocated in other functions.
  for (i = 0; i < mNumReactions; i++)
    {
      delete DependsOn[i];
      delete Affects[i];
    }
}

std::set<std::string> *CStochMethod::getDependsOn(C_INT32 reaction_index)
{
  std::set<std::string> *retset = new std::set<std::string>;

  unsigned C_INT32 i, imax = mpModel->getReactions()[reaction_index]->getFunctionParameters().size();
  unsigned C_INT32 j, jmax;

  //std::vector <const CMetab*> metablist;
  //std::cout << reaction_index << " depends on ";

  for (i = 0; i < imax; ++i)
    {
      if (mpModel->getReactions()[reaction_index]->getFunctionParameters()[i]->getUsage() == CFunctionParameter::PARAMETER)
        continue;
      //metablist = mpModel->getReactions()[reaction_index]->getParameterMappingMetab(i);
      const std::vector <std::string> & metabKeylist =
        mpModel->getReactions()[reaction_index]->getParameterMappings()[i];
      jmax = metabKeylist.size();
      for (j = 0; j < jmax; ++j)
        {
          retset->insert(metabKeylist[j]);
          //std::cout << "  " << metablist[j]->getObjectName() << ":" << metablist[j]->getKey();
        }
    }
  //std::cout << std::endl;
  return retset;
}

std::set<std::string> *CStochMethod::getAffects(C_INT32 reaction_index)
{
  std::set<std::string> *retset = new std::set<std::string>;

  // Get the balances  associated with the reaction at this index
  // XXX We first get the chemical equation, then the balances, since the getBalances method in CReaction is unimplemented!
  const CCopasiVector<CChemEqElement> & balances = mpModel->getReactions()[reaction_index]->getChemEq().getBalances();

  //std::cout << reaction_index << " affects ";

  for (unsigned C_INT32 i = 0; i < balances.size(); i++)
    {
      if (!balances[i]->getMetabolite()) continue;
      if (fabs(balances[i]->getMultiplicity()) >= 0.1)
        if (balances[i]->getMetabolite()->getStatus() != CModelEntity::FIXED)
          {
            retset->insert(balances[i]->getMetabolite()->getKey());
            //std::cout << " " << balances[i]->getMetabolite().getObjectName() << ":" << balances[i]->getMetabolite().getKey();
          }
    }

  //std::cout << std::endl;
  return retset;
}

//virtual
bool CStochMethod::isValidProblem(const CCopasiProblem * pProblem)
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

  //check for rules
  C_INT32 i, imax = pTP->getModel()->getNumModelValues();
  for (i = 0; i < imax; ++i)
    {
      if (pTP->getModel()->getModelValues()[i]->getStatus() == CModelEntity::ODE)
        {
          //ode rule found
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 18);
          return false;
        }
    }
  imax = pTP->getModel()->getNumMetabs();
  for (i = 0; i < imax; ++i)
    {
      if (pTP->getModel()->getMetabolites()[i]->getStatus() == CModelEntity::ODE)
        {
          //ode rule found
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 20);
          return false;
        }
    }
  imax = pTP->getModel()->getCompartments().size();
  for (i = 0; i < imax; ++i)
    {
      if (pTP->getModel()->getCompartments()[i]->getStatus() == CModelEntity::ODE)
        {
          //ode rule found
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 21);
          return false;
        }
    }

  //   if (modelHasAssignments(pTP->getModel()))
  //     {
  //       CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 19);
  //       return false;
  //}
  //  this test is disabled since we have preliminary support for assignments

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

//static
bool CStochMethod::modelHasAssignments(const CModel* pModel)
{
  C_INT32 i, imax = pModel->getNumModelValues();
  for (i = 0; i < imax; ++i)
    {
      if (pModel->getModelValues()[i]->getStatus() == CModelEntity::ASSIGNMENT)
        if (pModel->getModelValues()[i]->isUsed())
          {
            //used assignment found
            return true;
          }
    }

  imax = pModel->getNumMetabs();
  for (i = 0; i < imax; ++i)
    {
      if (pModel->getMetabolites()[i]->getStatus() == CModelEntity::ASSIGNMENT)
        if (pModel->getMetabolites()[i]->isUsed())
          {
            //used assignment found
            return true;
          }
    }

  imax = pModel->getCompartments().size();
  for (i = 0; i < imax; ++i)
    {
      if (pModel->getCompartments()[i]->getStatus() == CModelEntity::ASSIGNMENT)
        if (pModel->getCompartments()[i]->isUsed())
          {
            //used assignment found
            return true;
          }
    }

  return false;
}
