%{

#include "function/CFunctionDB.h"

%}

class CFunctionDB : public CCopasiContainer
{
  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: RootContainer)
     */
    CFunctionDB(const std::string & name = "FunctionDB",
                const CCopasiContainer * pParent = CCopasiContainer::Root);

    /**
     * Destructor
     */
    ~CFunctionDB();

    /**
     * Add the function to the database
     * @param CEvaluationTree * pFunction
     * @param const bool & adopt (default = false)
     * @return bool success
     */
    bool add(CEvaluationTree * pFunction, const bool & adopt);
    
    bool removeFunction(const std::string &key);

    /**
     *  Search for a function among the loaded functions. If no
     *  function is found NULL is returned
     *  @param "const string" &functionName
     *  @return CEvaluationTree *
     */
    CEvaluationTree * findFunction(const std::string & functionName);

    /**
     *  Search for a function among the loaded functions. If no
     *  function is found the database is searched and the apropriate
     *  function is loaded.
     *  @param "const string" &functionName
     *  @return CEvaluationTree * function (NULL if function is not found)
     */
    CEvaluationTree * findLoadFunction(const std::string & functionName);

    /**
     *  Retrieves the vector of loaded functions.
     *  @return "CCopasiVectorNS < CKinFunction > &" loadedFunctions
     */
    CCopasiVectorN < CEvaluationTree > & loadedFunctions();

    /**
     *  Retrieves the vector of functions that are suitable for a
     *  number of substrates, products and reversibility status.
     *  Note: The returnes CCopasiVector has to be deleted after use!
     *  @param "const unsigned C_INT32" noSubstrates the number of substrates
     *  @param "const unsigned C_INT32" noProducts the number of products
     *  @param "const TriLogic" reversible the reversibility status
     *  @return "std::vector<CFunction*> " suitableFunctions
     */
    std::vector<CFunction*>
    suitableFunctions(const unsigned C_INT32 noSubstrates,
                      const unsigned C_INT32 noProducts,
                      const TriLogic reversibility);


};


