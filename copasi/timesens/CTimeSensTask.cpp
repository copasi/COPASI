// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * CTimeSensTask class.
 *
 * This class implements a time sensitivities task which is comprised of a
 * of a problem and a method. Additionally calls to the reporting
 * methods are done when initialized.
 *
 */

#include <string>
#include <cmath>

#include "copasi/copasi.h"

#include "CTimeSensTask.h"
#include "CTimeSensProblem.h"
#include "CTimeSensMethod.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CState.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CReport.h"
#include "copasi/utilities/CProcessReport.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/utilities/CMethodFactory.h"

#define XXXX_Reporting

//static
bool CTimeSensTask::fle(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 <= d2);}

bool CTimeSensTask::fl(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 < d2);}

bool CTimeSensTask::ble(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 >= d2);}

bool CTimeSensTask::bl(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 > d2);}

// static
const CTaskEnum::Method CTimeSensTask::ValidMethods[] =
{
  CTaskEnum::Method::timeSensLsoda,
  CTaskEnum::Method::UnsetMethod
};

CTimeSensTask::CTimeSensTask(const CDataContainer * pParent,
                             const CTaskEnum::Task & type):
  CCopasiTask(pParent, type),
  mTimeSeriesRequested(true),
  mTimeSeries(),
  mpTimeSensProblem(NULL),
  mpSteadyState(NULL),
  mpTimeSensMethod(NULL),
  mUpdateMoieties(false),
  mContainerState(),
  mpContainerStateTime(NULL),
  mOutputStartTime(0.0),
  mpLessOrEqual(&fle),
  mpLess(&fl),
  mProceed(true)
{
  mpMethod = CMethodFactory::create(getType(), CTaskEnum::Method::timeSensLsoda, this);
  mUpdateMoieties = static_cast< CTimeSensMethod * >(mpMethod)->integrateReducedModel();

  signalMathContainerChanged();
}

CTimeSensTask::CTimeSensTask(const CTimeSensTask & src,
                             const CDataContainer * pParent):
  CCopasiTask(src, pParent),
  mTimeSeriesRequested(src.mTimeSeriesRequested),
  mTimeSeries(),
  mpTimeSensProblem(NULL),
  mpSteadyState(NULL),
  mpTimeSensMethod(NULL),
  mUpdateMoieties(false),
  mContainerState(),
  mpContainerStateTime(NULL),
  mOutputStartTime(0.0),
  mpLessOrEqual(src.mpLessOrEqual),
  mpLess(src.mpLess),
  mProceed(src.mProceed)
{
  mUpdateMoieties = static_cast< CTimeSensMethod * >(mpMethod)->integrateReducedModel();

  signalMathContainerChanged();
}

CTimeSensTask::~CTimeSensTask()
{
  cleanup();
}

void CTimeSensTask::cleanup()
{}

bool CTimeSensTask::initialize(const OutputFlag & of,
                               COutputHandler * pOutputHandler,
                               std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  mpTimeSensProblem = dynamic_cast<CTimeSensProblem *>(mpProblem);
  assert(mpTimeSensProblem);

  mpTimeSensMethod = dynamic_cast<CTimeSensMethod *>(mpMethod);
  assert(mpTimeSensMethod);

  mpTimeSensMethod->setProblem(mpTimeSensProblem);

  bool success = mpMethod->isValidProblem(mpProblem);

  mUpdateMoieties = static_cast< CTimeSensMethod * >(mpMethod)->integrateReducedModel();

  // Handle the time series as a regular output.
  mTimeSeriesRequested = mpTimeSensProblem->timeSeriesRequested();

  if ((pOutputHandler != NULL) &&
      mTimeSeriesRequested &&
      (of & CCopasiTask::TIME_SERIES))
    {
      mTimeSeries.allocate(mpTimeSensProblem->getStepNumber());
      pOutputHandler->addInterface(&mTimeSeries);
    }
  else
    {
      mTimeSeries.clear();
    }

  mpSteadyState = NULL;

  if (mpTimeSensProblem->getStartInSteadyState())
    {
      CDataModel* pDataModel = getObjectDataModel();

      if (pDataModel && pDataModel->getTaskList())
        mpSteadyState = dynamic_cast<CSteadyStateTask *>(&pDataModel->getTaskList()->operator[]("Steady-State"));

      if (mpSteadyState != NULL)
        mpSteadyState->initialize(of, NULL, NULL);
    }

  success &= updateMatrices();

  static_cast<CTimeSensMethod*>(mpMethod)->initializeDerivativesCalculations(static_cast<CTimeSensMethod*>(mpMethod)->integrateReducedModel());

  success &= CCopasiTask::initialize(of, pOutputHandler, pOstream);

  signalMathContainerChanged();

  return success;
}

