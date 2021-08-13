// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <algorithm>

#include "copasi/copasi.h"

#include "CFunction.h"
#include "CFunctionDB.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/utilities/copasimathml.h"

// static
CFunction * CFunction::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  CEvaluationTree * pTree = CEvaluationTree::fromData(data, pParent);

  CFunction * pNew = dynamic_cast< CFunction * >(pTree);

  if (pNew == NULL)
    {
      pdelete(pTree);
    }

  return pNew;
}

// virtual
CData CFunction::toData() const
{
  CData Data = CEvaluationTree::toData();

  // TODO CRITICAL Implement me!
  // fatalError();

  Data.appendData(CAnnotation::toData());

  return Data;
}

// virtual
bool CFunction::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = CEvaluationTree::applyData(data, changes);

  // TODO CRITICAL Implement me!
  // fatalError();

  success &= CAnnotation::applyData(data, changes);

  return success;
}

// virtual
void CFunction::createUndoData(CUndoData & undoData,
                               const CUndoData::Type & type,
                               const CData & oldData,
                               const CCore::Framework & framework) const
{
  CEvaluationTree::createUndoData(undoData, type, oldData, framework);

  if (type != CUndoData::Type::CHANGE)
    {
      return;
    }

  // TODO CRITICAL Implement me!
  // fatalError();

  CAnnotation::createUndoData(undoData, type, oldData, framework);

  return;
}

CFunction::CFunction(const std::string & name,
                     const CDataContainer * pParent,
                     const CEvaluationTree::Type & type):
  CEvaluationTree(name, pParent, type),
  CAnnotation(),
  mSBMLId(""),
  mVariables("Function Parameters", this),
  mCallParametersBegin(),
  mReversible(TriUnspecified)
{
  mKey = CRootContainer::getKeyFactory()->add("Function", this);
  initMiriamAnnotation(mKey);
}

CFunction::CFunction(const CFunction & src,
                     const CDataContainer * pParent):
  CEvaluationTree(src, pParent),
  CAnnotation(src),
  mSBMLId(src.mSBMLId),
  mVariables(src.mVariables, this),
  mCallParametersBegin(src.mCallParametersBegin),
  mReversible(src.mReversible)
{
  mKey = CRootContainer::getKeyFactory()->add("Function", this);
  setMiriamAnnotation(src.getMiriamAnnotation(), mKey, src.mKey);

  compile();
}

CFunction::~CFunction()
{
  CRootContainer::getKeyFactory()->remove(mKey);
}

const std::string & CFunction::getKey() const
{
  return CAnnotation::getKey();
}

void CFunction::setSBMLId(const std::string& id)
{
  this->mSBMLId = id;
}

const std::string& CFunction::getSBMLId() const
{
  return this->mSBMLId;
}

CIssue CFunction::setInfix(const std::string & infix)
{
  if (infix != mInfix)
    {
      CRootContainer::functionDefinitionChanged(this);
    }

  CIssue firstWorstIssue, issue;
  issue = CEvaluationTree::setInfix(infix);

  if (!issue || mpNodeList == NULL) return issue;

  // We need to check that the function does not contain any objects, calls to expression
  // or delay nodes.
  std::vector< CEvaluationNode * >::const_iterator it = mpNodeList->begin();
  std::vector< CEvaluationNode * >::const_iterator end = mpNodeList->end();

  for (; it != end; ++it)
    {
      switch ((*it)->mainType())
        {
          case CEvaluationNode::MainType::OBJECT:
            if ((*it)->subType() != CEvaluationNode::SubType::AVOGADRO)
              {
                issue = CIssue(CIssue::eSeverity::Error, CIssue::eKind::StructureInvalid);
                mValidity.add(issue);
                return firstWorstIssue &= issue;
              }

            break;

          case CEvaluationNode::MainType::DELAY:
            issue = CIssue(CIssue::eSeverity::Error, CIssue::eKind::StructureInvalid);
            mValidity.add(issue);
            return firstWorstIssue &= issue;
            break;

          case CEvaluationNode::MainType::CALL:

            if ((*it)->subType() == CEvaluationNode::SubType::EXPRESSION)
              {
                issue = CIssue(CIssue::eSeverity::Error, CIssue::eKind::StructureInvalid);
                mValidity.add(issue);
                return firstWorstIssue &= issue;
              }

            break;

          default:
            break;
        }
    }

  issue = initVariables();
  mValidity.add(issue);
  firstWorstIssue &= issue;

  if (!firstWorstIssue) return firstWorstIssue;

  firstWorstIssue &= compileNodes();

  return firstWorstIssue;
}

