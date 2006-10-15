/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/Attic/CTSSTask.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 08:31:12 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CTSSTask class.
 *
 */

#ifndef COPASI_CTSSTask
#define COPASI_CTSSTask

#include <iostream>

#include "utilities/CCopasiTask.h"
#include "utilities/CMatrix.h"
#include "utilities/CReadConfig.h"
#include "tss/CTSSMethod.h"

class CTSSProblem;
class CState;
class CReportDefinitionVector;

class CTSSTask : public CCopasiTask
  {
  public:

    /**
     * Default constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTSSTask(const CCopasiContainer * pParent = & RootContainer);

    /**
     * Copy constructor
     * @param const CTSSTask & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTSSTask(const CTSSTask & src,
             const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CTSSTask();

    /**
     * Initialize the task. If an ostream is given this ostream is used
     * instead of the target specified in the report. This allows nested
     * tasks to share the same output device.
     * @param const OutputFlag & of
     * @param std::ostream * pOstream (default: NULL)
     * @return bool success
     */
    virtual bool initialize(const OutputFlag & of, std::ostream * pOstream);

    /**
     * Process the task with or without initializing to the initial state.
     * @param const bool & useInitialValues
     * @return bool success
     */
    virtual bool process(const bool & useInitialValues);

    virtual bool processForScan(bool useInitialConditions, bool doOutput);

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
                                    const CTSSTask &A);

  private:
    /**
     * cleanup()
     */
    void cleanup();
  };

#endif // COPASI_CTSSTask
