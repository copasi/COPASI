// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <string.h>
#include <cmath>

#include "copasi/copasi.h"

#include "CLyapMethod.h"
#include "CLyapProblem.h"
#include "CLyapTask.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/lapack/blaswrap.h"

CLyapWolfMethod::CLyapWolfMethod(const CDataContainer * pParent,
                                 const CTaskEnum::Method & methodType,
                                 const CTaskEnum::Task & taskType):
  CLyapMethod(pParent, methodType, taskType),
  mContainerState()
{
  assert((void *) &mData == (void *) &mData.dim);

  mData.pMethod = this;
  initializeParameter();
}

CLyapWolfMethod::CLyapWolfMethod(const CLyapWolfMethod & src,
                                 const CDataContainer * pParent):
  CLyapMethod(src, pParent),
  mContainerState()
{
  assert((void *) &mData == (void *) &mData.dim);

  mData.pMethod = this;
  initializeParameter();
}

CLyapWolfMethod::~CLyapWolfMethod()
{}

void CLyapWolfMethod::initializeParameter()
{
  assertParameter("Orthonormalization Interval", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.0);
  assertParameter("Overall time", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1000.0);
  assertParameter("Relative Tolerance", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.0e-6);
  assertParameter("Absolute Tolerance", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.0e-12);
  assertParameter("Max Internal Steps", CCopasiParameter::Type::UINT, (unsigned C_INT32) 10000);

  // Check whether we have an (obsolete) parameter "Use Default Absolute Tolerance"
  CCopasiParameter *pParm;

  if ((pParm = getParameter("Use Default Absolute Tolerance")) != NULL)
    {
      C_FLOAT64 NewValue;

      if (pParm->getValue< bool >())
        {
          // The default
          NewValue = 1.e-12;
        }
      else
        {
          NewValue = getValue< C_FLOAT64 >("Absolute Tolerance");
        }

      setValue("Absolute Tolerance", NewValue);
      removeParameter("Use Default Absolute Tolerance");
    }

  // These parameters are no longer supported.
  removeParameter("Adams Max Order");
  removeParameter("BDF Max Order");
}

bool CLyapWolfMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

double CLyapWolfMethod::step(const double & deltaT)
{
  if (!mData.dim) //just do nothing if there are no variables
    {
      *mpContainerStateTime += deltaT;

      return deltaT;
    }

  C_FLOAT64 startTime = *mpContainerStateTime;
  C_FLOAT64 EndTime = *mpContainerStateTime + deltaT;
  C_INT one = 1;
  C_INT two = 2;
  C_INT DSize = (C_INT) mDWork.size();
  C_INT ISize = (C_INT) mIWork.size();

  mLSODA(&EvalF,  //  1. evaluate F
         &mData.dim,  //  2. number of variables
         mVariables.array(), //  3. the array of current concentrations
         mpContainerStateTime,  //  4. the current time
         &EndTime,  //  5. the final time
         &two,  //  6. vector absolute error, scalar relative error
         &mRtol,  //  7. relative tolerance array
         mAtol.array(),  //  8. absolute tolerance array
         &mTask,  //  9. output by overshoot & interpolation
         &mLsodaStatus,  // 10. the state control variable
         &one,  // 11. futher options (one)
         mDWork.array(),  // 12. the double work array
         &DSize,  // 13. the double work array size
         mIWork.array(),  // 14. the int work array
         &ISize,  // 15. the int work array size
         NULL,  // 16. evaluate J (not given)
         &mJType);           // 17. the type of Jacobian calculate (2)

  if (mLsodaStatus == -1)
    {
      ++mFailedSteps;
      mLsodaStatus = 2;
    }

  if (mLsodaStatus < 0
      && fabs(EndTime - *mpContainerStateTime) > 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() * EndTime)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 6, mErrorMsg.str().c_str());
    }

  return *mpContainerStateTime - startTime;
}

