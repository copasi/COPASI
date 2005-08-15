/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNode.cpp,v $
   $Revision: 1.18 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/08/15 14:01:05 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"

#include "sbml/math/ASTNode.h"

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

const CEvaluationNode::Type & CEvaluationNode::getType() const
  {return mType;}

bool CEvaluationNode::operator < (const CEvaluationNode & rhs)
{return (mPrecedence.right < rhs.mPrecedence.left);}

ASTNode* CEvaluationNode::toAST() const
  {
    return new ASTNode();
  }

const C_FLOAT64 * CEvaluationNode::getValuePointer() const
  {return &mValue;}

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

    if (getChild())
      ((CEvaluationNode*)getChild())->printRecursively(os, indent + 2);

    if (getSibling())
      ((CEvaluationNode*)getSibling())->printRecursively(os, indent);
  }
