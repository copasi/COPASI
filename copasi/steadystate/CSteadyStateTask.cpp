/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CSteadyStateTask.cpp,v $
   $Revision: 1.35 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/10/04 09:39:27 $
   End CVS Header */

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
#include "model/CModel.h"
#include "model/CState.h"
#include "utilities/CGlobals.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"

#define XXXX_Reporting

CSteadyStateTask::CSteadyStateTask(const CCopasiContainer * pParent):
    CCopasiTask(CCopasiTask::steadyState, pParent),
    mpSteadyState(NULL),
    mpEigenValues(NULL)
{
  mpProblem = new CSteadyStateProblem(this);
  mpMethod =
    CSteadyStateMethod::createSteadyStateMethod(CCopasiMethod::Newton);
  mpMethod->setObjectParent(this);
  //((CSteadyStateMethod *) mpMethod)->setProblem((CSteadyStateProblem *) mpProblem);
}

CSteadyStateTask::CSteadyStateTask(const CSteadyStateTask & src,
                                   const CCopasiContainer * pParent):
    CCopasiTask(src, pParent),
    mpSteadyState(src.mpSteadyState),
    mJacobian(src.mJacobian),
    mpEigenValues(src.mpEigenValues)
{
  mpProblem =
    new CSteadyStateProblem(* (CSteadyStateProblem *) src.mpProblem, this);
  mpMethod =
    CSteadyStateMethod::createSteadyStateMethod(src.mpMethod->getSubType());
  mpMethod->setObjectParent(this);
  //((CSteadyStateMethod *) mpMethod)->setProblem((CSteadyStateProblem *) mpProblem);
}

CSteadyStateTask::~CSteadyStateTask()
{
  pdelete(mpSteadyState);
  pdelete(mpEigenValues);
}

void CSteadyStateTask::cleanup()
{}

void CSteadyStateTask::load(CReadConfig & configBuffer)
{
  configBuffer.getVariable("SteadyState", "bool", &mScheduled,
                           CReadConfig::LOOP);

  ((CSteadyStateProblem *) mpProblem)->load(configBuffer);

  ((CSteadyStateMethod *) mpMethod)->load(configBuffer);
}

//CState * CSteadyStateTask::getState()
//{return mpSteadyState;}

const CState * CSteadyStateTask::getState() const
  {return mpSteadyState;}

const CMatrix< C_FLOAT64 > & CSteadyStateTask::getJacobian() const
  {return mJacobian;}

const CEigen * CSteadyStateTask::getEigenValues() const
  {
    return mpEigenValues;
  }

bool CSteadyStateTask::initialize(std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  CSteadyStateProblem* pProblem =
    dynamic_cast<CSteadyStateProblem *>(mpProblem);
  assert(pProblem);

  bool success = true;

  if (!mReport.open(pOstream)) success = false;
  if (!mReport.compile()) success = false;
  if (!pProblem->getModel()->compileIfNecessary()) success = false;

  pdelete(mpSteadyState);
  mpSteadyState = new CState(pProblem->getInitialState());

  mJacobian.resize(mpSteadyState->getVariableNumberSize(),
                   mpSteadyState->getVariableNumberSize());

  pdelete(mpEigenValues);
  mpEigenValues = new CEigen();

  //pProblem->setInitialState(pProblem->getModel()->getInitialState());

  return success;
}

bool CSteadyStateTask::process()
{
  assert(mpProblem && mpMethod);

  CSteadyStateProblem* pProblem =
    dynamic_cast<CSteadyStateProblem *>(mpProblem);
  assert(pProblem);

  CSteadyStateMethod* pMethod =
    dynamic_cast<CSteadyStateMethod *>(mpMethod);
  assert(pMethod);

  mReport.printHeader();

  mResult = pMethod->process(mpSteadyState,
                             pProblem,
                             mJacobian,
                             mpEigenValues);

  mReport.printBody();
  mReport.printFooter();

  return (mResult != CSteadyStateMethod::notFound);
}

std::ostream &operator<<(std::ostream &os, const CSteadyStateTask &A)
{
  os << std::endl;

  if (A.mResult == CSteadyStateMethod::notFound)
    {
      os << "A STEADY STATE COULD NOT BE FOUND." << std::endl;
      os << "(below are the last unsuccessful trial values)";
    }
  else
    {
      os << "STEADY STATE SOLUTION";

      if (A.mResult == CSteadyStateMethod::foundEquilibrium)
        os << " (chemical equilibrium)";
    }

  os << std::endl;

  return os;
}
