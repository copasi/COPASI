// CCompartment 
// 
// Derived from Gepasi's ccompart.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Pedro Mendes

#include <iostream>
#include <string>
#include <vector>

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
CCompartment& CCompartment::operator=(const CCompartment &RHS)
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

int CCompartment::Load(CReadConfig &configbuffer)
{
    mFail = configbuffer.GetVariable((string) "Compartment", 
                                     (string) "string",
                                     (void *) &mName);
    if (mFail) return mFail;

    configbuffer.SetMode(-CReadConfig_SEARCH);
    mFail = configbuffer.GetVariable((string) "Volume", 
                                     (string) "double",
                                     (void *) &mVolume);
    return mFail;
}


int CCompartment::Save(CWriteConfig &configbuffer)
{
    mFail = configbuffer.SetVariable((string) "Compartment",
                                     (string) "string",
                                     (void *) &mName);
    if (mFail) return mFail;

    mFail = configbuffer.SetVariable((string) "Volume", 
                                     (string) "double",
                                     (void *) &mVolume);
    return mFail;
}

CCompartmentVector::CCompartmentVector()
{
    mFail = 0;
    this->resize(0);
}

CCompartmentVector::CCompartmentVector(int size)
{
    mFail = 0;
    this->resize(size);
}

int CCompartmentVector::Save(CWriteConfig &configbuffer)
{
    int Size = this->size();
    
    mFail = configbuffer.SetVariable((string) "TotalCompartments",
                                     (string) "int",
                                     (void *) &Size);
    if (mFail) return mFail;

    for(int i = 0; i < Size; i++)
    {

        if (mFail = (*(&this->front()+i)).Save(configbuffer))
        {
            break;
        }
    }
    return mFail;
}

int CCompartmentVector::Load(CReadConfig &configbuffer)
{
    int Size = 0;
    
    configbuffer.SetMode(CReadConfig_SEARCH);
    configbuffer.SetMode(CReadConfig_LOOP);
    
    mFail = configbuffer.GetVariable((string) "TotalCompartments",
                                     (string) "int",
                                     (void *) &Size);
    if (mFail) return mFail;
    this->resize(Size);
    
    configbuffer.SetMode(-CReadConfig_LOOP);
    for(int i = 0; i < Size; i++)
    {
        if (mFail = (*(&this->front()+i)).Load(configbuffer))
        {
            break;
        }
    }
    
    return mFail;
}

int CCompartmentVector::Fail()
{
    return mFail;
}

