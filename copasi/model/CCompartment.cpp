// CCompartment 
// 
// Derived from Gepasi's ccompart.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Pedro Mendes

#include <iostream>

#include "copasi.h"
#include "CCompartment.h"
#include "utilities/utilities.h"

CCompartment::CCompartment()
{
  // initialize everything
  mName   = "compartment";
  mVolume = 1.0;
}

CCompartment::CCompartment(const CCompartment & src)
{
  mName        = src.mName;
  mVolume      = src.mVolume;

  mMetabolites = CCopasiVectorNS < CMetab >(src.mMetabolites);
  for (unsigned C_INT32 i = 0; i < mMetabolites.size(); i++)
    mMetabolites[i]->setCompartment(this);
}


CCompartment::CCompartment(const string & name,
                           C_FLOAT64 volume)
{
  // initialize everything
  mName   = name;
  if (!isValidName()) fatalError();
  mVolume = volume;
}

CCompartment::~CCompartment() {}

// void CCompartment::initialize() {}

void CCompartment::cleanup() {mMetabolites.cleanup();}

CCompartment & CCompartment::operator=(const CCompartment & rhs)
{
  mName        = rhs.mName;
  mVolume      = rhs.mVolume;

  mMetabolites = CCopasiVectorNS < CMetab >(rhs.mMetabolites);
    
  return *this;
}

C_INT32 CCompartment::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;
  // initialize();
    
  if ((Fail = configbuffer.getVariable("Compartment", "string",
				       (void *) &mName,
				       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("Volume", "C_FLOAT64",
				       (void *) &mVolume)))
    return Fail;
    
  if (configbuffer.getVersion() < "4") return Fail;
    
  C_INT32 MetabolitesNo;
  if ((Fail = configbuffer.getVariable("MetabolitesNo", "C_INT32",
				       (void *) &MetabolitesNo)))
    return Fail;
    
  mMetabolites.load(configbuffer, MetabolitesNo);
    
  return Fail;
}

C_INT32 CCompartment::save(CWriteConfig & configbuffer)
{
  C_INT32 Fail = 0;

  if ((Fail = configbuffer.setVariable("Compartment", "string",
				       (void *) &mName)))
    return Fail;

  if ((Fail = configbuffer.setVariable("Volume", "C_FLOAT64",
				       (void *) &mVolume)))
    return Fail;
    
  C_INT32 size = mMetabolites.size();
  if ((Fail = configbuffer.setVariable("MetabolitesNo", "C_INT32",
				       (void *) &size)))
    return Fail;

  mMetabolites.save(configbuffer);
  return Fail;
}

string CCompartment::getName() const {return mName;}

C_FLOAT64 CCompartment::getVolume() const {return mVolume;}

CCopasiVectorNS < CMetab > & CCompartment::metabolites() 
{return mMetabolites;}

void CCompartment::setName(const string & name) 
{
  mName = name;
  if (!isValidName()) fatalError();
}

void CCompartment::setVolume(C_FLOAT64 volume) {mVolume = volume;}

void CCompartment::addMetabolite(CMetab &metabolite)
{
  metabolite.setCompartment(this);
  mMetabolites.add(metabolite);
}

C_INT16 CCompartment::isValidName() const
{
  return (mName.find_first_of("; ") == string::npos);
}

void * CCompartment::getVolumeAddr()
{
  return &mVolume;
}
