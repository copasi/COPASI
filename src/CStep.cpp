// step.cpp : implementation of the CStep class
//
/////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

#include "copasi.h"
#include "globals.h"
#include "CStep.h"

/////////////////////////////////////////////////////////////////////////////
// CStep

// create an empty CStep object
CStep::CStep()
{
    mFlux = 0.0;
    mReversible = TRUE;
    
    mKinetics = NULL;
}


// create a CStep object with values
CStep::CStep(string &stepname, long subs, long prods)
{
    mName = stepname;
    mFlux = 0.0;
    mReversible = TRUE;

    mKinetics = NULL;
}

// destruct a CStep object
CStep::~CStep()
{
}


// assign the values to the member variables
long CStep::Assign(string &stepname, 
                   string &chemeq, 
                   string &ktype, 
                   long subs, 
                   long prods, 
                   long mods, 
                   double flux, 
                   short rev)
{
    mName = stepname;
    mChemEq = chemeq;
    mFlux = flux;
    mReversible = rev;
    
    mSubstrates.erase(0);
    mProducts.erase(0);
    mModifiers.erase(0);
    mParameters.erase(0);
    
    mKinetics = NULL;
    mKinType = ktype;

    assert(FALSE);  // Make sure we come here to fix the code!!!
    return -1;      // KinDB.Lookup(const string ktype, mKinetics);
}


// overload assignment operator
CStep &CStep::operator=(CStep &ptRHS)
{
    mName = ptRHS.mName;
    mChemEq = ptRHS.mChemEq;
    mFlux = ptRHS.mFlux;
    mReversible = ptRHS.mReversible;

    mSubstrates = ptRHS.mSubstrates;
    mProducts = ptRHS.mProducts;
    mModifiers = ptRHS.mModifiers;
    mParameters = ptRHS.mParameters;

    mKinetics = ptRHS.mKinetics;
    mKinType = ptRHS.mKinType;

    return *this;  // Assignment operator returns left side.
}

// allocate memory for dynamic variables
void CStep::AllocStep(long subs, long prods)
{
}


// free all dynamically allocated variables
void CStep::DeAlloc(void)
{
}


void CStep::AddSubstrate(long index) {mSubstrates.push_back(index);}

void CStep::AddProduct(long index) {mProducts.push_back(index);}

void CStep::AddModifier(long index) {mModifiers.push_back(index);}

void CStep::AddParameter(double constant) {mParameters.push_back(constant);}

void CStep::EraseSubstrates(long index) {mSubstrates.erase(0);}

void CStep::EraseProducts(long index) {mProducts.erase(0);}

void CStep::EraseModifiers(long index) {mModifiers.erase(0);}

void CStep::EraseParameters(double constant) {mParameters.erase(0);}



long CStep::Load(CReadConfig &configbuffer)
{
    char Name[10];
    long Fail = 0;
    long Size = 0;
    long i = 0;
    
    configbuffer.SetMode(CReadConfig_SEARCH);
    configbuffer.SetMode(CReadConfig_LOOP);
    
    if (Fail = configbuffer.GetVariable("Step", "string", &mName))
        return Fail;
    
    configbuffer.SetMode(-CReadConfig_SEARCH);
    configbuffer.SetMode(-CReadConfig_LOOP);
    
    if (Fail = configbuffer.GetVariable("Equation", "string", &mChemEq))
        return Fail;
    
    if (Fail = configbuffer.GetVariable("KineticType", "string", &mKinType))
        return Fail;
    
    // sanity check
    if (FALSE) //  (!KinDB.Lookup(mKinType, Kinetics))
    {
        FatalError()
            }

    if (Fail = configbuffer.GetVariable("Flux", "double", &mFlux))
        return Fail;
    
    if (Fail = configbuffer.GetVariable("Reversible", "long", &mReversible))
        return Fail;
    
    if (Fail = configbuffer.GetVariable("Substrates", "long", &Size))
        return Fail;
    mSubstrates.resize(Size);
    
    if (Fail = configbuffer.GetVariable("Products", "long", &Size))
        return Fail;
    mProducts.resize(Size);
    
    if (Fail = configbuffer.GetVariable("Modifiers", "long", &Size))
        return Fail;
    mModifiers.resize(Size);
    
    if (Fail = configbuffer.GetVariable("Constants", "long", &Size))
        return Fail;
    mParameters.resize(Size);

    // read the vectors
    for (i=0; i<mSubstrates.size(); i++)
    {
        Size = snprintf(Name, sizeof(Name), "Subs%d", i);
        if (Size < 0 || sizeof(Name) - 1 < Size) FatalError();

        if (Fail = configbuffer.GetVariable(Name, "long", &mSubstrates[i]))
            return Fail;
    }

    for (i=0; i<mProducts.size(); i++)
    {
        Size = snprintf(Name, sizeof(Name), "Prod%d", i);
        if (Size < 0 || sizeof(Name) - 1 < Size) FatalError();

        if (Fail = configbuffer.GetVariable(Name, "long", &mProducts[i]))
            return Fail;
    }

    for (i=0; i<mModifiers.size(); i++)
    {
        Size = snprintf(Name, sizeof(Name), "Modf%d", i);
        if (Size < 0 || sizeof(Name) - 1 < Size) FatalError();

        if (Fail = configbuffer.GetVariable(Name, "long", &mModifiers[i]))
            return Fail;
    }

    for (i=0; i<mParameters.size(); i++)
    {
        Size = snprintf(Name, sizeof(Name), "Param%d", i);
        if (Size < 0 || sizeof(Name) - 1 < Size) FatalError();

        if (Fail = configbuffer.GetVariable(Name, "double", &mParameters[i]))
            return Fail;
    }
    return Fail; 
}


