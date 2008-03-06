// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeOperator.cpp,v $
//   $Revision: 1.32 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/03/06 11:26:57 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

#include "copasi.h"
#include "CEvaluationNode.h"
#include <sstream>
#include "CEvaluationTree.h"
#include "sbml/math/ASTNode.h"

CEvaluationNodeOperator::CEvaluationNodeOperator():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{}

CEvaluationNodeOperator::CEvaluationNodeOperator(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::OPERATOR | subType), data),
    mpLeft(NULL),
    mpRight(NULL)
{
  switch (mType & 0x00FFFFFF)
    {
    case POWER:
      mPrecedence = PRECEDENCE_OPERATOR_POWER;
      break;

    case MULTIPLY:
      mPrecedence = PRECEDENCE_OPERATOR_MULTIPLY;
      break;

    case DIVIDE:
      mPrecedence = PRECEDENCE_OPERATOR_DIVIDE;
      break;

    case MODULUS:
      mPrecedence = PRECEDENCE_OPERATOR_MODULUS;
      break;

    case PLUS:
      mPrecedence = PRECEDENCE_OPERATOR_PLUS;
      break;

    case MINUS:
      mPrecedence = PRECEDENCE_OPERATOR_MINUS;
      break;

    default:
      break;
    }
}

CEvaluationNodeOperator::CEvaluationNodeOperator(const CEvaluationNodeOperator & src):
    CEvaluationNode(src)
{}

CEvaluationNodeOperator::~CEvaluationNodeOperator() {}

bool CEvaluationNodeOperator::compile(const CEvaluationTree * /* pTree */)
{
  mpLeft = static_cast<CEvaluationNode *>(getChild());
  if (mpLeft == NULL) return false;

  mpRight = static_cast<CEvaluationNode *>(mpLeft->getSibling());
  if (mpRight == NULL) return false;

  return (mpRight->getSibling() == NULL); // We must have only two children
}

std::string CEvaluationNodeOperator::getInfix() const
  {
    if (const_cast<CEvaluationNodeOperator *>(this)->compile(NULL))
      {
        Data Infix;

        if (*mpLeft < *(CEvaluationNode *)this)
          Infix = "(" + mpLeft->getInfix() + ")";
        else
          Infix = mpLeft->getInfix();

        Infix += mData;

        if (!(*(CEvaluationNode *)this < *mpRight))
          Infix += "(" + mpRight->getInfix() + ")";
        else
          Infix += mpRight->getInfix();

        return Infix;
      }
    else
      return "@";
  }

std::string CEvaluationNodeOperator::getDisplayString(const CEvaluationTree * pTree) const
  {
    if (const_cast<CEvaluationNodeOperator *>(this)->compile(NULL))
      {
        Data DisplayString;

        if (*mpLeft < *(CEvaluationNode *)this)
          DisplayString = "(" + mpLeft->getDisplayString(pTree) + ")";
        else
          DisplayString = mpLeft->getDisplayString(pTree);

        DisplayString += mData;

        if (!(*(CEvaluationNode *)this < *mpRight))
          DisplayString += "(" + mpRight->getDisplayString(pTree) + ")";
        else
          DisplayString += mpRight->getDisplayString(pTree);

        return DisplayString;
      }
    else
      return "@";
  }
std::string CEvaluationNodeOperator::getDisplay_C_String(const CEvaluationTree * pTree) const
  {
    if (const_cast<CEvaluationNodeOperator *>(this)->compile(NULL))
      {
        Data DisplayString;
        SubType subType = (SubType)CEvaluationNode::subType(this->getType());

        if (subType == POWER)
          DisplayString = "pow(";
        if (subType == MODULUS)
          DisplayString = "(int)";

        if (*mpLeft < *(CEvaluationNode *)this)
          DisplayString += "(" + mpLeft->getDisplay_C_String(pTree) + ")";
        else
          DisplayString += mpLeft->getDisplay_C_String(pTree);

        switch (subType)
          {
          case POWER:
            DisplayString += ",";
            break;
          case MODULUS:
            DisplayString += "%(int)";
            break;
          default:
            DisplayString += mData;
            break;
          }
        if (!(*(CEvaluationNode *)this < *mpRight))
          DisplayString += "(" + mpRight->getDisplay_C_String(pTree) + ")";
        else
          DisplayString += mpRight->getDisplay_C_String(pTree);

        if (subType == POWER)
          DisplayString += ")";

        return DisplayString;
      }
    else
      return "@";
  }

std::string CEvaluationNodeOperator::getDisplay_MMD_String(const CEvaluationTree * pTree) const
  {
    if (const_cast<CEvaluationNodeOperator *>(this)->compile(NULL))
      {
        std::string mdata = "";

        /* if ((SubType)CEvaluationNode::subType(this->getType()) == MODULUS)
        mdata = "@";
        else  */
        mdata = mData;

        Data DisplayString;

        if (*mpLeft < *(CEvaluationNode *)this)
          DisplayString = "(" + mpLeft->getDisplay_MMD_String(pTree) + ")";
        else
          DisplayString = mpLeft->getDisplay_MMD_String(pTree);

        DisplayString += mdata;

        if (!(*(CEvaluationNode *)this < *mpRight))
          DisplayString += "(" + mpRight->getDisplay_MMD_String(pTree) + ")";
        else
          DisplayString += mpRight->getDisplay_MMD_String(pTree);

        return DisplayString;
      }
    else
      return "@";
  }

std::string CEvaluationNodeOperator::getDisplay_XPP_String(const CEvaluationTree * pTree) const
  {
    if (const_cast<CEvaluationNodeOperator *>(this)->compile(NULL))
      {
        Data DisplayString;
        SubType subType = (SubType)CEvaluationNode::subType(this->getType());

        if (subType == MODULUS)
          DisplayString = "mod(";

        if (*mpLeft < *(CEvaluationNode *)this)
          DisplayString += "(" + mpLeft->getDisplay_XPP_String(pTree) + ")";
        else
          DisplayString += mpLeft->getDisplay_XPP_String(pTree);

        switch (subType)
          {
          case MODULUS:
            DisplayString += ",";
            break;
          default:
            DisplayString += mData;
            break;
          }
        if (!(*(CEvaluationNode *)this < *mpRight))
          DisplayString += "(" + mpRight->getDisplay_XPP_String(pTree) + ")";
        else
          DisplayString += mpRight->getDisplay_XPP_String(pTree);

        if (subType == MODULUS)
          DisplayString += ")";

        return DisplayString;
      }
    else
      return "@"; //TODO
  }

