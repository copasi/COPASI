/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunction.cpp,v $
   $Revision: 1.70 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/07/13 18:00:48 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CFunction.h"

CFunction::CFunction(const std::string & name,
                     const CCopasiContainer * pParent,
                     const CEvaluationTree::Type & type):
    CEvaluationTree(name, pParent, type),
    mVariables(),
    mpCallParameters(NULL),
    mReversible(TriUnspecified)
{}

CFunction::CFunction(const CFunction & src,
                     const CCopasiContainer * pParent):
    CEvaluationTree(src, pParent),
    mVariables(src.mVariables),
    mpCallParameters(NULL),
    mReversible(src.mReversible)
{}

CFunction::~CFunction()
{}

bool CFunction::setInfix(const std::string & infix)
{
  if (!CEvaluationTree::setInfix(infix)) return false;
  if (!initVariables()) return false;

  return true;
}

bool CFunction::compile()
{return compileNodes();}

unsigned C_INT32 CFunction::getVariableIndex(const std::string & name) const
  {
    CFunctionParameter::DataType VariableType;
    return mVariables.findParameterByName(name, VariableType);
  }

const C_FLOAT64 & CFunction::getVariableValue(const unsigned C_INT32 & index) const
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

  try
    {
      return mValue = mpRoot->value();
    }
  catch (...)
    {
      return mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
    }
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
  unsigned C_INT32 i;
  for (i = mVariables.size() - 1; i < C_INVALID_INDEX; i--)
    if (NewVariables.findParameterByName(mVariables[i]->getObjectName(), Type) == C_INVALID_INDEX)
      mVariables.remove(mVariables[i]->getObjectName());

  return true;
}

bool CFunction::isSuitable(const unsigned C_INT32 noSubstrates,
                           const unsigned C_INT32 noProducts,
                           const TriLogic reversible)
{
  //first reversibility:
  if (reversible != this->isReversible() &&
      this->isReversible() != TriUnspecified)
    return false;

  //check substrates
  if (mVariables.isVector(CFunctionParameter::SUBSTRATE))
    {
      if (noSubstrates < 1)
        return false;
    }
  else //is no vector
    {
      if (mVariables.getNumberOfParametersByUsage(CFunctionParameter::SUBSTRATE) != noSubstrates)
        return false;
    }

  //check products
  if (reversible == TriTrue)
    {
      if (mVariables.isVector(CFunctionParameter::PRODUCT))
        {
          if (noProducts < 1)
            return false;
        }
      else //is no vector
        {
          if (mVariables.getNumberOfParametersByUsage(CFunctionParameter::PRODUCT) != noProducts)
            return false;
        }
    }

  //no VARIABLE variables allowed for kinetic functions
  if (mVariables.getNumberOfParametersByUsage(CFunctionParameter::VARIABLE) != 0)
    return false;

  return true;
}

#include "utilities/copasimathml.h"

void CFunction::createListOfParametersForMathML(std::vector<std::vector<std::string> > & env)
{
  unsigned C_INT32 i, imax = getVariables().size();

  env.clear();
  env.resize(imax);

  for (i = 0; i < imax; ++i)
    {
      env[i].push_back("<mi>" + getVariables()[i]->getObjectName() + "</mi>");
    }
}

void CFunction::writeMathML(std::ostream & out,
                            const std::vector<std::vector<std::string> > & env,
                            bool expand, bool fullExpand,
                            unsigned C_INT32 l) const
  {
    if (expand && mpRoot)
      {
        bool flag = false; //TODO include check if parantheses are necessary
        if (flag) out << SPC(l) << "<mfenced>" << std::endl;
        mpRoot->writeMathML(out, env, fullExpand, l + 1);
        if (flag) out << SPC(l) << "</mfenced>" << std::endl;
      }
    else //no expand
      {
        out << SPC(l) << "<mrow>" << std::endl;
        out << SPC(l + 1) << CMathMl::fixName(getObjectName()) << std::endl;
        out << SPC(l + 1) << "<mfenced>" << std::endl;

        unsigned C_INT32 i, imax = getVariables().size();
        for (i = 0; i < imax; ++i)
          {
            out << SPC(l + 2) << env[i][0] << std::endl;
          }

        out << SPC(l + 1) << "</mfenced>" << std::endl;
        out << SPC(l) << "</mrow>" << std::endl;
      }
  }

void CFunction::writeMathML(std::ostream & out, unsigned C_INT32 l) const
  {
    //out << "<math>" << std::endl;

    out << SPC(l) << "<mrow>" << std::endl;
    out << SPC(l + 1) << CMathMl::fixName(getObjectName()) << std::endl;
    out << SPC(l + 1) << "<mfenced>" << std::endl;

    unsigned C_INT32 i, imax = getVariables().size();
    for (i = 0; i < imax; ++i)
      {
        out << SPC(l + 2) << "<mi>" << getVariables()[i]->getObjectName() << "</mi>" << std::endl;
      }

    out << SPC(l + 1) << "</mfenced>" << std::endl;
    out << SPC(l) << "</mrow>" << std::endl;

    //out << "</math>" << std::endl;
  }
