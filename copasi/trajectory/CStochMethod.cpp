#include "copasi.h"

#include <math.h>
#include <vector>
#include <numeric>
#include <limits.h>
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

#ifdef WIN32
#define min _cpp_min
#define max _cpp_max
#endif // WIN32

C_INT32 CStochMethod::checkModel(CModel * C_UNUSED(pmodel))
{
  // Here several checks will be performed to validate the model
  return 2; // suggest next reaction method

  // TODO check if stoich is integer
}

CStochMethod *
CStochMethod::createStochMethod(CTrajectoryProblem * pProblem)
{
  C_INT32 result = 1; // direct method as default
  if (pProblem && pProblem->getModel())
    {
      checkModel(pProblem->getModel());
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

CStochMethod::CStochMethod():
    CTrajectoryMethod()
{
  setName("STOCH");
  mTypeEnum = CTrajectoryMethod::stochastic;
  setType(CTrajectoryMethod::TypeName[mTypeEnum]);

  add("STOCH.MaxSteps", 1000000); // Max number of doSingleStep() per step()
  add("STOCH.Subtype", 1); // 0: default; 1: direct method; 2: next reaction method

  mRandomGenerator = CRandom::createGenerator(CRandom::r250);
}

CStochMethod::~CStochMethod()
{
  delete mRandomGenerator;
  mRandomGenerator = 0;
}

const double CStochMethod::step(const double & deltaT)
{
  // write the current state to the model:
  //mpProblem->getModel()->setState(mpCurrentState); //?

  // check for possible overflows:
  unsigned C_INT32 i;
  unsigned C_INT32 imax;

  for (i = 0, imax = mpProblem->getModel()->getIntMetab(); i < imax; i++)
    if (mpProblem->getModel()->getMetabolites()[i]->getNumberDbl() >= mMaxIntBeforeStep)
      {
        // throw exception or something like that
      }

  // do several steps:
  C_FLOAT64 time = mpCurrentState->getTime();
  C_FLOAT64 endtime = time + deltaT;

  for (i = 0; ((i < (unsigned C_INT32) mMaxSteps) && (time < endtime)); i++)
    {
      time = doSingleStep(time, endtime);
    }
  mpCurrentState->setTime(time);

  // get back the particle numbers:

  /* Set the variable Metabolites */
  C_FLOAT64 * Dbl = const_cast<C_FLOAT64 *>(mpCurrentState->getVariableNumberVectorDbl().array());
  for (i = 0, imax = mpProblem->getModel()->getIntMetab(); i < imax; i++, Dbl++)
    *Dbl = mpProblem->getModel()->getMetabolites()[i]->getNumberDbl();

#ifndef  COPASI_DEPRECATED
  C_INT32 * Int = const_cast<C_INT32 *>(mpCurrentState->getVariableNumberVectorInt().array());
  for (i = 0, imax = mpProblem->getModel()->getIntMetab(); i < imax; i++, Int++)
    *Int = mpProblem->getModel()->getMetabolites()[i]->getNumberInt();
#endif //  COPASI_DEPRECATED

  return deltaT;
}

const double CStochMethod::step(const double & deltaT,
                                const CState * initialState)
{
  /* get configuration data */
  mMaxSteps = (C_INT32) getValue("STOCH.MaxSteps");

  *mpCurrentState = *initialState;

  unsigned C_INT32 i, imax;

  mNumNumbers = mpCurrentState->getVariableNumberSize();
  mNumbers.resize(mNumNumbers);
  for (i = 0; i < mNumNumbers; ++i) mNumbers[i] = (C_INT32)mpCurrentState->getVariableNumberDbl(i);
  //TODO also put fixes variables here

  for (i = 0; i < mNumNumbers; ++i)
    mpCurrentState->setVariableNumber(i, floor(mpCurrentState->getVariableNumberDbl(i)));

  imax = mpCurrentState->getFixedNumberSize();
  for (i = 0; i < imax; ++i)
    mpCurrentState->setFixedNumber(i, floor(mpCurrentState->getFixedNumberDbl(i)));

  mpModel = mpProblem->getModel();
  mpProblem->getModel()->setState(mpCurrentState);

  mNumReactions = mpModel->getReactions().size();

  mAmu.clear(); mAmuOld.clear();
  for (i = 0; i < mNumReactions; i++)
    {
      mAmu.push_back(0);
      mAmuOld.push_back(0);
    }

  setupDependencyGraphAndBalances();
  std::cout << mDG;
  updatePropensities();

  // call init of the specific simulation method
  initMethod(mpCurrentState->getTime());

  return step(deltaT);
}

C_INT32 CStochMethod::updatePropensities()
{
  mA0Old = mA0;
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
  // We need the product of the cmu and hmu for this step.
  // We calculate this in one go, as there are fewer steps to
  // perform and we eliminate some possible rounding errors.
  C_FLOAT32 amu = 1; // initially
  //C_INT32 total_substrates = 0;
  C_INT32 num_ident = 0;
  C_INT32 number = 0;
  C_INT32 lower_bound;
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

  // We assume that all substrates are in the same compartment.
  // If there are no substrates, then volume is irrelevant. Otherwise,
  // we can use the volume of the compartment for the first substrate.
  //if (substrates.size() > 0) //check again!!
  /*if (total_substrates > 1) //check again!!
    {
      C_FLOAT64 invvolumefactor =
        pow((double)
            (substrates[0]->getMetabolite().getCompartment()->getVolumeInv()
             * substrates[0]->getMetabolite().getModel()->getNumber2QuantityFactor()),
            (int) total_substrates - 1);
      amu *= invvolumefactor;
      substrate_factor *= invvolumefactor;
    }*/

  // rate_factor is the rate function divided by substrate_factor.
  // It would be more efficient if this was generated directly, since in effect we
  // are multiplying and then dividing by the same thing (substrate_factor)!
  mpModel->getReactions()[index]->calculate();

  if (flag)
    {
      C_FLOAT64 rate_factor = mpModel->getReactions()[index]->getScaledFlux() / substrate_factor;
      //cout << "Rate factor = " << rate_factor << endl;
      amu *= rate_factor;
      mAmu[index] = amu;
    }
  else
  {mAmu[index] = mpModel->getReactions()[index]->getScaledFlux();}

  //std::cout << "Index = " << index << "  Amu = " << amu << std::endl;
  return 0;

  // a more efficient way to calculate mass action kinetics could be included
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
  for (bi = bals.begin(); bi != bals.end(); bi++)
    {
      mNumbers[bi->mIndex] = mNumbers[bi->mIndex] + bi->mMultiplicity;
      mpModel->getMetabolites()[bi->mIndex]->setNumberDbl(mNumbers[bi->mIndex]);
    }

  const std::set<C_INT32> & dep_nodes = mDG.getDependents(rxn);

  std::set<C_INT32>::const_iterator it;
  unsigned int ii;
  for (it = dep_nodes.begin(); it != dep_nodes.end(); it++)
    {
      ii = *it;
      mAmuOld[ii] = mAmu[ii];
      calculateAmu(ii);
    }

  mA0Old = mA0;

  mA0 = 0;
  mA0 = std::accumulate(mAmu.begin(), mAmu.end(), mA0);

  return 0;
}

C_INT32 CStochMethod::generateReactionIndex()
{
  C_FLOAT64 rand1 = mRandomGenerator->getRandomCC() * mA0;
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
  C_FLOAT32 rand2 = mRandomGenerator->getRandomOO();
  return - 1 * log(rand2) / mA0;
}

C_FLOAT64 CStochMethod::generateReactionTime(C_INT32 reaction_index)
{
  C_FLOAT32 rand2 = mRandomGenerator->getRandomOO();
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
          //bb.mIndex = mpModel->getMetabolites().getIndex((*bbb)[j]->getMetabolite().getName());
          //bb.mIndex = mpModel->findMetabByKey((*bbb)[j]->getMetaboliteKey());
          bb.mIndex = mpModel->getMetabolites().getIndex(&(*bbb)[j]->getMetabolite());
          bb.mMultiplicity = static_cast<C_INT32>(floor((*bbb)[j]->getMultiplicity() + 0.5));

          if (((*bbb)[j]->getMetabolite().getStatus()) != CMetab::METAB_FIXED)
            {
              if (bb.mMultiplicity > maxBalance) maxBalance = bb.mMultiplicity;
              mLocalBalances[i].push_back(bb);
              //std::cout << bb.mMetabAddr->getName() << "  ";
            }
        }

      bbb = &mpModel->getReactions()[i]->getChemEq().getSubstrates();
      //std::cout << std::endl << i << " : ";
      for (j = 0; j < bbb->size(); j++)
        {
          //bb.mIndex = mpModel->getMetabolites().getIndex((*bbb)[j]->getMetabolite().getName());
          //bb.mIndex = mpModel->findMetabByKey((*bbb)[j]->getMetaboliteKey());
          bb.mIndex = mpModel->getMetabolites().getIndex(&(*bbb)[j]->getMetabolite());
          bb.mMultiplicity = static_cast<C_INT32>(floor((*bbb)[j]->getMultiplicity() + 0.5));

          if (1)
            {
              mLocalSubstrates[i].push_back(bb);
              //std::cout << bb.mMetabAddr->getName() << "  ";
            }
        }
    }
  mMaxBalance = maxBalance; std::cout << "maxbalance" << mMaxBalance << std::endl;
  //mMaxIntBeforeStep= numeric_limits<C_INT32>::max() - mMaxSteps*mMaxBalance;
  mMaxIntBeforeStep = INT_MAX - 1 - mMaxSteps * mMaxBalance;

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

  std::vector <const CMetab*> metablist;
  std::cout << reaction_index << " depends on ";

  for (i = 0; i < imax; ++i)
    {
      if (mpModel->getReactions()[reaction_index]->getFunctionParameters()[i]->getUsage() == "PARAMETER")
        continue;
      metablist = mpModel->getReactions()[reaction_index]->getParameterMappingMetab(i);
      jmax = metablist.size();
      for (j = 0; j < jmax; ++j)
        {
          retset->insert(metablist[j]->getKey());
          std::cout << "  " << metablist[j]->getName() << ":" << metablist[j]->getKey();
        }
    }
  std::cout << std::endl;
  return retset;
}

std::set<std::string> *CStochMethod::getAffects(C_INT32 reaction_index)
{
  std::set<std::string> *retset = new std::set<std::string>;

  // Get the balances  associated with the reaction at this index
  // XXX We first get the chemical equation, then the balances, since the getBalances method in CReaction is unimplemented!
  const CCopasiVector<CChemEqElement> & balances = mpModel->getReactions()[reaction_index]->getChemEq().getBalances();

  std::cout << reaction_index << " affects ";

  for (unsigned C_INT32 i = 0; i < balances.size(); i++)
    {
      if (fabs(balances[i]->getMultiplicity()) >= 0.1)
        if (balances[i]->getMetabolite().getStatus() != CMetab::METAB_FIXED)
          {
            retset->insert(balances[i]->getMetabolite().getKey());
            std::cout << " " << balances[i]->getMetabolite().getName() << ":" << balances[i]->getMetabolite().getKey();
          }
    }

  std::cout << std::endl;
  return retset;
}
