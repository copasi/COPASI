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

const CCompartment * CMetab::mpParentCompartment = NULL;

void CMetab::setParentCompartment(const CCompartment * parentCompartment)
{mpParentCompartment = parentCompartment; }

/////////////////////////////////////////////////////////////////////////////
// CMetab

CMetab::CMetab(const CModel * pModel)
{
  if (pModel)
    mpModel = pModel;
  else
    mpModel = Copasi->Model;

  // initialize everything
  CONSTRUCTOR_TRACE;
  mName = "metab";

  if (!isValidName())
    fatalError();

  mConcDbl = Copasi->DefaultConc;
  mIConcDbl = Copasi->DefaultConc;
  mNumberInt = (C_INT32) (Copasi->DefaultConc * Copasi->DefaultVolume);
  mINumberInt = (C_INT32) (Copasi->DefaultConc * Copasi->DefaultVolume);
  mRate = 1.0;
  mTT = 0.0;
  mStatus = METAB_VARIABLE;
  mCompartment = const_cast<CCompartment *>(mpParentCompartment);
}

CMetab::CMetab(const CMetab & src)
{
  CONSTRUCTOR_TRACE;
  mName = src.mName;
  mConcDbl = src.mConcDbl;
  mIConcDbl = src.mIConcDbl;
  mNumberInt = src.mNumberInt;
  mINumberInt = src.mINumberInt;
  mRate = src.mRate;
  mTT = src.mTT;
  mStatus = src.mStatus;
  mCompartment = src.mCompartment;
  mpModel = src.mpModel;
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
  mNumberInt = RHS.mNumberInt;
  mINumberInt = RHS.mINumberInt;
  mRate = RHS.mRate;
  mTT = RHS.mTT;
  mStatus = RHS.mStatus;
  mCompartment = RHS.mCompartment;
  mpModel = RHS.mpModel;

  return *this;  // Assignment operator returns left side.
}

CMetab &CMetab::operator=(const CMetabOld &RHS)
{
  mName = RHS.mName;
  mConcDbl = RHS.mIConc;
  mIConcDbl = RHS.mIConc;
  mNumberInt = -1;
  mINumberInt = -1; // Invalid value, this causes checkConcentrationAndNumber() to fix it later
  mRate = 1.0;
  mTT = 0.0;
  mStatus = RHS.mStatus;
  mCompartment = NULL;
  mpModel = NULL;

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

  Fail = configbuffer.getVariable("InitialConcentration", "C_FLOAT64",
                                  (void *) & mIConcDbl);

  setInitialConcentration(mIConcDbl);
  setConcentration(mIConcDbl);

  Fail = configbuffer.getVariable("InitialParticleNumber", "C_INT32",
                                  (void *) & mINumberInt);

  if (Fail)
    return Fail; // is it really necessary to load and save both representations of quantity?

  mNumberInt = mINumberInt;

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

  Fail = configbuffer.setVariable("InitialConcentration", "C_FLOAT64",
                                  (void *) & mIConcDbl);

  if (Fail)
    return Fail;

  Fail = configbuffer.setVariable("InitialParticleNumber", "C_INT32",
                                  (void *) & mINumberInt);

  if (Fail)
    return Fail; // is it really necessary to load and save both representations of quantity?

  Fail = configbuffer.setVariable("Type", "C_INT16",
                                  (void *) & mStatus);

  return Fail;
}

C_INT32 CMetab::saveOld(CWriteConfig &configbuffer)
{
  C_INT32 c, Fail = 0;

  Fail = configbuffer.setVariable("Metabolite", "string", (void *) & mName);
  if (Fail)
    return Fail;
  Fail = configbuffer.setVariable("Concentration", "C_FLOAT64", (void *) & mIConcDbl);
  if (Fail)
    return Fail;
  c = mpModel->getCompartments().getIndex(mCompartment->getName());
  Fail = configbuffer.setVariable("Compartment", "C_INT32", (void *) & c);
  if (Fail)
    return Fail;
  Fail = configbuffer.setVariable("Type", "C_INT16", (void *) & mStatus);
  return Fail;
}

