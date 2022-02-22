// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <sbml/math/ASTNode.h>

#include "copasi/copasi.h"

#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "CFunction.h"
#include "CExpression.h"
#include "CFunctionDB.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/utilities/utility.h"
#include "copasi/utilities/CUnitValidator.h"
#include "copasi/core/CRootContainer.h"

CEvaluationNodeCall::CEvaluationNodeCall()
  : CEvaluationNode(MainType::CALL, SubType::INVALID, "")
  , mpFunction(NULL)
  , mpExpression(NULL)
  , mCallNodes()
  , mpCallParameters(NULL)
  , mQuotesRequired(false)
  , mRegisteredFunctionCN()
  , mCompiledSubType(SubType::INVALID)
{
  mPrecedence = PRECEDENCE_NUMBER;
}

CEvaluationNodeCall::CEvaluationNodeCall(const SubType & subType,
    const Data & data)
  : CEvaluationNode(MainType::CALL, subType, data)
  , mpFunction(NULL)
  , mpExpression(NULL)
  , mCallNodes()
  , mpCallParameters(NULL)
  , mQuotesRequired(false)
  , mRegisteredFunctionCN()
  , mCompiledSubType(SubType::INVALID)
{
  setData(data);

  switch (subType)
    {
      case SubType::FUNCTION:
      case SubType::EXPRESSION:
        break;

      default:
        fatalError();
        break;
    }

  mPrecedence = PRECEDENCE_FUNCTION;
}

CEvaluationNodeCall::CEvaluationNodeCall(const CEvaluationNodeCall & src)
  : CEvaluationNode(src)
  , mpFunction(src.mpFunction)
  , mpExpression(src.mpExpression)
  , mCallNodes(src.mCallNodes)
  , mpCallParameters(NULL)
  , mQuotesRequired(src.mQuotesRequired)
  , mRegisteredFunctionCN(src.mRegisteredFunctionCN)
  , mCompiledSubType(src.mCompiledSubType)
{
  mpCallParameters = buildParameters(mCallNodes);
}

CEvaluationNodeCall::~CEvaluationNodeCall()
{
  clearParameters(mpCallParameters, mCallNodes);
}

void CEvaluationNodeCall::calculate()
{
  switch (mCompiledSubType)
    {
      case SubType::FUNCTION:
        mValue = mpFunction->calcValue(*mpCallParameters);
        break;

      case SubType::EXPRESSION:
        mValue = mpExpression->calcValue();
        break;

      default:
        mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
        break;
    }
}

CIssue CEvaluationNodeCall::compile()
{
  CIssue issue = CIssue::Success;
  clearParameters(mpCallParameters, mCallNodes);

  CObjectInterface * pObjectInterface = NULL;

  if (mRegisteredFunctionCN != "")
    {
      pObjectInterface = const_cast< CObjectInterface * >(CRootContainer::getRoot()->getObject(mRegisteredFunctionCN));
    }

  mCompiledSubType = mSubType;

  switch (mCompiledSubType)
    {
      case SubType::FUNCTION:

        if (pObjectInterface != NULL)
          {
            mpFunction = dynamic_cast< CFunction * >(pObjectInterface);
          }
        else
          {
            mpFunction =
              dynamic_cast<CFunction *>(CRootContainer::getFunctionList()->findFunction(mData));
          }

        if (!mpFunction)
          {
            mCompiledSubType = SubType::INVALID;
            return CIssue(CIssue::eSeverity::Error, CIssue::eKind::CFunctionNotFound);
          }

        mRegisteredFunctionCN = mpFunction->getCN();

        // We need to check whether the provided arguments match the one needed by the
        // function;
        if (!verifyParameters(mCallNodes, mpFunction->getVariables()))
          {
            return CIssue(CIssue::eSeverity::Error, CIssue::eKind::VariablesMismatch);
          }

        if (mpFunction->isBoolean())
          issue &= setValueType(ValueType::Boolean);
        else if (mValueType == ValueType::Boolean)
          issue &= CIssue(CIssue::eSeverity::Error, CIssue::eKind::ValueTypeMismatch);

        mpCallParameters = buildParameters(mCallNodes);
        break;

      case SubType::EXPRESSION:

        if (pObjectInterface != NULL)
          {
            mpExpression = dynamic_cast<CExpression *>(pObjectInterface);
          }
        else
          {
            mpExpression =
              dynamic_cast<CExpression *>(CRootContainer::getFunctionList()->findFunction(mData));
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
                  dynamic_cast<CFunction *>(CRootContainer::getFunctionList()->findFunction(mData));
              }

            if (!mpFunction)
              {
                mCompiledSubType = SubType::DEFAULT;
                return CIssue(CIssue::eSeverity::Error, CIssue::eKind::CFunctionNotFound);
              }

            mRegisteredFunctionCN = mpFunction->getCN();

            mMainType = MainType::CALL;
            mSubType = SubType::FUNCTION; // need to set subtype, otherwise it is an infinite loop
            mCompiledSubType = SubType::FUNCTION; // need to set compiled subtype so that calculate() works

            issue = compile();
          }
        else
          {
            // This is not really needed since expression cannot be called
            fatalError();
          }

        break;

      default:
        issue = CIssue::Error;
        break;
    }

  return issue;
}

