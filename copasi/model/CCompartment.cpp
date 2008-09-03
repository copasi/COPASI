// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CCompartment.cpp,v $
//   $Revision: 1.69 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/09/03 23:11:28 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
#include "report/CRenameHandler.h"
#include "CCompartment.h"
#include "CModel.h"

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

// virtual
std::string CCompartment::getChildObjectUnits(const CCopasiObject * pObject) const
  {
    if (mpModel == NULL) return "";

    const std::string & Name = pObject->getObjectName();

    if (Name == "InitialVolume" ||
        Name == "Volume")
      return mpModel->getVolumeUnitName();
    else if (Name == "Rate")
      return mpModel->getVolumeUnitName() + "/" + mpModel->getTimeUnitName();

    return "";
  }

void CCompartment::cleanup() {mMetabolites.cleanup();}

std::set< const CCopasiObject * > CCompartment::getDeletedObjects() const
  {
    std::set< const CCopasiObject * > Deleted = CModelEntity::getDeletedObjects();

    // We need to add all metabolites
    CCopasiVector< CMetab >::const_iterator it = mMetabolites.begin();
    CCopasiVector< CMetab >::const_iterator end = mMetabolites.end();

    for (;it != end; ++it)
      Deleted.insert(*it);

    return Deleted;
  }

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
  if (!pMetabolite) return false;

  std::string oldCN = pMetabolite->getCN();

  bool success = mMetabolites.add(pMetabolite, true);

  //if a metabolite is added to a compartment successfully the CN of
  //the metabolite is changed. This needs to be handled similarly to a
  //rename.
  if (success && smpRenameHandler && getObjectParent())
    {
      std::string newCN = pMetabolite->getCN();
      smpRenameHandler->handle(oldCN, newCN);
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
}

std::ostream & operator<<(std::ostream &os, const CCompartment & d)
{
  os << "++++CCompartment: " << d.getObjectName() << " mValue " << *d.mpValueAccess;
  os << "    CCompartment.mMetabolites " << std::endl << d.mMetabolites;
  os << "----CCompartment " << std::endl;

  return os;
}
