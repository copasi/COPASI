/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTrajectoryTask.cpp,v $
   $Revision: 1.47 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/14 15:50:20 $
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
#include "utilities/COutputHandler.h"

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
    mTimeSeriesRequested(true),
    mDoOutput(OUTPUT_COMPLETE)
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

bool CTrajectoryTask::initialize(std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  CTrajectoryProblem* pProblem =
    dynamic_cast<CTrajectoryProblem *>(mpProblem);
  assert(pProblem);

  bool success = true;

  if (!mReport.open(pOstream)) success = false;
  if (!mReport.compile()) success = false;
  if (!pProblem->getModel()->compileIfNecessary()) success = false;
  //  if (!pProblem->
  //      setInitialState(pProblem->getModel()->getInitialState()))
  //    success = false;

  //pProblem->setInitialState(pProblem->getModel()->getInitialState());

  return success;
}

bool CTrajectoryTask::process()
{
  assert(mpProblem && mpMethod);

  CTrajectoryProblem * pProblem = (CTrajectoryProblem *) mpProblem;
  CTrajectoryMethod * pMethod = (CTrajectoryMethod *) mpMethod;

  mTimeSeriesRequested = pProblem->timeSeriesRequested();

  pdelete(mpState);
  mpState = new CState(pProblem->getInitialState());

  pMethod->setCurrentState(mpState);
  pMethod->setProblem(pProblem);

  C_FLOAT64 StepSize = pProblem->getStepSize();

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

  C_FLOAT64 ActualStepSize;
  const C_FLOAT64 & Time = mpState->getTime();
  C_FLOAT64 EndTime = pProblem->getEndTime() - StepSize;
  C_FLOAT64 outputStartTime = pProblem->getOutputStartTime();

  if (StepSize == 0.0 && pProblem->getEndTime() != pProblem->getStartTime())
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 5, StepSize);
      return false;
    }
  bool flagStopped = false;
  C_FLOAT64 handlerFactor = 1000 / (pProblem->getEndTime() - pProblem->getStartTime());
  if (mpProgressHandler) mpProgressHandler->init(1000, "performing simulation...", true);

  if (mDoOutput)
    {
      pProblem->getModel()->setState(mpState);
      pProblem->getModel()->updateRates();
    }

  if (mDoOutput == OUTPUT_COMPLETE)
    {
      pProblem->getModel()->setState(mpState);
      pProblem->getModel()->updateRates();
      mReport.printHeader();
      if (mpOutputHandler) mpOutputHandler->init();
      if (mTimeSeriesRequested) mTimeSeries.init(pProblem->getStepNumber(), mpState);
    }

  if ((*LE)(outputStartTime, Time) && (mDoOutput))
    {
      mReport.printBody();
      if (mpOutputHandler) mpOutputHandler->doOutput();
      if (mTimeSeriesRequested) mTimeSeries.add();
    }

  ActualStepSize = pMethod->step(StepSize, mpState);

  if (mpProgressHandler) flagStopped =
      mpProgressHandler->progress((C_INT32)((Time - pProblem->getStartTime()) * handlerFactor));

  if ((*LE)(outputStartTime, Time) && (mDoOutput))
    {
      pProblem->getModel()->setState(mpState);
      pProblem->getModel()->updateRates();
      mReport.printBody();
      if (mpOutputHandler) mpOutputHandler->doOutput();
      if (mTimeSeriesRequested) mTimeSeries.add();
    }

#ifdef  XXXX_Event
  if (ActualStepSize != StepSize)
    {
      /* Here we will do conditional event processing */
    }
