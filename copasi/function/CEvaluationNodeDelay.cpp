// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sbml/math/ASTNode.h>

#include "copasi.h"

#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/utility.h"
#include "copasi/report/CCopasiRootContainer.h"

CEvaluationNodeDelay::CEvaluationNodeDelay():
  CEvaluationNode(CEvaluationNode::INVALID, ""),
  mpDelayValue(NULL),
  mpDelayLag(NULL)
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeDelay::CEvaluationNodeDelay(const SubType & subType,
    const Data & /* data */):
  CEvaluationNode((Type)(CEvaluationNode::DELAY | subType), "delay"),
  mpDelayValue(NULL),
  mpDelayLag(NULL)
{
  switch (subType)
    {
      case DELAY:
        mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
        break;

      default:
        fatalError();
        break;
    }

  mPrecedence = PRECEDENCE_FUNCTION;
}

CEvaluationNodeDelay::CEvaluationNodeDelay(const CEvaluationNodeDelay & src):
  CEvaluationNode(src),
  mpDelayValue(NULL),
  mpDelayLag(NULL)
{}

CEvaluationNodeDelay::~CEvaluationNodeDelay() {}

bool CEvaluationNodeDelay::compile(const CEvaluationTree * /*pTree*/)
{
  bool success = true;

  switch (mType & 0x00FFFFFF)
    {
      case DELAY:
        mpDelayValue = static_cast<CEvaluationNode *>(getChild());

        if (mpDelayValue == NULL) return false;

        mpDelayLag = static_cast<CEvaluationNode *>(mpDelayValue->getSibling());

        if (mpDelayLag == NULL) return false;

        return (mpDelayLag->getSibling() == NULL); // We must have exactly 2 children

        break;

      default:
        success = false;
        break;
    }

  return success;
}

// virtual
std::string CEvaluationNodeDelay::getInfix(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeDelay*>(this)->compile(NULL))
    {
      switch (mType & 0x00FFFFFF)
        {
          case DELAY:
            return mData + "(" + children[0] + "," + children[1] + ")";
            break;

          default:
            break;
        }
    }

  return "@";
}

// virtual
std::string CEvaluationNodeDelay::getDisplayString(const std::vector< std::string > & children) const
{
  switch (mType & 0x00FFFFFF)
    {
      case DELAY:
        return mData + "(" + children[0] + "," + children[1] + ")";
        break;

      default:
        break;
    }

  return "@";
}

// virtual
std::string CEvaluationNodeDelay::getCCodeString(const std::vector< std::string > & children) const
{
  switch (mType & 0x00FFFFFF)
    {
      case DELAY:
        return mData + "(" + children[0] + "," + children[1] + ")";
        break;

      default:
        break;
    }

  return "@";
}

// virtual
std::string CEvaluationNodeDelay::getBerkeleyMadonnaString(const std::vector< std::string > & children) const
{
  switch (mType & 0x00FFFFFF)
    {
      case DELAY:
        return mData + "(" + children[0] + "," + children[1] + ")";
        break;

      default:
        break;
    }

  return "@";
}

// virtual
std::string CEvaluationNodeDelay::getXPPString(const std::vector< std::string > & children) const
{
  switch (mType & 0x00FFFFFF)
    {
      case DELAY:
        return mData + "(" + children[0] + "," + children[1] + ")";
        break;

      default:
        break;
    }

  return "@";
}

// static
CEvaluationNode * CEvaluationNodeDelay::fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children)
{
  assert(pASTNode->getNumChildren() == children.size());

  size_t i = 0, iMax = children.size();

  SubType subType = CEvaluationNodeDelay::DELAY;
  std::string data = "delay";

  CEvaluationNode * pConvertedNode = new CEvaluationNodeDelay(subType, data);

  for (i = 0; i < iMax; ++i)
    {
      pConvertedNode->addChild(children[i]);
    }

  pConvertedNode->compile(NULL);
  return pConvertedNode;
}

ASTNode* CEvaluationNodeDelay::toAST(const CCopasiDataModel* pDataModel) const
{
  ASTNode* pNode = new ASTNode(AST_FUNCTION_DELAY);
  const CEvaluationNode* child = static_cast<const CEvaluationNode*>(this->getChild());

  while (child)
    {
      pNode->addChild(child->toAST(pDataModel));
      child = static_cast<const CEvaluationNode*>(child->getSibling());
    }

  return pNode;
}

#include "utilities/copasimathml.h"

// virtual
std::string CEvaluationNodeDelay::getMMLString(const std::vector< std::string > & children,
    bool /* expand */,
    const std::vector< std::vector< std::string > > & /* variables */) const
{
  std::ostringstream out;

  switch (mType & 0x00FFFFFF)
    {
      case DELAY:
        out << "<mrow>" << std::endl;

        out << "<mi>" << mData << "</mi>" << std::endl;
        out << "<mrow>" << std::endl;
        out << "<mo> (</mo>" << std::endl;
        out << "<mrow>" << std::endl;

        out << children[0];

        out << "<mo> , </mo>" << std::endl;

        out << children[1];

        out << "</mrow>" << std::endl;
        out << "<mo>) </mo>" << std::endl;

        out << "</mrow>" << std::endl;
        out << "</mrow>" << std::endl;
        break;

      default:
        break;
    }

  return out.str();
}