long CStep::Save(CWriteConfig &configbuffer)
{
    char Name[10];
    long Fail = 0;
    long Size = 0;
    long i = 0;
    
    if (Fail = configbuffer.SetVariable("Step", "string", &mName))
        return Fail;
    
    if (Fail = configbuffer.SetVariable("Equation", "string", &mChemEq))
        return Fail;
    
    if (Fail = configbuffer.SetVariable("KineticType", "string", &mKinType))
        return Fail;
    
    if (Fail = configbuffer.SetVariable("Flux", "double", &mFlux))
        return Fail;
    
    if (Fail = configbuffer.SetVariable("Reversible", "long", &mReversible))
        return Fail;
    
    Size = mSubstrates.size();
    if (Fail = configbuffer.SetVariable("Substrates", "long", &Size))
        return Fail;
    
    Size = mProducts.size();
    if (Fail = configbuffer.SetVariable("Products", "long", &Size))
        return Fail;
    
    Size = mModifiers.size();
    if (Fail = configbuffer.SetVariable("Modifiers", "long", &Size))
        return Fail;
    
    Size = mParameters.size();
    if (Fail = configbuffer.SetVariable("Constants", "long", &Size))
        return Fail;

    // read the vectors
    for (i=0; i<mSubstrates.size(); i++)
    {
        Size = snprintf(Name, sizeof(Name), "Subs%d", i);
        if (Size < 0 || sizeof(Name) - 1 < Size) FatalError();

        if (Fail = configbuffer.SetVariable(Name, "long", &mSubstrates[i]))
            return Fail;
    }

    for (i=0; i<mProducts.size(); i++)
    {
        Size = snprintf(Name, sizeof(Name), "Prod%d", i);
        if (Size < 0 || sizeof(Name) - 1 < Size) FatalError();

        if (Fail = configbuffer.SetVariable(Name, "long", &mProducts[i]))
            return Fail;
    }

    for (i=0; i<mModifiers.size(); i++)
    {
        Size = snprintf(Name, sizeof(Name), "Modf%d", i);
        if (Size < 0 || sizeof(Name) - 1 < Size) FatalError();

        if (Fail = configbuffer.SetVariable(Name, "long", &mModifiers[i]))
            return Fail;
    }

    for (i=0; i<mParameters.size(); i++)
    {
        Size = snprintf(Name, sizeof(Name), "Param%d", i);
        if (Size < 0 || sizeof(Name) - 1 < Size) FatalError();

        if (Fail = configbuffer.SetVariable(Name, "double", &mParameters[i]))
            return Fail;
    }
    return Fail; 
}

string CStep::GetChemEq(void) {return mChemEq;}

long CStep::SubstrateNo(void) {return mSubstrates.size()};

CNodeK CStep::Substrate(long index) {return ;
