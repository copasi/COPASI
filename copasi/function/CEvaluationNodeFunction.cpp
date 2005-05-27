/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeFunction.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/27 21:00:58 $
   End CVS Header */

#include "copasi.h"

#include "mathematics.h"
#include "CEvaluationNode.h"

CEvaluationNodeFunction::CEvaluationNodeFunction():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{}

CEvaluationNodeFunction::CEvaluationNodeFunction(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::NUMBER | subType), data),
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
      mpFunction = sec;
      break;

    case SEC:
      mpFunction = NULL;
      break;

    case CSC:
      mpFunction = NULL;
      break;

    case COT:
      mpFunction = NULL;
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
      mpFunction = NULL;
      break;

    case CSCH:
      mpFunction = NULL;
      break;

    case COTH:
      mpFunction = NULL;
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
      mpFunction = NULL;
      break;

    case ARCCSC:
      mpFunction = NULL;
      break;

    case ARCCOT:
      mpFunction = NULL;
      break;

    case ARCSINH:
      mpFunction = NULL;
      break;

    case ARCCOSH:
      mpFunction = NULL;
      break;

    case ARCTANH:
      mpFunction = NULL;
      break;

    case ARCSECH:
      mpFunction = NULL;
      break;

    case ARCCSCH:
      mpFunction = NULL;
      break;

    case ARCCOTH:
      mpFunction = NULL;
      break;

    case SQRT:
      mpFunction = sqrt;
      break;

    case ABS:
      mpFunction = fabs;
      break;

    default:
      mpFunction = NULL;
      fatalError();
      break;
    }
}

CEvaluationNodeFunction::CEvaluationNodeFunction(const CEvaluationNodeFunction & src):
    CEvaluationNode(src),
    mpFunction(src.mpFunction)
{}

CEvaluationNodeFunction::~CEvaluationNodeFunction() {}

bool CEvaluationNodeFunction::compile()
{
  mpLeft = static_cast<CEvaluationNode *>(getChild());
  if (mpLeft == NULL) return false;

  return (mpLeft->getSibling() == NULL); // We must have only one child
}
