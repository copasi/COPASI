// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodCoranaWalk.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/06/04 14:40:24 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
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

// written by Pedro Mendes, January 2012
// adapted from the Corana Simulated Annealing algorithm
// this does only the top level iteration of that algorithm

#include <cmath>

#include "copasi.h"

#include "COptMethodCoranaWalk.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "parameterFitting/CFitProblem.h"
#include "report/CCopasiObjectReference.h"
#include "randomGenerator/CRandom.h"

#define STORED 2
#define NS 5
#define K 1.0

COptMethodCoranaWalk::COptMethodCoranaWalk(const CCopasiContainer * pParent):
    COptMethod(CCopasiTask::optimization, CCopasiMethod::CoranaWalk, pParent)
{
  addParameter("Temperature", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0);
  addParameter("Iterations", CCopasiParameter::UINT, (unsigned C_INT32) 100);
  addParameter("Random Number Generator", CCopasiParameter::UINT, (unsigned C_INT32) CRandom::mt19937);
  addParameter("Seed", CCopasiParameter::UINT, (unsigned C_INT32) 0);

  initObjects();
}

COptMethodCoranaWalk::COptMethodCoranaWalk(const COptMethodCoranaWalk & src,
    const CCopasiContainer * pParent):
    COptMethod(src, pParent)
{initObjects();}

COptMethodCoranaWalk::~COptMethodCoranaWalk()
{cleanup();}

void COptMethodCoranaWalk::initObjects()
{
  addObjectReference("Current Iteration", mCurrentIteration, CCopasiObject::ValueInt);
}

bool COptMethodCoranaWalk::optimise()
{
  if (!initialize())
    {
      if (mpCallBack)
        mpCallBack->finishItem(mIterations);

      return false;
    }

  size_t i, j;

  size_t h, a;
  C_FLOAT64 xc, p, c, New, minstep;
  bool processing;

  // set the minimum step size as being the average of step sizes
  // or 100*DBL_EPSILON if average is zero
  for (i = 0, minstep = 0.0; i < mVariableSize; i++)
    {
      minstep += mCurrent[i];
    }

  if (minstep > std::numeric_limits< C_FLOAT64 >::epsilon())
    minstep /= i;
  else
    minstep = 100 * std::numeric_limits< C_FLOAT64 >::epsilon();

  // initial point is first guess but we have to make sure that we
  // are within the parameter domain
  for (i = 0; i < mVariableSize; i++)
    {
      const COptItem & OptItem = *(*mpOptItem)[i];

      switch (OptItem.checkConstraint())
        {
          case - 1:
            mCurrent[i] = *OptItem.getLowerBoundValue();
            break;

          case 1:
            mCurrent[i] = *OptItem.getUpperBoundValue();
            break;

          case 0:
            mCurrent[i] = OptItem.getStartValue();
            break;
        }

      (*(*mpSetCalculateVariable)[i])(mCurrent[i]);

      // The step must not contain any zeroes
      mStep[i] = std::max(fabs(mCurrent[i]), minstep);
    }

  // find the objective function value at the start
  mCurrentValue = evaluate();
  // count it
  mCurrentIteration = 1;

  if (!isnan(mEvaluationValue))
    {
      // and store that value
      mBestValue = mEvaluationValue;
      mContinue &= mpOptProblem->setSolution(mBestValue, mCurrent);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);

      if (mpCallBack)
        mContinue &= mpCallBack->progressItem(mhIterations);
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
              (*(*mpSetCalculateVariable)[h])(New);

              // Check all parametric constraints
              if (!mpOptProblem->checkParametricConstraints())
                {
                  // Undo since not accepted
                  (*(*mpSetCalculateVariable)[h])(mCurrent[h]);
                  continue;
                }

              // evaluate the function
              evaluate();
              // count it
              mCurrentIteration++;

              if (mpCallBack)
                mContinue &= mpCallBack->progressItem(mhIterations);

              // Check all functional constraints
              if (!mpOptProblem->checkFunctionalConstraints())
                {
                  // Undo since not accepted
                  (*(*mpSetCalculateVariable)[h])(mCurrent[h]);

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
                      mContinue &= mpOptProblem->setSolution(mBestValue, mCurrent);

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
                    (*(*mpSetCalculateVariable)[h])(mCurrent[h]);
                }

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
          mCurrent = mpOptProblem->getSolutionVariables();

          for (a = 0; a < mVariableSize; a++)
            (*(*mpSetCalculateVariable)[a])(mCurrent[a]);

          mCurrentValue = mBestValue;
        }

      if (mpCallBack)
        mContinue &= mpCallBack->progressItem(mhIterations);
    }
  while (processing && mContinue);

  if (mpCallBack)
    mpCallBack->finishItem(mhIterations);

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

  mContinue &= mpOptProblem->calculate();
  mEvaluationValue = mpOptProblem->getCalculateValue();

  // When we leave the either functional domain
  // we set the objective value +Inf
  if (!mpOptProblem->checkFunctionalConstraints())
    mEvaluationValue = std::numeric_limits<C_FLOAT64>::infinity();

  return mEvaluationValue;
}

bool COptMethodCoranaWalk::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mTemperature = * getValue("Temperature").pUDOUBLE;
  mIterations = * getValue("Iterations").pUINT;
  mpRandom =
    CRandom::createGenerator(* (CRandom::Type *) getValue("Random Number Generator").pUINT,
                             * getValue("Seed").pUINT);

  mCurrentIteration = 0;

  if (mpCallBack)
    mhIterations =
      mpCallBack->addItem("Iterations",
                          mCurrentIteration, &mIterations);

  mBestValue = std::numeric_limits<C_FLOAT64>::infinity();
  mContinue = true;

  mVariableSize = mpOptItem->size();

  mCurrent.resize(mVariableSize);
  mStep.resize(mVariableSize);
  mAccepted.resize(mVariableSize);

  return true;
}
