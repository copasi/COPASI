// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/copasi.h"

#include "copasi/trajectory/CTrajectoryProblem.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CState.h"

#include "copasi/trajectory/CRadau5Method.h"

#ifdef min
#  undef min
#endif

#ifdef max
#  undef max
#endif

// Uncomment this line below to get numeric debug print out.
// #define DEBUG_NUMERICS 1

// Uncomment this line below to get processing flow output.
// #define DEBUG_FLOW 1

// static
void CRadau5Method::EvalM(C_INT *, double *, C_INT *, double *, C_INT *) {}

CRadau5Method::CRadau5Method(const CDataContainer * pParent,
                             const CTaskEnum::Method & methodType,
                             const CTaskEnum::Task & taskType):
  CTrajectoryMethod(pParent, methodType, taskType),
  mpRelativeTolerance(NULL),
  mpAbsoluteTolerance(NULL),
  mpMaxInternalSteps(NULL),
  mpInitialStepSize(NULL),
  mData(),
  mpY(NULL),
  mpYdot(NULL),
  mNumRoots(0),
  mTime(),
  mLsodaStatus(1),
  mLastSuccessState(),
  mLastRootState(),
  mAtol(),
  mpAtol(NULL),
  mErrorMsg(),
  mRADAU(),
  mTask(),
  mDWork(),
  mIWork(),
  mJType(),
  mRootMask(),
  mDiscreteRoots(),
  mRootMasking(CRadau5Method::NONE),
  mTargetTime(),
  mRootCounter(0),
  mPeekAheadMode(false)
{
  assert((void *) &mData == (void *) &mData.dim);

  mData.pMethod = this;
  initializeParameter();
}

CRadau5Method::CRadau5Method(const CRadau5Method & src,
                             const CDataContainer * pParent):
  CTrajectoryMethod(src, pParent),
  mpRelativeTolerance(NULL),
  mpAbsoluteTolerance(NULL),
  mpMaxInternalSteps(NULL),
  mpInitialStepSize(NULL),
  mData(src.mData),
  mpY(NULL),
  mpYdot(NULL),
  mNumRoots(src.mNumRoots),
  mTime(src.mTime),
  mLsodaStatus(src.mLsodaStatus),
  mLastSuccessState(src.mLastSuccessState),
  mLastRootState(src.mLastRootState),
  mAtol(src.mAtol),
  mpAtol(NULL),
  mErrorMsg(src.mErrorMsg.str()),
  mRADAU(),
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

CRadau5Method::~CRadau5Method()
{
  if (mRootsFound.array() != NULL)
    {
      delete [] mRootsFound.array();
    }
}

void CRadau5Method::initializeParameter()
{
  //CCopasiParameter *pParm;

  mpReducedModel = assertParameter("Integrate Reduced Model", CCopasiParameter::Type::BOOL, (bool) false);
  mpRelativeTolerance = assertParameter("Relative Tolerance", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.0e-4);
  mpAbsoluteTolerance = assertParameter("Absolute Tolerance", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.0e-6);
  mpMaxInternalSteps = assertParameter("Max Internal Steps", CCopasiParameter::Type::UINT, (unsigned C_INT32) 1000000000);
  mpInitialStepSize = assertParameter("Initial Step Size", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.0e-3);
}

bool CRadau5Method::elevateChildren()
{
  initializeParameter();
  return true;
}

// virtual
void CRadau5Method::stateChange(const CMath::StateChange & change)
{
  if (change == CMath::eStateChange::FixedEventTarget)
    {
      // The only thing which changed are fixed event targets which do not effect the simulation
      // thus we can continue from the saved state after updating the fixed event targets;
      memcpy(mSavedState.ContainerState.array(), mContainerState.array(), mpContainer->getCountFixedEventTargets() * sizeof(C_FLOAT64));
      memcpy(mLastRootState.ContainerState.array(), mContainerState.array(), mpContainer->getCountFixedEventTargets() * sizeof(C_FLOAT64));
    }
  else if (change & (CMath::StateChange(CMath::eStateChange::State) | CMath::eStateChange::ContinuousSimulation | CMath::eStateChange::EventSimulation))
    {
      // We need to restart the integrator
      mLsodaStatus = 1;

      mTime = *mpContainerStateTime;
      mPeekAheadMode = false;
      mSavedState.Status = FAILURE;

      if (mNumRoots > 0 &&
          mTime == mLastRootState.ContainerState[mpContainer->getCountFixedEventTargets()])
        {
          mLastRootState.ContainerState = mContainerState;
        }
      else
        {
          mLastRootState.ContainerState = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
        }

      mpContainer->updateSimulatedValues(*mpReducedModel);
      setRootMaskType(NONE);
    }
}

