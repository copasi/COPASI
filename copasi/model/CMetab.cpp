// cmetab.cpp : implementation of the CMetab class
//

#include <iostream>
#include <string>
#include <vector>

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "utilities/CGlobals.h"
#include "CCompartment.h"
#include "CMetab.h"

/////////////////////////////////////////////////////////////////////////////
// CMetab

CMetab::CMetab()
{
  // initialize everything
  CONSTRUCTOR_TRACE;
  mName = "metab";

  if (!isValidName())
    fatalError();

  mConcDbl = Copasi->DefaultConc;

  mIConcDbl = Copasi->DefaultConc;

  mNumber = (C_INT32) (Copasi->DefaultConc * Copasi->DefaultVolume);

  mINumber = (C_INT32) (Copasi->DefaultConc * Copasi->DefaultVolume);

  mRate = 1.0;

  mTT = 0.0;

  mStatus = METAB_VARIABLE;

  mCompartment = NULL;
}

CMetab::CMetab(const CMetab & src)
{
  CONSTRUCTOR_TRACE;
  mName = src.mName;
  mConcDbl = src.mConcDbl;
  mIConcDbl = src.mIConcDbl;
  mNumber = src.mNumber;
  mINumber = src.mINumber;
  mRate = src.mRate;
  mTT = src.mTT;
  mStatus = src.mStatus;
  mCompartment = src.mCompartment;
}

#ifdef XXXX
CMetab::CMetab(const string & name)
{
  CONSTRUCTOR_TRACE;
  reset(name);
}

#endif // XXXX

// overload assignment operator
CMetab &CMetab::operator=(const CMetab &RHS)
{
  mName = RHS.mName;
  mConcDbl = RHS.mConcDbl;
  mIConcDbl = RHS.mIConcDbl;
  mNumber = RHS.mNumber;
  mINumber = RHS.mINumber;
  mRate = RHS.mRate;
  mTT = RHS.mTT;
  mStatus = RHS.mStatus;
  mCompartment = RHS.mCompartment;

  return *this;  // Assignment operator returns left side.
}

CMetab &CMetab::operator=(const CMetabOld &RHS)
{
  mName = RHS.mName;
  mConcDbl = RHS.mIConc;
  mIConcDbl = RHS.mIConc;
  mNumber = (C_INT32) RHS.mIConc;
  mINumber = (C_INT32) RHS.mIConc;
  mRate = 1.0;
  mTT = 0.0;
  mStatus = RHS.mStatus;
  mCompartment = NULL;

  return *this;  // Assignment operator returns left side.
}
CMetab::~CMetab() {DESTRUCTOR_TRACE; }
void CMetab::cleanup() {}

C_INT32 CMetab::load(CReadConfig &configbuffer)
{
  C_INT32 Fail = 0;

  Fail = configbuffer.getVariable("Metabolite", "string",
                                  (void *) & mName,
                                  CReadConfig::SEARCH);

  if (Fail)
    return Fail;

  Fail = configbuffer.getVariable("Concentration(double)", "C_FLOAT64",
                                  (void *) & mIConcDbl);

  if (Fail)
    return Fail;

  mConcDbl = mIConcDbl;

  Fail = configbuffer.getVariable("Concentration(long)", "C_INT32",
                                  (void *) & mINumber);

  if (Fail)
    return Fail;

  mNumber = mINumber;

  Fail = configbuffer.getVariable("Type", "C_INT16",
                                  (void *) & mStatus);

  if (Fail)
    return Fail;

  // sanity check
  if ((mStatus < 0) || (mStatus > 7))
    {
      CCopasiMessage(CCopasiMessage::WARNING,
                     "The file specifies a non-existing type "
                     "for '%s'.\nReset to internal metabolite.",
                     mName.c_str());
      mStatus = 1;
    }

  // sanity check
  if ((mStatus != METAB_MOIETY) && (mIConcDbl < 0.0))
    {
      CCopasiMessage(CCopasiMessage::WARNING,
                     "The file specifies a negative concentration "
                     "for '%s'.\nReset to default.",
                     mName.c_str());
      mIConcDbl = Copasi->DefaultConc;
    }

  return Fail;
}

C_INT32 CMetab::save(CWriteConfig &configbuffer)
{
  C_INT32 Fail = 0;

  Fail = configbuffer.setVariable("Metabolite", "string",
                                  (void *) & mName);

  if (Fail)
    return Fail;

  Fail = configbuffer.setVariable("Concentration(double)", "C_FLOAT64",
                                  (void *) & mIConcDbl);

  if (Fail)
    return Fail;

  Fail = configbuffer.setVariable("Concentration(long)", "C_INT32",
                                  (void *) & mINumber);

  if (Fail)
    return Fail;

  Fail = configbuffer.setVariable("Type", "C_INT16",
                                  (void *) & mStatus);

  return Fail;
}
const string & CMetab::getName() const { return mName; }

const C_FLOAT64 & CMetab::getConcentration() const
  {
    return mConcDbl;
  }

const C_INT32 & CMetab::getNumber() const
  {
    return mNumber;
  }
const C_FLOAT64 & CMetab::getInitialConcentration() const { return mIConcDbl; }

