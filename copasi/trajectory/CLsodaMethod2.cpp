// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/copasi.h"

#include "CLsodaMethod2.h"
#include "CTrajectoryProblem.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CState.h"

// Uncomment this line below to get numeric debug print out.
// #define DEBUG_NUMERICS 1

// Uncomment this line below to get processing flow output.
// #define DEBUG_FLOW 1

CLsodaMethod2::CLsodaMethod2(const CDataContainer * pParent,
                             const CTaskEnum::Method & methodType,
                             const CTaskEnum::Task & taskType):
  CTrajectoryMethod(pParent, methodType, taskType),
  mpRelativeTolerance(NULL),
  mpAbsoluteTolerance(NULL),
  mpMaxInternalSteps(NULL),
  mpMaxInternalStepSize(NULL),
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
  mTask(),
  mDWork(),
  mIWork(),
  mJType(),
  mRootMask(),
  mRootMasking(CRootFinder::RootMasking::NONE),
  mTargetTime(),
  mPeekAheadMode(false)
{
  mData.pMethod = this;
  mpRootValueCalculator = new CRootFinder::EvalTemplate< CLsodaMethod2 >(this, & CLsodaMethod2::evalRoot);
  initializeParameter();
}

CLsodaMethod2::CLsodaMethod2(const CLsodaMethod2 & src,
                             const CDataContainer * pParent):
  CTrajectoryMethod(src, pParent),
  mpRelativeTolerance(NULL),
  mpAbsoluteTolerance(NULL),
  mpMaxInternalSteps(NULL),
  mpMaxInternalStepSize(NULL),
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
  mTask(src.mTask),
  mDWork(src.mDWork),
  mIWork(src.mIWork),
  mJType(src.mJType),
  mRootMask(src.mRootMask),
  mRootMasking(src.mRootMasking),
  mTargetTime(src.mTargetTime),
  mPeekAheadMode(src.mPeekAheadMode)
{
  mData.pMethod = this;
  mpRootValueCalculator = new CRootFinder::EvalTemplate< CLsodaMethod2 >(this, & CLsodaMethod2::evalRoot);

  initializeParameter();
}

CLsodaMethod2::~CLsodaMethod2()
{
  if (mRootsFound.array() != NULL)
    {
      delete [] mRootsFound.array();
    }
}

void CLsodaMethod2::initializeParameter()
{
  mpReducedModel = assertParameter("Integrate Reduced Model", CCopasiParameter::Type::BOOL, (bool) false);
  mpRelativeTolerance = assertParameter("Relative Tolerance", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.0e-6);
  mpAbsoluteTolerance = assertParameter("Absolute Tolerance", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.0e-12);
  mpMaxInternalSteps = assertParameter("Max Internal Steps", CCopasiParameter::Type::UINT, (unsigned C_INT32) 100000);
  mpMaxInternalStepSize = assertParameter("Max Internal Step Size", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 0.0);
}

bool CLsodaMethod2::elevateChildren()
{
  initializeParameter();

  return true;
}

// virtual
void CLsodaMethod2::stateChange(const CMath::StateChange & change)
{
  if (change == CMath::eStateChange::FixedEventTarget)
    {
      // The only thing which changed are fixed event targets which do not effect the simulation
      // thus we can continue from the saved state after updating the fixed event targets;
      memcpy(mSavedState.ContainerState.array(), mContainerState.array(), mpContainer->getCountFixedEventTargets() * sizeof(C_FLOAT64));
    }
  else if (change & (CMath::StateChange(CMath::eStateChange::State) | CMath::eStateChange::ContinuousSimulation | CMath::eStateChange::EventSimulation))
    {
      // We need to restart the integrator
      mLsodaStatus = 1;

      mTime = *mpContainerStateTime;
      mPeekAheadMode = false;
      mSavedState.Status = FAILURE;

      destroyRootMask();
    }
}

