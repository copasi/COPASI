/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CSteadyStateMethod.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:02 $
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
class CState;
class CStateX;
class CEigen;
class CCallbackHandler;

class CSteadyStateMethod : public CCopasiMethod
  {
  public:
    enum ReturnCode
    {
      notFound = 0,
      found,
      foundEquilibrium
    };

  protected:
    /**
     *  A pointer to the trajectory problem.
     */
    const CSteadyStateProblem * mpProblem;

    /**
     * A pointer to the steady state
     */
    CState * mpSteadyState;

    /**
     * A pointer to the steady state
     */
    CStateX * mpSteadyStateX;

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
    CCallbackHandler * mpProgressHandler;

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
     * @param const CState * initialState
     * @param C_FLOAT64 * jacobian
     * @param CEigen * pEigenValues
     * @return CSteadyStateMethod::ReturnCode returnCode
     */
    CSteadyStateMethod::ReturnCode process(CState * pState,
                                           CStateX * pStateX,
                                           const CSteadyStateProblem * pProblem,
                                           CMatrix< C_FLOAT64 > & jacobian,
                                           CMatrix< C_FLOAT64 > & jacobianX,
                                           CEigen * pEigenValues,
                                           CEigen * pEigenValuesX,
                                           CCallbackHandler* handler);

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
    bool isEquilibrium(const C_FLOAT64 & resolution);
  };

#include "CNewtonMethod.h"

#endif // COPASI_CSteadyStateMethod
