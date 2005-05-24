/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNode.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/24 18:06:16 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"

CEvaluationNode * CEvaluationNode::create(const Type & type,
    const std::string & contents)
{
  CEvaluationNode * pNode = NULL;

  switch (type)
    {
    case CEvaluationNode::NUMBER:
      pNode = new CEvaluationNodeNumber(contents);
      break;

    default:
      break;
    }

  return pNode;
}

CEvaluationNode::CEvaluationNode():
    CCopasiNode<Data>(),
    mType(CEvaluationNode::INVALID),
    mValue(0.0),
    mData("")
{}

CEvaluationNode::CEvaluationNode(const Type & type):
    CCopasiNode<Data>(),
    mType(type),
    mValue(0.0),
    mData("")
{}

CEvaluationNode::CEvaluationNode(const CEvaluationNode & src):
    CCopasiNode<Data>(src),
    mType(src.mType),
    mValue(src.mValue),
    mData(src.mData)
{}

CEvaluationNode::~CEvaluationNode() {}

CEvaluationNode::Data CEvaluationNode::getData() const
  {return mData;}
