// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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
                           const CTaskEnum::Task & taskType)
  : COptPopulationMethod(pParent, methodType, taskType, true)
  , mPool(0)
  , mPoolVal(0)
  , mPoolSize(0)
  , mStopAfterStalledGenerations(0)
  , mBestIndex(C_INVALID_INDEX)
  , mpLocalMinimizer(NULL)
  , mLocalMinimizerContext(true, this)
{
  assertParameter("Number of Iterations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 200);
  assertParameter("Random Number Generator", CCopasiParameter::Type::UINT, (unsigned C_INT32) CRandom::mt19937, eUserInterfaceFlag::editable);
  assertParameter("Seed", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);
  assertParameter("Stop after # Stalled Generations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);

  initObjects();
}

COptMethodSS::COptMethodSS(const COptMethodSS & src,
                           const CDataContainer * pParent,
                           const bool & parallel)
  : COptPopulationMethod(src, pParent, parallel)
  , mPool(0)
  , mPoolVal(0)
  , mPoolSize(0)
  , mStopAfterStalledGenerations(0)
  , mBestIndex(C_INVALID_INDEX)
  , mpLocalMinimizer(NULL)
  , mLocalMinimizerContext(parallel, this)
{
  // remove eventual existing parameters from the release version.
  initObjects();
}

COptMethodSS::~COptMethodSS()
{
  cleanup();
}

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
      if (mProcessReport
          && !mProcessReport.finishItem(mhGenerations))
        signalStop();

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

  CFitProblem * pFitProblem = dynamic_cast< CFitProblem * >(mProblemContext.active());

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

  mLocalMinimizerContext.setMaster(mpLocalMinimizer);
  mLocalMinimizerContext.setProblemContext(mProblemContext);

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

  // first we set up the problem
  // (optmethod and optproblem already setup in initialization)
  // let's get the list of parameters
  C_FLOAT64 GlobalValue;
  CVector< C_FLOAT64 > GlobalVariables;

  if (mProblemContext.singleThreadedExecution())
    {
      GlobalValue = mProblemContext.master()->getSolutionValue();
      GlobalVariables = mProblemContext.master()->getSolutionVariables();
    }
  else
    {
      mProblemContext.master()->incrementCounters(mProblemContext.active()->getCounters());
      mProblemContext.active()->reset();
    }

  const std::vector< COptItem * > & OptItemList = mProblemContext.active()->getOptItemList(true);

  // and set them to the values passed in solution
  for (i = 0; i < mVariableSize; i++)
    {
      OptItemList[i]->setStartValue(solution[i]);
    }

  // run it
  Running &= mLocalMinimizerContext.active()->optimise();

  // pass the results on to the calling parameters
  fval = mProblemContext.active()->getSolutionValue();
  solution = mProblemContext.active()->getSolutionVariables(true);

  if (mProblemContext.singleThreadedExecution())
    {
      mProblemContext.master()->setSolution(GlobalValue, GlobalVariables);
    }

  return Running;
}

// randomize the values of RefSet[i]
bool COptMethodSS::randomize(C_INT32 i)
{
  bool Running = true;  // flag for invalid values

  const std::vector< COptItem * > & OptItemList = mProblemContext.active()->getOptItemList(true);
  CRandom * pRandom = mRandomContext.active();

  for (size_t j = 0; j < mVariableSize; ++j)
    {
      COptItem & OptItem = *OptItemList[j];
      C_FLOAT64 & Sol = (*mPool[i])[j];

      Sol = OptItem.getRandomValue(pRandom);
      OptItem.setItemValue(Sol, COptItem::CheckPolicyFlag::All);
    }

  // calculate its fitness
  mValues[i] = evaluate(EvaluationPolicy::Constraints);

  // reset the stuck flag
  mStuck[i] = 1;
  return Running;
}

// initialise the population using the
// Diversification Generation Method
bool COptMethodSS::creation(void)
{
  size_t i, j, k, l;   // counters
  C_FLOAT64 mn, mx, la; // for boundaries of rnd
  C_FLOAT64 sum;        // to calculate a summation
  C_FLOAT64 a;          // to hold a random number
  bool Running = true;  // flag for invalid values

  // initialize all entries of the Pool.
  // first 4 candidates as a latin hypercube
  for (i = 0; (i < 4) && proceed(); i++)
    {
      const std::vector< COptItem * > & OptItemList = mProblemContext.active()->getOptItemList(true);
      CRandom * pRandom = mRandomContext.master();

      for (j = 0; j < mVariableSize; ++j)
        {
          // get pointers to appropriate elements (easier reading of code)
          COptItem & OptItem = *OptItemList[j];
          C_FLOAT64 & Sol = (*mPool[i])[j];
          const CIntervalValue & Interval = OptItem.getInterval();

          try
            {
              if (Interval.isLogarithmic())
                switch (Interval.getRange())
                  {
                  case CIntervalValue::Range::positive:
                    Sol = pow(10.0, log10(std::max(Interval.getMinimum(), std::numeric_limits< C_FLOAT64 >::min()))
                                      + 0.25 * Interval.getLogarithmicScale() * ((C_FLOAT64) i + pRandom->getRandomCC()));
                    break;

                  case CIntervalValue::Range::containsZero:
                    if (Interval.getLogarithmicScale() > 0)
                      {
                        C_FLOAT64 R = 2.0 / (2.0 + Interval.getLogarithmicScale());
                        C_FLOAT64 Sample = 0.25 * (i + pRandom->getRandomCC());

                        if (Sample < R)
                          Sol = Interval.getMinimum() * (1.0 - 2.0 * Sample / R);
                        else
                          Sol = pow(10.0, log10(std::max(-Interval.getMinimum(), std::numeric_limits< C_FLOAT64 >::min())) + Interval.getLogarithmicScale() * (Sample - R) / (1.0 - R));
                      }
                    else
                      {
                        C_FLOAT64 R = 2.0 / (2.0 - Interval.getLogarithmicScale());
                        C_FLOAT64 Sample = 0.25 * (i + pRandom->getRandomCC());

                        if (Sample < R)
                          Sol = Interval.getMaximum() * (1.0 - 2.0 * Sample / R);
                        else
                          Sol = -pow(10.0, log10(std::max(Interval.getMaximum(), std::numeric_limits< C_FLOAT64 >::min())) - Interval.getLogarithmicScale() * (Sample - R) / (1.0 - R));
                      }
                    break;

                  case CIntervalValue::Range::negative:
                    Sol = -pow(10.0, log10(std::max(-Interval.getMaximum(), std::numeric_limits< C_FLOAT64 >::min()))
                                       + 0.25 * Interval.getLogarithmicScale() * ((C_FLOAT64) i + pRandom->getRandomCC()));
                    break;
                  }
              else
                Sol = Interval.getMinimum() + 0.25 * Interval.getSize() * ((C_FLOAT64) i + pRandom->getRandomCC());
            }
          catch (const std::exception & e)
            {
              Sol = Interval.getMinimum() + 0.25 * Interval.getSize() * ((C_FLOAT64) i + 0.5);
            }

          OptItem.setItemValue(Sol, COptItem::CheckPolicyFlag::All);
        }

      // calculate its fitness
      mPoolVal[i] = evaluate(EvaluationPolicy::Constraints);
    }

  // next we add the initial guess from the user
  createIndividual(C_INVALID_INDEX, COptItem::CheckPolicyFlag::All);
  mPoolVal[i] = evaluate(EvaluationPolicy::Constraints);
  *mPool[i] = *mIndividuals[0];
  ++i;

  // the remaining entries depend on probabilities
  for (; (i < mPoolSize) && proceed(); ++i)
    {
      const std::vector< COptItem * > & OptItemList = mProblemContext.master()->getOptItemList(true);
      CRandom * pRandom = mRandomContext.master();

      for (j = 0; j < (C_INT32)mVariableSize; ++j)
        {
          // get pointers to appropriate elements (easier reading of code)
          COptItem & OptItem = *OptItemList[j];
          C_FLOAT64 & Sol = (*mPool[i])[j];
          const CIntervalValue & Interval = OptItem.getInterval();

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
                      if (Interval.isLogarithmic())
                        switch (Interval.getRange())
                          {
                          case CIntervalValue::Range::positive:
                            Sol = pow(10.0, log10(std::max(Interval.getMinimum(), std::numeric_limits< C_FLOAT64 >::min()))
                                              + 0.25 * Interval.getLogarithmicScale() * ((C_FLOAT64) k + pRandom->getRandomCC()));
                            break;

                          case CIntervalValue::Range::containsZero:
                            // TODO This is sampled form a normal distribution with mean = (maximum + minimum)/2 and sigma = 3
                            Sol = Interval.getMinimum() + 0.25 * Interval.getSize() * ((C_FLOAT64) k + pRandom->getRandomCC());
                            break;

                          case CIntervalValue::Range::negative:
                            Sol = -pow(10.0, log10(std::max(-Interval.getMaximum(), std::numeric_limits< C_FLOAT64 >::min()))
                                              + 0.25 * Interval.getLogarithmicScale() * ((C_FLOAT64) k + pRandom->getRandomCC()));
                            break;
                          }
                      else
                        Sol = Interval.getMinimum() + 0.25 * Interval.getSize() * ((C_FLOAT64) k + pRandom->getRandomCC());
                    }
                  catch (const std::exception & e)
                    {
                      Sol = Interval.getMinimum() + 0.25 * Interval.getSize() * ((C_FLOAT64) k + 0.5);
                    }

                  OptItem.setItemValue(Sol, COptItem::CheckPolicyFlag::All);

                  // increase the frequency
                  (*mFreq[j])[k] += 1;
                  break;
                }
            }
        }

      // calculate its fitness
      mPoolVal[i] = evaluate(EvaluationPolicy::Constraints);
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

          parent = (C_INT32)floor((C_FLOAT64)(child - 1) / 2);

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
              std::swap(mValues[child], mValues[parent]);
              std::swap(mStuck[child], mStuck[parent]);
              std::swap(mIndividuals[child], mIndividuals[parent]);

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
              std::swap(mValues[i], mValues[i + 1]);
              std::swap(mStuck[i], mStuck[i + 1]);
              std::swap(mIndividuals[i], mIndividuals[i + 1]);
              
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
  const CVector< C_FLOAT64 > & Child = *mChild[i];
  const CVector< C_FLOAT64 > & Pool = *mPool[j];

  for (size_t k = 0; k < mVariableSize; ++k)
    {
      mx = (fabs(Child[k]) + fabs(Pool[k])) / 2.0;

      if (fabs(Child[k] - Pool[k]) > dist * mx)
        return false;
    }

  return true;
}

