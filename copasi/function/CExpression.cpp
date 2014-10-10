// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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
  mDisplayString(""),
  mIsBoolean(false)
{
  initObjects();
}

CExpression::CExpression(const CExpression & src,
                         const CCopasiContainer * pParent):
  CEvaluationTree(src, pParent),
  mpListOfContainer(NULL),
  mDisplayString(src.mDisplayString),
  mIsBoolean(src.mIsBoolean)
{
  initObjects();
  compile();
}

CExpression::~CExpression() {}

void CExpression::initObjects()
{
  CObjectInterface * pObject =
    const_cast< CObjectInterface * >(getObject(CCopasiObjectName("Reference=Value")));
  assert(pObject != NULL);

  static_cast< CCopasiObject * >(pObject)->setRefresh(this, &CExpression::refresh);
}

void CExpression::setIsBoolean(const bool & isBoolean)
{
  mIsBoolean = isBoolean;
}

bool CExpression::setInfix(const std::string & infix)
{
  if (!CEvaluationTree::setInfix(infix)) return false;

  if (mpNodeList == NULL) return true;

  // Check whether the expression has the expected type.
  if (mpRoot != NULL)
    {
      if (mIsBoolean && !mpRoot->isBoolean())
        {
          return false;
        }

      // We wrap a boolean expression in an if construct for
      // non-boolean expressions
      if (!mIsBoolean && mpRoot->isBoolean())
        {
          std::string Infix = "if(" + infix + ", 1, 0)";
          CEvaluationTree::setInfix(Infix);
        }
    }

  // We need to check that the expression does not contain any variables
  std::vector< CEvaluationNode * >::const_iterator it = mpNodeList->begin();
  std::vector< CEvaluationNode * >::const_iterator end = mpNodeList->end();

  for (; it != end; ++it)
    if (((*it)->getType() & 0xFF000000) == CEvaluationNode::VARIABLE)
      return false;

  return true;
}

bool CExpression::compile(CObjectInterface::ContainerList listOfContainer)
{
  listOfContainer.push_back(getObjectParent());
  mpListOfContainer = & listOfContainer;

  bool success = compileNodes();

  if (mpRoot)
    {
      mDisplayString = mpRoot->buildDisplayString();
      mInfix = mpRoot->buildInfix();
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
  calculate();

  return mValue;
}

void CExpression::refresh()
{calcValue();}

const CObjectInterface * CExpression::getNodeObject(const CCopasiObjectName & CN) const
{
  if (mpListOfContainer != NULL)
    {
      return CObjectInterface::GetObjectFromCN(*mpListOfContainer, CN);
    }
  else
    {
      return getObjectFromCN(CN);
    }
}

const CObjectInterface::ContainerList & CExpression::getListOfContainer() const
{return *mpListOfContainer;}

bool CExpression::updateInfix()
{
  if (mpNodeList == NULL) return false;

  mInfix = mpRoot->buildInfix();

  return true;
}

const std::string & CExpression::getDisplayString() const
{return mDisplayString;}

std::string CExpression::getCCodeString() const
{
  std::string str1;

  if (mpRoot)
    str1 = mpRoot->buildCCodeString();
  else
    str1 = "";

  return str1;
}

std::string CExpression::getBerkeleyMadonnaString() const
{
  std::string str1;

  if (mpRoot)
    str1 = mpRoot->buildBerkeleyMadonnaString();
  else
    str1 = "";

  return str1;
}

std::string CExpression::getXPPString() const
{
  std::string str1;

  if (mpRoot)
    str1 = mpRoot->buildXPPString();
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

      out << mpRoot->buildMMLString(fullExpand, env);

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
