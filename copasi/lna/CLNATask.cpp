// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/lna/CLNATask.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: jpahle $
//   $Date: 2011/05/24 17:33:44 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"

#include "CLNATask.h"
#include "CLNAProblem.h"
#include "CLNAMethod.h"
#include "steadystate/CSteadyStateTask.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"

#define XXXX_Reporting

CLNATask::CLNATask(const CCopasiContainer * pParent):
    CCopasiTask(CCopasiTask::lna, pParent)
{
  mpProblem = new CLNAProblem(this);

  mpMethod = createMethod(CCopasiMethod::linearNoiseApproximation);
  this->add(mpMethod, true);
}

CLNATask::CLNATask(const CLNATask & src,
                   const CCopasiContainer * pParent):
    CCopasiTask(src, pParent)
{
  mpProblem =
    new CLNAProblem(*(CLNAProblem *) src.mpProblem, this);

  mpMethod = createMethod(src.mpMethod->getSubType());
  this->add(mpMethod, true);
}

CLNATask::~CLNATask()
{}

// virtual
CCopasiMethod * CLNATask::createMethod(const int & type) const
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  return CLNAMethod::createMethod(Type);
}

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

  if (!mpMethod->isValidProblem(mpProblem)) return false;

  CLNAMethod * pMethod = dynamic_cast<CLNAMethod*>(mpMethod);

  if (!pMethod) return false;

  pMethod->setModel(mpProblem->getModel());
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

  if (!mpMethod->isValidProblem(mpProblem)) return false;

  //we need to resize and initialize the result matrices before initializing the output
  if (!updateMatrices()) return false;

  bool success = true;

  //initialize reporting
  if (!CCopasiTask::initialize(of, pOutputHandler, pOstream)) success = false;

  if (!pProblem->getModel()->compileIfNecessary(mpCallBack)) success = false;

  CSteadyStateTask *pSubTask = pProblem->getSubTask();

  if (pSubTask)
    success = pSubTask->initialize(CCopasiTask::NO_OUTPUT, NULL, mReport.getStream());

  return success;
}

bool CLNATask::process(const bool & useInitialValues)
{
  bool success = true;
  bool stabilityAnalysisRequested = true;
  CEigen mEigenReduced;

  assert(mpMethod);

  CLNAMethod* pMethod = dynamic_cast<CLNAMethod *>(mpMethod);
  assert(pMethod);

  CSteadyStateTask *pSubTask =
    dynamic_cast<CLNAProblem *>(mpProblem)->getSubTask();

  if (pSubTask)
    {
      // LNA needs the calculation of stability information
      CSteadyStateProblem* pSSProblem = dynamic_cast<CSteadyStateProblem *>(pSubTask->getProblem());
      assert(pSSProblem);
      pSSProblem->setStabilityAnalysisRequested(stabilityAnalysisRequested);

      pSubTask->setCallBack(mpCallBack);
      pSubTask->process(useInitialValues);
      CSteadyStateMethod::ReturnCode SSstatus = pSubTask->getResult();
      pMethod->setSteadyStateStatus(SSstatus);
      success &= ((SSstatus == CSteadyStateMethod::found) || (SSstatus == CSteadyStateMethod::foundEquilibrium));

      if (!success && useInitialValues)
        {
          mpProblem->getModel()->applyInitialValues();
        }

      // check for positive or zero Eigen values
      if (success)
        {
          mEigenReduced = pSubTask->getEigenValuesReduced();

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
          mpProblem->getModel()->applyInitialValues();
        }

      success = false;
    }

  CCopasiTask::output(COutputInterface::BEFORE);

  success &= pMethod->process();

  CCopasiTask::output(COutputInterface::DURING);
  CCopasiTask::output(COutputInterface::AFTER);

  return success;
}

bool CLNATask::restore()
{
  bool success = CCopasiTask::restore();

  CSteadyStateTask *pSubTask =
    dynamic_cast<CLNAProblem *>(mpProblem)->getSubTask();

  if (pSubTask)
    success &= pSubTask->restore();

  return success;
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
  pMethod->setModel(mpProblem->getModel());

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
