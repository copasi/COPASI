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

#include "../core/CEnumAnnotation.h"

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
    UnsetTask,
    __SIZE
  };

  /**
   * String literals for the GUI to display type names of tasks known
   * to COPASI.
   */
  static const CEnumAnnotation< std::string, Task > TaskName;

  /**
   * XML type names of tasks known to COPASI.
   */
  static const CEnumAnnotation< std::string, Task > TaskXML;

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
    timeSensLsoda,
    __SIZE
  };

  /**
   * String literals for the GUI to display sub type names of methods known
   * to COPASI.
   */
  static const CEnumAnnotation< std::string, Method > MethodName;

  /**
   * XML sub type names of methods known to COPASI.
   */
  static const CEnumAnnotation< std::string, Method > MethodXML;
};

#endif // COPASI_CTaskEnum
