// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

#include <sstream>

#include "copasi/copasi.h"

#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "copasi/utilities/CValidatedUnit.h"

#include "copasi/randomGenerator/CRandom.h"

#include "sbml/math/ASTNode.h"
#include "copasi/sbml/ConverterASTNode.h"
#include "copasi/sbml/SBMLImporter.h"

CRandom * CEvaluationNodeFunction::mpRandom = NULL;

// static
C_FLOAT64 CEvaluationNodeFunction::runiform(C_FLOAT64 lowerBound, C_FLOAT64 upperBound)
{return lowerBound + mpRandom->getRandomOO() * (upperBound - lowerBound);}

// static
C_FLOAT64 CEvaluationNodeFunction::rnormal(C_FLOAT64 mean, C_FLOAT64 sd)
{return mpRandom->getRandomNormal(mean, sd);}

//static
C_FLOAT64 CEvaluationNodeFunction::rgamma(C_FLOAT64 shape,
    C_FLOAT64 scale)
{
  return mpRandom->getRandomGamma(shape, scale);
}

//static
C_FLOAT64 CEvaluationNodeFunction::rpoisson(C_FLOAT64 mu)
{
  return mpRandom->getRandomPoisson(mu);
}

// static
C_FLOAT64 CEvaluationNodeFunction::max(C_FLOAT64 x1, C_FLOAT64 x2)
{
  return std::max(x1, x2);
}

// static
C_FLOAT64 CEvaluationNodeFunction::min(C_FLOAT64 x1, C_FLOAT64 x2)
{
  return std::min(x1, x2);
}

CEvaluationNodeFunction::CEvaluationNodeFunction():
  CEvaluationNode(MainType::FUNCTION, SubType::INVALID, ""),
  mpFunction(NULL),
  mpFunction2(NULL),
  mpFunction4(NULL),
  mpArgNode1(NULL),
  mpArgNode2(NULL),
  mpArgNode3(NULL),
  mpArgNode4(NULL),
  mpArgValue1(NULL),
  mpArgValue2(NULL),
  mpArgValue3(NULL),
  mpArgValue4(NULL)
{
  mPrecedence = PRECEDENCE_NUMBER;
}

CEvaluationNodeFunction::CEvaluationNodeFunction(const SubType & subType,
    const Data & data):
  CEvaluationNode(MainType::FUNCTION, subType, data),
  mpFunction(NULL),
  mpFunction2(NULL),
  mpFunction4(NULL),
  mpArgNode1(NULL),
  mpArgNode2(NULL),
  mpArgNode3(NULL),
  mpArgNode4(NULL),
  mpArgValue1(NULL),
  mpArgValue2(NULL),
  mpArgValue3(NULL),
  mpArgValue4(NULL)
{
  mValueType = (mSubType != SubType::NOT) ? ValueType::Number : ValueType::Boolean;

  switch (subType)
    {
      case SubType::LOG:
        mpFunction = log;
        break;

      case SubType::LOG10:
        mpFunction = log10;
        break;

      case SubType::EXP:
        mpFunction = exp;
        break;

      case SubType::SIN:
        mpFunction = sin;
        break;

      case SubType::COS:
        mpFunction = cos;
        break;

      case SubType::TAN:
        mpFunction = tan;
        break;

      case SubType::SEC:
        mpFunction = sec;
        break;

      case SubType::CSC:
        mpFunction = csc;
        break;

      case SubType::COT:
        mpFunction = cot;
        break;

      case SubType::SINH:
        mpFunction = sinh;
        break;

      case SubType::COSH:
        mpFunction = cosh;
        break;

      case SubType::TANH:
        mpFunction = tanh;
        break;

      case SubType::SECH:
        mpFunction = sech;
        break;

      case SubType::CSCH:
        mpFunction = csch;
        break;

      case SubType::COTH:
        mpFunction = coth;
        break;

      case SubType::ARCSIN:
        mpFunction = asin;
        break;

      case SubType::ARCCOS:
        mpFunction = acos;
        break;

      case SubType::ARCTAN:
        mpFunction = atan;
        break;

      case SubType::ARCSEC:
        mpFunction = arcsec;
        break;

      case SubType::ARCCSC:
        mpFunction = arccsc;
        break;

      case SubType::ARCCOT:
        mpFunction = arccot;
        break;

      case SubType::ARCSINH:
        mpFunction = asinh;
        break;

      case SubType::ARCCOSH:
        mpFunction = acosh;
        break;

      case SubType::ARCTANH:
        mpFunction = atanh;
        break;

      case SubType::ARCSECH:
        mpFunction = asech;
        break;

      case SubType::ARCCSCH:
        mpFunction = acsch;
        break;

      case SubType::ARCCOTH:
        mpFunction = acoth;
        break;

      case SubType::SIGN:
        mpFunction = sign;
        break;

      case SubType::SQRT:
        mpFunction = sqrt;
        break;

      case SubType::ABS:
        mpFunction = fabs;
        break;

      case SubType::FLOOR:
        mpFunction = floor;
        break;

      case SubType::CEIL:
        mpFunction = ceil;
        break;

      case SubType::FACTORIAL:
        mpFunction = factorial;
        break;

      case SubType::MINUS:
        mpFunction = minus;
        break;

      case SubType::PLUS:
        mpFunction = plus;
        break;

      case SubType::NOT:
        mpFunction = copasiNot;
        break;

      case SubType::RUNIFORM:
        mpFunction2 = runiform;

        if (!mpRandom)
          mpRandom = CRandom::createGenerator();

        break;

      case SubType::RNORMAL:
        mpFunction2 = rnormal;

        if (!mpRandom)
          mpRandom = CRandom::createGenerator();

        break;

      case SubType::RPOISSON:
        mpFunction = rpoisson;

        if (!mpRandom)
          mpRandom = CRandom::createGenerator();

        break;

      case SubType::RGAMMA:
        mpFunction2 = rgamma;

        if (!mpRandom)
          mpRandom = CRandom::createGenerator();

        break;

      case SubType::MAX:
        mpFunction2 = max;
        break;

      case SubType::MIN:
        mpFunction2 = min;
        break;

      default:
        mpFunction = NULL;
        fatalError();
        break;
    }

  mPrecedence = PRECEDENCE_FUNCTION;
}

