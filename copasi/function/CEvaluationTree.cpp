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

#include "copasi/copasi.h"

#include <sstream>
#include <vector>
#include <algorithm>

#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "CFunction.h"
#include "CExpression.h"
#include "CEvaluationLexer.h"
#include "CFunctionDB.h"

#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CDataObjectReference.h"
#include "sbml/math/ASTNode.h"
#include "copasi/utilities/CCopasiTree.h"
#include "copasi/utilities/CNodeIterator.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/core/CDataObject.h"
#include "copasi/math/CMathObject.h"

const std::string CEvaluationTree::TypeName[] =
{
  "userdefined",
  "predefined",
  "predefined",
  "userdefined",
  "userdefined",
  "userdefined",
  "internal",
  ""
};

const char* CEvaluationTree::XMLType[] =
{
  "Function",
  "MassAction",
  "PreDefined",
  "UserDefined",
  "Expression",
  "Boolean",
  "MathExpression",
  NULL
};

CEvaluationTree *
CEvaluationTree::create(CEvaluationTree::Type type)
{
  CEvaluationTree * pNew = NULL;

  switch (type)
    {
      case Function:
        pNew = new CFunction();
        break;

      case MassAction:
        pNew = new CMassAction();
        break;

      case PreDefined:
        pNew = new CKinFunction();
        pNew->setType(PreDefined);
        break;

      case UserDefined:
        pNew = new CKinFunction();
        break;

      case Expression:
        pNew = new CExpression();
        break;

      default:
        fatalError();
        break;
    }

  return pNew;
}

CEvaluationTree *
CEvaluationTree::copy(const CEvaluationTree & src)
{
  CEvaluationTree * pNew = NULL;

  switch (src.getType())
    {
      case Function:
        pNew = new CFunction(*static_cast<const CFunction *>(&src), NO_PARENT);
        break;

      case MassAction:
        pNew = new CMassAction(*static_cast<const CMassAction *>(&src), NO_PARENT);
        break;

      case PreDefined:
      case UserDefined:
        pNew = new CKinFunction(*static_cast<const CKinFunction *>(&src), NO_PARENT);
        break;

      case Expression:
        pNew = new CExpression(*static_cast<const CExpression *>(&src), NO_PARENT);
        break;

      default:
        fatalError();
        break;
    }

  return pNew;
}

CEvaluationTree * CEvaluationTree::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  CEvaluationTree * pNew = create((CEvaluationTree::Type) data.getProperty(CData::EVALUATION_TREE_TYPE).toUint());

  if (pNew != NULL)
    {
      pNew->setObjectName(data.getProperty(CData::OBJECT_NAME).toString());
    }

  return pNew;
}

// virtual
CData CEvaluationTree::toData() const
{
  CData Data = CDataContainer::toData();

  // TODO CRITICAL Implement me!
  // fatalError();

  return Data;
}

// virtual
bool CEvaluationTree::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = CDataContainer::applyData(data, changes);

  // TODO CRITICAL Implement me!
  // fatalError();

  return success;
}

