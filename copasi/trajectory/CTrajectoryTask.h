// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTrajectoryTask.h,v $
//   $Revision: 1.32.14.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/25 21:15:15 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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

#include "trajectory/CTrajectoryMethod.h"
#include "utilities/CCopasiTask.h"
#include "utilities/CReadConfig.h"
#include "trajectory/CTimeSeries.h"

class CTrajectoryProblem;
class CTrajectoryMethod;
class CState;

class CTrajectoryTask : public CCopasiTask
  {
    //Attributes
  public:
    /**
     * The methods which can be selected for preforming this task.
     */
    static const unsigned C_INT32 ValidMethods[];

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
     * Initialize the task. If an ostream is given this ostream is used
     * instead of the target specified in the report. This allows nested
     * tasks to share the same output device.
     * @param const OutputFlag & of
     * @param COutputHandler * pOutputHandler
     * @param std::ostream * pOstream (default: NULL)
     * @return bool success
     */
    virtual bool initialize(const OutputFlag & of,
                            COutputHandler * pOutputHandler,
                            std::ostream * pOstream);

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
