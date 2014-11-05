// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CLsodaMethod.h"
#include "CTrajectoryProblem.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModel.h"
#include "model/CState.h"

CLsodaMethod::CLsodaMethod(const CCopasiMethod::SubType & subType,
                           const CCopasiContainer * pParent):
  CTrajectoryMethod(subType, pParent),
  mMethodState(),
  mY(NULL),
  mRootMask(),
  mTargetTime(0.0),
  mRootCounter(0),
  mPeekAheadMode(false)
{
  assert((void *) &mData == (void *) &mData.dim);

  mData.pMethod = this;
  initializeParameter();
}

CLsodaMethod::CLsodaMethod(const CLsodaMethod & src,
                           const CCopasiContainer * pParent):
  CTrajectoryMethod(src, pParent),
  mMethodState(),
  mY(NULL),
  mRootMask(src.mRootMask),
  mTargetTime(src.mTargetTime),
  mRootCounter(src.mRootCounter),
  mPeekAheadMode(src.mPeekAheadMode)
{
  assert((void *) &mData == (void *) &mData.dim);

  mData.pMethod = this;
  initializeParameter();
}

CLsodaMethod::~CLsodaMethod()
{}

void CLsodaMethod::initializeParameter()
{
  CCopasiParameter *pParm;

  mpReducedModel =
    assertParameter("Integrate Reduced Model", CCopasiParameter::BOOL, (bool) false)->getValue().pBOOL;
  mpRelativeTolerance =
    assertParameter("Relative Tolerance", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-6)->getValue().pUDOUBLE;
  mpAbsoluteTolerance =
    assertParameter("Absolute Tolerance", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-12)->getValue().pUDOUBLE;
  mpMaxInternalSteps =
    assertParameter("Max Internal Steps", CCopasiParameter::UINT, (unsigned C_INT32) 10000)->getValue().pUINT;

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("LSODA.RelativeTolerance")) != NULL)
    {
      *mpRelativeTolerance = *pParm->getValue().pUDOUBLE;
      removeParameter("LSODA.RelativeTolerance");

      if ((pParm = getParameter("LSODA.AbsoluteTolerance")) != NULL)
        {
          *mpAbsoluteTolerance = *pParm->getValue().pUDOUBLE;
          removeParameter("LSODA.AbsoluteTolerance");
        }

      if ((pParm = getParameter("LSODA.AdamsMaxOrder")) != NULL)
        {
          removeParameter("LSODA.AdamsMaxOrder");
        }

      if ((pParm = getParameter("LSODA.BDFMaxOrder")) != NULL)
        {
          removeParameter("LSODA.BDFMaxOrder");
        }

      if ((pParm = getParameter("LSODA.MaxStepsInternal")) != NULL)
        {
          *mpMaxInternalSteps = *pParm->getValue().pUINT;
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
          C_FLOAT64 OldValue = *mpAbsoluteTolerance;
          CCopasiDataModel* pDataModel = getObjectDataModel();
          assert(pDataModel != NULL);
          CModel * pModel = pDataModel->getModel();

          if (pModel == NULL)
            // The default
            NewValue = 1.e-12;
          else
            {
              const CCopasiVectorNS< CCompartment > & Compartment = pModel->getCompartments();
              size_t i, imax;
              C_FLOAT64 Volume = std::numeric_limits< C_FLOAT64 >::max();

              for (i = 0, imax = Compartment.size(); i < imax; i++)
                if (Compartment[i]->getValue() < Volume)
                  Volume = Compartment[i]->getValue();

              if (Volume == std::numeric_limits< C_FLOAT64 >::max())
                // The default
                NewValue = 1.e-12;
              else
                // Invert the scaling as best as we can
                NewValue = OldValue / (Volume * pModel->getQuantity2NumberFactor());
            }
        }

      *mpAbsoluteTolerance = NewValue;
      removeParameter("Use Default Absolute Tolerance");
    }

  // These parameters are no longer supported.
  removeParameter("Adams Max Order");
  removeParameter("BDF Max Order");
}

bool CLsodaMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

