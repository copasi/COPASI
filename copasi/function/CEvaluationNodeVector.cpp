/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeVector.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/07/13 22:50:08 $
   End CVS Header */

#include "copasi.h"

#include "mathematics.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeVector::CEvaluationNodeVector():
    CEvaluationNode((Type) (CEvaluationNode::VECTOR), ""),
    mVector()
{mPrecedence = PRECEDENCE_FUNCTION;}

CEvaluationNodeVector::CEvaluationNodeVector(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::VECTOR | subType), data),
    mVector()
{
  switch (subType)
    {
    case VECTOR:
      break;

    default:
      fatalError();
      break;
    }

  mPrecedence = PRECEDENCE_FUNCTION;
}

CEvaluationNodeVector::CEvaluationNodeVector(const CEvaluationNodeVector & src):
    CEvaluationNode(src),
    mVector(src.mVector)
{}

CEvaluationNodeVector::~CEvaluationNodeVector() {}

const C_FLOAT64 & CEvaluationNodeVector::value() const
  {
    std::vector< CEvaluationNode * >::const_iterator it = mVector.begin();
    std::vector< CEvaluationNode * >::const_iterator end = mVector.end();

    for (; it != end; ++it)
      (*it)->value();

    return mValue;
  }

bool CEvaluationNodeVector::compile(const CEvaluationTree * /* pTree */)
{return true;}

std::string CEvaluationNodeVector::getInfix() const
  {
    std::string Infix = "{";

    std::vector< CEvaluationNode * >::const_iterator it = mVector.begin();
    std::vector< CEvaluationNode * >::const_iterator end = mVector.end();

    if (it != end) Infix += (*it++)->getInfix();

    for (; it != end; ++it)
      Infix += "," + (*it)->getInfix();

    return Infix + "}";
  }

CEvaluationNode* CEvaluationNodeVector::createNodeFromASTTree(const ASTNode& node)
{
  // :TODO:
  SubType subType;
  std::string data = "";

  CEvaluationNodeVector* convertedNode = new CEvaluationNodeVector(subType, data);
  return convertedNode;
}

ASTNode* CEvaluationNodeVector::toAST() const
  {
    // :TODO:
    ASTNode* node = new ASTNode(AST_FUNCTION_PIECEWISE);
    return node;
  }

bool CEvaluationNodeVector::addChild(CCopasiNode< Data > * pChild,
                                     CCopasiNode< Data > * pAfter)
{
  CCopasiNode< Data >::addChild(pChild, pAfter);
  mVector.push_back(static_cast<CEvaluationNode *>(pChild));

  return true;
}

const std::vector< CEvaluationNode * > & CEvaluationNodeVector::getVector() const
  {return mVector;}
