// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/lyap/CLyapWolfMethod.cpp,v $
//   $Revision: 1.20 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:30:20 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
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
#include <string.h>

#include "copasi.h"

#include "CLyapMethod.h"
#include "CLyapProblem.h"
#include "CLyapTask.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "blaswrap.h"

CLyapWolfMethod::CLyapWolfMethod(const CCopasiContainer * pParent):
    CLyapMethod(CCopasiMethod::lyapWolf, pParent),
    mpState(NULL)
{
  assert((void *) &mData == (void *) &mData.dim);

  mData.pMethod = this;
  initializeParameter();
}

CLyapWolfMethod::CLyapWolfMethod(const CLyapWolfMethod & src,
                                 const CCopasiContainer * pParent):
    CLyapMethod(src, pParent),
    mpState(NULL)
{
  assert((void *) &mData == (void *) &mData.dim);

  mData.pMethod = this;
  initializeParameter();
}

CLyapWolfMethod::~CLyapWolfMethod()
{
  pdelete(mpState);
}

void CLyapWolfMethod::initializeParameter()
{
  assertParameter("Orthonormalization Interval", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0);
  assertParameter("Overall time", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1000.0);
  assertParameter("Relative Tolerance", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-6);
  assertParameter("Absolute Tolerance", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-12);
  assertParameter("Max Internal Steps", CCopasiParameter::UINT, (unsigned C_INT32) 10000);

  // Check whether we have an (obsolete) parameter "Use Default Absolute Tolerance"
  CCopasiParameter *pParm;

  if ((pParm = getParameter("Use Default Absolute Tolerance")) != NULL)
    {
      C_FLOAT64 NewValue;

      if (*pParm->getValue().pBOOL)
        {
          // The default
          NewValue = 1.e-12;
        }
      else
        {
          NewValue = *getValue("Absolute Tolerance").pUDOUBLE;
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
      mTime = mTime + deltaT;
      mpState->setTime(mTime);

      return deltaT;
    }

  C_FLOAT64 startTime = mTime;
  C_FLOAT64 EndTime = mTime + deltaT;
  C_INT one = 1;
  C_INT two = 2;
  C_INT DSize = (C_INT) mDWork.size();
  C_INT ISize = (C_INT) mIWork.size();

  mLSODA(&EvalF , //  1. evaluate F
         &mData.dim , //  2. number of variables
         mVariables.array(), //  3. the array of current concentrations
         &mTime , //  4. the current time
         &EndTime , //  5. the final time
         &two , //  6. vector absolute error, scalar relative error
         &mRtol , //  7. relative tolerance array
         mAtol.array() , //  8. absolute tolerance array
         &mState , //  9. output by overshoot & interpolation
         &mLsodaStatus , // 10. the state control variable
         &one , // 11. futher options (one)
         mDWork.array() , // 12. the double work array
         &DSize , // 13. the double work array size
         mIWork.array() , // 14. the int work array
         &ISize , // 15. the int work array size
         NULL , // 16. evaluate J (not given)
         &mJType);           // 17. the type of Jacobian calculate (2)

  if (mLsodaStatus == -1) mLsodaStatus = 2;

  if ((mLsodaStatus != 1) && (mLsodaStatus != 2) && (mLsodaStatus != -1))
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 6, mErrorMsg.str().c_str());
    }

  return mTime - startTime;
}

void CLyapWolfMethod::start(/*const CState * initialState*/)
{
  /* Reset lsoda */
  mLsodaStatus = 1;
  mState = 1;
  mJType = 2;
  mErrorMsg.str("");
  mLSODA.setOstream(mErrorMsg);

  /* Release previous state and make the initialState the current */
  pdelete(mpState);
  mpState = new CState(mpProblem->getModel()->getState());

  //mY = mpState->beginIndependent();
  mTime = mpState->getTime();

  mReducedModel = true; /* *getValue("Integrate Reduced Model").pBOOL;*/

  if (mReducedModel)
    mSystemSize = mpState->getNumIndependent();
  else
    mSystemSize = mpState->getNumIndependent() + mpProblem->getModel()->getNumDependentReactionMetabs();

  mNumExp = mpProblem->getExponentNumber();
  mDoDivergence = mpProblem->divergenceRequested();

  //calculate the number of variables for lsoda integration
  if (mDoDivergence)
    mData.dim = (C_INT)(mSystemSize * (1 + mNumExp) + 1);
  else
    mData.dim = (C_INT)(mSystemSize * (1 + mNumExp));

  //reserve space for exponents. The vectors in the task are resized by the task because they
  //need to have a minimum size defined in the task
  //pTask->mLocalExponents.resize(mNumExp);
  mSumExponents.resize(mNumExp);
  mNorms.resize(mNumExp);
  //pTask->mExponents.resize(mNumExp);

  //initialize the vector on which lsoda will work
  mVariables.resize(mData.dim);
  memcpy(mVariables.array(), mpState->beginIndependent(), mSystemSize * sizeof(C_FLOAT64));

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
  mRtol = * getValue("Relative Tolerance").pUDOUBLE;

  C_FLOAT64 * pTolerance = getValue("Absolute Tolerance").pUDOUBLE;
  CVector< C_FLOAT64 > tmpAtol = mpProblem->getModel()->initializeAtolVector(*pTolerance, mReducedModel);

  mAtol.resize(mData.dim);

  for (i = 0; i < mSystemSize; ++i)
    mAtol[i] = tmpAtol[i];

  for (i = mSystemSize; (int)i < mData.dim; ++i)
    mAtol[i] = 1e-20;

  mDWork.resize(22 + mData.dim * std::max<C_INT>(16, mData.dim + 9));
  mDWork[4] = mDWork[5] = mDWork[6] = mDWork[7] = mDWork[8] = mDWork[9] = 0.0;
  mIWork.resize(20 + mData.dim);
  mIWork[4] = mIWork[6] = mIWork[9] = 0;

  mIWork[5] = * getValue("Max Internal Steps").pUINT;
  mIWork[7] = 12;
  mIWork[8] = 5;

  return;
}

