// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <limits>
#include <cmath>

#include "copasi/copasi.h"

#include "CFitItem.h"

#include "copasi/report/CKeyFactory.h"
#include "copasi/utilities/CCopasiParameterGroup.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"

CFitItem::CFitItem(const CDataContainer * pParent,
                   const std::string & name):
  COptItem(pParent, name),
  mpGrpAffectedExperiments(NULL),
  mpGrpAffectedCrossValidations(NULL),
  mLocalValue(0)
{initializeParameter();}

CFitItem::CFitItem(const CFitItem & src,
                   const CDataContainer * pParent):
  COptItem(src, pParent),
  mpGrpAffectedExperiments(NULL),
  mpGrpAffectedCrossValidations(NULL),
  mLocalValue(0)
{initializeParameter();}

CFitItem::CFitItem(const CCopasiParameterGroup & group,
                   const CDataContainer * pParent):
  COptItem(group, pParent),
  mpGrpAffectedExperiments(NULL),
  mpGrpAffectedCrossValidations(NULL),
  mLocalValue(0)
{initializeParameter();}

CFitItem::~CFitItem()
{}

void CFitItem::initializeParameter()
{
  mpGrpAffectedExperiments = assertGroup("Affected Experiments");

  mpGrpAffectedCrossValidations = assertGroup("Affected Cross Validation Experiments");

  elevateChildren();
}

bool CFitItem::elevateChildren()
{
  // The functionality of SavedValue is no handled more transparently
  // through the StartValue. Therefore, in case we encounter an old file
  // we need to copy its value.
  CCopasiParameter *pSavedValue = getParameter("SavedValue");

  if (pSavedValue)
    {
      setStartValue(pSavedValue->getValue< C_FLOAT64 >());
      removeParameter("SavedValue");
    }

  mpGrpAffectedExperiments =
    elevate<CCopasiParameterGroup, CCopasiParameterGroup>(mpGrpAffectedExperiments);

  if (!mpGrpAffectedExperiments) return false;

  mpGrpAffectedCrossValidations =
    elevate<CCopasiParameterGroup, CCopasiParameterGroup>(mpGrpAffectedCrossValidations);

  if (!mpGrpAffectedCrossValidations) return false;

  return true;
}

bool CFitItem::isValid() const
{return COptItem::isValid();}

bool CFitItem::isValid(CCopasiParameterGroup & group)
{
  CFitItem tmp(group, NO_PARENT);

  return tmp.isValid();
}

bool CFitItem::compile(CObjectInterface::ContainerList listOfContainer)
{
  bool success = COptItem::compile(listOfContainer);

  mLocalValue = *mpParmStartValue;

  return success;
}

C_INT32 CFitItem::checkConstraint() const
{
  if (*mpLowerBound > mLocalValue) return - 1;

  if (mLocalValue > *mpUpperBound) return 1;

  return 0;
}

C_FLOAT64 CFitItem::getConstraintViolation() const
{
  switch (checkConstraint())
    {
      case - 1:
        return *mpLowerBound - mLocalValue;
        break;

      case 1:
        return mLocalValue - *mpUpperBound;
        break;
    }

  return 0.0;
}

std::ostream &operator<<(std::ostream &os, const CFitItem & o)
{
  os << * static_cast<const COptItem *>(&o) << std::endl;

  size_t i, imax = o.mpGrpAffectedExperiments->size();

  os << "    Affected Experiments:" << std::endl << "      ";

  if (imax == 0) os << "all";

  for (i = 0; i < imax; i++)
    {
      if (i) os << ", ";

      os << o.getExperiment(i);
    }

  imax = o.mpGrpAffectedCrossValidations->size();

  os << "    Affected Validation Experiments:" << std::endl << "      ";

  if (imax == 0) os << "all";

  for (i = 0; i < imax; i++)
    {
      if (i) os << ", ";

      os << o.getCrossValidation(i);
    }

  return os;
}

void CFitItem::setLocalValue(const C_FLOAT64 & value)
{
  mLocalValue = value;
  return;
}

const C_FLOAT64 & CFitItem::getLocalValue() const
{return mLocalValue;}

const C_FLOAT64 * CFitItem::getObjectValue() const
{return & mLocalValue;}

bool CFitItem::addExperiment(const std::string & key)
{
  size_t i, imax = mpGrpAffectedExperiments->size();

  for (i = 0; i < imax; i++)
    if (mpGrpAffectedExperiments->getValue< std::string >(i) == key) return false; // The key already exists.

  return mpGrpAffectedExperiments->addParameter("Experiment Key", CCopasiParameter::Type::KEY, key);
}