// virtual
void CTimeSensTask::signalMathContainerChanged()
{
  if (mpContainer != NULL)
    {
      mContainerState.initialize(mpContainer->getState(mUpdateMoieties));
      mpContainerStateTime = mContainerState.array() + mpContainer->getCountFixedEventTargets();
    }
  else
    {
      mContainerState.initialize(0, NULL);
      mpContainerStateTime = NULL;
    }
}

bool CTimeSensTask::process(const bool & useInitialValues)
{
  //*****
  mProceed = true;

  processStart(useInitialValues);

  //*****

  //size_t FailCounter = 0;

  C_FLOAT64 Duration = mpTimeSensProblem->getDuration();
  C_FLOAT64 StepSize = mpTimeSensProblem->getStepSize();
  C_FLOAT64 StepNumber = fabs(Duration) / StepSize;

  if (mpTimeSensProblem->getAutomaticStepSize() ||
      std::isnan(StepNumber) ||
      StepNumber < 1.0)
    {
      StepNumber = 1.0;
    }

  //the output starts only after "outputStartTime" has passed
  if (useInitialValues)
    mOutputStartTime = mpTimeSensProblem->getOutputStartTime();
  else
    mOutputStartTime = *mpContainerStateTime + mpTimeSensProblem->getOutputStartTime();

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

  output(COutputInterface::BEFORE);

  bool flagProceed = true;
  C_FLOAT64 handlerFactor = 100.0 / Duration;

  C_FLOAT64 Percentage = 0;
  size_t hProcess = C_INVALID_INDEX;

  if (mProcessReport && StepNumber > 1.0)
    {
      mProcessReport.setName("performing simulation...");
      C_FLOAT64 hundred = 100;
      hProcess = mProcessReport.addItem("Completion",
                                        Percentage,
                                        &hundred);
    }

  try
    {
      // We need to execute any scheduled events for T_0
      CMath::StateChange StateChange = mpContainer->processQueue(true);

      if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime))
        {
          output(COutputInterface::DURING);
        }

      if (StateChange)
        {
          mContainerState = mpContainer->getState(mUpdateMoieties);
          mpTimeSensMethod->stateChange(StateChange);
        }

      do
        {
          // This is numerically more stable then adding
          // mpTrajectoryProblem->getStepSize().
          NextTimeToReport =
            StartTime + (EndTime - StartTime) * StepCounter++ / StepNumber;

          flagProceed &= processStep(NextTimeToReport, NextTimeToReport == EndTime);

          if (hProcess != C_INVALID_INDEX)
            {
              Percentage = (*mpContainerStateTime - StartTime) * handlerFactor;
              flagProceed &= mProcessReport.progressItem(hProcess);
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
      mpContainer->updateTransientDataValues();
      mpContainer->pushAllTransientValues();

      if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime))
        {
          output(COutputInterface::DURING);
        }

      if (hProcess != C_INVALID_INDEX) mProcessReport.finishItem(hProcess);

      output(COutputInterface::AFTER);

      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 16);
    }

  catch (CCopasiException & Exception)
    {
      mpContainer->setState(mContainerState);
      mpContainer->updateSimulatedValues(mUpdateMoieties);
      mpContainer->updateTransientDataValues();
      mpContainer->pushAllTransientValues();

      if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime))
        {
          output(COutputInterface::DURING);
        }

      if (hProcess != C_INVALID_INDEX) mProcessReport.finishItem(hProcess);

      output(COutputInterface::AFTER);

      throw CCopasiException(Exception.getMessage());
    }

  if (hProcess != C_INVALID_INDEX) mProcessReport.finishItem(hProcess);

  output(COutputInterface::AFTER);

  return true;
}

bool CTimeSensTask::processStart(const bool & useInitialValues)
{
  bool success = true;
  mContainerState.initialize(mpContainer->getState(mUpdateMoieties));
  mpContainerStateTime = mContainerState.array() + mpContainer->getCountFixedEventTargets();

  if (useInitialValues)
    {
      if (mpTimeSensProblem->getStartInSteadyState())
        {
          if (mpSteadyState != NULL &&
              !mpSteadyState->process(true))
            {
              CCopasiMessage(CCopasiMessage::ERROR, "Steady state could not be reached.");
              success = false;
            }

          * mpContainerStateTime = 0;
        }
      else
        {
          mpContainer->applyInitialValues();
        }
    }

  mpTimeSensMethod->start();

  return success;
}

