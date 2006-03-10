/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeVariable.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2006/03/10 09:58:42 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeVariable::CEvaluationNodeVariable():
    CEvaluationNode(CEvaluationNode::INVALID, ""),
    mpTree(NULL),
    mIndex(C_INVALID_INDEX)
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeVariable::CEvaluationNodeVariable(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::VARIABLE | subType), data),
    mpTree(NULL),
    mIndex(C_INVALID_INDEX)
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeVariable::CEvaluationNodeVariable(const CEvaluationNodeVariable & src):
    CEvaluationNode(src),
    mpTree(src.mpTree),
    mIndex(src.mIndex)
{}

CEvaluationNodeVariable::~CEvaluationNodeVariable() {}

bool CEvaluationNodeVariable::compile(const CEvaluationTree * pTree)
{
  mpTree = pTree;
  mIndex = pTree->getVariableIndex(mData);

  if (mIndex == C_INVALID_INDEX) return false;

  return (getChild() == NULL); // We must not have any children.
}

const C_FLOAT64 & CEvaluationNodeVariable::value() const
{return *const_cast<C_FLOAT64 *>(&mValue) = mpTree->getVariableValue(mIndex);}

ASTNode* CEvaluationNodeVariable::toAST() const
  {
    ASTNode* node = new ASTNode();
    node->setType(AST_NAME);
    node->setName(this->getData().c_str());
    return node;
  }

#include "utilities/copasimathml.h"

void CEvaluationNodeVariable::writeMathML(std::ostream & out,
    const std::vector<std::vector<std::string> > & env,
    bool expand,
    unsigned C_INT32 l) const
  {
    if ((mIndex < env.size()) && (mIndex >= 0))
      out << SPC(l) << env[mIndex][0] << std::endl;
  }
