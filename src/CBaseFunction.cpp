#include "CBaseFunction.h"

CBaseFunction::CBaseFunction() 
{
    mReversible = FALSE;
    mIdentifierTypes.push_back(0);
}

CBaseFunction::~CBaseFunction() {;}

void CBaseFunction::SetName(const string & name) {mName = name;}

void CBaseFunction::SetType(enum Type type) {mType = type;}

void CBaseFunction::SetDescription(const string & description) 
{mDescription = description;}

void CBaseFunction::SetReversible(short reversible) 
{mReversible = reversible;}

string CBaseFunction::GetName() {return mName;}

long CBaseFunction::GetType() {return mType;}

string CBaseFunction::GetDescription() {return mDescription;}

short CBaseFunction::IsReversible() {return mReversible;}

vector < char > & CBaseFunction::IdentifierTypes() {return mIdentifierTypes;}

long CBaseFunction::NoIdentifiers(char identifierType)
{
    if (identifierType) 
    {
        long Count = 0;
	for (long i = 0; i < mIdentifiers.size(); i ++)
	    if (mIdentifiers[i].GetType() == identifierType) Count++;
        return Count;
    }
    else
        return mIdentifiers.size();
}

vector< CBaseIdentifier * > CBaseFunction::Identifiers(char identifierType)
{
    vector < CBaseIdentifier * > Identifiers;

    for (long i = 0; i < mIdentifiers.size(); i ++)
        if (!identifierType ||
	    mIdentifiers[i].GetType() == identifierType) 
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
