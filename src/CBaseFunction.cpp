#include "CBaseFunction.h"

CBaseFunction::CBaseFunction() 
{
    mReversible = FALSE;
    mTypes.push_back(0);
}

CBaseFunction::~CBaseFunction() {;}

void CBaseFunction::SetName(const string & name) {mName = name;}

void CBaseFunction::SetDescription(const string & description) 
{mDescription = description;}

void CBaseFunction::SetReversible(short reversible) 
{mReversible = reversible;}

string CBaseFunction::GetName() {return mName;}

string CBaseFunction::GetDescription() {return mDescription;}

short CBaseFunction::IsReversible() {return mReversible;}

vector < char > & CBaseFunction::IdentifierTypes() {return mTypes;}

vector< CBaseIdentifier * > CBaseFunction::Identifiers(char type = 0)
{
    vector < CBaseIdentifier * > Identifiers;
    
    for (long i = 0; i < mIdentifiers.size(); i ++)
        if (mIdentifiers[i].GetType() == type) 
            Identifiers.push_back(&mIdentifiers[i]);
    
    return Identifiers;
}

double CBaseFunction::CalcValue(vector < double * > identifiers)
{return 0.0;}

long CBaseFunction::FindIdentifier(const string & name)
{
    for (long i = 0; i < mIdentifiers.size(); i ++)
        if (mIdentifiers[i].GetName() == name) return i;
    
    return -1;
}

