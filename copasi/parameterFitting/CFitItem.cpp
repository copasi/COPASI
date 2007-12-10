// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CFitItem.cpp,v $
//   $Revision: 1.17 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/12/10 19:42:46 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <limits>
#include <math.h>

#include "copasi.h"

#include "CFitItem.h"

#include "report/CKeyFactory.h"
#include "utilities/CCopasiParameterGroup.h"

CFitItem::CFitItem(const std::string & name,
                   const CCopasiContainer * pParent):
    COptItem(name, pParent),
    mpGrpAffectedExperiments(NULL),
#ifdef COPASI_CROSSVALIDATION
    mpGrpAffectedCrossValidations(NULL),
#endif // COPASI_CROSSVALIDATION
    mLocalValue(0),
    mpLocalMethod(new SpecificUpdateMethod<CFitItem, C_FLOAT64>(this, &CFitItem::setLocalValue))
{initializeParameter();}

CFitItem::CFitItem(const CFitItem & src,
                   const CCopasiContainer * pParent):
    COptItem(src, pParent),
    mpGrpAffectedExperiments(NULL),
#ifdef COPASI_CROSSVALIDATION
    mpGrpAffectedCrossValidations(NULL),
#endif // COPASI_CROSSVALIDATION
    mLocalValue(0),
    mpLocalMethod(new SpecificUpdateMethod<CFitItem, C_FLOAT64>(this, &CFitItem::setLocalValue))
{initializeParameter();}

CFitItem::CFitItem(const CCopasiParameterGroup & group,
                   const CCopasiContainer * pParent):
    COptItem(group, pParent),
    mpGrpAffectedExperiments(NULL),
#ifdef COPASI_CROSSVALIDATION
    mpGrpAffectedCrossValidations(NULL),
#endif // COPASI_CROSSVALIDATION
    mLocalValue(0),
    mpLocalMethod(new SpecificUpdateMethod<CFitItem, C_FLOAT64>(this, &CFitItem::setLocalValue))
{initializeParameter();}

CFitItem::~CFitItem()
{pdelete(mpLocalMethod);}

void CFitItem::initializeParameter()
{
  mpGrpAffectedExperiments = assertGroup("Affected Experiments");

#ifdef COPASI_CROSSVALIDATION
  mpGrpAffectedCrossValidations = assertGroup("Affected Cross Validation Experiments");
#endif // COPASI_CROSSVALIDATION

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
      setStartValue(*pSavedValue->getValue().pDOUBLE);
      removeParameter("SavedValue");
    }

  mpGrpAffectedExperiments =
    elevate<CCopasiParameterGroup, CCopasiParameterGroup>(mpGrpAffectedExperiments);
  if (!mpGrpAffectedExperiments) return false;

#ifdef COPASI_CROSSVALIDATION
  mpGrpAffectedCrossValidations =
    elevate<CCopasiParameterGroup, CCopasiParameterGroup>(mpGrpAffectedCrossValidations);
  if (!mpGrpAffectedCrossValidations) return false;
#endif // COPASI_CROSSVALIDATION

  return true;
}

bool CFitItem::isValid() const
{return COptItem::isValid();}

bool CFitItem::isValid(CCopasiParameterGroup & group)
{
  CFitItem tmp(group);

  return tmp.isValid();
}

bool CFitItem::compile(const std::vector< CCopasiContainer * > listOfContainer)
{
  if (!COptItem::compile(listOfContainer)) return false;

  mLocalValue = *mpParmStartValue;

  return true;
}

C_INT32 CFitItem::checkConstraint() const
  {
    if (*mpLowerBound > mLocalValue) return - 1;
    if (mLocalValue > *mpUpperBound) return 1;
    return 0;
  }

