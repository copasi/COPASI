// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// DEBUG_OPT allows doing debug output only on this class and is preferable
// to using COPASI_DEBUG, which would make this output on for any debug version
#undef DEBUG_OPT

#include <limits>
#include <string>
#include <cmath>
#ifdef DEBUG_OPT
# include <iostream>
# include <fstream>
#endif

#include "copasi/copasi.h"
#include "COptMethodSS.h"
#include "COptProblem.h"
#include "copasi/parameterFitting/CFitProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "copasi/randomGenerator/CRandom.h"
#include "copasi/utilities/CProcessReport.h"
#include "copasi/utilities/CSort.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/utilities/CMethodFactory.h"

COptMethodSS::COptMethodSS(const CDataContainer * pParent,
                           const CTaskEnum::Method & methodType,
                           const CTaskEnum::Task & taskType):
  COptPopulationMethod(pParent, methodType, taskType, false),
  mPool(0),
  mPoolVal(0),
  mPoolSize(0),
  mEvaluationValue(std::numeric_limits< C_FLOAT64 >::max()),
  mStopAfterStalledGenerations(0),
  mBestValue(std::numeric_limits< C_FLOAT64 >::max()),
  mBestIndex(C_INVALID_INDEX),
  mpOptProblemLocal(NULL),
  mpLocalMinimizer(NULL)
{
  assertParameter("Number of Iterations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 200);
  assertParameter("Random Number Generator", CCopasiParameter::Type::UINT, (unsigned C_INT32) CRandom::mt19937, eUserInterfaceFlag::editable);
  assertParameter("Seed", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);
  assertParameter("Stop after # Stalled Generations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);

  initObjects();
}

COptMethodSS::COptMethodSS(const COptMethodSS & src,
                           const CDataContainer * pParent):
  COptPopulationMethod(src, pParent),
  mPool(0),
  mPoolVal(0),
  mPoolSize(0),
  mEvaluationValue(std::numeric_limits< C_FLOAT64 >::max()),
  mStopAfterStalledGenerations(0),
  mBestValue(std::numeric_limits< C_FLOAT64 >::max()),
  mBestIndex(C_INVALID_INDEX),
  mpOptProblemLocal(NULL),
  mpLocalMinimizer(NULL)
{
  // remove eventual existing parameters from the release version.
  initObjects();
}

COptMethodSS::~COptMethodSS()
{cleanup();}

// virtual
bool COptMethodSS::elevateChildren()
{
  return true;
}

void COptMethodSS::initObjects()
{
  addObjectReference("Current Iteration", mCurrentGeneration, CDataObject::ValueInt);
}

bool COptMethodSS::initialize()
{
  cleanup();

  size_t i;

  if (!COptPopulationMethod::initialize())
    {
      if (mProcessReport)
        mProcessReport.finishItem(mhGenerations);

      return false;
    }

  // get total number of iterations
  mGenerations = getValue< unsigned C_INT32 >("Number of Iterations");
  // set current iteration to zero
  mCurrentGeneration = 0;

  if (mProcessReport)
    mhGenerations =
      mProcessReport.addItem("Current Iteration",
                             mCurrentGeneration,
                             & mGenerations);

  mCurrentGeneration++;

  mCloseValue = 0.001;

  // frequency of local optimiser; this is hardcoded as 20 per Jose Egea,
  mLocalFreq = 20;

  // calculate the number of individuals in population
  mPopulationSize = (C_INT32) ceil(1.0 + sqrt(1.0 + 40.0 * mVariableSize) / 2.0);

  if (mPopulationSize % 2 != 0) mPopulationSize++;

  CFitProblem * pFitProblem = dynamic_cast< CFitProblem * >(mProblemContext.master());

  if (pFitProblem != NULL)
    {
      // this is a least squares problem (param estimation)
      // let's use our favorite lsq method
      mpLocalMinimizer = static_cast< COptMethod * >(CMethodFactory::create(getType(),
                         CTaskEnum::Method::LevenbergMarquardt,
                         getObjectParent()));

      // the intermediate local minimizations use a rather relaxed tolerance
      mpLocalMinimizer->setValue("Tolerance", (C_FLOAT64) 1.e-003);
      // TODO: not sure if we should let this one go that long...
      mpLocalMinimizer->setValue("Iteration Limit", (C_INT32) 2000);
    }
  else
    {
      // this is a generic optimisation problem
      // let's use Hooke and Jeeves
      mpLocalMinimizer = static_cast< COptMethod * >(CMethodFactory::create(getType(),
                         CTaskEnum::Method::HookeJeeves,
                         getObjectParent()));

      // with a rather relaxed tolerance (1e-3) for intermediate minimizations
      mpLocalMinimizer->setValue("Tolerance", (C_FLOAT64) 1.e-003);
      mpLocalMinimizer->setValue("Iteration Limit", (C_INT32) 50);
      mpLocalMinimizer->setValue("Rho", (C_FLOAT64) 0.2);
    }

  // local minimization problem (starts as a copy of the current problem)
  if (pFitProblem != NULL)
    {
      // this is a least squares problem (param estimation)
      mpOptProblemLocal = new CFitProblem(*pFitProblem, getObjectParent());
    }
  else
    {
      // this is a generic optimisation problem
      mpOptProblemLocal = new COptProblem(*mProblemContext.master(), getObjectParent());
    }

  // the local optimization method should not have a callback
  mpOptProblemLocal->setCallBack(NULL);

  // we also have to initialize the subtask
  mpOptProblemLocal->initializeSubtaskBeforeOutput();
  // initialize it
  mpOptProblemLocal->initialize();
  // no statistics to be calculated in the local problems
  mpOptProblemLocal->setCalculateStatistics(false);
  // do not randomize the initial values
  mpOptProblemLocal->setRandomizeStartValues(false);
  mpLocalMinimizer->setProblem(mpOptProblemLocal);

  // create matrix for the RefSet (population)
  mIndividuals.resize(mPopulationSize);

  for (i = 0; i < (size_t)mPopulationSize; ++i)
    mIndividuals[i] = new CVector< C_FLOAT64 >(mVariableSize);

  // create vector for function values (of RefSet members)
  mValues.resize(mPopulationSize);
  mValues = std::numeric_limits<C_FLOAT64>::infinity();

  // create vector for counting stuck iterations
  mStuck.resize(mPopulationSize);
  mStuck = 0;

  // create matrix for the RefSet children
  mChild.resize(mPopulationSize);

  for (i = 0; i < (size_t)mPopulationSize; ++i)
    mChild[i] = new CVector< C_FLOAT64 >(mVariableSize);

  // create vector for function values (of child members)
  mChildVal.resize(mPopulationSize);
  mChildVal = std::numeric_limits<C_FLOAT64>::infinity();

  // we have not generated any children yet
  mChildrenGenerated = false;

  // create matrix for the pool of diverse solutions
  // this will also be used to store the initial and
  // final positions of local optimizations
  if (10 * mVariableSize > 2 * mGenerations / mLocalFreq)
    {
      mPoolSize = 10 * mVariableSize;
    }
  else
    {
      mPoolSize = 2 * mGenerations / mLocalFreq;
    }

  mPool.resize(mPoolSize);

  for (i = 0; i < mPoolSize; i++)
    mPool[i] = new CVector< C_FLOAT64 >(mVariableSize);

  mPoolVal.resize(mPoolSize);
  mPoolVal = std::numeric_limits<C_FLOAT64>::infinity();

  // best is infinity, so anything will improve it
  mBestValue = std::numeric_limits<C_FLOAT64>::infinity();

  // array for frequencies
  // initialized at 1
  mFreq.resize(mVariableSize);

  for (i = 0; i < mVariableSize; i++)
    {
      mFreq[i] = new CVector< C_INT32 >(4);
      *mFreq[i] = 1;
    }

  // vector for probabilities
  // initialized at 0
  mProb.resize(4);
  mProb = 0.0;

  if (getParameter("Stop after # Stalled Generations"))
    mStopAfterStalledGenerations = getValue <unsigned C_INT32>("Stop after # Stalled Generations");

  return true;
}

bool COptMethodSS::cleanup()
{
  size_t i;

  pdelete(mpOptProblemLocal);

  pdelete(mpLocalMinimizer);

  for (i = 0; i < mChild.size(); i++)
    pdelete(mChild[i]);

  for (i = 0; i < mPool.size(); i++)
    pdelete(mPool[i]);

  for (i = 0; i < mFreq.size(); i++)
    pdelete(mFreq[i]);

  return COptPopulationMethod::cleanup();
}

// Find a local minimum
// solution has initial guess on entry, and solution on exit
// fval has value of objective function on exit
bool COptMethodSS::localmin(CVector< C_FLOAT64 > & solution, C_FLOAT64 & fval)
{
  bool Running = true;
  unsigned C_INT32 i;

  mpOptProblemLocal->reset();

  // first we set up the problem
  // (optmethod and optproblem already setup in initialization)
  // let's get the list of parameters
  std::vector<COptItem *> optitem = mpOptProblemLocal->getOptItemList(true);

  // and set them to the values passed in solution
  for (i = 0; i < mVariableSize; i++)
    {
      optitem[i]->setStartValue(solution[i]);
    }

  // reset the function counter of the local minimizer
  mpOptProblemLocal->resetCounters();

  // run it
  Running &= mpLocalMinimizer->optimise();
  // add the function evaluations taken in local to the global problem
  mProblemContext.master()->incrementCounters(mpOptProblemLocal->getCounters());
  // pass the results on to the calling parameters
  fval = mpOptProblemLocal->getSolutionValue();

  for (i = 0; i < mVariableSize; i++)
    {
      solution[i] = mpOptProblemLocal->getSolutionVariables(true)[i];
    }

  return Running;
}

// evaluate the fitness of one individual
bool COptMethodSS::evaluate(const CVector< C_FLOAT64 > & /* individual */)
{
  bool Running = true;

  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  // evaluate the fitness
  Running &= mProblemContext.master()->calculate();

  // check whether the functional constraints are fulfilled
  if (!mProblemContext.master()->checkFunctionalConstraints())
    mEvaluationValue = std::numeric_limits<C_FLOAT64>::infinity();
  else
    mEvaluationValue = mProblemContext.master()->getCalculateValue();

  return Running;
}

// randomize the values of RefSet[i]
bool COptMethodSS::randomize(C_INT32 i)
{
  C_FLOAT64 mn, mx, la; // for boundaries of rnd
  bool Running = true;  // flag for invalid values

  for (C_INT32 j = 0; j < (C_INT32)mVariableSize; ++j)
    {
      // get pointers to appropriate elements (easier reading of code)
      const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[j];
      C_FLOAT64 & Sol = (*mIndividuals[i])[j];
      // calculate lower and upper bounds for this variable
      mn = *OptItem.getLowerBoundValue();
      mx = *OptItem.getUpperBoundValue();

      try
        {
          // calculate orders of magnitude of the interval
          la = log10(mx) - log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min()));

          // determine if linear or log scale
          if ((mn < 0.0) || (mx <= 0.0))
            Sol = mn + mRandomContext.master()->getRandomCC() * (mx - mn);
          else
            {
              if (la < 1.8)
                Sol = mn + mRandomContext.master()->getRandomCC() * (mx - mn);
              else
                Sol = pow(10.0, log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min()))
                          + la * mRandomContext.master()->getRandomCC());
            }
        }
      catch (...)
        {
          // if there were errors, let's just stay with the midpoint
          Sol = (mx + mn) * 0.5;
        }

      // force it to be within the bounds
      switch (OptItem.checkConstraint(Sol))
        {
          case - 1:
            Sol = *OptItem.getLowerBoundValue();
            break;

          case 1:
            Sol = *OptItem.getUpperBoundValue();
            break;
        }

      // We need to set the value here so that further checks take
      // account of the value.
      *mProblemContext.master()->getContainerVariables(true)[j] = Sol;
    }

  // calculate its fitness
  Running = evaluate(*mIndividuals[i]);
  mValues[i] = mEvaluationValue;
  // reset the stuck flag
  mStuck[i] = 1;
  return Running;
}

