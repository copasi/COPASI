// CCompartment 
// 
// Derived from Gepasi's ccompart.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Pedro Mendes

#include <iostream>

#include "copasi.h"
#include "CCompartment.h"
#include "utilities.h"

CCompartment::CCompartment()
{
    // initialize everything
    mName   = "compartment";
    mVolume = 1.0;
    mMetabolites = NULL;
}

void CCompartment::Init()
{
    if (!mMetabolites) mMetabolites = new CCopasiVector < CMetab >;
}

CCompartment::CCompartment(const string & name,
                           C_FLOAT64 volume)
{
    // initialize everything
    mName   = name;
    if (!IsValidName()) FatalError();
    mVolume = volume;
    mMetabolites = NULL;
}

CCompartment::~CCompartment() 
{
    cout << "~CCompartment " << mName << endl;
}

void CCompartment::Delete()
{
    if (mMetabolites) delete mMetabolites;
    mMetabolites = NULL;
}

CCompartment & CCompartment::operator=(const CCompartment & rhs)
{
    mName        = rhs.mName;
    mVolume      = rhs.mVolume;
    mMetabolites = rhs.mMetabolites;
    
    return *this;
}

C_INT32 CCompartment::Load(CReadConfig & configbuffer)
{
    C_INT32 Fail = 0;
    Init();
    
    if (Fail = configbuffer.GetVariable("Compartment", "string",
                                        (void *) &mName,
                                        CReadConfig::SEARCH))
        return Fail;

    if (Fail = configbuffer.GetVariable("Volume", "C_FLOAT64",
                                        (void *) &mVolume))
        return Fail;
    
    if (configbuffer.GetVersion() < "4") return Fail;
    
    C_INT32 MetabolitesNo;
    if (Fail = configbuffer.GetVariable("MetabolitesNo", "C_INT32",
                                        (void *) &MetabolitesNo))
        return Fail;
    
    Fail = mMetabolites->Load(configbuffer, MetabolitesNo);
    
    return Fail;
}

C_INT32 CCompartment::Save(CWriteConfig & configbuffer)
{
    C_INT32 Fail = 0;

    if (Fail = configbuffer.SetVariable("Compartment", "string",
                                        (void *) &mName))
        return Fail;

    if (Fail = configbuffer.SetVariable("Volume", "C_FLOAT64",
                                        (void *) &mVolume))
        return Fail;
    
    C_INT32 size = mMetabolites->Size();
    if (Fail = configbuffer.SetVariable("MetabolitesNo", "C_INT32",
                                        (void *) &size))
        return Fail;

    Fail = mMetabolites->Save(configbuffer);
    return Fail;
}

string CCompartment::GetName() {return mName;}

C_FLOAT64 CCompartment::GetVolume() {return mVolume;}

CCopasiVector < CMetab > & CCompartment::GetMetabolites() 
{return *mMetabolites;}

void CCompartment::SetName(const string & name) 
{
    mName = name;
    if (!IsValidName()) FatalError();
}

void CCompartment::SetVolume(C_FLOAT64 volume) {mVolume = volume;}

void CCompartment::AddMetabolite(CMetab &metabolite)
{
    metabolite.SetCompartment(this);
    mMetabolites->Add(metabolite);
}

C_INT16 CCompartment::IsValidName()
{
    return (mName.find_first_of("; ") == string::npos);
}
