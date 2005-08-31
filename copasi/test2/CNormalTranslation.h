/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test2/CNormalTranslation.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/08/31 14:26:54 $
   End CVS Header */

// Main
//
// (C) Stefan Hoops 2002
//

#ifndef COPASI_CNormalTranslation
#define COPASI_CNormalTranslation

#include <sstream>
#include <string>
#include <iostream>

#include "CNormalFraction.h"

#include "copasi.h"

#include "function/CEvaluationTree.h"
#include "function/CEvaluationNode.h" 
//#include "function/CEvaluationNodeOperator.h"
//#include "function/CEvaluationNodeFunction.h"
//#include "function/CEvaluationNode.h"

//#include <vector>

//#include "utilities/CopasiTime.h"
//#include "randomGenerator/CRandom.h"
//#include "report/CKeyFactory.h"

#include "function/CFunction.h"

/**
 * The class for simplification and translation of trees into CNormal
 */
class CNormalTranslation
  {
  public:
    /**
     * Simplify an evaluation tree given by the root node by creating a new simplified tree from the original one.
     * The tree itself is actually not created!
     * @return CEvaluationNode*, pointer to root node of the newly created tree.
     */
    static CEvaluationNode * simplifyTree(const CEvaluationNode *node);

    /**
     * Creating a simplified tree by calling simplifyTree repeatedly until it cannot be simplified further.
     * The tree itself is actually not created! 
     * @return CEvaluationNode*, pointer to root node of the newly created tree.
     */
    static CEvaluationNode * simplifyTreeReptdly(const CEvaluationNode* root0);

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
  };

#endif // COPASI_CNormalTranslation