// initialise the population using the
// Diversification Generation Method
bool COptMethodSS::creation(void)
{
  C_INT32 i, j, k, l;   // counters
  C_FLOAT64 mn, mx, la; // for boundaries of rnd
  C_FLOAT64 sum;        // to calculate a summation
  C_FLOAT64 a;          // to hold a random number
  bool Running = true;  // flag for invalid values

  // initialize all entries of the Pool.
  // first 4 candidates as a latin hypercube
  for (i = 0; (i < 4) && Running; i++)
    {
      for (j = 0; j < (C_INT32)mVariableSize; ++j)
        {
          // get pointers to appropriate elements (easier reading of code)
          const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[j];
          C_FLOAT64 & Sol = (*mPool[i])[j];
          // calculate lower and upper bounds for this variable
          mn = *OptItem.getLowerBoundValue();
          mx = *OptItem.getUpperBoundValue();

          try
            {
              // calculate orders of magnitude of the interval
              la = log10(mx) - log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min()));

              // determine if linear or log scale
              if ((mn < 0.0) || (mx <= 0.0))
                Sol = mn + (mRandomContext.master()->getRandomCC() + (C_FLOAT64) i) * (mx - mn) * 0.25;
              else
                {
                  if (la < 1.8)
                    Sol = mn + (mRandomContext.master()->getRandomCC() + (C_FLOAT64) i) * (mx - mn) * 0.25;
                  else
                    Sol = pow(10.0, log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min()))
                              + la * 0.25 * (mRandomContext.master()->getRandomCC() + (C_FLOAT64) i));
                }
            }
          catch (...)
            {
              // TODO: this sounds a bit daft in this context, what else could be done, though?
              Sol = (mx + mn) * 0.5;
            }

          // force it to be within the bounds
          switch (OptItem.checkConstraint(Sol))
            {
              case - 1:
                Sol = *OptItem.getLowerBoundValue();
                break;

              case 1:
                Sol = *OptItem.getUpperBoundValue();
                break;
            }

          // We need to set the value here so that further checks take
          // account of the value.
          *mProblemContext.master()->getContainerVariables(true)[j] = Sol;
        }

      // calculate its fitness
      Running &= evaluate(*mPool[i]);
      mPoolVal[i] = mEvaluationValue;
    }

  // next we add the initial guess from the user
  for (j = 0; j < (C_INT32)mVariableSize; ++j)
    {
      const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[j];
      C_FLOAT64 & Sol = (*mPool[i])[j];

      // get the vector of initial value
      Sol = OptItem.getStartValue();

      // force it to be within the bounds
      switch (OptItem.checkConstraint(Sol))
        {
          case - 1:
            Sol = *OptItem.getLowerBoundValue();
            break;

          case 1:
            Sol = *OptItem.getUpperBoundValue();
            break;
        }

      // We need to set the value here so that further checks take
      // account of the value.
      *mProblemContext.master()->getContainerVariables(true)[j] = Sol;
    }

  // calculate its fitness
  Running &= evaluate(*mPool[i]);
  mPoolVal[i] = mEvaluationValue;
  ++i;

  // the remaining entries depend on probabilities
  for (; (i < (C_INT32)mPoolSize) && Running; ++i)
    {
      for (j = 0; j < (C_INT32)mVariableSize; ++j)
        {
          // get pointers to appropriate elements (easier reading of code)
          COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[j];
          C_FLOAT64 & Sol = (*mPool[i])[j];
          // calculate lower and upper bounds for this variable
          mn = *OptItem.getLowerBoundValue();
          mx = *OptItem.getUpperBoundValue();

          for (k = 0; k < 4; k++)
            {
              for (l = 0, sum = 0.0 ; l < 4; l++)
                sum += 1.0 / (*mFreq[j])[l];

              mProb[k] = 1.0 / (*mFreq[j])[k] / sum;

              // we only want the cumulative probabilities
              if (k > 0) mProb[k] += mProb[k - 1];
            }

          a = mRandomContext.master()->getRandomCC();

          for (k = 0; k < 4; k++)
            {
              // note that the original is <= but numerically < is essentially the same and faster
              if (a < mProb[k])
                {
                  try
                    {
                      // calculate orders of magnitude of the interval
                      la = log10(mx) - log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min()));

                      // determine if linear or log scale
                      if ((mn < 0.0) || (mx <= 0.0))
                        Sol = mn + (mRandomContext.master()->getRandomCC() + (C_FLOAT64) k) * (mx - mn) * 0.25;
                      else
                        {
                          if (la < 1.8)
                            Sol = mn + (mRandomContext.master()->getRandomCC() + (C_FLOAT64) k) * (mx - mn) * 0.25;
                          else
                            Sol = pow(10.0, log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min()))
                                      + la * 0.25 * (mRandomContext.master()->getRandomCC() + (C_FLOAT64) k));
                        }
                    }
                  catch (...)
                    {
                      // TODO: this sounds a bit daft in this context, what else could be done, though?
                      Sol = (mx + mn) * 0.5;
                    }

                  // force it to be within the bounds
                  switch (OptItem.checkConstraint(Sol))
                    {
                      case - 1:
                        Sol = *OptItem.getLowerBoundValue();
                        break;

                      case 1:
                        Sol = *OptItem.getUpperBoundValue();
                        break;
                    }

                  // We need to set the value here so that further checks take
                  // account of the value.
                  *mProblemContext.master()->getContainerVariables(true)[j] = Sol;
                  // increase the frequency
                  (*mFreq[j])[k] += 1;
                  break;
                }
            }
        }

      // calculate its fitness
      Running &= evaluate(*mPool[i]);
      mPoolVal[i] = mEvaluationValue;
    }

  // at this point the pool is formed
  // now we partially sort the pool for the h = b/2 top elements,
  // where b is mPopulationSize, This is done in place with heap sort
  CVector< C_FLOAT64 > *tempvec;
  C_FLOAT64 tempval;
  C_INT32 parent, child;
  C_INT32 h = mPopulationSize / 2;

  // top h are the heap, we first have to sort it
  for (i = 1; i < h; i++)
    {
      // bubble-up
      child = i;

      for (;;)
        {
          if (child == 0) break;

          parent = (C_INT32)floor((double)(child - 1) / 2);

          if (mPoolVal[child] < mPoolVal[parent])
            {
              // swap with parent
              tempval = mPoolVal[child];
              mPoolVal[child] = mPoolVal[parent];
              mPoolVal[parent] = tempval;
              tempvec = mPool[child];
              mPool[child] = mPool[parent];
              mPool[parent] = tempvec;
              // make parent the new child
              child = parent;
            }
          else break;
        }
    }

  for (i = h; i < (C_INT32)mPoolSize; ++i)
    {
      child = 0;

      // check if this element is smaller than any of the leafs
      for (size_t leaf = (size_t)h / 2; leaf < (size_t)h; ++leaf)
        {
          if (mPoolVal[i] < mPoolVal[leaf])
            {
              // keep if this leaf is worse than previous
              if (mPoolVal[child] < mPoolVal[leaf])
                child = leaf;
            }
        }

      if (child == 0) continue;

      if (mPoolVal[i] < mPoolVal[child])
        {
          // swap i and h+j
          tempval = mPoolVal[child];
          mPoolVal[child] = mPoolVal[i];
          mPoolVal[i] = tempval;
          tempvec = mPool[child];
          mPool[child] = mPool[i];
          mPool[i] = tempvec;

          // now bubble-up
          for (;;)
            {
              if (child == 0) break;

              parent = (C_INT32)floor((double)(child - 1) / 2);

              if (mPoolVal[child] < mPoolVal[parent])
                {
                  // swap with parent
                  tempval = mPoolVal[child];
                  mPoolVal[child] = mPoolVal[parent];
                  mPoolVal[parent] = tempval;
                  tempvec = mPool[child];
                  mPool[child] = mPool[parent];
                  mPool[parent] = tempvec;
                  // make parent the new child
                  child = parent;
                }
              else break;
            }
        }
    }

  // since some leafs are not in order in the array, we now do
  // a bubble sort (note: this is best case for bubble sort)
  // we use j because we do not want to change the value of h
  j = h;

  do
    {
      k = 0;

      for (i = 0; i <= j; i++)
        {
          if (mPoolVal[i] > mPoolVal[i + 1])
            {
              tempval = mPoolVal[i];
              mPoolVal[i] = mPoolVal[i + 1];
              mPoolVal[i + 1] = tempval;
              tempvec = mPool[i];
              mPool[i] = mPool[i + 1];
              mPool[i + 1] = tempvec;
              k = i;
            }
        }

      j = k;
    }
  while (j > 1);

  // at this point the pool is formed and partially sorted
  // now we build the RefSet:
  // 1st b/2 are the best ones in the Pool (sorted already)
  // the 2nd b/2 are random (or later can be made diverse by
  // maximising the Euclidean distances)
  for (i = 0; i < (int)mPopulationSize; i++)
    {
      (*mIndividuals[i]) = (*mPool[i]); // copy the whole vector
      mValues[i] = mPoolVal[i]; // keep the value
      mStuck[i] = 1;               // initialize the mStuck counter
    }

  // RefSet needs to be fully sorted. Note that top half is sorted
  // and we are guaranteed that it contains the best values
  // so it is only bottom half that needs sorting.
  sortRefSet(h, mPopulationSize);
  // we're done
  return Running;
}

