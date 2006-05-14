/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/lyap/CLyapProblem.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/05/14 16:52:24 $
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
    /**
     *  Number of exponents to calculate. 0 means all.
     */
    unsigned C_INT32 * mpExponentNumber;

    /**
     *
     */
    //bool * mpTimeSeriesRequested;

    /**
     * whether the divergence should also be calculated
     */
    bool * mpDivergenceRequested;

    /**
     *  Indicates at which point of time the calculation of exponents
     *  should be started.
     */
    C_FLOAT64 * mpTransientTime;

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
    //void setTimeSeriesRequested(bool flag);

    /**
     *
     */
    //bool timeSeriesRequested() const;

    /**
     *.
     */
    void setDivergenceRequested(bool flag);

    /**
     *
     */
    bool divergenceRequested() const;

    /**
     * This is the output method for any result of a problem. The default implementation
     * provided with CCopasiProblem. Does only print "Not implmented." To overide this
     * default behaviour one needs to reimplement the virtual printResult function.
     * @param std::ostream * ostream
     */
    virtual void printResult(std::ostream * ostream) const;

    /**
     * Load a trajectory problem
     * @param "CReadConfig &" configBuffer
     * @param "CReadConfig::Mode mode (Default: CReadConfig::NEXT)
     */
    //    void load(CReadConfig & configBuffer,
    //              CReadConfig::Mode mode = CReadConfig::NEXT);

  private:

    void initObjects();
  };

#endif
