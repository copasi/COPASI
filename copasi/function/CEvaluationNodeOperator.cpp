/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeOperator.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/31 17:48:57 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"

CEvaluationNodeOperator::CEvaluationNodeOperator():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{}

CEvaluationNodeOperator::CEvaluationNodeOperator(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::OPERATOR | subType), data),
    mpOperation(NULL),
    mpLeft(NULL),
    mpRight(NULL)
{
  switch (subType)
    {
    case POWER:
      mpOperation = operationPower;
      break;

    case MULTIPLY:
      mpOperation = operationMultiply;
      break;

    case DIVIDE:
      mpOperation = operationDivide;
      break;

    case MODULUS:
      mpOperation = operationModulus;
      break;

    case PLUS:
      mpOperation = operationPlus;
      break;

    case MINUS:
      mpOperation = operationMinus;
      break;

    default:
      mpOperation = NULL;
      fatalError();
      break;
    }
}

CEvaluationNodeOperator::CEvaluationNodeOperator(const CEvaluationNodeOperator & src):
    CEvaluationNode(src),
    mpOperation(src.mpOperation)
{}

CEvaluationNodeOperator::~CEvaluationNodeOperator() {}

bool CEvaluationNodeOperator::compile(const CEvaluationTree * /* pTree */)
{
  mpLeft = static_cast<CEvaluationNode *>(getChild());
  if (mpLeft == NULL) return false;

  mpRight = static_cast<CEvaluationNode *>(mpLeft->getSibling());
  if (mpRight == NULL) return false;

  return (mpRight->getSibling() == NULL); // We must have only two children
}
