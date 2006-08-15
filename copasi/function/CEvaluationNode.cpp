/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNode.cpp,v $
   $Revision: 1.29 $
   $Name:  $
   $Author: nsimus $
   $Date: 2006/08/15 11:39:31 $
   End CVS Header */

// Copyright � 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"
#include "CEvaluationNode.h"

#include "sbml/math/ASTNode.h"
#include "sbml/ConverterASTNode.h"
#include "sbml/util/List.h"

CEvaluationNode::CPrecedence::CPrecedence(const unsigned C_INT32 & left,
    const unsigned C_INT32 & right):
    left(left),
    right(right)
{}

CEvaluationNode::CPrecedence::CPrecedence(const CPrecedence & src):
    left(src.left),
    right(src.right)
{}

CEvaluationNode::CPrecedence::~CPrecedence() {}

CEvaluationNode * CEvaluationNode::create(const Type & type,
    const std::string & contents)
{
  CEvaluationNode * pNode = NULL;

  switch (CEvaluationNode::type(type))
    {
    case CEvaluationNode::CALL:
      pNode = new CEvaluationNodeCall((CEvaluationNodeCall::SubType) subType(type),
                                      contents);
      break;

    case CEvaluationNode::CHOICE:
      pNode = new CEvaluationNodeChoice((CEvaluationNodeChoice::SubType) subType(type),
                                        contents);
      break;

    case CEvaluationNode::CONSTANT:
      pNode = new CEvaluationNodeConstant((CEvaluationNodeConstant::SubType) subType(type),
                                          contents);
      break;

    case CEvaluationNode::FUNCTION:
      pNode = new CEvaluationNodeFunction((CEvaluationNodeFunction::SubType) subType(type),
                                          contents);
      break;

    case CEvaluationNode::LOGICAL:
      pNode = new CEvaluationNodeLogical((CEvaluationNodeLogical::SubType) subType(type),
                                         contents);
      break;

    case CEvaluationNode::NUMBER:
      pNode = new CEvaluationNodeNumber((CEvaluationNodeNumber::SubType) subType(type),
                                        contents);
      break;

    case CEvaluationNode::OBJECT:
      pNode = new CEvaluationNodeObject((CEvaluationNodeObject::SubType) subType(type),
                                        contents);
      break;

    case CEvaluationNode::OPERATOR:
      pNode = new CEvaluationNodeOperator((CEvaluationNodeOperator::SubType) subType(type),
                                          contents);
      break;

    case CEvaluationNode::STRUCTURE:
      pNode = new CEvaluationNodeStructure((CEvaluationNodeStructure::SubType) subType(type),
                                           contents);
      break;

    case CEvaluationNode::VARIABLE:
      pNode = new CEvaluationNodeVariable((CEvaluationNodeVariable::SubType) subType(type),
                                          contents);
      break;

    case CEvaluationNode::VECTOR:
      pNode = new CEvaluationNodeVector((CEvaluationNodeVector::SubType) subType(type),
                                        contents);
      break;

    case CEvaluationNode::WHITESPACE:
      pNode = new CEvaluationNodeWhiteSpace((CEvaluationNodeWhiteSpace::SubType) subType(type),
                                            contents);
      break;
    }

  return pNode;
}

CEvaluationNode::Type CEvaluationNode::subType(const Type & type)
{return (Type) (type & 0x00FFFFFF);}

CEvaluationNode::Type CEvaluationNode::type(const Type & type)
{return (Type) (type & 0xFF000000);}

