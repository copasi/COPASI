/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiTask.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/26 21:17:57 $
   End CVS Header */

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

const std::string CCopasiTask::TypeName[] =
  {
    "Stead-State",
    "Time-Course",
    "Scan",
    "Elementary Flux Modes",
    "Optimization",
    "Parameter Fitting",
    ""
  };

const char* CCopasiTask::XMLType[] =
  {
    "SteadyState",
    "TimeCourse",
    "Scan",
    "FluxMode",
    "Optimization",
    "ParameterFitting",
    NULL
  };

CCopasiTask::CCopasiTask():
    CCopasiContainer("NoName", NULL, "Task"),
    mType(CCopasiTask::unset),
    mKey(CKeyFactory::add("Task", this)),
    mScheduled(false),
    mpProblem(NULL),
    mpMethod(NULL),
    mReport()
{}

CCopasiTask::CCopasiTask(const CCopasiTask::Type & taskType,
                         const CCopasiContainer * pParent,
                         const std::string & type):
    CCopasiContainer(CCopasiTask::TypeName[taskType], pParent, type),
    mType(taskType),
    mKey(CKeyFactory::add("Task", this)),
    mScheduled(false),
    mpProblem(NULL),
    mpMethod(NULL),
    mReport()
{}

CCopasiTask::CCopasiTask(const CCopasiTask & src,
                         const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mType(src.mType),
    mKey(CKeyFactory::add("Task", this)),
    mScheduled(src.mScheduled),
    mpProblem(NULL),
    mpMethod(NULL),
    mReport(src.mReport)
{}

CCopasiTask::~CCopasiTask()
{
  CKeyFactory::remove(mKey);
  pdelete(mpProblem);
  pdelete(mpMethod);
}

const std::string & CCopasiTask::getName() const
  {return getObjectName();}

bool CCopasiTask::setName(const std::string & name)
{return setObjectName(name);}

CCopasiTask::Type CCopasiTask::getType() const {return mType;}

void CCopasiTask::setType(const CCopasiTask::Type & type) {mType = type;}

std::string CCopasiTask::getKey() const {return mKey;}

void CCopasiTask::setScheduled(const bool & scheduled) {mScheduled = scheduled;}

const bool & CCopasiTask::isScheduled() const {return mScheduled;}

bool CCopasiTask::initialize(std::ostream * C_UNUSED(pOstream)) {return true;}

bool CCopasiTask::process() {return true;}

bool CCopasiTask::restore() {return true;}

CCopasiProblem * CCopasiTask::getProblem() {return mpProblem;}

bool CCopasiTask::setMethodType(const int & C_UNUSED(type))
{return false;}

CCopasiMethod * CCopasiTask::getMethod() {return mpMethod;}

CReport & CCopasiTask::getReport() {return mReport;}
