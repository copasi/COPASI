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
    Compartment = NULL;
    mFail       = 0;
}

CMetab::CMetab(string name)
{
    Reset(name);
}

CMetab::CMetab(string name, short status, 
               CCompartment &compartment)
{
    mName       = name;
    mConc       = DefaultConc;
    mIConc      = DefaultConc;
    mRate       = 1.0;
    mTT         = 0.0;
    mStatus     = status;
    Compartment = &compartment;
    mFail       = 0;
}

// overload assignment operator
CMetab &CMetab::operator=(const CMetab &RHS)
{
    mName       = RHS.mName;
    mConc       = RHS.mConc;
    mIConc      = RHS.mIConc;
    mRate       = RHS.mRate;
    mTT         = RHS.mTT;
    mStatus     = RHS.mStatus;
    Compartment = RHS.Compartment;
    mFail       = RHS.mFail;

    return *this;  // Assignment operator returns left side.
}

int CMetab::Reset(string name)
{
    // initialize everything
    mName       = name;
    mConc       = mIConc;
    mRate       = 1.0;
    mTT         = 0.0;
    mStatus     = METAB_VARIABLE;
    Compartment = NULL;
    mFail       = 0;

    return mFail;
}


int CMetab::Load(CReadConfig &configbuffer,
                 CCompartmentVector &list)
{
    mFail = configbuffer.GetVariable((string) "Metabolite",
                                     (string) "string",
                                     (void *) &mName);
    if (mFail) return mFail;
    configbuffer.SetMode(-CReadConfig_SEARCH);

    mFail = configbuffer.GetVariable((string) "Concentration", 
                                     (string) "double",
                                     (void *) &mIConc);
    if (mFail) return mFail;

    int Index = -1;
    mFail = configbuffer.GetVariable((string) "Compartment", 
                                     (string) "int",
                                     (void *) &Index);
    if (mFail) return mFail;

    // sanity check
    if( Index < 0 )
    {
        CCopasiMessage(WARNING, 
                       "The file specifies a non-existing compartment "
                       "for '%s'.\nReset to the default compartment.",
                       mName.c_str());
        Index = 0;
    }
    Compartment = &list[Index];

    int Status;
    mFail = configbuffer.GetVariable((string) "Type", 
                                     (string) "int",
                                     (void *) &Status);
    mStatus = (short) Status;

    // sanity check
    if ((mStatus<0) || (mStatus>7))
    {
        CCopasiMessage(WARNING, 
                       "The file specifies a non-existing type "
                       "for '%s'.\nReset to internal metabolite.",
                       mName.c_str());
        mStatus = 1;
    }

    // sanity check
    if ((mStatus!=METAB_MOIETY) && (mIConc < 0.0))
    {
        CCopasiMessage(WARNING, 
                       "The file specifies a negative concentration "
                       "for '%s'.\nReset to default.",
                       mName.c_str());
        mIConc = DefaultConc;
    }
    return mFail;
}


int CMetab::Save(CWriteConfig &configbuffer,
                 CCompartmentVector &list)
{
    mFail = configbuffer.SetVariable((string) "Metabolite",
                                     (string) "string",
                                     (void *) &mName);
    if (mFail) return mFail;

    mFail = configbuffer.SetVariable((string) "Concentration", 
                                     (string) "double",
                                     (void *) &mIConc);
    if (mFail) return mFail;

    int Index = Compartment - &list.front();
    mFail = configbuffer.SetVariable((string) "Compartment", 
                                     (string) "int",
                                     (void *) &Index);
    if (mFail) return mFail;

    int Status = (int) mStatus;
    mFail = configbuffer.SetVariable((string) "Type", 
                                     (string) "int",
                                     (void *) &Status);
    return mFail;
}

CMetabVector::CMetabVector()
{
    mFail = 0;
    this->resize(0);
}

CMetabVector::CMetabVector(int size)
{
    mFail = 0;
    this->resize(size);
}

int CMetabVector::Save(CWriteConfig &configbuffer,
		       CCompartmentVector &list)
{
    int Size = this->size();
    
    mFail = configbuffer.SetVariable((string) "TotalMetabolites",
                                     (string) "int",
                                     (void *) &Size);
    if (mFail) return mFail;

    for(int i = 0; i < Size; i++)
    {

        if (mFail = (*(&this->front()+i)).Save(configbuffer, list))
        {
            break;
        }
    }
    return mFail;
}

int CMetabVector::Load(CReadConfig &configbuffer,
		       CCompartmentVector &list)
{
    int Size = 0;
    
    configbuffer.SetMode(CReadConfig_SEARCH);
    configbuffer.SetMode(CReadConfig_LOOP);
    
    mFail = configbuffer.GetVariable((string) "TotalMetabolites",
                                     (string) "int",
                                     (void *) &Size);
    if (mFail) return mFail;
    this->resize(Size);
    
    configbuffer.SetMode(-CReadConfig_LOOP);
    for(int i = 0; i < Size; i++)
    {
        if (mFail = (*(&this->front()+i)).Load(configbuffer, list))
        {
            break;
        }
    }
    
    return mFail;
}

int CMetabVector::Fail()
{
    return mFail;
}
