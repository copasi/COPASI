// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the 
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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

/**
 * CScanTask class.
 *
 * This class implements a scan task which is comprised of a
 * of a problem and a method.
 *
 */
#include "copasi/copasi.h"
#include "CScanTask.h"
#include "CScanProblem.h"
#include "CScanMethod.h"
#include "copasi/utilities/CReadConfig.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CReport.h"

#include "copasi/math/CMathContainer.h"
#include "copasi/optimization/COptProblem.h"

#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/trajectory/CTrajectoryProblem.h"
#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/steadystate/CSteadyStateProblem.h"
#include "copasi/lna/CLNAProblem.h"
#include "copasi/lna/CLNATask.h"
#include "copasi/parameterFitting/CFitTask.h"
#include "copasi/output/COutputHandler.h"
#include "copasi/utilities/CProcessReport.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/crosssection/CCrossSectionTask.h"
#include "copasi/utilities/CMethodFactory.h"

CScanTask::CScanTask(const CDataContainer * pParent,
                     const CTaskEnum::Task & type):
  CCopasiTask(pParent, type),
  mProgress(0),
  mhProgress(C_INVALID_INDEX),
  mpSubTask(NULL),
  mOutputInSubtask(false),
  mUseInitialValues(true)
{
  mpMethod = CMethodFactory::create(getType(), CTaskEnum::Method::scanMethod, this);
  static_cast< CScanMethod * >(mpMethod)->setProblem(static_cast< CScanProblem * >(mpProblem));
}

CScanTask::CScanTask(const CScanTask & src,
                     const CDataContainer * pParent):
  CCopasiTask(src, pParent),
  mProgress(0),
  mhProgress(C_INVALID_INDEX),
  mpSubTask(NULL),
  mOutputInSubtask(false),
  mUseInitialValues(true)
{
  static_cast< CScanMethod * >(mpMethod)->setProblem(static_cast< CScanProblem * >(mpProblem));
}

CScanTask::~CScanTask()
{cleanup();}

void CScanTask::cleanup()
{}

bool CScanTask::initialize(const OutputFlag & of,
                           COutputHandler * pOutputHandler,
                           std::ostream * pOstream)
{
  if (!isTaskValid())
    return false;

  bool success = mpMethod->isValidProblem(mpProblem);

  if ((of & REPORT) &&
      pOutputHandler != NULL)
    {
      if (mReport.open(getObjectDataModel(), pOstream))
        pOutputHandler->addInterface(&mReport);
      else
        CCopasiMessage(CCopasiMessage::COMMANDLINE, MCCopasiTask + 5, getObjectName().c_str());
    }

  success &= initSubtask(of, pOutputHandler, mReport.getStream());
  success &= CCopasiTask::initialize(of, pOutputHandler, mReport.getStream());

  return success;
}

void CScanTask::load(CReadConfig & C_UNUSED(configBuffer))
{}

bool CScanTask::process(const bool & useInitialValues)
{
  if (!mpProblem) fatalError();

  if (!mpMethod) fatalError();

  CScanProblem * pProblem = dynamic_cast<CScanProblem *>(mpProblem);

  if (!pProblem) fatalError();

  CScanMethod * pMethod = dynamic_cast<CScanMethod *>(mpMethod);

  if (!pMethod) fatalError();

  bool success = true;

  CCrossSectionTask* task = dynamic_cast<CCrossSectionTask*>(mpSubTask);

  if (task != NULL)
    task->createEvent();

  if (useInitialValues)
    {
      mpContainer->applyInitialValues();
    }

  //TODO: reports

  // initialize the method (parsing the ScanItems)
  pMethod->setProblem(pProblem);

  if (!pMethod->init()) return false;

  // init progress bar
  mProgress = 0;

  if (mProcessReport)
    {
      mProcessReport.setName("performing parameter scan...");

      unsigned C_INT32 totalSteps = (unsigned C_INT32) pMethod->getTotalNumberOfSteps();
      mhProgress = mProcessReport.addItem("Number of Steps",
                                          mProgress,
                                          &totalSteps);

      if (mpSubTask)
        mpSubTask->setCallBack(mProcessReport);
    }

  // init output handler (plotting)
  output(COutputInterface::BEFORE);

  //calling the scanner, output is done in the callback
  if (!pMethod->scan()) success = false;

  if (task != NULL)
    task->removeEvent();

  //finishing progress bar and output
  //if (mCallBack) mCallBack.finish();
  //if (mpOutputHandler) mpOutputHandler->finish();
  output(COutputInterface::AFTER);

  if (mpSubTask)
    mpSubTask->setCallBack(NULL);

  return success;
}

// virtual
const CTaskEnum::Method * CScanTask::getValidMethods() const
{
  static const CTaskEnum::Method ValidMethods[] =
  {
    CTaskEnum::Method::scanMethod,
    CTaskEnum::Method::UnsetMethod
  };

  return ValidMethods;
}