CEvaluationNode* CEvaluationNodeOperator::createNodeFromASTTree(const ASTNode& node)
{
  ASTNodeType_t type = node.getType();
  SubType subType;
  std::string data = "";
  switch (type)
    {
    case AST_PLUS:
      subType = PLUS;
      data = "+";
      break;
    case AST_MINUS:
      subType = MINUS;
      data = "-";
      break;
    case AST_TIMES:
      subType = MULTIPLY;
      data = "*";
      break;
    case AST_DIVIDE:
      subType = DIVIDE;
      data = "/";
      break;
    case AST_POWER:
    case AST_FUNCTION_POWER:
      subType = POWER;
      data = "^";
      break;
    default:
      subType = INVALID;
      fatalError();
      break;
    }
  CEvaluationNode* convertedNode = new CEvaluationNodeOperator(subType, data);

  // handle "-" since it can be unary or binary
  if (type == AST_MINUS)
    {
      switch (node.getNumChildren())
        {
        case 1:
          delete convertedNode;
          convertedNode = new CEvaluationNodeFunction(CEvaluationNodeFunction::MINUS, data);
          convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getLeftChild()));
          break;
        case 2:
          convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getLeftChild()));
          convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getRightChild()));
          break;
        default:
          // error
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCMathML + 3);
          break;
        }
    }
  // handle binary operators (POWER,/)
  else if (type == AST_DIVIDE || type == AST_POWER || type == AST_FUNCTION_POWER)
    {
      switch (node.getNumChildren())
        {
        case 2:
          convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getLeftChild()));
          convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getRightChild()));
          break;
        default:
          // error
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCMathML + 4);
          break;
        }
    }
  // handle n-ary operators (+,*)
  else if (type == AST_PLUS || type == AST_TIMES)
    {
      unsigned int numChildren = node.getNumChildren();
      unsigned int i;
      CEvaluationNodeOperator* pTmpNode;
      switch (numChildren)
        {
        case 0:
          // replace the current node with the identity node
          delete convertedNode;
          if (type == AST_PLUS)
            {
              convertedNode = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "0.0");
            }
          else
            {
              convertedNode = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "1.0");
            }
          break;
        case 1:
          // replace the current node with its only child
          delete convertedNode;
          convertedNode = CEvaluationTree::convertASTNode(*node.getLeftChild());
          break;
        case 2:
          convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getLeftChild()));
          convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getRightChild()));
          break;
        default:
          convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getLeftChild()));
          pTmpNode = dynamic_cast<CEvaluationNodeOperator*>(convertedNode);
          for (i = 1; i < numChildren;++i)
            {
              pTmpNode->addChild(new CEvaluationNodeOperator((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pTmpNode->getType()), pTmpNode->getData()));
              pTmpNode = dynamic_cast<CEvaluationNodeOperator*>(pTmpNode->getChild()->getSibling());
              assert(pTmpNode);
              pTmpNode->addChild(CEvaluationTree::convertASTNode(*node.getChild(i)));
            }
          break;
        }
    }
  return convertedNode;
}

ASTNode* CEvaluationNodeOperator::toAST() const
  {
    SubType subType = (SubType)CEvaluationNode::subType(this->getType());
    ASTNode* node = new ASTNode();
    switch (subType)
      {
      case POWER:
        node->setType(AST_POWER);
        break;
      case MULTIPLY:
        node->setType(AST_TIMES);
        break;
      case DIVIDE:
        node->setType(AST_DIVIDE);
        break;
      case MODULUS:
        // replace this with a more complex subtree
        CEvaluationNodeOperator::createModuloTree(this, node);
        break;
      case PLUS:
        node->setType(AST_PLUS);
        break;
      case MINUS:
        node->setType(AST_MINUS);
        break;
      case INVALID:
        break;
      }
    // for all but INVALID and MODULUS two children have to be converted
    if (subType != INVALID && subType != MODULUS)
      {
        const CEvaluationNode* child1 = dynamic_cast<const CEvaluationNode*>(this->getChild());
        const CEvaluationNode* child2 = dynamic_cast<const CEvaluationNode*>(child1->getSibling());
        node->addChild(child1->toAST());
        node->addChild(child2->toAST());
      }
    return node;
  }

/*
CEvaluationNode* CEvaluationNodeOperator::simplifyNode(CEvaluationNode *child1, CEvaluationNode *child2) const
{
    std::vector<CEvaluationNode*> children;
    children.push_back(child1);
    children.push_back(child1);
    return this->simplifyNode(children);
}
 */