// virtual
bool CFunction::isReadOnly() const
{
  switch (mType)
    {
      case MassAction:
      case PreDefined:
        return true;
        break;

      default:
        return false;
        break;
    };

  return false;
}

bool CFunction::operator == (const CFunction & rhs) const
{
  if (!(*static_cast< const CEvaluationTree * >(this) == rhs))
    return false;

  if (!(*static_cast< const CAnnotation * >(this) == rhs))
    return false;

  if (!(mVariables == rhs.mVariables))
    return false;

  return true;
}

size_t CFunction::getVariableIndex(const std::string & name) const
{
  return mVariables.findParameterByName(name);
}

const C_FLOAT64 & CFunction::getVariableValue(const size_t & index) const
{return *(mCallParametersBegin + index)->value;}

void CFunction::setReversible(const TriLogic & reversible)
{mReversible = reversible;}

const TriLogic & CFunction::isReversible() const
{return mReversible;}

CFunctionParameters & CFunction::getVariables()
{return mVariables;}

const CFunctionParameters & CFunction::getVariables() const
{return mVariables;}

bool CFunction::addVariable(const std::string & name,
                            CFunctionParameter::Role usage,
                            const CFunctionParameter::DataType & type)
{return mVariables.add(name, type, usage);}

const C_FLOAT64 & CFunction::calcValue(const CCallParameters<C_FLOAT64> & callParameters)
{
  mCallParametersBegin = callParameters.begin();

  calculate();

  return mValue;
}

void CFunction::load(CReadConfig & configBuffer,
                     CReadConfig::Mode mode)
{
  //  cleanup();

  C_INT32 Type;

  mode = CReadConfig::SEARCH;
  configBuffer.getVariable("User-defined", "C_INT32", &Type, mode);

  switch (Type)
    {
      case 1:
        setType(UserDefined);
        break;

      default:
        fatalError();
        break;
    }

  configBuffer.getVariable("Reversible", "C_INT32", &mReversible);

  mode = CReadConfig::SEARCH;

  std::string tmp;
  configBuffer.getVariable("FunctionName", "string", &tmp, mode);
  setObjectName(tmp);

  configBuffer.getVariable("Description", "string", &tmp);
  setInfix(tmp);

  // For older file version the parameters have to be build from information
  // dependend on the function type. Luckilly, only user defined functions are
  // the only ones occuring in those files.
}

CIssue CFunction::initVariables()
{
  if (mpNodeList == NULL && mInfix != "") return CIssue(CIssue::eSeverity::Error, CIssue::eKind::StructureInvalid);

  CFunctionParameters NewVariables;

  if (mInfix != "")
    {
      //first add all variables to the existing list
      std::vector< CEvaluationNode * >::iterator it = mpNodeList->begin();
      std::vector< CEvaluationNode * >::iterator end = mpNodeList->end();

      for (; it != end; ++it)
        if ((*it)->mainType() == CEvaluationNode::MainType::VARIABLE)
          {
            mVariables.add((*it)->getData(),
                           CFunctionParameter::DataType::FLOAT64,
                           CFunctionParameter::Role::VARIABLE);
            NewVariables.add((*it)->getData(),
                             CFunctionParameter::DataType::FLOAT64,
                             CFunctionParameter::Role::VARIABLE);
          }
    }

  //now remove all variables that are not in the tree anymore
  size_t i;

  for (i = mVariables.size() - 1; i != C_INVALID_INDEX; i--)
    if (NewVariables.findParameterByName(mVariables[i]->getObjectName()) == C_INVALID_INDEX)
      mVariables.remove(mVariables[i]->getObjectName());
    else
      mVariables[i]->setIsUsed(true);

  return CIssue::Success;
}

