/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/lyap/CLyapProblem.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/05/04 10:54:43 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CLyapProblem class.
 */

#ifndef COPASI_CLyapProblem
#define COPASI_CLyapProblem

#include <string>

#include "utilities/CCopasiProblem.h"
//#include "utilities/CReadConfig.h"

class CLyapProblem : public CCopasiProblem
  {
    // Attributes
  private:
    //C_FLOAT64 * mpDuration;

    /**
     *
     */
    //C_FLOAT64 * mpStepSize;

    /**
     *
     */
    //unsigned C_INT32 * mpStepNumber;

    /**
     *  Number of exponents to calculate. 0 means all.
     */
    unsigned C_INT32 * mpExponentNumber;

    /**
     *
     */
    bool * mpTimeSeriesRequested;

    /**
     *  Indicates how at which point of time the calculation of exponents
     *  should be started.
     */
    C_FLOAT64 * mpTransientTime;

    /**
     *  Indicate whether the step number or step size was set last.
     */
    //bool mStepNumberSetLast;

  public:
    // Operations

    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CLyapProblem(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor.
     * @param const CTrajectoryProblem & src
     * @paramconst CCopasiContainer * pParent (default: NULL)
     */
    CLyapProblem(const CLyapProblem & src,
                 const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CLyapProblem();

    /**
     * This methods must be called to elevate subgroups to
     * derived objects. The default implementation does nothing.
     * @return bool success
     */
    virtual bool elevateChildren();

    /**
     * Set the number of exponents to calculate
     * @param "const unsigned C_INT32 &"
     */
    void setExponentNumber(const unsigned C_INT32 & number);

    /**
     * Retrieve the number of exponents to calculate.
     * @return "const unsigned C_INT32 &"
     */
    const unsigned C_INT32 & getExponentNumber() const;

    /**
     * Set the size a integration step the trajectory method should do.
     * @param "const C_FLOAT64 &" stepSize
     * @parem bool success
     */
    //void setStepSize(const C_FLOAT64 & stepSize);

    /**
     * Retrieve the size a integration step the trajectory method should do.
     * @return "const C_FLOAT64 &" stepSize
     */
    //const C_FLOAT64 & getStepSize() const;

    /**
     * Set the end time.
     * @param "const C_FLOAT64 &" duration
     * @parem bool success
     */
    //void setDuration(const C_FLOAT64 & duration);

    /**
     * Retrieve the end time.
     * @return "const C_FLOAT64 &" duration
     */
    //const C_FLOAT64 & getDuration() const;

    /**
     * Set the end time.
     * @param "const C_FLOAT64 &" endTime
     */
    void setTransientTime(const C_FLOAT64 & endTime);

    /**
     * Retrieve the end time.
     * @return "const C_FLOAT64 &" endTime
     */
    const C_FLOAT64 & getTransientTime() const;

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
    //    void load(CReadConfig & configBuffer,
    //              CReadConfig::Mode mode = CReadConfig::NEXT);

  private:
    /**
     * This function synchronizes step size and number
     * @parem bool success
     */
    //bool sync();

    void initObjects();
  };

#endif // COPASI_CTrajectoryProblem