CTrajectoryMethod::Status CRadau5Method::step(const double & deltaT,
    const bool & final)
{
  if (mData.dim == 1 && mNumRoots == 0) //just do nothing if there are no variables except time
    {
      mTime += deltaT;
      *mpContainerStateTime = mTime;

      return NORMAL;
    }

  C_FLOAT64 StartTime = mTime;
  C_FLOAT64 EndTime = mTime + deltaT;

  /*
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
  */

  // The return status of the integrator.
  Status Status = NORMAL;

  mLastSuccessState = mContainerState;

  if (mRootsFound.size() > 0)
    {
      if (mSavedState.Status != FAILURE)
        {
          const C_FLOAT64 & SavedTime = mSavedState.ContainerState[mpContainer->getCountFixedEventTargets()];

          if (StartTime < SavedTime && SavedTime <= mTargetTime)
            {
              resetState(mSavedState);
            }
          else
            {
              mSavedState.Status = FAILURE;
            }
        }
    }
  else
    {
      mRADAU(&mData.dim, &EvalF, &mTime, mpY, &EndTime, &H,
             mRtol.array(), mpAtol, &ITOL,
             EvalJ, &IJAC, &MLJAC, &MUJAC,
             EvalM, &IMAS, &MLMAS, &MUMAS,
             solout, &IOUT, mDWork.array(), &LWORK,
             mIWork.array(), &LIWORK, &rpar, &ipar, &idid);

      if (idid < 1)
        {
          if (idid == -2)
            {
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 29);
            }
          else if (idid == -3)
            {
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 30);
            }

          Status = FAILURE;
          return Status;
        }

      if (!mpContainer->isStateValid())
        {
          if (!final || mTask == 4 || mTask == 5)
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
    }

  *mpContainerStateTime = mTime;

  return Status;
}

void CRadau5Method::start()
{
  CTrajectoryMethod::start();

  if (mpContainer->getEvents().size())
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 31);
    }

  /* Reset lsoda */
  mLsodaStatus = 1;

  mTask = mpProblem == NULL ? 1 : mpProblem->getAutomaticStepSize() ? 5 : 1;
  mJType = 2;
  mErrorMsg.str("");

  mTime = *mpContainerStateTime;

  mTargetTime = mTime;
  mRootCounter = 0;
  mPeekAheadMode = false;

  mNumRoots = (C_INT) mpContainer->getRoots().size();

  if (mRootsFound.array() != NULL)
    {
      delete [] mRootsFound.array();
    }

  mRootsFound.initialize(mNumRoots, new C_INT[mNumRoots]);
  mRootsFound = 0;

  destroyRootMask();

  mAtol = mpContainer->initializeAtolVector(*mpAbsoluteTolerance, *mpReducedModel);

  // We ignore fixed event targets and start with the time
  mData.dim = (C_INT)(mContainerState.size() - mpContainer->getCountFixedEventTargets());
  mpY = mpContainerStateTime;
  mpYdot = mpContainer->getRate(*mpReducedModel).array() + mpContainer->getCountFixedEventTargets();
  mpAtol = mAtol.array() + mpContainer->getCountFixedEventTargets();

  mRtol.resize(mData.dim);
  mRtol = *mpRelativeTolerance;

  if (mNumRoots > 0)
    {
      mRADAU.setOstream(mErrorMsg);
      mDiscreteRoots.initialize(mpContainer->getRootIsDiscrete());
      mLastRootState.ContainerState.resize(mContainerState.size());
      mLastRootState.ContainerState = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
      mLastRootState.RootsFound.resize(mNumRoots);
      mLastRootState.RootsFound = 0;

      saveState(mSavedState, FAILURE);
    }
  else
    {
      mRADAU.setOstream(mErrorMsg);
    }

  H = *mpInitialStepSize;

  IOUT = mTask == 5 ? 1 : 0;

  /* optional parameters */
  rpar = 0;
  ipar = 0;

  /* For vector tolerances ITOL=1 */
  ITOL = 1;

  /* RADAU5 computes jacobian internally */
  IJAC = 0;
  MLJAC = mData.dim;
  MUJAC = 0;

  /* Mass matrix routine is identity */
  IMAS = 0;
  MLMAS = 0;

  /* computing the size of the working arrays */
  int ljac, lmas, le;

  if (MLJAC == mData.dim) /* full jacobian */
    {
      ljac = mData.dim;
      le = mData.dim;
    }
  else            /* banded case */
    {
      ljac = MLJAC + MUJAC + 1;
      le = 2 * MLJAC + MUJAC + 1;
    }

  if (IMAS == 0)  /* no mass */
    lmas = 0;
  else if (MLMAS == mData.dim) /* full mass */
    lmas = mData.dim;
  else        /*banded mass */
    lmas = MLMAS + MUMAS + 1;

  /* allocation of workspace */
  LWORK = mData.dim * (ljac + lmas + 3 * le + 12) + 20;
  LIWORK = 3 * mData.dim + 20;

  mDWork.resize(LWORK);
  mDWork = 0.0;
  mIWork.resize(LIWORK);
  mIWork = 0;
  mIWork[1] = *mpMaxInternalSteps;

  return;
}

