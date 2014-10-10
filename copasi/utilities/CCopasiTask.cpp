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
 *  CCopasiTask class.
 *  This class is used to describe a task in COPASI. This class is
 *  intended to be used as the parent class for all tasks within COPASI.
 *
 *  Created for COPASI by Stefan Hoops 2003
 */

#include "copasi.h"

#include "CCopasiTask.h"
#include "CCopasiProblem.h"
#include "CCopasiMethod.h"
#include "report/CReport.h"
#include "report/CKeyFactory.h"
#include "utilities/COutputHandler.h"
#include "math/CMathContainer.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "report/CCopasiObjectReference.h"
#include "report/CCopasiTimer.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "copasi/report/CCopasiRootContainer.h"

const std::string CCopasiTask::TypeName[] =
{
  "Steady-State",
  "Time-Course",
  "Scan",
  "Elementary Flux Modes",
  "Optimization",
  "Parameter Estimation",
  "Metabolic Control Analysis",
  "Lyapunov Exponents",
  "Time Scale Separation Analysis",
  "Sensitivities",
  "Moieties",
  "Cross Section",
  "Linear Noise Approximation",
  "not specified",
  ""
};

const char* CCopasiTask::XMLType[] =
{
  "steadyState",
  "timeCourse",
  "scan",
  "fluxMode",
  "optimization",
  "parameterFitting",
  "metabolicControlAnalysis",
  "lyapunovExponents",
  "timeScaleSeparationAnalysis",
  "sensitivities",
  "moieties",
  "crosssection",
  "linearNoiseApproximation",
  "unset",
  NULL
};

const unsigned int CCopasiTask::ValidMethods[] =
{
  CCopasiMethod::unset
};

bool CCopasiTask::isValidMethod(const unsigned int & method,
                                const unsigned int * validMethods)
{
  unsigned C_INT32 i;

  for (i = 0; validMethods[i] != CCopasiMethod::unset; i++)
    if (method == validMethods[i]) return true;

  return false;
}

CCopasiTask::CCopasiTask():
  CCopasiContainer(CCopasiTask::TypeName[CCopasiTask::unset], NULL, "Task"),
  mType(CCopasiTask::unset),
  mKey(CCopasiRootContainer::getKeyFactory()->add("Task", this)),
  mDescription(this),
  mResult(this),
  mScheduled(false),
  mUpdateModel(false),
  mpProblem(NULL),
  mpMethod(NULL),
  mReport(),
  mInitialState(),
  mpContainer(NULL),
  mpCallBack(NULL),
  mpSliders(NULL),
  mDoOutput(OUTPUT_SE),
  mpOutputHandler(NULL),
  mOutputCounter(0)
{initObjects();}

CCopasiTask::CCopasiTask(const CCopasiContainer * pParent,
                         const CCopasiTask::Type & taskType,
                         const std::string & type):
  CCopasiContainer(CCopasiTask::TypeName[taskType], pParent, type),
  mType(taskType),
  mKey(CCopasiRootContainer::getKeyFactory()->add("Task", this)),
  mDescription(this),
  mResult(this),
  mScheduled(false),
  mUpdateModel(false),
  mpProblem(NULL),
  mpMethod(NULL),
  mReport(),
  mpContainer(NULL),
  mInitialState(),
  mpCallBack(NULL),
  mpSliders(NULL),
  mDoOutput(OUTPUT_SE),
  mpOutputHandler(NULL),
  mOutputCounter(0)
{initObjects();}

CCopasiTask::CCopasiTask(const CCopasiTask & src,
                         const CCopasiContainer * pParent):
  CCopasiContainer(src, pParent),
  mType(src.mType),
  mKey(CCopasiRootContainer::getKeyFactory()->add("Task", this)),
  mDescription(src.mDescription, this),
  mResult(src.mResult, this),
  mScheduled(src.mScheduled),
  mUpdateModel(src.mUpdateModel),
  mpProblem(NULL),
  mpMethod(NULL),
  mReport(src.mReport),
  mpContainer(src.mpContainer),
  mInitialState(src.mInitialState),
  mpCallBack(NULL),
  mpSliders(NULL),
  mDoOutput(src.mDoOutput),
  mpOutputHandler(NULL),
  mOutputCounter(0)
{initObjects();}

