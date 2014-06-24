// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <limits>

#include "copasi.h"

#include "CModelParameter.h"
#include "CModelParameterGroup.h"
#include "CModelParameterSet.h"
#include "CMetabNameInterface.h"
#include "CReaction.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "function/CExpression.h"
#include "model/CModel.h"
#include "report/CCopasiRootContainer.h"
#include "report/CKeyFactory.h"
#include "report/CCopasiObject.h"
#include "utilities/CDimension.h"
#include "copasi/utilities/CUnit.h"

// static
const char * CModelParameter::TypeNames[] =
{
  "Model",
  "Compartment",
  "Species",
  "ModelValue",
  "ReactionParameter",
  "Reaction",
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
  mSimulationType(type == CModelParameter::Model ? CModelEntity::TIME : CModelEntity::FIXED),
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
  mSimulationType(src.mSimulationType),
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

const std::string CModelParameter::getUnit(const Framework & framework) const
{
  std::string Unit;

  switch (mType)
    {
      case Model:
        return getModel()->getTimeUnitsDisplayString();
        break;

      case Compartment:
      {
        const CCompartment * pCompartment = static_cast< const CCompartment * >(mpObject);

        if (pCompartment == NULL)
          {
            return "";
          }

        return pCompartment->getChildObjectUnits(pCompartment->getInitialValueReference());
      }
      break;

      case Species:
      {
        const CMetab * pSpecies = static_cast< const CMetab * >(mpObject);

        if (pSpecies == NULL)
          {
            return "";
          }

        if (framework == Concentration)
          {
            return pSpecies->getChildObjectUnits(pSpecies->getInitialConcentrationReference());
          }

        return pSpecies->getChildObjectUnits(pSpecies->getInitialValueReference());
      }
      break;

      case ModelValue:
        break;

      case ReactionParameter:
      {
        const CReaction * pReaction = static_cast< const CModelParameterReactionParameter * >(this)->getReaction();

        if (pReaction == NULL)
          {
            return "";
          }

        const CModel * pModel = getModel();

        CFindDimensions Units(pReaction->getFunction(),
                              pModel->getQuantityUnit()->isDimensionless(),
                              pModel->getVolumeUnit()->isDimensionless(),
                              pModel->getTimeUnit()->isDimensionless(),
                              pModel->getAreaUnit()->isDimensionless(),
                              pModel->getLengthUnit()->isDimensionless());

        Units.setUseHeuristics(true);

        Units.setChemicalEquation(&pReaction->getChemEq());

        Units.findDimensions(pReaction->getCompartmentNumber() > 1);

        return Units.getDimensions()[pReaction->getParameterIndex(getName())].getDisplayString(pModel);
      }
      break;

      default:
        break;
    }

  return "";
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

bool CModelParameter::setSimulationType(const CModelEntity::Status & simulationType)
{
  bool success = true;

  switch (mType)
    {
      case Model:
        success = (simulationType == CModelEntity::TIME);
        break;

      case Species:
        success = (simulationType != CModelEntity::TIME);
        break;

      case ReactionParameter:
        success = (simulationType == CModelEntity::FIXED ||
                   simulationType == CModelEntity::ASSIGNMENT);
        break;

      case ModelValue:
      case Compartment:
        success = (simulationType != CModelEntity::TIME &&
                   simulationType != CModelEntity::REACTIONS);
        break;

      default:
        success = (simulationType == CModelEntity::FIXED);
        break;
    }

  if (success)
    {
      mSimulationType = simulationType;
    }

  return success;
}

const CModelEntity::Status & CModelParameter::getSimulationType() const
{
  return mSimulationType;
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

const CExpression* CModelParameter::getInitialExpressionPtr() const
{
  return mpInitialExpression;
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
  if (mType == Reaction ||
      mType == Group ||
      mType == Set ||
      (mType == Model && getModel()->isAutonomous()) ||
      (mIsInitialExpressionValid && getInitialExpression() != ""))
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
      return mpObject->getObjectName();
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

  mpObject = dynamic_cast< CCopasiObject * >(pModel->getObjectDataModel()->ObjectFromCN(ListOfContainer, mCN));

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
          else if (dynamic_cast< CCopasiParameter * >(mpObject) != NULL)
            mType = ReactionParameter;
        }
    }

  if (mpInitialExpression != NULL)
    {
      mIsInitialExpressionValid = mpInitialExpression->compile();
    }
}

const CModelParameter::CompareResult & CModelParameter::diff(const CModelParameter & other,
    const CModelParameter::Framework & framework,
    const bool & /* createMissing */)
{
  if (mCompareResult == Missing ||
      mCompareResult == Obsolete)
    {
      return mCompareResult;
    }

  switch (mType)
    {
      case Compartment:
      case Species:
      case ModelValue:

        if (other.getObject() != NULL &&
            mpObject != NULL &&
            static_cast< CModelEntity *>(mpObject)->getStatus() == CModelEntity::ASSIGNMENT &&
            (fabs(getValue(ParticleNumbers) - other.getValue(ParticleNumbers)) > 50 * (fabs(getValue(ParticleNumbers)) + fabs(other.getValue(ParticleNumbers))) * std::numeric_limits< C_FLOAT64 >::epsilon() ||
             getInitialExpression() != ""))
          {
            mCompareResult = Conflict;
            return mCompareResult;
          }

        break;

      default:
        break;
    }

  if (getInitialExpression() != other.getInitialExpression() ||
      fabs(getValue(framework) - other.getValue(framework)) > 50 * (fabs(getValue(framework)) + fabs(other.getValue(framework))) * std::numeric_limits< C_FLOAT64 >::epsilon())
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

            if (pEntity->getStatus() != CModelEntity::ASSIGNMENT)
              {
                pEntity->setInitialValue(mValue);

                if (mIsInitialExpressionValid)
                  {
                    pEntity->setInitialExpression(getInitialExpression());
                  }
              }
          }
          break;

          case ReactionParameter:
          {
            CCopasiParameter * pParameter = static_cast< CCopasiParameter * >(mpObject);
            CReaction * pReaction = static_cast< CReaction * >(mpObject->getObjectAncestor("Reaction"));

            if (mIsInitialExpressionValid &&
                getInitialExpression() != "")
              {
                CModel * pModel = mpParent->getModel();

                assert(pModel != NULL);

                std::vector< CCopasiContainer * > ListOfContainer;
                ListOfContainer.push_back(pModel);

                CCopasiObjectName CN = static_cast< CEvaluationNodeObject * >(mpInitialExpression->getRoot())->getObjectCN();
                CCopasiObject * pObject = dynamic_cast< CCopasiObject * >(pModel->getObjectDataModel()->ObjectFromCN(ListOfContainer, CN));

                assert(pObject != NULL);

                // We assign the object value
                pParameter->setValue(* (C_FLOAT64 *) pObject->getValuePointer());

                // We map the parameter to the global quantity
                pReaction->setParameterMapping(pParameter->getObjectName(), pObject->getObjectParent()->getKey());
              }
            else
              {
                pParameter->setValue(mValue);

                // We need to remove the existing mapping to a global quantity1.
                pReaction->setParameterMapping(pParameter->getObjectName(), pParameter->getKey());
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

// virtual
bool CModelParameter::refreshFromModel(const bool & modifyExistence)
{
  bool success = true;

  if (modifyExistence)
    {
      if (mCompareResult == CModelParameter::Obsolete)
        {
          delete this;

          return true;
        }

      if (mCompareResult == CModelParameter::Missing)
        {
          mCompareResult = CModelParameter::Identical;
        }

      if (mType != ReactionParameter &&
          mpObject != NULL)
        {
          mSimulationType = static_cast< CModelEntity * >(mpObject)->getStatus();
        }
    }

  if (mpObject != NULL)
    {
      switch (mType)
        {
          case Model:
          {
            CModel * pModel = static_cast< CModel * >(mpObject);

            if (!pModel->isAutonomous())
              {
                mValue = pModel->getInitialValue();
              }
            else
              {
                mValue = 0.0;
              }
          }
          break;

          case Compartment:
          case Species:
          case ModelValue:
          {
            CModelEntity * pEntity = static_cast< CModelEntity * >(mpObject);

            mValue = pEntity->getInitialValue();
          }
          break;

          case ReactionParameter:
          {
            CCopasiParameter * pParameter = static_cast< CCopasiParameter * >(mpObject);
            mValue = * pParameter->getValue().pDOUBLE;

            // We need to update the mapping
            // Check whether this refers to a global quantity.
            const CReaction * pReaction = static_cast< CModelParameterReactionParameter * >(this)->getReaction();

            if (pReaction != NULL)
              {
                if (pReaction->isLocalParameter(getName()))
                  {
                    mSimulationType = CModelEntity::FIXED;
                    static_cast< CModelParameterReactionParameter * >(this)->setGlobalQuantityCN("");
                  }
                else
                  {
                    mSimulationType = CModelEntity::ASSIGNMENT;
                    const std::vector<std::string> ModelValue = pReaction->getParameterMapping(getName());

                    assert(ModelValue.size() == 1);

                    CModelValue * pModelValue = static_cast< CModelValue * >(CCopasiRootContainer::getKeyFactory()->get(ModelValue[0]));
                    static_cast< CModelParameterReactionParameter * >(this)->setGlobalQuantityCN(pModelValue->getInitialValueReference()->getCN());
                  }
              }

            CCopasiObjectName GlobalQuantityCN = static_cast< CModelParameterReactionParameter * >(this)->getGlobalQuantityCN();

            if (GlobalQuantityCN != "")
              {
                CModelParameter * pGlobalQuantity = getSet()->getModelParameter(GlobalQuantityCN);

                if (pGlobalQuantity != NULL)
                  {
                    mValue = pGlobalQuantity->getValue(ParticleNumbers);
                  }
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

// virtual
size_t CModelParameter::getNumChildren() const
{
  return 0;
}

// virtual
const CModelParameter * CModelParameter::getChild(const size_t & /* index */) const
{
  return NULL;
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
  // If a compartment is deleted all contained species are not deleted however
  // their compartment is set to NULL.
  std::set< CModelParameterSpecies * >::iterator it = mSpecies.begin();
  std::set< CModelParameterSpecies * >::iterator end = mSpecies.end();

  for (; it != end; ++it)
    {
      (*it)->mpCompartment = NULL;
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
  mpCompartment(NULL),
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

  return nameFromCN(mCN) + '{' + nameFromCN(mCompartmentCN) + '}';
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
  setValue(mValue, ParticleNumbers);
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

      if (Primary.getObjectType() == "Vector" &&
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
          mValue = mConcentration * mpCompartment->getValue(ParticleNumbers) * pModel->getQuantity2NumberFactor();
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
          mConcentration = mValue / mpCompartment->getValue(ParticleNumbers) * pModel->getNumber2QuantityFactor();
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

CModelParameterReactionParameter::CModelParameterReactionParameter(CModelParameterGroup * pParent, const CModelParameter::Type & type):
  CModelParameter(pParent, type),
  mpReaction(NULL),
  mGlobalQuantityCN(),
  mpGlobalQuantity(NULL)
{}

CModelParameterReactionParameter::CModelParameterReactionParameter(const CModelParameterReactionParameter & src, CModelParameterGroup * pParent):
  CModelParameter(src, pParent),
  mpReaction(NULL),
  mGlobalQuantityCN(src.mGlobalQuantityCN),
  mpGlobalQuantity(NULL)
{}

// virtual
CModelParameterReactionParameter::~CModelParameterReactionParameter()
{}

// virtual
void CModelParameterReactionParameter::compile()
{
  CModelParameter::compile();

  mGlobalQuantityCN = std::string();

  std::string Infix = getInitialExpression();

  if (Infix.length() > 2)
    {
      // Infix: <CN,Reference=InitialValue> or <CN,Reference=Value>
      CCopasiObjectName Tmp = Infix.substr(1, Infix.length() - 2);
      std::string Separator = "";

      for (; Tmp != ""; Tmp = Tmp.getRemainder())
        {
          CCopasiObjectName Primary = Tmp.getPrimary();

          if (Primary.getObjectType() == "Reference")
            {
              break;
            }

          mGlobalQuantityCN += Separator + Primary;
          Separator = ",";
        }

      setSimulationType(CModelEntity::ASSIGNMENT);
    }
  else
    {
      setSimulationType(CModelEntity::FIXED);
    }

  mpGlobalQuantity = this->getSet()->getModelParameter(mGlobalQuantityCN);

  if (mpGlobalQuantity != NULL)
    {
      mValue = mpGlobalQuantity->getValue(ParticleNumbers);
    }

  std::vector< CCopasiContainer * > ListOfContainer;

  CModel * pModel = getModel();
  ListOfContainer.push_back(pModel);

  mpReaction = static_cast< CReaction * >(pModel->getObjectDataModel()->ObjectFromCN(ListOfContainer, mpParent->getCN()));
}

const CReaction * CModelParameterReactionParameter::getReaction() const
{
  return mpReaction;
}

void CModelParameterReactionParameter::setGlobalQuantityCN(const std::string & globalQuantityCN)
{
  if (globalQuantityCN == "")
    {
      setInitialExpression("");
    }
  else
    {
      setInitialExpression("<" + globalQuantityCN + ">");
    }

  compile();
}

const CRegisteredObjectName & CModelParameterReactionParameter::getGlobalQuantityCN() const
{
  return mGlobalQuantityCN;
}
