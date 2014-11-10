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

/**
 * CTrajectoryTask class.
 *
 * This class implements a trajectory task which is comprised of a
 * of a problem and a method. Additionally calls to the reporting
 * methods are done when initialized.
 *
 * Created for COPASI by Stefan Hoops 2002
 */

#include <string>
#include <cmath>

#include "copasi.h"

#include "CTrajectoryTask.h"
#include "CTrajectoryProblem.h"
#include "CTrajectoryMethod.h"
#include "math/CMathContainer.h"
#include "model/CModel.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"
#include "utilities/CProcessReport.h"
#include "utilities/CCopasiException.h"
#include  "CopasiDataModel/CCopasiDataModel.h"

#define XXXX_Reporting

bool fle(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 <= d2);}

bool fl(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 < d2);}

bool ble(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 >= d2);}

bool bl(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 > d2);}

// static
const CTaskEnum::Method CTrajectoryTask::ValidMethods[] =
{
  CTaskEnum::deterministic,
  CTaskEnum::stochastic,
  CTaskEnum::directMethod,
  CTaskEnum::tauLeap,
  CTaskEnum::adaptiveSA,
  CTaskEnum::hybridODE45,
#ifdef COPASI_DEBUG
  CTaskEnum::DsaLsodar,
#endif // COPASI_DEBUG
  CTaskEnum::UnsetMethod
};

CTrajectoryTask::CTrajectoryTask(const CCopasiContainer * pParent,
                                 const CTaskEnum::Task & type):
  CCopasiTask(pParent, type),
  mTimeSeriesRequested(true),
  mTimeSeries(),
  mpTrajectoryProblem(NULL),
  mpTrajectoryMethod(NULL),
  mUpdateMoieties(false),
  mContainerState(),
  mpContainerStateTime(NULL),
  mOutputStartTime(0.0),
  mpLessOrEqual(&fle),
  mpLess(&fl),
  mProceed(true)
{
  mpProblem = new CTrajectoryProblem(this);
  mpMethod = createMethod(CTaskEnum::deterministic);
  this->add(mpMethod, true);

  CCopasiParameter * pParameter = mpMethod->getParameter("Integrate Reduced Model");

  if (pParameter != NULL)
    mUpdateMoieties = *pParameter->getValue().pBOOL;
  else
    mUpdateMoieties = false;

  signalMathContainerChanged();
}

CTrajectoryTask::CTrajectoryTask(const CTrajectoryTask & src,
                                 const CCopasiContainer * pParent):
  CCopasiTask(src, pParent),
  mTimeSeriesRequested(src.mTimeSeriesRequested),
  mTimeSeries(),
  mpTrajectoryProblem(NULL),
  mpTrajectoryMethod(NULL),
  mUpdateMoieties(false),
  mContainerState(),
  mpContainerStateTime(NULL),
  mOutputStartTime(0.0),
  mpLessOrEqual(src.mpLessOrEqual),
  mpLess(src.mpLess),
  mProceed(src.mProceed)
{
  mpProblem =
    new CTrajectoryProblem(*static_cast< CTrajectoryProblem * >(src.mpProblem), this);

  mpMethod = createMethod(src.mpMethod->getSubType());
  * mpMethod = * src.mpMethod;

  mpMethod->elevateChildren();

  this->add(mpMethod, true);

  CCopasiParameter * pParameter = mpMethod->getParameter("Integrate Reduced Model");

  if (pParameter != NULL)
    mUpdateMoieties = *pParameter->getValue().pBOOL;
  else
    mUpdateMoieties = false;

  signalMathContainerChanged();
}

CTrajectoryTask::~CTrajectoryTask()
{
  cleanup();
}

void CTrajectoryTask::cleanup()
{}