std::ostream &operator<<(std::ostream &os, const CFitItem & o)
{
  os << * static_cast<const COptItem *>(&o) << std::endl;

  unsigned C_INT32 i, imax = o.mpGrpAffectedExperiments->size();

  os << "    Affected Experiments:" << std::endl << "      ";
  if (imax == 0) os << "all";

  for (i = 0; i < imax; i++)
    {
      if (i) os << ", ";
      os << o.getExperiment(i);
    }

#ifdef COPASI_CROSSVALIDATION
  imax = o.mpGrpAffectedCrossValidations->size();

  os << "    Affected Cross Validation Experiments:" << std::endl << "      ";
  if (imax == 0) os << "all";

  for (i = 0; i < imax; i++)
    {
      if (i) os << ", ";
      os << o.getCrossValidation(i);
    }
#endif // COPASI_CROSSVALIDATION

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

UpdateMethod * CFitItem::getUpdateMethod() const
  {return mpLocalMethod;}

bool CFitItem::addExperiment(const std::string & key)
{
  unsigned C_INT32 i, imax = mpGrpAffectedExperiments->size();

  for (i = 0; i < imax; i++)
    if (*mpGrpAffectedExperiments->getValue(i).pKEY == key) return false; // The key already exists.

  return mpGrpAffectedExperiments->addParameter("Experiment Key", CCopasiParameter::KEY, key);
}

const std::string & CFitItem::getExperiment(const unsigned C_INT32 & index) const
  {
    static const std::string Empty("");

    if (index < mpGrpAffectedExperiments->size())
      return *mpGrpAffectedExperiments->getValue(index).pKEY;

    return Empty;
  }

bool CFitItem::removeExperiment(const unsigned C_INT32 & index)
{return mpGrpAffectedExperiments->removeParameter(index);}

unsigned C_INT32 CFitItem::getExperimentCount() const
  {return mpGrpAffectedExperiments->size();}

std::string CFitItem::getExperiments() const
  {
    std::string Experiments;
    unsigned C_INT32 i, imax = mpGrpAffectedExperiments->size();
    const CCopasiObject * pObject;

    for (i = 0; i < imax; i++)
      {
        pObject = GlobalKeys.get(*mpGrpAffectedExperiments->getValue(i).pKEY);

        if (i && pObject)
          Experiments += ", ";

        Experiments += pObject->getObjectName();
      }

    return Experiments;
  }

#ifdef COPASI_CROSSVALIDATION
bool CFitItem::addCrossValidation(const std::string & key)
{
  unsigned C_INT32 i, imax = mpGrpAffectedCrossValidations->size();

  for (i = 0; i < imax; i++)
    if (*mpGrpAffectedCrossValidations->getValue(i).pKEY == key) return false; // The key already exists.

  return mpGrpAffectedCrossValidations->addParameter("Experiment Key", CCopasiParameter::KEY, key);
}

const std::string & CFitItem::getCrossValidation(const unsigned C_INT32 & index) const
  {
    static const std::string Empty("");

    if (index < mpGrpAffectedCrossValidations->size())
      return *mpGrpAffectedCrossValidations->getValue(index).pKEY;

    return Empty;
  }

bool CFitItem::removeCrossValidation(const unsigned C_INT32 & index)
{return mpGrpAffectedCrossValidations->removeParameter(index);}

unsigned C_INT32 CFitItem::getCrossValidationCount() const
  {return mpGrpAffectedCrossValidations->size();}

std::string CFitItem::getCrossValidations() const
  {
    std::string CrossValidations;
    unsigned C_INT32 i, imax = mpGrpAffectedCrossValidations->size();
    const CCopasiObject * pObject;

    for (i = 0; i < imax; i++)
      {
        pObject = GlobalKeys.get(*mpGrpAffectedCrossValidations->getValue(i).pKEY);

        if (i && pObject)
          CrossValidations += ", ";

        CrossValidations += pObject->getObjectName();
      }

    return CrossValidations;
  }
#endif // COPASI_CROSSVALIDATION

bool CFitItem::updateBounds(std::vector<COptItem * >::iterator it)
{
  while (*it != this)
    {
      if (mpLowerObject && (getLowerBound() == (*it)->getObjectCN()))
        mpLowerBound = &static_cast<CFitItem *>(*it)->getLocalValue();

      if (mpUpperObject && (getUpperBound() == (*it)->getObjectCN()))
        mpUpperBound = &static_cast<CFitItem *>(*it)->getLocalValue();

      ++it;
    }

  return true;
}

CFitConstraint::CFitConstraint(const std::string & name,
                               const CCopasiContainer * pParent):
    CFitItem(name, pParent)
{}

CFitConstraint::CFitConstraint(const CFitConstraint & src,
                               const CCopasiContainer * pParent):
    CFitItem(src, pParent)
{}

CFitConstraint::CFitConstraint(const CCopasiParameterGroup & group,
                               const CCopasiContainer * pParent):
    CFitItem(group, pParent)
{}

CFitConstraint::~CFitConstraint() {}

C_INT32 CFitConstraint::checkConstraint() const
  {
    if (*mpLowerBound > mLocalValue) return - 1;
    if (mLocalValue > *mpUpperBound) return 1;
    return 0;
  }

C_FLOAT64 CFitConstraint::getConstraintViolation() const
  {
    switch (checkConstraint())
      {
      case - 1:
        return *mpLowerBound - mLocalValue;
        break;

      case 1:
        return mLocalValue - *mpUpperBound;
        break;

      default:
        return 0.0;
        break;
      }
  }
