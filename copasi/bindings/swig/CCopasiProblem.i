%{

#include "utilities/CCopasiProblem.h"

%}


class CCopasiProblem : public CCopasiParameterGroup
{
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
     * Do all neccessary restore procedures so that the
     * model is in the same state as before
     * @parem const bool & updateModel
     * @result bool succes
     */
    virtual bool restore(const bool & updateModel);

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


};


