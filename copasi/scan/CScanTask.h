/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanTask.h,v $
   $Revision: 1.24 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/27 20:32:01 $
   End CVS Header */

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
#include "CScanMethod.h"
#include "utilities/CVector.h"
#include "CScanProblem.h"

class CScanMethod;
class CReport;

class CScanTask : public CCopasiTask
  {
    //Attributes
  private:

    /**
     * Pointer to the output stream for reporting
     */
    std::ostream * mpOut;

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
     * Initialize 
     * @param ofstream & out
     */
    bool initialize(std::ostream * out);

    /**
     * Loads parameters for this solver with data coming from a
     * CReadConfig object. (CReadConfig object reads an input stream)
     * @param configbuffer reference to a CReadConfig object.
     */
    void load(CReadConfig & configBuffer);

    /**
     * Do the integration
     */
    virtual bool process();

    /**
     * Do the subtask and the output
     */
    bool processCallback();

    /**
     * output separators
     */
    bool outputSeparatorCallback();

  protected:

    /**
     * Init the subtask
     */
    bool initSubtask();
  };
#endif // COPASI_CScanTask
