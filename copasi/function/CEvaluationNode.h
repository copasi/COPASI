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

#ifndef COPASI_CEvaluationNode
#define COPASI_CEvaluationNode

#include <iostream>
#include <vector>
#include <map>

#include "copasi/copasi.h"
#include "copasi/utilities/CCopasiNode.h"
#include "CFunctionAnalyzer.h"
#include "copasi/core/CEnumAnnotation.h"

class CMathContainer;
class CValidatedUnit;
class CIssue;

class CEvaluationTree;
LIBSBML_CPP_NAMESPACE_BEGIN
class ASTNode;
LIBSBML_CPP_NAMESPACE_END
class ConverterASTNode;
class CDataModel;

/**
 * This is the base class for nodes used in an evaluation trees
 */
class CEvaluationNode : public CCopasiNode< std::string >
{
public:
  /**
   * Enumeration of possible node types.
   */
  enum struct MainType
  {
    INVALID,
    NUMBER,
    CONSTANT,
    OPERATOR,
    OBJECT,
    FUNCTION,
    CALL,
    STRUCTURE,
    CHOICE,
    VARIABLE,
    WHITESPACE,
    LOGICAL,
    MV_FUNCTION, // This not yet implemented
    VECTOR,
    DELAY,
    UNIT,
    __SIZE
  };

  static const CEnumAnnotation< std::string, MainType > MainTypeName;

  enum struct SubType
  {
    DEFAULT,
    DELAY,
    IF,
    VECTOR,
    CN,
    DOUBLE,
    FUNCTION,
    LOG,
    OPEN,
    PI,
    POWER,
    EXPRESSION,
    POINTER,
    EXPONENTIALE,
    INTEGER,
    LOG10,
    MULTIPLY,
    OR,
    VECTOROPEN,
    COMMA,
    DIVIDE,
    ENOTATION,
    EXP,
    True,
    XOR,
    RATIONALE,
    AND,
    CLOSE,
    False,
    MODULUS,
    SIN,
    VECTORCLOSE,
    COS,
    EQ,
    Infinity,
    PLUS,
    NaN,
    MINUS,
    NE,
    TAN,
    REMAINDER,
    GT,
    SEC,
    CSC,
    GE,
    COT,
    LT,
    LE,
    SINH,
    COSH,
    TANH,
    SECH,
    CSCH,
    COTH,
    ARCSIN,
    ARCCOS,
    ARCTAN,
    ARCSEC,
    ARCCSC,
    ARCCOT,
    ARCSINH,
    ARCCOSH,
    ARCTANH,
    ARCSECH,
    ARCCSCH,
    ARCCOTH,
    SQRT,
    ABS,
    FLOOR,
    CEIL,
    FACTORIAL,
    NOT,
    RUNIFORM,
    RNORMAL,
    MAX,
    MIN,
    RGAMMA,
    RPOISSON,
    SIGN,
    AVOGADRO,
    INVALID,
    __SIZE
  };

  static const CEnumAnnotation< std::string, SubType > SubTypeName;

  enum struct ValueType
  {
    Unknown,
    Boolean,
    Number,
    __SIZE
  };

  // Methods
  /**
   * Creates an evaluation node of type with the given data
   * @param const MainType & mainType
   * @param const SubType & subType
   * @param const std::string & data
   * @return CEvaluationNode * evaluationNode
   */
  static CEvaluationNode * create(const MainType & mainType,
                                  const SubType & subType,
                                  const std::string & data);

  /**
   * Retrieve the subtype part of type
   * @return SubType subType
   */
  const SubType & subType() const;

  /**
   * Retrieve the type part of type
   * @return Type type
   */
  const MainType & mainType() const;

private:
  /**
   * A list of reserved key words
   */
  static const char * Keywords[];

public:
  /**
   * Check whether the string is a keyword
   * @param const std::string & str
   * @return bool isKeyword
   */
  static bool isKeyword(const std::string & str);

  /**
   * Default constructor
   */
  CEvaluationNode();

  /**
   * Unequal operator, compares two CEvaluationNode objects and return true if
   * they are equal.
   */
  bool operator!=(const CEvaluationNode& right) const;

