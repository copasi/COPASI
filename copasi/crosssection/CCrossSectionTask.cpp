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
#include "model/CMathModel.h"
#include "model/CState.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"
#include "utilities/CProcessReport.h"
#include "utilities/CCopasiException.h"
#include  "CopasiDataModel/CCopasiDataModel.h"


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
  mOutputStartTime(0.0)
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
  mOutputStartTime(0.0)
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

  //Here we mark one existing event as being the cut plane. This is probably
  //the place where in the future we will create this special event 
  //rather than just mark it.
  
  CModel* pModel = mpCrossSectionProblem->getModel();
  size_t i;
  for (i=0; i<pModel->getEvents().size(); ++i)
  {
    if (pModel->getEvents()[i]->getObjectName()=="__cutplane")
      pModel->getEvents()[i]->setIsCutPlane(true);
  }
  pModel->setCompileFlag();
  pModel->compileIfNecessary(NULL);
  
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
  processStart(useInitialValues);

  //this instructs the process queue to call back whenever an event is 
  //executed
  mpCrossSectionProblem->getModel()->getMathModel()->getProcessQueue().setEventCallBack(this, &EventCallBack);

  
  C_FLOAT64 MaxDuration = mpCrossSectionProblem->getDuration();

  //the output starts only after "outputStartTime" has passed
  mOutputStartTime = *mpCurrentTime + mpCrossSectionProblem->getOutputStartTime();
  
  //C_FLOAT64 NextTimeToReport;

  const C_FLOAT64 EndTime = *mpCurrentTime + MaxDuration;
  const C_FLOAT64 StartTime = *mpCurrentTime;
  C_FLOAT64 CompareEndTime;

  // It suffices to reach the end time within machine precision
  CompareEndTime = EndTime - 100.0 * (fabs(EndTime) * std::numeric_limits< C_FLOAT64 >::epsilon() + std::numeric_limits< C_FLOAT64 >::min());

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
      while ((*mpCurrentTime < CompareEndTime) && flagProceed);
    }

  catch (int)
    {
      mpCrossSectionProblem->getModel()->setState(*mpCurrentState);
      mpCrossSectionProblem->getModel()->updateSimulatedValues(mUpdateMoieties);


      if (mpCallBack != NULL) mpCallBack->finishItem(hProcess);

      output(COutputInterface::AFTER);

      //reset call back
      mpCrossSectionProblem->getModel()->getMathModel()->getProcessQueue().setEventCallBack(NULL, NULL);
      
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 16);
    }

  catch (CCopasiException & Exception)
    {
      mpCrossSectionProblem->getModel()->setState(*mpCurrentState);
      mpCrossSectionProblem->getModel()->updateSimulatedValues(mUpdateMoieties);


      if (mpCallBack != NULL) mpCallBack->finishItem(hProcess);

      output(COutputInterface::AFTER);

      //reset call back
      mpCrossSectionProblem->getModel()->getMathModel()->getProcessQueue().setEventCallBack(NULL, NULL);

      throw CCopasiException(Exception.getMessage());
    }

  if (mpCallBack != NULL) mpCallBack->finishItem(hProcess);

  output(COutputInterface::AFTER);

  //reset call back
  mpCrossSectionProblem->getModel()->getMathModel()->getProcessQueue().setEventCallBack(NULL, NULL);

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
      //pModel->getMathModel()->getProcessQueue().printDebug();
      
      //execute events for inequalities
      StateChanged |= pModel->processQueue(*mpCurrentTime, false, NULL);

      if (StateChanged)
        {
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

            // TODO Provide a call back method for resolving simultaneous assignments.
            
            //execute events for equalities
            StateChanged |= pModel->processQueue(*mpCurrentTime, true, NULL);

            if (fabs(*mpCurrentTime - endTime) < Tolerance)
              return true;

            break;

          case CTrajectoryMethod::ROOT:
            //we arrive here whenever the integrator finds a root
            //this does not necessarily mean an event fires
            pModel->setState(*mpCurrentState);
            pModel->updateSimulatedValues(mUpdateMoieties);

            //this checks whether equality events are triggered
            pModel->processRoots(*mpCurrentTime, true, true, mpTrajectoryMethod->getRoots());
            //pModel->getMathModel()->getProcessQueue().printDebug();

            if ((mOutputStartTime <= *mpCurrentTime) &&
                *mpCurrentTime == pModel->getProcessQueueExecutionTime() )
              {
                //this output is done when an event from an equality 
                //is scheduled in the queue
                //for the current time; befor the execution of the event
                output(COutputInterface::DURING);
              }

            // TODO Provide a call back method for resolving simultaneous assignments.
            
            //execute scheduled events for equalities
            StateChanged |= pModel->processQueue(*mpCurrentTime, true, NULL);

            //this checks whether inequality events are triggered
            pModel->processRoots(*mpCurrentTime, false, true, mpTrajectoryMethod->getRoots());
            //pModel->getMathModel()->getProcessQueue().printDebug();

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

            if ((mOutputStartTime <= *mpCurrentTime)  &&
                (  /*StateChanged || */
                 *mpCurrentTime == pModel->getProcessQueueExecutionTime()))
              {
                //this output is done when an event from an inequality
                //is scheduled in the queue 
                //for the current time; before the execution of this event
                output(COutputInterface::DURING);
              }

            break;

          case CTrajectoryMethod::FAILURE:
            //reset call back
            mpCrossSectionProblem->getModel()->getMathModel()->getProcessQueue().setEventCallBack(NULL, NULL);

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

  //reset call back
  mpCrossSectionProblem->getModel()->getMathModel()->getProcessQueue().setEventCallBack(NULL, NULL);

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

//static
void CCrossSectionTask::EventCallBack(void* pCSTask, C_INT32 type)
{static_cast<CCrossSectionTask *>(pCSTask)->eventCallBack(type);}

void CCrossSectionTask::eventCallBack(C_INT32 type)
{
  std::cout << "event call back: " << type << std::endl;
}