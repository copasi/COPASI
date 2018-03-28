// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "COptMethodSteepestDescent.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "FminBrent.h"

#include "copasi/core/CDataObjectReference.h"

COptMethodSteepestDescent::COptMethodSteepestDescent(const CDataContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType):
  COptMethod(pParent, methodType, taskType),
  mIterations(100),
  mTolerance(1e-6),
  mContinue(true),
  mBestValue(std::numeric_limits< C_FLOAT64 >::infinity()),
  mValue(0.0),
  mVariableSize(0),
  mIndividual(0),
  mGradient(0),
  mpDescent(new FDescentTemplate<COptMethodSteepestDescent>(this, &COptMethodSteepestDescent::descentLine)),
  mCurrentIteration(0)
{
  addParameter("Iteration Limit", CCopasiParameter::UINT, (unsigned C_INT32) 100);
  addParameter("Tolerance", CCopasiParameter::DOUBLE, (C_FLOAT64) 1e-6);

  addParameter("Log Verbosity", CCopasiParameter::UINT, (unsigned C_INT32) 0);

}

COptMethodSteepestDescent::COptMethodSteepestDescent(const COptMethodSteepestDescent & src,
    const CDataContainer * pParent): COptMethod(src, pParent),
  mIterations(src.mIterations),
  mTolerance(src.mTolerance),
  mContinue(src.mContinue),
  mBestValue(src.mBestValue),
  mValue(src.mValue),
  mVariableSize(src.mVariableSize),
  mIndividual(src.mIndividual),
  mGradient(src.mGradient),
  mpDescent(new FDescentTemplate<COptMethodSteepestDescent>(this, &COptMethodSteepestDescent::descentLine)),
  mCurrentIteration(src.mCurrentIteration)
{}

COptMethodSteepestDescent::~COptMethodSteepestDescent()
{
  pdelete(mpDescent);

  cleanup();
}

bool COptMethodSteepestDescent::optimise()
{
  if (!initialize()) return false;

  mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_start).with("OD.Steepest.Descent"));

  size_t i, k;
  C_FLOAT64 tmp, x0, alpha, mn, mx, fmn, fmx;
  bool calc_grad;

  // initial point is first guess but we have to make sure that we
  // are within the parameter domain
  bool pointInParameterDomain = true;

  for (i = 0; i < mVariableSize; i++)
    {
      const COptItem & OptItem = *(*mpOptItem)[i];

      switch (OptItem.checkConstraint(OptItem.getStartValue()))
        {
          case - 1:
            mIndividual[i] = *OptItem.getLowerBoundValue();
            pointInParameterDomain = false;
            break;

          case 1:
            mIndividual[i] = *OptItem.getUpperBoundValue();
            pointInParameterDomain = false;
            break;

          case 0:
            mIndividual[i] = OptItem.getStartValue();
            break;
        }

      *mContainerVariables[i] = mIndividual[i];
    }

  if (!pointInParameterDomain) mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_initial_point_out_of_domain));

  fmx = mBestValue = evaluate();

  mContinue = mpOptProblem->setSolution(mBestValue, mIndividual);

  // We found a new best value lets report it.
  //if (mpReport) mpReport->printBody();
  mpParentTask->output(COutputInterface::DURING);

  bool SolutionFound = false;

  for (mCurrentIteration = 0; mCurrentIteration < mIterations && mContinue && !SolutionFound; mCurrentIteration++)
    {
      // calculate the direction of steepest descent
      // by central finite differences
      gradient();
      // minimise the function in this direction
      // find brackets for the minimisation
      //  mn = 0.0; md = 1.0;
      //  mnbrak(&mn, &md, &mx, &fmn, &fmd, &fmx, descent_line);
      // make sure that no parameter will exceed its bounds
      x0 = std::numeric_limits< C_FLOAT64 >::max();

      for (i = 0; i < mVariableSize; i++)
        {
          if (fabs(mGradient[i]) > std::numeric_limits< C_FLOAT64 >::epsilon())
            {
              if (mGradient[i] > 0)
                {
                  tmp = *(*mpOptItem)[i]->getUpperBoundValue();
                }

              else
                {
                  tmp = *(*mpOptItem)[i]->getLowerBoundValue();
                }

              // calculate the size of the largest jump
              tmp = (tmp - mIndividual[i]) / mGradient[i];

              // keep it if it is the smallest
              if (tmp < x0) x0 = tmp;
            }
          else mGradient[i] = 0.0;
        }

      if (x0 < mTolerance) x0 = mTolerance;

      // we will move at a rate of 1/10 this size
      mn = mx = alpha = 0.0;

      for (k = 0, calc_grad = false; (k < 9) && !calc_grad && !SolutionFound; k++)
        {
          // set the minimum to the last successful step
          mn = mx;
          fmn = fmx;
          // increment alpha
          alpha += 0.1 * x0;
          // set the maximum to it
          mx = alpha;

          // take one step in that direction
          fmx = descentLine(alpha);

          fmx = evaluate();

          // if this was an upward step find the minimum
          if (fmx > fmn)
            {
              //md = mn + (mx-mn)/2;
              //Brent(mn, md, mx, descent_line, &alpha, &tmp, 1e-6, 50);

              FminBrent(mn, mx, mpDescent, &alpha, &tmp, mTolerance, 5);

              // take one step in that direction
              fmx = descentLine(alpha);

              // time to evaluate the new steepest descent direction
              calc_grad = true;
            }

          if (fabs(fmx - mBestValue) < mTolerance)
            SolutionFound = true;
        }

      for (i = 0; i < mVariableSize; i++)
        mIndividual[i] = *(*mpOptItem)[i]->getObjectValue();

      if (fmx < mBestValue)
        {
          mBestValue = fmx;

          mContinue = mpOptProblem->setSolution(mBestValue, mIndividual);

          // We found a new best value lets report it.
          //if (mpReport) mpReport->printBody();
          mpParentTask->output(COutputInterface::DURING);
        }
    }

  mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_finish_x_of_max_iter).iter(mCurrentIteration).with(mIterations));

  return true;
}

