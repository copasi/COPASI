// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <limits>

#include "copasi/copasi.h"

#include "CModelParameter.h"
#include "CModelParameterGroup.h"
#include "CModelParameterSet.h"
#include "CMetabNameInterface.h"
#include "CReaction.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/function/CExpression.h"
#include "copasi/model/CModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CDataObject.h"
#include "copasi/utilities/CUnitValidator.h"
#include "copasi/utilities/CUnit.h"
#include "copasi/math/CMathExpression.h"
#include "copasi/core/CDataString.h"

// static
const CEnumAnnotation< std::string, CModelParameter::Type > CModelParameter::TypeNames(
{
  "Model",
  "Compartment",
  "Species",
  "ModelValue",
  "ReactionParameter",
  "Reaction",
  "Group",
  "Set",
  "unknown"
});

// static
const CEnumAnnotation< std::string, CModelParameter::CompareResult > CModelParameter::CompareResultNames(
{
  "Obsolete",
  "Missing",
  "Modified",
  "Conflict",
  "Identical"
});

// static
CModelParameter * CModelParameter::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  CModelParameter * pModelParameter = NULL;

  Type type = TypeNames.toEnum(data.getProperty(CData::OBJECT_TYPE).toString(), Type::unknown);

  switch (type)
    {
      case Type::Compartment:
        pModelParameter = new CModelParameterCompartment(NULL);
        break;

      case Type::Species:
        pModelParameter = new CModelParameterSpecies(NULL);
        break;

      case Type::ReactionParameter:
        pModelParameter = new CModelParameterReactionParameter(NULL, type);
        break;

      case Type::Model:
      case Type::ModelValue:
        pModelParameter = new CModelParameter(NULL, type);
        break;

      case Type::Reaction:
      case Type::Group:
        pModelParameter = new CModelParameterGroup(NULL, type);
        break;

      case Type::Set:
      default:
        break;
    }

  return pModelParameter;
}

// virtual
void CModelParameter::destruct()
{
  delete this;
}

// virtual
CData CModelParameter::toData() const
{
  CData Data;

  if (mType != Type::Set)
    {
      Data.addProperty(CData::OBJECT_NAME, mCN);
      Data.addProperty(CData::OBJECT_UUID, getUuid().str());
      Data.addProperty(CData::OBJECT_PARENT_CN, getSet() != NULL ? getSet()->getCN() : CCommonName());
      Data.addProperty(CData::OBJECT_TYPE, TypeNames[mType]);
      Data.addProperty(CData::OBJECT_INDEX, getIndex());
    }

  switch (mType)
    {
      case Type::Model:
      case Type::Compartment:
      case Type::Species:
      case Type::ModelValue:
      case Type::ReactionParameter:
      {
        CData ParameterValue;
        ParameterValue.addProperty(CData::INITIAL_VALUE, mValue);

        Data.addProperty(CData::PARAMETER_VALUE, ParameterValue);
        Data.addProperty(CData::SIMULATION_TYPE, CModelEntity::StatusName[mSimulationType]);
        Data.addProperty(CData::INITIAL_EXPRESSION, getInitialExpression());
      }
      break;

      default:
        break;
    }

  return Data;
}

// virtual
bool CModelParameter::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  if (mType == Type::Set)
    {
      return true;
    }

  if (data.isSetProperty(CData::OBJECT_NAME))
    {
      setCN(data.getProperty(CData::OBJECT_NAME).toString());
    }

  if (mpParent != NULL && data.isSetProperty(CData::OBJECT_INDEX))
    {
      mpParent->updateIndex(data.getProperty(CData::OBJECT_INDEX).toSizeT(), this);
    }

  if (data.isSetProperty(CData::SIMULATION_TYPE))
    {
      mSimulationType = CModelEntity::StatusName.toEnum(data.getProperty(CData::SIMULATION_TYPE).toString(), CModelEntity::Status::FIXED);
    }

  if (data.isSetProperty(CData::PARAMETER_VALUE) && data.getProperty(CData::PARAMETER_VALUE).getType() == CDataValue::DATA)
    {
      const CData & Data = data.getProperty(CData::PARAMETER_VALUE).toData();
      setValue(Data.getProperty(CData::INITIAL_VALUE).toDouble(),
               CCore::FrameworkNames.toEnum(Data.getProperty(CData::FRAMEWORK).toString(), CCore::Framework::ParticleNumbers));
    }

  if (data.isSetProperty(CData::INITIAL_EXPRESSION))
    {
      setInitialExpression(data.getProperty(CData::INITIAL_EXPRESSION).toString());
    }

  return true;
}

