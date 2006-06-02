/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CMCATask.cpp,v $
   $Revision: 1.10.2.3 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/06/02 22:53:27 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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
#include "CSteadyStateTask.h"

#include "CopasiDataModel/CCopasiDataModel.h"
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

bool CMCATask::initialize(const OutputFlag & of,
                          std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  CMCAProblem* pProblem =
    dynamic_cast<CMCAProblem *>(mpProblem);
  assert(pProblem);

  if (!mpMethod->isValidProblem(mpProblem)) return false;

  bool success = true;

  //initialize reporting
  if (!CCopasiTask::initialize(of, pOstream)) success = false;
  if (!pProblem->getModel()->compileIfNecessary()) success = false;

  CSteadyStateTask *pSubTask = pProblem->getSubTask();

  if (pSubTask)
    success = pSubTask->initialize(CCopasiTask::NO_OUTPUT, mReport.getStream());
  //success = pSubTask->initialize(of, mReport.getStream());

  return success;
}

bool CMCATask::process(const bool & useInitialValues)
{
  bool success = true;

  assert(mpMethod);

  CMCAMethod* pMethod = dynamic_cast<CMCAMethod *>(mpMethod);
  assert(pMethod);
  pMethod->setModel(mpProblem->getModel());

  CSteadyStateTask *pSubTask =
    dynamic_cast<CMCAProblem *>(mpProblem)->getSubTask();
  if (pSubTask)
    {
      pSubTask->setCallBack(mpCallBack);
      success &= pSubTask->process(useInitialValues);

      if (!success && useInitialValues)
        {
          mpProblem->getModel()->applyInitialValues();
        }

      pMethod->setSteadyStateStatus(pSubTask->getResult());
    }
  else
    {
      pMethod->setSteadyStateStatus(CSteadyStateMethod::notFound);

      if (useInitialValues)
        {
          mpProblem->getModel()->applyInitialValues();
        }
    }

  CCopasiTask::output(COutputInterface::BEFORE);

  pMethod->process();

  CCopasiTask::output(COutputInterface::DURING);
  CCopasiTask::output(COutputInterface::AFTER);

  return true;
}

bool CMCATask::restore()
{
  bool success = CCopasiTask::restore();

  CSteadyStateTask *pSubTask =
    dynamic_cast<CMCAProblem *>(mpProblem)->getSubTask();

  if (pSubTask)
    success &= pSubTask->restore();

  return success;
}

std::ostream &operator<<(std::ostream &os, const CMCATask & C_UNUSED(A))
{
  os << std::endl;

  os << std::endl;

  return os;
}

void CMCATask::printResult(std::ostream * ostream) const
  {
    assert(mpProblem && mpMethod);

    CMCAProblem* pProblem =
      dynamic_cast<CMCAProblem *>(mpProblem);
    assert(pProblem);

    CMCAMethod* pMethod = dynamic_cast<CMCAMethod *>(mpMethod);
    assert(pMethod);
    pMethod->setModel(mpProblem->getModel());

    std::ostream & os = *ostream;

    os << *pMethod->getUnscaledElasticitiesAnn();

    //TODO
  }
