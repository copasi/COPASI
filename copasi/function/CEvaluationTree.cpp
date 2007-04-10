// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationTree.cpp,v $
//   $Revision: 1.46 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/04/10 16:48:44 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include <sstream>
#include <vector>

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
#include "CopasiDataModel/CCopasiDataModel.h"

const std::string CEvaluationTree::TypeName[] =
  {"userdefined", "predefined", "predefined", "userdefined", "userdefined", ""};

const char* CEvaluationTree::XMLType[] =
  {"Function", "MassAction", "PreDefined", "UserDefined", "Expression", NULL};

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
      pNew = new CFunction(*static_cast<const CFunction *>(&src));
      break;

    case MassAction:
      pNew = new CMassAction(*static_cast<const CMassAction *>(&src));
      break;

    case PreDefined:
    case UserDefined:
      pNew = new CKinFunction(*static_cast<const CKinFunction *>(&src));
      break;

    case Expression:
      pNew = new CExpression(*static_cast<const CExpression *>(&src));
      break;

    default:
      fatalError();
    }

  return pNew;
}

CEvaluationTree::CEvaluationTree(const std::string & name,
                                 const CCopasiContainer * pParent,
                                 const CEvaluationTree::Type & type):
    CCopasiContainer(name, pParent, "Function"),
    mType(type),
    mKey(GlobalKeys.add("Function", this)),
    mInfix(),
    mUsable(false),
    mErrorPosition(std::string::npos),
    mpNodeList(NULL),
    mpRoot(NULL),
    mValue(std::numeric_limits<C_FLOAT64>::quiet_NaN())
{
  initObjects();
  setInfix("");
}

