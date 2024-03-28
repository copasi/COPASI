// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  File name: COptProblem.h
 *
 *  Programmer: Yongqun He
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the header file of the COptProblem class.
 *           It specifies the optimization problem with its own members and
 *           functions. It's used by COptAlgorithm class and COptimization class
 */

#ifndef COPTPROBLEM_H
#define COPTPROBLEM_H

#include <string>
#include <vector>

#include "copasi/core/CDataTimer.h"

#include "copasi/utilities/CCopasiProblem.h"
#include "copasi/core/CDataVector.h"
#include "copasi/core/CVector.h"

#include "copasi/function/CExpression.h"

class CSteadyStateTask;
class CTrajectoryTask;
class COptItem;
class CMathExpression;

enum ProblemType
{
  SteadyState,
  Trajectory
};

/** @dia:pos -4.4,4.15 */
class COptProblem : public CCopasiProblem
{
  // Implementation

public:
  /**
   * The methods which can be selected for performing this task.
   */
  static const CTaskEnum::Task ValidSubtasks[];

  struct sCounter
  {
    /**
    * Counter of evaluations
    */
    unsigned C_INT32 Counter {0};

    /**
    * Counter of failed evaluations (throwing Exception)
    */
    unsigned C_INT32 FailedCounterException {0};

    /**
    * Counter of failed evaluations (result NaN)
    */
    unsigned C_INT32 FailedCounterNaN {0};

    /**
    * Counter of constraint checks
    */
    unsigned C_INT32 ConstraintCounter {0};

    /**
    * Counter of failed constraint checks
    */
    unsigned C_INT32 FailedConstraintCounter {0};
  };

