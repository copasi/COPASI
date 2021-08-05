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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi/copasi.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "CExpression.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/core/CDataObject.h"
#include "copasi/core/CDataContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/math/CMathObject.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/utilities/CValidatedUnit.h"

#include "sbml/math/ASTNode.h"
#include "sbml/SBase.h"
#include "sbml/SBMLTypeCodes.h"
#include "sbml/Compartment.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/Reaction.h"

CEvaluationNodeObject::CEvaluationNodeObject():
  CEvaluationNode(MainType::OBJECT, SubType::INVALID, ""),
  mpObject(NULL),
  mRegisteredObjectCN("")
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeObject::CEvaluationNodeObject(const SubType & subType,
    const Data & data):
  CEvaluationNode(MainType::OBJECT, subType, data),
  mpObject(NULL),
  mRegisteredObjectCN()
{
  mPrecedence = PRECEDENCE_NUMBER;
  mValueType = ValueType::Number;

  switch (subType)
    {
      case SubType::INVALID:
        break;

      case SubType::CN:

        if (mData == "<Reference=Avogadro Constant>")
          {
            mSubType = SubType::AVOGADRO;
          }

        mRegisteredObjectCN = mData.substr(1, mData.length() - 2);

        break;

      case SubType::AVOGADRO:
        mData = "<Reference=Avogadro Constant>";
        mRegisteredObjectCN = mData.substr(1, mData.length() - 2);
        break;

      case SubType::POINTER:
        mpValue = (const C_FLOAT64 *) stringToPointer(data);
        break;
    }
}

CEvaluationNodeObject::CEvaluationNodeObject(const C_FLOAT64 * pValue):
  CEvaluationNode(MainType::OBJECT, SubType::POINTER, "pointer"),
  mpObject(NULL),
  mRegisteredObjectCN("")
{
  mPrecedence = PRECEDENCE_NUMBER;
  mValueType = ValueType::Number;

  mpValue = pValue;
  mData = pointerToString(pValue);
}

