/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeLogical.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/06/27 15:08:12 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeLogical::CEvaluationNodeLogical():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{}

CEvaluationNodeLogical::CEvaluationNodeLogical(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::OPERATOR | subType), data),
    mpLeft(NULL),
    mpRight(NULL)
{}

CEvaluationNodeLogical::CEvaluationNodeLogical(const CEvaluationNodeLogical & src):
    CEvaluationNode(src)
{}

CEvaluationNodeLogical::~CEvaluationNodeLogical() {}

bool CEvaluationNodeLogical::compile(const CEvaluationTree * /* pTree */)
{
  mpLeft = static_cast<CEvaluationNode *>(getChild());
  if (mpLeft == NULL) return false;

  mpRight = static_cast<CEvaluationNode *>(mpLeft->getSibling());
  if (mpRight == NULL) return false;

  return (mpRight->getSibling() == NULL); // We must have exactly two children
}

CEvaluationNode* CEvaluationNodeLogical::createNodeFromASTTree(const ASTNode& node)
{
  SubType subType;
  std::string data = "";
  switch (node.getType())
    {
    case AST_LOGICAL_AND:
      subType = AND;
      data = "and";
      break;
    case AST_LOGICAL_OR:
      subType = OR;
      data = "or";
      break;
    case AST_LOGICAL_XOR:
      subType = XOR;
      data = "xor";
      break;
    case AST_RELATIONAL_EQ:
      subType = EQ;
      data = "eq";
      break;
    case AST_RELATIONAL_GEQ:
      subType = GE;
      data = "ge";
      break;
    case AST_RELATIONAL_GT:
      subType = GT;
      data = "gt";
      break;
    case AST_RELATIONAL_LEQ:
      subType = LE;
      data = "le";
      break;
    case AST_RELATIONAL_LT:
      subType = LT;
      data = "lt";
      break;
    case AST_RELATIONAL_NEQ:
      subType = NE;
      data = "ne";
      break;
    default:
      subType = INVALID;
      break;
    }
  CEvaluationNode* convertedNode = new CEvaluationNodeLogical(subType, data);
  // convert the two children
  if (subType != INVALID)
    {
      convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getLeftChild()));
      convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getRightChild()));
    }

  return convertedNode;
}

ASTNode* CEvaluationNodeLogical::toASTNode()
{
  SubType subType = (SubType)CEvaluationNode::subType(this->getType());
  ASTNode* node = new ASTNode();
  return node;
}
