#include <typeinfo>

#include "CBaseFunction.h"
#include "CKinFunction.h"
#include "utilities.h"

CBaseFunction::CBaseFunction() 
{mReversible = FALSE;}

CBaseFunction::~CBaseFunction() {}

void CBaseFunction::Delete() 
{

    for (C_INT32 i=0; i < mCallParameters.size(); i++)
    {
        if (mCallParameters[i])
        {
            mCallParameters[i]->Delete();
            mCallParameters[i] = NULL;
        }
    }
    
    mCallParameters.clear();
}

void CBaseFunction::Copy(const CBaseFunction &in)
{
    CBaseCallParameter *pCallParameter;
    
    mType = in.mType;
    mName = in.mName;
    mDescription = in.mDescription;
    mReversible = in.mReversible;

    for( C_INT32 i = 0; i < in.mCallParameters.size(); i++)
    {
        pCallParameter = new CBaseCallParameter;
        pCallParameter->Copy(*in.mCallParameters[i]);
        mCallParameters.push_back(pCallParameter);
    }
}
    
C_INT32 CBaseFunction::Load(CReadConfig & configbuffer,
                            CReadConfig::Mode mode)
{
    C_INT32 Fail = 0;
    CReadConfig::Mode Mode = mode;
    
    if (configbuffer.GetVersion() < "4")
        mType = CBaseFunction::USERDEFINED;
    else
    {
        if (Fail = configbuffer.GetVariable("FunctionType", "C_INT32", &mType,
                                            Mode))
            return Fail;
        Mode = CReadConfig::NEXT;
    }

    if (Fail = configbuffer.GetVariable("FunctionName", "string", &mName,
                                        Mode))
        return Fail;
    
    if (Fail = configbuffer.GetVariable("Description", "string", &mDescription))
        return Fail;
    
    if (configbuffer.GetVersion() < "4")
        mReversible = TRUE;
    else
    {
        if (Fail = configbuffer.GetVariable("Reversible", "C_INT16",
                                            &mReversible))
            return Fail;
    }
    
    
    return Fail;
}

C_INT32 CBaseFunction::Save(CWriteConfig & configbuffer)
{
    C_INT32 Fail = 0;
    
    if (Fail = configbuffer.SetVariable("FunctionType", "C_INT32", &mType))
        return Fail;

    if (Fail = configbuffer.SetVariable("FunctionName", "string", &mName))
        return Fail;
    
    if (Fail = configbuffer.SetVariable("Description", "string", &mDescription))
        return Fail;
    
    if (Fail = configbuffer.SetVariable("Reversible", "C_INT16", &mReversible))
        return Fail;
    
    return Fail;
}

void CBaseFunction::SetName(const string & name) {mName = name;}

void CBaseFunction::SetType(enum Type type) {mType = type;}

void CBaseFunction::SetDescription(const string & description) 
{mDescription = description;}

void CBaseFunction::SetReversible(C_INT16 reversible) 
{mReversible = reversible;}

string CBaseFunction::GetName() const {return mName;}

C_INT32 CBaseFunction::GetType() const {return mType;}

string CBaseFunction::GetDescription() const {return mDescription;}

C_INT16 CBaseFunction::IsReversible() const {return mReversible;}

vector < CBaseCallParameter * > & CBaseFunction::CallParameters() 
{return mCallParameters;}

C_FLOAT64 
CBaseFunction::CalcValue(const vector < CCallParameter > & callParameters) const
{return 0.0;}

pair < C_INT32, C_INT32 > 
CBaseFunction::FindIdentifier(const string & name) const
{
    pair < C_INT32, C_INT32 > Tuple(-1, -1);
    C_INT32 j;
    C_INT32 i;
    
    for (j = 0; j < mCallParameters.size(); j++)
        for (i = 0; i < mCallParameters[j]->mIdentifiers.size(); i ++)
            if (mCallParameters[j]->mIdentifiers[i]->GetName() == name) 
            {
                Tuple.first = j;
                Tuple.second = i;
                break;
            }

    return Tuple;
}


/*** CBaseCallParameter ***/

CBaseCallParameter::CBaseCallParameter()
{
    mType = CCallParameter::VECTOR_DOUBLE;
    mCount.SetRange(CRange::UNSPECIFIED, CRange::UNSPECIFIED);

    mIdentifierTypes.push_back(0);
}

