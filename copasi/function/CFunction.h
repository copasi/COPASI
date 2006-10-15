/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunction.h,v $
   $Revision: 1.45 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 07:16:08 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CFunction
#define COPASI_CFunction

#include "function/CEvaluationTree.h"
#include "function/CFunctionParameters.h"
#include "function/CCallParameters.h"
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
                     CFunctionParameter::Role usage = CFunctionParameter::VARIABLE,
                     const CFunctionParameter::DataType & type = CFunctionParameter::FLOAT64);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param "CReadConfig &" configBuffer
     *  @param "CReadConfig::Mode" mode (default: CReadConfig::SEARCH)
     *  @return Fail
     */
    virtual void load(CReadConfig & configBuffer,
                      CReadConfig::Mode mode = CReadConfig::SEARCH);

    /**
     * determines whether the function is suitable for a reaction with
     * the given number of substrates and products and reversibility
     */
    bool isSuitable(const unsigned C_INT32 noSubstrates,
                    const unsigned C_INT32 noProducts,
                    const TriLogic reversible);

  protected:
    bool initVariables();

    // Attributes
  private:

    /**
     *  The discription of the variables of the function.
     *  It describes which variables need to be passed to the function
     *  for evaluation and its eventual type.
     */
    CFunctionParameters mVariables;

    /**
     * A pointer to the call parameters during calculation.
     */
    const CCallParameters<C_FLOAT64> * mpCallParameters;

    /**
     *  Whether the function is reversible
     */
    TriLogic mReversible;

  public:
    virtual void writeMathML(std::ostream & out, unsigned C_INT32 l = 0) const;

    virtual void writeMathML(std::ostream & out,
                             const std::vector<std::vector<std::string> > & env,
                             bool expand = true, bool fullExpand = true,
                             unsigned C_INT32 l = 0) const;

    /**
     *  create a list of the names of the function parameters in mathml format.
     *  this list can be passed as the env argument to the writeMathML() method
     */
    void createListOfParametersForMathML(std::vector<std::vector<std::string> > & env);
  };

#include "CKinFunction.h"
#include "CMassAction.h"

#endif // COPASI_CFunction
