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

#include "utilities/CMethodParameterList.h"

class CSteadyStateProblem;
class CState;
class CEigen;

using std::string;

class CSteadyStateMethod : public CMethodParameterList
  {
  public:
    static const string TypeName[];

    // Attributes
    enum Type
    {
      unspecified = 0,
      Newton
    };

    enum ReturnCode
    {
      notFound = 0,
      found,
      foundEquilibrium
    };

  protected:
    /**
     *  The type of the method
     */
    CSteadyStateMethod::Type mTypeEnum;

    /**
     *  A pointer to the trajectory problem.
     */
    CSteadyStateProblem * mpProblem;

  private:
    /**
     * A pointer to the steady state
     */
    CState * mpSteadyState;

    /**
     * The jacobian of the steadystate
     */
    C_FLOAT64 * mJacobian;

    /**
     * A pointer to a CEigen object
     */
    CEigen * mpEigenValues;

    // Operations
  protected:
    /**
     *  Default constructor.
     */
    CSteadyStateMethod();

  public:
    /**
     * Create a trajectory method.
     * Note: the returned object has to be released after use with delete
     */
    static CSteadyStateMethod *
    createSteadyStateMethod(CSteadyStateMethod::Type type
                            = CSteadyStateMethod::Newton);

    /**
     *  Copy constructor.
     *  @param "const CSteadyStateMethod &" src
     */
    CSteadyStateMethod(const CSteadyStateMethod & src);

    /**
     *  Destructor.
     */
    ~CSteadyStateMethod();

    /**
     * Retrieve the type in numeric form
     * @return const CSteadyStateMethod::Type & type 
     */
    const CSteadyStateMethod::Type & getTypeEnum() const;

    /**
     *  Set a pointer to the problem.
     *  This method is used by CSteadyState 
     *  @param "CSteadyStateProblem *" problem
     */
    void setProblem(CSteadyStateProblem * problem);

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
    CSteadyStateMethod::ReturnCode process(CState & steadyState,
                                           const CState & initialState,
                                           C_FLOAT64 * jacobian,
                                           CEigen * pEigenValues);

  protected:

    /**
     * This instructs the method to calculate a the steady state
     * starting with the initialState given.
     * The steady state is returned in the object pointed to by steadyState.
     * @param CState * steadyState
     * @param const CState * initialState
     * @return CSteadyStateMethod::ReturnCode returnCode
     */
    virtual CSteadyStateMethod::ReturnCode
    process(CState & steadyState, const CState & initialState);

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