void CLyapWolfMethod::start(/*const CState * initialState*/)
{
  /* Reset lsoda */
  mLsodaStatus = 1;
  mTask = 1;
  mJType = 2;
  mErrorMsg.str("");
  mLSODA.setOstream(mErrorMsg);

  mReducedModel = true; /* *getValue("Integrate Reduced Model").pBOOL;*/

  /* Release previous state and make the initialState the current */
  mContainerState.initialize(mpContainer->getState(mReducedModel));

  //mY = mpState->beginIndependent();
  mpContainerStateTime = mContainerState.array() + mpContainer->getCountFixedEventTargets();

  mSystemSize = mContainerState.size() - mpContainer->getCountFixedEventTargets() - 1;

  mpYdot = mpContainer->getRate(mReducedModel).array() + mpContainer->getCountFixedEventTargets() + 1;

  mNumExp = mpProblem->getExponentNumber();
  mDoDivergence = mpProblem->divergenceRequested();

  //calculate the number of variables for lsoda integration
  if (mDoDivergence)
    mData.dim = (C_INT)(mSystemSize * (1 + mNumExp) + 1);
  else
    mData.dim = (C_INT)(mSystemSize * (1 + mNumExp));

  //initialize the vector on which lsoda will work
  mVariables.resize(mData.dim);

  //reserve space for exponents. The vectors in the task are resized by the task because they
  //need to have a minimum size defined in the task
  //pTask->mLocalExponents.resize(mNumExp);
  mSumExponents.resize(mNumExp);
  mNorms.resize(mNumExp);
  //pTask->mExponents.resize(mNumExp);

  memcpy(mVariables.array(), mpContainerStateTime + 1, mSystemSize * sizeof(C_FLOAT64));

  //generate base vectors. Just define some arbitrary starting vectors that are not too specific and orthonormalize
  // first fill the array with 0.1
  C_FLOAT64 *dbl, *dblEnd = mVariables.array() + mData.dim;

  for (dbl = mVariables.array() + mSystemSize; dbl != dblEnd; ++dbl)
    *dbl = 0.01;

  //now add 1.0
  if (mNumExp > 0)
    for (dbl = mVariables.array() + mSystemSize; dbl < dblEnd; dbl += (mSystemSize + 1))
      * dbl = 1.0;

  orthonormalize();

  //reserve space for jacobian
  mJacobian.resize(mSystemSize, mSystemSize);

  size_t i, imax = mNumExp;

  for (i = 0; i < imax; ++i)
    {
      mpTask->mLocalExponents[i] = 0;
      mSumExponents[i] = 0;
      mpTask->mExponents[i] = 0;
    }

  mpTask->mIntervalDivergence = 0;
  mSumDivergence = 0;
  mpTask->mAverageDivergence = 0;

  /* Configure lsoda */
  mRtol = getValue< C_FLOAT64 >("Relative Tolerance");

  C_FLOAT64 * pTolerance = &getValue< C_FLOAT64 >("Absolute Tolerance");
  CVector< C_FLOAT64 > tmpAtol = mpContainer->initializeAtolVector(*pTolerance, mReducedModel);

  mAtol.resize(mData.dim);

  for (i = 0; i < mSystemSize; ++i)
    mAtol[i] = tmpAtol[i];

  for (i = mSystemSize; (int)i < mData.dim; ++i)
    mAtol[i] = 1e-20;

  mDWork.resize(22 + mData.dim * std::max<C_INT>(16, mData.dim + 9));
  mDWork[4] = mDWork[5] = mDWork[6] = mDWork[7] = mDWork[8] = mDWork[9] = 0.0;
  mIWork.resize(20 + mData.dim);
  mIWork[4] = mIWork[6] = mIWork[9] = 0;

  mFailedSteps = 0;
  mStepLimit = getValue< unsigned C_INT32 >("Max Internal Steps");
  mIWork[5] = mStepLimit;
  mIWork[7] = 12;
  mIWork[8] = 5;

  return;
}

void CLyapWolfMethod::EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{static_cast<Data *>((void *) n)->pMethod->evalF(t, y, ydot);}

