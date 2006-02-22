/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CLsodaMethod.cpp,v $
   $Revision: 1.36 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/02/22 15:35:46 $
   End CVS Header */

#include "copasi.h"

#include "CTrajectoryMethod.h"
#include "model/CModel.h"
#include "model/CState.h"

CLsodaMethod::CLsodaMethod(const CCopasiContainer * pParent):
    CTrajectoryMethod(CCopasiMethod::deterministic, pParent),
    mpStateC(NULL),
    mpStateR(NULL),
    mpEval(NULL),
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
    mpStateC(NULL),
    mpStateR(NULL),
    mpEval(NULL),
    mY(NULL)
{}

CLsodaMethod::~CLsodaMethod()
{
  pdelete(mpStateC);
  pdelete(mpStateR);
}

void CLsodaMethod::step(const double & deltaT)
{
  if (!mDim) //just do nothing if there are no variables
    {
      mTime = mTime + deltaT;
      if (mpStateC)
        {
          mpStateC->setTime(mTime);
          *mpCurrentState = *mpStateC;
        }
      else
        {
          mpStateR->setTime(mTime);
          *mpCurrentState = *mpStateR;
        }

      return;
    }

  C_FLOAT64 EndTime = mTime + deltaT;
  C_INT one = 1;
  C_INT DSize = mDWork.size();
  C_INT ISize = mIWork.size();

  mLSODA(&EvalF,           //  1. evaluate F
         mDim,             //  2. number of variables
         mY ,           //  3. the array of current concentrations
         &mTime,           //  4. the current time
         &EndTime,         //  5. the final time
         &one,             //  6. scalar error control
         &mRtol,           //  7. relative tolerance array
         &mAtol,           //  8. absolute tolerance array
         &mState,          //  9. output by overshoot & interpolatation
         &mLsodaStatus,    // 10. the state control variable
         &one,             // 11. futher options (one)
         mDWork.array(),   // 12. the double work array
         &DSize,           // 13. the double work array size
         mIWork.array(),   // 14. the int work array
         &ISize,           // 15. the int work array size
         NULL,             // 16. evaluate J (not given)
         &mJType);       // 17. the type of jacobian calculate (2)

  if (mLsodaStatus == -1) mLsodaStatus = 2;

  if ((mLsodaStatus != 1) && (mLsodaStatus != 2) && (mLsodaStatus != -1))
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 6, mErrorMsg.str().c_str());
    }

  if (mpStateC)
    {
      mpStateC->setTime(mTime);
      *mpCurrentState = *mpStateC;
    }
  else
    {
      mpStateR->setTime(mTime);
      mpStateR->updateDependentNumbers();
      *mpCurrentState = *mpStateR;
    }

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
  pdelete(mpStateC);
  pdelete(mpStateR);

  if (mReducedModel)
    {
      mpStateR = new CStateX(*initialState);
      mDim[0] = mpStateR->getVariableNumberSize();
      mY = const_cast< C_FLOAT64 * >(mpStateR->getVariableNumberVector().array());
      mTime = mpStateR->getTime();
      mpEval = &CLsodaMethod::evalR;
    }
  else
    {
      mpStateC = new CState(*initialState);
      mDim[0] = mpStateC->getVariableNumberSize();
      mY = const_cast< C_FLOAT64 * >(mpStateC->getVariableNumberVector().array());
      mTime = mpStateC->getTime();
      mpEval = &CLsodaMethod::evalC;
    }

  mYdot.resize(mDim[0]);

  /* Configure lsoda */
  mReducedModel = * getValue("Integrate Reduced Model").pBOOL;
  mRtol = * getValue("LSODA.RelativeTolerance").pUDOUBLE;
  mDefaultAtol = * getValue("Use Default Absolute Tolerance").pBOOL;
  if (mDefaultAtol)
    {
      mAtol = getDefaultAtol(initialState->getModel());
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

void CLsodaMethod::EvalF(const C_INT * n, const double * t, const double * y, double * ydot)
{static_cast<CLsodaMethod *>((void *) n[1])->evalF(t, y, ydot);}

void CLsodaMethod::evalF(const double * t, const double * y, double * ydot)
{(*this.*mpEval)(*t, y, ydot);}

void CLsodaMethod::evalC(const C_FLOAT64 t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{
  assert (y == mY);
  mpStateC->setTime(t);

  const_cast<CModel *>(mpStateC->getModel())->getDerivatives_particles(mpStateC, ydot);

  return;
}

void CLsodaMethod::evalR(const C_FLOAT64 t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{
  assert (y == mY);
  mpStateR->setTime(t);

  const_cast<CModel *>(mpStateR->getModel())->getDerivativesX_particles(mpStateR, ydot);

  return;
}
