/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiTask.h,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/06/25 15:06:29 $
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

    /**
     * Perform neccessary cleaup procedures
     */
    virtual bool restore();

    /**
     * Retrieve the problem
     */
    CCopasiProblem * getProblem();

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
  };

#endif // COPASI_CCopasiTask
