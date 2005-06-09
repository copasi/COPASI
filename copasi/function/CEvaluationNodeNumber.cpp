/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeNumber.cpp,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/09 17:27:59 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"

#include "sbml/math/ASTNode.h"

#include <sstream>

CEvaluationNodeNumber::CEvaluationNodeNumber():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeNumber::CEvaluationNodeNumber(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::NUMBER | subType), data)
{
  char * end;
  const char * str = mData.c_str();

  switch (subType)
    {
    case DOUBLE:
    case INTEGER:
    case ENOTATION:
      mValue = strtod(str, NULL);
      break;

    case RATIONALE:
      str++; // Skip the '('
      mValue = strtod(str, &end);
      end++; // Skip the '/'
      mValue /= strtod(end, NULL);
      break;
    }

  mPrecedence = PRECEDENCE_NUMBER;
}

CEvaluationNodeNumber::CEvaluationNodeNumber(const CEvaluationNodeNumber & src):
    CEvaluationNode(src)
{}

CEvaluationNodeNumber::~CEvaluationNodeNumber() {}

CEvaluationNode* CEvaluationNodeNumber::createNodeFromASTTree(const ASTNode* node)
{
  ASTNodeType_t type = node->getType();
  std::stringstream ss;
  SubType subType;
  std::string data = "";
  switch (type)
    {
    case AST_INTEGER:
      subType = INTEGER;
      ss << node->getInteger();
      data = ss.str();
      break;
    case AST_REAL:
      subType = DOUBLE;
      ss << node->getReal();
      data = ss.str();
      break;
    case AST_REAL_E:
      subType = ENOTATION;
      ss << node->getReal();
      data = ss.str();
      break;
    case AST_RATIONAL:
      subType = RATIONALE;
      ss << "(" << node->getNumerator() << " / " << node->getDenominator() << ")";
      data = ss.str();
      break;
    default:
      subType = INVALID;
      break;
    }
  return new CEvaluationNodeNumber(subType, data);
}

ASTNode* CEvaluationNodeNumber::toASTNode()
{
  SubType subType = (SubType)CEvaluationNode::subType(this->getType());
  ASTNode* node = new ASTNode();
  double num1;
  double num2;
  char* end;
  const char * str = mData.c_str();

  switch (subType)
    {
    case DOUBLE:
      node->setType(AST_REAL);
      node->setValue(this->value());
      break;
    case INTEGER:
      node->setType(AST_INTEGER);
      node->setValue((long)this->value());
      break;
    case ENOTATION:
      node->setType(AST_REAL_E);
      num2 = floor(log10(this->value()));
      num1 = pow(10, log10(this->value()) - num2);
      node->setValue(num1, (long)num2);
      break;
    case RATIONALE:
      node->setType(AST_RATIONAL);
      str++; // Skip the '('
      num1 = strtod(str, &end);
      end++; // Skip the '/'
      num2 = strtod(end, NULL);
      node->setValue((long)num1, (long)num2);
      break;
    case INVALID:
      break;
    }
  return node;
}
