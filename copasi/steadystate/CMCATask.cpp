// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

  mpMethod = createMethod(CCopasiMethod::mcaMethodReder);
  this->add(mpMethod, true);
}

CMCATask::CMCATask(const CMCATask & src,
                   const CCopasiContainer * pParent):
  CCopasiTask(src, pParent)
{
  mpProblem =
    new CMCAProblem(*(CMCAProblem *) src.mpProblem, this);

  mpMethod = createMethod(src.mpMethod->getSubType());
  this->add(mpMethod, true);
}

CMCATask::~CMCATask()
{}

// virtual
CCopasiMethod * CMCATask::createMethod(const int & type) const
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  return CMCAMethod::createMethod(Type);
}

void CMCATask::cleanup()
{}

void CMCATask::load(CReadConfig & configBuffer)
{
  configBuffer.getVariable("MCA", "bool", &mScheduled,
                           CReadConfig::LOOP);

  ((CMCAProblem *) mpProblem)->load(configBuffer);

  ((CMCAMethod *) mpMethod)->load(configBuffer);
}

bool CMCATask::updateMatrices()
{
  assert(mpProblem != NULL && mpMethod != NULL);

  assert(dynamic_cast<CMCAProblem *>(mpProblem) != NULL);

  if (!mpMethod->isValidProblem(mpProblem)) return false;

  CMCAMethod * pMethod = dynamic_cast<CMCAMethod*>(mpMethod);

  if (!pMethod) return false;

  pMethod->setModel(mpProblem->getModel());
  pMethod->resizeAllMatrices();

  return true;
}

bool CMCATask::initialize(const OutputFlag & of,
                          COutputHandler * pOutputHandler,
                          std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  CMCAProblem* pProblem =
    dynamic_cast<CMCAProblem *>(mpProblem);
  assert(pProblem);

  if (!mpMethod->isValidProblem(mpProblem)) return false;

  //we need to resize an initialize the result matrices before initializing the output
  if (!updateMatrices()) return false;

  bool success = true;

  //initialize reporting
  if (!CCopasiTask::initialize(of, pOutputHandler, pOstream)) success = false;

  if (!pProblem->getModel()->compileIfNecessary(mpCallBack)) success = false;

  CSteadyStateTask *pSubTask = pProblem->getSubTask();

  if (pSubTask)
    success = pSubTask->initialize(CCopasiTask::NO_OUTPUT, NULL, mReport.getStream());

  //success = pSubTask->initialize(of, mReport.getStream());

  return success;
}

bool CMCATask::process(const bool & useInitialValues)
{
  bool success = true;

  assert(mpMethod);

  CMCAMethod* pMethod = dynamic_cast<CMCAMethod *>(mpMethod);
  assert(pMethod);
  //  pMethod->setModel(mpProblem->getModel());

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

      pMethod->setSteadyStateTask(pSubTask);
    }
  else
    {
      pMethod->setSteadyStateTask(NULL);

      if (useInitialValues)
        {
          mpProblem->getModel()->applyInitialValues();
        }
    }

  CCopasiTask::output(COutputInterface::BEFORE);

  pMethod->process();

  CCopasiTask::output(COutputInterface::DURING);
  CCopasiTask::output(COutputInterface::AFTER);

  return success;
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

  bool showCCs = false; //show CCs?
  bool showSS = false; //show Steady State result?

  if (pProblem->isSteadyStateRequested())
    {
      if (pMethod->getSteadyStateStatus() == CSteadyStateMethod::found)
        {
          os << "A steady state was found. All coefficients are shown." << std::endl;
          showCCs = true;
          showSS = true;
        }

      if (pMethod->getSteadyStateStatus() == CSteadyStateMethod::foundEquilibrium)
        {
          os << "Found equilibrium steady state. Only elasticities available." << std::endl;
          showSS = true;
        }

      if (pMethod->getSteadyStateStatus() == CSteadyStateMethod::foundNegative)
        {
          os << "Invalid steady state found (negative concentrations)." << std::endl;
          showSS = true;
        }

      if (pMethod->getSteadyStateStatus() == CSteadyStateMethod::notFound)
        {
          os << "No steady state found. Only elasticities available." << std::endl;
        }
    }
  else
    {
      os << "Since no steady state calculation was requested only elasticities are shown." << std::endl;
    }

  os << std::endl;
  os << *pMethod->getUnscaledElasticitiesAnn() << std::endl;
  os << *pMethod->getScaledElasticitiesAnn() << std::endl;

  if (showCCs)
    {
      os << *pMethod->getUnscaledConcentrationCCAnn() << std::endl;
      os << *pMethod->getScaledConcentrationCCAnn() << std::endl;

      os << *pMethod->getUnscaledFluxCCAnn() << std::endl;
      os << *pMethod->getScaledFluxCCAnn() << std::endl;
    }

  if (showSS)
    {
      if (!pProblem->getSubTask())
        {
          os << "Problem with steady state calculation. Please report as bug!" << std::endl;
          return;
        }

      os << "Results of the steady state subtask (the state for which the MCA was performed):" << std::endl;
      os << *pProblem->getSubTask();
    }
}
