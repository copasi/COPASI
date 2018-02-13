// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CCopasiMethod class.
 *  This class is used to describe a task in COPASI. This class is
 *  intended to be used as the parent class for all methods within COPASI.
 *
 *  Created for COPASI by Stefan Hoops 2003
 */

#include "copasi/copasi.h"

#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/utilities/CCopasiProblem.h"

#include "math/CMathContainer.h"

#include "crosssection/CCrossSectionMethod.h"
#include "elementaryFluxModes/CBitPatternMethod.h"
#include "elementaryFluxModes/CBitPatternTreeMethod.h"
#include "elementaryFluxModes/CEFMAlgorithm.h"
// #include "elementaryFluxModes/CSSAMethod.h"
#include "lna/CLNAMethod.h"
// #include "lyap/CLyapMethod.h"
#include "lyap/CLyapWolfMethod.h"
#include "moieties/CMoietiesMethod.h"
#include "optimization/COptMethodCoranaWalk.h"
#include "optimization/COptMethodDE.h"
#include "optimization/COptMethodEP.h"
#include "optimization/COptMethodGA.h"
#include "optimization/COptMethodGASR.h"
#include "optimization/COptMethodHookeJeeves.h"
#include "optimization/COptMethodLevenbergMarquardt.h"
#include "optimization/COptMethodNelderMead.h"
#include "optimization/COptMethodPS.h"
#include "optimization/COptMethodPraxis.h"
#include "optimization/COptMethodSA.h"
#include "optimization/COptMethodSRES.h"
#include "optimization/COptMethodSS.h"
#include "optimization/COptMethodStatistics.h"
#include "optimization/COptMethodSteepestDescent.h"
#include "optimization/COptMethodTruncatedNewton.h"
#include "optimization/CRandomSearch.h"
// #include "oscillation/COscillationMethod.h"
#include "scan/CScanMethod.h"
#include "sensitivities/CSensMethod.h"
#include "steadystate/CMCAMethod.h"
#include "steadystate/CNewtonMethod.h"
// #include "steadystate/CSteadyStateMethod.h"
// #include "trajectory/CExpRKMethod.h"
#include "trajectory/CHybridMethodODE45.h"
#include "trajectory/CLsodaMethod.h"
#include "trajectory/CStochDirectMethod.h"
// #include "trajectory/CStochMethod.h"
#include "trajectory/CHybridNextReactionRKMethod.h"
#include "trajectory/CHybridNextReactionLSODAMethod.h"
#include "trajectory/CStochNextReactionMethod.h"
#include "trajectory/CTauLeapMethod.h"
#include "trajectory/CTrajAdaptiveSA.h"
#include "trajectory/CTrajectoryMethodDsaLsodar.h"
#include "trajectory/CStochasticRungeKuttaRI5.h"
#include "tssanalysis/CCSPMethod.h"
#include "tssanalysis/CILDMMethod.h"
#include "tssanalysis/CILDMModifiedMethod.h"
// #include "tssanalysis/CTSSAMethod.h"