// virtual
CIssue CEvaluationNodeCall::setValueType(const ValueType & valueType)
{
  if (mValueType == ValueType::Unknown)
    {
      mValueType = valueType;
    }

  return CEvaluationNode::setValueType(valueType);
}

bool CEvaluationNodeCall::calls(std::set< std::string > & list) const
{
  if (list.count(mData)) return true;

  CEvaluationTree * pTree =
    CRootContainer::getFunctionList()->findFunction(mData);

  if (pTree) return pTree->calls(list);

  return false;
}

// virtual
const CEvaluationNode::Data & CEvaluationNodeCall::getData() const
{
  // We determine whether quoting is required here since we can not be sure
  // that the original infix is correct.

  std::string Data;

  if (isKeyword(mData))
    {
      mQuotesRequired = true;
    }

  if (mpFunction != NULL)
    {
      Data = mpFunction->getObjectName();
      mQuotesRequired |= mpFunction->getObjectName() != unQuote(quote(Data));

      return mpFunction->getObjectName();
    }

  if (mpExpression != NULL)
    {
      Data = mpExpression->getObjectName();
      mQuotesRequired |= mpExpression->getObjectName() != unQuote(quote(Data));

      return mpExpression->getObjectName();
    }

  return mData;
}

// virtual
bool CEvaluationNodeCall::setData(const Data & data)
{
  mData = unQuote(data);

  // We force quoting if the round trip unquote, quote does not recover the original input
  if (isKeyword(mData))
    {
      mQuotesRequired = true;
    }

  if (mData != data && quote(mData) != data)
    {
      mQuotesRequired = true;
    }

  mRegisteredFunctionCN = std::string("");

  return true;
}

// virtual
std::string CEvaluationNodeCall::getInfix(const std::vector< std::string > & children) const
{
  std::string Infix;

  //We use getData instead of mData since getData also detects whether quoting is needed.
  const std::string & Data = getData();

  Infix = quote(Data, "-+^*/%(){},\t\r\n\\") + "(";

  switch (mSubType)
    {
      case SubType::FUNCTION:
      case SubType::DEFAULT:
      {
        std::vector< std::string >::const_iterator it = children.begin();
        std::vector< std::string>::const_iterator end = children.end();

        if (it != end) Infix += *it++;

        for (; it != end; ++it)
          Infix += "," + *it;
      }

      break;

      case SubType::EXPRESSION:
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

  DisplayString = quote(mData, "-+^*/%(){},\t\r\n") + "(";

  switch (mSubType)
    {
      case SubType::FUNCTION:
      {
        std::vector< std::string >::const_iterator it = children.begin();
        std::vector< std::string >::const_iterator end = children.end();

        if (it != end) DisplayString += *it++;

        for (; it != end; ++it)
          DisplayString += "," + *it;
      }

      break;

      case SubType::EXPRESSION:
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

  std::string Data;

  if (mData.empty())
    Data = getData();
  else
    Data = mData;

  if (mQuotesRequired)
    {
      DisplayString = "\"" + quote(Data, "-+^*/%(){},\t\r\n\"") + "\"(";
    }
  else
    {
      DisplayString = quote(Data, "-+^*/%(){},\t\r\n") + "(";
    }

  switch (mSubType)
    {
      case SubType::FUNCTION:
      {

        std::vector< std::string >::const_iterator it = children.begin();
        std::vector< std::string >::const_iterator end = children.end();

        if (it != end) DisplayString += *it++;

        for (; it != end; ++it)
          DisplayString += "," + *it;
      }

      break;

      case SubType::EXPRESSION:
        break;

      default:
        return "@";
        break;
    }

  return DisplayString + ")";
}

// virtual
std::string CEvaluationNodeCall::getBerkeleyMadonnaString(const std::vector< std::string > & /* children */) const
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

  SubType subType = SubType::FUNCTION;
  std::string data = pASTNode->getName();

  CEvaluationNodeCall * pNode = new CEvaluationNodeCall(subType, data);

  pNode->addChildren(children);

  return pNode;
}

ASTNode* CEvaluationNodeCall::toAST(const CDataModel* pDataModel) const
{
  ASTNode* pNode = NULL;

  pNode = new ASTNode(AST_FUNCTION);
  const std::string funName = this->getData();
  CFunction * pFun = CRootContainer::getFunctionList()->findFunction(funName);
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

  if (pAfter == NULL)
    {
      mCallNodes.push_back(static_cast<CEvaluationNode *>(pChild));
      return true;
    }

  std::vector<CEvaluationNode *>::iterator it = mCallNodes.begin();

  if (pAfter != this)
    {
      std::vector<CEvaluationNode *>::iterator end = mCallNodes.end();

      while (it != end && *it != pAfter) ++it;
    }

  mCallNodes.insert(it, static_cast<CEvaluationNode *>(pChild));

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
      if ((*it)->mainType() == CEvaluationNode::MainType::VECTOR)
        (*pCallParameters)[i].vector = buildParameters(static_cast<const CEvaluationNodeVector *>(*it)->getNodes());
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
      if ((*it)->mainType() == CEvaluationNode::MainType::VECTOR)
        clearParameters((*pCallParameters)[i].vector,
                        static_cast<const CEvaluationNodeVector *>(*it)->getNodes());
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
      if (((*it)->mainType() == CEvaluationNode::MainType::VECTOR &&
           functionParameters[i]->getType() != CFunctionParameter::DataType::VFLOAT64) ||
          functionParameters[i]->getType() == CFunctionParameter::DataType::VFLOAT64)
        return false;
    }

  return true;
}

