// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathObject.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/22 14:00:43 $
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
void CMathObject::initializeMathObject(CMathObject *& pObject,
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
            if (mSimulationType == CMath::Assignment)
              return true;

            // If the concentration was changed in the context we need to recalculate.
            if (changedObjects.find(mpIntensiveProperty) != changedObjects.end())
              return true;

            return false;

          }

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
}

const CCopasiObject * CMathObject::getDataObject() const
{
  return mpDataObject;
}

bool CMathObject::compile(const CMathContainer & container)
{
  bool success = true;

  // The default value is NaN
  *mpValue = InvalidValue;

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
        // success = compilePropensity(container);
        break;

      case CMath::TotalMass:
        // success = compileTotalMass(container);
        break;

      case CMath::DependentMass:
        // success = compileDependentMass(container);
        break;
    }

  return success;
}

bool CMathObject::compileInitialValue(const CMathContainer & container)
{
  bool success = true;

  const CModelEntity * pEntity = static_cast< const CModelEntity * >(mpDataObject->getObjectParent());
  const CExpression * pExpression = pEntity->getInitialExpressionPtr();
  bool HaveInitialExpression = pExpression != NULL && pExpression->getInfix() != "";

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

            // Extensive Property * Conversion / Compartment Size
            if (HaveInitialExpression)
              {
                success &= createConvertedExpression(pSpecies->getInitialExpressionPtr(), container);
              }
            else
              {
                success &= createIntensiveValueExpression(pSpecies, container);
              }

            break;

          case CMath::Assignment:
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
          case CMath::EventTarget:
          case CMath::Time:
          case CMath::ODE:

            if (mEntityType == CMath::Species)
              {
                const CMetab * pSpecies = static_cast< const CMetab * >(pEntity);
                success &= createExtensiveValueExpression(pSpecies, container);
              }
            else if (HaveInitialExpression)
              {
                success &= createConvertedExpression(pEntity->getInitialExpressionPtr(), container);
              }

            break;

          case CMath::Independent:
          case CMath::Dependent:
          {
            const CMetab * pSpecies = static_cast< const CMetab * >(pEntity);
            success &= createExtensiveValueExpression(pSpecies, container);
          }
          break;

          case CMath::Assignment:

            if (mEntityType == CMath::Species)
              {
                const CMetab * pSpecies = static_cast< const CMetab * >(pEntity);
                success &= createExtensiveValueExpression(pSpecies, container);
              }
            else
              {
                success &= createConvertedExpression(pEntity->getInitialExpressionPtr(), container);
              }

            break;

          case CMath::SimulationTypeUndefined:
            success = false;
            break;
        }
    }

  return success;
}

