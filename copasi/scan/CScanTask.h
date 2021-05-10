// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CScanTask class.
 *
 * This class implements a scan task which is comprised of a
 * of a problem and a method.
 *
 */

#ifndef COPASI_CScanTask
#define COPASI_CScanTask

#include "copasi/core/CVector.h"
#include "copasi/utilities/CReadConfig.h"
#include "copasi/scan/CScanMethod.h"
#include "copasi/scan/CScanProblem.h"

class CScanMethod;
class CReport;

class CScanTask : public CCopasiTask
{
  //Attributes
private:

  /**
   * Pointer to the output stream for reporting
   */
  //std::ostream * mpOut;

  /**
   * for progress bar
   */
  unsigned C_INT32 mProgress;

  /**
   * Handle to process item
   */
  size_t mhProgress;

  /**
   * the subtask
   */
  CCopasiTask* mpSubTask;

  bool mOutputInSubtask;

  bool mUseInitialValues;

private:
  /**
   * Default constructor
   */
  CScanTask();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Task & type (default: scan)
   */
  CScanTask(const CDataContainer * pParent,
            const CTaskEnum::Task & type = CTaskEnum::Task::scan);

  /**
   * Copy constructor
   * @param const CScanTask & src
   */
  //-CScanTask(const CScanTask & src);
  CScanTask(const CScanTask & src,
            const CDataContainer * pParent);

  /**
   * Destructor
   */
  ~CScanTask();

  /**
   * cleanup()
   */
  void cleanup();

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

#ifndef SWIG

  /**
   * Retrieve the list of valid methods
   * @return const CTaskEnum::Method * pValidMethods
   */
  virtual const CTaskEnum::Method * getValidMethods() const;
#endif

  /**
   * Loads parameters for this solver with data coming from a
   * CReadConfig object. (CReadConfig object reads an input stream)
   * @param configbuffer reference to a CReadConfig object.
   */
  void load(CReadConfig & configBuffer);

  /**
   * Do the subtask and the output
   */
  bool processCallback();

  /**
   * output separators
   * if isLast==true this method has to decide if a separator should
   * be generated dependent on mOutputInSubtask.
   */
  bool outputSeparatorCallback(bool isLast = false);

  /**
   * Fix files written with Version 4.12.81 and earlier, which wrote the exp(mean) and exp(std. deviation) for
   * normal random distributions in the scan task.
   */
  void fixBuild81();

protected:

  /**
   * Init the subtask
   * @param const OutputFlag & of
   * @param COutputHandler * pOutputHandler
   * @return success
   */
  bool initSubtask(const OutputFlag & of,
                   COutputHandler * pOutputHandler,
                   std::ostream * pOstream);
};
#endif // COPASI_CScanTask