// virtual
void CModelParameter::createUndoData(CUndoData & undoData,
                                     const CUndoData::Type & type,
                                     const CData & oldData,
                                     const CCore::Framework & framework) const
{
  if (type != CUndoData::Type::CHANGE)
    {
      undoData = CUndoData(type, this);
      return;
    }

  if (mType != Type::Set)
    {
      undoData.addProperty(CData::OBJECT_NAME, oldData.getProperty(CData::OBJECT_NAME), mCN);
      // The UUID of an object must never be changed.
      // undoData.addProperty(CData::OBJECT_UUID, oldData.getProperty(CData::OBJECT_UUID), getUuid().str());
      undoData.addProperty(CData::OBJECT_PARENT_CN, oldData.getProperty(CData::OBJECT_PARENT_CN), getSet() != NULL ? getSet()->getCN() : CCommonName());
      undoData.addProperty(CData::OBJECT_TYPE, oldData.getProperty(CData::OBJECT_TYPE), TypeNames[mType]);
      undoData.addProperty(CData::OBJECT_INDEX, oldData.getProperty(CData::OBJECT_INDEX), getIndex());
    }

  switch (mType)
    {
      case Type::Model:
      case Type::Compartment:
      case Type::Species:
      case Type::ModelValue:
      case Type::ReactionParameter:
      {
        CData OldParameterValue;
        OldParameterValue.addProperty(CData::INITIAL_VALUE, oldData.getProperty(CData::PARAMETER_VALUE).toData().getProperty(CData::INITIAL_VALUE));
        OldParameterValue.addProperty(CData::FRAMEWORK, CCore::FrameworkNames[framework]);

        CData NewParameterValue;
        NewParameterValue.addProperty(CData::INITIAL_VALUE, mValue);
        NewParameterValue.addProperty(CData::FRAMEWORK, CCore::FrameworkNames[framework]);

        undoData.addProperty(CData::PARAMETER_VALUE, OldParameterValue, NewParameterValue);
        undoData.addProperty(CData::SIMULATION_TYPE, oldData.getProperty(CData::SIMULATION_TYPE), CModelEntity::StatusName[mSimulationType]);
        undoData.addProperty(CData::INITIAL_EXPRESSION, oldData.getProperty(CData::INITIAL_EXPRESSION), getInitialExpression());
      }
      break;

      default:
        break;
    }

  return;
}

