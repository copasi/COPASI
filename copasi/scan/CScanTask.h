// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanTask.h,v $
//   $Revision: 1.31 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/10/08 23:27:57 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include "utilities/CReadConfig.h"
#include "scan/CScanMethod.h"
#include "utilities/CVector.h"
#include "scan/CScanProblem.h"

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
     * Unique Key
     */
    std::string mKey;

    /**
     * for progress bar
     */
    unsigned C_INT32 mProgress;

    /**
     * the subtask
     */
    CCopasiTask* mpSubtask;

    bool mOutputInSubtask;

    bool mAdjustInitialConditions;

  public:

    /**
     * default constructor
     */
    CScanTask(const CCopasiContainer * pParent = & RootContainer);

    /**
     * Copy constructor
     * @param const CScanTask & src
     */
    //-CScanTask(const CScanTask & src);
    CScanTask(const CScanTask & src, const CCopasiContainer * pParent = NULL);

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
     * if isLast==true this method has to decide if a spearator should
     * be generated dependend on mOutputInSubtask.
     */
    bool outputSeparatorCallback(bool isLast = false);

  protected:

    /**
     * Init the subtask
     */
    bool initSubtask(COutputHandler * pOutputHandler);
  };
#endif // COPASI_CScanTask
