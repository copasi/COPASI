/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeCall.cpp,v $
   $Revision: 1.20 $
   $Name:  $
   $Author: nsimus $
   $Date: 2006/08/15 11:39:31 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <sbml/math/ASTNode.h>

#include "copasi.h"

#include "mathematics.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "CFunction.h"
#include "CExpression.h"
#include "CFunctionDB.h"
#include "CopasiDataModel/CCopasiDataModel.h"

CEvaluationNodeCall::CEvaluationNodeCall():
    CEvaluationNode(CEvaluationNode::INVALID, ""),
    mpFunction(NULL),
    mpExpression(NULL),
    mCallNodes(),
    mpCallParameters(NULL)
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeCall::CEvaluationNodeCall(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::CALL | subType), data),
    mpFunction(NULL),
    mpExpression(NULL),
    mCallNodes(),
    mpCallParameters(NULL)
{
  switch (subType)
    {
    case FUNCTION:
    case EXPRESSION:
      break;

    default:
      fatalError();
      break;
    }

  mPrecedence = PRECEDENCE_FUNCTION;
}

CEvaluationNodeCall::CEvaluationNodeCall(const CEvaluationNodeCall & src):
    CEvaluationNode(src),
    mpFunction(src.mpFunction),
    mpExpression(src.mpExpression),
    mCallNodes(src.mCallNodes),
    mpCallParameters(NULL)
{mpCallParameters = buildParameters(mCallNodes);}

CEvaluationNodeCall::~CEvaluationNodeCall() {}

const C_FLOAT64 & CEvaluationNodeCall::value() const
  {
    C_FLOAT64 &Value = *const_cast<C_FLOAT64 *>(&mValue);
    switch (mType & 0x00FFFFFF)
      {
      case FUNCTION:
        {
          std::vector< CEvaluationNode * >::const_iterator it = mCallNodes.begin();
          std::vector< CEvaluationNode * >::const_iterator end = mCallNodes.end();

          for (; it != end; ++it) (*it)->value();
        }
        return Value = mpFunction->calcValue(*mpCallParameters);
        break;

      case EXPRESSION:
        return Value = mpExpression->calcValue();
        break;

      default:
        return Value = std::numeric_limits<C_FLOAT64>::quiet_NaN();
        break;
      }
  }

bool CEvaluationNodeCall::compile(const CEvaluationTree * pTree)
{
  bool success = true;

  switch (mType & 0x00FFFFFF)
    {
    case FUNCTION:
      mpFunction =
        dynamic_cast<CFunction *>(CCopasiDataModel::Global->getFunctionList()->findFunction(mData));
      if (!mpFunction) return false;

      // We need to check whether the provided arguments match the on needed by the
      // function;
      if (!verifyParameters(mCallNodes, mpFunction->getVariables())) return false;

      clearParameters(mpCallParameters, mCallNodes);
      mpCallParameters = buildParameters(mCallNodes);

      break;

    case EXPRESSION:
      mpExpression =
        dynamic_cast<CExpression *>(CCopasiDataModel::Global->getFunctionList()->findFunction(mData));
      if (!mpExpression)
        {
          // We may have a function with no arguments the parser is not able to destinguish
          // between that and an expression.
          mpFunction =
            dynamic_cast<CFunction *>(CCopasiDataModel::Global->getFunctionList()->findFunction(mData));
          if (!mpFunction) return false;

          mType = (CEvaluationNode::Type) (CEvaluationNode::CALL | FUNCTION);

          success = compile(pTree);
        }
      else
        success = mpExpression->compile(static_cast<const CExpression *>(pTree)->getListOfContainer());

      break;

    default:
      success = false;
      break;
    }

  return success;
}

bool CEvaluationNodeCall::calls(std::set< std::string > & list) const
  {
    if (list.count(mData)) return true;

    CEvaluationTree * pTree =
      CCopasiDataModel::Global->getFunctionList()->findFunction(mData);

    if (pTree) return pTree->calls(list);

    return false;
  }

