/**
 * CSteadyStateTask class.
 *
 * This class implements a steady state task which is comprised of a
 * of a problem and a method. Additionally calls to the reporting 
 * methods are done when initialized.
 *  
 * Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CSteadyStateTask
#define COPASI_CSteadyStateTask

#include <iostream>

#include "utilities/CReadConfig.h"
#include "utilities/CWriteConfig.h"
#include "CSteadyStateMethod.h"

class CSteadyStateProblem;
class CState;
class COutputEvent;
class CEigen;

using std::ostream;
using std::endl;

class CSteadyStateTask
  {
    //Attributes
  private:

    /**
     * A pointer to the steady state problem.
     */
    CSteadyStateProblem *mpProblem;

    /**
     * A pointer to the method choosen for the evaluation.
     */
    CSteadyStateMethod * mpMethod;

    /**
     * A pointer to the found steady state.
     */
    CState * mpSteadyState;

    /**
     * The result of the steady state analysis.
     */
    CSteadyStateMethod::ReturnCode mResult;

    /**
     * The jacobian of the steady state.
     */
    CMatrix< C_FLOAT64 > mJacobian;

    /**
     *  The CEigen to work with
     */
    CEigen * mpEigenValues;

    /**
     * End Phase Output Event
     */
    COutputEvent *mpOutEnd;

    /**
     * Pointer to the output stream for reporting
     */
    std::ofstream * mpOut;

    //Operations
  public:
    /**
     * default constructor
     */
    CSteadyStateTask();

    /**
     * Copy constructor
     * @param const CSteadyStateTask & src
     */
    CSteadyStateTask(const CSteadyStateTask & src);

    /**
     * Destructor
     */
    ~CSteadyStateTask();

    /**
     * cleanup()
     */
    void cleanup();

    /**
     * Initilize the reporting feature
     * @param ofstream & out
     */
    void initializeReporting(std::ofstream & out);

    /**
     * Loads parameters for this solver with data coming from a
     * CReadConfig object. (CReadConfig object reads an input stream)
     * @param configbuffer reference to a CReadConfig object.
     */
    void load(CReadConfig & configBuffer);

    /**
     * Saves the parameters of the solver to a CWriteConfig object.
     * (Which usually has a file attached but may also have socket)
     * @param configbuffer reference to a CWriteConfig object.
     */
    void save(CWriteConfig & configBuffer);

    /**
     * Retrieve the steady state problem.
     * @return CSteadyStateProblem * pProblem
     */
    CSteadyStateProblem * getProblem();

    /**
     * Set the steady state problem
     * @param CSteadyStateProblem * pProblem
     */
    void setProblem(CSteadyStateProblem * pProblem);

    /**
     * Retrieve the method choosen.
     * @return CSteadyStateMethod * pMethod
     */
    CSteadyStateMethod * getMethod();

    /**
     * Set the method to be used for finding the steady state.
     * @param CSteadyStateMethod * pMethod
     */
    void setMethod(CSteadyStateMethod * pMethod);

    /**
     * Retrieves a pointer to steady state.
     * @return CState * pSteadyState
     */
    CState * getState();

    /**
     * Retrieves a the jacobian of the steady state.
     * @return const CMatrix< C_FLOAT64 > jacobian
     */
    const CMatrix< C_FLOAT64 > & getJacobian() const;

    /**
     * Retrieves a the eigen values of the steady state.
     * @return const CEigen * eigenValues
     */
    const CEigen * getEigenValues();

    /**
     * Do the integration
     */
    void process();

    // Friend functions
    friend ostream &operator<<(ostream &os, const CSteadyStateTask &A)
    {
      os << endl;

      if (A.mResult == CSteadyStateMethod::notFound)
        {
          os << "A STEADY STATE COULD NOT BE FOUND." << endl;
          os << "(below are the last unsuccessful trial values)";
        }
      else
        {
          os << "STEADY STATE SOLUTION";

          if (A.mResult == CSteadyStateMethod::foundEquilibrium)
            os << " (chemical equilibrium)";
        }

      os << endl;

      return os;
    }
  };
#endif // COPASI_CSteadyStateTask