// sort the RefSet and associated RefSetVal & Stuck
// between positions lower and upper.
void COptMethodSS::sortRefSet(C_INT32 lower, C_INT32 upper)
{
  C_INT32 i, j, k;
  C_INT32 parent, child;
  CVector< C_FLOAT64 > *tempvec;
  C_FLOAT64 tempval;

  // Use heap sort
  for (i = lower + 1; i < upper; i++)
    {
      // bubble-up
      child = i;

      for (;;)
        {
          if (child == 0) break;

          parent = (C_INT32)floor((double)(child - 1) / 2);

          if (mValues[child] < mValues[parent])
            {
              // swap with parent
              tempval = mValues[child];
              mValues[child] = mValues[parent];
              mValues[parent] = tempval;
              tempval = mStuck[child];
              mStuck[child] = mStuck[parent];
              mStuck[parent] = (C_INT32)tempval;
              tempvec = mIndividuals[child];
              mIndividuals[child] = mIndividuals[parent];
              mIndividuals[parent] = tempvec;
              // make parent the new child
              child = parent;
            }
          else break;
        }
    }

  // since some leafs are not in order in the array, we now do
  // a bubble sort (note: this is best case for bubble sort)
  j = upper - 1;

  do
    {
      k = lower;

      for (i = lower; i < j; i++)
        {
          if (mValues[i] > mValues[i + 1])
            {
              tempval = mValues[i];
              mValues[i] = mValues[i + 1];
              mValues[i + 1] = tempval;
              tempval = mStuck[i];
              mStuck[i] = mStuck[i + 1];
              mStuck[i + 1] = (C_INT32)tempval;
              tempvec = mIndividuals[i];
              mIndividuals[i] = mIndividuals[i + 1];
              mIndividuals[i + 1] = tempvec;
              k = i;
            }
        }

      j = k;
    }
  while (j > lower);
}

