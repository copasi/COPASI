/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeObject.cpp,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/07/03 10:24:36 $
   End CVS Header */

#include "copasi.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "report/CCopasiObjectName.h"
#include "report/CCopasiObject.h"
#include "report/CCopasiContainer.h"
#include "model/CModel.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeObject::CEvaluationNodeObject():
    CEvaluationNode(CEvaluationNode::INVALID, ""),
    mpValue(NULL),
    mRegisteredObjectCN("")
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeObject::CEvaluationNodeObject(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::OBJECT | subType), data),
    mpValue(NULL),
    mRegisteredObjectCN(data.substr(1, data.length() - 2))
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeObject::CEvaluationNodeObject(const CEvaluationNodeObject & src):
    CEvaluationNode(src),
    mpValue(src.mpValue),
    mRegisteredObjectCN(src.mRegisteredObjectCN)
{}

CEvaluationNodeObject::~CEvaluationNodeObject() {}

bool CEvaluationNodeObject::compile(const CEvaluationTree * pTree)
{
  mpValue = pTree->getObjectValue(mRegisteredObjectCN);

  if (mpValue == NULL) return false;

  return (getChild() == NULL); // We must not have any children.
}

CEvaluationNode::Data CEvaluationNodeObject::getData() const
{return "<" + mRegisteredObjectCN + ">";}

bool CEvaluationNodeObject::setData(const Data & data)
{
  mData = data;
  mRegisteredObjectCN = data.substr(1, data.length() - 2);

  return true;
}

std::string CEvaluationNodeObject::getInfix() const
  {return "<" + mRegisteredObjectCN + ">";}

CEvaluationNode* CEvaluationNodeObject::createNodeFromASTTree(const ASTNode& node)
{
  CEvaluationNodeObject* pNode = NULL;
  ASTNodeType_t type = node.getType();
  switch (type)
    {
    case AST_NAME:
      pNode = new CEvaluationNodeObject(ANY, CCopasiObjectName(std::string("<") + node.getName() + std::string(">")));
      break;
    case AST_NAME_TIME:
      pNode = new CEvaluationNodeObject(ANY, "<Reference=Time>");
      break;
    default:
      break;
    }
  return pNode;
}

ASTNode* CEvaluationNodeObject::toAST() const
  {
    ASTNode* node = new ASTNode();
    if (this->getData() == "<Reference=Time>")
      {
        node->setType(AST_NAME_TIME);
      }
    else
      {
        node->setType(AST_NAME);
        // since I can not get the model in which this node is located, I just
        // assume that it will always be the current global model.
        CCopasiObject* object = CCopasiContainer::ObjectFromName(mRegisteredObjectCN);
        assert(object);
        node->setName(object->getObjectName().c_str());
      }
    return node;
  }
