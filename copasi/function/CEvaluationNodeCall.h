// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CEvaluationNodeCall
#define COPASI_CEvaluationNodeCall

#include <limits>

#include "copasi/function/CCallParameters.h"

class CFunction;
class CExpression;
class CFunctionParameters;
class CDataModel;

/**
 * This is the class for nodes presenting operators used in an evaluation trees.
 */
class CEvaluationNodeCall : public CEvaluationNode
{
  // Operations
private:
  /**
   * Default constructor
   */
  CEvaluationNodeCall();

public:
  /**
   * Default constructor
   * @param const SubType & subType
   * @param const Data & data
   */
  CEvaluationNodeCall(const SubType & subType,
                      const Data & data);

  /**
   * Copy constructor
   * @param const CEvaluationNodeCall & src
   */
  CEvaluationNodeCall(const CEvaluationNodeCall & src);

  /**
   * Destructor
   */
  virtual ~CEvaluationNodeCall();

  /**
   * Calculate the numerical result of the node. It is assumed that
   * all child nodes are up to date.
   */
  virtual void calculate() override;

  /**
   * Compile a node;
   * @param const CEvaluationTree * pTree
   * @return CIssue issue;
   */
  virtual CIssue compile() override;

  /**
   * Set the type the result of the node
   * @param const ValueType & valueType
   * @return CIssue issue;
   */
  virtual CIssue setValueType(const ValueType & valueType) override;

  /**
   * Check whether node the calls any tree in the list
   * @param std::set< std::string > & list
   * @return bool calls
   */
  bool calls(std::set< std::string > & list) const;

  /**
   * Retrieve the infix value of the node and its eventual child nodes.
   * @return const Data & value
   */
  virtual std::string getInfix(const std::vector< std::string > & children) const override;

  /**
   * Retrieve the value of the node.
   * @return const Data & value
   */
  virtual const Data & getData() const override;

  /**
   * Set the data of the Node.
   * @param const Data & data
   * @return bool success
   */
  virtual bool setData(const Data & data) override;

  /**
   * Retrieve the display string of the node and its eventual child nodes.
   * @return const Data & value
   */
  virtual std::string getDisplayString(const std::vector< std::string > & children) const override;

  /**
   * Retrieve the display string of the node and its eventual child nodes in C.
   * @return const Data & value
   */
  virtual std::string getCCodeString(const std::vector< std::string > & children) const override;

  /**
   * Retrieve the display string of the node and its eventual child nodes
   * in Berkeley Madonna format.
   * @return const Data & value
   */
  virtual std::string getBerkeleyMadonnaString(const std::vector< std::string > & children) const override;

  /**
   ** Retrieve the display string of the node and its eventual child nodes
   ** in XPPAUT format.
   ** @return const Data & value
   **/
  virtual std::string getXPPString(const std::vector< std::string > & children) const override;

  /**
   * Figure out the appropriate CUnit to use, based on the child nodes.
   * This sets the default, appropriate for many cases, as Dimensionless
   * @param const CMathContainer & container
   * @param const std::vector< CValidatedUnit > & units
   * @return CValidatedUnit unit
   */
  virtual CValidatedUnit getUnit(const CMathContainer & container,
                                 const std::vector< CValidatedUnit > & units) const override;

  /**
   * Set the unit for the node and return the resulting unit. The child node units are
   * added to the map
   * @param const CMathContainer & container
   * @param const std::map < CEvaluationNode * , CValidatedUnit > & currentUnits
   * @param std::map < CEvaluationNode * , CValidatedUnit > & targetUnits
   * @return CUnit unit
   */
  virtual CValidatedUnit setUnit(const CMathContainer & container,
                                 const std::map < CEvaluationNode *, CValidatedUnit > & currentUnits,
                                 std::map < CEvaluationNode *, CValidatedUnit > & targetUnits) const override;

  /**
   * Creates a new CEvaluationNodeCall from an ASTNode and the given children
   * @param const ASTNode* pNode
   * @param const std::vector< CEvaluationNode * > & children
   * @return CEvaluationNode * pCretedNode
   */
  static CEvaluationNode * fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children);

  /**
   * Create a new ASTNode corresponding to this choice node.
   * @return ASTNode* return a pointer to the newly created node;
   */
  virtual ASTNode* toAST(const CDataModel* pDataModel) const override;

  /**
   * Add a child to a node.
   * If pAfter == this the child will be inserted at the front of the list
   * of children.
   * @param CCopasiNode< Data > * pChild
   * @param CCopasiNode< Data > * pAfter
   *        (default: NULL appended to the list of children)
   * @return bool Success
   */
  virtual bool addChild(CCopasiNode< Data > * pChild,
                        CCopasiNode< Data > * pAfter = NULL) override;

  /**
   * Remove a child from a node.
   * @param CCopasiNode< Data > * pChild
   * @return bool Success
   */
  virtual bool removeChild(CCopasiNode< Data > * pChild) override;

  /**
   * Retrieve the tree which is called from this node
   * @return const CFunction * calledTree
   */
  const CFunction * getCalledTree() const;

  /**
   * Retrieve the tree which is called from this node
   * @return CFunction * calledTree
   */
  CFunction * getCalledTree();

  /**
   * Build the MathML string
   * @param const std::vector< std::string > & children
   * @param bool expand = true
   * @param const std::vector< std::vector< std::string > > & variables
   * @return std::string MMLString
   */
  virtual std::string getMMLString(const std::vector< std::string > & children,
                                   bool expand,
                                   const std::vector< std::vector< std::string > > & variables) const override;

  /**
   *  returns the vector of child nodes, corresponding to the arguments of a function call
   */
  const std::vector<CEvaluationNode *> getListOfChildNodes() const {return mCallNodes;}

  /**
   * Check whether the result must be Boolean
   * @return const bool & isBooleanRequired
   */
  const bool & isBooleanRequired() const;

  /**
   * Check whether the result is Boolean
   * @return bool isBoolean
   */
  virtual bool isBoolean() const override;

private:
  /**
   * Build the list of call parameters which correspond to
   * the list of call nodes.
   */
  static CCallParameters< C_FLOAT64 > *
  buildParameters(const std::vector<CEvaluationNode *> & vector);

  /**
   * Clear the list of call parameters.
   */
  static void
  clearParameters(CCallParameters< C_FLOAT64 > * pCallParameters,
                  const std::vector<CEvaluationNode *> & vector);

  /**
   * Verifies that the parameters match the function parameters.
   * @param const std::vector<CEvaluationNode *> & vector
   * @param const CFunctionParameters & functionParameters
   * @return bool verified
   */
  static bool
  verifyParameters(const std::vector<CEvaluationNode *> & vector,
                   const CFunctionParameters &functionParameters);

  // Attributes
private:
  CFunction * mpFunction;
  CExpression * mpExpression;
  std::vector<CEvaluationNode *> mCallNodes;
  CCallParameters< C_FLOAT64 > * mpCallParameters;
  mutable bool mQuotesRequired;

  /**
   * The registered object name to track eventual renaming.
   */
  CRegisteredCommonName mRegisteredFunctionCN;

  SubType mCompiledSubType;
};

#endif // COPASI_CEvaluationNodeCall
