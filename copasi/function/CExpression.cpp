// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CExpression.cpp,v $
//   $Revision: 1.35 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/14 19:19:25 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
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

/*!
    \file CExpression.cpp
    \brief Implementation file of class CExpression
 */

#include "copasi.h"

#include "CExpression.h"

#include "CopasiDataModel/CCopasiDataModel.h"

CExpression::CExpression(const std::string & name,
                         const CCopasiContainer * pParent):
    CEvaluationTree(name, pParent, CEvaluationTree::Expression),
    mpListOfContainer(NULL),
    mDisplayString("")
{
  initObjects();
}

CExpression::CExpression(const CExpression & src,
                         const CCopasiContainer * pParent):
    CEvaluationTree(src, pParent),
    mpListOfContainer(NULL),
    mDisplayString(src.mDisplayString)
{
  initObjects();
  compile();
}

CExpression::~CExpression() {}

void CExpression::initObjects()
{
  CCopasiObjectInterface * pObject =
    const_cast< CCopasiObjectInterface * >(getObject(CCopasiObjectName("Reference=Value")));
  assert(pObject != NULL);

  static_cast< CCopasiObject * >(pObject)->setRefresh(this, &CExpression::refresh);
}

void CExpression::setBooleanRequired(const bool & booleanRequired)
{
  mBooleanRequired = booleanRequired;
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
  bool success = compileNodes();

  if (mpRoot)
    {
      mDisplayString = mpRoot->getDisplayString(this);
      mInfix = mpRoot->getInfix();
    }
  else
    {
      mDisplayString = "";
      mInfix = "";
    }

  mpListOfContainer = NULL;

  return success;
}

const C_FLOAT64 & CExpression::calcValue()
{
  if (!mUsable)
    return mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();

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
{
  const CCopasiDataModel* pDataModel = getObjectDataModel();
  assert(pDataModel != NULL);

  if (mpListOfContainer != NULL)
    return pDataModel->ObjectFromName(*mpListOfContainer, CN);
  else
    {
      return pDataModel->getDataObject(CN);
    }
}

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

std::string CExpression::getDisplay_C_String() const
{
  std::string str1;

  if (mpRoot)
    str1 = mpRoot->getDisplay_C_String(this);
  else
    str1 = "";

  return str1;
}

std::string CExpression::getDisplay_MMD_String() const
{
  std::string str1;

  if (mpRoot)
    str1 = mpRoot->getDisplay_MMD_String(this);
  else
    str1 = "";

  return str1;
}

std::string CExpression::getDisplay_XPP_String() const
{
  std::string str1;

  if (mpRoot)
    str1 = mpRoot->getDisplay_XPP_String(this);
  else
    str1 = "";

  return str1;
}

#include "utilities/copasimathml.h"

void CExpression::writeMathML(std::ostream & out, bool fullExpand, size_t l) const
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

// static
CExpression * CExpression::createInitialExpression(const CExpression & expression, const CCopasiDataModel* pDataModel)
{
  size_t Size = CCopasiMessage::size();
  CExpression * pInitialExpression = new CExpression(expression, expression.getObjectParent());

  std::vector< CEvaluationNode * > * pNodeList =
    const_cast< std::vector< CEvaluationNode * > * >(&pInitialExpression->getNodeList());
  std::vector< CEvaluationNode * >::iterator it = pNodeList->begin();
  std::vector< CEvaluationNode * >::iterator end = pNodeList->end();

  CEvaluationNodeObject * pNode;
  const CCopasiObject * pObject;
  const CCopasiContainer * pObjectParent;
  const CModelEntity * pEntity;
  const CMetab * pMetab;

  for (; it != end; ++it)
    {
      if ((pNode = dynamic_cast< CEvaluationNodeObject * >(*it)) != NULL)
        {
          assert(pDataModel != NULL);

          if ((pObject = static_cast< const CCopasiObject * >(pDataModel->getObject(pNode->getObjectCN()))) != NULL &&
              (pObjectParent = pObject->getObjectParent()) != NULL &&
              (pEntity = dynamic_cast<const CModelEntity * >(pObjectParent)) != NULL)
            {
              if (pEntity->getValueReference() == pObject)
                pNode->setData("<" + pEntity->getInitialValueReference()->getCN() + ">");
              else if ((pMetab = dynamic_cast<const CMetab * >(pEntity)) != NULL &&
                       pMetab->getConcentrationReference() == pObject)
                pNode->setData("<" + pMetab->getInitialConcentrationReference()->getCN() + ">");
            }
        }
    }

  pInitialExpression->updateTree();

  while (CCopasiMessage::size() > Size)
    CCopasiMessage::getLastMessage();

  return pInitialExpression;
}
