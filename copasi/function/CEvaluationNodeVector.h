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

#ifndef COPASI_CEvaluationNodeVector
#define COPASI_CEvaluationNodeVector

#include <limits>

class CCopasiDataModel;

/**
 * This is the class for nodes presenting operators used in an evaluation trees.
 */
class CEvaluationNodeVector : public CEvaluationNode
{
  // Operations
public:
  /**
   * Default constructor
   */
  CEvaluationNodeVector();

  /**
   * Default constructor
   * @param const SubType & subType
   * @param const Data & data
   */
  CEvaluationNodeVector(const SubType & subType,
                        const Data & data);

  /**
   * Copy constructor
   * @param const CEvaluationNodeVector & src
   */
  CEvaluationNodeVector(const CEvaluationNodeVector & src);

  /**
   * Destructor
   */
  virtual ~CEvaluationNodeVector();

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
   * Create a new ASTNode corresponding to this choice node.
   * @return ASTNode* return a pointer to the newly created node;
   */
  virtual ASTNode* toAST(const CCopasiDataModel* pDataModel) const;

  /**
   * Add a child to a node.
   * If pAfter == this the child will be inserted at the fornt of the list
   * of children.
   * @param CCopasiNode< Data > * pChild
   * @param CCopasiNode< Data > * pAfter
   *        (default: NULL appended to the list of children)
   * @return bool Success
   */
  bool addChild(CCopasiNode< Data > * pChild,
                CCopasiNode< Data > * pAfter = NULL);

  /**
   * Retrieve the vector of evaluation nodes
   * @return const std::vector< CEvaluationNode * > & vector
   */
  const std::vector< CEvaluationNode * > & getNodes() const;

private:

  // Attributes
private:
  std::vector< CEvaluationNode * > mNodes;
  std::vector< const C_FLOAT64 * > mValues;
};

#endif // COPASI_CEvaluationNodeVector
