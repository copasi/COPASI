// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
 * Created for COPASI by Ralph Gauges 2004
 */

#include "copasi/copasi.h"

#include "copasi/steadystate/CMCATask.h"
#include "copasi/steadystate/CMCAProblem.h"
#include "copasi/steadystate/CMCAMethod.h"
#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/steadystate/CSteadyStateProblem.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CReport.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/utilities/CMethodFactory.h"

#define XXXX_Reporting

CMCATask::CMCATask(const CDataContainer * pParent,
                   const CTaskEnum::Task & type):
  CCopasiTask(pParent, type)
{
  mpMethod = CMethodFactory::create(getType(), CTaskEnum::Method::mcaMethodReder, this);
}

CMCATask::CMCATask(const CMCATask & src,
                   const CDataContainer * pParent):
  CCopasiTask(src, pParent)
{}

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

  CCopasiTask *pSubTask = pProblem->getSubTask();

  if (pSubTask != nullptr)
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

  CSteadyStateTask * pSubTask = dynamic_cast< CSteadyStateTask * >(mpProblem->getSubTask());

  if (pSubTask)
    {
      pSubTask->setCallBack(mProcessReport);

      // We need to assure that the Jacobian is calculated!
      CSteadyStateProblem * pSteadyStateProblem = static_cast< CSteadyStateProblem * >(pSubTask->getProblem());
      bool jacobianRequested = pSteadyStateProblem->isJacobianRequested();

      pSteadyStateProblem->setJacobianRequested(true);
      success &= pSubTask->process(useInitialValues);
      pSteadyStateProblem->setJacobianRequested(jacobianRequested);

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

// virtual
bool CMCATask::setCallBack(CProcessReportLevel callBack)
{
  bool success = CCopasiTask::setCallBack(callBack);

  CCopasiTask *pSubTask = mpProblem->getSubTask();

  if (pSubTask != NULL)
    {
      success &= pSubTask->setCallBack(mProcessReport);
    }

  return success;
}

// virtual
const CTaskEnum::Method * CMCATask::getValidMethods() const
{
  static const CTaskEnum::Method ValidMethods[] =
  {
    CTaskEnum::Method::mcaMethodReder,
    CTaskEnum::Method::UnsetMethod
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