  /**
   * Equals operator, compares two CEvaluationNode objects and return true if
   * they are equal.
   */
  bool operator==(const CEvaluationNode& right) const;

  /**
   * Less operator, compares two CEvaluationNode objects and return true if
   * the first operand is smaller than the second.
   */
  bool operator<(const CEvaluationNode& right) const;

protected:
  /**
   * Specific constructor
   * @param const MainType & mainType
   * @param const SubType & subType
   * @param const Data & data
   */
  CEvaluationNode(const MainType & type,
                  const SubType & subType,
                  const Data & data);

public:
  /**
   * Copy constructor
   * @param const CEvaluationNode & src
   */
  CEvaluationNode(const CEvaluationNode & src);

  /**
   * Destructor
   */
  virtual ~CEvaluationNode();

  /**
   * Retrieve the value of the node
   * @return const C_FLOAT64 & value
   */
  // inline const C_FLOAT64 & getValue() const {return *mpValue;}

  /**
   * Calculate the numerical result of the node. It is assumed that
   * all child nodes are up to date.
   */
  virtual inline void calculate() {};

  /**
   * Compile a node;
   * @return CIssue issue;
   */
  virtual CIssue compile();

  const CEvaluationTree * getTree() const;
  void setTree(const CEvaluationTree * pTree);

  /**
   * Retrieve the infix value of the node and its eventual child nodes.
   * @return std::string Infix
   */
  virtual std::string getInfix(const std::vector< std::string > & children) const;

  /**
   * Build the infix string.
   * @return std::string Infix
   */
  std::string buildInfix() const;

  /**
   * Retrieve the display string of the node and its eventual child nodes.
   * @return std::string DisplayString
   */
  virtual std::string getDisplayString(const std::vector< std::string > & children) const;

  /**
   * Build the human readable display string.
   * @return std::string DisplayString
   */
  std::string buildDisplayString() const;

  /**
   * Retrieve the display string of the node and its eventual child nodes in C.
   * @return std::string CCodeString
   */
  virtual std::string getCCodeString(const std::vector< std::string > & children) const;

  /**
   * Build the C-code string.
   * @return std::string CCodeString
   */
  std::string buildCCodeString() const;

  /**
   * Retrieve the display string of the node and its eventual child nodes
   * in Berkeley Madonna format.
   * @return std::string BerkeleyMadonnaString
   */
  virtual std::string getBerkeleyMadonnaString(const std::vector< std::string > & children) const;

  /**
   * Build the Berkeley Madonna string.
   * @return std::string BerkeleyMadonnaString
   */
  std::string buildBerkeleyMadonnaString() const;

  /**
   * Retrieve the display string of the node and its eventual child nodes
   * in XPPAUT format.
   * @return std::string XPPString
   */
  virtual std::string getXPPString(const std::vector< std::string > & children) const;

  /**
   * Build the XPPAUT string.
   * @return std::string XPPString
   */
  std::string buildXPPString() const;

  /**
   * Check whether the result is Boolean
   * @return bool isBoolean
   */
  virtual bool isBoolean() const;

  /**
   * Set the type the result of the node
   * @param const ValueType & valueType
   * @return CIssue issue;
   */
  virtual CIssue setValueType(const ValueType & valueType);

  /**
   * Retrieve the value type of the node
   * @return const ValueType & valueType
   */
  const ValueType & getValueType() const;

  /**
   * Add the children to the node
   * @param const std::vector< CEvaluationNode * > & children
   */
  void addChildren(const std::vector< CEvaluationNode * > & children);

  /**
   * Create a new invalid ASTNode.
   * @return ASTNode* return a pointer to the newly created node;
   */
  virtual ASTNode* toAST(const CDataModel* pDataModel) const;

  /**
   * Copy a node and assign new children child1 and child2
   * @return CEvaluationNode* return a pointer to the new node
   */
  CEvaluationNode* copyNode(CEvaluationNode* child1, CEvaluationNode* child2) const;

  /**
   * Copy a node and assign new children in the vector
   * @return CEvaluationNode* return a pointer to the new node
   */
  CEvaluationNode* copyNode(const std::vector<CEvaluationNode*>& children) const;

  /**
   * Copy the whole branch with this node as root.
   * @return CEvaluationNode*, return a pointer to the root of the newly copied branch
   */
  CEvaluationNode* copyBranch() const;

