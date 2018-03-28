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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "COptMethodTruncatedNewton.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "parameterFitting/CFitProblem.h"
#include "copasi/core/CDataObjectReference.h"

COptMethodTruncatedNewton::COptMethodTruncatedNewton(const CDataContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType):
  COptMethod(pParent, methodType, taskType),
  mpTruncatedNewton(new FTruncatedNewtonTemplate<COptMethodTruncatedNewton>(this, &COptMethodTruncatedNewton::sFun)),
  mpCTruncatedNewton(new CTruncatedNewton())
{

  addParameter("Log Verbosity", CCopasiParameter::UINT, (unsigned C_INT32) 0);

  initObjects();
}

COptMethodTruncatedNewton::COptMethodTruncatedNewton(const COptMethodTruncatedNewton & src,
    const CDataContainer * pParent):
  COptMethod(src, pParent),
  mpTruncatedNewton(new FTruncatedNewtonTemplate<COptMethodTruncatedNewton>(this, &COptMethodTruncatedNewton::sFun)),
  mpCTruncatedNewton(new CTruncatedNewton())
{initObjects();}

COptMethodTruncatedNewton::~COptMethodTruncatedNewton()
{
  pdelete(mpTruncatedNewton);
  pdelete(mpCTruncatedNewton);
  cleanup();
}

void COptMethodTruncatedNewton::initObjects()
{
  addObjectReference("Current Iteration", mIteration, CDataObject::ValueInt);
}

bool COptMethodTruncatedNewton::optimise()
{
  if (!initialize()) return false;

  mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_start).with("OD.Truncated.Newton"));

  C_FLOAT64 fest;
  C_INT lw, ierror = 0;
  lw = 14 * mVariableSize;

  CVector< C_FLOAT64 > up(mVariableSize);
  CVector< C_FLOAT64 > low(mVariableSize);
  CVector< C_INT > iPivot(mVariableSize);
  CVector< C_FLOAT64 > dwork(lw);

  up = std::numeric_limits< C_FLOAT64 >::max();
  low = - std::numeric_limits< C_FLOAT64 >::max();

  // initial point is the first guess but we have to make sure that
  // we are within the parameter domain
  C_INT i, repeat;
  bool pointInParameterDomain = true;

  for (i = 0; i < mVariableSize; i++)
    {
      const COptItem & OptItem = *(*mpOptItem)[i];

      // :TODO: In COPASI the bounds are not necessarry fixed.
      // Since evaluate checks for boundaries and constraints this is not
      // needed. The question remaining is how does tnbc_ handle unconstraint problems?
      // low[i] = *OptItem.getLowerBoundValue();
      // up[i] = *OptItem.getUpperBoundValue();

      mCurrent[i] = OptItem.getStartValue();

      switch (OptItem.checkConstraint(mCurrent[i]))
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
            break;
        }

      // set the value
      *mContainerVariables[i] = (mCurrent[i]);
    }

  if (!pointInParameterDomain) mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_initial_point_out_of_domain));

  // Report the first value as the current best
  mBestValue = evaluate();
  mBest = mCurrent;
  mContinue = mpOptProblem->setSolution(mBestValue, mBest);

  repeat = 0;

  while (repeat < 10 && mContinue)
    {
      repeat++;

      // estimate minimum is 1/10 initial function value
      fest = (1 - pow(0.9, (C_FLOAT64) repeat)) * mEvaluationValue;
      ierror = 0;

      // minimise
      try
        {
          mpCTruncatedNewton->tnbc_(&ierror, &mVariableSize, mCurrent.array(), &fest, mGradient.array(), dwork.array(),
                                    &lw, mpTruncatedNewton, low.array(), up.array(), iPivot.array());
          mEvaluationValue = fest;
        }

      // This signals that the user opted to interupt
      catch (bool)
        {
          break;
        }

      if (ierror < 0)
        fatalError(); // Invalid parameter values.

      // The way the method is currently implemented may lead to parameters just outside the boundaries.
      // We need to check whether the current value is within the boundaries or whether the corrected
      // leads to an improved solution.

      bool withinBounds = true;

      for (i = 0; i < mVariableSize; i++)
        {
          const COptItem & OptItem = *(*mpOptItem)[i];

          //force it to be within the bounds
          switch (OptItem.checkConstraint(mCurrent[i]))
            {
              case - 1:
                withinBounds = false;
                mCurrent[i] = *OptItem.getLowerBoundValue();
                break;

              case 1:
                withinBounds = false;
                mCurrent[i] = *OptItem.getUpperBoundValue();
                break;

              case 0:
                break;
            }

          *mContainerVariables[i] = (mCurrent[i]);
        }

      evaluate();

      // Is the corrected value better than solution?
      if (mEvaluationValue < mBestValue)
        {
          // We found a new best value lets report it.
          // and store that value
          mBest = mCurrent;
          mBestValue = mEvaluationValue;

          mContinue = mpOptProblem->setSolution(mBestValue, mBest);

          // We found a new best value lets report it.
          mpParentTask->output(COutputInterface::DURING);
        }

      // We found a solution
      if (withinBounds)
        break;

      // Choosing another starting point will be left to the user
#ifdef XXXX

      // Try another starting point
      for (i = 0; i < mVariableSize; i++)
        {
          mCurrent[i] *= 1.2;
          const COptItem & OptItem = *(*mpOptItem)[i];

          //force it to be within the bounds
          switch (OptItem.checkConstraint(mCurrent[i]))
            {
              case - 1:
                mCurrent[i] = *OptItem.getLowerBoundValue();
                break;

              case 1:
                mCurrent[i] = *OptItem.getUpperBoundValue();
                break;

              case 0:
                break;
            }

          *mContainerVariables[i] = (mCurrent[i]);
        }

      evaluate();

      // Check whether we improved
      if (mEvaluationValue < mBestValue)
        {
          // We found a new best value lets report it.
          // and store that value
          mBest = mCurrent;
          mBestValue = mEvaluationValue;

          mContinue = mpOptProblem->setSolution(mBestValue, mBest);

          // We found a new best value lets report it.
          mpParentTask->output(COutputInterface::DURING);
        }

#endif // XXXX

      if (mLogVerbosity >= 1) mMethodLog.enterLogItem(COptLogItem(COptLogItem::TN_next_repeat).with(repeat));
    }

  mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_finish));

  return true;
}