CModelParameter::CModelParameter(CModelParameterGroup * pParent, const CModelParameter::Type & type)
  : CUndoObjectInterface()
  , mpParent(static_cast< CModelParameterGroup * >(pParent))
  , mType(type)
  , mCN()
  , mSimulationType(type == CModelParameter::Type::Model ? CModelEntity::Status::TIME : CModelEntity::Status::FIXED)
  , mValue(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
  , mpInitialExpression(NULL)
  , mCompareResult(CModelParameter::CompareResult::Identical)
  , mpObject(NULL)
  , mIsInitialExpressionValid(true)
{}

CModelParameter::CModelParameter(const CModelParameter & src, CModelParameterGroup * pParent)
  : CUndoObjectInterface(src)
  , mpParent(pParent)
  , mType(src.mType)
  , mCN(src.mCN)
  , mSimulationType(src.mSimulationType)
  , mValue(src.mValue)
  , mpInitialExpression(NULL)
  , mCompareResult(src.mCompareResult)
  , mpObject(src.mpObject)
  , mIsInitialExpressionValid(src.mIsInitialExpressionValid)
{
  assert(mType == Type::Set || mpParent != NULL);

  setInitialExpression(src.getInitialExpression());
}

// virtual
CModelParameter::~CModelParameter()
{
  if (mpParent != NULL)
    {
      mpParent->remove(this);
    }

  pdelete(mpInitialExpression);
}

// virtual
CModelParameterSet * CModelParameter::toSet()
{
  return NULL;
}

// virtual
const CModelParameterSet * CModelParameter::toSet() const
{
  return NULL;
}

bool CModelParameter::operator<(const CModelParameter & rhs) const
{
  return mCN < rhs.mCN;
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

CValidatedUnit CModelParameter::getUnit(const CCore::Framework & framework) const
{
  std::string Unit;

  switch (mType)
    {
      case Type::Model:
        return CValidatedUnit(getModel()->getTimeUnit(), false);
        break;

      case Type::Compartment:
      {
        const CCompartment * pCompartment = static_cast< const CCompartment * >(mpObject);

        if (pCompartment == NULL)
          {
            return CValidatedUnit(CUnit(""), false);
          }

        return CValidatedUnit(pCompartment->getChildObjectUnits(pCompartment->getInitialValueReference()), false);
      }
      break;

      case Type::Species:
      {
        const CMetab * pSpecies = static_cast< const CMetab * >(mpObject);

        if (pSpecies == NULL)
          {
            return CValidatedUnit(CUnit(""), false);
          }

        if (framework == CCore::Framework::Concentration)
          {
            return CValidatedUnit(pSpecies->getChildObjectUnits(pSpecies->getInitialConcentrationReference()), false);
          }

        return CValidatedUnit(pSpecies->getChildObjectUnits(pSpecies->getInitialValueReference()), false);
      }
      break;

      case Type::ModelValue:
      {
        const CModelValue * pModelValue = static_cast< const CModelValue * >(mpObject);

        if (pModelValue == NULL)
          {
            return CValidatedUnit(CUnit(""), false);
          }

        return CValidatedUnit(pModelValue->getUnitExpression(), false);
      }
      break;

      case Type::ReactionParameter:
        return mpParent->getObjectUnit(this);
        break;

      case Type::Reaction:
      {
        const CReaction * pReaction = static_cast< const CReaction * >(mpObject);

        if (pReaction == NULL)
          {
            return CValidatedUnit(CUnit(""), false);
          }

        return CValidatedUnit(pReaction->getKineticLawUnit(), false);
      }

      break;

      default:
        break;
    }

  return CValidatedUnit(CUnit(""), false);
}

// virtual
void CModelParameter::setCN(const CCommonName & cn)
{
  mCN = cn;
}

const CCommonName & CModelParameter::getCN() const
{
  return mCN;
}

bool CModelParameter::setSimulationType(const CModelEntity::Status & simulationType)
{
  bool success = true;

  switch (mType)
    {
      case Type::Model:
        success = (simulationType == CModelEntity::Status::TIME);
        break;

      case Type::Species:
        success = (simulationType != CModelEntity::Status::TIME);
        break;

      case Type::ReactionParameter:
        success = (simulationType == CModelEntity::Status::FIXED || simulationType == CModelEntity::Status::ASSIGNMENT);
        break;

      case Type::ModelValue:
      case Type::Compartment:
        success = (simulationType != CModelEntity::Status::TIME && simulationType != CModelEntity::Status::REACTIONS);
        break;

      default:
        success = (simulationType == CModelEntity::Status::FIXED);
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
void CModelParameter::setValue(const C_FLOAT64 & value, const CCore::Framework & /* framework */, bool updateModelIfActive)
{
  mValue = value;

  if (!updateModelIfActive)
    return;

  CModelParameterSet * pSet = getSet();

  if (pSet->isActive())
    {
      updateModel();
    }
}

// virtual
const C_FLOAT64 & CModelParameter::getValue(const CCore::Framework & /* framework */) const
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

const CExpression * CModelParameter::getInitialExpressionPtr() const
{
  return mpInitialExpression;
}

std::string CModelParameter::getInitialExpression() const
{
  if (mpInitialExpression == NULL)
    {
      return "";
    }

  mpInitialExpression->updateInfix();
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
      if (*it == this)
        return Index;
    }

  return C_INVALID_INDEX;
}

bool CModelParameter::isReadOnly() const
{
  if (mType == Type::Reaction || mType == Type::Group || mType == Type::Set || (mIsInitialExpressionValid && getInitialExpression() != ""))
    {
      return true;
    }

  return false;
}

CDataObject * CModelParameter::getObject() const
{
  return mpObject;
}

CModelParameterSet * CModelParameter::getSet() const
{
  if (mType == Type::Set)
    {
      return const_cast< CModelParameter * >(this)->toSet();
    }

  CModelParameterGroup * pParent = mpParent;

  while (pParent != NULL)
    {
      if (pParent->getType() == Type::Set)
        {
          return pParent->toSet();
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

  return CCommonName::nameFromCN(mCN);
}

void CModelParameter::compile()
{
  mpObject = NULL;
  mIsInitialExpressionValid = true;

  CObjectInterface::ContainerList ContainerList;
  ContainerList.push_back(getModel());

  mpObject = const_cast< CDataObject * >(CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(ContainerList, mCN)));

  if (mpObject != NULL)
    {
      if (mType == Type::unknown)
        {
          if (dynamic_cast< CModel * >(mpObject) != NULL)
            mType = Type::Model;
          else if (dynamic_cast< CCompartment * >(mpObject) != NULL)
            mType = Type::Compartment;
          else if (dynamic_cast< CMetab * >(mpObject) != NULL)
            mType = Type::Species;
          else if (dynamic_cast< CModelValue * >(mpObject) != NULL)
            mType = Type::ModelValue;
          else if (dynamic_cast< CCopasiParameter * >(mpObject) != NULL)
            mType = Type::ReactionParameter;
        }
    }

  if (mpInitialExpression != NULL)
    {
      size_t Size = CCopasiMessage::size();
      mIsInitialExpressionValid = mpInitialExpression->compile(ContainerList);

      while (CCopasiMessage::size() > Size)
        CCopasiMessage::getLastMessage();
    }
}

const CModelParameter::CompareResult & CModelParameter::diff(const CModelParameter & other,
    const CCore::Framework & framework,
    const bool & /* createMissing */)
{
  if (mCompareResult == CompareResult::Missing || mCompareResult == CompareResult::Obsolete)
    {
      return mCompareResult;
    }

  switch (mType)
    {
      case Type::Compartment:
      case Type::Species:
      case Type::ModelValue:

        if (other.getObject() != NULL && mpObject != NULL && static_cast< CModelEntity * >(mpObject)->getStatus() == CModelEntity::Status::ASSIGNMENT && (fabs(getValue(CCore::Framework::ParticleNumbers) - other.getValue(CCore::Framework::ParticleNumbers)) > 50 * (fabs(getValue(CCore::Framework::ParticleNumbers)) + fabs(other.getValue(CCore::Framework::ParticleNumbers))) * std::numeric_limits< C_FLOAT64 >::epsilon() || getInitialExpression() != ""))
          {
            mCompareResult = CompareResult::Conflict;
            return mCompareResult;
          }

        break;

      default:
        break;
    }

  if (getInitialExpression() != other.getInitialExpression() || fabs(getValue(framework) - other.getValue(framework)) > 50 * (fabs(getValue(framework)) + fabs(other.getValue(framework))) * std::numeric_limits< C_FLOAT64 >::epsilon())
    {
      mCompareResult = CompareResult::Modified;
    }
  else
    {
      mCompareResult = CompareResult::Identical;
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
          case Type::Model:
          case Type::Compartment:
          case Type::Species:
          case Type::ModelValue:
          {
            CModelEntity * pEntity = static_cast< CModelEntity * >(mpObject);

            if (pEntity->getStatus() != CModelEntity::Status::ASSIGNMENT && !std::isnan(mValue))
              {
                pEntity->setInitialValue(mValue);

                if (mIsInitialExpressionValid)
                  {
                    pEntity->setInitialExpression(getInitialExpression());
                  }
              }
          }
          break;

          case Type::ReactionParameter:
          {
            CCopasiParameter * pParameter = static_cast< CCopasiParameter * >(mpObject);
            CReaction * pReaction = static_cast< CReaction * >(mpObject->getObjectAncestor("Reaction"));
            CDataObject * pObject = NULL;

            if (mIsInitialExpressionValid
                && getInitialExpression() != "")
              {
                CModel * pModel = mpParent->getModel();
                CCommonName CN = static_cast< CEvaluationNodeObject * >(mpInitialExpression->getRoot())->getObjectCN();

                if (pModel != NULL)
                  {
                    pObject = const_cast< CDataObject * >(CObjectInterface::DataObject(pModel->getObjectFromCN(CN)));
                  }

                if (pObject != NULL)
                  {
                    // We assign the object value
                    pParameter->setValue(*(C_FLOAT64 *) pObject->getValuePointer());

                    // We map the parameter to the global quantity
                    std::vector< const CDataObject * > Objects(1, pObject->getObjectParent());
                    pReaction->setParameterObjects(pParameter->getObjectName(), Objects);
                  }
              }

            if (pObject == NULL
                && !std::isnan(mValue))
              {
                pParameter->setValue(mValue);

                // We need to remove the existing mapping to a global quantity1.
                std::vector< const CDataObject * > Objects(1, pParameter);
                pReaction->setParameterObjects(pParameter->getObjectName(), Objects);
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
      if (mCompareResult == CModelParameter::CompareResult::Obsolete)
        {
          delete this;

          return true;
        }

      if (mCompareResult == CModelParameter::CompareResult::Missing)
        {
          mCompareResult = CModelParameter::CompareResult::Identical;
        }

      if (mType != Type::ReactionParameter && mpObject != NULL)
        {
          mSimulationType = static_cast< CModelEntity * >(mpObject)->getStatus();
        }
    }

  if (mpObject != NULL)
    {
      C_FLOAT64 Value;

      switch (mType)
        {
          case Type::Model:
          case Type::Compartment:
          case Type::Species:
          case Type::ModelValue:
          {
            CModelEntity * pEntity = static_cast< CModelEntity * >(mpObject);

            Value = pEntity->getInitialValue();
          }
          break;

          case Type::ReactionParameter:
          {
            CCopasiParameter * pParameter = static_cast< CCopasiParameter * >(mpObject);
            Value = pParameter->getValue< C_FLOAT64 >();

            // We need to update the mapping
            // Check whether this refers to a global quantity.
            const CReaction * pReaction = static_cast< CModelParameterReactionParameter * >(this)->getReaction();

            if (pReaction != NULL)
              {
                if (pReaction->isLocalParameter(getName()))
                  {
                    mSimulationType = CModelEntity::Status::FIXED;
                    static_cast< CModelParameterReactionParameter * >(this)->setGlobalQuantityCN("");
                  }
                else
                  {
                    mSimulationType = CModelEntity::Status::ASSIGNMENT;
                    const std::vector< const CDataObject * > ModelValue = pReaction->getParameterObjects(getName());

                    assert(ModelValue.size() == 1);

                    const CModelValue * pModelValue = dynamic_cast< const CModelValue * >(ModelValue[0]);
                    static_cast< CModelParameterReactionParameter * >(this)->setGlobalQuantityCN(pModelValue != NULL ? pModelValue->getInitialValueReference()->getCN() : CDataString("not found").getCN());
                  }
              }

            CCommonName GlobalQuantityCN = static_cast< CModelParameterReactionParameter * >(this)->getGlobalQuantityCN();

            if (GlobalQuantityCN != "")
              {
                const CModelParameter * pGlobalQuantity = getSet()->getModelParameter(GlobalQuantityCN);

                if (pGlobalQuantity != NULL)
                  {
                    Value = pGlobalQuantity->getValue(CCore::Framework::ParticleNumbers);
                  }
              }
          }
          break;

          default:
            success = false;
            break;
        }

      setValue(Value, CCore::Framework::ParticleNumbers, false);
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

CModelParameterCompartment::CModelParameterCompartment(CModelParameterGroup * pParent, const CModelParameter::Type & type)
  : CModelParameter(pParent, type)
  , mSpecies()
{}

CModelParameterCompartment::CModelParameterCompartment(const CModelParameterCompartment & src, CModelParameterGroup * pParent)
  : CModelParameter(src, pParent)
  , mSpecies()
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
void CModelParameterCompartment::setValue(const C_FLOAT64 & value, const CCore::Framework & framework, bool updateModelIfActive)
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
      (*it)->setValue(*pSpeciesValue, framework, updateModelIfActive);
    }

  if (!updateModelIfActive)
    return;

  CModelParameterSet * pSet = getSet();

  if (pSet->isActive())
    {
      updateModel();
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

// virtual
CData CModelParameterSpecies::toData() const
{
  CData Data(CModelParameter::toData());

  CData ParameterValue = Data.getProperty(CData::PARAMETER_VALUE).toData();
  ParameterValue.addProperty(CData::INITIAL_INTENSIVE_VALUE, mConcentration);
  Data.addProperty(CData::PARAMETER_VALUE, ParameterValue);

  return Data;
}

// virtual
void CModelParameterSpecies::createUndoData(CUndoData & undoData,
    const CUndoData::Type & type,
    const CData & oldData,
    const CCore::Framework & framework) const
{
  CModelParameter::createUndoData(undoData, type, oldData, framework);

  if (type != CUndoData::Type::CHANGE)
    {
      return;
    }

  CData OldParameterValue;
  CData NewParameterValue;

  if (framework == CCore::Framework::Concentration)
    {
      OldParameterValue.addProperty(CData::INITIAL_VALUE, oldData.getProperty(CData::PARAMETER_VALUE).toData().getProperty(CData::INITIAL_INTENSIVE_VALUE));
      NewParameterValue.addProperty(CData::INITIAL_VALUE, mConcentration);
    }
  else
    {
      OldParameterValue.addProperty(CData::INITIAL_VALUE, oldData.getProperty(CData::PARAMETER_VALUE).toData().getProperty(CData::INITIAL_VALUE));
      NewParameterValue.addProperty(CData::INITIAL_VALUE, mValue);
    }

  OldParameterValue.addProperty(CData::FRAMEWORK, CCore::FrameworkNames[framework]);
  NewParameterValue.addProperty(CData::FRAMEWORK, CCore::FrameworkNames[framework]);

  undoData.addProperty(CData::PARAMETER_VALUE, OldParameterValue, NewParameterValue);

  return;
}

CModelParameterSpecies::CModelParameterSpecies(CModelParameterGroup * pParent, const CModelParameter::Type & type)
  : CModelParameter(pParent, type)
  , mCompartmentCN()
  , mpCompartment(NULL)
  , mConcentration(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
{}

CModelParameterSpecies::CModelParameterSpecies(const CModelParameterSpecies & src, CModelParameterGroup * pParent)
  : CModelParameter(src, pParent)
  , mCompartmentCN(src.mCompartmentCN)
  , mpCompartment(NULL)
  , mConcentration(src.mConcentration)
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

  return CCommonName::nameFromCN(mCN) + '{' + CCommonName::nameFromCN(mCompartmentCN) + '}';
}

// virtual
void CModelParameterSpecies::compile()
{
  CModelParameter::compile();

  mpCompartment = static_cast< CModelParameterCompartment * >(getSet()->toGroup()->getModelParameter(mCompartmentCN));

  if (mpCompartment != NULL)
    {
      mpCompartment->addSpecies(this);
    }

  // Update the concentration if possible
  setValue(mValue, CCore::Framework::ParticleNumbers);
}

// virtual
void CModelParameterSpecies::setCN(const CCommonName & cn)
{
  CModelParameter::setCN(cn);

  // Determine the CN for the compartment.
  // "CN=Root,Model=New Model,Vector=Compartments[compartment],Vector=Metabolites[A]"
  mCompartmentCN = mCN.substr(0, mCN.find(",Vector=Metabolites"));
}

// virtual
void CModelParameterSpecies::setValue(const C_FLOAT64 & value, const CCore::Framework & framework, bool updateModelIfActive)
{
  CModel * pModel = getModel();

  if (mpCompartment == NULL)
    {
      mpCompartment = static_cast< CModelParameterCompartment * >(getSet()->toGroup()->getModelParameter(mCompartmentCN));

      if (mpCompartment != NULL)
        {
          mpCompartment->addSpecies(this);
        }
    }

  if (framework == CCore::Framework::Concentration)
    {
      mConcentration = value;

      if (mpCompartment != NULL && pModel != NULL)
        {
          mValue = mConcentration * mpCompartment->getValue(CCore::Framework::ParticleNumbers) * pModel->getQuantity2NumberFactor();
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
          mConcentration = mValue / mpCompartment->getValue(CCore::Framework::ParticleNumbers) * pModel->getNumber2QuantityFactor();
        }
      else
        {
          mConcentration = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
        }
    }

  if (!updateModelIfActive)
    return;

  CModelParameterSet * pSet = getSet();

  if (pSet->isActive())
    {
      updateModel();
    }
}

// virtual
const C_FLOAT64 & CModelParameterSpecies::getValue(const CCore::Framework & framework) const
{
  if (framework == CCore::Framework::Concentration)
    {
      return mConcentration;
    }

  return mValue;
}

bool CModelParameterSpecies::updateModel()
{
  CMetab * pMetab = static_cast< CMetab * >(mpObject);

  if (pMetab && pMetab->getStatus() != CModelEntity::Status::ASSIGNMENT && !std::isnan(mConcentration))
    {
      pMetab->setInitialConcentration(mConcentration);
    }

  return CModelParameter::updateModel();
}

CCommonName CModelParameterSpecies::getCompartmentCN() const
{
  return mCompartmentCN;
}

std::ostream & operator<<(std::ostream & os, const CModelParameter & o)
{
  os << "Model Parameter:" << std::endl;
  os << "  Type:       " << CModelParameter::TypeNames[o.mType] << std::endl;
  os << "  CN:         " << o.mCN << std::endl;
  os << "  Value:      " << o.mValue << std::endl;
  os << "  Expression: " << o.getInitialExpression() << std::endl;
  os << "  Diff:       " << CModelParameter::CompareResultNames[o.mCompareResult] << std::endl;

  return os;
}

CModelParameterReactionParameter::CModelParameterReactionParameter(CModelParameterGroup * pParent, const CModelParameter::Type & type)
  : CModelParameter(pParent, type)
  , mpReaction(NULL)
  , mGlobalQuantityCN()
  , mpGlobalQuantity(NULL)
{}

CModelParameterReactionParameter::CModelParameterReactionParameter(const CModelParameterReactionParameter & src, CModelParameterGroup * pParent)
  : CModelParameter(src, pParent)
  , mpReaction(NULL)
  , mGlobalQuantityCN(src.mGlobalQuantityCN)
  , mpGlobalQuantity(NULL)
{}

// virtual
CModelParameterReactionParameter::~CModelParameterReactionParameter()
{}

// virtual
void CModelParameterReactionParameter::compile()
{
  CModelParameter::compile();

  mGlobalQuantityCN.clear();

  std::string Infix = getInitialExpression();

  if (Infix.length() > 2)
    {
      // Infix: <CN,Reference=InitialValue> or <CN,Reference=Value>
      CCommonName Tmp = Infix.substr(1, Infix.length() - 2);
      std::string ObjectType;
      std::string ObjectName;

      Tmp.split(mGlobalQuantityCN, ObjectType, ObjectName);
      setSimulationType(CModelEntity::Status::ASSIGNMENT);
    }
  else
    {
      setSimulationType(CModelEntity::Status::FIXED);
    }

  mpGlobalQuantity = getSet()->toGroup()->getModelParameter(mGlobalQuantityCN);

  if (mpGlobalQuantity != NULL)
    {
      mValue = mpGlobalQuantity->getValue(CCore::Framework::ParticleNumbers);
    }

  CObjectInterface::ContainerList ListOfContainer;

  CModel * pModel = getModel();
  ListOfContainer.push_back(pModel);

  mpReaction = static_cast< CReaction * >(const_cast< CDataObject * >(CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(ListOfContainer, mpParent->getCN()))));
}

const CReaction * CModelParameterReactionParameter::getReaction() const
{
  return mpReaction;
}

// static
CCommonName CModelParameterReactionParameter::getReactionCN(const CCommonName & reactionParameterCN)
{
  return reactionParameterCN.substr(0, reactionParameterCN.find(",ParameterGroup=Parameters"));
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

  mpParent->compile();
  compile();
}

const CRegisteredCommonName & CModelParameterReactionParameter::getGlobalQuantityCN() const
{
  return mGlobalQuantityCN;
}
