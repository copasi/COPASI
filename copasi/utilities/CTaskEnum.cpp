// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CTaskEnum.h"

EnumArray< const std::string, CTaskEnum::Task >::base TaskName
{
  "Steady-State",
  "Time-Course",
  "Scan",
  "Elementary Flux Modes",
  "Optimization",
  "Parameter Estimation",
  "Metabolic Control Analysis",
  "Lyapunov Exponents",
  "Time Scale Separation Analysis",
  "Sensitivities",
  "Moieties",
  "Cross Section",
  "Linear Noise Approximation",
  "Analytics",
  "not specified"
};

const EnumArray< const std::string, CTaskEnum::Task > CTaskEnum::TaskName(TaskName);

EnumArray< const std::string, CTaskEnum::Task >::base TaskXML
{
  "steadyState",
  "timeCourse",
  "scan",
  "fluxMode",
  "optimization",
  "parameterFitting",
  "metabolicControlAnalysis",
  "lyapunovExponents",
  "timeScaleSeparationAnalysis",
  "sensitivities",
  "moieties",
  "crosssection",
  "linearNoiseApproximation",
  "analytics",
  "unset"
};

const EnumArray< const std::string, CTaskEnum::Task > CTaskEnum::TaskXML(TaskXML);

EnumArray< const std::string, CTaskEnum::Method >::base MethodName
{
  "Not set",
  "Random Search",
  "Random Search (PVM)",
  "Simulated Annealing",
  "Corana Random Walk",
  "Differential Evolution",
  "Scatter Search",
  "Genetic Algorithm",
  "Evolutionary Programming",
  "Steepest Descent",
  "Hybrid GA/SA",
  "Genetic Algorithm SR",
  "Hooke & Jeeves",
  "Levenberg - Marquardt",
  "Nelder - Mead",
  "Evolution Strategy (SRES)",
  "Current Solution Statistics",
  "Particle Swarm",
  "Praxis",
  "Truncated Newton",
  "Enhanced Newton",
  "Deterministic (LSODA)",
  "Deterministic (LSODAR)",
  "Stochastic (Direct method)",
  "Stochastic (Gibson + Bruck)",
  "Stochastic (\xcf\x84-Leap)",
  "Stochastic (Adaptive SSA/\xcf\x84-Leap)",
  "Hybrid (Runge-Kutta)",
  "Hybrid (LSODA)",
  "Hybrid (RK-45)",
  "Hybrid (DSA-LSODAR)",
  "Stochastic Runge Kutta (RI5)",
  "ILDM (LSODA,Deuflhard)",
  "ILDM (LSODA,Modified)",
  "CSP (LSODA)",
  "MCA Method (Reder)",
  "Scan Framework",
  "Wolf Method",
  "Sensitivities Method",
#ifdef COPASI_SSA
  "Stoichiometric Stability Analysis",
#endif // COPASI_SSA
  "EFM Algorithm",
  "Bit Pattern Tree Algorithm",
  "Bit Pattern Algorithm",
  "Householder Reduction",
  "Cross Section Finder",
  "Linear Noise Approximation",
  "Analytics Finder"
};

const EnumArray< const std::string, CTaskEnum::Method > CTaskEnum::MethodName(MethodName);

EnumArray< const std::string, CTaskEnum::Method >::base MethodXML
{
  "NotSet",
  "RandomSearch",
  "RandomSearch(PVM)",
  "SimulatedAnnealing",
  "CoranaRandomWalk",
  "DifferentialEvolution",
  "ScatterSearch",
  "GeneticAlgorithm",
  "EvolutionaryProgram",
  "SteepestDescent",
  "HybridGASA",
  "GeneticAlgorithmSR",
  "HookeJeeves",
  "LevenbergMarquardt",
  "NelderMead",
  "EvolutionaryStrategySR",
  "CurrentSolutionStatistics",
  "ParticleSwarm",
  "Praxis",
  "TruncatedNewton",
  "EnhancedNewton",
  "Deterministic(LSODA)",
  "Deterministic(LSODAR)",
  "Stochastic",
  "DirectMethod",
  "TauLeap",
  "AdaptiveSA",
  "Hybrid",
  "Hybrid (LSODA)",
  "Hybrid (DSA-ODE45)",
  "Hybrid (DSA-LSODAR)",
  "Stochastic Runge Kutta (RI5)",
  "TimeScaleSeparation(ILDM,Deuflhard)",
  "TimeScaleSeparation(ILDM,Modified)",
  "TimeScaleSeparation(CSP)",
  "MCAMethod(Reder)",
  "ScanFramework",
  "WolfMethod",
  "SensitivitiesMethod",
#ifdef COPASI_SSA
  "StoichiometricStabilityAnalysis",
#endif // COPASI_SSA
  "EFMAlgorithm",
  "EFMBitPatternTreeMethod",
  "EFMBitPatternMethod",
  "Householder",
  "crossSectionMethod",
  "LinearNoiseApproximation",
  "analyticsMethod"
};

const EnumArray< const std::string, CTaskEnum::Method > CTaskEnum::MethodXML(MethodXML);
