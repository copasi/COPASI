// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/math/CMathContainer.h"

#include "copasi/crosssection/CCrossSectionMethod.h"
#include "copasi/elementaryFluxModes/CBitPatternMethod.h"
#include "copasi/elementaryFluxModes/CBitPatternTreeMethod.h"
#include "copasi/elementaryFluxModes/CEFMAlgorithm.h"
// #include "copasi/elementaryFluxModes/CSSAMethod.h"
#include "copasi/lna/CLNAMethod.h"
// #include "copasi/lyap/CLyapMethod.h"
#include "copasi/lyap/CLyapWolfMethod.h"
#include "copasi/moieties/CMoietiesMethod.h"
#include "copasi/optimization/COptMethodCoranaWalk.h"
#include "copasi/optimization/COptMethodDE.h"
#include "copasi/optimization/COptMethodEP.h"
#include "copasi/optimization/COptMethodGA.h"
#include "copasi/optimization/COptMethodGASR.h"
#include "copasi/optimization/COptMethodHookeJeeves.h"
#include "copasi/optimization/COptMethodLevenbergMarquardt.h"
#include "copasi/optimization/COptMethodNelderMead.h"
#include "copasi/optimization/COptMethodPS.h"
#include "copasi/optimization/COptMethodPraxis.h"
#include "copasi/optimization/COptMethodSA.h"
#include "copasi/optimization/COptMethodSRES.h"
#include "copasi/optimization/COptMethodSS.h"
#include "copasi/optimization/COptMethodStatistics.h"
#include "copasi/optimization/COptMethodSteepestDescent.h"
#include "copasi/optimization/COptMethodTruncatedNewton.h"
#include "copasi/optimization/COptMethodNL2SOL.h"
#include "copasi/optimization/CRandomSearch.h"
// #include "oscillation/COscillationMethod.h"
#include "copasi/scan/CScanMethod.h"
#include "copasi/sensitivities/CSensMethod.h"
#include "copasi/steadystate/CMCAMethod.h"
#include "copasi/steadystate/CNewtonMethod.h"
// #include "copasi/steadystate/CSteadyStateMethod.h"
// #include "copasi/trajectory/CExpRKMethod.h"
#include "copasi/trajectory/CHybridMethodODE45.h"
#include "copasi/trajectory/CLsodaMethod.h"
#include "copasi/trajectory/CRadau5Method.h"
#include "copasi/trajectory/CStochDirectMethod.h"
// #include "copasi/trajectory/CStochMethod.h"
#include "copasi/trajectory/CHybridNextReactionRKMethod.h"
#include "copasi/trajectory/CHybridNextReactionLSODAMethod.h"
#include "copasi/trajectory/CStochNextReactionMethod.h"
#include "copasi/trajectory/CTauLeapMethod.h"
#include "copasi/trajectory/CTrajAdaptiveSA.h"
#include "copasi/trajectory/CTrajectoryMethodDsaLsodar.h"
#include "copasi/trajectory/CStochasticRungeKuttaRI5.h"
#include "copasi/tssanalysis/CCSPMethod.h"
#include "copasi/tssanalysis/CILDMMethod.h"
#include "copasi/tssanalysis/CILDMModifiedMethod.h"
#include "copasi/timesens/CTimeSensLsodaMethod.h"
// #include "copasi/tssanalysis/CTSSAMethod.h"

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

      case CTaskEnum::Method::NL2SOL:
        pMethod = new COptMethodNL2SOL(pParent, methodType, taskType);
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

      case CTaskEnum::Method::RADAU5:
        pMethod = new CRadau5Method(pParent, methodType, taskType);
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

      case CTaskEnum::Method::timeSensLsoda:
        pMethod = new CTimeSensLsodaMethod(pParent, methodType, taskType);
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
