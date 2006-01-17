/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTrajectoryTask.cpp,v $
   $Revision: 1.66.2.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/01/17 15:16:06 $
   End CVS Header */

/**
 * CTrajectoryTask class.
 *
 * This class implements a trajectory task which is comprised of a
 * of a problem and a method. Additionally calls to the reporting 
 * methods are done when initialized.
 *  
 * Created for Copasi by Stefan Hoops 2002
 */

#include <string>

#include "copasi.h"

#include "CTrajectoryTask.h"
#include "CTrajectoryProblem.h"
#include "CTrajectoryMethod.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h" 
//#include "utilities/COutputHandler.h"
#include "utilities/CProcessReport.h"
#include "utilities/CCopasiException.h"

#define XXXX_Reporting

bool fle(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 <= d2);}

bool fl(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 < d2);}

bool ble(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 >= d2);}

bool bl(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 > d2);}

CTrajectoryTask::CTrajectoryTask(const CCopasiContainer * pParent):
    CCopasiTask(CCopasiTask::timeCourse, pParent),
    mpState(NULL),
    mTimeSeriesRequested(true)
{
  mpProblem = new CTrajectoryProblem(this);
  mpMethod =
    CTrajectoryMethod::createTrajectoryMethod(CCopasiMethod::deterministic,
        (CTrajectoryProblem *) mpProblem);
  this->add(mpMethod, true);
  //mpMethod->setObjectParent(this);
}

/*CTrajectoryTask::CTrajectoryTask(const CTrajectoryTask & src,
                                 const CCopasiContainer * pParent):
    CCopasiTask(src, pParent),
    mpState(src.mpState),
    mTimeSeriesRequested(src.mTimeSeriesRequested)
{fatalError();}*/

CTrajectoryTask::~CTrajectoryTask()
{
  cleanup();
}

void CTrajectoryTask::cleanup()
{
  pdelete(mpState);
}

void CTrajectoryTask::load(CReadConfig & configBuffer)
{
  configBuffer.getVariable("Dynamics", "bool", &mScheduled,
                           CReadConfig::LOOP);

  pdelete(mpProblem);
  mpProblem = new CTrajectoryProblem(this);
  ((CTrajectoryProblem *) mpProblem)->load(configBuffer);

  pdelete(mpMethod);
  mpMethod = CTrajectoryMethod::createTrajectoryMethod();
  this->add(mpMethod, true);
  //mpMethod->setObjectParent(this);
  ((CTrajectoryMethod *)mpMethod)->setProblem((CTrajectoryProblem *) mpProblem);
}

bool CTrajectoryTask::initialize(const OutputFlag & of,
                                 std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  CTrajectoryProblem* pProblem =
    dynamic_cast<CTrajectoryProblem *>(mpProblem);
  assert(pProblem);

  dynamic_cast<CTrajectoryMethod *>(mpMethod)->setProblem(pProblem);
  bool success = mpMethod->isValidProblem(mpProblem);

  pdelete(mpState);
  mpState = new CState(pProblem->getModel()->getState());

  if (!CCopasiTask::initialize(of, pOstream)) success = false;
  mTimeSeriesRequested = pProblem->timeSeriesRequested();

  initOutput();

  mpCurrentReport = &mReport;

  return success;
}

