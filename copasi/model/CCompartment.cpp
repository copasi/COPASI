/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CCompartment.cpp,v $
   $Revision: 1.65 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/08/02 11:31:03 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// CCompartment
//
// Derived from Gepasi's ccompart.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Pedro Mendes

#include <iostream>
#include <float.h>
#include <math.h>

#include "copasi.h"
#include "utilities/CReadConfig.h"
#include "utilities/CCopasiVector.h"
#include "utilities/utility.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"
#include "CCompartment.h"

CCompartment::CCompartment(const std::string & name,
                           const CCopasiContainer * pParent):
    CModelEntity(name, pParent, "Compartment"),
    mMetabolites("Metabolites", this)
{
  initObjects();

  mKey = GlobalKeys.add("Compartment", this);

  setStatus(FIXED);

  *mpIValue = 1.0;

  CONSTRUCTOR_TRACE;
}

CCompartment::CCompartment(const CCompartment & src,
                           const CCopasiContainer * pParent):
    CModelEntity(src, pParent),
    mMetabolites(src.mMetabolites, this)
{
  mKey = GlobalKeys.add("Compartment", this);
  CONSTRUCTOR_TRACE;
  initObjects();
}

CCompartment::~CCompartment()
{
  GlobalKeys.remove(mKey);
  DESTRUCTOR_TRACE;
}

void CCompartment::cleanup() {mMetabolites.cleanup();}

C_INT32 CCompartment::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;
  std::string tmp;
  if ((Fail = configbuffer.getVariable("Compartment", "string",
                                       (void *) & tmp,
                                       CReadConfig::SEARCH)))
    return Fail;
  setObjectName(tmp);

  C_FLOAT64 tmpdbl;
  if ((Fail = configbuffer.getVariable("Volume", "C_FLOAT64",
                                       (void *) & tmpdbl)))
    return Fail;

  setInitialValue(tmpdbl);

  return Fail;
}

CCopasiVectorNS < CMetab > & CCompartment::getMetabolites()
{return mMetabolites;}

const CCopasiVectorNS < CMetab > & CCompartment::getMetabolites() const
  {return mMetabolites;}

void CCompartment::setInitialValue(const C_FLOAT64 & initialValue)
{
  if ((initialValue == *mpIValue) && !isnan(initialValue) ||
      (isnan(initialValue) && isnan(*mpIValue))) return;

  *mpIValue = initialValue;

  C_INT32 i, imax = mMetabolites.size();
  for (i = 0; i < imax; ++i)
    {
      //update particle numbers is not necessary as concentration changes fix this
      //mMetabolites[i]->setInitialNumber(mMetabolites[i]->getInitialNumber() * Factor);
      //mMetabolites[i]->setNumber(mMetabolites[i]->getNumber() * Factor);
      mMetabolites[i]->setInitialConcentration(mMetabolites[i]->getInitialConcentration()); // a hack
      mMetabolites[i]->setConcentration(mMetabolites[i]->getConcentration()); // a hack
    }

  return;
}

#ifdef WIN32
// warning C4056: overflow in floating-point constant arithmetic
// warning C4756: overflow in constant arithmetic
# pragma warning (disable: 4056 4756)
#endif

void CCompartment::setValue(const C_FLOAT64 & value)
{
  // :TODO: This should never be called as long the volume is fixed.
  assert (false);

  if (isFixed()) return;

  *mpValueAccess = value;

  return;
}

#ifdef WIN32
# pragma warning (default: 4056 4756)
#endif

/* Note: the metabolite stored in mMetabolites has definetly mpCompartment set.
   In the case the compartment is part of a model also mpModel is set. */
bool CCompartment::createMetabolite(const CMetab & metabolite)
{
  CMetab * pMetab = new CMetab(metabolite);
  if (addMetabolite(pMetab)) return true;

  delete pMetab;
  return false;
}

bool CCompartment::addMetabolite(CMetab * pMetabolite)
{
  bool success = mMetabolites.add(pMetabolite, true);
  //update particle number in metab
  if (success)
    {
      //      pMetabolite->setParentCompartment(this);
      //      pMetabolite->setInitialConcentration(pMetabolite->getInitialConcentration()); // a hack
      //      pMetabolite->setConcentration(pMetabolite->getConcentration()); // a hack
    }

  return success;
}

bool CCompartment::removeMetabolite(CMetab * pMetabolite)
{
  unsigned C_INT32 index = mMetabolites.CCopasiVector < CMetab >::getIndex(pMetabolite);
  if (index == C_INVALID_INDEX)
    return false;

  mMetabolites.CCopasiVector < CMetab >::remove(index);

  return true;
}

//bool CCompartment::isValidName(const std::string & name) const
//{return (name.find_first_of(" ") == std::string::npos);}

void CCompartment::initObjects()
{
  mpIValueReference->setObjectName("InitialVolume");

  mpValueReference->setObjectName("Volume");
  mpValueReference->setUpdateMethod(this, &CCompartment::setInitialValue);

  //  Volume is currently constant, i.e., we only can modify the initial volume.
  //  To avoid confusion we call it volume :)
  //  pObject = addObjectReference("Volume", mVolume, CCopasiObject::ValueDbl);
  //  pObject->setUpdateMethod(this, &CCompartment::setVolume);
}

std::ostream & operator<<(std::ostream &os, const CCompartment & d)
{
  os << "++++CCompartment: " << d.getObjectName() << " mValue " << *d.mpValueAccess;
  os << "    CCompartment.mMetabolites " << std::endl << d.mMetabolites;
  os << "----CCompartment " << std::endl;

  return os;
}
