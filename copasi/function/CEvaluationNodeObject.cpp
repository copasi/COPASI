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
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "CExpression.h"
#include "core/CRegisteredCommonName.h"
#include "copasi/core/CDataObject.h"
#include "copasi/core/CDataContainer.h"
#include "model/CModel.h"
#include "CopasiDataModel/CDataModel.h"
#include "math/CMathObject.h"
#include "math/CMathContainer.h"
#include "utilities/CValidatedUnit.h"

#include "sbml/math/ASTNode.h"
#include "sbml/SBase.h"
#include "sbml/SBMLTypeCodes.h"
#include "sbml/Compartment.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/Reaction.h"

CEvaluationNodeObject::CEvaluationNodeObject():
  CEvaluationNode(T_OBJECT, S_INVALID, ""),
  mpObject(NULL),
  mRegisteredObjectCN("")
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeObject::CEvaluationNodeObject(const SubType & subType,
    const Data & data):
  CEvaluationNode(T_OBJECT, subType, data),
  mpObject(NULL),
  mRegisteredObjectCN()
{
  switch (subType)
    {
      case S_INVALID:
        break;

      case S_CN:
        mRegisteredObjectCN = data.substr(1, data.length() - 2);
        break;

      case S_POINTER:
        mpValue = (const C_FLOAT64 *) stringToPointer(data);
        break;
    }

  mPrecedence = PRECEDENCE_NUMBER;
}

CEvaluationNodeObject::CEvaluationNodeObject(const C_FLOAT64 * pValue):
  CEvaluationNode(T_OBJECT, S_POINTER, "pointer"),
  mpObject(NULL),
  mRegisteredObjectCN("")
{
  mPrecedence = PRECEDENCE_NUMBER;
  mpValue = pValue;
  mData = pointerToString(pValue);
}

CEvaluationNodeObject::CEvaluationNodeObject(const CEvaluationNodeObject & src):
  CEvaluationNode(src),
  mpObject(src.mpObject),
  mRegisteredObjectCN(src.mRegisteredObjectCN)
{
  mpValue = src.mpValue;
}

CEvaluationNodeObject::~CEvaluationNodeObject() {}

CIssue CEvaluationNodeObject::compile(const CEvaluationTree * pTree)
{
  mpObject = NULL;
  mpValue = NULL;

  switch (mSubType)
    {
      case S_CN:
      {
        const CExpression * pExpression = dynamic_cast< const CExpression * >(pTree);

        if (!pExpression) return CIssue(CIssue::eSeverity::Error, CIssue::eKind::CExpressionNotFound);

        mpObject =
          pExpression->getNodeObject(mRegisteredObjectCN);

        const CDataObject * pDataObject = dynamic_cast< const CDataObject * >(mpObject);

        if (pDataObject != NULL)
          {
            // We may have some container objects for which the value is an included
            // reference. For the math model to work this needs to be corrected.
            const CObjectInterface * pObject = pDataObject->getValueObject();

            if (!pObject)
              return CIssue(CIssue::eSeverity::Error, CIssue::eKind::ObjectNotFound);

            if (mpObject != pObject && pObject != NULL)
              {
                mpObject = pObject;
                mRegisteredObjectCN = mpObject->getCN();
                mData = getData();
              }

            if (pDataObject->hasFlag(CDataObject::ValueDbl))
              {
                mpValue = (C_FLOAT64 *) mpObject->getValuePointer();
              }
          }
        else if (mpObject != NULL)
          {
            mpValue = (C_FLOAT64 *) mpObject->getValuePointer();
          }

        if (mpValue == NULL)
          {
            mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
            mpValue = &mValue;
            return CIssue(CIssue::eSeverity::Error, CIssue::eKind::ValueNotFound);
          }

        mData = "<" + mRegisteredObjectCN + ">";
      }
      break;

      case S_POINTER:
        // We need to convert the data into a pointer
        mpValue = (const C_FLOAT64 *) stringToPointer(mData);

        if (pTree != NULL)
          {
            CMathContainer * pContainer = dynamic_cast< CMathContainer * >(pTree->getObjectAncestor("CMathContainer"));

            if (pContainer != NULL)
              {
                mpObject = pContainer->getMathObject(mpValue);
              }
          }

        if (mpValue == NULL)
          {
            mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
            mpValue = &mValue;
            return CIssue(CIssue::eSeverity::Error, CIssue::eKind::ValueNotFound);
          }

        break;

      case S_INVALID:
        break;
    }

  if (getChild() == NULL) // We must not have any children.
    return CIssue::Success;
  else
    return CIssue(CIssue::eSeverity::Error, CIssue::eKind::TooManyArguments);
}

