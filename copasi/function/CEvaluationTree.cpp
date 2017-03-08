// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"

#include <sstream>
#include <vector>
#include <algorithm>

#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "CFunction.h"
#include "CExpression.h"
#include "CEvaluationLexer.h"
#include "CFunctionDB.h"

#include "report/CKeyFactory.h"
#include "report/CCopasiObjectReference.h"
#include "sbml/math/ASTNode.h"
#include "utilities/CCopasiTree.h"
#include "utilities/CNodeIterator.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "math/CMathObject.h"

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

CEvaluationTree * CEvaluationTree::fromData(const CData & data)
{
  CEvaluationTree * pNew = create((CEvaluationTree::Type) data.getProperty(CData::EVALUATION_TREE_TYPE).toUint());

  if (pNew != NULL)
    {
      pNew->setObjectName(data.getProperty(CData::OBJECT_NAME).toString());
    }

  return pNew;
}

CEvaluationTree::CEvaluationTree(const std::string & name,
                                 const CCopasiContainer * pParent,
                                 const CEvaluationTree::Type & type):
  CCopasiContainer(name, pParent, "Function"),
  mType(type),
  mInfix(),
  mIssue(CIssue::Error),
  mErrorPosition(std::string::npos),
  mpNodeList(NULL),
  mpRootNode(NULL),
  mpRootValue(NULL),
  mValue(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
  mCalculationSequence(),
  mppEnd(NULL)
{
  initObjects();
  setInfix("");
}

CEvaluationTree::CEvaluationTree(const CEvaluationTree & src,
                                 const CCopasiContainer * pParent):
  CCopasiContainer(src, pParent),
  mType(src.mType),
  mInfix(),
  mIssue(CIssue::Error),
  mErrorPosition(std::string::npos),
  mpNodeList(NULL),
  mpRootNode(NULL),
  mpRootValue(NULL),
  mValue(src.mValue),
  mCalculationSequence(),
  mppEnd(NULL)
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
  mValidity.clear();

  // We assume until proven otherwise that the tree is not usable
  mIssue = CIssue(CIssue::Error);

  // Assume whatever (non null) string which was there before,
  // is still ok.
  if (infix == mInfix &&
      infix != "")
    {
      mIssue = CIssue::Success;
      return mIssue;
    }

  mInfix = infix;

  mIssue = parse();

  return mIssue;
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

  if (mType == MassAction)
    {
      mIssue = CIssue::Success;
      return mIssue;
    }

  if (mInfix == "")
    {
      mpNodeList = new std::vector< CEvaluationNode * >;
      mpRootNode = new CEvaluationNode();
      mpRootValue = mpRootNode->getValuePointer();
      mValue = *mpRootValue;
      mpNodeList->push_back(mpRootNode);

      mIssue = CIssue(CValidity::Warning, CValidity::ExpressionEmpty);
      mValidity.add(mIssue);
      return mIssue;
    }

  // parse the description into a linked node tree
  std::istringstream buffer(mInfix);
  CEvaluationLexer Parser(&buffer);

  if (Parser.yyparse() == 0)
    mIssue = CIssue::Success;
  else
    {
      mIssue = CIssue(CValidity::Error, CValidity::ExpressionInvalid);
      mValidity.add(mIssue);
    }

  mpNodeList = Parser.getNodeList();
  mpRootNode = Parser.getRootNode();

  if (mpRootNode != NULL)
    {
      mpRootValue = mpRootNode->getValuePointer();
      mValue = *mpRootValue;
    }
  else
    {
      mpRootValue = NULL;
      mValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
    }

  // clean up if parsing failed
  if (!mIssue)
    {
      mErrorPosition = Parser.getErrorPosition();
      clearNodes();
    }

  if (mIssue && hasCircularDependency())
    {
      mIssue = CIssue(CValidity::Error, CValidity::HasCircularDependency);
      mValidity.add(mIssue);
      CCopasiMessage(CCopasiMessage::ERROR, MCFunction + 4, mErrorPosition);
    }

  return mIssue;
}

CIssue CEvaluationTree::compile()
{return compileNodes();}

CIssue CEvaluationTree::getIssue() const
{return mIssue;}

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

  while (itNode.next() != itNode.end())
    {
      switch (itNode->mainType())
        {
          case CEvaluationNode::T_NUMBER:
          case CEvaluationNode::T_CONSTANT:
          case CEvaluationNode::T_OBJECT:
          case CEvaluationNode::T_UNIT:
            break;

          default:
            CalculationSequence.push_back(*itNode);
            break;
        }
    }

  mCalculationSequence.resize(CalculationSequence.size());
  CEvaluationNode ** ppIt = mCalculationSequence.begin();
  mppEnd = mCalculationSequence.end();

  std::vector< CEvaluationNode * >::const_iterator it = CalculationSequence.begin();

  for (; ppIt != mppEnd; ++ppIt, ++it)
    {
      *ppIt = *it;
    }
}

