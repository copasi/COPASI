// CCompartment 
// 
// Derived from Gepasi's ccompart.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Pedro Mendes

#include <iostream>
#include <string>

#include "copasi.h"
#include "CReadConfig.h"
#include "CWriteConfig.h"
#include "CCompartment.h"

CCompartment::CCompartment(void)
{
    // initialize everything
    mName   = "compartment";
    mVolume = 1.0;
    mFail   = 0;
}

CCompartment::CCompartment(string name, double volume)
{
    // initialize everything
    mName   = name;
    mVolume = volume;
    mFail   = 0;
}

CCompartment::~CCompartment(void)
{
}

// overload assignment operator
CCompartment& CCompartment::operator=(CCompartment &RHS)
{
    mVolume = RHS.mVolume;
    mName   = "";          // do we need this
    mName   = RHS.mName;
    mFail   = RHS.mFail;
    
    return *this;
}

string CCompartment::GetName(void)
{
    return mName;
}

void CCompartment::SetName(string& name)
{
    mName = name;
}

double CCompartment::GetVolume(void)
{
    return mVolume;
}

void CCompartment::SetVolume(double volume)
{
    // we should check for negative volumes and generate an exception
    // or set a failure code
    mVolume = volume;
}

int CCompartment::Fail()
{
    return mFail;
}

int CCompartment::Load(CReadConfig &pconfigbuffer)
{
    mFail = pconfigbuffer.GetVariable((string) "Compartment", 
                                       (string) "string",
                                       (void *) &mName);
    if (mFail) return mFail;

    mFail = pconfigbuffer.GetVariable((string) "Volume", 
                                       (string) "double",
                                       (void *) &mVolume);
    return mFail;
}


int CCompartment::Save( CWriteConfig &pconfigbuffer )
{
    mFail = pconfigbuffer.SetVariable((string) "Compartment",
                                       (string) "string",
                                       (void *) &mName);
    if (mFail) return mFail;

    mFail = pconfigbuffer.SetVariable((string) "Volume", 
                                       (string) "double",
                                       (void *) &mVolume);
    return mFail;
}
