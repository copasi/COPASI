// CStep 
// 
// Derived from Gepasi's cstep.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Stefan Hoops


#include "copasi.h"
#include "CGlobals.h"
#include "CStep.h"
#include "utilities.h"

CStep::CStep()
{
    mFlux = 0.0;
    mReversible = TRUE;
    mFunction = NULL;

}

CStep::CStep(const string & name)
{
    mName = name;
    mFlux = 0.0;
    mReversible = TRUE;
    mFunction = NULL;
}

CStep::~CStep()
{
}

CStep & CStep::operator=(const CStep & rhs)
{
    mName        = rhs.mName;
    mChemEq      = rhs.mChemEq;
    mFunction    = rhs.mFunction;
    mFlux        = rhs.mFlux;
    mReversible  = rhs.mReversible;
    mSubstrates  = rhs.mSubstrates;
    mProducts    = rhs.mProducts;
    mModifiers   = rhs.mModifiers;
    mParameters  = rhs.mParameters;
    mIdentifiers = rhs.mIdentifiers;

    return *this;
}

long CStep::Load(CReadConfig & configbuffer)
{
    char Name[10];
    long Fail = 0;
    long Size = 0;
    long i = 0;
    
    string KinType;
    
    if (Fail = configbuffer.GetVariable("Step", "string", &mName,
                                        CReadConfig::SEARCH))
        return Fail;
    
    if (Fail = configbuffer.GetVariable("Equation", "string", &mChemEq))
        return Fail;
    
    if (Fail = configbuffer.GetVariable("KineticType", "string", &KinType))
        return Fail;

    mFunction = &Copasi.FunctionDB.FindFunction(KinType);
    if (mFunction == NULL) return Fail = 1;
    
    if (Fail = configbuffer.GetVariable("Flux", "double", &mFlux))
        return Fail;
    
    if (Fail = configbuffer.GetVariable("Reversible", "long", &mReversible))
        return Fail;
    
    if (configbuffer.GetVersion() < "4")
        Fail = LoadOld(configbuffer);
    else 
        Fail = LoadNew(configbuffer);
        
    SetFunction(KinType);
    
    return Fail; 
}

long CStep::Save(CWriteConfig & configbuffer)
{
    long Fail = 0;
    long Size = 0;
    long i = 0;
    
    if (Fail = configbuffer.SetVariable("Step", "string", &mName))
        return Fail;
    
    if (Fail = configbuffer.SetVariable("Equation", "string", &mChemEq))
        return Fail;
    
    string KinType = mFunction->GetName();
    if (Fail = configbuffer.SetVariable("KineticType", "string", &KinType))
        return Fail;

    mFunction = &Copasi.FunctionDB.FindFunction(KinType);
    if (mFunction == NULL) return Fail = 1;
    
    if (Fail = configbuffer.SetVariable("Flux", "double", &mFlux))
        return Fail;
    
    if (Fail = configbuffer.SetVariable("Reversible", "long", &mReversible))
        return Fail;
    
    Size = mSubstrates.size();
    if (Fail = configbuffer.SetVariable("Substrates", "long", &Size))
        return Fail;
    for (i = 0; i < Size; i++)
    {
        if (Fail = configbuffer.SetVariable("Identifier", "string",
                                            &mSubstrates[i].Identifier))
            return Fail;
        if (Fail = configbuffer.SetVariable("Metabolite", "string",
                                            &mSubstrates[i].Metabolite))
            return Fail;
        if (Fail = configbuffer.SetVariable("Compartment", "string",
                                            &mSubstrates[i].Compartment))
            return Fail;
    }
    
    Size = mProducts.size();
    if (Fail = configbuffer.SetVariable("Products", "long", &Size))
        return Fail;
    for (i = 0; i < Size; i++)
    {
        if (Fail = configbuffer.SetVariable("Identifier", "string",
                                            &mProducts[i].Identifier))
            return Fail;
        if (Fail = configbuffer.SetVariable("Metabolite", "string",
                                            &mProducts[i].Metabolite))
            return Fail;
        if (Fail = configbuffer.SetVariable("Compartment", "string",
                                            &mProducts[i].Compartment))
            return Fail;
    }

    Size = mModifiers.size();
    if (Fail = configbuffer.SetVariable("Modifiers", "long", &Size))
        return Fail;
    for (i = 0; i < Size; i++)
    {
        if (Fail = configbuffer.SetVariable("Identifier", "string",
                                            &mModifiers[i].Identifier))
            return Fail;
        if (Fail = configbuffer.SetVariable("Metabolite", "string",
                                            &mModifiers[i].Metabolite))
            return Fail;
        if (Fail = configbuffer.SetVariable("Compartment", "string",
                                            &mModifiers[i].Compartment))
            return Fail;
    }

    Size = mParameters.size();
    if (Fail = configbuffer.SetVariable("Constants", "long", &Size))
        return Fail;
    for (i = 0; i < Size; i++)
    {
        if (Fail = configbuffer.SetVariable("Identifier", "string",
                                            &mParameters[i].Identifier))
            return Fail;
        if (Fail = configbuffer.SetVariable("Value", "double",
                                            &mParameters[i].Value))
            return Fail;
    }
    
    return Fail; 
}

