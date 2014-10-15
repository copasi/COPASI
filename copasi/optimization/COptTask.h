// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include "utilities/CVector.h"
#include "utilities/CCopasiTask.h"
#include "utilities/CProcessReport.h"

class COptProblem;
class COptMethod;
class CReport;

class COptTask : public CCopasiTask
{
public:
  static const CTaskEnum::Method ValidMethods[];

private:
  /**
   * Default constructor
   */
  COptTask();

public:
  /**
   * Specific constructor
   * @param const CCopasiContainer * pParent
   * @param const CTaskEnum::Task & type (default: optimization)
   */
  COptTask(const CCopasiContainer * pParent,
           const CTaskEnum::Task & type = CTaskEnum::optimization);

  /**
   * Copy constructor
   * @param const COptTask & src
   */
  //-COptTask(const COptTask & src);
  COptTask(const COptTask & src, const CCopasiContainer * pParent = NULL);

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

  /**
   * Retrieve the list of valid methods
   * @return const CTaskEnum::Method * pValidMethods
   */
  virtual const CTaskEnum::Method * getValidMethods() const;
};
#endif // COPASI_COptTask
