/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeNumber.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/24 21:03:40 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"

CEvaluationNodeNumber::CEvaluationNodeNumber():
    CEvaluationNode(CEvaluationNode::INVALID)
{}

CEvaluationNodeNumber::CEvaluationNodeNumber(const Data & data):
    CEvaluationNode(CEvaluationNode::NUMBER)
{setData(data);}

CEvaluationNodeNumber::CEvaluationNodeNumber(const CEvaluationNodeNumber & src):
    CEvaluationNode(src)
{}

CEvaluationNodeNumber::~CEvaluationNodeNumber() {}

bool CEvaluationNodeNumber::setData(const Data & data)
{
  mData = data;

  char * end;
  mValue = strtod(mData.c_str(), &end);
  return (*end == NULL);
}
