/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CFitProblem.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/06 22:19:49 $
   End CVS Header */

#ifndef COPASI_CFitProblem
#define COPASI_CFitProblem

#include "optimization/COptProblem.h"
#include "utilities/CMatrix.h"

class CExperimentSet;
class CTrajectoryProblem;
class CState;

class CFitProblem : public COptProblem
  {
  public:
    // Opreations
    /**
     * Default constructor
     * @param const CCopasiTask::Type & type (default: parameterFitting)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFitProblem(const CCopasiTask::Type & type = CCopasiTask::parameterFitting,
                const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor.
     * @param const CFitProblem & src
     * @paramconst CCopasiContainer * pParent (default: NULL)
     */
    CFitProblem(const CFitProblem & src,
                const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CFitProblem();

    /**
     * This methods must be called to elevate subgroups to
     * derived objects. The default implementation does nothing.
     * @return bool success
     */
    virtual bool elevateChildren();

    /**
     * Set the model of the problem
     * @param CModel * pModel
     * @result bool succes
     */
    virtual bool setModel(CModel * pModel);

    /**
     * Set the call back of the problem
     * @param CProcessReport * pCallBack
     * @result bool succes
     */
    virtual bool setCallBack(CProcessReport * pCallBack);

    /**
     * Do all neccessary initialization so that calls to caluclate will 
     * be successful. This is called once from CCopasiTask::process()
     * @result bool succes
     */
    virtual bool initialize();

    /**
     * Do the calculatting based on CalculateVariables and fill
     * CalculateResults with the results. 
     * @result bool continue
     */
    virtual bool calculate();

    /**
     * Do all neccessary restore procedures so that the
     * model is in the same state as before
     * @result bool succes
     */
    virtual bool restore();

    /**
     * This is the output method for any object. The default implementation
     * provided with CCopasiObject uses the ostream operator<< of the object
     * to print the object.To overide this default behaviour one needs to
     * reimplement the virtual print function.
     * @param std::ostream * ostream
     */
    virtual void print(std::ostream * ostream) const;

    /**
     * Output stream operator
     * @param ostream & os
     * @param const CFitProblem & A
     * @return ostream & os
     */
    friend std::ostream &operator<<(std::ostream &os, const CFitProblem & o);

    /**
     * This is the output method for any result of a problem. The default implementation
     * provided with CCopasiProblem. Does only print "Not implmented." To overide this
     * default behaviour one needs to reimplement the virtual printResult function.
     * @param std::ostream * ostream
     */
    virtual void printResult(std::ostream * ostream) const;

  private:
    /**
     * Allocates all group parameters and assures that they are 
     * properly initialized.
     */
    void initializeParameter();

    virtual bool createObjectiveFunction();

  private:
    // Attributes
    /**
     * The experiment set to which the model is fitted.
     */
    CExperimentSet * mpExperimentSet;

    /**
     * Matrix of update methods for items for each experiment.
     */
    CMatrix< UpdateMethod * > mExperimentUpdateMethods;

    /**
     * Copy of the trajectory problem so that we can restore the defaults
     */
    CTrajectoryProblem * mpTrajectoryProblem;

    /**
     * Copy of the initial state needed for calculate
     */
    CState * mpInitialState;
  };

#endif  // COPASI_CFitProblem