CIssue CEvaluationTree::compileNodes()
{
  mPrerequisits.clear();
  clearDirectDependencies();
  mCalculationSequence.resize(0);

  // Clear all mValidity flags, except those only set via setInfix
  mValidity.remove(CIssue(CValidity::AllSeverity, ~(CValidity::ExpressionInvalid |
                          CValidity::ExpressionEmpty |
                          CValidity::HasCircularDependency)));
  mIssue = CIssue::Success;

  if (mInfix == "")
    {
      mIssue = CIssue(CValidity::Warning, CValidity::NaNissue);
      mValidity.add(mIssue);
      return mIssue;
    }

  if (mpNodeList == NULL)
    {
      mIssue = CIssue(CValidity::Error, CValidity::StructureInvalid);
      mValidity.add(mIssue);
      return mIssue;
    }

  // The compile order must be child first.
  CNodeIterator< CEvaluationNode > itNode(mpRootNode);
  CEvaluationNode *pErrorNode = NULL;

  CIssue NodeIssue;

  while (itNode.next() != itNode.end())
    if (*itNode != NULL &&
        !(NodeIssue = itNode->compile(this)))
      {
        mValidity.add(NodeIssue);

        if (mIssue) // . . . if it was OkNoKind, before this, . . .
          {
            // Set mIssue to this first encountered Error.
            mIssue = NodeIssue;
            pErrorNode = *itNode;
          }
      }

  // Compile may change the value pointer of the root node.
  mpRootValue = mpRootNode->getValuePointer();
  mValue = *mpRootValue;

  std::vector< CEvaluationNode * >::iterator it;
  std::vector< CEvaluationNode * >::iterator end = mpNodeList->end();

  if (!mIssue)
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
      const CObjectInterface * pObject;

      for (it = mpNodeList->begin(); it != end; ++it)
        switch ((*it)->mainType())
          {
            case CEvaluationNode::T_OBJECT:
            {
              if (mType == Expression &&
                  (pObject = static_cast< CEvaluationNodeObject *>(*it)->getObjectInterfacePtr()) != NULL)
                {
                  const CCopasiObject * pDataObject = CObjectInterface::DataObject(pObject);
                  addDirectDependency(pDataObject);
                }
            }
            break;

            case CEvaluationNode::T_CALL:
              addDirectDependency(static_cast< CEvaluationNodeCall *>(*it)->getCalledTree());
              mPrerequisits.insert(static_cast< CEvaluationNodeCall *>(*it)->getCalledTree());
              break;

            default:
              break;
          }

      buildCalculationSequence();
    }

  return mIssue;
}

void CEvaluationTree::calculate()
{
  try
    {
      if (mpRootNode != NULL)
        {
          CEvaluationNode ** ppIt = mCalculationSequence.begin();

          for (; ppIt != mppEnd; ++ppIt)
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

  return updateTree();
}

CIssue CEvaluationTree::updateTree()
{
  mIssue = CIssue::Success;

  if (mpRootNode == NULL)
    {
      clearNodes();
      mIssue = CIssue(CValidity::Error, CValidity::StructureInvalid);
      mValidity.add(mIssue);
      return mIssue;
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
  mValidity.remove(CIssue(CValidity::AllSeverity, (CValidity::ExpressionInvalid |
                          CValidity::ExpressionEmpty |
                          CValidity::HasCircularDependency)));

  if (mInfix == "")
    {
      mIssue = CIssue(CValidity::Warning, CValidity::ExpressionEmpty);
      mValidity.add(mIssue);
      return mIssue;
    }

  return mIssue;
}

bool CEvaluationTree::setTree(const ASTNode& pRootNode)
{
  return setRoot(CEvaluationTree::fromAST(&pRootNode));
}

CEvaluationNode * CEvaluationTree::fromAST(const ASTNode * pASTNode)
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
              case AST_NAME_TIME:
#if LIBSBML_VERSION >= 40100
              case AST_NAME_AVOGADRO:
#endif // LIBSBML_VERSION >= 40100
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
  std::set< const CCopasiObject * > Self;
  Self.insert(this);

  CCopasiObject * pObject =
    addObjectReference("Value", mValue, CCopasiObject::ValueDbl);

  pObject->setDirectDependencies(Self);
}

CCopasiObject::DataObjectSet CEvaluationTree::getDeletedObjects() const
{
  CCopasiObject::DataObjectSet Deleted;

  Deleted.insert(this);
  Deleted.insert(static_cast< const CCopasiObject * >(getObject(CCopasiObjectName("Reference=Value"))));

  return Deleted;
}

ASTNode* CEvaluationTree::toAST(const CCopasiDataModel* pDataModel) const
{
  return mpRootNode->toAST(pDataModel);
}

bool CEvaluationTree::hasCircularDependency() const
{
  std::set< std::string > List;

  return calls(List);
}

bool CEvaluationTree::dependsOnTree(const std::string & name) const
{
  if (!mpNodeList) return false;

  std::vector< CEvaluationNode * >::const_iterator it = mpNodeList->begin();
  std::vector< CEvaluationNode * >::const_iterator end = mpNodeList->end();

  for (; it != end; ++it)
    if (((*it)->mainType()) == CEvaluationNode::T_CALL &&
        (*it)->getData() == name)
      return true;

  return false;
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
    if (((*it)->mainType()) == CEvaluationNode::T_CALL &&
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
          case (CEvaluationNode::T_CHOICE | CEvaluationNode::S_IF):
          case (CEvaluationNode::T_FUNCTION | CEvaluationNode::S_FLOOR):
          case (CEvaluationNode::T_FUNCTION | CEvaluationNode::S_CEIL):
          case (CEvaluationNode::T_OPERATOR | CEvaluationNode::S_MODULUS):
          case (CEvaluationNode::T_OPERATOR | CEvaluationNode::S_REMAINDER):
            // We found a discontinuity.
            return true;
            break;

          case (CEvaluationNode::T_CALL | CEvaluationNode::S_FUNCTION):
          case (CEvaluationNode::T_CALL | CEvaluationNode::S_EXPRESSION):

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
