/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTrajectoryTask.h,v $
   $Revision: 1.25.2.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/01/18 18:02:32 $
   End CVS Header */

/**
 * CTrajectoryTask class.
 *
 * This class implements a trajectory task which is comprised of a
 * of a problem and a method. Additionally calls to the reporting 
 * methods are done when initialized.
 *  
 * Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CTrajectoryTask
#define COPASI_CTrajectoryTask

#include "CTrajectoryMethod.h"
#include "utilities/CCopasiTask.h"
#include "utilities/CReadConfig.h"
#include "CTimeSeries.h"

class CTrajectoryProblem;
class CTrajectoryMethod;
class CState;

class CTrajectoryTask : public CCopasiTask
  {
    //Attributes
  private:

    /**
     * whether the time series should be stored in mTimeSeries
     */
    bool mTimeSeriesRequested;

    /**
     * the time series (if requested)
     */
    CTimeSeries mTimeSeries;

    /**
     * A pointer to the trajectory Problem
     */
    CTrajectoryProblem * mpTrajectoryProblem;

    /**
     * A pointer to the trajectory method
     */
    CTrajectoryMethod * mpTrajectoryMethod;

    /**
     * A pointer to the current state of the integration.
     */
    CState * mpCurrentState;

    /**
     * A pointer to the current time of the integration.
     */
    const C_FLOAT64 * mpCurrentTime;

  public:
    /**
     * Default constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTrajectoryTask(const CCopasiContainer * pParent = & RootContainer);

    /**
     * Destructor
     */
    ~CTrajectoryTask();

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
     * Process the task without any output in as few steps as possible
     * 
     */ 
    // virtual bool processSimple(bool singleStep = false);

    /**
     * Process the task (called by Scan task)
     */ 
    //virtual bool processForScan(bool useInitialConditions, bool doOutput);

    /**
     * Set the method type applied to solve the task
     * @param const CCopasiMethod::SubType & type
     * @return bool success
     */
    virtual bool setMethodType(const int & type);

    /**
     * Loads parameters for this solver with data coming from a
     * CReadConfig object. (CReadConfig object reads an input stream)
     * @param configbuffer reference to a CReadConfig object.
     */
    void load(CReadConfig & configBuffer);

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

    virtual bool initOutput();
    virtual bool doOutput();
    virtual bool finishOutput();

  private:
    /**
     * cleanup()
     */
    void cleanup();
  };
#endif // COPASI_CTrajectoryTask
