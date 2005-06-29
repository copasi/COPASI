/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeOperator.cpp,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/29 21:54:01 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeOperator::CEvaluationNodeOperator():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{}

CEvaluationNodeOperator::CEvaluationNodeOperator(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::OPERATOR | subType), data),
    mpLeft(NULL),
    mpRight(NULL)
{
  switch (mType & 0x00FFFFFF)
    {
    case POWER:
      mPrecedence = PRECEDENCE_OPERATOR_POWER;
      break;

    case MULTIPLY:
      mPrecedence = PRECEDENCE_OPERATOR_MULTIPLY;
      break;

    case DIVIDE:
      mPrecedence = PRECEDENCE_OPERATOR_DIVIDE;
      break;

    case MODULUS:
      mPrecedence = PRECEDENCE_OPERATOR_MODULUS;
      break;

    case PLUS:
      mPrecedence = PRECEDENCE_OPERATOR_PLUS;
      break;

    case MINUS:
      mPrecedence = PRECEDENCE_OPERATOR_MINUS;
      break;

    default:
      break;
    }
}

CEvaluationNodeOperator::CEvaluationNodeOperator(const CEvaluationNodeOperator & src):
    CEvaluationNode(src)
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

std::string CEvaluationNodeOperator::getInfix() const
  {
    if (const_cast<CEvaluationNodeOperator *>(this)->compile(NULL))
      {
        Data Infix;

        if (*mpLeft < *(CEvaluationNode *)this)
          Infix = "(" + mpLeft->getData() + ")";
        else
          Infix = mpLeft->getData();

        Infix += mData;

        if (!(*(CEvaluationNode *)this < *mpRight))
          Infix += "(" + mpRight->getData() + ")";
        else
          Infix += mpRight->getData();

        return Infix;
      }
    else
      return "@";
  }

CEvaluationNode* CEvaluationNodeOperator::createNodeFromASTTree(const ASTNode& node)
{
  ASTNodeType_t type = node.getType();
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
  CEvaluationNode* convertedNode = new CEvaluationNodeOperator(subType, data);

  // handle "-" since it can be unary or binary
  if (type == AST_MINUS)
    {
      switch (node.getNumChildren())
        {
        case 1:
          delete convertedNode;
          convertedNode = new CEvaluationNodeFunction(CEvaluationNodeFunction::MINUS, data);
          convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getLeftChild()));
          break;
        case 2:
          convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getLeftChild()));
          convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getRightChild()));
          break;
        default:
          // error
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCMathML + 3);
          break;
        }
    }
  // handle binary operators (POWER,/)
  else if (type == AST_DIVIDE || type == AST_POWER || type == AST_FUNCTION_POWER)
    {
      switch (node.getNumChildren())
        {
        case 2:
          convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getLeftChild()));
          convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getRightChild()));
          break;
        default:
          // error
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCMathML + 4);
          break;
        }
    }
  // handle n-ary operators (+,*)
  else if (type == AST_PLUS || type == AST_TIMES)
    {
      unsigned int numChildren = node.getNumChildren();
      unsigned int i;
      CEvaluationNodeOperator* pTmpNode;
      switch (numChildren)
        {
        case 0:
          // replace the current node with the identity node
          delete convertedNode;
          if (type == AST_PLUS)
            {
              convertedNode = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.0");
            }
          else
            {
              convertedNode = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");
            }
          break;
        case 1:
          // replace the current node with its only child
          delete convertedNode;
          convertedNode = CEvaluationTree::convertASTNode(*node.getLeftChild());
          break;
        case 2:
          convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getLeftChild()));
          convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getRightChild()));
          break;
        default:
          convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getLeftChild()));
          pTmpNode = dynamic_cast<CEvaluationNodeOperator*>(convertedNode);
          for (i = 1; i < numChildren;++i)
            {
              pTmpNode->addChild(new CEvaluationNodeOperator((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pTmpNode->getType()), pTmpNode->getData()));
              pTmpNode = dynamic_cast<CEvaluationNodeOperator*>(pTmpNode->getChild()->getSibling());
              assert(pTmpNode);
              pTmpNode->addChild(CEvaluationTree::convertASTNode(*node.getChild(i)));
            }
          break;
        }
    }
  return convertedNode;
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