void CLyapWolfMethod::evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{
  assert(y == mVariables.array());

  *mpContainerStateTime = *t;
  memcpy(mpContainerStateTime + 1, mVariables.array(), mSystemSize * sizeof(C_FLOAT64));

  mpContainer->updateSimulatedValues(mReducedModel);
  memcpy(ydot, mpYdot, mSystemSize * sizeof(C_FLOAT64));

  mpContainer->calculateJacobian(mJacobian, 1e-6, mReducedModel);

  //empty dummy entries... to be removed later
  //C_FLOAT64 *dbl, *dblEnd = ydot + mData.dim;
  //for (dbl = ydot + mSystemSize; dbl != dblEnd; ++dbl)
  //  *dbl = 0;

  //   char T = 'N';
  //   C_INT M = mSystemSize;
  //   C_INT N = mSystemSize;
  //   C_INT K = 1;
  //   //C_INT LD = mUnscaledElasticities.numCols();
  //
  //   C_FLOAT64 Alpha = 1.0;
  //   C_FLOAT64 Beta = 0.0;
  //
  //   dgemm_(&T, &T, &K, &N, &M, &Alpha,
  //          const_cast<C_FLOAT64*>(y) + mSystemSize, &K,
  //          mJacobian.array(), &M,
  //          &Beta,
  //          ydot + mSystemSize, &M);

  C_FLOAT64 *dbl1;
  const C_FLOAT64 *dbl2, *dbl3, *dbl1end, *dbl3end;

  dbl1 = ydot + mSystemSize;

  size_t i;

  for (i = 1; i <= mNumExp; ++i)
    {
      //dbl1 += mSystemSize;
      dbl1end = dbl1 + mSystemSize;
      dbl2 = mJacobian.array();

      for (; dbl1 != dbl1end; ++dbl1)
        {
          *dbl1 = 0.0;

          dbl3 = y + i * mSystemSize;
          dbl3end = dbl3 + mSystemSize;

          for (; dbl3 != dbl3end; ++dbl3, ++dbl2)
            *dbl1 += *dbl2 **dbl3;
        }
    }

  if (!mDoDivergence) return;

  //divergence; trace of jacobian
  *dbl1 = 0;
  dbl2 = mJacobian.array();

  for (i = 0; i < mSystemSize; ++i, dbl2 += (mSystemSize + 1))
    * dbl1 += *dbl2;

  return;
}

//this starts with current state
bool CLyapWolfMethod::calculate()
{
  //get the pointer to the parent task. It's needed for output
  mpTask = dynamic_cast<CLyapTask*>(getObjectParent());
  assert(mpTask);

  //initialize LSODA
  start();

  C_FLOAT64 stepSize = getValue< C_FLOAT64 >("Orthonormalization Interval");
  C_FLOAT64 transientTime = mpProblem->getTransientTime() + *mpContainerStateTime;
  C_FLOAT64 endTime = *mpContainerStateTime + getValue< C_FLOAT64 >("Overall time");
  C_FLOAT64 startTime = *mpContainerStateTime;

  bool flagProceed = true;

  if (mProcessReport)
    flagProceed = mProcessReport.proceed();

  C_FLOAT64 handlerFactor = 100.0 / (endTime - startTime);

  //** do the transient **
  C_FLOAT64 CompareTime = transientTime - 100.0 * fabs(transientTime) * std::numeric_limits< C_FLOAT64 >::epsilon();

  if (*mpContainerStateTime < CompareTime)
    {
      do
        {
          step(transientTime - *mpContainerStateTime);

          if (*mpContainerStateTime > CompareTime) break;

          if (mFailedSteps * 10 >= mStepLimit)
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCLyap + 6);

          /* Here we will do conditional event processing */

          /* Currently this is correct since no events are processed. */
          //CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 12);

          flagProceed &= mpTask->methodCallback((*mpContainerStateTime - startTime) * handlerFactor, true);
        }
      while (flagProceed);

      //mpLyapProblem->getModel()->setState(*mpCurrentState);
      //mpLyapProblem->getModel()->updateSimulatedValues();
    }
  else
    {
    }

  if (!flagProceed)
    return false;

  //copy state to model and do output
  mpContainer->updateSimulatedValues(mReducedModel);
  flagProceed = mpTask->methodCallback((*mpContainerStateTime - startTime) * handlerFactor, false);

  if (!flagProceed)
    return false;

  //********

  orthonormalize();

  if (mDoDivergence)
    *(mVariables.array() + mVariables.size() - 1) = 0; //divergence

  mLsodaStatus = 1; //the state has changed, we need to restart lsoda

  size_t i;

  C_FLOAT64 realStepSize;

  do
    {
      realStepSize = step(stepSize);

      if (mFailedSteps * 10 >= mStepLimit)
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCLyap + 6);

      orthonormalize();
      mLsodaStatus = 1; //the state has changed, we need to restart lsoda

      //process results of orthonormalisation
      for (i = 0; i < mNumExp; ++i)
        {
          mpTask->mLocalExponents[i] = log(mNorms[i]);
          mSumExponents[i] += mpTask->mLocalExponents[i];
          mpTask->mLocalExponents[i] = mpTask->mLocalExponents[i] / realStepSize;
          mpTask->mExponents[i] = mSumExponents[i] / (*mpContainerStateTime - transientTime);
        }

      //process result of divergence integration
      if (mDoDivergence)
        {
          mSumDivergence += *(mVariables.array() + mVariables.size() - 1);
          mpTask->mIntervalDivergence = *(mVariables.array() + mVariables.size() - 1) / realStepSize;
          *(mVariables.array() + mVariables.size() - 1) = 0;
          mpTask->mAverageDivergence = mSumDivergence / (*mpContainerStateTime - transientTime);
        }

      flagProceed &= mpTask->methodCallback((*mpContainerStateTime - startTime) * handlerFactor, false);
    }
  while ((*mpContainerStateTime < endTime) && flagProceed);

  return flagProceed;
}

