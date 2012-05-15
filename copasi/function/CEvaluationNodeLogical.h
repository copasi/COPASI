/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeLogical.h,v $
  $Revision: 1.18 $
  $Name:  $
  $Author: shoops $
  $Date: 2012/05/15 15:56:41 $
  End CVS Header */

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

#ifndef COPASI_CEvaluationNodeLogical
#define COPASI_CEvaluationNodeLogical

class ASTNode;
class CCopasiDataModel;

/**
 * This is the class for nodes presenting opertors used in an evaluation trees.
 */
class CEvaluationNodeLogical : public CEvaluationNode
{
public:
  /**
   * Enumeration of possible node types.
   */
  enum SubType
  {
    INVALID = 0x00FFFFFF,
    //      NOT = 0x00000001,
    OR = 0x00000001,
    XOR = 0x00000002,
    AND = 0x00000003,
    EQ = 0x00000004,
    NE = 0x00000005,
    GT = 0x00000006,
    GE = 0x00000007,
    LT = 0x00000008,
    LE = 0x00000009
  };

  // Operations
private:
  /**
   * Default constructor
   */
  CEvaluationNodeLogical();

public:
  /**
   * Default constructor
   * @param const SubType & subType
   * @param const Data & data
   */
  CEvaluationNodeLogical(const SubType & subType,
                         const Data & data);

  /**
   * Copy constructor
   * @param const CEvaluationNodeLogical & src
   */
  CEvaluationNodeLogical(const CEvaluationNodeLogical & src);

  /**
   * Destructor
   */
  virtual ~CEvaluationNodeLogical();

  /**
   * Calculate the numerical result of the node. It is assumed that
   * all child nodes are up to date.
   */
  virtual inline void calculate()
  {
    switch (mType & 0x00FFFFFF)
      {
        case OR:
          mValue = (mpLeft->getValue() > 0.5 ||
                    mpRight->getValue() > 0.5) ? 1.0 : 0.0;
          break;

        case XOR:
          mValue = ((mpLeft->getValue() > 0.5 && mpRight->getValue() < 0.5) ||
                    (mpLeft->getValue() < 0.5 && mpRight->getValue() > 0.5)) ? 1.0 : 0.0;
          break;

        case AND:
          mValue = (mpLeft->getValue() > 0.5 &&
                    mpRight->getValue() > 0.5) ? 1.0 : 0.0;
          break;

        case EQ:
          mValue = (mpLeft->getValue() == mpRight->getValue()) ? 1.0 : 0.0;
          break;

        case NE:
          mValue = (mpLeft->getValue() != mpRight->getValue()) ? 1.0 : 0.0;
          break;

        case GT:
          mValue = (mpLeft->getValue() > mpRight->getValue()) ? 1.0 : 0.0;
          break;

        case GE:
          mValue = (mpLeft->getValue() >= mpRight->getValue()) ? 1.0 : 0.0;
          break;

        case LT:
          mValue = (mpLeft->getValue() < mpRight->getValue()) ? 1.0 : 0.0;
          break;

        case LE:
          mValue = (mpLeft->getValue() <= mpRight->getValue()) ? 1.0 : 0.0;
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
  virtual std::string getDisplay_C_String(const CEvaluationTree * pTree) const;

  /**
   * Retrieve the display string of the node and its eventual child nodes
   * in Berkeley Madonna format.
   * @return const Data & value
   */
  virtual std::string getDisplay_MMD_String(const CEvaluationTree * pTree) const;

  /**
   * Retrieve the display string of the node and its eventual child nodes
   * in XPPAUT format.
   * @return const Data & value
   */
  virtual std::string getDisplay_XPP_String(const CEvaluationTree * pTree) const;

  /**
   * Creates a new CEvaluationNodeCall from an ASTNode and the given children
   * @param const ASTNode* pNode
   * @param const std::vector< CEvaluationNode * > & children
   * @return CEvaluationNode * pCretedNode
   */
  static CEvaluationNode * fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children);

  /**
   * Check whether the result is Boolean
   * @return bool isBoolean
   */
  virtual bool isBoolean() const;

  /**
   * Create a new ASTNode corresponding to this OperatorNode.
   * @return ASTNode* return a pointer to the newly created node;
   */
  virtual ASTNode* toAST(const CCopasiDataModel* pDataModel) const;

  /**
   * generate display MathML recursively
   */
  virtual void writeMathML(std::ostream & out,
                           const std::vector<std::vector<std::string> > & env,
                           bool expand = true,
                           size_t l = 0) const;

  // Attributes
private:
  CEvaluationNode * mpLeft;

  CEvaluationNode * mpRight;
};

#endif // COPASI_CEvaluationNodeLogical
