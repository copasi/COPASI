/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptTask.cpp,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/08/30 15:40:18 $
   End CVS Header */

/**
 * COptTask class.
 *
 * This class implements a optimization task which is comprised of a
 * of a problem and a method.
 *  
 */
#include "copasi.h"

#include "COptTask.h"
#include "COptProblem.h"
#include "COptMethod.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"

#include "model/CModel.h"
#include "model/CState.h"

//#include "trajectory/CTrajectoryTask.h"
//#include "trajectory/CTrajectoryProblem.h"
//#include "steadystate/CSteadyStateTask.h"
//#include "steadystate/CSteadyStateProblem.h"
//#include "utilities/COutputHandler.h"

COptTask::COptTask(const CCopasiContainer * pParent):
    CCopasiTask(CCopasiTask::optimization, pParent)
{
  mpProblem = new COptProblem(this);
  mpMethod = COptMethod::createMethod();
  this->add(mpMethod, true);
  //  mpMethod->setObjectParent(this);
  ((COptMethod *) mpMethod)->setProblem((COptProblem *) mpProblem);
}

COptTask::COptTask(const COptTask & src,
                   const CCopasiContainer * pParent):
    CCopasiTask(src, pParent)
{
  mpProblem = new COptProblem(* (COptProblem *) src.mpProblem, this);
  mpMethod = COptMethod::createMethod();
  this->add(mpMethod, true);
  //  mpMethod->setObjectParent(this);
  ((COptMethod *) mpMethod)->setProblem((COptProblem *) mpProblem);
}

COptTask::~COptTask()
{cleanup();}

void COptTask::cleanup(){}

bool COptTask::setCallBack(CProcessReport * pCallBack)
{
  bool success = CCopasiTask::setCallBack(pCallBack);

  if (!mpProblem->setCallBack(pCallBack)) success = false;
  if (!mpMethod->setCallBack(pCallBack)) success = false;

  return success;
}

bool COptTask::initialize(const OutputFlag & of,
                          std::ostream * pOstream)
{
  COptProblem * pProblem = dynamic_cast<COptProblem *>(mpProblem);
  COptMethod * pMethod = dynamic_cast<COptMethod *>(mpMethod);

  if (!pProblem || !pMethod) return false;

  //initialize reporting
  bool success = true;

  if (!CCopasiTask::initialize(of, pOstream)) success = false;
  //if (!mReport.open(pOstream)) success = false;
  //if (!mReport.compile()) success = false;

  if (!pProblem->initialize()) return false;

  pMethod->setProblem(pProblem);
  //  if (!pMethod->initialize()) return false;

  return success;
}

bool COptTask::process(const bool & /* useInitialValues */)
{
  COptProblem * pProblem = dynamic_cast<COptProblem *>(mpProblem);
  COptMethod * pMethod = dynamic_cast<COptMethod *>(mpMethod);

  if (!pProblem || !pMethod) return false;

  mpMethod->isValidProblem(mpProblem);

  //bool Report = (mReport.getStream() != NULL);

  //if (Report) mReport.printHeader();
  initOutput();

  bool success = pMethod->optimise();

  //if (Report) mReport.printFooter();
  finishOutput();

  pProblem->restore();

  return success;
}

bool COptTask::setMethodType(const int & type)
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  //*************************** bellow commented *****
  // To get the following portions to work COptMethod needs to implement
  // isValidSubType method
  /*if (!COptMethod::isValidSubType(Type)) return false;*/
  if (mpMethod->getSubType() == Type) return true;

  pdelete (mpMethod);
  //****Current COptMethod only takes type parameter, modify as needed later on if
  //    want to add COptProblem parameter ***/
  /*mpMethod =
    COptMethod::createMethod(Type,(COptProblem *) mpProblem);*/
  mpMethod = COptMethod::createMethod(Type);
  this->add(mpMethod, true);
  //mpMethod->setObjectParent(this);

  return true;
}

COptTask::CallBack::CallBack(CProcessReport & parentCallBack):
    CProcessReport(),
    mParentCallBack(parentCallBack)
{}

COptTask::CallBack::~CallBack() {}

unsigned C_INT32 COptTask::CallBack::addItem(const std::string & name,
    const CCopasiParameter::Type & type,
    const void * pValue,
    const void * pEndValue)
{
  CProcessReport::addItem(name, type, pValue, pEndValue);
  return mParentCallBack.addItem(name, type, pValue, pEndValue);
}

bool COptTask::CallBack::progress(const unsigned C_INT32 & index)
{
  return mParentCallBack.progress(index);
}

bool COptTask::CallBack::reset(const unsigned C_INT32 & index)
{
  return mParentCallBack.reset(index);
}

bool COptTask::CallBack::finish(const unsigned C_INT32 & index)
{
  return mParentCallBack.finish(index);
}
