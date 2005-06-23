/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeChoice.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/23 16:16:24 $
   End CVS Header */

#include "copasi.h"

#include "mathematics.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeChoice::CEvaluationNodeChoice():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeChoice::CEvaluationNodeChoice(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::FUNCTION | subType), data),
    mpIf(NULL),
    mpTrue(NULL),
    mpFalse(NULL)
{
  switch (subType)
    {
    case IF:
      break;

    default:
      fatalError();
      break;
    }

  mPrecedence = PRECEDENCE_FUNCTION;
}

CEvaluationNodeChoice::CEvaluationNodeChoice(const CEvaluationNodeChoice & src):
    CEvaluationNode(src),
    mpIf(src.mpIf),
    mpTrue(src.mpTrue),
    mpFalse(src.mpFalse)
{}

CEvaluationNodeChoice::~CEvaluationNodeChoice() {}

const C_FLOAT64 & CEvaluationNodeChoice::value() const
  {
    if (mpIf->value() != 0.0) return mpTrue->value();
    else return mpFalse->value();
  }

bool CEvaluationNodeChoice::compile(const CEvaluationTree * /* pTree */)
{
  mpIf = static_cast<CEvaluationNode *>(getChild());
  if (mpIf == NULL) return false;

  mpTrue = static_cast<CEvaluationNode *>(mpIf->getSibling());
  if (mpTrue == NULL) return false;

  mpFalse = static_cast<CEvaluationNode *>(mpTrue->getSibling());
  if (mpFalse == NULL) return false;

  return (mpFalse->getSibling() == NULL); // We must have exactly three children
}

CEvaluationNode* CEvaluationNodeChoice::createNodeFromASTTree(const ASTNode& node)
{
  SubType subType;
  std::string data = "";

  CEvaluationNodeChoice* convertedNode = new CEvaluationNodeChoice(subType, data);
  return convertedNode;
}

ASTNode* CEvaluationNodeChoice::toASTNode()
{
  ASTNode* node = new ASTNode();
  return node;
}