void CRadau5Method::EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot, C_FLOAT64 *, C_INT *)
{
  static_cast<Data *>((void *) n)->pMethod->evalF(t, y, ydot);
}

void CRadau5Method::evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{
  CVector< C_FLOAT64 > yTemp(mData.dim);
  memcpy(yTemp.array(), mpContainerStateTime, mData.dim * sizeof(C_FLOAT64));

  if (y != mpContainerStateTime)
    memcpy(mpContainerStateTime, y, mData.dim * sizeof(C_FLOAT64));

  mpContainer->updateSimulatedValues(*mpReducedModel);
  memcpy(ydot, mpYdot, mData.dim * sizeof(C_FLOAT64));

#ifdef DEBUG_NUMERICS
  std::cout << "State:     " << mpContainer->getState(false) << std::endl;
  std::cout << "Rate:      " << mpContainer->getRate(false) << std::endl;
#endif // DEBUG_NUMERICS

  memcpy(mpContainerStateTime, yTemp.array(), mData.dim * sizeof(C_FLOAT64));

  return;
}

void CRadau5Method::EvalR(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y,
                          const C_INT * nr, C_FLOAT64 * r)
{static_cast<Data *>((void *) n)->pMethod->evalR(t, y, nr, r);}

void CRadau5Method::evalR(const C_FLOAT64 * t, const C_FLOAT64 *  /* y */,
                          const C_INT *  nr, C_FLOAT64 * r)
{
  *mpContainerStateTime = *t;
  mpContainer->updateRootValues(*mpReducedModel);

  CVectorCore< C_FLOAT64 > RootValues(*nr, r);
  RootValues = mpContainer->getRoots();

#ifdef DEBUG_NUMERICS
  std::cout << "State: " << mpContainer->getState(*mpReducedModel) << std::endl;
  std::cout << "Roots: " << RootValues << std::endl;
#endif // DEBUG_OUTPUT

  if (mRootMasking != NONE)
    {
      maskRoots(RootValues);
    }

#ifdef DEBUG_NUMERICS
  std::cout << "Roots: " << RootValues << std::endl;
#endif // DEBUG_NUMERICS
};

// static
void CRadau5Method::EvalJ(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y,
                          C_FLOAT64 * ml, const C_INT * mu, C_FLOAT64 * pd, const C_INT * nRowPD)
{static_cast<Data *>((void *) n)->pMethod->evalJ(t, y, ml, mu, pd, nRowPD);}

// virtual
void CRadau5Method::evalJ(const C_FLOAT64 * t, const C_FLOAT64 * y,
                          C_FLOAT64 * ml, const C_INT * mu, C_FLOAT64 * pd, const C_INT * nRowPD)
{
  // TODO Implement me.
}

/* solout function to generate output after successfull computation for automatic step size */
void CRadau5Method::solout(C_INT * nr, double * xold, double * x, double * y, double * cont,
                           C_INT * lrc, C_INT * n, double * rpar, C_INT * ipar, C_INT * irtrn)
{
  if (*x != *xold && *(x + 1) != *rpar)
    {
      static_cast<Data *>((void *) ipar)->pMethod->output(x);
      *rpar = *(x + 1);
    }
}