//static
CCopasiMethod * CCopasiMethod::createMethod(const CDataContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType)
{
  CCopasiMethod * pMethod = NULL;

  switch (methodType)
    {
      case CTaskEnum::Method::UnsetMethod:
        pMethod = new CCopasiMethod(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::RandomSearch:
        pMethod = new CRandomSearch(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::SimulatedAnnealing:
        pMethod = new COptMethodSA(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::CoranaWalk:
        pMethod = new COptMethodCoranaWalk(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::DifferentialEvolution:
        pMethod = new COptMethodDE(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::ScatterSearch:
        pMethod = new COptMethodSS(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::GeneticAlgorithm:
        pMethod = new COptMethodGA(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::EvolutionaryProgram:
        pMethod = new COptMethodEP(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::SteepestDescent:
        pMethod = new COptMethodSteepestDescent(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::GeneticAlgorithmSR:
        pMethod = new COptMethodGASR(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::HookeJeeves:
        pMethod = new COptMethodHookeJeeves(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::LevenbergMarquardt:
        pMethod = new COptMethodLevenbergMarquardt(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::NelderMead:
        pMethod = new COptMethodNelderMead(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::SRES:
        pMethod = new COptMethodSRES(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::Statistics:
        pMethod = new COptMethodStatistics(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::ParticleSwarm:
        pMethod = new COptMethodPS(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::Praxis:
        pMethod = new COptMethodPraxis(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::TruncatedNewton:
        pMethod = new COptMethodTruncatedNewton(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::Newton:
        pMethod = new CNewtonMethod(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::deterministic:
        pMethod = new CLsodaMethod(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::directMethod:
        pMethod = new CStochDirectMethod(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::stochastic:
        pMethod = new CStochNextReactionMethod(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::tauLeap:
        pMethod = new CTauLeapMethod(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::adaptiveSA:
        pMethod = new CTrajAdaptiveSA(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::hybrid:
        pMethod = new CHybridNextReactionRKMethod(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::hybridLSODA:
        pMethod = new CHybridNextReactionLSODAMethod(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::hybridODE45:
        pMethod = new CHybridMethodODE45(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::DsaLsodar:
        pMethod = new CTrajectoryMethodDsaLsodar(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::stochasticRunkeKuttaRI5:
        pMethod = new CStochasticRungeKuttaRI5(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::tssILDM:
        pMethod = new CILDMMethod(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::tssILDMModified:
        pMethod = new CILDMModifiedMethod(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::tssCSP:
        pMethod = new CCSPMethod(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::mcaMethodReder:
        pMethod = new CMCAMethod(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::scanMethod:
        pMethod = new CScanMethod(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::lyapWolf:
        pMethod = new CLyapWolfMethod(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::sensMethod:
        pMethod = new CSensMethod(pParent, methodType, taskType);
        break;

#ifdef COPASI_SSA

      case CTaskEnum::Method::stoichiometricStabilityAnalysis:
        pMethod = new CSSAMethod(pParent, methodType, taskType);
        break;

#endif // COPASI_SSA

      case CTaskEnum::Method::EFMAlgorithm:
        pMethod = new CEFMAlgorithm(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::EFMBitPatternTreeAlgorithm:
        pMethod = new CBitPatternTreeMethod(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::EFMBitPatternAlgorithm:
        pMethod = new CBitPatternMethod(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::Householder:
        pMethod = new CMoietiesMethod(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::crossSectionMethod:
        pMethod = new CCrossSectionMethod(pParent, methodType, taskType);
        break;

      case CTaskEnum::Method::linearNoiseApproximation:
        pMethod = new CLNAMethod(pParent, methodType, taskType);
        break;
    }

  return pMethod;
}

CCopasiMethod::CCopasiMethod(const CDataContainer * pParent,
                             const CTaskEnum::Method & methodType,
                             const CTaskEnum::Task & taskType):
  CCopasiParameterGroup(CTaskEnum::MethodName[methodType], pParent, "Method"),
  mTaskType(taskType),
  mSubType(methodType),
  mpContainer(NULL),
  mpCallBack(NULL)
{}

CCopasiMethod::CCopasiMethod(const CCopasiMethod & src,
                             const CDataContainer * pParent):
  CCopasiParameterGroup(src, pParent),
  mTaskType(src.mTaskType),
  mSubType(src.mSubType),
  mpContainer(src.mpContainer),
  mpCallBack(src.mpCallBack)
{}

CCopasiMethod::~CCopasiMethod() {}

void CCopasiMethod::setMathContainer(CMathContainer * pContainer)
{
  if (pContainer != mpContainer)
    {
      mpContainer = pContainer;
      signalMathContainerChanged();
    }
}

// virtual
void CCopasiMethod::signalMathContainerChanged()
{}

CMathContainer * CCopasiMethod::getMathContainer() const
{
  return mpContainer;
}

bool CCopasiMethod::setCallBack(CProcessReport * pCallBack)
{
  mpCallBack = pCallBack;
  return true;
}

CProcessReport * CCopasiMethod::getCallBack() const
{
  return mpCallBack;
}

void CCopasiMethod::clearCallBack()
{
  setCallBack(NULL);
}

const CTaskEnum::Task & CCopasiMethod::getType() const {return mTaskType;}

// void CCopasiMethod::setType(const CTaskEnum::Task & type) {mTaskType = type;}

const CTaskEnum::Method & CCopasiMethod::getSubType() const
{return mSubType;}

// void CCopasiMethod::setSubType(const CTaskEnum::Method & subType)
// {mSubType = subType;}

//virtual
bool CCopasiMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (pProblem == NULL)
    {
      //no problem
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCCopasiMethod + 2);
      return false;
    }

  if (mpContainer == NULL)
    {
      //no model
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCCopasiMethod + 3);
      return false;
    }

  if (mpContainer->getEvents().size())
    {
      if (mTaskType == CTaskEnum::Task::lyap)
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCCopasiMethod + 4, "Lyapunov Exponents");
          return false;
        }

      if (mTaskType == CTaskEnum::Task::tssAnalysis)
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCCopasiMethod + 4, "Time Scale Separation Analysis");
          return false;
        }

      if (mTaskType == CTaskEnum::Task::lna)
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCCopasiMethod + 4, "Linear Noise Approximation");
          return false;
        }
    }

  return true;
}

void CCopasiMethod::load(CReadConfig & /* configBuffer */,
                         CReadConfig::Mode /* mode */)
{fatalError();}

void CCopasiMethod::print(std::ostream * ostream) const
{*ostream << *this;}

std::ostream &operator<<(std::ostream &os, const CCopasiMethod & o)
{
  os << "Method: " << o.getObjectName() << std::endl;

  CCopasiParameterGroup::elements::const_iterator it = o.beginIndex();
  CCopasiParameterGroup::elements::const_iterator end = o.endIndex();

  for (; it != end; ++it)
    {
      (*it)->print(&os);
      os << std::endl;
    }

  return os;
}

void CCopasiMethod::printResult(std::ostream * ostream) const
{*ostream << " Not implemented.";}
