// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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
#include "steadystate/CSteadyStateTask.h"
#include "model/CModel.h"
#include "model/CMathModel.h"
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

const unsigned int CTrajectoryTask::ValidMethods[] =
{
  CCopasiMethod::deterministic,
  CCopasiMethod::stochastic,
  CCopasiMethod::directMethod,
  CCopasiMethod::tauLeap,
  CCopasiMethod::adaptiveSA,
  CCopasiMethod::hybrid,
  CCopasiMethod::hybridLSODA,
#ifdef COPASI_DEBUG
  CCopasiMethod::hybridODE45,
  CCopasiMethod::DsaLsodar,
#endif // COPASI_DEBUG
  CCopasiMethod::unset
};

CTrajectoryTask::CTrajectoryTask(const CCopasiContainer * pParent):
  CCopasiTask(CCopasiTask::timeCourse, pParent),
  mTimeSeriesRequested(true),
  mTimeSeries(),
  mpTrajectoryProblem(NULL),
  mpSteadyState(NULL),
  mpTrajectoryMethod(NULL),
  mUpdateMoieties(false),
  mpCurrentState(NULL),
  mpCurrentTime(NULL),
  mOutputStartTime(0.0),
  mpLessOrEqual(&fle),
  mpLess(&fl)
{
  mpProblem = new CTrajectoryProblem(this);
  mpMethod = createMethod(CCopasiMethod::deterministic);
  this->add(mpMethod, true);

  CCopasiParameter * pParameter = mpMethod->getParameter("Integrate Reduced Model");

  if (pParameter != NULL)
    mUpdateMoieties = *pParameter->getValue().pBOOL;
  else
    mUpdateMoieties = false;
}

CTrajectoryTask::CTrajectoryTask(const CTrajectoryTask & src,
                                 const CCopasiContainer * pParent):
  CCopasiTask(src, pParent),
  mTimeSeriesRequested(src.mTimeSeriesRequested),
  mTimeSeries(),
  mpTrajectoryProblem(NULL),
  mpSteadyState(NULL),
  mpTrajectoryMethod(NULL),
  mUpdateMoieties(false),
  mpCurrentState(NULL),
  mpCurrentTime(NULL),
  mOutputStartTime(0.0),
  mpLessOrEqual(src.mpLessOrEqual),
  mpLess(src.mpLess)
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
}

CTrajectoryTask::~CTrajectoryTask()
{
  cleanup();
}

void CTrajectoryTask::cleanup()
{
  pdelete(mpCurrentState);
}

