// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifdef WIN32
# define _USE_MATH_DEFINES 1
#endif

#include <cmath>
#include <string>

#include "copasi.h"

#include "CEvaluationNode.h"
#include "utilities/CValidatedUnit.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeConstant::CEvaluationNodeConstant():
  CEvaluationNode(T_CONSTANT, S_INVALID,  "")
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeConstant::CEvaluationNodeConstant(const SubType & subType,
    const Data & data):
  CEvaluationNode(T_CONSTANT, subType, data)
{
  switch ((SubType) subType)
    {
      case S_PI:
        mValue = M_PI;
        break;

      case S_EXPONENTIALE:
        mValue = M_E;
        break;

      case S_TRUE:
        mValue = 1.0;
        break;

      case S_FALSE:
        mValue = 0.0;
        break;

      case S_INFINITY:
        mValue = std::numeric_limits<C_FLOAT64>::infinity();
        break;

      case S_NAN:
        mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
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

// virtual
std::string CEvaluationNodeConstant::getCCodeString(const std::vector< std::string > & /* children */) const
{
  std::string data = "";

  SubType subType = (SubType)this->subType();

  switch (subType)
    {
      case S_PI:
        data = "PI";
        break;

      case S_EXPONENTIALE:
        data = "EXPONENTIALE";
        break;

      case S_TRUE:
        data = "TRUE";
        break;

      case S_FALSE:
        data = "FALSE";
        break;

      case S_INFINITY:
        data = "INFINITY";
        break;

      case S_NAN:
        data = "NaN";
        break;

      default:
        data = "@";
        break;
    }

  return data;
}

// virtual
std::string CEvaluationNodeConstant::getBerkeleyMadonnaString(const std::vector< std::string > & /* children */) const
{
  std::ostringstream DisplayString;
  std::string data = "";

  SubType subType = (SubType)this->subType();

  switch (subType)
    {
      case S_PI:
        data = "PI";
        break;

      case S_EXPONENTIALE:
      case S_TRUE:
      case S_FALSE:
      case S_INFINITY:
      case S_NAN:
        DisplayString << mValue;
        data = DisplayString.str();
        break;

      default:
        data = "@";
        break;
    }

  return data;
}

// virtual
std::string CEvaluationNodeConstant::getXPPString(const std::vector< std::string > & /* children */) const
{
  std::ostringstream DisplayString;
  std::string data = "";

  SubType subType = (SubType) this->subType();

  switch (subType)
    {
      case S_PI:
        data = "pi";
        break;

      case S_EXPONENTIALE:
      case S_TRUE:
      case S_FALSE:
      case S_INFINITY:
      case S_NAN:
        DisplayString << mValue;
        data = DisplayString.str();
        break;

      default:
        data = "@"; //TODO
        break;
    }

  return data;
}

// static
CEvaluationNode * CEvaluationNodeConstant::fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children)
{
  assert(pASTNode->getNumChildren() == children.size());
  assert(children.size() == 0);

  SubType subType;
  std::string data = "";

  switch (pASTNode->getType())
    {
      case AST_CONSTANT_E:
        subType = S_EXPONENTIALE;
        data = "EXPONENTIALE";
        break;

      case AST_CONSTANT_PI:
        subType = S_PI;
        data = "PI";
        break;

      case AST_CONSTANT_TRUE:
        subType = S_TRUE;
        data = "TRUE";
        break;

      case AST_CONSTANT_FALSE:
        subType = S_FALSE;
        data = "FALSE";
        break;

      default:
        subType = S_INVALID;
        break;
    }

  return new CEvaluationNodeConstant(subType, data);
}

// virtual
bool CEvaluationNodeConstant::isBoolean() const
{
  switch (mSubType)
    {
      case S_TRUE:
      case S_FALSE:
        return true;

      default:
        return false;
    }
}

ASTNode* CEvaluationNodeConstant::toAST(const CCopasiDataModel* /*pDataModel*/) const
{
  SubType subType = (SubType)this->subType();
  ASTNode* node = new ASTNode();

  switch (subType)
    {
      case S_PI:
        node->setType(AST_CONSTANT_PI);
        break;

      case S_EXPONENTIALE:
        node->setType(AST_CONSTANT_E);
        break;

      case S_TRUE:
        node->setType(AST_CONSTANT_TRUE);
        break;

      case S_FALSE:
        node->setType(AST_CONSTANT_FALSE);
        break;

      case S_INFINITY:
        node->setType(AST_REAL);
        node->setValue(std::numeric_limits<C_FLOAT64>::infinity());
        break;

      case S_NAN:
      case S_INVALID:
        node->setType(AST_REAL);
        node->setValue(std::numeric_limits<C_FLOAT64>::quiet_NaN());
        break;
    }

  return node;
}

#include "utilities/copasimathml.h"

// virtual
std::string CEvaluationNodeConstant::getMMLString(const std::vector< std::string > & /* children */,
    bool /* expand */,
    const std::vector< std::vector< std::string > > & /* variables */) const
{
  std::ostringstream out;

  std::string data = "";

  switch ((SubType)this->subType())
    {
      case S_PI:
        data = "&pi;";
        break;

      case S_EXPONENTIALE:
        data = "e";
        break;

      case S_TRUE:
        data = "true";
        break;

      case S_FALSE:
        data = "false";
        break;

      case S_INFINITY:
        data = "&infin;";
        break;

      case S_NAN:
        data = "NaN";
        break;

      default:
        data = "@";
        break;
    }

  out << "<mi>" << data << "</mi>" << std::endl;

  return out.str();
}
