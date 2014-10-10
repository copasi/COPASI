// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CTSSATask class.
 *
 * This class implements a time scale separation analysis task which is comprised of a
 * of a problem and a method. Additionally calls to the reporting
 * methods are done when initialized.
 *
 */

#ifndef COPASI_CTSSATask
#define COPASI_CTSSATask

#include "tssanalysis/CTSSAMethod.h"
#include "utilities/CCopasiTask.h"
#include "trajectory/CTimeSeries.h"
#include "utilities/CVector.h"

class CTSSAProblem;
class CTSSAMethod;

class CTSSATask : public CCopasiTask
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
   * A pointer to the  Problem
   */
  CTSSAProblem * mpTSSAProblem;

  /**
   * A pointer to the method
   */
  CTSSAMethod * mpTSSAMethod;

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

private:
  /**
   * Default constructor
   */
  CTSSATask();

public:
  /**
   * Specific constructor
   * @param const CCopasiContainer * pParent
   * @param const CCopasiTask::Type & type (default: tssAnalysis)
   */
  CTSSATask(const CCopasiContainer * pParent,
            const CCopasiTask::Type & type = CCopasiTask::tssAnalysis);

  /**
   * Copy constructor
   * @param const CTSSATask & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CTSSATask(const CTSSATask & src,
            const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  ~CTSSATask();

  /**
   * Resizes result matrices and updates array annotations for a specific task.
   * This is used when we need to know about the data structures of a task result
   * without actually performing the task, e.g. when selecting objects for output.
   * For now we assume that this functionality is also performed when
   * initialize() is called.
   */
  virtual bool updateMatrices();

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
   * Starts the process of integration by calling CTSSAMethod::start
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
   * gets a reference to the time series
   * @return time series
   */
  const CTimeSeries & getTimeSeries() const;
};
#endif // COPASI_CTSSATask
