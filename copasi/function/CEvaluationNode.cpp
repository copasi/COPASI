// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNode.cpp,v $
//   $Revision: 1.36 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/10/26 14:19:14 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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

CEvaluationNode* CEvaluationNode::copyNode(CEvaluationNode* child1, CEvaluationNode* child2) const
  {
    std::vector<CEvaluationNode*> children;
    if (child1 != NULL) children.push_back(child1);
    if (child2 != NULL) children.push_back(child2);
    return copyNode(children);
  }

CEvaluationNode* CEvaluationNode::copyNode(const std::vector<CEvaluationNode*>& children) const
  {
    //std::cout << " this->getData() " << this->CEvaluationNode::getData() << std::endl;

    CEvaluationNode *newnode = create(getType(), getData());
    std::vector<CEvaluationNode*>::const_iterator it = children.begin(), endit = children.end();
    while (it != endit)
      {
        newnode->addChild(*it);
        ++it;
      }
    return newnode;
  }

CEvaluationNode* CEvaluationNode::copyBranch() const
  {
    std::vector<CEvaluationNode*> children;
    const CEvaluationNode* child = dynamic_cast<const CEvaluationNode*>(getChild());
    while (child != NULL)
      {
        CEvaluationNode *newchild = NULL;
        newchild = child->copyBranch();
        children.push_back(newchild);
        child = dynamic_cast<const CEvaluationNode*>(child->getSibling());
      }
    children.push_back(NULL);
    CEvaluationNode *newnode = copyNode(children);
    return newnode;
  }

CEvaluationNode* CEvaluationNode::simplifyNode(const std::vector<CEvaluationNode*>& children) const
  {
    CEvaluationNode *newnode = copyNode(children);
    return newnode;
  }

ASTNode* CEvaluationNode::toAST() const
  {
    return new ASTNode();
  }

const C_FLOAT64 * CEvaluationNode::getValuePointer() const
  {return &mValue;}

void CEvaluationNode::writeMathML(std::ostream & /* out */,
                                  const std::vector<std::vector<std::string> > & /* env */,
                                  bool /* expand */,
                                  unsigned C_INT32 /* l */) const
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

CEvaluationNode* CEvaluationNode::splitBranch(const CEvaluationNode* splitnode, bool left) const
  {
    if (splitnode == this)
      {
        const CEvaluationNode *child = dynamic_cast<const CEvaluationNode*>(this->getChild());
        if (!child) return NULL;
        if (left)
          {
            return child->copyBranch();
          }
        else
          {
            child = dynamic_cast<const CEvaluationNode*>(child->getSibling());
            if (!child) return NULL;
            return child->copyBranch();
          }
      }
    else
      {
        /*        const CEvaluationNode *child1 = dynamic_cast<const CEvaluationNode*>(getChild());
                CEvaluationNode *newchild1 = NULL;
                CEvaluationNode *newchild2 = NULL;
                if (child1 != NULL)
                  {
                    newchild1 = child1->splitBranch(splitnode, left);
                    const CEvaluationNode *child2 = dynamic_cast<const CEvaluationNode*>(child1->getSibling());
                    if (child2 != NULL)
                      {
                        newchild2 = child2->splitBranch(splitnode, left);
                      }
                  }
                CEvaluationNode *newnode = copyNode(newchild1, newchild2);
                return newnode;*/

        std::vector<CEvaluationNode*> children;
        const CEvaluationNode* child = dynamic_cast<const CEvaluationNode*>(getChild());
        while (child != NULL)
          {
            CEvaluationNode *newchild = NULL;
            newchild = child->splitBranch(splitnode, left);
            children.push_back(newchild);
            child = dynamic_cast<const CEvaluationNode*>(child->getSibling());
          }
        children.push_back(NULL);
        CEvaluationNode *newnode = copyNode(children);
        return newnode;
      }
  }

