// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// originally implemented by Michalina Kaszuba, 2012, University of Manchester

#include <limits>
#include <string>
#include <cmath>

#include "copasi/copasi.h"
#include "COptMethodDE.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "copasi/randomGenerator/CRandom.h"
#include "copasi/randomGenerator/CPermutation.h"
#include "copasi/utilities/CProcessReport.h"
#include "copasi/utilities/CSort.h"
#include "copasi/core/CDataObjectReference.h"

COptMethodDE::COptMethodDE(const CDataContainer * pParent,
                           const CTaskEnum::Method & methodType,
                           const CTaskEnum::Task & taskType):
  COptPopulationMethod(pParent, methodType, taskType, false),
  mpPermutation(NULL),
  mEvaluationValue(std::numeric_limits< C_FLOAT64 >::max()),
  mMutationVarians(0.1),
  mStopAfterStalledGenerations(0),
  mBestValue(std::numeric_limits< C_FLOAT64 >::max()),
  mBestIndex(C_INVALID_INDEX)

{
  assertParameter("Number of Generations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 2000);
  assertParameter("Population Size", CCopasiParameter::Type::UINT, (unsigned C_INT32) 10);
  assertParameter("Random Number Generator", CCopasiParameter::Type::UINT, (unsigned C_INT32) CRandom::mt19937, eUserInterfaceFlag::editable);
  assertParameter("Seed", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);
  assertParameter("Mutation Variance", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) 0.1, eUserInterfaceFlag::editable);
  assertParameter("Stop after # Stalled Generations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);

  initObjects();
}

COptMethodDE::COptMethodDE(const COptMethodDE & src,
                           const CDataContainer * pParent):
  COptPopulationMethod(src, pParent),
  mpPermutation(NULL),
  mEvaluationValue(std::numeric_limits< C_FLOAT64 >::max()),
  mMutationVarians(0.1),
  mStopAfterStalledGenerations(0),
  mBestValue(std::numeric_limits< C_FLOAT64 >::max()),
  mBestIndex(C_INVALID_INDEX)
{initObjects();}

COptMethodDE::~COptMethodDE()
{cleanup();}

// evaluate the fitness of one individual
bool COptMethodDE::evaluate(const CVector< C_FLOAT64 > & /* individual */)
{
  bool Continue = true;

  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  // evaluate the fitness
  Continue &= mProblemContext.master()->calculate();

  // check whether the functional constraints are fulfilled
  if (!mProblemContext.master()->checkFunctionalConstraints())
    mEvaluationValue = std::numeric_limits<C_FLOAT64>::infinity();
  else
    mEvaluationValue = mProblemContext.master()->getCalculateValue();

  return Continue;
}

bool COptMethodDE::replicate()
{
  size_t i, j;
  size_t a, b, c;

  bool Continue = true;

  for (i = mPopulationSize; i < 2 * mPopulationSize && Continue; i++)
    {
      mpPermutation->shuffle(3);

      // MUTATION a, b, c in [0, mPopulationSize - 1]
      a = mpPermutation->pick();
      // b is guaranteed to be different from a
      b = mpPermutation->next();
      // c is guaranteed to be different from a and b
      c = mpPermutation->next();

      // MUTATE CURRENT GENERATION
      for (j = 0; j < mVariableSize; j++)
        {
          const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[j];
          C_FLOAT64 & mut = (*mIndividuals[i])[j];

          mut = (*mIndividuals[c])[j] + 2 * ((*mIndividuals[a])[j] - (*mIndividuals[b])[j]);

          // force it to be within the bounds
          switch (OptItem.checkConstraint(mut))
            {
              case - 1:
                mut = *OptItem.getLowerBoundValue();
                break;

              case 1:
                mut = *OptItem.getUpperBoundValue();
                break;
            }

          // We need to set the value here so that further checks take
          // account of the value.
          *mProblemContext.master()->getContainerVariables(true)[j] = mut;
        }

      Continue &= evaluate(*mIndividuals[i]);
      mValues[i] = mEvaluationValue;
    }

  //CROSSOVER MUTATED GENERATION WITH THE CURRENT ONE
  for (i = 2 * mPopulationSize; i < 3 * mPopulationSize && Continue; i++)
    {
      for (j = 0; j < mVariableSize; j++)
        {

          const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[j];
          C_FLOAT64 & mut = (*mIndividuals[i])[j];

          size_t r = mRandomContext.master()->getRandomU(mPopulationSize - 1);

          if (r < 0.6 * mPopulationSize)
            {
              mut = (*mIndividuals[i - mPopulationSize])[j] *
                    mRandomContext.master()->getRandomNormal(1, mMutationVarians);
            }

          else
            mut = (*mIndividuals[i - 2 * mPopulationSize])[j];

          // force it to be within the bounds
          switch (OptItem.checkConstraint(mut))
            {
              case - 1:
                mut = *OptItem.getLowerBoundValue();
                break;

              case 1:
                mut = *OptItem.getUpperBoundValue();
                break;
            }

          *mProblemContext.master()->getContainerVariables(true)[j] = mut;
        }

      Continue &= evaluate(*mIndividuals[i]);
      mValues[i] = mEvaluationValue;
    }

  //SELECT NEXT GENERATION
  for (i = 2 * mPopulationSize; i < 3 * mPopulationSize && Continue; i++)
    {
      if (mValues[i - mPopulationSize] > mValues[i] && mValues[i - 2 * mPopulationSize] > mValues[i])
        {
          *mIndividuals[i - 2 * mPopulationSize] = *mIndividuals[i];
          mValues[i - 2 * mPopulationSize] = mValues[i];
        }
      else if (mValues[i - mPopulationSize] < mValues[i - 2 * mPopulationSize])
        {
          *mIndividuals[i - 2 * mPopulationSize] = *mIndividuals[i - mPopulationSize];
          mValues[i - 2 * mPopulationSize] = mValues[i - mPopulationSize];
        }
      else if (mBestIndex != i && mBestIndex == C_INVALID_INDEX)
        {
          for (j = 0; j < mVariableSize; j++)
            {
              const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[j];
              C_FLOAT64 & mut = (*mIndividuals[i - 2 * mPopulationSize])[j];

              size_t r = mRandomContext.master()->getRandomU(mPopulationSize - 1);

              if (r < 0.6 * mPopulationSize)
                mut *= mRandomContext.master()->getRandomNormal(1, mMutationVarians);

              // force it to be within the bounds
              switch (OptItem.checkConstraint(mut))
                {
                  case - 1:
                    mut = *OptItem.getLowerBoundValue();
                    break;

                  case 1:
                    mut = *OptItem.getUpperBoundValue();
                    break;
                }

              *mProblemContext.master()->getContainerVariables(true)[j] = mut;
            }

          Continue &= evaluate(*mIndividuals[i - 2 * mPopulationSize]);
          mValues[i - 2 * mPopulationSize] = mEvaluationValue;
        }
    }

  return Continue;
}

// check the best individual at this generation
size_t COptMethodDE::fittest()
{
  size_t i, BestIndex = C_INVALID_INDEX;
  C_FLOAT64 BestValue = std::numeric_limits< C_FLOAT64 >::max();

  for (i = 0; i < mPopulationSize; i++)
    if (mValues[i] < BestValue)
      {
        BestIndex = i;
        BestValue = mValues[i];
      }

  return BestIndex;
}

// check the best individual at this generation
void COptMethodDE::boost()
{
  size_t i;

  for (i = 2 * mPopulationSize; i < 3 * mPopulationSize; i++)
    if (mValues[i] < mValues[i - 2 * mPopulationSize])
      {
        *mIndividuals[i - 2 * mPopulationSize] = *mIndividuals[i];
        mValues[i - 2 * mPopulationSize] = mValues[i];
      }
}

// Initialize the population
bool COptMethodDE::creation(size_t first, size_t last)
{
  size_t Last = std::min(last, (size_t) mPopulationSize);
  size_t i, j;

  C_FLOAT64 mn;
  C_FLOAT64 mx;
  C_FLOAT64 la;

  bool Continue = true;

  for (i = first; i < Last && Continue; i++)
    {
      // We do not want to loose the best individual;
      if (mBestIndex != i)
        for (j = 0; j < mVariableSize; j++)
          {
            // calculate lower and upper bounds
            const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[j];
            mn = *OptItem.getLowerBoundValue();
            mx = *OptItem.getUpperBoundValue();

            C_FLOAT64 & mut = (*mIndividuals[i])[j];

            try
              {
                // determine if linear or log scale
                if ((mn < 0.0) || (mx <= 0.0))
                  mut = mn + mRandomContext.master()->getRandomCC() * (mx - mn);
                else
                  {
                    la = log10(mx) - log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min()));

                    if (la < 1.8)
                      mut = mn + mRandomContext.master()->getRandomCC() * (mx - mn);
                    else
                      mut = pow(10.0, log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min())) + la * mRandomContext.master()->getRandomCC());
                  }
              }

            catch (...)
              {
                mut = (mx + mn) * 0.5;
              }

            // force it to be within the bounds
            switch (OptItem.checkConstraint(mut))
              {
                case - 1:
                  mut = *OptItem.getLowerBoundValue();
                  break;

                case 1:
                  mut = *OptItem.getUpperBoundValue();
                  break;
              }

            // We need to set the value here so that further checks take
            // account of the value.
            *mProblemContext.master()->getContainerVariables(true)[j] = mut;
          }

      // calculate its fitness
      Continue &= evaluate(*mIndividuals[i]);
      mValues[i] = mEvaluationValue;
    }

  return Continue;
}