CEvaluationNodeFunction::CEvaluationNodeFunction(const CEvaluationNodeFunction & src):
  CEvaluationNode(src),
  mpFunction(src.mpFunction),
  mpFunction2(src.mpFunction2),
  mpFunction4(src.mpFunction4),
  mpArgNode1(src.mpArgNode1),
  mpArgNode2(src.mpArgNode2),
  mpArgNode3(src.mpArgNode3),
  mpArgNode4(src.mpArgNode4),
  mpArgValue1(src.mpArgValue1),
  mpArgValue2(src.mpArgValue2),
  mpArgValue3(src.mpArgValue3),
  mpArgValue4(src.mpArgValue4)
{}

CEvaluationNodeFunction::~CEvaluationNodeFunction() {}

CIssue CEvaluationNodeFunction::compile()
{
  bool success = true;

  mpArgNode1 = static_cast<CEvaluationNode *>(getChild());

  if (mpArgNode1 == NULL) return CIssue(CIssue::eSeverity::Error, CIssue::eKind::VariableNotfound);

  mpArgValue1 = mpArgNode1->getValuePointer();
  success &= mpArgNode1->setValueType(mValueType);

  if (mpFunction)
    {
      if (mpArgNode1->getSibling() == NULL)
        return CIssue::Success;
      else
        return CIssue(CIssue::eSeverity::Error, CIssue::eKind::TooManyArguments);// We must have only one child
    }

  mpArgNode2 = static_cast<CEvaluationNode *>(mpArgNode1->getSibling());

  if (mpArgNode2 == NULL) return CIssue(CIssue::eSeverity::Error, CIssue::eKind::VariableNotfound);

  mpArgValue2 = mpArgNode2->getValuePointer();
  success &= mpArgNode2->setValueType(mValueType);

  if (mpFunction2)
    {
      if (mpArgNode2->getSibling() == NULL)
        return CIssue::Success;
      else
        return CIssue(CIssue::eSeverity::Error, CIssue::eKind::TooManyArguments);// We must have only 2 children
    }

  // equality
  mpArgNode3 = static_cast<CEvaluationNode *>(mpArgNode2->getSibling());

  if (mpArgNode3 == NULL) return CIssue(CIssue::eSeverity::Error, CIssue::eKind::VariableNotfound);

  mpArgValue3 = mpArgNode3->getValuePointer();
  success &= mpArgNode3->setValueType(mValueType);

  mpArgNode4 = static_cast<CEvaluationNode *>(mpArgNode3->getSibling());

  if (mpArgNode4 == NULL) return CIssue(CIssue::eSeverity::Error, CIssue::eKind::VariableNotfound);

  mpArgValue4 = mpArgNode4->getValuePointer();
  success &= mpArgNode4->setValueType(mValueType);

  if (mpArgNode4->getSibling() == NULL)
    return CIssue::Success;
  else
    return CIssue(CIssue::eSeverity::Error, CIssue::eKind::TooManyArguments);// We must have exactly 4 children
}

// virtual
std::string CEvaluationNodeFunction::getInfix(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeFunction *>(this)->compile())
    switch (mSubType)
      {
        case SubType::MINUS:
        case SubType::PLUS:
          return handleSign(children[0]);

        case SubType::RUNIFORM:
        case SubType::RNORMAL:
        case SubType::RGAMMA:
        case SubType::MAX:
        case SubType::MIN:
          return mData + "(" + children[0] + "," + children[1] + ")";

        case SubType::RPOISSON:
          return mData + "(" + children[0] + ")";

        case SubType::NOT:
          return handleNot(children[0]);

        default:
          return mData + "(" + children[0] + ")";
      }
  else
    return "@";
}

// virtual
std::string CEvaluationNodeFunction::getDisplayString(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeFunction *>(this)->compile())
    switch (mSubType)
      {
        case SubType::MINUS:
        case SubType::PLUS:
          return handleSign(children[0]);

        case SubType::RUNIFORM:
        case SubType::RNORMAL:
        case SubType::RGAMMA:
        case SubType::MAX:
        case SubType::MIN:
          return mData + "(" + children[0] + "," + children[1] + ")";

        case SubType::RPOISSON:
          return mData + "(" + children[0] + ")";

        case SubType::NOT:
          return handleNot(children[0]);

        default:
          return mData + "(" + children[0] + ")";
      }
  else
    return "@";
}

// virtual
std::string CEvaluationNodeFunction::getCCodeString(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeFunction *>(this)->compile())
    {
      std::string data = "";

      switch ((SubType)this->subType())
        {
          case SubType::LOG:
            data = "log";
            break;

          case SubType::LOG10:
            data = "log10";
            break;

          case SubType::EXP:
            data = "exp";
            break;

          case SubType::SIN:
            data = "sin";
            break;

          case SubType::COS:
            data = "cos";
            break;

          case SubType::TAN:
            data = "tan";
            break;

          case SubType::SINH:
            data = "sinh";
            break;

          case SubType::COSH:
            data = "cosh";
            break;

          case SubType::TANH:
            data = "tanh";
            break;

          case SubType::ARCSIN:
            data = "asin";
            break;

          case SubType::ARCCOS:
            data = "acos";
            break;

          case SubType::ARCTAN:
            data = "atan";
            break;

          case SubType::ARCSINH:
            data = "asinh";
            break;

          case SubType::ARCCOSH:
            data = "acosh";
            break;

          case SubType::ARCTANH:
            data = "atanh";
            break;

          case SubType::SQRT:
            data = "sqrt";
            break;

          case SubType::ABS:
            data = "abs";
            break;

          case SubType::NOT:
            data = "!";
            break;

          case SubType::MINUS:
            data = "-";
            break;

          case SubType::PLUS:
            break;

          case SubType::SEC:
            data = "sec";
            break;

          case SubType::CSC:
            data = "csc";
            break;

          case SubType::COT:
            data = "cot";
            break;

          case SubType::SECH:
            data = "sech";
            break;

          case SubType::CSCH:
            data = "csch";
            break;

          case SubType::COTH:
            data = "coth";
            break;

          case SubType::ARCSEC:
            data = "arcsec";
            break;

          case SubType::ARCCSC:
            data = "arccsc";
            break;

          case SubType::ARCCOT:
            data = "arccot";
            break;

          case SubType::ARCSECH:
            data = "asech";
            break;

          case SubType::ARCCSCH:
            data = "acsch";
            break;

          case SubType::ARCCOTH:
            data = "acoth";
            break;

          case SubType::FLOOR:
            data = "floor";
            break;

          case SubType::CEIL:
            data = "ceil";
            break;

          case SubType::FACTORIAL:
            data = "factorial";
            break;

          case SubType::RUNIFORM:
            data = "user_provided_uniform";
            break;

          case SubType::RNORMAL:
            data = "user_provided_normal";
            break;

          case SubType::RGAMMA:
            data = "user_provided_normal";
            break;

          case SubType::RPOISSON:
            data = "user_provided_normal";
            break;

          case SubType::MAX:
            data = "max";
            break;

          case SubType::MIN:
            data = "min";
            break;

          default:
            data = "@";
            break;
        }

      switch (mSubType)
        {
          case SubType::MINUS:
            return "(" + data + children[0] + ")";
            break;

          case SubType::PLUS:
            //return handleSign(mpLeft->getDisplay_C_String(pTree));
            return children[0];
            break;

          case SubType::RUNIFORM:
          case SubType::RNORMAL:
          case SubType::RGAMMA:
          case SubType::MAX:
          case SubType::MIN:
            return data + "(" + children[0] + "," + children[1] + ")";

          default:
            return data + "(" + children[0] + ")";
        }
    }

  //else
  return "@";
}