const CEvaluationNode::Data & CEvaluationNodeObject::getData() const
{
  static std::string data;

  switch (mSubType)
    {
      case S_CN:
        return data = "<" + mRegisteredObjectCN + ">";
        break;

      case S_POINTER:
        return mData;
        break;
    }

  return mData;
}

bool CEvaluationNodeObject::setData(const Data & data)
{
  mData = data;

  if (mSubType == S_CN)
    mRegisteredObjectCN = data.substr(1, data.length() - 2);

  return true;
}

// virtual
std::string CEvaluationNodeObject::getInfix(const std::vector< std::string > & /* children */) const
{
  switch (mSubType)
    {
      case S_CN:
        return "<" + mRegisteredObjectCN + ">";
        break;

      case S_POINTER:
        return mData;
        break;
    }

  return mData;
}

#if 0
std::string CEvaluationNodeObject::getDisplayString(const CEvaluationTree * pTree) const
{
  const CExpression * pExpression = dynamic_cast< const CExpression * >(pTree);

  if (!pExpression) return false;

  const CDataObject * pObject =
    CDataContainer::ObjectFromCN(mRegisteredObjectCN);

  if (pObject == NULL) return "<" + mRegisteredObjectCN + ">";

  return "<" + pObject->getObjectDisplayName() + ">";
}
#endif

// virtual
std::string CEvaluationNodeObject::getDisplayString(const std::vector< std::string > & /* children */) const
{
  const CDataObject* object = dynamic_cast<const CDataObject*>(mpObject);

  if (object != NULL)
    return object->getObjectDisplayName();

  return "<" + mRegisteredObjectCN + ">";
}

// virtual
std::string CEvaluationNodeObject::getCCodeString(const std::vector< std::string > & /* children */) const
{
  return mData;
}

// virtual
std::string CEvaluationNodeObject::getBerkeleyMadonnaString(const std::vector< std::string > & /* children */) const
{
  return mData;
}

// virtual
std::string CEvaluationNodeObject::getXPPString(const std::vector< std::string > & /* children */) const
{
  return mData;
}

// static
CEvaluationNode * CEvaluationNodeObject::fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children)
{
  assert(pASTNode->getNumChildren() == children.size());

  CEvaluationNodeObject* pNode = NULL;

  switch (pASTNode->getType())
    {
      case AST_NAME_AVOGADRO:
      case AST_NAME_TIME:
      case AST_NAME:
        pNode = new CEvaluationNodeObject(S_CN, CCommonName(std::string("<") + pASTNode->getName() + std::string(">")));
        break;

      default:
        break;
    }

  return pNode;
}

