%{

#include "function/CFunction.h"

%}

class CFunction : public CEvaluationTree
{
  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CEvaluationTree::Type & type (default: Function)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFunction(const std::string & name = "NoName",
              const CCopasiContainer * pParent = NULL,
              const Type & type = Function);

    /**
     * Copy constructor
     * @param "const CFunction &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFunction(const CFunction & src,
              const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor
     */
    virtual ~CFunction();

    /**
     * Set the infix description of the tree and compile it.
     * @param const std::string & infix
     * @return bool success
     */
    virtual bool setInfix(const std::string & infix);

    /**
     * Retrieve the index to the value of the named variable.
     * @param const std::string & name
     * @return unsigned C_INT32 index
     */
    virtual unsigned C_INT32 getVariableIndex(const std::string & name) const;

    /**
     *  Set whether the function is reversible.
     */
    void setReversible(const TriLogic & reversible);

    /**
     *  Retrieves whether the function is reversible.
     */
    const TriLogic & isReversible() const;

    /**
     * Retrives the definition of the parameters
     * @return CFunctionParameters & variables
     */
    CFunctionParameters & getVariables();

    /**
     * Adds the description of a variable.
     * @param const string & name
     * @param const string & usage (Default: VARIABLE)
     * @param const CFunctionParameters::DataType & type (Default: value)
     * @return bool success
     */
    bool addVariable(const std::string & name,
                     CFunctionParameter::Role usage = CFunctionParameter::VARIABLE,
                     const CFunctionParameter::DataType & type = CFunctionParameter::FLOAT64);


    /**
     * determines whether the function is suitable for a reaction with
     * the given number of substrates and products and reversibility
     */
    bool isSuitable(const unsigned C_INT32 noSubstrates,
                    const unsigned C_INT32 noProducts,
                    const TriLogic reversible);


};