CEvaluationTree::CEvaluationTree(const CEvaluationTree & src,
                                 const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mType(src.mType),
    mKey(GlobalKeys.add("Function", this)),
    mInfix(),
    mUsable(false),
    mErrorPosition(std::string::npos),
    mpNodeList(NULL),
    mpRoot(NULL),
    mValue(src.mValue)
{
  initObjects();
  setInfix(src.mInfix);
  compileNodes();
}

CEvaluationTree::~CEvaluationTree()
{
  CEvaluationLexer::freeNodeList(mpNodeList);
  GlobalKeys.remove(mKey);
}

const CEvaluationTree::Type & CEvaluationTree::getType() const
  {return mType;}

void CEvaluationTree::setType(const CEvaluationTree::Type & type)
{mType = type;}

const std::string & CEvaluationTree::getKey() const
  {return mKey;}

bool CEvaluationTree::setInfix(const std::string & infix)
{
  if (infix == mInfix &&
      infix != "") return true;

  // We assume until proven otherwise that the tree is not usable
  mUsable = false;

  mInfix = infix;

  return parse();
}

const std::string & CEvaluationTree::getInfix() const
{return mInfix;;}

std::string::size_type CEvaluationTree::getErrorPosition() const
  {return mErrorPosition;}

const std::vector< CEvaluationNode * > & CEvaluationTree::getNodeList() const
  {
    if (!mpNodeList)
      const_cast<CEvaluationTree *>(this)->mpNodeList = new std::vector< CEvaluationNode * >;
    return *mpNodeList;
  }

unsigned C_INT32 CEvaluationTree::getVariableIndex(const std::string & /*name*/) const
{return C_INVALID_INDEX;}

const C_FLOAT64 & CEvaluationTree::getVariableValue(const unsigned C_INT32 & /*index*/) const
  {
    static C_FLOAT64 Value = std::numeric_limits<C_FLOAT64>::quiet_NaN();
    return Value;
  }

bool CEvaluationTree::parse()
{
  bool success = true;

  // clean up
  CEvaluationLexer::freeNodeList(mpNodeList);
  mpNodeList = NULL;
  mpRoot = NULL;

  if (mType == MassAction) return true;
  if (mInfix == "")
    {
      mpNodeList = new std::vector< CEvaluationNode * >;
      mpRoot = new CEvaluationNode();
      mpNodeList->push_back(mpRoot);
      return true;
    }

  // parse the description into a linked node tree
  std::istringstream buffer(mInfix);
  CEvaluationLexer Parser(&buffer);

  success = (Parser.yyparse() == 0);

  mpNodeList = Parser.getNodeList();
  mpRoot = Parser.getRootNode();

  // clean up if parsing failed
  if (!success)
    {
      mErrorPosition = Parser.getErrorPosition();

      CEvaluationLexer::freeNodeList(mpNodeList);
      mpNodeList = NULL;
      mpRoot = NULL;
    }

  if (success && hasCircularDependency())
    {
      success = false;
      CCopasiMessage(CCopasiMessage::ERROR, MCFunction + 4, mErrorPosition);
    }

  return success;
}

bool CEvaluationTree::compile()
{return compileNodes();}

bool CEvaluationTree::isUsable() const
  {return mUsable;}

bool CEvaluationTree::compileNodes()
{
  mDependencies.clear();

  if (mInfix == "")
    return mUsable = true;
  if (mpNodeList == NULL)
    return mUsable = false;

  std::vector< CEvaluationNode * >::iterator it;
  std::vector< CEvaluationNode * >::iterator end = mpNodeList->end();

  for (it = mpNodeList->begin(), mUsable = true; it != end && mUsable; ++it)
    mUsable = (*it)->compile(this);

  if (!mUsable)
    {
      end = it;
      mErrorPosition = 0;

      for (it = mpNodeList->begin(); it != end; ++it)
        mErrorPosition += (*it)->getData().length();

      mErrorPosition -= (*--it)->getData().length();
      CCopasiMessage(CCopasiMessage::ERROR, MCFunction + 3, mErrorPosition);
    }
  else
    {
      const CCopasiObject * pObject;

      for (it = mpNodeList->begin(); it != end; ++it)
        switch ((*it)->getType() & 0xFF000000)
          {
          case CEvaluationNode::OBJECT:
            if (mType == Expression &&
                (pObject = static_cast<CExpression *>(this)->getNodeObject(static_cast< CEvaluationNodeObject *>(*it)->getObjectCN())) != NULL)
              mDependencies.insert(pObject);
            break;

          case CEvaluationNode::CALL:
            mDependencies.insert(static_cast< CEvaluationNodeCall *>(*it)->getCalledTree());
            break;

          default:
            break;
          }
    }

  return mUsable;
}

bool CEvaluationTree::setRoot(CEvaluationNode* pRootNode)
{
  if (pRootNode == NULL) return false;
  if (mpNodeList != NULL)
    CEvaluationLexer::freeNodeList(mpNodeList);

  mpRoot = pRootNode;

  mpNodeList = new std::vector< CEvaluationNode * >;

  return this->updateTree();
}

bool CEvaluationTree::updateTree()
{
  if (!mpRoot || !mpNodeList) return false;
  mpNodeList->clear();
  CCopasiTree<CEvaluationNode>::iterator it = mpRoot;
  CCopasiTree<CEvaluationNode>::iterator end = NULL;

  for (; it != end; ++it)
    mpNodeList->push_back(&*it);

  mInfix = mpRoot->getInfix();

  return true;
}

bool CEvaluationTree::setTree(const ASTNode& pRootNode)
{
  return this->setRoot(CEvaluationTree::convertASTNode(pRootNode));
}

CEvaluationNode* CEvaluationTree::convertASTNode(const ASTNode& node)
{
  CEvaluationNode* pResultNode = NULL;
  ASTNodeType_t nodeType = node.getType();
  CCopasiMessage Message;
  switch (nodeType)
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
      pResultNode = CEvaluationNodeOperator::createNodeFromASTTree(node);
      break;
    case AST_INTEGER:
    case AST_REAL:
    case AST_REAL_E:
    case AST_RATIONAL:
      // create a CEvaluationNodeNumber
      pResultNode = CEvaluationNodeNumber::createNodeFromASTTree(node);
      break;
    case AST_NAME:
    case AST_NAME_TIME:
      // create a CEvaluationNodeObject
      pResultNode = CEvaluationNodeObject::createNodeFromASTTree(node);
      break;
    case AST_CONSTANT_E:
    case AST_CONSTANT_PI:
    case AST_CONSTANT_FALSE:
    case AST_CONSTANT_TRUE:
      // create a CEvaluationNodeConstant
      pResultNode = CEvaluationNodeConstant::createNodeFromASTTree(node);
      break;
    case AST_FUNCTION:
      // create a function call node
      pResultNode = CEvaluationNodeCall::createNodeFromASTTree(node);
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
      // create a CEvaluationNodeFunction
      pResultNode = CEvaluationNodeFunction::createNodeFromASTTree(node);
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
      pResultNode = CEvaluationNodeLogical::createNodeFromASTTree(node);
      break;
    case AST_FUNCTION_PIECEWISE:
      pResultNode = CEvaluationNodeChoice::createNodeFromASTTree(node);
      break;
    case AST_FUNCTION_DELAY:
      // create an unsupported element error
      Message = CCopasiMessage(CCopasiMessage::EXCEPTION, MCMathML + 1,
                               node.getName());
      break;

    case AST_UNKNOWN:
      // create an unknown element error
      Message = CCopasiMessage(CCopasiMessage::EXCEPTION, MCMathML + 2);

      break;
    }
  return pResultNode;
}

