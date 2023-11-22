// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

#include <cmath>

#include "copasi/copasi.h"

#include "CMathObject.h"
#include "CMathExpression.h"
#include "CMathContainer.h"

#include "copasi/model/CMetab.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CModel.h"
#include "copasi/function/CExpression.h"
#include "copasi/utilities/CBalanceTree.h"
#include "copasi/utilities/utility.h"

// Uncomment next line track any NaN value in calculations
// #define TRACK_NAN

// static
C_FLOAT64 CMathObject::InvalidValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

// static
void CMathObject::initialize(CMathObject * pObject,
                             C_FLOAT64 * pValue,
                             const CMath::ValueType & valueType,
                             const CMath::EntityType & entityType,
                             const CMath::SimulationType & simulationType,
                             const bool & isIntensiveProperty,
                             const bool & isInitialValue,
                             const CDataObject * pDataObject)
{
  pObject->mpValue = pValue;
  pObject->mValueType = valueType;
  pObject->mEntityType = entityType;
  pObject->mSimulationType = simulationType;
  pObject->mIsIntensiveProperty = isIntensiveProperty;
  pObject->mIsInitialValue = isInitialValue;
  pObject->mpDataObject = pDataObject;

  pdelete(pObject->mpExpression);
  pObject->mpCorrespondingProperty = NULL;
  pObject->mpCorrespondingPropertyValue = NULL;
  pObject->mpCompartmentValue = NULL;
  pObject->mpQuantity2NumberValue = NULL;
  pObject->mStoichiometryVector.resize(0);
  pObject->mRateVector.resize(0);
  pObject->mpCalculate = NULL;
}

CMathObject::CMathObject():
  CObjectInterface(),
  mpExpression(NULL),
  mpValue(&InvalidValue),
  mPrerequisites(),
  mValueType(CMath::ValueType::Undefined),
  mEntityType(CMath::EntityType::Undefined),
  mSimulationType(CMath::SimulationType::Undefined),
  mIsIntensiveProperty(false),
  mIsInitialValue(false),
  mpCorrespondingProperty(NULL),
  mpCorrespondingPropertyValue(NULL),
  mpCompartmentValue(NULL),
  mpQuantity2NumberValue(NULL),
  mStoichiometryVector(),
  mRateVector(),
  mpCalculate(NULL),
  mpDataObject(NULL)
{}

CMathObject::CMathObject(const CMathObject & src):
  CObjectInterface(src),
  mpExpression(src.mpExpression),
  mpValue(src.mpValue),
  mPrerequisites(src.mPrerequisites),
  mValueType(src.mValueType),
  mEntityType(src.mEntityType),
  mSimulationType(src.mSimulationType),
  mIsIntensiveProperty(src.mIsIntensiveProperty),
  mIsInitialValue(src.mIsInitialValue),
  mpCorrespondingProperty(src.mpCorrespondingProperty),
  mpCorrespondingPropertyValue(src.mpCorrespondingPropertyValue),
  mpCompartmentValue(src.mpCompartmentValue),
  mpQuantity2NumberValue(src.mpQuantity2NumberValue),
  mStoichiometryVector(src.mStoichiometryVector),
  mRateVector(src.mRateVector),
  mpCalculate(src.mpCalculate),
  mpDataObject(src.mpDataObject)
{}

// virtual
CMathObject::~CMathObject()
{
  pdelete(mpExpression);
}

void CMathObject::copy(const CMathObject & src, CMathContainer & container)
{
  assert(&src != this);
  *this = src;

  if (src.mpExpression != NULL)
    {
      mpExpression = CMathExpression::copy(*src.mpExpression, container);
    }
  else
    {
      mpExpression = NULL;
    }
}

void CMathObject::relocate(CMathContainer * pContainer,
                           const std::vector< CMath::sRelocate > & relocations)
{
  pContainer->relocateValue(mpValue, relocations);
  pContainer->relocateObject(mpCorrespondingProperty, relocations);
  pContainer->relocateValue(mpCorrespondingPropertyValue, relocations);
  pContainer->relocateValue(mpCompartmentValue, relocations);
  pContainer->relocateValue(mpQuantity2NumberValue, relocations);

  if (mpExpression != NULL)
    {
      mpExpression = CMathExpression::copy(*mpExpression, *pContainer);
      mpExpression->relocate(pContainer, relocations);
    }

  const C_FLOAT64 ** ppRate = mRateVector.begin();
  const C_FLOAT64 ** ppRateEnd = mRateVector.end();

  for (; ppRate != ppRateEnd; ++ppRate)
    {
      pContainer->relocateValue(*ppRate, relocations);
    }

  pContainer->relocateObjectSet(mPrerequisites, relocations);
}

// virtual
CCommonName CMathObject::getCN() const
{
  if (mpDataObject == NULL)
    return CCommonName("CMathObject: no data equivalence.");

  return mpDataObject->getCN();
}

std::string CMathObject::getObjectDisplayName() const
{
  if (mpDataObject == NULL)
    {
      return "Math Container Internal Object";
    }

  return mpDataObject->getObjectDisplayName();
}

//virtual
const CObjectInterface * CMathObject::getObject(const CCommonName & cn) const
{
  if (mpDataObject == NULL)
    return NULL;

  const CObjectInterface * pObject = mpDataObject->getObject(cn);

  if (pObject != mpDataObject)
    return pObject;

  return this;
}

// virtual
const CObjectInterface::ObjectSet & CMathObject::getPrerequisites() const
{
  return mPrerequisites;
}

// virtual
bool CMathObject::isPrerequisiteForContext(const CObjectInterface * pObject,
    const CCore::SimulationContextFlag & context,
    const CObjectInterface::ObjectSet & changedObjects) const
{
  // This method should only be called for objects which are prerequisites.
  // We check for this only in debug mode.
  assert(mPrerequisites.find(pObject) != mPrerequisites.end());

  switch (mEntityType)
    {
      case CMath::EntityType::Moiety:

        if (context.isSet(CCore::SimulationContext::UpdateMoieties) &&
            mValueType == CMath::ValueType::TotalMass)
          {
            return true;
          }

        if (context.isSet(CCore::SimulationContext::UseMoieties) &&
            mValueType == CMath::ValueType::DependentMass)
          {
            return true;
          }

        return false;
        break;

      case CMath::EntityType::Species:

        // For species we need to account for the duality of the intensive and extensive value
        if (mValueType != CMath::ValueType::Value)
          return true;

        if (context.isSet(CCore::SimulationContext::UseMoieties) &&
            mSimulationType == CMath::SimulationType::Dependent &&
            !mIsIntensiveProperty)
          {
            const CMathObject * pMathObject = dynamic_cast< const CMathObject * >(pObject);

            if (pMathObject != NULL &&
                pMathObject->getEntityType() == CMath::EntityType::Moiety &&
                pMathObject->getValueType() == CMath::ValueType::DependentMass)
              {
                return true;
              }

            return false;
          }

        // If the value is in the context, it does not depend on the object.
        if (changedObjects.find(this) != changedObjects.end())
          return false;

        if (mIsIntensiveProperty)
          {
            // Densities which are not in the context have to be recalculated.
            return true;
          }
        else
          {
            // Amount which are determine by assignment need to be recalculated.
            if (mSimulationType == CMath::SimulationType::Assignment)
              return true;

            // If the concentration was changed in the context we need to recalculate.
            if (changedObjects.find(mpCorrespondingProperty) != changedObjects.end())
              return true;

            // If the concentration is calculated by an assignment we need to recalculate.
            if (mpCorrespondingProperty->getSimulationType() == CMath::SimulationType::Assignment)
              return true;

            return false;
          }

        break;

      case CMath::EntityType::Event:

        if (context.isSet(CCore::SimulationContext::EventHandling) &&
            mValueType == CMath::ValueType::Discontinuous)
          {
            switch (mpExpression->getRoot()->mainType() | mpExpression->getRoot()->subType())
              {
                case (CEvaluationNode::MainType::CHOICE | CEvaluationNode::SubType::IF):
                {
                  const CMathObject * pMathObject = dynamic_cast< const CMathObject * >(pObject);

                  if (pMathObject != NULL &&
                      pMathObject->mValueType == CMath::ValueType::EventTrigger)
                    {
                      return false;
                    }

                  return true;
                }
                break;

                case (CEvaluationNode::MainType::FUNCTION | CEvaluationNode::SubType::FLOOR):
                  return false;
                  break;

                case (CEvaluationNode::MainType::FUNCTION | CEvaluationNode::SubType::CEIL):
                  return false;
                  break;

                default:
                  return true;
              }
          }

        return true;
        break;

      case CMath::EntityType::Delay:

        if (context.isSet(CCore::SimulationContext::EventHandling))
          {
            return true;
          }

        return (mValueType == CMath::ValueType::DelayLag);

        break;

      default:
        return true;
    }

  // This should never be reached.
  return true;
}

