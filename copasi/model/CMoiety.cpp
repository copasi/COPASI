// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <stdio.h>
#include <sstream>

#include "copasi.h"
#include "CMoiety.h"
#include "CModel.h"
#include "CCompartment.h"
#include "CMetabNameInterface.h"

#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"//By G
#include "function/CExpression.h"
#include "utilities/CCopasiMessage.h"
#include "utilities/CReadConfig.h"
#include "utilities/CCopasiVector.h"
#include "utilities/utility.h"
#include "copasi/report/CCopasiRootContainer.h"

// static
const C_FLOAT64 CMoiety::DefaultFactor(1.0);

CMoiety::CMoiety(const std::string & name,
                 const CCopasiContainer * pParent):
  CCopasiContainer(name, pParent, "Moiety"),
  mKey(CCopasiRootContainer::getKeyFactory()->add("Moiety", this)), //By G
  mNumber(0),
  mINumber(0),
  mIAmount(0),
  mEquation(),
  mpINumberReference(NULL),
  mpNumberReference(NULL),
  mpDNumberReference(NULL),
  mpConversionFactor(&CMoiety::DefaultFactor)
{
  initObjects();
  CONSTRUCTOR_TRACE;
}

CMoiety::CMoiety(const CMoiety & src,
                 const CCopasiContainer * pParent):
  CCopasiContainer(src, pParent),
  mKey(CCopasiRootContainer::getKeyFactory()->add("Moiety", this)), //By G
  mNumber(src.mNumber),
  mINumber(src.mINumber),
  mIAmount(src.mIAmount),
  mEquation(src.mEquation),
  mpINumberReference(NULL),
  mpNumberReference(NULL),
  mpDNumberReference(NULL),
  mpConversionFactor(src.mpConversionFactor)
{
  initObjects();
  CONSTRUCTOR_TRACE;
}

CMoiety::~CMoiety()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
  DESTRUCTOR_TRACE;
}

void CMoiety::initObjects()
{
  setRefresh(this, &CMoiety::refreshDependentNumber);

  mpINumberReference = new CTotalNumberReference("InitialValue", this, mINumber);
  mpINumberReference->setRefresh(this, &CMoiety::refreshInitialValue);

  mpNumberReference = new CTotalNumberReference("Value", this, mNumber);
  mpNumberReference->setRefresh(this, &CMoiety::refreshValue);

  mpDNumberReference = new CDependentNumberReference("DependentValue", this, mNumber);
  mpDNumberReference->addDirectDependency(this);

  CCopasiObject * pObject = addObjectReference("Amount", mIAmount, CCopasiObject::ValueDbl);
  pObject->setRefresh(this, &CMoiety::refreshAmount);
  pObject->addDirectDependency(mpNumberReference);

  return;
}

void CMoiety::add(C_FLOAT64 value, CMetab * pMetabolite)
{
  if (!mEquation.size())
    pMetabolite->setDependentOn(this);
  else
    addDirectDependency(pMetabolite->mpValueReference);

  mpINumberReference->addDirectDependency(pMetabolite->mpIValueReference);
  mpNumberReference->addDirectDependency(pMetabolite->mpValueReference);

  std::pair<C_FLOAT64, CMetab *> element;

  element.first = value;
  element.second = pMetabolite;

  mEquation.push_back(element);
}

void CMoiety::cleanup()
{
  clearDirectDependencies();
  mEquation.clear();
  mpINumberReference->clearDirectDependencies();
  mpNumberReference->clearDirectDependencies();
}

void CMoiety::refreshDependentNumber()
{
  mNumber = mINumber;

  std::vector< std::pair< C_FLOAT64, CMetab * > >::iterator it = mEquation.begin() + 1;
  std::vector< std::pair< C_FLOAT64, CMetab * > >::iterator end = mEquation.end();

  for (; it != end; ++it)
    mNumber -= it->first * it->second->getValue();

  // It is save to update the particle number of the dependent species here.
  // We are mimicking the behavior of the new math container by doing it.
  mEquation.begin()->second->setValue(mNumber);

  return;
}

const C_FLOAT64 & CMoiety::dependentNumber()
{
  refreshDependentNumber();
  return mNumber;
}

const C_FLOAT64 & CMoiety::getDependentNumber() const
{return mNumber;}

CCopasiObject * CMoiety::getTotalNumberReference() const
{return mpNumberReference;}

CCopasiObject * CMoiety::getDependentNumberReference() const
{return mpDNumberReference;}

const std::string & CMoiety::getKey() const {return mKey;} //By G

bool CMoiety::setObjectParent(const CCopasiContainer * pParent)
{
  bool success = CCopasiContainer::setObjectParent(pParent);
  initConversionFactor();

  return success;
}

