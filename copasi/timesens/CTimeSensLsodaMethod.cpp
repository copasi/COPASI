// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/copasi.h"

#include "CTimeSensLsodaMethod.h"
#include "CTimeSensProblem.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CState.h"

// Uncomment this line below to get numeric debug print out.
// #define DEBUG_NUMERICS 1

// Uncomment this line below to get processing flow output.
// #define DEBUG_FLOW 1

CTimeSensLsodaMethod::CTimeSensLsodaMethod(const CDataContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType):
  CTimeSensMethod(pParent, methodType, taskType),
  mpRelativeTolerance(NULL),
  mpAbsoluteTolerance(NULL),
  mpMaxInternalSteps(NULL),
  mpMaxInternalStepSize(NULL),
  mData(),
  //mpY(NULL),
  mpYdot(NULL),
  mNumRoots(0),
  mTime(),
  mLsodaStatus(1),
  mLastSuccessState(),
  mLastRootState(),
  mAtol(),
  //mpAtol(NULL),
  mErrorMsg(),
  mLSODA(),
  mLSODAR(),
  mTask(),
  mDWork(),
  mIWork(),
  mJType(),
  mRootMask(),
  mDiscreteRoots(),
  mRootMasking(CTimeSensLsodaMethod::NONE),
  mTargetTime(),
  mRootCounter(0),
  mPeekAheadMode(false)
{
  assert((void *) &mData == (void *) &mData.dim);

  mData.pMethod = this;
  initializeParameter();
}

CTimeSensLsodaMethod::CTimeSensLsodaMethod(const CTimeSensLsodaMethod & src,
    const CDataContainer * pParent):
  CTimeSensMethod(src, pParent),
  mpRelativeTolerance(NULL),
  mpAbsoluteTolerance(NULL),
  mpMaxInternalSteps(NULL),
  mpMaxInternalStepSize(NULL),
  mData(src.mData),
  //mpY(NULL),
  mpYdot(NULL),
  mNumRoots(src.mNumRoots),
  mTime(src.mTime),
  mLsodaStatus(src.mLsodaStatus),
  mLastSuccessState(src.mLastSuccessState),
  mLastRootState(src.mLastRootState),
  mAtol(src.mAtol),
  //mpAtol(NULL),
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

CTimeSensLsodaMethod::~CTimeSensLsodaMethod()
{
  if (mRootsFound.array() != NULL)
    {
      delete [] mRootsFound.array();
    }
}

void CTimeSensLsodaMethod::initializeParameter()
{
  mpReducedModel = assertParameter("Integrate Reduced Model", CCopasiParameter::Type::BOOL, (bool) false);
  mpRelativeTolerance = assertParameter("Relative Tolerance", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.0e-6);
  mpAbsoluteTolerance = assertParameter("Absolute Tolerance", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.0e-12);
  mpMaxInternalSteps = assertParameter("Max Internal Steps", CCopasiParameter::Type::UINT, (unsigned C_INT32) 10000);
  mpMaxInternalStepSize = assertParameter("Max Internal Step Size", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 0.0);
}

bool CTimeSensLsodaMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

// virtual
void CTimeSensLsodaMethod::stateChange(const CMath::StateChange & change)
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

      //the event has changed variables in the math container, so the state for the integrator needs to be updated
      memcpy(mVariables.array(), mpContainerStateTime, (mSystemSize + 1) * sizeof(C_FLOAT64)); //TODO shift?
    }
}

