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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CCopasiTimer
#define COPASI_CCopasiTimer

#include "copasi/core/CDataObject.h"
#include "utilities/CopasiTime.h"

class CCopasiTimer: public CDataObject
{
public:
  /**
   * Enumeration of timer types
   */
  enum Type
  {
    WALL = 0,
    PROCESS,
    THREAD
  };

  // Operations
  /**
   * Default constructor
   * @param const Type & type (default: WALL)
   * @param const CDataContainer * pParent (default: NULL)
   */
  CCopasiTimer(const Type & type = WALL,
               const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param const CCopasiTimer & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CCopasiTimer(const CCopasiTimer & src,
               const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CCopasiTimer();

  /**
   * Start or restart the timer.
   * @return bool success
   */
  bool start();

  /**
   * Calculate the objects value.
   */
  virtual void calculateValue();

  /**
   * Retrieve the elapsed time.
   * @return const CCopasiTimeVariable & elapsedTime
   */
  const CCopasiTimeVariable & getElapsedTime() const;

  /**
   * Retrieve the elapsed time in seconds.
   * @return const C_FLOAT64 & elapsedTimeSeconds
   */
  const C_FLOAT64 & getElapsedTimeSeconds() const;

  /**
   * This is the output method for any object. The default implementation
   * provided with CDataObject uses the ostream operator<< of the object
  * to print the object. To override this default behavior one needs to
   * reimplement the virtual print function.
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const;

  virtual void * getValuePointer() const;

private:
  // Attributes
  /**
   * The timer type
   */
  Type mType;

  /**
   * The start time of the timer.
   */
  CCopasiTimeVariable mStartTime;

  /**
   * The elapsed time of the timer.
   */
  CCopasiTimeVariable mElapsedTime;

  /**
   * The elapsed time as a double used for reporting.
   */
  C_FLOAT64 mElapsedTimeSeconds;
};

#endif // COPASI_CCopasiTimer
