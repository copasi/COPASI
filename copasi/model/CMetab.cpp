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
  mName       = "metab";
  if (!isValidName()) fatalError();
  mConc       = Copasi->DefaultConc;
  mIConc      = Copasi->DefaultConc;
  mRate       = 1.0;
  mTT         = 0.0;
  mStatus     = METAB_VARIABLE;
  mCompartment = NULL;
}

CMetab::CMetab(const CMetab & src)
{
  CONSTRUCTOR_TRACE;
  mName        = src.mName;
  mConc        = src.mConc;
  mIConc       = src.mIConc;
  mRate        = src.mRate;
  mTT          = src.mTT;
  mStatus      = src.mStatus;
  mCompartment = src.mCompartment;
}

CMetab::CMetab(const string & name)
{
  CONSTRUCTOR_TRACE;
  reset(name);
}

// overload assignment operator
CMetab &CMetab::operator=(const CMetab &RHS)
{
  mName        = RHS.mName;
  mConc        = RHS.mConc;
  mIConc       = RHS.mIConc;
  mRate        = RHS.mRate;
  mTT          = RHS.mTT;
  mStatus      = RHS.mStatus;
  mCompartment = RHS.mCompartment;

  return *this;  // Assignment operator returns left side.
}

CMetab &CMetab::operator=(const CMetabOld &RHS)
{
  mName        = RHS.mName;
  mConc        = RHS.mIConc;
  mIConc       = RHS.mIConc;
  mRate        = 1.0;
  mTT          = 0.0;
  mStatus      = RHS.mStatus;
  mCompartment = NULL;

  return *this;  // Assignment operator returns left side.
}

CMetab::~CMetab() {DESTRUCTOR_TRACE;}

C_INT32 CMetab::reset(const string& name)
{
  // initialize everything
  mName        = name;
  if (!isValidName()) fatalError();
  mConc        = mIConc;
  mRate        = 1.0;
  mTT          = 0.0;
  mStatus      = METAB_VARIABLE;
  mCompartment = NULL;

  return 0;
}

void CMetab::cleanup() {} 

C_INT32 CMetab::load(CReadConfig &configbuffer)
{
  C_INT32 Fail = 0;
    
  Fail = configbuffer.getVariable("Metabolite", "string",
				  (void *) &mName,
				  CReadConfig::SEARCH);
  if (Fail) return Fail;

  Fail = configbuffer.getVariable("Concentration", "C_FLOAT64",
				  (void *) &mIConc);
  if (Fail) return Fail;
  mConc = mIConc;
    
  Fail = configbuffer.getVariable("Type", "C_INT16",
				  (void *) &mStatus);
  if (Fail) return Fail;

  // sanity check
  if ((mStatus<0) || (mStatus>7))
    {
      CCopasiMessage(CCopasiMessage::WARNING, 
		     "The file specifies a non-existing type "
		     "for '%s'.\nReset to internal metabolite.",
		     mName.c_str());
      mStatus = 1;
    }

  // sanity check
  if ((mStatus!=METAB_MOIETY) && (mIConc < 0.0))
    {
      CCopasiMessage(CCopasiMessage::WARNING, 
		     "The file specifies a negative concentration "
		     "for '%s'.\nReset to default.",
		     mName.c_str());
      mIConc = Copasi->DefaultConc;
    }
  return Fail;
}


C_INT32 CMetab::save(CWriteConfig &configbuffer)
{
  C_INT32 Fail = 0;
    
  Fail = configbuffer.setVariable("Metabolite", "string",
				  (void *) &mName);
  if (Fail) return Fail;

  Fail = configbuffer.setVariable("Concentration", "C_FLOAT64",
				  (void *) &mIConc);
  if (Fail) return Fail;

  Fail = configbuffer.setVariable("Type", "C_INT16",
				  (void *) &mStatus);
  return Fail;
}

const string & CMetab::getName() const {return mName;}

