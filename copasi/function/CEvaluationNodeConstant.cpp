/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeConstant.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/24 21:02:37 $
   End CVS Header */

#include <string>

#include "copasi.h"
#include "mathematics.h"

#include "CEvaluationNode.h"

CEvaluationNodeConstant::CEvaluationNodeConstant():
    CEvaluationNode(CEvaluationNode::INVALID)
{}

CEvaluationNodeConstant::CEvaluationNodeConstant(const Data & data):
    CEvaluationNode(CEvaluationNode::CONSTANT)
{setData(data);}

CEvaluationNodeConstant::CEvaluationNodeConstant(const CEvaluationNodeConstant & src):
    CEvaluationNode(src)
{}

CEvaluationNodeConstant::~CEvaluationNodeConstant() {}

bool CEvaluationNodeConstant::setData(const Data & data)
{
  bool success = true;
  mData = data;

  if (mData == "pi" || mData == "PI")
    mValue = M_PI;
  else if (mData == "exponentiale" || mData == "EXPONENTIALE")
    mValue = M_E;
  else if (mData == "true" || mData == "TRUE")
    mValue = 0.0;
  else if (mData == "false" || mData == "FALSE")
    mValue = 1.0;
  else
    success = false;

  return success;
}
