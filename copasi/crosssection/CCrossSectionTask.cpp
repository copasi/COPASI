// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 * CCrossSectionTask class.
 *
 * This class implements a cross section task.
 */

#include <string>
#include <cmath>

#include "copasi.h"

#include "CCrossSectionTask.h"
#include "CCrossSectionProblem.h"
//#include "CCrossSectionMethod.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"
#include "utilities/CProcessReport.h"
#include "utilities/CCopasiException.h"
#include  "CopasiDataModel/CCopasiDataModel.h"

bool cs_fle(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 <= d2);}

bool cs_fl(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 < d2);}

bool cs_ble(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 >= d2);}

bool cs_bl(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 > d2);}

const unsigned int CCrossSectionTask::ValidMethods[] =
{
  CCopasiMethod::deterministic,
  //  CCopasiMethod::stochastic,
  //CCopasiMethod::directMethod,
  //CCopasiMethod::tauLeap,
  //CCopasiMethod::adaptiveSA,
  //CCopasiMethod::hybrid,
  //CCopasiMethod::hybridLSODA,
#ifdef COPASI_DEBUG
  CCopasiMethod::DsaLsodar,
#endif // COPASI_DEBUG
  CCopasiMethod::unset
};

CCrossSectionTask::CCrossSectionTask(const CCopasiContainer * pParent):
  CCopasiTask(CCopasiTask::crosssection, pParent),
  mTimeSeriesRequested(true),
  mTimeSeries(),
  mpCrossSectionProblem(NULL),
  mpTrajectoryMethod(NULL),
  mUpdateMoieties(false),
  mpCurrentState(NULL),
  mpCurrentTime(NULL),
  mOutputStartTime(0.0),
  mpLessOrEqual(&cs_fle),
  mpLess(&cs_fl)
{
  mpProblem = new CCrossSectionProblem(this);
  mpMethod = createMethod(CCopasiMethod::deterministic);
  this->add(mpMethod, true);

/*  CCopasiParameter * pParameter = mpMethod->getParameter("Integrate Reduced Model");

  if (pParameter != NULL)
    mUpdateMoieties = *pParameter->getValue().pBOOL;
  else
    mUpdateMoieties = false;*/
}

CCrossSectionTask::CCrossSectionTask(const CCrossSectionTask & src,
                                     const CCopasiContainer * pParent):
  CCopasiTask(src, pParent),
  mTimeSeriesRequested(src.mTimeSeriesRequested),
  mTimeSeries(),
  mpCrossSectionProblem(NULL),
  mpTrajectoryMethod(NULL),
  mUpdateMoieties(false),
  mpCurrentState(NULL),
  mpCurrentTime(NULL),
  mOutputStartTime(0.0),
  mpLessOrEqual(src.mpLessOrEqual),
  mpLess(src.mpLess)
{
  mpProblem =
    new CCrossSectionProblem(*static_cast< CCrossSectionProblem * >(src.mpProblem), this);

  mpMethod = createMethod(src.mpMethod->getSubType());
  * mpMethod = * src.mpMethod;

  mpMethod->elevateChildren();

  this->add(mpMethod, true);

/*  CCopasiParameter * pParameter = mpMethod->getParameter("Integrate Reduced Model");

  if (pParameter != NULL)
    mUpdateMoieties = *pParameter->getValue().pBOOL;
  else
    mUpdateMoieties = false;*/
}

CCrossSectionTask::~CCrossSectionTask()
{
  cleanup();
}

void CCrossSectionTask::cleanup()
{
  pdelete(mpCurrentState);
}

bool CCrossSectionTask::initialize(const OutputFlag & of,
                                   COutputHandler * pOutputHandler,
                                   std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  mpCrossSectionProblem = dynamic_cast<CCrossSectionProblem *>(mpProblem);
  assert(mpCrossSectionProblem);

  mpTrajectoryMethod = dynamic_cast<CTrajectoryMethod *>(mpMethod);
  assert(mpTrajectoryMethod);

  mpTrajectoryMethod->setProblem(mpCrossSectionProblem);

  bool success = mpMethod->isValidProblem(mpProblem);

  CCopasiParameter * pParameter = mpMethod->getParameter("Integrate Reduced Model");

  if (pParameter != NULL)
    mUpdateMoieties = *pParameter->getValue().pBOOL;
  else
    mUpdateMoieties = false;

  pdelete(mpCurrentState);
  mpCurrentState = new CState(mpCrossSectionProblem->getModel()->getState());
  mpCurrentTime = &mpCurrentState->getTime();

  //mpOutputStartTime = & mpTrajectoryProblem->getOutputStartTime();

  // Handle the time series as a regular output.
  mTimeSeriesRequested = mpCrossSectionProblem->timeSeriesRequested();

  if ((pOutputHandler != NULL) &&
      mTimeSeriesRequested &&
      (of & CCopasiTask::TIME_SERIES))
    {
      mTimeSeries.allocate(20);
      pOutputHandler->addInterface(&mTimeSeries);
    }
  else
    {
      mTimeSeries.clear();
    }

  if (!CCopasiTask::initialize(of, pOutputHandler, pOstream)) success = false;

  return success;
}

