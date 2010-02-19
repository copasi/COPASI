// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeDelay.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/02/19 15:15:28 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sbml/math/ASTNode.h>

#include "copasi.h"

#include "mathematics.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/utility.h"
#include "copasi/report/CCopasiRootContainer.h"

CEvaluationNodeDelay::CEvaluationNodeDelay():
    CEvaluationNode(CEvaluationNode::INVALID, ""),
    mCallNodes()
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeDelay::CEvaluationNodeDelay(const SubType & subType,
    const Data & /*data*/):
    CEvaluationNode((Type)(CEvaluationNode::DELAY | subType), "delay"),
    mCallNodes()
{
  mData = unQuote(mData);

  switch (subType)
    {
      case DELAY:
        break;

      default:
        fatalError();
        break;
    }

  mPrecedence = PRECEDENCE_FUNCTION;
}

CEvaluationNodeDelay::CEvaluationNodeDelay(const CEvaluationNodeDelay & src):
    CEvaluationNode(src),
    mCallNodes(src.mCallNodes)
{}

CEvaluationNodeDelay::~CEvaluationNodeDelay() {}

const C_FLOAT64 & CEvaluationNodeDelay::value() const
{
  C_FLOAT64 &Value = *const_cast<C_FLOAT64 *>(&mValue);

  switch (mType & 0x00FFFFFF)
    {
      case DELAY:
      default:
        return Value = std::numeric_limits<C_FLOAT64>::quiet_NaN();
        break;
    }
}

bool CEvaluationNodeDelay::compile(const CEvaluationTree * /*pTree*/)
{
  bool success = true;

  switch (mType & 0x00FFFFFF)
    {
      case DELAY:
        break;

      default:
        success = false;
        break;
    }

  return success;
}

std::string CEvaluationNodeDelay::getInfix() const
{
  std::string Infix = quote(mData, "-+^*/%(){},\t\r\n") + "(";

  switch (mType & 0x00FFFFFF)
    {
      case DELAY:
      {
        std::vector< CEvaluationNode * >::const_iterator it = mCallNodes.begin();
        std::vector< CEvaluationNode * >::const_iterator end = mCallNodes.end();

        if (it != end) Infix += (*it++)->getInfix();

        for (; it != end; ++it)
          Infix += "," + (*it)->getInfix();
      }

      break;

      default:
        return "@";
        break;
    }

  return Infix + ")";
}

std::string CEvaluationNodeDelay::getDisplayString(const CEvaluationTree * pTree) const
{
  std::string DisplayString = quote(mData, "-+^*/%(){},\t\r\n") + "(";

  switch (mType & 0x00FFFFFF)
    {
      case DELAY:
      {
        std::vector< CEvaluationNode * >::const_iterator it = mCallNodes.begin();
        std::vector< CEvaluationNode * >::const_iterator end = mCallNodes.end();

        if (it != end) DisplayString += (*it++)->getDisplayString(pTree);

        for (; it != end; ++it)
          DisplayString += "," + (*it)->getDisplayString(pTree);
      }

      break;

      default:
        return "@";
        break;
    }

  return DisplayString + ")";
}

std::string CEvaluationNodeDelay::getDisplay_C_String(const CEvaluationTree * pTree) const
{
  std::string DisplayString = quote(mData, "-+^*/%(){},\t\r\n") + "(";

  switch (mType & 0x00FFFFFF)
    {
      case DELAY:
      {
        std::vector< CEvaluationNode * >::const_iterator it = mCallNodes.begin();
        std::vector< CEvaluationNode * >::const_iterator end = mCallNodes.end();

        if (it != end) DisplayString += (*it++)->getDisplay_C_String(pTree);

        for (; it != end; ++it)
          DisplayString += "," + (*it)->getDisplay_C_String(pTree);
      }

      break;

      default:
        return "@";
        break;
    }

  return DisplayString + ")";
}

std::string CEvaluationNodeDelay::getDisplay_MMD_String(const CEvaluationTree * /* pTree */) const
{
  std::string DisplayString = quote(mData, "-+^*/%(){},\t\r\n");

  return DisplayString;
}

std::string CEvaluationNodeDelay::getDisplay_XPP_String(const CEvaluationTree * /* pTree */) const
{
  std::string DisplayString = quote(mData, "-+^*/%(){},\t\r\n");

  return DisplayString;
}

CEvaluationNode* CEvaluationNodeDelay::createNodeFromASTTree(const ASTNode& node)
{
  SubType subType = CEvaluationNodeDelay::DELAY;
  std::string data = "delay";

  CEvaluationNodeDelay* pConvertedNode = new CEvaluationNodeDelay(subType, data);
  unsigned int i, iMax = node.getNumChildren();

  for (i = 0; i < iMax; ++i)
    {
      pConvertedNode->addChild(CEvaluationTree::convertASTNode(*node.getChild(i)));
    }

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

bool CEvaluationNodeDelay::addChild(CCopasiNode< Data > * pChild,
                                    CCopasiNode< Data > * pAfter)
{
  CCopasiNode< Data >::addChild(pChild, pAfter);
  mCallNodes.push_back(static_cast<CEvaluationNode *>(pChild));

  return true;
}

bool CEvaluationNodeDelay::removeChild(CCopasiNode< Data > * pChild)
{
  std::vector<CEvaluationNode *>::iterator it = mCallNodes.begin();
  std::vector<CEvaluationNode *>::iterator end = mCallNodes.end();

  while (it != end && *it != pChild) ++it;

  if (it != end) mCallNodes.erase(it);

  return CCopasiNode< Data >::removeChild(pChild);
}

#include "utilities/copasimathml.h"

void CEvaluationNodeDelay::writeMathML(std::ostream & out,
                                       const std::vector<std::vector<std::string> > & env,
                                       bool expand,
                                       unsigned C_INT32 l) const
{
  switch (mType & 0x00FFFFFF)
    {
      case DELAY:
      {
        out << SPC(l) << "<mrow>" << std::endl;

        out << SPC(l + 1) << "<mi>" << mData << "</mi>" << std::endl;
        out << SPC(l + 1) << "<mo> &ApplyFunction; </mo>" << std::endl;
        out << SPC(l + 1) << "<mrow>" << std::endl;
        out << SPC(l + 2) << "<mo> (</mo>" << std::endl;
        out << SPC(l + 2) << "<mrow>" << std::endl;

        std::vector< CEvaluationNode * >::const_iterator it = mCallNodes.begin();
        std::vector< CEvaluationNode * >::const_iterator end = mCallNodes.end();

        if (it != end)(*it++)->writeMathML(out, env, expand, l + 3);

        for (; it != end; ++it)
          {

            out << SPC(l + 3) << "<mo> , </mo>" << std::endl;
            (*it)->writeMathML(out, env, expand, l + 3);
          }

        out << SPC(l + 2) << "</mrow>" << std::endl;
        out << SPC(l + 2) << "<mo>) </mo>" << std::endl;

        out << SPC(l + 1) << "</mrow>" << std::endl;
        out << SPC(l) << "</mrow>" << std::endl;
      }
      break;

      default:
        break;
    }

  return;
}
