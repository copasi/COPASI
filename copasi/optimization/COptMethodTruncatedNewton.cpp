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

#include "COptMethodTruncatedNewton.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "copasi/parameterFitting/CFitProblem.h"
#include "copasi/core/CDataObjectReference.h"

COptMethodTruncatedNewton::COptMethodTruncatedNewton(const CDataContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType):
  COptMethod(pParent, methodType, taskType, false),
  mpTruncatedNewton(new FTruncatedNewtonTemplate<COptMethodTruncatedNewton>(this, &COptMethodTruncatedNewton::sFun)),
  mpCTruncatedNewton(new CTruncatedNewton())
{
  initObjects();
}

COptMethodTruncatedNewton::COptMethodTruncatedNewton(const COptMethodTruncatedNewton & src,
    const CDataContainer * pParent):
  COptMethod(src, pParent, false),
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

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry(
        "Truncated Newton algorithm started",
        "For more information about this method see: http://copasi.org/Support/User_Manual/Methods/Optimization_Methods/Truncated_Newton/"
      )
    );

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
  C_INT i;
  bool pointInParameterDomain = true;
  const std::vector< COptItem * > & OptItemList = mProblemContext.active()->getOptItemList(true);

  for (i = 0; i < mVariableSize; i++)
    {
      COptItem & OptItem = *OptItemList[i];

      // :TODO: In COPASI the bounds are not necessarry fixed.
      // Since evaluate checks for boundaries and constraints this is not
      // needed. The question remaining is how does tnbc_ handle unconstraint problems?
      // low[i] = *OptItem.getLowerBoundValue();
      // up[i] = *OptItem.getUpperBoundValue();

      mCurrent[i] = OptItem.getStartValue();
      pointInParameterDomain &= OptItem.setItemValue(mCurrent[i], COptItem::CheckPolicyFlag::All);
      pointInParameterDomain &= (mCurrent[i] == OptItem.getStartValue());
    }

  if (!pointInParameterDomain && (mLogVerbosity > 0))
    mMethodLog.enterLogEntry(COptLogEntry("Initial point outside parameter domain."));

  // Report the first value as the current best
  mEvaluationValue = evaluate(EvaluationPolicyFlag::All);
  mBest = mCurrent;
  setSolution(mEvaluationValue, mBest, true);

  //tnbc_ wants a signed int for loglevel...
  C_INT msglvl;
  msglvl = (int) mLogVerbosity;

  // estimate minimum is 1/10 initial function value (which is now in mBestValue)
  fest = 0.1 * getBestValue();
  ierror = 0;

  // minimise
  try
    {
      mpCTruncatedNewton->tnbc_(&ierror,
                                &mVariableSize,
                                mCurrent.array(),
                                &fest,
                                mGradient.array(),
                                dwork.array(),
                                &lw,
                                mpTruncatedNewton,
                                low.array(),
                                up.array(),
                                iPivot.array(),
                                &msglvl,
                                &mMethodLog);
      mEvaluationValue = fest;

      if (mLogVerbosity > 0)
        mMethodLog.enterLogEntry(COptLogEntry("tnbc_() return value = " + std::to_string(ierror)));

      // Is the corrected value better than solution?
      if (mEvaluationValue < getBestValue())
        {
          // We found a new bestAlgorithm finished. value lets report it.
          // and store that value
          mBest = mCurrent;
          setSolution(mEvaluationValue, mBest, true);
        }
    }

  // This signals that the user opted to interrupt
  catch (bool)
    {
      if (mLogVerbosity > 0)
        mMethodLog.enterLogEntry(COptLogEntry("Algorithm was terminated by user."));
    }

  if (ierror < 0)
    fatalError(); // Invalid parameter values.

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(COptLogEntry("Algorithm finished."));

  return true;
}

