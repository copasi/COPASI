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
}

CCompartment::CCompartment(const string & name,
                           double volume)
{
    // initialize everything
    mName   = name;
    if (!IsValidName()) FatalError();
    mVolume = volume;
}

CCompartment::~CCompartment() 
{
    cout << "~CCompartment " << mName << endl;
}

CCompartment & CCompartment::operator=(const CCompartment & rhs)
{
    mName        = rhs.mName;
    mVolume      = rhs.mVolume;
    mMetabolites = rhs.mMetabolites;
    
    return *this;
}

long CCompartment::Load(CReadConfig & configbuffer)
{
    long Fail = 0;

    if (Fail = configbuffer.GetVariable("Compartment", "string",
                                        (void *) &mName,
                                        CReadConfig::SEARCH))
        return Fail;

    if (Fail = configbuffer.GetVariable("Volume", "double",
                                        (void *) &mVolume))
        return Fail;
    
    if (configbuffer.GetVersion() < "4") return Fail;
    
    long MetabolitesNo;
    if (Fail = configbuffer.GetVariable("MetabolitesNo", "long",
                                        (void *) &MetabolitesNo))
        return Fail;
    
    Fail = mMetabolites.Load(configbuffer, MetabolitesNo);
    
    return Fail;
}

long CCompartment::Save(CWriteConfig & configbuffer)
{
    long Fail = 0;

    if (Fail = configbuffer.SetVariable("Compartment", "string",
                                        (void *) &mName))
        return Fail;

    if (Fail = configbuffer.SetVariable("Volume", "double",
                                        (void *) &mVolume))
        return Fail;
    
    long size = mMetabolites.Size();
    if (Fail = configbuffer.SetVariable("MetabolitesNo", "long",
                                        (void *) &size))
        return Fail;

    Fail = mMetabolites.Save(configbuffer);
    return Fail;
}

string CCompartment::GetName() {return mName;}

double CCompartment::GetVolume() {return mVolume;}

CCopasiVector < CMetab > & CCompartment::GetMetabolites() {return mMetabolites;}

void CCompartment::SetName(const string & name) 
{
    mName = name;
    if (!IsValidName()) FatalError();
}

void CCompartment::SetVolume(double volume) {mVolume = volume;}

void CCompartment::AddMetabolite(CMetab &metabolite)
{
    metabolite.SetCompartment(this);
    mMetabolites.Add(metabolite);
}

short CCompartment::IsValidName()
{
    return (mName.find_first_of("; ") == string::npos);
}