CEvaluationNode::CEvaluationNode():
    CCopasiNode<Data>(),
    mType(CEvaluationNode::INVALID),
    mValue(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mData(""),
    mPrecedence(PRECEDENCE_DEFAULT)
{}

CEvaluationNode::CEvaluationNode(const Type & type,
                                 const Data & data):
    CCopasiNode<Data>(),
    mType(type),
    mValue(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mData(data),
    mPrecedence(PRECEDENCE_DEFAULT)
{assert(mData != "");}

CEvaluationNode::CEvaluationNode(const CEvaluationNode & src):
    CCopasiNode<Data>(src),
    mType(src.mType),
    mValue(src.mValue),
    mData(src.mData),
    mPrecedence(src.mPrecedence)
{assert(mData != "");}

CEvaluationNode::~CEvaluationNode() {}

bool CEvaluationNode::compile(const CEvaluationTree * /* pTree */)
{return true;}

CEvaluationNode::Data CEvaluationNode::getData() const
  {return mData;}

bool CEvaluationNode::setData(const Data & data)
{
  mData = data;
  return true;
}

std::string CEvaluationNode::getInfix() const
  {return mData;}

std::string CEvaluationNode::getDisplayString(const CEvaluationTree * /* pTree */) const
  {return mData;}

std::string CEvaluationNode::getDisplay_C_String(const CEvaluationTree * /* pTree */) const
  {return mData;}

std::string CEvaluationNode::getDisplay_MMD_String(const CEvaluationTree * /* pTree */) const
  {return mData;}

std::string CEvaluationNode::getDisplay_XPP_String(const CEvaluationTree * /* pTree */) const
  {return mData;}

const CEvaluationNode::Type & CEvaluationNode::getType() const
  {return mType;}

bool CEvaluationNode::operator < (const CEvaluationNode & rhs)
{return (mPrecedence.right < rhs.mPrecedence.left);}

CEvaluationNode* CEvaluationNode::copyNode(CEvaluationNode *child1, CEvaluationNode *child2) const
  {
    //std::cout << " this->getData() " << this->CEvaluationNode::getData() << std::endl;

    CEvaluationNode *newnode = create(getType(), getData());
    if (child1 != NULL)
      {
        newnode->addChild(child1, NULL);
        if (child2 != NULL)
          {
            newnode->addChild(child2, child1);
          }
      }
    return newnode;
  }

CEvaluationNode* CEvaluationNode::copyBranch() const
  {
    const CEvaluationNode *child1 = dynamic_cast<const CEvaluationNode*>(getChild());
    CEvaluationNode *newchild1 = NULL;
    CEvaluationNode *newchild2 = NULL;
    if (child1 != NULL)
      {
        newchild1 = child1->copyBranch();
        const CEvaluationNode *child2 = dynamic_cast<const CEvaluationNode*>(child1->getSibling());
        if (child2 != NULL)
          {
            newchild2 = child2->copyBranch();
          }
      }
    CEvaluationNode *newnode = copyNode(newchild1, newchild2);
    return newnode;
  }

CEvaluationNode* CEvaluationNode::simplifyNode(CEvaluationNode *child1, CEvaluationNode *child2) const
  {
    CEvaluationNode *newnode = copyNode(child1, child2);
    return newnode;
  }

ASTNode* CEvaluationNode::toAST() const
  {
    return new ASTNode();
  }

const C_FLOAT64 * CEvaluationNode::getValuePointer() const
  {return &mValue;}

void CEvaluationNode::writeMathML(std::ostream & out,
                                  const std::vector<std::vector<std::string> > & env,
                                  bool expand,
                                  unsigned C_INT32 l) const
  {}

void CEvaluationNode::printRecursively(std::ostream & os, int indent) const
  {
    int i;

    os << std::endl;

    for (i = 0; i < indent; ++i) os << " ";
    os << "mData: " << mData << std::endl;

    for (i = 0; i < indent; ++i) os << " ";
    os << "mType: " << type(mType) << "  subType: " << subType(mType) << std::endl;

    for (i = 0; i < indent; ++i) os << " ";
    os << "mValue: " << mValue << std::endl;

    CEvaluationNode* tmp;

    tmp = (CEvaluationNode*)getChild();

    while (tmp)
      {
        tmp -> printRecursively(os, indent + 2);
        tmp = (CEvaluationNode*)tmp->getSibling();
      }

    /*    if (getChild())
          ((CEvaluationNode*)getChild())->printRecursively(os, indent + 2);

        if (getSibling())
          ((CEvaluationNode*)getSibling())->printRecursively(os, indent);*/
  }

void CEvaluationNode::printRecursively() const
  {
    this->printRecursively(std::cout, 0);
  }

/**
 * Replaces all LOG10 (AST_FUNCTION_LOG) nodes that have two
 * children with the quotient of two LOG10 nodes with the base
 * as the argument for the divisor LOG10 node.
 */
void CEvaluationNode::replaceLog(ConverterASTNode* sourceNode)
{
  if (sourceNode->getType() == AST_FUNCTION_LOG && sourceNode->getNumChildren() == 2)
    {
      List* l = new List();
      ConverterASTNode* child1 = (ConverterASTNode*)sourceNode->getChild(0);
      ConverterASTNode* child2 = (ConverterASTNode*)sourceNode->getChild(1);
      ConverterASTNode* logNode1 = new ConverterASTNode(AST_FUNCTION_LOG);
      l->add(child1);
      logNode1->setChildren(l);
      ConverterASTNode* logNode2 = new ConverterASTNode(AST_FUNCTION_LOG);
      l = new List();
      l->add(child2);
      logNode2->setChildren(l);
      l = new List();
      l->add(logNode2);
      l->add(logNode1);
      sourceNode->setChildren(l);
      sourceNode->setType(AST_DIVIDE);
    }
}

/**
 * Replaces all root nodes with the corresponding power
 * operator since COPASI does not have the ROOT function.
 */
void CEvaluationNode::replaceRoot(ConverterASTNode* sourceNode)
{
  if (sourceNode->getType() == AST_FUNCTION_ROOT && sourceNode->getNumChildren() == 2)
    {
      ConverterASTNode* child1 = (ConverterASTNode*)sourceNode->getChild(0);
      ConverterASTNode* child2 = (ConverterASTNode*)sourceNode->getChild(1);
      ConverterASTNode* divideNode = new ConverterASTNode(AST_DIVIDE);
      ConverterASTNode* oneNode = new ConverterASTNode(AST_REAL);
      oneNode->setValue(1.0);
      List* l = new List();
      l->add(divideNode);
      divideNode->addChild(oneNode);
      divideNode->addChild(child1);

      List* l2 = new List();
      l2->add(child2);
      l2->add(divideNode);

      sourceNode->setChildren(l2);
      sourceNode->setType(AST_POWER);
    }
}
