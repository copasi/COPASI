// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelParameter.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/06/04 17:36:43 $
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
    mpParent(static_cast< CModelParameterGroup * >(pParent)),
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

// virtual
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

  CModelParameterSet * pSet = getSet();

  if (pSet->isActive())
    {
      updateModel();
    }
}

// virtual
const C_FLOAT64 & CModelParameter::getValue(const Framework & /* framework */) const
{
  return mValue;
}

void CModelParameter::setInitialExpression(const std::string & initialExpression)
{
  if (initialExpression == "")
    {
      pdelete(mpInitialExpression);
      return;
    }

  if (mpInitialExpression == NULL)
    {
      mpInitialExpression = new CExpression("InitialExpression", getSet());
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
  if (mType == Set)
    {
      return static_cast< CModelParameterSet * >(const_cast< CModelParameter * >(this));
    }

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

CModel * CModelParameter::getModel() const
{
  CModelParameterSet * pSet = getSet();

  if (pSet != NULL)
    {
      return pSet->getModel();
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
      if (mType == Species)
        {
          return mpObject->getObjectDisplayName();
        }
      else
        {
          return mpObject->getObjectName();
        }
    }

  return nameFromCN(mCN);
}

void CModelParameter::compile()
{
  mpObject = NULL;
  mIsInitialExpressionValid = true;

  CModel * pModel = getModel();

  assert(pModel != NULL);

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

                assert(pModel != NULL);

                std::vector< CCopasiContainer * > ListOfContainer;
                ListOfContainer.push_back(pModel);

                CCopasiObjectName CN = static_cast< CEvaluationNodeObject * >(mpInitialExpression->getRoot())->getObjectCN();
                CCopasiObject * pObject = pModel->getObjectDataModel()->ObjectFromName(ListOfContainer, CN);

                assert(pObject != NULL);

                CReaction * pReaction = static_cast< CReaction * >(mpObject->getObjectAncestor("Reaction"));
                pReaction->setParameterMapping(pParameter->getObjectName(), pObject->getObjectParent()->getKey());
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
    mCompartmentCN(),
    mpCompartment(NULL),
    mConcentration(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
{}

CModelParameterSpecies::CModelParameterSpecies(const CModelParameterSpecies & src, CModelParameterGroup * pParent):
    CModelParameter(src, pParent),
    mCompartmentCN(src.mCompartmentCN),
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
      return CMetabNameInterface::getDisplayName(pModel, *static_cast< CMetab * >(mpObject), false);
    }

  return nameFromCN(mCN) + '{' + nameFromCN(getCompartmentCN()) + '}';
}

// virtual
void CModelParameterSpecies::compile()
{
  CModelParameter::compile();

  mpCompartment = static_cast< CModelParameterCompartment * >(getSet()->getModelParameter(mCompartmentCN));

  if (mpCompartment != NULL)
    {
      mpCompartment->addSpecies(this);
    }

  // Update the concentration if possible
  setValue(mValue);
}

// virtual
void CModelParameterSpecies::setCN(const CCopasiObjectName & cn)
{
  CModelParameter::setCN(cn);

  // Determine the CN for the compartment.
  // "CN=Root,Model=New Model,Vector=Compartments[compartment],Vector=Metabolites[A]"
  CCopasiObjectName Tmp = mCN;
  std::string Separator = "";

  for (; Tmp != ""; Tmp = Tmp.getRemainder())
    {
      CCopasiObjectName Primary = Tmp.getPrimary();
      mCompartmentCN += Separator + Primary;
      Separator = ",";

      if (Primary.getObjectType() == "Vector" ||
          Primary.getObjectName() == "Compartments")
        {
          break;
        }
    }
}


// virtual
void CModelParameterSpecies::setValue(const C_FLOAT64 & value, const Framework & framework)
{
  CModel * pModel = getModel();

  if (framework == Concentration)
    {
      mConcentration = value;

      if (mpCompartment != NULL && pModel != NULL)
        {
          mValue = mConcentration * mpCompartment->getValue() * pModel->getQuantity2NumberFactor();
        }
      else
        {
          mValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
        }
    }
  else
    {
      mValue = value;

      if (mpCompartment != NULL && pModel != NULL)
        {
          mConcentration = mValue / mpCompartment->getValue() * pModel->getNumber2QuantityFactor();
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
  return mCompartmentCN;
}

std::ostream &operator<<(std::ostream &os, const CModelParameter & o)
{
  os << "Model Parameter:" << std::endl;
  os << "  Type:       " << CModelParameter::TypeNames[o.mType] << std::endl;
  os << "  CN:         " << o.mCN << std::endl;
  os << "  Value:      " << o.mValue << std::endl;
  os << "  Expression: " << o.getInitialExpression() << std::endl;
  os << "  Diff:       " << o.mCompareResult << std::endl;

  return os;
}
