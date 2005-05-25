/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeConstant.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/25 15:55:42 $
   End CVS Header */

#include <string>

#include "copasi.h"
#include "mathematics.h"

#include "CEvaluationNode.h"

CEvaluationNodeConstant::CEvaluationNodeConstant():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{}

CEvaluationNodeConstant::CEvaluationNodeConstant(const Type & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::NUMBER | subType), data)
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

  setData(data);
}

CEvaluationNodeConstant::CEvaluationNodeConstant(const CEvaluationNodeConstant & src):
    CEvaluationNode(src)
{}

CEvaluationNodeConstant::~CEvaluationNodeConstant() {}
