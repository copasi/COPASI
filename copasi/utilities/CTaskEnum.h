// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CTaskEnum
#define COPASI_CTaskEnum

#include <string>

#include "copasi/core/CEnumAnnotation.h"

class CTaskEnum
{
public:
  /**
   * Enumeration of the types of tasks known to COPASI.
   */
  enum struct Task
  {
    steadyState = 0,
    timeCourse,
    scan,
    fluxMode,
    optimization,
    parameterFitting,
    mca,
    lyap,
    tssAnalysis,
    sens,
    moieties,
    crosssection,
    lna,
    analytics,
    timeSens,
    UnsetTask
  };

private:
  constexpr static CEnumAnnotationInstance _TaskName{
    Task::UnsetTask,
    MapNode{Task::steadyState, "Steady-State"},
    MapNode{Task::timeCourse, "Time-Course"},
    MapNode{Task::scan, "Scan"},
    MapNode{Task::fluxMode, "Elementary Flux Modes"},
    MapNode{Task::optimization, "Optimization"},
    MapNode{Task::parameterFitting, "Parameter Estimation"},
    MapNode{Task::mca, "Metabolic Control Analysis"},
    MapNode{Task::lyap, "Lyapunov Exponents"},
    MapNode{Task::tssAnalysis, "Time Scale Separation Analysis"},
    MapNode{Task::sens, "Sensitivities"},
    MapNode{Task::moieties, "Moieties"},
    MapNode{Task::crosssection, "Cross Section"},
    MapNode{Task::lna, "Linear Noise Approximation"},
    MapNode{Task::analytics, "Analytics"},
    MapNode{Task::timeSens, "Time-Course Sensitivities"},
    MapNode{Task::UnsetTask, "not specified"}};

public:
  constexpr static CEnumAnnotation< Task, std::string_view > TaskName{_TaskName};

private:
  constexpr static CEnumAnnotationInstance _TaskXML{
    Task::UnsetTask,
    MapNode{Task::steadyState, "steadyState"},
    MapNode{Task::timeCourse, "timeCourse"},
    MapNode{Task::scan, "scan"},
    MapNode{Task::fluxMode, "fluxMode"},
    MapNode{Task::optimization, "optimization"},
    MapNode{Task::parameterFitting, "parameterFitting"},
    MapNode{Task::mca, "metabolicControlAnalysis"},
    MapNode{Task::lyap, "lyapunovExponents"},
    MapNode{Task::tssAnalysis, "timeScaleSeparationAnalysis"},
    MapNode{Task::sens, "sensitivities"},
    MapNode{Task::moieties, "moieties"},
    MapNode{Task::crosssection, "crosssection"},
    MapNode{Task::lna, "linearNoiseApproximation"},
    MapNode{Task::analytics, "analytics"},
    MapNode{Task::timeSens, "timeSensitivities"},
    MapNode{Task::UnsetTask, "unset"}};

public:
  constexpr static CEnumAnnotation< Task, std::string_view > TaskXML{_TaskXML};

