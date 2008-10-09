// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sensitivities/CSensTask.h,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/10/09 15:53:15 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CSensTask class.
 *
 */

#ifndef COPASI_CSensTask
#define COPASI_CSensTask

#include <iostream>

#include "utilities/CCopasiTask.h"

class CSensTask : public CCopasiTask
  {
  public:

    /**
     * Default constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CSensTask(const CCopasiContainer * pParent = & RootContainer);

    /**
     * Copy constructor
     * @param const CSensTask & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CSensTask(const CSensTask & src,
              const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CSensTask();

    /**
     * Resizes result matrices and updates array annotations.
     * This is used when we need to know about the data structures of a task result
     * without actually performing the task, e.g. when selecting objects for output.
     * For now we assume that this functionality is also performed when
     * initialize() is called.
     */
    virtual bool updateMatrices();

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
     * This is the output method for any object. The default implementation
     * provided with CCopasiObject uses the ostream operator<< of the object
     * to print the object.To overide this default behaviour one needs to
     * reimplement the virtual print function.
     * @param std::ostream * ostream
     */
    virtual void print(std::ostream * ostream) const;

    // Friend functions
    friend std::ostream &operator<<(std::ostream &os,
                                    const CSensTask &A);

  private:
    /**
     * cleanup()
     */
    void cleanup();
  };

#endif // COPASI_CSensTask
