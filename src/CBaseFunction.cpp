#include "CBaseFunction.h"

CBaseFunction::CBaseFunction() 
{
    mCallParameters = new vector < CBaseCallParameter >;
    mReversible = FALSE;
}

CBaseFunction::~CBaseFunction() 
{
    delete [] mCallParameters;
}

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

vector < CBaseFunction::CBaseCallParameter > & CBaseFunction::CallParameters() 
{return *mCallParameters;}

CBaseFunction::CBaseCallParameter::CBaseCallParameter()
{
    mIdentifierTypes = new vector < char >;
    mIdentifiers = new vector< CBaseIdentifier >;
}

CBaseFunction::CBaseCallParameter::~CBaseCallParameter()
{
    delete [] mIdentifierTypes;
    delete [] mIdentifiers;
}

long CBaseFunction::CBaseCallParameter::NoIdentifiers(char identifierType)
{
    if (identifierType) 
    {
        long Count = 0;
	for (long i = 0; i < mIdentifiers->size(); i ++)
	    if ((*mIdentifiers)[i].GetType() == identifierType) Count++;
        return Count;
    }
    else
        return mIdentifiers->size();
}

void CBaseFunction::CBaseCallParameter::SetType(enum Type type) {mType = type;}

void CBaseFunction::CBaseCallParameter::SetCount(long count) {mCount = count;}

vector< CBaseIdentifier * > 
CBaseFunction::CBaseCallParameter::Identifiers(char identifierType)
{
    vector < CBaseIdentifier * > Identifiers;

    for (long i = 0; i < mIdentifiers->size(); i ++)
        if (!identifierType ||
	    (*mIdentifiers)[i].GetType() == identifierType) 
	    Identifiers.push_back(&(*mIdentifiers)[i]);

    return Identifiers;
}

double CBaseFunction::CalcValue(vector < double * > identifiers)
{return 0.0;}

pair < long, long > CBaseFunction::FindIdentifier(const string & name)
{
    pair < long, long > Tuple(-1, -1);
    long j;
    long i;
    
    for (j = 0; j < mCallParameters->size(); j++)
        for (i = 0; i < (*mCallParameters)[j].mIdentifiers->size(); i ++)
            if ((*(*mCallParameters)[j].mIdentifiers)[i].GetName() == name) 
                {
                    Tuple.first = j;
                    Tuple.second = i;
                    break;
                }

    return Tuple;
}
