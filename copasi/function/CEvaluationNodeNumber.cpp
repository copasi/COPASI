/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeNumber.cpp,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/02 17:49:39 $
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

  switch (subType)
    {
    case DOUBLE:
    case INTEGER:
    case ENOTATION:
      mValue = strtod(mData.c_str(), NULL);
      break;

    case RATIONALE:
      mValue = strtod(mData.c_str(), &end);
      end++;
      mValue /= strtod(end, NULL);
      break;
    }

  mPrecedence = PRECEDENCE_NUMBER;
}

CEvaluationNodeNumber::CEvaluationNodeNumber(const CEvaluationNodeNumber & src):
    CEvaluationNode(src)
{}

CEvaluationNodeNumber::~CEvaluationNodeNumber() {}