std::string CEvaluationNodeCall::getInfix() const
  {
    std::string Infix = mData + "(";
    switch (mType & 0x00FFFFFF)
      {
      case FUNCTION:
        {
          std::vector< CEvaluationNode * >::const_iterator it = mCallNodes.begin();
          std::vector< CEvaluationNode * >::const_iterator end = mCallNodes.end();

          if (it != end) Infix += (*it++)->getInfix();

          for (; it != end; ++it)
            Infix += "," + (*it)->getInfix();
        }

        break;

      case EXPRESSION:
        break;

      default:
        return "@";
        break;
      }
    return Infix + ")";
  }

std::string CEvaluationNodeCall::getDisplayString(const CEvaluationTree * pTree) const
  {
    std::string DisplayString = mData + "(";
    switch (mType & 0x00FFFFFF)
      {
      case FUNCTION:
        {
          std::vector< CEvaluationNode * >::const_iterator it = mCallNodes.begin();
          std::vector< CEvaluationNode * >::const_iterator end = mCallNodes.end();

          if (it != end) DisplayString += (*it++)->getDisplayString(pTree);

          for (; it != end; ++it)
            DisplayString += "," + (*it)->getDisplayString(pTree);
        }

        break;

      case EXPRESSION:
        break;

      default:
        return "@";
        break;
      }
    return DisplayString + ")";
  }

std::string CEvaluationNodeCall::getDisplay_C_String(const CEvaluationTree * pTree) const
  {
    std::string DisplayString = mData + "(";
    switch (mType & 0x00FFFFFF)
      {
      case FUNCTION:
        {
          std::vector< CEvaluationNode * >::const_iterator it = mCallNodes.begin();
          std::vector< CEvaluationNode * >::const_iterator end = mCallNodes.end();

          if (it != end) DisplayString += (*it++)->getDisplay_C_String(pTree);

          for (; it != end; ++it)
            DisplayString += "," + (*it)->getDisplay_C_String(pTree);
        }

        break;

      case EXPRESSION:
        break;

      default:
        return "@";
        break;
      }
    return DisplayString + ")";
  }

std::string CEvaluationNodeCall::getDisplay_MMD_String(const CEvaluationTree * pTree) const
  {
    std::string DisplayString = mData;

    return DisplayString;
  }

std::string CEvaluationNodeCall::getDisplay_XPP_String(const CEvaluationTree * pTree) const
  {
    std::string DisplayString = mData;

    return DisplayString;
  }

CEvaluationNode* CEvaluationNodeCall::createNodeFromASTTree(const ASTNode& node)
{
  SubType subType = CEvaluationNodeCall::FUNCTION;
  std::string data = node.getName();

  CEvaluationNodeCall* convertedNode = new CEvaluationNodeCall(subType, data);
  unsigned int i, iMax = node.getNumChildren();
  for (i = 0; i < iMax;++i)
    {
      convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getChild(i)));
    }
  return convertedNode;
}

ASTNode* CEvaluationNodeCall::toAST() const
  {
    ASTNode* node = new ASTNode(AST_FUNCTION);
    const std::string funName = this->getData();
    CEvaluationTree* pFun = CCopasiDataModel::Global->getFunctionList()->findFunction(funName);
    if (pFun->getSBMLId() != "")
      {
        node->setName(pFun->getSBMLId().c_str());
      }
    else
      {
        node->setName(funName.c_str());
        pFun->setSBMLId(funName);
      }
    const CEvaluationNode* child = static_cast<const CEvaluationNode*>(this->getChild());
    while (child)
      {
        node->addChild(child->toAST());
        child = static_cast<const CEvaluationNode*>(child->getSibling());
      }
    return node;
  }

bool CEvaluationNodeCall::addChild(CCopasiNode< Data > * pChild,
                                   CCopasiNode< Data > * pAfter)
{
  CCopasiNode< Data >::addChild(pChild, pAfter);
  mCallNodes.push_back(static_cast<CEvaluationNode *>(pChild));

  return true;
}

bool CEvaluationNodeCall::removeChild(CCopasiNode< Data > * pChild)
{
  std::vector<CEvaluationNode *>::iterator it = mCallNodes.begin();
  std::vector<CEvaluationNode *>::iterator end = mCallNodes.end();

  while (it != end && *it != pChild) ++it;
  if (it != end) mCallNodes.erase(it);

  return CCopasiNode< Data >::removeChild(pChild);
}