const C_INT32 & CMetab::getInitialNumber() const
  {
    return mINumber;
  }
const C_INT16 & CMetab::getStatus() const { return mStatus; }
CCompartment * CMetab::getCompartment() { return mCompartment; }

void CMetab::setTransitionTime(const C_FLOAT64 & transitionTime)
{mTT = transitionTime; }
const C_FLOAT64 & CMetab::getTransitionTime() { return mTT; }
void CMetab::setName(const string & name) {mName = name; }

void CMetab::setConcentration(const C_FLOAT64 concentration)
{
  mConcDbl = concentration;
  mNumber = (C_INT32) (concentration * mCompartment->getVolume());
}

void CMetab::setInitialConcentration(const C_FLOAT64 initialConcentration)
{
  mIConcDbl = initialConcentration;
  mINumber = (C_INT32) (initialConcentration * mCompartment->getVolume());
}

void CMetab::setNumber(const C_INT32 number)
{
  mNumber = number;
  mConcDbl = ((C_FLOAT64) number) * mCompartment->getVolumeInv();
}

void CMetab::setInitialNumber(const C_INT32 initialNumber)
{
  mINumber = initialNumber;
  mIConcDbl = ((C_FLOAT64) initialNumber) * mCompartment->getVolumeInv();
}
void CMetab::setStatus(const C_INT16 status) {mStatus = status; }

void CMetab::setCompartment(CCompartment * compartment)
{
  mCompartment = compartment;
}

C_INT16 CMetab::isValidName()
{
  return (mName.find_first_of("; ") == string::npos);
}
CMetabOld::CMetabOld() {CONSTRUCTOR_TRACE; }
CMetabOld::~CMetabOld() {DESTRUCTOR_TRACE; }
void CMetabOld::cleanup(){}

C_INT32 CMetabOld::load(CReadConfig &configbuffer)
{
  C_INT32 Fail = 0;

  Fail = configbuffer.getVariable("Metabolite", "string",
                                  (void *) & mName,
                                  CReadConfig::SEARCH);

  if (Fail)
    return Fail;

  Fail = configbuffer.getVariable("Concentration", "C_FLOAT64",
                                  (void *) & mIConc);

  if (Fail)
    return Fail;

  Fail = configbuffer.getVariable("Compartment", "C_INT32",
                                  (void *) & mCompartment);

  if (Fail)
    return Fail;

  C_INT32 Status;

  Fail = configbuffer.getVariable("Type", "C_INT32",
                                  (void *) & Status);

  mStatus = (C_INT16) Status;

  // sanity check
  if ((mStatus < 0) || (mStatus > 7))
    {
      CCopasiMessage(CCopasiMessage::WARNING,
                     "The file specifies a non-existing type "
                     "for '%s'.\nReset to internal metabolite.",
                     mName.c_str());
      mStatus = 1;
    }

  // sanity check
  if ((mStatus != METAB_MOIETY) && (mIConc < 0.0))
    {
      CCopasiMessage(CCopasiMessage::WARNING,
                     "The file specifies a negative concentration "
                     "for '%s'.\nReset to default.",
                     mName.c_str());
      mIConc = Copasi->DefaultConc;
    }

  return Fail;
}
C_INT32 CMetabOld::save(CWriteConfig & configbuffer){ return 0; }
C_INT32 CMetabOld::getIndex() const { return mCompartment; }
string CMetabOld::getName() const { return mName; }

/**
 * Returns the address of mIConcDbl  Wei Sun
 */
void * CMetab::getIConcAddr()
{
  return &mIConcDbl;
}

/**
 * Returns the address of mConcDbl
 */
void * CMetab::getConcAddr()
{
  return &mConcDbl;
}

/**
 * Returns the address of mTT
 */
void * CMetab::getTTAddr()
{
  return &mTT;
}

// non-member
bool operator<(const CMetab &lhs, const CMetab &rhs)
{
  // Do the comparison based on the name

  if (lhs.getName() < rhs.getName())
    {
      return true;
    }
  else
    {
      return false;
    }
}

/**
 * Return rate of production of this metaboLite
 */
const C_FLOAT64 & CMetab::getRate()
{
  return mRate;
}

void CMetab::setRate(const C_FLOAT64 & rate)
{
  mRate = rate * getCompartment()->getVolumeInv();
  //  calculateTransitionTime();
}
void CMetab::calculateTransitionTime(void) {mTT = mConcDbl / mRate; }

ostream & operator<<(ostream &os, const CMetab & d)
{
  os << "    ++++CMetab: " << d.mName << endl;
  os << "        mConcDbl " << d.mConcDbl << " mIConcDbl " << d.mIConcDbl << endl;
  os << "        mNumber " << d.mNumber << " mINumber " << d.mINumber << endl;
  os << "        mRate " << d.mRate << " mTT " << d.mTT << " mStatus " << d.mStatus << endl;

  if (d.mCompartment)
    os << "        *mCompartment " << d.mCompartment->getName() << endl;
  else
    os << "        mCompartment == 0 " << endl;

  os << "    ----CMetab " << endl;

  return os;
}
