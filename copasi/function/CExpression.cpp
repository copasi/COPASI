/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CExpression.cpp,v $
   $Revision: 1.16.2.1 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/09/22 15:06:48 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CExpression.h"
#include "CFunctionDB.h"

#include "CopasiDataModel/CCopasiDataModel.h"

CExpression::CExpression(const std::string & name,
                         const CCopasiContainer * pParent):
    CEvaluationTree(name, pParent, Expression),
    mpListOfContainer(NULL),
    mDisplayString("")
{}

CExpression::CExpression(const CExpression & src,
                         const CCopasiContainer * pParent):
    CEvaluationTree(src, pParent),
    mpListOfContainer(NULL),
    mDisplayString(src.mDisplayString)
{}

CExpression::~CExpression() {}

void CExpression::initObjects()
{
  CCopasiObject * pObject =
    const_cast< CCopasiObject * >(getObject(CCopasiObjectName("Reference=Value")));
  assert (pObject != NULL);

  pObject->setRefresh(this, &CExpression::refresh);
}

bool CExpression::setInfix(const std::string & infix)
{
  if (!CEvaluationTree::setInfix(infix)) return false;

  if (mpNodeList == NULL) return true;

  // We need to check that the expression does not contain any variables
  std::vector< CEvaluationNode * >::const_iterator it = mpNodeList->begin();
  std::vector< CEvaluationNode * >::const_iterator end = mpNodeList->end();

  for (; it != end; ++it)
    if (((*it)->getType() & 0xFF000000) == CEvaluationNode::VARIABLE)
      return false;

  return true;
}

bool CExpression::compile(std::vector< CCopasiContainer * > listOfContainer)
{
  mpListOfContainer = & listOfContainer;

  if (mpRoot)
    mDisplayString = mpRoot->getDisplayString(this);
  else
    mDisplayString = "";

  bool success = compileNodes();

  if (success && mpNodeList)
    {
      const CCopasiObject * pObject;
      std::set< const CCopasiObject * > Dependencies;

      std::vector< CEvaluationNode * >::const_iterator it = mpNodeList->begin();
      std::vector< CEvaluationNode * >::const_iterator end = mpNodeList->end();

      for (; it != end; ++it)
        if (((*it)->getType() & 0xFF000000) == CEvaluationNode::OBJECT &&
            (pObject = getNodeObject(static_cast< CEvaluationNodeObject *>(*it)->getObjectCN())) != NULL)
          Dependencies.insert(pObject);
        else if (((*it)->getType() & 0xFF000000) == CEvaluationNode::CALL)
          Dependencies.insert(static_cast< CEvaluationNodeCall *>(*it)->getCalledTree());

      setDirectDependencies(Dependencies);
      const_cast< CCopasiObject * >(getObject(CCopasiObjectName("Reference=Value")))->setDirectDependencies(Dependencies);
    }

  return success;
}

const C_FLOAT64 & CExpression::calcValue()
{
  try
    {
      return mValue = mpRoot->value();
    }
  catch (...)
    {
      return mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
    }
}

void CExpression::refresh()
{calcValue();}

const CCopasiObject * CExpression::getNodeObject(const CCopasiObjectName & CN) const
  {return CCopasiContainer::ObjectFromName(*mpListOfContainer, CN);}

const std::vector< CCopasiContainer * > & CExpression::getListOfContainer() const
  {return *mpListOfContainer;}

bool CExpression::updateInfix()
{
  if (mpNodeList == NULL) return false;

  mInfix = mpRoot->getInfix();

  return true;
}

const std::string & CExpression::getDisplayString() const
{return mDisplayString;}

#include "utilities/copasimathml.h"

void CExpression::writeMathML(std::ostream & out, bool fullExpand, unsigned C_INT32 l) const
  {
    if (mpRoot)
      {
        //create empty environment. Variable nodes should not occur in an expression
        std::vector<std::vector<std::string> > env;

        bool flag = false; //TODO include check if parantheses are necessary
        if (flag) out << SPC(l) << "<mfenced>" << std::endl;
        mpRoot->writeMathML(out, env, fullExpand, l + 1);
        if (flag) out << SPC(l) << "</mfenced>" << std::endl;
      }
  }
