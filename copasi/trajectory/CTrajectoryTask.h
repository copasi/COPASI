/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTrajectoryTask.h,v $
   $Revision: 1.20 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/12/16 17:12:57 $
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
     * A pointer to the current state of the integration.
     */
    CState * mpState;

    /**
     * the time series (if requested)
     */
    CTimeSeries mTimeSeries;

    /**
     * whether the time series should be stored in mTimeSeries
     */
    bool mTimeSeriesRequested;

  public:
    /**
     * Default constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTrajectoryTask(const CCopasiContainer * pParent = & RootContainer);

    /* *
     * Copy constructor
     * @param const CTrajectoryTask & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */ 
    //CTrajectoryTask(const CTrajectoryTask & src,
    //                const CCopasiContainer * pParent = NULL);

    /* *
     * special constructor. Allows definition of a Trajectory task without loading one
     */ 
    //CTrajectoryTask(CTrajectoryProblem * pProblem,
    //                CTrajectoryMethod::SubType type =
    //                  CTrajectoryMethod::deterministic,
    //                const CCopasiContainer * pParent = NULL);

    /* *
     * special constructor. Allows definition of a Trajectory task
     * and a problem without loading one.
     *  @param "CModel *" pmodel
     *  @param "C_FLOAT64" starttime
     *  @param "C_FLOAT64" endtime
     *  @param "unsigned C_INT32" stepnumber : number of steps
     *  @param "CTrajectoryMethod::SubType" type : type of the method that will be created
     */ 
    //CTrajectoryTask(CModel * pModel,
    //                C_FLOAT64 starttime, C_FLOAT64 endtime,
    //                unsigned C_INT32 stepnumber,
    //                CTrajectoryMethod::SubType type
    //                = CTrajectoryMethod::deterministic,
    //                const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    ~CTrajectoryTask();

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
     * Process the task without any output in as few steps as possible
     * 
     */
    virtual bool processSimple(bool singleStep = false);

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

  private:
    /**
     * cleanup()
     */
    void cleanup();
  };
#endif // COPASI_CTrajectoryTask