CTrajectoryMethod::Status CLsodaMethod2::step(const double & deltaT)
{
  if (mData.dim == 1 && mNumRoots == 0) //just do nothing if there are no variables except time
    {
      mTime += deltaT;
      *mpContainerStateTime = mTime;

      return NORMAL;
    }

  C_FLOAT64 StartTime = mTime;
  C_FLOAT64 EndTime = mTime + deltaT;

  if (mTargetTime != EndTime)
    {
      // We have a new end time and reset the root counter.
      mTargetTime = EndTime;

      if (mTask == 5)
        {
          mDWork[0] = mTargetTime;
        }
    }

  C_INT ITOL = 2; // mRtol scalar, mAtol vector
  C_INT one = 1;
  C_INT DSize = (C_INT) mDWork.size();
  C_INT ISize = (C_INT) mIWork.size();

  // The return status of the integrator.
  Status Status = NORMAL;

  mLastSuccessState = mContainerState;

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

  if (mLsodaStatus <= 0 ||
      !mpContainer->isStateValid())
    {
      if (mTask == 4 || mTask == 5)
        {
          Status = FAILURE;
          mPeekAheadMode = false;

          if (mLsodaStatus <= 0)
            {
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 6, mErrorMsg.str().c_str());
            }
          else
            {
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 25, mTime);
            }
        }

      // We try to recover by preventing overshooting.
#ifdef DEBUG_NUMERICS
      std::cout << "State: " << mpContainer->getState(*mpReducedModel) << std::endl;
#endif // DEBUG_NUMERICS

      mContainerState = mLastSuccessState;
#ifdef DEBUG_NUMERICS
      std::cout << "State: " << mpContainer->getState(*mpReducedModel) << std::endl;
#endif // DEBUG_NUMERICS

      mTime = *mpContainerStateTime;
      mTask += 3;
      mDWork[0] = EndTime;
      stateChange(CMath::eStateChange::State);

      Status = step(deltaT);
      mTask -= 3;

      return Status;
    }

  *mpContainerStateTime = mTime;

  return Status;
}

void CLsodaMethod2::start()
{
  CTrajectoryMethod::start();

  /* Reset lsoda */
  mLsodaStatus = 1;

  mTask = mpProblem == NULL ? 1 : mpProblem->getAutomaticStepSize() ? 5 : 1;
  mJType = 2;
  mErrorMsg.str("");

  mTime = *mpContainerStateTime;

  mTargetTime = mTime;
  mPeekAheadMode = false;

  mNumRoots = mpContainer->getRoots().size();
  mRootMask.resize(mNumRoots);
  mRootMask = CRootFinder::NONE;

  C_INT *pMask = mRootMask.begin() + 1;
  C_INT *pMaskEnd = mRootMask.end();
  const bool * pDiscrete = mpContainer->getRootIsDiscrete().begin();

  // We ignore all discrete roots since they cannot be triggered during continuous integration.
  for (; pMask != pMaskEnd; ++pMask, ++pDiscrete)
    *pMask = *pDiscrete ? CRootFinder::DISCRETE : CRootFinder::NONE;

  mRootFinder.initialize(mpRootValueCalculator, *mpRelativeTolerance, mRootMask);
  mRoots.initialize(mRootFinder.getRootValues());
  mRootsFound.initialize(mRootFinder.getToggledRoots());

  mAtol = mpContainer->initializeAtolVector(*mpAbsoluteTolerance, *mpReducedModel);

  // We ignore fixed event targets and start with the time
  mData.dim = (C_INT)(mContainerState.size() - mpContainer->getCountFixedEventTargets());
  mpY = mpContainerStateTime;
  mpYdot = mpContainer->getRate(*mpReducedModel).array() + mpContainer->getCountFixedEventTargets();
  mpAtol = mAtol.array() + mpContainer->getCountFixedEventTargets();

  /* Configure lsoda(r) */
  mDWork.resize(22 + mData.dim * std::max<C_INT>(16, mData.dim + 9));
  mDWork[4] = mDWork[6] = mDWork[7] = mDWork[8] = mDWork[9] = 0.0;

  mDWork[5] = *mpMaxInternalStepSize;

  mIWork.resize(20 + mData.dim);
  mIWork[4] = mIWork[6] = mIWork[9] = 0;

  mIWork[5] = *mpMaxInternalSteps;
  mIWork[7] = 12;
  mIWork[8] = 5;

  mLSODA.setOstream(mErrorMsg);

  return;
}