bool CCrossSectionTask::process(const bool & useInitialValues)
{
  //*****

  processStart(useInitialValues);

  //*****

  C_FLOAT64 MaxDuration = mpCrossSectionProblem->getDuration();
  //C_FLOAT64 StepSize = mpCrossSectionProblem->getStepSize();
  //C_FLOAT64 StepNumber = fabs(Duration) / StepSize;

  //if (isnan(StepNumber) || StepNumber < 1.0)
  //  StepNumber = 1.0;

  //the output starts only after "outputStartTime" has passed
<<<<<<< HEAD
  if (useInitialValues)
    mOutputStartTime = mpCrossSectionProblem->getOutputStartTime();
  else
    mOutputStartTime = *mpCurrentTime + mpCrossSectionProblem->getOutputStartTime();

  C_FLOAT64 NextTimeToReport;
=======
  mOutputStartTime = *mpCurrentTime + mpCrossSectionProblem->getOutputStartTime();
  
  //C_FLOAT64 NextTimeToReport;
>>>>>>> Some more steps towards cross section implementation

  const C_FLOAT64 EndTime = *mpCurrentTime + MaxDuration;
  const C_FLOAT64 StartTime = *mpCurrentTime;
  C_FLOAT64 CompareEndTime;

  if (MaxDuration < 0.0)
    {
      mpLessOrEqual = &cs_ble;
      mpLess = &cs_bl;

      // It suffices to reach the end time within machine precision
      CompareEndTime = EndTime + 100.0 * (fabs(EndTime) * std::numeric_limits< C_FLOAT64 >::epsilon() + std::numeric_limits< C_FLOAT64 >::min());
    }
  else
    {
      mpLessOrEqual = &cs_fle;
      mpLess = &cs_fl;

      // It suffices to reach the end time within machine precision
      CompareEndTime = EndTime - 100.0 * (fabs(EndTime) * std::numeric_limits< C_FLOAT64 >::epsilon() + std::numeric_limits< C_FLOAT64 >::min());
    }

  //unsigned C_INT32 StepCounter = 1;

  //if (StepSize == 0.0 && Duration != 0.0)
  //  {
  //    CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryProblem + 1, StepSize);
  //    return false;
  //  }

  output(COutputInterface::BEFORE);

  bool flagProceed = true;
  C_FLOAT64 handlerFactor = 100.0 / MaxDuration;

  C_FLOAT64 Percentage = 0;
  size_t hProcess;

  if (mpCallBack != NULL)
    {
      mpCallBack->setName("performing simulation...");
      C_FLOAT64 hundred = 100;
      hProcess = mpCallBack->addItem("Completion",
                                     Percentage,
                                     &hundred);
    }

  try
    {
      do
        {
          // This is numerically more stable then adding
          // mpTrajectoryProblem->getStepSize().
          //NextTimeToReport =
          //  StartTime + (EndTime - StartTime) * StepCounter++ / StepNumber;

          flagProceed &= processStep(EndTime);

          if (mpCallBack != NULL )
            {
              Percentage = (*mpCurrentTime - StartTime) * handlerFactor;
              flagProceed &= mpCallBack->progressItem(hProcess);
            }

          //if ((*mpLessOrEqual)(mOutputStartTime, *mpCurrentTime))
          //  {
          //    output(COutputInterface::DURING);
          //  }
        }
      while ((*mpLess)(*mpCurrentTime, CompareEndTime) && flagProceed);
    }

  catch (int)
    {
      mpCrossSectionProblem->getModel()->setState(*mpCurrentState);
      mpCrossSectionProblem->getModel()->updateSimulatedValues(mUpdateMoieties);

<<<<<<< HEAD
      if (mpCallBack != NULL && StepNumber > 1.0) mpCallBack->finishItem(hProcess);
=======

      if (mpCallBack != NULL) mpCallBack->finishItem(hProcess);
>>>>>>> Some more steps towards cross section implementation

      output(COutputInterface::AFTER);

      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 16);
    }

  catch (CCopasiException & Exception)
    {
      mpCrossSectionProblem->getModel()->setState(*mpCurrentState);
      mpCrossSectionProblem->getModel()->updateSimulatedValues(mUpdateMoieties);

<<<<<<< HEAD
      if (mpCallBack != NULL && StepNumber > 1.0) mpCallBack->finishItem(hProcess);
=======

      if (mpCallBack != NULL) mpCallBack->finishItem(hProcess);
>>>>>>> Some more steps towards cross section implementation

      output(COutputInterface::AFTER);

      throw CCopasiException(Exception.getMessage());
    }

  if (mpCallBack != NULL) mpCallBack->finishItem(hProcess);

  output(COutputInterface::AFTER);

  return true;
}

