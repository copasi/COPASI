#include "copasi.h"

#include <math.h>
#include <vector>
#include <set>

#include "utilities/utilities.h"
#include "function/function.h"
#include "CStochSolver.h"
#include "CTrajectory.h"

CStochSolver::CStochSolver()
    : mMethodType(CTrajectory::STOCH_DIRECT),
    mMethod(0)
{}

CStochSolver::CStochSolver(C_INT32 method_type)
    : mMethodType(method_type),
    mMethod(0)
{}

void CStochSolver::initialize(CModel *model)
{
  if (mMethodType == CTrajectory::STOCH_NEXTREACTION)
    {
      //        mMethod = new CStochNextReactionMethod(model);
    }
  else
    {
      mMethod = new CStochDirectMethod(model);
    }

  mMethod->initMethod();
  cout << "Done initializing stochastic method\n";
}
CStochSolver::~CStochSolver() {cleanup(); }

void CStochSolver::cleanup()
{
  if (mMethod)
    {
      mMethod->cleanup();
      delete mMethod;
    }

  mMethod = NULL;
}

CStochMethod *CStochSolver::getStochMethod()
{
  return mMethod;
}

CStochMethod::CStochMethod()
    : mModel(NULL),
    mFail(0)
{
  mRandomGenerator = new CRandom();
}

CStochMethod::CStochMethod(CModel *model)
    : mModel(model),
    mFail(0)
{
  mRandomGenerator = new CRandom();
}
CStochMethod::~CStochMethod() {cleanup(); }

void CStochMethod::cleanup()
{
  delete mRandomGenerator;
  mRandomGenerator = 0;
}

C_INT32 CStochMethod::updatePropensities()
{
  mA0 = 0;

  for (unsigned C_INT32 i = 0; i < mModel->getReactions().size(); i++)
    {
      calculateAmu(i);
      mA0 += mAmu[i];
    }

  return 0;
}

C_INT32 CStochMethod::calculateAmu(C_INT32 index)
{
  // We need the product of the cmu and hmu for this step.
  // We calculate this in one go, as there are fewer steps to
  // perform and we eliminate some possible rounding errors.
  C_FLOAT32 amu = 1; // initially
  C_INT32 total_substrates = 0;
  C_INT32 num_ident = 0;
  C_INT32 number = 0;
  C_INT32 lower_bound;
  // substrate_factor - The substrates, raised to their multiplicities,
  // multiplied with one another. If there are, e.g. m substrates of type m,
  // and n of type N, then substrate_factor = M^m * N^n.
  C_FLOAT64 substrate_factor = 1;
  // First, find the reaction associated with this index.
  // Keep a pointer to this.
  CChemEq *chemeq = &mModel->getReactions()[index]->getChemEq();
  // Iterate through each substrate in the reaction
  CCopasiVector < CChemEqElement > & substrates =
    const_cast < CCopasiVector < CChemEqElement > & > (chemeq->getSubstrates());

  for (unsigned C_INT32 i = 0; i < substrates.size(); i++)
    {
      num_ident = static_cast<C_INT32>(substrates[i]->getMultiplicity());
      cout << "Num ident = " << num_ident << endl;
      total_substrates += num_ident;
      number = static_cast<C_INT32> (substrates[i]->getMetabolite().getNumber());
      lower_bound = number - num_ident;
      cout << "Number = " << number << "  Lower bound = " << lower_bound << endl;
      substrate_factor = substrate_factor * pow(number, num_ident);
      cout << "Substrate factor = " << substrate_factor << endl;

      while (number > lower_bound)
        {
          amu *= number;
          number--;
        }
    }

  // We assume that all substrates are in the same compartment.
  // If there are no substrates, then volume is irrelevant. Otherwise,
  // we can use the volume of the compartment for the first substrate.
  if (substrates.size() > 0)
    {
      C_FLOAT64 volume =
        substrates[0]->getMetabolite().getCompartment()->getVolume();
      amu = amu / pow(volume, total_substrates - 1);
    }

  // rate_factor is the rate function divided by substrate_factor.
  // It would be more efficient if this was generated directly, since in effect we
  // are multiplying and then dividing by the same thing (substrate_factor)!
  C_FLOAT64 rate_factor = mModel->getReactions()[index]->calculate() / substrate_factor;

  cout << "Rate factor = " << rate_factor << endl;

  amu *= rate_factor;

  mAmu[index] = amu;

  cout << "Index = " << index << "  Amu = " << amu << endl;

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
  CCopasiVector <CChemEqElement> & balances =
    const_cast < CCopasiVector <CChemEqElement> & >
    (mModel->getReactions()[rxn]->getChemEq().getBalances());
  CChemEqElement *bal = 0;
  C_FLOAT32 new_num;

  for (unsigned C_INT32 i = 0; i < balances.size(); i++)
    {
      bal = balances[i];
      new_num = bal->getMetabolite().getNumber() + bal->getMultiplicity();
      bal->getMetabolite().setNumber(new_num);
    }

  // Update the model to take into account the new particle numbers
  mModel->setConcentrations(mModel->getNumbers());

  return 0;
}