void CLsodaMethod2::EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{static_cast<Data *>((void *) n)->pMethod->evalF(t, y, ydot);}

void CLsodaMethod2::evalF(const C_FLOAT64 * t, const C_FLOAT64 * /* y */, C_FLOAT64 * ydot)
{
  *mpContainerStateTime = *t;

  mpContainer->updateSimulatedValues(*mpReducedModel);
  memcpy(ydot, mpYdot, mData.dim * sizeof(C_FLOAT64));

#ifdef DEBUG_NUMERICS
  std::cout << "State:     " << mpContainer->getState(false) << std::endl;
  std::cout << "Rate:      " << mpContainer->getRate(false) << std::endl;
#endif // DEBUG_NUMERICS

  return;
}

void CLsodaMethod2::evalRoot(const double & time, CVectorCore< C_FLOAT64 > & rootValues)
{
  // Interpolate the state variables using dinty_

  /* CALL DINTDY (T, K, RWORK(21), NYH, DKY, IFLAG) */

  /* The input parameters are: */

  /* T         = value of independent variable where answers are desired */
  /*             (normally the same as the T last returned by DLSODA). */
  /*             For valid results, T must lie between TCUR - HU and TCUR. */
  /*             (See optional outputs for TCUR and HU.) */
  /* K         = integer order of the derivative desired.  K must satisfy */
  /*             0 .le. K .le. NQCUR, where NQCUR is the current order */
  /*             (see optional outputs).  The capability corresponding */
  /*             to K = 0, i.e. computing y(T), is already provided */
  /*             by DLSODA directly.  Since NQCUR .ge. 1, the first */
  /*             derivative dy/dt is always available with DINTDY. */
  /* RWORK(21) = the base address of the history array YH. */
  /* NYH       = column length of YH, equal to the initial value of NEQ. */

  /* The output parameters are: */

  /* DKY       = a real array of length NEQ containing the computed value */
  /*             of the K-th derivative of y(t). */
  /* IFLAG     = integer flag, returned as 0 if K and T were legal, */
  /*             -1 if K was illegal, and -2 if T was illegal. */
  /*             On an error return, a message is also written. */

  C_INT K = 0;
  C_INT iFlag;
  CVector< C_FLOAT64 > InterpolatedState(mData.dim);
  C_FLOAT64 * pTime = const_cast< C_FLOAT64 * >(&time);

  mLSODA.dintdy_(pTime, &K, &mDWork[21], &mData.dim, InterpolatedState.array(), &iFlag);

  if (iFlag < 0) fatalError();

  // Update the math container state and calculate the roots
  memcpy(mpY, InterpolatedState.array(), mData.dim * sizeof(C_FLOAT64));
  *mpContainerStateTime = time;
  mpContainer->updateSimulatedValues(*mpReducedModel);

  // Return the root values
  memcpy(rootValues.array(), mpContainer->getRoots().array(), mNumRoots * sizeof(C_FLOAT64));
}

// static
void CLsodaMethod2::EvalJ(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y,
                          const C_INT * ml, const C_INT * mu, C_FLOAT64 * pd, const C_INT * nRowPD)
{static_cast<Data *>((void *) n)->pMethod->evalJ(t, y, ml, mu, pd, nRowPD);}

// virtual
void CLsodaMethod2::evalJ(const C_FLOAT64 * t, const C_FLOAT64 * y,
                          const C_INT * ml, const C_INT * mu, C_FLOAT64 * pd, const C_INT * nRowPD)
{
  // TODO Implement me.
}