CEvaluationNodeObject::CEvaluationNodeObject(const bool * pValue):
  CEvaluationNode(MainType::OBJECT, SubType::POINTER, "pointer"),
  mpObject(NULL),
  mRegisteredObjectCN("")
{
  mPrecedence = PRECEDENCE_NUMBER;
  mValueType = ValueType::Boolean;

  mpValue = (const C_FLOAT64 *) pValue;
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

CIssue CEvaluationNodeObject::compile()
{

  mpObject = NULL;
  mpValue = NULL;

  mpTree = getTree();

  switch (mSubType)
    {
      case SubType::CN:
      {
        if (mpTree == NULL)
          {
            mValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
            mpValue = &mValue;

            return CIssue(CIssue::eSeverity::Error, CIssue::eKind::StructureInvalid);
          }

        mpObject = mpTree->getNodeObject(mRegisteredObjectCN);

        const CDataObject * pDataObject = CObjectInterface::DataObject(mpObject);

        if (pDataObject != NULL)
          {
            // We may have some container objects for which the value is an included
            // reference. For the math model to work this needs to be corrected.
            const CObjectInterface * pObject = pDataObject->getValueObject();

            if (!pObject)
              {
                mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
                mpValue = &mValue;

                return CIssue(CIssue::eSeverity::Error, CIssue::eKind::ObjectNotFound);
              }

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

            if (mpObject == NULL)
              return CIssue(CIssue::eSeverity::Error, CIssue::eKind::ObjectNotFound);

            return CIssue(CIssue::eSeverity::Error, CIssue::eKind::ValueNotFound);
          }

        mData = "<" + mRegisteredObjectCN + ">";
      }
      break;

      case SubType::POINTER:
        // We need to convert the data into a pointer
        mpValue = (const C_FLOAT64 *) stringToPointer(mData);

        if (mpTree != NULL)
          {
            CMathContainer * pContainer = dynamic_cast< CMathContainer * >(mpTree->getObjectAncestor("CMathContainer"));

            if (pContainer != NULL)
              {
                mpObject = pContainer->getMathObject(mpValue);

                if (mpObject == NULL)
                  {
                    mpObject = pContainer->getDataObject(mpValue);
                  }
              }
          }

        if (mpValue == NULL)
          {
            mValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
            mpValue = &mValue;

            return CIssue(CIssue::eSeverity::Error, CIssue::eKind::ValueNotFound);
          }

        break;

      case SubType::AVOGADRO:
        if (mpTree == NULL)
          {
            mValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
            mpValue = &mValue;

            return CIssue(CIssue::eSeverity::Error, CIssue::eKind::StructureInvalid);
          }

        mpObject = mpTree->getNodeObject(mData.substr(1, mData.length() - 2));

        if (mpObject != NULL)
          {
            mpValue = (C_FLOAT64 *) mpObject->getValuePointer();
          }
        else
          {
            // Fall back to behavior before fix of Bug 3026 for GUI where the proper context is not provided.
            CDataModel * pDataModel = mpTree->getObjectDataModel();

            if (pDataModel != NULL)
              {
                if (pDataModel->getModel() != NULL)
                  {
                    mpObject = mpTree->getNodeObject(pDataModel->getModel()->getCN() + "," + mRegisteredObjectCN);

                    if (mpObject != NULL)
                      {
                        mpValue = (C_FLOAT64 *) mpObject->getValuePointer();
                      }
                  }
              }
          }

        if (mpValue == NULL)
          {
            mValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
            mpValue = &mValue;

            if (mpObject == NULL)
              return CIssue(CIssue::eSeverity::Error, CIssue::eKind::ObjectNotFound);

            return CIssue(CIssue::eSeverity::Error, CIssue::eKind::ValueNotFound);
          }

        break;

      case SubType::INVALID:
        break;
    }

  if (getChild() == NULL) // We must not have any children.
    return CIssue::Success;
  else
    return CIssue(CIssue::eSeverity::Error, CIssue::eKind::TooManyArguments);
}

bool CEvaluationNodeObject::mapObject(const std::string srcCN, const CDataContainer * pTarget)
{
  size_t Length = srcCN.length();

  if (mRegisteredObjectCN.compare(0, Length, srcCN) != 0)
    return true;

  mpValue = NULL;
  mpObject = pTarget->getObject(mRegisteredObjectCN.substr(Length + 1));

  const CDataObject * pDataObject = CObjectInterface::DataObject(mpObject);

  if (pDataObject != NULL)
    {
      // We may have some container objects for which the value is an included
      // reference. For the math model to work this needs to be corrected.
      const CObjectInterface * pObject = pDataObject->getValueObject();

      if (!pObject)
        {
          mValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
          mpValue = &mValue;

          return false;
        }

      if (mpObject != pObject && pObject != NULL)
        {
          mpObject = pObject;
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
      mValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
      mpValue = &mValue;

      return false;
    }

  return true;
}

const CEvaluationNode::Data & CEvaluationNodeObject::getData() const
{
  switch (mSubType)
    {
      case SubType::CN:
        const_cast< CEvaluationNodeObject * >(this)->mData = "<" + mRegisteredObjectCN + ">";
        break;

      case SubType::POINTER:
        break;
    }

  return mData;
}

bool CEvaluationNodeObject::setData(const Data & data)
{
  mData = data;

  if (mSubType == SubType::CN)
    mRegisteredObjectCN = data.substr(1, data.length() - 2);

  return true;
}

// virtual
std::string CEvaluationNodeObject::getInfix(const std::vector< std::string > & /* children */) const
{
  switch (mSubType)
    {
      case SubType::CN:
        return "<" + mRegisteredObjectCN + ">";
        break;

      case SubType::POINTER:
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
      case AST_NAME:
      case AST_NAME_TIME:
        pNode = new CEvaluationNodeObject(SubType::CN, CCommonName(std::string("<") + pASTNode->getName() + std::string(">")));
        break;

      case AST_NAME_AVOGADRO:
        pNode = new CEvaluationNodeObject(SubType::AVOGADRO, "");
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
          if (pOrigObject->getObjectName() == "Avogadro Constant")
            {
              node->setType(AST_NAME_AVOGADRO);
              node->setName("avogadro");
            }
          else
            {
              node->setType(AST_NAME_TIME);
              node->setName("time");

              if (pModel->getInitialTime() != 0.0)
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 1);
                }
            }
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
      case SubType::CN:
        break;

      case SubType::POINTER:

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

#include "copasi/utilities/copasimathml.h"

// virtual
std::string CEvaluationNodeObject::getMMLString(const std::vector< std::string > & /* children */,
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
