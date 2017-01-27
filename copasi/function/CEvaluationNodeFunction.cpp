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

#include <sstream>

#include "copasi.h"

#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "utilities/CValidatedUnit.h"

#include "randomGenerator/CRandom.h"

#include "sbml/math/ASTNode.h"
#include "sbml/ConverterASTNode.h"

CRandom * CEvaluationNodeFunction::mpRandom = NULL;

// static
C_FLOAT64 CEvaluationNodeFunction::runiform(const C_FLOAT64 & lowerBound, const C_FLOAT64 & upperBound)
{return lowerBound + mpRandom->getRandomOO() * (upperBound - lowerBound);}

// static
C_FLOAT64 CEvaluationNodeFunction::rnormal(const C_FLOAT64 & mean, const C_FLOAT64 & sd)
{return mpRandom->getRandomNormal(mean, sd);}

//static
C_FLOAT64 CEvaluationNodeFunction::rgamma(const C_FLOAT64 & shape,
    const C_FLOAT64 & scale)
{
  return mpRandom->getRandomGamma(shape, scale);
}

//static
C_FLOAT64 CEvaluationNodeFunction::rpoisson(const C_FLOAT64 mu)
{
  return mpRandom->getRandomPoisson(mu);
}

// static
C_FLOAT64 CEvaluationNodeFunction::max(const C_FLOAT64 & x1, const C_FLOAT64 & x2)
{
  return std::max(x1, x2);
}

// static
C_FLOAT64 CEvaluationNodeFunction::min(const C_FLOAT64 & x1, const C_FLOAT64 & x2)
{
  return std::min(x1, x2);
}

