// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"

#include "CEvaluationNode.h"
#include <sstream>
#include "CEvaluationTree.h"

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
  CEvaluationNode(CEvaluationNode::INVALID, ""),
  mpFunction(NULL),
  mpFunction2(NULL),
  mpFunction4(NULL),
  mpArg1(NULL),
  mpArg2(NULL),
  mpArg3(NULL),
  mpArg4(NULL)
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeFunction::CEvaluationNodeFunction(const SubType & subType,
    const Data & data):
  CEvaluationNode((Type)(CEvaluationNode::FUNCTION | subType), data),
  mpFunction(NULL),
  mpFunction2(NULL),
  mpFunction4(NULL),
  mpArg1(NULL),
  mpArg2(NULL),
  mpArg3(NULL),
  mpArg4(NULL)
{
  switch (subType)
    {
      case LOG:
        mpFunction = log;
        break;

      case LOG10:
        mpFunction = log10;
        break;

      case EXP:
        mpFunction = exp;
        break;

      case SIN:
        mpFunction = sin;
        break;

      case COS:
        mpFunction = cos;
        break;

      case TAN:
        mpFunction = tan;
        break;

      case SEC:
        mpFunction = sec;
        break;

      case CSC:
        mpFunction = csc;
        break;

      case COT:
        mpFunction = cot;
        break;

      case SINH:
        mpFunction = sinh;
        break;

      case COSH:
        mpFunction = cosh;
        break;

      case TANH:
        mpFunction = tanh;
        break;

      case SECH:
        mpFunction = sech;
        break;

      case CSCH:
        mpFunction = csch;
        break;

      case COTH:
        mpFunction = coth;
        break;

      case ARCSIN:
        mpFunction = asin;
        break;

      case ARCCOS:
        mpFunction = acos;
        break;

      case ARCTAN:
        mpFunction = atan;
        break;

      case ARCSEC:
        mpFunction = arcsec;
        break;

      case ARCCSC:
        mpFunction = arccsc;
        break;

      case ARCCOT:
        mpFunction = arccot;
        break;

      case ARCSINH:
        mpFunction = asinh;
        break;

      case ARCCOSH:
        mpFunction = acosh;
        break;

      case ARCTANH:
        mpFunction = atanh;
        break;

      case ARCSECH:
        mpFunction = asech;
        break;

      case ARCCSCH:
        mpFunction = acsch;
        break;

      case ARCCOTH:
        mpFunction = acoth;
        break;

      case SQRT:
        mpFunction = sqrt;
        break;

      case ABS:
        mpFunction = fabs;
        break;

      case FLOOR:
        mpFunction = floor;
        break;

      case CEIL:
        mpFunction = ceil;
        break;

      case FACTORIAL:
        mpFunction = factorial;
        break;

      case MINUS:
        mpFunction = minus;
        break;

      case PLUS:
        mpFunction = plus;
        break;

      case NOT:
        mpFunction = copasiNot;
        break;

      case RUNIFORM:
        mpFunction2 = runiform;

        if (!mpRandom)
          mpRandom = CRandom::createGenerator();

        break;

      case RNORMAL:
        mpFunction2 = rnormal;

        if (!mpRandom)
          mpRandom = CRandom::createGenerator();

        break;

      case MAX:
        mpFunction2 = max;
        break;

      case MIN:
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
  mpArg1(NULL),
  mpArg2(NULL),
  mpArg3(NULL),
  mpArg4(NULL)
{}

CEvaluationNodeFunction::~CEvaluationNodeFunction() {}

bool CEvaluationNodeFunction::compile(const CEvaluationTree * /* pTree */)
{
  mpArg1 = static_cast<CEvaluationNode *>(getChild());

  if (mpArg1 == NULL) return false;

  if (mpFunction)
    return (mpArg1->getSibling() == NULL); // We must have only one child

  mpArg2 = static_cast<CEvaluationNode *>(mpArg1->getSibling());

  if (mpArg2 == NULL) return false;

  if (mpFunction2)
    return (mpArg2->getSibling() == NULL); // We must have exactly 1 children

  // equality
  mpArg3 = static_cast<CEvaluationNode *>(mpArg2->getSibling());

  if (mpArg3 == NULL) return false;

  mpArg4 = static_cast<CEvaluationNode *>(mpArg3->getSibling());

  if (mpArg4 == NULL) return false;

  return (mpArg4->getSibling() == NULL); // We must have exactly 4 children
}

// virtual
std::string CEvaluationNodeFunction::getInfix(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeFunction *>(this)->compile(NULL))
    switch (mType & 0x00FFFFFF)
      {
        case MINUS:
        case PLUS:
          return handleSign(children[0]);

        case RUNIFORM:
        case RNORMAL:
        case MAX:
        case MIN:
          return mData + "(" + children[0] + "," + children[1] + ")";

        case NOT:
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
    switch (mType & 0x00FFFFFF)
      {
        case MINUS:
        case PLUS:
          return handleSign(children[0]);

        case RUNIFORM:
        case RNORMAL:
        case MAX:
        case MIN:
          return mData + "(" + children[0] + "," + children[1] + ")";

        case NOT:
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

      switch ((SubType)CEvaluationNode::subType(this->getType()))
        {
          case LOG:
            data = "log";
            break;

          case LOG10:
            data = "log10";
            break;

          case EXP:
            data = "exp";
            break;

          case SIN:
            data = "sin";
            break;

          case COS:
            data = "cos";
            break;

          case TAN:
            data = "tan";
            break;

          case SINH:
            data = "sinh";
            break;

          case COSH:
            data = "cosh";
            break;

          case TANH:
            data = "tanh";
            break;

          case ARCSIN:
            data = "asin";
            break;

          case ARCCOS:
            data = "acos";
            break;

          case ARCTAN:
            data = "atan";
            break;

          case ARCSINH:
            data = "asinh";
            break;

          case ARCCOSH:
            data = "acosh";
            break;

          case ARCTANH:
            data = "atanh";
            break;

          case SQRT:
            data = "sqrt";
            break;

          case ABS:
            data = "abs";
            break;

          case NOT:
            data = "!";
            break;

          case MINUS:
            data = "-";
            break;

          case PLUS:
            break;

          case SEC:
            data = "sec";
            break;

          case CSC:
            data = "csc";
            break;

          case COT:
            data = "cot";
            break;

          case SECH:
            data = "sech";
            break;

          case CSCH:
            data = "csch";
            break;

          case COTH:
            data = "coth";
            break;

          case ARCSEC:
            data = "arcsec";
            break;

          case ARCCSC:
            data = "arccsc";
            break;

          case ARCCOT:
            data = "arccot";
            break;

          case ARCSECH:
            data = "asech";
            break;

          case ARCCSCH:
            data = "acsch";
            break;

          case ARCCOTH:
            data = "acoth";
            break;

          case FLOOR:
            data = "floor";
            break;

          case CEIL:
            data = "ceil";
            break;

          case FACTORIAL:
            data = "factorial";
            break;

          case RUNIFORM:
            data = "user_provided_uniform";
            break;

          case RNORMAL:
            data = "user_provided_normal";
            break;

          case MAX:
            data = "max";
            break;

          case MIN:
            data = "min";
            break;

          default:
            data = "@";
            break;
        }

      switch (mType & 0x00FFFFFF)
        {
          case MINUS:
            return "(" + data + children[0] + ")";
            break;

          case PLUS:
            //return handleSign(mpLeft->getDisplay_C_String(pTree));
            return children[0];
            break;

          case RUNIFORM:
          case RNORMAL:
          case MAX:
          case MIN:
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

      switch ((SubType)CEvaluationNode::subType(this->getType()))
        {
          case LOG:
          case LOG10:
          case EXP:
          case SIN:
          case COS:
          case TAN:
          case SINH:
          case COSH:
          case TANH:
          case ARCSIN:
          case ARCCOS:
          case ARCTAN:
          case ARCSINH:
          case ARCCOSH:
          case ARCTANH:
          case SQRT:
          case ABS:
          case NOT:
            break;

          case MINUS:
            data = "-";
            break;

          case PLUS:
            data = "";
            break;

          case SEC:
          case CSC:
          case COT:
          case SECH:
          case CSCH:
          case COTH:
          case ARCSEC:
          case ARCCSC:
          case ARCCOT:
          case ARCSECH:
          case ARCCSCH:
          case ARCCOTH:
          case FLOOR:
          case CEIL:
          case FACTORIAL:
          case RUNIFORM:
          case RNORMAL:
          case MAX:
          case MIN:
          default:
            data = "ILLEGAL FUNCTION";
            break;
        }

      switch (mType & 0x00FFFFFF)
        {
          case MINUS:
            return "(" + data + children[0] + ")";
            break;

          case PLUS:
            //return handleSign(mpLeft->getDisplay_MMD_String(pTree));
            return children[0];
            break;

          case RUNIFORM:
          case RNORMAL:
          case MAX:
          case MIN:
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

      switch ((SubType)CEvaluationNode::subType(this->getType()))
        {
          case LOG:
          case LOG10:
          case EXP:
          case SIN:
          case COS:
          case TAN:
          case SINH:
          case COSH:
          case TANH:
          case ARCSIN:
          case ARCCOS:
          case ARCTAN:
          case SQRT:
          case ABS:
          case NOT:
          case PLUS:
            break;

          case MINUS:
            data = "-";
            break;

          case FLOOR:
            data = "flr";
            break;

          case CEIL:
            data = "ceil";
            break;

          case ARCSINH:
          case ARCCOSH:
          case ARCTANH:
          case SEC:
          case CSC:
          case COT:
          case SECH:
          case CSCH:
          case COTH:
          case ARCSEC:
          case ARCCSC:
          case ARCCOT:
          case ARCSECH:
          case ARCCSCH:
          case ARCCOTH:
          case FACTORIAL:
          case RUNIFORM:
          case RNORMAL:
          case MAX:
          case MIN:
          default:
            data = "@"; //TODO
            break;
        }

      switch (mType & 0x00FFFFFF)
        {
          case MINUS:
            return "(" + data + children[0] + ")";
            break;

          case PLUS:
            return children[0];
            break;

          case RUNIFORM:
          case RNORMAL:
          case MAX:
          case MIN:
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
            pNode = new CEvaluationNodeFunction(CEvaluationNodeFunction::SQRT, "sqrt");
            pNode->addChild(children[0]);
            break;

          case 2:
            /**
             * Replaces all root nodes with the corresponding power
             * operator since COPASI does not have the ROOT function.
             */
          {
            pNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::POWER, "^");
            pNode->addChild(children[1]); // Value
            CEvaluationNode * pExponent = new CEvaluationNodeOperator(CEvaluationNodeOperator::DIVIDE, "/");
            pNode->addChild(pExponent);
            pExponent->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1"));
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

      CEvaluationNode * pNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::DIVIDE, "/");
      CEvaluationNode * pValue = new CEvaluationNodeFunction(CEvaluationNodeFunction::LOG10, "log10");
      pValue->addChild(children[1]);
      CEvaluationNode * pBase = new CEvaluationNodeFunction(CEvaluationNodeFunction::LOG10, "log10");
      pBase->addChild(children[0]);
      pNode->addChild(pValue);
      pNode->addChild(pBase);

      return pNode;
    }

  switch (type)
    {
      case AST_FUNCTION_ABS:
        subType = ABS;
        data = "abs";
        break;

      case AST_FUNCTION_ARCCOS:
        subType = ARCCOS;
        data = "acos";
        break;

      case AST_FUNCTION_ARCCOSH:
        subType = ARCCOSH;
        data = "arccosh";
        break;

      case AST_FUNCTION_ARCCOT:
        subType = ARCCOT;
        data = "arccot";
        break;

      case AST_FUNCTION_ARCCOTH:
        subType = ARCCOTH;
        data = "arccoth";
        break;

      case AST_FUNCTION_ARCCSC:
        subType = ARCCSC;
        data = "arccsc";
        break;

      case AST_FUNCTION_ARCCSCH:
        subType = ARCCSCH;
        data = "arccsch";
        break;

      case AST_FUNCTION_ARCSEC:
        subType = ARCSEC;
        data = "arcsec";
        break;

      case AST_FUNCTION_ARCSECH:
        subType = ARCSECH;
        data = "arcsech";
        break;

      case AST_FUNCTION_ARCSIN:
        subType = ARCSIN;
        data = "asin";
        break;

      case AST_FUNCTION_ARCSINH:
        subType = ARCSINH;
        data = "arcsinh";
        break;

      case AST_FUNCTION_ARCTAN:
        subType = ARCTAN;
        data = "atan";
        break;

      case AST_FUNCTION_ARCTANH:
        subType = ARCTANH;
        data = "arctanh";
        break;

      case AST_FUNCTION_CEILING:
        subType = CEIL;
        data = "ceil";
        break;

      case AST_FUNCTION_COS:
        subType = COS;
        data = "cos";
        break;

      case AST_FUNCTION_COSH:
        subType = COSH;
        data = "cosh";
        break;

      case AST_FUNCTION_COT:
        subType = COT;
        data = "cot";
        break;

      case AST_FUNCTION_COTH:
        subType = COTH;
        data = "coth";
        break;

      case AST_FUNCTION_CSC:
        subType = CSC;
        data = "csc";
        break;

      case AST_FUNCTION_CSCH:
        subType = CSCH;
        data = "csch";
        break;

      case AST_FUNCTION_EXP:
        subType = EXP;
        data = "exp";
        break;

      case AST_FUNCTION_FACTORIAL:
        subType = FACTORIAL;
        data = "factorial";
        break;

      case AST_FUNCTION_FLOOR:
        subType = FLOOR;
        data = "floor";
        break;

      case AST_FUNCTION_LN:
        subType = LOG;
        data = "log";
        break;

      case AST_FUNCTION_LOG:
        subType = LOG10;
        data = "log10";
        break;

      case AST_FUNCTION_SEC:
        subType = SEC;
        data = "sec";
        break;

      case AST_FUNCTION_SECH:
        subType = SECH;
        data = "sech";
        break;

      case AST_FUNCTION_SIN:
        subType = SIN;
        data = "sin";
        break;

      case AST_FUNCTION_SINH:
        subType = SINH;
        data = "sinh";
        break;

      case AST_FUNCTION_TAN:
        subType = TAN;
        data = "tan";
        break;

      case AST_FUNCTION_TANH:
        subType = TANH;
        data = "tanh";
        break;

      case AST_LOGICAL_NOT:
        subType = NOT;
        data = "not";
        break;

      default:
        subType = INVALID;
        fatalError();
        break;
    }

  assert(iMax == 1);
  CEvaluationNode * pNode = new CEvaluationNodeFunction(subType, data);
  pNode->addChild(children[0]);

  return pNode;
}

// virtual
bool CEvaluationNodeFunction::isBoolean() const
{
  switch ((SubType) CEvaluationNode::subType(mType))
    {
      case NOT:
        return true;

      default:
        return false;
    }
}

ASTNode* CEvaluationNodeFunction::toAST(const CCopasiDataModel* pDataModel) const
{
  SubType subType = (SubType)CEvaluationNode::subType(this->getType());
  ASTNode* node = new ASTNode();
  bool needFirstArg = true;

  switch (subType)
    {
      case INVALID:
        break;

      case LOG:
        node->setType(AST_FUNCTION_LN);
        break;

      case LOG10:
        node->setType(AST_FUNCTION_LOG);
        break;

      case EXP:
        node->setType(AST_FUNCTION_EXP);
        break;

      case SIN:
        node->setType(AST_FUNCTION_SIN);
        break;

      case COS:
        node->setType(AST_FUNCTION_COS);
        break;

      case TAN:
        node->setType(AST_FUNCTION_TAN);
        break;

      case SEC:
        node->setType(AST_FUNCTION_SEC);
        break;

      case CSC:
        node->setType(AST_FUNCTION_CSC);
        break;

      case COT:
        node->setType(AST_FUNCTION_COT);
        break;

      case SINH:
        node->setType(AST_FUNCTION_SINH);
        break;

      case COSH:
        node->setType(AST_FUNCTION_COSH);
        break;

      case TANH:
        node->setType(AST_FUNCTION_TANH);
        break;

      case SECH:
        node->setType(AST_FUNCTION_SECH);
        break;

      case CSCH:
        node->setType(AST_FUNCTION_CSCH);
        break;

      case COTH:
        node->setType(AST_FUNCTION_COTH);
        break;

      case ARCSIN:
        node->setType(AST_FUNCTION_ARCSIN);
        break;

      case ARCCOS:
        node->setType(AST_FUNCTION_ARCCOS);
        break;

      case ARCTAN:
        node->setType(AST_FUNCTION_ARCTAN);
        break;

      case ARCSEC:
        node->setType(AST_FUNCTION_ARCSEC);
        break;

      case ARCCSC:
        node->setType(AST_FUNCTION_ARCCSC);
        break;

      case ARCCOT:
        node->setType(AST_FUNCTION_ARCCOT);
        break;

      case ARCSINH:
        node->setType(AST_FUNCTION_ARCSINH);
        break;

      case ARCCOSH:
        node->setType(AST_FUNCTION_ARCCOSH);
        break;

      case ARCTANH:
        node->setType(AST_FUNCTION_ARCTANH);
        break;

      case ARCSECH:
        node->setType(AST_FUNCTION_ARCSECH);
        break;

      case ARCCSCH:
        node->setType(AST_FUNCTION_ARCCSCH);
        break;

      case ARCCOTH:
        node->setType(AST_FUNCTION_ARCCOTH);
        break;

      case SQRT:
        node->setType(AST_FUNCTION_ROOT);
        break;

      case ABS:
        node->setType(AST_FUNCTION_ABS);
        break;

      case CEIL:
        node->setType(AST_FUNCTION_CEILING);
        break;

      case FLOOR:
        node->setType(AST_FUNCTION_FLOOR);
        break;

      case FACTORIAL:
        node->setType(AST_FUNCTION_FACTORIAL);
        break;

      case MINUS:
        node->setType(AST_MINUS);
        break;

      case PLUS:
        // if this is the unary plus as I suspect,
        // the node will be replaced by its only child
        delete node;
        node = dynamic_cast<const CEvaluationNode*>(this->getChild())->toAST(pDataModel);
        break;

      case NOT:
        node->setType(AST_LOGICAL_NOT);
        break;

      case RUNIFORM:
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

      case RNORMAL:
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

      case MAX:
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

      case MIN:
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

  if (subType != INVALID)
    {
      // the following is a workaround for a bug in libsbml 3.1.1 and 3.2.0
      // where libsbml does not handle the case correctly that a root
      // function can have one or two children (MathML.cpp in function
      // writeFunctionRoot)
      if (subType == SQRT)
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

  switch (mType & 0x00FFFFFF)
    {
      case MINUS:
      {
        switch (CEvaluationNode::type(child1->getType()))
          {
            case CEvaluationNode::OPERATOR:
            {
              switch ((CEvaluationNodeOperator::SubType) CEvaluationNode::subType(child1->getType()))
                {
                  case CEvaluationNodeOperator::DIVIDE:
                  {
                    // -(a/b) -> (-a)/b
                    // want to recognize a fraction in a sum easily
                    CEvaluationNode *newnode = CEvaluationNode::create((Type)(OPERATOR | CEvaluationNodeOperator::DIVIDE), "/");
                    CEvaluationNode *newchild1 = CEvaluationNode::create((Type)(FUNCTION | MINUS), "-");
                    CEvaluationNode *newchild2 = dynamic_cast<CEvaluationNode*>(child1->getChild()->getSibling())->copyBranch();
                    CEvaluationNode *grandchild = dynamic_cast<CEvaluationNode*>(child1->getChild())->copyBranch();
                    newnode->addChild(newchild1, NULL);
                    newnode->addChild(newchild2, newchild1);
                    newchild1->addChild(grandchild, NULL);
                    delete child1;
                    return newnode;
                  }

                  case CEvaluationNodeOperator::PLUS:
                  {
                    // -(a+b) -> (-a)+(-b)
                    // negativity should be property of product
                    CEvaluationNode *newnode = CEvaluationNode::create((Type)(OPERATOR | CEvaluationNodeOperator::PLUS), "+");
                    CEvaluationNode *newchild1 = CEvaluationNode::create((Type)(FUNCTION | MINUS), "-");
                    CEvaluationNode *newchild2 = CEvaluationNode::create((Type)(FUNCTION | MINUS), "-");
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

            case CEvaluationNode::FUNCTION:
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

            case CEvaluationNode::NUMBER:
            {
              std::stringstream tmp;
              tmp << child1->getValue() *(-1.0);
              CEvaluationNode* newnode = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), tmp.str());
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

      case SQRT:
      {
        // write as ^0.5
        CEvaluationNode* newnode = CEvaluationNode::create((Type)(OPERATOR | CEvaluationNodeOperator::POWER), "^");
        CEvaluationNode* newchild2 = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), "0.5");
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

  Type T = mpArg1->getType();

  if ((T & 0xFF000000) == OPERATOR)
    {
      Result = mData + "(" + str + ")";
    }
  else if (getParent() != NULL &&
           static_cast< const CEvaluationNode * >(getParent())->getType() == (OPERATOR | CEvaluationNodeOperator::POWER))
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

  Type T = mpArg1->getType();

  if ((T & 0xFF000000) == LOGICAL)
    {
      Result += "(" + str + ")";
    }
  else
    Result += str;

  return Result;
}

CEvaluationNode * CEvaluationNodeFunction::getLeft()
{return mpArg1;}
const CEvaluationNode * CEvaluationNodeFunction::getLeft() const
{return mpArg1;}

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

  bool flag = ((CEvaluationNode::type(mpArg1->getType()) == CEvaluationNode::NUMBER) ||
               (CEvaluationNode::type(mpArg1->getType()) == CEvaluationNode::VARIABLE) ||
               (CEvaluationNode::type(mpArg1->getType()) == CEvaluationNode::CONSTANT));

  bool flag1 = false;

  switch (mType & 0x00FFFFFF)
    {
      case INVALID:
        data = "@";
        break;

      case LOG:
        data = "ln";
        break;

      case LOG10:
        break;

      case EXP:
        break;

      case SIN:
        data = "sin";
        break;

      case COS:
        data = "cos";
        break;

      case TAN:
        data = "tan";
        break;

      case SEC:
        data = "sec";
        break;

      case CSC:
        data = "csc";
        break;

      case COT:
        data = "cot";
        break;

      case SINH:
        data = "sinh";
        break;

      case COSH:
        data = "cosh";
        break;

      case TANH:
        data = "tanh";
        break;

      case SECH:
        data = "sech";
        break;

      case CSCH:
        data = "csch";
        break;

      case COTH:
        data = "coth";
        break;

      case ARCSIN:
        data = "arcsin";
        break;

      case ARCCOS:
        data = "arccos";
        break;

      case ARCTAN:
        data = "arctan";
        break;

      case ARCSEC:
        data = "arcsec";
        break;

      case ARCCSC:
        data = "arccsc";
        break;

      case ARCCOT:
        data = "arccot";
        break;

      case ARCSINH:
        data = "arcsinh";
        break;

      case ARCCOSH:
        data = "arccosh";
        break;

      case ARCTANH:
        data = "arctanh";
        break;

      case ARCSECH:
        data = "arcsech";
        break;

      case ARCCSCH:
        data = "arccsch";
        break;

      case ARCCOTH:
        data = "arccoth";
        break;

      case SQRT:
        ldata = "<msqrt>";
        rdata = "</msqrt>";
        break;

      case ABS:
        ldata = "|";
        rdata = "|";
        break;

      case CEIL:
        data = "ceil";
        break;

      case FLOOR:
        data = "floor";
        break;

      case FACTORIAL:
        break;

      case MINUS:
        break;

      case PLUS:
        break;

      case NOT:
        data = "!";
        break;
    }

  const CEvaluationNode * pParent = static_cast<const CEvaluationNode *>(getParent());

  out << "<mrow>" << std::endl;

  switch (mType & 0x00FFFFFF)
    {
      case PLUS:

        flag = ((mpArg1->getType() == (CEvaluationNode::OPERATOR | PLUS))
                || (mpArg1->getType() == (CEvaluationNode::OPERATOR | MINUS))
                || (((mpArg1->getType() & 0xFF000000) == CEvaluationNode::CALL) && expand));

        if (flag) out << "<mfenced>" << std::endl;

        out << children[0];

        if (flag) out << "</mfenced>" << std::endl;

        break;

      case MINUS:

        if (pParent != 0)
          {
            Type T = pParent->getType();

            flag1 = ((T & 0xFF000000) == OPERATOR &&
                     this == static_cast<const CEvaluationNode *>(pParent->getChild()->getSibling()));

            flag1 |= (T == (OPERATOR | CEvaluationNodeOperator::POWER));

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

      case FACTORIAL:

        if (!flag) out << "<mfenced>" << std::endl;

        out << children[0];

        if (!flag) out << "</mfenced>" << std::endl;

        out << "<mo>" << "!" << "</mo>" << std::endl;

        break;

      case SQRT:
      case ABS:

        out << ldata << std::endl;

        out << children[0];

        out << rdata << std::endl;

        break;

      case EXP:

        out << "<msup>" << std::endl;
        out << "<mo> e  </mo>" << std::endl;

        out << children[0];

        out << "</msup>" << std::endl;

        break;

      case LOG10:

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

      case CEIL:
      case FLOOR:
        out << "<mi> " << data << " </mi>" << std::endl;

        out << "<mfenced>" << std::endl;

        out << children[0];

        out << "</mfenced>" << std::endl;

        break;

      case RUNIFORM:
      case RNORMAL:
      case MAX:
      case MIN:
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
