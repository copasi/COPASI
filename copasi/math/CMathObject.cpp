// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <cmath>

#include "copasi.h"

#include "CMathObject.h"
#include "CMathExpression.h"
#include "CMathContainer.h"

#include "model/CMetab.h"
#include "model/CCompartment.h"
#include "model/CModel.h"
#include "function/CExpression.h"
#include "utilities/utility.h"
// static
C_FLOAT64 CMathObject::InvalidValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

// static
void CMathObject::initialize(CMathObject *& pObject,
                             C_FLOAT64 *& pValue,
                             const CMath::ValueType & valueType,
                             const CMath::EntityType & entityType,
                             const CMath::SimulationType & simulationType,
                             const bool & isIntensiveProperty,
                             const bool & isInitialValue,
                             const CCopasiObject * pDataObject)
{
  pObject->mpValue = pValue;
  pObject->mValueType = valueType;
  pObject->mEntityType = entityType;
  pObject->mSimulationType = simulationType;
  pObject->mIsIntensiveProperty = isIntensiveProperty;
  pObject->mIsInitialValue = isInitialValue;
  pObject->mpDataObject = pDataObject;

  pObject->mpExpression = NULL;
  pObject->mpCorrespondingProperty = NULL;

  pObject++;
  pValue++;
}

CMathObject::CMathObject():
  CObjectInterface(),
  mpExpression(NULL),
  mpValue(&InvalidValue),
  mPrerequisites(),
  mValueType(CMath::ValueTypeUndefined),
  mEntityType(CMath::EntityTypeUndefined),
  mSimulationType(CMath::SimulationTypeUndefined),
  mIsIntensiveProperty(false),
  mIsInitialValue(false),
  mpCorrespondingProperty(NULL),
  mpDataObject(NULL)
{}

// virtual
CMathObject::~CMathObject()
{
  pdelete(mpExpression);
}

void CMathObject::copy(const CMathObject & src, CMathContainer & container, const size_t & valueOffset, const size_t & objectOffset)
{
  mpValue = (C_FLOAT64 *)((size_t) src.mpValue + valueOffset);
  mValueType = src.mValueType;
  mEntityType = src.mEntityType;
  mSimulationType = src.mSimulationType;
  mIsIntensiveProperty = src.mIsIntensiveProperty;
  mIsInitialValue = src.mIsInitialValue;
  mpDataObject = src.mpDataObject;

  if (src.mpCorrespondingProperty != NULL)
    {
      mpCorrespondingProperty = (CMathObject *)((size_t) src.mpCorrespondingProperty + objectOffset);
    }
  else
    {
      mpCorrespondingProperty = NULL;
    }

  if (src.mpExpression != NULL)
    {
      mpExpression = CMathExpression::copy(*src.mpExpression, container, valueOffset, objectOffset);
    }
  else
    {
      mpExpression = NULL;
    }

  ObjectSet::const_iterator it = src.getPrerequisites().begin();
  ObjectSet::const_iterator end = src.getPrerequisites().end();

  for (; it != end; ++it)
    {
      mPrerequisites.insert((CMathObject *)((size_t) *it + objectOffset));
    }

  // We do not need to calculate since the value has been copied.
}

void CMathObject::reallocate(CMathContainer & container, const size_t & valueOffset, const size_t & objectOffset)
{
  mpValue = (C_FLOAT64 *)((size_t) mpValue + valueOffset);

  if (mpCorrespondingProperty != NULL)
    {
      mpCorrespondingProperty = (CMathObject *)((size_t) mpCorrespondingProperty + objectOffset);
    }

  if (mpExpression != NULL)
    {
      mpExpression->reallocate(container, valueOffset, objectOffset);
    }

  ObjectSet OldPrerequisites = mPrerequisites;
  mPrerequisites.clear();

  ObjectSet::const_iterator it = OldPrerequisites.begin();
  ObjectSet::const_iterator end = OldPrerequisites.end();

  for (; it != end; ++it)
    {
      mPrerequisites.insert((CMathObject *)((size_t) *it + objectOffset));
    }

  // We do not need to calculate since the value has been copied during reallocation.
}

