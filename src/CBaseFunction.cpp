#include "CBaseFunction.h"
#include "utilities.h"

CBaseFunction::CBaseFunction() 
{
    mCallParameters = NULL;
    mReversible = FALSE;
}

void CBaseFunction::Init() 
{
    C_INT32 i;
    
    if (!mCallParameters ) mCallParameters = new vector < CBaseCallParameter >;
    for (i = 0; i < mCallParameters->size(); i++)
        (*mCallParameters)[i].Init();
}

CBaseFunction::~CBaseFunction() {;}

void CBaseFunction::Delete() 
{
    if (mCallParameters)
    {
        for (C_INT32 i=0; i < mCallParameters->size(); i++)
            (*mCallParameters)[i].Delete();
        
        delete mCallParameters;
        mCallParameters = NULL;
    }
}

void CBaseFunction::SetName(const string & name) {mName = name;}

void CBaseFunction::SetType(enum Type type) {mType = type;}

void CBaseFunction::SetDescription(const string & description) 
{mDescription = description;}

void CBaseFunction::SetReversible(C_INT16 reversible) 
{mReversible = reversible;}

string CBaseFunction::GetName() {return mName;}

C_INT32 CBaseFunction::GetType() {return mType;}

string CBaseFunction::GetDescription() {return mDescription;}

C_INT16 CBaseFunction::IsReversible() {return mReversible;}

vector < CBaseCallParameter > & CBaseFunction::CallParameters() 
{return *mCallParameters;}

CBaseCallParameter::CBaseCallParameter()
{
    mType = CCallParameter::VECTOR_DOUBLE;
    mCount = -1;
    
    mIdentifierTypes = NULL;
    mIdentifiers = NULL;
}

void CBaseCallParameter::Init()
{
    if (!mIdentifierTypes) mIdentifierTypes = new vector < C_INT32 >;
    if (!mIdentifierTypes->size()) mIdentifierTypes->push_back(0);
    
    if (!mIdentifiers) mIdentifiers = new vector < CBaseIdentifier >;
}

CBaseCallParameter::~CBaseCallParameter() {;}

void CBaseCallParameter::Delete()
{
    if (mIdentifierTypes) delete mIdentifierTypes;
    mIdentifierTypes = NULL;
    
    if (mIdentifiers) delete mIdentifiers;
    mIdentifiers = NULL;
}

C_INT32 CBaseCallParameter::NoIdentifiers(char identifierType)
{
    if (identifierType) 
    {
        C_INT32 Count = 0;
	for (C_INT32 i = 0; i < mIdentifiers->size(); i ++)
	    if ((*mIdentifiers)[i].GetType() == identifierType) Count++;
        return Count;
    }
    else
        return mIdentifiers->size();
}

void CBaseCallParameter::SetType(enum CCallParameter::Type type)
{mType = type;}

void CBaseCallParameter::SetCount() {mCount = mIdentifiers->size();}

void CBaseCallParameter::SetCount(C_INT32 count) {mCount = count;}

enum CCallParameter::Type CBaseCallParameter::GetType()
{return mType;}

C_INT32 CBaseCallParameter::GetCount() 
{return mCount;}

vector < C_INT32 > & CBaseCallParameter::IdentifierTypes()
{return *mIdentifierTypes;}

vector < CBaseIdentifier * > 
CBaseCallParameter::Identifiers(char identifierType)
{
    vector < CBaseIdentifier * > Identifiers;

    for (C_INT32 i = 0; i < mIdentifiers->size(); i ++)
        if (!identifierType ||
	    (*mIdentifiers)[i].GetType() == identifierType) 
	    Identifiers.push_back(&(*mIdentifiers)[i]);

    return Identifiers;
}

C_FLOAT64 CBaseFunction::CalcValue(vector < CCallParameter > callParameters)
{return 0.0;}

pair < C_INT32, C_INT32 > CBaseFunction::FindIdentifier(const string & name)
{
    pair < C_INT32, C_INT32 > Tuple(-1, -1);
    C_INT32 j;
    C_INT32 i;
    
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

CCallParameter::CCallParameter()
{
    mType = VECTOR_DOUBLE;
    mIdentifiers = NULL;
}

void CCallParameter::Init()
{
    if (!mIdentifiers) mIdentifiers = new vector < void * >;
}

CCallParameter::~CCallParameter() {;}

void CCallParameter::Delete() 
{
    if (mIdentifiers) delete mIdentifiers;
    mIdentifiers = NULL;
}

void CCallParameter::SetType(enum CCallParameter::Type type) {mType = type;}

enum CCallParameter::Type CCallParameter::GetType() {return mType;}

vector < void * > & CCallParameter::Identifiers() {return *mIdentifiers;}
