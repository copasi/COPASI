// CNodeK.cpp : classes for function tree
//
/////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <stdio.h>

#include "copasi.h"
#include "CCopasiMessage.h"
#include "CNodeK.h"

CNodeK::CNodeK()
{
    mType     = N_NOP;
    mSubtype  = N_NOP;
    mLeft     = NULL;
    mRight    = NULL;
    mConstant = 0.0;
    mIndex    = -1;
}

CNodeK::CNodeK(char type, char subtype)
{
    mType     = type;
    mSubtype  = subtype;
    mLeft     = NULL;
    mRight    = NULL;
    mConstant = 0.0;
    mIndex    = -1;
}

CNodeK::CNodeK(const string & name)
{
    mType     = N_IDENTIFIER;
    mSubtype  = N_NOP;
    mLeft     = NULL;
    mRight    = NULL;
    mConstant = 0.0;
    mName     = name;
    mIndex    = -1;
}

CNodeK::CNodeK(double constant)
{
    mType     = N_NUMBER;
    mSubtype  = N_NOP;
    mLeft     = NULL;
    mRight    = NULL;
    mConstant = constant;
    mIndex    = -1;
}

CNodeK::~CNodeK()
{
}

long CNodeK::Load(CReadConfig & configbuffer)
{
    long Fail = 0;
    
    if (Fail = configbuffer.GetVariable("Node", "node", &mType, &mSubtype,
                                        CReadConfig::SEARCH))
        return Fail;
    
    if (IsIdentifier() && mType != N_IDENTIFIER)
    {
        mSubtype = mType;
        mType = N_IDENTIFIER;
    }
    
    // leave the Left & Right pointers out
    // value of the constant if one
    if (mType == N_NUMBER)
    {
        if (Fail = configbuffer.GetVariable("Value", "double", &mConstant))
            return Fail;
    }
    else if (mType == N_IDENTIFIER)
    {
        if (Fail = configbuffer.GetVariable("Index", "long", &mIndex))
            return Fail;
        if (Fail = configbuffer.GetVariable("Name", "string", &mName))
            return Fail;
    }

    return Fail;
}

long CNodeK::Save(CWriteConfig & configbuffer)
{
    long Fail = 0;
    
    // the file has already been opened
    // we don't care about exceptions here.
    // They should be caught by the calling function
    // First the Type and subtype
    if (Fail = configbuffer.SetVariable("Node", "node", &mType, &mSubtype))
        return Fail;
    
    // leave the Left & Right pointers out
    // value of the constant if one
    if (mType==N_NUMBER)
    {
        if (Fail = configbuffer.SetVariable("Value", "double", &mConstant))
            return Fail;
    }
    else if (IsIdentifier())
    {
        if (Fail = configbuffer.SetVariable("Index", "long", &mIndex))
            return Fail;
        if (Fail = configbuffer.SetVariable("Name", "string", &mName))
            return Fail;
    }
    return Fail;
}

char CNodeK::GetType() {return mType;}

char CNodeK::GetSubtype() {return mSubtype;}

CNodeK & CNodeK::GetLeft()
{
    if (!mLeft) 
        FatalError(); // Call LeftIsValid first to avoid this!
    return *mLeft;
}

CNodeK & CNodeK::GetRight()
{
    if (!mRight) 
        FatalError(); // Call RightIsValid first to avoid this!
    return *mRight;
}

string CNodeK::GetName() 
{
    static unsigned long ctr = 0;
    char name[9];
    
    if (IsIdentifier()) return mName;
    else 
    {
        sprintf(name, "%X", ctr++);
        return name;
    }
}

double CNodeK::GetConstant() {return mConstant;}

long CNodeK::GetIndex() {return mIndex;}

void CNodeK::SetType(char type) {mType = type;}

void CNodeK::SetSubtype(char subtype) {mSubtype = subtype;}

void CNodeK::SetLeft(CNodeK & left) {mLeft = &left;}

void CNodeK::SetLeft(CNodeK * pleft) {mLeft = pleft;}

void CNodeK::SetRight(CNodeK & right) {mRight = &right;}

void CNodeK::SetRight(CNodeK * pright) {mRight = pright;}

void CNodeK::SetName(const string & name) {mName = name;}

void CNodeK::SetConstant(double & constant) {mConstant = constant;}

void CNodeK::SetIndex(long index) {mIndex = index;}

short CNodeK::IsLeftValid() {return (short) mLeft;}

short CNodeK::IsRightValid() {return (short) mRight;}

short CNodeK::IsNumber() {return mType == N_NUMBER;}

short CNodeK::IsIdentifier()
{
    switch (mType)
    {
    case N_IDENTIFIER:
    case N_SUBSTRATE:
    case N_PRODUCT:
    case N_MODIFIER:
    case N_KCONSTANT: return TRUE;
    default: return FALSE;
    }
}

short CNodeK::IsOperator() {return mType == N_OPERATOR;}

short CNodeK::LeftPrecedence()
{
    switch (mType)
    {
    case N_NUMBER:
    case N_IDENTIFIER:
    case N_FUNCTION:   return 5;
    }
    // if we got here then it is an operator
    switch (mSubtype)
    {
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 3;
    case '(': return 6;
    case '^': return 5;
    case ')':
    case '%': return 0;
    }
    return 0;
}

short CNodeK::RightPrecedence()
{
    switch (mType)
    {
    case N_NUMBER:
    case N_IDENTIFIER: return 6;
    case N_FUNCTION:   return 4;
    }

    // if we got here then it is an operator
    switch (mSubtype)
    {
    case '+':
    case '-': return 2;
    case '*':
    case '/': return 4;
    case ')': return 6;
    case '^': return 4;
    case '(':
    case '%': return 0;
    }
    return 0;
}

double CNodeK::Value(vector < double * > & identifiers)
{
    // if it is a constant or an identifier just return its value
    if (IsNumber()) return mConstant;

    switch (mType)
    {
    case N_IDENTIFIER :
        return *identifiers[mIndex];
        break;
        
    case N_OPERATOR:
	switch (mSubtype)
	{
        case '+':
            return mLeft->Value(identifiers) + mRight->Value(identifiers);

        case '-': 
            return mLeft->Value(identifiers) - mRight->Value(identifiers);

        case '*': 
            return mLeft->Value(identifiers) * mRight->Value(identifiers);
        
        case '/': 
            return mLeft->Value(identifiers) / mRight->Value(identifiers);
        
        case '^': 
            return pow(mLeft->Value(identifiers), mRight->Value(identifiers));
        
        default: 
            FatalError();   // THROW EXCEPTION
            return 0.0;
	}
	break;

    case N_FUNCTION:
	switch (mSubtype)
	{
        case '+': 
            return mLeft->Value(identifiers);

        case '-': 
            return - mLeft->Value(identifiers);

        case N_EXP: 
            return exp(mLeft->Value(identifiers));

        case N_LOG: 
            return log(mLeft->Value(identifiers));

        case N_LOG10: 
            return log10(mLeft->Value(identifiers));

        case N_SIN: 
            return sin(mLeft->Value(identifiers));

        case N_COS: 
            return cos(mLeft->Value(identifiers));

        default: 
            FatalError();   // THROW EXCEPTION
            return 0.0;    
	}
	break;

    default: 
        FatalError();   // THROW EXCEPTION
        return 0.0;
    }
    FatalError();   // THROW EXCEPTION
    return 0.0;
}


