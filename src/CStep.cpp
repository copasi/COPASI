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
CStep::CStep(string &stepname, int subs, int prods)
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
int CStep::Assign(string &stepname, 
                  string &chemeq, 
                  string &ktype, 
                  int subs, 
                  int prods, 
                  int mods, 
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
void CStep::AllocStep(int subs, int prods)
{
}


// free all dynamically allocated variables
void CStep::DeAlloc(void)
{
}


void CStep::AddSubstrate(int index) {mSubstrates.push_back(index);}

void CStep::AddProduct(int index) {mProducts.push_back(index);}

void CStep::AddModifier(int index) {mModifiers.push_back(index);}

void CStep::AddParameter(double constant) {mParameters.push_back(constant);}

void CStep::EraseSubstrates(int index) {mSubstrates.erase(0);}

void CStep::EraseProducts(int index) {mProducts.erase(0);}

void CStep::EraseModifiers(int index) {mModifiers.erase(0);}

void CStep::EraseParameters(double constant) {mParameters.erase(0);}



int CStep::Load(CReadConfig &configbuffer)
{
    char Name[10];
    int Fail = 0;
    int Size = 0;
    int i = 0;
    
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
    
    if (Fail = configbuffer.GetVariable("Reversible", "int", &mReversible))
        return Fail;
    
    if (Fail = configbuffer.GetVariable("Substrates", "int", &Size))
        return Fail;
    mSubstrates.resize(Size);
    
    if (Fail = configbuffer.GetVariable("Products", "int", &Size))
        return Fail;
    mProducts.resize(Size);
    
    if (Fail = configbuffer.GetVariable("Modifiers", "int", &Size))
        return Fail;
    mModifiers.resize(Size);
    
    if (Fail = configbuffer.GetVariable("Constants", "int", &Size))
        return Fail;
    mParameters.resize(Size);

    // read the vectors
    for (i=0; i<mSubstrates.size(); i++)
    {
        Size = snprintf(Name, sizeof(Name), "Subs%d", i);
        if (Size < 0 || sizeof(Name) - 1 < Size) FatalError();

        if (Fail = configbuffer.GetVariable(Name, "int", &mSubstrates[i]))
            return Fail;
    }

    for (i=0; i<mProducts.size(); i++)
    {
        Size = snprintf(Name, sizeof(Name), "Prod%d", i);
        if (Size < 0 || sizeof(Name) - 1 < Size) FatalError();

        if (Fail = configbuffer.GetVariable(Name, "int", &mProducts[i]))
            return Fail;
    }

    for (i=0; i<mModifiers.size(); i++)
    {
        Size = snprintf(Name, sizeof(Name), "Modf%d", i);
        if (Size < 0 || sizeof(Name) - 1 < Size) FatalError();

        if (Fail = configbuffer.GetVariable(Name, "int", &mModifiers[i]))
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


int CStep::Save(CWriteConfig &configbuffer)
{
    char Name[10];
    int Fail = 0;
    int Size = 0;
    int i = 0;
    
   if (Fail = configbuffer.SetVariable("Step", "string", &mName))
        return Fail;
    
    if (Fail = configbuffer.SetVariable("Equation", "string", &mChemEq))
        return Fail;
    
    if (Fail = configbuffer.SetVariable("KineticType", "string", &mKinType))
        return Fail;
    
    if (Fail = configbuffer.SetVariable("Flux", "double", &mFlux))
        return Fail;
    
    if (Fail = configbuffer.SetVariable("Reversible", "int", &mReversible))
        return Fail;
    
    Size = mSubstrates.size();
    if (Fail = configbuffer.SetVariable("Substrates", "int", &Size))
        return Fail;
    
    Size = mProducts.size();
    if (Fail = configbuffer.SetVariable("Products", "int", &Size))
        return Fail;
    
    Size = mModifiers.size();
    if (Fail = configbuffer.SetVariable("Modifiers", "int", &Size))
        return Fail;
    
    Size = mParameters.size();
    if (Fail = configbuffer.SetVariable("Constants", "int", &Size))
        return Fail;

    // read the vectors
    for (i=0; i<mSubstrates.size(); i++)
    {
        Size = snprintf(Name, sizeof(Name), "Subs%d", i);
        if (Size < 0 || sizeof(Name) - 1 < Size) FatalError();

        if (Fail = configbuffer.SetVariable(Name, "int", &mSubstrates[i]))
            return Fail;
    }

    for (i=0; i<mProducts.size(); i++)
    {
        Size = snprintf(Name, sizeof(Name), "Prod%d", i);
        if (Size < 0 || sizeof(Name) - 1 < Size) FatalError();

        if (Fail = configbuffer.SetVariable(Name, "int", &mProducts[i]))
            return Fail;
    }

    for (i=0; i<mModifiers.size(); i++)
    {
        Size = snprintf(Name, sizeof(Name), "Modf%d", i);
        if (Size < 0 || sizeof(Name) - 1 < Size) FatalError();

        if (Fail = configbuffer.SetVariable(Name, "int", &mModifiers[i]))
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