  /**
   * Create a simplified node from the original node with children child1 and child2 (if not exist, = NULL)
   * @return CEvaluationNode* return a pointer to the simplified node;
   */
  virtual CEvaluationNode* simplifyNode(const std::vector<CEvaluationNode*>& children) const;

  /**
   * Comparison operator used to evaluate the precedence of the node.
   * it compares the right precedence of the left node with the left
   * precedence of the right node.
   * @param const CEvaluationNode & rhs;
   * @return bool isLess
   */
  bool operator < (const CEvaluationNode & rhs);

  /**
   * Retrieve the pointer to the value of the node
   * @return const C_FLOAT64 * pValue
   */
  const C_FLOAT64 * getValuePointer() const;

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
   * Build the MathML string
   * @param bool expand = true
   * @param const std::vector< std::vector< std::string > > & variables
   * @return std::string MMLString
   */
  std::string buildMMLString(bool expand, const std::vector< std::vector< std::string > > & variables) const;

  void printRecursively(std::ostream & os, int indent = 0) const;

  void printRecursively() const;

  /**
   * Split the tree in two parts at the given splitnode, starting from *this.
   * Returned is the root node of a copy of the tree, including everything above
   * the split node and either the branch below the left child of the split node
   * or the branch below the right child of the split node. The split node itself
   * is not included either case.
   */
  CEvaluationNode* splitBranch(const CEvaluationNode* splitnode, bool left) const;

  /**
   * Find a minus operator in the tree that is suitable for splitting with splitBranch().
   * Specifically it is a minus operator that is connected with the root node by
   * multiplication or division nodes only. For the division nodes only the
   * left child is considered.
   */
  const CEvaluationNode* findTopMinus(const std::vector<CFunctionAnalyzer::CValue> & callParameters) const;

  /**
   * Figure out the appropriate CUnit to use, based on the child nodes.
   * This sets the default, appropriate for many cases, as Dimensionless
   * @param const CMathContainer & container
   * @param const std::vector< CValidatedUnit > & units
   * @return CUnit unit
   */
  virtual CValidatedUnit getUnit(const CMathContainer & container,
                                 const std::vector< CValidatedUnit > & units) const;

  /**
   * Set the unit for the node and return the resulting unit. The child node units are
   * added to the map
   * @param const CMathContainer & container
   * @param const std::map < CEvaluationNode * , CValidatedUnit > & currentUnits
   * @param std::map < CEvaluationNode * , CValidatedUnit > & targetUnits
   * @return CUnit unit
   */
  virtual CValidatedUnit setUnit(const CMathContainer & container,
                                 const std::map < CEvaluationNode *, CValidatedUnit > & currentUnits,
                                 std::map < CEvaluationNode *, CValidatedUnit > & targetUnits) const;

  // Attributes
protected:
  /**
   * The type the node
   */
  MainType mMainType;

  /**
   * The type the node
   */
  SubType mSubType;

  /**
   * The value type of the node
   */
  ValueType mValueType;

  /**
   * The numerical value of the node
   */
  C_FLOAT64 mValue;

  /**
   * A pointer to the numerical value of the node
   */
  const C_FLOAT64 * mpValue;

  const CEvaluationTree * mpTree;

