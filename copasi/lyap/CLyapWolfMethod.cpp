/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/lyap/CLyapWolfMethod.cpp,v $
   $Revision: 1.5.2.3 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/05/21 12:10:45 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CLyapMethod.h"
#include "CLyapProblem.h"
#include "CLyapTask.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "blaswrap.h"

CLyapWolfMethod::CLyapWolfMethod(const CCopasiContainer * pParent):
    CLyapMethod(CCopasiMethod::lyapWolf, pParent),
    mpState(NULL)
    //mY(NULL)
{
  mDim[1] = (C_INT) (void *) this;

  addParameter("Orthonormalization Interval",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0);
  addParameter("Overall time",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1000.0);
  //addParameter("Integrate Reduced Model",
  //             CCopasiParameter::BOOL, (bool) true);
  addParameter("Relative Tolerance",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-006);
  addParameter("Use Default Absolute Tolerance",
               CCopasiParameter::BOOL, (bool) true);
  addParameter("Absolute Tolerance",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e009);
  addParameter("Adams Max Order",
               CCopasiParameter::UINT, (unsigned C_INT32) 12);
  addParameter("BDF Max Order",
               CCopasiParameter::UINT, (unsigned C_INT32) 5);
  addParameter("Max Internal Steps",
               CCopasiParameter::UINT, (unsigned C_INT32) 10000);
}

CLyapWolfMethod::CLyapWolfMethod(const CLyapWolfMethod & src,
                                 const CCopasiContainer * pParent):
    CLyapMethod(src, pParent),
    mpState(NULL)
    //mY(NULL)
{}

CLyapWolfMethod::~CLyapWolfMethod()
{
  pdelete(mpState);
}

void CLyapWolfMethod::step(const double & deltaT)
{
  if (!mDim[0]) //just do nothing if there are no variables
    {
      mTime = mTime + deltaT;
      mpState->setTime(mTime);
      //*mpCurrentState = *mpState;

      return;
    }

  C_FLOAT64 EndTime = mTime + deltaT;
  C_INT one = 1;
  C_INT DSize = mDWork.size();
  C_INT ISize = mIWork.size();

  mLSODA(&EvalF ,          //  1. evaluate F
         mDim ,            //  2. number of variables
         mVariables.array(), //  3. the array of current concentrations
         &mTime ,          //  4. the current time
         &EndTime ,        //  5. the final time
         &one ,            //  6. scalar error control
         &mRtol ,          //  7. relative tolerance array
         &mAtol ,          //  8. absolute tolerance array
         &mState ,         //  9. output by overshoot & interpolatation
         &mLsodaStatus ,   // 10. the state control variable
         &one ,            // 11. futher options (one)
         mDWork.array() ,  // 12. the double work array
         &DSize ,          // 13. the double work array size
         mIWork.array() ,  // 14. the int work array
         &ISize ,          // 15. the int work array size
         NULL ,            // 16. evaluate J (not given)
         &mJType);        // 17. the type of jacobian calculate (2)

  if (mLsodaStatus == -1) mLsodaStatus = 2;

  if ((mLsodaStatus != 1) && (mLsodaStatus != 2) && (mLsodaStatus != -1))
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 6, mErrorMsg.str().c_str());
    }

  //mpState->setTime(mTime); //TODO: really???
  //*mpCurrentState = *mpState;

  return;
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
    {
      mpState->setUpdateDependentRequired(true);
      mSystemSize = mpState->getNumIndependent();
    }
  else
    {
      mpState->setUpdateDependentRequired(false);
      mSystemSize = mpState->getNumVariable();
    }

  mNumExp = mpProblem->getExponentNumber();
  mDoDivergence = mpProblem->divergenceRequested();

  //calculate the number of variables for lsoda integration
  if (mDoDivergence)
    mDim[0] = mSystemSize * (1 + mNumExp) + 1;
  else
    mDim[0] = mSystemSize * (1 + mNumExp);

  //std::cout << "lyap: " << mSystemSize << " " << mNumExp << " " << mDim[0] << std::endl;

  //initialize the vector on which lsoda will work
  mVariables.resize(mDim[0]);
  memcpy(mVariables.array(), mpState->beginIndependent(), mSystemSize * sizeof(C_FLOAT64));

  //generate base vectors; first fill the array with 0
  C_FLOAT64 *dbl, *dblEnd = mVariables.array() + mDim[0];
  for (dbl = mVariables.array() + mSystemSize; dbl != dblEnd; ++dbl)
    *dbl = 0.0;
  //now add 1.0
  for (dbl = mVariables.array() + mSystemSize; dbl < dblEnd; dbl += (mSystemSize + 1))
    * dbl = 1.0;

  //reserve space for jacobian
  mJacobian.resize(mSystemSize, mSystemSize);

  //reserve space for exponents
  //pTask->mLocalExponents.resize(mNumExp);
  mSumExponents.resize(mNumExp);
  mNorms.resize(mNumExp);
  //pTask->mExponents.resize(mNumExp);
  C_INT32 i, imax = mNumExp;
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
  mDefaultAtol = * getValue("Use Default Absolute Tolerance").pBOOL;
  if (mDefaultAtol)
    {
      mAtol = getDefaultAtol(mpProblem->getModel());
      setValue("Absolute Tolerance", mAtol);
    }
  else
    mAtol = * getValue("Absolute Tolerance").pUDOUBLE;

  mDWork.resize(22 + mDim[0] * std::max<C_INT>(16, mDim[0] + 9));
  mDWork[4] = mDWork[5] = mDWork[6] = mDWork[7] = mDWork[8] = mDWork[9] = 0.0;
  mIWork.resize(20 + mDim[0]);
  mIWork[4] = mIWork[6] = mIWork[9] = 0;

  mIWork[5] = * getValue("Max Internal Steps").pUINT;
  mIWork[7] = * getValue("Adams Max Order").pUINT;
  mIWork[8] = * getValue("BDF Max Order").pUINT;

  return;
}

