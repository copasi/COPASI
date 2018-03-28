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

#include "COptMethodPraxis.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "parameterFitting/CFitProblem.h"
#include "copasi/core/CDataObjectReference.h"

COptMethodPraxis::COptMethodPraxis(const CDataContainer * pParent,
                                   const CTaskEnum::Method & methodType,
                                   const CTaskEnum::Task & taskType):
  COptMethod(pParent, methodType, taskType),
  mpPraxis(new FPraxisTemplate<COptMethodPraxis>(this, &COptMethodPraxis::evaluateFunction)),
  mpCPraxis(new CPraxis())
{
  addParameter("Tolerance", CCopasiParameter::DOUBLE, (C_FLOAT64) 1.e-005);

  addParameter("Log Verbosity", CCopasiParameter::UINT, (unsigned C_INT32) 0);

  initObjects();
}

COptMethodPraxis::COptMethodPraxis(const COptMethodPraxis & src,
                                   const CDataContainer * pParent):
  COptMethod(src, pParent),
  mpPraxis(new FPraxisTemplate<COptMethodPraxis>(this, &COptMethodPraxis::evaluateFunction)),
  mpCPraxis(new CPraxis())
{initObjects();}

COptMethodPraxis::~COptMethodPraxis()
{
  pdelete(mpPraxis);
  pdelete(mpCPraxis);
  cleanup();
}

void COptMethodPraxis::initObjects()
{
  addObjectReference("Current Iteration", mIteration, CDataObject::ValueInt);
}

bool COptMethodPraxis::optimise()
{
  if (!initialize()) return false;

  mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_start).with("OD.Praxis"));

  C_INT i;
  C_INT prin = 0;
  C_FLOAT64 tmp = 0.0;
  C_FLOAT64 machep, stepmx, d1, d2;

  // initial point is the first guess but we have to make sure that
  // we are within the parameter domain

  bool pointInParameterDomain = true;

  for (i = 0; i < mVariableSize; i++)
    {
      const COptItem & OptItem = *(*mpOptItem)[i];
      mCurrent[i] = OptItem.getStartValue();

      //force it to be within the bounds
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
        }

      //set the value
      *mContainerVariables[i] = (mCurrent[i]);
    }

  if (!pointInParameterDomain) mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_initial_point_out_of_domain));

  // Report the first value as the current best
  mBestValue = evaluate();
  mBest = mCurrent;
  mContinue = mpOptProblem->setSolution(mBestValue, mBest);

  // We found a new best value lets report it.
  mpParentTask->output(COutputInterface::DURING);

  //estimate the machine epsilon
  d1 = 1.0;

  do
    {
      d1 /= 2.0;
      d2 = d1 + 1.;
    }
  while (d2 != 1.0);

  machep = d1 * 2.0;

  //estimate the maximum step size
  stepmx = 0.6;

  //carry out the minimisation
  try
    {
      mpCPraxis->praxis_(&mTolerance, &machep, &stepmx, &mVariableSize, &prin, mCurrent.array(), mpPraxis, &tmp);
    }
  catch (bool)
    {}

  mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_finish));

  return true;
}

bool COptMethodPraxis::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mLogVerbosity = getValue< unsigned C_INT32 >("Log Verbosity");

  mTolerance = getValue< C_FLOAT64 >("Tolerance");
  mIteration = 0;

  mVariableSize = (C_INT) mpOptItem->size();
  mCurrent.resize(mVariableSize);
  mBest.resize(mVariableSize);

  mContinue = true;

  return true;
}

bool COptMethodPraxis::cleanup()
{
  return true;
}

// evaluate the value of the objective function
const C_FLOAT64 & COptMethodPraxis::evaluateFunction(C_FLOAT64 *x, C_INT *n)
{
  C_INT i;

  for (i = 0; i < *n; i++)
    *mContainerVariables[i] = (x[i]);

  //carry out the function evaluation
  evaluate();

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

  if (!mContinue)
    throw bool(mContinue);

  return mEvaluationValue;
}

const C_FLOAT64 & COptMethodPraxis::evaluate()
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

unsigned C_INT32 COptMethodPraxis::getMaxLogVerbosity() const
{
  return 0;
}
