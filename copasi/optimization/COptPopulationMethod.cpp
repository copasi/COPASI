// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

#include "copasi/optimization/COptPopulationMethod.h"
#include "copasi/optimization/COptProblem.h"
#include "copasi/optimization/COptItem.h"
#include "copasi/optimization/COptTask.h"

#include "copasi/randomGenerator/CRandom.h"
#include "copasi/randomGenerator/CIntervalValue.h"
#include "copasi/utilities/CProcessReport.h"
#include "copasi/core/CDataObject.h"
#include "copasi/core/CDataObjectReference.h"

COptPopulationMethod::COptPopulationMethod(const CDataContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType,
    const bool & parallel)
  : COptMethod(pParent, methodType, taskType, parallel)
  , mPopulationSize(0)
  , mGenerations(0)
  , mCurrentGeneration(0)
  , mhGenerations(C_INVALID_INDEX)
  , mVariableSize(0)
  , mIndividuals()
  , mValues()
  , mRandomContext(parallel)
  , mContinue(true)
  , mBestValue()
{
  initObjects();
}

COptPopulationMethod::COptPopulationMethod(const COptPopulationMethod & src,
    const CDataContainer * pParent)
  : COptMethod(src, pParent)
  , mPopulationSize(0)
  , mGenerations(0)
  , mCurrentGeneration(0)
  , mhGenerations(C_INVALID_INDEX)
  , mVariableSize(0)
  , mIndividuals()
  , mValues()
  , mRandomContext(src.mParallel)
  , mContinue(true)
  , mBestValue()
{
  initObjects();
}

COptPopulationMethod::~COptPopulationMethod()
{
  cleanup();
}

void COptPopulationMethod::initObjects()
{
  if (getSubType() != CTaskEnum::Method::ParticleSwarm
      && getSubType() != CTaskEnum::Method::ScatterSearch)
    addObjectReference("Current Generation", mCurrentGeneration, CDataObject::ValueInt);
}

#include <iostream>

bool
COptPopulationMethod::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mCurrentGeneration = 0;
  mGenerations = 0;
  mBestValue = std::numeric_limits< C_FLOAT64 >::infinity();

  if (getParameter("Number of Generations") != NULL)
    mGenerations = getValue< unsigned C_INT32 >("Number of Generations");

  if (mProcessReport
      && (getSubType() != CTaskEnum::Method::ParticleSwarm && getSubType() != CTaskEnum::Method::ScatterSearch))
    {
      mhGenerations =
        mProcessReport.addItem("Current Generation",
                               mCurrentGeneration,
                               &mGenerations);
    }

  ++mCurrentGeneration;

  if (getParameter("Population Size") != NULL)
    mPopulationSize = getValue< unsigned C_INT32 >("Population Size");
  else
    mPopulationSize = 0;

  CRandom::Type RNG = (getParameter("Random Number Generator") != NULL) ? (CRandom::Type) getValue< unsigned C_INT32 >("Random Number Generator") : CRandom::Type::mt19937;
  unsigned C_INT32 seed = (getParameter("Seed") != NULL) ? getValue< unsigned C_INT32 >("Seed") : 0;

  mRandomContext.init(RNG, seed);
  mVariableSize = mProblemContext.master()->getOptItemList(true).size();

  return true;
}

bool
COptPopulationMethod::cleanup()
{
  size_t i;

  for (i = 0; i < mIndividuals.size(); i++)
    pdelete(mIndividuals[i]);

  mIndividuals.clear();

  return true;
}

// virtual evaluate the fitness of one individual
C_FLOAT64 COptPopulationMethod::evaluate()
{
  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.
  COptProblem *& pOptProblem = mProblemContext.active();

  // evaluate the fitness
  if (!pOptProblem->calculate())
#pragma omp atomic write
    mContinue = false;

  C_FLOAT64 EvaluationValue;

  // check whether the functional constraints are fulfilled
  if (!pOptProblem->checkFunctionalConstraints())
    EvaluationValue = std::numeric_limits<C_FLOAT64>::infinity();
  else
    EvaluationValue = pOptProblem->getCalculateValue();

  if (mProblemContext.isThread(&pOptProblem))
    {
#pragma omp critical (ps_evaluate_increment_counters)
      mProblemContext.master()->incrementCounters(pOptProblem->getCounters());

      pOptProblem->resetCounters();
    }

  return EvaluationValue;
}

