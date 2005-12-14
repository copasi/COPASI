/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CFitItem.cpp,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/12/14 19:16:31 $
   End CVS Header */

#include "copasi.h"

#include "CFitItem.h"

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
{mpGrpAffectedExperiments = assertGroup("Affected Experiments");}

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

  mLocalValue = * COptItem::getObjectValue();

  return true;
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

bool CFitItem::setLocalValue(const C_FLOAT64 & value)
{
  mLocalValue = value;
  return true;
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
