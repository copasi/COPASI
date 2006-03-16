/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CLsodaMethod.cpp,v $
   $Revision: 1.38 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2006/03/16 10:07:05 $
   End CVS Header */

#include "copasi.h"

#include "CTrajectoryMethod.h"
#include "CTrajectoryProblem.h"
#include "model/CModel.h"
#include "model/CState.h"

CLsodaMethod::CLsodaMethod(const CCopasiContainer * pParent):
    CTrajectoryMethod(CCopasiMethod::deterministic, pParent),
    mpState(NULL),
    mY(NULL)
{
  mDim[1] = (C_INT) (void *) this;

  addParameter("Integrate Reduced Model",
               CCopasiParameter::BOOL, (bool) true);
  addParameter("LSODA.RelativeTolerance",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-006);
  addParameter("Use Default Absolute Tolerance",
               CCopasiParameter::BOOL, (bool) true);
  addParameter("LSODA.AbsoluteTolerance",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e009);
  addParameter("LSODA.AdamsMaxOrder",
               CCopasiParameter::UINT, (unsigned C_INT32) 12);
  addParameter("LSODA.BDFMaxOrder",
               CCopasiParameter::UINT, (unsigned C_INT32) 5);
  addParameter("LSODA.MaxStepsInternal",
               CCopasiParameter::UINT, (unsigned C_INT32) 10000);
}

CLsodaMethod::CLsodaMethod(const CLsodaMethod & src,
                           const CCopasiContainer * pParent):
    CTrajectoryMethod(src, pParent),
    mpState(NULL),
    mY(NULL)
{}

CLsodaMethod::~CLsodaMethod()
{
  pdelete(mpState);
}

void CLsodaMethod::step(const double & deltaT)
{
  if (!mDim) //just do nothing if there are no variables
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

  mLSODA(&EvalF,             //  1. evaluate F
         mDim,               //  2. number of variables
         mY ,             //  3. the array of current concentrations
         &mTime,             //  4. the current time
         &EndTime,           //  5. the final time
         &one,               //  6. scalar error control
         &mRtol,             //  7. relative tolerance array
         &mAtol,             //  8. absolute tolerance array
         &mState,            //  9. output by overshoot & interpolatation
         &mLsodaStatus,      // 10. the state control variable
         &one,               // 11. futher options (one)
         mDWork.array(),     // 12. the double work array
         &DSize,             // 13. the double work array size
         mIWork.array(),     // 14. the int work array
         &ISize,             // 15. the int work array size
         NULL,               // 16. evaluate J (not given)
         &mJType);       // 17. the type of jacobian calculate (2)

  if (mLsodaStatus == -1) mLsodaStatus = 2;

  if ((mLsodaStatus != 1) && (mLsodaStatus != 2) && (mLsodaStatus != -1))
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 6, mErrorMsg.str().c_str());
    }

  mpState->setTime(mTime);
  *mpCurrentState = *mpState;

  return;
}

void CLsodaMethod::start(const CState * initialState)
{
  /* Reset lsoda */
  mLsodaStatus = 1;
  mState = 1;
  mJType = 2;
  mErrorMsg.str("");
  mLSODA.setOstream(mErrorMsg);

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

  /* Configure lsoda */
  mRtol = * getValue("LSODA.RelativeTolerance").pUDOUBLE;
  mDefaultAtol = * getValue("Use Default Absolute Tolerance").pBOOL;
  if (mDefaultAtol)
    {
      mAtol = getDefaultAtol(mpProblem->getModel());
      setValue("LSODA.AbsoluteTolerance", mAtol);
    }
  else
    mAtol = * getValue("LSODA.AbsoluteTolerance").pUDOUBLE;

  mDWork.resize(22 + mDim[0] * std::max<C_INT>(16, mDim[0] + 9));
  mDWork[4] = mDWork[5] = mDWork[6] = mDWork[7] = mDWork[8] = mDWork[9] = 0.0;
  mIWork.resize(20 + mDim[0]);
  mIWork[4] = mIWork[6] = mIWork[9] = 0;

  mIWork[5] = * getValue("LSODA.MaxStepsInternal").pUINT;
  mIWork[7] = * getValue("LSODA.AdamsMaxOrder").pUINT;
  mIWork[8] = * getValue("LSODA.BDFMaxOrder").pUINT;

  return;
}

C_FLOAT64 CLsodaMethod::getDefaultAtol(const CModel * pModel) const
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

void CLsodaMethod::EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{static_cast<CLsodaMethod *>((void *) n[1])->evalF(t, y, ydot);}

void CLsodaMethod::evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
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