bool COptPopulationMethod::setSolution(const C_FLOAT64 & value,
                                       const CVector< C_FLOAT64 > & variables,
                                       const bool & algorithmOrder)
{
  bool solutionUpdated = false;

  // We have a possible race condition therefore we check again
#pragma omp critical(opt_method_set_solution)
  if (value < mBestValue)
    {
      // and store that value
      mBestValue = value;

      if (!mProblemContext.master()->setSolution(value, variables, algorithmOrder))
#pragma omp atomic write
        mContinue = false;

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);

      solutionUpdated = true;
    }

  return solutionUpdated;
}

bool COptPopulationMethod::createIndividual(const size_t & index)
{
  bool success = true;
  bool useStartValues = (index == C_INVALID_INDEX);
  size_t Index = useStartValues ? 0 : index;

  COptProblem *& pProblem = mProblemContext.active();
  CRandom * pRandom = mRandomContext.active();

  C_FLOAT64 * pIndividual = mIndividuals[Index]->begin();
  C_FLOAT64 * pEnd = mIndividuals[Index]->end();
  std::vector< COptItem * >::const_iterator itOptItem = pProblem->getOptItemList(true).begin();

  if (useStartValues)
    {
      bool pointInParameterDomain = true;

      for (size_t item = 0; pIndividual != pEnd; ++pIndividual, ++itOptItem, ++item)
        {
          COptItem & OptItem = **itOptItem;
          *pIndividual = OptItem.getStartValue();

          const C_FLOAT64 & Minimum = *OptItem.getLowerBoundValue();
          const C_FLOAT64 & Maximum = *OptItem.getUpperBoundValue();

          // force it to be within the bounds
          switch (OptItem.checkConstraint(*pIndividual))
            {
            case -1:
              *pIndividual = Minimum;
              pointInParameterDomain = false;
              break;

            case 1:
              *pIndividual = Maximum;
              pointInParameterDomain = false;
              break;
            }

          (*itOptItem)->setItemValue(*pIndividual);
          finalizeCreation(Index, item, CIntervalValue(Minimum, Maximum), pRandom);
        }

      if (!pointInParameterDomain && (mLogVerbosity > 0))
        mMethodLog.enterLogEntry(COptLogEntry("Initial point outside parameter domain."));
    }
  else
    {
      for (size_t item = 0; pIndividual != pEnd; ++pIndividual, ++itOptItem, ++item)
        {
          COptItem & OptItem = **itOptItem;
          const C_FLOAT64 & Minimum = *OptItem.getLowerBoundValue();
          const C_FLOAT64 & Maximum = *OptItem.getUpperBoundValue();

          CIntervalValue Interval(Minimum, Maximum);
          *pIndividual = Interval.randomValue(pRandom);

          // force it to be within the bounds
          switch (OptItem.checkConstraint(*pIndividual))
            {
            case -1:
              *pIndividual = Minimum;
              break;

            case 1:
              *pIndividual = Maximum;
              break;
            }

          (*itOptItem)->setItemValue(*pIndividual);
          finalizeCreation(Index, item, Interval, pRandom);
        }
    }

  return success;
}

// virtual
void COptPopulationMethod::finalizeCreation(const size_t & /* individual */ , const size_t & /* item */, const CIntervalValue & /* interval */, CRandom * /* pRandom */)
{}

C_INT32 COptPopulationMethod::getPopulationSize()
{
  return mPopulationSize;
}

C_INT32 COptPopulationMethod::getNumGenerations()
{
  return mGenerations;
}

C_INT32 COptPopulationMethod::getCurrentGeneration()
{
  return mCurrentGeneration;
}

const C_FLOAT64 & COptPopulationMethod::getBeastValue() const
{
  return mBestValue;
}

const std::vector< CVector < C_FLOAT64 > * >& COptPopulationMethod::getPopulation()
{
  return mIndividuals;
}

const CVector< C_FLOAT64 >& COptPopulationMethod::getObjectiveValues()
{
  return mValues;
}

void COptPopulationMethod::print(std::ostream * ostream) const
{
  COptMethod::print(ostream);

  *ostream << "\n" << *this;
}

std::ostream &operator<<(std::ostream &os, const COptPopulationMethod & o)
{
  os << "Population Information: " << "\n";
  os << "Population Size: " << o.mPopulationSize << "\n";
  os << "# Generations / Iterations: " << o.mGenerations << "\n";
  os << "Current Generation / Iteration: " << o.mCurrentGeneration << "\n";
  os << "Population Values: " << "\n" << "   " << o.mValues << "\n" << "\n";
  os << "Population:" << "\n";

  std::vector< CVector < C_FLOAT64 > * >::const_iterator it = o.mIndividuals.begin();

  for (; it != o.mIndividuals.end(); ++it)
    {
      os << "   " << **it << "\n";
    }

  return os;
}
