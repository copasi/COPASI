// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CNormalTranslation_H__
#define COPASI_CNormalTranslation_H__

class CNormalFraction;
class CEvaluationTree;

#include <exception>
#include <list>

#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationNodeOperator.h"

class recursion_limit_exception : public std::exception
{
public:
  enum LIMIT_TYPE
  {
    SIMPLIFY,
    NORM_AND_SIMPLIFY
  };

  /**
   * constructor
   */
  recursion_limit_exception(LIMIT_TYPE type);

protected:
  LIMIT_TYPE mType;
};

struct summ_match
{

  summ_match() :
    factor(0.0)
    , pNode(NULL)
  {
  }

  double factor;
  CEvaluationNode* pNode;
  std::set<unsigned int> addition_indices;
  std::set<unsigned int> subtraction_indices;
};

struct product_match : public summ_match
{

  product_match() :
    summ_match()
    , pExponentNode(NULL)
  {
  }

  CEvaluationNode* pExponentNode;
};

/**
 * The class for simplification and translation of trees into CNormal
 */
class CNormalTranslation
{
public:
  static bool has_duplicate_nodes(const CEvaluationNode* pNode);

  /**
   * Simplify an evaluation tree given by the root node by creating a new simplified tree from the original one.
   * The tree itself is actually not created!
   * @return NodeClass*, pointer to root node of the newly created tree.
   */
  static CEvaluationNode* simplifyTree(const CEvaluationNode* node);

  /**
   * Creating a simplified tree by calling simplifyTree repeatedly until it cannot be simplified further.
   * The tree itself is actually not created!
   * @return NodeClass*, pointer to root node of the newly created tree.
   */
  static CEvaluationNode* simplifyTreeReptdly(const CEvaluationNode* root0);

  /**
   * Translate and simplify a tree given by the root node into CNormal structure
   * @return CNormalFraction*
   */
  static CNormalFraction* normAndSimplify(const CEvaluationNode* root0);

  /**
   * Translate and simplify a tree by calling normAndSimplify repeatedly until it cannot be simplified further
   * The second parameter is a depth value that is used to track the
   * recursion. If a given limit (currently 20) is reached, the algorithm throws an exception.
   * @return CNormalFraction*
   */
  static CNormalFraction* normAndSimplifyReptdly(const CEvaluationTree* tree0, unsigned int depth = 0);

  /**
   * Translate and simplify a tree by calling normAndSimplify repeatedly until it cannot be simplified further
   * @return CNormalFraction*
   */
  static CNormalFraction* normAndSimplifyReptdly(const CEvaluationNode* tree0, unsigned int depth = 0);

  /**
   * More general version of createOperatorChain.
   * This method can also be used to combine logical item chains.
   * Once I know this works, I will replace createOperatorChain with this
   * method.
   */
  static CEvaluationNode* createChain(const CEvaluationNode* pLink, const CEvaluationNode* pNeutralElement, const std::vector<const CEvaluationNode*>& elements);

  /**
   * More general version of createOperatorChain.
   * This version does not copy the nodes in the given vector, but uses them
   * directly.
   * This method can also be used to combine logical item chains.
   * method.
   */
  static CEvaluationNode* createChain(const CEvaluationNode* pLink, const CEvaluationNode* pNeutralElement, const std::vector<CEvaluationNode*>& elements);

  /**
   * Given a vector of nodes, this method creates a multiplication chain of
   * all the nodes. The chain contains copies of the nodes passed in.
   */
  static CEvaluationNode* createOperatorChain(CEvaluationNode::SubType type, const char* data, const std::vector<CEvaluationNode*>& nodes);

  /**
   * Given a vector of nodes, this method creates a multiplication chain of
   * all the nodes. The chain contains copies of the nodes passed in.
   */
  static CEvaluationNode* createOperatorChain(CEvaluationNode::SubType type, const char* data, const std::vector<const CEvaluationNode*>& nodes);

  /**
   * Given a root node, this method traverses the tree and expands products in
   * power bases to multiplications of power items.
   * It is the responsibility of the caller to delete the returned node.
   */
  static CEvaluationNode* expandPowerBases(const CEvaluationNode* pRoot);

  /**
   * Given a root node, this method traverses the tree and expands sums in
   * power exponents to multiplications of power items.
   * It is the responsibility of the caller to delete the returned node.
   */
  static CEvaluationNode* expandPowerExponents(const CEvaluationNode* pRoot);

  /**
   * Given a node, the method check if the node is a PLUS node, if so, it
   * calls itself recursively on the children.
   * This way all summands of a summation chain are gathered.
   * All items in the vector are children of pRoot.
   */
  static void findSummands(const CEvaluationNode* pRoot, std::vector<const CEvaluationNode*>& summands);

