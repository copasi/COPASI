// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"
#include "utilities/CCopasiNode.h"
#include "CFunctionAnalyzer.h"

class CMathContainer;
class CValidatedUnit;

class CEvaluationTree;
LIBSBML_CPP_NAMESPACE_BEGIN
class ASTNode;
LIBSBML_CPP_NAMESPACE_END
class ConverterASTNode;
class CCopasiDataModel;

/**
 * This is the base class for nodes used in an evaluation trees
 */
class CEvaluationNode : public CCopasiNode< std::string >
{
public:
  /**
   * Enumeration of possible node types.
   */
  enum MainType
  {
    T_INVALID = 0xFF000000,
    T_NUMBER = 0x01000000,
    T_CONSTANT = 0x02000000,
    T_OPERATOR = 0x03000000,
    T_OBJECT = 0x04000000,
    T_FUNCTION = 0x05000000,
    T_CALL = 0x06000000,
    T_STRUCTURE = 0x07000000,
    T_CHOICE = 0x08000000,
    T_VARIABLE = 0x09000000,
    T_WHITESPACE = 0x0a000000,
    T_LOGICAL = 0x0b000000,
    T_MV_FUNCTION = 0x0c000000, // This not yet implemented
    T_VECTOR = 0x0d000000,
    T_DELAY = 0x0e000000,
    T_UNIT = 0x0f000000
  };

#ifdef S_FALSE
# undef S_FALSE
#endif

  enum SubType
  {
    S_DEFAULT = 0x00000000,
    S_DELAY = 0x00000001,
    S_IF = 0x00000002,
    S_VECTOR = 0x00000003,
    S_CN = 0x00000004,
    S_DOUBLE = 0x00000005,
    S_FUNCTION = 0x00000006,
    S_LOG = 0x00000007,
    S_OPEN = 0x00000008,
    S_PI = 0x00000009,
    S_POWER = 0x0000000A,
    S_EXPRESSION = 0x0000000B,
    S_POINTER = 0x0000000C,
    S_EXPONENTIALE = 0x0000000D,
    S_INTEGER = 0x0000000E,
    S_LOG10 = 0x0000000F,
    S_MULTIPLY = 0x00000010,
    S_OR = 0x00000011,
    S_VECTOR_OPEN = 0x00000012,
    S_COMMA = 0x00000013,
    S_DIVIDE = 0x00000014,
    S_ENOTATION = 0x00000015,
    S_EXP = 0x00000016,
    S_TRUE = 0x00000017,
    S_XOR = 0x00000018,
    S_RATIONALE = 0x00000019,
    S_AND = 0x0000001A,
    S_CLOSE = 0x0000001B,
    S_FALSE = 0x0000001C,
    S_MODULUS = 0x0000001D,
    S_SIN = 0x0000001E,
    S_VECTOR_CLOSE = 0x0000001F,
    S_COS = 0x00000020,
    S_EQ = 0x00000021,
    S_INFINITY = 0x00000022,
    S_PLUS = 0x00000023,
    S_NAN = 0x00000024,
    S_MINUS = 0x00000025,
    S_NE = 0x00000026,
    S_TAN = 0x00000027,
    S_REMAINDER = 0x00000028,
    S_GT = 0x00000029,
    S_SEC = 0x0000002A,
    S_CSC = 0x0000002B,
    S_GE = 0x0000002C,
    S_COT = 0x0000002D,
    S_LT = 0x0000002E,
    S_LE = 0x0000002F,
    S_SINH = 0x00000030,
    S_COSH = 0x00000031,
    S_TANH = 0x00000032,
    S_SECH = 0x00000033,
    S_CSCH = 0x00000034,
    S_COTH = 0x00000035,
    S_ARCSIN = 0x00000036,
    S_ARCCOS = 0x00000037,
    S_ARCTAN = 0x00000038,
    S_ARCSEC = 0x00000039,
    S_ARCCSC = 0x0000003A,
    S_ARCCOT = 0x0000003B,
    S_ARCSINH = 0x0000003C,
    S_ARCCOSH = 0x0000003D,
    S_ARCTANH = 0x0000003E,
    S_ARCSECH = 0x0000003F,
    S_ARCCSCH = 0x00000040,
    S_ARCCOTH = 0x00000041,
    S_SQRT = 0x00000042,
    S_ABS = 0x00000043,
    S_FLOOR = 0x00000044,
    S_CEIL = 0x00000045,
    S_FACTORIAL = 0x00000046,
    S_NOT = 0x00000047,
    S_RUNIFORM = 0x00000048,
    S_RNORMAL = 0x00000049,
    S_MAX = 0x0000004A,
    S_MIN = 0x0000004B,
    S_RGAMMA = 0x0000004C,
    S_RPOISSON = 0x0000004D,
    S_SIGN = 0x0000004E,
    S_INVALID = 0x00FFFFFF
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
   * @param const CEvaluationTree * pTree
   * @return bool success;
   */
  virtual bool compile(const CEvaluationTree * pTree);

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
   * Add the children to the node
   * @param const std::vector< CEvaluationNode * > & children
   */
  void addChildren(const std::vector< CEvaluationNode * > & children);

  /**
   * Create a new invalid ASTNode.
   * @return ASTNode* return a pointer to the newly created node;
   */
  virtual ASTNode* toAST(const CCopasiDataModel* pDataModel) const;

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
                                 const std::map < CEvaluationNode * , CValidatedUnit > & currentUnits,
                                 std::map < CEvaluationNode * , CValidatedUnit > & targetUnits) const;

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
   * The numerical value of the node
   */
  C_FLOAT64 mValue;

  /**
   * A pointer to the numerical value of the node
   */
  const C_FLOAT64 * mpValue;

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
