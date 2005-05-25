/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeNumber.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/25 15:55:42 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"

CEvaluationNodeNumber::CEvaluationNodeNumber():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{}

CEvaluationNodeNumber::CEvaluationNodeNumber(const Type & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::NUMBER | subType), data)
{
  char * end;
  mValue = strtod(mData.c_str(), &end);
}

CEvaluationNodeNumber::CEvaluationNodeNumber(const CEvaluationNodeNumber & src):
    CEvaluationNode(src)
{}

CEvaluationNodeNumber::~CEvaluationNodeNumber() {}
