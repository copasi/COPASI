// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeCall.cpp,v $
//   $Revision: 1.46 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/16 23:11:30 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <sbml/math/ASTNode.h>

#include "copasi.h"

#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "CFunction.h"
#include "CExpression.h"
#include "CFunctionDB.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/utility.h"
#include "copasi/report/CCopasiRootContainer.h"

CEvaluationNodeCall::CEvaluationNodeCall():
    CEvaluationNode(CEvaluationNode::INVALID, ""),
    mpFunction(NULL),
    mpExpression(NULL),
    mCallNodes(),
    mpCallParameters(NULL),
    mBooleanRequired(false),
    mRegisteredFucntionCN()
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeCall::CEvaluationNodeCall(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type)(CEvaluationNode::CALL | subType), data),
    mpFunction(NULL),
    mpExpression(NULL),
    mCallNodes(),
    mpCallParameters(NULL),
    mQuotesRequired(false),
    mBooleanRequired(false),
    mRegisteredFucntionCN()
{
  setData(data);
  mData = unQuote(mData);

  // We force quoting if the round trip unquote, quote does not recover the original input
  if (mData != data && quote(mData) != data)
    {
      mQuotesRequired = true;
    }

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
    mpCallParameters(NULL),
    mQuotesRequired(src.mQuotesRequired),
    mBooleanRequired(src.mBooleanRequired)
{mpCallParameters = buildParameters(mCallNodes);}

CEvaluationNodeCall::~CEvaluationNodeCall() {}

void CEvaluationNodeCall::calculate()
{
  switch (mType & 0x00FFFFFF)
    {
      case FUNCTION:
        mValue = mpFunction->calcValue(*mpCallParameters);
        break;

      case EXPRESSION:
        mValue = mpExpression->calcValue();
        break;

      default:
        mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
        break;
    }
}

bool CEvaluationNodeCall::compile(const CEvaluationTree * pTree)
{
  bool success = true;
  clearParameters(mpCallParameters, mCallNodes);

  CObjectInterface * pObjectInterface = NULL;

  if (mRegisteredFucntionCN != "")
    {
      pObjectInterface = const_cast< CObjectInterface * >(CCopasiRootContainer::getRoot()->getObject(mRegisteredFucntionCN));
    }

  switch (mType & 0x00FFFFFF)
    {
      case FUNCTION:

        if (pObjectInterface != NULL)
          {
            mpFunction = dynamic_cast< CFunction * >(pObjectInterface);
          }
        else
          {
            mpFunction =
              dynamic_cast<CFunction *>(CCopasiRootContainer::getFunctionList()->findFunction(mData));
          }

        if (!mpFunction) return false;

        mRegisteredFucntionCN = mpFunction->getCN();

        // We need to check whether the provided arguments match the on needed by the
        // function;
        if (!verifyParameters(mCallNodes, mpFunction->getVariables())) return false;

        mpCallParameters = buildParameters(mCallNodes);
        break;

      case EXPRESSION:

        if (pObjectInterface != NULL)
          {
            mpExpression = dynamic_cast<CExpression *>(pObjectInterface);
          }
        else
          {
            mpExpression =
              dynamic_cast<CExpression *>(CCopasiRootContainer::getFunctionList()->findFunction(mData));
          }

        if (!mpExpression)
          {
            // We may have a function with no arguments the parser is not able to distinguish
            // between that and an expression.
            if (pObjectInterface != NULL)
              {
                mpFunction = dynamic_cast< CFunction * >(pObjectInterface);
              }
            else
              {
                mpFunction =
                  dynamic_cast<CFunction *>(CCopasiRootContainer::getFunctionList()->findFunction(mData));
              }

            if (!mpFunction) return false;

            mRegisteredFucntionCN = mpFunction->getCN();

            mType = (CEvaluationNode::Type)(CEvaluationNode::CALL | FUNCTION);
            success = compile(pTree);
          }
        else
          {
            mRegisteredFucntionCN = mpExpression->getCN();

            success = mpExpression->compile(static_cast<const CExpression *>(pTree)->getListOfContainer());
          }

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
    CCopasiRootContainer::getFunctionList()->findFunction(mData);

  if (pTree) return pTree->calls(list);

  return false;
}

// virtual
const CEvaluationNode::Data & CEvaluationNodeCall::getData() const
{
  std::string Data;

  if (mpFunction != NULL)
    {
      Data = mpFunction->getObjectName();
      mQuotesRequired = mpFunction->getObjectName() != unQuote(quote(Data));

      return mpFunction->getObjectName();
    }

  if (mpExpression != NULL)
    {
      Data = mpExpression->getObjectName();
      mQuotesRequired = mpExpression->getObjectName() != unQuote(quote(Data));

      return mpExpression->getObjectName();
    }

  return mData;
}

// virtual
bool CEvaluationNodeCall::setData(const Data & data)
{
  mData = unQuote(data);

  // We force quoting if the round trip unquote, quote does not recover the original input
  if (mData != data && quote(mData) != data)
    {
      mQuotesRequired = true;
    }

  mRegisteredFucntionCN = std::string("");

  return true;
}


// virtual
std::string CEvaluationNodeCall::getInfix(const std::vector< std::string > & children) const
{
  std::string Infix;

  const std::string & Data = getData();

  if (mQuotesRequired)
    {
      Infix = "\"" + quote(Data, "-+^*/%(){},\t\r\n\"") + "\"(";
    }
  else
    {
      Infix = quote(Data, "-+^*/%(){},\t\r\n") + "(";
    }

  switch (mType & 0x00FFFFFF)
    {
      case FUNCTION:
      {
        std::vector< std::string >::const_iterator it = children.begin();
        std::vector< std::string>::const_iterator end = children.end();

        if (it != end) Infix += *it++;

        for (; it != end; ++it)
          Infix += "," + *it;
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

// virtual
std::string CEvaluationNodeCall::getDisplayString(const std::vector< std::string > & children) const
{
  std::string DisplayString;

  if (mQuotesRequired)
    {
      DisplayString = "\"" + quote(mData, "-+^*/%(){},\t\r\n\"") + "\"(";
    }
  else
    {
      DisplayString = quote(mData, "-+^*/%(){},\t\r\n") + "(";
    }

  switch (mType & 0x00FFFFFF)
    {
      case FUNCTION:
      {
        std::vector< std::string >::const_iterator it = children.begin();
        std::vector< std::string >::const_iterator end = children.end();

        if (it != end) DisplayString += *it++;

        for (; it != end; ++it)
          DisplayString += "," + *it;
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

// virtual
std::string CEvaluationNodeCall::getCCodeString(const std::vector< std::string > & children) const
{
  std::string DisplayString;

  if (mQuotesRequired)
    {
      DisplayString = "\"" + quote(mData, "-+^*/%(){},\t\r\n\"") + "\"(";
    }
  else
    {
      DisplayString = quote(mData, "-+^*/%(){},\t\r\n") + "(";
    }

  switch (mType & 0x00FFFFFF)
    {
      case FUNCTION:
      {
        std::vector< std::string >::const_iterator it = children.begin();
        std::vector< std::string >::const_iterator end = children.end();

        if (it != end) DisplayString += *it++;

        for (; it != end; ++it)
          DisplayString += "," + *it;
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

// virtual
std::string CEvaluationNodeCall::getBerkeleyMadonnaString(const std::vector< std::string > & children) const
{
  std::string DisplayString;

  if (mQuotesRequired)
    {
      DisplayString = "\"" + quote(mData, "-+^*/%(){},\t\r\n\"") + "\"(";
    }
  else
    {
      DisplayString = quote(mData, "-+^*/%(){},\t\r\n") + "(";
    }

  return DisplayString;
}

// virtual
std::string CEvaluationNodeCall::getXPPString(const std::vector< std::string > & /* children */) const
{
  std::string DisplayString;

  if (mQuotesRequired)
    {
      DisplayString = "\"" + quote(mData, "-+^*/%(){},\t\r\n\"") + "\"(";
    }
  else
    {
      DisplayString = quote(mData, "-+^*/%(){},\t\r\n") + "(";
    }

  return DisplayString;
}

// static
CEvaluationNode * CEvaluationNodeCall::fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children)
{
  assert(pASTNode->getNumChildren() == children.size());

  SubType subType = CEvaluationNodeCall::FUNCTION;
  std::string data = pASTNode->getName();

  CEvaluationNodeCall * pNode = new CEvaluationNodeCall(subType, data);

  pNode->addChildren(children);

  return pNode;
}

ASTNode* CEvaluationNodeCall::toAST(const CCopasiDataModel* pDataModel) const
{
  ASTNode* pNode = NULL;

  pNode = new ASTNode(AST_FUNCTION);
  const std::string funName = this->getData();
  CFunction * pFun = CCopasiRootContainer::getFunctionList()->findFunction(funName);
  assert(pFun != NULL);

  if (pFun == NULL || pFun->getSBMLId().empty()) fatalError();

  pNode->setName(pFun->getSBMLId().c_str());

  const CEvaluationNode* child = static_cast<const CEvaluationNode*>(this->getChild());

  while (child)
    {
      pNode->addChild(child->toAST(pDataModel));
      child = static_cast<const CEvaluationNode*>(child->getSibling());
    }

  return pNode;
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
  size_t i;

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

  size_t i;

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

  size_t i;

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
      case EXPRESSION:
        return CCopasiRootContainer::getFunctionList()->findFunction(mData);

      default:
        return NULL;
    }
}

#include "utilities/copasimathml.h"

// virtual
std::string CEvaluationNodeCall::getMMLString(const std::vector< std::string > & children,
    bool expand,
    const std::vector< std::vector< std::string > > & /* variables */) const
{
  std::ostringstream out;

  std::vector< std::string >::const_iterator it = children.begin();
  std::vector< std::string >::const_iterator end = children.end();

  switch (mType & 0x00FFFFFF)
    {
      case FUNCTION:
      {

        if (!expand || !mpFunction)
          {
            out << "<mrow>" << std::endl;

            out << "<mi>" << CMathMl::fixName(mData) << "</mi>" << std::endl;
            out << "<mrow>" << std::endl;
            out << "<mo>(</mo>" << std::endl;
            out << "<mrow>" << std::endl;

            if (it != end)
              {
                out << *it++;
              }

            for (; it != end; ++it)
              {
                out << "<mo> , </mo>" << std::endl;
                out << *it;
              }

            out << "</mrow>" << std::endl;
            out << "<mo>) </mo>" << std::endl;

            out << "</mrow>" << std::endl;
            out << "</mrow>" << std::endl;
          }
        else
          {
            std::vector< std::vector< std::string > > Variables;

            for (; it != end; ++it)
              {
                std::vector< std::string > Variable;
                Variable.push_back(*it);
                Variables.push_back(Variable);
              }

            out << "<mfenced>" << std::endl;
            out << mpFunction->writeMathML(Variables, expand, expand);
            out << "</mfenced>" << std::endl;
          }
      }
      break;

      case EXPRESSION:
        break;
      default:
        break;
    }

  return out.str();
}

void CEvaluationNodeCall::setBooleanRequired(const bool & booleanRequired)
{mBooleanRequired = booleanRequired;}

const bool & CEvaluationNodeCall::isBooleanRequired() const
{return mBooleanRequired;}

// virtual
bool CEvaluationNodeCall::isBoolean() const
{
  const CEvaluationTree * pEvaluationTree = getCalledTree();

  if (pEvaluationTree != NULL)
    {
      return pEvaluationTree->isBoolean();
    }

  return false;
}