void CLsodaMethod2::createRootMask()
{
  CVector< C_FLOAT64 > RootDerivatives;
  RootDerivatives.resize(mNumRoots);

  mpContainer->updateSimulatedValues(false);
  mpContainer->calculateRootDerivatives(RootDerivatives);

  C_INT *pMask = mRootMask.begin() + 1;
  C_INT *pMaskEnd = mRootMask.end();
  const C_FLOAT64 * pRootValue = mContainerRoots.begin();
  const C_FLOAT64 * pRootDerivative = RootDerivatives.array();
  const bool * pDiscrete = mpContainer->getRootIsDiscrete().begin();

  for (; pMask != pMaskEnd; ++pMask, ++pRootValue, ++pRootDerivative, ++pDiscrete)
    if (*pDiscrete)
      {
        *pMask = CRootFinder::DISCRETE;
      }
    else if (fabs(*pRootDerivative) < *mpAbsoluteTolerance &&
             fabs(*pRootValue) < 1e3 * std::numeric_limits< C_FLOAT64 >::min())
      {
        *pMask = CRootFinder::CONTINUOUS;
      }

  mRootMasking = CRootFinder::ALL;

  // std::cout << "mRootMask:     " << mRootMask << std::endl;
}

void CLsodaMethod2::destroyRootMask()
{
  mpContainer->updateSimulatedValues(false);

  C_FLOAT64 RootLimit = (1.0 + std::numeric_limits< C_FLOAT64 >::epsilon()) * fabs(mRootFinder.getRootError()) + 100.0 * std::numeric_limits< C_FLOAT64 >::min();
  mRootMasking = CRootFinder::NONE;

  C_INT *pMask = mRootMask.begin() + 1;
  C_INT *pMaskEnd = mRootMask.end();
  const C_FLOAT64 * pRootValue = mContainerRoots.begin();

  for (; pMask != pMaskEnd; ++pMask, ++pRootValue)
    if (*pMask != CRootFinder::DISCRETE ||
        fabs(*pRootValue) >= RootLimit)
      {
        *pMask = CRootFinder::NONE;
      }
    else
      {
        mRootMasking = CRootFinder::DISCRETE;
      }
}

