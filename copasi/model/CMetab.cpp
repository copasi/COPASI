/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMetab.cpp,v $
   $Revision: 1.52 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/18 16:53:10 $
   End CVS Header */

// cmetab.cpp : implementation of the CMetab class
//

#include <iostream>
#include <string>
#include <vector>

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "utilities/CGlobals.h"
#include "utilities/utility.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"
#include "CCompartment.h"
#include "CModel.h"
#include "CMetab.h"

const CCompartment * CMetab::mpParentCompartment = NULL;

const std::string CMetab::StatusName[] =
  {"fixed", "independent", "dependent"};

void CMetab::setParentCompartment(const CCompartment * parentCompartment)
{mpParentCompartment = parentCompartment;}

/////////////////////////////////////////////////////////////////////////////
// CMetab

CMetab::CMetab(const std::string & name,
               const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Metabolite",
                     CCopasiObject::Container |
                     CCopasiObject::ValueDbl |
                     CCopasiObject::NonUniqueName),
    mKey(CKeyFactory::add("Metabolite", this)),
    mConcDbl(1.0),
    mIConcDbl(1.0),
    mNumberInt(1),
    mINumberInt(1),
    mRate(1.0),
    mTT(0.0),
    mStatus(METAB_VARIABLE)
{
  if (getObjectParent())
    {
      initModel();
      initCompartment(NULL);
    }

  initObjects();
  CONSTRUCTOR_TRACE;
}

CMetab::CMetab(const CMetab & src,
               const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(CKeyFactory::add("Metabolite", this)),
    mConcDbl(src.mConcDbl),
    mIConcDbl(src.mIConcDbl),
    mNumberInt(src.mNumberInt),
    mINumberInt(src.mINumberInt),
    mRate(src.mRate),
    mTT(src.mTT),
    mStatus(src.mStatus)
{
  initModel();
  initCompartment(src.mpCompartment);
  initObjects();
  CONSTRUCTOR_TRACE;
}

CMetab &CMetab::operator=(const CMetabOld &RHS)
{
  setObjectName(RHS.getObjectName());
  mConcDbl = RHS.mIConc;
  mIConcDbl = RHS.mIConc;
  mNumberInt = -1;
  mINumberInt = -1; // Invalid value, this causes checkConcentrationAndNumber() to fix it later
  mRate = 1.0;
  mTT = 0.0;
  mStatus = RHS.mStatus;
  mpCompartment = NULL;
  mpModel = NULL;

  return *this;  // Assignment operator returns left side.
}

CMetab::~CMetab()
{
  CKeyFactory::remove(mKey);
  DESTRUCTOR_TRACE;
}

void CMetab::cleanup() {}

void CMetab::initModel()
{
  mpModel = (CModel *) getObjectAncestor("Model");
  if (!mpModel) mpModel = Copasi->pModel;
}

void CMetab::initCompartment(const CCompartment * pCompartment)
{
  mpCompartment = (const CCompartment *) getObjectAncestor("Compartment");
  if (!mpCompartment) mpCompartment = pCompartment;
  if (!mpCompartment) mpCompartment = mpParentCompartment;
}

C_INT32 CMetab::load(CReadConfig &configbuffer)
{
  C_INT32 Fail = 0;

  std::string tmp;
  Fail = configbuffer.getVariable("Metabolite", "string",
                                  (void *) & tmp,
                                  CReadConfig::SEARCH);

  if (Fail)
    return Fail;
  setObjectName(tmp);

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
                     getObjectName().c_str());
      mStatus = 1;
    }

  // sanity check
  if ((mStatus != METAB_MOIETY) && (mIConcDbl < 0.0))
    {
      CCopasiMessage(CCopasiMessage::WARNING,
                     "The file specifies a negative concentration "
                     "for '%s'.\nReset to default.",
                     getObjectName().c_str());
      mIConcDbl = 1.0;
    }

  return Fail;
}

C_INT32 CMetab::save(CWriteConfig &configbuffer)
{
  C_INT32 Fail = 0;
  std::string tmp = getObjectName();
  Fail = configbuffer.setVariable("Metabolite", "string", &tmp);

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
  std::string tmp = getObjectName();
  Fail = configbuffer.setVariable("Metabolite", "string", &tmp);
  if (Fail)
    return Fail;
  Fail = configbuffer.setVariable("Concentration", "C_FLOAT64", (void *) & mIConcDbl);
  if (Fail)
    return Fail;
  c = mpModel->getCompartments().getIndex(mpCompartment->getName());
  Fail = configbuffer.setVariable("Compartment", "C_INT32", (void *) & c);
  if (Fail)
    return Fail;
  Fail = configbuffer.setVariable("Type", "C_INT16", (void *) & mStatus);
  return Fail;
}

void CMetab::saveSBML(std::ofstream &fout)
{
  std::string str;
  FixSName(getObjectName(), str);
  fout << "\t\t\t<specie name=\"" << str << "\"";
  FixSName(getCompartment()->getName(), str);
  fout << " compartment=\"" + str + "\"";
  fout << " initialAmount=\"" << mIConcDbl << "\"";
  fout << " boundaryCondition=\"";
  if (mStatus == METAB_FIXED)
    fout << "true";
  else
    fout << "false";
  fout << "\"/>" << std::endl;
}

std::string CMetab::getKey() const {return mKey;}

const std::string & CMetab::getName() const {return getObjectName();}

const C_FLOAT64 & CMetab::getConcentration() const {return mConcDbl;}

C_FLOAT64 CMetab::getNumberDbl() const
  {
    return mConcDbl * mpCompartment->getVolume()
    * mpModel->getQuantity2NumberFactor();
  }

const C_FLOAT64 & CMetab::getInitialConcentration() const
  {
    return mIConcDbl;
  }

