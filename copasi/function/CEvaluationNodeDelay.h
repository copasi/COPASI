// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeDelay.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/02/19 15:15:28 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CEvaluationNodeDelay
#define COPASI_CEvaluationNodeDelay

#include <iostream>
#include <vector>

#include <copasi/function/CEvaluationNode.h>

class ASTNode;
class CCopasiDataModel;

/**
 * This is class for nodes representing the (SBML) delay function.
 */
class CEvaluationNodeDelay : public CEvaluationNode
{
public:
  /**
   * Enumeration of possible node types.
   */
  enum SubType
  {
    INVALID = 0x00FFFFFF,
    DELAY = 0x00000000
  };

  // Operations
private:
  /**
   * Default constructor
   */
  CEvaluationNodeDelay();

public:
  /**
   * constructor
   * @param const SubType & subType
   * @param const Data & data
   */
  CEvaluationNodeDelay(const SubType & subType,
                       const Data & data);

  /**
   * Copy constructor
   * @param const CEvaluationNodeDelay & src
   */
  CEvaluationNodeDelay(const CEvaluationNodeDelay & src);

  /**
   * Destructor
   */
  virtual ~CEvaluationNodeDelay();

  /**
   * Retrieve the value of the node
   * @return const C_FLOAT64 & value
   */
  virtual const C_FLOAT64 & value() const;

  /**
   * Retrieve the display string of the node and its eventual child nodes.
   * @return const Data & value
   */
  virtual std::string getDisplayString(const CEvaluationTree * pTree) const;

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
   ** Retrieve the display string of the node and its eventual child nodes
   ** in XPPAUT format.
   ** @return const Data & value
   **/
  virtual std::string getDisplay_XPP_String(const CEvaluationTree * pTree) const;

  /**
   * Creates a new CEvaluationNodeDelay from an ASTNode.
   * @param const ASTNode* node
   * @return CEvaluationNode* return a pointer to the newly created node;
   */
  static CEvaluationNode* createNodeFromASTTree(const ASTNode& node);

  /**
   * Create a new ASTNode corresponding to this delay node.
   * @return ASTNode* return a pointer to the newly created node;
   */
  ASTNode* toAST(const CCopasiDataModel* pDataModel) const;

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
                        CCopasiNode< Data > * pAfter = NULL);

  /**
   * Remove a child from a node.
   * @param CCopasiNode< Data > * pChild
   * @return bool Success
   */
  virtual bool removeChild(CCopasiNode< Data > * pChild);

  /**
   *  returns the vector of child nodes, corresponding to the arguments of a function call
   */
  const std::vector<CEvaluationNode *> getListOfChildNodes() const {return mCallNodes;}

  /**
   * generate display MathML recursively
   */
  virtual void writeMathML(std::ostream & out,
                           const std::vector<std::vector<std::string> > & env,
                           bool expand = true,
                           unsigned C_INT32 l = 0) const;

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
  virtual std::string getInfix() const;

private:
  std::vector<CEvaluationNode *> mCallNodes;
};

#endif // COPASI_CEvaluationNodeDelay
