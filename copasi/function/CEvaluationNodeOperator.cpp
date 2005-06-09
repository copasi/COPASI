/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeOperator.cpp,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/06/09 13:46:28 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"

#include "sbml/math/ASTNode.h"

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

CEvaluationNode* CEvaluationNodeOperator::createNodeFromASTTree(const ASTNode* node)
{
  ASTNodeType_t type = node->getType();
  SubType subType;
  std::string data = "";
  switch (type)
    {
    case AST_PLUS:
      subType = PLUS;
      data = "+";
      break;
    case AST_MINUS:
      subType = MINUS;
      data = "-";
      break;
    case AST_TIMES:
      subType = MULTIPLY;
      data = "*";
      break;
    case AST_DIVIDE:
      subType = DIVIDE;
      data = "/";
      break;
    case AST_POWER:
    case AST_FUNCTION_POWER:
      subType = POWER;
      data = "^";
      break;
    default:
      subType = INVALID;
      break;
    }
  return new CEvaluationNodeOperator(subType, data);
}

ASTNode* CEvaluationNodeOperator::toASTNode()
{
  SubType subType = (SubType)CEvaluationNode::subType(this->getType());
  ASTNode* node = new ASTNode();
  switch (subType)
    {
    case POWER:
      node->setType(AST_POWER);
      break;
    case MULTIPLY:
      node->setType(AST_TIMES);
      break;
    case DIVIDE:
      node->setType(AST_DIVIDE);
      break;
    case MODULUS:
      // replace this with a more complex subtree
      CEvaluationNodeOperator::createModuloTree(this, node);
      break;
    case PLUS:
      node->setType(AST_PLUS);
      break;
    case MINUS:
      node->setType(AST_MINUS);
      break;
    case INVALID:
      break;
    }
  // for all but INVALID and MODULUS two children have to be converted
  if (subType != INVALID && subType != MODULUS)
    {
      CEvaluationNode* child1 = dynamic_cast<CEvaluationNode*>(this->getChild());
      CEvaluationNode* child2 = dynamic_cast<CEvaluationNode*>(child1->getSibling());
      node->addChild(child1->toASTNode());
      node->addChild(child2->toASTNode());
    }
  return node;
}

bool CEvaluationNodeOperator::createModuloTree(CEvaluationNodeOperator* pNode, ASTNode* pASTNode)
{
  // x%y -> x-floor(x/y)*x
  bool result = false;
  if ((SubType)CEvaluationNode::subType(pNode->getType()) == MODULUS)
    {
      // the node has two children x and y
      CEvaluationNode* x = dynamic_cast<CEvaluationNode*>(pNode->getChild());
      if (x != NULL)
        {
          CEvaluationNode* y = dynamic_cast<CEvaluationNode*>(x->getSibling());
          if (y != NULL)
            {
              pASTNode->setType(AST_MINUS);
              ASTNode* tmpASTNode = new ASTNode(AST_DIVIDE);
              tmpASTNode->addChild(x->toASTNode());
              tmpASTNode->addChild(y->toASTNode());
              ASTNode* tmpASTNode2 = new ASTNode(AST_FUNCTION_FLOOR);
              tmpASTNode2->addChild(tmpASTNode);
              tmpASTNode = new ASTNode(AST_TIMES);
              tmpASTNode->addChild(x->toASTNode());
              tmpASTNode->addChild(tmpASTNode2);
              pASTNode->addChild(x->toASTNode());
              pASTNode->addChild(tmpASTNode);
              result = true;
            }
        }
    }
  return result;
}