bool CTrajectoryTask::process(const bool & useInitialValues)
{
  assert(/*mpProblem && */mpMethod);

  //*****

  if (useInitialValues)
    mpProblem->getModel()->applyInitialValues();

  //*****

  CTrajectoryProblem * pProblem = (CTrajectoryProblem *) mpProblem;
  CTrajectoryMethod * pMethod = (CTrajectoryMethod *) mpMethod;

  //the following is a hack that has to disappear soon.
  //pProblem->setInitialState(pProblem->getModel()->getInitialState());

  unsigned C_INT32 FailCounter = 0;

  // set the start time
  // pProblem->getModel()->setTime(pProblem->getStartTime());

  *mpState = pProblem->getModel()->getState();

  pMethod->setCurrentState(mpState);

  C_FLOAT64 StepSize = pProblem->getStepSize();
  C_FLOAT64 NextTimeToReport;

  const C_FLOAT64 & Time = mpState->getTime();
  const C_FLOAT64 EndTime = Time + pProblem->getDuration();
  const C_FLOAT64 StartTime = Time;

  C_FLOAT64 ActualStepSize;
  C_FLOAT64 StepNumber = (pProblem->getDuration()) / StepSize;

  bool (*LE)(const C_FLOAT64 &, const C_FLOAT64 &);
  bool (*L)(const C_FLOAT64 &, const C_FLOAT64 &);
  if (StepSize < 0.0)
    {
      LE = &ble;
      L = &bl;
    }
  else
    {
      LE = &fle;
      L = &fl;
    }

  unsigned C_INT32 StepCounter = 1;

  C_FLOAT64 outputStartTime = pProblem->getOutputStartTime();

  if (StepSize == 0.0 && pProblem->getDuration() != 0.0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryProblem + 1, StepSize);
      return false;
    }
  bool flagProceed = true;
  C_FLOAT64 handlerFactor = 100.0 / pProblem->getDuration();

  C_FLOAT64 Percentage = 0;
  unsigned C_INT32 hProcess;

  if (mpCallBack)
    {
      mpCallBack->setName("performing simulation...");
      C_FLOAT64 hundred = 100;
      hProcess = mpCallBack->addItem("Completion",
                                     CCopasiParameter::DOUBLE,
                                     &Percentage,
                                     &hundred);
    }

  if ((*LE)(outputStartTime, Time)) doOutput();

  // We start the integration
  // This is numerically more stable then adding pProblem->getStepSize().
  NextTimeToReport = StartTime + (EndTime - StartTime) * StepCounter++ / StepNumber;
  try
    {
      pMethod->start(mpState);
      ActualStepSize = pMethod->step(StepSize);
    }
  catch (CCopasiException Exception)
    {
      if (mpCallBack) mpCallBack->finish(hProcess);
      throw CCopasiException(Exception.getMessage());
    }

  if (mpCallBack)
    {
      Percentage = (Time - StartTime) * handlerFactor;
      flagProceed = mpCallBack->progress(hProcess);
    }

  if ((*LE)(outputStartTime, Time) &&
      !(*L)(Time, NextTimeToReport * (1 - 100 * DBL_EPSILON)))
    {
      doOutput();
    }

  if ((*L)(Time, NextTimeToReport * (1 - 100 * DBL_EPSILON)))
    {
      /* Here we will do conditional event processing */
      FailCounter++;
      StepSize = NextTimeToReport - Time;
      if (mpCallBack)
        flagProceed = mpCallBack->proceed();
    }
  else
    {
      FailCounter = 0;
      // This is numerically more stable then adding pProblem->getStepSize().
      NextTimeToReport = StartTime + (EndTime - StartTime) * StepCounter++ / StepNumber;
      // Make sure that we do not overstep
      if ((*L)(EndTime, NextTimeToReport)) NextTimeToReport = EndTime;
      StepSize = NextTimeToReport - Time;
    }

  while ((*L)(Time, EndTime * (1 - 100 * DBL_EPSILON)) && flagProceed)
    {
      try
        {
          ActualStepSize = pMethod->step(StepSize);
        }
      catch (CCopasiException Exception)
        {
          if (mpCallBack) mpCallBack->finish(hProcess);
          throw CCopasiException(Exception.getMessage());
        }

      //std::cout << EndTime << "  " << Time << "  " << EndTime-Time << std::endl;

      if (mpCallBack)
        {
          Percentage = (Time - StartTime) * handlerFactor;
          flagProceed = mpCallBack->progress(hProcess);
        }

      if ((*LE)(outputStartTime, Time) &&
          !(*L)(Time, NextTimeToReport * (1 - 100 * DBL_EPSILON)))
        {
          doOutput();
        }

      if ((*L)(Time, NextTimeToReport * (1 - 100 * DBL_EPSILON)))
        {
          /* Here we will do conditional event processing */

          FailCounter++;
          if (FailCounter > 0) // Currently this is correct since no events are processed.
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 12);

          StepSize = NextTimeToReport - Time;
          if (mpCallBack)
            flagProceed = mpCallBack->proceed();
        }
      else
        {
          FailCounter = 0;
          // This is numerically more stable then adding pProblem->getStepSize().
          NextTimeToReport = StartTime + (EndTime - StartTime) * StepCounter++ / StepNumber;
          // Make sure that we do not overstep
          if ((*L)(EndTime, NextTimeToReport)) NextTimeToReport = EndTime;
          StepSize = NextTimeToReport - Time;
        }
    }

  //pProblem->setEndState(new CState(*mpState));

  if (mpCallBack) mpCallBack->finish(hProcess);

  pProblem->getModel()->setState(mpState);
  pProblem->getModel()->updateRates();

  finishOutput();

  return true;
}

bool CTrajectoryTask::setMethodType(const int & type)
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  if (!CTrajectoryMethod::isValidSubType(Type)) return false;
  if (mpMethod->getSubType() == Type) return true;

  pdelete (mpMethod);
  mpMethod =
    CTrajectoryMethod::createTrajectoryMethod(Type,
        (CTrajectoryProblem *) mpProblem);
  this->add(mpMethod, true);
  //mpMethod->setObjectParent(this);

  return true;
}

CState * CTrajectoryTask::getState()
{return mpState;}

const CTimeSeries & CTrajectoryTask::getTimeSeries() const
  {return mTimeSeries;}

bool CTrajectoryTask::initOutput()
{
  //output preparation
  if (mDoOutput == OUTPUT_COMPLETE)
    {
      mpProblem->getModel()->setState(mpState);
      mpProblem->getModel()->updateRates();
    }

  CCopasiTask::initOutput();

  //time series
  if (mDoOutput == OUTPUT_COMPLETE)
    {
      CTrajectoryProblem * pProblem = (CTrajectoryProblem *) mpProblem;
      if (mTimeSeriesRequested) mTimeSeries.init(pProblem->getStepNumber(), mpState);
    }
  return true;
}

bool CTrajectoryTask::doOutput()
{
  //output preparation
  if (mDoOutput)
    {
      mpProblem->getModel()->setState(mpState);
      mpProblem->getModel()->updateRates();
    }

  CCopasiTask::doOutput();

  //time series
  if (mDoOutput == OUTPUT_COMPLETE)
    {
      if (mTimeSeriesRequested) mTimeSeries.add();
    }
  return true;
}

bool CTrajectoryTask::finishOutput()
{
  //output preparation
  if (mDoOutput == OUTPUT_COMPLETE)
    {
      mpProblem->getModel()->setState(mpState);
      mpProblem->getModel()->updateRates();
    }

  CCopasiTask::finishOutput();

  //time series
  if (mDoOutput == OUTPUT_COMPLETE)
    {
      if (mTimeSeriesRequested) mTimeSeries.finish();
    }
  return true;
}