void CTrajectoryTask::load(CReadConfig & configBuffer)
{
  configBuffer.getVariable("Dynamics", "bool", &mScheduled,
                           CReadConfig::LOOP);

  pdelete(mpProblem);
  mpProblem = new CTrajectoryProblem(this);
  ((CTrajectoryProblem *) mpProblem)->load(configBuffer);

  pdelete(mpMethod);
  mpMethod = createMethod(CTaskEnum::deterministic);

  CCopasiParameter * pParameter = mpMethod->getParameter("Integrate Reduced Model");

  if (pParameter != NULL)
    mUpdateMoieties = *pParameter->getValue().pBOOL;

  ((CTrajectoryMethod *)mpMethod)->setProblem((CTrajectoryProblem *) mpProblem);
}

bool CTrajectoryTask::initialize(const OutputFlag & of,
                                 COutputHandler * pOutputHandler,
                                 std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  mpTrajectoryProblem = dynamic_cast<CTrajectoryProblem *>(mpProblem);
  assert(mpTrajectoryProblem);

  mpTrajectoryMethod = dynamic_cast<CTrajectoryMethod *>(mpMethod);
  assert(mpTrajectoryMethod);

  mpTrajectoryMethod->setProblem(mpTrajectoryProblem);

  bool success = mpMethod->isValidProblem(mpProblem);

  CCopasiParameter * pParameter = mpMethod->getParameter("Integrate Reduced Model");

  if (pParameter != NULL)
    mUpdateMoieties = *pParameter->getValue().pBOOL;
  else
    mUpdateMoieties = false;

  // Handle the time series as a regular output.
  mTimeSeriesRequested = mpTrajectoryProblem->timeSeriesRequested();

  if ((pOutputHandler != NULL) &&
      mTimeSeriesRequested &&
      (of & CCopasiTask::TIME_SERIES))
    {
      mTimeSeries.allocate(mpTrajectoryProblem->getStepNumber());
      pOutputHandler->addInterface(&mTimeSeries);
    }
  else
    {
      mTimeSeries.clear();
    }

  success &= CCopasiTask::initialize(of, pOutputHandler, pOstream);

  signalMathContainerChanged();

  return success;
}

// virtual
void CTrajectoryTask::signalMathContainerChanged()
{
  if (mpContainer != NULL)
    {
      mContainerState.initialize(mpContainer->getState(mUpdateMoieties));
      mpContainerStateTime = mContainerState.array() + mpContainer->getTimeIndex();
    }
  else
    {
      mContainerState.initialize(0, NULL);
      mpContainerStateTime = NULL;
    }
}

