// CNodeK.cpp : classes for function tree
//
/////////////////////////////////////////////////////////////////////////////

#include <math.h>

#include "copasi.h"
#include "globals.h"
#include "CNodeK.h"

////////////////////////////////////
// CNodeK implementation

CNodeK::CNodeK()
{
    mType     = N_NOP;
    mSubtype  = N_NOP;
    mLeft     = NULL;
    mRight    = NULL;
    mConstant = 0.0;
    mIndex    = -1;
}

CNodeK::CNodeK(const char type, const char subtype)
{
    mType     = type;
    mSubtype  = subtype;
    mLeft     = NULL;
    mRight    = NULL;
    mConstant = 0.0;
    mIndex    = -1;
}

// this constructor is for identifier nodes
CNodeK::CNodeK(const string &name)
{
    mType     = N_IDENTIFIER;
    mSubtype  = N_NOP;
    mLeft     = NULL;
    mRight    = NULL;
    mConstant = 0.0;
    mName     = name;
    mIndex    = -1;
}

// this constructor is for numerical constants
CNodeK::CNodeK(const double c)
{
    mType     = N_NUMBER;
    mSubtype  = N_NOP;
    mLeft     = NULL;
    mRight    = NULL;
    mConstant = c;
    mIndex    = -1;
}

CNodeK::~CNodeK()
{
}

void CNodeK::SetLeft(CNodeK &pt) {mLeft = &pt;}

void CNodeK::SetLeft(CNodeK *pt) {mLeft = pt;}

void CNodeK::SetRight(CNodeK &pt) {mRight = &pt;}

void CNodeK::SetRight(CNodeK *pt) {mRight = pt;}

void CNodeK::SetSubtype(const char subtype) {mSubtype = subtype;}
    
void CNodeK::SetIndex(const int index) {mIndex = index;}

void CNodeK::SetName(const string &name) {mName = name;}

CNodeK &CNodeK::GetLeft(void) 
{ 
    if (!mLeft) 
        FatalError(); // Call LeftIsValid first to avoid this!
    return *mLeft;
}

CNodeK &CNodeK::GetRight(void)
{
    if (!mRight) 
        FatalError(); // Call RightIsValid first to avoid this!
    return *mRight;
}

string CNodeK::GetName(void) {return mName;}

char CNodeK::GetType(void) {return mType;}

char CNodeK::GetSubtype(void) {return mSubtype;}

int CNodeK::IsLeftValid() {return (int) mLeft;}

int CNodeK::IsRightValid() {return (int) mRight;}

int CNodeK::IsNumber(void) {return mType == N_NUMBER;}

int CNodeK::IsIdentifier(void)
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

int CNodeK::IsOperator(void)
{
    return mType == N_OPERATOR;
}

void CNodeK::Constant(const double constant)
{
    mType     = N_NUMBER;
    mConstant = constant;
}

void CNodeK::Operator(char operation)
{
    mType     = N_OPERATOR;
    mSubtype  = operation;
}

void CNodeK::Function(void)
{
    mType     = N_FUNCTION;
}

// calculates the value of this sub-tree (ie with this node as root)
double CNodeK::Value(const CModel &model, double *s, int r)
{
    // if it is a constant or an identifier just return its value
    if (IsNumber()) return mConstant;

    switch (mType)
    {
    case N_SUBSTRATE:
//        return s[model.IRow[model.Step[r].Substrate[Index]]];
        FatalError();   // THROW EXCEPTION
    break;
        
    case N_PRODUCT:
//        return s[model.IRow[model.Step[r].Product[Index]]];
        FatalError();   // THROW EXCEPTION
        break;
        
    case N_MODIFIER:
//        return s[model.IRow[model.Step[r].Modifier[Index]]];
        FatalError();   // THROW EXCEPTION
        break;
        
    case N_KCONSTANT:
//        return model.Step[r].Param[Index];
        FatalError();   // THROW EXCEPTION
        break;
        
    case N_OPERATOR:
	switch (mSubtype)
	{
        case '+':
            return mLeft->Value(model, s,r) + mRight->Value(model, s,r);

        case '-': 
            return mLeft->Value(model, s,r) - mRight->Value(model, s,r);

        case '*': 
            return mLeft->Value(model, s,r) * mRight->Value(model, s,r);
        
        case '/': 
            return mLeft->Value(model, s,r) / mRight->Value(model, s,r);
        
        case '^': 
            return pow(mLeft->Value(model, s,r), mRight->Value(model, s,r));
        
        default: 
            FatalError();   // THROW EXCEPTION
            return 0.0;
	}
	break;

    case N_FUNCTION:
	switch (mSubtype)
	{
        case '+': 
            return mLeft->Value(model, s,r);

        case '-': 
            return - mLeft->Value(model, s,r);

        case N_EXP: 
            return exp(mLeft->Value(model, s,r));

        case N_LOG: 
            return log(mLeft->Value(model, s,r));

        case N_LOG10: 
            return log10(mLeft->Value(model, s,r));

        case N_SIN: 
            return sin(mLeft->Value(model, s,r));

        case N_COS: 
            return cos(mLeft->Value(model, s,r));

        default: 
            FatalError();   // THROW EXCEPTION
            return 0.0;// THROW EXCEPTION
	}
	break;

    default: 
        FatalError();   // THROW EXCEPTION
        return 0.0;
    }
    FatalError();   // THROW EXCEPTION
    return 0.0;
}

int CNodeK::RightPrecedence(void)
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

int CNodeK::LeftPrecedence(void)
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

int CNodeK::Save(CWriteConfig &configbuffer)
{
    int Fail = 0;
    
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
        if (Fail = configbuffer.SetVariable("Index", "int", &mIndex))
            return Fail;
        if (Fail = configbuffer.SetVariable("Name", "string", &mName))
            return Fail;
    }
    return Fail;
}


int CNodeK::Load(CReadConfig &configbuffer)
{
    int Fail = 0;
    
    if (Fail = configbuffer.GetVariable("Node", "node", &mType, &mSubtype))
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
        if (Fail = configbuffer.GetVariable("Index", "int", &mIndex))
            return Fail;
        if (Fail = configbuffer.GetVariable("Name", "string", &mName))
            return Fail;
    }

    return Fail;
}

CNodeKVector::CNodeKVector()
{
    this->resize(0);
}

CNodeKVector::CNodeKVector(int size)
{
    this->resize(size);
}

int CNodeKVector::Save(CWriteConfig &configbuffer)
{
    int Fail = 0;
    int Size = this->size();
    
    if (Fail = configbuffer.SetVariable("Nodes", "int",
                                        (void *) &Size))
        return Fail;

    for(int i = 0; i < Size; i++)
    {

        if (Fail = (&this->front()+i)->Save(configbuffer))
        {
            break;
        }
    }
    return Fail;
}

int CNodeKVector::Load(CReadConfig &configbuffer)
{
    int Fail = 0;
    int Size = 0;
    
    configbuffer.SetMode(CReadConfig_SEARCH);
    configbuffer.SetMode(CReadConfig_LOOP);
    
    if (Fail = configbuffer.GetVariable("Nodes","int",
                                        (void *) &Size))
        return Fail;

    this->resize(Size);
    
    configbuffer.SetMode(-CReadConfig_LOOP);
    for(int i = 0; i < Size; i++)
    {
        if (Fail = (&this->front()+i)->Load(configbuffer))
        {
            break;
        }
    }
    
    return Fail;
}
