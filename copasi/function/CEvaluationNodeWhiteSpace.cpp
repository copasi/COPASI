/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeWhiteSpace.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/07/03 10:24:36 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"

#include "sbml/math/ASTNode.h"

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

ASTNode* CEvaluationNodeWhiteSpace::toAST() const
  {
    ASTNode* node = new ASTNode();
    return node;
  }
