#include <stdio.h>
#include <math.h>

#include "copasi.h"
#include "CCopasiMessage.h"
#include "CMoiety.h"

CMoiety::CMoiety()
{
}

CMoiety::CMoiety(const string & name)
{
    mName = name;
}

CMoiety::~CMoiety()
{
}

void CMoiety::Add(double value,
             CMetab & metabolite)
{
    ELEMENT element;
    element.Value = value;
    element.Metab = &metabolite;
        
    mEquation.push_back(element);
}

void CMoiety::Add(double value,
             CMetab * metabolite)
{
    ELEMENT element;
    element.Value = value;
    element.Metab = metabolite;
        
    mEquation.push_back(element);
}

void CMoiety::Delete()
{
    mEquation.clear();
}

void CMoiety::Delete(const string & name)
{
    int i;

    for (i = 0; i < mEquation.size(); i++)
        if (mEquation[i].Metab->GetName() == name) break;
    
    if (i == mEquation.size()) FatalError();

    Delete(i);
}

void CMoiety::Delete(long index)
{
    mEquation.erase(&mEquation[index], &mEquation[index+1]);
}

void CMoiety::Change(long index,
		     double value)
{
    mEquation[index].Value = value;
}

void CMoiety::Change(const string & name,
		     double value)
{
    int i;

    for (i = 0; i < mEquation.size(); i++)
        if (mEquation[i].Metab->GetName() == name) break;
    
    if (i == mEquation.size()) FatalError();

    Change(i, value);
}

double CMoiety::Value()
{
    double Value = 0;
    
    for(int i=0; i < mEquation.size(); i++)
        Value += mEquation[i].Value * *mEquation[i].Metab->GetConcentration();
    
    return Value;
}

string CMoiety::GetDescription()
{
    string Description;
    char szValue[5];
    int nchars = 0;
    
    for(int i=0; i < mEquation.size(); i++)
    {
        if (mEquation[i].Value)
        {
            nchars = snprintf(szValue, sizeof(szValue), 
                              "%f", fabs(mEquation[i].Value));
            
            if (nchars >= sizeof(szValue) || nchars < 0) FatalError() ;
            if ( mEquation[i].Value < 0 )
                Description += "- ";
            else
                Description += "+ ";

            Description += szValue;
            Description += " ";
            
            Description += mEquation[i].Metab->GetName();
            Description += " ";
        }
    }
    return Description;
}
