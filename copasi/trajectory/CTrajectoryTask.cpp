/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTrajectoryTask.cpp,v $
   $Revision: 1.33 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/06/23 14:02:57 $
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
//#include "output/COutput.h"
//#include "output/COutputEvent.h"
//#include "output/COutputList.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "utilities/CGlobals.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"
#include "utilities/COutputHandler.h"

#define XXXX_Reporting

CTrajectoryTask::CTrajectoryTask(const CCopasiContainer * pParent):
    CCopasiTask(CCopasiTask::timeCourse, pParent),
    mpState(NULL)
{
  mpProblem = new CTrajectoryProblem(this);
  mpMethod =
    CTrajectoryMethod::createTrajectoryMethod(CCopasiMethod::deterministic,
        (CTrajectoryProblem *) mpProblem);
  mpMethod->setObjectParent(this);
}

CTrajectoryTask::CTrajectoryTask(const CTrajectoryTask & src,
                                 const CCopasiContainer * pParent):
    CCopasiTask(src, pParent),
    mpState(src.mpState)
{fatalError();}

CTrajectoryTask::CTrajectoryTask(CTrajectoryProblem * pProblem,
                                 CTrajectoryMethod::SubType subType,
                                 const CCopasiContainer * pParent):
    CCopasiTask(CCopasiTask::timeCourse, pParent),
    mpState(NULL)
{
  mpProblem = pProblem;
  mpProblem->setObjectParent(this);
  mpMethod =
    CTrajectoryMethod::createTrajectoryMethod(subType,
        (CTrajectoryProblem *) mpProblem);
  mpMethod->setObjectParent(this);
}

CTrajectoryTask::CTrajectoryTask(CModel * pModel,
                                 C_FLOAT64 starttime, C_FLOAT64 endtime,
                                 unsigned C_INT32 stepnumber,
                                 CTrajectoryMethod::SubType subType,
                                 const CCopasiContainer * pParent):
    CCopasiTask(CCopasiTask::timeCourse, pParent),
    mpState(NULL)
{
  mpProblem = new CTrajectoryProblem(this);
  ((CTrajectoryProblem *) mpProblem)->setModel(pModel);
  ((CTrajectoryProblem *) mpProblem)->setStartTime(starttime);
  ((CTrajectoryProblem *) mpProblem)->setEndTime(endtime);
  ((CTrajectoryProblem *) mpProblem)->setStepNumber(stepnumber);

  mpMethod =
    CTrajectoryMethod::createTrajectoryMethod(subType,
        (CTrajectoryProblem *) mpProblem);
  mpMethod->setObjectParent(this);
}

CTrajectoryTask::~CTrajectoryTask()
{
  cleanup();
}

void CTrajectoryTask::cleanup()
{pdelete(mpState);}

void CTrajectoryTask::load(CReadConfig & configBuffer)
{
  configBuffer.getVariable("Dynamics", "bool", &mScheduled,
                           CReadConfig::LOOP);

  pdelete(mpProblem);
  mpProblem = new CTrajectoryProblem(this);
  ((CTrajectoryProblem *) mpProblem)->load(configBuffer);

  pdelete(mpMethod);
  mpMethod = CTrajectoryMethod::createTrajectoryMethod();
  mpMethod->setObjectParent(this);
  ((CTrajectoryMethod *)mpMethod)->setProblem((CTrajectoryProblem *) mpProblem);
}

CState * CTrajectoryTask::getState()
{return mpState;}

bool CTrajectoryTask::initialize(std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  CTrajectoryProblem* pProblem =
    dynamic_cast<CTrajectoryProblem *>(mpProblem);
  assert(pProblem);

  bool success = true;

  if (!mReport.open(pOstream)) success = false;
  if (!mReport.compile()) success = false;
  if (!pProblem->getModel()->compile2()) success = false;
  //  if (!pProblem->
  //      setInitialState(pProblem->getModel()->getInitialState()))
  //    success = false;
  pProblem->setInitialState(pProblem->getModel()->getInitialState());

  return success;
}

bool CTrajectoryTask::process()
{
  assert(mpProblem && mpMethod);

  CTrajectoryProblem * pProblem = (CTrajectoryProblem *) mpProblem;
  CTrajectoryMethod * pMethod = (CTrajectoryMethod *) mpMethod;

  pdelete(mpState);
  mpState = new CState(pProblem->getInitialState());

  pMethod->setCurrentState(mpState);
  pMethod->setProblem(pProblem);

  CVector< C_FLOAT64 > Derivatives(mpState->getVariableNumberSize());

  pProblem->getModel()->getDerivatives(mpState, Derivatives);
  mReport.printHeader();

  pProblem->getModel()->getDerivatives(mpState, Derivatives);
  mReport.printBody();

  if (mpOutputHandler) mpOutputHandler->init();

  C_FLOAT64 StepSize = pProblem->getStepSize();
  C_FLOAT64 ActualStepSize;
  const C_FLOAT64 & Time = mpState->getTime();
  C_FLOAT64 EndTime = pProblem->getEndTime() - StepSize;

  ActualStepSize = pMethod->step(StepSize, mpState);

  pProblem->getModel()->getDerivatives(mpState, Derivatives);
  mReport.printBody();

#ifdef  XXXX_Event
  if (ActualStepSize != StepSize)
    {
      /* Here we will do conditional event processing */
    }
#endif // XXXX_Event

  while (Time < EndTime)
    {
      ActualStepSize = pMethod->step(StepSize);

      pProblem->getModel()->getDerivatives(mpState, Derivatives);
      mReport.printBody();
      if (mpOutputHandler) mpOutputHandler->doOutput();

#ifdef  XXXX_Event
      if (ActualStepSize != StepSize)
        {
          /* Here we will do conditional event processing */
        }
#endif // XXXX_Event
    }

  while (Time < pProblem->getEndTime())
    {
      ActualStepSize = pMethod->step(pProblem->getEndTime() - Time);

#ifdef  XXXX_Event
      pProblem->getModel()->getDerivatives(mpState, Derivatives);
      mReport.printBody();

      if (ActualStepSize != (pProblem->getEndTime() - Time))
        {
          /* Here we will do conditional event processing */
        }
#endif // XXXX_Event
    }

  pProblem->setEndState(new CState(*mpState));

  pProblem->getModel()->getDerivatives(mpState, Derivatives);
  mReport.printFooter();

  if (mpOutputHandler) mpOutputHandler->finish();

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
  mpMethod->setObjectParent(this);

  return true;
}