void CCrossSectionTask::processStart(const bool & useInitialValues)
{
  if (useInitialValues)
    mpCrossSectionProblem->getModel()->applyInitialValues();

  *mpCurrentState = mpCrossSectionProblem->getModel()->getState();

  mpTrajectoryMethod->setCurrentState(mpCurrentState);
  mpTrajectoryMethod->start(mpCurrentState);

  return;
}

bool CCrossSectionTask::processStep(const C_FLOAT64 & endTime)
{
  CModel * pModel = mpCrossSectionProblem->getModel();
  bool StateChanged = false;
  bool proceed = true;

  C_FLOAT64 Tolerance = 100.0 * (fabs(endTime) * std::numeric_limits< C_FLOAT64 >::epsilon() + std::numeric_limits< C_FLOAT64 >::min());
  C_FLOAT64 NextTime = endTime;

  while (proceed)
    {
      // TODO Provide a call back method for resolving simultaneous assignments.
      StateChanged |= pModel->processQueue(*mpCurrentTime, false, NULL);

      if (StateChanged)
        {
          if ((*mpLessOrEqual)(mOutputStartTime, *mpCurrentTime) )
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
                *mpCurrentTime == pModel->getProcessQueueExecutionTime() )
              {
                output(COutputInterface::DURING);
              }

            // TODO Provide a call back method for resolving simultaneous assignments.
            StateChanged |= pModel->processQueue(*mpCurrentTime, true, NULL);

            if (fabs(*mpCurrentTime - endTime) < Tolerance)
              return true;

            if ((*mpLessOrEqual)(mOutputStartTime, *mpCurrentTime) &&
                StateChanged )
              {
                output(COutputInterface::DURING);
              }

            break;

          case CTrajectoryMethod::ROOT:
            pModel->setState(*mpCurrentState);
            pModel->updateSimulatedValues(mUpdateMoieties);

            pModel->processRoots(*mpCurrentTime, true, true, mpTrajectoryMethod->getRoots());

            if ((*mpLessOrEqual)(mOutputStartTime, *mpCurrentTime) &&
                *mpCurrentTime == pModel->getProcessQueueExecutionTime() )
              {
                output(COutputInterface::DURING);
              }

            // TODO Provide a call back method for resolving simultaneous assignments.
            StateChanged |= pModel->processQueue(*mpCurrentTime, true, NULL);

            pModel->processRoots(*mpCurrentTime, false, true, mpTrajectoryMethod->getRoots());

            // If the root happens to coincide with end of the step we have to return and
            // inform the integrator of eventual state changes.
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

            if ((*mpLessOrEqual)(mOutputStartTime, *mpCurrentTime)  &&
                (StateChanged ||
                 *mpCurrentTime == pModel->getProcessQueueExecutionTime()))
              {
                output(COutputInterface::DURING);
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

bool CCrossSectionTask::restore()
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

bool CCrossSectionTask::setMethodType(const int & type)
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
CCopasiMethod * CCrossSectionTask::createMethod(const int & type) const
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  return CTrajectoryMethod::createMethod(Type);
}

CState * CCrossSectionTask::getState()
{return mpCurrentState;}

const CTimeSeries & CCrossSectionTask::getTimeSeries() const
{return mTimeSeries;}
