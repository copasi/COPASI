
%{
#include "utilities/CCopasiTask.h"
%}

#ifndef COPASI_DEBUG

%nodefaultctor
%nodefaultdtor

#endif /* !COPASI_DEBUG */


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
#ifdef COPASI_DEBUG
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
#endif /*COPASI_DEBUG */

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

    

};


#ifndef COPASI_DEBUG

%clearnodefaultctor
%clearnodefaultdtor

#endif /* !COPASI_DEBUG */


