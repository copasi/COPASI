// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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
 *  CCopasiTask class.
 *  This class is used to describe a task in COPASI. This class is
 *  intended to be used as the parent class for all tasks within COPASI.
 *
 *  Created for COPASI by Stefan Hoops 2003
 */

#include "copasi/copasi.h"

#include "copasi/utilities/CCopasiTask.h"
#include "copasi/utilities/CCopasiProblem.h"
#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/utilities/CTaskFactory.h"
#include "copasi/utilities/CProblemFactory.h"
#include "copasi/utilities/CMethodFactory.h"
#include "copasi/report/CReport.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/output/COutputHandler.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CState.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/core/CDataTimer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/report/CReportDefinition.h"

// static
CCopasiTask * CCopasiTask::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  CCopasiTask * pNew = CTaskFactory::create(CTaskEnum::TaskName.toEnum(data.getProperty(CData::TASK_TYPE).toString()), NO_PARENT);

  if (pNew != NULL)
    {
      pNew->setObjectName(data.getProperty(CData::OBJECT_NAME).toString());
    }

  return pNew;
}

// virtual
CData CCopasiTask::toData() const
{
  CData Data = CDataContainer::toData();

  Data.addProperty(CData::TASK_TYPE, CTaskEnum::TaskName[mType]);
  Data.addProperty(CData::TASK_SCHEDULED, mScheduled);
  Data.addProperty(CData::TASK_UPDATE_MODEL, mUpdateModel);
  Data.addProperty(CData::TASK_REPORT, mReport.getReportDefinition() != NULL ? mReport.getReportDefinition()->getCN() : CCommonName());
  Data.addProperty(CData::TASK_REPORT_TARGET, mReport.getTarget());
  Data.addProperty(CData::TASK_REPORT_APPEND, mReport.append());
  Data.addProperty(CData::TASK_REPORT_CONFIRM_OVERWRITE, mReport.confirmOverwrite());

  if (!mIgnoreProblemData)
    Data.addProperty(CData::PROBLEM, mpProblem != NULL ? mpProblem->toData() : CData());

  Data.addProperty(CData::METHOD_TYPE, CTaskEnum::MethodName[mpMethod != NULL ? mpMethod->getSubType()  : CTaskEnum::Method::UnsetMethod]);
  Data.addProperty(CData::METHOD, mpMethod != NULL ? mpMethod->toData() : CData());

  return Data;
}

// virtual
bool CCopasiTask::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = CDataContainer::applyData(data, changes);

  // The task type must not be changed
  if (data.isSetProperty(CData::TASK_TYPE) &&
      data.getProperty(CData::TASK_TYPE).toString() != CTaskEnum::TaskName[mType])
    {
      fatalError();
    }

  if (data.isSetProperty(CData::TASK_SCHEDULED))
    {
      mScheduled =  data.getProperty(CData::TASK_SCHEDULED).toBool();
    }

  if (data.isSetProperty(CData::TASK_UPDATE_MODEL))
    {
      mUpdateModel = data.getProperty(CData::TASK_UPDATE_MODEL).toBool();
    }

  if (data.isSetProperty(CData::TASK_REPORT))
    {
      const CReportDefinition * pReportDefinition = dynamic_cast< const CReportDefinition * >(getObjectFromCN(data.getProperty(CData::TASK_REPORT).toString()));
      mReport.setReportDefinition(pReportDefinition);
    }

  if (data.isSetProperty(CData::TASK_REPORT_TARGET))
    {
      mReport.setTarget(data.getProperty(CData::TASK_REPORT_TARGET).toString());
    }

  if (data.isSetProperty(CData::TASK_REPORT_APPEND))
    {
      mReport.setAppend(data.getProperty(CData::TASK_REPORT_APPEND).toBool());
    }

  if (data.isSetProperty(CData::TASK_REPORT_CONFIRM_OVERWRITE))
    {
      mReport.setConfirmOverwrite(data.getProperty(CData::TASK_REPORT_CONFIRM_OVERWRITE).toBool());
    }

  if (data.isSetProperty(CData::PROBLEM) && mpProblem != NULL)
    {
      mpProblem->applyData(data.getProperty(CData::PROBLEM).toData(), changes);
    }

  if (data.isSetProperty(CData::METHOD_TYPE) &&
      (mpMethod == NULL ||
       data.getProperty(CData::METHOD_TYPE).toString() != CTaskEnum::MethodName[mpMethod->getSubType()]))
    {
      setMethodType(CTaskEnum::MethodName.toEnum(data.getProperty(CData::METHOD_TYPE).toString()));
    }

  if (data.isSetProperty(CData::METHOD))
    {
      mpMethod->applyData(data.getProperty(CData::METHOD).toData(), changes);
    }

  return success;
}

