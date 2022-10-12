// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

/**
 * COscillationTask class.
 *
 * This class implements an oscillation detection task
 */

#ifndef COPASI_COscillationTask
#define COPASI_COscillationTask

#include "copasi/utilities/CCopasiTask.h"

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
   * @param const CDataContainer * pParent (default: NULL)
   */
  //COscillationTask(const CTaskEnum::Task & type = CTaskEnum::oscillation,
  //                 const CDataContainer * pParent = NO_PARENT);
  COscillationTask(const CTaskEnum::Task & type,
                   const CDataContainer * pParent);

  /**
   * Copy constructor
   * @param const COscillationTask & src
   */
  COscillationTask(const COscillationTask & src,
                   const CDataContainer * pParent);

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
   * @param CProcessReportLevel * pCallBack
   * @result bool succes
   */
  virtual bool setCallBack(CProcessReportLevel callBack) override;

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
