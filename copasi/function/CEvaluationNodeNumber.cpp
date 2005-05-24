/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeNumber.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/24 18:06:17 $
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
  char * end;
  mValue = strtod(data.c_str(), &end);
  return (*end == NULL);
}
