/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeCall.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/07/15 14:21:35 $
   End CVS Header */

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
    mEvaluationTreeName(""),
    mpFunction(NULL),
    mpExpression(NULL),
    mCallNodes(),
    mpCallParameters(NULL)
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeCall::CEvaluationNodeCall(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::FUNCTION | subType), data),
    mEvaluationTreeName(""),
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
    mEvaluationTreeName(src.mEvaluationTreeName),
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
        dynamic_cast<CFunction *>(CCopasiDataModel::Global->getFunctionList()->findFunction(mEvaluationTreeName));
      if (!mpFunction) return false;
      clearParameters(mpCallParameters, mCallNodes);
      mpCallParameters = buildParameters(mCallNodes);
      break;

    case EXPRESSION:
      mpExpression =
        dynamic_cast<CExpression *>(CCopasiDataModel::Global->getFunctionList()->findFunction(mEvaluationTreeName));
      if (!mpExpression) return false;
      if (!mpExpression->compile(static_cast<const CExpression *>(pTree)->getListOfContainer())) return false;
      break;

    default:
      success = false;
      break;
    }

  return success;
}

std::string CEvaluationNodeCall::getInfix() const
  {
    std::string Infix = mData + "(" + mEvaluationTreeName;
    switch (mType & 0x00FFFFFF)
      {
      case FUNCTION:
        Infix += "(";

        {
          std::vector< CEvaluationNode * >::const_iterator it = mCallNodes.begin();
          std::vector< CEvaluationNode * >::const_iterator end = mCallNodes.end();

          if (it != end) Infix += (*it++)->getInfix();

          for (; it != end; ++it)
            Infix += "," + (*it)->getInfix();
        }

        return Infix + "))";
        break;

      case EXPRESSION:
        return Infix + ")";
        break;

      default:
        return "@";
        break;
      }
  }

CEvaluationNode* CEvaluationNodeCall::createNodeFromASTTree(const ASTNode& node)
{
  SubType subType;
  std::string data = "";

  CEvaluationNodeCall* convertedNode = new CEvaluationNodeCall(subType, data);
  return convertedNode;
}

ASTNode* CEvaluationNodeCall::toAST() const
  {
    ASTNode* node = new ASTNode(AST_FUNCTION_PIECEWISE);
    return node;
  }

void CEvaluationNodeCall::setEvaluationTreeName(const std::string & name)
{mEvaluationTreeName = name;}

bool CEvaluationNodeCall::addChild(CCopasiNode< Data > * pChild,
                                   CCopasiNode< Data > * pAfter)
{
  CCopasiNode< Data >::addChild(pChild, pAfter);
  mCallNodes.push_back(static_cast<CEvaluationNode *>(pChild));

  return true;
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
        (*pCallParameters)[i].vector =
          buildParameters(static_cast<const CEvaluationNodeVector *>(*it)->getVector());
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
