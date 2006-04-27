/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test2/CNormalTranslation.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:32:06 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CNormalTranslation.h"
#include "CNormalFraction.h"

CEvaluationNode * CNormalTranslation::simplifyTree(const CEvaluationNode *node)
{
  const CEvaluationNode * child1 = dynamic_cast<const CEvaluationNode*>(node->getChild());
  CEvaluationNode * newchild1 = NULL;
  CEvaluationNode * newchild2 = NULL;
  if (child1 != NULL)
    {
      newchild1 = simplifyTree(child1);

      const CEvaluationNode * child2 = dynamic_cast<const CEvaluationNode*>(child1->getSibling());
      if (child2 != NULL)
        newchild2 = simplifyTree(child2);
    }

  CEvaluationNode* newnode = node->simplifyNode(newchild1, newchild2);

  return newnode;
}

CEvaluationNode * CNormalTranslation::simplifyTreeReptdly(const CEvaluationNode* root0)
{
  CEvaluationNode * root1 = simplifyTree(root0);

  if (root1->getInfix() != root0->getInfix())
    {
      CEvaluationNode * root2 = simplifyTreeReptdly(root1);
      delete root1;
      return root2;
    }
  else
    return root1;
}

CNormalFraction* CNormalTranslation::normAndSimplify(const CEvaluationNode* root0)
{
  CEvaluationNode * root1 = simplifyTreeReptdly(root0);

  CNormalFraction* fraction = CNormalFraction::createFraction(root1);
  fraction->simplify();

  delete root1;

  return fraction;
}

CNormalFraction* CNormalTranslation::normAndSimplifyReptdly(const CEvaluationTree* tree0)
{
  const CEvaluationNode * root0 = tree0->getRoot();

  CNormalFraction * fraction0 = normAndSimplify(root0);

  std::stringstream tmp;
  tmp << *fraction0;

  CEvaluationTree * tree1 = new CEvaluationTree("second tree", NULL, CEvaluationTree::Function);

  tree1->setInfix(tmp.str());

  if (tree1->getInfix() != tree0->getInfix())
    {
      CNormalFraction * fraction1 = normAndSimplifyReptdly(tree1);
      delete tree1;
      delete fraction0;
      return fraction1;
    }
  else
    {
      delete tree1;
      return fraction0;
    }
}
