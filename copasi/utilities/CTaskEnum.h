// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CTaskEnum
#define COPASI_CTaskEnum

#include <string>

class CTaskEnum
{
public:
  /**
   * Enumeration of the types of tasks known to COPASI.
   */
  enum Task
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
    UnsetTask
  };

  /**
   * String literals for the GUI to display type names of tasks known
   * to COPASI.
   */
  static const std::string TaskName[];

  /**
   * XML type names of tasks known to COPASI.
   */
  static const char* TaskXML[];

  /**
   * Enumeration of the sub types of methods known to COPASI.
   */
  enum Method
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
    NelderMead,
    SRES,
    Statistics,
    ParticleSwarm,
    Praxis,
    TruncatedNewton,
    Newton,
    deterministic,
    LSODAR,
    directMethod,
    stochastic,
    tauLeap,
    adaptiveSA,
    hybridODE45,
    DsaLsodar,
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
    linearNoiseApproximation
  };

  /**
   * String literals for the GUI to display sub type names of methods known
   * to COPASI.
   */
  static const std::string MethodName[];

  /**
   * XML sub type names of methods known to COPASI.
   */
  static const char* MethodXML[];
};

#endif // COPASI_CTaskEnum