  /**
   * This method expands products. (A+B)*(C+D) -> (A*C)+(A*D)+(B*C)+(B*D)
   * This method should be replaced by the one below pretty soon.
   */
  static CEvaluationNode* expandProducts(const CEvaluationNode* pOrig);

  /**
   * This method expands products. (A+B)*(C+D) -> (A*C)+(A*D)+(B*C)+(B*D)
   */
  //static CEvaluationNode* expandProducts(CEvaluationNode* pOrig);

  /**
   * This method splits a product into the individual elements
   */
  static void splitProduct(const CEvaluationNode* pRoot, std::vector<const CEvaluationNode*>& multiplications, std::vector<const CEvaluationNode*>& divisions, bool division);

  /**
   * This method splits a sum into the individual elements.
   * The returned nodes are copies of the original.
   */
  static void splitSum(const CEvaluationNode* pRoot, std::vector<CEvaluationNode*>& additions, std::vector<CEvaluationNode*>& substractions, bool minus);

  /**
   * This method splits a sum into the individual elements.
   * The returned nodes are part of the original node and not copies.
   */
  static void splitSum(const CEvaluationNode* pRoot, std::vector<const CEvaluationNode*>& additions, std::vector<const CEvaluationNode*>& substractions, bool minus);

  /**
   * This method evaluates operators acting on two numbers
   */
  // obsolete recursive version
  //static CEvaluationNode* evaluateNumbers(const CEvaluationNode* pOrig);

  /**
   * This method evaluates operators acting on two numbers
   */
  static CEvaluationNode* newEvaluateNumbers(const CEvaluationNode* pOrig);

  /**
   * Neutral element for an addition chain.
   */
  static const CEvaluationNode NEUTRAL_ELEMENT_ADD;

  /**
   * Neutral element for a multiplication chain.
   */
  static const CEvaluationNode NEUTRAL_ELEMENT_MULTIPLY;

  /**
   * Neutral element for an or chain.
   */
  static const CEvaluationNode NEUTRAL_ELEMENT_OR;

  /**
   * Neutral element for an and chain.
   */
  static const CEvaluationNode NEUTRAL_ELEMENT_AND;

  /**
   * Number node that represents 0.0
   */
  static const CEvaluationNode ZERO_NODE;

  /**
   * Number node that represents 1.0
   */
  static const CEvaluationNode ONE_NODE;

  /**
   * Operator node that represents the PLUS operation.
   */
  static const CEvaluationNode PLUS_NODE;

  /**
   * Operator node that represents the TIMES operation.
   */
  static const CEvaluationNode TIMES_NODE;

protected:
  /**
   * This routine moves all negative numbers from vector v1 to v2
   * and changes the number to a positive number.
   */
  static void swapNegativeNumbers(std::vector<CEvaluationNode*>& v1, std::vector<CEvaluationNode*>& v2);

  /**
   * This routine finds all negative numbers in vector v1
   * and adds a copy with a positive number to v2
   */
  static void findNegativeNumbers(std::vector<const CEvaluationNode*>& v1, std::vector<CEvaluationNode*>& v2);

  /**
   * This routine is responsible for recursively simplifying a given
   * CEvaluationNode based tree.
   */
  static CEvaluationNode* simplify(const CEvaluationNode* pOrig);

  /**
   * This routine is responsible for all elementary eliminations, e.g. addition
   * of 0.
   * These steps can not lead to new simplifications in the children of the node
   * being simplified, so it is not necessary to run this on the children again.
   */
  static CEvaluationNode* elementaryElimination(CEvaluationNode* pOrig);

  /**
   * This method makes elementary eliminations on function nodes
   */
  static CEvaluationNode* elementaryEliminationFunction(const CEvaluationNode* pFunctionNode);

  /**
   * This method makes the elementary elimination on a power node.
   */
  static CEvaluationNode* elementaryEliminationPower(const CEvaluationNode* pPowerNode);

  /**
   * This method makes the elementary elimination on a modulus node.
   */
  static CEvaluationNode* elementaryEliminationModulus(const CEvaluationNode* pModulusNode);

  /**
   * This method makes the elementary elimination on a multiply node.
   */
  static CEvaluationNode* elementaryEliminationMultiply(const CEvaluationNode* pMultiplyNode);

  /**
   * This method makes the elementary elimination on a divide node.
   */
  static CEvaluationNode* elementaryEliminationDivide(const CEvaluationNode* pDivideNode);

