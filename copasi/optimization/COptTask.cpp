/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptTask.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: chlee $ 
   $Date: 2005/01/24 16:11:29 $
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
#include "utilities/CGlobals.h" 
//#include "utilities/CReadConfig.h"
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

bool COptTask::initialize(std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);
  COptProblem* pProblem =
    dynamic_cast<COptProblem *>(mpProblem);

  bool success = true;

  if (!mReport.open(pOstream)) success = false;
  if (!mReport.compile()) success = false;
  if (!pProblem->getModel()->compileIfNecessary()) success = false;

  return success;
}

/*void COptTask::load(CReadConfig & configBuffer)
{
  COptProblem* pProblem =
    dynamic_cast<COptProblem *>(mpProblem);
  assert(pProblem);
 
  //pProblem->load(configBuffer);
}*/

bool COptTask::process()
{
  /*if (!mpProblem)
    fatalError();
  if (!mpMethod)
    fatalError();*/
  assert(mpProblem && mpMethod);

  bool success = true;

  COptProblem * pProblem = (COptProblem *) mpProblem;
  COptMethod * pMethod = (COptMethod *) mpMethod;

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