C_FLOAT64 CLyapWolfMethod::getDefaultAtol(const CModel * pModel) const
  {
    if (!pModel) return 1.0e009;

    const CCopasiVectorNS< CCompartment > & Compartment = pModel->getCompartments();
    unsigned C_INT32 i, imax;
    C_FLOAT64 Volume = DBL_MAX;
    for (i = 0, imax = Compartment.size(); i < imax; i++)
      if (Compartment[i]->getVolume() < Volume) Volume = Compartment[i]->getVolume();

    if (Volume == DBL_MAX) return 1.0e009;

    return Volume * pModel->getQuantity2NumberFactor() * 1.e-12;
  }

void CLyapWolfMethod::EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{static_cast<CLyapWolfMethod *>((void *) n[1])->evalF(t, y, ydot);}

void CLyapWolfMethod::evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{
  assert (y == mVariables.array());

  //set time in model
  mpState->setTime(*t);

  //copy working array to state
  memcpy(mpState->beginIndependent(), mVariables.array(), mSystemSize * sizeof(C_FLOAT64));

  //copy state to model
  CModel * pModel = mpProblem->getModel();
  pModel->setState(*mpState);
  pModel->applyAssignments();

  //the model
  if (mReducedModel)
    pModel->calculateDerivativesX(ydot);
  else
    pModel->calculateDerivatives(ydot);

  //the linearized model

  //get jacobian
  pModel->calculateElasticityMatrix(1e-6, 1e-12); //TODO configure parameters
  pModel->calculateJacobianX(mJacobian);

  //empty dummy entries... to be removed later
  //C_FLOAT64 *dbl, *dblEnd = ydot + mDim[0];
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

  unsigned C_INT32 i;
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

  //debug output
  /*  std::cout << mJacobian;
    std::cout << "y: ";
    const C_FLOAT64 *cdbl, *cdblEnd = y + 2*mSystemSize;
    for (cdbl = y + mSystemSize; cdbl != cdblEnd; ++cdbl)
      std::cout << *cdbl << " ";
    std::cout << std::endl;

    std::cout << "ydot: ";
    dblEnd = ydot + 2*mSystemSize;
    for (dbl = ydot + mSystemSize; dbl != dblEnd; ++dbl)
      std::cout << *dbl << " ";
    std::cout << std::endl;*/

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

  //unsigned C_INT32 StepCounter = 1;

  bool flagProceed = true;
  C_FLOAT64 handlerFactor = 100.0 / (endTime - mTime);

  //C_FLOAT64 Percentage = 0;

  //** do the transient **
  C_FLOAT64 CompareTime = transientTime - 100 * fabs(transientTime) * DBL_EPSILON;

  if (mTime < CompareTime)
    {
      do
        {
          step(transientTime - mTime);

          if (mTime > CompareTime) break;

          /* Here we will do conditional event processing */

          /* Currently this is correct since no events are processed. */
          //CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 12);
          std::cout << "needed several steps for transient" << std::endl;
        }
      while (true);

      //mpLyapProblem->getModel()->setState(*mpCurrentState);
      //mpLyapProblem->getModel()->refreshConcentrations();
    }
  else
    {
      std::cout << "no transient" << std::endl;
    }

  //copy working array to state
  memcpy(mpState->beginIndependent(), mVariables.array(), mSystemSize * sizeof(C_FLOAT64));
  mpState->setTime(mTime);
  //copy state to model
  mpProblem->getModel()->setState(*mpState);
  mpProblem->getModel()->applyAssignments();
  mpTask->methodCallback((mTime - startTime) * handlerFactor);
  //********

  orthonormalize();
  if (mDoDivergence)
    *(mVariables.array() + mVariables.size() - 1) = 0; //divergence
  mLsodaStatus = 1; //the state has changed, we need to restart lsoda

  unsigned C_INT32 i;

  do
    {
      step(stepSize);

      orthonormalize();
      mLsodaStatus = 1; //the state has changed, we need to restart lsoda

      //process results of orthonormalisation
      for (i = 0; i < mNumExp; ++i)
        {
          mpTask->mLocalExponents[i] = log(mNorms[i]);
          mSumExponents[i] += mpTask->mLocalExponents[i];
          mpTask->mLocalExponents[i] = mpTask->mLocalExponents[i] / stepSize;
          mpTask->mExponents[i] = mSumExponents[i] / (mTime - transientTime);
        }

      //process result of divergence integration
      if (mDoDivergence)
        {
          mSumDivergence += *(mVariables.array() + mVariables.size() - 1);
          mpTask->mIntervalDivergence = *(mVariables.array() + mVariables.size() - 1) / stepSize;
          *(mVariables.array() + mVariables.size() - 1) = 0;
          mpTask->mAverageDivergence = mSumDivergence / (mTime - transientTime);
        }

      //       std::cout << mTime << " "
      //               << mpTask->mLocalExponents[0] << " " << mSumExponents[0]
      //               << " " << mpTask->mExponents[0] <<  std::endl;

      //copy working array to state
      memcpy(mpState->beginIndependent(), mVariables.array(), mSystemSize * sizeof(C_FLOAT64));
      mpState->setTime(mTime);
      //copy state to model
      mpProblem->getModel()->setState(*mpState);
      mpProblem->getModel()->applyAssignments();
      flagProceed &= mpTask->methodCallback((mTime - startTime) * handlerFactor);
    }
  while ((mTime < endTime) && flagProceed);

  return true;
}

void CLyapWolfMethod::orthonormalize()
{
  //TODO generalize
  C_FLOAT64 *dbl, *dblEnd;

  dbl = mVariables.array() + mSystemSize;
  dblEnd = dbl + mSystemSize;
  mNorms[0] = norm(dbl, dblEnd);
  scalarmult(dbl, dblEnd, 1 / mNorms[0]);

  unsigned C_INT32 i, j;
  for (i = 1; i < mNumExp; ++i)
    {
      /*      C_FLOAT64 norm = 0;
            C_FLOAT64 *dbl, *dblEnd = mVariables.array() + (i+2) * mSystemSize;
            for (dbl = mVariables.array() + (i+1)*mSystemSize; dbl != dblEnd; ++dbl)
              norm += *dbl * *dbl;
            mNorms[i] = sqrt(norm);
            std::cout << mNorms[0] << std::endl;
            for (dbl = mVariables.array() + (i+1)*mSystemSize; dbl != dblEnd; ++dbl)
              *dbl /= mNorms[i];*/
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
  assert (pLP);

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
