/**
 * CSteadyStateTask class.
 *
 * This class implements a steady state task which is comprised of a
 * of a problem and a method. Additionally calls to the reporting 
 * methods are done when initialized.
 *  
 * Created for Copasi by Stefan Hoops 2002
 */

#include "copasi.h"

#include "CSteadyStateTask.h"
#include "CSteadyStateProblem.h"
#include "CSteadyStateMethod.h"
#include "CEigen.h"

#include "output/output.h"
#include "model/CState.h"
#include "model/cmodel.h"
#include "utilities/CGlobals.h"

#define XXXX_Reporting

CSteadyStateTask::CSteadyStateTask():
    mpProblem(new CSteadyStateProblem),
    mpMethod(CSteadyStateMethod::createSteadyStateMethod()),
    mRequested(false),
    mpSteadyState(NULL),
    mpEigenValues(NULL),
    mpOutEnd(NULL)
{}

CSteadyStateTask::CSteadyStateTask(const CSteadyStateTask & src):
    mpProblem(src.mpProblem),
    mpMethod(src.mpMethod),
    mRequested(src.mRequested),
    mpSteadyState(src.mpSteadyState),
    mJacobian(src.mJacobian),
    mpEigenValues(src.mpEigenValues),
    mpOutEnd(src.mpOutEnd)
{}

CSteadyStateTask::~CSteadyStateTask()
{
  cleanup();
}

void CSteadyStateTask::cleanup()
{
  pdelete(mpProblem);
  pdelete(mpMethod);
  pdelete(mpSteadyState);
  pdelete(mpEigenValues);
  pdelete(mpOutEnd);
}

void CSteadyStateTask::initializeReporting(std::ofstream & out)
{
  pdelete(mpOutEnd);

  mpOut = & out;
  mpOutEnd = new COutputEvent(*this);
}

void CSteadyStateTask::load(CReadConfig & configBuffer)
{
  if (configBuffer.getVersion() < "4.0")
    configBuffer.getVariable("SteadyState", "bool", &mRequested,
                             CReadConfig::LOOP);
  else
    configBuffer.getVariable("RunSteadyState", "bool", &mRequested,
                             CReadConfig::LOOP);

  pdelete(mpProblem);
  mpProblem = new CSteadyStateProblem();
  mpProblem->load(configBuffer);

  pdelete(mpMethod);
  if (configBuffer.getVersion() < "4.0")
    {
      mpMethod = CSteadyStateMethod::createSteadyStateMethod();
    }
  else
    {
      C_INT32 Method;
      configBuffer.getVariable("SteadyStateMethod", "C_INT32", &Method,
                               CReadConfig::SEARCH);

      mpMethod = CSteadyStateMethod::
                 createSteadyStateMethod((CSteadyStateMethod::Type) Method);
    }

  mpMethod->load(configBuffer);
}

void CSteadyStateTask::save(CWriteConfig & configBuffer)
{
  configBuffer.setVariable("RunSteadyState", "bool", &mRequested);

  mpProblem->save(configBuffer);

  const C_INT32 Method = mpMethod->getTypeEnum();
  configBuffer.setVariable("SteadyStateMethod", "C_INT32", &Method);

  mpMethod->save(configBuffer);
}

CSteadyStateProblem * CSteadyStateTask::getProblem()
{return mpProblem;}

void CSteadyStateTask::setProblem(CSteadyStateProblem * pProblem)
{
  pdelete(mpProblem);
  mpProblem = pProblem;
}

CSteadyStateMethod * CSteadyStateTask::getMethod()
{return mpMethod;}

void CSteadyStateTask::setMethod(CSteadyStateMethod * pMethod)
{
  pdelete(mpMethod);
  mpMethod = pMethod;
}

void CSteadyStateTask::setRequested(const bool & requested)
{mRequested = requested;}

bool CSteadyStateTask::isRequested() const {return mRequested;}

CState * CSteadyStateTask::getState()
{return mpSteadyState;}

const CMatrix< C_FLOAT64 > & CSteadyStateTask::getJacobian() const
  {return mJacobian;}

const CEigen * CSteadyStateTask::getEigenValues()
{
  return mpEigenValues;
}

void CSteadyStateTask::process()
{
  if (!mpProblem)
    fatalError();
  if (!mpMethod)
    fatalError();

  pdelete(mpSteadyState);
  mpSteadyState = new CState(mpProblem->getInitialState());

  mJacobian.resize(mpSteadyState->getVariableNumberSize(),
                   mpSteadyState->getVariableNumberSize());

  pdelete(mpEigenValues);
  mpEigenValues = new CEigen();

  if (mpOutEnd)
    Copasi->pOutputList->compile("Steady-state output",
                                 mpProblem->getModel(),
                                 this);

  mpMethod->setProblem(mpProblem);

  mResult = mpMethod->process(*mpSteadyState,
                              mpProblem->getInitialState(),
                              mJacobian,
                              mpEigenValues);

  if (mpOutEnd)
    mpOutEnd->print(*this, *Copasi->pOutputList, *mpOut);

  return;
}

void CSteadyStateTask::setModel(CModel* mModel)
{
  if (mpProblem)
    mpProblem->setModel(mModel);
}
