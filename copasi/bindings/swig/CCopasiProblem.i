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
     * Retrieve the model of the problem
     * @result CModel * pModel
     */
    CModel * getModel() const;


};


