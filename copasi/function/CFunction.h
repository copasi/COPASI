// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunction.h,v $
//   $Revision: 1.54 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/16 23:11:32 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CFunction
#define COPASI_CFunction

#include "function/CEvaluationTree.h"
#include "function/CFunctionParameters.h"
#include "function/CCallParameters.h"
#include "utilities/CCopasiVector.h"

/*!
    \brief The class for handling a chemical kinetic function

 This class is designed to handle all about a given chemical kinetic function from
 editing and displaying (with help of MathML) the function to calculating the function value.
 */
class CFunction:
    public CEvaluationTree, public CAnnotation
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
   * @param const CFunction & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CFunction(const CFunction & src,
            const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  virtual ~CFunction();

  /**
   * Retrieves the key of the EvaluationTree
   * @return const std::string & key
   */
  const std::string & getKey() const;

  /**
   * Sets the SBMLId.
   */
  void setSBMLId(const std::string& id);

  /**
   * Returns a reference to the SBML Id.
   */
  const std::string& getSBMLId() const;

  /**
   * Function to set the infix description of the tree and compile it.
   * @param const std::string & infix
   * @return bool success
   */
  virtual bool setInfix(const std::string & infix);

  /**
   * Comparison operator
   * @param const CFunction & rhs
   * @return bool equal
   */
  bool operator == (const CFunction & rhs) const;

  /**
   * Function to calculate the value of the function
   * @param const CCallParameters<C_FLOAT64> & callParameters
   * @return const C_FLOAT64 & result
   */
  virtual const C_FLOAT64 & calcValue(const CCallParameters<C_FLOAT64> & callParameters);

  /**
   * Function to return whether it depends on the given parameter
   * @param const void * parameter
   * @param const CCallParameters<C_FLOAT64> & callParameters
   * @param bool dependsOn
   */
  virtual bool dependsOn(const C_FLOAT64 * parameter,
                         const CCallParameters<C_FLOAT64> & callParameters) const;

  /**
   * Function to retrieve the index to the value of the named variable.
   * @param const std::string & name
   * @return size_t index
   */
  virtual size_t getVariableIndex(const std::string & name) const;

  /**
   * Function to retrieve the value of the indexed variable.
   *
   * Note this function is only usable during calcValue, since the values
   * of the call parameters are only defined during that time.
   * @param const size_t & index
   * @return const C_FLOAT64 & variableValue
   */
  virtual const C_FLOAT64 & getVariableValue(const size_t & index) const;

  /**
   * Function to set whether it is reversible.
   */
  void setReversible(const TriLogic & reversible);

  /**
   * Function to retrieve whether it is reversible.
   */
  const TriLogic & isReversible() const;

  /**
   * Function to retrive the definition of the parameters
   * @return CFunctionParameters & variables
   */
  CFunctionParameters & getVariables();

  /**
   * Function to retrive the definition of the parameters
   * @return const CFunctionParameters & variables
   */
  const CFunctionParameters & getVariables() const;

  /**
   * Function to add the description of a variable.
   * @param const string & name
   * @param const string & usage (Default: VARIABLE)
   * @param const CFunctionParameters::DataType & type (Default: value)
   * @return bool success
   */
  bool addVariable(const std::string & name,
                   CFunctionParameter::Role usage = CFunctionParameter::VARIABLE,
                   const CFunctionParameter::DataType & type = CFunctionParameter::FLOAT64);

  /**
   * Function to load an object with data coming from a CReadConfig object.
   * (CReadConfig object reads an input stream)
   * @param "CReadConfig &" configBuffer
   * @param "CReadConfig::Mode" mode (default: CReadConfig::SEARCH)
   * @return Fail
   */
  virtual void load(CReadConfig & configBuffer,
                    CReadConfig::Mode mode = CReadConfig::SEARCH);

  /**
   * Function to determine whether it is suitable for a reaction with
   * the given number of substrates and products and reversibility
   */
  bool isSuitable(const size_t noSubstrates,
                  const size_t noProducts,
                  const TriLogic reversible);

  /**
   * Complete the list of evaluation tree such that all called trees are includes.
   * @param std::vector< CFunction * > & list
   * @param const size_t & added (Default: list.size())
   * @return bool success
   */
  static bool completeFunctionList(std::vector< CFunction * > & list,
                                   const size_t & added = 0);


protected:
  /**
   * Function to initialize the parameters
   * @return bool success
   */
  bool initVariables();

  // Attributes
private:

  /**
   * The unique key of the functions
   */
  std::string mKey;

  /**
   * The id of the corresponding function in an SBML file.
   * This value is either set upon importing an SBML file,
   * or when the object is first exported to an SBML file.
   */
  std::string mSBMLId;

  /**
   * The description of the variables of the function.
   * It describes which variables need to be passed to the function
   * for evaluation and its eventual type.
   */
  CFunctionParameters mVariables;

  /**
   * A pointer to the call parameters during calculation.
   */
  const CCallParameters<C_FLOAT64> * mpCallParameters;

  /**
   * Whether the function is reversible
   */
  TriLogic mReversible;

public:
  /**
   * This is an overloaded member function, provided for convenience.
   * It behaves essentially like the above function.
   * @param std::ostream & out
   * @param size_t l
   */
  virtual void writeMathML(std::ostream & out, size_t l = 0) const;

  /**
   * Function to write the mathematical formula in format of MathML.
   * @param std::ostream & out
   * @param const std::vector< std::vector< std::string > > & variables
   * @param bool expand = true
   * @param bool fullExpand
   * @return std::string
   */
  virtual std::string writeMathML(const std::vector< std::vector< std::string > > & variables,
                                  bool expand = true, bool fullExpand = true) const;

  /**
   * Function to create a list of the names of the function parameters in MathML format.
   *  This list can be passed as the env argument to the writeMathML() method.
   *  @param std::vector<std::vector<std::string> > & env
   */
  void createListOfParametersForMathML(std::vector<std::vector<std::string> > & env);

  /**
   * Insert operator
   */
  friend std::ostream& operator<<(std::ostream &os, const CFunction & f);

  /**
   * Function to duplicate itself
   */
  CFunction * createCopy() const;

  /**
   *  Function to split
   *
   *  @param const CEvaluationNode* node
   *  @param const std::string & name1
   *  @param const std::string & name2
   */
  std::pair<CFunction *, CFunction *> splitFunction(const CEvaluationNode* node,
      const std::string & name1,
      const std::string & name2) const;
};

#include "CKinFunction.h"
#include "CMassAction.h"

#endif // COPASI_CFunction