bool CTrajectoryTask::process(const bool & useInitialValues)
{
  //*****

  processStart(useInitialValues);

  //*****

  //size_t FailCounter = 0;

  C_FLOAT64 Duration = mpTrajectoryProblem->getDuration();
  C_FLOAT64 StepSize = mpTrajectoryProblem->getStepSize();
  C_FLOAT64 StepNumber = fabs(Duration) / StepSize;

  if (isnan(StepNumber) || StepNumber < 1.0)
    StepNumber = 1.0;

  //the output starts only after "outputStartTime" has passed
  if (useInitialValues)
    mOutputStartTime = mpTrajectoryProblem->getOutputStartTime();
  else
    mOutputStartTime = *mpContainerStateTime + mpTrajectoryProblem->getOutputStartTime();

  C_FLOAT64 NextTimeToReport;

  const C_FLOAT64 EndTime = *mpContainerStateTime + Duration;
  const C_FLOAT64 StartTime = *mpContainerStateTime;
  C_FLOAT64 CompareEndTime;

  if (StepSize < 0.0)
    {
      mpLessOrEqual = &ble;
      mpLess = &bl;

      // It suffices to reach the end time within machine precision
      CompareEndTime = EndTime + 100.0 * (fabs(EndTime) * std::numeric_limits< C_FLOAT64 >::epsilon() + std::numeric_limits< C_FLOAT64 >::min());
    }
  else
    {
      mpLessOrEqual = &fle;
      mpLess = &fl;

      // It suffices to reach the end time within machine precision
      CompareEndTime = EndTime - 100.0 * (fabs(EndTime) * std::numeric_limits< C_FLOAT64 >::epsilon() + std::numeric_limits< C_FLOAT64 >::min());
    }

  unsigned C_INT32 StepCounter = 1;

  if (StepSize == 0.0 && Duration != 0.0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryProblem + 1, StepSize);
      return false;
    }

  // We need to execute any scheduled events for T_0
  mpContainer->processQueue(true);;

  output(COutputInterface::BEFORE);

  bool flagProceed = true;
  C_FLOAT64 handlerFactor = 100.0 / Duration;

  C_FLOAT64 Percentage = 0;
  size_t hProcess;

  if (mpCallBack != NULL && StepNumber > 1.0)
    {
      mpCallBack->setName("performing simulation...");
      C_FLOAT64 hundred = 100;
      hProcess = mpCallBack->addItem("Completion",
                                     Percentage,
                                     &hundred);
    }

  if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime)) output(COutputInterface::DURING);

  try
    {
      do
        {
          // This is numerically more stable then adding
          // mpTrajectoryProblem->getStepSize().
          NextTimeToReport =
            StartTime + (EndTime - StartTime) * StepCounter++ / StepNumber;

          flagProceed &= processStep(NextTimeToReport);

          if (mpCallBack != NULL && StepNumber > 1.0)
            {
              Percentage = (*mpContainerStateTime - StartTime) * handlerFactor;
              flagProceed &= mpCallBack->progressItem(hProcess);
            }

          if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime))
            {
              output(COutputInterface::DURING);
            }
        }
      while ((*mpLess)(*mpContainerStateTime, CompareEndTime) && flagProceed);
    }

  catch (int)
    {
      mpContainer->setState(mContainerState);
      mpContainer->updateSimulatedValues(mUpdateMoieties);
      mpContainer->pushState();

      if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime))
        {
          output(COutputInterface::DURING);
        }

      if (mpCallBack != NULL && StepNumber > 1.0) mpCallBack->finishItem(hProcess);

      output(COutputInterface::AFTER);

      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 16);
    }

  catch (CCopasiException & Exception)
    {
      mpContainer->setState(mContainerState);
      mpContainer->updateSimulatedValues(mUpdateMoieties);
      mpContainer->pushState();

      if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime))
        {
          output(COutputInterface::DURING);
        }

      if (mpCallBack != NULL && StepNumber > 1.0) mpCallBack->finishItem(hProcess);

      output(COutputInterface::AFTER);

      throw CCopasiException(Exception.getMessage());
    }

  if (mpCallBack != NULL && StepNumber > 1.0) mpCallBack->finishItem(hProcess);

  output(COutputInterface::AFTER);

  return true;
}

void CTrajectoryTask::processStart(const bool & useInitialValues)
{
  if (useInitialValues)
    {
      mpContainer->applyInitialValues();
    }

  mContainerState.initialize(mpContainer->getState(mUpdateMoieties));
  mpContainerStateTime = mContainerState.array() + mpContainer->getTimeIndex();

  mpTrajectoryMethod->start();

  return;
}