// virtual
void CCopasiTask::createUndoData(CUndoData & undoData,
                                 const CUndoData::Type & type,
                                 const CData & oldData,
                                 const CCore::Framework & framework) const
{
  CDataContainer::createUndoData(undoData, type, oldData, framework);

  if (type != CUndoData::Type::CHANGE)
    {
      return;
    }

  undoData.addProperty(CData::TASK_TYPE, oldData.getProperty(CData::TASK_TYPE), CTaskEnum::TaskName[mType]);
  undoData.addProperty(CData::TASK_SCHEDULED, oldData.getProperty(CData::TASK_SCHEDULED), mScheduled);
  undoData.addProperty(CData::TASK_UPDATE_MODEL, oldData.getProperty(CData::TASK_UPDATE_MODEL), mUpdateModel);
  undoData.addProperty(CData::TASK_REPORT, oldData.getProperty(CData::TASK_REPORT), mReport.getReportDefinition() != NULL ? mReport.getReportDefinition()->getCN() : CCommonName());
  undoData.addProperty(CData::TASK_REPORT_TARGET, oldData.getProperty(CData::TASK_REPORT_TARGET), mReport.getTarget());
  undoData.addProperty(CData::TASK_REPORT_APPEND, oldData.getProperty(CData::TASK_REPORT_APPEND), mReport.append());
  undoData.addProperty(CData::TASK_REPORT_CONFIRM_OVERWRITE, oldData.getProperty(CData::TASK_REPORT_CONFIRM_OVERWRITE), mReport.confirmOverwrite());

  if (!mIgnoreProblemData)
    {
      if (mpProblem != NULL)
        {
          CUndoData UndoData;
          mpProblem->createUndoData(UndoData, type, oldData.getProperty(CData::PROBLEM).toData(), framework);
          undoData.addProperty(CData::PROBLEM, UndoData.getOldData(), UndoData.getNewData());
        }
      else
        {
          undoData.addProperty(CData::PROBLEM, oldData.getProperty(CData::PROBLEM), CData());
        }
    }

  undoData.addProperty(CData::METHOD_TYPE, oldData.getProperty(CData::METHOD_TYPE), CTaskEnum::MethodName[mpMethod != NULL ? mpMethod->getSubType() : CTaskEnum::Method::UnsetMethod]);

  if (mpMethod != NULL)
    {
      if (undoData.isChangedProperty(CData::METHOD_TYPE))
        {
          // Method data needs to be put into pre and post processing data as we have a simultaneous remove and insert of methods
          CUndoData MethodUndoData;
          CCopasiMethod * pTmpMethod = CMethodFactory::create(getType(), CTaskEnum::MethodName.toEnum(oldData.getProperty(CData::METHOD_TYPE).toString()), this);
          pTmpMethod->createUndoData(MethodUndoData, CUndoData::Type::CHANGE, oldData.getProperty(CData::METHOD).toData(), CCore::Framework::ParticleNumbers);
          undoData.addPreProcessData(MethodUndoData);
          delete pTmpMethod;

          MethodUndoData.clear();
          pTmpMethod = CMethodFactory::create(getType(), mpMethod->getSubType(), this);
          mpMethod->createUndoData(MethodUndoData, CUndoData::Type::CHANGE, pTmpMethod->toData(), CCore::Framework::ParticleNumbers);
          undoData.addPostProcessData(MethodUndoData);
          delete pTmpMethod;
        }
      else
        {
          // Method data can be added directly
          CUndoData MethodUndoData;
          mpMethod->createUndoData(MethodUndoData, CUndoData::Type::CHANGE, oldData.getProperty(CData::METHOD).toData(), CCore::Framework::ParticleNumbers);
          undoData.addProperty(CData::METHOD, MethodUndoData.getOldData(), MethodUndoData.getNewData());
        }
    }
  else
    {
      undoData.addProperty(CData::METHOD, oldData.getProperty(CData::METHOD), CData());
    }

  return;
}

