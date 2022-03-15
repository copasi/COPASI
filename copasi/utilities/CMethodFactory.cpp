// Copyright (C) 2020 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/copasi.h"

#include "copasi/utilities/CTaskFactory.h"
#include "copasi/utilities/CMethodFactory.h"

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
CCopasiMethod * CMethodFactory::create(const CTaskEnum::Task & taskType,
                                       const CTaskEnum::Method & methodType,
                                       const CDataContainer * pParent)
{
  const CCopasiTask * pTask = dynamic_cast< const CCopasiTask * >(pParent);

  if (pTask == NULL ||
      pTask->getType() != taskType)
    pTask = CTaskFactory::create(taskType, NULL);

  if (pTask == NULL
      || !pTask->isValidMethod(methodType, pTask->getValidMethods()))
    return NULL;

  CCopasiMethod * pMethod = NULL;

  switch (methodType)
    {
      case CTaskEnum::Method::UnsetMethod:
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

  if (pMethod != NULL
      && dynamic_cast< CCopasiTask * >(pMethod->getObjectParent()) != NULL)
    pMethod->setMathContainer(static_cast< CCopasiTask * >(pMethod->getObjectParent())->getMathContainer());

  if (pTask != pParent)
    delete pTask;

  return pMethod;
}

// static
CCopasiMethod * CMethodFactory::copy(const CCopasiMethod * pSrc, const CDataContainer * pParent)
{
  if (pSrc == NULL)
    return NULL;

  CCopasiMethod * pCopy = NULL;

  switch (pSrc->getSubType())
    {
      case CTaskEnum::Method::UnsetMethod:
        break;

      case CTaskEnum::Method::RandomSearch:
        pCopy = new CRandomSearch(*static_cast< const CRandomSearch * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::SimulatedAnnealing:
        pCopy = new COptMethodSA(*static_cast< const COptMethodSA * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::CoranaWalk:
        pCopy = new COptMethodCoranaWalk(*static_cast< const COptMethodCoranaWalk * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::DifferentialEvolution:
        pCopy = new COptMethodDE(*static_cast< const COptMethodDE * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::ScatterSearch:
        pCopy = new COptMethodSS(*static_cast< const COptMethodSS * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::GeneticAlgorithm:
        pCopy = new COptMethodGA(*static_cast< const COptMethodGA * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::EvolutionaryProgram:
        pCopy = new COptMethodEP(*static_cast< const COptMethodEP * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::SteepestDescent:
        pCopy = new COptMethodSteepestDescent(*static_cast< const COptMethodSteepestDescent * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::GeneticAlgorithmSR:
        pCopy = new COptMethodGASR(*static_cast< const COptMethodGASR * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::HookeJeeves:
        pCopy = new COptMethodHookeJeeves(*static_cast< const COptMethodHookeJeeves * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::LevenbergMarquardt:
        pCopy = new COptMethodLevenbergMarquardt(*static_cast< const COptMethodLevenbergMarquardt * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::NL2SOL:
        pCopy = new COptMethodNL2SOL(*static_cast< const COptMethodNL2SOL * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::NelderMead:
        pCopy = new COptMethodNelderMead(*static_cast< const COptMethodNelderMead * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::SRES:
        pCopy = new COptMethodSRES(*static_cast< const COptMethodSRES * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::Statistics:
        pCopy = new COptMethodStatistics(*static_cast< const COptMethodStatistics * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::ParticleSwarm:
        pCopy = new COptMethodPS(*static_cast< const COptMethodPS * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::Praxis:
        pCopy = new COptMethodPraxis(*static_cast< const COptMethodPraxis * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::TruncatedNewton:
        pCopy = new COptMethodTruncatedNewton(*static_cast< const COptMethodTruncatedNewton * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::Newton:
        pCopy = new CNewtonMethod(*static_cast< const CNewtonMethod * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::deterministic:
        pCopy = new CLsodaMethod(*static_cast< const CLsodaMethod * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::RADAU5:
        pCopy = new CRadau5Method(*static_cast< const CRadau5Method * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::directMethod:
        pCopy = new CStochDirectMethod(*static_cast< const CStochDirectMethod * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::stochastic:
        pCopy = new CStochNextReactionMethod(*static_cast< const CStochNextReactionMethod * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::tauLeap:
        pCopy = new CTauLeapMethod(*static_cast< const CTauLeapMethod * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::adaptiveSA:
        pCopy = new CTrajAdaptiveSA(*static_cast< const CTrajAdaptiveSA * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::hybrid:
        pCopy = new CHybridNextReactionRKMethod(*static_cast< const CHybridNextReactionRKMethod * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::hybridLSODA:
        pCopy = new CHybridNextReactionLSODAMethod(*static_cast< const CHybridNextReactionLSODAMethod * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::hybridODE45:
        pCopy = new CHybridMethodODE45(*static_cast< const CHybridMethodODE45 * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::DsaLsodar:
        pCopy = new CTrajectoryMethodDsaLsodar(*static_cast< const CTrajectoryMethodDsaLsodar * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::stochasticRunkeKuttaRI5:
        pCopy = new CStochasticRungeKuttaRI5(*static_cast< const CStochasticRungeKuttaRI5 * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::tssILDM:
        pCopy = new CILDMMethod(*static_cast< const CILDMMethod * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::tssILDMModified:
        pCopy = new CILDMModifiedMethod(*static_cast< const CILDMModifiedMethod * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::tssCSP:
        pCopy = new CCSPMethod(*static_cast< const CCSPMethod * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::mcaMethodReder:
        pCopy = new CMCAMethod(*static_cast< const CMCAMethod * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::scanMethod:
        pCopy = new CScanMethod(*static_cast< const CScanMethod * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::lyapWolf:
        pCopy = new CLyapWolfMethod(*static_cast< const CLyapWolfMethod * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::sensMethod:
        pCopy = new CSensMethod(*static_cast< const CSensMethod * >(pSrc), pParent);
        break;

#ifdef COPASI_SSA

      case CTaskEnum::Method::stoichiometricStabilityAnalysis:
        pCopy = new CSSAMethod(*static_cast< const CSSAMethod * >(pSrc), pParent);
        break;

#endif // COPASI_SSA

      case CTaskEnum::Method::EFMAlgorithm:
        pCopy = new CEFMAlgorithm(*static_cast< const CEFMAlgorithm * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::EFMBitPatternTreeAlgorithm:
        pCopy = new CBitPatternTreeMethod(*static_cast< const CBitPatternTreeMethod * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::EFMBitPatternAlgorithm:
        pCopy = new CBitPatternMethod(*static_cast< const CBitPatternMethod * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::Householder:
        pCopy = new CMoietiesMethod(*static_cast< const CMoietiesMethod * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::crossSectionMethod:
        pCopy = new CCrossSectionMethod(*static_cast< const CCrossSectionMethod * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::linearNoiseApproximation:
        pCopy = new CLNAMethod(*static_cast< const CLNAMethod * >(pSrc), pParent);
        break;

      case CTaskEnum::Method::timeSensLsoda:
        pCopy = new CTimeSensLsodaMethod(*static_cast< const CTimeSensLsodaMethod * >(pSrc), pParent);
        break;
    }

  if (pCopy != NULL
      && dynamic_cast< CCopasiTask * >(pCopy->getObjectParent()) != NULL)
    pCopy->setMathContainer(static_cast< CCopasiTask * >(pCopy->getObjectParent())->getMathContainer());

  return pCopy;
}