void COptMethodDE::initObjects()
{
}

bool COptMethodDE::initialize()
{
  cleanup();

  size_t i;

  if (!COptPopulationMethod::initialize())
    {
      if (mProcessReport)
        mProcessReport.finishItem(mhGenerations);

      return false;
    }

  if (mPopulationSize < 4)
    {
      if (mLogVerbosity > 0)
        mMethodLog.enterLogEntry(COptLogEntry("User defined Population Size too small. Reset to minimum (4)."));

      mPopulationSize = 4;
      setValue("Population Size", mPopulationSize);
    }

  mpPermutation = new CPermutation(mRandomContext.master(), mPopulationSize);

  mIndividuals.resize(3 * mPopulationSize);

  for (i = 0; i < 3 * mPopulationSize; i++)
    mIndividuals[i] = new CVector< C_FLOAT64 >(mVariableSize);

  mValues.resize(3 * mPopulationSize);
  mValues = std::numeric_limits<C_FLOAT64>::infinity();
  mBestValue = std::numeric_limits<C_FLOAT64>::infinity();

  mMutationVarians = 0.1;

  if (getParameter("Mutation Variance"))
    {
      mMutationVarians = getValue< C_FLOAT64 >("Mutation Variance");

      if (mMutationVarians < 0.0 || 1.0 < mMutationVarians)
        {
          mMutationVarians = 0.1;
          setValue("Mutation Variance", mMutationVarians);
        }
    }

  if (getParameter("Stop after # Stalled Generations"))
    mStopAfterStalledGenerations = getValue <unsigned C_INT32>("Stop after # Stalled Generations");

  return true;
}

