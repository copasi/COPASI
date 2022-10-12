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

// written by Pedro Mendes, January 2012
// adapted from the Corana Simulated Annealing algorithm
// this does only the top level iteration of that algorithm

#include <cmath>

#include "copasi/copasi.h"

#include "COptMethodCoranaWalk.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "copasi/parameterFitting/CFitProblem.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/randomGenerator/CRandom.h"

#define STORED 2
#define NS 5
#define K 1.0

COptMethodCoranaWalk::COptMethodCoranaWalk(const CDataContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType)
  : COptMethod(pParent, methodType, taskType, false)
  , mTemperature(1.0)
  , mhIterations(C_INVALID_INDEX)
  , mIterations(100)
  , mCurrentIteration(0)
  , mpRandom(NULL)
  , mVariableSize(0)
  , mBestValue(std::numeric_limits< C_FLOAT64 >::infinity())
  , mEvaluationValue(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
  , mContinue(true)
  , mCurrent()
  , mCurrentValue(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
  , mStep()
  , mAccepted()
{
  assertParameter("Iterations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 100);
  assertParameter("Temperature", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.0);
  assertParameter("Random Number Generator", CCopasiParameter::Type::UINT, (unsigned C_INT32) CRandom::mt19937, eUserInterfaceFlag::editable);
  assertParameter("Seed", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);

  initObjects();
}

COptMethodCoranaWalk::COptMethodCoranaWalk(const COptMethodCoranaWalk & src,
    const CDataContainer * pParent)
  : COptMethod(src, pParent)
  , mTemperature(src.mTemperature)
  , mhIterations(C_INVALID_INDEX)
  , mIterations(src.mIterations)
  , mCurrentIteration(src.mCurrentIteration)
  , mpRandom(NULL)
  , mVariableSize(src.mVariableSize)
  , mBestValue(src.mBestValue)
  , mEvaluationValue(src.mEvaluationValue)
  , mContinue(src.mContinue)
  , mCurrent(src.mCurrent)
  , mCurrentValue(src.mCurrentValue)
  , mStep(src.mStep)
  , mAccepted(src.mAccepted)
{initObjects();}

COptMethodCoranaWalk::~COptMethodCoranaWalk()
{cleanup();}

void COptMethodCoranaWalk::initObjects()
{
  addObjectReference("Current Iteration", mCurrentIteration, CDataObject::ValueInt);
}

bool COptMethodCoranaWalk::optimise()
{
  if (!initialize())
    {
      if (mProcessReport)
        mProcessReport.finishItem(mIterations);

      return false;
    }

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(COptLogEntry("Algorithm started."));

  size_t i, j;

  size_t h, a;
  C_FLOAT64 xc, p, c, New, minstep;
  bool processing;

  // set the minimum step size as being the average of step sizes
  // or 100*DBL_EPSILON if average is zero
  for (i = 0, minstep = 0.0; i < mVariableSize; i++)
    {
      minstep += fabs(mCurrent[i]);
    }

  if (minstep > std::numeric_limits< C_FLOAT64 >::epsilon())
    minstep /= mVariableSize;
  else
    minstep = 100 * std::numeric_limits< C_FLOAT64 >::epsilon();

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(COptLogEntry("Minimal step size is " + std::to_string(minstep) + "."));

  // initial point is first guess but we have to make sure that we
  // are within the parameter domain
  bool pointInParameterDomain = true;

  for (i = 0; i < mVariableSize; i++)
    {
      const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[i];

      switch (OptItem.checkConstraint(OptItem.getStartValue()))
        {
          case - 1:
            mCurrent[i] = *OptItem.getLowerBoundValue();
            pointInParameterDomain = false;
            break;

          case 1:
            mCurrent[i] = *OptItem.getUpperBoundValue();
            pointInParameterDomain = false;
            break;

          case 0:
            mCurrent[i] = OptItem.getStartValue();
            break;
        }

      *mProblemContext.master()->getContainerVariables(true)[i] = mCurrent[i];

      // The step must not contain any zeroes
      mStep[i] = std::max(fabs(mCurrent[i]), minstep);
    }

  if (!pointInParameterDomain && (mLogVerbosity > 0))
    mMethodLog.enterLogEntry(COptLogEntry("Initial point outside parameter domain."));

  // find the objective function value at the start
  mCurrentValue = evaluate();
  // count it
  mCurrentIteration = 1;

  if (!std::isnan(mEvaluationValue))
    {
      // and store that value
      mBestValue = mEvaluationValue;
      mContinue &= mProblemContext.master()->setSolution(mBestValue, mCurrent, true);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
      mpParentTask->output(COutputInterface::MONITORING);

      if (mProcessReport)
        mContinue &= mProcessReport.progressItem(mhIterations);
    }

  mAccepted = 0;

  processing = true; // we want to do some work

  do
    {
      for (j = 0; j < NS && mContinue && processing; j++) // adjustment in all directions
        {
          for (h = 0; h < mVariableSize && mContinue && processing; h++) // adjustment in one direction
            {
              // Calculate the step
              xc = (2.0 * mpRandom->getRandomCC() - 1) * mStep[h];
              New = mCurrent[h] + xc;

              // Set the new parameter value
              *mProblemContext.master()->getContainerVariables(true)[h] = New;

              // Check all parametric constraints
              if (!mProblemContext.master()->checkParametricConstraints())
                {
                  // Undo since not accepted
                  *mProblemContext.master()->getContainerVariables(true)[h] = mCurrent[h];
                  continue;
                }

              // evaluate the function
              evaluate();
              // count it
              mCurrentIteration++;

              if (mProcessReport)
                mContinue &= mProcessReport.progressItem(mhIterations);

              // Check all functional constraints
              if (!mProblemContext.master()->checkFunctionalConstraints())
                {
                  // Undo since not accepted
                  *mProblemContext.master()->getContainerVariables(true)[h] = mCurrent[h];

                  continue;
                }

              // here we have a completely feasible point
              // keep if energy is reduced
              if (mEvaluationValue <= mCurrentValue)
                {
                  // only one value has changed...
                  mCurrent[h] = New;
                  mCurrentValue = mEvaluationValue;
                  i++;  // a new point
                  mAccepted[h]++; // a new point in this coordinate

                  if (mCurrentValue < mBestValue)
                    {
                      // and store that value
                      mBestValue = mEvaluationValue;
                      mContinue &= mProblemContext.master()->setSolution(mBestValue, mCurrent, true);

                      // We found a new best value lets report it.
                      mpParentTask->output(COutputInterface::DURING);
                    }
                }
              else
                {
                  // keep with probability p, if energy is increased
                  p = exp((mCurrentValue - mEvaluationValue) / (K * mTemperature));

                  if (p > mpRandom->getRandomCO())
                    {
                      // only one value has changed...
                      mCurrent[h] = New;
                      mCurrentValue = mEvaluationValue;
                      i++;  // a new point
                      mAccepted[h]++; // a new point in this coordinate
                    }
                  else
                    // Undo since not accepted
                    *mProblemContext.master()->getContainerVariables(true)[h] = mCurrent[h];
                }

              mpParentTask->output(COutputInterface::MONITORING);

              // check if it is time to stop
              if (mCurrentIteration == mIterations) processing = false;
            }
        }

      // update the step sizes
      for (a = 0; a < mVariableSize; a++)
        {
          c = (C_FLOAT64) mAccepted[a] / (C_FLOAT64) NS;

          if (c > 0.6)
            mStep[a] *= 1 + 5 * (c - 0.6);
          else if (c < 0.4)
            mStep[a] /= 1 + 5 * (0.4 - c);

          mAccepted[a] = 0;
        }

      // the equilibrium energy

      if (processing)
        {
          mCurrent = mProblemContext.master()->getSolutionVariables(true);

          for (a = 0; a < mVariableSize; a++)
            *mProblemContext.master()->getContainerVariables(true)[a] = mCurrent[a];

          mCurrentValue = mBestValue;
        }

      if (mProcessReport)
        mContinue &= mProcessReport.progressItem(mhIterations);
    }
  while (processing && mContinue);

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry("Algorithm finished.",
                   "Terminated after " + std::to_string(mCurrentIteration) + " of " +
                   std::to_string(mIterations) + " iterations."));

  if (mProcessReport)
    mProcessReport.finishItem(mhIterations);

  return true;
}

bool COptMethodCoranaWalk::cleanup()
{
  return true;
}

const C_FLOAT64 & COptMethodCoranaWalk::evaluate()
{
  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  mContinue &= mProblemContext.master()->calculate();
  mEvaluationValue = mProblemContext.master()->getCalculateValue();

  // When we leave the either functional domain
  // we set the objective value +Inf
  if (!mProblemContext.master()->checkFunctionalConstraints())
    mEvaluationValue = std::numeric_limits<C_FLOAT64>::infinity();

  return mEvaluationValue;
}

bool COptMethodCoranaWalk::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mTemperature = getValue< C_FLOAT64 >("Temperature");
  mIterations = getValue< unsigned C_INT32 >("Iterations");
  mpRandom =
    CRandom::createGenerator((CRandom::Type) getValue< unsigned C_INT32 >("Random Number Generator"),
                             getValue< unsigned C_INT32 >("Seed"));

  mCurrentIteration = 0;

  if (mProcessReport)
    mhIterations =
      mProcessReport.addItem("Iterations",
                             mCurrentIteration, &mIterations);

  mBestValue = std::numeric_limits<C_FLOAT64>::infinity();
  mContinue = true;

  mVariableSize = mProblemContext.master()->getOptItemList(true).size();

  mCurrent.resize(mVariableSize);
  mStep.resize(mVariableSize);
  mAccepted.resize(mVariableSize);

  return true;
}

unsigned C_INT32 COptMethodCoranaWalk::getMaxLogVerbosity() const
{
  return 0;
}

C_FLOAT64 COptMethodCoranaWalk::getBestValue() const
{
  return mBestValue;
}

C_FLOAT64 COptMethodCoranaWalk::getCurrentValue() const
{
  return mBestValue;
}

const CVector< C_FLOAT64 > * COptMethodCoranaWalk::getBestParameters() const
{
  return &mCurrent;
}

const CVector< C_FLOAT64 > * COptMethodCoranaWalk::getCurrentParameters() const
{
  return &mCurrent;
}