CEvaluationNode* CEvaluationNodeOperator::simplifyNode(const std::vector<CEvaluationNode*>& children) const
  {
    assert(children.size() > 0);
    CEvaluationNode* child1 = children[0];
    CEvaluationNode* child2 = NULL;
    if (children.size() > 1)
      {
        child2 = children[1];
      }
    switch (CEvaluationNode::subType(mType))
      {
      case POWER:
        {
          if (CEvaluationNode::type(child2->getType()) == NUMBER)
            {
              if (CEvaluationNode::type(child1->getType()) == NUMBER)
                {// both children numbers ->calculate
                  std::stringstream tmp;
                  tmp.precision(18);
                  tmp << pow(child1->value(), child2->value());
                  CEvaluationNode *newnode = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), tmp.str());
                  delete child1;
                  delete child2;
                  return newnode;
                }
              if (fabs(child2->value() - 1.0) < 1.0E-100)
                {// a^1 -> a
                  delete child2;
                  return child1;
                }
              if (fabs(child2->value()) < 1.0E-100)
                {// a^0 -> 1
                  CEvaluationNode* newnode = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), "1.0");
                  delete child1;
                  delete child2;
                  return newnode;
                }
              if (child2->value() < 0.0)
                {//negative float exponent ->write as fraction
                  CEvaluationNode* newnode = CEvaluationNode::create((Type)(OPERATOR | DIVIDE), "/");
                  CEvaluationNode* newchild1 = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), "1.0");
                  CEvaluationNode* newchild2 = CEvaluationNode::create((Type)(OPERATOR | POWER), "^");
                  CEvaluationNode* grandchild1 = child1;
                  std::stringstream tmp;
                  tmp.precision(18);
                  tmp << fabs(child2->value());
                  CEvaluationNode* grandchild2 = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), tmp.str());
                  newnode->addChild(newchild1, NULL);
                  newnode->addChild(newchild2, newchild1);
                  newchild2->addChild(grandchild1, NULL);
                  newchild2->addChild(grandchild2, grandchild1);
                  delete child2;
                  return newnode;
                }
              if ((child1->getType() == (CEvaluationNode::Type)(FUNCTION | CEvaluationNodeFunction::MINUS))
                  && ((fabs(child2->value() - floor(child2->value())) < 1.0E-100) || (fabs(child2->value() - floor(child2->value()) - 1.0) < 1.0E-100)))
                {// (-a)^n -> (-1)^n * a^n  for n int
                  // make negativity a property of product,
                  // easier to recognize a negative exponent.
                  int exp;
                  if (fabs(child2->value() - floor(child2->value())) < 1.0E-100)
                    exp = (int) floor(child2->value());
                  else
                    exp = (int) floor(child2->value()) + 1;

                  CEvaluationNode* newpower = CEvaluationNode::create((Type)(OPERATOR | POWER), "^");
                  CEvaluationNode* newchild1 = dynamic_cast<CEvaluationNode*>(child1->getChild())->copyBranch();
                  newpower->addChild(newchild1, NULL);
                  newpower->addChild(child2, newchild1);
                  delete child1;

                  if (pow(-1.0, exp) == 1.0)
                    return newpower;
                  CEvaluationNode* newnode = CEvaluationNode::create((Type)(FUNCTION | CEvaluationNodeFunction::MINUS), "-");
                  newnode->addChild(newpower, NULL);
                  return newnode;
                }
            }
          if (child1->getData() == "^")
            {// (a^b)^c -> a^(b*c)
              CEvaluationNode* newnode = CEvaluationNode::create((Type)(OPERATOR | POWER), "^");
              CEvaluationNode* newchild1 = dynamic_cast<CEvaluationNode*>(child1->getChild())->copyBranch();
              CEvaluationNode* newchild2 = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
              CEvaluationNode* grandchild1 = dynamic_cast<CEvaluationNode*>(child1->getChild()->getSibling())->copyBranch();
              CEvaluationNode* grandchild2 = child2;
              newnode->addChild(newchild1, NULL);
              newnode->addChild(newchild2, newchild1);
              newchild2->addChild(grandchild1, NULL);
              newchild2->addChild(grandchild2, grandchild1);
              delete child1;
              return newnode;
            }
          /* disable this since negative exponents are actually generated
             during the simplification. the normalization should get rid of
             those.
          if (child2->getType() == (Type)(FUNCTION | CEvaluationNodeFunction::MINUS))
            {// a^(-b) -> 1/(a^b)
              // don't want negative exponents
              CEvaluationNode* newnode = CEvaluationNode::create((Type)(OPERATOR | DIVIDE), "/");
              CEvaluationNode* newchild1 = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), "1.0");
              CEvaluationNode* newchild2 = CEvaluationNode::create((Type)(OPERATOR | POWER), "^");
              CEvaluationNode* grandchild1 = child1;
              CEvaluationNode* grandchild2 = dynamic_cast<CEvaluationNode*>(child2->getChild())->copyBranch();
              newnode->addChild(newchild1, NULL);
              newnode->addChild(newchild2, newchild1);
              newchild2->addChild(grandchild1, NULL);
              newchild2->addChild(grandchild2, grandchild1);
              delete child2;
              return newnode;
            }
          */
          if (child1->getData() == "*")
            {// (a*b)^c -> a^c * b^c
              CEvaluationNode* newnode = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
              CEvaluationNode* newchild1 = CEvaluationNode::create((Type)(OPERATOR | POWER), "^");
              CEvaluationNode* newchild2 = CEvaluationNode::create((Type)(OPERATOR | POWER), "^");
              CEvaluationNode * grandchild1 = dynamic_cast<CEvaluationNode*>(child1->getChild())->copyBranch();
              CEvaluationNode * grandchild2 = child2->copyBranch();
              CEvaluationNode * grandchild3 = dynamic_cast<CEvaluationNode*>(child1->getChild()->getSibling())->copyBranch();
              CEvaluationNode * grandchild4 = child2;
              newnode->addChild(newchild1, NULL);
              newnode->addChild(newchild2, newchild1);
              newchild1->addChild(grandchild1, NULL);
              newchild1->addChild(grandchild2, grandchild1);
              newchild2->addChild(grandchild3, NULL);
              newchild2->addChild(grandchild4, grandchild3);
              delete child1;
              return newnode;
            }

          if (child1->getData() == "/")
            {// (a/b)^c -> a^c/b^c
              CEvaluationNode* newnode = CEvaluationNode::create((Type)(OPERATOR | DIVIDE), "/");
              CEvaluationNode* newchild1 = CEvaluationNode::create((Type)(OPERATOR | POWER), "^");
              CEvaluationNode* newchild2 = CEvaluationNode::create((Type)(OPERATOR | POWER), "^");
              CEvaluationNode * grandchild1 = dynamic_cast<CEvaluationNode*>(child1->getChild())->copyBranch();
              CEvaluationNode * grandchild2 = child2->copyBranch();
              CEvaluationNode * grandchild3 = dynamic_cast<CEvaluationNode*>(child1->getChild()->getSibling())->copyBranch();
              CEvaluationNode * grandchild4 = child2;
              newnode->addChild(newchild1, NULL);
              newnode->addChild(newchild2, newchild1);
              newchild1->addChild(grandchild1, NULL);
              newchild1->addChild(grandchild2, grandchild1);
              newchild2->addChild(grandchild3, NULL);
              newchild2->addChild(grandchild4, grandchild3);
              delete child1;
              return newnode;
            }
          /*
          if ((child1->getData() == "+") && (CEvaluationNode::type(child2->getType()) == NUMBER) && (child2->value() >= 1.0 + 1.0E-100))
            {// (a+b)^x -> (a+b) * (a+b)^(x-1)  for real x > 1
              // this is expanded step by step
              CEvaluationNode* newnode = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
              CEvaluationNode* newchild1 = child1->copyBranch();
              CEvaluationNode* newchild2 = CEvaluationNode::create((Type)(OPERATOR | POWER), "^");
              CEvaluationNode * grandchild1 = child1;
              std::stringstream tmp;
              tmp.precision(18);
              tmp << child2->value() - 1.0;
              CEvaluationNode * grandchild2 = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), tmp.str());
              newnode->addChild(newchild1, NULL);
              newnode->addChild(newchild2, newchild1);
              newchild2->addChild(grandchild1, NULL);
              newchild2->addChild(grandchild2, grandchild1);
              delete child2;
              return newnode;
            }
            // don't do this during the simplification. This has to be done
            // during the normalization
          if (child2->getData() == "+")
            {// a^(b+c) -> a^b*a^c   minimize exponent
              CEvaluationNode* newnode = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
              CEvaluationNode* newchild1 = CEvaluationNode::create((Type)(OPERATOR | POWER), "^");
              CEvaluationNode* newchild2 = CEvaluationNode::create((Type)(OPERATOR | POWER), "^");
              CEvaluationNode * grandchild1 = child1->copyBranch();
              CEvaluationNode * grandchild2 = dynamic_cast<CEvaluationNode*>(child2->getChild())->copyBranch();
              CEvaluationNode * grandchild3 = child1;
              CEvaluationNode * grandchild4 = dynamic_cast<CEvaluationNode*>(child2->getChild()->getSibling())->copyBranch();
              newnode->addChild(newchild1, NULL);
              newnode->addChild(newchild2, newchild1);
              newchild1->addChild(grandchild1, NULL);
              newchild1->addChild(grandchild2, grandchild1);
              newchild2->addChild(grandchild3, NULL);
              newchild2->addChild(grandchild4, grandchild3);
              delete child2;
              return newnode;
            }
            */
          CEvaluationNode *newnode = copyNode(child1, child2);
          return newnode;
        }

      case MULTIPLY:
        {
          if (CEvaluationNode::type(child1->getType()) == NUMBER)
            {
              if (CEvaluationNode::type(child2->getType()) == NUMBER)
                {// both children numbers ->calculate
                  std::stringstream tmp;
                  tmp.precision(18);
                  tmp << child1->value() * child2->value();
                  CEvaluationNode *newnode = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), tmp.str());
                  delete child1;
                  delete child2;
                  return newnode;
                }
              if (fabs(child1->value()) < 1.0E-100)
                {// 0*a -> 0
                  CEvaluationNode *newnode = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), "0.0");
                  delete child1;
                  delete child2;
                  return newnode;
                }
              if (fabs(child1->value() - 1.0) < 1.0E-100)
                {// 1*a -> a
                  delete child1;
                  return child2;
                }
              if (child1->value() < 0.0)
                {// x*a -> -(|x|*a)  x < 0
                  //  make negativity a property of product,
                  // easier to recognize a negative exponent.
                  CEvaluationNode *newnode = CEvaluationNode::create((Type)(FUNCTION | CEvaluationNodeFunction::MINUS), "-");
                  CEvaluationNode *newchild1 = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
                  std::stringstream tmp;
                  tmp.precision(18);
                  tmp << fabs(child1->value());
                  CEvaluationNode *grandchild1 = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), tmp.str());
                  CEvaluationNode *grandchild2 = child2;
                  newnode->addChild(newchild1, NULL);
                  newchild1->addChild(grandchild1, NULL);
                  newchild1->addChild(grandchild2, grandchild1);
                  delete child1;
                  return newnode;
                }
            }
          if (CEvaluationNode::type(child2->getType()) == NUMBER)
            {// because of commutativity the same as before for child1.
              if (fabs(child2->value()) < 1.0E-100)
                {// a*0 -> 0
                  CEvaluationNode *newnode = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), "0.0");
                  delete child1;
                  delete child2;
                  return newnode;
                }
              if (fabs(child2->value() - 1.0) < 1.0E-100)
                {// a*1 -> a
                  delete child2;
                  return child1;
                }
              if (child2->value() < 0.0)
                {// a*x -> -(a*|x|)  for x < 0
                  CEvaluationNode *newnode = CEvaluationNode::create((Type)(FUNCTION | CEvaluationNodeFunction::MINUS), "-");
                  CEvaluationNode *newchild1 = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
                  std::stringstream tmp;
                  tmp.precision(18);
                  tmp << fabs(child2->value());
                  CEvaluationNode *grandchild1 = child1;
                  CEvaluationNode *grandchild2 = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), tmp.str());
                  newnode->addChild(newchild1, NULL);
                  newchild1->addChild(grandchild1, NULL);
                  newchild1->addChild(grandchild2, grandchild1);
                  delete child2;
                  return newnode;
                }
            }
          if (child1->getData() == "/")
            {
              if (child2->getData() == "/")
                {// (a/b)*(c/d) -> (a*d)/(b*c)
                  // this rule is actually already executed by the following two rules, but more efficiently this way
                  CEvaluationNode * newnode = CEvaluationNode::create((Type)(OPERATOR | DIVIDE), "/");
                  CEvaluationNode * newchild1 = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
                  CEvaluationNode * newchild2 = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
                  CEvaluationNode * grandchild1 = dynamic_cast<CEvaluationNode*>(child1->getChild())->copyBranch();
                  CEvaluationNode * grandchild2 = dynamic_cast<CEvaluationNode*>(child2->getChild())->copyBranch();
                  CEvaluationNode * grandchild3 = dynamic_cast<CEvaluationNode*>(child1->getChild()->getSibling())->copyBranch();
                  CEvaluationNode * grandchild4 = dynamic_cast<CEvaluationNode*>(child2->getChild()->getSibling())->copyBranch();
                  newnode->addChild(newchild1, NULL);
                  newnode->addChild(newchild2, newchild1);
                  newchild1->addChild(grandchild1, NULL);
                  newchild1->addChild(grandchild2, grandchild1);
                  newchild2->addChild(grandchild3, NULL);
                  newchild2->addChild(grandchild4, grandchild3);
                  delete child1;
                  delete child2;
                  return newnode;
                }
              // (a/b) * c  ->  (a*c)/b
              CEvaluationNode * newnode = CEvaluationNode::create((Type)(OPERATOR | DIVIDE), "/");
              CEvaluationNode * newchild1 = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
              CEvaluationNode * newchild2 = dynamic_cast<CEvaluationNode*>(child1->getChild()->getSibling())->copyBranch();
              CEvaluationNode * grandchild1 = dynamic_cast<CEvaluationNode*>(child1->getChild())->copyBranch();
              CEvaluationNode * grandchild2 = child2;
              newnode->addChild(newchild1, NULL);
              newnode->addChild(newchild2, newchild1);
              newchild1->addChild(grandchild1, NULL);
              newchild1->addChild(grandchild2, grandchild1);
              delete child1;
              return newnode;
            }
          if (child2->getData() == "/")
            {// a * (b/c) -> (a*b)/c
              CEvaluationNode * newnode = CEvaluationNode::create((Type)(OPERATOR | DIVIDE), "/");
              CEvaluationNode * newchild1 = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
              CEvaluationNode * newchild2 = dynamic_cast<CEvaluationNode*>((child2->getChild())->getSibling())->copyBranch();
              CEvaluationNode * grandchild1 = child1;
              CEvaluationNode * grandchild2 = dynamic_cast<CEvaluationNode*>(child2->getChild())->copyBranch();
              newnode->addChild(newchild1, NULL);
              newnode->addChild(newchild2, newchild1);
              newchild1->addChild(grandchild1, NULL);
              newchild1->addChild(grandchild2, grandchild1);
              delete child2;
              return newnode;
            }
          if (CEvaluationNode::type(child1->getType()) == (Type)(FUNCTION | CEvaluationNodeFunction::MINUS))
            {// (-a) * b -> -(a*b)
              // make negativity a property of product
              CEvaluationNode* newnode = CEvaluationNode::create((Type)(FUNCTION | CEvaluationNodeFunction::MINUS), "-");
              CEvaluationNode* newchild1 = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
              CEvaluationNode* grandchild1 = dynamic_cast<CEvaluationNode*>(child1->getChild())->copyBranch();
              CEvaluationNode* grandchild2 = child2;
              newnode->addChild(newchild1, NULL);
              newchild1->addChild(grandchild1, NULL);
              newchild1->addChild(grandchild2, grandchild1);
              delete child1;
              return newnode;
            }
          if (CEvaluationNode::type(child2->getType()) == (Type)(FUNCTION | CEvaluationNodeFunction::MINUS))
            {// a*(-b) -> -(a*b)
              // make negativity a property of product,
              // easier to recognize a negative exponent.
              CEvaluationNode* newnode = CEvaluationNode::create((Type)(FUNCTION | CEvaluationNodeFunction::MINUS), "-");
              CEvaluationNode* newchild1 = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
              CEvaluationNode* grandchild1 = child1;
              CEvaluationNode* grandchild2 = dynamic_cast<CEvaluationNode*>(child2->getChild())->copyBranch();
              newnode->addChild(newchild1, NULL);
              newchild1->addChild(grandchild1, NULL);
              newchild1->addChild(grandchild2, grandchild1);
              delete child2;
              return newnode;
            }
          if (child1->getData() == "+")
            {// expand (a+b)*c -> a*c + b*c
              CEvaluationNode * newnode = CEvaluationNode::create((Type)(OPERATOR | PLUS), "+");
              CEvaluationNode * newchild1 = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
              CEvaluationNode * newchild2 = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
              CEvaluationNode * grandchild1 = dynamic_cast<CEvaluationNode*>(child1->getChild())->copyBranch();
              CEvaluationNode * grandchild2 = child2->copyBranch();
              CEvaluationNode * grandchild3 = dynamic_cast<CEvaluationNode*>(child1->getChild()->getSibling())->copyBranch();
              CEvaluationNode * grandchild4 = child2;
              newnode->addChild(newchild1, NULL);
              newnode->addChild(newchild2, newchild1);
              newchild1->addChild(grandchild1, NULL);
              newchild1->addChild(grandchild2, grandchild1);
              newchild2->addChild(grandchild3, NULL);
              newchild2->addChild(grandchild4, grandchild3);
              delete child1;
              return newnode;
            }
          if (child2->getData() == "+")
            {// expand a*(b+c) -> a*b + a*c
              CEvaluationNode * newnode = CEvaluationNode::create((Type)(OPERATOR | PLUS), "+");
              CEvaluationNode * newchild1 = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
              CEvaluationNode * newchild2 = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
              CEvaluationNode * grandchild1 = child1->copyBranch();
              CEvaluationNode * grandchild2 = dynamic_cast<CEvaluationNode*>(child2->getChild())->copyBranch();
              CEvaluationNode * grandchild3 = child1;
              CEvaluationNode * grandchild4 = dynamic_cast<CEvaluationNode*>(child2->getChild()->getSibling())->copyBranch();
              newnode->addChild(newchild1, NULL);
              newnode->addChild(newchild2, newchild1);
              newchild1->addChild(grandchild1, NULL);
              newchild1->addChild(grandchild2, grandchild1);
              newchild2->addChild(grandchild3, NULL);
              newchild2->addChild(grandchild4, grandchild3);
              delete child2;
              return newnode;
            }
          if(CEvaluationNode::type(child1->getType())==CEvaluationNode::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(child1->getType()))==CEvaluationNodeOperator::POWER)
          {
              // A^n*A^l -> A^(n+l) this way exponents can be simplified 
              // check if the second child is also a power item
              if(CEvaluationNode::type(child2->getType())==CEvaluationNode::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(child2->getType()))==CEvaluationNodeOperator::POWER)
              {
                if(dynamic_cast<const CEvaluationNode*>(child2->getChild())->getInfix()==dynamic_cast<const CEvaluationNode*>(child1->getChild())->getInfix())
                {
                    CEvaluationNode* newNode=CEvaluationNode::create((Type)( OPERATOR | POWER),"^");
                    CEvaluationNode* newchild1 = dynamic_cast<CEvaluationNode*>(child2->getChild())->copyBranch();
                    newNode->addChild(newchild1);
                    CEvaluationNode* newchild2 = CEvaluationNode::create((Type)(OPERATOR | PLUS), "+");
                    CEvaluationNode* grandchild1 = dynamic_cast<CEvaluationNode*>(child1->getChild()->getSibling())->copyBranch();
                    CEvaluationNode* grandchild2 = dynamic_cast<CEvaluationNode*>(child2->getChild()->getSibling())->copyBranch();
                    // simplify newchild2
                    std::vector<CEvaluationNode*> children;
                    children.push_back(grandchild1);
                    children.push_back(grandchild2);
                    newNode->addChild(newchild2->simplifyNode(children));
                    // simplify the result again since a power node with an
                    // exponent of 1 or 0 could have been created.
                    delete child1;
                    children.clear();
                    children.push_back(dynamic_cast<CEvaluationNode*>(newNode->getChild())->copyBranch());
                    children.push_back(dynamic_cast<CEvaluationNode*>(newNode->getChild()->getSibling())->copyBranch());
                    child1=newNode->simplifyNode(children);
                    delete newNode;
                    newNode=child1;
                    delete newchild2;
                    delete child2;
                    return newNode;
                }

              }
              else
              {
                // A^n * A -> A^(n+1)  
                // check if the second child is the same as the first child to
                // the power operator
                if(child2->getInfix()==dynamic_cast<const CEvaluationNode*>(child1->getChild())->getInfix())
                {
                    CEvaluationNode* newNode=CEvaluationNode::create((Type)( OPERATOR | POWER),"^");
                    CEvaluationNode* newchild1 = dynamic_cast<CEvaluationNode*>(child2->getChild())->copyBranch();
                    newNode->addChild(newchild1);
                    CEvaluationNode* newchild2 = CEvaluationNode::create((Type)(OPERATOR | PLUS), "+");
                    CEvaluationNode* grandchild1 = dynamic_cast<CEvaluationNode*>(child1->getChild()->getSibling())->copyBranch();
                    CEvaluationNode* grandchild2 = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE,"1.0");
                    // simplify newchild2
                    std::vector<CEvaluationNode*> children;
                    children.push_back(grandchild1);
                    children.push_back(grandchild2);
                    newNode->addChild(newchild2->simplifyNode(children));
                    // simplify the result again since a power node with an
                    // exponent of 1 or 0 could have been created.
                    delete child1;
                    children.clear();
                    children.push_back(dynamic_cast<CEvaluationNode*>(newNode->getChild())->copyBranch());
                    children.push_back(dynamic_cast<CEvaluationNode*>(newNode->getChild()->getSibling())->copyBranch());
                    child1=newNode->simplifyNode(children);
                    delete newNode;
                    newNode=child1;
                    delete newchild2;
                    delete child2;
                    return newNode;
                }
              }
          }
          else if(CEvaluationNode::type(child2->getType())==CEvaluationNode::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(child2->getType()))==CEvaluationNodeOperator::POWER)
          {
             // A*A^n -> A^(n+1)
             // check if child 1 is the same as the first child to the power
             // operator 
             if(child1->getInfix()==dynamic_cast<const CEvaluationNode*>(child2->getChild())->getInfix())
             {
                CEvaluationNode* newNode=CEvaluationNode::create((Type)( OPERATOR | POWER),"^");
                newNode->addChild(child1);
                CEvaluationNode* newchild2 = CEvaluationNode::create((Type)(OPERATOR | PLUS), "+");
                CEvaluationNode* grandchild1 = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE,"1.0");
                CEvaluationNode* grandchild2 = dynamic_cast<CEvaluationNode*>(child2->getChild()->getSibling())->copyBranch();
                // simplify newchild2
                std::vector<CEvaluationNode*> children;
                children.push_back(grandchild1);
                children.push_back(grandchild2);
                newNode->addChild(newchild2->simplifyNode(children));
                // simplify the result again since a power node with an
                // exponent of 1 or 0 could have been created.
                children.clear();
                children.push_back(dynamic_cast<CEvaluationNode*>(newNode->getChild())->copyBranch());
                children.push_back(dynamic_cast<CEvaluationNode*>(newNode->getChild()->getSibling())->copyBranch());
                child1=newNode->simplifyNode(children);
                delete newNode;
                newNode=child1;
                delete newchild2;
                delete child2;
                return newNode;
             }
          }

          // default: copy
          CEvaluationNode *newnode = copyNode(child1, child2);
          return newnode;
        }
      case DIVIDE:
        {
          if (CEvaluationNode::type(child1->getType()) == NUMBER)
            {
              if (CEvaluationNode::type(child2->getType()) == NUMBER)
                {// both children numbers ->calculate
                  std::stringstream tmp;
                  tmp.precision(18);
                  tmp << child1->value() / child2->value();
                  CEvaluationNode *newnode = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), tmp.str());
                  delete child1;
                  delete child2;
                  return newnode;
                }
              if (fabs(child1->value()) < 1.0E-100)
                {// 0/a -> a
                  CEvaluationNode *newnode = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), "0.0");
                  delete child1;
                  delete child2;
                  return newnode;
                }
            }
          if (CEvaluationNode::type(child2->getType()) == NUMBER)
            {
              // a/0 -> false
              if (fabs(child2->value()) < 1.0E-100)
                return false;
              if (fabs(child2->value() - 1.0) < 1.0E-100)
                {// a/1 -> a
                  delete child2;
                  return child1;
                }
            }
          if (child1->getInfix() == child2->getInfix())
            {// a/a -> 1
              CEvaluationNode *newnode = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), "1.0");
              delete child1;
              delete child2;
              return newnode;
            }
          if (child1->getData() == "/")
            {
              if (child2->getData() == "/")
                {// (a/b)/(c/d) -> (a*d)/(b*c)
                  // this rule is actually already executed by the following two rules, but more efficiently this way
                  CEvaluationNode* newnode = CEvaluationNode::create((Type)(OPERATOR | DIVIDE), "/");
                  CEvaluationNode* newchild1 = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
                  CEvaluationNode* newchild2 = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
                  CEvaluationNode* grandchild1 = dynamic_cast<CEvaluationNode*>(child1->getChild())->copyBranch();
                  CEvaluationNode* grandchild2 = dynamic_cast<CEvaluationNode*>(child2->getChild()->getSibling())->copyBranch();
                  CEvaluationNode* grandchild3 = dynamic_cast<CEvaluationNode*>(child1->getChild()->getSibling())->copyBranch();
                  CEvaluationNode* grandchild4 = dynamic_cast<CEvaluationNode*>(child2->getChild())->copyBranch();
                  newnode->addChild(newchild1, NULL);
                  newnode->addChild(newchild2, newchild1);
                  newchild1->addChild(grandchild1, NULL);
                  newchild1->addChild(grandchild2, grandchild1);
                  newchild2->addChild(grandchild3, NULL);
                  newchild2->addChild(grandchild4, grandchild3);
                  delete child1;
                  delete child2;
                  return newnode;
                }
              // (a/b)/c -> a/(b*c)
              CEvaluationNode* newnode = CEvaluationNode::create((Type)(OPERATOR | DIVIDE), "/");
              CEvaluationNode* newchild1 = dynamic_cast<CEvaluationNode*>(child1->getChild())->copyBranch();
              CEvaluationNode* newchild2 = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
              CEvaluationNode* grandchild1 = dynamic_cast<CEvaluationNode*>(child1->getChild()->getSibling())->copyBranch();
              CEvaluationNode* grandchild2 = child2;
              newnode->addChild(newchild1, NULL);
              newnode->addChild(newchild2, newchild1);
              newchild2->addChild(grandchild1, NULL);
              newchild2->addChild(grandchild2, grandchild1);
              delete child1;
              return newnode;
            }
          if (child2->getData() == "/")
            {// a/(b/c) -> (a*c)/b
              CEvaluationNode* newnode = CEvaluationNode::create((Type)(OPERATOR | DIVIDE), "/");
              CEvaluationNode* newchild1 = CEvaluationNode::create((Type)(OPERATOR | MULTIPLY), "*");
              CEvaluationNode* newchild2 = dynamic_cast<CEvaluationNode*>(child2->getChild())->copyBranch();
              CEvaluationNode* grandchild1 = child1;
              CEvaluationNode* grandchild2 = dynamic_cast<CEvaluationNode*>(child2->getChild()->getSibling())->copyBranch();
              newnode->addChild(newchild1, NULL);
              newnode->addChild(newchild2, newchild1);
              newchild1->addChild(grandchild1, NULL);
              newchild1->addChild(grandchild2, grandchild1);
              delete child2;
              return newnode;
            }
          if(CEvaluationNode::type(child1->getType())==CEvaluationNode::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(child1->getType()))==CEvaluationNodeOperator::POWER)
          {
              // A^n / A^l -> A^(n-l)
              // check if the second child is also a power item
              if(CEvaluationNode::type(child2->getType())==CEvaluationNode::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(child2->getType()))==CEvaluationNodeOperator::POWER)
              {
                if(dynamic_cast<const CEvaluationNode*>(child2->getChild())->getInfix()==dynamic_cast<const CEvaluationNode*>(child1->getChild())->getInfix())
                {
                    CEvaluationNode* newNode=CEvaluationNode::create((Type)( OPERATOR | POWER),"^");
                    CEvaluationNode* newchild1 = dynamic_cast<CEvaluationNode*>(child2->getChild())->copyBranch();
                    newNode->addChild(newchild1);
                    CEvaluationNode* newchild2 = CEvaluationNode::create((Type)(OPERATOR | MINUS), "-");
                    CEvaluationNode* grandchild1 = dynamic_cast<CEvaluationNode*>(child1->getChild()->getSibling())->copyBranch();
                    CEvaluationNode* grandchild2 = dynamic_cast<CEvaluationNode*>(child2->getChild()->getSibling())->copyBranch();
                    // simplify newchild2
                    std::vector<CEvaluationNode*> children;
                    children.push_back(grandchild1);
                    children.push_back(grandchild2);
                    newNode->addChild(newchild2->simplifyNode(children));
                    // simplify the result again since a power node with an
                    // exponent of 1 or 0 could have been created.
                    delete child1;
                    children.clear();
                    children.push_back(dynamic_cast<CEvaluationNode*>(newNode->getChild())->copyBranch());
                    children.push_back(dynamic_cast<CEvaluationNode*>(newNode->getChild()->getSibling())->copyBranch());
                    child1=newNode->simplifyNode(children);
                    delete newNode;
                    newNode=child1;
                    delete newchild2;
                    delete child2;
                    return newNode;
                }

              }
              else
              {
                // A^n/A -> A^(n-1)  
                // check if the second child is the same as the first child to
                // the power operator
                if(child2->getInfix()==dynamic_cast<const CEvaluationNode*>(child1->getChild())->getInfix())
                {
                    CEvaluationNode* newNode=CEvaluationNode::create((Type)( OPERATOR | POWER),"^");
                    CEvaluationNode* newchild1 = dynamic_cast<CEvaluationNode*>(child2->getChild())->copyBranch();
                    newNode->addChild(newchild1);
                    CEvaluationNode* newchild2 = CEvaluationNode::create((Type)(OPERATOR | MINUS), "-");
                    CEvaluationNode* grandchild1 = dynamic_cast<CEvaluationNode*>(child1->getChild()->getSibling())->copyBranch();
                    CEvaluationNode* grandchild2 = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE,"1.0");
                    // simplify newchild2
                    std::vector<CEvaluationNode*> children;
                    children.push_back(grandchild1);
                    children.push_back(grandchild2);
                    newNode->addChild(newchild2->simplifyNode(children));
                    // simplify the result again since a power node with an
                    // exponent of 1 or 0 could have been created.
                    delete child1;
                    children.clear();
                    children.push_back(dynamic_cast<CEvaluationNode*>(newNode->getChild())->copyBranch());
                    children.push_back(dynamic_cast<CEvaluationNode*>(newNode->getChild()->getSibling())->copyBranch());
                    child1=newNode->simplifyNode(children);
                    delete newNode;
                    newNode=child1;
                    delete newchild2;
                    delete child2;
                    return newNode;
                }
              }
          }
          else if(CEvaluationNode::type(child2->getType())==CEvaluationNode::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(child2->getType()))==CEvaluationNodeOperator::POWER)
          {
             // A / A^n -> A^(1-n)
             // check if child 1 is the same as the first child to the power
             // operator 
             if(child1->getInfix()==dynamic_cast<const CEvaluationNode*>(child2->getChild())->getInfix())
             {
                CEvaluationNode* newNode=CEvaluationNode::create((Type)( OPERATOR | POWER),"^");
                newNode->addChild(child1);
                CEvaluationNode* newchild2 = CEvaluationNode::create((Type)(OPERATOR | MINUS), "-");
                CEvaluationNode* grandchild1 = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE,"1.0");
                CEvaluationNode* grandchild2 = dynamic_cast<CEvaluationNode*>(child2->getChild()->getSibling())->copyBranch();
                // simplify newchild2
                std::vector<CEvaluationNode*> children;
                children.push_back(grandchild1);
                children.push_back(grandchild2);
                newNode->addChild(newchild2->simplifyNode(children));
                // simplify the result again since a power node with an
                // exponent of 1 or 0 could have been created.
                children.clear();
                children.push_back(dynamic_cast<CEvaluationNode*>(newNode->getChild())->copyBranch());
                children.push_back(dynamic_cast<CEvaluationNode*>(newNode->getChild()->getSibling())->copyBranch());
                child1=newNode->simplifyNode(children);
                delete newNode;
                newNode=child1;
                delete newchild2;
                delete child2;
                return newNode;
             }
          }
          // default: copy
          CEvaluationNode *newnode = copyNode(child1, child2);
          return newnode;
        }
      case PLUS:
        {
          if (CEvaluationNode::type(child1->getType()) == NUMBER)
            {
              if (CEvaluationNode::type(child2->getType()) == NUMBER)
                {// both children numbers ->calculate
                  std::stringstream tmp;
                  tmp.precision(18);
                  tmp << child1->value() + child2->value();
                  CEvaluationNode *newnode = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), tmp.str());
                  delete child1;
                  delete child2;
                  return newnode;
                }
              if (fabs(child1->value()) < 1.0E-100)
                {// 0 + a -> a
                  delete child1;
                  return child2;
                }
            }
          if ((CEvaluationNode::type(child2->getType()) == NUMBER) && (fabs(child2->value()) < 1.0E-100))
            {// a + 0 -> a
              delete child2;
              return child1;
            }
          if (((child1->getType() == (Type)(FUNCTION | CEvaluationNodeFunction::MINUS))
               && (dynamic_cast<CEvaluationNode*>(child1->getChild())->getInfix() == child2->getInfix()))
              ||
              ((child2->getType() == (Type)(FUNCTION | CEvaluationNodeFunction::MINUS))
               && (dynamic_cast<CEvaluationNode*>(child2->getChild())->getInfix() == child1->getInfix())))
            {// -(a) + a  and  a + (-a)  -> 0
              CEvaluationNode *newnode = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), "0.0");
              delete child1;
              delete child2;
              return newnode;
            }
          // default: copy
          CEvaluationNode *newnode = copyNode(child1, child2);
          return newnode;
        }
      case MINUS:
        {
          if (CEvaluationNode::type(child1->getType()) == NUMBER)
            {
              if (CEvaluationNode::type(child2->getType()) == NUMBER)
                {// both children numbers ->calculate
                  std::stringstream tmp;
                  tmp.precision(18);
                  tmp << child1->value() - child2->value();
                  CEvaluationNode *newnode = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), tmp.str());
                  delete child1;
                  delete child2;
                  return newnode;
                }
              if (fabs(child1->value()) < 1.0E-100)
                {// 0-a -> -(a)
                  CEvaluationNode *newnode = CEvaluationNode::create((Type)(FUNCTION | CEvaluationNodeFunction::MINUS), "-");
                  newnode->addChild(child2, NULL);
                  delete child1;
                  return newnode;
                }
            }

          if ((CEvaluationNode::type(child2->getType()) == NUMBER) && (fabs(child2->value()) < 1.0E-100))
            {// a-0 -> a
              delete child2;
              return child1;
            }

          if (child1->getInfix() == child2->getInfix())
            {// a-a -> 0
              CEvaluationNode *newnode = CEvaluationNode::create((Type)(NUMBER | CEvaluationNodeNumber::DOUBLE), "0.0");
              delete child1;
              delete child2;
              return newnode;
            }
          // default:  a - b  ->  a + (-b)
          CEvaluationNode *newnode = CEvaluationNode::create((Type)(OPERATOR | PLUS), "+");
          CEvaluationNode *newchild2 = CEvaluationNode::create((Type)(FUNCTION | CEvaluationNodeFunction::MINUS), "-");
          newnode->addChild(child1, NULL);
          newnode->addChild(newchild2, child1);
          newchild2->addChild(child2, NULL);
          return newnode;
        }
      default:       //case MODULUS
        {
          CEvaluationNode *newnode = copyNode(child1, child2);
          return newnode;
        }
      }
  }