CCallParameters< C_FLOAT64 > *
CEvaluationNodeCall::buildParameters(const std::vector<CEvaluationNode *> & vector)
{
  std::vector<CEvaluationNode *>::const_iterator it = vector.begin();
  std::vector<CEvaluationNode *>::const_iterator end = vector.end();

  CCallParameters< C_FLOAT64 > * pCallParameters =
    new CCallParameters< C_FLOAT64 >(vector.size());
  unsigned C_INT32 i;
  for (i = 0; it != end; ++it, i++)
    {
      if (type((*it)->getType()) == CEvaluationNode::VECTOR)
        (*pCallParameters)[i].vector = buildParameters(static_cast<const CEvaluationNodeVector *>(*it)->getVector());
      else
        (*pCallParameters)[i].value = (*it)->getValuePointer();
    }

  return pCallParameters;
}

void
CEvaluationNodeCall::clearParameters(CCallParameters< C_FLOAT64 > * pCallParameters,
                                     const std::vector<CEvaluationNode *> & vector)
{
  if (!pCallParameters) return;

  std::vector<CEvaluationNode *>::const_iterator it = vector.begin();
  std::vector<CEvaluationNode *>::const_iterator end = vector.end();

  unsigned C_INT32 i;
  for (i = 0; it != end; ++it, i++)
    {
      if (type((*it)->getType()) == CEvaluationNode::VECTOR)
        clearParameters((*pCallParameters)[i].vector,
                        static_cast<const CEvaluationNodeVector *>(*it)->getVector());
    }

  delete pCallParameters;
  return;
}

bool
CEvaluationNodeCall::verifyParameters(const std::vector<CEvaluationNode *> & vector,
                                      const CFunctionParameters & functionParameters)
{
  if (vector.size() != functionParameters.size()) return false;

  std::vector<CEvaluationNode *>::const_iterator it = vector.begin();
  std::vector<CEvaluationNode *>::const_iterator end = vector.end();

  unsigned C_INT32 i;

  for (i = 0; it != end; ++it, i++)
    {
      if ((type((*it)->getType()) == CEvaluationNode::VECTOR &&
           functionParameters[i]->getType() != CFunctionParameter::VFLOAT64) ||
          functionParameters[i]->getType() == CFunctionParameter::VFLOAT64)
        return false;
    }

  return true;
}

const CEvaluationTree * CEvaluationNodeCall::getCalledTree() const
  {
    switch (mType & 0x00FFFFFF)
      {
      case FUNCTION:
        return mpFunction;

      case EXPRESSION:
        return mpExpression;

      default:
        return NULL;
      }
  }

#include "utilities/copasimathml.h"

void CEvaluationNodeCall::writeMathML(std::ostream & out,
                                      const std::vector<std::vector<std::string> > & env,
                                      bool expand,
                                      unsigned C_INT32 l) const
  {
    switch (mType & 0x00FFFFFF)
      {
      case FUNCTION:
        {

#if 0
          if (!expand)
            {
#endif
              out << SPC(l) << "<mrow>" << std::endl;

              out << SPC(l + 1) << "<mi>" << mData << "</mi>" << std::endl;
              out << SPC(l + 1) << "<mo> &ApplyFunction; </mo>" << std::endl;
              out << SPC(l + 1) << "<mrow>" << std::endl;
              out << SPC(l + 2) << "<mo> (</mo>" << std::endl;
              out << SPC(l + 2) << "<mrow>" << std::endl;

              std::vector< CEvaluationNode * >::const_iterator it = mCallNodes.begin();
              std::vector< CEvaluationNode * >::const_iterator end = mCallNodes.end();

              if (it != end) (*it++)->writeMathML(out, env, expand, l + 3);

              for (; it != end; ++it)
                {

                  out << SPC(l + 3) << "<mo> , </mo>" << std::endl;
                  (*it)->writeMathML(out, env, expand, l + 3);
                }

              out << SPC(l + 2) << "</mrow>" << std::endl;
              out << SPC(l + 2) << "<mo>) </mo>" << std::endl;

              out << SPC(l + 1) << "</mrow>" << std::endl;
              out << SPC(l) << "</mrow>" << std::endl;
#if 0
            }
          // else  :TODO
#endif
        }
        break;

      case EXPRESSION:
        break;

      default:
        break;
      }

    return;
  }
