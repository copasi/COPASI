// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#include <iomanip>
#include <sstream>
#include <stdlib.h>
#include <cmath>

#include "copasi/copasi.h"
#include "CEvaluationNode.h"
#include "copasi/utilities/utility.h"
#include "copasi/utilities/CValidatedUnit.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeNumber::CEvaluationNodeNumber():
  CEvaluationNode(MainType::NUMBER, SubType::INVALID, "")
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeNumber::CEvaluationNodeNumber(const SubType & subType,
    const Data & data):
  CEvaluationNode(MainType::NUMBER, subType, data)
{
  mPrecedence = PRECEDENCE_NUMBER;
  mValueType = ValueType::Number;

  const char * end;
  const char * str = mData.c_str();

  switch (subType)
    {
      case SubType::DOUBLE:
      case SubType::INTEGER:
      case SubType::ENOTATION:
      {
        //mValue = strToDouble(str, NULL);
        std::istringstream in;
        in.imbue(std::locale::classic());
        in.str(str);
        in >> mValue;
      }
      break;

      case SubType::RATIONALE:
        str++; // Skip the '('
        mValue = strToDouble(str, &end);
        end++; // Skip the '/'
        mValue /= strToDouble(end, NULL);
        break;

      case SubType::INVALID:
        fatalError();
        break;
    }
}

CEvaluationNodeNumber::CEvaluationNodeNumber(const C_FLOAT64 & number):
  CEvaluationNode(MainType::NUMBER, SubType::DOUBLE, "")
{
  mPrecedence = PRECEDENCE_NUMBER;
  mValueType = ValueType::Number;

  mValue = number;

  std::ostringstream Data;

  Data.imbue(std::locale::classic());
  Data.precision(std::numeric_limits<double>::digits10 + 2);
  Data << mValue;

  mData = Data.str();
  mPrecedence = PRECEDENCE_NUMBER;
}

CEvaluationNodeNumber::CEvaluationNodeNumber(const CEvaluationNodeNumber & src):
  CEvaluationNode(src)
{}

CEvaluationNodeNumber::~CEvaluationNodeNumber() {}

