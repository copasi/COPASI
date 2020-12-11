// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CTaskContext
#define COPASI_CTaskContext

#include "copasi/OpenMP/CMathContext.h"
#include "copasi/utilities/CCopasiTask.h"

class CTaskContext: public CContext< CCopasiTask * >
{
public:
  CTaskContext() = delete;

  CTaskContext(const CTaskContext & src) = delete;

  CTaskContext(CCopasiTask * pTask);

  ~CTaskContext();

  /**
   * Set the pointer to container used for calculations
   * @param CCopasiTask * pTask
   */
  void setTask(CCopasiTask * pTask);

  /**
   * Set the pointer to container used for calculations
   * @param CMathContainer * pContainer
   */
  void setMathContainer(CMathContainer * pContainer);

  /**
   * Initialize the task. If an ostream is given this ostream is used
   * instead of the target specified in the report. This allows nested
   * tasks to share the same output device.
   * @param const OutputFlag & of
   * @param COutputHandler * pOutputHandler
   * @param std::ostream * pOstream (default: NULL)
   * @return bool success
   */
  bool initialize(const CCopasiTask::OutputFlag & of,
                  COutputHandler * pOutputHandler,
                  std::ostream * pOstream);

  /**
   * Process the task with or without initializing to the initial state.
   * @param const bool & useInitialValues
   * @return bool success
   */
  bool process(const bool & useInitialValues);

  /**
   * Perform necessary cleanup procedures
   */
  bool restore();

private:
  CMathContext mMathContext;
};

#endif // COPASI_CTaskContext