std::string CMoiety::getDescription(const CModel * model) const
{
  std::ostringstream Description;
  Description.imbue(std::locale::classic());
  Description.precision(16);

  std::vector< std::pair< C_FLOAT64, CMetab * > >::const_iterator it = mEquation.begin();
  std::vector< std::pair< C_FLOAT64, CMetab * > >::const_iterator end = mEquation.end();

  for (; it != end; ++it)
    {
      if (it != mEquation.begin())
        {
          if (it->first < 0.0)
            Description << " - ";
          else
            Description << " + ";
        }

      if (fabs(it->first) > 1.0 + 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() ||
          fabs(it->first) < 1.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
        Description << fabs(it->first) << "*";

      Description << CMetabNameInterface::getDisplayName(model, *it->second, false);
    }

  return Description.str();
}

void CMoiety::refreshInitialValue()
{
  mINumber = 0;

  std::vector< std::pair< C_FLOAT64, CMetab * > >::iterator it = mEquation.begin();
  std::vector< std::pair< C_FLOAT64, CMetab * > >::iterator end = mEquation.end();

  for (; it != end; ++it)
    mINumber += it->first * it->second->getInitialValue();

  return;
}

CCopasiObject * CMoiety::getInitialValueReference() const
{return mpINumberReference;}

C_FLOAT64 CMoiety::getNumber() const
{
  return mINumber;
}

void CMoiety::refreshValue()
{
  std::vector< std::pair< C_FLOAT64, CMetab * > >::iterator it = mEquation.begin();
  std::vector< std::pair< C_FLOAT64, CMetab * > >::iterator end = mEquation.end();

  for (; it != end; ++it)
    mINumber += it->first * it->second->getValue();
}

CCopasiObject * CMoiety::getValueReference() const
{
  return mpNumberReference;
}

std::string CMoiety::getExpression() const
{
  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(16);

  std::vector< std::pair< C_FLOAT64, CMetab * > >::const_iterator it = mEquation.begin();
  std::vector< std::pair< C_FLOAT64, CMetab * > >::const_iterator end = mEquation.end();

  for (; it != end; ++it)
    {
      if (it != mEquation.begin())
        {
          if (it->first < 0.0)
            Infix << "-";
          else
            Infix << "+";
        }

      if (fabs(it->first) > 1.0 + 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() ||
          fabs(it->first) < 1.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
        Infix << fabs(it->first) << "*";

      Infix << "<" << it->second->getInitialValueReference()->getCN() << ">";
    }

  return Infix.str();
}

const C_FLOAT64 & CMoiety::getAmount() const
{
  return mIAmount;
}

void CMoiety::refreshAmount()
{
  mIAmount = mINumber * *mpConversionFactor;
}

const std::vector<std::pair< C_FLOAT64, CMetab * > > & CMoiety::getEquation() const
{
  return mEquation;
}

void CMoiety::initConversionFactor()
{
  const CModel * pModel = dynamic_cast< const CModel * >(getObjectAncestor("Model"));

  if (pModel != NULL)
    {
      mpConversionFactor = &pModel->getNumber2QuantityFactor();
    }
  else
    {
      mpConversionFactor = &DefaultFactor;
    }
}

CTotalNumberReference::CTotalNumberReference(const std::string & name,
    const CCopasiContainer * pParent,
    C_FLOAT64 & reference):
  CCopasiObjectReference< C_FLOAT64 >(name, pParent, reference)
{}

CTotalNumberReference::CTotalNumberReference(const CTotalNumberReference & src,
    const CCopasiContainer * pParent):
  CCopasiObjectReference< C_FLOAT64 >(src, pParent)
{}

CTotalNumberReference::~CTotalNumberReference()
{}

// virtual
bool CTotalNumberReference::isPrerequisiteForContext(const CObjectInterface * /* pObject */,
    const CMath::SimulationContextFlag & context,
    const CObjectInterface::ObjectSet & /* changedObjects */) const
{
  return (context & CMath::UpdateMoieties);
}

CDependentNumberReference::CDependentNumberReference(const std::string & name,
    const CCopasiContainer * pParent,
    C_FLOAT64 & reference):
  CCopasiObjectReference< C_FLOAT64 >(name, pParent, reference)
{}

CDependentNumberReference::CDependentNumberReference(const CDependentNumberReference & src,
    const CCopasiContainer * pParent):
  CCopasiObjectReference< C_FLOAT64 >(src, pParent)
{}

CDependentNumberReference::~CDependentNumberReference()
{}

// virtual
bool CDependentNumberReference::isPrerequisiteForContext(const CObjectInterface * /* pObject */,
    const CMath::SimulationContextFlag & context,
    const CObjectInterface::ObjectSet & /* changedObjects */) const
{
  return (context & CMath::UseMoieties);
}
