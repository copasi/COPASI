// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeConstant.cpp,v $
//   $Revision: 1.23 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/07/24 18:40:21 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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

std::string CEvaluationNodeConstant::getDisplay_C_String(const CEvaluationTree * /*pTree*/) const
  {
    std::string data = "";

    SubType subType = (SubType)CEvaluationNode::subType(this->getType());

    switch (subType)
      {
      case PI:
        data = "PI";
        break;
      case EXPONENTIALE:
        data = "EXPONENTIALE";
        break;
      case TRUE:
        data = "TRUE";
        break;
      case FALSE:
        data = "FALSE";
        break;
      case _INFINITY:
        data = "INFINITY";
        break;
      case _NaN:
        data = "@";
        break;
      default:
        data = "@";
        break;
      }
    return data;
  }

std::string CEvaluationNodeConstant::getDisplay_MMD_String(const CEvaluationTree * /*pTree*/) const
  {
    std::ostringstream DisplayString;
    std::string data = "";

    SubType subType = (SubType)CEvaluationNode::subType(this->getType());

    switch (subType)
      {
      case PI:
        data = "PI";
        break;
      case EXPONENTIALE:
      case TRUE:
      case FALSE:
      case _INFINITY:
      case _NaN:
        DisplayString << mValue;
        data = DisplayString.str();
        break;
      default:
        data = "@";
        break;
      }
    return data;
  }

std::string CEvaluationNodeConstant::getDisplay_XPP_String(const CEvaluationTree * /*pTree*/) const
  {
    std::ostringstream DisplayString;
    std::string data = "";

    SubType subType = (SubType)CEvaluationNode::subType(this->getType());

    switch (subType)
      {
      case PI:
        data = "pi";
        break;
      case EXPONENTIALE:
      case TRUE:
      case FALSE:
      case _INFINITY:
      case _NaN:
        DisplayString << mValue;
        data = DisplayString.str();
        break;
      default:
        data = "@"; //TODO
        break;
      }

    return data;
  }

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

#include "utilities/copasimathml.h"

void CEvaluationNodeConstant::writeMathML(std::ostream & out,
    const std::vector<std::vector<std::string> > & /* env */,
    bool /* expand */,
    unsigned C_INT32 /* l */) const
  {
    SubType subType = (SubType)CEvaluationNode::subType(this->getType());

    std::string data = "";

    switch (subType)
      {
      case PI:
        data = "&pi;";
        break;
      case EXPONENTIALE:
        data = "e";
        break;
      case TRUE:
        data = "true";
        break;
      case FALSE:
        data = "false";
        break;
      case _INFINITY:
        data = "&infin;";
        break;
      case _NaN:
        data = "NaN";
        break;
      default:
        data = "@";
        break;
      }

    out << SPC(1) << "<mi>" << data << "</mi>" << std::endl;
  }

#ifdef WIN32
# pragma warning (default: 4056 4756)
#endif
