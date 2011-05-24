// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathObject.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/24 16:32:32 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMathObject.h"
#include "CMathExpression.h"
#include "CMathContainer.h"

#include "model/CMetab.h"
#include "model/CCompartment.h"
#include "model/CModel.h"
#include "function/CExpression.h"

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
    mpIntensiveProperty(NULL),
    mpDataObject(NULL)
{}

// virtual
CMathObject::~CMathObject()
{
  pdelete(mpExpression);
}

// virtual
CCopasiObjectName CMathObject::getCN() const
{
  if (mpDataObject == NULL)
    return CCopasiObjectName("");

  return mpDataObject->getCN();
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

        if ((context & CMath::UpdateMoities) &&
            mValueType == CMath::TotalMass)
          {
            return true;
          }

        if ((context & CMath::UseMoities) &&
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

        if ((context & CMath::UseMoities) &&
            mSimulationType == CMath::Independent &&
            !mIsIntensiveProperty)
          {
            return true;
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
            if (mSimulationType == CMath::Assignment && !mIsInitialValue)
              return true;

            // If the concentration was changed in the context we need to recalculate.
            if (changedObjects.find(mpIntensiveProperty) != changedObjects.end())
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

  // For an extensive transient value of a dependent species we have 2
  // possible assignments depending on the context.
  //   1) Conversion from the intensive property
  //   2) Dependent mass off a moiety
  //
  // The solution is that the moiety automatically updates the value in conjunction
  // with the dependency graph omitting the value in the update sequence if the context
  // is CMath::UseMoities.
}

const CCopasiObject * CMathObject::getDataObject() const
{
  return mpDataObject;
}

const CMath::ValueType & CMathObject::getValueType() const
{
  return mValueType;
}

const CMath::EntityType & CMathObject::getEntityType() const
{
  return mEntityType;
}

const CMath::SimulationType & CMathObject::getSimulationType() const
{
  return mSimulationType;
}

const bool & CMathObject::isIntensiveProperty() const
{
  return mIsIntensiveProperty;
}

const bool & CMathObject::isInitialValue() const
{
  return mIsInitialValue;
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

      mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                            mpExpression->getPrerequisites().end());
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

bool CMathObject::compile(CMathContainer & container)
{
  std::cout << *this;

  bool success = true;

  // The default value is NaN
  *mpValue = InvalidValue;

  // Remove any existing expression
  if (mValueType != CMath::Discontinuous)
    {
      pdelete(mpExpression);
    }

  // Reset the prerequisites
  mPrerequisites.clear();

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

      case CMath::ValueRate:
        success = compileValueRate(container);
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

        if (mpExpression != NULL)
          {
            success &= mpExpression->compile();

            mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                                  mpExpression->getPrerequisites().end());
          }

        break;

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

  // std::cout << *this << std::endl;

  return success;
}

bool CMathObject::compileInitialValue(CMathContainer & container)
{
  bool success = true;

  const CModelEntity * pEntity = dynamic_cast< const CModelEntity * >(mpDataObject->getObjectParent());

  if (mIsIntensiveProperty)
    {
      // Only species have intensive properties.
      const CMetab * pSpecies = static_cast< const CMetab * >(pEntity);

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
            const CMetab * pSpecies = static_cast< const CMetab * >(pEntity);
            mpIntensiveProperty = container.getMathObject(pSpecies->getInitialConcentrationReference());
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

  if (mIsIntensiveProperty)
    {
      // Only species have intensive properties.
      const CMetab * pSpecies = static_cast< const CMetab * >(mpDataObject->getObjectParent());

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
      const CMetab * pSpecies = NULL;

      if (mEntityType == CMath::Species)
        {
          pSpecies = static_cast< const CMetab * >(mpDataObject->getObjectParent());
          mpIntensiveProperty = container.getMathObject(pSpecies->getConcentrationReference());
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

bool CMathObject::compileValueRate(CMathContainer & container)
{
  bool success = true;

  if (mIsIntensiveProperty)
    {
      // Only species have intensive properties.
      const CMetab * pSpecies = static_cast< const CMetab * >(mpDataObject->getObjectParent());

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
                const CMetab * pSpecies = static_cast< const CMetab * >(mpDataObject->getObjectParent());
                success &= createExtensiveODERateExpression(pSpecies, container);
              }
            else
              {
                const CModelEntity * pEntity = static_cast< const CModelEntity * >(mpDataObject->getObjectParent());
                success &= createConvertedExpression(pEntity->getExpressionPtr(), container);
              }

            break;

          case CMath::Independent:
          case CMath::Dependent:
          {
            const CMetab * pSpecies = static_cast< const CMetab * >(mpDataObject->getObjectParent());
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

bool CMathObject::compileFlux(CMathContainer & container)
{
  bool success = true;

  const CReaction * pReaction = static_cast< const CReaction * >(mpDataObject->getObjectParent());

  mpExpression = new CMathExpression(*pReaction->getFunction(),
                                     pReaction->getCallParameters(),
                                     container,
                                     !mIsInitialValue);

  return success;
}

bool CMathObject::compilePropensity(CMathContainer & container)
{
  bool success = true;

  const CReaction * pReaction = static_cast< const CReaction * >(mpDataObject->getObjectParent());


  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(16);

  // Propensity for reversible reactions must be NaN
  if (pReaction->isReversible())
    {
      Infix << "NAN";
    }
  else if (container.getModel().getModelType() == CModel::deterministic)
    {
      Infix << "<" << pReaction->getParticleFluxReference()->getCN() << ">";

      std::ostringstream Divisor;
      Divisor.imbue(std::locale::classic());
      Divisor.precision(16);

      const CCopasiVector<CChemEqElement> & Substrates = pReaction->getChemEq().getSubstrates();
      CCopasiVector< CChemEqElement >::const_iterator itSubstrate = Substrates.begin();
      CCopasiVector< CChemEqElement >::const_iterator endSubstrate = Substrates.end();
      bool first = true;

      for (; itSubstrate != endSubstrate; ++itSubstrate)
        {
          const std::string NumberCN = (*itSubstrate)->getMetabolite()->getValueReference()->getCN();
          C_FLOAT64 Multiplicity = (*itSubstrate)->getMultiplicity();

          Multiplicity -= 1.0; // Nothing to correct if the multiplicity is 1.

          if (Multiplicity > 2.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
            {
              if (!first)
                {
                  Divisor << "*";
                }

              first = false;
              Divisor << "<" << NumberCN << ">^" << Multiplicity;
            }
          else if (Multiplicity > 1.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
            {
              if (!first)
                {
                  Divisor << "*";
                }

              first = false;
              Divisor << "<" << NumberCN << ">";
            }

          while (Multiplicity > 1.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
            {
              Infix << "*(<" << NumberCN << ">-" << Multiplicity << ")";
              Multiplicity -= 1.0;
            }
        }

      if (Divisor.str() != "")
        {
          Infix << "/(" << Divisor.str() << ")";
        }
    }
  else
    {
      // Propensity is the same as the flux.
      Infix << "<" << pReaction->getParticleFluxReference()->getCN() << ">";
    }

  CExpression E("PropensityExpression", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container, !mIsInitialValue);
  mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                        mpExpression->getPrerequisites().end());

  return success;
}

bool CMathObject::compileTotalMass(CMathContainer & container)
{
  bool success = true;
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

      Infix << "*<";
      Infix << it->second->getValueReference()->getCN();
      Infix << ">";
    }

  CExpression E("TotalMass", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container, !mIsInitialValue);
  mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                        mpExpression->getPrerequisites().end());

  return success;
}

bool CMathObject::compileDependentMass(CMathContainer & container)
{
  bool success = true;
  const CMoiety * pMoiety = static_cast< const CMoiety *>(mpDataObject->getObjectParent());

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(16);

  Infix << "<" << pMoiety->getTotalNumberReference()->getCN() << ">";

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

      Infix << "*<";
      Infix << it->second->getValueReference()->getCN();
      Infix << ">";
    }

  CExpression E("DependentMass", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container, !mIsInitialValue);
  mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                        mpExpression->getPrerequisites().end());

  return success;
}

bool CMathObject::createConvertedExpression(const CExpression * pExpression,
    CMathContainer & container)
{
  assert(pExpression != NULL);

  bool success = true;

  mpExpression = new CMathExpression(*pExpression, container,
                                     !mIsInitialValue && mValueType != CMath::Discontinuous);
  mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                        mpExpression->getPrerequisites().end());

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
  Infix << "*<";
  Infix << pNumber->getCN();
  Infix << ">/<";
  Infix << pCompartment->getCN();
  Infix << ">";

  CExpression E("IntensiveValueExpression", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container, !mIsInitialValue);
  mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                        mpExpression->getPrerequisites().end());

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
  Infix << "*<";
  Infix << pDensity->getCN();
  Infix << ">*<";
  Infix << pCompartment->getCN();
  Infix << ">";

  CExpression E("ExtensiveValueExpression", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container, !mIsInitialValue);
  mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                        mpExpression->getPrerequisites().end());

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

  Infix << "(<";
  Infix << pSpecies->getRateReference()->getCN();
  Infix << ">*";
  Infix << container.getModel().getNumber2QuantityFactor();
  Infix << "-<";
  Infix << pSpecies->getCompartment()->getValueReference()->getCN();
  Infix << ">*<";
  Infix << pSpecies->getCompartment()->getRateReference()->getCN();
  Infix << ">)/<";
  Infix << pSpecies->getCompartment()->getValueReference()->getCN();
  Infix << ">";

  CExpression E("IntensiveRateExpression", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container, !mIsInitialValue);
  mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                        mpExpression->getPrerequisites().end());

  return success;
}

bool CMathObject::createExtensiveODERateExpression(const CMetab * pSpecies,
    CMathContainer & container)
{
  bool success = true;

  /*
    mRate = mpModel->getQuantity2NumberFactor() *
      mpCompartment->getValue() * mpExpression->calcValue() ;
   */

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(16);

  Infix << container.getModel().getQuantity2NumberFactor();
  Infix << "*<";
  Infix << pSpecies->getCompartment()->getValueReference()->getCN();
  Infix << ">*";
  Infix << pSpecies->getExpression();

  CExpression E("ExtensiveODERateExpression", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container, !mIsInitialValue);
  mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                        mpExpression->getPrerequisites().end());

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
              Infix << Multiplicity;
            }
          else
            {
              Infix << "+" << Multiplicity;
            }

          First = false;

          Infix << "*<";
          Infix << (*it)->getParticleFluxReference()->getCN();
          Infix << ">";
        }
    }

  CExpression E("ExtensiveReactionExpression", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container, !mIsInitialValue);
  mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                        mpExpression->getPrerequisites().end());

  return success;
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

  os << "  Value Type:            ";

  switch (o.mValueType)
    {
      case CMath::ValueTypeUndefined:
        os << "ValueTypeUndefined" << std::endl;
        break;

      case CMath::Value:
        os << "Value" << std::endl;
        break;

      case CMath::ValueRate:
        os << "ValueRate" << std::endl;
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

  if (o.mpIntensiveProperty != NULL)
    {
      os << o.mpIntensiveProperty->getCN() << std::endl;
    }
  else
    {
      os << "NULL" << std::endl;
    }

  os << "  Value:                 " << *o.mpValue << " (" << o.mpValue << ")" << std::endl;

  os << "  Expression:            ";

  if (o.mpExpression != NULL)
    {
      os << o.mpExpression->getRoot()->getInfix() << std::endl;
    }
  else
    {
      os << "NULL" << std::endl;
    }

  // CObjectInterface::ObjectSet mPrerequisites;

  return os;
}
