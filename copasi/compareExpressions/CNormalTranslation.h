// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalTranslation.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/03/06 11:28:49 $
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
    static CEvaluationNode* createMultiplicationChain(const std::vector<CEvaluationNode*>& nodes);
    
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
    static void findSummands(const CEvaluationNode* pRoot,std::vector<const CEvaluationNode*>& summands);
  };

#endif // COPASI_CNormalTranslation_H__
