// CCompartment 
// 
// Derived from Gepasi's ccompart.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Pedro Mendes

#include "copasi.h"
#include "CCompartmentVector.h"

CCompartmentVector::CCompartmentVector() {}

CCompartmentVector::~CCompartmentVector() {}

long CCompartmentVector::Load(CReadConfig & configbuffer, long size)
{
    CCompartment c;
    long Fail = 0;
    
    for (long i = 0; i < size; i++)
    {
        if (Fail = c.Load(configbuffer)) return Fail;
        mCompartments.push_back(c);
    }
    
    return Fail;
}

long CCompartmentVector::Save(CWriteConfig & configbuffer)
{
    long Fail = 0;

    for (long i = 0; i < Size(); i++)
        if (Fail = mCompartments[i].Save(configbuffer)) return Fail;
    
    return Fail;
}

long CCompartmentVector::Add(CCompartment & compartment)
{
    if ( Get(compartment.GetName()) ) return 1;

    mCompartments.push_back(compartment);
}

long CCompartmentVector::Delete(long index)
{
    if ( 0 <= index && index < Size() )
    {
        mCompartments.erase(&mCompartments[index], &mCompartments[index+1]);
        return 0;
    }
    
    return 1;
}

long CCompartmentVector::Delete(const string & name)
{
    long i;
    
    for ( i = 0; i < Size(); i++ )
        if ( name == mCompartments[i].GetName() ) 
            break;

    return Delete(i);
}

CCompartment * CCompartmentVector::Get(long index)
{
    if ( 0 <= index && index < Size() )
        return &mCompartments[index];

    return NULL;
}

CCompartment * CCompartmentVector::Get(const string & name)
{
    for (long i = 0; i < Size(); i++ )
        if ( name == mCompartments[i].GetName() ) 
            return &mCompartments[i];

    return NULL;
}

long CCompartmentVector::Size() {return mCompartments.size();}