// virtual
void CMathObject::print(std::ostream * ostream) const
{
  (*ostream) << *mpValue;
}

void CMathObject::setDataObject(const CDataObject * pDataObject)
{
  mpDataObject = pDataObject;
}

// virtual
const CDataObject * CMathObject::getDataObject() const
{
  return mpDataObject;
}

// virtual
void * CMathObject::getValuePointer() const
{
  return mpValue;
}

// virtual
void CMathObject::calculateValue()
{
  assert(mpCalculate != NULL);

  (this->*mpCalculate)();

#ifdef TRACK_NAN

  // Check for NaN
  if (std::isnan(*mpValue) && mpExpression->getInfix() != "")
    {
      std::cout << "NaN Value for: " << getCN() << std::endl;
    }

#endif // TRACK_NAN

  // For an extensive transient value of a dependent species we have 2
  // possible assignments depending on the context.
  //   1) Conversion from the intensive property
  //   2) Dependent mass off a moiety
  //
  // The solution is that the moiety automatically updates the value in conjunction
  // with the dependency graph omitting the value in the update sequence if the context
  // is CMath::UseMoieties.
}

const C_FLOAT64 & CMathObject::getValue() const
{
  return *mpValue;
}

bool CMathObject::canCalculateValue() const
{
  return mpCalculate != NULL;
}

void CMathObject::calculateExpression()
{
  assert(mpExpression != NULL);

  *mpValue = mpExpression->value();
}

void CMathObject::calculateExtensiveValue()
{
  *mpValue = *mpCorrespondingPropertyValue * *mpCompartmentValue * *mpQuantity2NumberValue;
}

void CMathObject::calculateIntensiveValue()
{
  *mpValue = *mpCorrespondingPropertyValue / (*mpCompartmentValue * *mpQuantity2NumberValue);
}

void CMathObject::calculateParticleFlux()
{
  *mpValue = *mpCorrespondingPropertyValue * *mpQuantity2NumberValue;
}

void CMathObject::calculateExtensiveReactionRate()
{
  *mpValue = 0.0;

  const C_FLOAT64 * pStoi = mStoichiometryVector.begin();
  const C_FLOAT64 ** ppRate = mRateVector.begin();
  const C_FLOAT64 ** ppRateEnd = mRateVector.end();

  for (; ppRate != ppRateEnd; ++ppRate, ++pStoi)
    {
      *mpValue += *pStoi * **ppRate;
    }
}

void CMathObject::calculatePropensity()
{
  *mpValue = std::max(0.0, *mpCorrespondingPropertyValue);
}

void CMathObject::calculateCorrectedPropensity()
{
  *mpValue = std::max(0.0, *mpCorrespondingPropertyValue);

  const C_FLOAT64 * pStoi = mStoichiometryVector.begin();
  const C_FLOAT64 ** ppRate = mRateVector.begin();
  const C_FLOAT64 ** ppRateEnd = mRateVector.end();

  for (; ppRate != ppRateEnd; ++ppRate, ++pStoi)
    {
      for (C_FLOAT64 m = *pStoi; m > 0.1; m -= 1.0)
        {
          *mpValue = std::max(0.0, *mpValue * (1.0 - m / **ppRate));
        }
    }
}

void CMathObject::calculateTransitionTime()
{
  C_FLOAT64 PositiveFlux = 0.0;
  C_FLOAT64 NegativeFlux = 0.0;

  const C_FLOAT64 * pStoi = mStoichiometryVector.begin();
  const C_FLOAT64 ** ppRate = mRateVector.begin();
  const C_FLOAT64 ** ppRateEnd = mRateVector.end();

  // The first entry is the species' particle number
  C_FLOAT64 Value = **ppRate;
  ++pStoi;
  ++ppRate;

  for (; ppRate != ppRateEnd; ++ppRate, ++pStoi)
    {
      C_FLOAT64 tmp = *pStoi * **ppRate;

      if (tmp >= 0)
        PositiveFlux += tmp;
      else
        NegativeFlux -= tmp;
    }

  *mpValue = fabs(Value) / std::max(NegativeFlux, PositiveFlux);
}

const CMath::ValueType & CMathObject::getValueType() const
{
  return mValueType;
}

void CMathObject::setValueType(const CMath::ValueType & valueType)
{
  mValueType = valueType;
}

const CMath::EntityType & CMathObject::getEntityType() const
{
  return mEntityType;
}

const CMath::SimulationType & CMathObject::getSimulationType() const
{
  return mSimulationType;
}

void CMathObject::setSimulationType(const CMath::SimulationType & simulationType)
{
  mSimulationType = simulationType;
}

const bool & CMathObject::isIntensiveProperty() const
{
  return mIsIntensiveProperty;
}

const bool & CMathObject::isInitialValue() const
{
  return mIsInitialValue;
}

const CMathObject * CMathObject::getCorrespondingProperty() const
{
  return mpCorrespondingProperty;
}

const C_FLOAT64 * CMathObject::getCompartmentValue() const
{
  return mpCompartmentValue;
}

bool CMathObject::setExpression(const std::string & infix,
                                const bool & isBoolean,
                                CMathContainer & container)
{
  bool success = true;
  CExpression Expression;
  Expression.setIsBoolean(isBoolean);

  success &= Expression.setInfix(infix);
  CObjectInterface::ContainerList ListOfContainer;
  ListOfContainer.push_back(&container);
  success &= Expression.compile(ListOfContainer);
  success &= setExpression(Expression, container);

  return success;
}

bool CMathObject::setExpression(const CExpression & expression,
                                CMathContainer & container)
{
  bool success = true;

  success &= createConvertedExpression(&expression, container);

  return success;
}

bool CMathObject::setExpressionPtr(CMathExpression * pMathExpression)
{
  bool success = true;

  mPrerequisites.clear();

  pdelete(mpExpression);
  mpExpression = pMathExpression;

  if (mpExpression != NULL)
    {
      success &= mpExpression->compile();
      compileExpression();
    }
  else
    {
      success = false;
    }

  return success;
}

const CMathExpression * CMathObject::getExpressionPtr() const
{
  return mpExpression;
}

void CMathObject::appendDelays(CMath::DelayData & Delays) const
{
  if (mpExpression == NULL)
    {
      return;
    }

  std::vector< CEvaluationNode * >::const_iterator it = mpExpression->getNodeList().begin();
  std::vector< CEvaluationNode * >::const_iterator end = mpExpression->getNodeList().end();

  for (; it != end; ++it)
    {
      switch ((*it)->mainType())
        {
          case CEvaluationNode::MainType::DELAY:
          {
            CEvaluationNode * pValueExpression = static_cast< CEvaluationNode * >((*it)->getChild());
            std::string Expression = static_cast< CEvaluationNode * >(pValueExpression->getSibling())->buildInfix();

            CMath::DelayData::iterator found = Delays.find(Expression);

            if (found == Delays.end())
              {
                found = Delays.insert(std::make_pair(Expression, CMath::DelayValueData()));
              }

            Expression = pValueExpression->buildInfix();
            found->second.insert(std::make_pair(Expression, std::make_pair((*it)->buildInfix(), const_cast< CMathObject * >(this))));
          }
          break;

          default:
            break;
        }
    }

  return;
}

#ifdef USE_JIT
bool CMathObject::compile(CMathContainer & container, CJitCompiler & jitCompiler)
#else
bool CMathObject::compile(CMathContainer & container)
#endif
{
  mPrerequisites.clear();
  bool success = true;

  mpQuantity2NumberValue = static_cast< const C_FLOAT64 * >(container.getQuantity2NumberFactorObject()->getValuePointer());

  if (mpDataObject != NULL)
    {
      if (mEntityType == CMath::EntityType::Species)
        {
          const CMetab * pSpecies = static_cast< const CMetab * >(mpDataObject->getObjectParent());
          mpCompartmentValue = static_cast< const C_FLOAT64 * >(container.getMathObject(pSpecies->getCompartment()->getValueReference())->getValuePointer());
        }
      else if (mEntityType == CMath::EntityType::Reaction)
        {
          const CReaction * pReaction = static_cast< const CReaction * >(mpDataObject->getObjectParent());

          if (pReaction->getScalingCompartment() != NULL)
            {
              mpCompartmentValue = static_cast< const C_FLOAT64 * >(container.getMathObject(pReaction->getScalingCompartment()->getValueReference())->getValuePointer());
            }
        }

      if (mIsInitialValue &&
          mpCompartmentValue != NULL)
        {
          mpCompartmentValue = container.getInitialValuePointer(mpCompartmentValue);
        }
    }

  switch (mValueType)
    {
      case CMath::ValueType::Undefined:
        success = false;
        break;

      case CMath::ValueType::Value:

        if (mIsInitialValue)
          {
            success = compileInitialValue(container);
          }
        else
          {
            success = compileValue(container);
          }

        break;

      case CMath::ValueType::Rate:
        success = compileRate(container);
        break;

      case CMath::ValueType::ParticleFlux:
        success = compileParticleFlux(container);
        break;

      case CMath::ValueType::Flux:
        success = compileFlux(container);
        break;

      case CMath::ValueType::Noise:

        if (mEntityType == CMath::EntityType::Reaction)
          {
            success = compileReactionNoise(container);
          }
        else
          {
            success = compileNoise(container);
          }

        break;

      case CMath::ValueType::ParticleNoise:
        success = compileReactionParticleNoise(container);
        break;

      case CMath::ValueType::Propensity:
        success = compilePropensity(container);
        break;

      case CMath::ValueType::TotalMass:
        success = compileTotalMass(container);
        break;

      case CMath::ValueType::DependentMass:
        success = compileDependentMass(container);
        break;

      case CMath::ValueType::TransitionTime:
        success = compileTransitionTime(container);
        break;

      case CMath::ValueType::Discontinuous:
        compileExpression();
        break;

      case CMath::ValueType::EventDelay:
      case CMath::ValueType::EventPriority:
      case CMath::ValueType::EventAssignment:
      case CMath::ValueType::EventTrigger:
      case CMath::ValueType::EventRoot:
      case CMath::ValueType::EventRootState:
        // These objects are compiled through the event compile,
        // which is executed after the object compile. It is therefore
        // correct to leave the object in its default state.
        break;

      case CMath::ValueType::__SIZE:
        break;
    }

#ifdef USE_JIT
  setJITCompiler(jitCompiler);
#endif // USE_JIT

  return success;
}

