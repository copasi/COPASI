/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CCompartment.cpp,v $
   $Revision: 1.53 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/05/29 21:44:02 $
   End CVS Header */

// CCompartment
//
// Derived from Gepasi's ccompart.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Pedro Mendes

#include <iostream>
#include <float.h>

#define  COPASI_TRACE_CONSTRUCTION

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
    mKey(GlobalKeys.add("Compartment", this)),
    //mInitialVolume(1.0),
    //mVolume(1.0),
    mVolumeInv(1.0),
    mMetabolites("Metabolites", this)
{
  mStatus = FIXED;
  initObjects();
  setValue(1.0);
  CONSTRUCTOR_TRACE;
}

CCompartment::CCompartment(const CCompartment & src,
                           const CCopasiContainer * pParent):
    CModelEntity(src, pParent),
    mKey(GlobalKeys.add("Compartment", this)),
    //mInitialVolume(src.mInitialVolume),
    //mVolume(src.mVolume),
    mVolumeInv(src.mVolumeInv),
    mMetabolites(src.mMetabolites, this)
{
  CONSTRUCTOR_TRACE;
  initObjects();
  //  for (unsigned C_INT32 i = 0; i < mMetabolites.size(); i++)
  //    mMetabolites[i]->setCompartment(this);
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

  if ((Fail = configbuffer.getVariable("Volume", "C_FLOAT64",
                                       (void *) & mIValue)))
    return Fail;

  setVolume(mIValue);

  if (configbuffer.getVersion() < "4")
    return Fail;

  C_INT32 MetabolitesNo;

  if ((Fail = configbuffer.getVariable("MetabolitesNo", "C_INT32",
                                       (void *) & MetabolitesNo)))
    return Fail;

  CMetab::setParentCompartment(this);
  mMetabolites.load(configbuffer, MetabolitesNo);

  return Fail;
}

const std::string & CCompartment::getKey() const {return mKey;}

const C_FLOAT64 & CCompartment::getVolumeInv() const {return mVolumeInv;}

CCopasiVectorNS < CMetab > & CCompartment::getMetabolites()
{return mMetabolites;}

const CCopasiVectorNS < CMetab > & CCompartment::getMetabolites() const
  {return mMetabolites;}

bool CCompartment::setInitialValue(const C_FLOAT64 & volume)
{
  C_FLOAT64 Factor = volume / mIValue;
  mIValue = volume;

  /* This assumes state==FIXED */
  setValue(volume);

  C_INT32 i, imax = mMetabolites.size();
  for (i = 0; i < imax; ++i)
    {
      //update particle numbers
      mMetabolites[i]->setInitialNumber(mMetabolites[i]->getInitialNumber() * Factor);
      mMetabolites[i]->setNumber(mMetabolites[i]->getNumber() * Factor);
    }

  return true;
}

bool CCompartment::setValue(const C_FLOAT64 & volume)
{
  mValue = volume;

  if (volume != 0.0) mVolumeInv = 1.0 / volume;
  else mVolumeInv = DBL_MAX;

  return true;
}

/* Note: the metabolite stored in mMetabolites has definetly mpCompartment set.
   In the case the compartment is part of a model also mpModel is set. */
bool CCompartment::createMetabolite(const CMetab & metabolite)
{
  CMetab * pMetab = new CMetab(metabolite);
  return addMetabolite(pMetab);
}

bool CCompartment::addMetabolite(CMetab * pMetabolite)
{
  bool success = mMetabolites.add(pMetabolite, true);
  //update particle number in metab
  if (success)
    {
      pMetabolite->setParentCompartment(this);
      pMetabolite->setInitialConcentration(pMetabolite->getInitialConcentration()); // a hack
      pMetabolite->setConcentration(pMetabolite->getConcentration()); // a hack
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
  CCopasiObject * pObject;
  addObjectReference("InitialVolume", mIValue, CCopasiObject::ValueDbl);
  pObject = addObjectReference("Volume", mValue, CCopasiObject::ValueDbl);
  pObject->setUpdateMethod(this, &CCompartment::setInitialValue);

  //  Volume is currently constant, i.e., we only can modify the initial volume.
  //  To avoid confusion we call it volume :)
  //  pObject = addObjectReference("Volume", mVolume, CCopasiObject::ValueDbl);
  //  pObject->setUpdateMethod(this, &CCompartment::setVolume);
}

/*void * CCompartment::getVolumeAddr()
{
  return &mVolume;
}*/

std::ostream & operator<<(std::ostream &os, const CCompartment & d)
{
  os << "++++CCompartment: " << d.getObjectName() << " mValue " << d.mValue
  << " mVolumeInv " << d.mVolumeInv << std::endl;
  os << "    CCompartment.mMetabolites " << std::endl << d.mMetabolites;
  os << "----CCompartment " << std::endl;

  return os;
}
