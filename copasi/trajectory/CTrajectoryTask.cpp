/**
 * CTrajectoryTask class.
 *
 * This class implements a trajectory task which is comprised of a
 * of a problem and a method. Additionally calls to the reporting 
 * methods are done when initialized.
 *  
 * Created for Copasi by Stefan Hoops 2002
 */

#include "copasi.h"
#include "CTrajectoryTask.h"
#include "CTrajectoryProblem.h"
#include "CTrajectoryMethod.h"
#include "output/output.h"
#include "model/CState.h"
#include "utilities/CGlobals.h"

#define XXXX_Reporting

CTrajectoryTask::CTrajectoryTask():
    mpProblem(NULL),
    mpMethod(NULL),
    mpState(NULL),
    mpOutInit(NULL),
    mpOutPoint(NULL),
    mpOutEnd(NULL)
{}

CTrajectoryTask::CTrajectoryTask(const CTrajectoryTask & src):
    mpProblem(src.mpProblem),
    mpMethod(src.mpMethod),
    mpState(src.mpState),
    mpOutInit(src.mpOutInit),
    mpOutPoint(src.mpOutPoint),
    mpOutEnd(src.mpOutEnd)
{}

CTrajectoryTask::CTrajectoryTask(CTrajectoryProblem * pProblem,
                                 CTrajectoryMethod::Type type):
    mpProblem(pProblem),
    mpMethod(NULL),
    mpState(NULL),
    mpOutInit(NULL),
    mpOutPoint(NULL),
    mpOutEnd(NULL)
{
  if (mpProblem)
    {
      mpMethod = CTrajectoryMethod::createTrajectoryMethod(type, pProblem);
    }
}

CTrajectoryTask::CTrajectoryTask(CModel * pModel,
                                 C_FLOAT64 starttime, C_FLOAT64 endtime,
                                 unsigned C_INT32 stepnumber,
                                 CTrajectoryMethod::Type type):
    mpProblem(NULL),
    mpMethod(NULL),
    mpState(NULL),
    mpOutInit(NULL),
    mpOutPoint(NULL),
    mpOutEnd(NULL)
{
  mpProblem = new CTrajectoryProblem(pModel, starttime, endtime, stepnumber);
  if (mpProblem)
    {
      mpMethod = CTrajectoryMethod::createTrajectoryMethod(type, mpProblem);
    }
}

CTrajectoryTask::~CTrajectoryTask()
{
  cleanup();
}

void CTrajectoryTask::cleanup()
{
  pdelete(mpProblem);
  pdelete(mpMethod);
  pdelete(mpState);
  pdelete(mpOutInit);
  pdelete(mpOutPoint);
  pdelete(mpOutEnd);
}

void CTrajectoryTask::initializeReporting(std::ofstream & out)
{
  pdelete(mpOutInit);
  pdelete(mpOutPoint);
  pdelete(mpOutEnd);

  mpOut = & out;
  mpOutInit = new COutputEvent(0);
  mpOutPoint = new COutputEvent(1);
  mpOutEnd = new COutputEvent(2);
}

void CTrajectoryTask::load(CReadConfig & configBuffer)
{
  if (configBuffer.getVersion() < "4.0")
    configBuffer.getVariable("Dynamics", "BOOL", &mRequested,
                             CReadConfig::LOOP);
  else
    configBuffer.getVariable("RunTrajectory", "BOOL", &mRequested,
                             CReadConfig::LOOP);

  pdelete(mpProblem);
  mpProblem = new CTrajectoryProblem();
  mpProblem->load(configBuffer);

  if (configBuffer.getVersion() < "4.0")
    {
      mpMethod = CTrajectoryMethod::createTrajectoryMethod();
    }
  else
    {
      C_INT32 Method;
      configBuffer.getVariable("TrajectoryMethod", "C_INT32", &Method,
                               CReadConfig::SEARCH);

      mpMethod = CTrajectoryMethod::
                 createTrajectoryMethod((CTrajectoryMethod::Type) Method);
      // load the right parameters if several are in the file
      mpMethod->loadSpecific(configBuffer,
                             mpMethod->getName(),
                             mpMethod->getType());
    }
}