const CEvaluationNode* CEvaluationTree::getRoot() const
  {
    return this->mpRoot;
  }

CEvaluationNode* CEvaluationTree::getRoot()
{
  return this->mpRoot;
}

void CEvaluationTree::initObjects()
{
  std::set< const CCopasiObject * > Self;
  Self.insert(this);

  CCopasiObject * pObject =
    addObjectReference("Value", mValue, CCopasiObject::ValueDbl);

  pObject->setDirectDependencies(Self);
}

ASTNode* CEvaluationTree::toAST() const
  {
    return this->mpRoot->toAST();
  }

void CEvaluationTree::setSBMLId(const std::string& id)
{
  this->mSBMLId = id;
}

const std::string& CEvaluationTree::getSBMLId() const
  {
    return this->mSBMLId;
  }

bool CEvaluationTree::completeEvaluationTreeList(CCopasiVectorN< CEvaluationTree > & list,
    const unsigned C_INT32 & added)
{
  unsigned Added = 0;

  unsigned C_INT32 i, imax = list.size();
  unsigned C_INT32 Index;

  CEvaluationTree * pTree;
  std::vector< CEvaluationNode * >::const_iterator it;
  std::vector< CEvaluationNode * >::const_iterator end;

  CCopasiVectorN< CEvaluationTree > & Functions =
    CCopasiDataModel::Global->getFunctionList()->loadedFunctions();

  for (i = (added) ? imax - added : 0; i < imax; i++)
    {
      pTree = list[i];

      for (it = pTree->getNodeList().begin(), end = pTree->getNodeList().end(); it != end; ++it)
        {
          if (((*it)->getType() & 0xFF000000) == CEvaluationNode::CALL &&
              (Index = Functions.getIndex((*it)->getData())) != C_INVALID_INDEX &&
              list.add(Functions[Index]))
            Added ++;
        }
    }

  if (Added)
    return completeEvaluationTreeList(list, Added);
  else
    return true;
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
      if (((*it)->getType() & 0xFF000000) == CEvaluationNode::CALL &&
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
      if (((*it)->getType() & 0xFF000000) == CEvaluationNode::CALL &&
          dynamic_cast<CEvaluationNodeCall *>(*it)->calls(list))
        {
          Calls = true;
          break;
        }

    list.erase(Result.first);

    return Calls;
  }
