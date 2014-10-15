// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/**
 * COscillationTask class.
 *
 * This class implements an oscillation detection task
 */

#ifndef COPASI_COscillationTask
#define COPASI_COscillationTask

#include "utilities/CCopasiTask.h"

class COscillationProblem;
class COscillationMethod;
class CReport;

class COscillationTask : public CCopasiTask
{
  //Attributes

public:
  /**
   * The methods which can be selected for preforming this task.
   */
  static unsigned C_INT32 ValidMethods[];

  /**
   * default constructor
   * @param const CTaskEnum::Task & type (default: optimization)
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  //COscillationTask(const CTaskEnum::Task & type = CTaskEnum::oscillation,
  //                 const CCopasiContainer * pParent = NULL);
  COscillationTask(const CTaskEnum::Task & type ,
                   const CCopasiContainer * pParent);

  /**
   * Copy constructor
   * @param const COscillationTask & src
   */
  COscillationTask(const COscillationTask & src, const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  ~COscillationTask();

  /**
   * cleanup()
   */
  void cleanup();

  /**
   * Set the call back of the task
   * @param CProcessReport * pCallBack
   * @result bool succes
   */
  virtual bool setCallBack(CProcessReport * pCallBack);

  /**
   * Initialize the task. If an ostream is given this ostream is used
   * instead of the target specified in the report. This allows nested
   * tasks to share the same output device.
   * @param const OutputFlag & of
   * @param COutputHandler * pOutputHandler
   * @param std::ostream * pOstream (default: NULL)
   * @return bool success
   */
  virtual bool initialize(const OutputFlag & of,
                          COutputHandler * pOutputHandler,
                          std::ostream * pOstream);

  /**
   * Process the task with or without initializing to the initial state.
   * @param const bool & useInitialValues
   * @return bool success
   */
  virtual bool process(const bool & useInitialValues);
};
#endif // COPASI_COscillationTask
