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
#include "utilities/CGlobals.h"

#define XXXX_Reporting

CSteadyStateTask::CSteadyStateTask():
    mpProblem(NULL),
    mpMethod(NULL),
    mpSteadyState(NULL),
    mJacobian(NULL),
    mpEigenValues(NULL),
    mpOutEnd(NULL)
{}

CSteadyStateTask::CSteadyStateTask(const CSteadyStateTask & src):
    mpProblem(src.mpProblem),
    mpMethod(src.mpMethod),
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
  pdelete(mJacobian);
  pdelete(mpEigenValues);
  pdelete(mpOutEnd);
}

void CSteadyStateTask::initializeReporting(ofstream & out)
{
  pdelete(mpOutEnd);

  mpOut = & out;
  mpOutEnd = new COutputEvent(*this);
}

void CSteadyStateTask::load(CReadConfig & configBuffer)
{
  pdelete(mpProblem);
  mpProblem = new CSteadyStateProblem();
  mpProblem->load(configBuffer);

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
      mpMethod->load(configBuffer);
    }
}

void CSteadyStateTask::save(CWriteConfig & configBuffer)
{
  mpProblem->save(configBuffer);

  const C_INT32 Method = mpMethod->getTypeEnum();
  configBuffer.setVariable("SteadyStateMethod", "C_INT32", &Method);

  mpMethod->save(configBuffer);
}

CSteadyStateProblem * CSteadyStateTask::getProblem()
{return mpProblem; }

void CSteadyStateTask::setProblem(CSteadyStateProblem * pProblem)
{mpProblem = pProblem; }

CSteadyStateMethod * CSteadyStateTask::getMethod()
{return mpMethod; }

void CSteadyStateTask::setMethod(CSteadyStateMethod * pMethod)
{mpMethod = pMethod; }

CState * CSteadyStateTask::getState()
{return mpSteadyState; }

const C_FLOAT64 * CSteadyStateTask::getJacobian()
{
  return mJacobian;
}

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
  mpSteadyState = new CState(*mpProblem->getInitialState());

  pdelete(mJacobian);
  mJacobian = new C_FLOAT64[mpSteadyState->getVariableNumberSize()];

  pdelete(mpEigenValues);
  mpEigenValues = new CEigen();

  if (mpOutEnd)
    Copasi->OutputList.compile("Steady-state output",
                               mpProblem->getModel(),
                               this);

  mpMethod->setProblem(mpProblem);

  mResult = mpMethod->process(*mpSteadyState,
                              *mpProblem->getInitialState(),
                              mJacobian,
                              mpEigenValues);
}
