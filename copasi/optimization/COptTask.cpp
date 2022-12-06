// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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
 * COptTask class.
 *
 * This class implements a optimization task which is comprised
 * of a problem and a method.
 *
 */
#include "copasi/copasi.h"

#include "COptTask.h"
#include "COptProblem.h"
#include "COptMethod.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CReport.h"

#include "copasi/model/CModel.h"
#include "copasi/model/CState.h"
#include "copasi/utilities/CMethodFactory.h"

// static
const CTaskEnum::Method COptTask::ValidMethods[]  =
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

COptTask::COptTask(const CDataContainer * pParent,
                   const CTaskEnum::Task & type):
  CCopasiTask(pParent, type)
{
  if (getType() == CTaskEnum::Task::optimization)
    {
      mpMethod = CMethodFactory::create(getType(), CTaskEnum::Method::RandomSearch, this);
      static_cast< COptMethod * >(mpMethod)->setProblem(static_cast< COptProblem * >(mpProblem));
    }
}

COptTask::COptTask(const COptTask & src,
                   const CDataContainer * pParent):
  CCopasiTask(src, pParent)
{
  static_cast< COptMethod * >(mpMethod)->setProblem(static_cast< COptProblem * >(mpProblem));
}

COptTask::~COptTask()
{cleanup();}

void COptTask::cleanup() {}

bool COptTask::setCallBack(CProcessReportLevel callBack)
{
  bool success = CCopasiTask::setCallBack(callBack);

  if (success &&
      mpProblem != NULL)
    {
      success &=  mpProblem->setCallBack(mProcessReport);
    }

  return success;
}

bool COptTask::initialize(const OutputFlag & of,
                          COutputHandler * pOutputHandler,
                          std::ostream * pOstream)
{
  if (!isTaskValid())
    return false;

  COptProblem * pProblem = dynamic_cast<COptProblem *>(mpProblem);
  COptMethod * pMethod = dynamic_cast<COptMethod *>(mpMethod);

  if (!pProblem || !pMethod) return false;

  //initialize reporting
  bool success = true;

  //do the part of the initialization of the subtask that needs to be
  //performed before the output is initialized. This is kind of a hack,
  //we need to find a more general solution for this
  success &= pProblem->initializeSubtaskBeforeOutput();

  success &= CCopasiTask::initialize(of, pOutputHandler, pOstream);

  //if (!mReport.open(pOstream)) success = false;
  //if (!mReport.compile()) success = false;

  success &= pProblem->initialize();

  pMethod->setProblem(pProblem);
  //  if (!pMethod->initialize()) return false;

  return success;
}

bool COptTask::process(const bool & useInitialValues)
{
  COptProblem * pProblem = dynamic_cast<COptProblem *>(mpProblem);
  COptMethod * pMethod = dynamic_cast<COptMethod *>(mpMethod);

  if (!pProblem || !pMethod) return false;

  mpMethod->isValidProblem(mpProblem);

  pProblem->randomizeStartValues();
  pProblem->rememberStartValues();

  if (useInitialValues) pProblem->resetCounters();

  output(COutputInterface::BEFORE);

  bool success = pMethod->optimise();

  if (mProcessReport)
    mProcessReport.setIgnoreStop();

  pProblem->calculateStatistics();

  output(COutputInterface::AFTER);

  return success;
}

// virtual
const CTaskEnum::Method * COptTask::getValidMethods() const
{
  return COptTask::ValidMethods;
}
