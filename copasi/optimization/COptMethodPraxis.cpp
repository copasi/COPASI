// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/copasi.h"

#include "COptMethodPraxis.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "copasi/parameterFitting/CFitProblem.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/sbml/SBMLImporter.h"

COptMethodPraxis::COptMethodPraxis(const CDataContainer * pParent,
                                   const CTaskEnum::Method & methodType,
                                   const CTaskEnum::Task & taskType)
  : COptMethod(pParent, methodType, taskType, false)
  , mTolerance(1.e-005)
  , mIteration(0)
  , mhIteration()
  , mVariableSize(0)
  , mCurrent()
  , mBest()
  , mEvaluationValue(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
  , mpPraxis(new FPraxisTemplate< COptMethodPraxis >(this, &COptMethodPraxis::evaluateFunction))
  , mPraxis()
{
  assertParameter("Tolerance", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) 1.e-005);

  initObjects();
}

COptMethodPraxis::COptMethodPraxis(const COptMethodPraxis & src,
                                   const CDataContainer * pParent)
  : COptMethod(src, pParent, false)
  , mTolerance(1.e-005)
  , mIteration(src.mIteration)
  , mhIteration(src.mhIteration)
  , mVariableSize(src.mVariableSize)
  , mCurrent(src.mCurrent)
  , mBest(src.mBest)
  , mEvaluationValue(src.mEvaluationValue)
  , mpPraxis(new FPraxisTemplate< COptMethodPraxis >(this, &COptMethodPraxis::evaluateFunction))
  , mPraxis()
{
  initObjects();
}

COptMethodPraxis::~COptMethodPraxis()
{
  pdelete(mpPraxis);
  cleanup();
}

void COptMethodPraxis::initObjects()
{
  addObjectReference("Current Iteration", mIteration, CDataObject::ValueInt);
}

bool COptMethodPraxis::optimise()
{
  if (!initialize()) return false;

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry(
        "Algorithm started.",
        "For more information about this method see: http://copasi.org/Support/User_Manual/Methods/Optimization_Methods/Praxis/"
      )
    );

  C_INT32 i;
  C_INT32 prin = 0;
  C_FLOAT64 tmp = 0.0;
  C_FLOAT64 machep, stepmx, d1, d2;

  // initial point is the first guess but we have to make sure that
  // we are within the parameter domain

  bool pointInParameterDomain = true;
  const std::vector< COptItem * > & OptItemList = mProblemContext.active()->getOptItemList(true);

  for (i = 0; i < mVariableSize; i++)
    {
      COptItem & OptItem = *OptItemList[i];
      mCurrent[i] = OptItem.getStartValue();
      pointInParameterDomain &= OptItem.setItemValue(mCurrent[i], COptItem::CheckPolicyFlag::All);
      pointInParameterDomain &= (mCurrent[i] == OptItem.getStartValue());
    }

  if (!pointInParameterDomain && (mLogVerbosity > 0))
    mMethodLog.enterLogEntry(COptLogEntry("Initial point outside parameter domain."));

  // Report the first value as the current best
  mEvaluationValue = evaluate(EvaluationPolicyFlag::All);

  if (!std::isnan(mEvaluationValue))
    setSolution(mEvaluationValue, mCurrent, true);

  mBest = mCurrent;
  mCountWithinTolerance = 0;

  // We found a new best value lets report it.
  mpParentTask->output(COutputInterface::DURING);
  mpParentTask->output(COutputInterface::MONITORING);

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

  // carry out the minimisation
  try
    {
      tmp = mPraxis(mTolerance, stepmx, mVariableSize, prin, mCurrent.array(), mpPraxis);
    }
  catch (bool)
    {}

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(COptLogEntry("Algorithm finished."));

  return true;
}

bool COptMethodPraxis::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mTolerance = getValue< C_FLOAT64 >("Tolerance");
  mIteration = 0;

  mVariableSize = (C_INT32) mProblemContext.active()->getOptItemList(true).size();
  mCurrent.resize(mVariableSize);
  mBest.resize(mVariableSize);

  return true;
}

bool COptMethodPraxis::cleanup()
{
  return true;
}

// evaluate the value of the objective function
const C_FLOAT64 & COptMethodPraxis::evaluateFunction(C_FLOAT64 *x, C_INT32 & n)
{
  C_INT32 i;
  bool Proceed = proceed();
  const std::vector< COptItem * > & OptItemList = mProblemContext.active()->getOptItemList(true);

  for (i = 0; i < n; i++)
    OptItemList[i]->setItemValue((x[i]), COptItem::CheckPolicyFlag::None);

  //carry out the function evaluation
  mEvaluationValue = evaluate(EvaluationPolicyFlag::All);

  if (mEvaluationValue < getBestValue())
    {
      // We found a new best value lets report it.
      // and store that value
      for (i = 0; i < n; i++)
        mBest[i] = x[i];

      mCountWithinTolerance = 0;
      setSolution(mEvaluationValue, mBest, true);
    }
  else if (SBMLImporter::areApproximatelyEqual(getBestValue(), mEvaluationValue, mTolerance))
    {
      double Norm = 0;
      double tmp;

      for (i = 0; i < n; i++)
        {
          tmp = mBest[i] - x[i];
          Norm += tmp * tmp;
        }

      if (sqrt(Norm) < mTolerance)
        {
          ++mCountWithinTolerance;
          Proceed &= (mCountWithinTolerance < 100);
        }
    }

  mpParentTask->output(COutputInterface::MONITORING);

  if (!Proceed)
    throw bool(Proceed);

  return mEvaluationValue;
}

unsigned C_INT32 COptMethodPraxis::getMaxLogVerbosity() const
{
  return 0;
}

C_FLOAT64 COptMethodPraxis::getCurrentValue() const
{
  return mEvaluationValue;
}

const CVector< C_FLOAT64 > * COptMethodPraxis::getBestParameters() const
{
  return &mBest;
}

const CVector< C_FLOAT64 > * COptMethodPraxis::getCurrentParameters() const
{
  return &mCurrent;
}