const CEvaluationNode* CEvaluationNode::findTopMinus(const std::vector<CFunctionAnalyzer::CValue> & callParameters) const
  {
    if (getType() == (OPERATOR | CEvaluationNodeOperator::MINUS))
      return this;

    if (getType() == (OPERATOR | CEvaluationNodeOperator::MULTIPLY))
      {
        //look at left child recursively
        const CEvaluationNode *child = dynamic_cast<const CEvaluationNode*>(this->getChild());
        const CEvaluationNode *tmp = NULL;
        if (child) tmp = child->findTopMinus(callParameters);
        if (tmp)
          {
            //we have found a minus operator in the branch of the left child. We
            //only want to report this as a split point if the other branch is positive.
            const CEvaluationNode *child2 = dynamic_cast<const CEvaluationNode*>(child->getSibling());
            if (CFunctionAnalyzer::evaluateNode(child2, callParameters, CFunctionAnalyzer::NOOBJECT).isPositive())
              return tmp;
            else
              return NULL;
          }

        //otherwise look at right child
        const CEvaluationNode *child2 = dynamic_cast<const CEvaluationNode*>(child->getSibling());
        if (child2) tmp = child2->findTopMinus(callParameters);
        if (tmp)
          {
            //we have found a minus operator in the branch of the right child. We
            //only want to report this as a split point if the other branch is positive.
            if (CFunctionAnalyzer::evaluateNode(child, callParameters, CFunctionAnalyzer::NOOBJECT).isPositive())
              return tmp;
            else
              return NULL;
          }

        //TODO: check if both children contain a minus. This would not be a valid split point.
      }

    if (getType() == (OPERATOR | CEvaluationNodeOperator::DIVIDE))
      {
        //look at left child only (recursively)
        const CEvaluationNode *child = dynamic_cast<const CEvaluationNode*>(this->getChild());
        const CEvaluationNode *tmp = NULL;
        if (child) tmp = child->findTopMinus(callParameters);
        if (tmp) return tmp;
      }

    return NULL;
  }

bool CEvaluationNode::operator==(const CEvaluationNode& right) const
  {
    bool result = true;
    if (this->getType() == right.getType())
      {
        switch (CEvaluationNode::type(this->getType()))
          {
          case CEvaluationNode::CONSTANT:
          case CEvaluationNode::NUMBER:
          case CEvaluationNode::OBJECT:
          case CEvaluationNode::CALL:
          case CEvaluationNode::STRUCTURE:
          case CEvaluationNode::VARIABLE:
          case CEvaluationNode::WHITESPACE:
            result = (this->getData() == right.getData());
            break;
          case CEvaluationNode::OPERATOR:
          case CEvaluationNode::FUNCTION:
          case CEvaluationNode::CHOICE:
          case CEvaluationNode::LOGICAL:
          case CEvaluationNode::MV_FUNCTION:
          case CEvaluationNode::VECTOR:
          case CEvaluationNode::INVALID:
            break;
          }
        const CEvaluationNode* pChild1 = dynamic_cast<const CEvaluationNode*>(this->getChild());
        const CEvaluationNode* pChild2 = dynamic_cast<const CEvaluationNode*>(right.getChild());
        while (result == true)
          {
            if (pChild1 == NULL || pChild2 == NULL)
              {
                if (!(pChild1 == NULL && pChild2 == NULL))
                  {
                    result = false;
                  }
              }
            else
              {
                result = (*pChild1 == *pChild2);
              }
            pChild1 = dynamic_cast<const CEvaluationNode*>(pChild1->getSibling());
            pChild2 = dynamic_cast<const CEvaluationNode*>(pChild2->getSibling());
          }
      }
    return result;
  }

bool CEvaluationNode::operator<(const CEvaluationNode& right) const
  {
    bool result = false;
    if (this->getType() < right.getType())
      {
        result = true;
      }
    else if (this->getType() == right.getType())
      {
        switch (CEvaluationNode::type(this->getType()))
          {
          case CEvaluationNode::CONSTANT:
          case CEvaluationNode::NUMBER:
          case CEvaluationNode::OBJECT:
          case CEvaluationNode::CALL:
          case CEvaluationNode::STRUCTURE:
          case CEvaluationNode::VARIABLE:
          case CEvaluationNode::WHITESPACE:
            result = (this->getData() < right.getData());
            break;
          case CEvaluationNode::OPERATOR:
          case CEvaluationNode::FUNCTION:
          case CEvaluationNode::CHOICE:
          case CEvaluationNode::LOGICAL:
          case CEvaluationNode::MV_FUNCTION:
          case CEvaluationNode::VECTOR:
          case CEvaluationNode::INVALID:
            break;
          }
        const CEvaluationNode* pChild1 = dynamic_cast<const CEvaluationNode*>(this->getChild());
        const CEvaluationNode* pChild2 = dynamic_cast<const CEvaluationNode*>(right.getChild());
        while (result == false)
          {
            if (pChild1 == NULL || pChild2 == NULL)
              {
                if (pChild1 == NULL && pChild2 != NULL)
                  {
                    result = true;
                  }
              }
            else
              {
                result = (*pChild1 < *pChild2);
              }
            pChild1 = dynamic_cast<const CEvaluationNode*>(pChild1->getSibling());
            pChild2 = dynamic_cast<const CEvaluationNode*>(pChild2->getSibling());
          }
      }
    return result;
  }
