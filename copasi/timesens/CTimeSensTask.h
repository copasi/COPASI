  // Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
 * CTimeSensTask class.
 *
 * This class implements a sensitivity task which is comprised of a
 * of a problem and a method.
 *
 * Created by copying the trajectory task
 */

#ifndef COPASI_CTimeSensTask
#define COPASI_CTimeSensTask

//#include "timesens/CTimeSensMethod.h"
#include "utilities/CCopasiTask.h"
#include "trajectory/CTimeSeries.h"

class CTimeSensProblem;
class CTimeSensMethod;
class CMathContainer;
class CSteadyStateTask;

class CTimeSensTask : public CCopasiTask
{
public:
  static const CTaskEnum::Method ValidMethods[];

private:

  static bool fle(const C_FLOAT64 & d1, const C_FLOAT64 & d2);
  static bool fl(const C_FLOAT64 & d1, const C_FLOAT64 & d2);
  static bool ble(const C_FLOAT64 & d1, const C_FLOAT64 & d2);
  static bool bl(const C_FLOAT64 & d1, const C_FLOAT64 & d2);

  /**
   * Default constructor
   */
  CTimeSensTask();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Task & type (default: timeCourse)
   */
  CTimeSensTask(const CDataContainer * pParent,
                  const CTaskEnum::Task & type = CTaskEnum::Task::timeSens);

  /**
    * Copy constructor
    * @param const CTimeSensTask & src
    * @param const CDataContainer * pParent (default: NULL)
    */
  CTimeSensTask(const CTimeSensTask & src,
                  const CDataContainer * pParent);

  /**
   * Destructor
   */
  ~CTimeSensTask();

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
   * Starts the process of integration by calling CTimeSensMethod::start
   * @param const bool & useInitialValues
   */
  void processStart(const bool & useInitialValues);

  /**
   * Integrates one step
   * @param const C_FLOAT64 & nextTime
   * @param const bool & final (default: false)
   * @return bool success;
   */
  bool processStep(const C_FLOAT64 & nextTime, const bool & final = false);

#ifndef SWIG

  /**
   * Retrieve the list of valid methods
   * @return const CTaskEnum::Method * pValidMethods
   */
  virtual const CTaskEnum::Method * getValidMethods() const;
#endif

  /**
   * gets a reference to the time series
   * @return time series
   */
  const CTimeSeries & getTimeSeries() const;

protected:
  /**
   * Signal that the math container has changed
   */
  virtual void signalMathContainerChanged();

  /**
   * Signal that the method has changed
   */
  virtual void signalMethodChanged();

private:
  /**
   * cleanup()
   */
  void cleanup();

// Attributes
protected:
  /**
   * whether the time series should be stored in mTimeSeries
   */
  bool mTimeSeriesRequested;

  /**
   * the time series (if requested)
   */
  CTimeSeries mTimeSeries;

  /**
   * A pointer to the time sensitivities Problem
   */
  CTimeSensProblem * mpTimeSensProblem;

  /**
   * Pointer to CSteadyStateTask.  To be used in processStart() to start
   * simulation in steady state
   */
  CSteadyStateTask * mpSteadyState;

  /**
   * A pointer to the time sensitivities method
   */
  CTimeSensMethod * mpTimeSensMethod;

  /**
   * Indicates whether we need to update moieties.
   */
  bool mUpdateMoieties;

  /**
   * The current state of the integration.
   */
  CVectorCore< C_FLOAT64 > mContainerState;

  /**
   * A pointer to the current time of the integration.
   */
  C_FLOAT64 * mpContainerStateTime;

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

protected:
  /**
   * A Boolean flag indication whether to proceed with the integration
   */
  bool mProceed;
};
#endif // COPASI_CTimeSensTask
