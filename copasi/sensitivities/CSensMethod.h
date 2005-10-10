/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sensitivities/CSensMethod.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/10/10 16:13:43 $
   End CVS Header */

#ifndef COPASI_SENSMethod
#define COPASI_SENSMethod

#include <string>

#include "utilities/CCopasiMethod.h" 
//#include "utilities/CMatrix.h"

#include "utilities/CAnnotatedMatrix.h"

class CSensProblem;
class CState;
class CStateX;
//class CProcessReport;

class CSensMethod : public CCopasiMethod
  {
  protected:
    /**
     *  A pointer to the tss problem.
     */
    const CSensProblem * mpProblem;

    /**
     * A pointer to the progress bar handler
     */ 
    //CProcessReport * mpProgressHandler;

    // Operations
  private:
    /**
     * Default constructor.
     */
    CSensMethod();

  protected:
    /**
     * Specific constructor.
     * @param CCopasiMethod::SubType subType 
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CSensMethod(CCopasiMethod::SubType subType,
                const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Create a trajectory method.
     * Note: the returned object has to be released after use with delete
     */
    static CSensMethod *
    createSensMethod(CCopasiMethod::SubType subType
                     = CCopasiMethod::sensMethod);

    /**
     * Copy constructor.
     * @param "const CTSSMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CSensMethod(const CSensMethod & src,
                const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CSensMethod();

    /**
     *  Set a pointer to the problem.
     *  This method is used by CSteadyState 
     *  @param "CSteadyStateProblem *" problem
     */ 
    //void setProblem(CSteadyStateProblem * problem);

    /**
     */
    bool process(CProcessReport * handler);

    bool initialize(CSensProblem* problem);

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

    CCopasiArray mTarget1, mTarget2;

    CCopasiArray mResult;

    std::vector<std::vector<CCopasiObject*> > mTargetObjects, mVariableObjects;

    std::vector<unsigned int> mTargetSizes, mVariableSizes;
  };

#endif // COPASI_CTSSMethod
