/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CFitItem.cpp,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/02/14 14:35:28 $
   End CVS Header */

#include <limits>
#include <math.h>

#include "copasi.h"

#include "CFitItem.h"

#include "utilities/CCopasiParameterGroup.h"

CFitItem::CFitItem(const std::string & name,
                   const CCopasiContainer * pParent):
    COptItem(name, pParent),
    mpParmSavedValue(NULL),
    mpGrpAffectedExperiments(NULL),
    mLocalValue(0),
    mpLocalMethod(new SpecificUpdateMethod<CFitItem, C_FLOAT64>(this, &CFitItem::setLocalValue))
{initializeParameter();}

CFitItem::CFitItem(const CFitItem & src,
                   const CCopasiContainer * pParent):
    COptItem(src, pParent),
    mpParmSavedValue(NULL),
    mpGrpAffectedExperiments(NULL),
    mLocalValue(0),
    mpLocalMethod(new SpecificUpdateMethod<CFitItem, C_FLOAT64>(this, &CFitItem::setLocalValue))
{initializeParameter();}

CFitItem::CFitItem(const CCopasiParameterGroup & group,
                   const CCopasiContainer * pParent):
    COptItem(group, pParent),
    mpParmSavedValue(NULL),
    mpGrpAffectedExperiments(NULL),
    mLocalValue(0),
    mpLocalMethod(new SpecificUpdateMethod<CFitItem, C_FLOAT64>(this, &CFitItem::setLocalValue))
{initializeParameter();}

CFitItem::~CFitItem()
{pdelete(mpLocalMethod);}

void CFitItem::initializeParameter()
{
  mpParmSavedValue =
    assertParameter("SavedValue", CCopasiParameter::DOUBLE, std::numeric_limits<C_FLOAT64>::quiet_NaN())->getValue().pDOUBLE;
  mpGrpAffectedExperiments = assertGroup("Affected Experiments");
}

bool CFitItem::elevateChildren()
{
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

  if (isnan(*mpParmSavedValue))
    {
      mLocalValue = * COptItem::getObjectValue();
      *mpParmSavedValue = mLocalValue;
    }
  else
    mLocalValue = *mpParmSavedValue;

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

bool CFitItem::setSavedValue(const C_FLOAT64 & value)
{
  *mpParmSavedValue = value;
  return true;
}

const C_FLOAT64 & CFitItem::getSavedValue() const
  {return *mpParmSavedValue;}

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
{return *mpGrpAffectedExperiments->getValue(index).pKEY;}

bool CFitItem::removeExperiment(const unsigned C_INT32 & index)
{return mpGrpAffectedExperiments->removeParameter(index);}

unsigned C_INT32 CFitItem::getExperimentCount() const
  {return mpGrpAffectedExperiments->size();}

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
