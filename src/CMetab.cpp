// cmetab.cpp : implementation of the CMetab class
//

#include <iostream>
#include <string>
#include <vector>

#include "copasi.h"
#include "globals.h"
#include "CReadConfig.h"
#include "CWriteConfig.h"
#include "CCompartment.h"
#include "CMetab.h"

/////////////////////////////////////////////////////////////////////////////
// CMetab

CMetab::CMetab()
{
    // initialize everything
    mName       = "metab";
    mConc       = DefaultConc;
    mIConc      = DefaultConc;
    mRate       = 1.0;
    mTT         = 0.0;
    mStatus     = METAB_VARIABLE;
}

CMetab::CMetab(const string & name)
{
    Reset(name);
}

CMetab::CMetab(const string & name, const short status, 
               const string & compartment)
{
    mName        = name;
    mConc        = DefaultConc;
    mIConc       = DefaultConc;
    mRate        = 1.0;
    mTT          = 0.0;
    mStatus      = status;
    mCompartment = compartment;
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

CMetab::~CMetab() {}

long CMetab::Reset(const string& name)
{
    // initialize everything
    mName        = name;
    mConc        = mIConc;
    mRate        = 1.0;
    mTT          = 0.0;
    mStatus      = METAB_VARIABLE;
    mCompartment = "";

    return 0;
}


long CMetab::Load(CReadConfig &configbuffer)
{
    long Fail = 0;
    
    Fail = configbuffer.GetVariable("Metabolite", "string",
                                    (void *) &mName,
                                    CReadConfig::SEARCH);
    if (Fail) return Fail;

    Fail = configbuffer.GetVariable("Concentration", "double",
                                    (void *) &mIConc);
    if (Fail) return Fail;

    long Index = -1;
    Fail = configbuffer.GetVariable("Compartment", "string",
                                    (void *) &mCompartment);
    if (Fail) return Fail;

    long Status;
    Fail = configbuffer.GetVariable("Type", "long",
                                    (void *) &Status);
    mStatus = (short) Status;

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
        mIConc = DefaultConc;
    }
    return Fail;
}


long CMetab::Save(CWriteConfig &configbuffer)
{
    long Fail = 0;
    
    Fail = configbuffer.SetVariable("Metabolite", "string",
                                    (void *) &mName);
    if (Fail) return Fail;

    Fail = configbuffer.SetVariable("Concentration", "double",
                                    (void *) &mIConc);
    if (Fail) return Fail;

    Fail = configbuffer.SetVariable("Compartment", "string",
                                    (void *) &mCompartment);
    if (Fail) return Fail;

    long Status = (long) mStatus;
    Fail = configbuffer.SetVariable("Type", "long",
                                    (void *) &Status);
    return Fail;
}

string CMetab::GetName() {return mName;}
