// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptTask.h,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/11 23:32:54 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
    //Attributes

  public:
    /**
     * The methods which can be selected for preforming this task.
     */
    static unsigned C_INT32 ValidMethods[];

    /**
     * default constructor
     * @param const CCopasiTask::Type & type (default: optimization)
     * @param const CCopasiContainer * pParent (default: RootContainer)
     */
    COptTask(const CCopasiTask::Type & type = CCopasiTask::optimization,
             const CCopasiContainer * pParent = & RootContainer);

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
     * Set the method type applied to solve the task
     * @param const CCopasiMethod::SubType & type
     * @return bool success
     */
    virtual bool setMethodType(const int & type);

    /**
     * Do the single tasks and the output
     */
    //bool processCallback();
  };
#endif // COPASI_COptTask
