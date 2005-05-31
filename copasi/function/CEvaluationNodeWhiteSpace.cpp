/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeWhiteSpace.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/31 17:48:57 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"

CEvaluationNodeWhiteSpace::CEvaluationNodeWhiteSpace():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{}

CEvaluationNodeWhiteSpace::CEvaluationNodeWhiteSpace(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::WHITESPACE | subType), data)
{}

CEvaluationNodeWhiteSpace::CEvaluationNodeWhiteSpace(const CEvaluationNodeWhiteSpace & src):
    CEvaluationNode(src)
{}

CEvaluationNodeWhiteSpace::~CEvaluationNodeWhiteSpace() {}