// virtual
std::string CEvaluationNodeFunction::getBerkeleyMadonnaString(const std::vector< std::string > & children) const
{
  std::string data = "";

  if (const_cast<CEvaluationNodeFunction *>(this)->compile())
    {
      data = mData;

      switch ((SubType)this->subType())
        {
          case SubType::LOG:
          case SubType::LOG10:
          case SubType::EXP:
          case SubType::SIN:
          case SubType::COS:
          case SubType::TAN:
          case SubType::SINH:
          case SubType::COSH:
          case SubType::TANH:
          case SubType::ARCSIN:
          case SubType::ARCCOS:
          case SubType::ARCTAN:
          case SubType::ARCSINH:
          case SubType::ARCCOSH:
          case SubType::ARCTANH:
          case SubType::SQRT:
          case SubType::ABS:
          case SubType::NOT:
            break;

          case SubType::MINUS:
            data = "-";
            break;

          case SubType::PLUS:
            data = "";
            break;

          case SubType::SEC:
          case SubType::CSC:
          case SubType::COT:
          case SubType::SECH:
          case SubType::CSCH:
          case SubType::COTH:
          case SubType::ARCSEC:
          case SubType::ARCCSC:
          case SubType::ARCCOT:
          case SubType::ARCSECH:
          case SubType::ARCCSCH:
          case SubType::ARCCOTH:
          case SubType::FLOOR:
          case SubType::CEIL:
          case SubType::FACTORIAL:
          case SubType::RUNIFORM:
          case SubType::RNORMAL:
          case SubType::RGAMMA:
          case SubType::RPOISSON:
          case SubType::MAX:
          case SubType::MIN:
          default:
            data = "ILLEGAL FUNCTION";
            break;
        }

      switch (mSubType)
        {
          case SubType::MINUS:
            return "(" + data + children[0] + ")";
            break;

          case SubType::PLUS:
            //return handleSign(mpLeft->getDisplay_MMD_String(pTree));
            return children[0];
            break;

          case SubType::RUNIFORM:
          case SubType::RNORMAL:
          case SubType::RGAMMA:
          case SubType::MAX:
          case SubType::MIN:
            return data + "(" + children[0] + "," + children[1] + ")";

          default:
            return data + "(" + children[0] + ")";
        }
    }

  //else
  return "@";
}

// virtual
std::string CEvaluationNodeFunction::getXPPString(const std::vector< std::string > & children) const
{
  std::string data = "";

  if (const_cast<CEvaluationNodeFunction *>(this)->compile())
    {
      data = mData;

      switch ((SubType)this->subType())
        {
          case SubType::LOG:
          case SubType::LOG10:
          case SubType::EXP:
          case SubType::SIN:
          case SubType::COS:
          case SubType::TAN:
          case SubType::SINH:
          case SubType::COSH:
          case SubType::TANH:
          case SubType::ARCSIN:
          case SubType::ARCCOS:
          case SubType::ARCTAN:
          case SubType::SQRT:
          case SubType::ABS:
          case SubType::NOT:
          case SubType::PLUS:
            break;

          case SubType::MINUS:
            data = "-";
            break;

          case SubType::FLOOR:
            data = "flr";
            break;

          case SubType::CEIL:
            data = "ceil";
            break;

          case SubType::ARCSINH:
          case SubType::ARCCOSH:
          case SubType::ARCTANH:
          case SubType::SEC:
          case SubType::CSC:
          case SubType::COT:
          case SubType::SECH:
          case SubType::CSCH:
          case SubType::COTH:
          case SubType::ARCSEC:
          case SubType::ARCCSC:
          case SubType::ARCCOT:
          case SubType::ARCSECH:
          case SubType::ARCCSCH:
          case SubType::ARCCOTH:
          case SubType::FACTORIAL:
          case SubType::RUNIFORM:
          case SubType::RNORMAL:
          case SubType::RGAMMA:
          case SubType::RPOISSON:
          case SubType::MAX:
          case SubType::MIN:
          default:
            data = "@"; //TODO
            break;
        }

      switch (mSubType)
        {
          case SubType::MINUS:
            return "(" + data + children[0] + ")";
            break;

          case SubType::PLUS:
            return children[0];
            break;

          case SubType::RUNIFORM:
          case SubType::RNORMAL:
          case SubType::RGAMMA:
          case SubType::MAX:
          case SubType::MIN:
            return data + "(" + children[0] + "," + children[1] + ")";

          default:
            return data + "(" + children[0] + ")";
        }
    }
  else
    return "@"; //TODO

  return ""; //should never be reached, only because of warning
}