CEvaluationNodeFunction::CEvaluationNodeFunction():
  CEvaluationNode(T_FUNCTION, S_INVALID, ""),
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
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeFunction::CEvaluationNodeFunction(const SubType & subType,
    const Data & data):
  CEvaluationNode(T_FUNCTION, subType, data),
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
  switch (subType)
    {
      case S_LOG:
        mpFunction = log;
        break;

      case S_LOG10:
        mpFunction = log10;
        break;

      case S_EXP:
        mpFunction = exp;
        break;

      case S_SIN:
        mpFunction = sin;
        break;

      case S_COS:
        mpFunction = cos;
        break;

      case S_TAN:
        mpFunction = tan;
        break;

      case S_SEC:
        mpFunction = sec;
        break;

      case S_CSC:
        mpFunction = csc;
        break;

      case S_COT:
        mpFunction = cot;
        break;

      case S_SINH:
        mpFunction = sinh;
        break;

      case S_COSH:
        mpFunction = cosh;
        break;

      case S_TANH:
        mpFunction = tanh;
        break;

      case S_SECH:
        mpFunction = sech;
        break;

      case S_CSCH:
        mpFunction = csch;
        break;

      case S_COTH:
        mpFunction = coth;
        break;

      case S_ARCSIN:
        mpFunction = asin;
        break;

      case S_ARCCOS:
        mpFunction = acos;
        break;

      case S_ARCTAN:
        mpFunction = atan;
        break;

      case S_ARCSEC:
        mpFunction = arcsec;
        break;

      case S_ARCCSC:
        mpFunction = arccsc;
        break;

      case S_ARCCOT:
        mpFunction = arccot;
        break;

      case S_ARCSINH:
        mpFunction = asinh;
        break;

      case S_ARCCOSH:
        mpFunction = acosh;
        break;

      case S_ARCTANH:
        mpFunction = atanh;
        break;

      case S_ARCSECH:
        mpFunction = asech;
        break;

      case S_ARCCSCH:
        mpFunction = acsch;
        break;

      case S_ARCCOTH:
        mpFunction = acoth;
        break;

      case S_SIGN:
        mpFunction = sign;
        break;

      case S_SQRT:
        mpFunction = sqrt;
        break;

      case S_ABS:
        mpFunction = fabs;
        break;

      case S_FLOOR:
        mpFunction = floor;
        break;

      case S_CEIL:
        mpFunction = ceil;
        break;

      case S_FACTORIAL:
        mpFunction = factorial;
        break;

      case S_MINUS:
        mpFunction = minus;
        break;

      case S_PLUS:
        mpFunction = plus;
        break;

      case S_NOT:
        mpFunction = copasiNot;
        break;

      case S_RUNIFORM:
        mpFunction2 = runiform;

        if (!mpRandom)
          mpRandom = CRandom::createGenerator();

        break;

      case S_RNORMAL:
        mpFunction2 = rnormal;

        if (!mpRandom)
          mpRandom = CRandom::createGenerator();

        break;

      case S_RPOISSON:
        mpFunction = rpoisson;

        if (!mpRandom)
          mpRandom = CRandom::createGenerator();

        break;

      case S_RGAMMA:
        mpFunction2 = rgamma;

        if (!mpRandom)
          mpRandom = CRandom::createGenerator();

        break;

      case S_MAX:
        mpFunction2 = max;
        break;

      case S_MIN:
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

bool CEvaluationNodeFunction::compile(const CEvaluationTree * /* pTree */)
{
  mpArgNode1 = static_cast<CEvaluationNode *>(getChild());

  if (mpArgNode1 == NULL) return false;

  mpArgValue1 = mpArgNode1->getValuePointer();

  if (mpFunction)
    return (mpArgNode1->getSibling() == NULL); // We must have only one child

  mpArgNode2 = static_cast<CEvaluationNode *>(mpArgNode1->getSibling());

  if (mpArgNode2 == NULL) return false;

  mpArgValue2 = mpArgNode2->getValuePointer();

  if (mpFunction2)
    return (mpArgNode2->getSibling() == NULL); // We must have exactly 1 children

  // equality
  mpArgNode3 = static_cast<CEvaluationNode *>(mpArgNode2->getSibling());

  if (mpArgNode3 == NULL) return false;

  mpArgValue3 = mpArgNode3->getValuePointer();

  mpArgNode4 = static_cast<CEvaluationNode *>(mpArgNode3->getSibling());

  if (mpArgNode4 == NULL) return false;

  mpArgValue4 = mpArgNode4->getValuePointer();

  return (mpArgNode4->getSibling() == NULL); // We must have exactly 4 children
}

// virtual
std::string CEvaluationNodeFunction::getInfix(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeFunction *>(this)->compile(NULL))
    switch (mSubType)
      {
        case S_MINUS:
        case S_PLUS:
          return handleSign(children[0]);

        case S_RUNIFORM:
        case S_RNORMAL:
        case S_RGAMMA:
        case S_MAX:
        case S_MIN:
          return mData + "(" + children[0] + "," + children[1] + ")";

        case S_RPOISSON:
          return mData + "(" + children[0] + ")";

        case S_NOT:
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
  if (const_cast<CEvaluationNodeFunction *>(this)->compile(NULL))
    switch (mSubType)
      {
        case S_MINUS:
        case S_PLUS:
          return handleSign(children[0]);

        case S_RUNIFORM:
        case S_RNORMAL:
        case S_RGAMMA:
        case S_MAX:
        case S_MIN:
          return mData + "(" + children[0] + "," + children[1] + ")";

        case S_RPOISSON:
          return mData + "(" + children[0] + ")";

        case S_NOT:
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
  if (const_cast<CEvaluationNodeFunction *>(this)->compile(NULL))
    {
      std::string data = "";

      switch ((SubType)this->subType())
        {
          case S_LOG:
            data = "log";
            break;

          case S_LOG10:
            data = "log10";
            break;

          case S_EXP:
            data = "exp";
            break;

          case S_SIN:
            data = "sin";
            break;

          case S_COS:
            data = "cos";
            break;

          case S_TAN:
            data = "tan";
            break;

          case S_SINH:
            data = "sinh";
            break;

          case S_COSH:
            data = "cosh";
            break;

          case S_TANH:
            data = "tanh";
            break;

          case S_ARCSIN:
            data = "asin";
            break;

          case S_ARCCOS:
            data = "acos";
            break;

          case S_ARCTAN:
            data = "atan";
            break;

          case S_ARCSINH:
            data = "asinh";
            break;

          case S_ARCCOSH:
            data = "acosh";
            break;

          case S_ARCTANH:
            data = "atanh";
            break;

          case S_SQRT:
            data = "sqrt";
            break;

          case S_ABS:
            data = "abs";
            break;

          case S_NOT:
            data = "!";
            break;

          case S_MINUS:
            data = "-";
            break;

          case S_PLUS:
            break;

          case S_SEC:
            data = "sec";
            break;

          case S_CSC:
            data = "csc";
            break;

          case S_COT:
            data = "cot";
            break;

          case S_SECH:
            data = "sech";
            break;

          case S_CSCH:
            data = "csch";
            break;

          case S_COTH:
            data = "coth";
            break;

          case S_ARCSEC:
            data = "arcsec";
            break;

          case S_ARCCSC:
            data = "arccsc";
            break;

          case S_ARCCOT:
            data = "arccot";
            break;

          case S_ARCSECH:
            data = "asech";
            break;

          case S_ARCCSCH:
            data = "acsch";
            break;

          case S_ARCCOTH:
            data = "acoth";
            break;

          case S_FLOOR:
            data = "floor";
            break;

          case S_CEIL:
            data = "ceil";
            break;

          case S_FACTORIAL:
            data = "factorial";
            break;

          case S_RUNIFORM:
            data = "user_provided_uniform";
            break;

          case S_RNORMAL:
            data = "user_provided_normal";
            break;

          case S_RGAMMA:
            data = "user_provided_normal";
            break;

          case S_RPOISSON:
            data = "user_provided_normal";
            break;

          case S_MAX:
            data = "max";
            break;

          case S_MIN:
            data = "min";
            break;

          default:
            data = "@";
            break;
        }

      switch (mSubType)
        {
          case S_MINUS:
            return "(" + data + children[0] + ")";
            break;

          case S_PLUS:
            //return handleSign(mpLeft->getDisplay_C_String(pTree));
            return children[0];
            break;

          case S_RUNIFORM:
          case S_RNORMAL:
          case S_RGAMMA:
          case S_MAX:
          case S_MIN:
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

  if (const_cast<CEvaluationNodeFunction *>(this)->compile(NULL))
    {
      data = mData;

      switch ((SubType)this->subType())
        {
          case S_LOG:
          case S_LOG10:
          case S_EXP:
          case S_SIN:
          case S_COS:
          case S_TAN:
          case S_SINH:
          case S_COSH:
          case S_TANH:
          case S_ARCSIN:
          case S_ARCCOS:
          case S_ARCTAN:
          case S_ARCSINH:
          case S_ARCCOSH:
          case S_ARCTANH:
          case S_SQRT:
          case S_ABS:
          case S_NOT:
            break;

          case S_MINUS:
            data = "-";
            break;

          case S_PLUS:
            data = "";
            break;

          case S_SEC:
          case S_CSC:
          case S_COT:
          case S_SECH:
          case S_CSCH:
          case S_COTH:
          case S_ARCSEC:
          case S_ARCCSC:
          case S_ARCCOT:
          case S_ARCSECH:
          case S_ARCCSCH:
          case S_ARCCOTH:
          case S_FLOOR:
          case S_CEIL:
          case S_FACTORIAL:
          case S_RUNIFORM:
          case S_RNORMAL:
          case S_RGAMMA:
          case S_RPOISSON:
          case S_MAX:
          case S_MIN:
          default:
            data = "ILLEGAL FUNCTION";
            break;
        }

      switch (mSubType)
        {
          case S_MINUS:
            return "(" + data + children[0] + ")";
            break;

          case S_PLUS:
            //return handleSign(mpLeft->getDisplay_MMD_String(pTree));
            return children[0];
            break;

          case S_RUNIFORM:
          case S_RNORMAL:
          case S_RGAMMA:
          case S_MAX:
          case S_MIN:
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

  if (const_cast<CEvaluationNodeFunction *>(this)->compile(NULL))
    {
      data = mData;

      switch ((SubType)this->subType())
        {
          case S_LOG:
          case S_LOG10:
          case S_EXP:
          case S_SIN:
          case S_COS:
          case S_TAN:
          case S_SINH:
          case S_COSH:
          case S_TANH:
          case S_ARCSIN:
          case S_ARCCOS:
          case S_ARCTAN:
          case S_SQRT:
          case S_ABS:
          case S_NOT:
          case S_PLUS:
            break;

          case S_MINUS:
            data = "-";
            break;

          case S_FLOOR:
            data = "flr";
            break;

          case S_CEIL:
            data = "ceil";
            break;

          case S_ARCSINH:
          case S_ARCCOSH:
          case S_ARCTANH:
          case S_SEC:
          case S_CSC:
          case S_COT:
          case S_SECH:
          case S_CSCH:
          case S_COTH:
          case S_ARCSEC:
          case S_ARCCSC:
          case S_ARCCOT:
          case S_ARCSECH:
          case S_ARCCSCH:
          case S_ARCCOTH:
          case S_FACTORIAL:
          case S_RUNIFORM:
          case S_RNORMAL:
          case S_RGAMMA:
          case S_RPOISSON:
          case S_MAX:
          case S_MIN:
          default:
            data = "@"; //TODO
            break;
        }

      switch (mSubType)
        {
          case S_MINUS:
            return "(" + data + children[0] + ")";
            break;

          case S_PLUS:
            return children[0];
            break;

          case S_RUNIFORM:
          case S_RNORMAL:
          case S_RGAMMA:
          case S_MAX:
          case S_MIN:
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
            pNode = new CEvaluationNodeFunction(S_SQRT, "sqrt");
            pNode->addChild(children[0]);
            break;

          case 2:
            /**
             * Replaces all root nodes with the corresponding power
             * operator since COPASI does not have the ROOT function.
             */
          {
            pNode = new CEvaluationNodeOperator(S_POWER, "^");
            pNode->addChild(children[1]); // Value
            CEvaluationNode * pExponent = new CEvaluationNodeOperator(S_DIVIDE, "/");
            pNode->addChild(pExponent);
            pExponent->addChild(new CEvaluationNodeNumber(S_DOUBLE, "1"));
            pExponent->addChild(children[0]); // Degree
          }
          break;
        }

      return pNode;
    }
  else if (type == AST_FUNCTION_LOG && iMax == 2)
    {
      /**
       * Replaces all LOG10 (AST_FUNCTION_LOG) nodes that have two
       * children with the quotient of two LOG10 nodes with the base
       * as the argument for the divisor LOG10 node.
       */

      CEvaluationNode * pNode = new CEvaluationNodeOperator(S_DIVIDE, "/");
      CEvaluationNode * pValue = new CEvaluationNodeFunction(S_LOG10, "log10");
      pValue->addChild(children[1]);
      CEvaluationNode * pBase = new CEvaluationNodeFunction(S_LOG10, "log10");
      pBase->addChild(children[0]);
      pNode->addChild(pValue);
      pNode->addChild(pBase);

      return pNode;
    }

  switch (type)
    {
      case AST_FUNCTION_ABS:
        subType = S_ABS;
        data = "abs";
        break;

      case AST_FUNCTION_ARCCOS:
        subType = S_ARCCOS;
        data = "acos";
        break;

      case AST_FUNCTION_ARCCOSH:
        subType = S_ARCCOSH;
        data = "arccosh";
        break;

      case AST_FUNCTION_ARCCOT:
        subType = S_ARCCOT;
        data = "arccot";
        break;

      case AST_FUNCTION_ARCCOTH:
        subType = S_ARCCOTH;
        data = "arccoth";
        break;

      case AST_FUNCTION_ARCCSC:
        subType = S_ARCCSC;
        data = "arccsc";
        break;

      case AST_FUNCTION_ARCCSCH:
        subType = S_ARCCSCH;
        data = "arccsch";
        break;

      case AST_FUNCTION_ARCSEC:
        subType = S_ARCSEC;
        data = "arcsec";
        break;

      case AST_FUNCTION_ARCSECH:
        subType = S_ARCSECH;
        data = "arcsech";
        break;

      case AST_FUNCTION_ARCSIN:
        subType = S_ARCSIN;
        data = "asin";
        break;

      case AST_FUNCTION_ARCSINH:
        subType = S_ARCSINH;
        data = "arcsinh";
        break;

      case AST_FUNCTION_ARCTAN:
        subType = S_ARCTAN;
        data = "atan";
        break;

      case AST_FUNCTION_ARCTANH:
        subType = S_ARCTANH;
        data = "arctanh";
        break;

      case AST_FUNCTION_CEILING:
        subType = S_CEIL;
        data = "ceil";
        break;

      case AST_FUNCTION_COS:
        subType = S_COS;
        data = "cos";
        break;

      case AST_FUNCTION_COSH:
        subType = S_COSH;
        data = "cosh";
        break;

      case AST_FUNCTION_COT:
        subType = S_COT;
        data = "cot";
        break;

      case AST_FUNCTION_COTH:
        subType = S_COTH;
        data = "coth";
        break;

      case AST_FUNCTION_CSC:
        subType = S_CSC;
        data = "csc";
        break;

      case AST_FUNCTION_CSCH:
        subType = S_CSCH;
        data = "csch";
        break;

      case AST_FUNCTION_EXP:
        subType = S_EXP;
        data = "exp";
        break;

      case AST_FUNCTION_FACTORIAL:
        subType = S_FACTORIAL;
        data = "factorial";
        break;

      case AST_FUNCTION_FLOOR:
        subType = S_FLOOR;
        data = "floor";
        break;

      case AST_FUNCTION_LN:
        subType = S_LOG;
        data = "log";
        break;

      case AST_FUNCTION_LOG:
        subType = S_LOG10;
        data = "log10";
        break;

      case AST_FUNCTION_SEC:
        subType = S_SEC;
        data = "sec";
        break;

      case AST_FUNCTION_SECH:
        subType = S_SECH;
        data = "sech";
        break;

      case AST_FUNCTION_SIN:
        subType = S_SIN;
        data = "sin";
        break;

      case AST_FUNCTION_SINH:
        subType = S_SINH;
        data = "sinh";
        break;

      case AST_FUNCTION_TAN:
        subType = S_TAN;
        data = "tan";
        break;

      case AST_FUNCTION_TANH:
        subType = S_TANH;
        data = "tanh";
        break;

      case AST_LOGICAL_NOT:
        subType = S_NOT;
        data = "not";
        break;

      default:
        subType = S_INVALID;
        fatalError();
        break;
    }

  assert(iMax == 1);
  CEvaluationNode * pNode = new CEvaluationNodeFunction(subType, data);

  if (!children.empty())
    pNode->addChild(children[0]);

  return pNode;
}

// virtual
bool CEvaluationNodeFunction::isBoolean() const
{
  switch (mSubType)
    {
      case S_NOT:
        return true;

      default:
        return false;
    }
}

ASTNode* CEvaluationNodeFunction::toAST(const CCopasiDataModel* pDataModel) const
{
  SubType subType = (SubType)this->subType();
  ASTNode* node = new ASTNode();
  bool needFirstArg = true;

  switch (subType)
    {
      case S_INVALID:
        break;

      case S_LOG:
        node->setType(AST_FUNCTION_LN);
        break;

      case S_LOG10:
      {
        // log 10 needs two children, the log and the base
        node->setType(AST_FUNCTION_LOG);

        ASTNode* logBase = new ASTNode();
        logBase->setType(AST_INTEGER);
        logBase->setValue(10);
        node->addChild(logBase);

        break;
      }

      case S_EXP:
        node->setType(AST_FUNCTION_EXP);
        break;

      case S_SIN:
        node->setType(AST_FUNCTION_SIN);
        break;

      case S_COS:
        node->setType(AST_FUNCTION_COS);
        break;

      case S_TAN:
        node->setType(AST_FUNCTION_TAN);
        break;

      case S_SEC:
        node->setType(AST_FUNCTION_SEC);
        break;

      case S_CSC:
        node->setType(AST_FUNCTION_CSC);
        break;

      case S_COT:
        node->setType(AST_FUNCTION_COT);
        break;

      case S_SINH:
        node->setType(AST_FUNCTION_SINH);
        break;

      case S_COSH:
        node->setType(AST_FUNCTION_COSH);
        break;

      case S_TANH:
        node->setType(AST_FUNCTION_TANH);
        break;

      case S_SECH:
        node->setType(AST_FUNCTION_SECH);
        break;

      case S_CSCH:
        node->setType(AST_FUNCTION_CSCH);
        break;

      case S_COTH:
        node->setType(AST_FUNCTION_COTH);
        break;

      case S_ARCSIN:
        node->setType(AST_FUNCTION_ARCSIN);
        break;

      case S_ARCCOS:
        node->setType(AST_FUNCTION_ARCCOS);
        break;

      case S_ARCTAN:
        node->setType(AST_FUNCTION_ARCTAN);
        break;

      case S_ARCSEC:
        node->setType(AST_FUNCTION_ARCSEC);
        break;

      case S_ARCCSC:
        node->setType(AST_FUNCTION_ARCCSC);
        break;

      case S_ARCCOT:
        node->setType(AST_FUNCTION_ARCCOT);
        break;

      case S_ARCSINH:
        node->setType(AST_FUNCTION_ARCSINH);
        break;

      case S_ARCCOSH:
        node->setType(AST_FUNCTION_ARCCOSH);
        break;

      case S_ARCTANH:
        node->setType(AST_FUNCTION_ARCTANH);
        break;

      case S_ARCSECH:
        node->setType(AST_FUNCTION_ARCSECH);
        break;

      case S_ARCCSCH:
        node->setType(AST_FUNCTION_ARCCSCH);
        break;

      case S_ARCCOTH:
        node->setType(AST_FUNCTION_ARCCOTH);
        break;

      case S_SQRT:
        node->setType(AST_FUNCTION_ROOT);
        break;

      case S_ABS:
        node->setType(AST_FUNCTION_ABS);
        break;

      case S_CEIL:
        node->setType(AST_FUNCTION_CEILING);
        break;

      case S_FLOOR:
        node->setType(AST_FUNCTION_FLOOR);
        break;

      case S_FACTORIAL:
        node->setType(AST_FUNCTION_FACTORIAL);
        break;

      case S_MINUS:
        node->setType(AST_MINUS);
        break;

      case S_PLUS:
        // if this is the unary plus as I suspect,
        // the node will be replaced by its only child
        delete node;
        node = dynamic_cast<const CEvaluationNode*>(this->getChild())->toAST(pDataModel);
        break;

      case S_NOT:
        node->setType(AST_LOGICAL_NOT);
        break;

      case S_RUNIFORM:
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

      case S_RNORMAL:
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

      case S_RGAMMA:
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

      case S_RPOISSON:
      {
        needFirstArg = false;
        node->setType(AST_FUNCTION);
        node->setName("RPOISSON");
        const CEvaluationNode* child = dynamic_cast<const CEvaluationNode*>(this->getChild());
        node->addChild(child->toAST(pDataModel));
      }
      break;

      case S_MAX:
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

      case S_MIN:
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

  if (subType != S_INVALID)
    {
      // the following is a workaround for a bug in libsbml 3.1.1 and 3.2.0
      // where libsbml does not handle the case correctly that a root
      // function can have one or two children (MathML.cpp in function
      // writeFunctionRoot)
      if (subType == S_SQRT)
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
      case S_MINUS:
      {
        switch (child1->mainType())
          {
            case CEvaluationNode::T_OPERATOR:
            {
              switch (child1->subType())
                {
                  case S_DIVIDE:
                  {
                    // -(a/b) -> (-a)/b
                    // want to recognize a fraction in a sum easily
                    CEvaluationNode *newnode = CEvaluationNode::create(T_OPERATOR, S_DIVIDE, "/");
                    CEvaluationNode *newchild1 = CEvaluationNode::create(T_FUNCTION, S_MINUS, "-");
                    CEvaluationNode *newchild2 = dynamic_cast<CEvaluationNode*>(child1->getChild()->getSibling())->copyBranch();
                    CEvaluationNode *grandchild = dynamic_cast<CEvaluationNode*>(child1->getChild())->copyBranch();
                    newnode->addChild(newchild1, NULL);
                    newnode->addChild(newchild2, newchild1);
                    newchild1->addChild(grandchild, NULL);
                    delete child1;
                    return newnode;
                  }

                  case S_PLUS:
                  {
                    // -(a+b) -> (-a)+(-b)
                    // negativity should be property of product
                    CEvaluationNode *newnode = CEvaluationNode::create(T_OPERATOR, S_PLUS, "+");
                    CEvaluationNode *newchild1 = CEvaluationNode::create(T_FUNCTION, S_MINUS, "-");
                    CEvaluationNode *newchild2 = CEvaluationNode::create(T_FUNCTION, S_MINUS, "-");
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

            case CEvaluationNode::T_FUNCTION:
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

            case CEvaluationNode::T_NUMBER:
            {
              std::stringstream tmp;
              tmp << *child1->getValuePointer() *(-1.0);
              CEvaluationNode* newnode = CEvaluationNode::create(T_NUMBER, S_DOUBLE, tmp.str());
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

      case S_SQRT:
      {
        // write as ^0.5
        CEvaluationNode* newnode = CEvaluationNode::create(T_OPERATOR, S_POWER, "^");
        CEvaluationNode* newchild2 = CEvaluationNode::create(T_NUMBER, S_DOUBLE, "0.5");
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

  if (T == T_OPERATOR)
    {
      Result = mData + "(" + str + ")";
    }
  else if (getParent() != NULL &&
           static_cast< const CEvaluationNode * >(getParent())->mainType() == T_OPERATOR &&
           static_cast< const CEvaluationNode * >(getParent())->subType() == S_POWER)
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

  if ((T & 0xFF000000) == T_LOGICAL)
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

#include "utilities/copasimathml.h"

// virtual
std::string CEvaluationNodeFunction::getMMLString(const std::vector< std::string > & children,
    bool expand,
    const std::vector< std::vector< std::string > > & /* variables */) const
{
  std::ostringstream out;

  std::string data = "";
  std::string ldata = "";
  std::string rdata = "";

  bool flag = ((mpArgNode1->mainType() == CEvaluationNode::T_NUMBER) ||
               (mpArgNode1->mainType() == CEvaluationNode::T_VARIABLE) ||
               (mpArgNode1->mainType() == CEvaluationNode::T_CONSTANT));

  bool flag1 = false;

  switch (mSubType)
    {
      case S_INVALID:
        data = "@";
        break;

      case S_LOG:
        data = "ln";
        break;

      case S_LOG10:
        break;

      case S_EXP:
        break;

      case S_SIN:
        data = "sin";
        break;

      case S_COS:
        data = "cos";
        break;

      case S_TAN:
        data = "tan";
        break;

      case S_SEC:
        data = "sec";
        break;

      case S_CSC:
        data = "csc";
        break;

      case S_COT:
        data = "cot";
        break;

      case S_SINH:
        data = "sinh";
        break;

      case S_COSH:
        data = "cosh";
        break;

      case S_TANH:
        data = "tanh";
        break;

      case S_SECH:
        data = "sech";
        break;

      case S_CSCH:
        data = "csch";
        break;

      case S_COTH:
        data = "coth";
        break;

      case S_ARCSIN:
        data = "arcsin";
        break;

      case S_ARCCOS:
        data = "arccos";
        break;

      case S_ARCTAN:
        data = "arctan";
        break;

      case S_ARCSEC:
        data = "arcsec";
        break;

      case S_ARCCSC:
        data = "arccsc";
        break;

      case S_ARCCOT:
        data = "arccot";
        break;

      case S_ARCSINH:
        data = "arcsinh";
        break;

      case S_ARCCOSH:
        data = "arccosh";
        break;

      case S_ARCTANH:
        data = "arctanh";
        break;

      case S_ARCSECH:
        data = "arcsech";
        break;

      case S_ARCCSCH:
        data = "arccsch";
        break;

      case S_ARCCOTH:
        data = "arccoth";
        break;

      case S_SQRT:
        ldata = "<msqrt>";
        rdata = "</msqrt>";
        break;

      case S_ABS:
        ldata = "|";
        rdata = "|";
        break;

      case S_SIGN:
        data = "sign";
        break;

      case S_CEIL:
        data = "ceil";
        break;

      case S_FLOOR:
        data = "floor";
        break;

      case S_FACTORIAL:
        break;

      case S_MINUS:
        break;

      case S_PLUS:
        break;

      case S_NOT:
        data = "!";
        break;
    }

  const CEvaluationNode * pParent = static_cast<const CEvaluationNode *>(getParent());

  out << "<mrow>" << std::endl;

  switch (mSubType)
    {
      case S_PLUS:
      {
        size_t type = (mpArgNode1->mainType() | mpArgNode1->subType());

        flag = ((type == (T_OPERATOR | S_PLUS))
                || (type == (T_OPERATOR | S_MINUS))
                || ((mpArgNode1->mainType() == T_CALL) && expand));
      }

      if (flag) out << "<mfenced>" << std::endl;

      out << children[0];

      if (flag) out << "</mfenced>" << std::endl;

      break;

      case S_MINUS:

        if (pParent != 0)
          {
            MainType T = pParent->mainType();

            flag1 = (T == T_OPERATOR &&
                     this == static_cast<const CEvaluationNode *>(pParent->getChild()->getSibling()));

            flag1 |= (T == (T_OPERATOR | S_POWER));

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

      case S_FACTORIAL:

        if (!flag) out << "<mfenced>" << std::endl;

        out << children[0];

        if (!flag) out << "</mfenced>" << std::endl;

        out << "<mo>" << "!" << "</mo>" << std::endl;

        break;

      case S_SQRT:
      case S_ABS:

        out << ldata << std::endl;

        out << children[0];

        out << rdata << std::endl;

        break;

      case S_EXP:

        out << "<msup>" << std::endl;
        out << "<mo> e  </mo>" << std::endl;

        out << children[0];

        out << "</msup>" << std::endl;

        break;

      case S_LOG10:

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

      case S_CEIL:
      case S_FLOOR:
        out << "<mi> " << data << " </mi>" << std::endl;

        out << "<mfenced>" << std::endl;

        out << children[0];

        out << "</mfenced>" << std::endl;

        break;

      case S_RUNIFORM:
      case S_RNORMAL:
      case S_RGAMMA:
      case S_MAX:
      case S_MIN:
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

      case S_RPOISSON:
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
      case S_LOG:
      case S_LOG10:
      case S_EXP:
      case S_SIN:
      case S_COS:
      case S_TAN:
      case S_SEC:
      case S_CSC:
      case S_COT:
      case S_SINH:
      case S_COSH:
      case S_TANH:
      case S_SECH:
      case S_CSCH:
      case S_COTH:
      case S_ARCSIN:
      case S_ARCCOS:
      case S_ARCTAN:
      case S_ARCSEC:
      case S_ARCCSC:
      case S_ARCCOT:
      case S_ARCSINH:
      case S_ARCCOSH:
      case S_ARCTANH:
      case S_ARCSECH:
      case S_ARCCSCH:
      case S_ARCCOTH:
      case S_FACTORIAL:
      case S_NOT:
        Unit = CValidatedUnit::merge(Unit, units[0]);
        break;

      case S_MAX:
      case S_MIN:
      case S_RUNIFORM:
      case S_RNORMAL:
        Unit = CValidatedUnit::merge(units[0], units[1]);
        break;

      case S_MINUS:
      case S_PLUS:
      case S_FLOOR:
      case S_CEIL:
      case S_ABS:
      case S_RPOISSON:
        Unit = units[0];

        break;

      case S_RGAMMA:
        // The unit of the gamma distribution is the inverse of the scale parameter (units[1])
        Unit = units[1].exponentiate(-1);

        // The shape parameter must be dimensionless
        if (!Unit.conflict())
          {
            Unit.setConflict(!(units[0] == CUnit(CBaseUnit::dimensionless)));
          }

        break;

      case S_SQRT:
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
    const std::map < CEvaluationNode * , CValidatedUnit > & currentUnits,
    std::map < CEvaluationNode * , CValidatedUnit > & targetUnits) const
{
  CValidatedUnit Result = CValidatedUnit::merge(currentUnits.find(const_cast< CEvaluationNodeFunction * >(this))->second,
                          targetUnits[const_cast< CEvaluationNodeFunction * >(this)]);

  switch ((SubType)this->subType())
    {
      case S_LOG:
      case S_LOG10:
      case S_EXP:
      case S_SIN:
      case S_COS:
      case S_TAN:
      case S_SEC:
      case S_CSC:
      case S_COT:
      case S_SINH:
      case S_COSH:
      case S_TANH:
      case S_SECH:
      case S_CSCH:
      case S_COTH:
      case S_ARCSIN:
      case S_ARCCOS:
      case S_ARCTAN:
      case S_ARCSEC:
      case S_ARCCSC:
      case S_ARCCOT:
      case S_ARCSINH:
      case S_ARCCOSH:
      case S_ARCTANH:
      case S_ARCSECH:
      case S_ARCCSCH:
      case S_ARCCOTH:
      case S_FACTORIAL:
      case S_NOT:
        targetUnits[mpArgNode1] = CValidatedUnit(CBaseUnit::dimensionless, false);
        break;

      case S_MAX:
      case S_MIN:
      case S_RUNIFORM:
      case S_RNORMAL:
        targetUnits[mpArgNode1] = Result;
        targetUnits[mpArgNode2] = Result;
        break;

      case S_MINUS:
      case S_PLUS:
      case S_FLOOR:
      case S_CEIL:
      case S_ABS:
      case S_RPOISSON:
        targetUnits[mpArgNode1] = Result;
        break;

      case S_RGAMMA:
        targetUnits[mpArgNode1] = CValidatedUnit(CBaseUnit::dimensionless, false);
        targetUnits[mpArgNode2] = Result.exponentiate(-1);

        break;

      case S_SQRT:
        targetUnits[mpArgNode1] = Result.exponentiate(2.0);
        break;

      default:
        Result.setConflict(true);
        break;
    }

  return Result;
}
