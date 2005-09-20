/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CFitItem.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/09/20 13:07:39 $
   End CVS Header */

#include "copasi.h"

#include "CFitItem.h"

#include "utilities/CCopasiParameterGroup.h"

CFitItem::CFitItem(CCopasiParameterGroup & group) :
    COptItem(group),
    mLocalValue(0),
    mpLocalMethod(new SpecificUpdateMethod<CFitItem, C_FLOAT64>(this, &CFitItem::setLocalValue))
{}

CFitItem::CFitItem(CFitItem & src) :
    COptItem(src),
    mLocalValue(0),
    mpLocalMethod(new SpecificUpdateMethod<CFitItem, C_FLOAT64>(this, &CFitItem::setLocalValue))
{}

CFitItem::~CFitItem()
{pdelete(mpLocalMethod);}

bool CFitItem::initialize(const CCopasiObjectName & objectCN)
{
  if (!COptItem::initialize(objectCN)) return false;

  mpGroup->addGroup("List of affected Experiments");

  return isValid();
}

bool CFitItem::isValid() const
  {
    if (!COptItem::isValid()) return false;

    if (!dynamic_cast<CCopasiParameterGroup *>(mpGroup->getParameter("List of affected Experiments")))
      return false;

    return true;
  }

bool CFitItem::isValid(CCopasiParameterGroup & group)
{
  CFitItem tmp(group);

  return tmp.isValid();
}

bool CFitItem::compile(const std::vector< CCopasiContainer * > listOfContainer)
{
  if (!COptItem::compile(listOfContainer)) return false;

  if (static_cast<CCopasiParameterGroup *>(mpGroup->getParameter("List of affected Experiments"))->size() == 0)
    return false;

  return true;
}

std::ostream &operator<<(std::ostream &os, const CFitItem & o)
{
  os << * static_cast<const COptItem *>(&o);

  /* :TODO: add local ouput */

  return os;
}

bool CFitItem::setLocalValue(const C_FLOAT64 & value)
{
  mLocalValue = value;
  return true;
}

const C_FLOAT64 & CFitItem::getLocalValue() const
  {return mLocalValue;}

bool CFitItem::addExperiment(const std::string & key)
{
  CCopasiParameterGroup * pGrp =
    dynamic_cast<CCopasiParameterGroup *>(mpGroup->getParameter("List of affected Experiments"));

  assert(pGrp);

  unsigned C_INT32 i, imax = pGrp->size();

  for (i = 0; i < imax; i++)
    if (*pGrp->getValue(i).pKEY == key) return false; // The key already exists.

  return pGrp->addParameter("Experiment Key", CCopasiParameter::KEY, key);
}

const std::string & CFitItem::getExperiment(const unsigned C_INT32 & index) const
  {
    CCopasiParameterGroup * pGrp =
      dynamic_cast<CCopasiParameterGroup *>(mpGroup->getParameter("List of affected Experiments"));

    assert(pGrp && index < pGrp->size());

    return *pGrp->getValue(index).pKEY;
  }

bool CFitItem::removeExperiment(const unsigned C_INT32 & index)
{
  CCopasiParameterGroup * pGrp =
    dynamic_cast<CCopasiParameterGroup *>(mpGroup->getParameter("List of affected Experiments"));

  assert(pGrp);

  return pGrp->removeParameter(index);
}

unsigned C_INT32 CFitItem::getExperimentCount() const
  {
    CCopasiParameterGroup * pGrp =
      dynamic_cast<CCopasiParameterGroup *>(mpGroup->getParameter("List of affected Experiments"));

    assert(pGrp);

    return pGrp->size();
  }