bool COptMethodSteepestDescent::cleanup()
{
  // pdelete all used variables
  return true;
}

bool COptMethodSteepestDescent::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mLogVerbosity = getValue< unsigned C_INT32 >("Log Verbosity");

  mIterations = getValue< unsigned C_INT32 >("Iteration Limit");
  mTolerance = getValue< C_FLOAT64 >("Tolerance");

  mContinue = true;
  mVariableSize = mpOptItem->size();
  mIndividual.resize(mVariableSize);
  mGradient.resize(mVariableSize);

  mBestValue = std::numeric_limits<C_FLOAT64>::infinity();

  return true;
}

void COptMethodSteepestDescent::gradient()
{

  C_FLOAT64 **ppContainerVariable = mContainerVariables.array();
  C_FLOAT64 **ppContainerVariableEnd = ppContainerVariable + mVariableSize;
  C_FLOAT64 * pGradient = mGradient.array();

  C_FLOAT64 y;
  C_FLOAT64 x;

  y = evaluate();

  for (; ppContainerVariable != ppContainerVariableEnd; ++ppContainerVariable, ++pGradient)
    {
      if ((x = **ppContainerVariable) != 0.0)
        {
          **ppContainerVariable = x * 1.001;
          *pGradient = (y - evaluate()) / (x * 0.001);
        }

      else
        {
          **ppContainerVariable = 1e-7;
          *pGradient = (y - evaluate()) / 1e-7;
        }

      **ppContainerVariable = x;
    }
}

C_FLOAT64 COptMethodSteepestDescent::descentLine(const C_FLOAT64 & x)
{
  C_FLOAT64 **ppContainerVariable = mContainerVariables.array();
  C_FLOAT64 **ppContainerVariableEnd = ppContainerVariable + mVariableSize;
  C_FLOAT64 * pGradient = mGradient.array();
  C_FLOAT64 * pIndividual = mIndividual.array();

  for (; ppContainerVariable != ppContainerVariableEnd; ++ppContainerVariable, ++pIndividual, ++pGradient)
    {
      **ppContainerVariable = *pIndividual + x **pGradient;
    }

  return evaluate();
}

// evaluate the fitness of one individual
const C_FLOAT64 & COptMethodSteepestDescent::evaluate()
{
  // evaluate the fitness
  mContinue = mpOptProblem->calculate();

  mValue = mpOptProblem->getCalculateValue();

  // when we leave the either the parameter or functional domain
  // we penalize the objective value by forcing it to be larger
  // than the best value recorded so far.
  if (mValue < mBestValue &&
      (!mpOptProblem->checkParametricConstraints() ||
       !mpOptProblem->checkFunctionalConstraints()))
    mValue = mBestValue + fabs(mBestValue - mValue);

  return mValue;
}

void COptMethodSteepestDescent::initObjects()
{
  addObjectReference("Current Iteration", mCurrentIteration, CDataObject::ValueInt);
}

unsigned C_INT32 COptMethodSteepestDescent::getMaxLogVerbosity() const
{
  return 0;
}