#ifdef USE_JIT
void CMathObject::setJITCompiler(CJitCompiler & jitCompiler)
{
  if (CJitCompiler::JitEnabled()
      && mpCalculate == &CMathObject::calculateExpression
      && mpExpression != NULL
      && mpExpression->size() < 2048
      && mpExpression->getValidity().getFirstWorstIssue().isSuccess()
      && !mpExpression->getPrerequisites().empty())
    {
      mpExpression->setCompiler(&jitCompiler);
    }
}
#endif // USE_JIT

bool CMathObject::compileInitialValue(CMathContainer & container)
{
  bool success = true;

  // The default value is NaN
  *mpValue = InvalidValue;

  // Initial values are taken from the data model
  if (mpDataObject != NULL)
    {
      *mpValue = * (C_FLOAT64 *) mpDataObject->getValuePointer();
    }

  const CModelEntity * pEntity = dynamic_cast< const CModelEntity * >(mpDataObject->getObjectParent());
  const CMetab * pSpecies = NULL;

  // Only species have corresponding properties (extensive vs intensive).
  if (mEntityType == CMath::EntityType::Species)
    {
      pSpecies = static_cast< const CMetab * >(pEntity);

      if (mIsIntensiveProperty)
        {
          mpCorrespondingProperty = container.getMathObject(pSpecies->getInitialValueReference());
        }
      else
        {
          mpCorrespondingProperty = container.getMathObject(pSpecies->getInitialConcentrationReference());
        }

      mpCorrespondingPropertyValue = static_cast< const C_FLOAT64 * >(mpCorrespondingProperty->getValuePointer());
    }

  if (mIsIntensiveProperty)
    {
      switch (mSimulationType)
        {
          case CMath::SimulationType::EventTarget:
          case CMath::SimulationType::Fixed:
          case CMath::SimulationType::ODE:
          case CMath::SimulationType::Independent:
          case CMath::SimulationType::Dependent:
          case CMath::SimulationType::Conversion:
            success &= createIntensiveValueExpression(pSpecies, container);
            break;

          case CMath::SimulationType::Assignment:
            // Extensive Property * Conversion / Compartment Size
            success &= createConvertedExpression(pSpecies->getInitialExpressionPtr(), container);

            break;

          case CMath::SimulationType::Time:
          case CMath::SimulationType::Undefined:
            success = false;
            break;

          case CMath::SimulationType::__SIZE:
            break;
        }
    }
  else
    {
      switch (mSimulationType)
        {
          case CMath::SimulationType::Fixed:
            break;

          case CMath::SimulationType::Assignment:
            if (pEntity != NULL)
              {
                success &= createConvertedExpression(pEntity->getInitialExpressionPtr(), container);
              }
            else
              {
                compileExpression();
              }

            break;

          case CMath::SimulationType::Conversion:
          {
            success &= createExtensiveValueExpression(pSpecies, container);
          }
          break;

          case CMath::SimulationType::Undefined:
          case CMath::SimulationType::EventTarget:
          case CMath::SimulationType::Time:
          case CMath::SimulationType::ODE:
          case CMath::SimulationType::Independent:
          case CMath::SimulationType::Dependent:
            success = false;
            break;

          case CMath::SimulationType::__SIZE:
            break;
        }
    }

  return success;
}

bool CMathObject::compileValue(CMathContainer & container)
{
  bool success = true;

  // The default value is NaN
  *mpValue = InvalidValue;

  const CModelEntity * pEntity = NULL;
  const CMetab * pSpecies = NULL;

  if (mpDataObject != NULL)
    {
      pEntity = dynamic_cast< const CModelEntity * >(mpDataObject->getObjectParent());
    }

  // Only species have corresponding properties (extensive vs intensive).
  if (mEntityType == CMath::EntityType::Species)
    {
      pSpecies = static_cast< const CMetab * >(pEntity);

      if (mIsIntensiveProperty)
        {
          mpCorrespondingProperty = container.getMathObject(pSpecies->getValueReference());
        }
      else
        {
          mpCorrespondingProperty = container.getMathObject(pSpecies->getConcentrationReference());
        }

      mpCorrespondingPropertyValue = static_cast< const C_FLOAT64 * >(mpCorrespondingProperty->getValuePointer());
    }

  if (mIsIntensiveProperty)
    {
      switch (mSimulationType)
        {
          case CMath::SimulationType::Assignment:
            success &= createConvertedExpression(pSpecies->getExpressionPtr(), container);
            break;

          case CMath::SimulationType::EventTarget:
          case CMath::SimulationType::Conversion:
            success &= createIntensiveValueExpression(pSpecies, container);
            break;

          case CMath::SimulationType::Undefined:
          case CMath::SimulationType::Fixed:
          case CMath::SimulationType::Time:
          case CMath::SimulationType::ODE:
          case CMath::SimulationType::Independent:
          case CMath::SimulationType::Dependent:
            success = false;
            break;

          case CMath::SimulationType::__SIZE:
            break;
        }
    }
  else
    {
      // Species need an additional conversion since the event targets the
      // intensive property.
      if (mEntityType == CMath::EntityType::Species)
        {
          success &= createExtensiveValueExpression(pSpecies, container);
        }

      switch (mSimulationType)
        {
          case CMath::SimulationType::Fixed:
          case CMath::SimulationType::EventTarget:
          case CMath::SimulationType::Time:
          case CMath::SimulationType::ODE:
          case CMath::SimulationType::Independent:
          case CMath::SimulationType::Conversion:
            break;

          case CMath::SimulationType::Dependent:
          {
            // We need to add the dependent number of the moiety as a possible
            // prerequisite.
            const CMoiety * pMoiety = pSpecies->getMoiety();
            const CMathObject * pDependentNumber =
              container.getMathObject(pMoiety->getDependentNumberReference());

            mPrerequisites.insert(pDependentNumber);
          }
          break;

          case CMath::SimulationType::Assignment:
            if (pEntity != NULL)
              {
                success &= createConvertedExpression(pEntity->getExpressionPtr(), container);
              }
            else
              {
                compileExpression();
              }

            break;

          case CMath::SimulationType::Undefined:
            success = false;
            break;

          case CMath::SimulationType::__SIZE:
            break;
        }
    }

  return success;
}

bool CMathObject::compileRate(CMathContainer & container)
{
  bool success = true;

  // The default value is NaN
  *mpValue = InvalidValue;

  const CModelEntity * pEntity = NULL;
  const CMetab * pSpecies = NULL;

  if (mpDataObject != NULL)
    {
      pEntity = dynamic_cast< const CModelEntity * >(mpDataObject->getObjectParent());
    }

  // Only species have corresponding properties (extensive vs intensive).
  if (mEntityType == CMath::EntityType::Species)
    {
      pSpecies = static_cast< const CMetab * >(pEntity);
    }

  if (mIsIntensiveProperty)
    {
      // Only species have intensive properties.
      switch (mSimulationType)
        {
          case CMath::SimulationType::Assignment:
            success &= createIntensiveRateExpression(pSpecies, container);
            break;

          case CMath::SimulationType::Undefined:
          case CMath::SimulationType::Fixed:
          case CMath::SimulationType::EventTarget:
          case CMath::SimulationType::Time:
          case CMath::SimulationType::ODE:
          case CMath::SimulationType::Independent:
          case CMath::SimulationType::Dependent:
          case CMath::SimulationType::Conversion:
            success = false;
            break;

          case CMath::SimulationType::__SIZE:
            break;
        }
    }
  else
    {

      switch (mSimulationType)
        {
          case CMath::SimulationType::Fixed:
            *mpValue = 0;
            break;

          case CMath::SimulationType::Time:
            *mpValue = 1;
            break;

          case CMath::SimulationType::ODE:

            if (mEntityType == CMath::EntityType::Species)
              {
                success &= createExtensiveODERateExpression(pSpecies, container);
              }
            else if (pEntity != NULL)
              {
                success &= createConvertedExpression(pEntity->getExpressionPtr(), container);
              }
            else
              {
                compileExpression();
              }

            break;

          case CMath::SimulationType::Independent:
          case CMath::SimulationType::Dependent:
          {
            success &= createExtensiveReactionRateExpression(pSpecies, container);
          }
          break;

          case CMath::SimulationType::Assignment:
            // TODO When we have symbolic differentiation we can deal with this.
            break;

          case CMath::SimulationType::Undefined:
          case CMath::SimulationType::EventTarget:
          case CMath::SimulationType::Conversion:
            success = false;
            break;

          case CMath::SimulationType::__SIZE:
            break;
        }
    }

  return success;
}