// static
CEvaluationNode * CEvaluationNodeFunction::fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children)
{
  assert(pASTNode->getNumChildren() == children.size());

  size_t iMax = children.size();

  int type = (int)pASTNode->getType();
  SubType subType;
  std::string data = "";

  if (type == AST_FUNCTION_ROOT)
    {
      CEvaluationNode * pNode = NULL;

      switch (iMax)
        {
          case 1:
            pNode = new CEvaluationNodeFunction(SubType::SQRT, "sqrt");
            pNode->addChild(children[0]);
            break;

          case 2:
            /**
             * Replaces all root nodes with the corresponding power
             * operator since COPASI does not have the ROOT function.
             */
          {
            pNode = new CEvaluationNodeOperator(SubType::POWER, "^");
            pNode->addChild(children[1]); // Value
            CEvaluationNode * pExponent = new CEvaluationNodeOperator(SubType::DIVIDE, "/");
            pNode->addChild(pExponent);
            pExponent->addChild(new CEvaluationNodeNumber(SubType::DOUBLE, "1"));
            pExponent->addChild(children[0]); // Degree
          }
          break;
        }

      return pNode;
    }
  else if (type == AST_FUNCTION_LOG && iMax == 2)
    {
      /**
       * Replaces all LOG10 (AST_FUNCTION_LOG) nodes that have two children and
       * the base is not 10 with the quotient of two LOG10 nodes with the base
       * as the argument for the divisor LOG10 node.
       */
      CEvaluationNode * pNode = nullptr;

      if (children[0]->mainType() == CEvaluationNode::MainType::NUMBER
          && SBMLImporter::areApproximatelyEqual(*children[0]->getValuePointer(), 10.0, 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon()))
        {
          pNode = new CEvaluationNodeFunction(SubType::LOG10, "log10");
          pNode->addChild(children[1]);
        }
      else
        {
          CEvaluationNode * pValue = new CEvaluationNodeFunction(SubType::LOG10, "log10");
          pValue->addChild(children[1]);
          CEvaluationNode * pBase = new CEvaluationNodeFunction(SubType::LOG10, "log10");
          pBase->addChild(children[0]);

          pNode = new CEvaluationNodeOperator(SubType::DIVIDE, "/");
          pNode->addChild(pValue);
          pNode->addChild(pBase);
        }

      return pNode;
    }

  switch (type)
    {
      case AST_FUNCTION_ABS:
        subType = SubType::ABS;
        data = "abs";
        break;

      case AST_FUNCTION_ARCCOS:
        subType = SubType::ARCCOS;
        data = "acos";
        break;

      case AST_FUNCTION_ARCCOSH:
        subType = SubType::ARCCOSH;
        data = "arccosh";
        break;

      case AST_FUNCTION_ARCCOT:
        subType = SubType::ARCCOT;
        data = "arccot";
        break;

      case AST_FUNCTION_ARCCOTH:
        subType = SubType::ARCCOTH;
        data = "arccoth";
        break;

      case AST_FUNCTION_ARCCSC:
        subType = SubType::ARCCSC;
        data = "arccsc";
        break;

      case AST_FUNCTION_ARCCSCH:
        subType = SubType::ARCCSCH;
        data = "arccsch";
        break;

      case AST_FUNCTION_ARCSEC:
        subType = SubType::ARCSEC;
        data = "arcsec";
        break;

      case AST_FUNCTION_ARCSECH:
        subType = SubType::ARCSECH;
        data = "arcsech";
        break;

      case AST_FUNCTION_ARCSIN:
        subType = SubType::ARCSIN;
        data = "asin";
        break;

      case AST_FUNCTION_ARCSINH:
        subType = SubType::ARCSINH;
        data = "arcsinh";
        break;

      case AST_FUNCTION_ARCTAN:
        subType = SubType::ARCTAN;
        data = "atan";
        break;

      case AST_FUNCTION_ARCTANH:
        subType = SubType::ARCTANH;
        data = "arctanh";
        break;

      case AST_FUNCTION_CEILING:
        subType = SubType::CEIL;
        data = "ceil";
        break;

      case AST_FUNCTION_COS:
        subType = SubType::COS;
        data = "cos";
        break;

      case AST_FUNCTION_COSH:
        subType = SubType::COSH;
        data = "cosh";
        break;

      case AST_FUNCTION_COT:
        subType = SubType::COT;
        data = "cot";
        break;

      case AST_FUNCTION_COTH:
        subType = SubType::COTH;
        data = "coth";
        break;

      case AST_FUNCTION_CSC:
        subType = SubType::CSC;
        data = "csc";
        break;

      case AST_FUNCTION_CSCH:
        subType = SubType::CSCH;
        data = "csch";
        break;

      case AST_FUNCTION_EXP:
        subType = SubType::EXP;
        data = "exp";
        break;

      case AST_FUNCTION_FACTORIAL:
        subType = SubType::FACTORIAL;
        data = "factorial";
        break;

      case AST_FUNCTION_FLOOR:
        subType = SubType::FLOOR;
        data = "floor";
        break;

      case AST_FUNCTION_LN:
        subType = SubType::LOG;
        data = "log";
        break;

      case AST_FUNCTION_LOG:
        subType = SubType::LOG10;
        data = "log10";
        break;

      case AST_FUNCTION_SEC:
        subType = SubType::SEC;
        data = "sec";
        break;

      case AST_FUNCTION_SECH:
        subType = SubType::SECH;
        data = "sech";
        break;

      case AST_FUNCTION_SIN:
        subType = SubType::SIN;
        data = "sin";
        break;

      case AST_FUNCTION_SINH:
        subType = SubType::SINH;
        data = "sinh";
        break;

      case AST_FUNCTION_TAN:
        subType = SubType::TAN;
        data = "tan";
        break;

      case AST_FUNCTION_TANH:
        subType = SubType::TANH;
        data = "tanh";
        break;

      case AST_LOGICAL_NOT:
        subType = SubType::NOT;
        data = "not";
        break;

      default:
        subType = SubType::INVALID;
        fatalError();
        break;
    }

  assert(iMax == 1);
  CEvaluationNode * pNode = new CEvaluationNodeFunction(subType, data);

  if (!children.empty())
    pNode->addChild(children[0]);

  return pNode;
}

