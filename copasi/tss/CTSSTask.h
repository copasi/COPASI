/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/Attic/CTSSTask.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/22 15:42:42 $
   End CVS Header */

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
#include "CTSSMethod.h"

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
     * @param std::ostream * pOstream (default: NULL)
     */
    virtual bool initialize(std::ostream * pOstream = NULL);

    /**
     * Process the task
     */
    virtual bool process();

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