// static
CEvaluationNode * CEvaluationNodeNumber::fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children)
{
  assert(pASTNode->getNumChildren() == children.size());

  std::stringstream ss;
  ss.imbue(std::locale::classic());
  ss.precision(std::numeric_limits<double>::digits10 + 2);

  SubType subType;
  std::string data = "";
  CEvaluationNode* pNode = NULL;

  switch (pASTNode->getType())
    {
      case AST_INTEGER:
        subType = SubType::INTEGER;

        if (pASTNode->getInteger() < 0)
          {
            pNode = new CEvaluationNodeFunction(SubType::MINUS, "-");

            ss << abs(pASTNode->getInteger());
            data = ss.str();
            pNode->addChild(new CEvaluationNodeNumber(subType, data));
          }
        else
          {
            ss << pASTNode->getInteger();
            data = ss.str();
            pNode = new CEvaluationNodeNumber(subType, data);
          }

        break;

      case AST_REAL:
        subType = SubType::DOUBLE;

        if (pASTNode->getReal() == (std::numeric_limits<C_FLOAT64>::infinity()))
          {
            pNode = new CEvaluationNodeConstant(SubType::Infinity, "INFINITY");
          }
        else if (pASTNode->getReal() == (-std::numeric_limits<C_FLOAT64>::infinity()))
          {
            pNode = new CEvaluationNodeFunction(SubType::MINUS, "-");
            pNode->addChild(new CEvaluationNodeConstant(SubType::Infinity, "INFINITY"));
          }
        else if (std::isnan(pASTNode->getReal()))
          {
            pNode = new CEvaluationNodeConstant(SubType::NaN, "NAN");
          }
        else if (pASTNode->getReal() < 0.0)
          {
            pNode = new CEvaluationNodeFunction(SubType::MINUS, "-");

            ss << fabs(pASTNode->getReal());
            data = ss.str();
            pNode->addChild(new CEvaluationNodeNumber(subType, data));
          }
        else
          {
            ss << pASTNode->getReal();
            data = ss.str();
            pNode = new CEvaluationNodeNumber(subType, data);
          }

        break;

      case AST_REAL_E:
        subType = SubType::ENOTATION;

        if (pASTNode->getReal() == (std::numeric_limits<C_FLOAT64>::infinity()))
          {
            pNode = new CEvaluationNodeConstant(SubType::Infinity, "INFINITY");
          }
        else if (pASTNode->getReal() == (-std::numeric_limits<C_FLOAT64>::infinity()))
          {
            pNode = new CEvaluationNodeFunction(SubType::MINUS, "-");
            pNode->addChild(new CEvaluationNodeConstant(SubType::Infinity, "INFINITY"));
          }
        else if (std::isnan(pASTNode->getReal()))
          {
            pNode = new CEvaluationNodeConstant(SubType::NaN, "NAN");
          }
        else if (pASTNode->getReal() < 0.0)
          {
            pNode = new CEvaluationNodeFunction(SubType::MINUS, "-");

            ss << fabs(pASTNode->getReal());
            data = ss.str();
            pNode->addChild(new CEvaluationNodeNumber(subType, data));
          }
        else
          {
            ss << pASTNode->getReal();
            data = ss.str();
            pNode = new CEvaluationNodeNumber(subType, data);
          }

        break;

      case AST_RATIONAL:
        subType = SubType::RATIONALE;

        if (pASTNode->getReal() < 0.0) // getReal returns the value of the node
          {
            pNode = new CEvaluationNodeFunction(SubType::MINUS, "-");

            ss << "(" << abs(pASTNode->getNumerator()) << "/" << abs(pASTNode->getDenominator()) << ")";
            data = ss.str();
            pNode->addChild(new CEvaluationNodeNumber(subType, data));
          }
        else
          {
            ss << "(" << pASTNode->getNumerator() << "/" << pASTNode->getDenominator() << ")";
            data = ss.str();
            pNode = new CEvaluationNodeNumber(subType, data);
          }

        break;

      default:
        subType = SubType::INVALID;
        break;
    }

  return pNode;
}

ASTNode* CEvaluationNodeNumber::toAST(const CDataModel* /* pDataModel */) const
{
  SubType subType = (SubType)this->subType();
  ASTNode* node = new ASTNode();
  double num1;
  double num2;
  const char * end;
  const char * str = mData.c_str();

  switch (subType)
    {
      case SubType::DOUBLE:
        node->setType(AST_REAL);
        node->setValue(*mpValue);
        break;

      case SubType::INTEGER:
        node->setType(AST_INTEGER);
        node->setValue((long)*mpValue);
        break;

      case SubType::ENOTATION:
        node->setType(AST_REAL_E);
        num2 = floor(log10(*mpValue));
        num1 = pow(10.0, log10(*mpValue) - num2);
        node->setValue(num1, (long)num2);
        break;

      case SubType::RATIONALE:
        node->setType(AST_RATIONAL);
        str++; // Skip the '('
        num1 = strToDouble(str, &end);
        end++; // Skip the '/'
        num2 = strToDouble(end, NULL);
        node->setValue((long)num1, (long)num2);
        break;

      case SubType::INVALID:
        break;
    }

  return node;
}

#include "copasi/utilities/copasimathml.h"

// virtual
std::string CEvaluationNodeNumber::getMMLString(const std::vector< std::string > & /* children */,
    bool /* expand */,
    const std::vector< std::vector< std::string > > & /* variables */) const
{
  std::ostringstream out;

  //or use mValue instead?
  out << "<mn>" << mData << "</mn>" << std::endl;

  return out.str();
}

std::string CEvaluationNodeNumber::getCCodeString(const std::vector< std::string > & /*children*/) const
{
  std::ostringstream out;
  out <<  std::setprecision(std::numeric_limits<double>::digits10 + 2) <<  std::fixed  << *mpValue;
  return out.str();
}