void CTrajectoryTask::load(CReadConfig & configBuffer)
{
  configBuffer.getVariable("Dynamics", "bool", &mScheduled,
                           CReadConfig::LOOP);

  pdelete(mpProblem);
  mpProblem = new CTrajectoryProblem(this);
  ((CTrajectoryProblem *) mpProblem)->load(configBuffer);

  pdelete(mpMethod);
  mpMethod = CTrajectoryMethod::createMethod();
  this->add(mpMethod, true);

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

  pdelete(mpCurrentState);
  mpCurrentState = new CState(mpTrajectoryProblem->getModel()->getState());
  mpCurrentTime = &mpCurrentState->getTime();

  //mpOutputStartTime = & mpTrajectoryProblem->getOutputStartTime();

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

  mpTrajectoryProblem->getModel()->getMathModel()->getProcessQueue().setContinueSimultaneousEvents(mpTrajectoryProblem->getContinueSimultaneousEvents());

  if (mpTrajectoryProblem->getStartInSteadyState())
    {
      mpSteadyState =
        dynamic_cast<CSteadyStateTask *>((*mpTrajectoryProblem->getObjectDataModel()->getTaskList())["Steady-State"]);

      if (mpSteadyState == NULL) fatalError();

      mpSteadyState->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);
    }
  else
    {
      mpSteadyState = NULL;
    }

  if (!CCopasiTask::initialize(of, pOutputHandler, pOstream)) success = false;

  return success;
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
    mOutputStartTime = *mpCurrentTime + mpTrajectoryProblem->getOutputStartTime();

  C_FLOAT64 NextTimeToReport;

  const C_FLOAT64 EndTime = *mpCurrentTime + Duration;
  const C_FLOAT64 StartTime = *mpCurrentTime;
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
  size_t hProcess;

  if (mpCallBack != NULL && StepNumber > 1.0)
    {
      mpCallBack->setName("performing simulation...");
      C_FLOAT64 hundred = 100;
      hProcess = mpCallBack->addItem("Completion",
                                     Percentage,
                                     &hundred);
    }

  if ((*mpLessOrEqual)(mOutputStartTime, *mpCurrentTime)) output(COutputInterface::DURING);

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
              Percentage = (*mpCurrentTime - StartTime) * handlerFactor;
              flagProceed &= mpCallBack->progressItem(hProcess);
            }

          if ((*mpLessOrEqual)(mOutputStartTime, *mpCurrentTime))
            {
              output(COutputInterface::DURING);
            }
        }
      while ((*mpLess)(*mpCurrentTime, CompareEndTime) && flagProceed);
    }

  catch (int)
    {
      mpTrajectoryProblem->getModel()->setState(*mpCurrentState);
      mpTrajectoryProblem->getModel()->updateSimulatedValues(mUpdateMoieties);

      if ((*mpLessOrEqual)(mOutputStartTime, *mpCurrentTime))
        {
          output(COutputInterface::DURING);
        }

      if (mpCallBack != NULL && StepNumber > 1.0) mpCallBack->finishItem(hProcess);

      output(COutputInterface::AFTER);

      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 16);
    }

  catch (CCopasiException & Exception)
    {
      mpTrajectoryProblem->getModel()->setState(*mpCurrentState);
      mpTrajectoryProblem->getModel()->updateSimulatedValues(mUpdateMoieties);

      if ((*mpLessOrEqual)(mOutputStartTime, *mpCurrentTime))
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
      if (mpTrajectoryProblem->getStartInSteadyState())
        {
          if (!mpSteadyState->process(true))
            {
              CCopasiMessage(CCopasiMessage::ERROR, "Steady state could not be reached.");
            }

          mpSteadyState->getObjectDataModel()->getModel()->setTime(0);
        }
      else
        {
          mpTrajectoryProblem->getModel()->applyInitialValues();
        }
    }

  *mpCurrentState = mpTrajectoryProblem->getModel()->getState();

  mpTrajectoryMethod->setCurrentState(mpCurrentState);
  mpTrajectoryMethod->start(mpCurrentState);

  return;
}