bool CFunction::isSuitable(const size_t noSubstrates,
                           const size_t noProducts,
                           const TriLogic reversible)
{
  // A function which in neither restricted to reversible nor to irreversible reactions is always suitable
  // independent from the number of substrates or products
  if (isReversible() == TriUnspecified)
    return true;

  //first reversibility:
  if (reversible != isReversible())
    return false;

  //check substrates
  if (mVariables.isVector(CFunctionParameter::Role::SUBSTRATE))
    {
      if (noSubstrates == 0 || noSubstrates == C_INVALID_INDEX)
        return false;
    }
  else //is no vector
    {
      if (mVariables.getNumberOfParametersByUsage(CFunctionParameter::Role::SUBSTRATE) != noSubstrates &&
          noSubstrates != C_INVALID_INDEX)
        return false;
    }

  //check products
  if (reversible == TriTrue)
    {
      if (mVariables.isVector(CFunctionParameter::Role::PRODUCT))
        {
          if (noProducts == 0 || noProducts == C_INVALID_INDEX)
            return false;
        }
      else //is no vector
        {
          if (mVariables.getNumberOfParametersByUsage(CFunctionParameter::Role::PRODUCT) != noProducts &&
              noProducts != C_INVALID_INDEX)
            return false;
        }
    }

  //no VARIABLE variables allowed for kinetic functions
  if (mVariables.getNumberOfParametersByUsage(CFunctionParameter::Role::VARIABLE) != 0)
    return false;

  return true;
}

bool CFunction::completeFunctionList(std::vector< const CFunction * > & list,
                                     const size_t & added)
{
  unsigned Added = 0;

  size_t i, imax = list.size();
  size_t Index;

  const CEvaluationTree * pTree;
  std::vector< CEvaluationNode * >::const_iterator it;
  std::vector< CEvaluationNode * >::const_iterator end;

  CDataVectorN< CFunction > & Functions =
    CRootContainer::getFunctionList()->loadedFunctions();

  for (i = (added) ? imax - added : 0; i < imax; i++)
    {
      pTree = list[i];

      for (it = pTree->getNodeList().begin(), end = pTree->getNodeList().end(); it != end; ++it)
        {
          if ((*it)->mainType() == CEvaluationNode::MainType::CALL &&
              (Index = Functions.getIndex((*it)->getData())) != C_INVALID_INDEX &&
              list.end() == std::find(list.begin(), list.end(), &Functions[Index]))
            {
              list.push_back(&Functions[Index]);
              Added++;
            }
        }
    }

  if (Added)
    return completeFunctionList(list, Added);
  else
    return true;
}

void CFunction::createListOfParametersForMathML(std::vector<std::vector<std::string> > & env)
{
  size_t i, imax = getVariables().size();

  env.clear();
  env.resize(imax);

  for (i = 0; i < imax; ++i)
    {
      env[i].push_back("<mi>" + CMathMl::fixName(getVariables()[i]->getObjectName()) + "</mi>");
    }
}

// virtual
std::string CFunction::writeMathML(const std::vector< std::vector< std::string > > & variables,
                                   bool expand, bool fullExpand) const
{
  std::ostringstream out;

  if (expand && getRoot() != NULL)
    {
      bool flag = false; //TODO include check if parentheses are necessary

      if (flag) out << "<mfenced>" << std::endl;

      out << getRoot()->buildMMLString(fullExpand, variables);

      if (flag) out << "</mfenced>" << std::endl;
    }
  else //no expand
    {
      out << "<mrow>" << std::endl;
      out << CMathMl::fixName(getObjectName()) << std::endl;
      out << "<mfenced>" << std::endl;

      size_t i, imax = variables.size();

      for (i = 0; i < imax; ++i)
        {
          out << variables[i][0] << std::endl;
        }

      out << "</mfenced>" << std::endl;
      out << "</mrow>" << std::endl;
    }

  return out.str();
}

void CFunction::writeMathML(std::ostream & out, size_t l) const
{
  //out << "<math>" << std::endl;

  out << SPC(l) << "<mrow>" << std::endl;
  out << SPC(l + 1) << CMathMl::fixName(getObjectName()) << std::endl;
  out << SPC(l + 1) << "<mfenced>" << std::endl;

  size_t i, imax = getVariables().size();

  for (i = 0; i < imax; ++i)
    {
      out << SPC(l + 2) << "<mi>" << CMathMl::fixName(getVariables()[i]->getObjectName()) << "</mi>" << std::endl;
    }

  out << SPC(l + 1) << "</mfenced>" << std::endl;
  out << SPC(l) << "</mrow>" << std::endl;

  //out << "</math>" << std::endl;
}