const CFunction * CEvaluationNodeCall::getCalledTree() const
{
  switch (mSubType)
    {
      case SubType::FUNCTION:
      case SubType::EXPRESSION:
        return CRootContainer::getFunctionList()->findFunction(mData);

      default:
        return NULL;
    }
}

CFunction * CEvaluationNodeCall::getCalledTree()
{
  switch (mSubType)
    {
      case SubType::FUNCTION:
      case SubType::EXPRESSION:
        return CRootContainer::getFunctionList()->findFunction(mData);

      default:
        return NULL;
    }
}

#include "copasi/utilities/copasimathml.h"

// virtual
std::string CEvaluationNodeCall::getMMLString(const std::vector< std::string > & children,
    bool expand,
    const std::vector< std::vector< std::string > > & /* variables */) const
{
  std::ostringstream out;

  std::vector< std::string >::const_iterator it = children.begin();
  std::vector< std::string >::const_iterator end = children.end();

  switch (mSubType)
    {
      case SubType::FUNCTION:
      {

        if (!expand || !mpFunction)
          {
            out << "<mrow>" << std::endl;

            out << "<mi>" << CMathMl::fixName(quote(mData, "-+^*/%(){},\t\r\n")) << "</mi>" << std::endl;
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

      case SubType::EXPRESSION:
        break;

      default:
        break;
    }

  return out.str();
}

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

CValidatedUnit CEvaluationNodeCall::getUnit(const CMathContainer & math,
    const std::vector< CValidatedUnit > & units) const
{
  CEvaluationTree * pTree = NULL;

  switch (mSubType)
    {
      case SubType::FUNCTION:
        pTree = mpFunction;
        break;

      case SubType::EXPRESSION:
        pTree = mpExpression;
        break;

      default:
        return CValidatedUnit();
        break;
    }

  if (!pTree)
    return CValidatedUnit();

  CUnitValidator Validator(math, *pTree);
  Validator.validateUnits(CValidatedUnit(CBaseUnit::undefined, false), units);

  return Validator.getUnit();
}

// virtual
CValidatedUnit CEvaluationNodeCall::setUnit(const CMathContainer & container,
    const std::map < CEvaluationNode *, CValidatedUnit > & currentUnits,
    std::map < CEvaluationNode *, CValidatedUnit > & targetUnits) const
{
  CEvaluationTree * pTree = NULL;

  switch (mSubType)
    {
      case SubType::FUNCTION:
        pTree = mpFunction;
        break;

      case SubType::EXPRESSION:
        pTree = mpExpression;
        break;

      default:
        return CValidatedUnit();
        break;
    }

  if (!pTree)
    return CValidatedUnit();

  // Retrieve the current units of the variables
  std::vector< CEvaluationNode * >::const_iterator it = mCallNodes.begin();
  std::vector< CEvaluationNode * >::const_iterator end = mCallNodes.end();

  std::vector< CValidatedUnit > CurrentVariableUnits(mCallNodes.size());
  std::vector< CValidatedUnit >::iterator itUnit = CurrentVariableUnits.begin();

  for (; it != end; ++it, ++itUnit)
    {
      *itUnit = currentUnits.find(const_cast< CEvaluationNode * >(*it))->second;
    }

  CUnitValidator Validator(container, *pTree);

  Validator.validateUnits(CEvaluationNode::setUnit(container, currentUnits, targetUnits),
                          CurrentVariableUnits);

  std::vector< CValidatedUnit >::const_iterator itValidatedVariableUnit = Validator.getVariableUnits().begin();

  for (it = mCallNodes.begin(); it != end; ++it, ++itValidatedVariableUnit)
    {
      std::map < CEvaluationNode *, CValidatedUnit >::iterator found = targetUnits.find(const_cast< CEvaluationNode * >(*it));

      if (found == targetUnits.end())
        {
          found = targetUnits.insert(std::make_pair(const_cast< CEvaluationNode * >(*it), CValidatedUnit(CBaseUnit::undefined, false))).first;
        }

      found->second = CValidatedUnit::merge(found->second, *itValidatedVariableUnit);
    }

  return Validator.getUnit();
}
