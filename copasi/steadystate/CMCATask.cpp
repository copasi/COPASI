// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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
#include "report/CKeyFactory.h"
#include "report/CReport.h"
#include "math/CMathContainer.h"

#define XXXX_Reporting

CMCATask::CMCATask(const CCopasiContainer * pParent,
                   const CTaskEnum::Task & type):
  CCopasiTask(pParent, type)
{
  mpProblem = new CMCAProblem(this);

  mpMethod = createMethod(CTaskEnum::mcaMethodReder);
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

  bool success = mpMethod->isValidProblem(mpProblem);

  //we need to resize an initialize the result matrices before initializing the output
  success &= updateMatrices();

  //initialize reporting
  success &= CCopasiTask::initialize(of, pOutputHandler, pOstream);

  CSteadyStateTask *pSubTask = pProblem->getSubTask();

  if (pSubTask)
    success &= pSubTask->initialize(CCopasiTask::NO_OUTPUT, NULL, mReport.getStream());

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
          mpContainer->applyInitialValues();
        }

      pMethod->setSteadyStateTask(pSubTask);
    }
  else
    {
      pMethod->setSteadyStateTask(NULL);

      if (useInitialValues)
        {
          mpContainer->applyInitialValues();
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

// virtual
const CTaskEnum::Method * CMCATask::getValidMethods() const
{
  static const CTaskEnum::Method ValidMethods[] =
  {
    CTaskEnum::mcaMethodReder,
    CTaskEnum::UnsetMethod
  };

  return ValidMethods;
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
