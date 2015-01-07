// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CTrajectoryTask class.
 *
 * This class implements a trajectory task which is comprised of a
 * of a problem and a method. Additionally calls to the reporting
 * methods are done when initialized.
 *
 * Created for COPASI by Stefan Hoops 2002
 */

#ifndef COPASI_CTrajectoryTask
#define COPASI_CTrajectoryTask

#include "trajectory/CTrajectoryMethod.h"
#include "utilities/CCopasiTask.h"
#include "utilities/CReadConfig.h"
#include "trajectory/CTimeSeries.h"

class CTrajectoryProblem;
class CTrajectoryMethod;
class CSteadyStateTask;
class CState;

class CTrajectoryTask : public CCopasiTask
{
  //Attributes
public:
  /**
   * The methods which can be selected for performing this task.
   */
  static const unsigned int ValidMethods[];

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
   * Pointer to CSteadyStateTask.  To be used in processStart() to start
   * simulation in steady state
   */
  CSteadyStateTask * mpSteadyState;

  /**
   * A pointer to the trajectory method
   */
  CTrajectoryMethod * mpTrajectoryMethod;

  /**
   * Indicates whether we need to update moieties.
   */
  bool mUpdateMoieties;

  /**
   * A pointer to the current state of the integration.
   */
  CState * mpCurrentState;

  /**
   * A pointer to the current time of the integration.
   */
  const C_FLOAT64 * mpCurrentTime;

  /**
   * A pointer to the time at which the output starts.
   */
  C_FLOAT64 mOutputStartTime;

  /**
   * A pointer to lessOrEqual comparison
   */
  bool (*mpLessOrEqual)(const C_FLOAT64 &, const C_FLOAT64 &);

  /**
   * A pointer to less comparison
   */
  bool (*mpLess)(const C_FLOAT64 &, const C_FLOAT64 &);

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
   * Perform necessary cleanup procedures
   */
  virtual bool restore();

  /**
   * Set the method type applied to solve the task
   * @param const CCopasiMethod::SubType & type
   * @return bool success
   */
  virtual bool setMethodType(const int & type);

  /**
   * Create a method of the specified type to solve the task.
   * It is the duty of the caller to release the CCopasiMethod.
   * @param const CCopasiMethod::SubType & type
   * @return CCopasiMethod *
   */
  virtual CCopasiMethod * createMethod(const int & type) const;

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
