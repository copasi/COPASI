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
#include "utilities/readwrite.h"

CScanTask::CScanTask():
    mRequested(true),
    mpProblem(new CScanProblem),
    mpMethod(CScanMethod::createMethod()),
    mpOut(NULL)
{}

CScanTask::CScanTask(const CScanTask & src):
    mRequested(src.mRequested),
    mpProblem(new CScanProblem(*src.mpProblem)),
    mpMethod(new CScanMethod(*src.mpMethod)),
    mpOut(src.mpOut)
{}

CScanTask::~CScanTask()
{cleanup();}

void CScanTask::cleanup()
{
  pdelete(mpProblem);
  pdelete(mpMethod);
  pdelete(mpOut);
}

void CScanTask::initializeReporting(std::ostream & C_UNUSED(out))
{}

void CScanTask::load(CReadConfig & C_UNUSED(configBuffer))
{}

void CScanTask::save(CWriteConfig & C_UNUSED(configBuffer))
{}

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
  mpMethod->InitScan();
  unsigned C_INT32 scanDimension = mpProblem->getListSize();
  int i;
  // find the last master
  for (i = scanDimension - 1; i >= 0; i--)
    if (mpProblem->getScanItemParameter(i, "indp")) break;
  if (i >= 0)
    // execute many simulations
    mpMethod->scan(i, true);
  mpMethod->simulate();

  return;
}
