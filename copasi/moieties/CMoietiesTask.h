// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CMoietiesTask
#define COPASI_CMoietiesTask

#include "copasi/utilities/CCopasiTask.h"

class CProcessReport;

class CMoietiesTask : public CCopasiTask
{
private:
  /**
   * Default constructor
   */
  CMoietiesTask();

public:
  /**
   * Specific constructor
   * @param const CCopasiContainer * pParent
   * @param const CTaskEnum::Task & type (default: moieties)
   */
  CMoietiesTask(const CCopasiContainer * pParent,
                const CTaskEnum::Task & type = CTaskEnum::moieties);

  /**
   * Copy constructor
   * @param const CMoietiesTask & src
   */
  //-CMoietiesTask(const CMoietiesTask & src);
  CMoietiesTask(const CMoietiesTask & src, const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  ~CMoietiesTask();

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

  /**
   * Perform necessary cleanup procedures
   */
  virtual bool restore();

  /**
   * Retrieve the list of valid methods
   * @return const CTaskEnum::Method * pValidMethods
   */
  virtual const CTaskEnum::Method * getValidMethods() const;
};
#endif // COPASI_CMoietiesTask
