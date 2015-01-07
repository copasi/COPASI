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
 *  CTrajectoryProblem class.
 *  This class describes the trajectory problem, i.e., it allows to specify
 *  for example initial conditions and number of steps.
 *
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CTrajectoryProblem
#define COPASI_CTrajectoryProblem

#include <string>

#include "utilities/CCopasiProblem.h"
#include "utilities/CReadConfig.h"

class CTrajectoryProblem : public CCopasiProblem
{
public:
  // Operations

  /**
   * Default constructor.
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CTrajectoryProblem(const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor.
   * @param const CTrajectoryProblem & src
   * @paramconst CCopasiContainer * pParent (default: NULL)
   */
  CTrajectoryProblem(const CTrajectoryProblem & src,
                     const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor.
   */
  ~CTrajectoryProblem();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  /**
   * Set the number of time steps the trajectory method should integrate.
   * @param "const unsigned C_INT32 &" stepNumber
   * @parem bool success
   */
  void setStepNumber(const unsigned C_INT32 & stepNumber);

  /**
   * Retrieve the number of time steps the trajectory method should integrate.
   * @return "const unsigned C_INT32 &" stepNumber
   */
  const unsigned C_INT32 & getStepNumber() const;

  /**
   * Set the size a integration step the trajectory method should do.
   * @param "const C_FLOAT64 &" stepSize
   * @parem bool success
   */
  void setStepSize(const C_FLOAT64 & stepSize);

  /**
   * Retrieve the size a integration step the trajectory method should do.
   * @return "const C_FLOAT64 &" stepSize
   */
  const C_FLOAT64 & getStepSize() const;

  /**
   * Set the end time.
   * @param "const C_FLOAT64 &" duration
   * @parem bool success
   */
  void setDuration(const C_FLOAT64 & duration);

  /**
   * Retrieve the end time.
   * @return "const C_FLOAT64 &" duration
   */
  const C_FLOAT64 & getDuration() const;

  /**
   * Set the end time.
   * @param "const C_FLOAT64 &" endTime
   */
  void setOutputStartTime(const C_FLOAT64 & endTime);

  /**
   * Retrieve the end time.
   * @return "const C_FLOAT64 &" endTime
   */
  const C_FLOAT64 & getOutputStartTime() const;

  /**
   *.
   */
  void setTimeSeriesRequested(bool flag);

  /**
   *
   */
  bool timeSeriesRequested() const;

  /**
   * Set whether to output events in addition to the normal steps
   * @param const bool & outputEvent
   */
  void setOutputEvent(const bool & outputEvent);

  /**
   * Retrieve whether to do additional output for events.
   */
  const bool & getOutputEvent() const;

  /**
   * Set whether to continue on simultaneous events
   * @param const bool & continueSimultaneousEvents
   */
  void setContinueSimultaneousEvents(const bool & continueSimultaneousEvents);

  /**
   * Retrieve whether to continue on simultaneous events.
   * @return const bool & continueSimultaneousEvents
   */
  const bool & getContinueSimultaneousEvents() const;

  void setStartInSteadyState(bool flag);
  bool getStartInSteadyState() const;

  /**
   * Load a trajectory problem
   * @param "CReadConfig &" configBuffer
   * @param "CReadConfig::Mode mode (Default: CReadConfig::NEXT)
   */
  void load(CReadConfig & configBuffer,
            CReadConfig::Mode mode = CReadConfig::NEXT);

private:
  /**
   * Initialize the method parameter
   */
  void initializeParameter();

  /**
   * This function synchronizes step size and number
   * @return bool success
   */
  bool sync();

  void initObjects();

  // Attributes
protected:
  /**
   * Pointer to parameter value for duration.
   */
  C_FLOAT64 * mpDuration;

  /**
   * Pointer to parameter value for step size.
   */
  C_FLOAT64 * mpStepSize;

  /**
   * Pointer to parameter value for step number
   */
  unsigned C_INT32 * mpStepNumber;

  /**
   * Pointer to parameter value indicating whether a time series needs to be
   * stored in memory
   */
  bool * mpTimeSeriesRequested;

  /**
   * Pointer to parameter value for  output start time
   */
  C_FLOAT64 * mpOutputStartTime;

  /**
   * Pointer to parameter value indicating whether events should be added to the
   * output
   */
  bool * mpOutputEvent;

  /**
   * Pointer to parameter value indicating whether to continue when simultaneous events
   * are encountered
   */
  bool * mpContinueSimultaneousEvents;

  /**
   * Indicates whether a time course is supposed to start in a steady state
   * realized as a CCopasiParameter
   */
  bool* mpStartInSteadyState;

  /**
   *  Indicate whether the step number or step size was set last.
   */
  bool mStepNumberSetLast;
};

#endif // COPASI_CTrajectoryProblem
