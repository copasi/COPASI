
%{
#include "utilities/CCopasiTask.h"
%}

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
      lyap,
#ifdef COPASI_DEBUG
      tss,
      sens,
#endif // COPASI_DEBUG
#ifdef COPASI_SSA
      ssa,
#endif // COPASI_SSA
      unset,
    };

    enum OutputFlag
    {
      NO_OUTPUT = 0,                       //do no output
      OUTPUT,                              //do output, but do not initialize/finish
      OUTPUT_COMPLETE          //do output, including initialization and closing
    };
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
     * Retrieve the problem
     */
    CCopasiProblem * getProblem();

    /**
     * Retrieve the method
     */
    CCopasiMethod * getMethod();

    

};




