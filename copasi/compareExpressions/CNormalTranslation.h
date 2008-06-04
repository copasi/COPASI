// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalTranslation.h,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/06/04 18:51:16 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CNormalTranslation_H__
#define COPASI_CNormalTranslation_H__

class CNormalFraction;
class CEvaluationTree;

#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationNodeOperator.h"

/**
 * The class for simplification and translation of trees into CNormal
 */
class CNormalTranslation
  {
  public:
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
     * @return CNormalFraction*
     */
    static CNormalFraction* normAndSimplifyReptdly(const CEvaluationTree* tree0);

    /**
     * Translate and simplify a tree by calling normAndSimplify repeatedly until it cannot be simplified further
     * @return CNormalFraction*
     */
    static CNormalFraction* normAndSimplifyReptdly(const CEvaluationNode* tree0);

    /**
     * Given a vector of nodes, this method creates a multiplication chain of
     * all the nodes. The chain contains the original nodes and not copies.
     */
    static CEvaluationNode* createOperatorChain(CEvaluationNodeOperator::SubType type, const char* data, const std::vector<CEvaluationNode*>& nodes);

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
     */
    static CEvaluationNode* expandProducts(const CEvaluationNode* pOrig);

    /**
     * This method splits a product into the individual elements
     */
    static void splitProduct(const CEvaluationNode* pRoot, std::vector<const CEvaluationNode*>& multiplications, std::vector<const CEvaluationNode*>& divisions, bool division);

    /**
     * This method splits a sum into the individual elements
     */
    static void splitSum(const CEvaluationNode* pRoot, std::vector<CEvaluationNode*>& additions, std::vector<CEvaluationNode*>& substractions, bool minus);

    /**
     * This method evaluates operators acting on two numbers
     */
    static CEvaluationNode* evaluateNumbers(const CEvaluationNode* pOrig);

  protected:
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
    static CEvaluationNode* elementaryElimination(const CEvaluationNode* pOrig);

    /**
     * This method makes elementary eliminations on function nodes
     */
    static CEvaluationNode* elementaryEliminationFunction(const CEvaluationNode* pFunctionNode, std::vector<CEvaluationNode*>& children);

    /**
     * This method makes the elementary elimination on a power node.
     */
    static CEvaluationNode* elementaryEliminationPower(const CEvaluationNode* pPowerNode, const std::vector<CEvaluationNode*>& children);

    /**
     * This method makes the elementary elimination on a modulus node.
     */
    static CEvaluationNode* elementaryEliminationModulus(const CEvaluationNode* pModulusNode, const std::vector<CEvaluationNode*>& children);

    /**
     * This method makes the elementary elimination on a multiply node.
     */
    static CEvaluationNode* elementaryEliminationMultiply(const CEvaluationNode* pMultiplyNode, const std::vector<CEvaluationNode*>& children);

    /**
     * This method makes the elementary elimination on a divide node.
     */
    static CEvaluationNode* elementaryEliminationDivide(const CEvaluationNode* pDivideNode, const std::vector<CEvaluationNode*>& children);

    /**
     * This method makes the elementary elimination on a plus node.
     */
    static CEvaluationNode* elementaryEliminationPlus(const CEvaluationNode* pPlusNode, const std::vector<CEvaluationNode*>& children);

    /**
     * This method makes the elementary elimination on a minus node.
     */
    static CEvaluationNode* elementaryEliminationMinus(const CEvaluationNode* pMinusNode, const std::vector<CEvaluationNode*>& children);

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
    static std::vector<std::pair<CEvaluationNode*, CEvaluationNode*> > matchPowerBases(const std::vector<const CEvaluationNode*>& multiplications, const std::vector<const CEvaluationNode*>& divisions);

    /**
     * The methods get a vector of addition elements and a vector of subtractions
     * elements and tries to find equal elements in those two vectors.
     */
    static std::vector<std::pair<CEvaluationNode*, CEvaluationNode*> > matchSummands(const std::vector<CEvaluationNode*>& additions, const std::vector<CEvaluationNode*>& subtractions);

    /**
     * Multiplies the two given nodes and returns the result.
     */
    static CEvaluationNode* multiply(const CEvaluationNode* pNode1, const CEvaluationNode* pNode2);

    /**
     * This method does all the canceling on a given node and its children.
     */
    static CEvaluationNode* cancel(const CEvaluationNode* pOrig);

    /**
     * This method elminates subexpressions from an expression
     */
    static CEvaluationNode* eliminate(const CEvaluationNode* pOrig);

    static const double ZERO;

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
  };

#endif // COPASI_CNormalTranslation_H__