void CLyapWolfMethod::orthonormalize()
{
  if (mNumExp < 1) return;

  //TODO generalize
  C_FLOAT64 *dbl, *dblEnd;

  dbl = mVariables.array() + mSystemSize;
  dblEnd = dbl + mSystemSize;
  mNorms[0] = norm(dbl, dblEnd);
  scalarmult(dbl, dblEnd, 1 / mNorms[0]);

  size_t i, j;

  for (i = 1; i < mNumExp; ++i)
    {
      dbl += mSystemSize;
      dblEnd = dbl + mSystemSize;

      //orthogonalisation
      for (j = 0; j < i; ++j)
        {
          add(dbl, dblEnd,
              -product(dbl, dblEnd, mVariables.array() + (j + 1)*mSystemSize),
              mVariables.array() + (j + 1)*mSystemSize);
        }

      //normalisation
      mNorms[i] = norm(dbl, dblEnd);
      scalarmult(dbl, dblEnd, 1 / mNorms[i]);
    }
}

//static
C_FLOAT64 CLyapWolfMethod::norm(const C_FLOAT64* dbl1, const C_FLOAT64 * dbl2)
{
  C_FLOAT64 sum = 0;

  for (; dbl1 != dbl2; ++dbl1)
    sum += *dbl1 **dbl1;

  return sqrt(sum);
}

//static
void CLyapWolfMethod::scalarmult(C_FLOAT64* dbl1, const C_FLOAT64* dbl2,
                                 const C_FLOAT64 & f)
{
  for (; dbl1 != dbl2; ++dbl1)
    *dbl1 *= f;
}

//static
C_FLOAT64 CLyapWolfMethod::product(const C_FLOAT64* dbl1, const C_FLOAT64* dbl1End,
                                   const C_FLOAT64* dbl2)
{
  C_FLOAT64 sum = 0;

  for (; dbl1 != dbl1End; ++dbl1, ++dbl2)
    sum += *dbl1 **dbl2;

  return sum;
}

//static
void CLyapWolfMethod::add(C_FLOAT64* dbl1, const C_FLOAT64* dbl1End,
                          const C_FLOAT64 & f, const C_FLOAT64* dbl2)
{
  //calculate v1 = v1 + f * v2
  for (; dbl1 != dbl1End; ++dbl1, ++dbl2)
    *dbl1 += f **dbl2;
}

//virtual
bool CLyapWolfMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CLyapMethod::isValidProblem(pProblem)) return false;

  const CLyapProblem * pLP = dynamic_cast<const CLyapProblem *>(pProblem);
  assert(pLP);

  C_FLOAT64 stepSize = getValue< C_FLOAT64 >("Orthonormalization Interval");
  C_FLOAT64 transientTime = pLP->getTransientTime();
  C_FLOAT64 endTime = getValue< C_FLOAT64 >("Overall time");

  if (transientTime >= endTime)
    {
      //
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCLyap + 4);
      return false;
    }

  if (stepSize > (endTime - transientTime))
    {
      //
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCLyap + 5);
      return false;
    }

  return true;
}
