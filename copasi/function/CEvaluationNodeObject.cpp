/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeObject.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/02 12:37:15 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "report/CCopasiObjectName.h"

CEvaluationNodeObject::CEvaluationNodeObject():
    CEvaluationNode(CEvaluationNode::INVALID, ""),
    mpValue(NULL)
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeObject::CEvaluationNodeObject(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::OBJECT | subType), data),
    mpValue(NULL)
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeObject::CEvaluationNodeObject(const CEvaluationNodeObject & src):
    CEvaluationNode(src),
    mpValue(src.mpValue)
{}

CEvaluationNodeObject::~CEvaluationNodeObject() {}

bool CEvaluationNodeObject::compile(const CEvaluationTree * pTree)
{
  mpValue = pTree->getObjectValue(mData);

  if (mpValue == NULL) return false;

  return (getChild() == NULL); // We must not have any children.
}
