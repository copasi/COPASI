// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CLyapTask class.
 */

#ifndef COPASI_CLyapTask
#define COPASI_CLyapTask

#include "copasi/lyap/CLyapMethod.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/utilities/CReadConfig.h"

class CLyapProblem;
class CLyapMethod;
class CState;

class CLyapTask : public CCopasiTask
{
  friend class CLyapWolfMethod;

  //Attributes
private:

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
   *  Divergence averaged over the last orthonormalization interval
   */
  C_FLOAT64 mIntervalDivergence;

  /**
   *  Divergence averaged over the whole integration time
   */
  C_FLOAT64 mAverageDivergence;

  //for the progress bar
  C_FLOAT64 mPercentage;
  size_t mhProcess;

  //for updating the references
  std::vector<CDataObjectReference< C_FLOAT64 > * > mvExpRef;
  std::vector<CDataObjectReference< C_FLOAT64 > * > mvLocExpRef;

  bool mResultAvailable;
  bool mResultHasDivergence;
  size_t mModelVariablesInResult;
  size_t mNumExponentsCalculated;

private:
  /**
   * Default constructor
   */
  CLyapTask();

public:
  /**
   * Default constructor
   * @param const CDataContainer * pParent
   * @param const  CTaskEnum::Task & type (default: lyap)
   */
  CLyapTask(const CDataContainer * pParent,
            const CTaskEnum::Task & type = CTaskEnum::Task::lyap);

  /**
   * Copy constructor
   * @param const CLyapTaks &src
   * @param const CDataContainer * pParent
   */
  CLyapTask(const CLyapTask & src,
            const CDataContainer * pParent);

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

#ifndef SWIG
  /**
   * Retrieve the list of valid methods
   * @return const CTaskEnum::Method * pValidMethods
   */
  virtual const CTaskEnum::Method * getValidMethods() const;
#endif

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
  size_t modelVariablesInResult() const;

  size_t numberOfExponentsCalculated() const;

  /**
   * This is called by the method to generate the output and update the progress
   * bar. The parameter is the percentage for the progress bar.
   * The return value is the return value of the progress bar handler (and
   * determines if the calculation will be stopped).
   * If onlyProgess is true, no output is done.
   */
  bool methodCallback(const C_FLOAT64 & percentage, bool onlyProgress);

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
