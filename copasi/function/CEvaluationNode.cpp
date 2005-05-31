/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNode.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/31 17:48:57 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"

CEvaluationNode * CEvaluationNode::create(const Type & type,
    const std::string & contents)
{
  CEvaluationNode * pNode = NULL;

  switch (CEvaluationNode::type(type))
    {
    case CEvaluationNode::CONSTANT:
      pNode = new CEvaluationNodeConstant((CEvaluationNodeConstant::SubType) subType(type),
                                          contents);
      break;

    case CEvaluationNode::FUNCTION:
      pNode = new CEvaluationNodeFunction((CEvaluationNodeFunction::SubType) subType(type),
                                          contents);
      break;

    case CEvaluationNode::NUMBER:
      pNode = new CEvaluationNodeNumber((CEvaluationNodeNumber::SubType) subType(type),
                                        contents);
      break;

    case CEvaluationNode::OPERATOR:
      pNode = new CEvaluationNodeOperator((CEvaluationNodeOperator::SubType) subType(type),
                                          contents);
      break;

    case CEvaluationNode::VARIABLE:
      pNode = new CEvaluationNodeVariable((CEvaluationNodeVariable::SubType) subType(type),
                                          contents);
      break;

    default:
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
    mValue(0.0),
    mData("")
{}

CEvaluationNode::CEvaluationNode(const Type & type,
                                 const Data & data):
    CCopasiNode<Data>(),
    mType(type),
    mValue(0.0),
    mData(data)
{}

CEvaluationNode::CEvaluationNode(const CEvaluationNode & src):
    CCopasiNode<Data>(src),
    mType(src.mType),
    mValue(src.mValue),
    mData(src.mData)
{}

CEvaluationNode::~CEvaluationNode() {}

bool CEvaluationNode::compile(const CEvaluationTree * /* pTree */)
{
  return (getChild() == NULL); // We must not have any children.;
}

CEvaluationNode::Data CEvaluationNode::getData() const
  {return mData;}

bool CEvaluationNode::setData(const Data & data)
{
  mData = data;
  return true;
}