bool CEvaluationNodeOperator::createModuloTree(const CEvaluationNodeOperator* pNode, ASTNode* pASTNode) const
  {
    // x%y -> x-floor(x/y)*x
    bool result = false;
    if ((SubType)CEvaluationNode::subType(pNode->getType()) == MODULUS)
      {
        // the node has two children x and y
        const CEvaluationNode* x = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
        if (x != NULL)
          {
            const CEvaluationNode* y = dynamic_cast<const CEvaluationNode*>(x->getSibling());
            if (y != NULL)
              {
                pASTNode->setType(AST_MINUS);
                ASTNode* tmpASTNode = new ASTNode(AST_DIVIDE);
                tmpASTNode->addChild(x->toAST());
                tmpASTNode->addChild(y->toAST());
                ASTNode* tmpASTNode2 = new ASTNode(AST_FUNCTION_FLOOR);
                tmpASTNode2->addChild(tmpASTNode);
                tmpASTNode = new ASTNode(AST_TIMES);
                tmpASTNode->addChild(x->toAST());
                tmpASTNode->addChild(tmpASTNode2);
                pASTNode->addChild(x->toAST());
                pASTNode->addChild(tmpASTNode);
                result = true;
              }
          }
      }
    return result;
  }

CEvaluationNode * CEvaluationNodeOperator::getLeft()
{return mpLeft;}
const CEvaluationNode * CEvaluationNodeOperator::getLeft() const
  {return mpLeft;}
