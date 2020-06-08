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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CDerive
#define COPASI_CDerive

#include "copasi/copasi.h"
#include <vector>

class CEvaluationNode;
class CDataObject;
class CEvaluationTree;
class CModel;

class CDerive
{
public:

  CDerive();
  CDerive(std::vector<const CEvaluationNode*>&  env,
          const CEvaluationTree* pTree,
          bool simplify);

  //private:

  /// tests whether the node is numerically 1
  static bool isOne(const CEvaluationNode* node);

  /// tests whether the node is numerically 0
  static bool isZero(const CEvaluationNode* node);

  /// delete a branch starting from the given node
  static void deleteBranch(CEvaluationNode* node);

  /**
   * These methods create a node for a basic mathematical operation.
   * In addition they check for basic simplifications
   */
  CEvaluationNode* multiply(CEvaluationNode* n1, CEvaluationNode* n2);
  CEvaluationNode* divide(CEvaluationNode* n1, CEvaluationNode* n2);
  CEvaluationNode* add(CEvaluationNode* n1, CEvaluationNode* n2);
  CEvaluationNode* subtract(CEvaluationNode* n1, CEvaluationNode* n2);
  CEvaluationNode* power(CEvaluationNode* n1, CEvaluationNode* n2);

  static CEvaluationNode * copyBranch_var2obj(const CEvaluationNode* node, std::vector<const CEvaluationNode*> & env);

  /**
   * create a derivative of a mathematical expression with root at *node
   * with respect to the variable *pObject.
   * in env we pass the vector of trees that will be substituted for variable nodes
   * The treatment of object nodes in env[] is specific:
   *  - It is assumed that the value of all the objects is updated before the derivative will be evaluated
   *    (the evaluation of objects is not expanded)
   *  - However, the derivation of objects is expanded, for entities with assignments, concentrations,
   *    dependent species, reactions.
   *
   * @param node
   * @param pObject the variable to derive
   * @param env vector of trees to be substituted for variable nodes
   * @param pTree, the tree to differentiate
   * @param simplify if true the expression will be simplified
   */
  CEvaluationNode* deriveBranch(const CEvaluationNode* node, const CDataObject * pObject);

  void compileTree(CEvaluationNode* node);

private:

  std::vector<const CEvaluationNode*> mEnv;
  const CEvaluationTree* mpTree;
  bool mSimplify;

};

#endif
