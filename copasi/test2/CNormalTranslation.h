// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/copasi.h"

#include "copasi/function/CEvaluationTree.h"
#include "copasi/function/CEvaluationNode.h"
//#include "copasi/function/CEvaluationNodeOperator.h"
//#include "copasi/function/CEvaluationNodeFunction.h"
//#include "copasi/function/CEvaluationNode.h"

//#include <vector>

//#include "copasi/utilities/CopasiTime.h"
//#include "copasi/randomGenerator/CRandom.h"
//#include "copasi/report/CKeyFactory.h"

#include "copasi/function/CFunction.h"

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
