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
#include "math/CMathContainer.h"
#include "model/CModel.h"
#include "model/CState.h"

CLsodaMethod::CLsodaMethod(const CCopasiMethod::SubType & subType,
                           const CCopasiContainer * pParent):
  CTrajectoryMethod(subType, pParent),
  mpReducedModel(NULL),
  mpRelativeTolerance(NULL),
  mpAbsoluteTolerance(NULL),
  mpMaxInternalSteps(NULL),
  mData(),
  mpY(NULL),
  mpYdot(NULL),
  mNumRoots(0),
  mTime(),
  mLsodaStatus(1),
  mLastSuccessState(),
  mAtol(),
  mpAtol(NULL),
  mErrorMsg(),
  mLSODA(),
  mLSODAR(),
  mTask(),
  mDWork(),
  mIWork(),
  mJType(),
  mRootMask(),
  mDiscreteRoots(),
  mRootMasking(CLsodaMethod::NONE),
  mTargetTime(),
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
  mpReducedModel(NULL),
  mpRelativeTolerance(NULL),
  mpAbsoluteTolerance(NULL),
  mpMaxInternalSteps(NULL),
  mData(src.mData),
  mpY(NULL),
  mpYdot(NULL),
  mNumRoots(src.mNumRoots),
  mTime(src.mTime),
  mLsodaStatus(src.mLsodaStatus),
  mLastSuccessState(src.mLastSuccessState),
  mAtol(src.mAtol),
  mpAtol(NULL),
  mErrorMsg(src.mErrorMsg.str()),
  mLSODA(),
  mLSODAR(),
  mTask(src.mTask),
  mDWork(src.mDWork),
  mIWork(src.mIWork),
  mJType(src.mJType),
  mRootMask(src.mRootMask),
  mDiscreteRoots(),
  mRootMasking(src.mRootMasking),
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
void CLsodaMethod::stateChange(const CMath::StateChange & change)
{
  if (change & CMath::ContinuousSimulation)
    {
      mLsodaStatus = 1;
      mTime = *mpContainerStateTime;
      mPeekAheadMode = false;

      destroyRootMask();
    }
}

CTrajectoryMethod::Status CLsodaMethod::step(const double & deltaT)
{
  C_FLOAT64 StartTime = mTime;
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
      mLastSuccessState = mContainerState;

      mLSODAR(&EvalF, //  1. evaluate F
              &mData.dim, //  2. number of variables
              mpY, //  3. the array of current concentrations
              &mTime, //  4. the current time
              &EndTime, //  5. the final time
              &ITOL, //  6. error control
              mpRelativeTolerance, //  7. relative tolerance array
              mpAtol, //  8. absolute tolerance array
              &mTask, //  9. output by overshoot & interpolation
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
           mTime == StartTime))
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

                  mContainerState = mLastSuccessState;
                  mTime = *mpContainerStateTime;
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
            // integration until the state changes are larger than the relative tolerances
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
             mpY, //  3. the array of current concentrations
             &mTime, //  4. the current time
             &EndTime, //  5. the final time
             &ITOL, //  6. error control
             mpRelativeTolerance, //  7. relative tolerance array
             mpAtol, //  8. absolute tolerance array
             &mTask, //  9. output by overshoot & interpolation
             &mLsodaStatus, // 10. the state control variable
             &one, // 11. further options (one)
             mDWork.array(), // 12. the double work array
             &DSize, // 13. the double work array size
             mIWork.array(), // 14. the int work array
             &ISize, // 15. the int work array size
             EvalJ, // 16. evaluate J (not given)
             &mJType);        // 17. the type of jacobian calculate (2)
    }

  if ((mLsodaStatus <= 0))
    {
      Status = FAILURE;
      mPeekAheadMode = false;
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 6, mErrorMsg.str().c_str());
    }

  *mpContainerStateTime = mTime;

  if (!mpContainer->isStateValid())
    {
      Status = FAILURE;
      mPeekAheadMode = false;
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 25, mTime);
    }

  return Status;
}

void CLsodaMethod::start(CVectorCore< C_FLOAT64 > & initialState)
{
  /* Reset lsoda */
  mLsodaStatus = 1;
  mTask = 1;
  mJType = 2;
  mErrorMsg.str("");

  /* Release previous state and make the initialState the current */
  mContainerState = initialState;
  mTime = *mpContainerStateTime;

  mTargetTime = mTime;
  mRootCounter = 0;
  mPeekAheadMode = false;

  mNumRoots = (C_INT) mpContainer->getRoots().size();
  mRoots.resize(mNumRoots);
  destroyRootMask();

  mAtol = mpContainer->initializeAtolVector(*mpAbsoluteTolerance, *mpReducedModel);

  // We ignore fixed event targets
  mData.dim = (C_INT)(mContainerState.size() - mpContainer->getCountFixedEventTargets());
  mpY = mpContainerStateTime;
  mpYdot = mpContainer->getRate(*mpReducedModel).array() + mpContainer->getTimeIndex();
  mpAtol = mAtol.array() + mpContainer->getTimeIndex();

  /* Configure lsoda(r) */
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
      mDiscreteRoots.initialize(mpContainer->getRootIsDiscrete());
    }
  else
    {
      mLSODA.setOstream(mErrorMsg);
    }

  return;
}