bool CScanTask::processCallback()
{
  bool success = mpSubTask->process(mUseInitialValues);

  //do output
  if (success && !mOutputInSubtask)
    if (dynamic_cast< CFitTask * >(mpSubTask))
      {
        output(COutputInterface::AFTER);
      }
    else
      output(COutputInterface::DURING);
  


  if (mpSubTask->isUpdateModel())
    {
      COptProblem* problem = dynamic_cast<COptProblem*>(mpSubTask->getProblem());

      if (problem != NULL)
        {
          problem->restore(true);
        }
    }

  //do progress bar
  ++mProgress;

  if (mProcessReport) return mProcessReport.progressItem(mhProgress);

  return true;
}

bool CScanTask::outputSeparatorCallback(bool isLast)
{
  if ((!isLast) || mOutputInSubtask)
    {
      if (dynamic_cast< CFitTask * >(mpSubTask))
        separate(COutputInterface::AFTER);
      else
        separate(COutputInterface::DURING);
    }

  return true;
}

bool CScanTask::initSubtask(const OutputFlag & /* of */,
                            COutputHandler * pOutputHandler,
                            std::ostream * pOstream)
{
  if (!mpProblem) fatalError();

  CScanProblem * pProblem = dynamic_cast<CScanProblem *>(mpProblem);

  if (!pProblem) fatalError();

  //get the parameters from the problem
  CTaskEnum::Task type = (CTaskEnum::Task) pProblem->getValue< unsigned C_INT32 >("Subtask");
  CDataModel* pDataModel = getObjectDataModel();
  assert(pDataModel != NULL);

  switch (type)
    {
      case CTaskEnum::Task::steadyState:
        mpSubTask = dynamic_cast<CCopasiTask*>
                    (&pDataModel->getTaskList()->operator[]("Steady-State"));
        break;

      case CTaskEnum::Task::timeCourse:
        mpSubTask = dynamic_cast<CCopasiTask*>
                    (&pDataModel->getTaskList()->operator[]("Time-Course"));
        break;

      case CTaskEnum::Task::mca:
        mpSubTask = dynamic_cast<CCopasiTask*>
                    (&pDataModel->getTaskList()->operator[]("Metabolic Control Analysis"));
        break;

      case CTaskEnum::Task::lyap:
        mpSubTask = dynamic_cast<CCopasiTask*>
                    (&pDataModel->getTaskList()->operator[]("Lyapunov Exponents"));
        break;

      case CTaskEnum::Task::optimization:
        mpSubTask = dynamic_cast<CCopasiTask*>
                    (&pDataModel->getTaskList()->operator[]("Optimization"));
        break;

      case CTaskEnum::Task::parameterFitting:
        mpSubTask = dynamic_cast<CCopasiTask*>
                    (&pDataModel->getTaskList()->operator[]("Parameter Estimation"));
        break;

      case CTaskEnum::Task::sens:
        mpSubTask = dynamic_cast<CCopasiTask*>
                    (&pDataModel->getTaskList()->operator[]("Sensitivities"));
        break;

      case CTaskEnum::Task::lna:
        mpSubTask = dynamic_cast<CCopasiTask*>
                    (&pDataModel->getTaskList()->operator[]("Linear Noise Approximation"));
        break;

      case CTaskEnum::Task::tssAnalysis :
        mpSubTask = dynamic_cast<CCopasiTask*>
                    (&pDataModel->getTaskList()->operator[](CTaskEnum::TaskName[CTaskEnum::Task::tssAnalysis]));
        break;

      case CTaskEnum::Task::crosssection:
        mpSubTask = dynamic_cast<CCopasiTask*>
                    (&pDataModel->getTaskList()->operator[]("Cross Section"));
        break;

      case CTaskEnum::Task::timeSens:
        mpSubTask = dynamic_cast<CCopasiTask*>
                    (&pDataModel->getTaskList()->operator[](CTaskEnum::TaskName[CTaskEnum::Task::timeSens]));
        break;

      default:
        mpSubTask = NULL;
    }

  mOutputInSubtask = pProblem->getValue< bool >("Output in subtask");
  mUseInitialValues = !pProblem->getContinueFromCurrentState();

  if (!mpSubTask) return false;

  mpSubTask->setMathContainer(mpContainer); //TODO
  mpSubTask->setCallBack(NULL);

  if (mOutputInSubtask)
    {
        if (dynamic_cast< CFitTask * >(mpSubTask))
          return mpSubTask->initialize(OUTPUT_AFTER, pOutputHandler, pOstream);
        else 
          return mpSubTask->initialize(OUTPUT_DURING, pOutputHandler, pOstream);
    }
  else
    return mpSubTask->initialize(NO_OUTPUT, pOutputHandler, pOstream);

  return true;
}

void CScanTask::fixBuild81()
{
  CScanProblem * pProblem = dynamic_cast< CScanProblem * >(mpProblem);

  if (pProblem == NULL) return;

  pProblem->fixBuild81();

  return;
}
