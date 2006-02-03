/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CCompartment.cpp,v $
   $Revision: 1.59.2.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2006/02/03 11:08:20 $
   End CVS Header */

// CCompartment
//
// Derived from Gepasi's ccompart.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Pedro Mendes

#include <iostream>
#include <float.h>

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
    //mKey(GlobalKeys.add("Compartment", this)),
    //mInitialVolume(1.0),
    //mVolume(1.0),
    mVolumeInv(1.0),
    mMetabolites("Metabolites", this)
{
  mKey = GlobalKeys.add("Compartment", this);
  mStatus = FIXED;
  initObjects();
  setValue(1.0);
  CONSTRUCTOR_TRACE;
}

CCompartment::CCompartment(const CCompartment & src,
                           const CCopasiContainer * pParent):
    CModelEntity(src, pParent),
    //mKey(GlobalKeys.add("Compartment", this)),
    //mInitialVolume(src.mInitialVolume),
    //mVolume(src.mVolume),
    mVolumeInv(src.mVolumeInv),
    mMetabolites(src.mMetabolites, this)
{
  mKey = GlobalKeys.add("Compartment", this);
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

  C_FLOAT64 tmpdbl;
  if ((Fail = configbuffer.getVariable("Volume", "C_FLOAT64",
                                       (void *) & tmpdbl)))
    return Fail;

  setInitialVolume(tmpdbl);

  return Fail;
}

const C_FLOAT64 & CCompartment::getVolumeInv() const {return mVolumeInv;}

CCopasiVectorNS < CMetab > & CCompartment::getMetabolites()
{return mMetabolites;}

const CCopasiVectorNS < CMetab > & CCompartment::getMetabolites() const
  {return mMetabolites;}

void CCompartment::setInitialValue(const C_FLOAT64 & initialValue)
{
  if (initialValue == mIValue) return;

  C_FLOAT64 Factor = 0;
  if (mIValue != 0.0)
    {
      Factor = initialValue / mIValue;
    }

  mIValue = initialValue;

  /* This assumes state==FIXED */
  setValue(initialValue);
  C_INT32 i, imax = mMetabolites.size();

  for (i = 0; i < imax; ++i)
    {
      //update particle numbers
      mMetabolites[i]->setInitialNumber(mMetabolites[i]->getInitialNumber() * Factor);
      mMetabolites[i]->setNumber(mMetabolites[i]->getNumber() * Factor);
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
  mValue = value;

  if (value != 0.0) mVolumeInv = 1.0 / value;
  else mVolumeInv = 2.0 * DBL_MAX;

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
