/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanTask.cpp,v $
   $Revision: 1.40 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/12/14 17:10:27 $
   End CVS Header */

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
#include "utilities/CGlobals.h"
#include "utilities/CReadConfig.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"

#include "model/CModel.h"
#include "model/CState.h"

#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"

CScanTask::CScanTask(const CCopasiContainer * pParent):
    CCopasiTask(CCopasiTask::scan, pParent)
{
  mpProblem = new CScanProblem(this);
  mpMethod = CScanMethod::createMethod();
  mpMethod->setObjectParent(this);
  ((CScanMethod *) mpMethod)->setProblem((CScanProblem *) mpProblem);
}

CScanTask::CScanTask(const CScanTask & src,
                     const CCopasiContainer * pParent):
    CCopasiTask(src, pParent)
{
  mpProblem = new CScanProblem(* (CScanProblem *) src.mpProblem, this);
  mpMethod = CScanMethod::createMethod();
  mpMethod->setObjectParent(this);
  ((CScanMethod *) mpMethod)->setProblem((CScanProblem *) mpProblem);
}

CScanTask::~CScanTask()
{cleanup();}

void CScanTask::cleanup()
{
  //pdelete(mpProblem);
  //pdelete(mpMethod);
  //  pdelete(mpOutEnd);
  //-pdelete(mReport);
}

void CScanTask::initializeReporting(std::ostream & out)
{
  //  pdelete(mpOutEnd);
  mpOut = & out;
  // added by Liang for Scan Report
  mReport.open(mpOut);
  mReport.compile();

  CScanProblem* pProblem =
    dynamic_cast<CScanProblem *>(mpProblem);
  assert(pProblem);

  // for Steadystate Report
  if (pProblem->processSteadyState())
    pProblem->getSteadyStateTask()->initialize(mpOut);

  // for Trajectory Report
  if (pProblem->processTrajectory())
    pProblem->getTrajectoryTask()->initialize(mpOut);
}

void CScanTask::load(CReadConfig & configBuffer)
{
  CScanProblem* pProblem =
    dynamic_cast<CScanProblem *>(mpProblem);
  assert(pProblem);

  pProblem->load(configBuffer);
}

bool CScanTask::process()
{
  if (!mpProblem)
    fatalError();
  if (!mpMethod)
    fatalError();

  CScanProblem * pProblem = (CScanProblem *) mpProblem;
  CScanMethod * pMethod = (CScanMethod *) mpMethod;

  pMethod->setProblem(pProblem);
  pProblem->initialize();

  mReport.compile();
  mReport.printHeader();

  if ((pProblem->getSteadyStateTask() != NULL) && pProblem->processSteadyState())
    {
      pProblem->getSteadyStateTask()->getProblem()->getModel()->compileIfNecessary();
    }
  if ((pProblem->getTrajectoryTask() != NULL) && pProblem->processTrajectory())
    {
      pProblem->getTrajectoryTask()->getProblem()->getModel()->compileIfNecessary();
    }

  unsigned C_INT32 scanDimension = pProblem->getListSize();
  int i;

  // find the last master
  for (i = scanDimension - 1; i >= 0; i--)
    if (pProblem->getScanItemParameter(i, "indp")) break;

  if (i >= 0)
    // execute many simulations
    pMethod->scan(i, true, &CReport::printBody, &mReport);

  //  if (mpOutEnd)
  //    mpOutEnd->print(*Copasi->pOutputList, *mpOut);
  mReport.printFooter();

  pProblem->restore();
  return true;
}
