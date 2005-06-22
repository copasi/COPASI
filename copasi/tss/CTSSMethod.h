/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/Attic/CTSSMethod.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/22 15:42:42 $
   End CVS Header */

#ifndef COPASI_CTSSMethod
#define COPASI_CTSSMethod

#include <string>

#include "utilities/CCopasiMethod.h"
#include "utilities/CMatrix.h"

class CTSSProblem;
class CState;
class CStateX;
class CProcessReport;

class CTSSMethod : public CCopasiMethod
  {
  protected:
    /**
     *  A pointer to the tss problem.
     */
    const CTSSProblem * mpProblem;

    /**
     * A pointer to the progress bar handler
     */
    CProcessReport * mpProgressHandler;

    // Operations
  private:
    /**
     * Default constructor.
     */
    CTSSMethod();

  protected:
    /**
     * Specific constructor.
     * @param CCopasiMethod::SubType subType 
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTSSMethod(CCopasiMethod::SubType subType,
               const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Create a trajectory method.
     * Note: the returned object has to be released after use with delete
     */
    static CTSSMethod *
    createTSSMethod(CCopasiMethod::SubType subType
                    = CCopasiMethod::tssMethod);

    /**
     * Copy constructor.
     * @param "const CTSSMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTSSMethod(const CTSSMethod & src,
               const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CTSSMethod();

    /**
     *  Set a pointer to the problem.
     *  This method is used by CSteadyState 
     *  @param "CSteadyStateProblem *" problem
     */ 
    //void setProblem(CSteadyStateProblem * problem);

    /**
     */
    bool process(CProcessReport * handler);

    /**
     * Check if the method is suitable for this problem
     * @return bool suitability of the method
     */
    virtual bool isValidProblem(const CCopasiProblem * pProblem);

  protected:

    /**
     * This instructs the method to calculate a the steady state
     * starting with the initialState given.
     * The steady state is returned in the object pointed to by steadyState.
     * @return CTSSMethod::ReturnCode returnCode
     */
    bool processInternal();
  };

#endif // COPASI_CTSSMethod
