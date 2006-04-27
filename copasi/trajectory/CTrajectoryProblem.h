/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTrajectoryProblem.h,v $
   $Revision: 1.22 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:32:17 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
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
     * Load a trajectory problem
     * @param "CReadConfig &" configBuffer
     * @param "CReadConfig::Mode mode (Default: CReadConfig::NEXT)
     */
    void load(CReadConfig & configBuffer,
              CReadConfig::Mode mode = CReadConfig::NEXT);

  private:
    /**
     * This function synchronizes step size and number
     * @parem bool success
     */
    bool sync();

    void initObjects();
  };

#endif // COPASI_CTrajectoryProblem
