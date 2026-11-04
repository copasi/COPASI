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
 * COptTask class.
 *
 * This class implements a optimization task which is comprised of a
 * of a problem and a method.
 *
 */

#ifndef COPASI_COptTask
#define COPASI_COptTask

#include "copasi/core/CVector.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/utilities/CProcessReport.h"

class COptProblem;
class COptMethod;
class CReport;

class COptTask : public CCopasiTask
{
private:
  /**
   * Default constructor
   */
  COptTask();

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
   * @param const CTaskEnum::Task & type (default: optimization)
   */
  COptTask(const CDataContainer * pParent,
           const CTaskEnum::Task & type = CTaskEnum::Task::optimization);

  /**
   * Copy constructor
   * @param const COptTask & src
   */
  //-COptTask(const COptTask & src);
  COptTask(const COptTask & src,
           const CDataContainer * pParent);

  /**
   * Destructor
   */
  ~COptTask();

  /**
   * cleanup()
   */
  void cleanup();

  /**
   * Set the call back of the task
   * @param CProcessReport * pCallBack
   * @result bool success
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

#ifndef SWIG
  /**
   * Retrieve the list of valid methods
   * @return const CTaskEnum::Method * pValidMethods
   */
  const CEnumAnnotation< CTaskEnum::Method, std::string_view > getValidMethods() const override;
#endif
};
#endif // COPASI_COptTask