CEvaluationNode * CEvaluationNodeOperator::getRight()
{return mpRight;}
const CEvaluationNode * CEvaluationNodeOperator::getRight() const
  {return mpRight;}

#include "utilities/copasimathml.h"

void CEvaluationNodeOperator::writeMathML(std::ostream & out,
    const std::vector<std::vector<std::string> > & env,
    bool expand,
    unsigned C_INT32 l) const
  {
    bool flag;
    switch (mType & 0x00FFFFFF)
      {
      case PLUS:

        out << SPC(l) << "<mrow>" << std::endl;
        mpLeft->writeMathML(out, env, expand, l + 1);
        out << SPC(l + 1) << "<mo>" << "+" << "</mo>" << std::endl;
        mpRight->writeMathML(out, env, expand, l + 1);
        out << SPC(l) << "</mrow>" << std::endl;
        break;

      case MINUS:
        out << SPC(l) << "<mrow>" << std::endl;
        mpLeft->writeMathML(out, env, expand, l + 1);
        out << SPC(l + 1) << "<mo>" << "-" << "</mo>" << std::endl;

        flag = ((mpRight->getType() == (CEvaluationNode::OPERATOR | PLUS))
                || (mpRight->getType() == (CEvaluationNode::OPERATOR | MINUS))
                || (((mpRight->getType() & 0xFF000000) == CEvaluationNode::CALL) && expand)
);
        if (flag) out << SPC(l + 1) << "<mfenced>" << std::endl;
        mpRight->writeMathML(out, env, expand, l + 1);
        if (flag) out << SPC(l + 1) << "</mfenced>" << std::endl; // ???
        out << SPC(l) << "</mrow>" << std::endl;
        break;

      case MULTIPLY:
        out << SPC(l) << "<mrow>" << std::endl;

        //do we need "()" ?
        flag = ((mpLeft->getType() == (CEvaluationNode::OPERATOR | PLUS))
                || (mpLeft->getType() == (CEvaluationNode::OPERATOR | MINUS))
                || (((mpLeft->getType() & 0xFF000000) == CEvaluationNode::CALL) && expand)
);
        if (flag) out << SPC(l + 1) << "<mfenced>" << std::endl;
        mpLeft->writeMathML(out, env, expand, l + 1);
        if (flag) out << SPC(l + 1) << "</mfenced>" << std::endl;

        out << SPC(l + 1) << "<mo>" << "&CenterDot;" << "</mo>" << std::endl;

        flag = ((mpRight->getType() == (CEvaluationNode::OPERATOR | PLUS))
                || (mpRight->getType() == (CEvaluationNode::OPERATOR | MINUS))
                || (((mpRight->getType() & 0xFF000000) == CEvaluationNode::CALL) && expand)
);
        if (flag) out << SPC(l + 1) << "<mfenced>" << std::endl;
        mpRight->writeMathML(out, env, expand, l + 1);
        if (flag) out << SPC(l + 1) << "</mfenced>" << std::endl;
        out << SPC(l) << "</mrow>" << std::endl;

        break;

      case DIVIDE:
        out << SPC(l) << "<mfrac>" << std::endl;

        //out << SPC(l + 1) << "<mrow>" << std::endl;
        mpLeft->writeMathML(out, env, expand, l + 1);
        //out << SPC(level + 1) << "</mrow>" << std::endl;

        //out << SPC(l + 1) << "<mrow>" << std::endl;
        mpRight->writeMathML(out, env, expand, l + 1);
        //out << SPC(l + 1) << "</mrow>" << std::endl;

        out << SPC(l) << "</mfrac>" << std::endl;
        break;

      case POWER:
        out << SPC(l) << "<msup>" << std::endl;

        //do we need "()" ?
        flag = ((mpLeft->getType() == (CEvaluationNode::OPERATOR | PLUS))
                || (mpLeft->getType() == (CEvaluationNode::OPERATOR | MINUS))
                || (mpLeft->getType() == (CEvaluationNode::OPERATOR | MULTIPLY))
                || (mpLeft->getType() == (CEvaluationNode::OPERATOR | DIVIDE))
                || (mpLeft->getType() == (CEvaluationNode::OPERATOR | POWER))
                || (((mpLeft->getType() & 0xFF000000) == CEvaluationNode::CALL) && expand)
);
        if (flag) out << SPC(l + 1) << "<mfenced>" << std::endl;
        mpLeft->writeMathML(out, env, expand, l + 2);
        if (flag) out << SPC(l + 1) << "</mfenced>" << std::endl;

        out << SPC(l + 1) << "<mrow>" << std::endl;
        mpRight->writeMathML(out, env, expand, l + 2);
        out << SPC(l + 1) << "</mrow>" << std::endl;

        out << SPC(l) << "</msup>" << std::endl;
        break;

      case MODULUS:
        out << SPC(l) << "<mrow>" << std::endl;

        //do we need "()" ?
        flag = true;
        if (flag) out << SPC(l + 1) << "<mfenced>" << std::endl;
        mpLeft->writeMathML(out, env, expand, l + 1);
        if (flag) out << SPC(l + 1) << "</mfenced>" << std::endl;

        out << SPC(l + 1) << "<mo>" << "%" << "</mo>" << std::endl;

        flag = true;
        if (flag) out << SPC(l + 1) << "<mfenced>" << std::endl;
        mpRight->writeMathML(out, env, expand, l + 1);
        if (flag) out << SPC(l + 1) << "</mfenced>" << std::endl;
        out << SPC(l) << "</mrow>" << std::endl;
        break;
      }
  }