// check if all the indexes of a Child member are closer to
// the indexes of a Pool member than a certain relative distance
bool COptMethodSS::closerChild(C_INT32 i, C_INT32 j, C_FLOAT64 dist)
{
  C_FLOAT64 mx;

  for (C_INT32 k = 0; k < (C_INT32)mVariableSize; ++k)
    {
      mx = (fabs((*mChild[i])[k]) + fabs((*mPool[j])[k])) / 2.0;

      if (fabs((*mChild[i])[k] - (*mPool[j])[k]) / mx > dist) return false;
    }

  return true;
}

// check if all the indexes of two refset members
// are closer than a certain relative distance
bool COptMethodSS::closerRefSet(C_INT32 i, C_INT32 j, C_FLOAT64 dist)
{
  C_FLOAT64 mx;

  for (C_INT32 k = 0; k < (C_INT32)mVariableSize; ++k)
    {
      mx = (fabs((*mIndividuals[i])[k]) + fabs((*mIndividuals[j])[k])) / 2.0;

      if (fabs((*mIndividuals[i])[k] - (*mIndividuals[j])[k]) / mx > dist) return false;
    }

  return true;
}

// combine individuals in the RefSet two by two
// this is a sort of (1+1)-ES strategy
bool COptMethodSS::combination(void)
{
  C_INT32 i, j, k;      // counters
  C_FLOAT64 mn, mx;     // for bounds on parameters
  C_FLOAT64 beta;       // bias
  C_FLOAT64 la;         // for orders of magnitude
  C_FLOAT64 alpha;      // 1 or -1
  C_FLOAT64 bm2;        // b-2
  C_FLOAT64 omatb;      // (1-alpha*beta)*0.5
  C_FLOAT64 dd;         // (x(i) - x(j) ) / 2 * (1-alpha*beta)
  C_FLOAT64 c1, c2;     // coordinates of the edges of hyperectangle
  CVector< C_FLOAT64 > xnew, xpr;
  C_FLOAT64 xnewval, xprval; // to hold temp value of "parent" in go-beyond strategy
  C_FLOAT64 lambda = 1.0; // damping factor for go-beyond strategy
  C_INT32 improvement; // count iterations with improvement in go-beyond strategy
  bool Running = true; // flag for invalid values

  // make xnew large enough
  xnew.resize(mVariableSize);
  xpr.resize(mVariableSize);
  // calculate a constant
  bm2 = C_FLOAT64(mPopulationSize) - 2.0;
  // signal no children yet
  mChildrenGenerated = false;

  // generate children for each member of the population
  for (i = 0; (i < (int)mPopulationSize) && Running; i++)
    {
      // keep the parent value in childval[i] so that we only accept better than that
      mChildVal[i] = mValues[i];

      for (j = 0; j < (int)mPopulationSize; j++)
        {
          // no self-reproduction...
          if (i != j)
            {
              if (i < j) alpha = 1.0; else alpha = -1.0;

              beta = (fabs(C_FLOAT64(j) - C_FLOAT64(i)) - 1.0) / bm2;
              omatb = (1.0 + alpha * beta) * 0.5;

              // generate a child
              for (k = 0; k < (C_INT32)mVariableSize; ++k)
                {
                  // get the bounds of this parameter
                  COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[k];
                  mn = *OptItem.getLowerBoundValue();
                  mx = *OptItem.getUpperBoundValue();

                  try
                    {
                      // calculate orders of magnitude of the interval
                      if (((*mIndividuals[i])[k] > 0.0) && ((*mIndividuals[j])[k] > 0.0))
                        {
                          la = log10((*mIndividuals[i])[k]) - log10(std::max((*mIndividuals[j])[k], std::numeric_limits< C_FLOAT64 >::min()));
                        }
                      else
                        la = 1.0;

                      dd = ((*mIndividuals[i])[k] - (*mIndividuals[j])[k]) * omatb;
                      // one of the box limits
                      c1 = (*mIndividuals[i])[k] - dd;

                      // force it to be within the bounds
                      switch (OptItem.checkConstraint(c1))
                        {
                          case -1:
                            c1 = mn;
                            break;

                          case 1:
                            c1 = mx;
                            break;
                        }

                      // the other box limit
                      c2 = (*mIndividuals[i])[k] + dd;

                      // force it to be within the bounds
                      switch (OptItem.checkConstraint(c2))
                        {
                          case -1:
                            c2 = mn;
                            break;

                          case 1:
                            c2 = mx;
                            break;
                        }

                      xnew[k] = c1 + (c2 - c1) * mRandomContext.master()->getRandomCC();
                    }
                  catch (...)
                    {
                      // if something failed leave the value intact
                      xnew[k] = (*mIndividuals[i])[k];
                    }

                  // We need to set the value here so that further checks take
                  // account of the value.
                  *mProblemContext.master()->getContainerVariables(true)[k] = xnew[k];
                }

              // calculate the child's fitness
              Running &= evaluate(xnew);

              // keep it if it is better than the previous one
              if (mEvaluationValue < mChildVal[i])
                {
                  // keep a copy of this vector in mChild
                  (*mChild[i]) = xnew;
                  // and the fitness value
                  mChildVal[i] = mEvaluationValue;
                  // signal that child is better than parent
                  mStuck[i] = 0;
                  // signal we have generated a child (improvement)
                  mChildrenGenerated = true;
                }
            }
        }

      // now we apply the go-beyond strategy for
      // cases where the child was an improvement
      if (mStuck[i] == 0)
        {
          // copy the parent
          xpr = (*mIndividuals[i]);
          xprval = mValues[i];
          lambda = 1.0; // this is really 1/lambda so we can use mult rather than div
          improvement = 1;

          // while newval < childval
          for (; ;)
            {
              for (k = 0; k < (C_INT32)mVariableSize; ++k)
                {
                  dd = (xpr[k] - (*mChild[i])[k]) * lambda;
                  xnew[k] = (*mChild[i])[k] + dd * mRandomContext.master()->getRandomCC();
                  // get the bounds of this parameter
                  const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[k];

                  // put it on the bounds if it had exceeded them
                  switch (OptItem.checkConstraint(xnew[k]))
                    {
                      case -1:
                        xnew[k] = *OptItem.getLowerBoundValue();
                        break;

                      case 1:
                        xnew[k] = *OptItem.getUpperBoundValue();
                        break;
                    }

                  // We need to set the value here so that further checks take
                  // account of the value.
                  *mProblemContext.master()->getContainerVariables(true)[k] = xnew[k];
                }

              // calculate the child's fitness
              Running &= evaluate(xnew);
              xnewval = mEvaluationValue;

              // if there was no improvement we finish here => exit for(;;)
              if (mChildVal[i] <= xnewval) break;

              // old child becomes parent
              xpr = (*mChild[i]);
              xprval = mChildVal[i];
              // new child becomes child
              (*mChild[i]) = xnew;
              mChildVal[i] = xnewval;
              // mark improvement
              improvement++;

              if (improvement == 2)
                {
                  lambda *= 0.5;
                  improvement = 0;
                }
            }
        }
    }

  return Running;
}