ASTNode* CEvaluationNodeFunction::toAST(const CDataModel* pDataModel) const
{
  SubType subType = (SubType)this->subType();
  ASTNode* node = new ASTNode();
  bool needFirstArg = true;

  switch (subType)
    {
      case SubType::INVALID:
        break;

      case SubType::LOG:
        node->setType(AST_FUNCTION_LN);
        break;

      case SubType::LOG10:
      {
        // log 10 needs two children, the log and the base
        node->setType(AST_FUNCTION_LOG);

        ASTNode* logBase = new ASTNode();
        logBase->setType(AST_INTEGER);
        logBase->setValue(10);
        node->addChild(logBase);

        break;
      }

      case SubType::EXP:
        node->setType(AST_FUNCTION_EXP);
        break;

      case SubType::SIN:
        node->setType(AST_FUNCTION_SIN);
        break;

      case SubType::COS:
        node->setType(AST_FUNCTION_COS);
        break;

      case SubType::TAN:
        node->setType(AST_FUNCTION_TAN);
        break;

      case SubType::SEC:
        node->setType(AST_FUNCTION_SEC);
        break;

      case SubType::CSC:
        node->setType(AST_FUNCTION_CSC);
        break;

      case SubType::COT:
        node->setType(AST_FUNCTION_COT);
        break;

      case SubType::SINH:
        node->setType(AST_FUNCTION_SINH);
        break;

      case SubType::COSH:
        node->setType(AST_FUNCTION_COSH);
        break;

      case SubType::TANH:
        node->setType(AST_FUNCTION_TANH);
        break;

      case SubType::SECH:
        node->setType(AST_FUNCTION_SECH);
        break;

      case SubType::CSCH:
        node->setType(AST_FUNCTION_CSCH);
        break;

      case SubType::COTH:
        node->setType(AST_FUNCTION_COTH);
        break;

      case SubType::ARCSIN:
        node->setType(AST_FUNCTION_ARCSIN);
        break;

      case SubType::ARCCOS:
        node->setType(AST_FUNCTION_ARCCOS);
        break;

      case SubType::ARCTAN:
        node->setType(AST_FUNCTION_ARCTAN);
        break;

      case SubType::ARCSEC:
        node->setType(AST_FUNCTION_ARCSEC);
        break;

      case SubType::ARCCSC:
        node->setType(AST_FUNCTION_ARCCSC);
        break;

      case SubType::ARCCOT:
        node->setType(AST_FUNCTION_ARCCOT);
        break;

      case SubType::ARCSINH:
        node->setType(AST_FUNCTION_ARCSINH);
        break;

      case SubType::ARCCOSH:
        node->setType(AST_FUNCTION_ARCCOSH);
        break;

      case SubType::ARCTANH:
        node->setType(AST_FUNCTION_ARCTANH);
        break;

      case SubType::ARCSECH:
        node->setType(AST_FUNCTION_ARCSECH);
        break;

      case SubType::ARCCSCH:
        node->setType(AST_FUNCTION_ARCCSCH);
        break;

      case SubType::ARCCOTH:
        node->setType(AST_FUNCTION_ARCCOTH);
        break;

      case SubType::SQRT:
        node->setType(AST_FUNCTION_ROOT);
        break;

      case SubType::ABS:
        node->setType(AST_FUNCTION_ABS);
        break;

      case SubType::CEIL:
        node->setType(AST_FUNCTION_CEILING);
        break;

      case SubType::FLOOR:
        node->setType(AST_FUNCTION_FLOOR);
        break;

      case SubType::FACTORIAL:
        node->setType(AST_FUNCTION_FACTORIAL);
        break;

      case SubType::MINUS:
        node->setType(AST_MINUS);
        break;

      case SubType::PLUS:
        // if this is the unary plus as I suspect,
        // the node will be replaced by its only child
        needFirstArg = false;
        delete node;
        node = dynamic_cast<const CEvaluationNode*>(this->getChild())->toAST(pDataModel);
        break;

      case SubType::NOT:
        node->setType(AST_LOGICAL_NOT);
        break;

      case SubType::RUNIFORM:
      {
        needFirstArg = false;
        node->setType(AST_FUNCTION);
        node->setName("RUNIFORM");
        const CEvaluationNode* child = dynamic_cast<const CEvaluationNode*>(this->getChild());
        const CEvaluationNode* sibling = dynamic_cast<const CEvaluationNode*>(child->getSibling());
        node->addChild(child->toAST(pDataModel));
        node->addChild(sibling->toAST(pDataModel));
      }
      break;

      case SubType::RNORMAL:
      {
        needFirstArg = false;
        node->setType(AST_FUNCTION);
        node->setName("RNORMAL");
        const CEvaluationNode* child = dynamic_cast<const CEvaluationNode*>(this->getChild());
        const CEvaluationNode* sibling = dynamic_cast<const CEvaluationNode*>(child->getSibling());
        node->addChild(child->toAST(pDataModel));
        node->addChild(sibling->toAST(pDataModel));
      }
      break;

      case SubType::RGAMMA:
      {
        needFirstArg = false;
        node->setType(AST_FUNCTION);
        node->setName("RGAMMA");
        const CEvaluationNode* child = dynamic_cast<const CEvaluationNode*>(this->getChild());
        const CEvaluationNode* sibling = dynamic_cast<const CEvaluationNode*>(child->getSibling());
        node->addChild(child->toAST(pDataModel));
        node->addChild(sibling->toAST(pDataModel));
      }
      break;

      case SubType::RPOISSON:
      {
        needFirstArg = false;
        node->setType(AST_FUNCTION);
        node->setName("RPOISSON");
        const CEvaluationNode* child = dynamic_cast<const CEvaluationNode*>(this->getChild());
        node->addChild(child->toAST(pDataModel));
      }
      break;

      case SubType::MAX:
      {
        needFirstArg = false;
        node->setType(AST_FUNCTION);
        node->setName("MAX");
        const CEvaluationNode* child = dynamic_cast<const CEvaluationNode*>(this->getChild());
        const CEvaluationNode* sibling = dynamic_cast<const CEvaluationNode*>(child->getSibling());
        node->addChild(child->toAST(pDataModel));
        node->addChild(sibling->toAST(pDataModel));
      }
      break;

      case SubType::MIN:
      {
        needFirstArg = false;
        node->setType(AST_FUNCTION);
        node->setName("MIN");
        const CEvaluationNode* child = dynamic_cast<const CEvaluationNode*>(this->getChild());
        const CEvaluationNode* sibling = dynamic_cast<const CEvaluationNode*>(child->getSibling());
        node->addChild(child->toAST(pDataModel));
        node->addChild(sibling->toAST(pDataModel));
      }
      break;
        // :TODO: Bug 894: Implement me.
        //fatalError();
      break;
    }

  if (subType != SubType::INVALID)
    {
      // the following is a workaround for a bug in libsbml 3.1.1 and 3.2.0
      // where libsbml does not handle the case correctly that a root
      // function can have one or two children (MathML.cpp in function
      // writeFunctionRoot)
      if (subType == SubType::SQRT)
        {
          // add a degree node of value 2 as the first child
          ASTNode* pDegreeNode = new ASTNode();
          pDegreeNode->setType(AST_INTEGER);
          pDegreeNode->setValue(2);
          node->addChild(pDegreeNode);
        }

      if (needFirstArg)
        {
          const CEvaluationNode* child = dynamic_cast<const CEvaluationNode*>(this->getChild());
          node->addChild(child->toAST(pDataModel));
        }
    }

  return node;
}

