#include "CBaseFunction.h"
#include "utilities.h"

CBaseFunction::CBaseFunction() 
{
    mCallParameters = NULL;
    mReversible = FALSE;
}

void CBaseFunction::Init() 
{
    long i;
    
    if (!mCallParameters ) mCallParameters = new vector < CBaseCallParameter >;
    for (i = 0; i < mCallParameters->size(); i++)
        (*mCallParameters)[i].Init();
}

CBaseFunction::~CBaseFunction() {;}

void CBaseFunction::Delete() 
{
    if (mCallParameters)
    {
        for (long i=0; i < mCallParameters->size(); i++)
            (*mCallParameters)[i].Delete();
        
        delete mCallParameters;
        mCallParameters = NULL;
    }
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
    if (!mIdentifierTypes) mIdentifierTypes = new vector < int >;
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

long CBaseCallParameter::NoIdentifiers(char identifierType)
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

void CBaseCallParameter::SetType(enum CCallParameter::Type type)
{mType = type;}

void CBaseCallParameter::SetCount() {mCount = mIdentifiers->size();}

void CBaseCallParameter::SetCount(long count) {mCount = count;}

enum CCallParameter::Type CBaseCallParameter::GetType()
{return mType;}

long CBaseCallParameter::GetCount() 
{return mCount;}

vector < int > & CBaseCallParameter::IdentifierTypes()
{return *mIdentifierTypes;}

vector < CBaseIdentifier * > 
CBaseCallParameter::Identifiers(char identifierType)
{
    vector < CBaseIdentifier * > Identifiers;

    for (long i = 0; i < mIdentifiers->size(); i ++)
        if (!identifierType ||
	    (*mIdentifiers)[i].GetType() == identifierType) 
	    Identifiers.push_back(&(*mIdentifiers)[i]);

    return Identifiers;
}

double CBaseFunction::CalcValue(vector < CCallParameter > callParameters)
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

