// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/lyap/CLyapTask.h,v $
//   $Revision: 1.10.14.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/25 21:15:23 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CLyapTask class.
 */

#ifndef COPASI_CLyapTask
#define COPASI_CLyapTask

#include "lyap/CLyapMethod.h"
#include "utilities/CCopasiTask.h"
#include "utilities/CReadConfig.h"
//#include "trajectory/CTimeSeries.h"

class CLyapProblem;
class CLyapMethod;
class CState;

class CLyapTask : public CCopasiTask
  {
    friend class CLyapWolfMethod;

    //Attributes
  private:

    /**
     * whether the time series should be stored in mTimeSeries
     */
    //bool mTimeSeriesRequested;

    /**
     * the time series (if requested)
     */
    //CTimeSeries mTimeSeries;

    /**
     * A pointer to the trajectory Problem
     */
    CLyapProblem * mpLyapProblem;

    /**
     * A pointer to the trajectory method
     */
    CLyapMethod * mpLyapMethod;

    /**
     *  Vectors with the result
     */
    CVector<C_FLOAT64> mLocalExponents;
    CVector<C_FLOAT64> mExponents;

    C_FLOAT64 mSumOfExponents;
    C_FLOAT64 mSumOfLocalExponents;

    /**
     *  Divergence at the point of time of the reporting
     */
    //C_FLOAT64 mDivergence;

    /**
     *  Divergence averaged over the last orthonormalization interval
     */
    C_FLOAT64 mIntervalDivergence;

    /**
     *  Divergence averaged over the whole integration time
     */
    C_FLOAT64 mAverageDivergence;

    //for the progress bar
    C_FLOAT64 mPercentage;
    unsigned C_INT32 mhProcess;

    //for updating the references
    std::vector<CCopasiObjectReference<C_FLOAT64> *> mvExpRef;
    std::vector<CCopasiObjectReference<C_FLOAT64> *> mvLocExpRef;

    bool mResultAvailable;
    bool mResultHasDivergence;
    unsigned C_INT32 mModelVariablesInResult;
    unsigned C_INT32 mNumExponentsCalculated;

  public:
    /**
     * Default constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CLyapTask(const CCopasiContainer * pParent = & RootContainer);

    /**
     * Destructor
     */
    ~CLyapTask();

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
     * Perform neccessary cleaup procedures
     */
    virtual bool restore();

    //methods needed by the result widget

    const CVector<C_FLOAT64> & exponents() const
      {return mExponents;}

    //const CVector<C_FLOAT64> & localExponents() const
    //{return mLocalExponents;}

    const C_FLOAT64 & sumOfExponents() const
      {return mSumOfExponents;}

    const C_FLOAT64 & averageDivergence() const
      {return mAverageDivergence;}

    /**
     *
     */
    bool resultAvailable() const;

    /**
     * was divergence requested for the last calculation?
     */
    bool resultHasDivergence() const;

    /**
     * how many independent variables had the model at the time of the
     * last calculation?
     */
    unsigned C_INT32 modelVariablesInResult() const;

    unsigned C_INT32 numberOfExponentsCalculated() const;

    /**
     * Set the method type applied to solve the task
     * @param const CCopasiMethod::SubType & type
     * @return bool success
     */
    virtual bool setMethodType(const int & type);

    /**
     * Loads parameters for this solver with data coming from a
     * CReadConfig object. (CReadConfig object reads an input stream)
     * @param configbuffer reference to a CReadConfig object.
     */
    //void load(CReadConfig & configBuffer);

    /**
     * gets a reference to the time series
     * @return time series
     */
    //const CTimeSeries & getTimeSeries() const;

    /**
     * Perform an output event for the current activity
     * @param const Activity & activity
     */
    virtual void output(const COutputInterface::Activity & activity);

    /**
     * This is called by the method to generate the output and update the progress
     * bar. The parameter is the percentage for the progress bar.
     * The return value is the return value of the progress bar handler (and
     * determines if the calculation will be stopped).
     */
    bool methodCallback(const C_FLOAT64 & percentage);

    /**
     * This functionality is expected from CLyapProblem but has to be implmented
     * here for the moment. This is called from the corresponding method of the problem
     */
    void printResult(std::ostream * ostream) const;

  private:
    /**
     * cleanup()
     */
    void cleanup();

    void initObjects();

    /**
     * this does calculations that need to be done before output:
     * sum of exponents, divergence, ...
     */
    void calculationsBeforeOutput();
  };
#endif // COPASI_CLyapTask