// virtual
CCopasiObjectName CMathObject::getCN() const
{
  if (mpDataObject == NULL)
    return CCopasiObjectName("");

  return mpDataObject->getCN();
}

std::string CMathObject::getObjectDisplayName(bool regular, bool richtext) const
{
  if (mpDataObject == NULL)
    {
      return "Math Container Internal Object";
    }

  return mpDataObject->getObjectDisplayName(regular, richtext);
}

//virtual
const CObjectInterface * CMathObject::getObject(const CCopasiObjectName & cn) const
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
    const CMath::SimulationContextFlag & context,
    const CObjectInterface::ObjectSet & changedObjects) const
{
  // This method should only be called for objects which are prerequisites.
  // We check for this only in debug mode.
  assert(mPrerequisites.find(pObject) != mPrerequisites.end());

  switch (mEntityType)
    {
      case CMath::Moiety:

        if ((context & CMath::UpdateMoieties) &&
            mValueType == CMath::TotalMass)
          {
            return true;
          }

        if ((context & CMath::UseMoieties) &&
            mValueType == CMath::DependentMass)
          {
            return true;
          }

        return false;
        break;

      case CMath::Species:

        // For species we need to account for the duality of the intensive and extensive value
        if (mValueType != CMath::Value)
          return true;

        if ((context & CMath::UseMoieties) &&
            mSimulationType == CMath::Dependent &&
            !mIsIntensiveProperty)
          {
            if (mpCorrespondingProperty != pObject)
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
            if (mSimulationType == CMath::Assignment)
              return true;

            // If the concentration was changed in the context we need to recalculate.
            if (changedObjects.find(mpCorrespondingProperty) != changedObjects.end())
              return true;

            // If the concentration is calculated by an assignment we need to recalculate.
            if (mpCorrespondingProperty->getSimulationType() == CMath::Assignment)
              return true;

            return false;
          }

        break;

      case CMath::Event:

        if ((context & CMath::EventHandling) &&
            mValueType == CMath::Discontinuous)
          {
            switch ((int) mpExpression->getRoot()->getType())
              {
                case(CEvaluationNode::CHOICE | CEvaluationNodeChoice::IF):
                {
                  const CMathObject * pMathObject = dynamic_cast< const CMathObject * >(pObject);

                  if (pMathObject != NULL &&
                      pMathObject->mValueType == CMath::EventTrigger)
                    {
                      return false;
                    }

                  return true;
                }
                break;

                case(CEvaluationNode::FUNCTION | CEvaluationNodeFunction::FLOOR):
                  return false;
                  break;

                case(CEvaluationNode::FUNCTION | CEvaluationNodeFunction::CEIL):
                  return false;
                  break;

                default:
                  return true;
              }
          }

        return true;
        break;

      case CMath::Delay:

        if (context & CMath::EventHandling)
          {
            return true;
          }

        return (mValueType == CMath::DelayLag);

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

// virtual
const CCopasiObject * CMathObject::getDataObject() const
{
  return mpDataObject;
}

// virtual
void * CMathObject::getValuePointer() const
{
  return mpValue;
}

void CMathObject::calculate()
{
  // This method should only be called if there is something to calculate, i.e.
  // mpExpression != NULL
  assert(mpExpression != NULL);

  *mpValue = mpExpression->value();

#ifdef COPASI_DEBUG

  // Check for NaN
  if (isnan(*mpValue))
    {
      std::cout << "NaN Value for: " << getCN() << std::endl;
    }

#endif // COPASI_DEBUG

  // For an extensive transient value of a dependent species we have 2
  // possible assignments depending on the context.
  //   1) Conversion from the intensive property
  //   2) Dependent mass off a moiety
  //
  // The solution is that the moiety automatically updates the value in conjunction
  // with the dependency graph omitting the value in the update sequence if the context
  // is CMath::UseMoieties.
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

  pdelete(mpExpression);
  mPrerequisites.clear();

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
      switch (CEvaluationNode::type((*it)->getType()))
        {
          case CEvaluationNode::DELAY:
          {
            CEvaluationNode * pValueExpression = static_cast< CEvaluationNode * >((*it)->getChild());
            std::string LagExpression = static_cast< CEvaluationNode * >(pValueExpression->getSibling())->buildInfix();

            CMath::DelayData::iterator found = Delays.find(LagExpression);

            if (found == Delays.end())
              {
                found = Delays.insert(std::make_pair(LagExpression, CMath::DelayValueData()));
              }

            found->second.insert(std::make_pair(pValueExpression->buildInfix(), std::make_pair(*it, const_cast< CMathObject * >(this))));
          }
          break;

          default:
            break;
        }
    }

  return;
}

bool CMathObject::compile(CMathContainer & container)
{

  bool success = true;

  switch (mValueType)
    {
      case CMath::ValueTypeUndefined:
        success = false;
        break;

      case CMath::Value:

        if (mIsInitialValue)
          {
            success = compileInitialValue(container);
          }
        else
          {
            success = compileValue(container);
          }

        break;

      case CMath::Rate:
        success = compileRate(container);
        break;

      case CMath::ParticleFlux:
        success = compileParticleFlux(container);
        break;

      case CMath::Flux:
        success = compileFlux(container);
        break;

      case CMath::Propensity:
        success = compilePropensity(container);
        break;

      case CMath::TotalMass:
        success = compileTotalMass(container);
        break;

      case CMath::DependentMass:
        success = compileDependentMass(container);
        break;

      case CMath::Discontinuous:
      case CMath::EventDelay:
      case CMath::EventPriority:
      case CMath::EventAssignment:
      case CMath::EventTrigger:
      case CMath::EventRoot:
      case CMath::EventRootState:
        // These objects are compiled through the event compile,
        // which is executed after the object compile. It is therefore
        // correct to leave the object in its default state.
        break;
    }

  return success;
}

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

  // Reset the prerequisites
  mPrerequisites.clear();

  const CModelEntity * pEntity = dynamic_cast< const CModelEntity * >(mpDataObject->getObjectParent());
  const CMetab * pSpecies = NULL;

  // Only species have corresponding properties (extensive vs intensive).
  if (mEntityType == CMath::Species)
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
    }

  if (mIsIntensiveProperty)
    {
      switch (mSimulationType)
        {
          case CMath::EventTarget:
          case CMath::Fixed:
          case CMath::ODE:
          case CMath::Independent:
          case CMath::Dependent:
          case CMath::Conversion:
            success &= createIntensiveValueExpression(pSpecies, container);
            break;

          case CMath::Assignment:
            // Extensive Property * Conversion / Compartment Size
            success &= createConvertedExpression(pSpecies->getInitialExpressionPtr(), container);

            break;

          case CMath::Time:
          case CMath::SimulationTypeUndefined:
            success = false;
            break;
        }
    }
  else
    {
      switch (mSimulationType)
        {
          case CMath::Fixed:
            break;

          case CMath::Assignment:
            success &= createConvertedExpression(pEntity->getInitialExpressionPtr(), container);
            break;

          case CMath::Conversion:
          {
            success &= createExtensiveValueExpression(pSpecies, container);
          }
          break;

          case CMath::SimulationTypeUndefined:
          case CMath::EventTarget:
          case CMath::Time:
          case CMath::ODE:
          case CMath::Independent:
          case CMath::Dependent:
            success = false;
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

  // Reset the prerequisites
  mPrerequisites.clear();

  const CModelEntity * pEntity = NULL;
  const CMetab * pSpecies = NULL;

  if (mpDataObject != NULL)
    {
      pEntity = dynamic_cast< const CModelEntity * >(mpDataObject->getObjectParent());
    }

  // Only species have corresponding properties (extensive vs intensive).
  if (mEntityType == CMath::Species)
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
    }

  if (mIsIntensiveProperty)
    {
      switch (mSimulationType)
        {
          case CMath::Assignment:
            success &= createConvertedExpression(pSpecies->getExpressionPtr(), container);
            break;

          case CMath::EventTarget:
          case CMath::Conversion:
            success &= createIntensiveValueExpression(pSpecies, container);
            break;

          case CMath::SimulationTypeUndefined:
          case CMath::Fixed:
          case CMath::Time:
          case CMath::ODE:
          case CMath::Independent:
          case CMath::Dependent:
            success = false;
            break;
        }
    }
  else
    {
      // Species need an additional conversion since the event targets the
      // intensive property.
      if (mEntityType == CMath::Species)
        {
          success &= createExtensiveValueExpression(pSpecies, container);
        }

      switch (mSimulationType)
        {
          case CMath::Fixed:
          case CMath::EventTarget:
          case CMath::Time:
          case CMath::ODE:
          case CMath::Independent:
          case CMath::Conversion:
            break;

          case CMath::Dependent:
          {
            // We need to add the dependent number of the moiety as a possible
            // prerequisite.
            const CMoiety * pMoiety = pSpecies->getMoiety();
            const CMathObject * pDependentNumber =
              container.getMathObject(pMoiety->getDependentNumberReference());

            mPrerequisites.insert(pDependentNumber);
          }
          break;

          case CMath::Assignment:
          {
            const CModelEntity * pEntity = static_cast< const CModelEntity * >(mpDataObject->getObjectParent());
            success &= createConvertedExpression(pEntity->getExpressionPtr(), container);
          }
          break;

          case CMath::SimulationTypeUndefined:
            success = false;
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

  // Reset the prerequisites
  mPrerequisites.clear();

  const CModelEntity * pEntity = NULL;
  const CMetab * pSpecies = NULL;

  if (mpDataObject != NULL)
    {
      pEntity = dynamic_cast< const CModelEntity * >(mpDataObject->getObjectParent());
    }

  // Only species have corresponding properties (extensive vs intensive).
  if (mEntityType == CMath::Species)
    {
      pSpecies = static_cast< const CMetab * >(pEntity);
    }

  if (mIsIntensiveProperty)
    {
      // Only species have intensive properties.
      switch (mSimulationType)
        {
          case CMath::Assignment:
            success &= createIntensiveRateExpression(pSpecies, container);
            break;

          case CMath::SimulationTypeUndefined:
          case CMath::Fixed:
          case CMath::EventTarget:
          case CMath::Time:
          case CMath::ODE:
          case CMath::Independent:
          case CMath::Dependent:
          case CMath::Conversion:
            success = false;
            break;
        }
    }
  else
    {

      switch (mSimulationType)
        {
          case CMath::Fixed:
            *mpValue = 0;
            break;

          case CMath::Time:
            *mpValue = 1;
            break;

          case CMath::ODE:

            if (mEntityType == CMath::Species)
              {
                success &= createExtensiveODERateExpression(pSpecies, container);
              }
            else
              {
                success &= createConvertedExpression(pEntity->getExpressionPtr(), container);
              }

            break;

          case CMath::Independent:
          case CMath::Dependent:
          {
            success &= createExtensiveReactionRateExpression(pSpecies, container);
          }
          break;

          case CMath::Assignment:
            // TODO When we have symbolic differentiation we can deal with this.
            break;

          case CMath::SimulationTypeUndefined:
          case CMath::EventTarget:
          case CMath::Conversion:
            success = false;
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

  // Reset the prerequisites
  mPrerequisites.clear();

  const CReaction * pReaction = static_cast< const CReaction * >(mpDataObject->getObjectParent());

  // We need to check whether this reaction is a single compartment reaction and scale
  // it if true.
  //   mParticleFlux = *mUnitScalingFactor * mFlux;
  //   mUnitScalingFactor = & pModel->getQuantity2NumberFactor();

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(16);

  Infix << container.getModel().getQuantity2NumberFactor();
  Infix << "*";
  Infix << pointerToString(container.getMathObject(pReaction->getFluxReference())->getValuePointer());

  CExpression E("ParticleExpression", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container, !mIsInitialValue);
  compileExpression();

  return success;
}

bool CMathObject::compileFlux(CMathContainer & container)
{
  bool success = true;

  // The default value is NaN
  *mpValue = InvalidValue;

  // Reset the prerequisites
  mPrerequisites.clear();

  const CReaction * pReaction = static_cast< const CReaction * >(mpDataObject->getObjectParent());

  // We need to check whether this reaction is a single compartment reaction and scale it if true.
  //   mFlux = *mScalingFactor * mpFunction->calcValue(mMap.getPointers());
  //   mScalingFactor = compartment volume or 1

  mpExpression = new CMathExpression(*pReaction->getFunction(),
                                     pReaction->getCallParameters(),
                                     container,
                                     !mIsInitialValue);

  std::set< const CCompartment * > Compartments = pReaction->getChemEq().getCompartments();

  if (Compartments.size() == 1)
    {
      CExpression Tmp(mpExpression->getObjectName(), &container);

      std::string Infix = pointerToString(container.getMathObject((*Compartments.begin())->getValueReference())->getValuePointer()) + "*(" + mpExpression->getInfix() + ")";
      success &= Tmp.setInfix(Infix);
      success &= Tmp.compile();

      pdelete(mpExpression);
      mpExpression = new CMathExpression(Tmp, container, false);
    }

  compileExpression();

  return success;
}

bool CMathObject::compilePropensity(CMathContainer & container)
{
  bool success = true;

  // The default value is NaN
  *mpValue = InvalidValue;

  // Reset the prerequisites
  mPrerequisites.clear();

  const CReaction * pReaction = static_cast< const CReaction * >(mpDataObject->getObjectParent());

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(16);

  // Propensity for reversible reactions must be NaN
  if (pReaction->isReversible())
    {
      Infix << "NAN";
    }
  else
    {
      // Propensity is the same as the flux.
      Infix << pointerToString(container.getMathObject(pReaction->getParticleFluxReference())->getValuePointer());

      // Apply correction for deterministic models
      if (container.getModel().getModelType() == CModel::deterministic)
        {
          std::ostringstream Divisor;
          Divisor.imbue(std::locale::classic());
          Divisor.precision(16);

          const CCopasiVector<CChemEqElement> & Substrates = pReaction->getChemEq().getSubstrates();
          CCopasiVector< CChemEqElement >::const_iterator itSubstrate = Substrates.begin();
          CCopasiVector< CChemEqElement >::const_iterator endSubstrate = Substrates.end();
          bool first = true;

          for (; itSubstrate != endSubstrate; ++itSubstrate)
            {
              const std::string NumberPointer = pointerToString(container.getMathObject((*itSubstrate)->getMetabolite()->getValueReference())->getValuePointer());

              C_FLOAT64 Multiplicity = (*itSubstrate)->getMultiplicity();

              Multiplicity -= 1.0; // Nothing to correct if the multiplicity is 1.

              if (Multiplicity > 2.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
                {
                  if (!first)
                    {
                      Divisor << "*";
                    }

                  first = false;
                  Divisor << NumberPointer << "^" << Multiplicity;
                }
              else if (Multiplicity > 1.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
                {
                  if (!first)
                    {
                      Divisor << "*";
                    }

                  first = false;
                  Divisor << NumberPointer;
                }

              while (Multiplicity > 1.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
                {
                  Infix << "*(" << NumberPointer << "-" << Multiplicity << ")";
                  Multiplicity -= 1.0;
                }
            }

          if (Divisor.str() != "")
            {
              Infix << "/(" << Divisor.str() << ")";
            }
        }
    }

  CExpression E("PropensityExpression", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container, !mIsInitialValue);
  compileExpression();

  return success;
}

bool CMathObject::compileTotalMass(CMathContainer & container)
{
  bool success = true;

  // The default value is NaN
  *mpValue = InvalidValue;

  // Reset the prerequisites
  mPrerequisites.clear();

  const CMoiety * pMoiety = static_cast< const CMoiety *>(mpDataObject->getObjectParent());

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(16);

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

      First = false;

      Infix << "*";
      Infix << pointerToString(container.getMathObject(it->second->getValueReference())->getValuePointer());
    }

  CExpression E("TotalMass", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container, !mIsInitialValue);
  compileExpression();

  return success;
}

bool CMathObject::compileDependentMass(CMathContainer & container)
{
  bool success = true;

  // The default value is NaN
  *mpValue = InvalidValue;

  // Reset the prerequisites
  mPrerequisites.clear();

  const CMoiety * pMoiety = static_cast< const CMoiety *>(mpDataObject->getObjectParent());

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(16);

  Infix << pointerToString(container.getMathObject(pMoiety->getTotalNumberReference())->getValuePointer());

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

      First = false;

      Infix << "*";
      Infix << pointerToString(container.getMathObject(it->second->getValueReference())->getValuePointer());
    }

  CExpression E("DependentMass", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container, !mIsInitialValue);
  compileExpression();

  return success;
}

void CMathObject::compileExpression()
{
  assert(mpExpression);

  if (mIsInitialValue)
    {
      mpExpression->convertToInitialExpression();
    }

  mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                        mpExpression->getPrerequisites().end());

  if (mPrerequisites.empty())
    {
      calculate();
    }
}

bool CMathObject::createConvertedExpression(const CExpression * pExpression,
    CMathContainer & container)
{
  assert(pExpression != NULL);

  bool success = true;

  bool ReplaceDiscontinousNodes =
    !mIsInitialValue &&
    mValueType != CMath::Discontinuous &&
    mValueType != CMath::EventAssignment &&
    mValueType != CMath::EventPriority &&
    mValueType != CMath::EventDelay;

  mpExpression = new CMathExpression(*pExpression, container, ReplaceDiscontinousNodes);
  compileExpression();

  return success;
}

bool CMathObject::createIntensiveValueExpression(const CMetab * pSpecies,
    CMathContainer & container)
{
  bool success = true;

  // mConc = *mpValue / mpCompartment->getValue() * mpModel->getNumber2QuantityFactor();
  CObjectInterface * pNumber = NULL;
  CObjectInterface * pCompartment = NULL;

  if (mIsInitialValue)
    {
      pNumber = pSpecies->getInitialValueReference();
      pCompartment = pSpecies->getCompartment()->getInitialValueReference();
    }
  else
    {
      pNumber = pSpecies->getValueReference();
      pCompartment = pSpecies->getCompartment()->getValueReference();
    }

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(16);

  Infix << container.getModel().getNumber2QuantityFactor();
  Infix << "*";
  Infix << pointerToString(container.getMathObject(pNumber)->getValuePointer());
  Infix << "/";
  Infix << pointerToString(container.getMathObject(pCompartment)->getValuePointer());;

  CExpression E("IntensiveValueExpression", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container, !mIsInitialValue);
  compileExpression();

  return success;
}

bool CMathObject::createExtensiveValueExpression(const CMetab * pSpecies,
    CMathContainer & container)
{
  bool success = true;

  // mConc * mpCompartment->getValue() * mpModel->getQuantity2NumberFactor();

  CObjectInterface * pDensity = NULL;
  CObjectInterface * pCompartment = NULL;

  if (mIsInitialValue)
    {
      pDensity = pSpecies->getInitialConcentrationReference();
      pCompartment = pSpecies->getCompartment()->getInitialValueReference();
    }
  else
    {
      pDensity = pSpecies->getConcentrationReference();
      pCompartment = pSpecies->getCompartment()->getValueReference();
    }

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(16);

  Infix << container.getModel().getQuantity2NumberFactor();
  Infix << "*";
  Infix << pointerToString(container.getMathObject(pDensity)->getValuePointer());
  Infix << "*";
  Infix << pointerToString(container.getMathObject(pCompartment)->getValuePointer());

  CExpression E("ExtensiveValueExpression", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container, !mIsInitialValue);
  compileExpression();

  return success;
}

bool CMathObject::createIntensiveRateExpression(const CMetab * pSpecies,
    CMathContainer & container)
{
  bool success = true;

  /*
    mConcRate =
      (mRate * mpModel->getNumber2QuantityFactor() - mConc * mpCompartment->getRate())
      / mpCompartment->getValue();
   */

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(16);

  Infix << "(";
  Infix << pointerToString(container.getMathObject(pSpecies->getRateReference())->getValuePointer());
  Infix << "*";
  Infix << container.getModel().getNumber2QuantityFactor();
  Infix << "-";
  Infix << pointerToString(container.getMathObject(pSpecies->getCompartment()->getValueReference())->getValuePointer());
  Infix << "*";
  Infix << pointerToString(container.getMathObject(pSpecies->getCompartment()->getRateReference())->getValuePointer());
  Infix << ")/";
  Infix << pointerToString(container.getMathObject(pSpecies->getCompartment()->getValueReference())->getValuePointer());

  CExpression E("IntensiveRateExpression", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container, !mIsInitialValue);
  compileExpression();

  return success;
}

bool CMathObject::createExtensiveODERateExpression(const CMetab * pSpecies,
    CMathContainer & container)
{
  bool success = true;

  /*
    mRate = mpModel->getQuantity2NumberFactor() *
      mpCompartment->getValue() * mpExpression->calcValue();
   */

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(16);

  Infix << container.getModel().getQuantity2NumberFactor();
  Infix << "*";
  Infix << pointerToString(container.getMathObject(pSpecies->getCompartment()->getValueReference())->getValuePointer());
  Infix << "*(";
  Infix << pSpecies->getExpression();
  Infix << ")";

  CExpression E("ExtensiveODERateExpression", &container);

  success &= E.setInfix(Infix.str());

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
  Infix.precision(16);

  std::string Key = pSpecies->getKey();
  bool First = true;

  CCopasiVectorN< CReaction >::const_iterator it = container.getModel().getReactions().begin();
  CCopasiVectorN< CReaction >::const_iterator end = container.getModel().getReactions().end();

  for (; it != end; ++it)
    {
      const CCopasiVector< CChemEqElement > &Balances =
        (*it)->getChemEq().getBalances();
      CCopasiVector< CChemEqElement >::const_iterator itChem = Balances.begin();
      CCopasiVector< CChemEqElement >::const_iterator endChem = Balances.end();

      for (; itChem != endChem; ++itChem)
        if ((*itChem)->getMetaboliteKey() == Key)
          break;

      if (itChem != endChem)
        {
          const C_FLOAT64 & Multiplicity = (*itChem)->getMultiplicity();

          if (First || Multiplicity < 0.0)
            {
              if (Multiplicity == std::numeric_limits< C_FLOAT64 >::infinity())
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
              if (Multiplicity == std::numeric_limits< C_FLOAT64 >::infinity())
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
          Infix << pointerToString(container.getMathObject((*it)->getParticleFluxReference())->getValuePointer());
        }
    }

  CExpression E("ExtensiveReactionExpression", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container, !mIsInitialValue);
  compileExpression();

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

  os << "  Pointer:               " << &o << std::endl;
  os << "  Value Type:            ";

  switch (o.mValueType)
    {
      case CMath::ValueTypeUndefined:
        os << "ValueTypeUndefined" << std::endl;
        break;

      case CMath::Value:
        os << "Value" << std::endl;
        break;

      case CMath::Rate:
        os << "ValueRate" << std::endl;
        break;

      case CMath::ParticleFlux:
        os << "ParticleFlux" << std::endl;
        break;

      case CMath::Flux:
        os << "Flux" << std::endl;
        break;

      case CMath::Propensity:
        os << "Propensity" << std::endl;
        break;

      case CMath::TotalMass:
        os << "TotalMass" << std::endl;
        break;

      case CMath::DependentMass:
        os << "DependentMass" << std::endl;
        break;

      case CMath::Discontinuous:
        os << "Discontinuous" << std::endl;
        break;

      case CMath::EventDelay:
        os << "EventDelay" << std::endl;
        break;

      case CMath::EventPriority:
        os << "EventPriority" << std::endl;
        break;

      case CMath::EventAssignment:
        os << "EventAssignment" << std::endl;
        break;

      case CMath::EventTrigger:
        os << "EventTrigger" << std::endl;
        break;

      case CMath::EventRoot:
        os << "EventRoot" << std::endl;
        break;

      case CMath::EventRootState:
        os << "EventRootState" << std::endl;
        break;
    }

  os << "  Simulation Type:       ";

  switch (o.mSimulationType)
    {
      case CMath::SimulationTypeUndefined:
        os << "SimulationTypeUndefined" << std::endl;
        break;

      case CMath::Fixed:
        os << "Fixed" << std::endl;
        break;

      case CMath::EventTarget:
        os << "EventTarget" << std::endl;
        break;

      case CMath::Time:
        os << "Time" << std::endl;
        break;

      case CMath::ODE:
        os << "ODE" << std::endl;
        break;

      case CMath::Independent:
        os << "Independent" << std::endl;
        break;

      case CMath::Dependent:
        os << "Dependent" << std::endl;
        break;

      case CMath::Assignment:
        os << "Assignment" << std::endl;
        break;

      case CMath::Conversion:
        os << "Conversion" << std::endl;
        break;
    };

  os << "  Entity Type:           ";

  switch (o.mEntityType)
    {
      case CMath::EntityTypeUndefined:
        os << "EntityTypeUndefined" << std::endl;
        break;

      case CMath::Model:
        os << "Model" << std::endl;
        break;

      case CMath::Analysis:
        os << "Analysis" << std::endl;
        break;

      case CMath::GlobalQuantity:
        os << "GlobalQuantity" << std::endl;
        break;

      case CMath::Compartment:
        os << "Compartment" << std::endl;
        break;

      case CMath::Species:
        os << "Species" << std::endl;
        break;

      case CMath::LocalReactionParameter:
        os << "LocalReactionParameter" << std::endl;
        break;

      case CMath::StoichiometricCoefficients:
        os << "StoichiometricCoefficients" << std::endl;
        break;

      case CMath::Reaction:
        os << "Reaction" << std::endl;
        break;

      case CMath::Moiety:
        os << "Moiety" << std::endl;
        break;

      case CMath::Event:
        os << "Event" << std::endl;
        break;
    };

  os << "  Is Intensive Property: " << (o.mIsIntensiveProperty ? "true" : "false") << std::endl;

  os << "  Is Initial Value:      " << (o.mIsInitialValue ? "true" : "false") << std::endl;

  os << "  Intensive Property:    ";

  if (o.mpCorrespondingProperty != NULL)
    {
      os << o.mpCorrespondingProperty->getCN() << std::endl;
    }
  else
    {
      os << "NULL" << std::endl;
    }

  os << "  Value:                 " << *o.mpValue << " (" << o.mpValue << ")" << std::endl;

  os << "  Expression:            ";

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
