/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CSteadyStateTask.h,v $
   $Revision: 1.17 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/10/04 09:39:27 $
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

#include "utilities/CCopasiTask.h"
#include "utilities/CMatrix.h"
#include "utilities/CReadConfig.h"
#include "CSteadyStateMethod.h"

class CSteadyStateProblem;
class CState;
class CEigen;

class CSteadyStateTask : public CCopasiTask
  {
    //Attributes
  private:
    /**
     * A pointer to the found steady state.
     */
    CState * mpSteadyState;

    /**
     * The jacobian of the steady state.
     */
    CMatrix< C_FLOAT64 > mJacobian;

    /**
     *  The CEigen to work with
     */
    CEigen * mpEigenValues;

    /**
     * The result of the steady state analysis.
     */
    CSteadyStateMethod::ReturnCode mResult;

    //Operations
  public:

    /**
     * Default constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CSteadyStateTask(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CSteadyStateTask & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CSteadyStateTask(const CSteadyStateTask & src,
                     const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CSteadyStateTask();

    /**
     * Initialize the task. If an ostream is given this ostream is used
     * instead of the target specified in the report. This allows nested 
     * tasks to share the same output device.
     * @param std::ostream * pOstream (default: NULL)
     */
    virtual bool initialize(std::ostream * pOstream = NULL);

    /**
     * Process the task
     */
    virtual bool process();

    /**
     * Loads parameters for this solver with data coming from a
     * CReadConfig object. (CReadConfig object reads an input stream)
     * @param configbuffer reference to a CReadConfig object.
     */
    void load(CReadConfig & configBuffer);

    /**
     * Retrieves a pointer to steady state.
     * @return CState * pSteadyState
     */ 
    //CState * getState();
    const CState * getState() const;

    /**
     * Retrieves a the jacobian of the steady state.
     * @return const CMatrix< C_FLOAT64 > jacobian
     */
    const CMatrix< C_FLOAT64 > & getJacobian() const;

    /**
     * Retrieves a the eigen values of the steady state.
     * @return const CEigen * eigenValues
     */
    const CEigen * getEigenValues() const;

    // Friend functions
    friend std::ostream &operator<<(std::ostream &os,
                                    const CSteadyStateTask &A);

  private:
    /**
     * cleanup()
     */
    void cleanup();
  };

#endif // COPASI_CSteadyStateTask
