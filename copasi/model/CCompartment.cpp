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
#include "utilities/utilities.h"
#include "report/CCopasiObjectReference.h"
#include "CCompartment.h"

CCompartment::CCompartment():
    CCopasiContainer("NoName", NULL, "Compartment"),
    mName(mObjectName),
    mVolume(Copasi->DefaultVolume),
    mVolumeInv(1 / Copasi->DefaultVolume),
    mMetabolites("Metabolites", this)
{CONSTRUCTOR_TRACE;}

CCompartment::CCompartment(const CCompartment & src):
    CCopasiContainer(src),
    mName(CCopasiContainer::mObjectName),
    mVolume(src.mVolume),
    mVolumeInv(src.mVolumeInv),
    mMetabolites(src.mMetabolites, this)
{
  CONSTRUCTOR_TRACE;

  for (unsigned C_INT32 i = 0; i < mMetabolites.size(); i++)
    mMetabolites[i]->setCompartment(this);
}

CCompartment::~CCompartment() {DESTRUCTOR_TRACE;}

void CCompartment::cleanup() {mMetabolites.cleanup();}

C_INT32 CCompartment::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;

  if ((Fail = configbuffer.getVariable("Compartment", "string",
                                       (void *) & mName,
                                       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("Volume", "C_FLOAT64",
                                       (void *) & mVolume)))
    return Fail;

  if (mVolume != 0)
    mVolumeInv = 1 / mVolume;

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

C_INT32 CCompartment::saveOld(CWriteConfig & configbuffer)
{
  C_INT32 Fail = 0;

  if ((Fail = configbuffer.setVariable("Compartment", "string",
                                       (void *) & mName)))
    return Fail;
  if ((Fail = configbuffer.setVariable("Volume", "C_FLOAT64",
                                       (void *) & mVolume)))
    return Fail;
  return Fail;
}

void CCompartment::saveSBML(std::ofstream &fout)
{
  std::string str;
  FixSName(mName, str);
  fout << "\t\t\t<compartment name=\"" << str << "\"";
  fout << " volume=\"" << mVolume << "\"/>" << std::endl;
}

const std::string & CCompartment::getName() const
  {
    return mName;
  }

const C_FLOAT64 & CCompartment::getVolume() const
  {
    return mVolume;
  }

const C_FLOAT64 & CCompartment::getVolumeInv() const
  {
    return mVolumeInv;
  }

CCopasiVectorNS < CMetab > & CCompartment::metabolites()
{
  return mMetabolites;
}

void CCompartment::setName(const std::string & name)
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
  //pMetabolite->setConcentration(pMetabolite->getConcentration());
  //pMetabolite->setInitialConcentration(pMetabolite->getInitialConcentration());
  // Volume is known now. But the model is not known. So we can not calculate numbers
  // from concentrations
  mMetabolites.add(pMetabolite);
}

bool CCompartment::isValidName(const std::string & name) const
  {return (name.find_first_of(" ") == std::string::npos);}

void CCompartment::initObjects()
{
  addObjectReference("Name", mName);
  addObjectReference("Volume", mVolume);
  add((CCopasiContainer *) &mMetabolites);
}

void * CCompartment::getVolumeAddr()
{
  return &mVolume;
}
