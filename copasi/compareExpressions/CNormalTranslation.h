// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalTranslation.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/08/07 16:49:49 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CNormalTranslation_H__
#define COPASI_CNormalTranslation_H__

class CNormalFraction;

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
  };

#endif // COPASI_CNormalTranslation_H__
