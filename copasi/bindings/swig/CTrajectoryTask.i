%{

#include "trajectory/CTrajectoryTask.h"

%}

class CTrajectoryTask : public CCopasiTask
{
  public:

    /**
     * Default constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTrajectoryTask(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CTrajectoryTask & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTrajectoryTask(const CTrajectoryTask & src,
                    const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    ~CTrajectoryTask();


    /**
     * Set the method type applied to solve the task
     * @param const CCopasiMethod::SubType & type
     * @return bool success
     */
    virtual bool setMethodType(const int & type);

    /**
     * Retrieves a pointer to current state of the integration.
     * @return CState * pState
     */
    CState * getState();

    /**
     * gets a reference to the time series
     * @return time series
     */
    const CTimeSeries & getTimeSeries() const;

    %extend{
    
      bool process(bool useInitialValues)
      {
        bool result=self->initialize(CCopasiTask::OUTPUT_COMPLETE,NULL);
        if(result)
        {
          result=self->process(useInitialValues);
        }
        if(result)
        {
          result=self->restore();
        }
        return result;
      }  
    
    }

};