bool COptMethodTruncatedNewton::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mLogVerbosity = getValue< unsigned C_INT32 >("Log Verbosity");

  mVariableSize = (C_INT) mpOptItem->size();
  mCurrent.resize(mVariableSize);
  mBest.resize(mVariableSize);

  mContinue = true;
  mBestValue = std::numeric_limits<C_FLOAT64>::infinity();
  mGradient.resize(mVariableSize);

  return true;
}

bool COptMethodTruncatedNewton::cleanup()
{
  return true;
}

// callback function, evaluate the value of the objective function and its gradient
//(by finite differences), translated by f2c, edited by Pedro and then modified for COPASI by Joseph
C_INT COptMethodTruncatedNewton::sFun(C_INT *n, C_FLOAT64 *x, C_FLOAT64 *f, C_FLOAT64 *g)
{
  C_INT i;

  // set the parameter values
  for (i = 0; i < *n; i++)
    *mContainerVariables[i] = (x[i]);

  //carry out the function evaluation
  *f = evaluate();

  // Check whether we improved
  if (mEvaluationValue < mBestValue)
    {
      // We found a new best value lets report it.
      // and store that value
      for (i = 0; i < *n; i++)
        mBest[i] = x[i];

      mBestValue = mEvaluationValue;
      mContinue = mpOptProblem->setSolution(mBestValue, mBest);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  // Calculate the gradient
  for (i = 0; i < *n && mContinue; i++)
    {
      if (x[i] != 0.0)
        {
          *mContainerVariables[i] = (x[i] * 1.001);
          g[i] = (evaluate() - *f) / (x[i] * 0.001);
        }

      else
        {
          *mContainerVariables[i] = (1e-7);
          g[i] = (evaluate() - *f) / 1e-7;
        }

      *mContainerVariables[i] = (x[i]);
    }

  if (!mContinue)
    throw bool(mContinue);

  return 0;
}

const C_FLOAT64 & COptMethodTruncatedNewton::evaluate()
{
  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.
  mContinue = mpOptProblem->calculate();
  mEvaluationValue = mpOptProblem->getCalculateValue();

  // when we leave the either the parameter or functional domain
  // we penalize the objective value by forcing it to be larger
  // than the best value recorded so far.
  if (mEvaluationValue < mBestValue &&
      (!mpOptProblem->checkParametricConstraints() ||
       !mpOptProblem->checkFunctionalConstraints()))
    mEvaluationValue = mBestValue + mBestValue - mEvaluationValue;

  return mEvaluationValue;
}

unsigned C_INT32 COptMethodTruncatedNewton::getMaxLogVerbosity() const
{
  return 1;
}