void CRadau5Method::output(const double *t)
{
  if (*t < mpProblem->getDuration())
    {
      *mpContainerStateTime = *t;
      CTrajectoryMethod::output(*mpReducedModel);
      *mpContainerStateTime = 0;
    }
}

void CRadau5Method::maskRoots(CVectorCore< C_FLOAT64 > & rootValues)
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

void CRadau5Method::setRootMaskType(const CRadau5Method::eRootMasking & maskType)
{
  if (maskType == ALL)
    {
      createRootMask();
      return;
    }

  if (mRootMasking == NONE) return;

  mRootMask.resize(mNumRoots);

  // We assume that the simulated values are up to date
  mpContainer->updateRootValues(*mpReducedModel);

  const bool * pDiscrete = mDiscreteRoots.array();
  bool * pMask = mRootMask.begin();
  bool * pMaskEnd = mRootMask.end();
  const C_FLOAT64 * pRootValue = mpContainer->getRoots().begin();
  mRootMasking = NONE;

  for (; pMask != pMaskEnd; ++pMask, ++pDiscrete, ++pRootValue)
    {
      if (*pMask)
        {
          if (fabs(*pRootValue) < 1e3 * std::numeric_limits< C_FLOAT64 >::min())
            {
              if (mRootMasking != ALL)
                {
                  mRootMasking = *pDiscrete ? DISCRETE : ALL;
                }
            }
          else
            {
              *pMask = false;
            }
        }
    }

#ifdef DEBUG_NUMERICS
  std::cout << "Root Values:          " << mpContainer->getRoots() << std::endl;
  std::cout << "Root Discrete:        " << mpContainer->getRootIsDiscrete() << std::endl;
  std::cout << "Root Mask:            " << mRootMask << std::endl;
#endif // DEBUG_NUMERICS
}

void CRadau5Method::createRootMask()
{
  size_t NumRoots = mRootsFound.size();
  mRootMask.resize(NumRoots);
  CVector< C_FLOAT64 > RootValues;
  RootValues.resize(NumRoots);
  CVector< C_FLOAT64 > RootDerivatives;
  RootDerivatives.resize(NumRoots);

  mpContainer->updateRootValues(*mpReducedModel);
  RootValues = mpContainer->getRoots();
  mpContainer->calculateRootDerivatives(RootDerivatives);

  bool *pMask = mRootMask.begin();
  bool *pMaskEnd = mRootMask.end();
  C_INT * pRootFound = mRootsFound.begin();
  C_FLOAT64 * pRootValue = RootValues.begin();
  C_FLOAT64 * pRootDerivative = RootDerivatives.begin();
  const bool * pIsDiscrete = mpContainer->getRootIsDiscrete().begin();

  for (; pMask != pMaskEnd; ++pMask, ++pRootValue, ++pRootDerivative, ++pRootFound, ++pIsDiscrete)
    {
      *pMask = (fabs(*pRootValue) < 1e3 * std::numeric_limits< C_FLOAT64 >::min() ||
//                (fabs(*pRootDerivative) < *mpAbsoluteTolerance && !*pIsDiscrete) ||
                (*pRootFound > 0 && *pRootDerivative * *pRootValue < 0 && fabs(*pRootValue) < 1e3 * std::numeric_limits< C_FLOAT64 >::epsilon())) ? true : false;
    }

#ifdef DEBUG_NUMERICS
  std::cout << "Roots Found:          " << mRootsFound << std::endl;
  std::cout << "Root Values:          " << RootValues << std::endl;
  std::cout << "Root Derivatives:     " << RootDerivatives << std::endl;
  std::cout << "Root Discrete:        " << mpContainer->getRootIsDiscrete() << std::endl;
  std::cout << "Root Mask:            " << mRootMask << std::endl;
#endif // DEBUG_NUMERICS

  mRootMasking = ALL;
}

void CRadau5Method::destroyRootMask()
{
  mRootMask = false;
  mRootMasking = NONE;
}