bool COptMethodDE::cleanup()
{
  pdelete(mpPermutation);
  return COptPopulationMethod::cleanup();
}

bool COptMethodDE::optimise()
{
  bool Continue = true;

  if (!initialize())
    {
      if (mProcessReport)
        mProcessReport.finishItem(mhGenerations);

      return false;
    }

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry(
        "Algorithm started.",
        "For more information about this method see: http://copasi.org/Support/User_Manual/Methods/Optimization_Methods/Differential_Evolution/"
      )
    );

  size_t i;

  // initialise the population
  // first individual is the initial guess
  bool pointInParameterDomain = true;

  for (i = 0; i < mVariableSize; i++)
    {
      C_FLOAT64 & mut = (*mIndividuals[0])[i];
      const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[i];

      mut = OptItem.getStartValue();

      // force it to be within the bounds
      switch (OptItem.checkConstraint(mut))
        {
          case - 1:
            mut = *OptItem.getLowerBoundValue();
            pointInParameterDomain = false;
            break;

          case 1:
            mut = *OptItem.getUpperBoundValue();
            pointInParameterDomain = false;
            break;
        }

      // We need to set the value here so that further checks take
      // account of the value.
      *mProblemContext.master()->getContainerVariables(true)[i] = mut;
    }

  if (!pointInParameterDomain && (mLogVerbosity > 0))
    mMethodLog.enterLogEntry(COptLogEntry("Initial point outside parameter domain."));

  Continue &= evaluate(*mIndividuals[0]);
  mValues[0] = mEvaluationValue;

  if (!std::isnan(mEvaluationValue))
    {
      // and store that value
      mBestValue = mValues[0];
      Continue &= mProblemContext.master()->setSolution(mBestValue, *mIndividuals[0], true);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  // the others are random
  Continue &= creation(1, mPopulationSize);

  mBestIndex = fittest();

  if (mBestIndex != C_INVALID_INDEX &&
      mValues[mBestIndex] < mBestValue)
    {
      // and store that value
      mBestValue = mValues[mBestIndex];
      Continue = mProblemContext.master()->setSolution(mBestValue, *mIndividuals[mBestIndex], true);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  if (!Continue)
    {
      if (mLogVerbosity > 0)
        mMethodLog.enterLogEntry(COptLogEntry("Algorithm was terminated by user after initial population creation."));

      if (mProcessReport)
        mProcessReport.finishItem(mhGenerations);

      cleanup();
      return true;
    }

  size_t Stalled = 0;

  // ITERATE FOR gener GENERATIONS
  for (mCurrentGeneration = 2;
       mCurrentGeneration <= mGenerations && Continue;
       mCurrentGeneration++, Stalled++)
    {

      if (mStopAfterStalledGenerations != 0 && Stalled > mStopAfterStalledGenerations)
        break;

      if (Stalled > 50)
        {
          if (mLogVerbosity > 0)
            mMethodLog.enterLogEntry(
              COptLogEntry(
                "Generation " + std::to_string(mCurrentGeneration) +
                ": Fittest individual has not changed in the last " + std::to_string(Stalled - 1) +
                " generations. 40% of individuals randomized."
              ));

          Stalled = 0;

          Continue &= creation((size_t) 0.4 * mPopulationSize, (size_t) 0.8 * mPopulationSize);
        }

      // perturb the population a bit
      Continue &= creation((size_t)(mPopulationSize * 0.9), mPopulationSize);

      Continue &= replicate();

      // get the index of the fittest
      mBestIndex = fittest();

      if ((mBestIndex != C_INVALID_INDEX) && (mValues[mBestIndex] < mBestValue))
        {
          Stalled = 0;
          mBestValue = mValues[mBestIndex];

          Continue &= mProblemContext.master()->setSolution(mBestValue, *mIndividuals[mBestIndex], true);

          // We found a new best value lets report it.
          //if (mpReport) mpReport->printBody();
          mpParentTask->output(COutputInterface::DURING);
        }

      if (mProcessReport)
        Continue &= mProcessReport.progressItem(mhGenerations);

      //use a different output channel. It will later get a proper enum name
      mpParentTask->output(COutputInterface::MONITORING);
    }

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry("Algorithm finished.",
                   "Terminated after " + std::to_string(mCurrentGeneration - 1) + " of " +
                   std::to_string(mGenerations) + " generations."));

  if (mProcessReport)
    mProcessReport.finishItem(mhGenerations);

  cleanup();

  return true;
}

unsigned C_INT32 COptMethodDE::getMaxLogVerbosity() const
{
  return 1;
}