CTrajectoryMethod::Status CLsodaMethod2::peekAhead()
{
  // Save the current state
  CVector< C_FLOAT64 > StartState = mContainerState;

  mPeekAheadMode = true;
  Status PeekAheadStatus = ROOT;

  CVector< C_FLOAT64 > CurrentRoots = mpContainer->getRoots();
#ifdef DEBUG_NUMERICS
  std::cout << "Current Roots:        " << mpContainer->getRoots() << std::endl;
#endif // DEBUG_NUMERICS

  CVector< C_INT > CombinedRootsFound = mRootsFound;
#ifdef DEBUG_OUTPUT
  std::cout << "Combined Roots found: " << CombinedRootsFound << std::endl;
#endif // DEBUG_NUMERICS

  C_FLOAT64 MaxPeekAheadTime = std::max(mTargetTime, mTime * (1.0 + 2.0 * *mpRelativeTolerance));

  while (mPeekAheadMode)
    {
      switch (step(MaxPeekAheadTime - mTime))
        {
          case NORMAL:

            if (mRootMasking != CRootFinder::RootMasking::ALL)
              {
                // If we are here we are certain that the state has sufficiently changed.
                mPeekAheadMode = false;

                // It is possible that LSODA does not detect a root if the original root
                // value was very close to 0.0. We have a new root if we have a sign change.
                // This must have been at the start of the integration.
                C_INT * pCombinedRoot = CombinedRootsFound.array();
                C_INT * pCombinedRootEnd = pCombinedRoot + CombinedRootsFound.size();
                const C_FLOAT64 * pOldRoot = CurrentRoots.array();
                const C_FLOAT64 * pNewRoot = mpContainer->getRoots().array();

                for (; pCombinedRoot != pCombinedRootEnd; ++pCombinedRoot, ++pOldRoot, ++pNewRoot)
                  {
                    *pCombinedRoot |= (*pOldRoot **pNewRoot < 0.0);
                  }

                // Save the state for future use.
                saveState();
                mSavedState.Status = NORMAL;

                // Set the result to the state when peakAhead was entered.
                mContainerState = StartState;
                mTime = *mpContainerStateTime;

#ifdef DEBUG_NUMERICS
                std::cout << "Current Roots:        " << mpContainer->getRoots() << std::endl;
                std::cout << "Combined Roots found: " << CombinedRootsFound << std::endl;
#endif // DEBUG_OUTPUT
              }
            else
              {
                // If we are here LSODA returned with status -33, i.e.
                // time did not advanced due to to indistinguishable roots

                // Root masking has been enabled in step and the integrator is ready
                // to continue with the previous state.

                // Remove masked roots from the result set
                const C_INT *pMask = mRootMask.array();
                const C_INT *pMaskEnd = pMask + mRootMask.size();
                C_INT * pCombinedRoot = CombinedRootsFound.array();

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
              }

            break;

          case ROOT:
          {
            // Check whether the new state is within the tolerances
            C_FLOAT64 * pOld = StartState.array();
            C_FLOAT64 * pOldEnd = pOld + StartState.size();
            C_FLOAT64 * pNew = mContainerState.array();
            C_FLOAT64 * pAtol = mAtol.array();

            for (; pOld != pOldEnd; ++pOld, ++pNew, ++pAtol)
              {
                if ((2.0 * fabs(*pNew - *pOld) > fabs(*pNew + *pOld) **mpRelativeTolerance) &&
                    fabs(*pNew) > *pAtol &&
                    fabs(*pOld) > *pAtol)
                  {
                    break;
                  }
              }

            if (pOld != pOldEnd)
              {
                // If we are here we are certain that the state has sufficiently changed.
                mPeekAheadMode = false;

                // Save the state for future use.
                saveState();
                mSavedState.Status = ROOT;

                // Set the result to the state when peakAhead was entered.
                mContainerState = StartState;
                mTime = *mpContainerStateTime;
              }
            else
              {
                // We found more roots within the desired tolerance
                // Combine all the roots
                C_INT * pRoot = mRootsFound.array();
                C_INT * pRootEnd = pRoot + mRootsFound.size();
                C_INT * pCombinedRoot = CombinedRootsFound.array();
                bool FoundNewRoot = false;

                for (; pRoot != pRootEnd; ++pRoot, ++pCombinedRoot)
                  {
                    if (*pCombinedRoot > 0) continue;

                    if (*pRoot > 0)
                      {
                        *pCombinedRoot = 1;
                        FoundNewRoot = true;
                      }
                  }

                if (!FoundNewRoot)
                  {
                    createRootMask();
                  }

#ifdef DEBUG_NUMERICS
                std::cout << "Combined Roots found: " << CombinedRootsFound << std::endl;
#endif // DEBUG_NUMERICS
              }
          }
          break;

          case FAILURE:
            PeekAheadStatus = FAILURE;
            mPeekAheadMode = false;
            break;
        }
    }

  mRootsFound = CombinedRootsFound;

  return PeekAheadStatus;
}

void CLsodaMethod2::saveState()
{
  *mpContainerStateTime = mTime;
  mSavedState.ContainerState = mContainerState;
  mSavedState.DWork = mDWork;
  mSavedState.IWork = mIWork;
  mSavedState.RootsFound = mRootsFound;
  mSavedState.Status = FAILURE;

  mLSODA.saveState(mSavedState.LsodaState);
}

void CLsodaMethod2::resetState()
{
  if (mSavedState.Status == ROOT)
    {
      mLsodaStatus = 3;
    }

  mContainerState = mSavedState.ContainerState;
  mTime = *mpContainerStateTime;
  mDWork = mSavedState.DWork;
  mIWork = mSavedState.IWork;
  mRootsFound = mSavedState.RootsFound;
  mSavedState.Status = FAILURE;

  mLSODA.resetState(mSavedState.LsodaState);
}
