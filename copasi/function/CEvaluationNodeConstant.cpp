/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeConstant.cpp,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/07/01 09:48:34 $
   End CVS Header */

#include <string>

#include "copasi.h"
#include "mathematics.h"

#include "CEvaluationNode.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeConstant::CEvaluationNodeConstant():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeConstant::CEvaluationNodeConstant(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::CONSTANT | subType), data)
{
  switch ((SubType) subType)
    {
    case PI:
      mValue = M_PI;
      break;

    case EXPONENTIALE:
      mValue = M_E;
      break;

    case TRUE:
      mValue = 1.0;
      break;

    case FALSE:
      mValue = 0.0;
      break;

    default:
      mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      break;
    }

  mPrecedence = PRECEDENCE_NUMBER;
}

CEvaluationNodeConstant::CEvaluationNodeConstant(const CEvaluationNodeConstant & src):
    CEvaluationNode(src)
{}

CEvaluationNodeConstant::~CEvaluationNodeConstant() {}

CEvaluationNode* CEvaluationNodeConstant::createNodeFromASTTree(const ASTNode& node)
{
  ASTNodeType_t type = node.getType();
  SubType subType;
  std::string data = "";
  switch (type)
    {
    case AST_CONSTANT_E:
      subType = EXPONENTIALE;
      data = "EXPONENTIALE";
      break;
    case AST_CONSTANT_PI:
      subType = PI;
      data = "PI";
      break;
    case AST_CONSTANT_TRUE:
      subType = TRUE;
      data = "TRUE";
      break;
    case AST_CONSTANT_FALSE:
      subType = FALSE;
      data = "FALSE";
      break;
    default:
      subType = INVALID;
      break;
    }
  return new CEvaluationNodeConstant(subType, data);
}

ASTNode* CEvaluationNodeConstant::toASTNode()
{
  SubType subType = (SubType)CEvaluationNode::subType(this->getType());
  ASTNode* node = new ASTNode();
  switch (subType)
    {
    case PI:
      node->setType(AST_CONSTANT_PI);
      break;
    case EXPONENTIALE:
      node->setType(AST_CONSTANT_E);
      break;
    case TRUE:
      node->setType(AST_CONSTANT_TRUE);
      break;
    case FALSE:
      node->setType(AST_CONSTANT_FALSE);
      break;
    case INVALID:
      break;
    }
  return node;
}
