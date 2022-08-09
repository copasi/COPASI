// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/copasi.h"

#include "COptMethodNL2SOL.h"
#include "COptProblem.h"
#include "copasi/parameterFitting/CFitProblem.h"
#include "COptItem.h"
#include "COptTask.h"
#include "FminBrent.h"

COptMethodNL2SOL::COptMethodNL2SOL(const CDataContainer * pParent,
                                   const CTaskEnum::Method & methodType,
                                   const CTaskEnum::Task & taskType):
  COptMethod(pParent, methodType, taskType, false),
  v(NULL),
  iv(NULL),
  mIterations(150),
  mVariableSize(0),
  bounds(NULL),
  nResiduals(0),
  mCurrent(),
  mBest(),
  mBestValue(std::numeric_limits< C_FLOAT64 >::infinity()),
  mContinue(true),
  fCalcr(new FNL2SOLTemplate<COptMethodNL2SOL>(this, &COptMethodNL2SOL::calcr)),
  mpCNL2SOL(new CNL2SOL())
{
  assertParameter("Iteration Limit", CCopasiParameter::Type::UINT, (unsigned C_INT32) 2000);
  initObjects();
}

COptMethodNL2SOL::COptMethodNL2SOL(const COptMethodNL2SOL & src,
                                   const CDataContainer * pParent):
  COptMethod(src, pParent),
  v(NULL),
  iv(NULL),
  mIterations(150),
  mVariableSize(0),
  bounds(NULL),
  nResiduals(0),
  mCurrent(),
  mBest(),
  mBestValue(std::numeric_limits< C_FLOAT64 >::infinity()),
  mContinue(true),
  fCalcr(new FNL2SOLTemplate<COptMethodNL2SOL>(this, &COptMethodNL2SOL::calcr)),
  mpCNL2SOL(new CNL2SOL())
{initObjects();}

COptMethodNL2SOL::~COptMethodNL2SOL()
{
  pdelete(fCalcr);
  pdelete(mpCNL2SOL);
  cleanup();
}

void COptMethodNL2SOL::initObjects()
{
  addObjectReference("Current Iteration", mIterations, CDataObject::ValueInt);
}

bool COptMethodNL2SOL::optimise()
{
  if (!initialize()) return false;

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry(
        "Algorithm started",
        "For more information about this method see: http://copasi.org/Support/User_Manual/Methods/Optimization_Methods/NL2SOL/"
      )
    );

  integer j, dummy;
  integer uiparam[1];
  doublereal urparam[1];

  // generate the bound arrays
  bool pointInParameterDomain = true;

  for (j = 0; j < mVariableSize; j++)
    {
      const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[j];
      mCurrent[j] = OptItem.getStartValue();

      switch (OptItem.checkConstraint(mCurrent[j]))
        {
          case - 1:
            mCurrent[j] = *OptItem.getLowerBoundValue();
            pointInParameterDomain = false;
            break;

          case 1:
            mCurrent[j] = *OptItem.getUpperBoundValue();
            pointInParameterDomain = false;
            break;

          case 0:
            break;
        }

      bounds[2 * j] = *OptItem.getLowerBoundValue();
      bounds[2 * j + 1] = *OptItem.getUpperBoundValue();

      // set the value
      *mProblemContext.master()->getContainerVariables(true)[j] = (mCurrent[j]);
    }

  if (!pointInParameterDomain && (mLogVerbosity > 0))
    mMethodLog.enterLogEntry(COptLogEntry("Initial point outside parameter domain."));

  calcr(&nResiduals, &mVariableSize, mCurrent.array(), &dummy, NULL, &dummy, &mBestValue, (U_fp) fCalcr);
  mBest = mCurrent;

  if (!std::isnan(mEvaluationValue))
    {
      // and store that value
      mBestValue = mEvaluationValue;
      mContinue &= mProblemContext.master()->setSolution(mBestValue, mBest, true);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
      mpParentTask->output(COutputInterface::MONITORING);
    }

  try
    {
      // load all default values
      iv[0] = 0;
      dummy = 1;
      mpCNL2SOL->divset_N(&dummy, iv, &liv, &lv, v);

      // set the maximal number of iterations
      // TO DO: iv[17] = funcEvaluations // Comment code review (08/07/2018): number of maximum function evaluations (default =200)
      iv[17] = mIterations;
      //v[33] = 1e-16; // Comment code review (08/07/2018): leaving the default
      // set memory
      iv[0] = 12;
      iv[20] = 0; // Comment code review (08/07/2018): Supressing the ouput

      mpCNL2SOL->dn2fb_(&nResiduals, &mVariableSize, mCurrent.array(), bounds, fCalcr,
                        iv, &liv, &lv, v, uiparam, urparam, (U_fp) fCalcr);
    }
  catch (unsigned int)
    {
      fatalError();
    }

  if (mLogVerbosity > 0) mMethodLog.enterLogEntry(COptLogEntry("Algorithm finished."));

  return true;
}