const std::string & CFitItem::getExperiment(const size_t & index) const
{
  static const std::string Empty("");

  if (index < mpGrpAffectedExperiments->size())
    return mpGrpAffectedExperiments->getValue< std::string >(index);

  return Empty;
}

bool CFitItem::removeExperiment(const size_t & index)
{return mpGrpAffectedExperiments->removeParameter(index);}

size_t CFitItem::getExperimentCount() const
{return mpGrpAffectedExperiments->size();}

std::string CFitItem::getExperiments() const
{
  std::string Experiments;
  size_t i, imax = mpGrpAffectedExperiments->size();
  const CDataObject * pObject;

  for (i = 0; i < imax; i++)
    {
      pObject = CRootContainer::getKeyFactory()->get(mpGrpAffectedExperiments->getValue< std::string >(i));

      if (pObject != NULL)
        {
          if (i != 0)
            {
              Experiments += ", ";
            }

          Experiments += pObject->getObjectName();
        }
    }

  return Experiments;
}

bool CFitItem::addCrossValidation(const std::string & key)
{
  size_t i, imax = mpGrpAffectedCrossValidations->size();

  for (i = 0; i < imax; i++)
    if (mpGrpAffectedCrossValidations->getValue< std::string >(i) == key) return false; // The key already exists.

  return mpGrpAffectedCrossValidations->addParameter("Experiment Key", CCopasiParameter::Type::KEY, key);
}

const std::string & CFitItem::getCrossValidation(const size_t & index) const
{
  static const std::string Empty("");

  if (index < mpGrpAffectedCrossValidations->size())
    return mpGrpAffectedCrossValidations->getValue< std::string >(index);

  return Empty;
}

bool CFitItem::removeCrossValidation(const size_t & index)
{return mpGrpAffectedCrossValidations->removeParameter(index);}

size_t CFitItem::getCrossValidationCount() const
{return mpGrpAffectedCrossValidations->size();}

std::string CFitItem::getCrossValidations() const
{
  std::string CrossValidations;
  size_t i, imax = mpGrpAffectedCrossValidations->size();
  const CDataObject * pObject;

  for (i = 0; i < imax; i++)
    {
      pObject = CRootContainer::getKeyFactory()->get(mpGrpAffectedCrossValidations->getValue< std::string >(i));

      if (i && pObject)
        CrossValidations += ", ";

      CrossValidations += pObject->getObjectName();
    }

  return CrossValidations;
}

bool CFitItem::updateBounds(const std::vector<COptItem * > & items)
{
  // TODO CRITICAL Bug 3108
  std::vector<COptItem * >::const_iterator it = items.begin();
  std::vector<COptItem * >::const_iterator end = items.end();

  for (; it != end && *it != this; ++it)
    {
      if (mpLowerObject && (getLowerBound() == (*it)->getObjectCN()))
        mpLowerBound = &static_cast<CFitItem *>(*it)->getLocalValue();

      if (mpUpperObject && (getUpperBound() == (*it)->getObjectCN()))
        mpUpperBound = &static_cast<CFitItem *>(*it)->getLocalValue();
    }

  return true;
}

CFitConstraint::CFitConstraint(const CDataContainer * pParent,
                               const std::string & name):
  CFitItem(pParent, name),
  mCheckConstraint(0),
  mConstraintViolation(0.0)
{}

CFitConstraint::CFitConstraint(const CFitConstraint & src,
                               const CDataContainer * pParent):
  CFitItem(src, pParent),
  mCheckConstraint(src.mCheckConstraint),
  mConstraintViolation(src.mConstraintViolation)
{}

CFitConstraint::CFitConstraint(const CCopasiParameterGroup & group,
                               const CDataContainer * pParent):
  CFitItem(group, pParent),
  mCheckConstraint(0),
  mConstraintViolation(0.0)
{}

CFitConstraint::~CFitConstraint() {}

void CFitConstraint::resetConstraintViolation()
{
  mCheckConstraint = 0;
  mConstraintViolation = 0.0;
}

void CFitConstraint::calculateConstraintViolation()
{
  if (*mpLowerBound > *mpObjectValue) mCheckConstraint = -1;
  else if (*mpObjectValue > *mpUpperBound) mCheckConstraint = 1;
  else mCheckConstraint = 0;

  switch (mCheckConstraint)
    {
      case - 1:
        mConstraintViolation += *mpLowerBound - *mpObjectValue;
        break;

      case 1:
        mConstraintViolation += *mpObjectValue - *mpUpperBound;
        break;

      default:
        break;
    }
}

C_INT32 CFitConstraint::checkConstraint() const
{return mCheckConstraint;}

C_FLOAT64 CFitConstraint::getConstraintViolation() const
{return mConstraintViolation;}