bool CMathObject::compileValue(const CMathContainer & container)
{
  bool success = true;

  if (mIsIntensiveProperty)
    {
      // Only species have intensive properties.
      const CMetab * pSpecies = static_cast< const CMetab * >(mpDataObject->getObjectParent());

      switch (mSimulationType)
        {
          case CMath::EventTarget:
          case CMath::Fixed:
          case CMath::ODE:
          case CMath::Independent:
          case CMath::Dependent:
            // If the object does not already have an assignment we need to create one:
            // Extensive Property * Conversion / Compartment Size
            success &= createIntensiveValueExpression(pSpecies, container);
            break;

          case CMath::Assignment:
            success &= createConvertedExpression(pSpecies->getExpressionPtr(), container);
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
          case CMath::EventTarget:
          case CMath::Time:
          case CMath::ODE:

            if (mEntityType == CMath::Species)
              {
                const CMetab * pSpecies = static_cast< const CMetab * >(mpDataObject->getObjectParent());
                success &= createExtensiveValueExpression(pSpecies, container);
              }

            break;

          case CMath::Independent:
          {
            const CMetab * pSpecies = static_cast< const CMetab * >(mpDataObject->getObjectParent());
            success &= createExtensiveValueExpression(pSpecies, container);
          }
          break;

          case CMath::Dependent:
          {
            const CMetab * pSpecies = static_cast< const CMetab * >(mpDataObject->getObjectParent());
            success &= createExtensiveValueExpression(pSpecies, container);

            // We need to add the dependent number of the moiety as a possible
            // prerequisite.
            const CMoiety * pMoiety = pSpecies->getMoiety();
            const CMathObject * pDependentNumber =
              container.getMathObject(pMoiety->getDependentNumberReference());

            mPrerequisites.insert(pDependentNumber);
          }
          break;

          case CMath::Assignment:

            if (mEntityType == CMath::Species)
              {
                const CMetab * pSpecies =
                  static_cast< const CMetab * >(mpDataObject->getObjectParent());
                success &= createExtensiveValueExpression(pSpecies, container);
              }
            else
              {
                const CModelEntity * pEntity =
                  static_cast< const CModelEntity * >(mpDataObject->getObjectParent());
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

bool CMathObject::compileValueRate(const CMathContainer & container)
{
  bool success = true;

  const CModelEntity * pEntity = static_cast< const CModelEntity * >(mpDataObject->getObjectParent());

  if (mIsIntensiveProperty)
    {
      // Only species have intensive properties.
      const CMetab * pSpecies = static_cast< const CMetab * >(pEntity);

      switch (mSimulationType)
        {
          case CMath::EventTarget:
          case CMath::Fixed:
            *mpValue = 0;
            break;

          case CMath::ODE:
          case CMath::Independent:
          case CMath::Dependent:
            success &= createIntensiveRateExpression(pSpecies, container);
            break;

          case CMath::Assignment:
            // TODO When we have symbolic differentiation we can deal with this.
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
          case CMath::EventTarget:
            *mpValue = 0;
            break;

          case CMath::Time:
            *mpValue = 1;
            break;

          case CMath::ODE:

            if (mEntityType == CMath::Species)
              {
                const CMetab * pSpecies = static_cast< const CMetab * >(pEntity);
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
            const CMetab * pSpecies = static_cast< const CMetab * >(mpDataObject->getObjectParent());
            success &= createExtensiveReactionRateExpression(pSpecies, container);
          }
          break;

          case CMath::Assignment:
            // TODO When we have symbolic differentiation we can deal with this.
            break;

          case CMath::SimulationTypeUndefined:
            success = false;
            break;
        }
    }

  return success;
}

bool CMathObject::compileFlux(const CMathContainer & container)
{
  bool success = true;

  CReaction * pReaction = static_cast< const CReaction * >(mpDataObject->getObjectParent());

  mpExpression = new CMathExpression(*pReaction->getFunction(),
                                     pReaction->getCallParameters(),
                                     container);

  return success;
}

bool CMathObject::compilePropensity(const CMathContainer & container)
{
  bool success = true;

  CReaction * pReaction = static_cast< const CReaction * >(mpDataObject->getObjectParent());

  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(16);


  if (container.getModel().getModelType() == CModel::deterministic)
    {
      // We need to apply the stochastic correction.
      std::ostringstream Condition;
      Condition.imbue(std::locale::classic());
      Condition.precision(16);

      std::ostringstream Multiplier;
      Multiplier.imbue(std::locale::classic());
      Multiplier.precision(16);
      Multiplier << "<" << pReaction->getParticleFluxReference()->getCN() << ">";

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

          if (!first)
            {
              Condition << "&&";
              Divisor << "*";
            }

          first = false;

          Condition << "fabs(<" << NumberCN << ">-" << Multiplicity << ")>";
          Condition << 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon();

          Multiplicity -= 1.0; // Nothing to correct if the multiplicity is 1.

          if (fabs(Multiplicity - 1.0) > 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
            {
              Divisor << "<" << NumberCN << ">^" << Multiplicity;
            }
          else if (fabs(Multiplicity) > 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
            {
              Divisor << "<" << NumberCN << ">";
            }

          while (fabs(Multiplicity) > 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
            {
              Multiplier << "*(<" << NumberCN << ">-" << Multiplicity << ")";
              Multiplicity -= 1.0;
            }
        }

      Infix << "if(";
      Infix << Condition.str();
      Infix << ",";
      Infix << Multiplier.str() << "/(" << Divisor.str() << ")";
      Infix << ",0.0)";
    }
  else
    {
      // Propensity is the same as the flux.
      Infix << "<" << pReaction->getParticleFluxReference()->getCN() << ">";
    }

  CExpression E("PropensityExpression", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container);
  mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                        mpExpression->getPrerequisites().end());

  return success;
}

bool CMathObject::compileTotalMass(const CMathContainer & container)
{
  bool success = true;

  return success;
}

bool CMathObject::compileDependentMass(const CMathContainer & container)
{
  bool success = true;

  return success;
}

bool CMathObject::createConvertedExpression(const CExpression * pExpression,
    const CMathContainer & container)
{
  assert(pExpression != NULL);

  bool success = true;

  mpExpression = new CMathExpression(*pExpression, container);
  mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                        mpExpression->getPrerequisites().end());

  return success;
}

bool CMathObject::createIntensiveValueExpression(const CMetab * pSpecies,
    const CMathContainer & container)
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

  mpExpression = new CMathExpression(E, container);
  mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                        mpExpression->getPrerequisites().end());

  return success;
}

bool CMathObject::createExtensiveValueExpression(const CMetab * pSpecies,
    const CMathContainer & container)
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

  mpExpression = new CMathExpression(E, container);
  mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                        mpExpression->getPrerequisites().end());

  return success;
}

bool CMathObject::createIntensiveRateExpression(const CMetab * pSpecies,
    const CMathContainer & container)
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
  Infix << ">/<";
  Infix << pSpecies->getCompartment()->getValueReference()->getCN();
  Infix << ">";

  CExpression E("IntensiveRateExpression", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container);
  mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                        mpExpression->getPrerequisites().end());

  return success;
}

bool CMathObject::createExtensiveODERateExpression(const CMetab * pSpecies,
    const CMathContainer & container)
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

  mpExpression = new CMathExpression(E, container);
  mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                        mpExpression->getPrerequisites().end());

  return success;
}

bool CMathObject::createExtensiveReactionRateExpression(const CMetab * pSpecies,
    const CMathContainer & container)
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

          Infix << "*<";
          Infix << (*it)->getParticleFluxReference();
          Infix << ">";
        }
    }

  CExpression E("ExtensiveReactionExpression", &container);

  success &= E.setInfix(Infix.str());

  mpExpression = new CMathExpression(E, container);
  mPrerequisites.insert(mpExpression->getPrerequisites().begin(),
                        mpExpression->getPrerequisites().end());

  return success;
  return success;
}