CEvaluationTree::CEvaluationTree(const std::string & name,
                                 const CDataContainer * pParent,
                                 const CEvaluationTree::Type & type)
  : CDataContainer(name, pParent, "Function")
  , mType(type)
  , mInfix()
  , mErrorPosition(std::string::npos)
  , mpNodeList(NULL)
  , mpRootNode(NULL)
  , mpRootValue(NULL)
  , mValue(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
  , mCalculationSequence()
{
  initObjects();
  setInfix("");
}

CEvaluationTree::CEvaluationTree(const CEvaluationTree & src,
                                 const CDataContainer * pParent)
  : CDataContainer(src, pParent)
  , mType(src.mType)
  , mInfix()
  , mErrorPosition(std::string::npos)
  , mpNodeList(NULL)
  , mpRootNode(NULL)
  , mpRootValue(NULL)
  , mValue(src.mValue)
  , mCalculationSequence()
{
  initObjects();
  setInfix(src.mInfix);
}

CEvaluationTree::~CEvaluationTree()
{
  clearNodes();
}

const CEvaluationTree::Type & CEvaluationTree::getType() const
{return mType;}

void CEvaluationTree::setType(const CEvaluationTree::Type & type)
{
  mType = type;
}

CIssue CEvaluationTree::setInfix(const std::string & infix)
{
  CIssue issue;

  if (infix != mInfix)
    {
      mValidity.clear();

      // We assume until proven otherwise that the tree is not usable
      issue = CIssue::Error;

      // Assume whatever (non null) string which was there before,
      // is still ok.
      if (infix == mInfix &&
          infix != "")
        {
          return issue = CIssue::Success;
        }

      mInfix = infix;

      issue = parse();
    }

  return issue;
}

const std::string & CEvaluationTree::getInfix() const
{return mInfix;}

bool CEvaluationTree::operator == (const CEvaluationTree & rhs) const
{
  return (mInfix == rhs.mInfix && mType == rhs.mType);
}

std::string::size_type CEvaluationTree::getErrorPosition() const
{return mErrorPosition;}

const std::vector< CEvaluationNode * > & CEvaluationTree::getNodeList() const
{
  if (!mpNodeList)
    const_cast<CEvaluationTree *>(this)->mpNodeList = new std::vector< CEvaluationNode * >;

  return *mpNodeList;
}

size_t CEvaluationTree::getVariableIndex(const std::string & /*name*/) const
{return C_INVALID_INDEX;}

const C_FLOAT64 & CEvaluationTree::getVariableValue(const size_t & /*index*/) const
{
  static C_FLOAT64 Value = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  return Value;
}

CIssue CEvaluationTree::parse()
{
  // clean up
  clearNodes();

  // Clear all mValidity flags which might be set here.
  mValidity.remove(CValidity::Severity::All,
                   CValidity::Kind(CIssue::eKind::ExpressionInvalid) | CIssue::eKind::HasCircularDependency);

  if (mType == MassAction)
    {
      return CIssue::Success;
    }

  CIssue lastIssue; // Default: CIssue::Success

  if (mInfix == "")
    {
      mpNodeList = new std::vector< CEvaluationNode * >;
      mpRootNode = new CEvaluationNode();
      mpRootNode->setTree(this);

      mpRootValue = mpRootNode->getValuePointer();
      mValue = *mpRootValue;
      mpNodeList->push_back(mpRootNode);

      return lastIssue;
    }

  // parse the description into a linked node tree
  std::istringstream buffer(mInfix);
  CEvaluationLexer Parser(&buffer);

  if (Parser.yyparse() != 0)
    {
      lastIssue = CIssue(CIssue::eSeverity::Error, CIssue::eKind::ExpressionInvalid);
      mValidity.add(lastIssue);
    }

  mpNodeList = Parser.getNodeList();
  mpRootNode = Parser.getRootNode();

  if (mpRootNode != NULL)
    {
      mpRootNode->setTree(this);
      mpRootValue = mpRootNode->getValuePointer();
      mValue = *mpRootValue;
    }
  else
    {
      mpRootValue = NULL;
      mValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
    }

  // clean up if parsing failed
  if (!lastIssue)
    {
      mErrorPosition = Parser.getErrorPosition();
      clearNodes();
    }
  else if (hasCircularDependency())
    {
      lastIssue = CIssue(CIssue::eSeverity::Error, CIssue::eKind::HasCircularDependency);
      mValidity.add(lastIssue);
      CCopasiMessage(CCopasiMessage::ERROR, MCFunction + 4, mErrorPosition);
    }

  return lastIssue;
}

CIssue CEvaluationTree::compile()
{return compileNodes();}

bool CEvaluationTree::isBoolean() const
{
  if (mpRootNode != NULL)
    return mpRootNode->isBoolean();

  return false;
}

void CEvaluationTree::buildCalculationSequence()
{
  CNodeIterator < CEvaluationNode > itNode(mpRootNode);
  std::vector< CEvaluationNode * > CalculationSequence;

  if (mpRootNode != NULL)
    while (itNode.next() != itNode.end())
      {
        switch (itNode->mainType())
          {
            case CEvaluationNode::MainType::NUMBER:
            case CEvaluationNode::MainType::CONSTANT:
            case CEvaluationNode::MainType::OBJECT:
            case CEvaluationNode::MainType::UNIT:
              break;

            default:
              CalculationSequence.push_back(*itNode);
              break;
          }
      }

  mCalculationSequence.resize(CalculationSequence.size());
  CEvaluationNode ** ppIt = mCalculationSequence.begin();
  CEvaluationNode ** ppEnd = mCalculationSequence.end();

  std::vector< CEvaluationNode * >::const_iterator it = CalculationSequence.begin();

  for (; ppIt != ppEnd; ++ppIt, ++it)
    {
      *ppIt = *it;
    }
}

CIssue CEvaluationTree::compileNodes()
{
  mPrerequisits.clear();
  mCalculationSequence.resize(0);

  // Clear all mValidity flags, except those only set via setInfix
  mValidity.remove(CValidity::Severity::All,
                   ~(CValidity::Kind(CIssue::eKind::ExpressionInvalid) |
                     CIssue::eKind::HasCircularDependency |
                     CIssue::eKind::ExpressionDataTypeInvalid));

  if (mInfix == "")
    {
      return mValidity.getFirstWorstIssue();
    }

  if (mpNodeList == NULL)
    {
      mValidity.add(CIssue(CIssue::eSeverity::Error, CIssue::eKind::StructureInvalid));
      return mValidity.getFirstWorstIssue();
    }

  // The compile order must be child first.
  CNodeIterator< CEvaluationNode > itNode(mpRootNode);
  CEvaluationNode *pErrorNode = NULL;

  CIssue firstWorstIssue, nodeIssue;

  while (itNode.next() != itNode.end())
    if (*itNode != NULL &&
        !(nodeIssue = itNode->compile()))
      {
        mValidity.add(nodeIssue);
        firstWorstIssue &= nodeIssue;

        // Set the first encountered node error.
        if (pErrorNode == NULL)
          {
            pErrorNode = *itNode;
          }
      }

  if (mpRootNode == NULL)
    {
      mValidity.add(CIssue(CIssue::eSeverity::Error, CIssue::eKind::StructureInvalid));
      return mValidity.getFirstWorstIssue();
    }

  // Compile may change the value pointer of the root node.
  mpRootValue = mpRootNode->getValuePointer();
  mValue = *mpRootValue;

  std::vector< CEvaluationNode * >::iterator it;
  std::vector< CEvaluationNode * >::iterator end = mpNodeList->end();

  if (!firstWorstIssue)
    {
      // Find the error node in the node list
      for (it = mpNodeList->begin(); it != end; ++it)
        {
          if (*it == pErrorNode)
            {
              end = it + 1;
              break;
            }
        }

      mErrorPosition = 0;

      for (it = mpNodeList->begin(); it != end; ++it)
        mErrorPosition += (*it)->getData().length();

      mErrorPosition -= (*--it)->getData().length();

      std::stringstream str;
      str << getObjectName();

      if (getObjectParent() != NULL)
        str << " of element '" << getObjectParent()->getObjectName() << "'";

      CCopasiMessage(CCopasiMessage::ERROR, MCFunction + 3, str.str().c_str(), mErrorPosition);
    }
  else
    {
      for (it = mpNodeList->begin(); it != end; ++it)
        switch ((*it)->mainType())
          {
            case CEvaluationNode::MainType::CALL:
              mPrerequisits.insert(static_cast< CEvaluationNodeCall *>(*it)->getCalledTree());
              break;

            default:
              break;
          }

      buildCalculationSequence();
    }

  return firstWorstIssue;
}

void CEvaluationTree::calculate()
{
  try
    {
      if (mpRootNode != NULL && mValidity.getFirstWorstIssue().isSuccess())
        {
          CEvaluationNode ** ppIt = mCalculationSequence.begin();
          CEvaluationNode ** ppEnd = mCalculationSequence.end();

          for (; ppIt != ppEnd; ++ppIt)
            {
              (*ppIt)->calculate();
            }

          mValue = *mpRootValue;
        }
      else
        {
          mValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
        }
    }

  catch (...)
    {
      mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
    }
}

/**
 * Convenient function to free the list of generated nodes.
 */
void CEvaluationTree::clearNodes()
{
  if (mpNodeList == NULL)
    {
      return;
    }

  std::vector< CEvaluationNode * >::iterator it = mpNodeList->begin();
  std::vector< CEvaluationNode * >::iterator end = mpNodeList->end();

  for (; it != end; ++it)
    if (*it && (*it)->getParent())
      (*it)->getParent()->removeChild(*it);

  for (it = mpNodeList->begin(); it != end; ++it)
    pdelete(*it);

  pdelete(mpNodeList);

  mpRootNode = NULL;
  mpRootValue = NULL;
  mValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
}

bool CEvaluationTree::setRoot(CEvaluationNode* pRootNode)
{
  if (pRootNode == NULL) return false;

  assert(pRootNode->getParent() == NULL);

  clearNodes();

  mpRootNode = pRootNode;
  mpRootNode->setTree(this);

  return updateTree();
}

CIssue CEvaluationTree::updateTree()
{
  CIssue issue; //Default: CIssue::Success

  if (mpRootNode == NULL)
    {
      clearNodes();

      if (!mInfix.empty())
        {
          issue = CIssue(CIssue::eSeverity::Error, CIssue::eKind::StructureInvalid);
          mValidity.add(issue);
        }

      return issue;
    }

  mpRootValue = mpRootNode->getValuePointer();
  mValue = *mpRootValue;

  if (mpNodeList == NULL)
    {
      mpNodeList = new std::vector< CEvaluationNode * >;
    }

  // Clear the list but preserve the tree
  mpNodeList->clear();

  CCopasiTree<CEvaluationNode>::iterator it = mpRootNode;
  CCopasiTree<CEvaluationNode>::iterator end = NULL;

  for (; it != end; ++it)
    mpNodeList->push_back(&*it);

  mInfix = mpRootNode->buildInfix();

  // Clear any infix-determined flags, assuming
  // buildInfix does the right things.
  mValidity.remove(CValidity::Severity::All,
                   CValidity::Kind(CIssue::eKind::ExpressionInvalid) | CIssue::eKind::HasCircularDependency);

  return issue;
}

// virtual
const CObjectInterface * CEvaluationTree::getNodeObject(const CCommonName & CN) const
{
  if (CN == "Reference=Avogadro Constant")
    return CRootContainer::getFunctionList()->getObject(CN);

  return getObjectFromCN(CN);
}

bool CEvaluationTree::setTree(const ASTNode& pRootNode, bool isFunction)
{
  bool success = setRoot(CEvaluationTree::fromAST(&pRootNode, isFunction));

  // The compile order must be child first.
  CNodeIterator< CEvaluationNode > itNode(mpRootNode);
  CEvaluationNode *pErrorNode = NULL;

  bool UpdateTree = false;

  while (itNode.next() != itNode.end())
    if (*itNode != NULL &&
        itNode->compile() == CIssue(CIssue::eSeverity::Error, CIssue::eKind::ValueTypeMismatch))
      {
        // Attempt to convert child nodes to the appropriate type;
        CEvaluationNode::ValueType TargetType = itNode->getValueType();
        CEvaluationNode * pNode = static_cast< CEvaluationNode * >(itNode->getChild());

        while (pNode != NULL)
          {
            if (!pNode->setValueType(TargetType))
              {
                switch (TargetType)
                  {
                    case CEvaluationNode::ValueType::Number:
                    {
                      CEvaluationNode * pBoolean = pNode;
                      pNode = new CEvaluationNodeChoice(CEvaluationNode::SubType::IF, "if");
                      itNode->addChild(pNode, pBoolean);
                      itNode->removeChild(pBoolean);

                      pNode->addChild(pBoolean);
                      pNode->addChild(new CEvaluationNodeNumber(1.0));
                      pNode->addChild(new CEvaluationNodeNumber(0.0));

                      UpdateTree = true;
                    }
                    break;

                    case CEvaluationNode::ValueType::Boolean:
                    case CEvaluationNode::ValueType::Unknown:
                      // We do not convert to these type yet
                      break;
                  }
              }

            pNode = static_cast< CEvaluationNode * >(pNode->getSibling());
          }
      }

  if (UpdateTree)
    {
      success &= updateTree();
    }

  return success;
}

CEvaluationNode * CEvaluationTree::fromAST(const ASTNode * pASTNode, bool isFunction)
{
  if (pASTNode == NULL) return NULL;

  CNodeContextIterator< const ASTNode, std::vector< CEvaluationNode * > > itNode(pASTNode);
  CEvaluationNode* pResultNode = NULL;

  while (itNode.next() != itNode.end())
    {
      if (*itNode != NULL)
        {
          CCopasiMessage Message;

          switch (itNode->getType())
            {
              case AST_LAMBDA:
                // this nodetype will never be handled directly
                break;

              case AST_PLUS:
              case AST_MINUS:
              case AST_TIMES:
              case AST_DIVIDE:
              case AST_POWER:
              case AST_FUNCTION_POWER:
                // create a CEvaluationNodeOperator
                pResultNode = CEvaluationNodeOperator::fromAST(*itNode, itNode.context());
                break;

              case AST_INTEGER:
              case AST_REAL:
              case AST_REAL_E:
              case AST_RATIONAL:
                // create a CEvaluationNodeNumber
                pResultNode = CEvaluationNodeNumber::fromAST(*itNode, itNode.context());
                break;

              case AST_NAME:

                if (isFunction)
                  pResultNode = CEvaluationNodeVariable::fromAST(*itNode, itNode.context());
                else
                  pResultNode = CEvaluationNodeObject::fromAST(*itNode, itNode.context());

                break;

              case AST_NAME_TIME:

                if (isFunction)
                  {
                    fatalError();
                  }
                else
                  pResultNode = CEvaluationNodeObject::fromAST(*itNode, itNode.context());

                break;

              case AST_NAME_AVOGADRO:

                // create a CEvaluationNodeObject
                pResultNode = CEvaluationNodeObject::fromAST(*itNode, itNode.context());
                break;

              case AST_CONSTANT_E:
              case AST_CONSTANT_PI:
              case AST_CONSTANT_FALSE:
              case AST_CONSTANT_TRUE:
                // create a CEvaluationNodeConstant
                pResultNode = CEvaluationNodeConstant::fromAST(*itNode, itNode.context());
                break;

              case AST_FUNCTION:
                // create a function call node
                pResultNode = CEvaluationNodeCall::fromAST(*itNode, itNode.context());
                break;

              case AST_FUNCTION_DELAY:
                // create a function call node
                pResultNode = CEvaluationNodeDelay::fromAST(*itNode, itNode.context());
                break;

              case AST_FUNCTION_ABS:
              case AST_FUNCTION_ARCCOS:
              case AST_FUNCTION_ARCCOSH:
              case AST_FUNCTION_ARCCOT:
              case AST_FUNCTION_ARCCOTH:
              case AST_FUNCTION_ARCCSC:
              case AST_FUNCTION_ARCCSCH:
              case AST_FUNCTION_ARCSEC:
              case AST_FUNCTION_ARCSECH:
              case AST_FUNCTION_ARCSIN:
              case AST_FUNCTION_ARCSINH:
              case AST_FUNCTION_ARCTAN:
              case AST_FUNCTION_ARCTANH:
              case AST_FUNCTION_CEILING:
              case AST_FUNCTION_COS:
              case AST_FUNCTION_COSH:
              case AST_FUNCTION_COT:
              case AST_FUNCTION_COTH:
              case AST_FUNCTION_CSC:
              case AST_FUNCTION_CSCH:
              case AST_FUNCTION_EXP:
              case AST_FUNCTION_FACTORIAL:
              case AST_FUNCTION_FLOOR:
              case AST_FUNCTION_LN:
              case AST_FUNCTION_LOG:
              case AST_FUNCTION_ROOT:
              case AST_FUNCTION_SEC:
              case AST_FUNCTION_SECH:
              case AST_FUNCTION_SIN:
              case AST_FUNCTION_SINH:
              case AST_FUNCTION_TAN:
              case AST_FUNCTION_TANH:
              case AST_LOGICAL_NOT:
                pResultNode = CEvaluationNodeFunction::fromAST(*itNode, itNode.context());
                break;

              case AST_LOGICAL_AND:
              case AST_LOGICAL_OR:
              case AST_LOGICAL_XOR:
              case AST_RELATIONAL_EQ:
              case AST_RELATIONAL_GEQ:
              case AST_RELATIONAL_GT:
              case AST_RELATIONAL_LEQ:
              case AST_RELATIONAL_LT:
              case AST_RELATIONAL_NEQ:
                pResultNode = CEvaluationNodeLogical::fromAST(*itNode, itNode.context());
                break;

              case AST_FUNCTION_PIECEWISE:
                pResultNode = CEvaluationNodeChoice::fromAST(*itNode, itNode.context());
                break;

              case AST_UNKNOWN:
                // create an unknown element error
                Message = CCopasiMessage(CCopasiMessage::EXCEPTION, MCMathML + 2);

                break;
            }

          if (itNode.parentContextPtr() != NULL)
            {
              itNode.parentContextPtr()->push_back(pResultNode);
            }
        }
    }

  return pResultNode;
}

const CEvaluationNode* CEvaluationTree::getRoot() const
{
  return mpRootNode;
}

CEvaluationNode* CEvaluationTree::getRoot()
{
  return mpRootNode;
}

void CEvaluationTree::initObjects()
{
  addObjectReference("Value", mValue);
}

ASTNode* CEvaluationTree::toAST(const CDataModel* pDataModel) const
{
  return mpRootNode->toAST(pDataModel);
}

bool CEvaluationTree::hasCircularDependency() const
{
  std::set< std::string > List;

  return calls(List);
}

bool CEvaluationTree::calls(std::set< std::string > & list) const
{
  if (!mpNodeList) return false;

  std::pair<std::set< std::string >::iterator, bool> Result = list.insert(getObjectName());

  if (!Result.second) return true;

  bool Calls = false;
  std::vector< CEvaluationNode * >::iterator it;
  std::vector< CEvaluationNode * >::iterator end = mpNodeList->end();

  for (it = mpNodeList->begin(); it != end; ++it)
    if (((*it)->mainType()) == CEvaluationNode::MainType::CALL &&
        dynamic_cast<CEvaluationNodeCall *>(*it)->calls(list))
      {
        Calls = true;
        break;
      }

  list.erase(Result.first);

  return Calls;
}

bool CEvaluationTree::hasDiscontinuity() const
{
  if (mpNodeList == NULL)
    return false;

  std::vector< CEvaluationNode * >::iterator it = mpNodeList->begin();
  std::vector< CEvaluationNode * >::iterator end = mpNodeList->end();

  for (; it != end; ++it)
    {
      switch ((*it)->mainType() | (*it)->subType())
        {
          case (CEvaluationNode::MainType::CHOICE | CEvaluationNode::SubType::IF):
          case (CEvaluationNode::MainType::FUNCTION | CEvaluationNode::SubType::FLOOR):
          case (CEvaluationNode::MainType::FUNCTION | CEvaluationNode::SubType::CEIL):
          case (CEvaluationNode::MainType::OPERATOR | CEvaluationNode::SubType::MODULUS):
          case (CEvaluationNode::MainType::OPERATOR | CEvaluationNode::SubType::REMAINDER):
            // We found a discontinuity.
            return true;
            break;

          case (CEvaluationNode::MainType::CALL | CEvaluationNode::SubType::FUNCTION):
          case (CEvaluationNode::MainType::CALL | CEvaluationNode::SubType::EXPRESSION):

            // If the called tree has a discontinuity so do we.
            if (static_cast< CEvaluationNodeCall * >(*it)->getCalledTree() != NULL &&
                static_cast< CEvaluationNodeCall * >(*it)->getCalledTree()->hasDiscontinuity())
              {
                return true;
              }

            break;
        }
    }

  return false;
}

bool CEvaluationTree::containsCN(const DataObjectSet& elements) const
{
  if (mpNodeList == NULL)
    return false;

  std::vector< CEvaluationNode * >::iterator it = mpNodeList->begin();
  std::vector< CEvaluationNode * >::iterator end = mpNodeList->end();

  for (; it != end; ++it)
    {
      switch ((*it)->mainType() | (*it)->subType())
        {
          case (CEvaluationNode::MainType::OBJECT | CEvaluationNode::SubType::CN):
          {
            // We found a discontinuity.
            auto setIt = elements.begin();
            auto setEnd = elements.end();

            for (; setIt != setEnd; ++setIt)
              {
                if ((*setIt)->getCN() == static_cast<CEvaluationNodeObject*>(*it)->getObjectCN())
                  return true;
              }

            break;
          }

          case (CEvaluationNode::MainType::CALL | CEvaluationNode::SubType::FUNCTION):
          case (CEvaluationNode::MainType::CALL | CEvaluationNode::SubType::EXPRESSION):

            // If the called tree has a discontinuity so do we.
            if (static_cast<CEvaluationNodeCall *>(*it)->getCalledTree() != NULL &&
                static_cast<CEvaluationNodeCall *>(*it)->getCalledTree()->containsCN(elements))
              {
                return true;
              }

            break;
        }
    }

  return false;
}

size_t CEvaluationTree::size() const
{
  return mCalculationSequence.size();
}

bool CEvaluationTree::mapObjectNodes(const CDataContainer * pSrc, const CDataContainer * pTarget)
{
  if (pSrc == NULL || pTarget == NULL)
    return false;

  if (mpNodeList == NULL)
    return true;

  mPrerequisits.clear();
  mCalculationSequence.resize(0);

  bool success = true;
  std::string SrcCN = pSrc->getCN();

  std::vector< CEvaluationNode * >::iterator it = mpNodeList->begin();
  std::vector< CEvaluationNode * >::iterator end = mpNodeList->end();

  for (; it != end; ++it)
    {
      switch ((*it)->mainType() | (*it)->subType())
        {
          case (CEvaluationNode::MainType::OBJECT | CEvaluationNode::SubType::CN):
            success &= static_cast<CEvaluationNodeObject*>(*it)->mapObject(SrcCN, pTarget);
            mPrerequisits.insert(static_cast<CEvaluationNodeObject*>(*it)->getObjectInterfacePtr());

            break;

          case (CEvaluationNode::MainType::CALL | CEvaluationNode::SubType::FUNCTION):
          case (CEvaluationNode::MainType::CALL | CEvaluationNode::SubType::EXPRESSION):
            if (static_cast<CEvaluationNodeCall *>(*it)->getCalledTree() != NULL)
              {
                CFunction * pCalled = static_cast< CEvaluationNodeCall * >(*it)->getCalledTree();

                success &= pCalled->mapObjectNodes(pSrc, pTarget);
                mPrerequisits.insert(pCalled->getPrerequisites().begin(), pCalled->getPrerequisites().end());
              }
            else
              {
                success = false;
              }

            break;
        }
    }

  mpRootValue = mpRootNode->getValuePointer();

  if (success)
    {
      mValue = *mpRootValue;
      buildCalculationSequence();
    }
  else
    {
      mValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
    }

  return success;
}
