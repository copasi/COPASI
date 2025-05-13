// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  COptMethod class
 *  This class describes the interface to all optimization methods.
 *  The various method like RandomSearch or GA have to be derived from
 *  this class.
 *
 *  Created for COPASI by Stefan Hoops 2002
 */

#include <limits.h>

#include "copasi/copasi.h"

#include "copasi/optimization/COptTask.h"
#include "copasi/optimization/COptMethod.h"
#include "copasi/optimization/COptProblem.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CConfigurationFile.h"

COptMethod::COptMethod(const CDataContainer * pParent,
                       const CTaskEnum::Method & methodType,
                       const CTaskEnum::Task & taskType,
                       const bool & parallel)
  : CCopasiMethod(pParent, methodType, taskType)
  , mpParentTask(NULL)
  , mParallel(parallel)
  , mMathContext(parallel)
  , mProblemContext(parallel, this)
  , mLogVerbosity(0)
  , mMethodLog()
  , mBestValue()
  , mProceed()
{
  assertParameter("Log Verbosity", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);
}

COptMethod::COptMethod(const COptMethod & src,
                       const CDataContainer * pParent)
  : CCopasiMethod(src, pParent)
  , mpParentTask(src.mpParentTask)
  , mParallel(src.mParallel)
  , mMathContext(src.mParallel)
  , mProblemContext(src.mParallel, this)
  , mLogVerbosity(src.mLogVerbosity)
  , mMethodLog(src.mMethodLog)
  , mBestValue()
  , mProceed()
{
  mMathContext.setMaster(src.mMathContext.master());
  mProblemContext.setMaster(src.mProblemContext.master());
  mProblemContext.setMathContext(mMathContext);
}

//YOHE: seems "virtual" cannot be outside of class declaration
COptMethod::~COptMethod()
{}

// static
std::pair< C_FLOAT64, bool > COptMethod::objectiveValue(COptProblem * pProblem, const CVectorCore< C_FLOAT64 > & parameters)
{
  std::pair< C_FLOAT64, bool > Result;

  pProblem->setParameters(parameters);
  Result.second = pProblem->calculate();
  Result.first = pProblem->getCalculateValue();

  return Result;
}

// static
/*
void COptMethod::reflect(COptProblem * pProblem, const C_FLOAT64 & bestValue, C_FLOAT64 & objectiveValue)
{
  C_FLOAT64 BestValue = std::min(bestValue, 0.5 * std::numeric_limits< C_FLOAT64 >::max());

  if (objectiveValue < bestValue
      && (!pProblem->checkParametricConstraints()
          || !pProblem->checkFunctionalConstraints()))
    objectiveValue = BestValue + (BestValue - objectiveValue);
}
 */

void COptMethod::setProblem(COptProblem * pProblem)
{
  mProblemContext.setMaster(pProblem);
  mProblemContext.setMathContext(mMathContext);
}

//virtual C_INT32 COptMethod::Optimise(C_FLOAT64 (*func) (void))
bool COptMethod::optimise(void)
{
  return false;
}

bool COptMethod::initialize()
{
  mBestValue = std::numeric_limits< C_FLOAT64 >::infinity();
  mProceed = true;

  if (mMathContext.master() == NULL
      || mProblemContext.master() == NULL)
    return false;

  if (mMathContext.sync())
    {
      mProblemContext.setMathContext(mMathContext);

      if (mProblemContext.size() > 1)
#pragma omp parallel for
        for (size_t i = 0; i < mProblemContext.size(); ++i)
          {
            mProblemContext.threadData()[i]->initializeSubtaskBeforeOutput();
            mProblemContext.threadData()[i]->initialize();
          }
    }
  else
    {
      mProblemContext.master()->reset();

      if (mProblemContext.size() > 1)
#pragma omp parallel for
        for (size_t i = 0; i < mProblemContext.size(); ++i)
          mProblemContext.threadData()[i]->reset();
    }

  mpParentTask = dynamic_cast< COptTask * >(getObjectParent());

  if (!mpParentTask) return false;

  //new log
  mLogVerbosity = getValue< unsigned C_INT32 >("Log Verbosity");
  mMethodLog = COptLog();

  return true;
}

// virtual
void COptMethod::signalMathContainerChanged()
{
  mMathContext.setMaster(mpContainer);
  mProblemContext.setMathContext(mMathContext);
}

bool COptMethod::cleanup()
{return true;}

//virtual
bool COptMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const COptProblem * pTP = dynamic_cast<const COptProblem *>(pProblem);

  if (!pTP)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Problem is not an optimization problem.");
      return false;
    }

  return true;
}

unsigned C_INT32 COptMethod::getMaxLogVerbosity() const
{
  return 0;
}

const COptLog &COptMethod::getMethodLog() const
{
  return mMethodLog;
}

const C_FLOAT64 & COptMethod::getBestValue() const
{
  return mBestValue;
}

C_FLOAT64 COptMethod::getCurrentValue() const
{
  return std::numeric_limits< C_FLOAT64 >::infinity();
}

const CVector< C_FLOAT64 > * COptMethod::getBestParameters() const
{
  return NULL;
}

const CVector< C_FLOAT64 > * COptMethod::getCurrentParameters() const
{
  return NULL;
}

// virtual evaluate the fitness of one individual
C_FLOAT64 COptMethod::evaluate(const EvaluationPolicyFlag & policy)
{
  if (!mProceed)
    return std::numeric_limits< C_FLOAT64 >::infinity();
    
  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.
  COptProblem *& pOptProblem = mProblemContext.active();

  // evaluate the fitness
  if (!pOptProblem->calculate())
    signalStop();

  C_FLOAT64 EvaluationValue = pOptProblem->getCalculateValue();

  if (!std::isnan(EvaluationValue))
    {
      if ((policy & EvaluationPolicy::Parameter
           && !pOptProblem->checkParametricConstraints())
          || (policy & EvaluationPolicy::Constraints
              && !pOptProblem->checkFunctionalConstraints()))
        {
          if (policy & EvaluationPolicy::Reflect)
            {
              C_FLOAT64 BestValue = std::min(mBestValue, 0.5 * std::numeric_limits< C_FLOAT64 >::max());
              EvaluationValue = BestValue + (BestValue - EvaluationValue);
            }
          else
            EvaluationValue = std::numeric_limits< C_FLOAT64 >::infinity();
        }
    }

  if (mProcessReport
      && !mProcessReport.proceed())
    signalStop();

  return EvaluationValue;
}

bool COptMethod::setSolution(const C_FLOAT64 & value,
                             const CVector< C_FLOAT64 > & variables,
                             const bool & algorithmOrder)
{
  bool solutionUpdated = false;

  // We have a possible race condition therefore we check again
#pragma omp critical (opt_method_set_solution)
  if (value < mBestValue)
    {
      // and store that value
      mBestValue = value;

      if (!mProblemContext.master()->setSolution(value, variables, algorithmOrder))
        signalStop();

      if (!mProblemContext.singleThreadedExecution())
        {
          mProblemContext.master()->incrementCounters(mProblemContext.active()->getCounters());
          mProblemContext.active()->resetCounters();
        }

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);

      solutionUpdated = true;
    }

  return solutionUpdated;
}

const bool & COptMethod::proceed() const
{
  return mProceed;
}

void COptMethod::signalStop()
{
  if (mProceed)
#pragma omp atomic write
    mProceed = false;
}
