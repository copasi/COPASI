/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeVector.h,v $
  $Revision: 1.11 $
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

#ifndef COPASI_CEvaluationNodeVector
#define COPASI_CEvaluationNodeVector

#include <limits>

class CCopasiDataModel;

/**
 * This is the class for nodes presenting opertors used in an evaluation trees.
 */
class CEvaluationNodeVector : public CEvaluationNode
{
public:
  /**
   * Enumeration of possible node types.
   */
  enum SubType
  {
    INVALID = 0x00FFFFFF,
    VECTOR = 0x00000000
  };

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
  const std::vector< CEvaluationNode * > & getVector() const;

private:

  // Attributes
private:
  std::vector< CEvaluationNode * > mVector;
};

#endif // COPASI_CEvaluationNodeVector
