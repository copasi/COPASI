// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_CEvaluationTree
#define COPASI_CEvaluationTree

#include <stack>

#include "copasi/function/CEvaluationNode.h"
#include "copasi/core/CDataContainer.h"
#include "copasi/core/CVector.h"

#include "copasi/copasi.h"
LIBSBML_CPP_NAMESPACE_BEGIN
class ASTNode;
LIBSBML_CPP_NAMESPACE_END
template <class CType> class CDataVectorN;

class CEvaluationTree:
  public CDataContainer
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

protected:
  CEvaluationTree(const CEvaluationTree & src);

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
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CEvaluationTree * pDataObject
   */
  static CEvaluationTree * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CDataContainer * pParent (default: NULL)
   * @param const CEvaluationTree::Type & type (default: Function)
   */
  CEvaluationTree(const std::string & name = "NoName",
                  const CDataContainer * pParent = NO_PARENT,
                  const Type & type = Function);

  /**
   * Copy constructor
   * @param const CEvaluationTree & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CEvaluationTree(const CEvaluationTree & src,
                  const CDataContainer * pParent);

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
  virtual bool setRoot(CEvaluationNode* pRootNode);

  /**
   * Sets the complete tree from an SBML ASTNode.
   * @param const ASTNode& root node of the tree
   * @param bool isFunction
   * @return bool success
   */
  bool setTree(const ASTNode& pRootNode, bool isFunction);

  /**
   * Retrieve a pointer to the object defined by CN. This method may only be called
   * during compile() since the list mpListOfContainer is only valid then.
   * @param const CCommonName & CN
   * @return const CObjectInterface * value
   */
  virtual const CObjectInterface * getNodeObject(const CCommonName & CN) const;

  /**
   * Converts an SBML ASTNode to the corresponding
   * CEvaluationNode tree.
   * @param const ASTNode * pASTNode
   * @param bool isFunction
   * @return CEvaluationNode*
   */
  static CEvaluationNode* fromAST(const ASTNode * pASTNode, bool isFunction);

  /**
   * Converts a CEvaluationTree to an ASTNode based tree.
   * @return ASTNode* root node of the tree.
   */
  virtual ASTNode* toAST(const CDataModel* pDataModel) const;

  /**
   * Set the infix description of the tree and compile it.
   * @param const std::string & infix
   * @return CIssue issue
   */
  virtual CIssue setInfix(const std::string & infix);

  /**
   * Compile the evaluation tree.
   */
  virtual CIssue compile();

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
  CIssue updateTree();

  /**
   * Check whether the the tree has circular dependencies.
   * @return bool hasCircularDependency
   */
  bool hasCircularDependency() const;

  /**
   * Check whether the evaluation tree calls any tree in the list
   * @param std::set< std::string > & list
   * @return bool calls
   */
  bool calls(std::set< std::string > & list) const;

  /**
   * Check whether tree may introduce discontinuities.
   * @return bool hasDiscontinuity
   */
  bool hasDiscontinuity() const;

  /**
   * @return true if any of the given CN's is used by this expression
   */
  bool containsCN(const DataObjectSet& elements) const;

  /**
   * Retrieve the number of node evaluations required to computate the value of the tree.
   * @return size_t size
   */
  size_t size() const;

  /**
   * Map object nodes which are children of the src container to children of the target container
   * @param const CDataContainer * pSrc
   * @param const CDataContainer * pTarget
   * @return bool success;
   */
  bool mapObjectNodes(const CDataContainer * pSrc, const CDataContainer * pTarget);

protected:
  /**
   * Parse the description
   * @return CIssue issue
   */
  CIssue parse();

  /**
   * Compile the individual nodes.
   * @return CIssue issue
   */
  CIssue compileNodes();

  /**
   * Build the sequence of calculations required to determine
   * the value of the expression.
   */
  void buildCalculationSequence();

  /**
   * Calculate the value
   */
  void calculate();

  /**
   * Convenient function to free the list of generated nodes.
   */
  void clearNodes();

private:
  /**
   * Initialize the contained CDataObjects
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

private:
  /**
   * The root node of the tree.
   */
  CEvaluationNode * mpRootNode;

protected:
  const C_FLOAT64 * mpRootValue;

  /**
   * The last computed value of the tree;
   */
  C_FLOAT64 mValue;

  /**
   * A vector of nodes which need to be calculated in sequence
   */
  CVector< CEvaluationNode * > mCalculationSequence;
};

#endif // COPASI_CEvaluationTree
