// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationTree.h,v $
//   $Revision: 1.41 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/24 16:32:35 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_CEvaluationTree
#define COPASI_CEvaluationTree

#include <vector>
#include <stack>

#include "copasi/model/CAnnotation.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/report/CCopasiContainer.h"

class ASTNode;
template <class CType> class CCopasiVectorN;

class CEvaluationTree:
    public CCopasiContainer
{
public:
  /**
   *  The valid types of a function
   */
  enum Type
  {
    Function = 0,
    MassAction,
    PreDefined,
    UserDefined,
    Expression,
    MathExpression
  };

  /**
   *  The string representation of valid types of a function
   */
  static const std::string TypeName[];

  /**
   *  The string representation of valid types of a function
   */
  static const char * XMLType[];

  // Operations
public:
  /**
   * Create an EvaluationTree of the specified type.
   * Note: the returned object has to be released after use with delete.
   * @param CEvaluationTree::Type type
   * @return EvaluationTree * pEvaluationTree
   */
  static CEvaluationTree *
  create(CEvaluationTree::Type type);

  /**
   * Copy an EvaluationTree of the specified type.
   * Note: the returned object has to be released after use with delete.
   * @param const EvaluationTree & src
   * @return EvaluationTree * pEvaluationTree
   */
  static CEvaluationTree *
  copy(const CEvaluationTree & src);

  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CCopasiContainer * pParent (default: NULL)
   * @param const CEvaluationTree::Type & type (default: Function)
   */
  CEvaluationTree(const std::string & name = "NoName",
                  const CCopasiContainer * pParent = NULL,
                  const Type & type = Function);

  /**
   * Copy constructor
   * @param const CEvaluationTree & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CEvaluationTree(const CEvaluationTree & src,
                  const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  virtual ~CEvaluationTree();

  /**
   * Retrieves the type of the function
   * @return const CEvaluationTree::Type & type
   */
  const CEvaluationTree::Type & getType() const;

protected:
  /**
   * Set the type of the function
   * @param const CEvaluationTree::Type & type
   */
  void setType(const CEvaluationTree::Type & type);

public:
  /**
   * Sets the root node of the tree.
   * @param CEvaluationNode* root node of the tree
   * @return bool success
   */
  bool setRoot(CEvaluationNode* pRootNode);

  /**
   * Sets the complete tree from an SBML ASTNode.
   * @param const ASTNode& root node of the tree
   * @return bool success
   */
  bool setTree(const ASTNode& pRootNode);

  /**
   * Converts an SBML ASTNode to the corresponding
   * CEvaluationNode tree.
   * @param const ASTNode& node
   * @return CEvaluationNode*
   */
  static CEvaluationNode* convertASTNode(const ASTNode& node);

  /**
   * Converts a CEvaluationTree to an ASTNode based tree.
   * @return ASTNode* root node of the tree.
   */
  virtual ASTNode* toAST(const CCopasiDataModel* pDataModel) const;

  /**
   * Set the infix description of the tree and compile it.
   * @param const std::string & infix
   * @return bool success
   */
  virtual bool setInfix(const std::string & infix);

  /**
   * Compile the evaluation tree.
   */
  virtual bool compile();

  /**
   * Check whether this function is usable, i.e., properly defined
   * @return bool isUsable
   */
  bool isUsable() const;

  /**
   * Check whether this function evaluates to a boolean value.
   * @return bool isBoolean
   */
  bool isBoolean() const;

  /**
   * Retrieve the infix description of the tree
   * @return const std::string & infix
   */
  const std::string & getInfix() const;

  /**
   * Comparison operator
   * @param const CEvaluationTree & rhs
   * @return bool equal
   */
  bool operator == (const CEvaluationTree & rhs) const;

  /**
   * Retrieve the position of the error in the string description.
   * std::string::npos indicates no error.
   * @return std::string::size_type errorPosition
   */
  std::string::size_type getErrorPosition() const;

  /**
   * Retrieve the list of nodes
   * @return const std::vector< CEvaluationNode * > & nodeList;
   */
  const std::vector< CEvaluationNode * > & getNodeList() const;

  /**
   * Retrieve the index to the value of the named variable.
   * @param const std::string & name
   * @return size_t
   */
  virtual size_t getVariableIndex(const std::string & name) const;

  /**
   * Retrieve the value of the indexed variable
   * @param const size_t & index
   * @return const C_FLOAT64 & variableValue
   */
  virtual const C_FLOAT64 & getVariableValue(const size_t & index) const;

  /**
   * Returns the root node of the tree.
   */
  CEvaluationNode* getRoot();

  /**
   * Returns the root node of the tree.
   */
  const CEvaluationNode* getRoot() const;

  /**
   * Updates the infix and the nodeList
   */
  bool updateTree();

  /**
   * Check whether the the tree has circular dependencies.
   * @return bool hasCircularDependency
   */
  bool hasCircularDependency() const;

  /**
   * Checks whether the tree has a call node referring to the expression
   * with the given name
   * @param const std::string & name
   * @return bool dependsOn
   */
  bool dependsOnTree(const std::string & name) const;

  /**
   * Retrieve the list of deleted objects.
   * @return CCopasiObject::DataObjectSet deletedObjects
   */
  CCopasiObject::DataObjectSet getDeletedObjects() const;

  /**
   * Check whether the evaluation tree calls any tree in the list
   * @param std::set< std::string > & list
   * @return bool calls
   */
  bool calls(std::set< std::string > & list) const;

  /**
   * Check whether tree may introduce discontinuities.
   * @return bool hasDiscontinity
   */
  bool hasDiscontinuity() const;

protected:
  /**
   * Parse the description
   * @return bool success
   */
  bool parse();

  /**
   * Compile the individual nodes.
   * @return bool success
   */
  bool compileNodes();

private:
  /**
   * Initialize the contained CCopasiObjects
   */
  void initObjects();

  // Attributes
protected:
  /**
   * The type of the function
   */
  CEvaluationTree::Type mType;

private:
  /**
   * The key of the function
   */
  // std::string mKey;

protected:
  /**
   * The infix representation of the expression
   */
  std::string mInfix;

  /**
   * Value indicating whether this functions might be used in a model
   */
  bool mUsable;

private:
  /**
   * The error position in case the compilation fails.
   * std::string::npos indicates no error.
   */
  std::string::size_type mErrorPosition;

protected:
  /**
   * A vector of nodes containing the result of parse.
   */
  std::vector< CEvaluationNode * > * mpNodeList;

  /**
   * The root node of the tree.
   */
  CEvaluationNode * mpRoot;

  /**
   * The last computed value of the tree;
   */
  C_FLOAT64 mValue;

  /**
   * Indicates whether the tree must evaluate to a boolean value.
   */
  bool mBooleanRequired;
};

#endif // COPASI_CEvaluationTree
