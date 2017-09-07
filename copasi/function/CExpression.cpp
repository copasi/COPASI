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

/*!
    \file CExpression.cpp
    \brief Implementation file of class CExpression
 */

#include "copasi.h"

#include "CExpression.h"

#include "CopasiDataModel/CDataModel.h"

CExpression::CExpression(const std::string & name,
                         const CDataContainer * pParent):
  CEvaluationTree(name, pParent, CEvaluationTree::Expression),
  mpListOfContainer(NULL),
  mDisplayString(""),
  mIsBoolean(false)
{
  initObjects();
}

CExpression::CExpression(const CExpression & src,
                         const CDataContainer * pParent):
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
    const_cast< CObjectInterface * >(getObject(CCommonName("Reference=Value")));
  assert(pObject != NULL);
}

void CExpression::setIsBoolean(const bool & isBoolean)
{
  mIsBoolean = isBoolean;
}

CIssue CExpression::setInfix(const std::string & infix)
{
  CIssue firstWorstIssue, issue;
  firstWorstIssue = CEvaluationTree::setInfix(infix);
  mValidity.add(firstWorstIssue);

  if (!firstWorstIssue || mpNodeList == NULL)
    return firstWorstIssue;

  // Check whether the expression has the expected type.
  if (mpRootNode != NULL)
    {
      if (mIsBoolean && !mpRootNode->isBoolean())
        {
          issue = CIssue(CIssue::eSeverity::Error, CIssue::eKind::ExpressionDataTypeInvalid);
          mValidity.add(issue);
          return firstWorstIssue &= issue;
        }

      // We wrap a boolean expression in an if construct for
      // non-boolean expressions
      if (!mIsBoolean && mpRootNode->isBoolean())
        {
          std::string Infix = "if(" + infix + ", 1, 0)";
          issue = CEvaluationTree::setInfix(Infix);
          mValidity.add(issue);
          firstWorstIssue &= issue;
        }
    }

  // We need to check that the expression does not contain any variables
  std::vector< CEvaluationNode * >::const_iterator it = mpNodeList->begin();
  std::vector< CEvaluationNode * >::const_iterator end = mpNodeList->end();

  for (; it != end; ++it)
    if ((*it)->mainType() == CEvaluationNode::MainType::VARIABLE)
      {
        issue = CIssue(CIssue::eSeverity::Error, CIssue::eKind::VariableInExpression);
        mValidity.add(issue);
        return firstWorstIssue &= issue;
      }

  return firstWorstIssue;
}

CIssue CExpression::compile(CObjectInterface::ContainerList listOfContainer)
{
  if (getObjectParent() != NULL)
    listOfContainer.push_back(getObjectParent());

  mpListOfContainer = & listOfContainer;

  // Reset all compile related issues
  mValidity.remove(CValidity::Severity::All,
                   (CValidity::Kind(CIssue::eKind::ExpressionInvalid) |
                    CIssue::eKind::ExpressionEmpty |
                    CIssue::eKind::HasCircularDependency |
                    CIssue::eKind::ExpressionDataTypeInvalid));

  CIssue issue = compileNodes();
  mValidity.add(issue);

  if (mpRootNode)
    {
      mDisplayString = mpRootNode->buildDisplayString();
      mInfix = mpRootNode->buildInfix();
    }
  else
    {
      mDisplayString = "";
      mInfix = "";
    }

  mpListOfContainer = NULL;

  return issue;
}

const C_FLOAT64 & CExpression::calcValue()
{
  calculate();

  return mValue;
}

void CExpression::refresh()
{calcValue();}

const CObjectInterface * CExpression::getNodeObject(const CCommonName & CN) const
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
  if (mpRootNode != NULL)
    {
      mInfix = mpRootNode->buildInfix();
    }

  return true;
}

const std::string & CExpression::getDisplayString() const
{return mDisplayString;}

std::string CExpression::getCCodeString() const
{
  std::string str1;

  if (mpRootNode)
    str1 = mpRootNode->buildCCodeString();
  else
    str1 = "";

  return str1;
}

std::string CExpression::getBerkeleyMadonnaString() const
{
  std::string str1;

  if (mpRootNode)
    str1 = mpRootNode->buildBerkeleyMadonnaString();
  else
    str1 = "";

  return str1;
}

std::string CExpression::getXPPString() const
{
  std::string str1;

  if (mpRootNode)
    str1 = mpRootNode->buildXPPString();
  else
    str1 = "";

  return str1;
}

#include "utilities/copasimathml.h"

void CExpression::writeMathML(std::ostream & out, bool fullExpand, size_t l) const
{
  if (mpRootNode)
    {
      //create empty environment. Variable nodes should not occur in an expression
      std::vector<std::vector<std::string> > env;

      bool flag = false; //TODO include check if parantheses are necessary

      if (flag) out << SPC(l) << "<mfenced>" << std::endl;

      out << mpRootNode->buildMMLString(fullExpand, env);

      if (flag) out << SPC(l) << "</mfenced>" << std::endl;
    }
}

// static
CExpression * CExpression::createInitialExpression(const CExpression & expression, const CDataModel* pDataModel)
{
  size_t Size = CCopasiMessage::size();
  CExpression * pInitialExpression = new CExpression(expression, expression.getObjectParent());

  std::vector< CEvaluationNode * > * pNodeList =
    const_cast< std::vector< CEvaluationNode * > * >(&pInitialExpression->getNodeList());
  std::vector< CEvaluationNode * >::iterator it = pNodeList->begin();
  std::vector< CEvaluationNode * >::iterator end = pNodeList->end();

  CEvaluationNodeObject * pNode;
  const CDataObject * pObject;
  const CDataContainer * pObjectParent;
  const CModelEntity * pEntity;
  const CMetab * pMetab;

  for (; it != end; ++it)
    {
      if ((pNode = dynamic_cast< CEvaluationNodeObject * >(*it)) != NULL)
        {
          assert(pDataModel != NULL);

          if ((pObject = static_cast< const CDataObject * >(pDataModel->getObject(pNode->getObjectCN()))) != NULL &&
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