void CTrajectoryTask::save(CWriteConfig & configBuffer)
{
  configBuffer.setVariable("RunTrajectory", "BOOL", &mRequested);

  mpProblem->save(configBuffer);

  const C_INT32 Method = mpMethod->getTypeEnum();
  configBuffer.setVariable("TrajectoryMethod", "C_INT32", &Method);

  mpMethod->save(configBuffer);
}

CTrajectoryProblem * CTrajectoryTask::getProblem()
{return mpProblem;}

void CTrajectoryTask::setProblem(CTrajectoryProblem * pProblem)
{mpProblem = pProblem;}

CTrajectoryMethod * CTrajectoryTask::getMethod()
{return mpMethod;}

void CTrajectoryTask::setMethod(CTrajectoryMethod * pMethod)
{mpMethod = pMethod;}

CState * CTrajectoryTask::getState()
{return mpState;}

void CTrajectoryTask::setRequested(const bool & requested)
{mRequested = requested;}

bool CTrajectoryTask::isRequested() const {return mRequested;}

void CTrajectoryTask::process()
{
  if (!mpProblem)
    fatalError();
  if (!mpMethod)
    fatalError();

  pdelete(mpState);
  mpState = new CState(*mpProblem->getInitialState());

  if (mpOutInit || mpOutPoint || mpOutEnd)
    Copasi->OutputList.compile("Time-course output",
                               mpProblem->getModel(),
                               mpState);

  mpMethod->setCurrentState(mpState);
  mpMethod->setProblem(mpProblem);

  CVector< C_FLOAT64 > Derivatives(mpState->getVariableNumberSize());
  if (mpOutInit)
    {
      /* Correct output depends on the model being updated */
      /* We should try to avoid this in the future         */
      mpProblem->getModel()->getDerivatives(mpState, Derivatives);
      mpOutInit->print(Copasi->OutputList, *mpOut);
    }

  if (mpOutPoint)
    {
      /* Correct output depends on the model being updated */
      /* We should try to avoid this in the future         */
      mpProblem->getModel()->getDerivatives(mpState, Derivatives);
      mpOutPoint->print(Copasi->OutputList, *mpOut);
    }

  C_FLOAT64 StepSize = mpProblem->getStepSize();
  C_FLOAT64 ActualStepSize;
  const C_FLOAT64 & Time = mpState->getTime();
  C_FLOAT64 EndTime = mpProblem->getEndTime() - StepSize;

  ActualStepSize = mpMethod->step(StepSize, mpState);
  if (mpOutPoint)
    {
      /* Correct output depends on the model being updated */
      /* We should try to avoid this in the future         */
      mpProblem->getModel()->getDerivatives(mpState, Derivatives);
      mpOutPoint->print(Copasi->OutputList, *mpOut);
    }

#ifdef  XXXX_Event
  if (ActualStepSize != StepSize)
    {
      /* Here we will do conditional event processing */
    }
#endif // XXXX_Event

  while (Time < EndTime)
    {
      ActualStepSize = mpMethod->step(StepSize);

      if (mpOutPoint)
        {
          /* Correct output depends on the model being updated */
          /* We should try to avoid this in the future         */
          mpProblem->getModel()->getDerivatives(mpState, Derivatives);
          mpOutPoint->print(Copasi->OutputList, *mpOut);
        }

#ifdef  XXXX_Event
      if (ActualStepSize != StepSize)
        {
          /* Here we will do conditional event processing */
        }
#endif // XXXX_Event
    }

#ifdef  XXXX_Event
  while (Time < mpProblem->getEndTime())
    {
      ActualStepSize = mpMethod->step(mpProblem->getEndTime() - Time);

      if (mpOutPoint)
        {
          /* Correct output depends on the model being updated */
          /* We should try to avoid this in the future         */
          mpProblem->getModel()->getDerivatives(mpState, Derivatives);
          mpOutPoint->print(Copasi->OutputList, *mpOut);
        }

      if (ActualStepSize != (mpProblem->getEndTime() - Time))
        {
          /* Here we will do conditional event processing */
        }
    }
#endif // XXXX_Event

  mpProblem->setEndState(new CState(*mpState));

  if (mpOutEnd)
    {
      /* Correct output depends on the model being updated */
      /* We should try to avoid this in the future         */
      mpProblem->getModel()->getDerivatives(mpState, Derivatives);
      mpOutEnd->print(Copasi->OutputList, *mpOut);
    }
}
