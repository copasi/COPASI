#include <stdio.h>

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

CMoiety::Add(double value,
             CMetab & metabolite)
{
    ELEMENT element;
    element.Value = value;
    element.Metab = &metabolite;
        
    mEquation.push_back(element);
}

CMoiety::Add(double value,
             CMetab * metabolite)
{
    ELEMENT element;
    element.Value = value;
    element.Metab = metabolite;
        
    mEquation.push_back(element);
}

CMoiety::Delete()
{
    mEquation.clear();
}

CMoiety::Delete(const string & name)
{
    int i;

    for (i = 0; i < mEquation.size(); i++)
        if (mEquation[i].Metab->GetName() == name) break;
    
    if (i == mEquation.size()) FatalError();

    Delete(i);
}

CMoiety::Delete(long index)
{
    mEquation.erase(&mEquation[index], &mEquation[index+1]);
}

CMoiety::Change(long index,
                double value)
{
    mEquation[index].Value = value;
}

CMoiety::Change(const string & name,
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