vector < CStep::ID2METAB > &CStep::Substrates() {return mSubstrates;}

vector < CStep::ID2METAB > &CStep::Products() {return mProducts;}

vector < CStep::ID2METAB > &CStep::Modifiers() {return mModifiers;}

vector < CStep::ID2PARAM > &CStep::Parameters() {return mParameters;}

string CStep::GetName() {return mName;}

string CStep::GetChemEq() {return mChemEq;}

CKinFunction & CStep::GetFunction() {return *mFunction;}

double CStep::GetFlux() {return mFlux;}

short CStep::IsReversible() {return (mReversible == TRUE);}

void CStep::SetName(const string & name) {mName = name;}

void CStep::SetChemEq(const string & chemEq) {mChemEq = chemEq;}

void CStep::SetFlux(double flux) {mFlux = flux;}

void CStep::SetReversible(short reversible) {mReversible = reversible;}

void CStep::SetFunction(const string & functionName)
{
    mFunction = &Copasi.FunctionDB.FindFunction(functionName);
}

void CStep::InitIdentifiers()
{
    mIdentifiers.clear();
    
    if (mFunction)
    {
        mIdentifiers.resize(mFunction->Identifiers().size());
        for (long i = 0; i < mIdentifiers.size(); i++)
            mIdentifiers[i] = NULL;
    }
}

void CStep::SetIdentifiers()
{
    long i;
    
    for (i = 0; i < mSubstrates.size(); i++)
        mIdentifiers[mFunction->FindIdentifier(mSubstrates[i].Identifier)] =
            mSubstrates[i].pMetabolite->GetConcentration();
    
    for (i = 0; i < mProducts.size(); i++)
        mIdentifiers[mFunction->FindIdentifier(mProducts[i].Identifier)] =
            mProducts[i].pMetabolite->GetConcentration();

    for (i = 0; i < mModifiers.size(); i++)
        mIdentifiers[mFunction->FindIdentifier(mModifiers[i].Identifier)] =
            mModifiers[i].pMetabolite->GetConcentration();

    for (i = 0; i < mParameters.size(); i++)
        mIdentifiers[mFunction->FindIdentifier(mParameters[i].Identifier)] =
            &mParameters[i].Value;
}

void CStep::CheckIdentifiers()
{
    for (long i = 0; i < mIdentifiers.size(); i++)
        if ( !mIdentifiers[i] ) FatalError();
}

void CStep::Compile(CCopasiVector < CMetab * > &metabolites)
{
    InitIdentifiers();
    SetIdentifiers();
    CheckIdentifiers();
}

long CStep::LoadNew(CReadConfig & configbuffer)
{
    long Fail = 0;
    long Size;
    long i;
    
    if (Fail = configbuffer.GetVariable("Substrates", "long", &Size))
        return Fail;
    mSubstrates.resize(Size);
    for (i=0; i < Size; i++)
    {
//        Size = snprintf(Name, sizeof(Name), "Subs%d", i);
//        if (Size < 0 || sizeof(Name) - 1 < Size) FatalError();

        if (Fail = configbuffer.GetVariable("Identifier", "string",
                                            &mSubstrates[i].Identifier))
            return Fail;
        if (Fail = configbuffer.GetVariable("Metabolite", "string",
                                            &mSubstrates[i].Metabolite))
            return Fail;
        if (Fail = configbuffer.GetVariable("Compartment", "string",
                                            &mSubstrates[i].Compartment))
            return Fail;
   }
    
    if (Fail = configbuffer.GetVariable("Products", "long", &Size))
        return Fail;
    mProducts.resize(Size);
    for (i=0; i < Size; i++)
    {
        if (Fail = configbuffer.GetVariable("Identifier", "string",
                                            &mProducts[i].Identifier))
            return Fail;
        if (Fail = configbuffer.GetVariable("Metabolite", "string",
                                            &mProducts[i].Metabolite))
            return Fail;
        if (Fail = configbuffer.GetVariable("Compartment", "string",
                                            &mProducts[i].Compartment))
            return Fail;
    }

    if (Fail = configbuffer.GetVariable("Modifiers", "long", &Size))
        return Fail;
    mModifiers.resize(Size);
    for (i = 0; i < Size; i++)
    {
        if (Fail = configbuffer.GetVariable("Identifier", "string",
                                            &mModifiers[i].Identifier))
            return Fail;
        if (Fail = configbuffer.GetVariable("Metabolite", "string",
                                            &mModifiers[i].Metabolite))
            return Fail;
        if (Fail = configbuffer.GetVariable("Compartment", "string",
                                            &mModifiers[i].Compartment))
            return Fail;
    }

    if (Fail = configbuffer.GetVariable("Constants", "long", &Size))
        return Fail;
    mParameters.resize(Size);
    for (i = 0; i < Size; i++)
    {
        if (Fail = configbuffer.GetVariable("Identifier", "string",
                                            &mParameters[i].Identifier))
            return Fail;
        if (Fail = configbuffer.GetVariable("Value", "double",
                                            &mParameters[i].Value))
            return Fail;
    }
    
    return Fail;
}

long CStep::LoadOld(CReadConfig & configbuffer)
{
    long Fail = 0;
    long Size;
    long i;

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
    return Fail;
}
