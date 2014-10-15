// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CTaskEnum.h"

const std::string CTaskEnum::TaskName[] =
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
  "not specified",
  ""
};

const char* CTaskEnum::TaskXML[] =
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
  "unset",
  NULL
};

const std::string CTaskEnum::MethodName[] =
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
  "Hybrid (ODE45)",
  "Hybrid (DSA-LSODAR)",
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
  ""
};

const char * CTaskEnum::MethodXML[] =
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
  "Hybrid (DSA-ODE45)",
  "Hybrid (DSA-LSODAR)",
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
  NULL
};
