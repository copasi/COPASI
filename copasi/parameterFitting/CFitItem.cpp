/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CFitItem.cpp,v $
   $Revision: 1.15 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/14 13:31:19 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
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
    mLocalValue(0),
    mpLocalMethod(new SpecificUpdateMethod<CFitItem, C_FLOAT64>(this, &CFitItem::setLocalValue))
{initializeParameter();}

CFitItem::CFitItem(const CFitItem & src,
                   const CCopasiContainer * pParent):
    COptItem(src, pParent),
    mpGrpAffectedExperiments(NULL),
    mLocalValue(0),
    mpLocalMethod(new SpecificUpdateMethod<CFitItem, C_FLOAT64>(this, &CFitItem::setLocalValue))
{initializeParameter();}

CFitItem::CFitItem(const CCopasiParameterGroup & group,
                   const CCopasiContainer * pParent):
    COptItem(group, pParent),
    mpGrpAffectedExperiments(NULL),
    mLocalValue(0),
    mpLocalMethod(new SpecificUpdateMethod<CFitItem, C_FLOAT64>(this, &CFitItem::setLocalValue))
{initializeParameter();}

CFitItem::~CFitItem()
{pdelete(mpLocalMethod);}

void CFitItem::initializeParameter()
{
  mpGrpAffectedExperiments = assertGroup("Affected Experiments");

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
    if (*mpLowerBound > *mpObjectValue)
      {
        C_FLOAT64 Delta = *mpLowerBound - *mpObjectValue;
        if (fabs(mLocalValue) < Delta)
          const_cast<CFitConstraint *>(this)->mLocalValue = -Delta;

        return - 1;
      }

    if (*mpObjectValue > *mpUpperBound)
      {
        C_FLOAT64 Delta = *mpObjectValue - *mpUpperBound;
        if (fabs(mLocalValue) < Delta)
          const_cast<CFitConstraint *>(this)->mLocalValue = Delta;

        return 1;
      }

    return 0;
  }

C_FLOAT64 CFitConstraint::getConstraintViolation() const
{return mLocalValue;}
