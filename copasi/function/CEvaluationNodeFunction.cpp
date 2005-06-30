/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeFunction.cpp,v $
   $Revision: 1.22 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/30 13:50:14 $
   End CVS Header */

#include "copasi.h"

#include "mathematics.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"

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

std::string CEvaluationNodeFunction::getInfix() const
  {
    if (const_cast<CEvaluationNodeFunction *>(this)->compile(NULL))
      return mData + "(" + mpLeft->getInfix() + ")";
    else
      return "@";
  }

CEvaluationNode* CEvaluationNodeFunction::createNodeFromASTTree(const ASTNode& node)
{
  ASTNodeType_t type = node.getType();
  SubType subType;
  std::string data = "";
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
      data = "acosh";
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
      /*
      case AST_FUNCTION_ROOT:
          subType=ROOT;
          break;
          */
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
      break;
    }
  // all functions have one child
  // convert child and add the converted node as child
  // to the current node.
  CEvaluationNodeFunction* convertedNode = new CEvaluationNodeFunction(subType, data);
  if (subType != INVALID)
    {
      ASTNode* child = node.getLeftChild();
      CEvaluationNode* convertedChildNode = CEvaluationTree::convertASTNode(*child);
      convertedNode->addChild(convertedChildNode);
    }
  return convertedNode;
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
      // the nodde will be replaced by its only child
      delete node;
      node = dynamic_cast<CEvaluationNode*>(this->getChild())->toASTNode();
      break;
    case NOT:
      fatalError();
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