// virtual
void CLsodaMethod::stateChanged()
{
  if (!mNoODE && mLsodaStatus != 1)
    {
      // Compare the independent state variables
      // This an be done directly by comparing mMethodState and *mpCurrentState
      C_FLOAT64 *pMethod = mY;
      C_FLOAT64 *pMethodEnd = pMethod + mData.dim;
      C_FLOAT64 *pCurrent = mpCurrentState->beginIndependent();

      for (; pMethod != pMethodEnd; ++pMethod, ++pCurrent)
        {
          // We may need to use the absolute and relative tolerance
          if (*pMethod != *pCurrent)
            {
              mLsodaStatus = 1;

              break;
            }
        }

      // Bug 2106 It is not sufficient to check for the state variables we also need
      // to check for fixed values which are event targets.
      pMethod = mMethodState.beginFixed();
      pMethodEnd = mMethodState.endFixed();
      pCurrent = mpCurrentState->beginFixed();

      for (; pMethod != pMethodEnd; ++pMethod, ++pCurrent)
        {
          // We may need to use the absolute and relative tolerance
          if (*pMethod != *pCurrent)
            {
              mLsodaStatus = 1;

              break;
            }
        }

      if (mLsodaStatus != 1)
        {
          // Compare the rates of the independent state variables
          // we need to call evalF for mMethodState and *mpCurrentState and compare the returned rates.
          CVector< C_FLOAT64 > MethodRate(mData.dim);
          CVector< C_FLOAT64 > CurrentRate(mData.dim);

          evalF(&mTime, mY, MethodRate.array());

          mMethodState = *mpCurrentState;
          mTime = mMethodState.getTime();

          evalF(&mTime, mY, CurrentRate.array());

          pMethod = MethodRate.array();
          pMethodEnd = pMethod + mData.dim;
          pCurrent = CurrentRate.array();

          for (; pMethod != pMethodEnd; ++pMethod, ++pCurrent)
            {
              // We may need to use the absolute and relative tolerance
              if (*pMethod != *pCurrent)
                {
                  mLsodaStatus = 1;
                  break;
                }
            }
        }
    }

  mMethodState = *mpCurrentState;
  mTime = mMethodState.getTime();

  mPeekAheadMode = false;
  destroyRootMask();
}

