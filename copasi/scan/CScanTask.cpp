/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanTask.cpp,v $
   $Revision: 1.28 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/30 17:59:01 $
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
#include "utilities/readwrite.h"
#include "output/COutputEvent.h"
#include "output/COutputList.h"
#include "output/COutput.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"

#include "model/CModel.h"
#include "model/CState.h"

#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"

CScanTask::CScanTask():
    CCopasiContainer("ScanTask", NULL, "ScanTask", CCopasiObject::Container),
    mReport(new CReport()),
    mRequested(true),
    mpProblem(new CScanProblem),
    mpMethod(CScanMethod::createMethod()),
    mpOutEnd(NULL),
    mKey(CKeyFactory::add("ScanTask", this))
{}

CScanTask::CScanTask(const CScanTask & src):
    CCopasiContainer("ScanTask", NULL, "ScanTask", CCopasiObject::Container),
    mReport(new CReport()),
    mRequested(src.mRequested),
    mpProblem(new CScanProblem(*src.mpProblem)),
    mpMethod(new CScanMethod(*src.mpMethod)),
    mpOutEnd(src.mpOutEnd),
    mKey(CKeyFactory::add("ScanTask", this))
{}

CScanTask::~CScanTask()
{cleanup();}

void CScanTask::cleanup()
{
  CKeyFactory::remove(mKey);
  pdelete(mpProblem);
  pdelete(mpMethod);
  pdelete(mpOutEnd);
  pdelete(mReport);
}

void CScanTask::initializeReporting(std::ostream & out)
{
  pdelete(mpOutEnd);
  mpOut = & out;
  // added by Liang for Scan Report
  mReport->setOutputStreamAddr(mpOut);
  mReport->compile();

  // for Steadystate Report
  if (mpProblem->ifSteadyStateTask())
    mpProblem->getSteadyStateTask()->initializeReporting(out);

  // for Trajectory Report
  if (mpProblem->ifTrajectoryTask())
    mpProblem->getTrajectoryTask()->initializeReporting(out);
}

void CScanTask::load(CReadConfig & configBuffer)
{
  mpProblem->load(configBuffer);
}

void CScanTask::setRequested(const bool & requested)
{mRequested = requested;}

bool CScanTask::isRequested() const {return mRequested;}

CScanProblem * CScanTask::getProblem()
{return mpProblem;}

void CScanTask::setProblem(CScanProblem * pProblem)
{mpProblem = pProblem;}

CScanMethod * CScanTask::getMethod()
{return mpMethod;}

void CScanTask::setMethod(CScanMethod * pMethod)
{mpMethod = pMethod;}

void CScanTask::process()
{
  if (!mpProblem)
    fatalError();
  if (!mpMethod)
    fatalError();

  mpMethod->setProblem(mpProblem);
  mpProblem->InitScan();

  mReport->compile();
  mReport->printHeader();

  if ((mpProblem->getSteadyStateTask() != NULL) && mpProblem->processSteadyState())
    {
      mpProblem->getSteadyStateTask()->getProblem()->getModel()->compile();
    }
  if ((mpProblem->getTrajectoryTask() != NULL) && mpProblem->processTrajectory())
    {
      mpProblem->getTrajectoryTask()->getProblem()->getModel()->compile();
    }

  unsigned C_INT32 scanDimension = mpProblem->getListSize();
  int i;
  // find the last master
  for (i = scanDimension - 1; i >= 0; i--)
    if (mpProblem->getScanItemParameter(i, "indp")) break;
  if (i >= 0)
    // execute many simulations
    mpMethod->scan(i, true, &CReport::printBody, mReport);

  //  if (mpOutEnd)
  //    mpOutEnd->print(*Copasi->pOutputList, *mpOut);
  mReport->printFooter();

  return;
}
