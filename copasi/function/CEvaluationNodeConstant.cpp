/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeConstant.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/02 12:37:15 $
   End CVS Header */

#include <string>

#include "copasi.h"
#include "mathematics.h"

#include "CEvaluationNode.h"

CEvaluationNodeConstant::CEvaluationNodeConstant():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeConstant::CEvaluationNodeConstant(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::CONSTANT | subType), data)
{
  switch ((SubType) subType)
    {
    case PI:
      mValue = M_PI;
      break;

    case EXPONENTIALE:
      mValue = M_PI;
      break;

    case TRUE:
      mValue = 1.0;
      break;

    case FALSE:
      mValue = 0.0;
      break;

    default:
      mValue = 0.0; // :TODO: this should be NaN
      break;
    }

  mPrecedence = PRECEDENCE_NUMBER;
}

CEvaluationNodeConstant::CEvaluationNodeConstant(const CEvaluationNodeConstant & src):
    CEvaluationNode(src)
{}

CEvaluationNodeConstant::~CEvaluationNodeConstant() {}
