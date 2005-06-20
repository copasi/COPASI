/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptProblem.h,v $
   $Revision: 1.29 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/20 15:54:19 $
   End CVS Header */

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
    //data member
  private:
    /**
     * Pointer to CSteadyStateTask.  To be used in calculate() to select between
     * trajectory and steady state method
     */
    CSteadyStateTask * mpSteadyState;

    /**
     * Pointer to CTrajectory.  To be used in calculate() to select between
     * trajectory and steady state method
     */
    CTrajectoryTask * mpTrajectory;

    /**
     * The objective function which should be minimized or maximized.
     */
    CExpression * mpFunction;

    std::vector< COptItem * > mOptItemList;

    std::vector< UpdateMethod * > mUpdateMethods;

    /**
     * A vector of results for calculate
     */
    C_FLOAT64 mCalculateValue;

    /**
     * A vector of solution variables
     */
    CVector< C_FLOAT64 > mSolutionVariables;

    /**
     * A vector of solution results
     */
    C_FLOAT64 mSolutionValue;

    C_FLOAT64 mCounter;

    // Implementation

  public:

    /**
     * Default constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptProblem(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor.
     * @param const COptProblem & src
     * @paramconst CCopasiContainer * pParent (default: NULL)
     */
    COptProblem(const COptProblem & src,
                const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~COptProblem();

    /**
     * Set the model of the problem
     * @param CModel * pModel
     * @result bool succes
     */
    virtual bool setModel(CModel * pModel);

    /**
     * Set the call back of the problem
     * @param CProcessReport * pCallBack
     * @result bool succes
     */
    virtual bool setCallBack(CProcessReport * pCallBack);

    /**
     * Do all neccessary initialization so that calls to caluclate will 
     * be successful. This is called once from CCopasiTask::process()
     * @result bool succes
     */
    virtual bool initialize();

    /**
     * Do the calculatting based on CalculateVariables and fill
     * CalculateResults with the results. 
     * @result bool succes
     */
    virtual bool calculate();

    /**
     * calculate function for optimization
     * @result bool fullfilled
     */
    virtual bool checkParametricConstraints();

    /**
     * calculate function for optimization
     * @result bool fullfilled
     */
    virtual bool checkFunctionalConstraints();

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
     * Retrieve the update methods for the variables for calculation.
     * @return const std::vector< UpdateMethod * > & updateMethods
     */
    const std::vector< UpdateMethod * > & getCalculateVariableUpdateMethods() const;

    /**
     * Retrieve the result of a calculation
     */
    const C_FLOAT64 & getCalculateValue() const;

    /**
     * Set the solution variables.
     * @param const CVector< C_FLOAT64 > & value
     */
    void setSolutionVariables(const CVector< C_FLOAT64 > & variables);

    /**
     * Retrieve the solution variables
     */
    const CVector< C_FLOAT64 > & getSolutionVariables() const;

    /**
     * Set the solution value.
     * @param const C_FLOAT64 & value
     */
    void setSolutionValue(const C_FLOAT64 & value);

    /**
     * Retrieve the result for the solution
     */
    const C_FLOAT64 & getSolutionValue() const;

    /**
     * Set problem type : Steady State or Trajectory
     * @param: ProblemType type
     */
    void setProblemType(ProblemType type);

    /**
     * Retrieve the 'index' optimization item.
     * @param const unsigned C_INT32 & index
     * @return COptItem optItem
     */
    COptItem getOptItem(const unsigned C_INT32 & index);

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
    COptItem addOptItem(const CCopasiObjectName & objectCN);

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
     * @return bool sccuess
     */
    bool setObjectivFunction(const std::string & infix);

    /**
     * Retrieve the objective function.
     * @return const std::string infix.
     */
    const std::string getObjectFunction();

  private:
    virtual void initObjects();
  };

#endif  // the end