  /**
   * Structure holding the precedence information
   * The Precedence Table
   * ====================
   *
   * Nodes of type WHITESPACE are ignored.
   * Higher right than left precedence means evaluation
   * proceeds form left to right. Higher left precedence
   * as can be found for the operator '^' means evaluation
   * proceeds from right to left.
   *
   *  left precedence |              | right precedence
   * -----------------+--------------+------------------
   *                  | LOGIC:       |
   *   3              |  .not.       |  2
   *   4              |  .or.        |  5
   *   6              |  .xor.       |  7
   *   8              |  .and.       |  9
   *  10              |  .eq.        | 11
   *  12              |  .ne.        | 13
   *  14              |  .gt.        | 15
   *  16              |  .ge.        | 17
   *  18              |  .lt.        | 19
   *  20              |  .le.        | 21
   * -----------------+--------------+------------------
   *                  | OPERATOR:    |
   *  22              |  -           | 23
   *  22              |  +           | 23
   *  26              |  %           | 27
   *  28              |  /           | 29
   *  28              |  *           | 29
   *  33              |  ^           | 32
   * -----------------+--------------+------------------
   *  35              | FUNCTION     | 34
   *  35              | MV_FUNCTION  | 34
   *  35              | CALL         | 34
   *  35              | CHOICE       | 34
   * -----------------+--------------+------------------
   *  36              | NUMBER       | 37
   *  36              | CONSTANT     | 37
   *  36              | OBJECT       | 37
   *  36              | VARIABLE     | 37
   * -----------------+--------------+------------------
   *                  | STRUCTURE:   |
   *  ULONG_MAX       |  (| 1
   *  0               |  , | 1
   *  0               |)           | ULONG_MAX
   */
  class CPrecedence
  {
  public:
    /**
     * Default constructor
     * @param const size_t & left (default: 0)
     * @param const size_t & right (default: 0)
     */
    CPrecedence(const size_t & left = 0,
                const size_t & right = 0);

    /**
     * Copy constructor
     * @param const CPrecedence & src
     */
    CPrecedence(const CPrecedence & src);

    /**
     * Destructor
     */
    ~CPrecedence();

    /**
     * The left precedence
     */
    size_t left;

    /**
     * The left precedence
     */
    size_t right;
  }
  mPrecedence;
};

constexpr size_t operator | (CEvaluationNode::MainType main, CEvaluationNode::SubType sub)
{
  return static_cast< size_t >(main) * 0xffffff + static_cast< size_t >(sub);
}

#define PRECEDENCE_DEFAULT CPrecedence(0, 0)

#define PRECEDENCE_LOGIG_NOT CPrecedence(3, 2)
#define PRECEDENCE_LOGIG_OR CPrecedence(4, 5)
#define PRECEDENCE_LOGIG_XOR CPrecedence(6, 7)
#define PRECEDENCE_LOGIG_AND CPrecedence(8, 9)
#define PRECEDENCE_LOGIG_EQ CPrecedence(10, 11)
#define PRECEDENCE_LOGIG_NE CPrecedence(12, 13)
#define PRECEDENCE_LOGIG_GT CPrecedence(14, 15)
#define PRECEDENCE_LOGIG_GE CPrecedence(16, 17)
#define PRECEDENCE_LOGIG_LT CPrecedence(18, 19)
#define PRECEDENCE_LOGIG_LE CPrecedence(20, 21)

#define PRECEDENCE_OPERATOR_MINUS CPrecedence(22, 23)
#define PRECEDENCE_OPERATOR_PLUS CPrecedence(22, 23)
#define PRECEDENCE_OPERATOR_REMAINDER CPrecedence(26, 27)
#define PRECEDENCE_OPERATOR_MODULUS CPrecedence(26, 27)
#define PRECEDENCE_OPERATOR_DIVIDE CPrecedence(28, 29)
#define PRECEDENCE_OPERATOR_MULTIPLY CPrecedence(28, 29)
#define PRECEDENCE_OPERATOR_POWER CPrecedence(33, 32)

#define PRECEDENCE_FUNCTION CPrecedence(35, 34)

#define PRECEDENCE_NUMBER CPrecedence(36, 37)

#define PRECEDENCE_STRUCTURE_OPEN CPrecedence(ULONG_MAX, 1)
#define PRECEDENCE_STRUCTURE_COMMA CPrecedence(0, 1)
#define PRECEDENCE_STRUCTURE_CLOSE CPrecedence(0, ULONG_MAX)

#include "CEvaluationNodeCall.h"
#include "CEvaluationNodeChoice.h"
#include "CEvaluationNodeConstant.h"
#include "CEvaluationNodeDelay.h"
#include "CEvaluationNodeFunction.h"
#include "CEvaluationNodeLogical.h"
#include "CEvaluationNodeNumber.h"
#include "CEvaluationNodeObject.h"
#include "CEvaluationNodeOperator.h"
#include "CEvaluationNodeStructure.h"
#include "CEvaluationNodeVariable.h"
#include "CEvaluationNodeVector.h"
#include "CEvaluationNodeWhiteSpace.h"
#include "CEvaluationNodeUnit.h"

#endif // COPASI_CEvaluationNode
