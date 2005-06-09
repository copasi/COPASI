/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeFunction.cpp,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/06/09 13:46:28 $
   End CVS Header */

#include "copasi.h"

#include "mathematics.h"
#include "CEvaluationNode.h"

#include "sbml/math/ASTNode.h"

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

CEvaluationNode* CEvaluationNodeFunction::createNodeFromASTTree(const ASTNode* node)
{
  ASTNodeType_t type = node->getType();
  SubType subType;
  std::string data = "";
  switch (type)
    {
    case AST_FUNCTION_ABS:
      subType = ABS;
      break;
    case AST_FUNCTION_ARCCOS:
      subType = ARCCOS;
      break;
    case AST_FUNCTION_ARCCOT:
      subType = ARCCOT;
      break;
    case AST_FUNCTION_ARCCOTH:
      subType = ARCCOTH;
      break;
    case AST_FUNCTION_ARCCSC:
      subType = ARCCSC;
      break;
    case AST_FUNCTION_ARCCSCH:
      subType = ARCCSCH;
      break;
    case AST_FUNCTION_ARCSEC:
      subType = ARCSEC;
      break;
    case AST_FUNCTION_ARCSECH:
      subType = ARCSECH;
      break;
    case AST_FUNCTION_ARCSIN:
      subType = ARCSIN;
      break;
    case AST_FUNCTION_ARCSINH:
      subType = ARCSINH;
      break;
    case AST_FUNCTION_ARCTAN:
      subType = ARCTAN;
      break;
    case AST_FUNCTION_ARCTANH:
      subType = ARCTANH;
      break;
      /*
      case AST_FUNCTION_CEILING:
      subType=ARCCOS;
      break;
      */
    case AST_FUNCTION_COS:
      subType = COS;
      break;
    case AST_FUNCTION_COSH:
      subType = COSH;
      break;
    case AST_FUNCTION_COT:
      subType = COT;
      break;
    case AST_FUNCTION_COTH:
      subType = COTH;
      break;
    case AST_FUNCTION_CSC:
      subType = CSC;
      break;
    case AST_FUNCTION_CSCH:
      subType = CSCH;
      break;
    case AST_FUNCTION_EXP:
      subType = EXP;
      break;
      /*
      case AST_FUNCTION_FACTORIAL:
          subType=ARCCOS;
          break;
          */
      /*
      case AST_FUNCTION_FLOOR:
          subType=FLOOR;
          break;
          */
    case AST_FUNCTION_LN:
      subType = LOG;
      break;
    case AST_FUNCTION_LOG:
      subType = LOG10;
      break;
      /*
      case AST_FUNCTION_ROOT:
          subType=ROOT;
          break;
          */
    case AST_FUNCTION_SEC:
      subType = SEC;
      break;
    case AST_FUNCTION_SECH:
      subType = SECH;
      break;
    case AST_FUNCTION_SIN:
      subType = SIN;
      break;
    case AST_FUNCTION_SINH:
      subType = SINH;
      break;
    case AST_FUNCTION_TAN:
      subType = TAN;
      break;
    case AST_FUNCTION_TANH:
      subType = TANH;
      break;
    default:
      subType = INVALID;
      break;
    }
  return new CEvaluationNodeFunction(subType, data);
}

ASTNode* CEvaluationNodeFunction::toASTNode()
{
  SubType subType = (SubType)CEvaluationNode::subType(this->getType());
  ASTNode* node = new ASTNode();
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
    case MINUS:
      node->setType(AST_MINUS);
      break;
    case PLUS:
      // if this is the unary plus as I suspect,
      // the nodde will be replaced by its only child
      delete node;
      node = dynamic_cast<CEvaluationNode*>(this->getChild())->toASTNode();
      break;
    }
  // for all but INVALID one child has to be converted
  if (subType != INVALID)
    {
      CEvaluationNode* child1 = dynamic_cast<CEvaluationNode*>(this->getChild());
      node->addChild(child1->toASTNode());
    }
  return node;
}