void CMetab::saveSBML(std::ofstream &fout)
{
  string str;
  FixSName(mName, str);
  fout << "\t\t\t<specie name=\"" << str << "\"";
  FixSName(getCompartment()->getName(), str);
  fout << " compartment=\"" + str + "\"";
  fout << " initialAmount=\"" << mIConcDbl << "\"";
  fout << " boundaryCondition=\"";
  if (mStatus == METAB_FIXED)
    fout << "true";
  else
    fout << "false";
  fout << "\"/>" << endl;
}

const string & CMetab::getName() const
  {
    return mName;
  }

const C_FLOAT64 & CMetab::getConcentration() const
  {
    return mConcDbl;
  }

const C_INT32 & CMetab::getNumberInt() const
  {
    return mNumberInt;
  }

C_FLOAT64 CMetab::getNumberDbl() const
  {
    return mConcDbl * mCompartment->getVolume()
           * mpModel->getQuantity2NumberFactor();
  }

const C_FLOAT64 & CMetab::getInitialConcentration() const
  {
    return mIConcDbl;
  }

const C_INT32 & CMetab::getInitialNumberInt() const
  {
    return mINumberInt;
  }

C_FLOAT64 CMetab::getInitialNumberDbl() const
  {
    return mIConcDbl * mCompartment->getVolume()
           * mpModel->getQuantity2NumberFactor();
  }

const C_INT16 & CMetab::getStatus() const
  {
    return mStatus;
  }

CCompartment * CMetab::getCompartment()
{
  return mCompartment;
}

const CModel * CMetab::getModel() const
  {
    return mpModel;
  }

void CMetab::setTransitionTime(const C_FLOAT64 & transitionTime)
{
  mTT = transitionTime;
}

const C_FLOAT64 & CMetab::getTransitionTime()
{
  return mTT;
}

void CMetab::setName(const string & name)
{
  mName = name;
}

// ***** set quantities ********

void CMetab::setConcentration(const C_FLOAT64 concentration)
{
  mConcDbl = concentration;
  mNumberInt = (C_INT32) (concentration * mCompartment->getVolume()
                          * mpModel->getQuantity2NumberFactor());
}

void CMetab::setInitialConcentration(const C_FLOAT64 initialConcentration)
{
  mIConcDbl = initialConcentration;
  mINumberInt = (C_INT32) (initialConcentration * mCompartment->getVolume()
                           * mpModel->getQuantity2NumberFactor());
}

void CMetab::setNumberInt(const C_INT32 number)
{
  mNumberInt = number;
  mConcDbl = ((C_FLOAT64) number) * mCompartment->getVolumeInv()
             * mpModel->getNumber2QuantityFactor();
}

void CMetab::setInitialNumberInt(const C_INT32 initialNumber)
{
  mINumberInt = initialNumber;
  mIConcDbl = ((C_FLOAT64) initialNumber) * mCompartment->getVolumeInv()
              * mpModel->getNumber2QuantityFactor();
}

void CMetab::setNumberDbl(const C_FLOAT64 number)
{
  mConcDbl = number * mCompartment->getVolumeInv()
             * mpModel->getNumber2QuantityFactor();
  mNumberInt = (C_INT32) number;
}

void CMetab::setInitialNumberDbl(const C_FLOAT64 initialNumber)
{
  mIConcDbl = initialNumber * mCompartment->getVolumeInv()
              * mpModel->getNumber2QuantityFactor();
  mINumberInt = (C_INT32) initialNumber;
}

//  ******************

void CMetab::setStatus(const C_INT16 status)
{
  mStatus = status;
}

void CMetab::setCompartment(CCompartment * compartment)
{
  mCompartment = compartment;
}

void CMetab::setModel(CModel * model)
{
  mpModel = model;
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
C_INT32 CMetabOld::save(CWriteConfig & C_UNUSED(configbuffer)){ return 0; }
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
  mRate = rate * getCompartment()->getVolumeInv()
          * mpModel->getNumber2QuantityFactor();
  //  calculateTransitionTime();
}
void CMetab::calculateTransitionTime(void) {mTT = mConcDbl / mRate; }

void CMetab::checkConcentrationAndNumber()
{
  if (mNumberInt < 0)
    {
      setConcentration(getConcentration());
      setInitialConcentration(getInitialConcentration());
    }

  if (mConcDbl < 0)
    {
      setNumberInt(getNumberInt());
      setInitialNumberInt(getInitialNumberInt());
    }
}
