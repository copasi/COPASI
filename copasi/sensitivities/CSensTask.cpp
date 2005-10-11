/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sensitivities/CSensTask.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/10/11 16:21:49 $
   End CVS Header */

/**
 * CSensTask class.
 *
 */

#include "copasi.h"

#include "CSensTask.h"
#include "CSensProblem.h"
#include "CSensMethod.h"
#include "model/CModel.h"
#include "model/CState.h" 
//#include "model/CMetabNameInterface.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"

#define XXXX_Reporting

CSensTask::CSensTask(const CCopasiContainer * pParent):
    CCopasiTask(CCopasiTask::sens, pParent)
{
  mpProblem = new CSensProblem(this);
  mpMethod = CSensMethod::createSensMethod(CCopasiMethod::sensMethod);
  this->add(mpMethod, true);
  //mpMethod->setObjectParent(this);
  //((CSteadyStateMethod *) mpMethod)->setProblem((CSteadyStateProblem *) mpProblem);
}

CSensTask::CSensTask(const CSensTask & src,
                     const CCopasiContainer * pParent):
    CCopasiTask(src, pParent)
{
  mpProblem =
    new CSensProblem(* (CSensProblem *) src.mpProblem, this);
  mpMethod =
    CSensMethod::createSensMethod(src.mpMethod->getSubType());
  this->add(mpMethod, true);
  //mpMethod->setObjectParent(this);
  //((CSteadyStateMethod *) mpMethod)->setProblem((CSteadyStateProblem *) mpProblem);
}

CSensTask::~CSensTask()
{}

void CSensTask::cleanup()
{}

void CSensTask::print(std::ostream * ostream) const {(*ostream) << (*this);}

bool CSensTask::initialize(const OutputFlag & of, std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  CSensProblem* pProblem =
    dynamic_cast<CSensProblem *>(mpProblem);
  assert(pProblem);

  bool success = true;

  if (CCopasiTask::initialize(of, pOstream)) success = false;

  if (!pProblem->getModel()->compileIfNecessary()) success = false;
  //pProblem->setInitialState(pProblem->getModel()->getInitialState());

  return success;
}

bool CSensTask::process(const bool & /* useInitialValues */)
{
  assert(/*mpProblem && */mpMethod);
  mpMethod->isValidProblem(mpProblem);

  CSensProblem* pProblem =
    dynamic_cast<CSensProblem *>(mpProblem);
  assert(pProblem);

  CSensMethod* pMethod =
    dynamic_cast<CSensMethod *>(mpMethod);
  assert(pMethod);

  mReport.printHeader();

  bool success = pMethod->process(mpCallBack);

  mReport.printBody();
  mReport.printFooter();

  return (success);
}

std::ostream &operator<<(std::ostream &os, const CSensTask &A)
{
  return os;
}