CCopasiTask::~CCopasiTask()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);

  pdelete(mpProblem);
  pdelete(mpMethod);
  pdelete(mpSliders);
}

//const std::string & CCopasiTask::getName() const {return getObjectName();}

//bool CCopasiTask::setName(const std::string & name)
//{return setObjectName(name);}

CCopasiTask::Type CCopasiTask::getType() const {return mType;}

void CCopasiTask::setType(const CCopasiTask::Type & type) {mType = type;}

const std::string & CCopasiTask::getKey() const {return mKey;}

void CCopasiTask::setScheduled(const bool & scheduled) {mScheduled = scheduled;}

const bool & CCopasiTask::isScheduled() const {return mScheduled;}

void CCopasiTask::setUpdateModel(const bool & updateModel) {mUpdateModel = updateModel;}

const bool & CCopasiTask::isUpdateModel() const {return mUpdateModel;}

void CCopasiTask::setMathContainer(CMathContainer * pContainer)
{
  if (mpProblem != NULL)
    {
      mpProblem->setMathContainer(pContainer);
    }

  if (mpMethod != NULL)
    {
      mpMethod->setMathContainer(pContainer);
    }

  if (pContainer != mpContainer)
    {
      mpContainer = pContainer;
      signalMathContainerChanged();
    }
}

// virtual
void CCopasiTask::signalMathContainerChanged()
{}

CMathContainer * CCopasiTask::getMathContainer() const
{
  return mpContainer;
}

bool CCopasiTask::setCallBack(CProcessReport * pCallBack)
{
  mpCallBack = pCallBack;
  return true;
}

CProcessReport * CCopasiTask::getCallBack() const
{
  return mpCallBack;
}

COutputHandler* CCopasiTask::getOutputHandler() const
{
  return mpOutputHandler;
}

bool CCopasiTask::initialize(const OutputFlag & of,
                             COutputHandler * pOutputHandler,
                             std::ostream * pOstream)
{
  bool success = true;

  if (mpProblem == NULL)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCCopasiTask + 1, getObjectName().c_str());
      return false;
    }

  if (mpContainer == NULL)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCCopasiTask + 2, getObjectName().c_str());
      return false;
    }

  if (mpMethod == NULL)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCCopasiTask + 3, getObjectName().c_str());
      return false;
    }

  if (mpContainer != NULL)
    {
      mInitialState = mpContainer->getInitialState();
    }
  else
    {
      mInitialState.resize(0);
    }

  mDoOutput = of;
  mpOutputHandler = pOutputHandler;

  if (mDoOutput == NO_OUTPUT ||
      mpOutputHandler == NULL) return true;

  mOutputCounter = 0;

  if (mDoOutput & REPORT)
    {
      if (mReport.open(getObjectDataModel(), pOstream) &&
          mReport.getTarget() != "")
        mpOutputHandler->addInterface(&mReport);
      else if (pOstream == NULL)
        CCopasiMessage(CCopasiMessage::COMMANDLINE, MCCopasiTask + 5, getObjectName().c_str());
    }

  CObjectInterface::ContainerList ListOfContainer;
  ListOfContainer.push_back(this);

  if (mpContainer != NULL)
    {
      ListOfContainer.push_back(mpContainer);
    }

  if (!mpOutputHandler->compile(ListOfContainer))
    {
      // Warning
      CCopasiMessage(CCopasiMessage::WARNING, MCCopasiTask + 7);
      success = false;
    }

  return success;
}

bool CCopasiTask::process(const bool &)
{return false;}

bool CCopasiTask::restore()
{
  setCallBack(NULL);

  if (!mUpdateModel)
    {
      if (mpContainer != NULL)
        {
          mpContainer->setInitialState(mInitialState);
          mpContainer->updateInitialValues(CModelParameter::ParticleNumbers);
        }
    }

  mpProblem->restore(mUpdateModel);

  return true;
}

CCopasiProblem * CCopasiTask::getProblem() {return mpProblem;}

const CCopasiProblem * CCopasiTask::getProblem() const {return mpProblem;}

// virtual
bool CCopasiTask::setMethodType(const int & C_UNUSED(type))
{
  return false;
}

// virtual
CCopasiMethod * CCopasiTask::createMethod(const int & /* type */) const
{
  return NULL;
}