CTrajectoryMethod::Status CRadau5Method::peekAhead()
{
  // Save the current state
  State StartState;
  saveState(StartState, ROOT);

  saveState(mLastRootState, ROOT);

  mPeekAheadMode = true;
  Status PeekAheadStatus = ROOT;

  CVector< C_FLOAT64 > CurrentRoots = mpContainer->getRoots();
#ifdef DEBUG_NUMERICS
  std::cout << "Current Roots:        " << CurrentRoots << std::endl;
#endif // DEBUG_NUMERICS

  CVector< C_INT > CombinedRootsFound = mRootsFound;
#ifdef DEBUG_OUTPUT
  std::cout << "Combined Roots found: " << CombinedRootsFound << std::endl;
#endif // DEBUG_NUMERICS

  C_FLOAT64 MaxPeekAheadTime = std::max(mTargetTime, mTime * (1.0 + 2.0 * *mpRelativeTolerance));
  mLsodaStatus = 2;

  while (mPeekAheadMode)
    {
      switch (step(MaxPeekAheadTime - mTime))
        {
          case NORMAL:

            if (hasStateChanged(StartState.ContainerState))
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
                saveState(mSavedState, NORMAL);

                // Set the result to the state when peakAhead was entered.
                resetState(StartState);
                mRootsFound = CombinedRootsFound;

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
                const bool *pMask = mRootMask.array();
                const bool *pMaskEnd = pMask + mRootMask.size();
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
            if (hasStateChanged(StartState.ContainerState))
              {
                // If we are here we are certain that the state has sufficiently changed.
                mPeekAheadMode = false;

                // Save the state for future use.
                saveState(mSavedState, ROOT);

                // Set the result to the state when peakAhead was entered.
                resetState(StartState);
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
                    setRootMaskType(ALL);
                  }

                mRootsFound = CombinedRootsFound;
                saveState(mLastRootState, ROOT);

                // We can safely advance the start state to include the new roots.

                saveState(StartState, ROOT);
#ifdef DEBUG_NUMERICS
                std::cout << "Combined Roots found: " << CombinedRootsFound << std::endl;
#endif // DEBUG_NUMERICS
              }
          }
          break;

          case FAILURE:
            // We pretend that we we did not fail
            // Since continuation fails we attempt restart
            resetState(StartState);
            mLsodaStatus = 1;
            mRootCounter = 0;

            // Invalidate the saved state
            mSavedState.Status = FAILURE;
            mPeekAheadMode = false;
            break;
        }
    }

  mRootsFound = CombinedRootsFound;

  return PeekAheadStatus;
}

bool CRadau5Method::hasStateChanged(const CVectorCore< C_FLOAT64 > & startState) const
{
  // Check whether we are at the start of the integrations, i.e., the start state time is NaN.
  if (std::isnan(startState[mpContainer->getCountFixedEventTargets()]))
    {
      return true;
    }

  // Check whether the new state is within the tolerances
  const C_FLOAT64 * pOld = startState.array();
  const C_FLOAT64 * pOldEnd = pOld + startState.size();
  const C_FLOAT64 * pNew = mContainerState.array();
  const C_FLOAT64 * pAtol = mAtol.array();

  for (; pOld != pOldEnd; ++pOld, ++pNew, ++pAtol)
    {
      if ((2.0 * fabs(*pNew - *pOld) > fabs(*pNew + *pOld) **mpRelativeTolerance) &&
          fabs(*pNew) > *pAtol &&
          fabs(*pOld) > *pAtol)
        {
          return true;
        }
    }

  return false;
}
void CRadau5Method::saveState(CRadau5Method::State & state, const CTrajectoryMethod::Status & status) const
{
  *mpContainerStateTime = mTime;

  state.ContainerState = mContainerState;
  state.DWork = mDWork;
  state.IWork = mIWork;
  state.RootsFound = mRootsFound;
  state.RootMask = mRootMask;
  state.RootMasking = mRootMasking;
  state.Status = status;

  mRADAU.saveState(state.LsodaState);
}

void CRadau5Method::resetState(CRadau5Method::State & state)
{
  mLsodaStatus = (state.Status == ROOT) ? 3 : 2;

  mContainerState = state.ContainerState;
  mTime = *mpContainerStateTime;
  mDWork = state.DWork;
  mIWork = state.IWork;
  mRootsFound = state.RootsFound;
  mRootMask = state.RootMask;
  mRootMasking = state.RootMasking;

  mRADAU.resetState(state.LsodaState);
}