bool CMathObject::compileParticleFlux(CMathContainer & container)
{
  bool success = true;

  // The default value is NaN
  *mpValue = InvalidValue;

  const CReaction * pReaction = static_cast< const CReaction * >(mpDataObject->getObjectParent());

  // We need to check whether this reaction is a single compartment reaction and scale
  // it if true.
  //   mParticleFlux = *mUnitScalingFactor * mFlux;
  //   mUnitScalingFactor = & pModel->getQuantity2NumberFactor();

  mpCorrespondingProperty = container.getMathObject(pReaction->getFluxReference());

  if (mIsInitialValue)
    {
      mpCorrespondingProperty = container.getInitialValueObject(mpCorrespondingProperty);
    }

  mpCorrespondingPropertyValue = static_cast< const C_FLOAT64 * >(mpCorrespondingProperty->getValuePointer());

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(std::numeric_limits<double>::digits10 + 2);

  Infix << pointerToString(mpQuantity2NumberValue);
  Infix << "*";
  Infix << pointerToString(mpCorrespondingPropertyValue);

  if (mpExpression == NULL)
    {
      mpExpression = new CMathExpression("ParticleFluxExpression", container);
    }

  success &= mpExpression->setInfix(Infix.str());
  success &= mpExpression->compile();
  compileExpression();

  mpCalculate = &CMathObject::calculateParticleFlux;

  return success;
}

bool CMathObject::compileFlux(CMathContainer & container)
{
  bool success = true;

  // The default value is NaN
  *mpValue = InvalidValue;

  const CReaction * pReaction = static_cast< const CReaction * >(mpDataObject->getObjectParent());

  // We need to check whether this reaction is a single compartment reaction and scale it if true.
  //   mFlux = *mScalingFactor * mpFunction->calcValue(mMap.getPointers());
  //   mScalingFactor = compartment volume or 1

  pdelete(mpExpression);
  mpExpression = new CMathExpression(*pReaction->getFunction(),
                                     pReaction->getCallParameters(),
                                     container,
                                     !mIsInitialValue);

  if (mpCompartmentValue != NULL &&
      pReaction->getEffectiveKineticLawUnitType() == CReaction::KineticLawUnit::ConcentrationPerTime)
    {
      CExpression Tmp(mpExpression->getObjectName(), &container);

      std::string Infix = pointerToString(mpCompartmentValue) + "*(" + mpExpression->getInfix() + ")";
      success &= Tmp.setInfix(Infix);
      success &= Tmp.compile();

      pdelete(mpExpression);
      mpExpression = new CMathExpression(Tmp, container, false);
    }

  compileExpression();

  return success;
}

bool CMathObject::compileNoise(CMathContainer & container)
{
  bool success = true;

  // The default value is NaN
  *mpValue = InvalidValue;

  // Reset the prerequisites
  mPrerequisites.clear();

  const CModelEntity * pEntity = NULL;
  const CMetab * pSpecies = NULL;

  if (mpDataObject != NULL)
    {
      pEntity = dynamic_cast< const CModelEntity * >(mpDataObject->getObjectParent());
    }

  // Only species have corresponding properties (extensive vs intensive).
  if (mEntityType == CMath::EntityType::Species)
    {
      pSpecies = static_cast< const CMetab * >(pEntity);
    }

  if (mIsIntensiveProperty)
    {
      // Only species have intensive properties.
      switch (mSimulationType)
        {
          case CMath::SimulationType::Assignment:
            success &= createIntensiveNoiseExpression(pSpecies, container);
            break;

          case CMath::SimulationType::Undefined:
          case CMath::SimulationType::Fixed:
          case CMath::SimulationType::EventTarget:
          case CMath::SimulationType::Time:
          case CMath::SimulationType::ODE:
          case CMath::SimulationType::Independent:
          case CMath::SimulationType::Dependent:
          case CMath::SimulationType::Conversion:
            success = false;
            break;

          case CMath::SimulationType::__SIZE:
            break;
        }
    }
  else
    {
      switch (mSimulationType)
        {
          case CMath::SimulationType::ODE:

            if (pEntity != NULL &&
                pEntity->hasNoise())
              {
                if (mEntityType == CMath::EntityType::Species)
                  {
                    success &= createExtensiveNoiseExpression(pSpecies, container);
                  }
                else if (pEntity->getNoiseExpressionPtr() != NULL)
                  {
                    success &= createConvertedExpression(pEntity->getNoiseExpressionPtr(), container);
                  }

                container.addNoiseInputObject(this);
                compileExpression();
              }

            else
              {
                *mpValue = 0.0;
              }

            break;

          case CMath::SimulationType::Independent:
          case CMath::SimulationType::Dependent:
            // TODO CRITICAL Implement me!
          {
            success &= createExtensiveReactionNoiseExpression(pSpecies, container);
          }

          break;

          case CMath::SimulationType::Fixed:
          case CMath::SimulationType::Time:
          case CMath::SimulationType::Assignment:
          case CMath::SimulationType::Undefined:
          case CMath::SimulationType::EventTarget:
          case CMath::SimulationType::Conversion:
            success = false;
            break;

          case CMath::SimulationType::__SIZE:
            break;
        }
    }

  return success;
}

bool CMathObject::compileReactionParticleNoise(CMathContainer & container)
{
  bool success = true;

  // The default value is NaN
  *mpValue = InvalidValue;

  // Reset the prerequisites
  mPrerequisites.clear();
  pdelete(mpExpression);

  const CReaction * pReaction = static_cast< const CReaction * >(mpDataObject->getObjectParent());

  if (pReaction->hasNoise())
    {
      mpExpression = new CMathExpression(*pReaction->getNoiseExpressionPtr(),
                                         container,
                                         !mIsInitialValue);

      container.addNoiseInputObject(this);
    }

  compileExpression();

  return success;
}

bool CMathObject::compileReactionNoise(CMathContainer & container)
{
  bool success = true;

  // The default value is NaN
  *mpValue = InvalidValue;

  // Reset the prerequisites
  mPrerequisites.clear();
  pdelete(mpExpression);

  const CReaction * pReaction = static_cast< const CReaction * >(mpDataObject->getObjectParent());

  if (pReaction->hasNoise())
    {
      std::string Infix = pointerToString(container.getMathObject(pReaction->getParticleNoiseReference())->getValuePointer());
      Infix += "/" + pointerToString(mpQuantity2NumberValue);

      // We need to check whether this reaction is a single compartment reaction and scale
      // it if true.
      //   mParticleNoise = *mUnitScalingFactor * mNoise;
      //   mUnitScalingFactor = & pModel->getQuantity2NumberFactor();
      if (pReaction->getScalingCompartment() != NULL &&
          pReaction->getEffectiveKineticLawUnitType() == CReaction::KineticLawUnit::ConcentrationPerTime)
        {
          Infix += "/" + pointerToString(mpCompartmentValue);
        }

      mpExpression = new CMathExpression("ReactionNoiseExpression", container);
      success &= mpExpression->setInfix(Infix);
      success &= mpExpression->compile();
    }

  compileExpression();

  return success;
}