C_FLOAT64 CMetab::getInitialNumberDbl() const
  {
    return mIConcDbl * mpCompartment->getVolume()
    * mpModel->getQuantity2NumberFactor();
  }

const C_INT16 & CMetab::getStatus() const
  {
    return mStatus;
  }

const CCompartment * CMetab::getCompartment() const
  {
    return mpCompartment;
  }

const CModel * CMetab::getModel() const
  {
    return mpModel;
  }

void CMetab::setTransitionTime(const C_FLOAT64 & transitionTime)
{
  mTT = transitionTime;
}

const C_FLOAT64 & CMetab::getTransitionTime() const
  {
    return mTT;
  }

bool CMetab::setName(const std::string & name)
{
  return setObjectName(name);
}

bool CMetab::setObjectParent(const CCopasiContainer * pParent)
{
  CCopasiObject::setObjectParent(pParent);

  initCompartment(NULL);
  initModel();

  return true;
}

// ***** set quantities ********

void CMetab::setConcentration(const C_FLOAT64 concentration)
{
  mConcDbl = concentration;
  mNumberInt = (C_INT32) (concentration * mpCompartment->getVolume()
                          * mpModel->getQuantity2NumberFactor());
}

void CMetab::setInitialConcentration(const C_FLOAT64 initialConcentration)
{
  mIConcDbl = initialConcentration;
  mINumberInt = (C_INT32) (initialConcentration * mpCompartment->getVolume()
                           * mpModel->getQuantity2NumberFactor());
}

void CMetab::setNumberDbl(const C_FLOAT64 number)
{
  mConcDbl = number * mpCompartment->getVolumeInv()
             * mpModel->getNumber2QuantityFactor();
  mNumberInt = (C_INT32) number;
}

void CMetab::setInitialNumberDbl(const C_FLOAT64 initialNumber)
{
  mIConcDbl = initialNumber * mpCompartment->getVolumeInv()
              * mpModel->getNumber2QuantityFactor();
  mINumberInt = (C_INT32) initialNumber;
}

//  ******************

void CMetab::setStatus(const C_INT16 status)
{
  mStatus = status;
}

void CMetab::setCompartment(const CCompartment * compartment)
{
  mpCompartment = compartment;
}

void CMetab::setModel(CModel * model)
{
  mpModel = model;
}

bool CMetab::isValidName(const std::string &name) const
  {
    return (name.find_first_of("; ") == std::string::npos);
  }

void CMetab::initObjects()
{
  addObjectReference("Concentration", mConcDbl, CCopasiObject::ValueDbl);
  addObjectReference("InitialConcentration", mIConcDbl, CCopasiObject::ValueDbl);
  addObjectReference("TransitionTime", mTT, CCopasiObject::ValueDbl);
}

CMetabOld::CMetabOld(const std::string & name,
                     const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Old Metabolite"),
    mIConc(1.0),
    mStatus(CMetab::METAB_VARIABLE),
    mCompartment()
{CONSTRUCTOR_TRACE;}

CMetabOld::CMetabOld(const CMetabOld & src,
                     const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mIConc(src.mIConc),
    mStatus(src.mStatus),
    mCompartment(src.mCompartment)
{CONSTRUCTOR_TRACE;}

CMetabOld::~CMetabOld() {DESTRUCTOR_TRACE;}

void CMetabOld::cleanup(){}

C_INT32 CMetabOld::load(CReadConfig &configbuffer)
{
  C_INT32 Fail = 0;
  std::string tmp;
  Fail = configbuffer.getVariable("Metabolite", "string",
                                  (void *) & tmp,
                                  CReadConfig::SEARCH);

  if (Fail)
    return Fail;
  setObjectName(tmp);

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
                     getObjectName().c_str());
      mStatus = 1;
    }

  // sanity check
  if ((mStatus != METAB_MOIETY) && (mIConc < 0.0))
    {
      CCopasiMessage(CCopasiMessage::WARNING,
                     "The file specifies a negative concentration "
                     "for '%s'.\nReset to default.",
                     getObjectName().c_str());
      mIConc = 1.0;
    }

  return Fail;
}
C_INT32 CMetabOld::save(CWriteConfig & C_UNUSED(configbuffer)){return 0;}
C_INT32 CMetabOld::getIndex() const {return mCompartment;}
const std::string & CMetabOld::getName() const {return getObjectName();}

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
const C_FLOAT64 & CMetab::getRate() const
  {
    return mRate;
  }

void CMetab::setRate(const C_FLOAT64 & rate)
{
  mRate = rate * getCompartment()->getVolumeInv()
          * mpModel->getNumber2QuantityFactor();
  //  calculateTransitionTime();
}
void CMetab::calculateTransitionTime(void) {mTT = mConcDbl / mRate;}

void * CMetab::getReference() const
  {return const_cast<C_FLOAT64 *>(&mConcDbl);}

std::ostream & operator<<(std::ostream &os, const CMetab & d)
{
  os << "    ++++CMetab: " << d.getObjectName() << std::endl;
  os << "        mConcDbl " << d.mConcDbl << " mIConcDbl " << d.mIConcDbl << std::endl;
  os << "        mNumberInt " << d.mNumberInt << " mINumberInt " << d.mINumberInt << std::endl;
  os << "        mRate " << d.mRate << " mTT " << d.mTT << " mStatus " << d.mStatus << std::endl;

  if (d.mpCompartment)
    os << "        mpCompartment == " << d.mpCompartment << std::endl;
  else
    os << "        mpCompartment == 0 " << std::endl;

  if (d.mpModel)
    os << "        mpModel == " << d.mpModel << std::endl;
  else
    os << "        mpModel == 0 " << std::endl;

  os << "    ----CMetab " << std::endl;

  return os;
}
