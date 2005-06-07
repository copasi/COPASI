/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeFunction.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/07 14:41:50 $
   End CVS Header */

#include "copasi.h"

#include "mathematics.h"
#include "CEvaluationNode.h"

CEvaluationNodeFunction::CEvaluationNodeFunction():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeFunction::CEvaluationNodeFunction(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::FUNCTION | subType), data),
    mpFunction(NULL),
    mpLeft(NULL)
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

    case MINUS:
      mpFunction = minus;
      break;

    case PLUS:
      mpFunction = plus;
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
    mpFunction(src.mpFunction)
{}

CEvaluationNodeFunction::~CEvaluationNodeFunction() {}

bool CEvaluationNodeFunction::compile(const CEvaluationTree * /* pTree */)
{
  mpLeft = static_cast<CEvaluationNode *>(getChild());
  if (mpLeft == NULL) return false;

  return (mpLeft->getSibling() == NULL); // We must have only one child
}
