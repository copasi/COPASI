/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CSteadyStateTask.h,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:33:15 $
   End CVS Header */

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
class CModel;
class CReport;

class CSteadyStateTask : public CCopasiContainer
  {
    //Attributes
  private:

    CReport* mReport;

    /**
     * A pointer to the steady state problem.
     */
    CSteadyStateProblem *mpProblem;

    std::string mKey;

    /**
     * A pointer to the method choosen for the evaluation.
     */
    CSteadyStateMethod * mpMethod;

    /**
     * Flag indicating whether the task shall be executed by CopasiSE
     */
    bool mRequested;

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
    std::ostream * mpOut;

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

    inline CReport* getReport() {return mReport;};

    /**
     * Initilize the reporting feature
     * @param ofstream & out
     */
    void initializeReporting(std::ostream & out);

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
     * Set wheter the execution of the task is requested.
     * @param const bool & execute
     */
    void setRequested(const bool & requested);

    /**
     * Retrieve whether the execution of the task is requested
     * @return bool isRequested
     */
    bool isRequested() const;

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

    inline std::string getKey() const {return mKey;}

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
    friend std::ostream &operator<<(std::ostream &os, const CSteadyStateTask &A)
    {
      os << std::endl;

      if (A.mResult == CSteadyStateMethod::notFound)
        {
          os << "A STEADY STATE COULD NOT BE FOUND." << std::endl;
          os << "(below are the last unsuccessful trial values)";
        }
      else
        {
          os << "STEADY STATE SOLUTION";

          if (A.mResult == CSteadyStateMethod::foundEquilibrium)
            os << " (chemical equilibrium)";
        }

      os << std::endl;

      return os;
    }

  private:
    /**
     * cleanup()
     */
    void cleanup();
  };
#endif // COPASI_CSteadyStateTask