  /**
   * Enumeration of the sub types of methods known to COPASI.
   */
  enum struct Method
  {
    UnsetMethod = 0,
    RandomSearch,
    RandomSearchMaster,
    SimulatedAnnealing,
    CoranaWalk,
    DifferentialEvolution,
    ScatterSearch,
    GeneticAlgorithm,
    EvolutionaryProgram,
    SteepestDescent,
    HybridGASA,
    GeneticAlgorithmSR,
    HookeJeeves,
    LevenbergMarquardt,
    NL2SOL,
    NelderMead,
    SRES,
    Statistics,
    ParticleSwarm,
    Praxis,
    TruncatedNewton,
    Newton,
    deterministic,
    RADAU5,
    LSODA2,
    directMethod,
    stochastic,
    tauLeap,
    adaptiveSA,
    hybrid,
    hybridLSODA,
    hybridODE45,
    DsaLsodar,
    stochasticRunkeKuttaRI5,
    tssILDM,
    tssILDMModified,
    tssCSP,
    mcaMethodReder,
    scanMethod,
    lyapWolf,
    sensMethod,
#ifdef COPASI_SSA
    stoichiometricStabilityAnalysis,
#endif // COPASI_SSA
    EFMAlgorithm,
    EFMBitPatternTreeAlgorithm,
    EFMBitPatternAlgorithm,
    Householder,
    crossSectionMethod,
    linearNoiseApproximation,
    analyticsMethod,
    timeSensLsoda
  };

private:
  constexpr static CEnumAnnotationInstance _MethodName{
    Method::UnsetMethod,
    MapNode{Method::UnsetMethod, "Not set"},
    MapNode{Method::RandomSearch, "Random Search"},
    MapNode{Method::RandomSearchMaster, "Random Search (PVM)"},
    MapNode{Method::SimulatedAnnealing, "Simulated Annealing"},
    MapNode{Method::CoranaWalk, "Corana Random Walk"},
    MapNode{Method::DifferentialEvolution, "Differential Evolution"},
    MapNode{Method::ScatterSearch, "Scatter Search"},
    MapNode{Method::GeneticAlgorithm, "Genetic Algorithm"},
    MapNode{Method::EvolutionaryProgram, "Evolutionary Programming"},
    MapNode{Method::SteepestDescent, "Steepest Descent"},
    MapNode{Method::HybridGASA, "Hybrid GA/SA"},
    MapNode{Method::GeneticAlgorithmSR, "Genetic Algorithm SR"},
    MapNode{Method::HookeJeeves, "Hooke & Jeeves"},
    MapNode{Method::LevenbergMarquardt, "Levenberg - Marquardt"},
    MapNode{Method::NL2SOL, "NL2SOL"},
    MapNode{Method::NelderMead, "Nelder - Mead"},
    MapNode{Method::SRES, "Evolution Strategy (SRES)"},
    MapNode{Method::Statistics, "Current Solution Statistics"},
    MapNode{Method::ParticleSwarm, "Particle Swarm"},
    MapNode{Method::Praxis, "Praxis"},
    MapNode{Method::TruncatedNewton, "Truncated Newton"},
    MapNode{Method::Newton, "Enhanced Newton"},
    MapNode{Method::deterministic, "Deterministic (LSODA)"},
    MapNode{Method::RADAU5, "Deterministic (RADAU5)"},
    MapNode{Method::LSODA2, "Deterministic (LSODA2)"},
    MapNode{Method::directMethod, "Stochastic (Direct method)"},
    MapNode{Method::stochastic, "Stochastic (Gibson + Bruck)"},
    MapNode{Method::tauLeap, "Stochastic (\xcf\x84-Leap)"},
    MapNode{Method::adaptiveSA, "Stochastic (Adaptive SSA/\xcf\x84-Leap)"},
    MapNode{Method::hybrid, "Hybrid (Runge-Kutta)"},
    MapNode{Method::hybridLSODA, "Hybrid (LSODA)"},
    MapNode{Method::hybridODE45, "Hybrid (RK-45)"},
    MapNode{Method::DsaLsodar, "Hybrid (DSA-LSODAR)"},
    MapNode{Method::stochasticRunkeKuttaRI5, "SDE Solver (RI5)"},
    MapNode{Method::tssILDM, "ILDM (LSODA,Deuflhard)"},
    MapNode{Method::tssILDMModified, "ILDM (LSODA,Modified)"},
    MapNode{Method::tssCSP, "CSP (LSODA)"},
    MapNode{Method::mcaMethodReder, "MCA Method (Reder)"},
    MapNode{Method::scanMethod, "Scan Framework"},
    MapNode{Method::lyapWolf, "Wolf Method"},
    MapNode{Method::sensMethod, "Sensitivities Method"},
#ifdef COPASI_SSA
    MapNode{Method::stoichiometricStabilityAnalysis, "Stoichiometric Stability Analysis"},
#endif // COPASI_SSA
    MapNode{Method::EFMAlgorithm, "EFM Algorithm"},
    MapNode{Method::EFMBitPatternTreeAlgorithm, "Bit Pattern Tree Algorithm"},
    MapNode{Method::EFMBitPatternAlgorithm, "Bit Pattern Algorithm"},
    MapNode{Method::Householder, "Householder Reduction"},
    MapNode{Method::crossSectionMethod, "Cross Section Finder"},
    MapNode{Method::linearNoiseApproximation, "Linear Noise Approximation"},
    MapNode{Method::analyticsMethod, "Analytics Finder"},
    MapNode{Method::timeSensLsoda, "LSODA Sensitivities"}};

public:
  constexpr static CEnumAnnotation< Method, std::string_view > MethodName{_MethodName};

private:
  constexpr static CEnumAnnotationInstance _MethodXML{
    Method::UnsetMethod,
    MapNode{Method::UnsetMethod, "NotSet"},
    MapNode{Method::RandomSearch, "RandomSearch"},
    MapNode{Method::RandomSearchMaster, "RandomSearch(PVM)"},
    MapNode{Method::SimulatedAnnealing, "SimulatedAnnealing"},
    MapNode{Method::CoranaWalk, "CoranaRandomWalk"},
    MapNode{Method::DifferentialEvolution, "DifferentialEvolution"},
    MapNode{Method::DifferentialEvolution, "ScatterSearch"},
    MapNode{Method::GeneticAlgorithm, "GeneticAlgorithm"},
    MapNode{Method::EvolutionaryProgram, "EvolutionaryProgram"},
    MapNode{Method::SteepestDescent, "SteepestDescent"},
    MapNode{Method::HybridGASA, "HybridGASA"},
    MapNode{Method::GeneticAlgorithmSR, "GeneticAlgorithmSR"},
    MapNode{Method::HookeJeeves, "HookeJeeves"},
    MapNode{Method::LevenbergMarquardt, "LevenbergMarquardt"},
    MapNode{Method::NL2SOL, "NL2SOL"},
    MapNode{Method::NelderMead, "NelderMead"},
    MapNode{Method::SRES, "EvolutionaryStrategySR"},
    MapNode{Method::Statistics, "CurrentSolutionStatistics"},
    MapNode{Method::ParticleSwarm, "ParticleSwarm"},
    MapNode{Method::Praxis, "Praxis"},
    MapNode{Method::TruncatedNewton, "TruncatedNewton"},
    MapNode{Method::Newton, "EnhancedNewton"},
    MapNode{Method::deterministic, "Deterministic(LSODA)"},
    MapNode{Method::RADAU5, "Deterministic(RADAU5)"},
    MapNode{Method::LSODA2, "Deterministic(LSODA2)"},
    MapNode{Method::directMethod, "DirectMethod"},
    MapNode{Method::stochastic, "Stochastic"},
    MapNode{Method::tauLeap, "TauLeap"},
    MapNode{Method::adaptiveSA, "AdaptiveSA"},
    MapNode{Method::hybrid, "Hybrid"},
    MapNode{Method::hybridLSODA, "Hybrid (LSODA)"},
    MapNode{Method::hybridODE45, "Hybrid (DSA-ODE45)"},
    MapNode{Method::DsaLsodar, "Hybrid (DSA-LSODAR)"},
    MapNode{Method::stochasticRunkeKuttaRI5, "Stochastic Runge Kutta (RI5)"},
    MapNode{Method::tssILDM, "TimeScaleSeparation(ILDM,Deuflhard)"},
    MapNode{Method::tssILDMModified, "TimeScaleSeparation(ILDM,Modified)"},
    MapNode{Method::tssCSP, "TimeScaleSeparation(CSP)"},
    MapNode{Method::mcaMethodReder, "MCAMethod(Reder)"},
    MapNode{Method::scanMethod, "ScanFramework"},
    MapNode{Method::lyapWolf, "WolfMethod"},
    MapNode{Method::sensMethod, "SensitivitiesMethod"},
#ifdef COPASI_SSA
    MapNode{Method::stoichiometricStabilityAnalysis, "StoichiometricStabilityAnalysis"},
#endif // COPASI_SSA
    MapNode{Method::EFMAlgorithm, "EFMAlgorithm"},
    MapNode{Method::EFMBitPatternTreeAlgorithm, "EFMBitPatternTreeMethod"},
    MapNode{Method::EFMBitPatternAlgorithm, "EFMBitPatternMethod"},
    MapNode{Method::Householder, "Householder"},
    MapNode{Method::crossSectionMethod, "crossSectionMethod"},
    MapNode{Method::linearNoiseApproximation, "LinearNoiseApproximation"},
    MapNode{Method::analyticsMethod, "analyticsMethod"},
    MapNode{Method::timeSensLsoda, "Sensitivities(LSODA)"}};

public:
  constexpr static CEnumAnnotation< Method, std::string_view > MethodXML{_MethodXML};
};

#endif // COPASI_CTaskEnum
