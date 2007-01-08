/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiTask.cpp,v $
   $Revision: 1.53 $
   $Name:  $
   $Author: ssahle $
   $Date: 2007/01/08 14:45:39 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CCopasiTask class.
 *  This class is used to describe a task in COPASI. This class is
 *  intended to be used as the parent class for all tasks whithin COPASI.
 *
 *  Created for Copasi by Stefan Hoops 2003
 */

#include "copasi.h"

#include "CCopasiTask.h"
#include "CCopasiProblem.h"
#include "CCopasiMethod.h"
#include "report/CReport.h"
#include "report/CKeyFactory.h"
#include "utilities/COutputHandler.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "report/CCopasiObjectReference.h"
#include "CopasiDataModel/CCopasiDataModel.h"

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
#ifdef COPASI_DEBUG
    "Time Scale Separation",
#endif // COPASI_DEBUG
    "Sensitivities",
#ifdef COPASI_SSA
    "Stoichiometric Stability Analysis",
#endif // COPASI_SSA
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
#ifdef COPASI_DEBUG
    "timeScaleSeparation",
#endif // COPASI_DEBUG
    "sensitivities",
#ifdef COPASI_SSA
    "stoichiometricStabilityAnalysis",
#endif // COPASI_SSA
    NULL
  };

const unsigned C_INT32 CCopasiTask::ValidMethods[] =
  {
    CCopasiMethod::unset
  };

bool CCopasiTask::isValidMethod(const unsigned C_INT32 & method,
                                const unsigned C_INT32 * validMethods)
{
  unsigned C_INT32 i;
  for (i = 0; validMethods[i] != CCopasiMethod::unset; i++)
    if (method == validMethods[i]) return true;

  return false;
}

//static
CCopasiTask::Type CCopasiTask::XMLNameToEnum(const char * xmlTypeName)
{
  unsigned C_INT32 i = 0;
  while (XMLType[i] && strcmp(xmlTypeName, XMLType[i])) i++;

  if (XMLType[i]) return (CCopasiTask::Type) i;
  else return CCopasiTask::unset;
}

CCopasiTask::CCopasiTask(const std::string & name,
                         const CCopasiContainer * pParent,
                         const std::string & type):
    CCopasiContainer(name, pParent, type),
    mType(CCopasiTask::unset),
    mKey(GlobalKeys.add("Task", this)),
    mDescription(this),
    mResult(this),
    mScheduled(false),
    mUpdateModel(false),
    mpInitialState(NULL),
    mpProblem(NULL),
    mpMethod(NULL),
    mReport(),
    mpCallBack(NULL),
    mpSliders(NULL),
    mDoOutput(OUTPUT_COMPLETE),
    mOutputCounter(0)
{initObjects();}

CCopasiTask::CCopasiTask(const CCopasiTask::Type & taskType,
                         const CCopasiContainer * pParent,
                         const std::string & type):
    CCopasiContainer(CCopasiTask::TypeName[taskType], pParent, type),
    mType(taskType),
    mKey(GlobalKeys.add("Task", this)),
    mDescription(this),
    mResult(this),
    mScheduled(false),
    mUpdateModel(false),
    mpInitialState(NULL),
    mpProblem(NULL),
    mpMethod(NULL),
    mReport(),
    mpCallBack(NULL),
    mpSliders(NULL),
    mDoOutput(OUTPUT_COMPLETE),
    mOutputCounter(0)
{initObjects();}

CCopasiTask::CCopasiTask(const CCopasiTask & src,
                         const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mType(src.mType),
    mKey(GlobalKeys.add("Task", this)),
    mDescription(src.mDescription, this),
    mResult(src.mResult, this),
    mScheduled(src.mScheduled),
    mUpdateModel(src.mUpdateModel),
    mpInitialState(src.mpInitialState ? new CState(*src.mpInitialState) : NULL),
    mpProblem(NULL),
    mpMethod(NULL),
    mReport(src.mReport),
    mpCallBack(NULL),
    mpSliders(NULL),
    mDoOutput(OUTPUT_COMPLETE),
    mOutputCounter(0)
{initObjects();}

CCopasiTask::~CCopasiTask()
{
  GlobalKeys.remove(mKey);

  pdelete(mpInitialState);
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

bool CCopasiTask::setCallBack(CProcessReport * pCallBack)
{
  mpCallBack = pCallBack;
  return true;
}

CProcessReport * CCopasiTask::getCallBack() const
  {
    return mpCallBack;
  }

bool CCopasiTask::initialize(const OutputFlag & of,
                             std::ostream * pOstream)
{
  bool success = true;

  if (!mpProblem)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCCopasiTask + 1, getObjectName().c_str());
      return false;
    }
  if (!mpProblem->getModel())
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCCopasiTask + 2, getObjectName().c_str());
      return false;
    }
  if (!mpMethod)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCCopasiTask + 3, getObjectName().c_str());
      return false;
    }

  if (!mpProblem->getModel()->compileIfNecessary())
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCCopasiTask + 4, mpProblem->getModel()->getObjectName().c_str());
      return false;
    }

  if (!mUpdateModel)
    {
      pdelete(mpInitialState);
      mpInitialState = new CState(mpProblem->getModel()->getInitialState());
    }

  mDoOutput = of;
  if (mDoOutput == NO_OUTPUT) return true;

  mOutputCounter = 0;

  if (mReport.open(pOstream))
    CCopasiDataModel::Global->addInterface(&mReport);
  else
    CCopasiMessage(CCopasiMessage::COMMANDLINE, MCCopasiTask + 5);

  std::vector< CCopasiContainer * > ListOfContainer;
  ListOfContainer.push_back(this);

  if (!CCopasiDataModel::Global->compile(ListOfContainer))
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
  //mReport.close();
  setCallBack(NULL);

  if (!mUpdateModel)
    {
      if (mpInitialState)
        mpProblem->getModel()->setInitialState(*mpInitialState);
    }

  mpProblem->restore(mUpdateModel);

  return true;
}

CCopasiProblem * CCopasiTask::getProblem() {return mpProblem;}

const CCopasiProblem * CCopasiTask::getProblem() const {return mpProblem;}

bool CCopasiTask::setMethodType(const int & C_UNUSED(type))
{return false;}

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
  switch (activity)
    {
    case COutputInterface::DURING:
        if (mDoOutput != NO_OUTPUT)
          CCopasiDataModel::Global->output(activity);
      break;

    case COutputInterface::BEFORE:
    case COutputInterface::AFTER:
      if (mDoOutput == OUTPUT_COMPLETE)
        CCopasiDataModel::Global->output(activity);
      break;
    }
}

void CCopasiTask::separate(const COutputInterface::Activity & activity)
{
  switch (activity)
    {
    case COutputInterface::DURING:
      if (mDoOutput)
        CCopasiDataModel::Global->separate(activity);
      break;

    case COutputInterface::BEFORE:
    case COutputInterface::AFTER:
      if (mDoOutput == OUTPUT_COMPLETE)
        CCopasiDataModel::Global->separate(activity);
      break;
    }
}

void CCopasiTask::initObjects()
{
  addObjectReference("Output counter", mOutputCounter, CCopasiObject::ValueInt);
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
