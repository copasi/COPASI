/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiProblem.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:04 $
   End CVS Header */

/**
 *  CCopasiProblem class.
 *  This class is used to describe a problem in COPASI. This class is 
 *  intended to be used as the parent class for all problems whithin COPASI.
 *  
 *  Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CCopasiProblem
#define COPASI_CCopasiProblem

#include <string>

#include "CCopasiParameterGroup.h"
#include "CVector.h"
#include "CCopasiTask.h"
#include "model/CState.h"

class CModel;

class CCopasiProblem : public CCopasiParameterGroup
  {
    // Attributes
  private:
    /**
     * The type of the problem
     */
    CCopasiTask::Type mType;

  protected:
    /**
     * The model of the problem
     */
    CModel * mpModel;

    /**
     * A vector of variables for calculate
     */
    CVector< C_FLOAT64 > mCalculateVariables;

    /**
     * A vector of results for calculate
     */
    CVector< C_FLOAT64 > mCalculateResults;

    /**
     * A vector of solution variables
     */
    CVector< C_FLOAT64 > mSolutionVariables;

    /**
     * A vector of solution results
     */
    CVector< C_FLOAT64 > mSolutionResults;

    // Operations
  private:
    /**
     * Default constructor
     */
    CCopasiProblem();

  protected:
    /**
     * Specific constructor
     * @param const CCopasiTask::Type & type
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiProblem(const CCopasiTask::Type & type,
                   const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Copy constructor
     * @param const CCopasiProblemr & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiProblem(const CCopasiProblem & src,
                   const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CCopasiProblem();

    /**
     * Retrieve the type of the problem
     * @return  const string & type
     */
    const CCopasiTask::Type & getType() const;

    /**
     * Set the model of the problem
     * @param CModel * pModel
     * @result bool succes
     */
    virtual bool setModel(CModel * pModel);

    /**
     * Retrieve the model of the problem
     * @result CModel * pModel
     */
    CModel * getModel() const;

    /**
     * Retrieve the size of the variable vectors
     * @result unsigned C_INT32 VariableSize
     */
    unsigned C_INT32 getVariableSize() const;

    /**
     * Retrieve the size of the result vectors
     * @result unsigned C_INT32 ResultSize
     */
    unsigned C_INT32 getResultSize() const;

    /**
     * Retrieve the variables for calculation
     */
    C_FLOAT64 * getCalculateVariables();

    /**
     * Retrieve the result of a calculation
     */
    C_FLOAT64 * getCalculateResults();

    /**
     * Retrieve the solution variables
     */
    C_FLOAT64 * getSolutionVariables();

    /**
     * Retrieve the results for the solution
     */
    C_FLOAT64 * getSolutionResults();

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
     * Sets the initial value (in case this applies to the specific problem)
     */
    virtual void setInitialState(const CState & initialState);
  };

#endif // COPASI_CCopasiProblem
