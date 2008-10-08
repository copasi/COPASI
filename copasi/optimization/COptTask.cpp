// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptTask.cpp,v $
//   $Revision: 1.38 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/10/08 23:32:59 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * COptTask class.
 *
 * This class implements a optimization task which is comprised of a
 * of a problem and a method.
 *
 */
#include "copasi.h"

#include "COptTask.h"
#include "COptProblem.h"
#include "COptMethod.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"

#include "model/CModel.h"
#include "model/CState.h"

//#include "trajectory/CTrajectoryTask.h"
//#include "trajectory/CTrajectoryProblem.h"
//#include "steadystate/CSteadyStateTask.h"
//#include "steadystate/CSteadyStateProblem.h"
//#include "utilities/COutputHandler.h"

unsigned C_INT32 COptTask::ValidMethods[] =
  {
    CCopasiMethod::Statistics,
    CCopasiMethod::GeneticAlgorithm,
    CCopasiMethod::GeneticAlgorithmSR,
    CCopasiMethod::HookeJeeves,
    CCopasiMethod::LevenbergMarquardt,
    CCopasiMethod::EvolutionaryProgram,
    CCopasiMethod::RandomSearch,
    CCopasiMethod::NelderMead,
    CCopasiMethod::ParticleSwarm,
    CCopasiMethod::Praxis,
    CCopasiMethod::TruncatedNewton,
    CCopasiMethod::SimulatedAnnealing,
    CCopasiMethod::SRES,
    CCopasiMethod::SteepestDescent,
    CCopasiMethod::unset
  };

COptTask::COptTask(const CCopasiTask::Type & type,
                   const CCopasiContainer * pParent):
    CCopasiTask(type, pParent)
{
  mpProblem = new COptProblem(type, this);
  mpMethod = COptMethod::createMethod();
  this->add(mpMethod, true);
  //  mpMethod->setObjectParent(this);
  ((COptMethod *) mpMethod)->setProblem((COptProblem *) mpProblem);
}

COptTask::COptTask(const COptTask & src,
                   const CCopasiContainer * pParent):
    CCopasiTask(src, pParent)
{
  mpProblem = new COptProblem(* (COptProblem *) src.mpProblem, this);
  mpMethod = COptMethod::createMethod(src.mpMethod->getSubType());
  this->add(mpMethod, true);
  //  mpMethod->setObjectParent(this);
  ((COptMethod *) mpMethod)->setProblem((COptProblem *) mpProblem);
}

COptTask::~COptTask()
{cleanup();}

void COptTask::cleanup(){}

bool COptTask::setCallBack(CProcessReport * pCallBack)
{
  bool success = CCopasiTask::setCallBack(pCallBack);

  if (!mpProblem->setCallBack(pCallBack)) success = false;
  if (!mpMethod->setCallBack(pCallBack)) success = false;

  return success;
}

bool COptTask::initialize(const OutputFlag & of,
                          COutputHandler * pOutputHandler,
                          std::ostream * pOstream)
{
  COptProblem * pProblem = dynamic_cast<COptProblem *>(mpProblem);
  COptMethod * pMethod = dynamic_cast<COptMethod *>(mpMethod);

  if (!pProblem || !pMethod) return false;

  //initialize reporting
  bool success = true;

  //do the part of the initialization of the subtask that needs to be
  //performed before the output is initialized. This is kind of a hack,
  //we need to find a more general solution for this
  if (!pProblem->initializeSubtaskBeforeOutput()) success = false;

  if (!CCopasiTask::initialize(of, pOutputHandler, pOstream)) success = false;
  //if (!mReport.open(pOstream)) success = false;
  //if (!mReport.compile()) success = false;

  if (!pProblem->initialize()) success = false;

  pMethod->setProblem(pProblem);
  //  if (!pMethod->initialize()) return false;

  return success;
}

bool COptTask::process(const bool & /* useInitialValues */)
{
  COptProblem * pProblem = dynamic_cast<COptProblem *>(mpProblem);
  COptMethod * pMethod = dynamic_cast<COptMethod *>(mpMethod);

  if (!pProblem || !pMethod) return false;

  mpMethod->isValidProblem(mpProblem);

  output(COutputInterface::BEFORE);

  bool success = pMethod->optimise();

  pProblem->calculateStatistics();

  output(COutputInterface::AFTER);

  return success;
}

bool COptTask::setMethodType(const int & type)
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  if (mpMethod->getSubType() == Type) return true;

  pdelete (mpMethod);

  mpMethod = COptMethod::createMethod(Type);
  this->add(mpMethod, true);

  return true;
}