CCopasiMethod * CCopasiTask::getMethod() {return mpMethod;}

const CCopasiMethod * CCopasiTask::getMethod() const {return mpMethod;}

CReport & CCopasiTask::getReport() {return mReport;}

const CCopasiTask::CDescription & CCopasiTask::getDescription() const
{return mDescription;}

const CCopasiTask::CResult & CCopasiTask::getResult() const
{return mResult;}

void CCopasiTask::cleanup() {}

CCopasiParameterGroup * CCopasiTask::getSliders()
{return mpSliders;}

// output stuff

void CCopasiTask::output(const COutputInterface::Activity & activity)
{
  if (mpOutputHandler != NULL)
    switch (activity)
      {
        case COutputInterface::DURING:

          if (mDoOutput != NO_OUTPUT)
            {
              mpOutputHandler->output(activity);
              ++mOutputCounter;
            }

          break;

        case COutputInterface::BEFORE:

          if (mDoOutput & OUTPUT_BEFORE)
            mpOutputHandler->output(activity);

          break;

        case COutputInterface::AFTER:

          if (mDoOutput & OUTPUT_AFTER)
            mpOutputHandler->output(activity);

          break;
      }
}

void CCopasiTask::separate(const COutputInterface::Activity & activity)
{
  if (mpOutputHandler != NULL)
    switch (activity)
      {
        case COutputInterface::DURING:

          if (mDoOutput)
            mpOutputHandler->separate(activity);

          break;

        case COutputInterface::BEFORE:

          if (mDoOutput & OUTPUT_BEFORE)
            mpOutputHandler->separate(activity);

          break;

        case COutputInterface::AFTER:

          if (mDoOutput & OUTPUT_AFTER)
            mpOutputHandler->separate(activity);

          break;
      }
}

void CCopasiTask::initObjects()
{
  addObjectReference("Output counter", mOutputCounter, CCopasiObject::ValueInt);
  new CCopasiTimer(CCopasiTimer::WALL, this);
  new CCopasiTimer(CCopasiTimer::PROCESS, this);

  CCopasiDataModel *pDataModel = getObjectDataModel();

  if (pDataModel != NULL)
    {
      if (pDataModel->getModel() != NULL)
        {
          setMathContainer(&pDataModel->getModel()->getMathContainer());
        }
    }
}

CCopasiTask::CDescription::CDescription(const CCopasiContainer * pParent):
  CCopasiObject("Description", pParent, "Object")
{}

CCopasiTask::CDescription::CDescription(const CCopasiTask::CDescription & src,
                                        const CCopasiContainer * pParent):
  CCopasiObject(src, pParent)
{}

CCopasiTask::CDescription::~CDescription() {}

void CCopasiTask::CDescription::print(std::ostream * ostream) const
{*ostream << *this;}

std::ostream &operator<<(std::ostream &os,
                         const CCopasiTask::CDescription & o)
{
  const CCopasiTask & Task = *static_cast<const CCopasiTask *>(o.getObjectParent());

  os << Task.getObjectName() << " Task" << std::endl << std::endl;

  if (Task.getProblem())
    {
      Task.getProblem()->print(&os);
      os << std::endl;
    }
  else
    os << "No Problem Specified!" << std::endl;

  if (Task.getMethod())
    {
      Task.getMethod()->print(&os);
      os << std::endl;
    }
  else
    os << "No Method Specified!" << std::endl;

  return os;
}

CCopasiTask::CResult::CResult(const CCopasiContainer * pParent):
  CCopasiObject("Result", pParent, "Object")
{}

CCopasiTask::CResult::CResult(const CCopasiTask::CResult & src,
                              const CCopasiContainer * pParent):
  CCopasiObject(src, pParent)
{}

CCopasiTask::CResult::~CResult() {}

void CCopasiTask::CResult::print(std::ostream * ostream) const
{*ostream << *this;}

std::ostream &operator<<(std::ostream &os,
                         const CCopasiTask::CResult & o)
{
  const CCopasiTask & Task = *static_cast<const CCopasiTask *>(o.getObjectParent());

  os << Task.getObjectName() << " Result:" << std::endl << std::endl;

  if (Task.getProblem())
    {
      Task.getProblem()->printResult(&os);
      os << std::endl;
    }
  else
    os << "No Problem Specified!" << std::endl;

  return os;
}
