// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/CTSSAProblem.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2008/02/24 16:24:38 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include "utilities/CCopasiProblem.h"
#include "utilities/CReadConfig.h"

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

    /**
     *  The initial state, i.e., the starting conditions of the trajectroy.
     */
    //CState mInitialState;

    /**
     *  The final state of the trajectory at time EndTime
     */
    //CState mEndState;

  public:
    // Operations

    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTSSAProblem(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor.
     * @param const CTSSAProblem & src
     * @paramconst CCopasiContainer * pParent (default: NULL)
     */
    CTSSAProblem(const CTSSAProblem & src,
                 const CCopasiContainer * pParent = NULL);

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

    /**
     * Load a time scale separation analysis problem
     * @param "CReadConfig &" configBuffer
     * @param "CReadConfig::Mode mode (Default: CReadConfig::NEXT)
     */
    void load(CReadConfig & configBuffer,
              CReadConfig::Mode mode = CReadConfig::NEXT);

    /**
     * Set the Deufelhard Tolerance.
     */
    void setDeufelhardTol(C_FLOAT64 value);

    /**
     * Get the Deufelhard Tolerance.
     */
    C_FLOAT64 getDeufelhardTol();

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
  };

#endif // COPASI_CTSSAProblem
