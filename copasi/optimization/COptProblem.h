// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptProblem.h,v $
//   $Revision: 1.57 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/09/12 18:04:12 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include "report/CCopasiTimer.h"

#include "utilities/CCopasiProblem.h"
#include "utilities/CVector.h"
#include "utilities/CCopasiVector.h"

#include "function/CExpression.h"

class CSteadyStateTask;
class CTrajectoryTask;
class COptItem;

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
     * Default constructor
     * @param const CCopasiTask::Type & type (default: optimization)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptProblem(const CCopasiTask::Type & type = CCopasiTask::optimization,
                const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor.
     * @param const COptProblem & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptProblem(const COptProblem & src,
                const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~COptProblem();

    /**
     * This methods must be called to elevate subgroups to
     * derived objects. The default implementation does nothing.
     * @return bool success
     */
    virtual bool elevateChildren();

    /**
     * Set the model of the problem
     * @param CModel * pModel
     * @result bool success
     */
    virtual bool setModel(CModel * pModel);

    /**
     * Set the call back of the problem
     * @param CProcessReport * pCallBack
     * @result bool success
     */
    virtual bool setCallBack(CProcessReport * pCallBack);

    /**
     * Do all necessary initialization so that calls to calculate will
     * be successful. This is called once from CCopasiTask::process()
     * @result bool success
     */
    virtual bool initialize();

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
    virtual bool restore(const bool & updateModel);

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
     * Calculate the statistics for the problem
     * @param const C_FLOAT64 & factor (Default: 1.0e-003)
     * @param const C_FLOAT64 & resolution (Default: 1.0e-009)
     */
    virtual bool calculateStatistics(const C_FLOAT64 & factor = 1.0e-003,
                                     const C_FLOAT64 & resolution = 1.0e-009);

    /**
     * Retrieve the size of the variable vectors.
     * @result unsigned C_INT32 VariableSize
     */
    unsigned C_INT32 getVariableSize() const;

    /**
     * Retrieve the list of optimization parameters.
     * @return const std::vector< COptItem * > & optItemList
     */
    const std::vector< COptItem * > & getOptItemList() const;

    /**
     * Retrieve the list of constraints.
     * @return const std::vector< COptItem * > & constraintList
     */
    const std::vector< COptItem * > & getConstraintList() const;

    /**
     * Retrieve the update methods for the variables for calculation.
     * @return const std::vector< UpdateMethod * > & updateMethods
     */
    const std::vector< UpdateMethod * > & getCalculateVariableUpdateMethods() const;

    /**
     * Retrieve the result of a calculation
     */
    const C_FLOAT64 & getCalculateValue() const;

    /**
     * Retrieve the solution variables
     */
    const CVector< C_FLOAT64 > & getSolutionVariables() const;

    /**
     * Set the solution.
     * @param const C_FLOAT64 & value
     * @param const CVector< C_FLOAT64 > & variables
     * @return bool continue;
     */
    virtual bool setSolution(const C_FLOAT64 & value,
                             const CVector< C_FLOAT64 > & variables);

    /**
     * Retrieve the result for the solution
     */
    const C_FLOAT64 & getSolutionValue() const;

    /**
     * Retrieve the 'index' optimization item.
     * @param const unsigned C_INT32 & index
     * @return COptItem optItem
     */
    COptItem & getOptItem(const unsigned C_INT32 & index);

    /**
     * Retrieve the number of optimization items.
     * @return const unsigned C_INT32 size
     */
    const unsigned C_INT32 getOptItemSize() const;

    /**
     * Add an optimization item to the problem.
     * @param const CCopasiObjectName & objectCN
     * @return COptItem optItemAdded
     */
    COptItem & addOptItem(const CCopasiObjectName & objectCN);

    /**
     * Remove an optimization items.
     * @param const unsigned C_INT32 & index
     * @return bool success
     */
    bool removeOptItem(const unsigned C_INT32 & index);

    /**
     * Swap two optimization items.
     * @param const unsigned C_INT32 & iFrom
     * @param const unsigned C_INT32 & iTo
     * @return bool success
     */
    bool swapOptItem(const unsigned C_INT32 & iFrom,
                     const unsigned C_INT32 & iTo);

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
     * @param const CCopasiTask::Type & subtaskType
     * @return success
     */
    bool setSubtaskType(const CCopasiTask::Type & subtaskType);

    /**
     * Retrieve the subtask type
     * @return CCopasiTask::Type subtaskType
     */
    CCopasiTask::Type getSubtaskType() const;

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
     * Retrieve the objective function.
     * @return const unsigned C_INT32 & functionEvaluations
     */
    const unsigned C_INT32 & getFunctionEvaluations() const;

    /**
     * Retrieve the objective function.
     * @return const C_FLOAT64 & executionTime
     */
    const C_FLOAT64 & getExecutionTime() const;

    /**
     * This is the output method for any object. The default implementation
     * provided with CCopasiObject uses the ostream operator<< of the object
     * to print the object.To override this default behavior one needs to
     * reimplement the virtual print function.
     * @param std::ostream * ostream
     */
    virtual void print(std::ostream * ostream) const;

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
    virtual void printResult(std::ostream * ostream) const;

  private:
    /**
     * Allocates all group parameters and assures that they are
     * properly initialized.
     */
    void initializeParameter();

    void initObjects();

    virtual bool createObjectiveFunction();

    //    bool buildOptItemListFromParameterGroup();

    //data member
  protected:
    /**
     * A static value containing Infinity.
     */
    C_FLOAT64 mInfinity;

    /**
     * A pointer to the value of the CCopasiParameter holding the CN for the subtask
     */
    std::string * mpParmSubtaskCN;

    /**
     * A pointer to the value of the CCopasiParameter holding the ObjectiveFunctionKey
     */
    std::string * mpParmObjectiveFunctionKey;

    /**
     * A pointer to the value of the CCopasiParameter holding Maximize
     */
    bool * mpParmMaximize;

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
     * Pointer to the subtask to be used in the optimization
     */
    mutable CCopasiTask * mpSubtask;

    /**
     * The objective function which should be minimized or maximized.
     */
    CExpression * mpFunction;

    /**
     * A vector of update method to the values of the optimization items.
     */
    std::vector< UpdateMethod * > mUpdateMethods;

    /**
     * A vector of refresh methods which need to be called update all initial
     * values which depend on the optimization items.
     */
    std::vector< Refresh * > mInitialRefreshMethods;

    /**
     * A vector of refresh methods which need to be called retrieve the value
     * of the objective function.
     */
    std::vector< Refresh * > mRefreshMethods;

    /**
     * A vector of refresh methods which need to be called retrieve the values
     * of constraints.
     */
    std::vector< Refresh * > mRefreshConstraints;

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
     * A vector of solution results
     */
    C_FLOAT64 mSolutionValue;

    /**
     * Counter of evaluations
     */
    unsigned C_INT32 mCounter;

    /**
     * Counter of failed evaluations
     */
    unsigned C_INT32 mFailedCounter;

    /**
     * Counter of constraint checks
     */
    unsigned C_INT32 mConstraintCounter;

    /**
     * Counter of failed constraint checks
     */
    unsigned C_INT32 mFailedConstraintCounter;

    /**
     * A CPU Timer
     */
    CCopasiTimer mCPUTime;

    /**
     * Handle of "Best Value" process report item
     */
    unsigned C_INT32 mhSolutionValue;

    /**
     * Handle of "Function Evaluations" process report item
     */
    unsigned C_INT32 mhCounter;

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
  };

#endif  // the end
