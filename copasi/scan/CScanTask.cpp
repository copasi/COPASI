/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanTask.cpp,v $
   $Revision: 1.43 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/01/04 17:20:48 $
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
#include "utilities/COutputHandler.h"

CScanTask::CScanTask(const CCopasiContainer * pParent):
    CCopasiTask(CCopasiTask::scan, pParent)
{
  mpProblem = new CScanProblem(this);
  mpMethod = CScanMethod::createMethod();
  this->add(mpMethod, true);
  //  mpMethod->setObjectParent(this);
  ((CScanMethod *) mpMethod)->setProblem((CScanProblem *) mpProblem);
}

CScanTask::CScanTask(const CScanTask & src,
                     const CCopasiContainer * pParent):
    CCopasiTask(src, pParent)
{
  mpProblem = new CScanProblem(* (CScanProblem *) src.mpProblem, this);
  mpMethod = CScanMethod::createMethod();
  this->add(mpMethod, true);
  //  mpMethod->setObjectParent(this);
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

bool CScanTask::initialize(std::ostream * out)
{
  CScanProblem* pProblem =
    dynamic_cast<CScanProblem *>(mpProblem);

  bool success = true;

  if (!pProblem->getModel()->compileIfNecessary()) success = false;

  //  pdelete(mpOutEnd);
  //mpOut = & out;
  // added by Liang for Scan Report
  //mReport.open(mpOut);
  //mReport.compile();

  assert(pProblem);

  // for Steadystate Report
  //  if (pProblem->processSteadyState())
  //    pProblem->getSteadyStateTask()->initialize(mpOut);

  // for Trajectory Report
  //  if (pProblem->processTrajectory())
  //    pProblem->getTrajectoryTask()->initialize(mpOut);
  return success;
}

void CScanTask::load(CReadConfig & configBuffer)
{
  CScanProblem* pProblem =
    dynamic_cast<CScanProblem *>(mpProblem);
  assert(pProblem);

  //pProblem->load(configBuffer);
}

bool CScanTask::process()
{
  if (!mpProblem)
    fatalError();
  if (!mpMethod)
    fatalError();

  bool success = true;

  CScanProblem * pProblem = (CScanProblem *) mpProblem;
  CScanMethod * pMethod = (CScanMethod *) mpMethod;

  pMethod->setProblem(pProblem);

  //TODO: reports

  //initialize the method (parsing the ScanItems)
  if (!pMethod->init()) return false;

  //init progress bar
  mProgress = 0;
  if (mpProgressHandler) mpProgressHandler->init(pMethod->getTotalNumberOfSteps(), "performing parameter scan...", true);

  //init output handler (plotting)
  if (mpOutputHandler) mpOutputHandler->init();

  //calling the scanner, output is done in the callback
  if (!pMethod->scan()) success = false;

  //finishing progress bar and output
  if (mpProgressHandler) mpProgressHandler->finish();
  if (mpOutputHandler) mpOutputHandler->finish();

  //pProblem->initialize();

  //mReport.compile();
  //mReport.printHeader();

  /*  if ((pProblem->getSteadyStateTask() != NULL) && pProblem->processSteadyState())
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
   
    pProblem->restore();*/
  return success;
}

bool CScanTask::processCallback()
{
  //do tasks

  //do output
  if (mpOutputHandler) mpOutputHandler->doOutput();

  //do progress bar
  ++mProgress;
  if (mpProgressHandler) return !mpProgressHandler->progress(mProgress);

  return true;
}