C_INT32 CStochMethod::generateReactionIndex()
{
  C_FLOAT64 rand1 = mRandomGenerator->getUniformRandom();
  C_FLOAT64 sum = 0;
  unsigned C_INT32 index = 0;

  while (index < mModel->getReactions().size())
    {
      sum += mAmu[index] / mA0;

      if (rand1 <= sum)
        {
          return index;
        }

      index++;
    }

  // shouldn't get here
  return mFail;
}

C_FLOAT64 CStochMethod::generateReactionTime()
{
  C_FLOAT32 rand2 = mRandomGenerator->getUniformRandom();
  return -1 * log(rand2 / mA0);
}

CStochDirectMethod::CStochDirectMethod()
    : CStochMethod()
{}

CStochDirectMethod::CStochDirectMethod(CModel *model)
    : CStochMethod(model)
{}
CStochDirectMethod::~CStochDirectMethod() {cleanup(); }

C_INT32 CStochDirectMethod::initMethod()
{
  // Populate the vector of propensities

  for (unsigned C_INT32 i = 0; i < mModel->getReactions().size(); i++)
    {
      mAmu.push_back(0);
    }

  return 0;
}

C_FLOAT64 CStochDirectMethod::doStep(C_FLOAT64 initial_time)
{
  updatePropensities();
  C_INT32 rxn = generateReactionIndex();
  C_FLOAT64 step_time = generateReactionTime();
  updateSystemState(rxn);
  return initial_time + step_time;
}

CStochNextReactionMethod::CStochNextReactionMethod(CModel *model)
    : CStochMethod(model)
{}
CStochNextReactionMethod::~CStochNextReactionMethod() {cleanup(); }

C_INT32 CStochNextReactionMethod::initMethod(C_FLOAT64 start_time)
{
  // Populate the vector of propensities

  for (unsigned C_INT32 i = 0; i < mModel->getReactions().size(); i++)
    {
      mAmu.push_back(0);
    }

  setupDependencyGraph();
  updatePropensities();
  setupPriorityQueue(start_time);
  return 0;
}

C_FLOAT64 CStochNextReactionMethod::doStep()
{
  C_FLOAT64 time = mPQ.topKey();
  C_INT32 reaction_index = mPQ.topIndex();
  updateSystemState(reaction_index);
  updatePriorityQueue(reaction_index, time);
  return time;
}