std::ostream& operator<<(std::ostream &os, const CFunction & f)
{
  os << "CFunction: " << f.getObjectName() << "   ";

  if (f.mReversible == TriUnspecified)
    os << "(general)";
  else if (f.mReversible == TriFalse)
    os << "(irreversible)";
  else
    os << "(reversible)";

  os << std::endl;
  os << f.mVariables;
  os << f.getInfix() << std::endl;

  return os;
}

CFunction * CFunction::createCopy() const
{
  CFunction* newFunction = new CFunction();

  //newFunction->mVariables = this->mVariables; //WRONG! only shallow copy!!
  newFunction->mReversible = this->mReversible;

  if (getRoot() != NULL)
    newFunction->setRoot(getRoot()->copyBranch());

  //newFunction->mInfix = newFunction->mpRoot->getInfix();

  return newFunction;
}

#include "CFunctionAnalyzer.h"

std::pair<CFunction *, CFunction *> CFunction::splitFunction(const CEvaluationNode * /* node */,
    const std::string & name1,
    const std::string & name2) const
{
  if (getRoot() == NULL) return std::pair<CFunction *, CFunction *>((CFunction*)NULL, (CFunction*)NULL);

  if (mReversible != TriTrue) return std::pair<CFunction *, CFunction *>((CFunction*)NULL, (CFunction*)NULL);

  //create 2 new functions
  CFunction* newFunction1 = new CFunction();
  newFunction1->setObjectName(name1);

  CFunction* newFunction2 = new CFunction();
  newFunction2->setObjectName(name2);

  //when searching for a split point we need to analyze subtrees. For
  //doing this a representation of the call parameters in the format
  //used by CFunctionAnalyzer is needed.
  std::vector<CFunctionAnalyzer::CValue> callParameters;
  CFunctionAnalyzer::constructCallParameters(this->getVariables(), callParameters, true);
  // find the split point
  const CEvaluationNode* splitnode = getRoot()->findTopMinus(callParameters);

  if (!splitnode) return std::pair<CFunction *, CFunction *>((CFunction*)NULL, (CFunction*)NULL);

  //create the 2 split trees
  CEvaluationNode* tmpRoots1 = getRoot()->splitBranch(splitnode, true); //left side
  CEvaluationNode* tmpRoots2 = getRoot()->splitBranch(splitnode, false); //right side

  if (tmpRoots1)
    newFunction1->setRoot(tmpRoots1);

  if (tmpRoots2)
    newFunction2->setRoot(tmpRoots2);

  newFunction1->mVariables = this->mVariables; //copy the parameter list
  newFunction1->initVariables(); //remove unused parameters
  newFunction1->mReversible = TriFalse;

  newFunction2->mVariables = this->mVariables; //copy the parameter list
  newFunction2->initVariables(); //remove unused parameters
  newFunction2->mReversible = TriFalse;

  //update the roles
  size_t i, imax;

  imax = newFunction1->mVariables.size();

  for (i = 0; i < imax; ++i)
    {
      if (newFunction1->mVariables[i]->getUsage() == CFunctionParameter::Role::PRODUCT)
        newFunction1->mVariables[i]->setUsage(CFunctionParameter::Role::MODIFIER);
    }

  imax = newFunction2->mVariables.size();

  for (i = 0; i < imax; ++i)
    {
      if (newFunction2->mVariables[i]->getUsage() == CFunctionParameter::Role::PRODUCT)
        newFunction2->mVariables[i]->setUsage(CFunctionParameter::Role::SUBSTRATE);
      else if (newFunction2->mVariables[i]->getUsage() == CFunctionParameter::Role::SUBSTRATE)
        newFunction2->mVariables[i]->setUsage(CFunctionParameter::Role::MODIFIER);
    }

  newFunction1->compile();
  newFunction2->compile();
  return std::pair<CFunction *, CFunction *>(newFunction1, newFunction2);
}
