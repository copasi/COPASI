/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptProblem.h,v $
   $Revision: 1.22 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/03/18 02:56:37 $
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

class CSteadyStateTask;
class CTrajectoryTask;
class COptFunction;
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
     * The minimum values of the parameters
     */
    CVector< const C_FLOAT64 * > mCalculateVariablesMin;

    /**
     * The maximum values of the parameters
     */
    CVector< const C_FLOAT64 * > mCalculateVariablesMax;

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
    COptFunction * mpFunction;

    std::vector< COptItem * > mOptItemList;

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
     * Set the solution value.
     * @param const C_FLOAT64 & value
     */
    void setSolutionValue(const C_FLOAT64 & value);

    /**
     * Retrieve the vector of Minimum values of the parameters
     * @return CVector< const C_FLOAT64 * > & parameterMin
     */
    CVector< const C_FLOAT64 * > & getParameterMin();

    /**
     * Retrieve the vector of maximum values of the parameters
     * @return CVector< C_FLOAT64 * > & parameterMax
     */
    CVector< const C_FLOAT64 * > & getParameterMax();

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
  };

#endif  // the end