CTrajectoryMethod::Status CLsodaMethod::step(const double & deltaT)
{
  if (mData.dim == 0 && mNumRoots == 0) //just do nothing if there are no variables
    {
      mTime = mTime + deltaT;
      mMethodState.setTime(mTime);
      *mpCurrentState = mMethodState;

      return NORMAL;
    }

  C_FLOAT64 EndTime = mTime + deltaT;

  if (mTargetTime != EndTime)
    {
      // We have a new end time and reset the root counter.
      mTargetTime = EndTime;
      mRootCounter = 0;
    }
  else
    {
      // We are called with the same end time which means a root has previously been
      // found. We increase the root counter and check whether the limit is reached.
      mRootCounter++;

      if (mRootCounter > *mpMaxInternalSteps)
        {
          return FAILURE;
        }
    }

  C_INT ITOL = 2; // mRtol scalar, mAtol vector
  C_INT one = 1;
  C_INT DSize = (C_INT) mDWork.size();
  C_INT ISize = (C_INT) mIWork.size();

  // The return status of the integrator.
  Status Status = NORMAL;

  if (mRoots.size() > 0)
    {
      mLSODAR(&EvalF, //  1. evaluate F
              &mData.dim, //  2. number of variables
              mY, //  3. the array of current concentrations
              &mTime, //  4. the current time
              &EndTime, //  5. the final time
              &ITOL, //  6. error control
              &mRtol, //  7. relative tolerance array
              mAtol.array(), //  8. absolute tolerance array
              &mState, //  9. output by overshoot & interpolation
              &mLsodaStatus, // 10. the state control variable
              &one, // 11. further options (one)
              mDWork.array(), // 12. the double work array
              &DSize, // 13. the double work array size
              mIWork.array(), // 14. the int work array
              &ISize, // 15. the int work array size
              &EvalJ, // 16. evaluate J (not given)
              &mJType, // 17. type of j evaluation 2 internal full matrix
              &EvalR, // 18. evaluate constraint functions
              &mNumRoots, // 19. number of constraint functions g(i)
              mRoots.array()); // 20. integer array of length NG for output of root information

      // There exist situations where LSODAR reports status = 3, which are actually status = -33
      // Obviously the trivial case is where LSODAR did not advance at all, i.e, the start time
      // equals the current time. It may also happen that a very small steps has been taken in
      // we reset short before we reach the internal step limit.
      if (mLsodaStatus == 3 &&
          (mRootCounter > 0.99 * *mpMaxInternalSteps ||
           mTime == mpCurrentState->getTime()))
        {
          mLsodaStatus = -33;
          mRootCounter = 0;
        }

      switch (mLsodaStatus)
        {
          case -33:

            switch (mRootMasking)
              {
                case NONE:
                case DISCRETE:
                  // Reset the integrator to the state before the failed integration.

                  mMethodState = *mpCurrentState;
                  mTime = mMethodState.getTime();
                  mLsodaStatus = 1;

                  // Create a mask which hides all roots being constant and zero.
                  createRootMask();
                  break;

                case ALL:
                  break;
              }

            break;

          case 3:

            // If mLsodaStatus == 3 we have found a root. This needs to be indicated to
            // the caller as it is not sufficient to rely on the fact that T < TOUT
            if (mLsodaStatus == 3)
              {
                // It is sufficient to switch to 2. Eventual state changes due to events
                // are indicated via the method stateChanged()
                mLsodaStatus = 2;
                Status = ROOT;
              }

            // To detect simultaneous roots we have to peek ahead, i.e., continue
            // integration until the state changes are larger that the relative
            if (!mPeekAheadMode)
              {
                Status = peekAhead();
              }

            // The break statement is intentionally missing since we
            // have to continue to check the root masking state.
          default:

            switch (mRootMasking)
              {
                case NONE:
                case DISCRETE:
                  break;

                case ALL:
                {
                  const bool * pDiscrete = mDiscreteRoots.array();
                  bool * pMask = mRootMask.array();
                  bool * pMaskEnd = pMask + mNumRoots;
                  bool Destroy = true;

                  for (; pMask != pMaskEnd; ++pMask, ++pDiscrete)
                    {
                      if (*pMask)
                        {
                          if (*pDiscrete)
                            {
                              Destroy = false;
                            }
                          else
                            {
                              *pMask = false;
                            }
                        }
                    }

                  if (Destroy)
                    {
                      destroyRootMask();
                    }
                  else
                    {
                      mRootMasking = DISCRETE;
                    }

                  // We have to restart the integrator
                  mLsodaStatus = 1;
                }

                break;
              }

            break;
        }
    }
  else
    {
      mLSODA(&EvalF, //  1. evaluate F
             &mData.dim, //  2. number of variables
             mY, //  3. the array of current concentrations
             &mTime, //  4. the current time
             &EndTime, //  5. the final time
             &ITOL, //  6. error control
             &mRtol, //  7. relative tolerance array
             mAtol.array(), //  8. absolute tolerance array
             &mState, //  9. output by overshoot & interpolation
             &mLsodaStatus, // 10. the state control variable
             &one, // 11. further options (one)
             mDWork.array(), // 12. the double work array
             &DSize, // 13. the double work array size
             mIWork.array(), // 14. the int work array
             &ISize, // 15. the int work array size
             EvalJ, // 16. evaluate J (not given)
             &mJType);        // 17. the type of jacobian calculate (2)
    }

  // Why did we ignore this error?
  // if (mLsodaStatus == -1) mLsodaStatus = 2;

  mMethodState.setTime(mTime);

  if (!mPeekAheadMode)
    {
      *mpCurrentState = mMethodState;
    }

  if ((mLsodaStatus <= 0))
    {
      Status = FAILURE;
      mPeekAheadMode = false;
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 6, mErrorMsg.str().c_str());
    }

  if (!mMethodState.isValid())
    {
      Status = FAILURE;
      mPeekAheadMode = false;
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 25, mTime);
    }

  return Status;
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

  /* Release previous state and make the initialState the current */
  mMethodState = *initialState;
  mTime = mMethodState.getTime();
  mTargetTime = mTime;
  mRootCounter = 0;
  mPeekAheadMode = false;

  mNumRoots = (C_INT) mpModel->getNumRoots();
  mRoots.resize(mNumRoots);
  destroyRootMask();

  if (*mpReducedModel)
    mData.dim = (C_INT) mMethodState.getNumIndependent();
  else
    mData.dim = (C_INT)(mMethodState.getNumIndependent() + mpModel->getNumDependentReactionMetabs());

  // When we have roots we need to add an artificial ODE dDummy/dt = 1
  if (mData.dim == 0 && mNumRoots != 0)
    {
      mData.dim = 1;
      mNoODE = true;
      mAtol.resize(1);
      mAtol[0] = *mpAbsoluteTolerance;
      mDummy = 0;
      mY = &mDummy;
    }
  else
    {
      mNoODE = false;
      mAtol = mpModel->initializeAtolVector(*mpAbsoluteTolerance, *mpReducedModel);
      mY = mMethodState.beginIndependent();
    }

  mYdot.resize(mData.dim);

  /* Configure lsoda(r) */
  mRtol = *mpRelativeTolerance;

  mDWork.resize(22 + mData.dim * std::max<C_INT>(16, mData.dim + 9) + 3 * mNumRoots);
  mDWork[4] = mDWork[5] = mDWork[6] = mDWork[7] = mDWork[8] = mDWork[9] = 0.0;
  mIWork.resize(20 + mData.dim);
  mIWork[4] = mIWork[6] = mIWork[9] = 0;

  mIWork[5] = *mpMaxInternalSteps;
  mIWork[7] = 12;
  mIWork[8] = 5;

  if (mNumRoots > 0)
    {
      mLSODAR.setOstream(mErrorMsg);
      mDiscreteRoots.resize(mNumRoots);

      CMathTrigger::CRootFinder * const* ppRootFinder = mpModel->getRootFinders().array();
      CMathTrigger::CRootFinder * const* ppRootFinderEnd = ppRootFinder + mNumRoots;
      bool * pDiscrete = mDiscreteRoots.array();

      for (; ppRootFinder != ppRootFinderEnd; ++ppRootFinder, ++pDiscrete)
        {
          *pDiscrete = (*ppRootFinder)->isDiscrete();
        }
    }
  else
    {
      mLSODA.setOstream(mErrorMsg);
    }

  return;
}

