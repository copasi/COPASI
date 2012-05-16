// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunction.cpp,v $
//   $Revision: 1.89 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/16 23:11:32 $
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

#include <algorithm>

#include "copasi.h"

#include "CFunction.h"
#include "CFunctionDB.h"

#include "report/CCopasiRootContainer.h"
#include "utilities/copasimathml.h"

CFunction::CFunction(const std::string & name,
                     const CCopasiContainer * pParent,
                     const CEvaluationTree::Type & type):
    CEvaluationTree(name, pParent, type),
    CAnnotation(),
    mKey(CCopasiRootContainer::getKeyFactory()->add("Function", this)),
    mSBMLId(""),
    mVariables("Function Parameters", this),
    mpCallParameters(NULL),
    mReversible(TriUnspecified)
{}

CFunction::CFunction(const CFunction & src,
                     const CCopasiContainer * pParent):
    CEvaluationTree(src, pParent),
    CAnnotation(src),
    mKey(CCopasiRootContainer::getKeyFactory()->add("Function", this)),
    mSBMLId(src.mSBMLId),
    mVariables(src.mVariables, this),
    mpCallParameters(NULL),
    mReversible(src.mReversible)
{
  setMiriamAnnotation(src.getMiriamAnnotation(), mKey, src.mKey);
  compile();
}

CFunction::~CFunction()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
}

const std::string & CFunction::getKey() const
{return mKey;}

void CFunction::setSBMLId(const std::string& id)
{
  this->mSBMLId = id;
}

const std::string& CFunction::getSBMLId() const
{
  return this->mSBMLId;
}

bool CFunction::setInfix(const std::string & infix)
{
  if (!CEvaluationTree::setInfix(infix)) return false;

  if (mpNodeList == NULL) return true;

  // We need to check that the function does not contain any objects, calls to expression
  // or delay nodes.
  std::vector< CEvaluationNode * >::const_iterator it = mpNodeList->begin();
  std::vector< CEvaluationNode * >::const_iterator end = mpNodeList->end();

  for (; it != end; ++it)
    {
      switch (CEvaluationNode::type((*it)->getType()))
        {
          case CEvaluationNode::OBJECT:
          case CEvaluationNode::DELAY:
            return false;
            break;

          case CEvaluationNode::CALL:

            if ((CEvaluationNodeCall::SubType) CEvaluationNode::subType((*it)->getType()) == CEvaluationNodeCall::EXPRESSION)
              {
                return false;
              }

            break;

          default:
            break;
        }
    }

  if (!initVariables()) return false;

  return true;
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
  CFunctionParameter::DataType VariableType;
  return mVariables.findParameterByName(name, VariableType);
}

const C_FLOAT64 & CFunction::getVariableValue(const size_t & index) const
{return *(*mpCallParameters)[index].value;}

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
  mpCallParameters = & callParameters;

  calculate();

  return mValue;
}

