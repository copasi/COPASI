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
#include "utilities/readwrite.h"
#include "utilities/CCopasiVector.h"
#include "utilities/utility.h"
#include "report/CCopasiObjectReference.h"
#include "CCompartment.h"

CCompartment::CCompartment(const std::string & name,
                           const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Compartment"),
    mName(mObjectName),
    mInitialVolume(1.0),
    mVolume(1.0),
    mVolumeInv(1.0),
    mMetabolites("Metabolites", this)
{
  initObjects();
  CONSTRUCTOR_TRACE;
}

CCompartment::CCompartment(const CCompartment & src,
                           const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mName(CCopasiContainer::mObjectName),
    mInitialVolume(src.mInitialVolume),
    mVolume(src.mVolume),
    mVolumeInv(src.mVolumeInv),
    mMetabolites(src.mMetabolites, this)
{
  CONSTRUCTOR_TRACE;
  initObjects();
  //  for (unsigned C_INT32 i = 0; i < mMetabolites.size(); i++)
  //    mMetabolites[i]->setCompartment(this);
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
                                       (void *) & mInitialVolume)))
    return Fail;

  setVolume(mInitialVolume);

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

const std::string & CCompartment::getName() const {return mName;}

const C_FLOAT64 & CCompartment::getInitialVolume() const
  {return mInitialVolume;}

const C_FLOAT64 & CCompartment::getVolume() const {return mVolume;}

const C_FLOAT64 & CCompartment::getVolumeInv() const {return mVolumeInv;}

CCopasiVectorNS < CMetab > & CCompartment::getMetabolites()
{return mMetabolites;}

const CCopasiVectorNS < CMetab > & CCompartment::getMetabolites() const
  {return mMetabolites;}

void CCompartment::setName(const std::string & name)
{
  mName = name;
  //if (!isValidName()) fatalError();
}

void CCompartment::setInitialVolume(C_FLOAT64 volume)
{
  mInitialVolume = volume;

  /* This has to be moved to the state */
  setVolume(volume);
}

void CCompartment::setVolume(C_FLOAT64 volume)
{
  mVolume = volume;

  if (volume != 0.0) mVolumeInv = 1.0 / volume;
  else mVolumeInv = DBL_MAX;
}

/* Note: the metabolite stored in mMetabolites has definetly mpCompartment set.
   In the case the compartment is part of a model also mpModel is set. */
void CCompartment::addMetabolite(CMetab &metabolite)
{mMetabolites.add(metabolite);}

#ifdef XXXX
void CCompartment::addMetabolite(CMetab &metabolite)
{
  CMetab *pMetabolite = new CMetab(metabolite, this);

  pMetabolite->setCompartment(this);
  //pMetabolite->setConcentration(pMetabolite->getConcentration());
  //pMetabolite->setInitialConcentration(pMetabolite->getInitialConcentration());
  // Volume is known now. But the model is not known. So we can not calculate numbers
  // from concentrations
  mMetabolites.add(pMetabolite);
}
#endif // XXXX

bool CCompartment::isValidName(const std::string & name) const
  {return (name.find_first_of(" ") == std::string::npos);}

void CCompartment::initObjects()
{
  addObjectReference("Name", mName);
  addObjectReference("Volume", mVolume);
  add(&mMetabolites);
}

void * CCompartment::getVolumeAddr()
{
  return &mVolume;
}
