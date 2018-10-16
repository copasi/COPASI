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
 *  CTimeSensProblem class.
 *  This class describes the time sensitivities problem, i.e., it allows to specify
 *  for example initial conditions and number of steps.
 */

#ifndef COPASI_CTimeSensProblem
#define COPASI_CTimeSensProblem

#include <string>

#include "utilities/CCopasiProblem.h"
#include "utilities/CReadConfig.h"

class CTimeSensProblem : public CCopasiProblem
{
protected:
  CTimeSensProblem(const CTimeSensProblem & src);

public:
  // Operations

  /**
   * Default constructor.
   * @param const CDataContainer * pParent (default: NULL)
   */
  CTimeSensProblem(const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor.
   * @param const CTimeSensProblem & src
   * @paramconst CDataContainer * pParent (default: NULL)
   */
  CTimeSensProblem(const CTimeSensProblem & src,
                     const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CTimeSensProblem();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  /**
   * Set the number of time steps the time sensitivities method should integrate.
   * @param "const unsigned C_INT32 &" stepNumber
   * @parem bool success
   */
  void setStepNumber(const unsigned C_INT32 & stepNumber);

  /**
   * Retrieve the number of time steps the time sensitivities method should integrate.
   * @return "const unsigned C_INT32 &" stepNumber
   */
  const unsigned C_INT32 & getStepNumber() const;

  /**
   * Set the size a integration step the time sensitivities method should do.
   * @param "const C_FLOAT64 &" stepSize
   */
  void setStepSize(const C_FLOAT64 & stepSize);

  /**
   * Retrieve the size a integration step the time sensitivities method should do.
   * @return const bool & automaticStepSize
   */
  const bool & getAutomaticStepSize() const;

  /**
   * Set the size a integration step the time sensitivities method should do.
   * @param const bool & automaticStepSize
   */
  void setAutomaticStepSize(const bool & automaticStepSize);

  /**
   * Retrieve the size a integration step the time sensitivities method should do.
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
   * Pointer to parameter value indicating automatic step size.
   */
  bool * mpAutomaticStepSize;

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
   * Indicates whether a time course is supposed to start in a steady state
   * realized as a CCopasiParameter
   */
  bool* mpStartInSteadyState;

  /**
   *  Indicate whether the step number or step size was set last.
   */
  bool mStepNumberSetLast;
};

#endif // COPASI_CTimeSensProblem
