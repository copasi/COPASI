/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunction.h,v $
   $Revision: 1.38 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/29 18:47:03 $
   End CVS Header */

#ifndef COPASI_CFunction
#define COPASI_CFunction

#include "CEvaluationTree.h"
#include "CFunctionParameters.h"
#include "CCallParameters.h"
#include "utilities/CCopasiVector.h"

class CFunction:
      public CEvaluationTree
  {
    // Operations
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
     * Compile the function.
     */
    virtual bool compile();

    /**
     * Calculates the value of the function
     * @param const CCallParameters<C_FLOAT64> & callParameters
     * @return const C_FLOAT64 & result
     */
    virtual const C_FLOAT64 & calcValue(const CCallParameters<C_FLOAT64> & callParameters);

    /**
     * Returns whether the function depends on the given parameter
     * &param const void * parameter
     * &param const CCallParameters<C_FLOAT64> & callParameters
     * &param bool dependsOn
     */
    virtual bool dependsOn(const C_FLOAT64 * parameter,
                           const CCallParameters<C_FLOAT64> & callParameters) const;

    /**
     * Retrieve the index to the value of the named variable.
     * @param const std::string & name
     * @return unsigned C_INT32 index
     */
    virtual unsigned C_INT32 getVariableIndex(const std::string & name) const;

    /**
     * Retrieve the value of the indexed variable.
     * Note this function is only usable during calcValue, since the values
     * of the call parameters are only defined during that time.
     * @param const unsigned C_INT32 & index
     * @return const C_FLOAT64 & variableValue
     */
    virtual const C_FLOAT64 & getVariableValue(const unsigned C_INT32 & index) const;

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
     * Retrives the definition of the parameters
     * @return const CFunctionParameters & variables
     */
    const CFunctionParameters & getVariables() const;

    /**
     * Adds the description of a variable. 
     * @param const string & name
     * @param const string & usage (Default: VARIABLE)
     * @param const CFunctionParameters::DataType & type (Default: value)
     * @return bool success
     */
    bool addVariable(const std::string & name,
                     const std::string & usage = "VARIABLE",
                     const CFunctionParameter::DataType & type = CFunctionParameter::FLOAT64);

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
     * Adds one usage descriptiont
     * @param const string & usage (SUBSTRATE or PRODUCT)
     * @param const unsigned C_INT32 & lowerBound
     * @param const unsigned C_INT32 & upperBound
     */
    void addUsage(const std::string& usage,
                  const unsigned C_INT32 & lowerBound,
                  const unsigned C_INT32 & upperBound);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param "CReadConfig &" configBuffer
     *  @param "CReadConfig::Mode" mode (default: CReadConfig::SEARCH)
     *  @return Fail
     */
    virtual void load(CReadConfig & configBuffer,
                      CReadConfig::Mode mode = CReadConfig::SEARCH);

  protected:
    bool initVariables();
    bool guessModifierUsageRange();

    // Attributes
  private:

    /**
     *  The discription of the variables of the function.
     *  It describes which variables need to be passed to the function
     *  for evaluation and its eventual type.
     */
    CFunctionParameters mVariables;

    /**
     *  A vector of usages ranges describing the condition under which a 
     *  function may be used.
     *  Specifically it describes what number of substrates and products a
     *  reaction may have to be able to use this function as its rate function.
     */
    CCopasiVectorNS < CUsageRange > mUsageDescriptions;

    /**
     * A pointer to the call parameters during calculation.
     */
    const CCallParameters<C_FLOAT64> * mpCallParameters;

    /**
     *  Whether the function is reversible
     */
    TriLogic mReversible;
  };

#include "CKinFunction.h"
#include "CMassAction.h"

#endif // COPASI_CFunction
