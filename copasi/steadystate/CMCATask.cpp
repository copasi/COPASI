/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CMCATask.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/03/03 10:38:14 $
   End CVS Header */

/**
 * CMCATask class.
 *
 * This class implements a metabolic control analysis task which is comprised of a
 * problem and a method. Additionally calls to the reporting 
 * methods are done when initialized.
 *  
 * Created for Copasi by Ralph Gauges 2004
 */

#include "copasi.h"

#include "CMCATask.h"
#include "CMCAProblem.h"
#include "CMCAMethod.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"

#define XXXX_Reporting

CMCATask::CMCATask(const CCopasiContainer * pParent):
    CCopasiTask(CCopasiTask::mca, pParent)
{
  mpProblem = new CMCAProblem(this);
  mpMethod = new CMCAMethod(this);
}

CMCATask::CMCATask(const CMCATask & src,
                   const CCopasiContainer * pParent):
    CCopasiTask(src, pParent)
{
  mpProblem =
    new CMCAProblem(* (CMCAProblem *) src.mpProblem, this);
  mpMethod = new CMCAMethod(this);
}

CMCATask::~CMCATask()
{}

void CMCATask::cleanup()
{}

void CMCATask::load(CReadConfig & configBuffer)
{
  configBuffer.getVariable("MCA", "bool", &mScheduled,
                           CReadConfig::LOOP);

  ((CMCAProblem *) mpProblem)->load(configBuffer);

  ((CMCAMethod *) mpMethod)->load(configBuffer);
}

bool CMCATask::initialize(std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  CMCAProblem* pProblem =
    dynamic_cast<CMCAProblem *>(mpProblem);
  assert(pProblem);

  bool success = true;

  if (!mReport.open(pOstream)) success = false;
  if (!mReport.compile()) success = false;
  if (!pProblem->getModel()->compileIfNecessary()) success = false;

  return success;
}

bool CMCATask::process()
{
  assert(mpProblem && mpMethod);

  CMCAProblem* pProblem =
    dynamic_cast<CMCAProblem *>(mpProblem);
  assert(pProblem);

  CMCAMethod* pMethod =
    dynamic_cast<CMCAMethod *>(mpMethod);
  assert(pMethod);

  pMethod->setModel(pProblem->getModel());

  mReport.printHeader();
  pMethod->process();

  mReport.printBody();
  mReport.printFooter();

  return 0;
}

std::ostream &operator<<(std::ostream &os, const CMCATask & C_UNUSED(A))
{
  os << std::endl;

  os << std::endl;

  return os;
}