ASTNode* CEvaluationNodeObject::toAST(const CDataModel* pDataModel) const
{
  ASTNode* node = new ASTNode();
  node->setType(AST_NAME);

  if (mRegisteredObjectCN == "rateOf" || mData == "<rateOf>")
    {
      node->setType(AST_FUNCTION);
      const CEvaluationNode* child = dynamic_cast<const CEvaluationNode*>(this->getChild());

      if (child == NULL) fatalError();

      const CEvaluationNodeObject* sibling = dynamic_cast<const CEvaluationNodeObject*>(this->getChild()->getSibling());

      if (sibling == NULL) fatalError();

      node->setName(sibling->getObjectCN().c_str());
      node->addChild(child->toAST(pDataModel));
      return node;
    }

  // since I can not get the model in which this node is located, I just
  // assume that it will always be the current global model.
  const CDataObject* pOrigObject = CObjectInterface::DataObject(pDataModel->getObjectFromCN(mRegisteredObjectCN));

  if (pOrigObject == NULL)
    {
      node->setName(mRegisteredObjectCN.c_str());
      return node;
    }

  const CDataObject* pObject = pOrigObject;

  // if it is a reference, we get the parent of the reference
  if (pObject->hasFlag(CDataObject::Reference))
    {
      pObject = pObject->getObjectParent();
    }

  const CModelEntity* pME = dynamic_cast<const CModelEntity*>(pObject);

  if (pME != NULL)
    {
      const CModel* pModel = dynamic_cast<const CModel*>(pME);

      if (pModel != NULL)
        {
#if LIBSBML_VERSION >= 40100

          if (pOrigObject->getObjectName() == "Avogadro Constant")
            {
              node->setType(AST_NAME_AVOGADRO);
              node->setName("avogadro");
            }
          else
            {
#endif // LIBSBML_VERSION >= 40100
              node->setType(AST_NAME_TIME);
              node->setName("time");

              if (pModel->getInitialTime() != 0.0)
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 1);
                }

#if LIBSBML_VERSION >= 40100
            }

#endif // LIBSBML_VERSION >= 40100
        }
      else
        {
          node->setName(pME->getSBMLId().c_str());
        }
    }
  else
    {
      const CCopasiParameter* pPara = dynamic_cast<const CCopasiParameter*>(pObject);

      if (pPara != NULL)
        {
          // now we have to use the common name as the name for the
          // node since we need to be able to identify local parameters
          // in arbitrary expressions for the export
          node->setName(pPara->getCN().c_str());
        }
      else
        {
          const CReaction* pReaction = dynamic_cast<const CReaction*>(pObject);

          if (pReaction)
            {
              node->setName(pReaction->getSBMLId().c_str());
            }
          else
            {
              fatalError();
            }
        }
    }

  return node;
}

const CRegisteredCommonName & CEvaluationNodeObject::getObjectCN() const
{return mRegisteredObjectCN;}

const CObjectInterface * CEvaluationNodeObject::getObjectInterfacePtr() const
{
  return mpObject;
}

const C_FLOAT64 * CEvaluationNodeObject::getObjectValuePtr() const
{
  return mpValue;
}

void CEvaluationNodeObject::setObjectValuePtr(C_FLOAT64 * pObjectValue)
{
  switch (mSubType)
    {
      case S_CN:
        break;

      case S_POINTER:

        if (mpValue != pObjectValue)
          {
            mpValue = pObjectValue;
            mData = pointerToString(mpValue);

            if (mpValue == NULL)
              {
                mpValue = &mValue;
              }
          }

        break;
    }

  return;
}

#include "utilities/copasimathml.h"

// virtual
std::string CEvaluationNodeObject::getMMLString(const std::vector< std::string > & /* children */ ,
    bool /* expand */,
    const std::vector< std::vector< std::string > > & /* variables */) const
{
  std::ostringstream out;

  const CDataObject * pDataObject = CObjectInterface::DataObject(mpObject);

  out << CMathMl::getMMLName(pDataObject) << std::endl;

  return out.str();
}

// virtual
CValidatedUnit CEvaluationNodeObject::getUnit(const CMathContainer & container,
    const std::vector< CValidatedUnit > & units) const
{
  const CObjectInterface * pObject = container.getMathObject(mpValue);
  const CDataObject * pDataObject = (pObject != NULL) ? pObject->getDataObject() : NULL;

  if (pDataObject != NULL)
    {
      return CValidatedUnit::merge(units[0], CValidatedUnit(pDataObject->getUnits(), false));
    }

  return CValidatedUnit::merge(units[0], CValidatedUnit());
}