bool CCopasiTask::isValidMethod(const CTaskEnum::Method & method,
                                const CTaskEnum::Method * validMethods)
{
  unsigned C_INT32 i;

  for (i = 0; validMethods[i] != CTaskEnum::Method::UnsetMethod; i++)
    if (method == validMethods[i]) return true;

  return false;
}

CCopasiTask::CCopasiTask()
  : CDataContainer(CTaskEnum::TaskName[CTaskEnum::Task::UnsetTask], NULL, "Task")
  , mType(CTaskEnum::Task::UnsetTask)
  , mKey(CRootContainer::getKeyFactory()->add("Task", this))
  , mDescription(this)
  , mResult(this)
  , mScheduled(false)
  , mUpdateModel(false)
  , mIgnoreProblemData(false)
  , mpProblem(NULL)
  , mpMethod(NULL)
  , mReport()
  , mInitialState()
  , mpContainer(NULL)
  , mProcessReport()
  , mpSliders(NULL)
  , mDoOutput(OUTPUT_SE)
  , mpOutputHandler(NULL)
  , mOutputCounter(0)
{
  initObjects();
}

CCopasiTask::CCopasiTask(const CDataContainer * pParent,
                         const CTaskEnum::Task & taskType,
                         const std::string & type)
  : CDataContainer(CTaskEnum::TaskName[taskType], pParent, type)
  , mType(taskType)
  , mKey(CRootContainer::getKeyFactory()->add("Task", this))
  , mDescription(this)
  , mResult(this)
  , mScheduled(false)
  , mUpdateModel(false)
  , mIgnoreProblemData(false)
  , mpProblem(NULL)
  , mpMethod(NULL)
  , mReport()
  , mpContainer(NULL)
  , mInitialState()
  , mProcessReport()
  , mpSliders(NULL)
  , mDoOutput(OUTPUT_SE)
  , mpOutputHandler(NULL)
  , mOutputCounter(0)
{
  mpProblem = CProblemFactory::create(taskType, this);

  initObjects();
}

CCopasiTask::CCopasiTask(const CCopasiTask & src,
                         const CDataContainer * pParent)
  : CDataContainer(src, pParent)
  , mType(src.mType)
  , mKey(CRootContainer::getKeyFactory()->add("Task", this))
  , mDescription(src.mDescription, this)
  , mResult(src.mResult, this)
  , mScheduled(src.mScheduled)
  , mUpdateModel(src.mUpdateModel)
  , mIgnoreProblemData(src.mIgnoreProblemData)
  , mpProblem(NULL)
  , mpMethod(NULL)
  , mReport(src.mReport)
  , mpContainer(src.mpContainer)
  , mInitialState(src.mInitialState)
  , mProcessReport()
  , mpSliders(NULL)
  , mDoOutput(src.mDoOutput)
  , mpOutputHandler(NULL)
  , mOutputCounter(0)
{
  mpProblem = CProblemFactory::copy(src.mpProblem, this);
  mpMethod = CMethodFactory::copy(src.mpMethod, this);

  initObjects();
}

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

