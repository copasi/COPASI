// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_CEvaluationNodeOperator
#define COPASI_CEvaluationNodeOperator

#include "copasi.h"
LIBSBML_CPP_NAMESPACE_BEGIN
class ASTNode;
LIBSBML_CPP_NAMESPACE_END
class CCopasiDataModel;

/**
 * This is the class for nodes presenting operators used in an evaluation trees.
 */
class CEvaluationNodeOperator : public CEvaluationNode
{
  // Operations
private:
  /**
   * Default constructor
   */
  CEvaluationNodeOperator();

public:
  /**
   * Default constructor
   * @param const SubType & subType
   * @param const Data & data
   */
  CEvaluationNodeOperator(const SubType & subType,
                          const Data & data);

  /**
   * Copy constructor
   * @param const CEvaluationNodeOperator & src
   */
  CEvaluationNodeOperator(const CEvaluationNodeOperator & src);

  /**
   * Destructor
   */
  virtual ~CEvaluationNodeOperator();

  /**
   * Calculate the numerical result of the node. It is assumed that
   * all child nodes are up to date.
   */
  virtual void calculate();

  /**
   * Compile a node;
   * @param const CFunction * pFunction
   * @return bool success;
   */
  virtual bool compile(const CEvaluationTree * pTree);

  /**
   * Retrieve the infix value of the node and its eventual child nodes.
   * @return const Data & value
   */
  virtual std::string getInfix(const std::vector< std::string > & children) const;

  /**
   * Retrieve the display string of the node and its eventual child nodes.
   * @return const Data & value
   */
  virtual std::string getDisplayString(const std::vector< std::string > & children) const;

  /**
   * Retrieve the display string of the node and its eventual child nodes in C.
   * @return const Data & value
   */
  virtual std::string getCCodeString(const std::vector< std::string > & children) const;

  /**
   * Retrieve the display string of the node and its eventual child nodes
   * in Berkeley Madonna format.
   * @return const Data & value
   */
  virtual std::string getBerkeleyMadonnaString(const std::vector< std::string > & children) const;

  /**
   * Retrieve the display string of the node and its eventual child nodes
   * in XPPAUT format.
   * @return const Data & value
   */
  virtual std::string getXPPString(const std::vector< std::string > & children) const;

  /**
   * Creates a new CEvaluationNodeCall from an ASTNode and the given children
   * @param const ASTNode* pNode
   * @param const std::vector< CEvaluationNode * > & children
   * @return CEvaluationNode * pCretedNode
   */
  static CEvaluationNode * fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children);

  /**
   * Create a new ASTNode corresponding to this OperatorNode.
   * @return ASTNode* return a pointer to the newly created node;
   */
  virtual ASTNode* toAST(const CCopasiDataModel* pDataModel) const;

  /**
   * Create a simplified node for an operatorNode with children from vector (if not exist, = NULL),
   * and assign new children
   * @return CEvaluationNode* return a pointer to the simplified node;
   */
  virtual CEvaluationNode* simplifyNode(const std::vector<CEvaluationNode*>& children) const;

  /**
   * Convert our modulo to something SBML understands
   * @param const CEvaluationNodeOperator* pNode the modulo
   *  operator node to be converted.
   * @param const ASTNode* pASTNode the root node for the SBML math expression
   * @return bool which is true on sucessfull conversion.
   */
  bool createModuloTree(const CEvaluationNodeOperator* pNode, ASTNode* pASTNode, const CCopasiDataModel* pDataModel) const;

  /**
   * Build the MathML string
   * @param const std::vector< std::string > & children
   * @param bool expand = true
   * @param const std::vector< std::vector< std::string > > & variables
   * @return std::string MMLString
   */
  virtual std::string getMMLString(const std::vector< std::string > & children,
                                   bool expand,
                                   const std::vector< std::vector< std::string > > & variables) const;

  CEvaluationNode * getLeft();
  const CEvaluationNode * getLeft() const;
  CEvaluationNode * getRight();
  const CEvaluationNode * getRight() const;

private:
  void s_power();
  void s_multiply();
  void s_divide();
  void s_modulus();
  void s_plus();
  void s_minus();
  void s_remainder();
  void s_invalid();

// Attributes
  CEvaluationNode * mpLeftNode;
  CEvaluationNode * mpRightNode;

  const C_FLOAT64 * mpLeftValue;
  const C_FLOAT64 * mpRightValue;

  typedef void (CEvaluationNodeOperator::*OPERATOR)();
  OPERATOR mpOperator;
};

#endif // COPASI_CEvaluationNodeOperator
