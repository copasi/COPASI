// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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
# ifndef _USE_MATH_DEFINES
# define _USE_MATH_DEFINES 1
# endif // _USE_MATH_DEFINES
#endif

#include <cmath>
#include <string>

#include "copasi/copasi.h"

#include "CEvaluationNode.h"
#include "copasi/utilities/CValidatedUnit.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeConstant::CEvaluationNodeConstant():
  CEvaluationNode(MainType::CONSTANT, SubType::INVALID,  "")
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeConstant::CEvaluationNodeConstant(const SubType & subType,
    const Data & data):
  CEvaluationNode(MainType::CONSTANT, subType, data)
{
  mValueType = (mSubType != SubType::True && mSubType != SubType::False) ? ValueType::Number : ValueType::Boolean;

  switch ((SubType) subType)
    {
      case SubType::PI:
        mValue = M_PI;
        break;

      case SubType::EXPONENTIALE:
        mValue = M_E;
        break;

      case SubType::True:
        mValue = 1.0;
        break;

      case SubType::False:
        mValue = 0.0;
        break;

      case SubType::Infinity:
        mValue = std::numeric_limits<C_FLOAT64>::infinity();
        break;

      case SubType::NaN:
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
      case SubType::PI:
        data = "PI";
        break;

      case SubType::EXPONENTIALE:
        data = "EXPONENTIALE";
        break;

      case SubType::True:
        data = "TRUE";
        break;

      case SubType::False:
        data = "FALSE";
        break;

      case SubType::Infinity:
        data = "INFINITY";
        break;

      case SubType::NaN:
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
      case SubType::PI:
        data = "PI";
        break;

      case SubType::EXPONENTIALE:
      case SubType::True:
      case SubType::False:
      case SubType::Infinity:
      case SubType::NaN:
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
      case SubType::PI:
        data = "pi";
        break;

      case SubType::EXPONENTIALE:
      case SubType::True:
      case SubType::False:
      case SubType::Infinity:
      case SubType::NaN:
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
        subType = SubType::EXPONENTIALE;
        data = "EXPONENTIALE";
        break;

      case AST_CONSTANT_PI:
        subType = SubType::PI;
        data = "PI";
        break;

      case AST_CONSTANT_TRUE:
        subType = SubType::True;
        data = "TRUE";
        break;

      case AST_CONSTANT_FALSE:
        subType = SubType::False;
        data = "FALSE";
        break;

      default:
        subType = SubType::INVALID;
        break;
    }

  return new CEvaluationNodeConstant(subType, data);
}

ASTNode* CEvaluationNodeConstant::toAST(const CDataModel* /*pDataModel*/) const
{
  SubType subType = (SubType)this->subType();
  ASTNode* node = new ASTNode();

  switch (subType)
    {
      case SubType::PI:
        node->setType(AST_CONSTANT_PI);
        break;

      case SubType::EXPONENTIALE:
        node->setType(AST_CONSTANT_E);
        break;

      case SubType::True:
        node->setType(AST_CONSTANT_TRUE);
        break;

      case SubType::False:
        node->setType(AST_CONSTANT_FALSE);
        break;

      case SubType::Infinity:
        node->setType(AST_REAL);
        node->setValue(std::numeric_limits<C_FLOAT64>::infinity());
        break;

      case SubType::NaN:
      case SubType::INVALID:
        node->setType(AST_REAL);
        node->setValue(std::numeric_limits<C_FLOAT64>::quiet_NaN());
        break;
    }

  return node;
}

#include "copasi/utilities/copasimathml.h"

// virtual
std::string CEvaluationNodeConstant::getMMLString(const std::vector< std::string > & /* children */,
    bool /* expand */,
    const std::vector< std::vector< std::string > > & /* variables */) const
{
  std::ostringstream out;

  std::string data = "";

  switch ((SubType)this->subType())
    {
      case SubType::PI:
        data = "&pi;";
        break;

      case SubType::EXPONENTIALE:
        data = "e";
        break;

      case SubType::True:
        data = "true";
        break;

      case SubType::False:
        data = "false";
        break;

      case SubType::Infinity:
        data = "&infin;";
        break;

      case SubType::NaN:
        data = "NaN";
        break;

      default:
        data = "@";
        break;
    }

  out << "<mi>" << data << "</mi>" << std::endl;

  return out.str();
}