bool COptMethodSS::childLocalMin(void)
{
  C_INT32 i, best;
  C_FLOAT64 bestVal;
  bool Running = true;

  // signal nothing found yet
  best = -1;
  bestVal = std::numeric_limits<C_FLOAT64>::infinity();

  // find the best child
  for (i = 0; i < (int)mPopulationSize; i++)
    {
      if ((mStuck[i] == 0) && (mChildVal[i] < bestVal))
        {
          bestVal = mChildVal[i];
          best = i;
        }
    }

  // no child in this iteration? exit now
  if (best == -1) return true;

  // check if this child is not close to previous ones
  for (i = 0; i < (C_INT32)mLocalStored; ++i)
    {
      // is the other one like me?
      if (closerChild(best, i, mCloseValue))
        {
          // it is too close, exit now
          return true;
        }
    }

  // store the initial position
  *(mPool[mLocalStored]) = *(mChild[best]);
  mPoolVal[mLocalStored] = mChildVal[best]; //bestVal;
  mLocalStored++;

  // do local minimization on it
  Running &= localmin(*(mChild[best]), mChildVal[best]);

  // store the result
  *(mPool[mLocalStored]) = *(mChild[best]);
  mPoolVal[mLocalStored] = mChildVal[best];
  mLocalStored++;

  // clear the local optimisation counter
  mLocalIter = 1;

  return Running;
}

