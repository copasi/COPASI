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
#include "output/COutput.h"
#include "output/COutputEvent.h"
#include "output/COutputList.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "utilities/CGlobals.h"
#include "report/CKeyFactory.h"
#include "report/CReportDefinition.h"

#define XXXX_Reporting

CTrajectoryTask::CTrajectoryTask(const std::string & name,
                                 const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "TrajectoryTask", CCopasiObject::Container),
    mReport(new CReport),
    mKey(CKeyFactory::add("TrajectoryTask", this)),
    mpProblem(new CTrajectoryProblem),
    mpMethod(CTrajectoryMethod::createTrajectoryMethod()),
    mpState(NULL),
    mpOutInit(NULL),
    mpOutPoint(NULL),
    mpOutEnd(NULL)
{}

CTrajectoryTask::CTrajectoryTask(const CTrajectoryTask & src,
                                 const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mReport(new CReport),
    mKey(CKeyFactory::add("TrajectoryTask", this)),
    mpProblem(src.mpProblem),
    mpMethod(src.mpMethod),
    mpState(src.mpState),
    mpOutInit(src.mpOutInit),
    mpOutPoint(src.mpOutPoint),
    mpOutEnd(src.mpOutEnd)
{}

CTrajectoryTask::CTrajectoryTask(CTrajectoryProblem * pProblem,
                                 CTrajectoryMethod::Type type,
                                 const CCopasiContainer * pParent):
    CCopasiContainer("TrajectoryTask", pParent, "TrajectoryTask", CCopasiObject::Container),
    mReport(new CReport),
    mKey(CKeyFactory::add("TrajectoryTask", this)),
    mpProblem(pProblem),
    mpMethod(CTrajectoryMethod::createTrajectoryMethod(type, pProblem)),
    mpState(NULL),
    mpOutInit(NULL),
    mpOutPoint(NULL),
    mpOutEnd(NULL)
{}

CTrajectoryTask::CTrajectoryTask(CModel * pModel,
                                 C_FLOAT64 starttime, C_FLOAT64 endtime,
                                 unsigned C_INT32 stepnumber,
                                 CTrajectoryMethod::Type type,
                                 const CCopasiContainer * pParent):
    CCopasiContainer("TrajectoryTask", pParent, "TrajectoryTask", CCopasiObject::Container),
    mReport(new CReport),
    mKey(CKeyFactory::add("TrajectoryTask", this)),
    mpProblem(new CTrajectoryProblem(pModel, starttime, endtime, stepnumber)),
    mpMethod(CTrajectoryMethod::createTrajectoryMethod(type, mpProblem)),
    mpState(NULL),
    mpOutInit(NULL),
    mpOutPoint(NULL),
    mpOutEnd(NULL)
{}

CTrajectoryTask::~CTrajectoryTask()
{
  cleanup();
}

void CTrajectoryTask::cleanup()
{
  CKeyFactory::remove(mKey);
  pdelete(mpProblem);
  pdelete(mpMethod);
  pdelete(mpState);
  pdelete(mpOutInit);
  pdelete(mpOutPoint);
  pdelete(mpOutEnd);
  pdelete(mReport);
}

std::string CTrajectoryTask::getKey() const {return mKey;}

void CTrajectoryTask::initializeReporting(std::ostream & out)
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
    configBuffer.getVariable("Dynamics", "bool", &mRequested,
                             CReadConfig::LOOP);
  else
    configBuffer.getVariable("RunTrajectory", "bool", &mRequested,
                             CReadConfig::LOOP);

  pdelete(mpProblem);
  mpProblem = new CTrajectoryProblem();
  mpProblem->load(configBuffer);

  pdelete(mpMethod);
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
  configBuffer.setVariable("RunTrajectory", "bool", &mRequested);

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
  mpState = new CState(mpProblem->getInitialState());

  if (mpOutInit || mpOutPoint || mpOutEnd)
    Copasi->pOutputList->compile("Time-course output",
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
      mpOutInit->print(*Copasi->pOutputList, *mpOut);
    }

  if (mpOutPoint)
    {
      /* Correct output depends on the model being updated */
      /* We should try to avoid this in the future         */
      mpProblem->getModel()->getDerivatives(mpState, Derivatives);
      mpOutPoint->print(*Copasi->pOutputList, *mpOut);
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
      mpOutPoint->print(*Copasi->pOutputList, *mpOut);
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
          mpOutPoint->print(*Copasi->pOutputList, *mpOut);
        }

#ifdef  XXXX_Event
      if (ActualStepSize != StepSize)
        {
          /* Here we will do conditional event processing */
        }
#endif // XXXX_Event
    }

  while (Time < mpProblem->getEndTime())
    {
      ActualStepSize = mpMethod->step(mpProblem->getEndTime() - Time);

#ifdef  XXXX_Event
      if (mpOutPoint)
        {
          /* Correct output depends on the model being updated */
          /* We should try to avoid this in the future         */
          mpProblem->getModel()->getDerivatives(mpState, Derivatives);
          mpOutPoint->print(*Copasi->pOutputList, *mpOut);
        }

      if (ActualStepSize != (mpProblem->getEndTime() - Time))
        {
          /* Here we will do conditional event processing */
        }
#endif // XXXX_Event
    }

  mpProblem->setEndState(new CState(*mpState));

  if (mpOutEnd)
    {
      /* Correct output depends on the model being updated */
      /* We should try to avoid this in the future         */
      mpProblem->getModel()->getDerivatives(mpState, Derivatives);
      mpOutEnd->print(*Copasi->pOutputList, *mpOut);
    }
}