CBaseCallParameter::~CBaseCallParameter() {}

void CBaseCallParameter::Delete()
{
    for (C_INT32 i = 0; i < mIdentifiers.size(); i++ )
        if (mIdentifiers[i]) delete mIdentifiers[i];
    
    mIdentifiers.clear();
}

void CBaseCallParameter::Copy(const CBaseCallParameter & in)
{
    CBaseIdentifier * pIdentifier;
    
    mType = in.mType;
    mCount = in.mCount;
    mIdentifierTypes = in.mIdentifierTypes;

    for (C_INT32 i = 0; i < in.mIdentifiers.size(); i++)
    {
        pIdentifier = new CBaseIdentifier;
//        memcpy(pIdentifier, in.mIdentifiers[i], sizeof(CBaseIdentifier));
        pIdentifier->SetName(in.mIdentifiers[i]->GetName());
        pIdentifier->SetType(in.mIdentifiers[i]->GetType());
        mIdentifiers.push_back(pIdentifier);
    }
}

C_INT32 CBaseCallParameter::NoIdentifiers(char identifierType)
{
    if (identifierType) 
    {
        C_INT32 Count = 0;
	for (C_INT32 i = 0; i < mIdentifiers.size(); i ++)
	    if (mIdentifiers[i]->GetType() == identifierType) Count++;
        return Count;
    }
    else
        return mIdentifiers.size();
}

void CBaseCallParameter::SetType(enum CCallParameter::Type type)
{mType = type;}

void CBaseCallParameter::SetCount() 
{mCount.SetRange(mIdentifiers.size(), mIdentifiers.size());}

void CBaseCallParameter::SetCount(unsigned C_INT32 count) 
{mCount.SetRange(count, count);}

void CBaseCallParameter::SetCount(unsigned C_INT32 low,
                                  unsigned C_INT32 high)
{mCount.SetRange(low, high);}

enum CCallParameter::Type CBaseCallParameter::GetType() const
{return mType;}

unsigned C_INT32 CBaseCallParameter::GetCountLow() const
{return mCount.GetLow();}

unsigned C_INT32 CBaseCallParameter::GetCountHigh() const
{return mCount.GetHigh();}

vector < C_INT32 > & CBaseCallParameter::IdentifierTypes()
{return mIdentifierTypes;}

vector < CBaseIdentifier * > & CBaseCallParameter::Identifiers()
 {return mIdentifiers;}

vector < CBaseIdentifier * > 
CBaseCallParameter::Identifiers(char identifierType)
{
    vector < CBaseIdentifier * > Identifiers;

    for (C_INT32 i = 0; i < mIdentifiers.size(); i ++)
        if (mIdentifiers[i]->GetType() == identifierType) 
	    Identifiers.push_back(mIdentifiers[i]);

    return Identifiers;
}


/*** CCallParameter ***/

CCallParameter::CCallParameter()
{mType = VECTOR_DOUBLE;}

CCallParameter::~CCallParameter() {}

void CCallParameter::SetType(enum CCallParameter::Type type) {mType = type;}

enum CCallParameter::Type CCallParameter::GetType() const {return mType;}

vector < void * > & CCallParameter::Identifiers() {return mIdentifiers;}


/*** CRange ***/

CRange::CRange() {mLow = mHigh = CRange::UNSPECIFIED;}

CRange::CRange(unsigned C_INT32 low, unsigned C_INT32 high) 
{mLow = low; mHigh = high; CheckRange();}

CRange::~CRange() {}

void CRange::SetLow(unsigned C_INT32 low) {mLow = low; CheckRange();} 
void CRange::SetHigh(unsigned C_INT32 high) {mHigh = high; CheckRange();}

void CRange::SetRange(unsigned C_INT32 low, unsigned C_INT32 high)
{mLow = low; mHigh = high; CheckRange();}

unsigned C_INT32 CRange::GetLow() const {return mLow;}

unsigned C_INT32 CRange::GetHigh() const {return mHigh;}

C_INT16 CRange::IsRange() const
{
    if (mHigh - mLow) return 1;
    else return 0;
}

void CRange::CheckRange() const
{
    if (mLow > mHigh) 
        CCopasiMessage(CCopasiMessage::ERROR, MCRange + 1, mLow, mHigh);
}
