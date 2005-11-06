/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiTask.h,v $
   $Revision: 1.30 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/06 14:30:10 $
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
class CState;

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
      sens,
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

    /**
     * The methods which can be selected for performing this task.
     */
    static const unsigned C_INT32 ValidMethods[];

    enum OutputFlag
    {
      NO_OUTPUT = 0,                     //do no output
      OUTPUT,                            //do output, but do not initialize/finish
      OUTPUT_COMPLETE          //do output, including initialization and closing
    };

  class CDescription: public CCopasiObject
      {
      public:
        /**
         * Default constructor
         */
        CDescription(const CCopasiContainer * pParent = NULL);

        /**
         * Copy constructor
         * @param const CDescription & src
         * @param const CCopasiContainer * pParent (default: NULL)
         */
        CDescription(const CDescription & src,
                     const CCopasiContainer * pParent = NULL);

        /**
         * Destructor
         */
        virtual ~CDescription();

        /**
         * This is the output method for any object. The default implementation
         * provided with CCopasiObject uses the ostream operator<< of the object
         * to print the object.To overide this default behaviour one needs to
         * reimplement the virtual print function.
         * @param std::ostream * ostream
         */
        virtual void print(std::ostream * ostream) const;

        /**
         * Output stream operator
         * @param ostream & os
         * @param const CDescription & A
         * @return ostream & os
         */
        friend std::ostream &operator<<(std::ostream &os, const CDescription & o);
      };

  class CResult: public CCopasiObject
      {
      public:
        /**
         * Default constructor
         */
        CResult(const CCopasiContainer * pParent = NULL);

        /**
         * Copy constructor
         * @param const CResult & src
         * @param const CCopasiContainer * pParent (default: NULL)
         */
        CResult(const CResult & src,
                const CCopasiContainer * pParent = NULL);

        /**
         * Destructor
         */
        virtual ~CResult();

        /**
         * This is the output method for any object. The default implementation
         * provided with CCopasiObject uses the ostream operator<< of the object
         * to print the object.To overide this default behaviour one needs to
         * reimplement the virtual print function.
         * @param std::ostream * ostream
         */
        virtual void print(std::ostream * ostream) const;

        /**
         * Output stream operator
         * @param ostream & os
         * @param const CResult & A
         * @return ostream & os
         */
        friend std::ostream &operator<<(std::ostream &os, const CResult & o);
      };

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
     * The description of the task.
     */
    CDescription mDescription;

    /**
     * The result of the task.
     */
    CResult mResult;

    /**
     * Tells whether the task is scheduled for execution
     */
    bool mScheduled;

    /**
     * Tells whether the task shall update the model with the result.
     * The restore method must act accordingly.
     */
    bool mUpdateModel;

    /**
     * The state of the model before execution of the task. If mUpdateModel
     * is false this state is restored.
     */
    CState * mpInitialState;

    /**
     * The problem of the task
     */
    CCopasiProblem * mpProblem;

    /**
     * The method used to solve the problem.
     */
    CCopasiMethod * mpMethod;

    /**
     * The report that belongs to this specific task
     */
    CReport mReport;

    /**
     * The report actually used to track results.
     * May be an external report from some parent task
     */
    CReport* mpCurrentReport;

    /**
     * The output handler (at this time only for plotting)
     */
    CCallbackHandler * mpOutputHandler;

    /**
     * progress bar handler 
     */
    CProcessReport * mpCallBack;

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
     * @param const bool & scheduled
     */
    void setScheduled(const bool & scheduled);

    /**
     * Check whether the task is scheduled
     * @return const bool & scheduled
     */
    const bool & isScheduled() const;

    /**
     * Set whether the task must update the model
     * @param const bool & updateModel
     */
    void setUpdateModel(const bool & updateModel);

    /**
     * Check whether the task must update the modle
     * @return const bool & updateModel
     */
    const bool & isUpdateModel() const;

    /**
     * Set the call back of the task
     * @param CProcessReport * pCallBack
     * @result bool succes
     */
    virtual bool setCallBack(CProcessReport * pCallBack);

    CProcessReport * getCallBack() const;

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

    /**
     * Process the task. This is called by the scan task.
     */ 
    //virtual bool processForScan(bool useInitialConditions, bool doOutput);

    /**
     * Perform neccessary cleaup procedures
     */
    virtual bool restore();

    /**
     * Retrieve the problem
     */
    CCopasiProblem * getProblem();

    /**
     * Retrieve the problem
     */
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
     * Retrieve the method
     */
    const CCopasiMethod * getMethod() const;

    /**
     * Retrieve the report
     */
    CReport & getReport();

    /**
     * Retrieve the description
     */
    const CDescription & getDescription() const;

    /**
     * Retrieve the result
     */
    const CResult & getResult() const;

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

#ifdef XXXX
    /**
     * set Output handler
     **/
    void setProgressHandler(CProcessReport * pHandler);
#endif // XXXX

    /**
     * Retrieve a pointer to the group of sliders.
     * @return CCopasiParameterGroup * pSliders
     */
    CCopasiParameterGroup * getSliders();

    //the following methods are wrappers for doing output. They are intended
    //to hide the fact that output is done using different mechanisms, e.g. reports and plots

    virtual bool initOutput();
    virtual bool doOutput();
    virtual bool finishOutput();
    virtual bool separatorOutput();

    inline const OutputFlag & getOutputMode() const
      {return mDoOutput;};

  protected:
    OutputFlag mDoOutput;
    unsigned C_INT32 mOutputCounter;

  private:
    void initObjects();
  };

#endif // COPASI_CCopasiTask