CEvaluationNode* CEvaluationNodeFunction::simplifyNode(const std::vector<CEvaluationNode*>& children) const
{
  assert(children.size() > 0);
  CEvaluationNode* child1 = children[0];

  switch (mSubType)
    {
      case SubType::MINUS:
      {
        switch (child1->mainType())
          {
            case CEvaluationNode::MainType::OPERATOR:
            {
              switch (child1->subType())
                {
                  case SubType::DIVIDE:
                  {
                    // -(a/b) -> (-a)/b
                    // want to recognize a fraction in a sum easily
                    CEvaluationNode *newnode = CEvaluationNode::create(MainType::OPERATOR, SubType::DIVIDE, "/");
                    CEvaluationNode *newchild1 = CEvaluationNode::create(MainType::FUNCTION, SubType::MINUS, "-");
                    CEvaluationNode *newchild2 = dynamic_cast<CEvaluationNode*>(child1->getChild()->getSibling())->copyBranch();
                    CEvaluationNode *grandchild = dynamic_cast<CEvaluationNode*>(child1->getChild())->copyBranch();
                    newnode->addChild(newchild1, NULL);
                    newnode->addChild(newchild2, newchild1);
                    newchild1->addChild(grandchild, NULL);
                    delete child1;
                    return newnode;
                  }

                  case SubType::PLUS:
                  {
                    // -(a+b) -> (-a)+(-b)
                    // negativity should be property of product
                    CEvaluationNode *newnode = CEvaluationNode::create(MainType::OPERATOR, SubType::PLUS, "+");
                    CEvaluationNode *newchild1 = CEvaluationNode::create(MainType::FUNCTION, SubType::MINUS, "-");
                    CEvaluationNode *newchild2 = CEvaluationNode::create(MainType::FUNCTION, SubType::MINUS, "-");
                    CEvaluationNode *grandchild1 = dynamic_cast<CEvaluationNode*>(child1->getChild())->copyBranch();
                    CEvaluationNode *grandchild2 = dynamic_cast<CEvaluationNode*>(child1->getChild()->getSibling())->copyBranch();
                    newnode->addChild(newchild1, NULL);
                    newnode->addChild(newchild2, newchild1);
                    newchild1->addChild(grandchild1, NULL);
                    newchild2->addChild(grandchild2, NULL);
                    delete child1;
                    return newnode;
                  }

                  default:        // cases POWER, MULTIPLY, MODULUS. don't expect MINUS to occur anymore
                  {
                    CEvaluationNode *newnode = copyNode(children);
                    return newnode;
                  }
                }
            }

            case CEvaluationNode::MainType::FUNCTION:
            {
              if (child1->getData() == "-")
                {
                  // -(-a) -> a
                  CEvaluationNode *newnode = dynamic_cast<CEvaluationNode*>(child1->getChild())->copyBranch();
                  delete child1;
                  return newnode;
                }

              // default: copy
              CEvaluationNode *newnode = copyNode(children);
              return newnode;
            }

            case CEvaluationNode::MainType::NUMBER:
            {
              std::stringstream tmp;
              tmp << *child1->getValuePointer() *(-1.0);
              CEvaluationNode* newnode = CEvaluationNode::create(MainType::NUMBER, SubType::DOUBLE, tmp.str());
              delete child1;
              return newnode;
            }

            default:         //cases VARIABLE, CONSTANT..
            {
              CEvaluationNode *newnode = copyNode(children);
              return newnode;
            }
          }

        break;
      }

      case SubType::SQRT:
      {
        // write as ^0.5
        CEvaluationNode* newnode = CEvaluationNode::create(MainType::OPERATOR, SubType::POWER, "^");
        CEvaluationNode* newchild2 = CEvaluationNode::create(MainType::NUMBER, SubType::DOUBLE, "0.5");
        newnode->addChild(child1, NULL);
        newnode->addChild(newchild2, child1);
        return newnode;
      }

      default:
      {
        CEvaluationNode *newnode = copyNode(children);
        return newnode;
      }
    }
}

std::string CEvaluationNodeFunction::handleSign(const std::string & str) const
{
  Data Result;

  MainType T = mpArgNode1->mainType();

  if (T == MainType::OPERATOR)
    {
      Result = mData + "(" + str + ")";
    }
  else if (getParent() != NULL &&
           static_cast< const CEvaluationNode * >(getParent())->mainType() == MainType::OPERATOR &&
           static_cast< const CEvaluationNode * >(getParent())->subType() == SubType::POWER)
    {
      Result = "(" + mData + str + ")";
    }
  else
    {
      Result = mData + str;
    }

  return Result;
}

std::string CEvaluationNodeFunction::handleNot(const std::string & str) const
{
  Data Result = mData + " ";

  MainType T = mpArgNode1->mainType();

  if (T == MainType::LOGICAL)
    {
      Result += "(" + str + ")";
    }
  else
    Result += str;

  return Result;
}

CEvaluationNode * CEvaluationNodeFunction::getLeft()
{return mpArgNode1;}
const CEvaluationNode * CEvaluationNodeFunction::getLeft() const
{return mpArgNode1;}