void CLsodaMethod::EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{static_cast<Data *>((void *) n)->pMethod->evalF(t, y, ydot);}

void CLsodaMethod::evalF(const C_FLOAT64 * t, const C_FLOAT64 * /* y */, C_FLOAT64 * ydot)
{
  // If we have no ODEs add a constant one.
  if (mNoODE)
    {
      *ydot = 1.0;
      return;
    }

  mMethodState.setTime(*t);

  mpModel->setState(mMethodState);
  mpModel->updateSimulatedValues(*mpReducedModel);

  if (*mpReducedModel)
    mpModel->calculateDerivativesX(ydot);
  else
    mpModel->calculateDerivatives(ydot);

  return;
}

void CLsodaMethod::EvalR(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y,
                         const C_INT * nr, C_FLOAT64 * r)
{static_cast<Data *>((void *) n)->pMethod->evalR(t, y, nr, r);}

void CLsodaMethod::evalR(const C_FLOAT64 *  t, const C_FLOAT64 *  /* y */,
                         const C_INT *  nr, C_FLOAT64 * r)
{
  assert(*nr == (C_INT) mRoots.size());

  mMethodState.setTime(*t);

  mpModel->setState(mMethodState);

  if (*mpReducedModel)
    {
      mpModel->updateSimulatedValues(*mpReducedModel);
    }

  CVectorCore< C_FLOAT64 > RootValues(*nr, r);

  mpModel->evaluateRoots(RootValues, true);

  if (mRootMasking != NONE)
    {
      maskRoots(RootValues);
    }
};

// static
void CLsodaMethod::EvalJ(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y,
                         const C_INT * ml, const C_INT * mu, C_FLOAT64 * pd, const C_INT * nRowPD)
{static_cast<Data *>((void *) n)->pMethod->evalJ(t, y, ml, mu, pd, nRowPD);}

// virtual
void CLsodaMethod::evalJ(const C_FLOAT64 * t, const C_FLOAT64 * y,
                         const C_INT * ml, const C_INT * mu, C_FLOAT64 * pd, const C_INT * nRowPD)
{
  // TODO Implement me.
}

void CLsodaMethod::maskRoots(CVectorCore< C_FLOAT64 > & rootValues)
{
  const bool *pMask = mRootMask.array();
  const bool *pMaskEnd = pMask + mRootMask.size();
  C_FLOAT64 * pRoot = rootValues.array();

  for (; pMask != pMaskEnd; ++pMask, ++pRoot)
    {
      if (*pMask)
        {
          *pRoot = 1.0;
        }
    }
}

