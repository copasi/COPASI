// CMetab 
// 
// Derived from Gepasi's cmetab.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Stefan Hoops

#include "copasi.h"
#include "CMetabVector.h"

CMetabVector::CMetabVector() {}

CMetabVector::~CMetabVector() {}

long CMetabVector::Load(CReadConfig & configbuffer, long size)
{
    CMetab c;
    long Fail = 0;
    
    for (long i = 0; i < size; i++)
    {
        if (Fail = c.Load(configbuffer)) return Fail;
        mMetabs.push_back(c);
    }
    
    return Fail;
}

long CMetabVector::Save(CWriteConfig & configbuffer)
{
    long Fail = 0;

    for (long i = 0; i < Size(); i++)
        if (Fail = mMetabs[i].Save(configbuffer)) return Fail;
    
    return Fail;
}

long CMetabVector::Add(CMetab & metab)
{
    if ( Get(metab.GetName()) ) return 1;

    mMetabs.push_back(metab);
}

long CMetabVector::Delete(long index)
{
    if ( 0 <= index && index < Size() )
    {
        mMetabs.erase(&mMetabs[index], &mMetabs[index+1]);
        return 0;
    }
    
    return 1;
}

long CMetabVector::Delete(const string & name)
{
    long i;
    
    for ( i = 0; i < Size(); i++ )
        if ( name == mMetabs[i].GetName() ) 
            break;

    return Delete(i);
}

CMetab * CMetabVector::Get(long index)
{
    if ( 0 <= index && index < Size() )
        return &mMetabs[index];

    return NULL;
}

CMetab * CMetabVector::Get(const string & name)
{
    for (long i = 0; i < Size(); i++ )
        if ( name == mMetabs[i].GetName() ) 
            return &mMetabs[i];

    return NULL;
}

long CMetabVector::Size() {return mMetabs.size();}