bool CMathObject::compilePropensity(CMathContainer & container)
{
  bool success = true;

  // The default value is NaN
  *mpValue = InvalidValue;

  const CReaction * pReaction = static_cast< const CReaction * >(mpDataObject->getObjectParent());
  mpCorrespondingProperty = container.getMathObject(pReaction->getParticleFluxReference());
  mpCorrespondingPropertyValue = static_cast< const C_FLOAT64 * >(mpCorrespondingProperty->getValuePointer());
  std::vector< std::pair < C_FLOAT64, const C_FLOAT64 *> > CalculationVector;

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(std::numeric_limits<double>::digits10 + 2);

  // Propensity for reversible reactions must be NaN
  if (pReaction->isReversible())
    {
      Infix << "NAN";
    }
  else
    {
      // Propensity is the same as the particle flux, but it must not be negative.
      Infix << "max(0," << pointerToString(mpCorrespondingPropertyValue) << ")";

      // Apply correction for deterministic models
      if (container.getModel().getModelType() == CModel::ModelType::deterministic)
        {
          const CDataVector<CChemEqElement> & Substrates = pReaction->getChemEq().getSubstrates();
          CDataVector< CChemEqElement >::const_iterator itSubstrate = Substrates.begin();
          CDataVector< CChemEqElement >::const_iterator endSubstrate = Substrates.end();
          std::vector< CEvaluationNode * > Numerator;
          std::vector< CEvaluationNode * > Denominator;

          for (; itSubstrate != endSubstrate; ++itSubstrate)
            {
              const CMetab * pMetab = itSubstrate->getMetabolite();
              const C_FLOAT64 * pNumber = static_cast< const C_FLOAT64 * >((pMetab != NULL) ? container.getMathObject(pMetab->getValueReference())->getValuePointer() : &CMathObject::InvalidValue);
              const std::string NumberPointer = pointerToString(pNumber);

              C_FLOAT64 Multiplicity = itSubstrate->getMultiplicity();

              Multiplicity -= 1.0; // Nothing to correct if the multiplicity is 1.

              if (Multiplicity > 2.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
                {
                  CEvaluationNode * pPower = new CEvaluationNodeOperator(CEvaluationNode::SubType::POWER, "^");
                  pPower->addChild(new CEvaluationNodeObject(CEvaluationNode::SubType::POINTER, NumberPointer));
                  pPower->addChild(new CEvaluationNodeNumber(CEvaluationNode::SubType::DOUBLE, StringPrint("%e", Multiplicity)));
                  Denominator.emplace_back(pPower);
                }
              else if (Multiplicity > 1.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
                {
                  Denominator.emplace_back(new CEvaluationNodeObject(CEvaluationNode::SubType::POINTER, NumberPointer));
                }

              if (Multiplicity > 1.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
                {
                  CalculationVector.push_back(std::make_pair(Multiplicity, pNumber));
                }

              while (Multiplicity > 1.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
                {
                  CEvaluationNode * pMinus = new CEvaluationNodeOperator(CEvaluationNode::SubType::MINUS, "-");
                  pMinus->addChild(new CEvaluationNodeObject(CEvaluationNode::SubType::POINTER, NumberPointer));
                  pMinus->addChild(new CEvaluationNodeNumber(CEvaluationNode::SubType::DOUBLE, StringPrint("%e", Multiplicity)));

                  CEvaluationNode * pMax = new CEvaluationNodeFunction(CEvaluationNode::SubType::MAX, "max");
                  pMax->addChild(new CEvaluationNodeNumber(CEvaluationNode::SubType::DOUBLE, "0"));
                  pMax->addChild(pMinus);

                  Numerator.emplace_back(pMax);

                  Multiplicity -= 1.0;
                }
            }

          if (!Numerator.empty())
            {
              CExpression Tmp;
              Tmp.setRoot(BalanceTree< CEvaluationNode * >::create(Numerator, [](CEvaluationNode * const & pFirst, CEvaluationNode * const & pSecond)
              {
                CEvaluationNode * pNew = new CEvaluationNodeOperator(CEvaluationNode::SubType::MULTIPLY, "*");
                pNew->addChild(pFirst);
                pNew->addChild(pSecond);
                return pNew;
              }));

              Infix << "*" << Tmp.getInfix();
            }

          if (!Denominator.empty())
            {
              CExpression Tmp;
              Tmp.setRoot(BalanceTree< CEvaluationNode * >::create(Denominator, [](CEvaluationNode * const & pFirst, CEvaluationNode * const & pSecond)
              {
                CEvaluationNode * pNew = new CEvaluationNodeOperator(CEvaluationNode::SubType::MULTIPLY, "*");
                pNew->addChild(pFirst);
                pNew->addChild(pSecond);
                return pNew;
              }));

              Infix << "/(" << Tmp.getInfix() << ")";
            }
        }
    }

  if (mpExpression == NULL)
    {
      mpExpression = new CMathExpression("PropensityExpression", container);
    }

  success &= mpExpression->setInfix(Infix.str());
  success &= mpExpression->compile();
  compileExpression();

  if (!pReaction->isReversible())
    {
      if (CalculationVector.empty())
        {
          mpCalculate = &CMathObject::calculatePropensity;
        }
      else
        {
          mStoichiometryVector.resize(CalculationVector.size());
          mRateVector.resize(CalculationVector.size());
          std::vector< std::pair < C_FLOAT64, const C_FLOAT64 *> >::const_iterator itPair = CalculationVector.begin();
          std::vector< std::pair < C_FLOAT64, const C_FLOAT64 *> >::const_iterator endPair = CalculationVector.end();
          C_FLOAT64 * pStoi = mStoichiometryVector.begin();
          const C_FLOAT64 **ppRate = mRateVector.begin();

          for (; itPair != endPair; ++itPair, ++pStoi, ++ppRate)
            {
              *pStoi = itPair->first;
              *ppRate = itPair->second;
            }

          mpCalculate = &CMathObject::calculateCorrectedPropensity;
        }
    }

  return success;
}

bool CMathObject::compileTotalMass(CMathContainer & container)
{
  bool success = true;

  // The default value is NaN
  *mpValue = InvalidValue;

  std::vector< std::pair < C_FLOAT64, const C_FLOAT64 *> > CalculationVector;
  const CMoiety * pMoiety = static_cast< const CMoiety *>(mpDataObject->getObjectParent());

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(std::numeric_limits<double>::digits10 + 2);

  std::vector< std::pair< C_FLOAT64, CMetab * > >::const_iterator it = pMoiety->getEquation().begin();
  std::vector< std::pair< C_FLOAT64, CMetab * > >::const_iterator end = pMoiety->getEquation().end();
  bool First = true;

  for (; it != end; ++it)
    {
      const C_FLOAT64 & Multiplicity = it->first;

      if (First || Multiplicity < 0.0)
        {
          Infix << Multiplicity;
        }
      else
        {
          Infix << "+" << Multiplicity;
        }

      C_FLOAT64 * pValue = (C_FLOAT64 *) container.getMathObject(it->second->getValueReference())->getValuePointer();

      Infix << "*";
      Infix << pointerToString(pValue);

      if (mIsInitialValue)
        {
          pValue = container.getInitialValuePointer(pValue);
        }

      CalculationVector.push_back(std::make_pair(it->first, pValue));

      First = false;
    }

  if (mpExpression == NULL)
    {
      mpExpression = new CMathExpression("TotalMass", container);
    }

  success &= mpExpression->setInfix(Infix.str());
  success &= mpExpression->compile();
  compileExpression();

  mStoichiometryVector.resize(CalculationVector.size());
  mRateVector.resize(CalculationVector.size());
  std::vector< std::pair < C_FLOAT64, const C_FLOAT64 *> >::const_iterator itPair = CalculationVector.begin();
  std::vector< std::pair < C_FLOAT64, const C_FLOAT64 *> >::const_iterator endPair = CalculationVector.end();
  C_FLOAT64 * pStoi = mStoichiometryVector.begin();
  const C_FLOAT64 **ppRate = mRateVector.begin();

  for (; itPair != endPair; ++itPair, ++pStoi, ++ppRate)
    {
      *pStoi = itPair->first;
      *ppRate = itPair->second;
    }

  mpCalculate = &CMathObject::calculateExtensiveReactionRate;

  return success;
}

bool CMathObject::compileDependentMass(CMathContainer & container)
{
  bool success = true;

  // The default value is NaN
  *mpValue = InvalidValue;

  C_FLOAT64 * pValue;
  std::vector< std::pair< C_FLOAT64, const C_FLOAT64 * > > CalculationVector;
  const CMoiety * pMoiety = static_cast< const CMoiety * >(mpDataObject->getObjectParent());

  pValue = (C_FLOAT64 *) container.getMathObject(pMoiety->getTotalNumberReference())->getValuePointer();

  if (mIsInitialValue)
    {
      pValue = container.getInitialValuePointer(pValue);
    }

  CalculationVector.push_back(std::make_pair(1.0, pValue));

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(std::numeric_limits<double>::digits10 + 2);

  Infix << pointerToString(pValue);

  std::vector< std::pair< C_FLOAT64, CMetab * > >::const_iterator it = pMoiety->getEquation().begin();
  std::vector< std::pair< C_FLOAT64, CMetab * > >::const_iterator end = pMoiety->getEquation().end();
  bool First = true;

  // The first element in the equation is always the dependent species. We can directly update
  // its value and therefore point mpValue to it.
  mpValue = (C_FLOAT64 *) container.getMathObject(it->second->getValueReference())->getValuePointer();

  ++it;

  for (; it != end; ++it)
    {
      const C_FLOAT64 & Multiplicity = it->first;

      if (First || Multiplicity >= 0.0)
        {
          Infix << "-" << Multiplicity;
        }
      else
        {
          Infix << "+" << fabs(Multiplicity);
        }

      pValue = (C_FLOAT64 *) container.getMathObject(it->second->getValueReference())->getValuePointer();

      Infix << "*";
      Infix << pointerToString(pValue);

      if (mIsInitialValue)
        {
          pValue = container.getInitialValuePointer(pValue);
        }

      CalculationVector.push_back(std::make_pair(-it->first, pValue));

      First = false;
    }

  if (mpExpression == NULL)
    {
      mpExpression = new CMathExpression("DependentMass", container);
    }

  success &= mpExpression->setInfix(Infix.str());
  success &= mpExpression->compile();
  compileExpression();

  mStoichiometryVector.resize(CalculationVector.size());
  mRateVector.resize(CalculationVector.size());
  std::vector< std::pair < C_FLOAT64, const C_FLOAT64 *> >::const_iterator itPair = CalculationVector.begin();
  std::vector< std::pair < C_FLOAT64, const C_FLOAT64 *> >::const_iterator endPair = CalculationVector.end();
  C_FLOAT64 * pStoi = mStoichiometryVector.begin();
  const C_FLOAT64 **ppRate = mRateVector.begin();

  for (; itPair != endPair; ++itPair, ++pStoi, ++ppRate)
    {
      *pStoi = itPair->first;
      *ppRate = itPair->second;
    }

  mpCalculate = &CMathObject::calculateExtensiveReactionRate;

  return success;
}

bool CMathObject::compileTransitionTime(CMathContainer & container)
{
  bool success = true;

  // The default value is NaN
  *mpValue = InvalidValue;

  calculate pCalculate = NULL;

  const CMetab * pSpecies = static_cast< const CMetab *>(mpDataObject->getObjectParent());

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(std::numeric_limits<double>::digits10 + 2);

  switch (pSpecies->getStatus())
    {
      case CModelEntity::Status::ODE:
        // mTT = *mpValue / fabs(mRate);
        Infix << "abs(";
        Infix << pointerToString(container.getMathObject(pSpecies->getValueReference())->getValuePointer());
        Infix << "/";
        Infix << pointerToString(container.getMathObject(pSpecies->getRateReference())->getValuePointer());
        Infix << ")";
        break;

      case CModelEntity::Status::REACTIONS:
      {
        std::ostringstream PositiveFlux;
        PositiveFlux.imbue(std::locale::classic());
        PositiveFlux.precision(std::numeric_limits<double>::digits10 + 2);

        std::ostringstream NegativeFlux;
        NegativeFlux.imbue(std::locale::classic());
        NegativeFlux.precision(std::numeric_limits<double>::digits10 + 2);

        bool First = true;
        std::vector< std::pair < C_FLOAT64, const C_FLOAT64 *> > CalculationVector;
        CalculationVector.push_back(std::make_pair(1.0, (C_FLOAT64 *) container.getMathObject(pSpecies->getValueReference())->getValuePointer()));

        const std::set< std::pair< const CReaction *, C_FLOAT64 > > & Stoichiometry = container.getModel().getReactionsPerSpecies(pSpecies);

        std::set< std::pair< const CReaction *, C_FLOAT64 > >::const_iterator itStoi = Stoichiometry.begin();
        std::set< std::pair< const CReaction *, C_FLOAT64 > >::const_iterator endStoi = Stoichiometry.end();

        for (; itStoi != endStoi; ++itStoi)
          {
            const C_FLOAT64 & Multiplicity = itStoi->second;

            if (!First)
              {
                PositiveFlux << "+";
                NegativeFlux << "+";
              }

            PositiveFlux << "max(";
            NegativeFlux << "min(";

            if (std::isnan(Multiplicity))
              {
                PositiveFlux << "nan*";
                NegativeFlux << "nan*";
              }
            else if (Multiplicity == std::numeric_limits< C_FLOAT64 >::infinity())
              {
                PositiveFlux << "infinity*";
                NegativeFlux << "infinity*";
              }
            else if (Multiplicity == -std::numeric_limits< C_FLOAT64 >::infinity())
              {
                PositiveFlux << "-infinity*";
                NegativeFlux << "-infinity*";
              }
            // Remove multiplying with -1.0
            else if (-1.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() < Multiplicity &&
                     Multiplicity < -1.0 + 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
              {
                PositiveFlux << "-";
                NegativeFlux << "-";
              }
            // Remove multiplying with 1.0
            else if (1.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() < Multiplicity &&
                     Multiplicity < 1.0 + 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
              {
                // PositiveFlux << "+";
                // NegativeFlux << "+";
              }
            else
              {
                PositiveFlux << Multiplicity << "*";
                NegativeFlux << Multiplicity << "*";
              }

            C_FLOAT64 * pValue = (C_FLOAT64 *) container.getMathObject(itStoi->first->getParticleFluxReference())->getValuePointer();

            PositiveFlux << pointerToString(pValue);
            NegativeFlux << pointerToString(pValue);

            PositiveFlux << ",0)";
            NegativeFlux << ",0)";

            CalculationVector.push_back(std::make_pair(Multiplicity, pValue));

            First = false;
          }

        if (!First)
          {
            Infix << "abs(";
            Infix << pointerToString(container.getMathObject(pSpecies->getValueReference())->getValuePointer());
            Infix << ")/max(-(" << NegativeFlux.str() << ")," << PositiveFlux.str() << ")";
          }

        mStoichiometryVector.resize(CalculationVector.size());
        mRateVector.resize(CalculationVector.size());
        std::vector< std::pair< C_FLOAT64, const C_FLOAT64 * > >::const_iterator itPair = CalculationVector.begin();
        std::vector< std::pair< C_FLOAT64, const C_FLOAT64 * > >::const_iterator endPair = CalculationVector.end();
        C_FLOAT64 * pStoi = mStoichiometryVector.begin();
        const C_FLOAT64 ** ppRate = mRateVector.begin();

        for (; itPair != endPair; ++itPair, ++pStoi, ++ppRate)
          {
            *pStoi = itPair->first;
            *ppRate = itPair->second;
          }

        pCalculate = &CMathObject::calculateTransitionTime;
      }
      break;

      default:
        break;
    }

  if (mpExpression == NULL)
    {
      mpExpression = new CMathExpression("TransitionTimeExpression", container);
    }

  success &= mpExpression->setInfix(Infix.str());
  success &= mpExpression->compile();
  compileExpression();

  if (pCalculate != NULL)
    mpCalculate = pCalculate;

  return success;
}

void CMathObject::compileExpression()
{
  // Reset the prerequisites
  mPrerequisites.clear();
  mpCalculate = NULL;

  if (mpExpression == NULL
      || mpExpression->getValidity().getFirstWorstIssue().isError())
    {
      return;
    }

  if (mIsInitialValue)
    {
      mpExpression->convertToInitialExpression();
    }

  mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                        mpExpression->getPrerequisites().end());

  if (mPrerequisites.empty())
    {
      calculateExpression();
    }

  mpCalculate = &CMathObject::calculateExpression;
}

bool CMathObject::createConvertedExpression(const CExpression * pExpression,
    CMathContainer & container)
{
  assert(pExpression != NULL);

  if (!pExpression) return false;

  bool success = true;
  pdelete(mpExpression);

  if (pExpression->getValidity().getHighestSeverity() != CIssue::eSeverity::Error)
    {
      bool ReplaceDiscontinuosNodes =
        !mIsInitialValue &&
        mValueType != CMath::ValueType::Discontinuous &&
        mValueType != CMath::ValueType::EventAssignment &&
        mValueType != CMath::ValueType::EventPriority &&
        mValueType != CMath::ValueType::EventDelay;

      mpExpression = new CMathExpression(*pExpression, container, ReplaceDiscontinuosNodes);
    }

  compileExpression();

  return success;
}

bool CMathObject::createIntensiveValueExpression(const CMetab * pSpecies,
    CMathContainer & container)
{
  bool success = true;

  // mConc = *mpValue / (mpModel->getQuantity2NumberFactor() * mpCompartment->getValue());
  CObjectInterface * pNumber = NULL;
  CObjectInterface * pCompartment = NULL;

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(std::numeric_limits<double>::digits10 + 2);

  Infix << pointerToString(mpCorrespondingPropertyValue);
  Infix << "/(";
  Infix << pointerToString(mpCompartmentValue);
  Infix << "*";
  Infix << pointerToString(mpQuantity2NumberValue);
  Infix << ")";

  if (mpExpression == NULL)
    {
      mpExpression = new CMathExpression("IntensiveValueExpression", container);
    }

  success &= mpExpression->setInfix(Infix.str());
  success &= mpExpression->compile();
  compileExpression();

  mpCalculate = &CMathObject::calculateIntensiveValue;

  return success;
}

bool CMathObject::createExtensiveValueExpression(const CMetab * pSpecies,
    CMathContainer & container)
{
  bool success = true;

  // mConc * mpCompartment->getValue() * mpModel->getQuantity2NumberFactor();

  CObjectInterface * pIntensiveValue = NULL;
  CObjectInterface * pCompartment = NULL;

  if (mIsInitialValue)
    {
      pIntensiveValue = pSpecies->getInitialConcentrationReference();
      pCompartment = pSpecies->getCompartment()->getInitialValueReference();
    }
  else
    {
      pIntensiveValue = pSpecies->getConcentrationReference();
      pCompartment = pSpecies->getCompartment()->getValueReference();
    }

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(std::numeric_limits<double>::digits10 + 2);

  Infix << pointerToString(mpCorrespondingPropertyValue);
  Infix << "*";
  Infix << pointerToString(mpCompartmentValue);
  Infix << "*";
  Infix << pointerToString(mpQuantity2NumberValue);

  if (mpExpression == NULL)
    {
      mpExpression = new CMathExpression("ExtensiveValueExpression", container);
    }

  success &= mpExpression->setInfix(Infix.str());
  success &= mpExpression->compile();
  compileExpression();

  mpCalculate = &CMathObject::calculateExtensiveValue;

  return success;
}

bool CMathObject::createIntensiveRateExpression(const CMetab * pSpecies,
    CMathContainer & container)
{
  bool success = true;

  /*
    mConcRate =
      (mRate * mpModel->getQuantity2NumberFactor() - mConc * mpCompartment->getRate())
      / mpCompartment->getValue();
   */

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(std::numeric_limits<double>::digits10 + 2);

  Infix << "(";
  Infix << pointerToString(container.getMathObject(pSpecies->getRateReference())->getValuePointer());
  Infix << "/";
  Infix << pointerToString(mpQuantity2NumberValue);

  if (pSpecies->getCompartment()->getStatus() != CModelEntity::Status::FIXED)
    {
      Infix << "-";
      Infix << pointerToString(container.getMathObject(pSpecies->getConcentrationReference())->getValuePointer());
      Infix << "*";
      Infix << pointerToString(container.getMathObject(pSpecies->getCompartment()->getRateReference())->getValuePointer());
    }

  Infix << ")/";
  Infix << pointerToString(mpCompartmentValue);

  if (mpExpression == NULL)
    {
      mpExpression = new CMathExpression("IntensiveRateExpression", container);
    }

  success &= mpExpression->setInfix(Infix.str());
  success &= mpExpression->compile();
  compileExpression();

  return success;
}

bool CMathObject::createExtensiveODERateExpression(const CMetab * pSpecies,
    CMathContainer & container)
{
  bool success = true;

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(std::numeric_limits<double>::digits10 + 2);

  /*
    mRate = mpModel->getQuantity2NumberFactor() *
      mpCompartment->getValue() * mpExpression->calcValue();
   */

  if (!pSpecies->getExpression().empty())
    {
      Infix << pointerToString(mpQuantity2NumberValue);
      Infix << "*";
      Infix << pointerToString(mpCompartmentValue);
      Infix << "*(";
      Infix << pSpecies->getExpression();
      Infix << ")";
    }

  CExpression E("ExtensiveODERateExpression", &container);
  success &= E.setInfix(Infix.str());
  success &= E.compile();

  pdelete(mpExpression);
  mpExpression = new CMathExpression(E, container, !mIsInitialValue);
  compileExpression();

  return success;
}

bool CMathObject::createExtensiveReactionRateExpression(const CMetab * pSpecies,
    CMathContainer & container)
{
  bool success = true;

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(std::numeric_limits<double>::digits10 + 2);

  bool First = true;
  std::vector< std::pair < C_FLOAT64, const C_FLOAT64 *> > CalculationVector;
  const std::set< std::pair< const CReaction *, C_FLOAT64 > > & Stoichiometry = container.getModel().getReactionsPerSpecies(pSpecies);

  std::set< std::pair< const CReaction *, C_FLOAT64 > >::const_iterator itStoi = Stoichiometry.begin();
  std::set< std::pair< const CReaction *, C_FLOAT64 > >::const_iterator endStoi = Stoichiometry.end();

  for (; itStoi != endStoi; ++itStoi)
    {
      const C_FLOAT64 & Multiplicity = itStoi->second;

      if (First || Multiplicity < 0.0)
        {
          if (std::isnan(Multiplicity))
            {
              Infix << "nan*";
            }
          else if (Multiplicity == std::numeric_limits< C_FLOAT64 >::infinity())
            {
              Infix << "infinity*";
            }
          else if (Multiplicity == -std::numeric_limits< C_FLOAT64 >::infinity())
            {
              Infix << "-infinity*";
            }
          // Remove multiplying with -1.0
          else if (-1.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() < Multiplicity &&
                   Multiplicity < -1.0 + 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
            {
              Infix << "-";
            }
          // Remove multiplying with 1.0
          else if (1.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() < Multiplicity &&
                   Multiplicity < 1.0 + 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
            {
              // Infix << "+";
            }
          else
            {
              Infix << Multiplicity << "*";
            }
        }
      else
        {
          if (std::isnan(Multiplicity))
            {
              Infix << "+nan*";
            }
          else if (Multiplicity == std::numeric_limits< C_FLOAT64 >::infinity())
            {
              Infix << "+infinity*";
            }
          // Remove multiplying with 1.0
          else if (1.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() < Multiplicity &&
                   Multiplicity < 1.0 + 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
            {
              Infix << "+";
            }
          else
            {
              Infix << "+" << Multiplicity << "*";
            }
        }

      First = false;

      Infix << pointerToString(container.getMathObject(itStoi->first->getParticleFluxReference())->getValuePointer());

      const C_FLOAT64 * pRate = static_cast< const C_FLOAT64 * >(container.getMathObject(itStoi->first->getParticleFluxReference())->getValuePointer());

      if (mIsInitialValue)
        {
          pRate = container.getInitialValuePointer(pRate);
        }

      CalculationVector.push_back(std::make_pair(Multiplicity, pRate));
    }

  if (mpExpression == NULL)
    {
      mpExpression = new CMathExpression("ExtensiveReactionExpression", container);
    }

  success &= mpExpression->setInfix(Infix.str());
  success &= mpExpression->compile();
  compileExpression();

  mStoichiometryVector.resize(CalculationVector.size());
  mRateVector.resize(CalculationVector.size());
  std::vector< std::pair < C_FLOAT64, const C_FLOAT64 *> >::const_iterator itPair = CalculationVector.begin();
  std::vector< std::pair < C_FLOAT64, const C_FLOAT64 *> >::const_iterator endPair = CalculationVector.end();
  C_FLOAT64 * pStoi = mStoichiometryVector.begin();
  const C_FLOAT64 **ppRate = mRateVector.begin();

  for (; itPair != endPair; ++itPair, ++pStoi, ++ppRate)
    {
      *pStoi = itPair->first;
      *ppRate = itPair->second;
    }

  mpCalculate = &CMathObject::calculateExtensiveReactionRate;

  return success;
}

bool CMathObject::createIntensiveNoiseExpression(const CMetab * pSpecies,
    CMathContainer & container)
{
  // The default value is NaN
  *mpValue = InvalidValue;

  // Reset the prerequisites
  mPrerequisites.clear();
  pdelete(mpExpression);

  bool success = true;

  if (pSpecies->hasNoise() && pSpecies->getNoiseExpressionPtr())
    {
      mpExpression = new CMathExpression(*pSpecies->getNoiseExpressionPtr(), container, !mIsInitialValue);
    }

  compileExpression();

  return success;
}

bool CMathObject::createExtensiveNoiseExpression(const CMetab * pSpecies,
    CMathContainer & container)
{
  // The default value is NaN
  *mpValue = InvalidValue;

  // Reset the prerequisites
  mPrerequisites.clear();
  pdelete(mpExpression);

  bool success = true;

  if (pSpecies->hasNoise())
    {
      /*
        mRate = mpModel->getQuantity2NumberFactor() *
          mpCompartment->getValue() * mpNoiseExpression->calcValue();
       */

      std::string Infix;
      Infix = pointerToString(mpQuantity2NumberValue);
      Infix += "*" + pointerToString(mpCompartmentValue);
      Infix += "*(" + pSpecies->getNoiseExpression() + ")";

      CExpression E("ExtensiveNoiseExpression", &container);
      success &= E.setInfix(Infix);
      success &= E.compile();

      mpExpression = new CMathExpression(E, container, !mIsInitialValue);
    }
  else
    {
      *mpValue = 0.0;
    }

  compileExpression();

  return success;
}

bool CMathObject::createExtensiveReactionNoiseExpression(const CMetab * pSpecies,
    CMathContainer & container)
{
  // The default value is NaN
  *mpValue = InvalidValue;

  // Reset the prerequisites
  mPrerequisites.clear();
  pdelete(mpExpression);

  bool success = true;

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(16);

  bool First = true;
  std::vector< std::pair < C_FLOAT64, const C_FLOAT64 *> > CalculationVector;
  const std::set< std::pair< const CReaction *, C_FLOAT64 > > & Stoichiometry = container.getModel().getReactionsPerSpecies(pSpecies);

  std::set< std::pair< const CReaction *, C_FLOAT64 > >::const_iterator itStoi = Stoichiometry.begin();
  std::set< std::pair< const CReaction *, C_FLOAT64 > >::const_iterator endStoi = Stoichiometry.end();

  for (; itStoi != endStoi; ++itStoi)
    {
      if (!itStoi->first->hasNoise()) continue;

      const C_FLOAT64 & Multiplicity = itStoi->second;

      if (First || Multiplicity < 0.0)
        {
          if (std::isnan(Multiplicity))
            {
              Infix << "nan";
            }
          else if (Multiplicity == std::numeric_limits< C_FLOAT64 >::infinity())
            {
              Infix << "infinity";
            }
          else if (Multiplicity == -std::numeric_limits< C_FLOAT64 >::infinity())
            {
              Infix << "-infinity";
            }
          else
            {
              Infix << Multiplicity;
            }
        }
      else
        {
          if (std::isnan(Multiplicity))
            {
              Infix << "+nan";
            }
          else if (Multiplicity == std::numeric_limits< C_FLOAT64 >::infinity())
            {
              Infix << "+infinity";
            }
          else
            {
              Infix << "+" << Multiplicity;
            }
        }

      First = false;

      Infix << "*";
      Infix << pointerToString(container.getMathObject(itStoi->first->getParticleNoiseReference())->getValuePointer());

      const C_FLOAT64 * pNoise = static_cast< const C_FLOAT64 * >(container.getMathObject(itStoi->first->getParticleNoiseReference())->getValuePointer());

      if (mIsInitialValue)
        {
          pNoise = container.getInitialValuePointer(pNoise);
        }

      CalculationVector.push_back(std::make_pair(Multiplicity, pNoise));
    }

  if (!First)
    {
      mpExpression = new CMathExpression("ExtensiveReactionNoiseExpression", container);
      success &= mpExpression->setInfix(Infix.str());
      success &= mpExpression->compile();
      compileExpression();

      mStoichiometryVector.resize(CalculationVector.size());
      mRateVector.resize(CalculationVector.size());
      std::vector< std::pair < C_FLOAT64, const C_FLOAT64 *> >::const_iterator itPair = CalculationVector.begin();
      std::vector< std::pair < C_FLOAT64, const C_FLOAT64 *> >::const_iterator endPair = CalculationVector.end();
      C_FLOAT64 * pStoi = mStoichiometryVector.begin();
      const C_FLOAT64 **ppRate = mRateVector.begin();

      for (; itPair != endPair; ++itPair, ++pStoi, ++ppRate)
        {
          *pStoi = itPair->first;
          *ppRate = itPair->second;
        }

      mpCalculate = &CMathObject::calculateExtensiveReactionRate;
    }
  else
    {
      *mpValue = 0.0;
    }

  return success;
}

std::ostream &operator<<(std::ostream &os, const CMathObject & o)
{
  if (o.mpDataObject != NULL)
    {
      os << o.mpDataObject->getCN() << std::endl;
    }
  else
    {
      os << "Data Object = NULL" << std::endl;
    }

  os << "  Pointer:                " << &o << std::endl;
  os << "  Value Type:             ";

  switch (o.mValueType)
    {
      case CMath::ValueType::Undefined:
        os << "ValueTypeUndefined" << std::endl;
        break;

      case CMath::ValueType::Value:
        os << "Value" << std::endl;
        break;

      case CMath::ValueType::Rate:
        os << "ValueRate" << std::endl;
        break;

      case CMath::ValueType::ParticleFlux:
        os << "ParticleFlux" << std::endl;
        break;

      case CMath::ValueType::Flux:
        os << "Flux" << std::endl;
        break;

      case CMath::ValueType::Propensity:
        os << "Propensity" << std::endl;
        break;

      case CMath::ValueType::Noise:
        os << "Noise" << std::endl;
        break;

      case CMath::ValueType::ParticleNoise:
        os << "ParticleNoise" << std::endl;
        break;

      case CMath::ValueType::TotalMass:
        os << "TotalMass" << std::endl;
        break;

      case CMath::ValueType::DependentMass:
        os << "DependentMass" << std::endl;
        break;

      case CMath::ValueType::Discontinuous:
        os << "Discontinuous" << std::endl;
        break;

      case CMath::ValueType::EventDelay:
        os << "EventDelay" << std::endl;
        break;

      case CMath::ValueType::EventPriority:
        os << "EventPriority" << std::endl;
        break;

      case CMath::ValueType::EventAssignment:
        os << "EventAssignment" << std::endl;
        break;

      case CMath::ValueType::EventTrigger:
        os << "EventTrigger" << std::endl;
        break;

      case CMath::ValueType::EventRoot:
        os << "EventRoot" << std::endl;
        break;

      case CMath::ValueType::EventRootState:
        os << "EventRootState" << std::endl;
        break;

      case CMath::ValueType::DelayValue:
        os << "DelayValue" << std::endl;
        break;

      case CMath::ValueType::DelayLag:
        os << "DelayLag" << std::endl;
        break;

      case CMath::ValueType::TransitionTime:
        os << "TransitionTime" << std::endl;
        break;

      case CMath::ValueType::__SIZE:
        os << "***ENUM RANGE" << std::endl;
        break;
    }

  os << "  Simulation Type:        ";

  switch (o.mSimulationType)
    {
      case CMath::SimulationType::Undefined:
        os << "SimulationTypeUndefined" << std::endl;
        break;

      case CMath::SimulationType::Fixed:
        os << "Fixed" << std::endl;
        break;

      case CMath::SimulationType::EventTarget:
        os << "EventTarget" << std::endl;
        break;

      case CMath::SimulationType::Time:
        os << "Time" << std::endl;
        break;

      case CMath::SimulationType::ODE:
        os << "ODE" << std::endl;
        break;

      case CMath::SimulationType::Independent:
        os << "Independent" << std::endl;
        break;

      case CMath::SimulationType::Dependent:
        os << "Dependent" << std::endl;
        break;

      case CMath::SimulationType::Assignment:
        os << "Assignment" << std::endl;
        break;

      case CMath::SimulationType::Conversion:
        os << "Conversion" << std::endl;
        break;

      case CMath::SimulationType::__SIZE:
        os << "***ENUM RANGE" << std::endl;
        break;
    };

  os << "  Entity Type:            ";

  switch (o.mEntityType)
    {
      case CMath::EntityType::Undefined:
        os << "EntityTypeUndefined" << std::endl;
        break;

      case CMath::EntityType::Model:
        os << "Model" << std::endl;
        break;

      case CMath::EntityType::Analysis:
        os << "Analysis" << std::endl;
        break;

      case CMath::EntityType::GlobalQuantity:
        os << "GlobalQuantity" << std::endl;
        break;

      case CMath::EntityType::Compartment:
        os << "Compartment" << std::endl;
        break;

      case CMath::EntityType::Species:
        os << "Species" << std::endl;
        break;

      case CMath::EntityType::LocalReactionParameter:
        os << "LocalReactionParameter" << std::endl;
        break;

      case CMath::EntityType::StoichiometricCoefficients:
        os << "StoichiometricCoefficients" << std::endl;
        break;

      case CMath::EntityType::Reaction:
        os << "Reaction" << std::endl;
        break;

      case CMath::EntityType::Moiety:
        os << "Moiety" << std::endl;
        break;

      case CMath::EntityType::Event:
        os << "Event" << std::endl;
        break;

      case CMath::EntityType::Delay:
        os << "Delay" << std::endl;
        break;

      case CMath::EntityType::__SIZE:
        os << "***ENUM RANGE" << std::endl;
        break;
    };

  os << "  Is Intensive Property:  " << (o.mIsIntensiveProperty ? "true" : "false") << std::endl;

  os << "  Is Initial Value:       " << (o.mIsInitialValue ? "true" : "false") << std::endl;

  os << "  Corresponding Property: ";

  if (o.mpCorrespondingProperty != NULL)
    {
      os << o.mpCorrespondingProperty->getCN() << std::endl;
    }
  else
    {
      os << "NULL" << std::endl;
    }

  os << "  Value:                  " << *o.mpValue << " (" << o.mpValue << ")" << std::endl;

  os << "  Expression:             ";

  if (o.mpExpression != NULL)
    {
      os << o.mpExpression->getRoot()->buildInfix() << std::endl;
    }
  else
    {
      os << "NULL" << std::endl;
    }

  // CObjectInterface::ObjectSet mPrerequisites;

  return os;
}

const CValidity & CMathObject::getValidity() const
{
  return mValidity;
}

// virtual
void CMathObject::validityChanged(const CValidity & changedValidity)
{
  if (mpDataObject != NULL)
    {
      const_cast< CDataObject * >(mpDataObject)->validityChanged(changedValidity);
    }
}
