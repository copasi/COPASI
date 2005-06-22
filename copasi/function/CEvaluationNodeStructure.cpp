/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeStructure.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/22 16:14:27 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"

CEvaluationNodeStructure::CEvaluationNodeStructure():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{}

CEvaluationNodeStructure::CEvaluationNodeStructure(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::STRUCTURE | subType), data)
{
  switch (subType)
    {
    case OPEN:
      mPrecedence = PRECEDENCE_STRUCTURE_OPEN;
      break;

    case COMMA:
      mPrecedence = PRECEDENCE_STRUCTURE_COMMA;
      break;

    case CLOSE:
      mPrecedence = PRECEDENCE_STRUCTURE_CLOSE;
      break;

    case INVALID:
      fatalError();
      break;
    }
}

CEvaluationNodeStructure::CEvaluationNodeStructure(const CEvaluationNodeStructure & src):
    CEvaluationNode(src)
{}

CEvaluationNodeStructure::~CEvaluationNodeStructure() {}
