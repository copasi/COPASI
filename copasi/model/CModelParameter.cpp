// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelParameter.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/03/08 19:04:40 $
// End CVS Header

// Copyright (C) 2012 - 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <limits>

#include "copasi.h"

#include "CModelParameter.h"
#include "CModelParameterGroup.h"
#include "CModelParameterSet.h"
#include "CMetabNameInterface.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "function/CExpression.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "report/CCopasiObject.h"

// static
const char * CModelParameter::TypeNames[] =
{
  "Model",
  "Compartment",
  "Species",
  "ModelValue",
  "ReactionParameter",
  "Group",
  "Set",
  "unknown",
  NULL
};

// static
std::string CModelParameter::nameFromCN(const CCopasiObjectName & cn)
{
  CCopasiObjectName Primary = cn.getPrimary();
  CCopasiObjectName Remainder = cn.getRemainder();

  while (Remainder != "")
    {
      Primary = Remainder.getPrimary();
      Remainder = Remainder.getRemainder();
    }

  std::string Name = Primary.getElementName(0);

  if (Name != "")
    {
      return Name;
    }

  return Primary.getObjectName();
}

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
{
  if (mpParent != NULL)
    {
      mpParent->remove(this);
    }
}

void CModelParameter::setParent(CModelParameterGroup * pParent)
{
  mpParent = pParent;
}

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

// virtual
void CModelParameter::setValue(const C_FLOAT64 & value, const Framework & /* framework */)
{
  mValue = value;
}

// virtual
const C_FLOAT64 & CModelParameter::getValue(const Framework & /* framework */) const
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

bool CModelParameter::isReadOnly() const
{
  if (mType == Group ||
      mType == Set ||
      (mIsInitialExpressionValid && getInitialExpression() == ""))
    {
      return true;
    }

  return false;
}

CCopasiObject * CModelParameter::getObject() const
{
  return mpObject;
}

CModelParameterSet * CModelParameter::getSet() const
{
  CModelParameterGroup * pParent = mpParent;

  while (pParent != NULL)
    {
      if (pParent->getType() == Set)
        {
          return static_cast< CModelParameterSet * >(pParent);
        }

      pParent = pParent->getParent();
    }

  return NULL;
}

bool CModelParameter::isInitialExpressionValid() const
{
  return mIsInitialExpressionValid;
}

// virtual
std::string CModelParameter::getName() const
{
  if (mpObject != NULL)
    {
      return mpObject->getObjectDisplayName();
    }

  return nameFromCN(mCN);
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

            if (!pModel->isAutonomous())
              {
                pModel->setInitialValue(mValue);
              }
            else
              {
                pModel->setInitialValue(0.0);
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

CModelParameterCompartment::CModelParameterCompartment(CModelParameterGroup * pParent, const CModelParameter::Type & type):
    CModelParameter(pParent, type),
    mSpecies()
{}


CModelParameterCompartment::CModelParameterCompartment(const CModelParameterCompartment & src, CModelParameterGroup * pParent):
    CModelParameter(src, pParent),
    mSpecies()
{}

// virtual
CModelParameterCompartment::~CModelParameterCompartment()
{
  // If a compartment is deleted all contained species are also deleted.
  std::set< CModelParameterSpecies * >::iterator it = mSpecies.begin();
  std::set< CModelParameterSpecies * >::iterator end = mSpecies.end();

  for (; it != end; ++it)
    {
      (*it)->mpCompartment = NULL;
      delete *it;
    }
}

// virtual
void CModelParameterCompartment::setValue(const C_FLOAT64 & value, const Framework & framework)
{
  CVector< C_FLOAT64 > SpeciesValues(mSpecies.size());
  C_FLOAT64 * pSpeciesValue = SpeciesValues.array();

  std::set< CModelParameterSpecies * >::iterator it = mSpecies.begin();
  std::set< CModelParameterSpecies * >::iterator end = mSpecies.end();

  for (; it != end; ++it, ++pSpeciesValue)
    {
      *pSpeciesValue = (*it)->getValue(framework);
    }

  mValue = value;

  pSpeciesValue = SpeciesValues.array();
  it = mSpecies.begin();

  for (; it != end; ++it, ++pSpeciesValue)
    {
      (*it)->setValue(*pSpeciesValue, framework);
    }
}

void CModelParameterCompartment::addSpecies(CModelParameterSpecies * pSpecies)
{
  mSpecies.insert(pSpecies);
}

void CModelParameterCompartment::removeSpecies(CModelParameterSpecies * pSpecies)
{
  mSpecies.erase(pSpecies);
}


CModelParameterSpecies::CModelParameterSpecies(CModelParameterGroup * pParent, const CModelParameter::Type & type):
    CModelParameter(pParent, type),
    mpCompartment(NULL),
    mConcentration(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
{}

CModelParameterSpecies::CModelParameterSpecies(const CModelParameterSpecies & src, CModelParameterGroup * pParent):
    CModelParameter(src, pParent),
    mpCompartment(src.mpCompartment),
    mConcentration(src.mConcentration)
{}

// virtual
CModelParameterSpecies::~CModelParameterSpecies()
{
  if (mpCompartment != NULL)
    {
      mpCompartment->removeSpecies(this);
    }
}

// virtual
std::string CModelParameterSpecies::getName() const
{
  CModel * pModel = getSet()->getModel();

  if (mpObject != NULL)
    {
      return CMetabNameInterface::getDisplayName(pModel, *static_cast< CMetab * >(mpObject));
    }

  return nameFromCN(mCN) + '{' + nameFromCN(getCompartmentCN()) + '}';
}

// virtual
void CModelParameterSpecies::compile()
{
  CModelParameter::compile();

  mpCompartment = static_cast< CModelParameterCompartment * >(getSet()->getModelParameter(getCompartmentCN()));

  if (mpCompartment != NULL)
    {
      mpCompartment->addSpecies(this);
    }
}

// virtual
void CModelParameterSpecies::setValue(const C_FLOAT64 & value, const Framework & framework)
{
  if (framework == Concentration)
    {
      mConcentration = value;

      if (mpCompartment != NULL)
        {
          mValue = mConcentration / mpCompartment->getValue();
        }
      else
        {
          mValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
        }
    }
  else
    {
      mValue = value;

      if (mpCompartment != NULL)
        {
          mConcentration = mValue * mpCompartment->getValue();
        }
      else
        {
          mConcentration = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
        }
    }
}

// virtual
const C_FLOAT64 & CModelParameterSpecies::getValue(const Framework & framework) const
{
  if (framework == Concentration)
    {
      return mConcentration;
    }

  return mValue;
}

CCopasiObjectName CModelParameterSpecies::getCompartmentCN() const
{
  // Determine the parameter for the compartment.
  // "CN=Root,Model=New Model,Vector=Compartments[compartment],Vector=Metabolites[A]"

  CCopasiObjectName Tmp = mCN;
  CCopasiObjectName CompartmentCN;

  for (; Tmp != ""; Tmp = Tmp.getRemainder())
    {
      CCopasiObjectName Primary = Tmp.getPrimary();
      CompartmentCN += Primary;

      if (Primary.getObjectType() == "Vector" ||
          Primary.getObjectName() == "Compartments")
        {
          break;
        }
    }

  return CompartmentCN;
}