bool COptMethodSS::optimise()
{
  bool Running = true;
  bool needsort;
  size_t i, j;

  if (!initialize())
    {
      // initialisation failed, we exit
      if (mProcessReport)
        mProcessReport.finishItem(mhGenerations);

      return false;
    }

  mCurrentGeneration = 0;

  // create the Pool of diverse candidate solutions
  Running &= creation();

  // best value is (always) at position zero
  // store that value
  mBestValue = mValues[0];
  // set it upstream
  Running &= mProblemContext.master()->setSolution(mBestValue, *mIndividuals[0], true);
  // We found a new best value let's report it.
  mpParentTask->output(COutputInterface::DURING);

  // test if the user wants to stop, and do so if needed
  if (!Running)
    {
      if (mProcessReport)
        mProcessReport.finishItem(mhGenerations);

      cleanup();
      return true;
    }

  // mPool is now going to be used to keep track of initial and final
  // points of local minimizations (to avoid running them more than once)
  mPoolSize = 2 * mGenerations / mLocalFreq;
  // reset the number of stored minimizations
  mLocalStored = 0;
  // reset the counter for local minimisation
  mLocalIter = 1;

  size_t Stalled = 0;

  // run the mIterations (and count the creation as being the first)
  for (mCurrentGeneration = 1;
       mCurrentGeneration < mGenerations && Running;
       mCurrentGeneration++, Stalled++)
    {

      if (mStopAfterStalledGenerations != 0 && Stalled > mStopAfterStalledGenerations)
        break;

      // check for stagnation or similarity
      needsort = false;

      for (i = 0; i < (size_t)mPopulationSize; ++i)
        {
          // are we stuck? (20 iterations)
          if (mStuck[i] == 19)
            {
              // substitute this one by a random guess
              Running &= randomize(i);
              needsort = true;
              mStuck[i] = 1;
            }
          else
            {
              // check if another RefSet member is similar to us (relative dist 0.1%)
              for (j = i + 1; j < (size_t)mPopulationSize; ++j)
                {
                  // is the other one like me?
                  if (closerRefSet(i, j, mCloseValue))
                    //if (distRefSet(i, j) < 0.01)
                    {
                      // randomize the other one because it has worse value
                      Running &= randomize(j);
                      needsort = true;
                      mStuck[j] = 1;
                    }
                }
            }
        }

      // sort the RefSet if needed
      if (needsort) sortRefSet(0, mPopulationSize);

      // create children by combination
      Running &= combination();

      // check if we have to run a local search
      if (mLocalIter >= mLocalFreq && mChildrenGenerated)
        {
          // carry out a local search
          Running &= childLocalMin();
        }
      else
        {
          // count this
          mLocalIter++;
        }

      // substitute the parents for children or increment stuck counter
      needsort = false;

      for (i = 0; i < (size_t)mPopulationSize; ++i)
        {
          // check if child was better than parent
          if (mStuck[i] == 0)
            {
              // copy the child into the population
              (*mIndividuals[i]) = (*mChild[i]);
              // keep its obj funct value
              mValues[i] = mChildVal[i];
              // and reset the stuck counter
              mStuck[i] = 1;
              needsort = true;
            }
          else
            {
              // nothing to do, increment parent's stuck counters
              mStuck[i]++;
            }
        }

      // sort the RefSet if needed
      if (needsort) sortRefSet(0, mPopulationSize);

      // have we made any progress?
      if (mValues[0] < mBestValue)
        {
          Stalled = 0;

          // and store that value
          mBestValue = mValues[0];
          Running &= mProblemContext.master()->setSolution(mBestValue, *mIndividuals[0], true);
          // We found a new best value lets report it.
          mpParentTask->output(COutputInterface::DURING);
        }

      if (mProcessReport)
        Running &= mProcessReport.progressItem(mhGenerations);

      //use a different output channel. It will later get a proper enum name
      mpParentTask->output(COutputInterface::MONITORING);
    }

  // end of loop for iterations

  // the best ever might not be what is on position 0, so bring it back
  *mIndividuals[0] = mProblemContext.master()->getSolutionVariables(true);

  // now let's do a final local minimisation with a tighter tolerance

  if (Running)
    {
      mpLocalMinimizer->setValue("Tolerance", (C_FLOAT64) 1.e-006);
      Running &= localmin(*(mIndividuals[0]), mValues[0]);
    }

  // has it improved?
  if (mValues[0] < mBestValue)
    {
      // and store that value
      mBestValue = mValues[0];
      Running &= mProblemContext.master()->setSolution(mBestValue, *mIndividuals[0], true);
      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  if (mProcessReport)
    mProcessReport.finishItem(mhGenerations);

  cleanup();
  return true;
}

#ifdef DEBUG_OPT
bool COptMethodSS::serializeprob(void)
{
  std::ofstream ofile;
  // open the file for output, in append mode
  ofile.open("ssprob.txt", std::ios::out);  // | std::ios::app );

  if (! ofile.is_open())
    {
      std::cerr << "error opening file \'ssprob.txt\'" << std::endl;
      return false;
    }

  ofile << mProb << std::endl;
  ofile.close();
  return true;
}
// serialize the pool to a file for debugging purposes
bool COptMethodSS::serializepool(size_t first, size_t last)
{
  size_t Last = std::min(last, (size_t) mPoolSize);

  size_t i;
  size_t j;

  std::ofstream ofile;

  // open the file for output, in append mode
  ofile.open("sspool.txt", std::ios::out | std::ios::app);

  if (! ofile.is_open())
    {
      std::cerr << "error opening file \'sspool.txt\'" << std::endl;
      return false;
    }

  for (i = first; i < Last; i++)
    {
      for (j = 0; j < mVariableSize; j++)
        {
          C_FLOAT64 & mut = (*mPool[i])[j];
          // print this parameter
          ofile << mut << "\t";
        }

      // print the fitness of the individual
      ofile << mPoolVal[i] << std::endl;
    }

  ofile << std::endl;
  ofile.close();
  return true;
}
// write informative messages about the progress of the refset
bool COptMethodSS::inforefset(C_INT32 type, C_INT32 element)
{
  std::ofstream ofile;

  // open the file for output, in append mode
  ofile.open("ssrefset.txt", std::ios::out | std::ios::app);

  if (! ofile.is_open())
    {
      std::cerr << "error opening file \'ssrefset.txt\'" << std::endl;
      return false;
    }

  switch (type)
    {
      case 1: ofile << "element " << element << " improved in combination" << std::endl; break;

      case 2: ofile << "element " << element << " improved in go-beyond" << std::endl; break;

      case 3: ofile << "No element improved in iteration " << element << std::endl ; break;

      case 4: ofile << "element " << element << " randomized, too close to another" << std::endl; break;

      case 5: ofile << "element " << element << " randomized, was stuck" << std::endl; break;

      case 6: ofile << "child" << element << " too close to previous solution, no local min" << std::endl; break;

      case 7: ofile << "c1 is NaN (element" << element << ")" << std::endl; break;

      case 8: ofile << "c2 is NaN (element" << element << ")" << std::endl; break;

      case 9: ofile << "xnew[k] is NaN (element" << element << ")" << std::endl; break;

      case 10: ofile << "Children of " << element << std::endl; break;

      case 11: ofile << "Local minimization at value " << element << std::endl; break;
    }

  ofile.close();
  return true;
}

// serialize the population to a file for debugging purposes
bool COptMethodSS::serializerefset(C_INT32 first, C_INT32 last)
{
  C_INT32 Last = std::min(last, mPopulationSize);
  C_INT32 i, j;
  std::ofstream ofile;

  // open the file for output, in append mode
  ofile.open("ssrefset.txt", std::ios::out | std::ios::app);

  if (! ofile.is_open())
    {
      std::cerr << "error opening file \'ssrefset.txt\'" << std::endl;
      return false;
    }

  ofile << std::endl << "Refset" << std::endl;

  for (i = first; i < Last; i++)
    {
      for (j = 0; j < mVariableSize; j++)
        {
          C_FLOAT64 & mut = (*mIndividuals[i])[j];
          // print this parameter
          ofile << mut << "\t";
        }

      // print the fitness of the individual
      ofile << mValues[i] << std::endl;
    }

  ofile << std::endl;
  ofile.close();
  return true;
}
// serialize the population to a file for debugging purposes
bool COptMethodSS::serializevector(CVector< C_FLOAT64 > x, C_FLOAT64 xval)
{
  C_INT32 i;
  std::ofstream ofile;

  // open the file for output, in append mode
  ofile.open("ssrefset.txt", std::ios::out | std::ios::app);

  if (! ofile.is_open())
    {
      std::cerr << "error opening file \'ssrefset.txt\'" << std::endl;
      return false;
    }

  for (i = 0; i < mVariableSize; i++)
    {
      // print this parameter
      ofile << x[i] << "\t";
    }

  // print the fitness of the individual
  ofile << xval << std::endl;

  ofile.close();
  return true;
}
// serialize the population to a file for debugging purposes
bool COptMethodSS::serializechildren(size_t first, size_t last)
{
  size_t Last = std::min(last, (size_t) mPopulationSize);

  size_t i;
  size_t j;

  std::ofstream ofile;

  // open the file for output, in append mode
  ofile.open("sschild.txt", std::ios::out | std::ios::app);

  if (! ofile.is_open())
    {
      std::cerr << "error opening file \'sschild.txt\'" << std::endl;
      return false;
    }

  for (i = first; i < Last; i++)
    {
      for (j = 0; j < mVariableSize; j++)
        {
          C_FLOAT64 & mut = (*mChild[i])[j];
          // print this parameter
          ofile << mut << "\t";
        }

      // print the fitness of the individual
      ofile << mChildVal[i] << std::endl;
    }

  ofile << std::endl;
  ofile.close();
  return true;
}
#endif