// check if all the indexes of two refset members
// are closer than a certain relative distance
bool COptMethodSS::closerRefSet(C_INT32 i, C_INT32 j, C_FLOAT64 dist)
{
  C_FLOAT64 mx;
  const CVector< C_FLOAT64 > & I = *mIndividuals[i];
  const CVector< C_FLOAT64 > & J = *mIndividuals[j];

  for (size_t k = 0; k < mVariableSize; ++k)
    {
      mx = (fabs(I[k]) + fabs(J[k])) / 2.0;

      if (fabs(I[k] - J[k]) > dist * mx)
         return false;
    }

  return true;
}

// combine individuals in the RefSet two by two
// this is a sort of (1+1)-ES strategy
bool COptMethodSS::combination(void)
{
  size_t i, j;      // counters
  C_FLOAT64 beta;       // bias
  C_FLOAT64 alpha;      // 1 or -1
  C_FLOAT64 bm2;        // b-2
  C_FLOAT64 omatb;      // (1-alpha*beta)*0.5
  C_FLOAT64 dd;         // (x(i) - x(j) ) / 2 * (1-alpha*beta)
  C_FLOAT64 c1, c2;     // coordinates of the edges of hyperectangle
  CVector< C_FLOAT64 > xnew, xpr;
  C_FLOAT64 xnewval, xprval; // to hold temp value of "parent" in go-beyond strategy
  C_FLOAT64 lambda = 1.0; // damping factor for go-beyond strategy
  C_INT32 improvement; // count iterations with improvement in go-beyond strategy

  // make xnew large enough
  xnew.resize(mVariableSize);
  xpr.resize(mVariableSize);
  // calculate a constant
  bm2 = C_FLOAT64(mPopulationSize) - 2.0;
  // signal no children yet
  mChildrenGenerated = false;

  // generate children for each member of the population
#pragma omp parallel for schedule(runtime)
  for (i = 0; i < mPopulationSize; i++)
    {
      const std::vector< COptItem * > & OptItemList = mProblemContext.active()->getOptItemList(true);
      CRandom * pRandom = mRandomContext.active();

      // keep the parent value in childval[i] so that we only accept better than that
      mChildVal[i] = mValues[i];

      for (j = 0; j < mPopulationSize; j++)
        {
          // no self-reproduction...
          if (i != j)
            {
              if (i < j)
                alpha = 1.0;
              else
                alpha = -1.0;

              beta = (fabs(C_FLOAT64(j) - C_FLOAT64(i)) - 1.0) / bm2;
              omatb = (1.0 + alpha * beta) * 0.5;

              // generate a child
              for (size_t k = 0; k < mVariableSize; ++k)
                {
                  COptItem & OptItem = *OptItemList[j];
                  C_FLOAT64 & Sol = (*mPool[i])[j];
                  const CIntervalValue & Interval = OptItem.getInterval();

                  try
                    {
                      dd = ((*mIndividuals[i])[k] - (*mIndividuals[j])[k]) * omatb;

                      // one of the box limits
                      c1 = (*mIndividuals[i])[k] - dd;

                      // force it to be within the bounds
                      switch (OptItem.checkConstraint(c1))
                        {
                          case -1:
                            c1 = Interval.getMinimum();
                            break;

                          case 1:
                            c1 = Interval.getMaximum();
                            break;
                        }

                      // the other box limit
                      c2 = (*mIndividuals[i])[k] + dd;

                      // force it to be within the bounds
                      switch (OptItem.checkConstraint(c2))
                        {
                          case -1:
                            c2 = Interval.getMinimum();
                            break;

                          case 1:
                            c2 = Interval.getMinimum();
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
                  OptItemList[k]->setItemValue(xnew[k], COptItem::CheckPolicyFlag::All);
                }

              // calculate the child's fitness
              C_FLOAT64 EvaluationValue = evaluate(EvaluationPolicy::Constraints);

              // keep it if it is better than the previous one
              if (EvaluationValue < mChildVal[i])
                {
                  // keep a copy of this vector in mChild
                  (*mChild[i]) = xnew;
                  // and the fitness value
                  mChildVal[i] = EvaluationValue;

                  // signal that child is better than parent
                  mStuck[i] = 0;

#pragma omp critical (optmethodss_child_generated)
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
          while (proceed())
            {
              for (size_t k = 0; k < mVariableSize; ++k)
                {
                  COptItem & OptItem = *OptItemList[j];
                  dd = (xpr[k] - (*mChild[i])[k]) * lambda;
                  xnew[k] = (*mChild[i])[k] + dd * pRandom->getRandomCC();
                  // get the bounds of this parameter

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
                  OptItem.setItemValue(xnew[k], COptItem::CheckPolicyFlag::All);
                }

              // calculate the child's fitness
              xnewval = evaluate(EvaluationPolicy::Constraints);

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

  return true;
}

bool COptMethodSS::childLocalMin(void)
{
  size_t i, best;
  C_FLOAT64 bestVal;
  bool Running = true;

  // signal nothing found yet
  best = C_INVALID_INDEX;
  bestVal = std::numeric_limits<C_FLOAT64>::infinity();

  // find the best child
  for (i = 0; i < mPopulationSize; i++)
    {
      if ((mStuck[i] == 0) 
          && (mChildVal[i] < bestVal))
        {
          bestVal = mChildVal[i];
          best = i;
        }
    }

  // no child in this iteration? exit now
  if (best == C_INVALID_INDEX)
    return true;

  // check if this child is not close to previous ones
  for (i = 0; i < mLocalStored; ++i)
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
      if (mProcessReport
          && !mProcessReport.finishItem(mhGenerations))
        signalStop();

      return false;
    }

  mCurrentGeneration = 0;

  // create the Pool of diverse candidate solutions
  Running &= creation();

  // best value is (always) at position zero
  // store that value
  setSolution(mValues[0], *mIndividuals[0], true);

  // We found a new best value let's report it.
  mpParentTask->output(COutputInterface::DURING);

  // test if the user wants to stop, and do so if needed
  if (!Running)
    {
      if (mProcessReport
          && !mProcessReport.finishItem(mhGenerations))
        signalStop();

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

#pragma omp parallel for schedule(runtime)
      for (i = 0; i < mPopulationSize; ++i)
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
              for (j = i + 1; j < mPopulationSize; ++j)
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
      if (needsort) 
        sortRefSet(0, mPopulationSize);

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
      if (mValues[0] < getBestValue())
        {
          Stalled = 0;

          // and store that value
          setSolution(mValues[0], *mIndividuals[0], true);
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
  if (mValues[0] < getBestValue())
    setSolution(mValues[0], *mIndividuals[0], true);

  if (mProcessReport
      && !mProcessReport.finishItem(mhGenerations))
    signalStop();

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