CTaskEnum::Task CCopasiTask::getType() const
{
  return mType;
}

void CCopasiTask::setType(const CTaskEnum::Task & type)
{
  mType = type;
}

const std::string & CCopasiTask::getKey() const
{
  return mKey;
}

void CCopasiTask::setScheduled(const bool & scheduled)
{
  mScheduled = scheduled;
}

const bool & CCopasiTask::isScheduled() const
{
  return mScheduled;
}

void CCopasiTask::setUpdateModel(const bool & updateModel)
{
  mUpdateModel = updateModel;
}

const bool & CCopasiTask::isUpdateModel() const
{
  return mUpdateModel;
}

void CCopasiTask::setIgnoreProblemData(const bool & ignoreProblemData)
{
  mIgnoreProblemData = ignoreProblemData;
}

void CCopasiTask::setMathContainer(CMathContainer * pContainer)
{
  mpContainer = pContainer;

  if (mpProblem != NULL)
    {
      mpProblem->setMathContainer(pContainer);
    }

  if (mpMethod != NULL)
    {
      mpMethod->setMathContainer(pContainer);
    }

  signalMathContainerChanged();
}

// virtual
void CCopasiTask::signalMathContainerChanged()
{}

CMathContainer * CCopasiTask::getMathContainer() const
{
  return mpContainer;
}

bool CCopasiTask::setCallBack(CProcessReportLevel callBack)
{
  if (!isTaskValid())
    return false;

  // We automatically increase the level

  mProcessReport = ++callBack;

  bool success = true;

  if (mpMethod != NULL)
    {
      success &= mpMethod->setCallBack(mProcessReport);
    }

  return success;
}

const CProcessReportLevel & CCopasiTask::getCallBack() const
{
  return mProcessReport;
}

void CCopasiTask::clearCallBack()
{
  setCallBack(CProcessReportLevel());
}

COutputHandler* CCopasiTask::getOutputHandler() const
{
  return mpOutputHandler;
}

bool CCopasiTask::isTaskValid() const
{
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

  std::set< CCopasiTask * > CalledTasks;
  std::string Message;
  CCopasiTask * pSubTask = const_cast< CCopasiTask * >(this);

  while (pSubTask != NULL && CalledTasks.find(pSubTask) == CalledTasks.end())
    {
      CalledTasks.insert(pSubTask);

      if (!Message.empty())
        Message += " -> ";

      Message += pSubTask->getObjectName();

      pSubTask = pSubTask->getProblem()->getSubTask();
    }

  if (CalledTasks.find(pSubTask) != CalledTasks.end())
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCCopasiTask + 9, pSubTask->getObjectName().c_str(), Message.c_str());
      return false;
    }

  return true;
}

bool CCopasiTask::initialize(const OutputFlag & of,
                             COutputHandler * pOutputHandler,
                             std::ostream * pOstream)
{
  if (!isTaskValid())
    return false;

  bool success = true;

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

bool CCopasiTask::restore(const bool & updateModel)
{
  setCallBack(NULL);

  if (mpContainer != NULL)
    {
      // Update all transient values known to COPASI
      mpContainer->updateSimulatedValues(false);
      mpContainer->updateTransientDataValues();
      mpContainer->pushAllTransientValues();

      if (updateModel
          && mUpdateModel
          && mpContainer->isStateValid())
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

  mpProblem->restore(updateModel && mUpdateModel);

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
  if (!isValidMethod(type, getValidMethods())) return false;

  if (mpMethod->getSubType() == type) return true;

  pdelete(mpMethod);
  mpMethod = CMethodFactory::create(getType(), type, this);

  signalMethodChanged();

  return true;
}

// virtual
void CCopasiTask::signalMethodChanged()
{}

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
