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
  //Attributes

public:
  /**
   * The methods which can be selected for preforming this task.
   */
  static const unsigned int ValidMethods[];

private:
  /**
   * Default constructor
   */
  CMoietiesTask();

public:
  /**
   * Specific constructor
   * @param const CCopasiContainer * pParent
   * @param const CCopasiTask::Type & type (default: moieties)
   */
  CMoietiesTask(const CCopasiContainer * pParent,
                const CCopasiTask::Type & type = CCopasiTask::moieties);

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
   * Set the method type applied to solve the task
   * @param const CCopasiMethod::SubType & type
   * @return bool success
   */
  virtual bool setMethodType(const int & type);

  /**
   * Create a method of the specified type to solve the task.
   * It is the duty of the caller to release the CCopasiMethod.
   * @param const CCopasiMethod::SubType & type
   * @return CCopasiMethod *
   */
  virtual CCopasiMethod * createMethod(const int & type) const;
};
#endif // COPASI_CMoietiesTask
