// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeDelay.h,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/16 23:11:31 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CEvaluationNodeDelay
#define COPASI_CEvaluationNodeDelay

#include <iostream>
#include <vector>

#include "copasi/function/CEvaluationNode.h"

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
   ** Retrieve the display string of the node and its eventual child nodes
   ** in XPPAUT format.
   ** @return const Data & value
   **/
  virtual std::string getXPPString(const std::vector< std::string > & children) const;

  /**
   * Creates a new CEvaluationNodeCall from an ASTNode and the given children
   * @param const ASTNode* pNode
   * @param const std::vector< CEvaluationNode * > & children
   * @return CEvaluationNode * pCretedNode
   */
  static CEvaluationNode * fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children);

  /**
   * Create a new ASTNode corresponding to this delay node.
   * @return ASTNode* return a pointer to the newly created node;
   */
  ASTNode* toAST(const CCopasiDataModel* pDataModel) const;

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

private:
  CEvaluationNode * mpDelayedObject;
  CEvaluationNode * mpDeltaT;
};

#endif // COPASI_CEvaluationNodeDelay