void CLsodaMethod::createRootMask()
{
  size_t NumRoots = mRoots.size();
  mRootMask.resize(NumRoots);
  CVector< C_FLOAT64 > RootValues;
  RootValues.resize(NumRoots);
  CVector< C_FLOAT64 > RootDerivatives;
  RootDerivatives.resize(NumRoots);

  mpModel->setState(mMethodState);

  if (*mpReducedModel)
    {
      mpModel->updateSimulatedValues(*mpReducedModel);
    }

  mpModel->evaluateRoots(RootValues, true);
  mpModel->calculateRootDerivatives(RootDerivatives);

  bool *pMask = mRootMask.array();
  bool *pMaskEnd = pMask + mRootMask.size();
  C_FLOAT64 * pRootValue = RootValues.array();
  C_FLOAT64 * pRootDerivative = RootDerivatives.array();

  for (; pMask != pMaskEnd; ++pMask, ++pRootValue, ++pRootDerivative)
    {
      *pMask = (fabs(*pRootDerivative) < *mpAbsoluteTolerance ||
                fabs(*pRootValue) < 1e3 * std::numeric_limits< C_FLOAT64 >::min()) ? true : false;
    }

  mRootMasking = ALL;
}

void CLsodaMethod::destroyRootMask()
{
  mRootMask.resize(0);
  mRootMasking = NONE;
}

CTrajectoryMethod::Status CLsodaMethod::peekAhead()
{
  // Save the current state
  mMethodState.setTime(mTime);

  CState StartState = mMethodState;

  CState ResetState = mMethodState;
  mLSODAR.saveState();
  CVector< C_FLOAT64 > ResetDWork = mDWork;
  CVector< C_INT > ResetIWork = mIWork;

  mPeekAheadMode = true;
  Status PeekAheadStatus = ROOT;

  CVector< C_INT > CombinedRoots = mRoots;

  C_FLOAT64 MaxPeekAheadTime = std::max(mTargetTime, mTime * (1.0 + 2.0 * *mpRelativeTolerance));

  while (mPeekAheadMode)
    {
      switch (step(MaxPeekAheadTime - mTime))
        {
          case ROOT:
          {
            // Check whether the new state is within the tolerances
            C_FLOAT64 * pOld = StartState.beginIndependent();
            C_FLOAT64 * pOldEnd = pOld + mData.dim;
            C_FLOAT64 * pNew = mMethodState.beginIndependent();
            C_FLOAT64 * pAtol = mAtol.array();

            for (; pOld != pOldEnd; ++pOld, ++pNew, ++pAtol)
              {
                if ((2.0 * fabs(*pNew - *pOld) > (fabs(*pNew) + fabs(*pOld)) * *mpRelativeTolerance) &&
                    fabs(*pNew) > *pAtol &&
                    fabs(*pOld) > *pAtol)
                  {
                    break;
                  }
              }

            if (pOld != pOldEnd ||
                (mTime > StartState.getTime() * (1.0 + *mpRelativeTolerance) &&
                 fabs(mTime) > *mpAbsoluteTolerance &&
                 fabs(StartState.getTime()) > *mpAbsoluteTolerance))
              {
                mPeekAheadMode = false;
              }
            else
              {
                ResetState = mMethodState;
                mLSODAR.saveState();
                ResetDWork = mDWork;
                ResetIWork = mIWork;

                // Combine all the roots
                C_INT * pRoot = mRoots.array();
                C_INT * pRootEnd = pRoot + mRoots.size();
                C_INT * pCombinedRoot = CombinedRoots.array();

                for (; pRoot != pRootEnd; ++pRoot, ++pCombinedRoot)
                  {
                    if (*pRoot > 0)
                      {
                        *pCombinedRoot = 1;
                      }
                  }
              }
          }

          break;

          case FAILURE:
            mPeekAheadMode = false;
            PeekAheadStatus = FAILURE;
            break;

          case NORMAL:

            if (mRootMasking != ALL)
              {
                mPeekAheadMode = false;
              }

            break;
        }
    }

  // Reset the integrator to the saved state
  mMethodState = ResetState;
  mTime = mMethodState.getTime();
  mLSODAR.resetState();
  mDWork = ResetDWork;
  mIWork = ResetIWork;

  mPeekAheadMode = false;

  mRoots = CombinedRoots;

  return PeekAheadStatus;
}