CTimeSensMethod::Status CTimeSensLsodaMethod::step(const double & deltaT,
    const bool & final)
{
  if (mData.dim == 1 && mNumRoots == 0) //just do nothing if there are no variables except time
    {
      //TODO
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
      mRootCounter = 0;

      if (mTask == 5)
        {
          mDWork[0] = mTargetTime;
        }
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

      if (mLsodaStatus != 3)
        {
          mLSODAR(&EvalF, //  1. evaluate F
                  &mData.dim, //  2. number of variables
                  mVariables.array(), //  3. the array of current concentrations
                  &mTime, //  4. the current time
                  &EndTime, //  5. the final time
                  &ITOL, //  6. error control
                  mpRelativeTolerance, //  7. relative tolerance array
                  mAtol.array(), //  8. absolute tolerance array
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
                  mRootsFound.array()); // 20. integer array of length NG for output of root information

          memcpy(mpContainerStateTime, mVariables.array(), (mSystemSize + 1) * sizeof(C_FLOAT64));
          //copySensitivitiesToResultMatrix(); //TODO we do this now after each integration step, probably only necessary before output...

          // There exist situations where LSODAR reports status = 3, which are actually status = -33
          // Obviously the trivial case is where LSODAR did not advance at all, i.e, the start time
          // equals the current time. It may also happen that a very small steps has been taken.
          // We reset short before we reach the internal step limit.
#ifdef DEBUG_FLOW
          std::cout << "mTime = " << mTime << ", EndTime = " << EndTime << ", mTask = " << mTask << ", mLsodaStatus = " << mLsodaStatus << ", mRootCounter = " << mRootCounter << std::endl;
          std::cout << "mRootsFound = " << mRootsFound << std::endl;
          std::cout << "mDWork = " << mDWork << std::endl;
          std::cout << "mIWork = " << mIWork << std::endl;
#endif // DEBUG_FLOW

          if (mLsodaStatus == 3)
            {
              if (mLastRootState.Status == ROOT &&
                  mLastRootState.RootsFound == mRootsFound &&
                  (fabs(mTime - StartTime) < 50.0 * (fabs(mTime) + fabs(StartTime)) * std::numeric_limits< C_FLOAT64 >::epsilon() ||
                   (fabs(mTime - mLastRootState.ContainerState[mpContainer->getCountFixedEventTargets()]) < 50.0 * (fabs(mTime) + fabs(mLastRootState.ContainerState[mpContainer->getCountFixedEventTargets()])) * std::numeric_limits< C_FLOAT64 >::epsilon() &&
                    !hasStateChanged(mLastRootState.ContainerState))))
                {
                  mLsodaStatus = -33;
                  mRootCounter = 0;
                }
            }

          // Try without over shooting.
          if ((mLsodaStatus <= 0 && mLsodaStatus != -33) ||
              !mpContainer->isStateValid())
            {
              if (!final || mTask == 4 || mTask == 5)
                {
#ifdef DEBUG_FLOW
                  std::cout << "FAILURE: Attempt to prevent over shooting failed." << std::endl;
#endif // DEBUG_FLOW

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

#ifdef DEBUG_FLOW
              std::cout << "Attempting to prevent over shooting." << std::endl;
#endif // DEBUG_FLOW

              Status = step(deltaT);

              mTask -= 3;

              return Status;
            }
        }

#ifdef DEBUG_FLOW
      else
        {
          std::cout << "Continuing with root found by peek ahead." << std::endl;
        }

#endif // DEBUG_FLOW

      switch (mLsodaStatus)
        {
          case -33:

            // Reset the integrator to the state before the failed integration.

            mContainerState = mLastSuccessState;
            mTime = *mpContainerStateTime;
            mpContainer->updateSimulatedValues(*mpReducedModel);

            mLsodaStatus = 1;

            if (mLastRootState.ContainerState[mpContainer->getCountFixedEventTargets()] == mTime)
              {
                mRootsFound = mLastRootState.RootsFound;
              }

            // Create a mask which hides all roots being constant and zero.
#ifdef DEBUG_FLOW
            std::cout << "Creating Root Mask." << std::endl;
#endif // DEBUG_FLOW

            {
              CVector< bool > CurrentMask = mRootMask;
              setRootMaskType(ALL);

              if (CurrentMask == mRootMask)
                {
                  Status = FAILURE;
                }
              else
                {
                  return step(deltaT);
                }
            }

            break;

          case 3:

            // If mLsodaStatus == 3 we have found a root. This needs to be indicated to
            // the caller as it is not sufficient to rely on the fact that T < TOUT

            if (mRootMasking != NONE)
              {
                setRootMaskType(NONE);
              }

            // To detect simultaneous roots we have to peek ahead, i.e., continue
            // integration until the state changes are larger than the relative tolerances
            if (!mPeekAheadMode)
              {
#ifdef DEBUG_FLOW
                std::cout << "Starting peek ahead." << std::endl;
#endif // DEBUG_FLOW

                Status = peekAhead();

#ifdef DEBUG_FLOW
                std::cout << "Finishing peek ahead." << std::endl;
#endif // DEBUG_FLOW
              }

            // It is sufficient to switch to 2. Eventual state changes due to events
            // are indicated via the method stateChanged()
            if (mLsodaStatus == 3)
              {
                mLsodaStatus = 2;
              }

            Status = ROOT;

            saveState(mLastRootState, ROOT);
            break;

          // The break statement is intentionally missing since we
          // have to continue to check the root masking state.
          default:

            // We made a successful step and therefore invalidate the last root state
            mLastRootState.Status = FAILURE;

            switch (mRootMasking)
              {
                case NONE:
                  break;

                case DISCRETE:
                case ALL:
                  setRootMaskType(NONE);
                  break;
              }

            break;
        }
    }
  else
    {
      mLSODA(&EvalF, //  1. evaluate F
             &mData.dim, //  2. number of variables
             mVariables.array(), //  3. the array of current concentrations
             &mTime, //  4. the current time
             &EndTime, //  5. the final time
             &ITOL, //  6. error control
             mpRelativeTolerance, //  7. relative tolerance array
             mAtol.array(), //  8. absolute tolerance array
             &mTask, //  9. output by overshoot & interpolation
             &mLsodaStatus, // 10. the state control variable
             &one, // 11. further options (one)
             mDWork.array(), // 12. the double work array
             &DSize, // 13. the double work array size
             mIWork.array(), // 14. the int work array
             &ISize, // 15. the int work array size
             EvalJ, // 16. evaluate J (not given)
             &mJType);        // 17. the type of jacobian calculate (2)

      memcpy(mpContainerStateTime, mVariables.array(), (mSystemSize + 1) * sizeof(C_FLOAT64));
      //copySensitivitiesToResultMatrix(); //TODO we do this now after each integration step, probably only necessary before output...

      if (mLsodaStatus <= 0 ||
          !mpContainer->isStateValid())
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

void CTimeSensLsodaMethod::start()
{
  CTimeSensMethod::start();

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

  //init size of the system
  mData.dim = (C_INT)(1 + mSystemSize * (1 + mNumParameters)); //including time

  //initialize the vector on which lsoda will work
  mVariables.resize(mData.dim);

  //initial state of the system
  memcpy(mVariables.array(), mpContainerStateTime, (mSystemSize + 1) * sizeof(C_FLOAT64));
  //initial state of the sensitivities
  //the sensitivities are initialized with the derivatives of the initial assignments wrt the parameters
  CMatrix<C_FLOAT64> initSens;
  calculate_dInitialState_dPar(initSens);
  //std::cout << initSens;
  size_t i, j;

  for (i = 0; i < mSystemSize; ++i)
    for (j = 0; j < mNumParameters; ++j)
      {
        mVariables[i + (j + 1)*mSystemSize + 1] = (initSens[i][j]);
      }

  copySensitivitiesToResultMatrix();

  //reserve space for jacobian, etc.
  mJacobian.resize(mSystemSize, mSystemSize);
  mdRate_dPar.resize(mSystemSize, mNumParameters);

  mpYdot = mpContainer->getRate(*mpReducedModel).array() + mpContainer->getCountFixedEventTargets();

  //init absolute tolerances for the extended ODE
  CVector< C_FLOAT64 > tmpAtol = mpContainer->initializeAtolVector(*mpAbsoluteTolerance, *mpReducedModel);
  mAtol.resize(mData.dim);

  for (i = 0; i < mSystemSize + 1; ++i)
    mAtol[i] = tmpAtol[i + mpContainer->getCountFixedEventTargets()]; //TODO shift? + mpContainer->getCountFixedEventTargets()

  for (i = mSystemSize + 1; i < mData.dim; ++i)
    mAtol[i] = mAtol[i - mSystemSize]; // 1e-12;

  /* Configure lsoda(r) */
  mDWork.resize(22 + mData.dim * std::max<C_INT>(16, mData.dim + 9) + 3 * mNumRoots);
  mDWork[4] = mDWork[6] = mDWork[7] = mDWork[8] = mDWork[9] = 0.0;

  mDWork[5] = *mpMaxInternalStepSize;

  mIWork.resize(20 + mData.dim);
  mIWork[4] = mIWork[6] = mIWork[9] = 0;

  mIWork[5] = *mpMaxInternalSteps;
  mIWork[7] = 12;
  mIWork[8] = 5;

  if (mNumRoots > 0)
    {
      mLSODAR.setOstream(mErrorMsg);
      mDiscreteRoots.initialize(mpContainer->getRootIsDiscrete());
      mLastRootState.ContainerState.resize(mContainerState.size());
      mLastRootState.ContainerState = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
      mLastRootState.RootsFound.resize(mNumRoots);
      mLastRootState.RootsFound = 0;

      saveState(mSavedState, FAILURE);
    }
  else
    {
      mLSODA.setOstream(mErrorMsg);
    }

  return;
}

void CTimeSensLsodaMethod::EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{static_cast<Data *>((void *) n)->pMethod->evalF(t, y, ydot);}

void CTimeSensLsodaMethod::evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{
  /*
#ifdef DEBUG_NUMERICS
    std::cout << "State:     " << mpContainer->getState(false) << std::endl;
    std::cout << "Rate:      " << mpContainer->getRate(false) << std::endl;
#endif // DEBUG_NUMERICS
  */
  assert(y == mVariables.array());

  //update the container and calculate the RHS of the system
  *mpContainerStateTime = *t; //redundant?
  memcpy(mpContainerStateTime, mVariables.array(), (mSystemSize + 1) * sizeof(C_FLOAT64)); //TODO shift?
  mpContainer->updateSimulatedValues(*mpReducedModel);
  memcpy(ydot, mpYdot, (mSystemSize + 1) * sizeof(C_FLOAT64));

  //calculate the RHS of the extended system
  mpContainer->calculateJacobian(mJacobian, 1e-6, *mpReducedModel);
  calculate_dRate_dPar(mdRate_dPar, *mpReducedModel);
  //std::cout << mdRate_dPar;

  C_FLOAT64 *dbl1;
  const C_FLOAT64 *dbl2, *dbl3, *dbl1end, *dbl3end, *dbl_dRdP;
  dbl1 = ydot + mSystemSize + 1;
  size_t i;

  for (i = 1; i <= mNumParameters; ++i)
    {
      dbl1end = dbl1 + mSystemSize;
      dbl2 = mJacobian.array();

      dbl_dRdP = mdRate_dPar[0] + i - 1;

      for (; dbl1 != dbl1end; ++dbl1, dbl_dRdP += mNumParameters)
        {
          *dbl1 = *dbl_dRdP; // 0.0;

          dbl3 = y + 1 + i * mSystemSize;
          dbl3end = dbl3 + mSystemSize;

          for (; dbl3 != dbl3end; ++dbl3, ++dbl2)
            *dbl1 += *dbl2 **dbl3;
        }
    }

  return;
}

void CTimeSensLsodaMethod::EvalR(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y,
                                 const C_INT * nr, C_FLOAT64 * r)
{static_cast<Data *>((void *) n)->pMethod->evalR(t, y, nr, r);}

void CTimeSensLsodaMethod::evalR(const C_FLOAT64 * t, const C_FLOAT64 *  /* y */,
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
void CTimeSensLsodaMethod::EvalJ(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y,
                                 const C_INT * ml, const C_INT * mu, C_FLOAT64 * pd, const C_INT * nRowPD)
{static_cast<Data *>((void *) n)->pMethod->evalJ(t, y, ml, mu, pd, nRowPD);}

// virtual
void CTimeSensLsodaMethod::evalJ(const C_FLOAT64 * t, const C_FLOAT64 * y,
                                 const C_INT * ml, const C_INT * mu, C_FLOAT64 * pd, const C_INT * nRowPD)
{
  // TODO Implement me.
}

void CTimeSensLsodaMethod::maskRoots(CVectorCore< C_FLOAT64 > & rootValues)
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

void CTimeSensLsodaMethod::setRootMaskType(const CTimeSensLsodaMethod::eRootMasking & maskType)
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

void CTimeSensLsodaMethod::createRootMask()
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

void CTimeSensLsodaMethod::destroyRootMask()
{
  mRootMask = false;
  mRootMasking = NONE;
}

CTimeSensMethod::Status CTimeSensLsodaMethod::peekAhead()
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

bool CTimeSensLsodaMethod::hasStateChanged(const CVectorCore< C_FLOAT64 > & startState) const
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
void CTimeSensLsodaMethod::saveState(CTimeSensLsodaMethod::State & state, const CTimeSensMethod::Status & status) const
{
  *mpContainerStateTime = mTime;

  state.ContainerState = mContainerState;
  state.DWork = mDWork;
  state.IWork = mIWork;
  state.RootsFound = mRootsFound;
  state.RootMask = mRootMask;
  state.RootMasking = mRootMasking;
  state.Status = status;

  mLSODAR.saveState(state.LsodaState);
}

void CTimeSensLsodaMethod::resetState(CTimeSensLsodaMethod::State & state)
{
  mLsodaStatus = (state.Status == ROOT) ? 3 : 2;

  mContainerState = state.ContainerState;
  mTime = *mpContainerStateTime;
  mDWork = state.DWork;
  mIWork = state.IWork;
  mRootsFound = state.RootsFound;
  mRootMask = state.RootMask;
  mRootMasking = state.RootMasking;

  mLSODAR.resetState(state.LsodaState);
}

void CTimeSensLsodaMethod::copySensitivitiesToResultMatrix()
{
  //TODO for now this is a quite inefficient implementation
  size_t i, j;
  CArray::index_type index;
  index.resize(2);

  for (i = 0; i < mSystemSize; ++i)
    for (j = 0; j < mNumParameters; ++j)
      {
        //mVariables[i + (j+1)*mSystemSize + 1] = (initSens[i][j]);
        index[0] = i; index[1] = j;
        mpProblem->getStateResult()[index] =  mVariables[i + (j + 1) * mSystemSize + 1];
        mpProblem->getScaledStateResult()[index] =  mVariables[i + (j + 1) * mSystemSize + 1]
            * *mParameterTransientValuePointers[j]
            / *(mpContainerStateTime + 1 + i);
      }

  //calculate sensitivities for assignments
  calculate_dAssignments_dPar(mdAssignment_dPar);
  //std::cout << mdAssignment_dPar;
  calculate_dAssignments_dState(mAssignmentJacobian, *mpReducedModel);
  //std::cout << mAssignmentJacobian;

  C_FLOAT64 tmp;
  size_t k;

  for (i = 0; i < mpProblem->getNumTargets(); ++i)
    for (j = 0; j < mNumParameters; ++j)
      {
        tmp = mdAssignment_dPar[i][j];

        for (k = 0; k < mSystemSize; ++k)
          tmp += mAssignmentJacobian[i][k] * mVariables[k + (j + 1) * mSystemSize + 1];

        index[0] = i; index[1] = j;
        mpProblem->getTargetsResult()[index] = tmp;
        mpProblem->getScaledTargetsResult()[index] = tmp
            * *mParameterTransientValuePointers[j]
            / *mAssTargetValuePointers[i];
      }
}