C_FLOAT64 * CMetab::getConcentration() {return &mConc;}

C_FLOAT64 CMetab::getNumber() const 
{
  return mConc * mCompartment->getVolume();
}

C_FLOAT64 * CMetab::getInitialConcentration() {return &mIConc;}

C_FLOAT64 CMetab::getInitialNumber() const 
{
  return mIConc * mCompartment->getVolume();
}

const C_INT16 & CMetab::getStatus() const {return mStatus;}

CCompartment * CMetab::getCompartment() {return mCompartment;} 

void CMetab::setTransitionTime(const C_FLOAT64 & transitionTime)
{mTT = transitionTime;} 

const C_FLOAT64 & CMetab::getTransitionTime() {return mTT;} 

void CMetab::setName(const string & name) {mName = name;}

void CMetab::setConcentration(const C_FLOAT64 concentration)
{
  mConc = concentration;
}

void CMetab::setInitialConcentration(const C_FLOAT64 initialConcentration)
{
  mIConc = initialConcentration;
}

void CMetab::setNumber(const C_FLOAT64 number)
{
  mConc = number / mCompartment->getVolume();
}

void CMetab::setStatus(const C_INT16 status) {mStatus = status;}

void CMetab::setCompartment(CCompartment * compartment) 
{
  mCompartment = compartment;
} 

C_INT16 CMetab::isValidName()
{
  return (mName.find_first_of("; ") == string::npos);
}

CMetabOld::CMetabOld() {CONSTRUCTOR_TRACE;}

CMetabOld::~CMetabOld() {DESTRUCTOR_TRACE;}

void  CMetabOld::cleanup(){}

C_INT32 CMetabOld::load(CReadConfig &configbuffer)
{
  C_INT32 Fail = 0;
    
  Fail = configbuffer.getVariable("Metabolite", "string",
				  (void *) &mName,
				  CReadConfig::SEARCH);
  if (Fail) return Fail;

  Fail = configbuffer.getVariable("Concentration", "C_FLOAT64",
				  (void *) &mIConc);
  if (Fail) return Fail;
    
  Fail = configbuffer.getVariable("Compartment", "C_INT32",
				  (void *) &mCompartment);
  if (Fail) return Fail;

  C_INT32 Status;
  Fail = configbuffer.getVariable("Type", "C_INT32",
				  (void *) &Status);
  mStatus = (C_INT16) Status;

  // sanity check
  if ((mStatus<0) || (mStatus>7))
    {
      CCopasiMessage(CCopasiMessage::WARNING, 
		     "The file specifies a non-existing type "
		     "for '%s'.\nReset to internal metabolite.",
		     mName.c_str());
      mStatus = 1;
    }

  // sanity check
  if ((mStatus!=METAB_MOIETY) && (mIConc < 0.0))
    {
      CCopasiMessage(CCopasiMessage::WARNING, 
		     "The file specifies a negative concentration "
		     "for '%s'.\nReset to default.",
		     mName.c_str());
      mIConc = Copasi->DefaultConc;
    }
  return Fail;
}

C_INT32 CMetabOld::save(CWriteConfig & configbuffer){return 0;}

C_INT32 CMetabOld::getIndex() const {return mCompartment;}

string CMetabOld::getName() const {return mName;}

/**
 *	Returns the address of mIConc		Wei Sun
 */
void * CMetab::getIConcAddr()
{
  return &mIConc;
}

/**
 *	Returns the address of mConc
 */
void * CMetab::getConcAddr()
{
  return &mConc;
}

/**
 *	Returns the address of mTT
 */
void * CMetab::getTTAddr()
{
  return &mTT;
}

// non-member
bool operator<(const CMetab &lhs, const CMetab &rhs)
{
    // Do the comparison based on the name
    if (lhs.getName() <  rhs.getName())
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
C_FLOAT64 CMetab::getRate()
{
	return mRate;
}
