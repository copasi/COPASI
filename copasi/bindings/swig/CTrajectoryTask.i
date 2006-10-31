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
     * Process the task with or without initializing to the initial state.
     * @param const bool & useInitialValues
     * @return bool success
     */
    virtual bool process(const bool & useInitialValues);

    /**
     * Starts the process of integration by calling CTrajectoryMethod::start
     * @param const bool & useInitialValues
     */
    void processStart(const bool & useInitialValues);

    /**
     * Integrates one step
     * @param const C_FLOAT64 & nextTime
     * @return bool success;
     */
    bool processStep(const C_FLOAT64 & nextTime);

    /**
     * Perform neccessary cleaup procedures
     */
    virtual bool restore();

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
    
      bool initialize(const OutputFlag & of)
      {
        return self->initialize(of,NULL);
      }  
    
    }

};


