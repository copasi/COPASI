// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNode.h,v $
//   $Revision: 1.34.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/10/17 19:08:16 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CEvaluationNode
#define COPASI_CEvaluationNode

#include <iostream>
#include <vector>

#include "copasi.h"
#include "utilities/CCopasiNode.h"
#include "CFunctionAnalyzer.h"

class CEvaluationTree;
class ASTNode;
class ConverterASTNode;

/**
 * This is the base class for nodes used in an evaluation trees
 */
class CEvaluationNode : public CCopasiNode< std::string >
  {
  public:
    /**
     * Enumeration of possible node types.
     */
    enum Type
    {
      INVALID = 0xFF000000,
      NUMBER = 0x01000000,
      CONSTANT = 0x02000000,
      OPERATOR = 0x03000000,
      OBJECT = 0x04000000,
      FUNCTION = 0x05000000,
      CALL = 0x06000000,
      STRUCTURE = 0x07000000,
      CHOICE = 0x08000000,
      VARIABLE = 0x09000000,
      WHITESPACE = 0x0a000000,
      LOGICAL = 0x0b000000,
      MV_FUNCTION = 0x0c000000, // This not yet implemented
      VECTOR = 0x0d000000
    };

    // Methods
    /**
     * Creates an evaluation node of type with the given data
     * @param const Type & type
     * @param const Data & data
     * @return CEvaluationNode * evaluationNode
     */
    static CEvaluationNode * create(const Type & type,
                                    const Data & data);

    /**
     * Retrieve the subtype part of type
     * @param const Type & type
     * @return Type subType
     */
    static Type subType(const Type & type);

    /**
     * Retrieve the type part of type
     * @param const Type & type
     * @return Type type
     */
    static Type type(const Type & type);

  public:
    /**
     * Default constructor
     */
    CEvaluationNode();

    /**
     * Unequal operator, compares two CEvaluationNode objects and return true if
     * they are equal.
     */
    virtual bool operator!=(const CEvaluationNode& right) const;

    /**
     * Equals operator, compares two CEvaluationNode objects and return true if
     * they are equal.
     */
    virtual bool operator==(const CEvaluationNode& right) const;

    /**
     * Less operator, compares two CEvaluationNode objects and return true if
     * the first operand is smaller than the second.
     */
    virtual bool operator<(const CEvaluationNode& right) const;

  protected:
    /**
     * Specific constructor
     * @param const Type & type
     * @param const Data & data
     */
    CEvaluationNode(const Type & type,
                    const Data & data);

    /**
     * Replaces all root nodes with the corresponding power
     * operator since COPASI does not have the ROOT function.
     */
    static void replaceRoot(ConverterASTNode* sourceNode);

    /**
     * Replaces all LOG10 (AST_FUNCTION_LOG) nodes that have two
     * children with the quotient of two LOG10 nodes with the base
     * as the argument for the divisor LOG10 node.
     */
    static void replaceLog(ConverterASTNode* sourceNode);

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
    virtual inline const C_FLOAT64 & value() const {return mValue;}

    /**
     * Compile a node;
     * @param const CEvaluationTree * pTree
     * @return bool success;
     */
    virtual bool compile(const CEvaluationTree * pTree);

    /**
     * Retrieve the value of the node. This method is superseded
     * value() which will perform faster.
     * @return const Data value
     */
    virtual Data getData() const;

    /**
     * Set the data of the Node.
     * @param const Data & data
     * @return bool success
     */
    virtual bool setData(const Data & data);

    /**
     * Retrieve the infix value of the node and its eventual child nodes.
     * @return const Data & value
     */
    virtual std::string getInfix() const;

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
     * Retrieve the type of the node.
     * Note the type combines type and subType information. To
     * Retrieve the type use type(getType()) and to retrieve the
     * subType use subType(getType()).
     * @return const Type & type.
     */
    const Type & getType() const;

    /**
     * Create a new invalid ASTNode.
     * @return ASTNode* return a pointer to the newly created node;
     */
    virtual ASTNode* toAST() const;

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
     * generate display MathML recursively
     */
    virtual void writeMathML(std::ostream & out,
                             const std::vector<std::vector<std::string> > & env,
                             bool expand = true,
                             unsigned C_INT32 l = 0) const;

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

    // Attributes
  protected:
    /**
     * The type the node
     */
    Type mType;

    /**
     * The numerical value of the node
     */
    C_FLOAT64 mValue;

    /**
     * The data of the node
     */
    Data mData;

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
         * @param const unsigned C_INT32 & left (default: 0)
         * @param const unsigned C_INT32 & right (default: 0)
         */
        CPrecedence(const unsigned C_INT32 & left = 0,
                    const unsigned C_INT32 & right = 0);

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
        unsigned C_INT32 left;

        /**
         * The left precedence
         */
        unsigned C_INT32 right;
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
#include "CEvaluationNodeFunction.h"
#include "CEvaluationNodeLogical.h"
#include "CEvaluationNodeNumber.h"
#include "CEvaluationNodeObject.h"
#include "CEvaluationNodeOperator.h"
#include "CEvaluationNodeStructure.h"
#include "CEvaluationNodeVariable.h"
#include "CEvaluationNodeVector.h"
#include "CEvaluationNodeWhiteSpace.h"

#endif // COPASI_CEvaluationNode
