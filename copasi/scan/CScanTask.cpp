// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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
#include "copasi.h"
#include "CScanTask.h"
#include "CScanProblem.h"
#include "CScanMethod.h"
#include "utilities/CReadConfig.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"

#include "math/CMathContainer.h"
#include "optimization/COptProblem.h"

#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "lna/CLNAProblem.h"
#include "lna/CLNATask.h"
#include "utilities/COutputHandler.h"
#include "utilities/CProcessReport.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "crosssection/CCrossSectionTask.h"

CScanTask::CScanTask(const CCopasiContainer * pParent,
                     const CTaskEnum::Task & type):
  CCopasiTask(pParent, type),
  mProgress(0),
  mhProgress(C_INVALID_INDEX),
  mpSubtask(NULL),
  mOutputInSubtask(false),
  mUseInitialValues(true)
{
  mpProblem = new CScanProblem(this);
  mpMethod = createMethod(CTaskEnum::scanMethod);
  static_cast< CScanMethod * >(mpMethod)->setProblem(static_cast< CScanProblem * >(mpProblem));
}

CScanTask::CScanTask(const CScanTask & src,
                     const CCopasiContainer * pParent):
  CCopasiTask(src, pParent),
  mProgress(0),
  mhProgress(C_INVALID_INDEX),
  mpSubtask(NULL),
  mOutputInSubtask(false),
  mUseInitialValues(true)
{
  mpProblem = new CScanProblem(*(CScanProblem *) src.mpProblem, this);
  mpMethod = createMethod(CTaskEnum::scanMethod);
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
  assert(mpProblem && mpMethod);

  mpMethod->isValidProblem(mpProblem);

  bool success = true;

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

  CCrossSectionTask* task = dynamic_cast<CCrossSectionTask*>(mpSubtask);

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

  if (mpCallBack)
    {
      mpCallBack->setName("performing parameter scan...");

      unsigned C_INT32 totalSteps = (unsigned C_INT32) pMethod->getTotalNumberOfSteps();
      mhProgress = mpCallBack->addItem("Number of Steps",
                                       mProgress,
                                       &totalSteps);

      if (mpSubtask)
        mpSubtask->setCallBack(mpCallBack);
    }

  // init output handler (plotting)
  output(COutputInterface::BEFORE);

  //calling the scanner, output is done in the callback
  if (!pMethod->scan()) success = false;

  if (task != NULL)
    task->removeEvent();

  //finishing progress bar and output
  //if (mpCallBack) mpCallBack->finish();
  //if (mpOutputHandler) mpOutputHandler->finish();
  output(COutputInterface::AFTER);

  if (mpSubtask)
    mpSubtask->setCallBack(NULL);

  return success;
}

bool CScanTask::restore()
{
  bool success = true;

  if (mpSubtask != NULL)
    {
      success &= mpSubtask->restore();
    }

  success = CCopasiTask::restore();

  return success;
}

// virtual
const CTaskEnum::Method * CScanTask::getValidMethods() const
{
  static const CTaskEnum::Method ValidMethods[] =
  {
    CTaskEnum::scanMethod,
    CTaskEnum::UnsetMethod
  };

  return ValidMethods;
}

bool CScanTask::processCallback()
{
  bool success = mpSubtask->process(mUseInitialValues);

  //do output
  if (success && !mOutputInSubtask)
    output(COutputInterface::DURING);

  if (mpSubtask->isUpdateModel())
    {
      COptProblem* problem = dynamic_cast<COptProblem*>(mpSubtask->getProblem());

      if (problem != NULL)
        {
          problem->restoreModel(true);
        }
    }

  //do progress bar
  ++mProgress;

  if (mpCallBack) return mpCallBack->progressItem(mhProgress);

  return true;
}

bool CScanTask::outputSeparatorCallback(bool isLast)
{
  if ((!isLast) || mOutputInSubtask)
    separate(COutputInterface::DURING);

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
  CTaskEnum::Task type = *(CTaskEnum::Task*) pProblem->getValue("Subtask").pUINT;
  CCopasiDataModel* pDataModel = getObjectDataModel();
  assert(pDataModel != NULL);

  switch (type)
    {
      case CTaskEnum::steadyState:
        mpSubtask = dynamic_cast<CCopasiTask*>
                    ((*pDataModel->getTaskList())["Steady-State"]);
        break;

      case CTaskEnum::timeCourse:
        mpSubtask = dynamic_cast<CCopasiTask*>
                    ((*pDataModel->getTaskList())["Time-Course"]);
        break;

      case CTaskEnum::mca:
        mpSubtask = dynamic_cast<CCopasiTask*>
                    ((*pDataModel->getTaskList())["Metabolic Control Analysis"]);
        break;

      case CTaskEnum::lyap:
        mpSubtask = dynamic_cast<CCopasiTask*>
                    ((*pDataModel->getTaskList())["Lyapunov Exponents"]);
        break;

      case CTaskEnum::optimization:
        mpSubtask = dynamic_cast<CCopasiTask*>
                    ((*pDataModel->getTaskList())["Optimization"]);
        break;

      case CTaskEnum::parameterFitting:
        mpSubtask = dynamic_cast<CCopasiTask*>
                    ((*pDataModel->getTaskList())["Parameter Estimation"]);
        break;

      case CTaskEnum::sens:
        mpSubtask = dynamic_cast<CCopasiTask*>
                    ((*pDataModel->getTaskList())["Sensitivities"]);
        break;

      case CTaskEnum::lna:
        mpSubtask = dynamic_cast<CCopasiTask*>
                    ((*pDataModel->getTaskList())["Linear Noise Approximation"]);
        break;

      case CTaskEnum::tssAnalysis :
        mpSubtask = dynamic_cast<CCopasiTask*>
                    ((*pDataModel->getTaskList())[CTaskEnum::TaskName[CTaskEnum::tssAnalysis]]);
        break;

      case CTaskEnum::crosssection:
        mpSubtask = dynamic_cast<CCopasiTask*>
                    ((*pDataModel->getTaskList())["Cross Section"]);
        break;

      default:
        mpSubtask = NULL;
    }

  mOutputInSubtask = * pProblem->getValue("Output in subtask").pBOOL;
  mUseInitialValues = !pProblem->getContinueFromCurrentState();

  if (!mpSubtask) return false;

  mpSubtask->setMathContainer(mpContainer); //TODO
  mpSubtask->setCallBack(NULL);

  if (mOutputInSubtask)
    return mpSubtask->initialize(OUTPUT, pOutputHandler, pOstream);
  else
    return mpSubtask->initialize(NO_OUTPUT, pOutputHandler, pOstream);

  return true;
}

void CScanTask::fixBuild81()
{
  CScanProblem * pProblem = dynamic_cast< CScanProblem * >(mpProblem);

  if (pProblem == NULL) return;

  pProblem->fixBuild81();

  return;
}
