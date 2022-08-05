// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 * CLNATask class.
 *
 * This class implements a linear noise approximation analysis task which is comprised of a
 * problem and a method.
 *
 * Created for Copasi by Juergen Pahle 2010
 */

#include "copasi/copasi.h"

#include "CLNATask.h"
#include "CLNAProblem.h"
#include "CLNAMethod.h"
#include "copasi/steadystate/CSteadyStateTask.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CReport.h"
#include "copasi/utilities/CMethodFactory.h"

#define XXXX_Reporting

CLNATask::CLNATask(const CDataContainer * pParent,
                   const CTaskEnum::Task & type):
  CCopasiTask(pParent, type)
{
  mpMethod = CMethodFactory::create(this->getType(), CTaskEnum::Method::linearNoiseApproximation, this);
}

CLNATask::CLNATask(const CLNATask & src,
                   const CDataContainer * pParent):
  CCopasiTask(src, pParent)
{}

CLNATask::~CLNATask()
{}

void CLNATask::cleanup()
{}

void CLNATask::load(CReadConfig & configBuffer)
{
  configBuffer.getVariable("LNA", "bool", &mScheduled,
                           CReadConfig::LOOP);

  ((CLNAProblem *) mpProblem)->load(configBuffer);

  ((CLNAMethod *) mpMethod)->load(configBuffer);
}

bool CLNATask::updateMatrices()
{
  assert(mpProblem && mpMethod);

  CLNAProblem* pProblem =
    dynamic_cast<CLNAProblem *>(mpProblem);
  assert(pProblem);

  if (!mpMethod->isValidProblem(pProblem)) return false;

  CLNAMethod * pMethod = dynamic_cast<CLNAMethod*>(mpMethod);

  if (!pMethod) return false;

  pMethod->resizeAllMatrices();

  return true;
}

bool CLNATask::initialize(const OutputFlag & of,
                          COutputHandler * pOutputHandler,
                          std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  CLNAProblem* pProblem =
    dynamic_cast<CLNAProblem *>(mpProblem);
  assert(pProblem);

  bool success = mpMethod->isValidProblem(mpProblem);

  //we need to resize and initialize the result matrices before initializing the output
  success &= updateMatrices();

  //initialize reporting
  success &= CCopasiTask::initialize(of, pOutputHandler, pOstream);

  CCopasiTask * pSubTask = pProblem->getSubTask();

  if (pSubTask)
    success &= pSubTask->initialize(CCopasiTask::NO_OUTPUT, NULL, mReport.getStream());

  return success;
}

bool CLNATask::process(const bool & useInitialValues)
{
  bool success = true;
  bool stabilityAnalysisRequested = true;

  assert(mpMethod);

  CLNAMethod* pMethod = dynamic_cast<CLNAMethod *>(mpMethod);
  assert(pMethod);

  CSteadyStateTask * pSubTask = dynamic_cast< CSteadyStateTask * >(mpProblem->getSubTask());

  if (pSubTask)
    {
      // LNA needs the calculation of stability information
      CSteadyStateProblem* pSSProblem = dynamic_cast<CSteadyStateProblem *>(pSubTask->getProblem());
      assert(pSSProblem);
      pSSProblem->setStabilityAnalysisRequested(stabilityAnalysisRequested);

      pSubTask->setCallBack(mProcessReport);
      pSubTask->process(useInitialValues);
      CSteadyStateMethod::ReturnCode SSstatus = pSubTask->getResult();
      pMethod->setSteadyStateStatus(SSstatus);
      success &= ((SSstatus == CSteadyStateMethod::found) || (SSstatus == CSteadyStateMethod::foundEquilibrium));

      if (!success && useInitialValues)
        {
          mpContainer->applyInitialValues();
        }

      // check for positive or zero Eigen values
      if (success)
        {
          const CEigen &mEigenReduced = pSubTask->getEigenValuesReduced();

          if ((mEigenReduced.getNposreal() + mEigenReduced.getNimag() + mEigenReduced.getNzero()) > 0)
            {
              pMethod->setEigenValueStatus(CLNAMethod::nonNegEigenvaluesExist);
              success = false;
            }
          else
            {
              pMethod->setEigenValueStatus(CLNAMethod::allNeg);
            }
        }
    }
  else
    {
      pMethod->setSteadyStateStatus(CSteadyStateMethod::notFound);

      if (useInitialValues)
        {
          mpContainer->applyInitialValues();
        }

      success = false;
    }

  CCopasiTask::output(COutputInterface::BEFORE);

  success &= pMethod->process();

  CCopasiTask::output(COutputInterface::DURING);
  CCopasiTask::output(COutputInterface::AFTER);

  return success;
}

// virtual
bool CLNATask::setCallBack(CProcessReportLevel callBack)
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
const CTaskEnum::Method * CLNATask::getValidMethods() const
{
  static const CTaskEnum::Method ValidMethods[] =
  {
    CTaskEnum::Method::linearNoiseApproximation,
    CTaskEnum::Method::UnsetMethod
  };

  return ValidMethods;
}

std::ostream &operator<<(std::ostream &os, const CLNATask & C_UNUSED(A))
{
  os << std::endl;

  os << std::endl;

  return os;
}

void CLNATask::printResult(std::ostream * ostream) const
{
  assert(mpProblem && mpMethod);

  CLNAProblem* pProblem =
    dynamic_cast<CLNAProblem *>(mpProblem);
  assert(pProblem);

  CLNAMethod* pMethod = dynamic_cast<CLNAMethod *>(mpMethod);
  assert(pMethod);

  std::ostream & os = *ostream;

  bool showSS = false; //show Steady State result?

  if (pProblem->isSteadyStateRequested())
    {
      if (pMethod->getSteadyStateStatus() == CSteadyStateMethod::found)
        {
          os << "A steady state was found. All coefficients are shown." << std::endl;
          showSS = true;
        }

      if (pMethod->getSteadyStateStatus() == CSteadyStateMethod::foundEquilibrium)
        {
          os << "An equilibrium steady state was found. All coefficients are shown." << std::endl;
          showSS = true;
        }

      if (pMethod->getSteadyStateStatus() == CSteadyStateMethod::foundNegative)
        {
          os << "Invalid steady state found (negative concentrations)." << std::endl;
          showSS = true;
        }

      if (pMethod->getSteadyStateStatus() == CSteadyStateMethod::notFound)
        {
          os << "No steady state found." << std::endl;
        }
    }
  else
    {
      os << "No steady state calculation was requested." << std::endl;
    }

  os << std::endl;
  os << *pMethod->getCovarianceMatrixAnn() << std::endl;

  if (showSS)
    {
      if (!pProblem->getSubTask())
        {
          os << "Problem with steady state calculation. Please report as bug!" << std::endl;
          return;
        }

      os << "Results of the steady state subtask (the state for which the LNA was performed):" << std::endl;
      os << *pProblem->getSubTask();
    }
}
