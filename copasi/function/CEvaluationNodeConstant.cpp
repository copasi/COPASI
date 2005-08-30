/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeConstant.cpp,v $
   $Revision: 1.17 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/08/30 15:40:04 $
   End CVS Header */

#include <string>

#include "copasi.h"
#include "mathematics.h"

#include "CEvaluationNode.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeConstant::CEvaluationNodeConstant():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{mPrecedence = PRECEDENCE_NUMBER;}

#ifdef WIN32 
// warning C4056: overflow in floating-point constant arithmetic
// warning C4756: overflow in constant arithmetic
# pragma warning (disable: 4056 4756)
#endif

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

    case _INFINITY:
      mValue = 2.0 * DBL_MAX;
      break;

    case _NaN:
      mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      break;

    default:
      mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      break;
    }

  mPrecedence = PRECEDENCE_NUMBER;
}

#ifdef WIN32
# pragma warning (default: 4056 4756)
#endif

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

#ifdef WIN32 
// warning C4056: overflow in floating-point constant arithmetic
// warning C4756: overflow in constant arithmetic
# pragma warning (disable: 4056 4756)
#endif

ASTNode* CEvaluationNodeConstant::toAST() const
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
      case _INFINITY:
        node->setType(AST_REAL);
        node->setValue(2*DBL_MAX);
        break;
      case _NaN:
        node->setType(AST_REAL);
        node->setValue(std::numeric_limits<C_FLOAT64>::quiet_NaN());
      case INVALID:
        break;
      }
    return node;
  }

#ifdef WIN32
# pragma warning (default: 4056 4756)
#endif
