// CCompartment 
// 
// Derived from Gepasi's ccompart.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Pedro Mendes

#include <iostream>
#include <string>
// #include <sstream>

using namespace std ;

#include "CReadConfig.h"
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
CCompartment &CCompartment::operator=(CCompartment &RHS)
{
    mVolume = RHS.mVolume;
    mName   = "";          // do we need this
    mName   = RHS.mName;
    mFail   = RHS.mFail;
    
    return *this;
}

int CCompartment::Fail()
{
    return mFail;
}

int CCompartment::Load(CReadConfig *pconfigbuffer)
{
    mFail = pconfigbuffer->GetVariable((string) "Compartment", 
                                       (string) "string",
                                       (void *) &mName);
    if (mFail) return mFail;

    mFail = pconfigbuffer->GetVariable((string) "Volume", 
                                       (string) "double",
                                       (void *) &mVolume);
    return mFail;
}


int CCompartment::Save( ostream *pout )
{
    // this really should be changed to something like Load

    // we don't care about exceptions here.
    // They should be caught by the calling function
    // make sure fp numbers come out in scientific notation
    pout->setf( ios::scientific ); 
    // compartment objects are just a name and a volume
    *pout << "Compartment=" << mName << endl;
    *pout << "Volume=" << mVolume << endl;

    return mFail;
}