#include "copasi/utilities/copasimathml.h"

// virtual
std::string CEvaluationNodeFunction::getMMLString(const std::vector< std::string > & children,
    bool expand,
    const std::vector< std::vector< std::string > > & /* variables */) const
{
  std::ostringstream out;

  std::string data = "";
  std::string ldata = "";
  std::string rdata = "";

  bool flag = ((mpArgNode1->mainType() == CEvaluationNode::MainType::NUMBER) ||
               (mpArgNode1->mainType() == CEvaluationNode::MainType::VARIABLE) ||
               (mpArgNode1->mainType() == CEvaluationNode::MainType::CONSTANT));

  bool flag1 = false;

  switch (mSubType)
    {
      case SubType::INVALID:
        data = "@";
        break;

      case SubType::LOG:
        data = "log";
        break;

      case SubType::LOG10:
        data = "log10";
        break;

      case SubType::EXP:
        break;

      case SubType::SIN:
        data = "sin";
        break;

      case SubType::COS:
        data = "cos";
        break;

      case SubType::TAN:
        data = "tan";
        break;

      case SubType::SEC:
        data = "sec";
        break;

      case SubType::CSC:
        data = "csc";
        break;

      case SubType::COT:
        data = "cot";
        break;

      case SubType::SINH:
        data = "sinh";
        break;

      case SubType::COSH:
        data = "cosh";
        break;

      case SubType::TANH:
        data = "tanh";
        break;

      case SubType::SECH:
        data = "sech";
        break;

      case SubType::CSCH:
        data = "csch";
        break;

      case SubType::COTH:
        data = "coth";
        break;

      case SubType::ARCSIN:
        data = "arcsin";
        break;

      case SubType::ARCCOS:
        data = "arccos";
        break;

      case SubType::ARCTAN:
        data = "arctan";
        break;

      case SubType::ARCSEC:
        data = "arcsec";
        break;

      case SubType::ARCCSC:
        data = "arccsc";
        break;

      case SubType::ARCCOT:
        data = "arccot";
        break;

      case SubType::ARCSINH:
        data = "arcsinh";
        break;

      case SubType::ARCCOSH:
        data = "arccosh";
        break;

      case SubType::ARCTANH:
        data = "arctanh";
        break;

      case SubType::ARCSECH:
        data = "arcsech";
        break;

      case SubType::ARCCSCH:
        data = "arccsch";
        break;

      case SubType::ARCCOTH:
        data = "arccoth";
        break;

      case SubType::SQRT:
        ldata = "<msqrt>";
        rdata = "</msqrt>";
        break;

      case SubType::ABS:
        ldata = "|";
        rdata = "|";
        break;

      case SubType::SIGN:
        data = "sign";
        break;

      case SubType::CEIL:
        data = "ceil";
        break;

      case SubType::FLOOR:
        data = "floor";
        break;

      case SubType::FACTORIAL:
        break;

      case SubType::MINUS:
        break;

      case SubType::PLUS:
        break;

      case SubType::NOT:
        data = "!";
        break;
    }

  const CEvaluationNode * pParent = static_cast<const CEvaluationNode *>(getParent());

  out << "<mrow>" << std::endl;

  switch (mSubType)
    {
      case SubType::PLUS:
      {
        size_t type = (mpArgNode1->mainType() | mpArgNode1->subType());

        flag = ((type == (MainType::OPERATOR | SubType::PLUS))
                || (type == (MainType::OPERATOR | SubType::MINUS))
                || ((mpArgNode1->mainType() == MainType::CALL) && expand));
      }

      if (flag) out << "<mfenced>" << std::endl;

      out << children[0];

      if (flag) out << "</mfenced>" << std::endl;

      break;

      case SubType::MINUS:

        if (pParent != 0)
          {
            flag1 = (pParent->mainType() == MainType::OPERATOR &&
                     this == static_cast<const CEvaluationNode *>(pParent->getChild()->getSibling()));

            flag1 |= ((pParent->mainType() | pParent->subType()) == (MainType::OPERATOR | SubType::POWER));

            if (flag1) out << "<mfenced>" << std::endl;

            if (flag1) out << "<mrow>" << std::endl;
          }

        out << "<mo>" << "-" << "</mo>" << std::endl;

        if (!flag) out << "<mfenced>" << std::endl;

        out << children[0];

        if (!flag) out << "</mfenced>" << std::endl;

        if (flag1) out << "</mrow>" << std::endl;

        if (flag1) out << "</mfenced>" << std::endl;

        break;

      case SubType::FACTORIAL:

        if (!flag) out << "<mfenced>" << std::endl;

        out << children[0];

        if (!flag) out << "</mfenced>" << std::endl;

        out << "<mo>" << "!" << "</mo>" << std::endl;

        break;

      case SubType::SQRT:
      case SubType::ABS:

        out << ldata << std::endl;

        out << children[0];

        out << rdata << std::endl;

        break;

      case SubType::EXP:

        out << "<msup>" << std::endl;
        out << "<mo> e  </mo>" << std::endl;

        out << children[0];

        out << "</msup>" << std::endl;

        break;

      case SubType::LOG10:

        out << "<msub>" << std::endl;
        out << "<mo>" << "log" << "</mo>" << std::endl;
        out << "<mn>" << "10" << "</mn>" << std::endl;

        out << "</msub>" << std::endl;

        if (flag)
          out << "<mspace width=\"0.3em\"/>" << std::endl;
        else
          out << "<mfenced>" << std::endl;

        out << children[0];

        if (!flag) out << "</mfenced>" << std::endl;

        break;

      case SubType::CEIL:
      case SubType::FLOOR:
        out << "<mi> " << data << " </mi>" << std::endl;

        out << "<mfenced>" << std::endl;

        out << children[0];

        out << "</mfenced>" << std::endl;

        break;

      case SubType::RUNIFORM:
      case SubType::RNORMAL:
      case SubType::RGAMMA:
      case SubType::MAX:
      case SubType::MIN:
        out << "<mrow>" << std::endl;

        out << "<mi>" << mData << "</mi>" << std::endl;
        out << "<mrow>" << std::endl;
        out << "<mo>(</mo>" << std::endl;
        out << "<mrow>" << std::endl;

        out << children[0];

        out << "<mo> , </mo>" << std::endl;

        out << children[1];

        out << "</mrow>" << std::endl;
        out << "<mo>) </mo>" << std::endl;

        out << "</mrow>" << std::endl;
        out << "</mrow>" << std::endl;
        break;

      case SubType::RPOISSON:
        out << "<mrow>" << std::endl;

        out << "<mi>" << mData << "</mi>" << std::endl;
        out << "<mrow>" << std::endl;
        out << "<mo>(</mo>" << std::endl;
        out << "<mrow>" << std::endl;

        out << children[0];

        out << "</mrow>" << std::endl;
        out << "<mo>) </mo>" << std::endl;

        out << "</mrow>" << std::endl;
        out << "</mrow>" << std::endl;
        break;

      default:

        out << "<mi> " << data << " </mi>" << std::endl;

        if (flag)
          out << "<mspace width=\"0.3em\"/>" << std::endl;
        else
          out << "<mfenced>" << std::endl;

        out << children[0];

        if (!flag) out << "</mfenced>" << std::endl;

        break;
    }

  out << "</mrow>" << std::endl;

  return out.str();
}

