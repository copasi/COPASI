// CCompartment
//
// Derived from Gepasi's ccompart.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Pedro Mendes

#include <iostream>

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "utilities/CGlobals.h"
#include "CCompartment.h"
#include "utilities/utilities.h"

CCompartment::CCompartment()
{
  CONSTRUCTOR_TRACE;
  // initialize everything
  mName = "compartment";
  mVolume = Copasi->DefaultVolume;
  mVolumeInv = 1 / Copasi->DefaultVolume;
}

CCompartment::CCompartment(const CCompartment & src)
{
  CONSTRUCTOR_TRACE;
  mName = src.mName;
  mVolume = src.mVolume;
  mVolumeInv = src.mVolumeInv;
  mMetabolites = CCopasiVectorNS < CMetab >(src.mMetabolites);

  for (unsigned C_INT32 i = 0; i < mMetabolites.size(); i++)
    mMetabolites[i]->setCompartment(this);
}

CCompartment::CCompartment(const string & name,
                           C_FLOAT64 volume)
{
  CONSTRUCTOR_TRACE;
  // initialize everything
  mName = name;

  if (!isValidName())
    fatalError();

  mVolume = volume;

  mVolumeInv = 1 / volume;
}
CCompartment::~CCompartment() {DESTRUCTOR_TRACE; }
// void CCompartment::initialize() {}
void CCompartment::cleanup() {mMetabolites.cleanup(); }

CCompartment & CCompartment::operator=(const CCompartment & rhs)
{
  mName = rhs.mName;
  mVolume = rhs.mVolume;
  mVolumeInv = rhs.mVolumeInv;

  mMetabolites = CCopasiVectorNS < CMetab >(rhs.mMetabolites);

  return *this;
}

C_INT32 CCompartment::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;
  // initialize();

  if ((Fail = configbuffer.getVariable("Compartment", "string",
                                       (void *) & mName,
                                       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("Volume", "C_FLOAT64",
                                       (void *) & mVolume)))
    return Fail;

  if (configbuffer.getVersion() < "4")
    return Fail;

  C_INT32 MetabolitesNo;

  if ((Fail = configbuffer.getVariable("MetabolitesNo", "C_INT32",
                                       (void *) & MetabolitesNo)))
    return Fail;

  mMetabolites.load(configbuffer, MetabolitesNo);

  return Fail;
}

C_INT32 CCompartment::save(CWriteConfig & configbuffer)
{
  C_INT32 Fail = 0;

  if ((Fail = configbuffer.setVariable("Compartment", "string",
                                       (void *) & mName)))
    return Fail;

  if ((Fail = configbuffer.setVariable("Volume", "C_FLOAT64",
                                       (void *) & mVolume)))
    return Fail;

  C_INT32 size = mMetabolites.size();

  if ((Fail = configbuffer.setVariable("MetabolitesNo", "C_INT32",
                                       (void *) & size)))
    return Fail;

  mMetabolites.save(configbuffer);

  return Fail;
}
string CCompartment::getName() const { return mName; }
const C_FLOAT64 & CCompartment::getVolume() const { return mVolume; }
const C_FLOAT64 & CCompartment::getVolumeInv() const { return mVolumeInv; }

CCopasiVectorNS < CMetab > & CCompartment::metabolites()
{ return mMetabolites; }

void CCompartment::setName(const string & name)
{
  mName = name;
  //if (!isValidName()) fatalError();
}

void CCompartment::setVolume(C_FLOAT64 volume)
{
  mVolume = volume;
  mVolumeInv = 1.0 / volume;
}

void CCompartment::addMetabolite(CMetab &metabolite)
{
  CMetab *pMetabolite = new CMetab(metabolite);

  pMetabolite->setCompartment(this);
  mMetabolites.add(pMetabolite);
}

C_INT16 CCompartment::isValidName() const
  {
    return (mName.find_first_of(" ") == string::npos);
  }

void * CCompartment::getVolumeAddr()
{
  return &mVolume;
}

ostream & operator<<(ostream &os, const CCompartment & d)
{
  os << "++++CCompartment: " << d.mName << " mVolume " << d.mVolume
  << " mVolumeInv " << d.mVolumeInv << endl;
  os << "    CCompartment.mMetabolites " << endl << d.mMetabolites ;
  os << "----CCompartment " << endl;

  return os;
}
