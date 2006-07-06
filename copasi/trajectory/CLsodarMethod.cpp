/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/Attic/CLsodarMethod.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/07/06 17:03:56 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CLsodarMethod.h"
#include "CTrajectoryProblem.h"
#include "model/CModel.h"
#include "model/CState.h"

CLsodarMethod::CLsodarMethod(const CCopasiContainer * pParent):
    CTrajectoryMethod(CCopasiMethod::LSODAR, pParent),
    mpState(NULL),
    mY(NULL)
{
  mDim[1] = (C_INT) (void *) this;
  initializeParameter();
}

CLsodarMethod::CLsodarMethod(const CLsodarMethod & src,
                             const CCopasiContainer * pParent):
    CTrajectoryMethod(src, pParent),
    mpState(NULL),
    mY(NULL)
{
  mDim[1] = (C_INT) (void *) this;
  initializeParameter();
}

CLsodarMethod::~CLsodarMethod()
{
  pdelete(mpState);
}

void CLsodarMethod::initializeParameter()
{
  CCopasiParameter *pParm;

  assertParameter("Integrate Reduced Model", CCopasiParameter::BOOL, (bool) true);
  assertParameter("Relative Tolerance", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-006);
  assertParameter("Use Default Absolute Tolerance", CCopasiParameter::BOOL, (bool) true);
  assertParameter("Absolute Tolerance", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e009);
  assertParameter("Adams Max Order", CCopasiParameter::UINT, (unsigned C_INT32) 12);
  assertParameter("BDF Max Order", CCopasiParameter::UINT, (unsigned C_INT32) 5);
  assertParameter("Max Internal Steps", CCopasiParameter::UINT, (unsigned C_INT32) 10000);

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("LSODA.RelativeTolerance")) != NULL)
    {
      setValue("Relative Tolerance", *pParm->getValue().pUDOUBLE);
      removeParameter("LSODA.RelativeTolerance");

      if ((pParm = getParameter("LSODA.AbsoluteTolerance")) != NULL)
        {
          setValue("Absolute Tolerance", *pParm->getValue().pUDOUBLE);
          removeParameter("LSODA.AbsoluteTolerance");
        }

      if ((pParm = getParameter("LSODA.AdamsMaxOrder")) != NULL)
        {
          setValue("Adams Max Order", *pParm->getValue().pUINT);
          removeParameter("LSODA.AdamsMaxOrder");
        }

      if ((pParm = getParameter("LSODA.BDFMaxOrder")) != NULL)
        {
          setValue("BDF Max Order", *pParm->getValue().pUINT);
          removeParameter("LSODA.BDFMaxOrder");
        }

      if ((pParm = getParameter("LSODA.MaxStepsInternal")) != NULL)
        {
          setValue("Max Internal Steps", *pParm->getValue().pUINT);
          removeParameter("LSODA.MaxStepsInternal");
        }
    }
}

bool CLsodarMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

void CLsodarMethod::step(const double & deltaT)
{
  if (!mDim[0]) //just do nothing if there are no variables
    {
      mTime = mTime + deltaT;
      mpState->setTime(mTime);
      *mpCurrentState = *mpState;

      return;
    }

  C_FLOAT64 EndTime = mTime + deltaT;
  C_INT one = 1;
  C_INT DSize = mDWork.size();
  C_INT ISize = mIWork.size();

  mLSODAR(&EvalF,          //  1. evaluate F
          mDim,            //  2. number of variables
          mY,              //  3. the array of current concentrations
          &mTime,          //  4. the current time
          &EndTime,        //  5. the final time
          &one,            //  6. scalar error control
          &mRtol,          //  7. relative tolerance array
          &mAtol,          //  8. absolute tolerance array
          &mState,         //  9. output by overshoot & interpolatation
          &mLsodarStatus,  // 10. the state control variable
          &one,            // 11. further options (one)
          mDWork.array(),  // 12. the double work array
          &DSize,          // 13. the double work array size
          mIWork.array(),  // 14. the int work array
          &ISize,          // 15. the int work array size
          NULL,            // 16. evaluate J (not given)
          &mJType,         // 17. type of j evaluation 2 internal full matrix
          &EvalR,          // 18. evaluate constraint functions
          &mNumRoots,      // 19. number of constraint functions g(i)
          mRoots.array()); // 20. integer array of length NG for output of root information

  if (mLsodarStatus == -1) mLsodarStatus = 2;

  if ((mLsodarStatus != 1) && (mLsodarStatus != 2) && (mLsodarStatus != -1))
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 6, mErrorMsg.str().c_str());
    }

  mpState->setTime(mTime);
  *mpCurrentState = *mpState;

  return;
}

void CLsodarMethod::start(const CState * initialState)
{
  /* Reset lsodar */
  mLsodarStatus = 1;
  mState = 1;
  mJType = 2;
  mErrorMsg.str("");
  mLSODAR.setOstream(mErrorMsg);

  /* Release previous state and make the initialState the current */
  pdelete(mpState);
  mpState = new CState(*initialState);
  mY = mpState->beginIndependent();
  mTime = mpState->getTime();

  mReducedModel = * getValue("Integrate Reduced Model").pBOOL;
  if (mReducedModel)
    {
      mpState->setUpdateDependentRequired(true);
      mDim[0] = mpState->getNumIndependent();
    }
  else
    {
      mpState->setUpdateDependentRequired(false);
      mDim[0] = mpState->getNumVariable();
    }

  mYdot.resize(mDim[0]);

  mNumRoots = 0;
  mRoots.resize(mNumRoots);

  /* Configure lsodar */
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

C_FLOAT64 CLsodarMethod::getDefaultAtol(const CModel * pModel) const
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

void CLsodarMethod::EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{static_cast<CLsodarMethod *>((void *) n[1])->evalF(t, y, ydot);}

void CLsodarMethod::evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{
  assert (y == mY);

  mpState->setTime(*t);

  CModel * pModel = mpProblem->getModel();
  pModel->setState(*mpState);
  pModel->applyAssignments();

  if (mReducedModel)
    pModel->calculateDerivativesX(ydot);
  else
    pModel->calculateDerivatives(ydot);

  return;
}

void CLsodarMethod::EvalR(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y,
                          const C_INT * nr, const double * r)
{static_cast<CLsodarMethod *>((void *) n[1])->evalR(t, y, nr, r);}

void CLsodarMethod::evalR(const C_FLOAT64 * t, const C_FLOAT64 * y, const C_INT * nr, const double * r)
{};