// virtual
void CLsodaMethod::setContainer(CMathContainer * pContainer)
{
  mpContainer = pContainer;

  if (mpContainer != NULL)
    {
      mContainerState.initialize(mpContainer->getState(*mpReducedModel));
      mpContainerStateTime = mContainerState.array() + mpContainer->getTimeIndex();
    }
  else
    {
      mContainerState.initialize(0, NULL);
      mpContainerStateTime = NULL;
    }
}

void CLsodaMethod::EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{static_cast<Data *>((void *) n)->pMethod->evalF(t, y, ydot);}

void CLsodaMethod::evalF(const C_FLOAT64 * t , const C_FLOAT64 * /* y */, C_FLOAT64 * ydot)
{
  *mpContainerStateTime = *t;

  mpContainer->updateSimulatedValues(*mpReducedModel);
  memcpy(ydot, mpYdot, mData.dim * sizeof(C_FLOAT64));

  std::cout << "State: " << mpContainer->getState(*mpReducedModel) << std::endl;
  std::cout << "Rate:  " << mpContainer->getRate(*mpReducedModel) << std::endl;

  return;
}

void CLsodaMethod::EvalR(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y,
                         const C_INT * nr, C_FLOAT64 * r)
{static_cast<Data *>((void *) n)->pMethod->evalR(t, y, nr, r);}

void CLsodaMethod::evalR(const C_FLOAT64 * t, const C_FLOAT64 *  /* y */,
                         const C_INT *  nr, C_FLOAT64 * r)
{
  *mpContainerStateTime = *t;
  mpContainer->updateSimulatedValues(*mpReducedModel);

  CVectorCore< C_FLOAT64 > RootValues(*nr, r);
  RootValues = mpContainer->getRoots();

  std::cout << "State: " << mpContainer->getState(*mpReducedModel) << std::endl;
  std::cout << "Roots: " << RootValues << std::endl;

  if (mRootMasking != NONE)
    {
      maskRoots(RootValues);
    }

  std::cout << "Roots: " << RootValues << std::endl;
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

  mpContainer->updateSimulatedValues(*mpReducedModel);
  RootValues = mpContainer->getRoots();
  mpContainer->calculateRootDerivatives(RootDerivatives);

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
  *mpContainerStateTime = mTime;
  CVector< C_FLOAT64 > StartState = mContainerState;
  CVector< C_FLOAT64 > ResetState = mContainerState;
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
          case NORMAL:

            if (mRootMasking != ALL)
              {
                mPeekAheadMode = false;
              }
            else
              {
                // We need to remove the masked root
                const bool *pMask = mRootMask.array();
                const bool *pMaskEnd = pMask + mRootMask.size();
                C_INT * pCombinedRoot = CombinedRoots.array();

                PeekAheadStatus = NORMAL;

                for (; pMask != pMaskEnd; ++pMask, ++pCombinedRoot)
                  {
                    if (*pMask)
                      {
                        *pCombinedRoot = 0;
                      }

                    if (*pCombinedRoot)
                      {
                        PeekAheadStatus = ROOT;
                      }
                  }

                // No we reset the integrator to the start state with root masking enabled
                mLsodaStatus = 1;
                mContainerState = StartState;
                mTime = *mpContainerStateTime;
              }

            break;

          case ROOT:
          {
            // Check whether the new state is within the tolerances
            C_FLOAT64 * pOld = StartState.array();
            C_FLOAT64 * pOldEnd = pOld + mData.dim;
            C_FLOAT64 * pNew = mContainerState.array();
            C_FLOAT64 * pAtol = mAtol.array();

            for (; pOld != pOldEnd; ++pOld, ++pNew, ++pAtol)
              {
                if ((2.0 * fabs(*pNew - *pOld) > fabs(*pNew + *pOld) * *mpRelativeTolerance) &&
                    fabs(*pNew) > *pAtol &&
                    fabs(*pOld) > *pAtol)
                  {
                    break;
                  }
              }

            if (pOld != pOldEnd)
              {
                mPeekAheadMode = false;
              }
            else
              {
                ResetState = mContainerState;
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
            PeekAheadStatus = FAILURE;
            mPeekAheadMode = false;
            break;
        }
    }

  // Reset the integrator to the saved state
  mContainerState = ResetState;
  mTime = *mpContainerStateTime;
  mLSODAR.resetState();
  mDWork = ResetDWork;
  mIWork = ResetIWork;

  mRoots = CombinedRoots;

  return PeekAheadStatus;
}
