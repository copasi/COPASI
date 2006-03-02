/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CSteadyStateMethod.h,v $
   $Revision: 1.18 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/02 02:23:08 $
   End CVS Header */

/**
 *  CSteadyStateMethod class.
 *  This class describes the interface to all steady state methods.
 *  The variaous method like Netwon have to be derived from
 *  this class.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CSteadyStateMethod
#define COPASI_CSteadyStateMethod

#include <string>

#include "utilities/CCopasiMethod.h"
#include "utilities/CMatrix.h"

class CSteadyStateProblem;
class CSteadyStateTask;
class CState;
class CEigen;
class CProcessReport;
class CModel;

class CSteadyStateMethod : public CCopasiMethod
  {
  public:
    enum ReturnCode
    {
      notFound = 0,
      found,
      foundEquilibrium,
      foundNegative
    };

  protected:
    /**
     *  A pointer to the  problem.
     */
    const CSteadyStateProblem * mpProblem;

    /**
     *  A pointer to the model.
     */
    CModel * mpModel;

    /**
     *  A pointer to the task.
     */
    CSteadyStateTask * mpParentTask;

    /**
     * A pointer to the steady state
     */
    CState * mpSteadyState;

    /**
     * The jacobian of the steadystate
     */
    CMatrix< C_FLOAT64 > * mpJacobian;

    /**
     * The jacobian of the steadystate
     */
    CMatrix< C_FLOAT64 > * mpJacobianX;

    /**
     * A pointer to a CEigen object
     */
    CEigen * mpEigenValues;

    /**
     * A pointer to a CEigen object
     */
    CEigen * mpEigenValuesX;

    /**
     * A pointer to the progress bar handler
     */
    CProcessReport * mpProgressHandler;

    // Operations
  private:
    /**
     * Default constructor.
     */
    CSteadyStateMethod();

  protected:
    /**
     * Specific constructor.
     * @param CCopasiMethod::SubType subType 
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CSteadyStateMethod(CCopasiMethod::SubType subType,
                       const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Create a trajectory method.
     * Note: the returned object has to be released after use with delete
     */
    static CSteadyStateMethod *
    createSteadyStateMethod(CCopasiMethod::SubType subType
                            = CCopasiMethod::Newton);

    /**
     * Copy constructor.
     * @param "const CSteadyStateMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CSteadyStateMethod(const CSteadyStateMethod & src,
                       const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CSteadyStateMethod();

    /**
     *  Set a pointer to the problem.
     *  This method is used by CSteadyState 
     *  @param "CSteadyStateProblem *" problem
     */ 
    //void setProblem(CSteadyStateProblem * problem);

    /**
     * This instructs the method to calculate a the steady state
     * starting with the initialState given.
     * The steady state is returned in the object pointed to by steadyState.
     * @param CState * steadyState
     * @param CMatrix< C_FLOAT64 > & jacobian
     * @param CMatrix< C_FLOAT64 > & jacobianX
     * @param CEigen & EigenValues
     * @param CEigen & EigenValuesX
     * @param CProcessReport * handler
     * @return CSteadyStateMethod::ReturnCode returnCode
     */
    CSteadyStateMethod::ReturnCode process(CState * pState,
                                           CMatrix< C_FLOAT64 > & jacobian,
                                           CMatrix< C_FLOAT64 > & jacobianX,
                                           CEigen & EigenValues,
                                           CEigen & EigenValuesX,
                                           CProcessReport * handler);

    /**
     * Check if the method is suitable for this problem
     * @return bool suitability of the method
     */
    virtual bool isValidProblem(const CCopasiProblem * pProblem);

    /**
     * Initialize the method must be called before process
     * @param const CSteadyStateProblem * pProblem
     * @return bool success
     */
    virtual bool initialize(const CSteadyStateProblem * pProblem);

  protected:

    /**
     * This instructs the method to calculate a the steady state
     * starting with the initialState given.
     * The steady state is returned in the object pointed to by steadyState.
     * @return CSteadyStateMethod::ReturnCode returnCode
     */
    virtual CSteadyStateMethod::ReturnCode
    processInternal();

    /**
     * This function has to be called at the return of any implementation
     * of the protected function process()
     * @param bool steadyStateFound
     * @param const C_FLOAT64 & factor
     * @param const C_FLOAT64 & resolution
     * @return CSteadyStateMethod::ReturnCode returnCode
     */
    virtual CSteadyStateMethod::ReturnCode
    returnProcess(bool steadyStateFound,
                  const C_FLOAT64 & factor,
                  const C_FLOAT64 & resolution);

    /**
     * Check whether the steady state is chemical equilibrium
     * @param const C_FLOAT64 & resolution
     * @retrun bool isEquilibrium
     */
    bool isEquilibrium(const C_FLOAT64 & resolution) const;

    bool hasNegativeConcentrations(const C_FLOAT64 & resolution) const;
  };

#include "CNewtonMethod.h"

#endif // COPASI_CSteadyStateMethod