bool CTimeSensTask::processStep(const C_FLOAT64 & endTime, const bool & final)
{
  CMath::StateChange StateChange = CMath::StateChange::None;

  C_FLOAT64 Tolerance = 100.0 * (fabs(endTime) * std::numeric_limits< C_FLOAT64 >::epsilon() + std::numeric_limits< C_FLOAT64 >::min());
  C_FLOAT64 NextTime = endTime;

  while (mProceed)
    {
      // TODO Provide a call back method for resolving simultaneous assignments.
      StateChange = mpContainer->processQueue(false);

      if (StateChange)
        {
          if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime) &&
              mpTimeSensProblem->getOutputEvent())
            {
              output(COutputInterface::DURING);
            }

          mContainerState = mpContainer->getState(mUpdateMoieties);
          mpTimeSensMethod->stateChange(StateChange);
          StateChange = CMath::StateChange::None;
        }

      // std::min suffices since events are only supported in forward integration.
      NextTime = std::min(endTime, mpContainer->getProcessQueueExecutionTime());

      switch (mpTimeSensMethod->step(NextTime - *mpContainerStateTime, final))
        {
          case CTimeSensMethod::NORMAL:
            mpContainer->setState(mContainerState);
            mpContainer->updateSimulatedValues(mUpdateMoieties);

            if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime) &&
                *mpContainerStateTime == mpContainer->getProcessQueueExecutionTime() &&
                mpTimeSensProblem->getOutputEvent())
              {
                output(COutputInterface::DURING);
              }

            // TODO Provide a call back method for resolving simultaneous assignments.
            StateChange = mpContainer->processQueue(true);

            if (fabs(*mpContainerStateTime - endTime) < Tolerance ||
                (*mpLessOrEqual)(endTime, *mpContainerStateTime))
              {
                if (StateChange)
                  {
                    mContainerState = mpContainer->getState(mUpdateMoieties);
                    mpTimeSensMethod->stateChange(StateChange);
                    StateChange = CMath::StateChange::None;
                  }

                return true;
              }

            if (StateChange)
              {
                if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime) &&
                    mpTimeSensProblem->getOutputEvent())
                  {
                    output(COutputInterface::DURING);
                  }

                mContainerState = mpContainer->getState(mUpdateMoieties);
                mpTimeSensMethod->stateChange(StateChange);
                StateChange = CMath::StateChange::None;
              }
            else if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime) &&
                     mpTimeSensProblem->getAutomaticStepSize())
              {
                output(COutputInterface::DURING);
              }

            break;

          case CTimeSensMethod::ROOT:
            mpContainer->setState(mContainerState);
            mpContainer->updateSimulatedValues(mUpdateMoieties);
            mpContainer->updateRootValues(mUpdateMoieties);

            mpContainer->processRoots(true, mpTimeSensMethod->getRoots());

            if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime) &&
                *mpContainerStateTime == mpContainer->getProcessQueueExecutionTime() &&
                mpTimeSensProblem->getOutputEvent())
              {
                output(COutputInterface::DURING);
              }

            // TODO Provide a call back method for resolving simultaneous assignments.
            StateChange = mpContainer->processQueue(true);

            mpContainer->processRoots(false, mpTimeSensMethod->getRoots());

            // If the root happens to coincide with end of the step we have to return and
            // inform the integrator of eventual state changes.
            if (fabs(*mpContainerStateTime - endTime) < Tolerance ||
                (*mpLessOrEqual)(endTime, *mpContainerStateTime))
              {
                if (StateChange)
                  {
                    mContainerState = mpContainer->getState(mUpdateMoieties);
                    mpTimeSensMethod->stateChange(StateChange);
                    StateChange = CMath::StateChange::None;
                  }

                return true;
              }

            if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime) &&
                mpTimeSensProblem->getOutputEvent() &&
                (StateChange ||
                 *mpContainerStateTime == mpContainer->getProcessQueueExecutionTime()))
              {
                output(COutputInterface::DURING);
              }
            else if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime) &&
                     mpTimeSensProblem->getAutomaticStepSize())
              {
                output(COutputInterface::DURING);
              }

            if (StateChange)
              {
                mContainerState = mpContainer->getState(mUpdateMoieties);
                mpTimeSensMethod->stateChange(StateChange);
                StateChange = CMath::StateChange::None;
              }

            break;

          case CTimeSensMethod::FAILURE:
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 12);

            return false;
            break;
        }

      mProceed = mProcessReport.proceed();
    }

  return mProceed;
}

// virtual
const CTaskEnum::Method * CTimeSensTask::getValidMethods() const
{
  return CTimeSensTask::ValidMethods;
}

// virtual
void CTimeSensTask::signalMethodChanged()
{
  mUpdateMoieties = static_cast< CTimeSensMethod * >(mpMethod)->integrateReducedModel();

  return;
}

const CTimeSeries & CTimeSensTask::getTimeSeries() const
{return mTimeSeries;}

bool CTimeSensTask::updateMatrices()
{
  CTimeSensMethod* tmpMethod = dynamic_cast<CTimeSensMethod*>(mpMethod);

  if (tmpMethod)
    tmpMethod->initResult();

  return true;
}

//virtual
void CTimeSensTask::output(const COutputInterface::Activity & activity)
{
  if (mpTimeSensMethod)
    mpTimeSensMethod->copySensitivitiesToResultMatrix();

  CCopasiTask::output(activity);
}
