// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 * CCrossSectionTask class.
 *
 * This class implements a trajectory task which is comprised of a
 * of a problem and a method. Additionally calls to the reporting
 * methods are done when initialized.
 *
 * Created for COPASI by Sven Sahle 2012
 */

#ifndef COPASI_CCrossSectionTask
#define COPASI_CCrossSectionTask

//#include "crosssection/CCrosssectionMethod.h"
#include "copasi/model/CEvent.h"
#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/utilities/CReadConfig.h"
#include "copasi/trajectory/CTimeSeries.h"

class CCrossSectionProblem;
//class CCrossSectionMethod;
class CState;

class CCrossSectionTask : public CCopasiTask
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
  CCrossSectionProblem * mpCrossSectionProblem;

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

public:
  /**
   * Default constructor
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CCrossSectionTask(const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param const CCrossSectionTask & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CCrossSectionTask(const CCrossSectionTask & src,
                    const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  ~CCrossSectionTask();

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

  /**
   * this is the static call back function that is called by the
   * process queue when an event is executed-
   */
  static void EventCallBack(void* pCSTask, CEvent::Type type);

  /**
   * This is the member function that is called by the static call back function
   * It checks if an event describes the cut plane and does all
   * the necessary analysis and output in this case
   */
  void eventCallBack(CEvent::Type type);
};
#endif // COPASI_CCrossSectionTask