void CLyapWolfMethod::EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{static_cast<Data *>((void *) n)->pMethod->evalF(t, y, ydot);}

void CLyapWolfMethod::evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{
  assert(y == mVariables.array());

  //set time in model
  mpState->setTime(*t);

  //copy working array to state
  memcpy(mpState->beginIndependent(), mVariables.array(), mSystemSize * sizeof(C_FLOAT64));

  //copy state to model
  CModel * pModel = mpProblem->getModel();
  pModel->setState(*mpState);
  pModel->updateSimulatedValues(mReducedModel);

  //the model
  if (mReducedModel)
    pModel->calculateDerivativesX(ydot);
  else
    pModel->calculateDerivatives(ydot);

  //the linearized model

  //get jacobian
  pModel->calculateJacobianX(mJacobian, 1e-6, 1e-12);

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
            *dbl1 += *dbl2 * *dbl3;
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

  C_FLOAT64 stepSize = *getValue("Orthonormalization Interval").pUDOUBLE;
  C_FLOAT64 transientTime = mpProblem->getTransientTime() + mTime;
  C_FLOAT64 endTime = mTime + *getValue("Overall time").pUDOUBLE;
  C_FLOAT64 startTime = mTime;

  bool flagProceed = true;
  C_FLOAT64 handlerFactor = 100.0 / (endTime - startTime);

  //** do the transient **
  C_FLOAT64 CompareTime = transientTime - 100.0 * fabs(transientTime) * std::numeric_limits< C_FLOAT64 >::epsilon();

  if (mTime < CompareTime)
    {
      do
        {
          step(transientTime - mTime);

          if (mTime > CompareTime) break;

          /* Here we will do conditional event processing */

          /* Currently this is correct since no events are processed. */
          //CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 12);

          mpTask->methodCallback((mTime - startTime) * handlerFactor, true);
        }
      while (true);

      //mpLyapProblem->getModel()->setState(*mpCurrentState);
      //mpLyapProblem->getModel()->updateSimulatedValues();
    }
  else
    {
    }

  //copy working array to state
  memcpy(mpState->beginIndependent(), mVariables.array(), mSystemSize * sizeof(C_FLOAT64));
  mpState->setTime(mTime);

  //copy state to model and do output
  mpProblem->getModel()->setState(*mpState);
  mpProblem->getModel()->updateSimulatedValues(mReducedModel);
  mpTask->methodCallback((mTime - startTime) * handlerFactor, false);
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

      orthonormalize();
      mLsodaStatus = 1; //the state has changed, we need to restart lsoda

      //process results of orthonormalisation
      for (i = 0; i < mNumExp; ++i)
        {
          mpTask->mLocalExponents[i] = log(mNorms[i]);
          mSumExponents[i] += mpTask->mLocalExponents[i];
          mpTask->mLocalExponents[i] = mpTask->mLocalExponents[i] / realStepSize;
          mpTask->mExponents[i] = mSumExponents[i] / (mTime - transientTime);
        }

      //process result of divergence integration
      if (mDoDivergence)
        {
          mSumDivergence += *(mVariables.array() + mVariables.size() - 1);
          mpTask->mIntervalDivergence = *(mVariables.array() + mVariables.size() - 1) / realStepSize;
          *(mVariables.array() + mVariables.size() - 1) = 0;
          mpTask->mAverageDivergence = mSumDivergence / (mTime - transientTime);
        }

      //copy working array to state
      memcpy(mpState->beginIndependent(), mVariables.array(), mSystemSize * sizeof(C_FLOAT64));
      mpState->setTime(mTime);
      //copy state to model and do output
      mpProblem->getModel()->setState(*mpState);
      mpProblem->getModel()->updateSimulatedValues(mReducedModel);
      flagProceed &= mpTask->methodCallback((mTime - startTime) * handlerFactor, false);
    }
  while ((mTime < endTime) && flagProceed);

  return true;
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
    sum += *dbl1 * *dbl1;

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
    sum += *dbl1 * *dbl2;

  return sum;
}

//static
void CLyapWolfMethod::add(C_FLOAT64* dbl1, const C_FLOAT64* dbl1End,
                          const C_FLOAT64 & f, const C_FLOAT64* dbl2)
{
  //calculate v1 = v1 + f * v2
  for (; dbl1 != dbl1End; ++dbl1, ++dbl2)
    *dbl1 += f * *dbl2;
}

//virtual
bool CLyapWolfMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CLyapMethod::isValidProblem(pProblem)) return false;

  const CLyapProblem * pLP = dynamic_cast<const CLyapProblem *>(pProblem);
  assert(pLP);

  C_FLOAT64 stepSize = *getValue("Orthonormalization Interval").pUDOUBLE;
  C_FLOAT64 transientTime = pLP->getTransientTime();
  C_FLOAT64 endTime = *getValue("Overall time").pUDOUBLE;

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
