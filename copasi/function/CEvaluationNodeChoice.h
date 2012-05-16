/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeChoice.h,v $
  $Revision: 1.21 $
  $Name:  $
  $Author: shoops $
  $Date: 2012/05/16 23:11:31 $
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

#ifndef COPASI_CEvaluationNodeChoice
#define COPASI_CEvaluationNodeChoice

#include <limits>

class CCopasiDataModel;

/**
 * This is the class for nodes presenting operators used in an evaluation trees.
 */
class CEvaluationNodeChoice : public CEvaluationNode
{
public:
  /**
   * Enumeration of possible node types.
   */
  enum SubType
  {
    INVALID = 0x00FFFFFF,
    IF = 0x00000000
  };

  // Operations
private:
  /**
   * Default constructor
   */
  CEvaluationNodeChoice();

public:
  /**
   * Default constructor
   * @param const SubType & subType
   * @param const Data & data
   */
  CEvaluationNodeChoice(const SubType & subType,
                        const Data & data);

  /**
   * Copy constructor
   * @param const CEvaluationNodeChoice & src
   */
  CEvaluationNodeChoice(const CEvaluationNodeChoice & src);

  /**
   * Destructor
   */
  virtual ~CEvaluationNodeChoice();

  /**
   * Calculate the numerical result of the node. It is assumed that
   * all child nodes are up to date.
   */
  virtual void calculate();

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
   * Retrieve the display string of the node and its eventual child nodes in C .
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
   * Build the MathML string
   * @param const std::vector< std::string > & children
   * @param bool expand = true
   * @param const std::vector< std::vector< std::string > > & variables
   * @return std::string MMLString
   */
  virtual std::string getMMLString(const std::vector< std::string > & children,
                                   bool expand,
                                   const std::vector< std::vector< std::string > > & variables) const;

private:

  // Attributes
private:
  CEvaluationNode * mpIf;
  CEvaluationNode * mpTrue;
  CEvaluationNode * mpFalse;
};

#endif // COPASI_CEvaluationNodeChoice
