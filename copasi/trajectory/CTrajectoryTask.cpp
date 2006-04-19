/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTrajectoryTask.cpp,v $
   $Revision: 1.71 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/19 18:37:00 $
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

CTrajectoryTask::CTrajectoryTask(const CCopasiContainer * pParent):
    CCopasiTask(CCopasiTask::timeCourse, pParent),
    mTimeSeriesRequested(true),
    mTimeSeries(),
    mpTrajectoryProblem(NULL),
    mpTrajectoryMethod(NULL),
    mpCurrentState(NULL),
    mpCurrentTime(NULL)
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
    mpCurrentState(src.mpCurrentState),
    mTimeSeriesRequested(src.mTimeSeriesRequested)
{fatalError();}*/

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
  mpMethod = CTrajectoryMethod::createTrajectoryMethod();
  this->add(mpMethod, true);
  //mpMethod->setObjectParent(this);
  ((CTrajectoryMethod *)mpMethod)->setProblem((CTrajectoryProblem *) mpProblem);
}

bool CTrajectoryTask::initialize(const OutputFlag & of,
                                 std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  mpTrajectoryProblem = dynamic_cast<CTrajectoryProblem *>(mpProblem);
  assert(mpTrajectoryProblem);

  mpTrajectoryMethod = dynamic_cast<CTrajectoryMethod *>(mpMethod);
  assert(mpTrajectoryMethod);

  mpTrajectoryMethod->setProblem(mpTrajectoryProblem);

  bool success = mpMethod->isValidProblem(mpProblem);

  pdelete(mpCurrentState);
  mpCurrentState = new CState(mpTrajectoryProblem->getModel()->getState());
  mpCurrentTime = &mpCurrentState->getTime();

  if (!CCopasiTask::initialize(of, pOstream)) success = false;
  mTimeSeriesRequested = mpTrajectoryProblem->timeSeriesRequested();

  return success;
}

bool CTrajectoryTask::process(const bool & useInitialValues)
{
  //*****

  processStart(useInitialValues);

  //*****

  unsigned C_INT32 FailCounter = 0;

  C_FLOAT64 StepSize = mpTrajectoryProblem->getStepSize();
  C_FLOAT64 NextTimeToReport;

  const C_FLOAT64 EndTime = *mpCurrentTime + mpTrajectoryProblem->getDuration();
  const C_FLOAT64 StartTime = *mpCurrentTime;

  C_FLOAT64 StepNumber = (mpTrajectoryProblem->getDuration()) / StepSize;

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

  C_FLOAT64 outputStartTime = mpTrajectoryProblem->getOutputStartTime();

  if (StepSize == 0.0 && mpTrajectoryProblem->getDuration() != 0.0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryProblem + 1, StepSize);
      return false;
    }

  output(COutputInterface::BEFORE);

  bool flagProceed = true;
  C_FLOAT64 handlerFactor = 100.0 / mpTrajectoryProblem->getDuration();

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

  if ((*LE)(outputStartTime, *mpCurrentTime)) output(COutputInterface::DURING);

  try
    {
      do
        {
          // This is numerically more stable then adding
          // mpTrajectoryProblem->getStepSize().
          NextTimeToReport =
            StartTime + (EndTime - StartTime) * StepCounter++ / StepNumber;

          flagProceed &= processStep(NextTimeToReport);

          if (mpCallBack)
            {
              Percentage = (*mpCurrentTime - StartTime) * handlerFactor;
              flagProceed &= mpCallBack->progress(hProcess);
            }

          if ((*LE)(outputStartTime, *mpCurrentTime))
            {
              output(COutputInterface::DURING);
            }
        }
      while ((*L)(*mpCurrentTime, EndTime) && flagProceed);
    }

  catch (CCopasiException Exception)
    {
      mpTrajectoryProblem->getModel()->setState(*mpCurrentState);
      mpTrajectoryProblem->getModel()->refreshConcentrations();

      if ((*LE)(outputStartTime, *mpCurrentTime))
        {
          output(COutputInterface::DURING);
        }

      if (mpCallBack) mpCallBack->finish(hProcess);
      output(COutputInterface::AFTER);

      throw CCopasiException(Exception.getMessage());
    }

  if (mpCallBack) mpCallBack->finish(hProcess);

  output(COutputInterface::AFTER);

  return true;
}

void CTrajectoryTask::processStart(const bool & useInitialValues)
{
  if (useInitialValues)
    mpTrajectoryProblem->getModel()->applyInitialValues();

  *mpCurrentState = mpTrajectoryProblem->getModel()->getState();

  mpTrajectoryMethod->setCurrentState(mpCurrentState);
  mpTrajectoryMethod->start(mpCurrentState);

  return;
}

bool CTrajectoryTask::processStep(const C_FLOAT64 & nextTime)
{
  C_FLOAT64 CompareTime = nextTime - 100 * fabs(nextTime) * DBL_EPSILON;

  if (*mpCurrentTime <= CompareTime)
    {
      do
        {
          mpTrajectoryMethod->step(nextTime - *mpCurrentTime);

          if (*mpCurrentTime > CompareTime) break;

          /* Here we will do conditional event processing */

          /* Currently this is correct since no events are processed. */
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 12);
        }
      while (true);

      mpTrajectoryProblem->getModel()->setState(*mpCurrentState);
      mpTrajectoryProblem->getModel()->refreshConcentrations();

      return true;
    }

  CompareTime = nextTime + 100 * fabs(nextTime) * DBL_EPSILON;
  if (*mpCurrentTime >= CompareTime)
    {
      do
        {
          mpTrajectoryMethod->step(nextTime - *mpCurrentTime);

          if (*mpCurrentTime < CompareTime) break;

          /* Here we will do conditional event processing */

          /* Currently this is correct since no events are processed. */
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 12);
        }
      while (true);

      mpTrajectoryProblem->getModel()->setState(*mpCurrentState);
      mpTrajectoryProblem->getModel()->refreshConcentrations();

      return true;
    }

  // Current time is approximately nextTime;
  return false;
}

bool CTrajectoryTask::restore()
{
  bool success = CCopasiTask::restore();

  if (mUpdateModel)
    {
      CModel * pModel = mpProblem->getModel();

      pModel->setState(*mpCurrentState);
      pModel->applyAssignments();
      pModel->setInitialState(pModel->getState());
    }

  return success;
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
{return mpCurrentState;}

const CTimeSeries & CTrajectoryTask::getTimeSeries() const
  {return mTimeSeries;}

void CTrajectoryTask::output(const COutputInterface::Activity & activity)
{
  CCopasiDataModel::Global->output(activity);

  if (mTimeSeriesRequested && mDoOutput == OUTPUT_COMPLETE)
    switch (activity)
      {
      case COutputInterface::BEFORE:
        mTimeSeries.init(mpTrajectoryProblem->getStepNumber(), mpProblem->getModel());
        break;

      case COutputInterface::DURING:
        mTimeSeries.add();
        break;

      case COutputInterface::AFTER:
        mTimeSeries.finish();
        break;
      }
}