#endif // XXXX_Event

  while ((*L)(Time, EndTime) && (!flagStopped))
    {
      ActualStepSize = pMethod->step(StepSize);

      if (mpProgressHandler) flagStopped = mpProgressHandler->progress((C_INT32)((Time - pProblem->getStartTime()) * handlerFactor));

      if ((*LE)(outputStartTime, Time) && (mDoOutput))
        {
          pProblem->getModel()->setState(mpState);
          pProblem->getModel()->updateRates();
          mReport.printBody();
          if (mpOutputHandler) mpOutputHandler->doOutput();
          if (mTimeSeriesRequested) mTimeSeries.add();
        }
#ifdef  XXXX_Event
      if (ActualStepSize != StepSize)
        {
          /* Here we will do conditional event processing */
        }
#endif // XXXX_Event
    }

  while ((*L)(Time, pProblem->getEndTime()) && (!flagStopped))
    {
      ActualStepSize = pMethod->step(pProblem->getEndTime() - Time);

      if (mpProgressHandler) flagStopped = mpProgressHandler->progress((C_INT32)((Time - pProblem->getStartTime()) * handlerFactor));

      if ((*LE)(outputStartTime, Time) && (mDoOutput))
        {
          pProblem->getModel()->setState(mpState);
          pProblem->getModel()->updateRates();
          mReport.printBody();
          if (mpOutputHandler) mpOutputHandler->doOutput();
          if (mTimeSeriesRequested) mTimeSeries.add();
        }
#ifdef  XXXX_Event
      if (ActualStepSize != (pProblem->getEndTime() - Time))
        {
          /* Here we will do conditional event processing */
        }
#endif // XXXX_Event
    }

  //pProblem->setEndState(new CState(*mpState));

  if (mpProgressHandler) mpProgressHandler->finish();
  pProblem->getModel()->setState(mpState);
  pProblem->getModel()->updateRates();

  if ((*LE)(outputStartTime, Time) && (mDoOutput))
    {
      mReport.printFooter();
      if (mpOutputHandler) mpOutputHandler->finish();
      if (mTimeSeriesRequested) mTimeSeries.finish();
    }

  return true;
}

//virtual
bool CTrajectoryTask::processForScan(bool useInitialConditions, bool doOutput)
{
  assert(mpProblem /*&& mpMethod*/);

  CTrajectoryProblem* pProblem =
    dynamic_cast<CTrajectoryProblem *>(mpProblem);
  assert(pProblem);

  //set flag for output
  OutputFlag storeOutput = mDoOutput;
  if (doOutput)
    mDoOutput = OUTPUT;
  else
    mDoOutput = NO_OUTPUT;

  //handle initial conditions
  CState storeState;
  if (!useInitialConditions)
    {
      storeState = pProblem->getInitialState();
      pProblem->getModel()->setTime(pProblem->getInitialState().getTime());
      pProblem->setInitialState(pProblem->getModel()->getState());
      // pProblem->getInitialState().setTime(storeState.getTime());
    }

  //switch off time series storage
  bool storeTS = pProblem->timeSeriesRequested();
  pProblem->setTimeSeriesRequested(false);

  //do the calculation
  process();

  //restore ...
  if (!useInitialConditions) pProblem->setInitialState(storeState);
  mDoOutput = storeOutput;
  pProblem->setTimeSeriesRequested(storeTS);

  return true;
}

bool CTrajectoryTask::processSimple(bool singleStep) //without output
{
  assert(mpProblem && mpMethod);

  CTrajectoryProblem * pProblem = (CTrajectoryProblem *) mpProblem;
  CTrajectoryMethod * pMethod = (CTrajectoryMethod *) mpMethod;

  //give the method a state to work on
  pdelete(mpState);
  mpState = new CState(pProblem->getInitialState());
  pMethod->setCurrentState(mpState);

  pMethod->setProblem(pProblem);

  C_FLOAT64 StepSize = pProblem->getEndTime() - pProblem->getInitialState().getTime();
  bool (*L)(const C_FLOAT64 &, const C_FLOAT64 &) = (StepSize < 0.0) ? &bl : &fl;

  bool flagStopped = false;
  C_FLOAT64 handlerFactor = 1000 / (pProblem->getEndTime() - pProblem->getStartTime());
  if (mpProgressHandler) mpProgressHandler->init(1000, "performing simulation...", true);

  //first step
  pMethod->step(StepSize, &pProblem->getInitialState());

  if (mpProgressHandler) flagStopped =
      mpProgressHandler->progress((C_INT32)((mpState->getTime() - pProblem->getStartTime()) * handlerFactor));

  if (mpState->getTime() == pProblem->getEndTime()) return true; //end reached in one step
  if (singleStep) return false; //end not reached but only one step requested

  //more Steps if necessary
  while ((*L)(mpState->getTime(), pProblem->getEndTime()) && (!flagStopped))
    {
      StepSize = pProblem->getEndTime() - mpState->getTime();
      pMethod->step(StepSize);

      if (mpProgressHandler) flagStopped =
          mpProgressHandler->progress((C_INT32)((mpState->getTime() - pProblem->getStartTime()) * handlerFactor));
    }

  //pProblem->setEndState(new CState(*mpState));

  //if (mpProgressHandler) mpProgressHandler->finish();

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
