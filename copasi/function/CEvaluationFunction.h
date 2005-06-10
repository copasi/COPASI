/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/Attic/CEvaluationFunction.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/10 17:50:36 $
   End CVS Header */

#ifndef COPASI_CEvaluationFunction
#define COPASI_CEvaluationFunction

#include "CEvaluationTree.h"
#include "CFunctionParameters.h"
#include "CCallParameters.h"
#include "report/CCopasiContainer.h"
#include "utilities/CCopasiVector.h"

#define CFunctionVariable CFunctionParameter
#define CFunctionVariables CFunctionParameters

class CEvaluationFunction:
      public CCopasiContainer,
      public CEvaluationTree
  {
  public:
    /**
     *  The valid types of a function
     */
    enum Type
    {
      Base = 0,
      MassAction,
      PreDefined,
      UserDefined,
      Expression
    };

    /**
     *  The string representation of valid types of a function
     */
    static const std::string TypeName[];

    /**
     *  The string representation of valid types of a function
     */
    static const char * XMLType[];

    // Operations
  public:

    /**
     * Create a function of the specified type.
     * Note: the returned object has to be released after use with delete.
     */
    static CEvaluationFunction *
    createFunction(CEvaluationFunction::Type type = CEvaluationFunction::Base);

    /**
     * Create a function of the specified type.
     * Note: the returned object has to be released after use with delete.
     */
    static CEvaluationFunction *
    createFunction(const CEvaluationFunction * pFunction);

    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CEvaluationFunction(const std::string & name = "NoName",
                        const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CEvaluationFunction &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CEvaluationFunction(const CEvaluationFunction & src,
                        const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor
     */
    virtual ~CEvaluationFunction();

    /**
     * Retrieve the index to the value of the named variable.
     * @param const std::string & name
     * @return unsigned C_INT32
     */
    virtual unsigned C_INT32 getVariableIndex(const std::string & name) const;

    /**
     * Retrieve the value of the indexed variable
     * @param const unsigned C_INT32 & index
     * @return const C_FLOAT64 & variableValue
     */
    virtual const C_FLOAT64 & getVariableValue(const unsigned C_INT32 & index) const;

    /**
     * Compile the function.
     */
    virtual bool compile();

    /**
     * Retrieves the type of the function
     * @return const CEvaluationFunction::Type & type
     */
    const CEvaluationFunction::Type & getType() const;

    /**
     * Retrieves the key of the function
     * @return const std::string & key
     */
    const std::string & getKey() const;

    /**
     * Retrives the definition of the parameters
     * @return CFunctionVariables & variables
     */
    CFunctionVariables & getVariables();

    /**
     * Retrives the definition of the parameters
     * @return const CFunctionVariables & variables
     */
    const CFunctionVariables & getVariables() const;

    /**
     * Adds the description of a variable. 
     * @param const string & name
     * @param const string & usage (Default: VARIABLE)
     * @param const CFunctionVariables::DataType & type (Default: value)
     * @return bool success
     */
    bool addVariable(const std::string & name,
                     const std::string & usage = "VARIABLE",
                     const CFunctionVariable::DataType & type = CFunctionVariable::FLOAT64);

    /**
     * Retrives the of the usage description of variables.
     * @return CCopasiVectorNS < CUsageRange > & usage
     */
    CCopasiVectorNS < CUsageRange > & getUsageDescriptions();

    /**
     * Retrives the of the usage description of variables.
     * @return const CCopasiVectorNS < CUsageRange > & usage
     */
    const CCopasiVectorNS < CUsageRange > & getUsageDescriptions() const;

    /**
     * Calculates the value of the function
     * @param const CCallParameters<C_FLOAT64> & callParameters
     * @return C_FLOAT64 result
     */
    virtual C_FLOAT64 calcValue(const CCallParameters<C_FLOAT64> & callParameters) const;

    /**
     * Returns whether the function depends on the given parameter
     * &param const void * parameter
     * &param const CCallParameters<C_FLOAT64> & callParameters
     * &param bool dependsOn
     */
    virtual bool dependsOn(const C_FLOAT64 * parameter,
                           const CCallParameters<C_FLOAT64> & callParameters) const;

  protected:
    bool initVariables();

    // Attributes
  private:

    /**
     * The type of the function
     */
    CEvaluationFunction::Type mType;

    /**
     * The key of the function
     */
    std::string mKey;

    /**
     *  The discription of the variables of the function.
     *  It describes which variables need to be passed to the function
     *  for evaluation and its eventual type.
     */
    CFunctionVariables mVariables;

    /**
     *  A vector of usages ranges describing the condition under which a 
     *  function may be used.
     *  Specifically it describes what number of substrates and products a
     *  reaction may have to be able to use this function as its rate function.
     */
    CCopasiVectorNS < CUsageRange > mUsageDescriptions;
  };

#endif // COPASI_CEvaluationFunction
