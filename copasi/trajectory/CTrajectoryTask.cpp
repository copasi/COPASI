// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/copasi.h"

#include "CTrajectoryTask.h"
#include "CTrajectoryProblem.h"
#include "CTrajectoryMethod.h"
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
  CTaskEnum::Method::deterministic,
  CTaskEnum::Method::RADAU5,
  CTaskEnum::Method::stochastic,
  CTaskEnum::Method::directMethod,
  CTaskEnum::Method::tauLeap,
  CTaskEnum::Method::adaptiveSA,
  CTaskEnum::Method::hybrid,
  CTaskEnum::Method::hybridLSODA,
  CTaskEnum::Method::hybridODE45,
#ifdef COPASI_DEBUG
  CTaskEnum::Method::DsaLsodar,
#endif // COPASI_DEBUG
  CTaskEnum::Method::stochasticRunkeKuttaRI5,
  CTaskEnum::Method::UnsetMethod
};

CTrajectoryTask::CTrajectoryTask(const CDataContainer * pParent,
                                 const CTaskEnum::Task & type):
  CCopasiTask(pParent, type),
  mTimeSeriesRequested(true),
  mTimeSeries(),
  mpTrajectoryProblem(NULL),
  mpSteadyState(NULL),
  mpTrajectoryMethod(NULL),
  mUpdateMoieties(false),
  mContainerState(),
  mpContainerStateTime(NULL),
  mOutputStartTime(0.0),
  mpLessOrEqual(&fle),
  mpLess(&fl)
{
  mpMethod = CMethodFactory::create(getType(), CTaskEnum::Method::deterministic, this);
  mUpdateMoieties = static_cast< CTrajectoryMethod * >(mpMethod)->integrateReducedModel();

  signalMathContainerChanged();
}

CTrajectoryTask::CTrajectoryTask(const CTrajectoryTask & src,
                                 const CDataContainer * pParent):
  CCopasiTask(src, pParent),
  mTimeSeriesRequested(src.mTimeSeriesRequested),
  mTimeSeries(),
  mpTrajectoryProblem(NULL),
  mpSteadyState(NULL),
  mpTrajectoryMethod(NULL),
  mUpdateMoieties(false),
  mContainerState(),
  mpContainerStateTime(NULL),
  mOutputStartTime(0.0),
  mpLessOrEqual(src.mpLessOrEqual),
  mpLess(src.mpLess)
{
  mUpdateMoieties = static_cast< CTrajectoryMethod * >(mpMethod)->integrateReducedModel();

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
  mpMethod = CMethodFactory::create(getType(), CTaskEnum::Method::deterministic, this);

  mUpdateMoieties = static_cast< CTrajectoryMethod * >(mpMethod)->integrateReducedModel();
  static_cast< CTrajectoryMethod * >(mpMethod)->setProblem(static_cast< CTrajectoryProblem * >(mpProblem));
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

  mUpdateMoieties = static_cast< CTrajectoryMethod * >(mpMethod)->integrateReducedModel();

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

  mpSteadyState = NULL;

  if (mpTrajectoryProblem->getStartInSteadyState())
    {
      CDataModel* pDataModel = getObjectDataModel();

      if (pDataModel && pDataModel->getTaskList())
        mpSteadyState = dynamic_cast<CSteadyStateTask *>(&pDataModel->getTaskList()->operator[]("Steady-State"));

      if (mpSteadyState != NULL)
        mpSteadyState->initialize(of, NULL, NULL);
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
      mpContainerStateTime = mContainerState.array() + mpContainer->getCountFixedEventTargets();
    }
  else
    {
      mContainerState.initialize(0, NULL);
      mpContainerStateTime = NULL;
    }
}

bool CTrajectoryTask::process(const bool& useInitialValues)
{
  if (mpTrajectoryProblem->getUseValues())
    return processValues(useInitialValues);

  return processTrajectory(useInitialValues);
}

