/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeVariable.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/31 19:12:36 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"

CEvaluationNodeVariable::CEvaluationNodeVariable():
    CEvaluationNode(CEvaluationNode::INVALID, ""),
    mpValue(NULL)
{}

CEvaluationNodeVariable::CEvaluationNodeVariable(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::VARIABLE | subType), data),
    mpValue(NULL)
{}

CEvaluationNodeVariable::CEvaluationNodeVariable(const CEvaluationNodeVariable & src):
    CEvaluationNode(src),
    mpValue(src.mpValue)
{}

CEvaluationNodeVariable::~CEvaluationNodeVariable() {}

bool CEvaluationNodeVariable::compile(const CEvaluationTree * pTree)
{
  mpValue = pTree->getVariableValue(mData);

  if (mpValue == NULL) return false;

  return (getChild() == NULL); // We must not have any children.
}
