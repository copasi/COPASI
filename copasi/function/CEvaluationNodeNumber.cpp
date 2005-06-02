/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeNumber.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/02 12:37:15 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"

CEvaluationNodeNumber::CEvaluationNodeNumber():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeNumber::CEvaluationNodeNumber(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::NUMBER | subType), data)
{
  char * end;
  mValue = strtod(mData.c_str(), &end);

  mPrecedence = PRECEDENCE_NUMBER;
}

CEvaluationNodeNumber::CEvaluationNodeNumber(const CEvaluationNodeNumber & src):
    CEvaluationNode(src)
{}

CEvaluationNodeNumber::~CEvaluationNodeNumber() {}