  /**
   * This method makes the elementary elimination on a plus node.
   */
  static CEvaluationNode* elementaryEliminationPlus(const CEvaluationNode* pPlusNode);

  /**
   * This method makes the elementary elimination on a minus node.
   */
  static CEvaluationNode* elementaryEliminationMinus(const CEvaluationNode* pMinusNode);

  /**
   * This method removes nested power nodes, e.g. (a^b)^c -> a^(b*c)
   */
  static CEvaluationNode* eliminateNestedPowers(const CEvaluationNode* pOrig);

  /**
   * This method expands the exponents of power nodes, e.g. A^(x+y) -> A^x * A^y
   */
  static CEvaluationNode* expandPowerNodes(const CEvaluationNode* pOrig);

  /**
   * The methods get a vector of multiplication elements and a vector of division
   * elements and tries to find elements with the same power base in those two vectors.
   */
  //static std::vector<std::pair<CEvaluationNode*, CEvaluationNode*> > matchPowerBases(const std::vector<const CEvaluationNode*>& multiplications, const std::vector<const CEvaluationNode*>& divisions);
  static std::vector<product_match>                                  matchPowerBases(const std::vector<const CEvaluationNode*>& multiplications, const std::vector<const CEvaluationNode*>& divisions);

  /**
   * The methods get a vector of addition elements and a vector of subtractions
   * elements and tries to find equal elements in those two vectors.
   */
  static std::vector<std::pair<CEvaluationNode*, CEvaluationNode*> > matchSummands(const std::vector<CEvaluationNode*>& additions, const std::vector<CEvaluationNode*>& subtractions);
  static std::vector<summ_match>                                     matchSummands(const std::vector<const CEvaluationNode*>& additions, const std::vector<const CEvaluationNode*>& subtractions);

  /**
   * This methods records the order of nodes in a CEvaluationNode based tree.
   */
  static void order(const CEvaluationNode* pRoot, std::list<const CEvaluationNode*>& orderList);

  /**
   * Multiplies the two given nodes and returns the result.
   */
  static CEvaluationNode* multiply(const CEvaluationNode* pNode1, const CEvaluationNode* pNode2);

  /**
   * This method does all the canceling on a given node and its children.
   */
  // obsolete recursive version
  //static CEvaluationNode* cancel(const CEvaluationNode* pOrig);

  /**
   * New non-recursive cancel method.
   * This method does all the canceling on a given node and its children.
   * If no canceling was done, NULL is returned.
   */
  static CEvaluationNode* newCancel(const CEvaluationNode* pOrig);

  /**
   * This method elminates subexpressions from an expression
   */
  static CEvaluationNode* eliminate(const CEvaluationNode* pOrig);

  static const double ZERO;
  static const unsigned int RECURSION_LIMIT;
  /**
   * This method eliminates directly nested fractions. ((a/b)/(c/d)) -> (a*d)/(b*c)
   */
  static CEvaluationNode* eliminateDirectlyNestedFractions(const CEvaluationNode* pOrig);

  /**
   * This method gets rid of fractions within a power construct.
   * (a/b)^3 -> a^3 / b^3
   */
  static CEvaluationNode* eliminatePowersOfFractions(const CEvaluationNode* pOrig);

  /**
   * This methods converts a product of fractions into a fraction of products.
   */
  static CEvaluationNode* product2fraction(const CEvaluationNode* pOrig);

  /**
   * This method takes two vectors. One with a list of nodes that are added
   * and one with nodes that are subtracted.
   * It tries to find common factors and divisors in those nodes and returns
   * two result nodes. The first is the multiplication of all common factors and
   * divisors, the other is the sum of the remaining additions and subtractions after
   * removing the common factors and divisors.
   * e.g. (A*B*D+A*C*D) -> returns (A*D) and (B+C)
   */
  static std::pair<CEvaluationNode*, CEvaluationNode*> factorize(const std::vector<CEvaluationNode*>& additions, const std::vector<CEvaluationNode*>& subtractions);

  static void printPointers(const CEvaluationNode* pNode, const char* indent = "");
};

class CEvaluationNodeDepthFirstIterator
{
protected:
  CEvaluationNode* mpNode;

public:

  CEvaluationNodeDepthFirstIterator(CEvaluationNode* pRoot);

  CEvaluationNodeDepthFirstIterator& operator++();

  bool isValid() const;

  CEvaluationNode*& operator*();

  CEvaluationNode*& operator->();

  CEvaluationNodeDepthFirstIterator& operator=(CEvaluationNode* pNode);
};

#endif // COPASI_CNormalTranslation_H__
