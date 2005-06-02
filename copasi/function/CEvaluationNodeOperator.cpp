/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeOperator.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/02 12:37:15 $
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
      mPrecedence = PRECEDENCE_OPERATOR_POWER;
      break;

    case MULTIPLY:
      mpOperation = operationMultiply;
      mPrecedence = PRECEDENCE_OPERATOR_MULTIPLY;
      break;

    case DIVIDE:
      mpOperation = operationDivide;
      mPrecedence = PRECEDENCE_OPERATOR_DIVIDE;
      break;

    case MODULUS:
      mpOperation = operationModulus;
      mPrecedence = PRECEDENCE_OPERATOR_MODULUS;
      break;

    case PLUS:
      mpOperation = operationPlus;
      mPrecedence = PRECEDENCE_OPERATOR_PLUS;
      break;

    case MINUS:
      mpOperation = operationMinus;
      mPrecedence = PRECEDENCE_OPERATOR_MINUS;
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
