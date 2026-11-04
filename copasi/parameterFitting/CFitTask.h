// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
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
 * CFitTask class.
 *
 * This class implements a parameter estimation task which is comprised of a
 * of a problem and a method.
 *
 */

#ifndef COPASI_CFitTask
#define COPASI_CFitTask

#include "copasi/optimization/COptTask.h"

class CFitTask : public COptTask
{
public:
  //Attributes

private:
  /**
   * Default constructor
   */
  CFitTask();

public:
  constexpr static CEnumAnnotationSubset ValidMethods{
    CTaskEnum::MethodName,
    CTaskEnum::Method::Statistics,
    std::array{
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
      CTaskEnum::Method::NL2SOL,
      CTaskEnum::Method::NelderMead,
      CTaskEnum::Method::ParticleSwarm,
      CTaskEnum::Method::Praxis,
      CTaskEnum::Method::RandomSearch,
      CTaskEnum::Method::ScatterSearch,
      CTaskEnum::Method::SimulatedAnnealing,
      CTaskEnum::Method::SteepestDescent,
      CTaskEnum::Method::TruncatedNewton}};

  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Task & type (default: parameterFitting)
   */
  CFitTask(const CDataContainer * pParent,
           const CTaskEnum::Task & type = CTaskEnum::Task::parameterFitting);

  /**
   * Copy constructor
   * @param const CFitTask & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CFitTask(const CFitTask & src,
           const CDataContainer * pParent);

  /**
   * Destructor
   */
  ~CFitTask();

  /**
   * cleanup()
   */
  void cleanup();

  /**
   * Set the call back of the task
   * @param CProcessReport * pCallBack
   * @result bool succes
   */
  bool setCallBack(CProcessReportLevel callBack) override;

  /**
   * Initialize the task. If an ostream is given this ostream is used
   * instead of the target specified in the report. This allows nested
   * tasks to share the same output device.
   * @param const OutputFlag & of
   * @param COutputHandler * pOutputHandler
   * @param std::ostream * pOstream (default: NULL)
   * @return bool success
   */
  bool initialize(const OutputFlag & of,
                          COutputHandler * pOutputHandler,
                          std::ostream * pOstream) override;

  /**
   * Process the task with or without initializing to the initial state.
   * @param const bool & useInitialValues
   * @return bool success
   */
  bool process(const bool & useInitialValues) override;

  /**
   * Fix files written with Version 4.10.55, which wrote the square root of user defined weights for the
   * parameter fitting task
   */
  void fixBuild55();

#ifndef SWIG
  /**
   * Retrieve the list of valid methods
   * @return const CTaskEnum::Method * pValidMethods
   */
  const CEnumAnnotation< CTaskEnum::Method, std::string_view > getValidMethods() const override;
#endif
};
#endif // COPASI_CFitTask
