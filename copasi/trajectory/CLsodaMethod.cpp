/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CLsodaMethod.cpp,v $
   $Revision: 1.43 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/04 17:41:45 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CLsodaMethod.h"
#include "CTrajectoryProblem.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "model/CState.h"

CLsodaMethod::CLsodaMethod(const CCopasiContainer * pParent):
    CTrajectoryMethod(CCopasiMethod::deterministic, pParent),
    mpState(NULL),
    mY(NULL)
{
  mDim[1] = (C_INT) (void *) this;
  initializeParameter();
}

CLsodaMethod::CLsodaMethod(const CLsodaMethod & src,
                           const CCopasiContainer * pParent):
    CTrajectoryMethod(src, pParent),
    mpState(NULL),
    mY(NULL)
{
  mDim[1] = (C_INT) (void *) this;
  initializeParameter();
}

CLsodaMethod::~CLsodaMethod()
{
  pdelete(mpState);
}

void CLsodaMethod::initializeParameter()
{
  CCopasiParameter *pParm;

  assertParameter("Integrate Reduced Model", CCopasiParameter::BOOL, (bool) true);
  assertParameter("Relative Tolerance", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-6);
  assertParameter("Absolute Tolerance", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-12);
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

  // Check whether we have a method with "Use Default Absolute Tolerance"
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
          C_FLOAT64 OldValue = *getValue("Absolute Tolerance").pUDOUBLE;

          CModel * pModel = CCopasiDataModel::Global->getModel();

          if (pModel == NULL)
            // The default
            NewValue = 1.e-12;
          else
            {
              const CCopasiVectorNS< CCompartment > & Compartment = pModel->getCompartments();
              unsigned C_INT32 i, imax;
              C_FLOAT64 Volume = DBL_MAX;

              for (i = 0, imax = Compartment.size(); i < imax; i++)
                if (Compartment[i]->getValue() < Volume)
                  Volume = Compartment[i]->getValue();

              if (Volume == DBL_MAX)
                // The default
                NewValue = 1.e-12;
              else
                // Invert the scaling as best as we can
                NewValue = OldValue / (Volume * pModel->getQuantity2NumberFactor());
            }
        }

      setValue("Absolute Tolerance", NewValue);
      removeParameter("Use Default Absolute Tolerance");
    }
}

bool CLsodaMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

void CLsodaMethod::step(const double & deltaT)
{
  if (!mDim[0]) //just do nothing if there are no variables
    {
      mTime = mTime + deltaT;
      mpState->setTime(mTime);
      *mpCurrentState = *mpState;

      return;
    }

  C_FLOAT64 EndTime = mTime + deltaT;
  C_INT ITOL = 2; // mRtol scalar, mAtol vector
  C_INT one = 1;
  C_INT DSize = mDWork.size();
  C_INT ISize = mIWork.size();

  mLSODA(&EvalF,          //  1. evaluate F
         mDim,            //  2. number of variables
         mY,              //  3. the array of current concentrations
         &mTime,          //  4. the current time
         &EndTime,        //  5. the final time
         &ITOL,           //  6. error control
         &mRtol,          //  7. relative tolerance array
         mAtol.array(),   //  8. absolute tolerance array
         &mState,         //  9. output by overshoot & interpolatation
         &mLsodaStatus,   // 10. the state control variable
         &one,            // 11. futher options (one)
         mDWork.array(),  // 12. the double work array
         &DSize,          // 13. the double work array size
         mIWork.array(),  // 14. the int work array
         &ISize,          // 15. the int work array size
         NULL,            // 16. evaluate J (not given)
         &mJType);        // 17. the type of jacobian calculate (2)

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
  /* Retrieve the model to calculate */
  mpModel = mpProblem->getModel();

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
      mDim[0] = mpState->getNumIndependent() + mpModel->getNumDependentMetabs();
    }

  mYdot.resize(mDim[0]);

  /* Configure lsoda */
  mRtol = * getValue("Relative Tolerance").pUDOUBLE;
  initializeAtol();

  mDWork.resize(22 + mDim[0] * std::max<C_INT>(16, mDim[0] + 9));
  mDWork[4] = mDWork[5] = mDWork[6] = mDWork[7] = mDWork[8] = mDWork[9] = 0.0;
  mIWork.resize(20 + mDim[0]);
  mIWork[4] = mIWork[6] = mIWork[9] = 0;

  mIWork[5] = * getValue("Max Internal Steps").pUINT;
  mIWork[7] = * getValue("Adams Max Order").pUINT;
  mIWork[8] = * getValue("BDF Max Order").pUINT;

  return;
}

void CLsodaMethod::initializeAtol()
{
  C_FLOAT64 * pTolerance = getValue("Absolute Tolerance").pUDOUBLE;

  mAtol.resize(mDim[0]);
  C_FLOAT64 * pAtol = mAtol.array();
  C_FLOAT64 * pEnd = pAtol + mAtol.size();

  CModelEntity **ppEntity = mpModel->getStateTemplate().beginIndependent();
  CMetab * pMetab;

  for (; pAtol != pEnd; ++pAtol, ++ppEntity)
    {
      *pAtol = *pTolerance;

      // Rescale for metabolites as we are using particle numbers
      if ((pMetab = dynamic_cast< CMetab * >(*ppEntity)) != NULL)
        {
          *pAtol *=
            pMetab->getCompartment()->getValue() * mpModel->getQuantity2NumberFactor();
        }
    }
}

void CLsodaMethod::EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{static_cast<CLsodaMethod *>((void *) n[1])->evalF(t, y, ydot);}

void CLsodaMethod::evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{
  assert (y == mY);

  mpState->setTime(*t);

  mpModel->setState(*mpState);
  mpModel->applyAssignments();

  if (mReducedModel)
    mpModel->calculateDerivativesX(ydot);
  else
    mpModel->calculateDerivatives(ydot);

  return;
}