bool COptMethodTruncatedNewton::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mVariableSize = (C_INT) mProblemContext.active()->getOptItemList(true).size();
  mCurrent.resize(mVariableSize);
  mBest.resize(mVariableSize);

  mGradient.resize(mVariableSize);

  CFitProblem* pFitProblem = dynamic_cast<CFitProblem*>(mProblemContext.active());

  if (pFitProblem != NULL)
    {
      pFitProblem->setResidualsRequired(true);
    }

  return true;
}

bool COptMethodTruncatedNewton::cleanup()
{
  return true;
}

// callback function, evaluate the value of the objective function and its gradient
//(by finite differences), translated by f2c, edited by Pedro and then modified for COPASI by Joseph
C_INT COptMethodTruncatedNewton::sFun(C_INT* n, C_FLOAT64* x, C_FLOAT64* f, C_FLOAT64* g)
{
  C_INT i;

  const std::vector< COptItem * > & OptItemList = mProblemContext.active()->getOptItemList(true);

  // set the parameter values
  for (i = 0; i < *n; i++)
    OptItemList[i]->setItemValue(x[i], COptItem::CheckPolicyFlag::None);

  //carry out the function evaluation
  *f = evaluate(EvaluationPolicyFlag::All);

  CFitProblem* pFit = dynamic_cast<CFitProblem*>(mProblemContext.active());

  // Check whether we improved
  if (mEvaluationValue < getBestValue())
    {
      mBest = CVectorCore< C_FLOAT64 >(mVariableSize, x);
      setSolution(mEvaluationValue, mBest, true);
    }

  if (pFit && pFit->getUseTimeSens())
    {
      C_FLOAT64* pJacobianT = pFit->getTimeSensJac().array();
      const CVector< C_FLOAT64 >& Residuals = pFit->getResiduals();
      const C_FLOAT64* pCurrentResiduals;
      size_t ResidualSize = Residuals.size();
      const C_FLOAT64* pEnd = Residuals.array() + ResidualSize;

      for (size_t i = 0; i < mVariableSize; i++, g++)
        {
          *g = 0.0;
          pCurrentResiduals = Residuals.array();

          for (; pCurrentResiduals != pEnd; pCurrentResiduals++, pJacobianT++)
            *g -= *pJacobianT * *pCurrentResiduals;
        }
    }
  else
    {
      // Calculate the gradient
      for (i = 0; i < *n && proceed(); i++)
        {
          COptItem & OptItem = *OptItemList[i];

          if (x[i] != 0.0)
            {
              C_FLOAT64 X = x[i] * 1.001;
              OptItem.setItemValue(X, COptItem::CheckPolicyFlag::None);
              g[i] = (evaluate(EvaluationPolicyFlag::All) - *f) / (x[i] * 0.001);
            }
          else
            {
              // why use 1e-7? shouldn't this be epsilon, or something like that?
              C_FLOAT64 X = 1e-7;
              OptItem.setItemValue(X, COptItem::CheckPolicyFlag::None);
              g[i] = (evaluate(EvaluationPolicyFlag::All) - *f) / 1e-7;

              if (mLogVerbosity > 2)
                {
                  std::ostringstream auxStream;
                  auxStream << "Calculating gradient for zero valued parameter " << i << ", using 1e-7, results in " << g[i] << ".";
                  mMethodLog.enterLogEntry(COptLogEntry(auxStream.str()));
                }
            }

          OptItem.setItemValue(x[i], COptItem::CheckPolicyFlag::None);
        }
    }

  mpParentTask->output(COutputInterface::MONITORING);

  if (!proceed())
    throw bool(false);

  return 0;
}

unsigned C_INT32 COptMethodTruncatedNewton::getMaxLogVerbosity() const
{
  return 1;
}

C_FLOAT64 COptMethodTruncatedNewton::getCurrentValue() const
{
  return mEvaluationValue;
}

const CVector< C_FLOAT64 > * COptMethodTruncatedNewton::getBestParameters() const
{
  return &mBest;
}

const CVector< C_FLOAT64 > * COptMethodTruncatedNewton::getCurrentParameters() const
{
  return &mCurrent;
}
