/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiTask.h,v $
   $Revision: 1.20 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/06/22 12:15:49 $
   End CVS Header */

/**
 *  CCopasiTask class.
 *  This class is used to describe a task in COPASI. This class is 
 *  intended to be used as the parent class for all tasks whithin COPASI.
 *  
 *  Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CCopasiTask
#define COPASI_CCopasiTask

#include <string>

#include "report/CCopasiContainer.h"
#include "report/CReport.h"

class CCopasiProblem;
class CCopasiMethod;
class CCallbackHandler;
class CCopasiParameterGroup;
class CProcessReport;

class CCopasiTask : public CCopasiContainer
  {
  public:
    /**
     * Enumeration of the types of tasks known to COPASI.
     */
    enum Type
    {
      steadyState = 0,
      timeCourse,
      scan,
      fluxMode,
      optimization,
      parameterFitting,
      mca,
      tss,
      unset,
    };

    /**
     * String literals for the GUI to display type names of tasks known
     * to COPASI.
     */
    static const std::string TypeName[];

    /**
     * XML type names of tasks known to COPASI.
     */
    static const char* XMLType[];

    // Attributes
  protected:
    /**
     * The type of the task
     */
    Type mType;

    /**
     * The key of the task
     */
    std::string mKey;

    /**
     * Tells whether the task is scheduled for execution
     */
    bool mScheduled;

    /**
     * The problem of the task
     */
    CCopasiProblem * mpProblem;

    /**
     * The method used to solve the problem.
     */
    CCopasiMethod * mpMethod;

    /**
     * The report used to track results of the task.
     */
    CReport mReport;

    /**
     * The output handler (at this time only for plotting)
     */
    CCallbackHandler * mpOutputHandler;

    /**
     * progress bar handler 
     */
    CProcessReport * mpProgressHandler;

    /**
     * Pointer to group of sliders associated with the task.
     */
    CCopasiParameterGroup * mpSliders;

  public:
    /**
     * Default constructor
     */
    CCopasiTask(const std::string & name = "NoName",
                const CCopasiContainer * pParent = NULL,
                const std::string & type = "Task");

    /**
     * Specific constructor
     * @param const Type & taskType
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & type (default: "Task")
     */
    CCopasiTask(const Type & taskType,
                const CCopasiContainer * pParent = NULL,
                const std::string & type = "Task");

    /**
     * Copy constructor
     * @param const CCopasiTask & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiTask(const CCopasiTask & src,
                const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CCopasiTask();

    /**
     * Retrieve the name of the task
     * @return " const string &" name
     */ 
    //    const std::string & getName() const;

    /**
     * Set the name of the task
     * @param "const string &" name
     */
    bool setName(const std::string & name);

    /**
     * Retrieve the type of the task
     * @return CCopasiTask::Type type
     */
    Type getType() const;

    /**
     * Set the type of the task
     * @param CCopasiTask::Type & type
     */
    void setType(const Type & type);

    /**
     * Convert an XMLType string to the matching enum value
     * Returns CCopasiTask::unset if no match is found.
     * @param (const char * xmlTypeName)
     * @return CCopasiTask::Type type
     */
    static
    CCopasiTask::Type XMLNameToEnum(const char * xmlTypeName);

    /**
     * Retrieve the key for the task.
     * @return std::string key
     */
    virtual const std::string & getKey() const;

    /**
     * Set whether the task is scheduled
     * @param const bool & scheduled (default: true)
     */
    void setScheduled(const bool & scheduled);

    /**
     * Check whether the task is scheduled
     * @return const bool & scheduled
     */
    const bool & isScheduled() const;

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
     * @param std::ostream * pOstream (default: NULL)
     */
    virtual bool initialize(std::ostream * pOstream = NULL);

    /**
     * Process the task
     * @return bool success
     */
    virtual bool process();

    /**
     * Process the task. This is called by the scan task.
     */
    virtual bool processForScan(bool useInitialConditions, bool doOutput);

    /**
     * Perform neccessary cleaup procedures
     */
    virtual bool restore();

    /**
     * Retrieve the problem
     */
    CCopasiProblem * getProblem();
    const CCopasiProblem * getProblem() const;

    /**
     * Set the method type applied to solve the task
     * @param const CCopasiMethod::SubType & type
     * @return bool success
     */
    virtual bool setMethodType(const int & type);

    /**
     * Retrieve the method
     */
    CCopasiMethod * getMethod();

    /**
     * Retrieve the report
     */
    CReport & getReport();

    /**
     * Cleanup function
     **/
    void cleanup();

    /**
     * set Output handler
     **/
    void setOutputHandler(CCallbackHandler* pHandler);

    /**
     * get address of output handler
     **/
    CCallbackHandler* getOutputHandlerAddr();

    /**
     * set Output handler
     **/
    void setProgressHandler(CProcessReport * pHandler);

    /**
     * Retrieve a pointer to the group of sliders.
     * @return CCopasiParameterGroup * pSliders
     */
    CCopasiParameterGroup * getSliders();
  };

#endif // COPASI_CCopasiTask
