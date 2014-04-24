
// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CDerive
#define COPASI_CDerive

#include "copasi.h"
#include <vector>

class CEvaluationNode;
class CCopasiObject;
class CEvaluationTree;
class CModel;

class CDerive
  {
  public:

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
    static CEvaluationNode* multiply(CEvaluationNode* n1, CEvaluationNode* n2, bool simplify);
    static CEvaluationNode* divide(CEvaluationNode* n1, CEvaluationNode* n2, bool simplify);
    static CEvaluationNode* add(CEvaluationNode* n1, CEvaluationNode* n2, bool simplify);
    static CEvaluationNode* subtract(CEvaluationNode* n1, CEvaluationNode* n2, bool simplify);
    static CEvaluationNode* power(CEvaluationNode* n1, CEvaluationNode* n2, bool simplify);
  
    //static CEvaluationNode * copyBranch_var2obj(const CEvaluationNode* node, std::vector<const CEvaluationNode*> & env);

  
  /**
   * create a derivative of a mathematical expression with root at *node
   * with respect to the variable *pObject. 
   * in env we pass the vector of trees that will be substituted for variable nodes
   * The treatment of object nodes in env[] is specific:
   *  - It is assumed that the value of all the objects is updated before the derivative will be evaluated
   *    (the evaluation of objects is not expanded)
   *  - However, the derivation of objects is expanded, for entities with assignments, concentrations,
   *    dependent species, reactions. 
   */
  static CEvaluationNode* deriveBranch(const CEvaluationNode* node, const CCopasiObject * pObject,
                                       std::vector<const CEvaluationNode*>& env,
                                       //std::vector<const CCopasiObject*>& objenv,
                                       const CEvaluationTree* pTree,
                                       bool simplify);

    static void compileTree(CEvaluationNode* node, const CEvaluationTree * pTree);
  };



#endif
