// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
  * CFitTask class.
  *
  * This class implements a parameter estimation task which is comprised of a
  * of a problem and a method.
  *
  */
#include "copasi/copasi.h"

#include "CFitTask.h"
#include "CFitProblem.h"
#include "copasi/optimization/COptMethod.h"

#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/utilities/CMethodFactory.h"

const CTaskEnum::Method CFitTask::ValidMethods[]  =
{
  CTaskEnum::Method::Statistics,
#ifdef COPASI_DEBUG
  CTaskEnum::Method::CoranaWalk,
#endif // COPASI_DEBUG
  CTaskEnum::Method::DifferentialEvolution,
  CTaskEnum::Method::SRES,
  CTaskEnum::Method::EvolutionaryProgram,
  CTaskEnum::Method::GeneticAlgorithm,
  CTaskEnum::Method::GeneticAlgorithmSR,
  CTaskEnum::Method::HookeJeeves,
  CTaskEnum::Method::LevenbergMarquardt,
  CTaskEnum::Method::NL2SOL,
  CTaskEnum::Method::NelderMead,
  CTaskEnum::Method::ParticleSwarm,
  CTaskEnum::Method::Praxis,
  CTaskEnum::Method::RandomSearch,
  CTaskEnum::Method::ScatterSearch,
  CTaskEnum::Method::SimulatedAnnealing,
  CTaskEnum::Method::SteepestDescent,
  CTaskEnum::Method::TruncatedNewton,
  CTaskEnum::Method::UnsetMethod
};

CFitTask::CFitTask(const CDataContainer * pParent,
                   const CTaskEnum::Task & type):
  COptTask(pParent, type)
{
  if (getType() == CTaskEnum::Task::parameterFitting)
    {
      mpMethod = CMethodFactory::create(getType(), CTaskEnum::Method::EvolutionaryProgram, this);
      static_cast< COptMethod * >(mpMethod)->setProblem(static_cast< COptProblem * >(mpProblem));
    }
}

CFitTask::CFitTask(const CFitTask & src,
                   const CDataContainer * pParent):
  COptTask(src, pParent)
{}

CFitTask::~CFitTask()
{cleanup();}

void CFitTask::cleanup() {}

bool CFitTask::setCallBack(CProcessReport * pCallBack)
{
  bool success = CCopasiTask::setCallBack(pCallBack);

  if (!mpProblem->setCallBack(pCallBack)) success = false;

  if (!mpMethod->setCallBack(pCallBack)) success = false;

  return success;
}

bool CFitTask::initialize(const OutputFlag & of,
                          COutputHandler * pOutputHandler,
                          std::ostream * pOstream)
{
  return COptTask::initialize(of, pOutputHandler, pOstream);
}

bool CFitTask::process(const bool & useInitialValues)
{
  CFitProblem * pProblem = dynamic_cast<CFitProblem *>(mpProblem);
  COptMethod * pMethod = dynamic_cast<COptMethod *>(mpMethod);

  if (!pProblem || !pMethod) return false;

  mpMethod->isValidProblem(mpProblem);

  if (useInitialValues)
    {
      pProblem->updateInitialState();
    }

  pProblem->randomizeStartValues();
  pProblem->rememberStartValues();

  output(COutputInterface::BEFORE);

  bool success = pMethod->optimise();

  pProblem->calculateStatistics();
  pProblem->createParameterSets();

  output(COutputInterface::AFTER);

  return success;
}

void CFitTask::fixBuild55()
{
  CFitProblem * pFitProblem = dynamic_cast< CFitProblem * >(mpProblem);

  if (pFitProblem == NULL) return;

  pFitProblem->fixBuild55();

  return;
}

const CTaskEnum::Method * CFitTask::getValidMethods() const
{
  return CFitTask::ValidMethods;
}
