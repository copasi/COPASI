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
#include "CTaskFactory.h"
#include "report/CReport.h"
#include "report/CKeyFactory.h"
#include "output/COutputHandler.h"
#include "math/CMathContainer.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "copasi/core/CDataObjectReference.h"
#include "core/CDataTimer.h"
#include "CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"

// static
CCopasiTask * CCopasiTask::fromData(const CData & data)
{
  CCopasiTask * pNew = CTaskFactory::createTask((CTaskEnum::Task)data.getProperty(CData::TASK_TYPE).toUint(), NO_PARENT);

  if (pNew != NULL)
    {
      pNew->setObjectName(data.getProperty(CData::OBJECT_NAME).toString());
    }

  return pNew;
}

// virtual
CData CCopasiTask::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CCopasiTask::applyData(const CData & data)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

bool CCopasiTask::isValidMethod(const CTaskEnum::Method & method,
                                const CTaskEnum::Method * validMethods)
{
  unsigned C_INT32 i;

  for (i = 0; validMethods[i] != CTaskEnum::Method::UnsetMethod; i++)
    if (method == validMethods[i]) return true;

  return false;
}

CCopasiTask::CCopasiTask():
  CDataContainer(CTaskEnum::TaskName[CTaskEnum::Task::UnsetTask], NULL, "Task"),
  mType(CTaskEnum::Task::UnsetTask),
  mKey(CRootContainer::getKeyFactory()->add("Task", this)),
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

CCopasiTask::CCopasiTask(const CDataContainer * pParent,
                         const CTaskEnum::Task & taskType,
                         const std::string & type):
  CDataContainer(CTaskEnum::TaskName[taskType], pParent, type),
  mType(taskType),
  mKey(CRootContainer::getKeyFactory()->add("Task", this)),
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
                         const CDataContainer * pParent):
  CDataContainer(src, pParent),
  mType(src.mType),
  mKey(CRootContainer::getKeyFactory()->add("Task", this)),
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
  CRootContainer::getKeyFactory()->remove(mKey);

  pdelete(mpProblem);
  pdelete(mpMethod);
  pdelete(mpSliders);
}

//const std::string & CCopasiTask::getName() const {return getObjectName();}

//bool CCopasiTask::setName(const std::string & name)
//{return setObjectName(name);}

CTaskEnum::Task CCopasiTask::getType() const {return mType;}

void CCopasiTask::setType(const CTaskEnum::Task & type) {mType = type;}

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
  if (mpMethod != NULL)
    {
      mpMethod->setCallBack(pCallBack);
    }

  mpCallBack = pCallBack;

  return true;
}

CProcessReport * CCopasiTask::getCallBack() const
{
  return mpCallBack;
}

void CCopasiTask::clearCallBack()
{
  setCallBack(NULL);
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

  if (mpContainer != NULL)
    {
      // Update all transient values known to COPASI
      mpContainer->updateSimulatedValues(false);
      mpContainer->updateTransientDataValues();
      mpContainer->pushAllTransientValues();

      if (mUpdateModel &&
          mpContainer->isStateValid())
        {
          mpContainer->updateSimulatedValues(false);
          mpContainer->setInitialState(mpContainer->getState(false));

          if (mpContainer->isAutonomous())
            {
              // Set the initial time to 0
              mpContainer->getInitialState()[mpContainer->getCountFixed() + mpContainer->getCountFixedEventTargets()] = 0;
            }
        }
      else
        {
          mpContainer->setInitialState(mInitialState);
        }

      mpContainer->updateInitialValues(CCore::Framework::ParticleNumbers);
      mpContainer->pushInitialState();
    }

  mpProblem->restore(mUpdateModel);

  return true;
}

// virtual
const CTaskEnum::Method * CCopasiTask::getValidMethods() const
{
  static const CTaskEnum::Method ValidMethods[] =
  {
    CTaskEnum::Method::UnsetMethod
  };

  return ValidMethods;
}

CCopasiProblem * CCopasiTask::getProblem() {return mpProblem;}

const CCopasiProblem * CCopasiTask::getProblem() const {return mpProblem;}

// virtual
bool CCopasiTask::setMethodType(const CTaskEnum::Method & type)
{
  CTaskEnum::Method Type = (CTaskEnum::Method) type;

  if (!isValidMethod(Type, getValidMethods())) return false;

  if (mpMethod->getSubType() == Type) return true;

  pdelete(mpMethod);
  mpMethod = createMethod(Type);

  signalMethodChanged();

  return true;
}

// virtual
void CCopasiTask::signalMethodChanged()
{}

CCopasiMethod * CCopasiTask::createMethod(const CTaskEnum::Method & type) const
{
  CCopasiMethod * pMethod = CCopasiMethod::createMethod(this, type, mType);
  const_cast< CCopasiTask * >(this)->add(pMethod, true);

  pMethod->setMathContainer(mpContainer);

  return pMethod;
}

CCopasiMethod * CCopasiTask::getMethod() {return mpMethod;}

const CCopasiMethod * CCopasiTask::getMethod() const {return mpMethod;}

CReport & CCopasiTask::getReport() {return mReport;}

const CReport & CCopasiTask::getReport() const {return mReport;}

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

        default: //any unspecified channel is just passed through
          mpOutputHandler->output(activity);
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
  addObjectReference("Output counter", mOutputCounter, CDataObject::ValueInt);
  new CCopasiTimer(CCopasiTimer::Type::WALL, this);
  new CCopasiTimer(CCopasiTimer::Type::PROCESS, this);

  CDataModel *pDataModel = getObjectDataModel();

  if (pDataModel != NULL)
    {
      if (pDataModel->getModel() != NULL)
        {
          setMathContainer(&pDataModel->getModel()->getMathContainer());
        }
    }
}

CCopasiTask::CDescription::CDescription(const CDataContainer * pParent):
  CDataObject("Description", pParent, "Object")
{}

CCopasiTask::CDescription::CDescription(const CCopasiTask::CDescription & src,
                                        const CDataContainer * pParent):
  CDataObject(src, pParent)
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

CCopasiTask::CResult::CResult(const CDataContainer * pParent):
  CDataObject("Result", pParent, "Object")
{}

CCopasiTask::CResult::CResult(const CCopasiTask::CResult & src,
                              const CDataContainer * pParent):
  CDataObject(src, pParent)
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
