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
  virtual inline void calculate()
  {
    switch (mSubType)
      {
        case S_POWER:
          mValue = pow(mpLeft->getValue(), mpRight->getValue());
          break;

        case S_MULTIPLY:
          mValue = mpLeft->getValue() * mpRight->getValue();
          break;

        case S_DIVIDE:
          mValue = mpLeft->getValue() / mpRight->getValue();
          break;

        case S_MODULUS:

          if ((C_INT32) mpRight->getValue() == 0)
            mValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
          else
            mValue = (C_FLOAT64)(((C_INT32) mpLeft->getValue()) % ((C_INT32) mpRight->getValue()));

          break;

        case S_PLUS:
          mValue = mpLeft->getValue() + mpRight->getValue();
          break;

        case S_MINUS:
          mValue = mpLeft->getValue() - mpRight->getValue();
          break;

        case S_REMAINDER:
          mValue = fmod(mpLeft->getValue(), mpRight->getValue());
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
   * Figure out the appropriate CUnit to use, based on the child nodes.
   * This sets the default, appropriate for many cases, as Dimensionless
   * @param const CMathContainer & container
   * @param const std::vector< CValidatedUnit > & units
   * @return CValidatedUnit unit
   */
  virtual CValidatedUnit getUnit(const CMathContainer & container,
                                 const std::vector< CValidatedUnit > & units) const;

  /**
   * Set the unit for the node and return the resulting unit. The child node units are
   * added to the map
   * @param const CMathContainer & container
   * @param const std::map < CEvaluationNode * , CValidatedUnit > & currentUnits
   * @param std::map < CEvaluationNode * , CValidatedUnit > & targetUnits
   * @return CValidatedUnit unit
   */
  virtual CValidatedUnit setUnit(const CMathContainer & container,
                                 const std::map < CEvaluationNode * , CValidatedUnit > & currentUnits,
                                 std::map < CEvaluationNode * , CValidatedUnit > & targetUnits) const;

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
