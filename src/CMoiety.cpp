#include <stdio.h>
#include <math.h>

#include "copasi.h"
#include "CCopasiMessage.h"
#include "CMoiety.h"
#include "CCompartment.h"
#include "utilities.h"

CMoiety::CMoiety() {}

CMoiety::CMoiety(const string & name) {mName = name;}

CMoiety::~CMoiety() {}

void CMoiety::Add(C_FLOAT64 value,
                  CMetab & metabolite)
{
    ELEMENT element;
    element.mValue = value;
    element.mMetab = &metabolite;
        
    mEquation.push_back(element);
}

void CMoiety::Add(C_FLOAT64 value,
                  CMetab * metabolite)
{
    ELEMENT element;
    element.mValue = value;
    element.mMetab = metabolite;
        
    mEquation.push_back(element);
}

void CMoiety::Delete() {mEquation.clear();}

void CMoiety::Delete(const string & name)
{
    C_INT32 i;

    for (i = 0; i < mEquation.size(); i++)
        if (mEquation[i].mMetab->GetName() == name) break;
    
    if (i == mEquation.size()) FatalError();

    Delete(i);
}

void CMoiety::Delete(C_INT32 index)
{
    mEquation.erase(&mEquation[index], &mEquation[index+1]);
}

void CMoiety::Change(C_INT32 index,
		     C_FLOAT64 value)
{
    mEquation[index].mValue = value;
}

void CMoiety::Change(const string & name,
		     C_FLOAT64 value)
{
    C_INT32 i;

    for (i = 0; i < mEquation.size(); i++)
        if (mEquation[i].mMetab->GetName() == name) break;
    
    if (i == mEquation.size()) FatalError();

    Change(i, value);
}

C_FLOAT64 CMoiety::DependentNumber()
{
    C_FLOAT64 Number = mINumber;
    
    for(C_INT32 i=1; i < mEquation.size(); i++)
        Number -= mEquation[i].mValue * 
            *mEquation[i].mMetab->GetConcentration() * 
            mEquation[i].mMetab->GetCompartment()->GetVolume();
    
    return Number;
}

string CMoiety::GetName() const {return mName;}

string CMoiety::GetDescription() const
{
    string Description;
    char szValue[5];
    C_INT32 nchars = 0;
    
    for(C_INT32 i=0; i < mEquation.size(); i++)
    {
        if (i) 
        {
            if (mEquation[i].mValue < 0.0)
                Description += " - ";
            else
                Description += " + ";
        }
        if (fabs(mEquation[i].mValue) != 1.0)
            Description += StringPrint("%3.1f * ", fabs(mEquation[i].mValue));
        Description += mEquation[i].mMetab->GetName();
    }
    return Description;
}

void CMoiety::SetName(const string name) {mName = name;}

void CMoiety::SetInitialValue()
{
    mINumber = 0.0;
    
    for (C_INT32 i=0; i<mEquation.size(); i++)
        mINumber += mEquation[i].mValue *
            *mEquation[i].mMetab->GetConcentration() * 
            mEquation[i].mMetab->GetCompartment()->GetVolume();

    return;
}

