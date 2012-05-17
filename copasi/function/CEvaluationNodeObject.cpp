// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeObject.cpp,v $
//   $Revision: 1.61 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/17 18:11:30 $
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

#include "copasi.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "CExpression.h"
#include "report/CCopasiObjectName.h"
#include "report/CCopasiObject.h"
#include "report/CCopasiContainer.h"
#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "math/CMathObject.h"

#include "sbml/math/ASTNode.h"
#include "sbml/SBase.h"
#include "sbml/SBMLTypeCodes.h"
#include "sbml/Compartment.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/Reaction.h"

CEvaluationNodeObject::CEvaluationNodeObject():
    CEvaluationNode(CEvaluationNode::INVALID, ""),
    mpObject(NULL),
    mRegisteredObjectCN("")
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeObject::CEvaluationNodeObject(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type)(CEvaluationNode::OBJECT | subType), data),
    mpObject(NULL),
    mRegisteredObjectCN(data.substr(1, data.length() - 2))
{
  mPrecedence = PRECEDENCE_NUMBER;
}

CEvaluationNodeObject::CEvaluationNodeObject(const C_FLOAT64 * pValue):
    CEvaluationNode((Type)(CEvaluationNode::OBJECT | POINTER), "pointer"),
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

bool CEvaluationNodeObject::compile(const CEvaluationTree * pTree)
{
  mpObject = NULL;
  mpValue = NULL;

  switch ((int) subType(mType))
    {
      case CN:
      {
        const CExpression * pExpression = dynamic_cast< const CExpression * >(pTree);

        if (!pExpression) return false;

        mpObject =
          pExpression->getNodeObject(mRegisteredObjectCN);

        const CCopasiObject * pDataObject = dynamic_cast< const CCopasiObject * >(mpObject);

        if (pDataObject != NULL)
          {
            // We may have some container objects for which the value is an included
            // reference. For the math model to work this needs to be corrected.
            const CObjectInterface * pObject = pDataObject->getValueObject();

            if (mpObject != pObject)
              {
                mpObject = pObject;
                mRegisteredObjectCN = mpObject->getCN();
                mData = getData();
              }

            if (pDataObject->isValueDbl())
              {
                mpValue = (C_FLOAT64 *) mpObject->getValuePointer();
              }
          }
        else if (mpObject != NULL)
          {
            // TODO CRITICAL SH: I like to avoid these for the time being
            assert(false);

            mpValue = (C_FLOAT64 *) mpObject->getValuePointer();
          }

        if (mpValue == NULL)
          {
            mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
            mpValue = &mValue;
            return false;
          }


        mData = "<" + mRegisteredObjectCN + ">";
      }
      break;

      case POINTER:
        // We need to convert the data into a pointer
      {
        mpValue = (const C_FLOAT64 *) stringToPointer(mData);
      }
      break;

      case INVALID:
        break;
    }

  return (getChild() == NULL); // We must not have any children.
}

const CEvaluationNode::Data & CEvaluationNodeObject::getData() const
{
  static std::string data;

  switch ((int) subType(mType))
    {
      case CN:
        return data = "<" + mRegisteredObjectCN + ">";
        break;

      case POINTER:
        return mData;
        break;
    }

  return mData;
}

bool CEvaluationNodeObject::setData(const Data & data)
{
  mData = data;

  if ((int) subType(mType) == (int) CN)
    mRegisteredObjectCN = data.substr(1, data.length() - 2);

  return true;
}

// virtual
std::string CEvaluationNodeObject::getInfix(const std::vector< std::string > & /* children */) const
{
  switch ((int) subType(mType))
    {
      case CN:
        return "<" + mRegisteredObjectCN + ">";
        break;

      case POINTER:
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

  const CCopasiObject * pObject =
    CCopasiContainer::ObjectFromName(mRegisteredObjectCN);

  if (pObject == NULL) return "<" + mRegisteredObjectCN + ">";

  return "<" + pObject->getObjectDisplayName() + ">";
}
#endif

// virtual
std::string CEvaluationNodeObject::getDisplayString(const std::vector< std::string > & /* children */) const
{
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
        pNode = new CEvaluationNodeObject(CN, CCopasiObjectName(std::string("<") + pASTNode->getName() + std::string(">")));
        break;
      default:
        break;
    }

  return pNode;
}

ASTNode* CEvaluationNodeObject::toAST(const CCopasiDataModel* pDataModel) const
{
  ASTNode* node = new ASTNode();
  node->setType(AST_NAME);
  // since I can not get the model in which this node is located, I just
  // assume that it will always be the current global model.
  const CCopasiObject* pOrigObject = pDataModel->getDataObject(mRegisteredObjectCN);
  assert(pOrigObject);
  const CCopasiObject* pObject = pOrigObject;

  // if it is a reference, we get the parent of the reference
  if (pObject->isReference())
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

const CRegisteredObjectName & CEvaluationNodeObject::getObjectCN() const
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
  assert(pObjectValue);

  switch ((int) subType(mType))
    {
      case CN:
        break;

      case POINTER:

        if (mpValue != pObjectValue)
          {
            mpValue = pObjectValue;
            mData = pointerToString(mpValue);
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

  const CCopasiObject * pDataObject = dynamic_cast< const CCopasiObject * >(mpObject);

  if (pDataObject == NULL)
    {
      const CMathObject * pMathObject = dynamic_cast< const CMathObject * >(mpObject);

      if (pMathObject != NULL)
        {
          pDataObject = pMathObject->getDataObject();
        }
    }

  out << CMathMl::getMMLName(pDataObject) << std::endl;

  return out.str();
}
