// cmetab.cpp : implementation of the CMetab class
//

#include <iostream>
#include <string>
#include <vector>

#include "copasi.h"
#include "CGlobals.h"
#include "CCompartment.h"
#include "CMetab.h"

/////////////////////////////////////////////////////////////////////////////
// CMetab

CMetab::CMetab()
{
    // initialize everything
    mName       = "metab";
    if (!IsValidName()) FatalError();
    mConc       = Copasi.DefaultConc;
    mIConc      = Copasi.DefaultConc;
    mRate       = 1.0;
    mTT         = 0.0;
    mStatus     = METAB_VARIABLE;
    mCompartment = NULL;
}

CMetab::CMetab(const string & name)
{
    Reset(name);
}

#ifdef XXXX
CMetab::CMetab(const string & name, const C_INT16 status, 
               CCompartment & compartment)
{
    mName        = name;
    mConc        = Copasi.DefaultConc;
    mIConc       = Copasi.DefaultConc;
    mRate        = 1.0;
    mTT          = 0.0;
    mStatus      = status;
    mCompartment = &compartment;
}
#endif // XXXX

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

CMetab::~CMetab() {}

C_INT32 CMetab::Reset(const string& name)
{
    // initialize everything
    mName        = name;
    if (!IsValidName()) FatalError();
    mConc        = mIConc;
    mRate        = 1.0;
    mTT          = 0.0;
    mStatus      = METAB_VARIABLE;
    mCompartment = NULL;

    return 0;
}


C_INT32 CMetab::Load(CReadConfig &configbuffer)
{
    C_INT32 Fail = 0;
    
    Fail = configbuffer.GetVariable("Metabolite", "string",
                                    (void *) &mName,
                                    CReadConfig::SEARCH);
    if (Fail) return Fail;

    Fail = configbuffer.GetVariable("Concentration", "C_FLOAT64",
                                    (void *) &mIConc);
    if (Fail) return Fail;
    mConc = mIConc;
    
    Fail = configbuffer.GetVariable("Type", "C_INT16",
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
        mIConc = Copasi.DefaultConc;
    }
    return Fail;
}


C_INT32 CMetab::Save(CWriteConfig &configbuffer)
{
    C_INT32 Fail = 0;
    
    Fail = configbuffer.SetVariable("Metabolite", "string",
                                    (void *) &mName);
    if (Fail) return Fail;

    Fail = configbuffer.SetVariable("Concentration", "C_FLOAT64",
                                    (void *) &mIConc);
    if (Fail) return Fail;

    Fail = configbuffer.SetVariable("Type", "C_INT16",
                                    (void *) &mStatus);
    return Fail;
}

string CMetab::GetName() const {return mName;}

C_INT16 CMetab::IsValidName()
{
    return (mName.find_first_of("; ") == string::npos);
}

C_INT32 CMetabOld::Load(CReadConfig &configbuffer)
{
    C_INT32 Fail = 0;
    
    Fail = configbuffer.GetVariable("Metabolite", "string",
                                    (void *) &mName,
                                    CReadConfig::SEARCH);
    if (Fail) return Fail;

    Fail = configbuffer.GetVariable("Concentration", "C_FLOAT64",
                                    (void *) &mIConc);
    if (Fail) return Fail;
    
    C_INT32 Index = -1;
    Fail = configbuffer.GetVariable("Compartment", "C_INT32",
                                    (void *) &mCompartment);
    if (Fail) return Fail;

    C_INT32 Status;
    Fail = configbuffer.GetVariable("Type", "C_INT32",
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
        mIConc = Copasi.DefaultConc;
    }
    return Fail;
}

C_INT32 CMetabOld::GetIndex() const {return mCompartment;}

string CMetabOld::GetName() const {return mName;}
