// ckinetics.cpp : implementation of the CKinetics class
//
/////////////////////////////////////////////////////////////////////////////

#include "copasi.h"
#include "globals.h"
#include "CKinetics.h"

double UDKin(void *M, double *s, long r);

double UDKin(void *M, double *s, long r)
{
    double ret = 0.0;
// CModel *m = (CModel *) M;
#ifdef _DEBUG
// assert( m->Step[r].Kinetics->Funct );
#endif
// ret = m->Step[r].Kinetics->Funct->CalcValue( m, s, r );
    return ret;
}


/////////////////////////////////////////////////////////////////////////////
// CKinetics

// the default constructor
CKinetics::CKinetics()
{
    mFunction = NULL;
    mSubstrates = NULL;
    mProducts = NULL;
    mModifiers = NULL;
    mParameters = NULL;
    mReversible = FALSE;
    mUserDefined = FALSE;
}

// this constructor is for built-in kinetic types
CKinetics::CKinetics(const string &kiname, 
                     long subs, 
                     long prods, 
                     long mods, 
                     long prm, 
                     double (*ratefunc)(void *,double *, long), 
                     short rev)
{
    assert(FALSE);
    
    mName = kiname;
    mFunction = ratefunc;
    mReversible = rev;
    mUserDefined = FALSE;
}

// this constructor is for user-defined types
CKinetics::CKinetics(CKinFunction &function)
{
    mFunct = &function;
    mName = mFunct->GetName();
    mSubstrates = mFunct->Substrates();
    mProducts = mFunct->Products();
    mModifiers = mFunct->Modifiers();
    mParameters = mFunct->Parameters();
    
    mFunction = UDKin;
    mReversible = mFunct->IsReversible();
    mUserDefined = TRUE;
}

CKinetics::~CKinetics()
{
    // if (UserDefined && (Funct!=NULL)) delete Funct;
    // if (Param!=NULL) delete [] Param;
    // if (Modf!=NULL) delete [] Modf;
}

void CKinetics::SetParameterName(const string &name, long index)
{
    mFunct->SetParameterName(name, index);
}

void CKinetics::SetModifierName(const string &name, long index)
{
    mFunct->SetModifierName(name, index);
}

// returns the index of the parameter specified
long CKinetics::FindParameter(const string &name)
{
    for (long i=0; i<(*mParameters).size(); i++)
        if ((*mParameters)[i]->GetName() == name) return i;
    return -1;
}

// this function loads an object from the character buffer
long CKinetics::Load(CReadConfig &configbuffer)
{
    long Fail = 0;
#ifdef XXXX
    long SubstrateNo = 0;
    long ProductNo = 0;
    long ModifierNo = 0;
    long ParameterNo = 0;
#endif // XXXX
    
    configbuffer.SetMode(CReadConfig_SEARCH);
    configbuffer.SetMode(CReadConfig_LOOP);

    if (Fail = configbuffer.GetVariable("UDKType", "string", &mName))
        return Fail;

    configbuffer.SetMode(-CReadConfig_SEARCH);
    configbuffer.SetMode(-CReadConfig_LOOP);

    if (Fail = configbuffer.GetVariable("User-defined", "long", &mUserDefined))
        return Fail;

    if (!mUserDefined) return Fail;

    if (Fail = configbuffer.GetVariable("Reversible", "long", &mReversible))
        return Fail;

#ifdef XXXX
    if (Fail = configbuffer.GetVariable("Substrates", "long", &SubstrateNo))
        return Fail;

    if (Fail = configbuffer.GetVariable("Products", "long", &ProductNo))
        return Fail;

    if (Fail = configbuffer.GetVariable("Modifiers", "long", &ModifierNo))
        return Fail;

    if (Fail = configbuffer.GetVariable("Constants", "long", &ParameterNo))
        return Fail;
#endif // XXXX

    // create the CKinFunction object 
    mFunct = new CKinFunction;
    // load it
    if (Fail = mFunct->Load(configbuffer))
        return Fail;
    // set the function pointer to the right handler
    mFunction = UDKin;

    return Fail;
}

// this function saves the object to to the CStdioFile
long CKinetics::Save(CWriteConfig &configbuffer)
{
    long Fail = 0;
    long tmp = 0;

    if (Fail = configbuffer.SetVariable("UDKType", "string", &mName))
        return Fail;

    if (Fail = configbuffer.SetVariable("User-defined", "long", &mUserDefined))
        return Fail;

    if (!mUserDefined) return Fail;

    if (Fail = configbuffer.SetVariable("Reversible", "long", &mReversible))
        return Fail;

#ifdef XXXX
    tmp = (*mSubstrates).size();
    if (Fail = configbuffer.SetVariable("Substrates", "long", &tmp))
        return Fail;

    tmp = (*mProducts).size();
    if (Fail = configbuffer.SetVariable("Products", "long", &tmp))
        return Fail;

    tmp = (*mModifiers).size();
    if (Fail = configbuffer.SetVariable("Modifiers", "long", &tmp))
        return Fail;

    tmp = (*mParameters).size();
    if (Fail = configbuffer.SetVariable("Constants", "long", &tmp))
        return Fail;
#endif // XXXX

    if (Fail = mFunct->Save(configbuffer))
        return Fail;
    
    return Fail;
}
