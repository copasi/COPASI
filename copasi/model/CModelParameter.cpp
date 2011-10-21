// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelParameter.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/10/21 17:45:15 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <limits>

#include "copasi.h"

#include "CModelParameter.h"
#include "CModelParameterGroup.h"
#include "CModelParameterSet.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "function/CExpression.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "report/CCopasiObject.h"

CModelParameter::CModelParameter(CModelParameterGroup * pParent, const CModelParameter::Type & type):
    mpParent(pParent),
    mType(type),
    mCN(),
    mValue(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
    mpInitialExpression(NULL),
    mCompareResult(CModelParameter::Identical),
    mpObject(NULL),
    mIsInitialExpressionValid(true)
{
  assert(mType == Set || mpParent != NULL);
}

CModelParameter::CModelParameter(const CModelParameter & src, CModelParameterGroup * pParent):
    mpParent(pParent),
    mType(src.mType),
    mCN(src.mCN),
    mValue(src.mValue),
    mpInitialExpression(NULL),
    mCompareResult(src.mCompareResult),
    mpObject(src.mpObject),
    mIsInitialExpressionValid(src.mIsInitialExpressionValid)
{
  assert(mType == Set || mpParent != NULL);

  setInitialExpression(src.getInitialExpression());
}

// virtual
CModelParameter::~CModelParameter()
{}

CModelParameterGroup * CModelParameter::getParent() const
{
  return mpParent;
}

const CModelParameter::Type & CModelParameter::getType() const
{
  return mType;
}


void CModelParameter::setCN(const CCopasiObjectName & cn)
{
  mCN = cn;
}

const CCopasiObjectName & CModelParameter::getCN() const
{
  return mCN;
}

void CModelParameter::setValue(const C_FLOAT64 & value)
{
  mValue = value;
}

const C_FLOAT64 & CModelParameter::getValue() const
{
  return mValue;
}

void CModelParameter::setInitialExpression(const std::string & initialExpression)
{
  if (initialExpression != "" &&
      mpInitialExpression == NULL)
    {
      CModelParameterGroup * pParent = mpParent;

      while (pParent->getType() != Set)
        {
          pParent = pParent->getParent();
        }

      mpInitialExpression = new CExpression("InitialExpression", static_cast< CModelParameterSet * >(pParent));
    }

  mpInitialExpression->setInfix(initialExpression);
}

std::string CModelParameter::getInitialExpression() const
{
  if (mpInitialExpression == NULL)
    {
      return "";
    }

  return mpInitialExpression->getInfix();
}

void CModelParameter::setCompareResult(const CModelParameter::CompareResult & compareResult)
{
  mCompareResult = compareResult;
}

const CModelParameter::CompareResult & CModelParameter::getCompareResult() const
{
  return mCompareResult;
}


size_t CModelParameter::getIndex() const
{
  CModelParameterGroup::const_iterator it = mpParent->begin();
  CModelParameterGroup::const_iterator end = mpParent->end();


  size_t Index = 0;

  for (; it != end; ++it, ++Index)
    {
      if (*it == this) return Index;
    }

  return C_INVALID_INDEX;
}

CCopasiObject * CModelParameter::getObject() const
{
  return mpObject;
}

bool CModelParameter::isInitialExpressionValid() const
{
  return mIsInitialExpressionValid;
}

void CModelParameter::compile()
{
  mpObject = NULL;
  mIsInitialExpressionValid = true;

  CModel * pModel = mpParent->getModel();

  assert(pModel == NULL);

  std::vector< CCopasiContainer * > ListOfContainer;
  ListOfContainer.push_back(pModel);

  mpObject = pModel->getObjectDataModel()->ObjectFromName(ListOfContainer, mCN);

  if (mpObject != NULL)
    {
      if (mType == unknown)
        {
          if (dynamic_cast< CModel * >(mpObject) != NULL)
            mType = Model;
          else if (dynamic_cast< CCompartment * >(mpObject) != NULL)
            mType = Compartment;
          else if (dynamic_cast< CMetab * >(mpObject) != NULL)
            mType = Species;
          else if (dynamic_cast< CModelValue * >(mpObject) != NULL)
            mType = ModelValue;
          else if (dynamic_cast< CModelValue * >(mpObject) != NULL)
            mType = ReactionParameter;
        }
    }

  if (mpInitialExpression != NULL)
    {
      mIsInitialExpressionValid = mpInitialExpression->compile();
    }
}

const CModelParameter::CompareResult & CModelParameter::diff(const CModelParameter & other)
{
  if (getInitialExpression() != other.getInitialExpression() ||
      mValue != other.getValue())
    {
      mCompareResult = Modified;
    }
  else
    {
      mCompareResult = Identical;
    }

  return mCompareResult;
}

// virtual
bool CModelParameter::updateModel()
{
  bool success = true;

  if (mpObject != NULL)
    {
      switch (mType)
        {
          case Model:
          {
            CModel * pModel = static_cast< CModel * >(mpObject);

            if (pModel->isAutonomous())
              {
                pModel->setInitialValue(mValue);
              }
          }
          break;

          case Compartment:
          case Species:
          case ModelValue:
          {
            CModelEntity * pEntity = static_cast< CModelEntity * >(mpObject);
            pEntity->setInitialValue(mValue);

            if (mIsInitialExpressionValid)
              {
                pEntity->setInitialExpression(getInitialExpression());
              }
          }
          break;

          case ReactionParameter:
          {
            CCopasiParameter * pParameter = static_cast< CCopasiParameter * >(mpObject);
            pParameter->setValue(mValue);

            if (mIsInitialExpressionValid &&
                getInitialExpression() != "")
              {
                CModel * pModel = mpParent->getModel();

                assert(pModel == NULL);

                std::vector< CCopasiContainer * > ListOfContainer;
                ListOfContainer.push_back(pModel);

                CCopasiObjectName CN = static_cast< CEvaluationNodeObject * >(mpInitialExpression->getRoot())->getObjectCN();
                mpObject = pModel->getObjectDataModel()->ObjectFromName(ListOfContainer, CN);

                CReaction * pReaction = static_cast< CReaction * >(mpObject->getObjectAncestor("CReaction"));
                pReaction->setParameterMapping(pParameter->getObjectName(), mpObject->getKey());
              }
          }
          break;

          default:
            success = false;
            break;
        }
    }

  return success;
}