  /**
   * Default constructor
   * @param const CTaskEnum::Task & type (default: optimization)
   * @param const CDataContainer * pParent (default: NULL)
   */
  COptProblem(const CTaskEnum::Task & type = CTaskEnum::Task::optimization,
              const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor.
   * @param const COptProblem & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  COptProblem(const COptProblem & src,
              const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~COptProblem();

  /**
   * Calculate the objects value.
   */
  virtual void calculateValue() override;

  /**
   * Retrieve a pointer to the value of the object
   */
  virtual void * getValuePointer() const override;

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren() override;

  /**
  * Set the call back of the problem
  * @param CProcessReport * pCallBack
  * @result bool success
  */
  virtual bool setCallBack(CProcessReportLevel callBack) override;

  /**
   * Do all necessary initialization so that calls to calculate will
   * be successful. This is called once from CCopasiTask::process()
   * @result bool success
   */
  virtual bool initialize() override;

  /**
   * perform at least the initializations of the subtask that
   * must be done before the output is initialized.
   */
  virtual bool initializeSubtaskBeforeOutput();

  /**
   * Do the calculating based on CalculateVariables and fill
   * CalculateResults with the results.
   * @result bool continue
   */
  virtual bool calculate();

  /**
   * Do all necessary restore procedures so that the
   * model is in the same state as before
   * @param const bool & updateModel
   * @result bool success
   */
  virtual bool restore(const bool & updateModel) override;

  /**
   * Reset counters and objective value.
   */
  void reset();

  /**
   * Retrieve the optional sub task
   *
   * @return CCopasiTask* * pSubTask
   */
  virtual CCopasiTask * getSubTask() const override;

  /**
   * Check whether all parameters are within their boundaries.
   * @result bool within
   */
  virtual bool checkParametricConstraints();

  /**
   * Check whether all functional constraints are fulfilled.
   * @result bool fulfilled
   */
  virtual bool checkFunctionalConstraints();

  /**
   * Check whether all item intervals are valid.
   * @result bool valid
   */
  bool checkIntervals();

  /**
   * Adjust the start values so that we have valid intervals (>= 0) for all items
   * @return bool adjusted
   */
  bool adjustStartValuesForIntervals();

  /**
   * Adjust the start values so that we have valid intervals (>= 0) for all items
   * @param COptItem & optItem
   * @return bool adjusted
   */
  bool adjustStartValue(COptItem & optItem);

  /**
   * Adjust the value so that all intervals are >= 0
   * @param C_FLOAT64 * pValue
   * @param  const C_FLOAT64 & min
   * @param  const C_FLOAT64 & max
   * @return C_FLOAT64 adjusted (NaN if not adjustable)
   */
  C_FLOAT64 adjustForIntervals(C_FLOAT64 * pValue, const C_FLOAT64 & min, const C_FLOAT64 & max);

  /**
   * Calculate the RMS of the interval size for items which have invalid intervals
   * @param const C_FLOAT64 &  value
   * @return C_FLOAT64 minInterval
   */
  C_FLOAT64 evalMinimizeIntervals(const C_FLOAT64 & value);

  /**
   * Calculate the statistics for the problem
   * @param const C_FLOAT64 & factor (Default: 1.0e-003)
   * @param const C_FLOAT64 & resolution (Default: 1.0e-009)
   */
  virtual bool calculateStatistics(const C_FLOAT64 & factor = 1.0e-003,
                                   const C_FLOAT64 & resolution = 1.0e-009);

  /**
   * Retrieve the size of the variable vectors.
   * @result size_t VariableSize
   */
  size_t getVariableSize() const;

  /**
   * Retrieve the list of optimization parameters.
   * @param const bool & algorithmOrder (default: false)
   * @return const std::vector< COptItem * > & optItemList
   */
  const std::vector< COptItem * > & getOptItemList(const bool & algorithmOrder = false) const;

  /**
   * Retrieve the list of constraints.
   * @return const std::vector< COptItem * > & constraintList
   */
  const std::vector< COptItem * > & getConstraintList() const;

  /**
   * Set parameters for which calculations and checks will be performed
   * @param const CVectorCore< C_FLOAT64 > & parameters
   */
  void setParameters(const CVectorCore< C_FLOAT64 > & parameters);

// private:
  /**
   * Retrieve the update methods for the variables for calculation.
   * @param const bool & algorithmOrder (default: false)
   * @return const std::vector< UpdateMethod * > & updateMethods
   */
  CVectorCore< C_FLOAT64 * > & getContainerVariables(const bool & algorithmOrder = false) const;

protected:
  /**
   * Signal that the math container has changed
   */
  virtual void signalMathContainerChanged() override;

public:
  /**
   * Retrieve the result of a calculation
   */
  const C_FLOAT64 & getCalculateValue() const;

  /**
   * Retrieve the solution variables
   * @param const bool & algorithmOrder (default: false)
   */
  const CVector< C_FLOAT64 > & getSolutionVariables(const bool & algorithmOrder = false) const;

  /**
   * Retrieve the gradients for each solution variable.
   * @return const CVector< C_FLOAT64 > & variableGradients
   */
  const CVector< C_FLOAT64 > & getVariableGradients() const;

  /**
   * Set the solution.
   * @param const C_FLOAT64 & value
   * @param const CVector< C_FLOAT64 > & variables
   * @param const bool & algorithmOrder (default: false)
   * @return bool continue;
   */
  virtual bool setSolution(const C_FLOAT64 & value,
                           const CVector< C_FLOAT64 > & variables,
                           const bool & algorithmOrder = false);

  /**
   * Retrieve the result for the solution
   */
  const C_FLOAT64 & getSolutionValue() const;

  /**
   * Retrieve the 'index' optimization constraint.
   * @param const size_t & index
   * @return COptItem optItem
   */
  COptItem & getOptConstraint(const size_t & index);

  /**
   * Retrieve the number of optimization constraints.
   * @return const size_t size
   */
  size_t getOptConstraintSize() const;

  /**
   * Add an optimization constraint to the problem.
   * @param const CCommonName & objectCN
   * @return COptItem optItemAdded
   */
  COptItem & addOptConstraint(const CCommonName & objectCN);

  /**
   * Remove an optimization constraint.
   * @param const size_t & index
   * @return bool success
   */
  bool removeOptConstraint(const size_t & index);

  /**
   * Retrieve the 'index' optimization item.
   * @param const size_t & index
   * @return COptItem optItem
   */
  COptItem & getOptItem(const size_t & index);

  /**
   * Retrieve the number of optimization items.
   * @return const size_t size
   */
  size_t getOptItemSize() const;

  /**
   * Add an optimization item to the problem.
   * @param const CCommonName & objectCN
   * @return COptItem optItemAdded
   */
  COptItem & addOptItem(const CCommonName & objectCN);

  /**
   * Remove an optimization items.
   * @param const size_t & index
   * @return bool success
   */
  bool removeOptItem(const size_t & index);

  /**
   * Swap two optimization items.
   * @param const size_t & iFrom
   * @param const size_t & iTo
   * @return bool success
   */
  bool swapOptItem(const size_t & iFrom,
                   const size_t & iTo);

  /**
   * Set optimization function
   * @param const std::string & infix
   * @return bool success
   */
  bool setObjectiveFunction(const std::string & infix);

  /**
   * Retrieve the objective function.
   * @return const std::string infix.
   */
  const std::string getObjectiveFunction();

  /**
   * Set subtask type
   * @param const CTaskEnum::Task & subtaskType
   * @return CCommonName
   */
  CCommonName setSubtaskType(const CTaskEnum::Task & subtaskType);

  /**
   * Retrieve the subtask type
   * @return CTaskEnum::Task subtaskType
   */
  CTaskEnum::Task getSubtaskType() const;

  /**
   * Set whether we have to maximize the objective function
   * @param const bool & maximize
   */
  void setMaximize(const bool & maximize);

  /**
   * Check whether we have to maximize
   * @return const bool & maximize
   */
  const bool & maximize() const;

  /**
   * Set whether we have to randomize start values
   * @param const bool & randomize
   */
  void setRandomizeStartValues(const bool & randomize);

  /**
   * Retrieve whether we have to calculate statistics
   * @return const bool & randomize
   */
  const bool & getRandomizeStartValues() const;

  /**
   * Randomize the start values if requested
   */
  void randomizeStartValues();

  /**
   * Remember the start values;
   */
  void rememberStartValues();

  /**
   * Set whether we have to calculate statistics
   * @param const bool & calculate
   */
  void setCalculateStatistics(const bool & calculate);

  /**
   * Retrieve whether we have to calculate statistics
   * @return const bool & maximize
   */
  const bool & getCalculateStatistics() const;

  /**
   * Retrieve the evaluation counter.
   * @return const unsigned C_INT32 & functionEvaluations
   */
  const unsigned C_INT32 & getFunctionEvaluations() const;

  /**
   * Retrieve the constraint evaluation counter.
   * @return const unsigned C_INT32 & constraintCounter
   */
  const unsigned C_INT32 & getConstraintEvaluations() const;

  /**
   * Adds increment to the internal counters
   * @param const sCounter & increment
   */
  void incrementCounters(const sCounter & increment);

  /**
   * Retrieve the internal counter
   * @return const sCounter & counter
   */
  const sCounter & getCounters() const;

  /**
   * Resets the internal counter
   */
  void resetCounters();

  /**
   * Retrieve the counter of failed Evaluations (Exception)
   * @return const unsigned C_INT32 & failedEvaluationsExc
   */
  const unsigned C_INT32 & getFailedEvaluationsExc() const;

  /**
   * Retrieve the counter of failed Evaluations (NaN)
   * @return const unsigned C_INT32 & failedEvaluationsNaN
   */
  const unsigned C_INT32 & getFailedEvaluationsNaN() const;

  /**
   * Retrieve the counter of failed Constraint Evaluations
   * @return const unsigned C_INT32 & failedConstraintCounter
   */
  const unsigned C_INT32 & geFailedConstraintCounter() const;

  /**
   * Retrieve the objective function.
   * @return const C_FLOAT64 & executionTime
   */
  const C_FLOAT64 & getExecutionTime() const;

  /**
   * This is the output method for any object. The default implementation
   * provided with CDataObject uses the ostream operator<< of the object
   * to print the object.To override this default behavior one needs to
   * reimplement the virtual print function.
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const override;

  /**
   * Output stream operator
   * @param ostream & os
   * @param const COptProblem & A
   * @return ostream & os
   */
  friend std::ostream &operator<<(std::ostream &os, const COptProblem & o);

  /**
   * This is the output method for any result of a problem. The default implementation
   * provided with CCopasiProblem. Does only print "Not implemented." To override this
   * default behavior one needs to reimplement the virtual printResult function.
   * @param std::ostream * ostream
   */
  virtual void printResult(std::ostream * ostream) const override;

protected:
  /**
   * Do all necessary restore procedures for the container
   * is in the same state as before or the new state if update is true.
   * @param const bool & update
   */
  virtual void updateContainer(const bool & update);

private:
  /**
   * Allocates all group parameters and assures that they are
   * properly initialized.
   */
  void initializeParameter();

  void initObjects();

  //data member

  static C_FLOAT64 MissingValue;

protected:
  /**
   * A static value containing Infinity.
   */
  C_FLOAT64 mWorstValue;

  /**
   * A pointer to the value of the CCopasiParameter holding the CN for the subtask
   */
  std::string * mpParmSubTaskCN;

  /**
   * A pointer to the value of the CCopasiParameter holding the infix expression
   * of the objective function
   */
  std::string * mpParmObjectiveExpression;

  /**
   * A pointer to the value of the CCopasiParameter holding Maximize
   */
  bool * mpParmMaximize;

  /**
   * A pointer to the value of the CCopasiParameter holding Randomize Start Values
   */
  bool * mpParmRandomizeStartValues;

  /**
   * A pointer to the value of the CCopasiParameter holding Calculate Statistics
   */
  bool * mpParmCalculateStatistics;

  /**
   * A pointer to the value of the CCopasiParameterGroup holding the OptimizationItems
   */
  CCopasiParameterGroup * mpGrpItems;

  /**
   * A pointer to the value of the CCopasiParameter holding the OptimizationConstraints
   */
  CCopasiParameterGroup * mpGrpConstraints;

  /**
   * A pointer to the vector of optimization items
   */
  std::vector<COptItem *> * mpOptItems;

  /**
   * A pointer to the vector of optimization constraints
   */
  std::vector<COptItem *> * mpConstraintItems;

  /**
   * Pointer to the source of the subtask to be used in the optimization
   */
  CCopasiTask * mpSubTaskSrc;

  /**
   * Pointer to the subtask to be used in the optimization
   */
  mutable CCopasiTask * mpSubTask;

  /**
   * The objective function which should be minimized or maximized.
   */
  CExpression * mpObjectiveExpression;

  /**
   * The objective function which should be minimized or maximized.
   */
  CMathExpression * mpMathObjectiveExpression;

  /**
   * A vector of refresh methods which need to be called update all initial
   * values which depend on the optimization items.
   */
  CCore::CUpdateSequence mInitialRefreshSequence;

  /**
   * A vector of refresh methods which need to be called retrieve the value
   * of the objective function.
   */
  CCore::CUpdateSequence  mUpdateObjectiveFunction;

  /**
   * A vector of refresh methods which need to be called retrieve the values
   * of constraints.
   */
  CCore::CUpdateSequence mUpdateConstraints;

  /**
   * A vector of refresh methods which need to be called retrieve the values
   * of constraints.
   */
  CCore::CUpdateSequence mUpdateIntervals;

  /**
   * A vector of results for calculate
   */
  C_FLOAT64 mCalculateValue;

  /**
   * A vector of solution variables
   */
  CVector< C_FLOAT64 > mSolutionVariables;

  /**
   * A vector of solution variables
   */
  CVector< C_FLOAT64 > mOriginalVariables;

  /**
   * A vector of pointer to the container variables
   */
  mutable CVector< C_FLOAT64 * > mContainerVariables;

  sCounter mCounters;

  /**
   * A vector of solution results
   */
  C_FLOAT64 mSolutionValue;

  /**
   * A CPU Timer
   */
  CCopasiTimer mCPUTime;

  /**
   * Handle of "Best Value" process report item
   */
  size_t mhSolutionValue;

  /**
   * Handle of "Function Evaluations" process report item
   */
  size_t mhCounter;

  /**
   * Indicates whether the results shall be stored. The default
   * is false.
   */
  bool mStoreResults;

  /**
   * Indicates whether the statistics have been calculated for
   * the current result
   */
  bool mHaveStatistics;

  /**
   * The gradient vector for the parameters
   */
  CVector< C_FLOAT64 > mGradient;

  /**
   * The value of the smallest interval
   */
  C_FLOAT64 mMinInterval;

  /**
   * A pointer to the value to be adjusted to create valid intervals
   */
  C_FLOAT64 * mpAdjust;

  /**
   * The set of COptItems which intervals are adjusted
   */
  std::set< COptItem * > mAdjustedItems;

  /**
   * Number of items influencing intervals
   */
  size_t mCountInfluencingIntervals;

  std::map< COptItem *, size_t > mOptItem2Index;

  std::vector< COptItem * > mOptItemAlgorithm;

  mutable CVector < C_FLOAT64 * > mContainerVariablesAlgorithm;

  CVector < C_FLOAT64 > mSolutionVariablesAlgorithm;
};

#endif  // the end