bool CFunction::dependsOn(const C_FLOAT64 * parameter,
                          const CCallParameters<C_FLOAT64> & callParameters) const
{
  CCallParameters<C_FLOAT64>::const_iterator it = callParameters.begin();
  CCallParameters<C_FLOAT64>::const_iterator end = callParameters.end();

  while (it != end && parameter != it->value) it++;

  if (it != end)
    return true;
  else
    return false;
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

bool CFunction::initVariables()
{
  if (mpNodeList == NULL && mInfix != "") return false;

  CFunctionParameters NewVariables;

  if (mInfix != "")
    {
      //first add all variables to the existing list
      std::vector< CEvaluationNode * >::iterator it = mpNodeList->begin();
      std::vector< CEvaluationNode * >::iterator end = mpNodeList->end();

      for (; it != end; ++it)
        if (CEvaluationNode::type((*it)->getType()) == CEvaluationNode::VARIABLE)
          {
            mVariables.add((*it)->getData(),
                           CFunctionParameter::FLOAT64,
                           CFunctionParameter::VARIABLE);
            NewVariables.add((*it)->getData(),
                             CFunctionParameter::FLOAT64,
                             CFunctionParameter::VARIABLE);
          }
    }

  //now remove all variables that are not in the tree anymore
  CFunctionParameter::DataType Type;
  size_t i;

  for (i = mVariables.size() - 1; i != C_INVALID_INDEX; i--)
    if (NewVariables.findParameterByName(mVariables[i]->getObjectName(), Type) == C_INVALID_INDEX)
      mVariables.remove(mVariables[i]->getObjectName());

  return true;
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
  if (mVariables.isVector(CFunctionParameter::SUBSTRATE))
    {
      if (noSubstrates == 0 || noSubstrates == C_INVALID_INDEX)
        return false;
    }
  else //is no vector
    {
      if (mVariables.getNumberOfParametersByUsage(CFunctionParameter::SUBSTRATE) != noSubstrates &&
          noSubstrates != C_INVALID_INDEX)
        return false;
    }

  //check products
  if (reversible == TriTrue)
    {
      if (mVariables.isVector(CFunctionParameter::PRODUCT))
        {
          if (noProducts == 0 || noProducts == C_INVALID_INDEX)
            return false;
        }
      else //is no vector
        {
          if (mVariables.getNumberOfParametersByUsage(CFunctionParameter::PRODUCT) != noProducts &&
              noProducts != C_INVALID_INDEX)
            return false;
        }
    }

  //no VARIABLE variables allowed for kinetic functions
  if (mVariables.getNumberOfParametersByUsage(CFunctionParameter::VARIABLE) != 0)
    return false;

  return true;
}

bool CFunction::completeFunctionList(std::vector< CFunction * > & list,
                                     const size_t & added)
{
  unsigned Added = 0;

  size_t i, imax = list.size();
  size_t Index;

  CEvaluationTree * pTree;
  std::vector< CEvaluationNode * >::const_iterator it;
  std::vector< CEvaluationNode * >::const_iterator end;

  CCopasiVectorN< CFunction > & Functions =
    CCopasiRootContainer::getFunctionList()->loadedFunctions();

  for (i = (added) ? imax - added : 0; i < imax; i++)
    {
      pTree = list[i];

      for (it = pTree->getNodeList().begin(), end = pTree->getNodeList().end(); it != end; ++it)
        {
          if (((*it)->getType() & 0xFF000000) == CEvaluationNode::CALL &&
              (Index = Functions.getIndex((*it)->getData())) != C_INVALID_INDEX &&
              list.end() == std::find(list.begin(), list.end(), Functions[Index]))
            {
              list.push_back(Functions[Index]);
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

  if (expand && mpRoot)
    {
      bool flag = false; //TODO include check if parentheses are necessary

      if (flag) out << "<mfenced>" << std::endl;

      mpRoot->buildMMLString(fullExpand, variables);

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

  if (this->mpRoot)
    newFunction->setRoot(this->mpRoot->copyBranch());

  //newFunction->mInfix = newFunction->mpRoot->getInfix();

  return newFunction;
}

#include "CFunctionAnalyzer.h"

std::pair<CFunction *, CFunction *> CFunction::splitFunction(const CEvaluationNode * /* node */,
    const std::string & name1,
    const std::string & name2) const
{
  if (!this->mpRoot) return std::pair<CFunction *, CFunction *>((CFunction*)NULL, (CFunction*)NULL);

  if (this->mReversible != TriTrue) return std::pair<CFunction *, CFunction *>((CFunction*)NULL, (CFunction*)NULL);

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
  const CEvaluationNode* splitnode = this->mpRoot->findTopMinus(callParameters);

  if (!splitnode) return std::pair<CFunction *, CFunction *>((CFunction*)NULL, (CFunction*)NULL);

  //create the 2 split trees
  CEvaluationNode* tmpRoots1 = this->mpRoot->splitBranch(splitnode, true); //left side
  CEvaluationNode* tmpRoots2 = this->mpRoot->splitBranch(splitnode, false); //right side

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
      if (newFunction1->mVariables[i]->getUsage() == CFunctionParameter::PRODUCT)
        newFunction1->mVariables[i]->setUsage(CFunctionParameter::MODIFIER);
    }

  imax = newFunction2->mVariables.size();

  for (i = 0; i < imax; ++i)
    {
      if (newFunction2->mVariables[i]->getUsage() == CFunctionParameter::PRODUCT)
        newFunction2->mVariables[i]->setUsage(CFunctionParameter::SUBSTRATE);
      else if (newFunction2->mVariables[i]->getUsage() == CFunctionParameter::SUBSTRATE)
        newFunction2->mVariables[i]->setUsage(CFunctionParameter::MODIFIER);
    }

  newFunction1->compile();
  newFunction2->compile();
  return std::pair<CFunction *, CFunction *>(newFunction1, newFunction2);
}