CValidatedUnit CEvaluationNodeFunction::getUnit(const CMathContainer & /* container */,
    const std::vector< CValidatedUnit > & units) const
{
  CValidatedUnit Unit(CBaseUnit::dimensionless, false);

  switch ((SubType)this->subType())
    {
      case SubType::LOG:
      case SubType::LOG10:
      case SubType::EXP:
      case SubType::SIN:
      case SubType::COS:
      case SubType::TAN:
      case SubType::SEC:
      case SubType::CSC:
      case SubType::COT:
      case SubType::SINH:
      case SubType::COSH:
      case SubType::TANH:
      case SubType::SECH:
      case SubType::CSCH:
      case SubType::COTH:
      case SubType::ARCSIN:
      case SubType::ARCCOS:
      case SubType::ARCTAN:
      case SubType::ARCSEC:
      case SubType::ARCCSC:
      case SubType::ARCCOT:
      case SubType::ARCSINH:
      case SubType::ARCCOSH:
      case SubType::ARCTANH:
      case SubType::ARCSECH:
      case SubType::ARCCSCH:
      case SubType::ARCCOTH:
      case SubType::FACTORIAL:
      case SubType::NOT:
        Unit = CValidatedUnit::merge(Unit, units[0]);
        break;

      case SubType::MAX:
      case SubType::MIN:
      case SubType::RUNIFORM:
      case SubType::RNORMAL:
        Unit = CValidatedUnit::merge(units[0], units[1]);
        break;

      case SubType::MINUS:
      case SubType::PLUS:
      case SubType::FLOOR:
      case SubType::CEIL:
      case SubType::ABS:
      case SubType::RPOISSON:
        Unit = units[0];

        break;

      case SubType::RGAMMA:
        // The unit of the gamma distribution is the inverse of the scale parameter (units[1])
        Unit = units[1].exponentiate(-1);

        // The shape parameter must be dimensionless
        if (!Unit.conflict())
          {
            Unit.setConflict(!(units[0] == CUnit(CBaseUnit::dimensionless)));
          }

        break;

      case SubType::SQRT:
      {
        // Exponentiate to 1/2.
        // Test if each component's exponent
        // is an integer. (don't want fractional exponents) by . . .
        // modf(exp, NULL) =< std::numeric_limits::epsilon
        Unit = units[0].exponentiate(1.0 / 2.0);

        std::set< CUnitComponent >::const_iterator  it = Unit.getComponents().begin();
        std::set< CUnitComponent >::const_iterator end = Unit.getComponents().end();

        for (; it != end; it++)
          {
            if (!(remainder((*it).getExponent(), 1.0) <= 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon()))
              {
                Unit = CValidatedUnit(CBaseUnit::undefined, true);

                break;
              }
          }

        break;
      }

      default:
        Unit.setConflict(true);
        break;
    }

  return Unit;
}

// virtual
CValidatedUnit CEvaluationNodeFunction::setUnit(const CMathContainer & container,
    const std::map < CEvaluationNode *, CValidatedUnit > & currentUnits,
    std::map < CEvaluationNode *, CValidatedUnit > & targetUnits) const
{
  CValidatedUnit Result(CEvaluationNode::setUnit(container, currentUnits, targetUnits));

  switch ((SubType)this->subType())
    {
      case SubType::LOG:
      case SubType::LOG10:
      case SubType::EXP:
      case SubType::SIN:
      case SubType::COS:
      case SubType::TAN:
      case SubType::SEC:
      case SubType::CSC:
      case SubType::COT:
      case SubType::SINH:
      case SubType::COSH:
      case SubType::TANH:
      case SubType::SECH:
      case SubType::CSCH:
      case SubType::COTH:
      case SubType::ARCSIN:
      case SubType::ARCCOS:
      case SubType::ARCTAN:
      case SubType::ARCSEC:
      case SubType::ARCCSC:
      case SubType::ARCCOT:
      case SubType::ARCSINH:
      case SubType::ARCCOSH:
      case SubType::ARCTANH:
      case SubType::ARCSECH:
      case SubType::ARCCSCH:
      case SubType::ARCCOTH:
      case SubType::FACTORIAL:
      case SubType::NOT:
        targetUnits[mpArgNode1] = CValidatedUnit(CBaseUnit::dimensionless, false);
        break;

      case SubType::MAX:
      case SubType::MIN:
      case SubType::RUNIFORM:
      case SubType::RNORMAL:
        targetUnits[mpArgNode1] = Result;
        targetUnits[mpArgNode2] = Result;
        break;

      case SubType::MINUS:
      case SubType::PLUS:
      case SubType::FLOOR:
      case SubType::CEIL:
      case SubType::ABS:
      case SubType::RPOISSON:
        targetUnits[mpArgNode1] = Result;
        break;

      case SubType::RGAMMA:
        targetUnits[mpArgNode1] = CValidatedUnit(CBaseUnit::dimensionless, false);
        targetUnits[mpArgNode2] = Result.exponentiate(-1);

        break;

      case SubType::SQRT:
        targetUnits[mpArgNode1] = Result.exponentiate(2.0);
        break;

      default:
        Result.setConflict(true);
        break;
    }

  return Result;
}
