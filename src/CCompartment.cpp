// CCompartment 
// 
// Derived from Gepasi's ccompart.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Pedro Mendes

#include "copasi.h"
#include "CCompartment.h"

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
    mVolume = volume;
}

CCompartment::~CCompartment()
{
}

CCompartment & CCompartment::operator=(const CCompartment & rhs)
{
    mVolume = rhs.mVolume;
    mName   = rhs.mName;
    
    return *this;
}

long CCompartment::Load(CReadConfig & configbuffer)
{
    long Fail = 0;

    Fail = configbuffer.GetVariable("Compartment", "string",
                                    (void *) &mName,
                                    CReadConfig::SEARCH);
    if (Fail) return Fail;

    Fail = configbuffer.GetVariable("Volume", "double",
                                    (void *) &mVolume);
    return Fail;
}

long CCompartment::Save(CWriteConfig & configbuffer)
{
    long Fail = 0;

    Fail = configbuffer.SetVariable("Compartment", "string",
                                    (void *) &mName);
    if (Fail) return Fail;

    Fail = configbuffer.SetVariable("Volume", "double",
                                    (void *) &mVolume);
    return Fail;
}

string CCompartment::GetName() {return mName;}

double CCompartment::GetVolume() {return mVolume;}

void CCompartment::SetName(const string & name) {mName = name;}

void CCompartment::SetVolume(double volume) {mVolume = volume;}