bool CTrajectoryTask::processStep(const C_FLOAT64 & endTime)
{
  CModel * pModel = mpTrajectoryProblem->getModel();
  bool StateChanged = false;
  bool proceed = true;

  C_FLOAT64 Tolerance = 100.0 * (fabs(endTime) * std::numeric_limits< C_FLOAT64 >::epsilon() + std::numeric_limits< C_FLOAT64 >::min());
  C_FLOAT64 NextTime = endTime;

  while (proceed)
    {
      // TODO Provide a call back method for resolving simultaneous assignments.
      StateChanged = pModel->processQueue(*mpCurrentTime, false, NULL);

      if (StateChanged)
        {
          if ((*mpLessOrEqual)(mOutputStartTime, *mpCurrentTime) &&
              mpTrajectoryProblem->getOutputEvent())
            {
              output(COutputInterface::DURING);
            }

          *mpCurrentState = pModel->getState();
          mpTrajectoryMethod->stateChanged();
          StateChanged = false;
        }

      // std::min suffices since events are only supported in forward integration.
      NextTime = std::min(endTime, pModel->getProcessQueueExecutionTime());

      switch (mpTrajectoryMethod->step(NextTime - *mpCurrentTime))
        {
          case CTrajectoryMethod::NORMAL:
            pModel->setState(*mpCurrentState);
            pModel->updateSimulatedValues(mUpdateMoieties);

            if ((*mpLessOrEqual)(mOutputStartTime, *mpCurrentTime) &&
                *mpCurrentTime == pModel->getProcessQueueExecutionTime() &&
                mpTrajectoryProblem->getOutputEvent())
              {
                output(COutputInterface::DURING);
              }

            // TODO Provide a call back method for resolving simultaneous assignments.
            StateChanged = pModel->processQueue(*mpCurrentTime, true, NULL);

            if (fabs(*mpCurrentTime - endTime) < Tolerance)
              {
                if (StateChanged)
                  {
                    *mpCurrentState = pModel->getState();
                    mpTrajectoryMethod->stateChanged();
                    StateChanged = false;
                  }

                return true;
              }

            if (StateChanged)
              {
                if ((*mpLessOrEqual)(mOutputStartTime, *mpCurrentTime) &&
                    mpTrajectoryProblem->getOutputEvent())
                  {
                    output(COutputInterface::DURING);
                  }

                *mpCurrentState = pModel->getState();
                mpTrajectoryMethod->stateChanged();
                StateChanged = false;
              }

            break;

          case CTrajectoryMethod::ROOT:
            pModel->setState(*mpCurrentState);
            pModel->updateSimulatedValues(mUpdateMoieties);

            pModel->processRoots(*mpCurrentTime, true, true, mpTrajectoryMethod->getRoots());

            if ((*mpLessOrEqual)(mOutputStartTime, *mpCurrentTime) &&
                *mpCurrentTime == pModel->getProcessQueueExecutionTime() &&
                mpTrajectoryProblem->getOutputEvent())
              {
                output(COutputInterface::DURING);
              }

            // TODO Provide a call back method for resolving simultaneous assignments.
            StateChanged = pModel->processQueue(*mpCurrentTime, true, NULL);

            pModel->processRoots(*mpCurrentTime, false, true, mpTrajectoryMethod->getRoots());

            // If the root happens to coincide with end of the step we have to return
            if (fabs(*mpCurrentTime - endTime) < Tolerance)
              {
                if (StateChanged)
                  {
                    *mpCurrentState = pModel->getState();
                    mpTrajectoryMethod->stateChanged();
                    StateChanged = false;
                  }

                return true;
              }

            if ((*mpLessOrEqual)(mOutputStartTime, *mpCurrentTime) &&
                (StateChanged || *mpCurrentTime == pModel->getProcessQueueExecutionTime()) &&
                mpTrajectoryProblem->getOutputEvent())
              {
                output(COutputInterface::DURING);
              }

            if (StateChanged)
              {
                *mpCurrentState = pModel->getState();
                mpTrajectoryMethod->stateChanged();
                StateChanged = false;
              }

            break;

          case CTrajectoryMethod::FAILURE:
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 12);

            return false;
            break;
        }

      proceed = mpCallBack == NULL || mpCallBack->proceed();
    }

  return proceed;
}

bool CTrajectoryTask::restore()
{
  bool success = CCopasiTask::restore();

  if (mUpdateModel)
    {
      CModel * pModel = mpProblem->getModel();

      pModel->setState(*mpCurrentState);
      pModel->updateSimulatedValues(mUpdateMoieties);
      pModel->setInitialState(pModel->getState());
      pModel->updateInitialValues();
    }

  return success;
}

bool CTrajectoryTask::setMethodType(const int & type)
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  if (!isValidMethod(Type, ValidMethods)) return false;

  if (mpMethod->getSubType() == Type) return true;

  pdelete(mpMethod);
  mpMethod = createMethod(Type);
  this->add(mpMethod, true);

  CCopasiParameter * pParameter = mpMethod->getParameter("Integrate Reduced Model");

  if (pParameter != NULL)
    mUpdateMoieties = *pParameter->getValue().pBOOL;
  else
    mUpdateMoieties = false;

  return true;
}

// virtual
CCopasiMethod * CTrajectoryTask::createMethod(const int & type) const
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  return CTrajectoryMethod::createMethod(Type);
}

CState * CTrajectoryTask::getState()
{return mpCurrentState;}

const CTimeSeries & CTrajectoryTask::getTimeSeries() const
{return mTimeSeries;}