bool CTrajectoryTask::processTrajectory(const bool& useInitialValues)
{
  //*****
  if (!processStart(useInitialValues))
    return false;

  //*****

  //size_t FailCounter = 0;

  C_FLOAT64 Duration = mpTrajectoryProblem->getDuration();
  C_FLOAT64 StepSize = mpTrajectoryProblem->getStepSize();
  C_FLOAT64 StepNumber = fabs(Duration) / StepSize;

  if (mpTrajectoryProblem->getAutomaticStepSize() ||
      std::isnan(StepNumber) ||
      StepNumber < 1.0)
    {
      StepNumber = 1.0;
    }

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

  output(COutputInterface::BEFORE);

  bool flagProceed = true;
  C_FLOAT64 handlerFactor = 100.0 / Duration;

  C_FLOAT64 Percentage = 0;
  size_t hProcess = C_INVALID_INDEX;

  if (mProcessReport)
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
          mpTrajectoryMethod->stateChange(StateChange);
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

bool CTrajectoryTask::processValues(const bool& useInitialValues)
{
  //*****
  processStart(useInitialValues);

  //*****

  //size_t FailCounter = 0;

  std::set<C_FLOAT64> Values = mpTrajectoryProblem->getValues();

  if (Values.empty())
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryProblem + 32);
      return false;
    }

  std::set<C_FLOAT64>::const_iterator itValue = Values.begin();
  C_FLOAT64 Duration = *Values.rbegin() - *mpContainerStateTime;

  //the output starts only after "outputStartTime" has passed
  if (useInitialValues)
    mOutputStartTime = mpTrajectoryProblem->getOutputStartTime();
  else
    mOutputStartTime = *mpContainerStateTime + mpTrajectoryProblem->getOutputStartTime();

  C_FLOAT64 NextTimeToReport = - std::numeric_limits< C_FLOAT64 >::infinity();

  const C_FLOAT64 EndTime = *mpContainerStateTime + Duration;
  const C_FLOAT64 StartTime = *mpContainerStateTime;
  C_FLOAT64 CompareEndTime;

  mpLessOrEqual = &fle;
  mpLess = &fl;

  // It suffices to reach the end time within machine precision
  CompareEndTime = EndTime - 100.0 * (fabs(EndTime) * std::numeric_limits< C_FLOAT64 >::epsilon() + std::numeric_limits< C_FLOAT64 >::min());

  output(COutputInterface::BEFORE);

  bool flagProceed = true;
  C_FLOAT64 handlerFactor = 100.0 / Duration;

  C_FLOAT64 Percentage = 0;
  size_t hProcess = C_INVALID_INDEX;

  if (mProcessReport)
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
          mpTrajectoryMethod->stateChange(StateChange);
        }

      do
        {
          // We silently ignore values in the past
          while (NextTimeToReport <= *mpContainerStateTime && itValue != Values.end())
            {
              NextTimeToReport = *itValue++;
            }

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

bool CTrajectoryTask::processStart(const bool & useInitialValues)
{
  bool success = true;

  mContainerState.initialize(mpContainer->getState(mUpdateMoieties));
  mpContainerStateTime = mContainerState.array() + mpContainer->getCountFixedEventTargets();

  if (useInitialValues)
    {
      if (mpTrajectoryProblem->getStartInSteadyState())
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

  mpTrajectoryMethod->start();

  return success;
}

bool CTrajectoryTask::processStep(const C_FLOAT64 & endTime, const bool & final)
{
  CMath::StateChange StateChange = CMath::StateChange::None;

  C_FLOAT64 Tolerance = 100.0 * (fabs(endTime) * std::numeric_limits< C_FLOAT64 >::epsilon() + std::numeric_limits< C_FLOAT64 >::min());
  C_FLOAT64 NextTime = endTime;

  bool Proceed = true;

  while (Proceed)
    {
      // TODO Provide a call back method for resolving simultaneous assignments.
      StateChange = mpContainer->processQueue(false);

      if (StateChange)
        {
          if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime) &&
              mpTrajectoryProblem->getOutputEvent())
            {
              output(COutputInterface::DURING);
            }

          mContainerState = mpContainer->getState(mUpdateMoieties);
          mpTrajectoryMethod->stateChange(StateChange);
          StateChange = CMath::StateChange::None;
        }

      // std::min suffices since events are only supported in forward integration.
      NextTime = std::min(endTime, mpContainer->getProcessQueueExecutionTime());

      switch (mpTrajectoryMethod->step(NextTime - *mpContainerStateTime, final))
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

            if (fabs(*mpContainerStateTime - endTime) < Tolerance ||
                (*mpLessOrEqual)(endTime, *mpContainerStateTime))
              {
                if (StateChange)
                  {
                    mContainerState = mpContainer->getState(mUpdateMoieties);
                    mpTrajectoryMethod->stateChange(StateChange);
                    StateChange = CMath::StateChange::None;
                  }

                return true;
              }

            if (StateChange)
              {
                if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime) &&
                    mpTrajectoryProblem->getOutputEvent())
                  {
                    output(COutputInterface::DURING);
                  }

                mContainerState = mpContainer->getState(mUpdateMoieties);
                mpTrajectoryMethod->stateChange(StateChange);
                StateChange = CMath::StateChange::None;
              }
            else if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime) &&
                     mpTrajectoryProblem->getAutomaticStepSize())
              {
                output(COutputInterface::DURING);
              }

            break;

          case CTrajectoryMethod::ROOT:
            mpContainer->setState(mContainerState);
            mpContainer->updateSimulatedValues(mUpdateMoieties);
            mpContainer->updateRootValues(mUpdateMoieties);

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
            if (fabs(*mpContainerStateTime - endTime) < Tolerance ||
                (*mpLessOrEqual)(endTime, *mpContainerStateTime))
              {
                if (StateChange)
                  {
                    mContainerState = mpContainer->getState(mUpdateMoieties);
                    mpTrajectoryMethod->stateChange(StateChange);
                    StateChange = CMath::StateChange::None;
                  }

                return true;
              }

            if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime) &&
                mpTrajectoryProblem->getOutputEvent() &&
                (StateChange ||
                 *mpContainerStateTime == mpContainer->getProcessQueueExecutionTime()))
              {
                output(COutputInterface::DURING);
              }
            else if ((*mpLessOrEqual)(mOutputStartTime, *mpContainerStateTime) &&
                     mpTrajectoryProblem->getAutomaticStepSize())
              {
                output(COutputInterface::DURING);
              }

            if (StateChange)
              {
                mContainerState = mpContainer->getState(mUpdateMoieties);
                mpTrajectoryMethod->stateChange(StateChange);
                StateChange = CMath::StateChange::None;
              }

            break;

          case CTrajectoryMethod::FAILURE:
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 12);

            return false;
            break;
        }

      Proceed = mProcessReport.proceed();
    }

  return Proceed;
}

// virtual
const CTaskEnum::Method * CTrajectoryTask::getValidMethods() const
{
  return CTrajectoryTask::ValidMethods;
}

// virtual
void CTrajectoryTask::signalMethodChanged()
{
  mUpdateMoieties = static_cast< CTrajectoryMethod * >(mpMethod)->integrateReducedModel();

  return;
}

const CTimeSeries & CTrajectoryTask::getTimeSeries() const
{return mTimeSeries;}