bool CTrajectoryTask::processStep(const C_FLOAT64 & endTime)
{
  CMath::StateChange StateChange = CMath::NoChange;

  C_FLOAT64 Tolerance = 100.0 * (fabs(endTime) * std::numeric_limits< C_FLOAT64 >::epsilon() + std::numeric_limits< C_FLOAT64 >::min());
  C_FLOAT64 NextTime = endTime;

  while (mProceed)
    {
      // TODO Provide a call back method for resolving simultaneous assignments.
      StateChange = mpContainer->processQueue(false);

      if (StateChange != CMath::NoChange)
        {
          if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime) &&
              mpTrajectoryProblem->getOutputEvent())
            {
              output(COutputInterface::DURING);
            }

          mContainerState = mpContainer->getState(mUpdateMoieties);
          mpTrajectoryMethod->stateChange(StateChange);
          StateChange = CMath::NoChange;
        }

      // std::min suffices since events are only supported in forward integration.
      NextTime = std::min(endTime, mpContainer->getProcessQueueExecutionTime());

      switch (mpTrajectoryMethod->step(NextTime - *mpContainerStateTime))
        {
          case CTrajectoryMethod::NORMAL:
            mpContainer->setState(mContainerState);
            mpContainer->updateSimulatedValues(mUpdateMoieties);

            if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime) &&
                *mpContainerStateTime == mpContainer->getProcessQueueExecutionTime() &&
                mpTrajectoryProblem->getOutputEvent())
              {
                output(COutputInterface::DURING);
              }

            // TODO Provide a call back method for resolving simultaneous assignments.
            StateChange = mpContainer->processQueue(true);

            if (fabs(*mpContainerStateTime - endTime) < Tolerance)
              {
                if (StateChange != CMath::NoChange)
                  {
                    mContainerState = mpContainer->getState(mUpdateMoieties);
                    mpTrajectoryMethod->stateChange(StateChange);
                    StateChange = CMath::NoChange;
                  }

                return true;
              }

            if (StateChange != CMath::NoChange)
              {
                if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime) &&
                    mpTrajectoryProblem->getOutputEvent())
                  {
                    output(COutputInterface::DURING);
                  }

                mContainerState = mpContainer->getState(mUpdateMoieties);
                mpTrajectoryMethod->stateChange(StateChange);
                StateChange = CMath::NoChange;
              }

            break;

          case CTrajectoryMethod::ROOT:
            mpContainer->setState(mContainerState);
            mpContainer->updateSimulatedValues(mUpdateMoieties);

            mpContainer->processRoots(true, mpTrajectoryMethod->getRoots());

            if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime) &&
                *mpContainerStateTime == mpContainer->getProcessQueueExecutionTime() &&
                mpTrajectoryProblem->getOutputEvent())
              {
                output(COutputInterface::DURING);
              }

            // TODO Provide a call back method for resolving simultaneous assignments.
            StateChange = mpContainer->processQueue(true);

            mpContainer->processRoots(false, mpTrajectoryMethod->getRoots());

            // If the root happens to coincide with end of the step we have to return and
            // inform the integrator of eventual state changes.
            if (fabs(*mpContainerStateTime - endTime) < Tolerance)
              {
                if (StateChange != CMath::NoChange)
                  {
                    mContainerState = mpContainer->getState(mUpdateMoieties);
                    mpTrajectoryMethod->stateChange(StateChange);
                    StateChange = CMath::NoChange;
                  }

                return true;
              }

            if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime) &&
                mpTrajectoryProblem->getOutputEvent() &&
                (StateChange != CMath::NoChange ||
                 *mpContainerStateTime == mpContainer->getProcessQueueExecutionTime()))
              {
                output(COutputInterface::DURING);
              }

            if (StateChange != CMath::NoChange)
              {
                mContainerState = mpContainer->getState(mUpdateMoieties);
                mpTrajectoryMethod->stateChange(StateChange);
                StateChange = CMath::NoChange;
              }

            break;

          case CTrajectoryMethod::FAILURE:
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 12);

            return false;
            break;
        }

      mProceed = mpCallBack == NULL || mpCallBack->proceed();
    }

  return mProceed;
}

bool CTrajectoryTask::restore()
{
  bool success = CCopasiTask::restore();

  if (mUpdateModel)
    {
      mpContainer->updateSimulatedValues(true);
      mpContainer->setInitialState(mpContainer->getState(false));
      mpContainer->updateInitialValues(CModelParameter::ParticleNumbers);
      mpContainer->pushInitialState();
    }

  return success;
}

// virtual
const CTaskEnum::Method * CTrajectoryTask::getValidMethods() const
{
  return CTrajectoryTask::ValidMethods;
}

// virtual
void CTrajectoryTask::signalMethodChanged()
{
  CCopasiParameter * pParameter = mpMethod->getParameter("Integrate Reduced Model");

  if (pParameter != NULL)
    mUpdateMoieties = *pParameter->getValue().pBOOL;
  else
    mUpdateMoieties = false;

  return;
}

const CTimeSeries & CTrajectoryTask::getTimeSeries() const
{return mTimeSeries;}
