// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeOperator.h,v $
//   $Revision: 1.32 $
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

#ifndef COPASI_CEvaluationNodeOperator
#define COPASI_CEvaluationNodeOperator

class ASTNode;
class CCopasiDataModel;

/**
 * This is the class for nodes presenting operators used in an evaluation trees.
 */
class CEvaluationNodeOperator : public CEvaluationNode
{
public:
  /**
   * Enumeration of possible node types.
   */
  enum SubType
  {
    INVALID = 0x00FFFFFF,
    POWER = 0x00000000,
    MULTIPLY = 0x00000001,
    DIVIDE = 0x00000002,
    MODULUS = 0x00000003,
    PLUS = 0x00000004,
    MINUS = 0x00000005
  };

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
  virtual inline void calculate()
  {
    switch (mType & 0x00FFFFFF)
      {
        case POWER:
          mValue = pow(mpLeft->getValue(), mpRight->getValue());
          break;

        case MULTIPLY:
          mValue = mpLeft->getValue() * mpRight->getValue();
          break;

        case DIVIDE:
          mValue = mpLeft->getValue() / mpRight->getValue();
          break;

        case MODULUS:

          if ((C_INT32) mpRight->getValue() == 0)
            mValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
          else
            mValue = (C_FLOAT64)(((C_INT32) mpLeft->getValue()) % ((C_INT32) mpRight->getValue()));

          break;

        case PLUS:
          mValue = mpLeft->getValue() + mpRight->getValue();
          break;

        case MINUS:
          mValue = mpLeft->getValue() - mpRight->getValue();
          break;

        default:
          break;
      }
  }

  /**
   * Compile a node;
   * @param const CEvaluationTree * pTree
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

  // Attributes
private:
  CEvaluationNode * mpLeft;

  CEvaluationNode * mpRight;
};

#endif // COPASI_CEvaluationNodeOperator