void CStochNextReactionMethod::setupDependencyGraph()
{
  vector< set<CMetab>* > DependsOn;
  vector< set<CMetab>* > Affects;
  //    set<CMetab> *tmpdepends = 0;
  //    set<CMetab> *tmpaffects = 0;
  C_INT32 num_reactions = mModel->getReactions().size();
  C_INT32 i, j;
  // Do for each reaction:

  for (i = 0; i < num_reactions; i++)
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
  for (i = 0; i < num_reactions; i++)
    {
      for (j = 0; j < num_reactions; j++)
        {
          // Determine whether the intersection of these two sets is non-empty
          // Could also do this with set_intersection generic algorithm, but that
          // would require operator<() to be defined on the set elements.

          set
            <CMetab>::iterator iter = Affects[i]->begin();

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
      mDG.addDependent(i, i);
    }

  // Delete the memory allocated in getDependsOn() and getAffects()
  // since this is allocated in other functions.
  for (i = 0; i < num_reactions; i++)
    {
      delete DependsOn[i];
      delete Affects[i];
    }
}

void CStochNextReactionMethod::setupPriorityQueue(C_FLOAT64 start_time)
{
  C_INT32 rxn;
  C_FLOAT64 time;

  for (unsigned C_INT32 i = 0; i < mModel->getReactions().size(); i++)
    {
      rxn = generateReactionIndex();
      time = start_time + generateReactionTime();
      mPQ.pushPair(rxn, time);
    }

  mPQ.buildHeap();
}

void CStochNextReactionMethod::updatePriorityQueue(C_INT32 reaction_index, C_FLOAT64 time)
{
  vector<C_INT32> dep_nodes = mDG.getDependents(reaction_index);

  for (unsigned int i = 0; i < dep_nodes.size(); i++)
    {
      C_FLOAT64 new_time = time + generateReactionTime();
      mPQ.updateNode(dep_nodes[i], new_time);
    }
}

set
  <CMetab> *CStochNextReactionMethod::getDependsOn(C_INT32 reaction_index)
  {
    set
      <CMetab> *retset = new set
                           <CMetab>;

    //#if 0    // New way of doing this; supercedes bit #if'ed out
    // Get chemical equation balances
    CCopasiVector<CChemEqElement> balances = mModel->getReactions()[reaction_index]->getChemEq().getBalances();

    for (unsigned C_INT32 i = 0; i < balances.size(); i++)
      {
        retset->insert(balances[i]->getMetabolite());
      }

    //#endif // 0
#if 0
    // Get the reaction associated with this index
    CReaction *react = mModel->getReactions()[reaction_index];

    // Get the kinetic function associated with the reaction_index'th reaction in the model.
    CKinFunction *pfunction = dynamic_cast<CKinFunction*>(&react->getFunction());

    if (!pfunction)
      {
        // the dynamic cast didn't work
        CCopasiMessage(CCopasiMessage::ERROR, "Dynamic cast of CFunction to CKinFunction failed");
        return 0;
      }

    // Get the vector of nodes associated with this function
    CCopasiVectorS<CNodeK> node_vec = pfunction->getNodes();

    CNodeK *tmpnode;

    char subtype;

    CMetab *pmetab = 0;

    // Step through the nodes. If the node is an identifier and corresponds
    // to a substrate or modifier, then add it to the set.

    for (unsigned C_INT32 i = 0; i < node_vec.size(); i++)
      {
        pmetab = 0;
        tmpnode = node_vec[i];

        if ((tmpnode->getType() == N_IDENTIFIER) &&
            (((subtype = tmpnode->getSubtype()) == N_SUBSTRATE) ||
             (subtype == N_MODIFIER)))
          {
            // Get the identifier as known to the node.
            string id_name = tmpnode->getName();
            // Now try to find this, first amongst the substrates, then the products

            if ((pmetab = react->findSubstrate(id_name)) == 0)
              {
                pmetab = react->findModifier(id_name);
              }

            if (pmetab == 0)
              {
                // Uh oh, we haven't found a metabolite corresponding to this node.
                CCopasiMessage(CCopasiMessage::ERROR, "Couldn't find a substrate or modifier named %s", id_name.c_str());
              }

            // we found it
            retset->insert(*pmetab);
          }
      }

#endif // 0
    return retset;
  }

set
  <CMetab> *CStochNextReactionMethod::getAffects(C_INT32 reaction_index)
  {
    set
      <CMetab> *retset = new set
                           <CMetab>;

    // Get the balances  associated with the reaction at this index
    // XXX We first get the chemical equation, then the balances, since the getBalances method in CReaction is unimplemented!
    CCopasiVector<CChemEqElement> balances = mModel->getReactions()[reaction_index]->getChemEq().getBalances();

    for (unsigned C_INT32 i = 0; i < balances.size(); i++)
      {
        if (balances[i]->getMultiplicity() != 0)
          {
            retset->insert(balances[i]->getMetabolite());
          }
      }

    return retset;
  }
