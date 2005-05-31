/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeStructure.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/31 17:48:57 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"

CEvaluationNodeStructure::CEvaluationNodeStructure():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{}

CEvaluationNodeStructure::CEvaluationNodeStructure(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::STRUCTURE | subType), data)
{}

CEvaluationNodeStructure::CEvaluationNodeStructure(const CEvaluationNodeStructure & src):
    CEvaluationNode(src)
{}

CEvaluationNodeStructure::~CEvaluationNodeStructure() {}
