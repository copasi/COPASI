// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CTSSAProblem class.
 *  This class describes the time scale separation analysis problem, i.e., it allows to specify
 *  for example initial conditions and number of steps.
 *
 */

#ifndef COPASI_CTSSAProblem
#define COPASI_CTSSAProblem

#include <string>

#include "copasi/utilities/CCopasiProblem.h"

class CTSSAProblem : public CCopasiProblem
{
  // Attributes
private:
  /**
   *
   */
  C_FLOAT64 * mpDuration;

  /**
   *
   */
  C_FLOAT64 * mpStepSize;

  /**
   *
   */
  unsigned C_INT32 * mpStepNumber;

  /**
   *
   */
  bool * mpTimeSeriesRequested;

  /**
   *
   */
  C_FLOAT64 * mpOutputStartTime;

  /**
   *  Indicate whether the step number or step size was set last.
   */
  bool mStepNumberSetLast;

protected:
  CTSSAProblem(const CTSSAProblem & src);

public:
  // Operations

  /**
   * Default constructor.
   * @param const CDataContainer * pParent (default: NULL)
   */
  CTSSAProblem(const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor.
   * @param const CTSSAProblem & src
   * @paramconst CDataContainer * pParent (default: NULL)
   */
  CTSSAProblem(const CTSSAProblem & src,
               const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CTSSAProblem();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  /**
   * Set the number of time steps the method should integrate.
   * @param "const unsigned C_INT32 &" stepNumber
   * @parem bool success
   */
  void setStepNumber(const unsigned C_INT32 & stepNumber);

  /**
   * Retrieve the number of time steps the method should integrate.
   * @return "const unsigned C_INT32 &" stepNumber
   */
  const unsigned C_INT32 & getStepNumber() const;

  /**
   * Set the size a integration step the method should do.
   * @param "const C_FLOAT64 &" stepSize
   * @parem bool success
   */
  void setStepSize(const C_FLOAT64 & stepSize);

  /**
   * Retrieve the size a integration step the  method should do.
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

private:
  /**
   * Intialize the method parameter
   */
  void initializeParameter();

  /**
   * This function synchronizes step size and number
   * @parem bool success
   */
  bool sync();

  void initObjects();

  void printResult(std::ostream * ostream) const;
};

#endif // COPASI_CTSSAProblem
