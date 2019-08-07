// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/copasi.h"
#include "CMoiety.h"
#include "CModel.h"
#include "CCompartment.h"
#include "CMetabNameInterface.h"

#include "copasi/core/CDataObjectReference.h"
#include "copasi/report/CKeyFactory.h"//By G
#include "copasi/function/CExpression.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/utilities/CReadConfig.h"
#include "copasi/core/CDataVector.h"
#include "copasi/utilities/utility.h"
#include "copasi/core/CRootContainer.h"

// static
const C_FLOAT64 CMoiety::DefaultFactor(1.0);

// static
CMoiety * CMoiety::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CMoiety(data.getProperty(CData::OBJECT_NAME).toString(),
                     NO_PARENT);
}

// virtual
CData CMoiety::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CMoiety::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CMoiety::CMoiety(const std::string & name,
                 const CDataContainer * pParent):
  CDataContainer(name, pParent, "Moiety"),
  mKey(CRootContainer::getKeyFactory()->add("Moiety", this)), //By G
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
                 const CDataContainer * pParent):
  CDataContainer(src, pParent),
  mKey(CRootContainer::getKeyFactory()->add("Moiety", this)), //By G
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
  CRootContainer::getKeyFactory()->remove(mKey);
  DESTRUCTOR_TRACE;
}

void CMoiety::initObjects()
{
  mpINumberReference = new CTotalNumberReference("InitialValue", this, mINumber);
  mpNumberReference = new CTotalNumberReference("Value", this, mNumber);

  mpDNumberReference = new CDependentNumberReference("DependentValue", this, mNumber);

  CDataObject * pObject = addObjectReference("Amount", mIAmount, CDataObject::ValueDbl);

  return;
}

void CMoiety::add(C_FLOAT64 value, CMetab * pMetabolite)
{
  if (mEquation.empty())
    pMetabolite->setDependsOnMoiety(this);

  std::pair<C_FLOAT64, CMetab *> element;

  element.first = value;
  element.second = pMetabolite;

  mEquation.push_back(element);
}

void CMoiety::cleanup()
{
  mEquation.clear();
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

CDataObject * CMoiety::getInitialTotalNumberReference() const
{return mpINumberReference;}

CDataObject * CMoiety::getTotalNumberReference() const
{return mpNumberReference;}

CDataObject * CMoiety::getDependentNumberReference() const
{return mpDNumberReference;}

const std::string & CMoiety::getKey() const {return mKey;} //By G

bool CMoiety::setObjectParent(const CDataContainer * pParent)
{
  bool success = CDataContainer::setObjectParent(pParent);
  initConversionFactor();

  return success;
}

std::string CMoiety::getDescription(const CModel * model) const
{
  std::ostringstream Description;
  Description.imbue(std::locale::classic());
  Description.precision(std::numeric_limits<double>::digits10 + 2);

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

CDataObject * CMoiety::getInitialValueReference() const
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

CDataObject * CMoiety::getValueReference() const
{
  return mpNumberReference;
}

std::string CMoiety::getExpression() const
{
  std::ostringstream Infix;
  Infix.imbue(std::locale::classic());
  Infix.precision(std::numeric_limits<double>::digits10 + 2);

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
  mIAmount = mINumber **mpConversionFactor;
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
    const CDataContainer * pParent,
    C_FLOAT64 & reference):
  CDataObjectReference< C_FLOAT64 >(name, pParent, reference)
{}

CTotalNumberReference::CTotalNumberReference(const CTotalNumberReference & src,
    const CDataContainer * pParent):
  CDataObjectReference< C_FLOAT64 >(src, pParent)
{}

CTotalNumberReference::~CTotalNumberReference()
{}

// virtual
bool CTotalNumberReference::isPrerequisiteForContext(const CObjectInterface * /* pObject */,
    const CCore::SimulationContextFlag & context,
    const CObjectInterface::ObjectSet & /* changedObjects */) const
{
  return context.isSet(CCore::SimulationContext::UpdateMoieties);
}

CDependentNumberReference::CDependentNumberReference(const std::string & name,
    const CDataContainer * pParent,
    C_FLOAT64 & reference):
  CDataObjectReference< C_FLOAT64 >(name, pParent, reference)
{}

CDependentNumberReference::CDependentNumberReference(const CDependentNumberReference & src,
    const CDataContainer * pParent):
  CDataObjectReference< C_FLOAT64 >(src, pParent)
{}

CDependentNumberReference::~CDependentNumberReference()
{}

// virtual
bool CDependentNumberReference::isPrerequisiteForContext(const CObjectInterface * /* pObject */,
    const CCore::SimulationContextFlag & context,
    const CObjectInterface::ObjectSet & /* changedObjects */) const
{
  return context.isSet(CCore::SimulationContext::UpdateMoieties);
}
