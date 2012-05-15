// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNode.cpp,v $
//   $Revision: 1.53 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/15 15:56:41 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"
#include "CEvaluationNode.h"

#include "sbml/math/ASTNode.h"
#include "sbml/ConverterASTNode.h"
#include "sbml/util/List.h"

#include "utilities/CNodeIterator.h"

CEvaluationNode::CPrecedence::CPrecedence(const size_t & left,
    const size_t & right):
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

      case CEvaluationNode::DELAY:
        pNode = new CEvaluationNodeDelay((CEvaluationNodeDelay::SubType) subType(type),
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

      case CEvaluationNode::INVALID:
        pNode = new CEvaluationNode();
        break;

      case CEvaluationNode::MV_FUNCTION:
        break;
    }

  return pNode;
}

CEvaluationNode::Type CEvaluationNode::subType(const Type & type)
{return (Type)(type & 0x00FFFFFF);}

CEvaluationNode::Type CEvaluationNode::type(const Type & type)
{return (Type)(type & 0xFF000000);}

CEvaluationNode::CEvaluationNode():
    CCopasiNode<Data>(""),
    mType(CEvaluationNode::INVALID),
    mValue(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mPrecedence(PRECEDENCE_DEFAULT)
{}

CEvaluationNode::CEvaluationNode(const Type & type,
                                 const Data & data):
    CCopasiNode<Data>(data),
    mType(type),
    mValue(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mPrecedence(PRECEDENCE_DEFAULT)
{}

CEvaluationNode::CEvaluationNode(const CEvaluationNode & src):
    CCopasiNode<Data>(src),
    mType(src.mType),
    mValue(src.mValue),
    mPrecedence(src.mPrecedence)
{}

CEvaluationNode::~CEvaluationNode() {}

bool CEvaluationNode::compile(const CEvaluationTree * /* pTree */)
{return true;}

// virtual
std::string CEvaluationNode::getInfix(const std::vector< std::string > & /* children */) const
{return mData;}

std::string CEvaluationNode::buildInfix() const
{
  std::string Infix = "";
  CNodeContextIterator< const CEvaluationNode, std::vector< std::string > > it(this);

  while (it.next() != it.end())
    {
      if (*it != NULL)
        {
          if (it.parentContextPtr() != NULL)
            {
              it.parentContextPtr()->push_back(it->getInfix(it.context()));
            }
          else
            {
              Infix = it->getInfix(it.context());
            }
        }
    }

  return Infix;
}

// virtual
std::string CEvaluationNode::getDisplayString(const std::vector< std::string > & /* children */) const
{return mData;}

std::string CEvaluationNode::buildDisplayString() const
{
  std::string DisplayString = "";
  CNodeContextIterator< const CEvaluationNode, std::vector< std::string > > it(this);

  while (it.next() != it.end())
    {
      if (*it != NULL)
        {
          if (it.parentContextPtr() != NULL)
            {
              it.parentContextPtr()->push_back(it->getDisplayString(it.context()));
            }
          else
            {
              DisplayString = it->getDisplayString(it.context());
            }
        }
    }

  return DisplayString;
}


// TODO CRITICAL Replace the recursive call
std::string CEvaluationNode::getDisplay_C_String(const CEvaluationTree * /* pTree */) const
{return mData;}

// TODO CRITICAL Replace the recursive call
std::string CEvaluationNode::getDisplay_MMD_String(const CEvaluationTree * /* pTree */) const
{return mData;}

// TODO CRITICAL Replace the recursive call
std::string CEvaluationNode::getDisplay_XPP_String(const CEvaluationTree * /* pTree */) const
{return mData;}

const CEvaluationNode::Type & CEvaluationNode::getType() const
{return mType;}

// virtual
bool CEvaluationNode::isBoolean() const
{return false;}

void CEvaluationNode::addChildren(const std::vector< CEvaluationNode * > & children)
{
  std::vector< CEvaluationNode * >::const_iterator it = children.begin();
  std::vector< CEvaluationNode * >::const_iterator end = children.end();

  for (; it != end; ++it)
    {
      addChild(*it);
    }
}

bool CEvaluationNode::operator < (const CEvaluationNode & rhs)
{return (mPrecedence.right < rhs.mPrecedence.left);}

// TODO CRITICAL Replace the recursive call
CEvaluationNode* CEvaluationNode::copyNode(CEvaluationNode* child1, CEvaluationNode* child2) const
{
  std::vector<CEvaluationNode*> children;

  if (child1 != NULL) children.push_back(child1);

  if (child2 != NULL) children.push_back(child2);

  return copyNode(children);
}

// TODO CRITICAL Replace the recursive call
CEvaluationNode* CEvaluationNode::copyNode(const std::vector<CEvaluationNode*>& children) const
{
  CEvaluationNode *newnode = create(mType, getData());
  std::vector<CEvaluationNode*>::const_iterator it = children.begin(), endit = children.end();

  while (it != endit)
    {
      newnode->addChild(*it);
      ++it;
    }

  return newnode;
}

// TODO CRITICAL Replace the recursive call
CEvaluationNode* CEvaluationNode::copyBranch() const
{
  std::vector<CEvaluationNode*> children;
  const CEvaluationNode* child = dynamic_cast<const CEvaluationNode*>(getChild());

  while (child != NULL)
    {
      children.push_back(child->copyBranch());
      child = dynamic_cast<const CEvaluationNode*>(child->getSibling());
    }

  //children.push_back(NULL);
  CEvaluationNode *newnode = copyNode(children);
  return newnode;
}

CEvaluationNode* CEvaluationNode::simplifyNode(const std::vector<CEvaluationNode*>& children) const
{
  CEvaluationNode *newnode = copyNode(children);
  return newnode;
}

ASTNode* CEvaluationNode::toAST(const CCopasiDataModel* /*pDataModel*/) const
{
  return new ASTNode();
}

const C_FLOAT64 * CEvaluationNode::getValuePointer() const
{return &mValue;}

// TODO CRITICAL Replace the recursive call
void CEvaluationNode::writeMathML(std::ostream & /* out */,
                                  const std::vector<std::vector<std::string> > & /* env */,
                                  bool /* expand */,
                                  size_t /* l */) const
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
}

void CEvaluationNode::printRecursively() const
{
  this->printRecursively(std::cout, 0);
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

// TODO CRITICAL Replace the recursive call
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

bool CEvaluationNode::operator!=(const CEvaluationNode& right) const
{
  return !(*this == right);
}

// TODO CRITICAL Replace the recursive call
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
          case CEvaluationNode::DELAY:
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

              break;
            }
          else
            {
              result = (*pChild1 == *pChild2);
              pChild1 = dynamic_cast<const CEvaluationNode*>(pChild1->getSibling());
              pChild2 = dynamic_cast<const CEvaluationNode*>(pChild2->getSibling());
            }
        }
    }
  else
    {
      result = false;
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
          case CEvaluationNode::DELAY:
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