bool COptMethodNL2SOL::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mVariableSize = (C_INT) mProblemContext.master()->getOptItemList(true).size();
  mCurrent.resize(mVariableSize);
  mBest.resize(mVariableSize);

  mContinue = true;
  mBestValue = std::numeric_limits<C_FLOAT64>::infinity();

  mIterations = getValue< unsigned C_INT32 >("Iteration Limit");

  CFitProblem * pFitProblem = dynamic_cast< CFitProblem * >(mProblemContext.master());

  if (pFitProblem != NULL)// if (false)
    {
      mHaveResiduals = true;
      pFitProblem->setResidualsRequired(true);
      nResiduals = pFitProblem->getResiduals().size();
      mResidualJacobianT.resize(mVariableSize, nResiduals);
    }

  // create the work array
  lv = 105 + mVariableSize * (nResiduals + 2 * mVariableSize + 21) + 2 * nResiduals;
  v = new doublereal[lv] {0};

  liv = 82 + 4 * mVariableSize;
  iv = new integer[liv] {0};

  bounds = new doublereal[2 * mVariableSize] {0};
  return true;
}

bool COptMethodNL2SOL::cleanup()
{
  if (iv != NULL)
    {
      delete [] iv;
      iv = NULL;
    }

  if (v != NULL)
    {
      delete [] v;
      v = NULL;
    }

  if (bounds != NULL)
    {
      delete [] bounds;
      bounds = NULL;
    }

  return true;
}

const C_FLOAT64 & COptMethodNL2SOL::evaluate()
{
  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.
  mContinue = mProblemContext.master()->calculate();
  mEvaluationValue = mProblemContext.master()->getCalculateValue();

  // when we leave the either the parameter or functional domain
  // we penalize the objective value by forcing it to be larger
  // than the best value recorded so far.
  if (mEvaluationValue < mBestValue &&
      (!mProblemContext.master()->checkParametricConstraints() ||
       !mProblemContext.master()->checkFunctionalConstraints()))
    mEvaluationValue = mBestValue + mBestValue - mEvaluationValue;

  return mEvaluationValue;
}

unsigned C_INT32 COptMethodNL2SOL::getMaxLogVerbosity() const
{
  return 1;
}

C_FLOAT64 COptMethodNL2SOL::getBestValue() const
{
  return mBestValue;
}

C_FLOAT64 COptMethodNL2SOL::getCurrentValue() const
{
  return mEvaluationValue;
}

const CVector< C_FLOAT64 > * COptMethodNL2SOL::getBestParameters() const
{
  return &mBest;
}

const CVector< C_FLOAT64 > * COptMethodNL2SOL::getCurrentParameters() const
{
  return &mCurrent;
}

C_INT COptMethodNL2SOL::calcr(integer *n, integer *p, doublereal *x, integer *nf, doublereal *resid,
                              integer *uiparm, doublereal *urparm, U_fp ufparm)
{
  int i;

  // set the parameter values
  for (i = 0; i < *p; i++)
    *(mProblemContext.master()->getContainerVariables(true)[i]) = x[i];

  //urparm[0] = (*f)(resid );

  urparm[0] = evaluate();

  if (mEvaluationValue < mBestValue)
    {
      // We found a new best value lets report it.
      // and store that value
      mBest = mCurrent;
      mBestValue  = mEvaluationValue;

      mContinue = mProblemContext.master()->setSolution(mBestValue, mBest, true);
      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  mpParentTask->output(COutputInterface::MONITORING);

  if (resid != NULL)
    {
      const CVector< C_FLOAT64 > Residuals =
        static_cast<CFitProblem *>(mProblemContext.master())->getResiduals();

      for (i = 0; i < *n; i++) resid[i] = Residuals[i];
    }

  if (urparm[0] == std::numeric_limits< C_FLOAT64 >::max()) *nf = 0;

  return 0;
}
