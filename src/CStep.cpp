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

    mSubstrates = NULL;
    mProducts = NULL;
    mModifiers = NULL;
    mParameters = NULL;
    mCallParameters = NULL;
}

CStep::CStep(const string & name)
{
    mName = name;
    mFlux = 0.0;
    mReversible = TRUE;
    mFunction = NULL;

    mSubstrates = NULL;
    mProducts = NULL;
    mModifiers = NULL;
    mParameters = NULL;
    mCallParameters = NULL;
}

void CStep::Init()
{
    if (!mSubstrates) mSubstrates = new vector < CId2Metab >;
    if (!mProducts) mProducts = new vector < CId2Metab >;
    if (!mModifiers) mModifiers = new vector < CId2Metab >;
    if (!mParameters) mParameters = new vector < CId2Param >;
    if (!mCallParameters) mCallParameters = new vector < CCallParameter >;
}

CStep::~CStep() {}

void CStep::Delete()
{
    if (mSubstrates) delete mSubstrates;
    mSubstrates = NULL;
    if (mProducts) delete mProducts;
    mProducts = NULL;
    if (mModifiers) delete mModifiers;
    mModifiers = NULL;
    if (mParameters) delete mParameters;
    mParameters = NULL;
    if (mCallParameters) delete mCallParameters;
    mCallParameters = NULL;
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
    mCallParameters = rhs.mCallParameters;

    return *this;
}

C_INT32 CStep::Load(CReadConfig & configbuffer)
{
    C_INT32 Fail = 0;
    C_INT32 Size = 0;
    C_INT32 i = 0;
    
    string KinType;
    
    Init();
    
    if (Fail = configbuffer.GetVariable("Step", "string", &mName,
                                        CReadConfig::SEARCH))
        return Fail;
    
    if (Fail = configbuffer.GetVariable("Equation", "string", &mChemEq))
        return Fail;
    
    if (Fail = configbuffer.GetVariable("KineticType", "string", &KinType))
        return Fail;

    SetFunction(KinType);
    if (mFunction == NULL) return Fail = 1;

    InitIdentifiers();
    
    if (Fail = configbuffer.GetVariable("Flux", "C_FLOAT64", &mFlux))
        return Fail;
    
    if (Fail = configbuffer.GetVariable("Reversible", "C_INT32", &mReversible))
        return Fail;
    
    if (configbuffer.GetVersion() < "4")
        Fail = LoadOld(configbuffer);
    else 
        Fail = LoadNew(configbuffer);
        
    return Fail; 
}

C_INT32 CStep::Save(CWriteConfig & configbuffer)
{
    C_INT32 Fail = 0;
    C_INT32 Size = 0;
    C_INT32 i = 0;
    
    if (Fail = configbuffer.SetVariable("Step", "string", &mName))
        return Fail;
    
    if (Fail = configbuffer.SetVariable("Equation", "string", &mChemEq))
        return Fail;
    
    string KinType = mFunction->GetName();
    if (Fail = configbuffer.SetVariable("KineticType", "string", &KinType))
        return Fail;

    if (Fail = configbuffer.SetVariable("Flux", "C_FLOAT64", &mFlux))
        return Fail;
    
    if (Fail = configbuffer.SetVariable("Reversible", "C_INT32", &mReversible))
        return Fail;
    
    Size = mSubstrates->size();
    if (Fail = configbuffer.SetVariable("Substrates", "C_INT32", &Size))
        return Fail;
    for (i = 0; i < Size; i++)
    {
        if (Fail = configbuffer.SetVariable("Identifier", "string",
                                            &(*mSubstrates)[i].mIdentifierName))
            return Fail;
        if (Fail = configbuffer.SetVariable("Metabolite", "string",
                                            &(*mSubstrates)[i].mMetaboliteName))
            return Fail;
        if (Fail = configbuffer.SetVariable("Compartment", "string",
                                            &(*mSubstrates)[i].mCompartmentName))
            return Fail;
    }
    
    Size = mProducts->size();
    if (Fail = configbuffer.SetVariable("Products", "C_INT32", &Size))
        return Fail;
    for (i = 0; i < Size; i++)
    {
        if (Fail = configbuffer.SetVariable("Identifier", "string",
                                            &(*mProducts)[i].mIdentifierName))
            return Fail;
        if (Fail = configbuffer.SetVariable("Metabolite", "string",
                                            &(*mProducts)[i].mMetaboliteName))
            return Fail;
        if (Fail = configbuffer.SetVariable("Compartment", "string",
                                            &(*mProducts)[i].mCompartmentName))
            return Fail;
    }

    Size = mModifiers->size();
    if (Fail = configbuffer.SetVariable("Modifiers", "C_INT32", &Size))
        return Fail;
    for (i = 0; i < Size; i++)
    {
        if (Fail = configbuffer.SetVariable("Identifier", "string",
                                            &(*mModifiers)[i].mIdentifierName))
            return Fail;
        if (Fail = configbuffer.SetVariable("Metabolite", "string",
                                            &(*mModifiers)[i].mMetaboliteName))
            return Fail;
        if (Fail = configbuffer.SetVariable("Compartment", "string",
                                            &(*mModifiers)[i].mCompartmentName))
            return Fail;
    }

    Size = mParameters->size();
    if (Fail = configbuffer.SetVariable("Constants", "C_INT32", &Size))
        return Fail;
    for (i = 0; i < Size; i++)
    {
        if (Fail = configbuffer.SetVariable("Identifier", "string",
                                            &(*mParameters)[i].mIdentifierName))
            return Fail;
        if (Fail = configbuffer.SetVariable("Value", "C_FLOAT64",
                                            &(*mParameters)[i].mValue))
            return Fail;
    }
    
    return Fail; 
}

vector < CStep::CId2Metab > &CStep::Substrates() {return *mSubstrates;}

vector < CStep::CId2Metab > &CStep::Products() {return *mProducts;}

vector < CStep::CId2Metab > &CStep::Modifiers() {return *mModifiers;}

vector < CStep::CId2Param > &CStep::Parameters() {return *mParameters;}

string CStep::GetName() {return mName;}

string CStep::GetChemEq() {return mChemEq;}

CBaseFunction & CStep::GetFunction() {return *mFunction;}

C_FLOAT64 CStep::GetFlux() {return mFlux;}

C_INT16 CStep::IsReversible() {return (mReversible == TRUE);}

void CStep::SetName(const string & name) {mName = name;}

void CStep::SetChemEq(const string & chemEq) {mChemEq = chemEq;}

void CStep::SetFlux(C_FLOAT64 flux) {mFlux = flux;}

void CStep::SetReversible(C_INT16 reversible) {mReversible = reversible;}

void CStep::SetFunction(const string & functionName)
{
    mFunction = &Copasi.FunctionDB.FindFunction(functionName);
}

void CStep::InitIdentifiers()
{
    C_INT32 i;
    C_INT32 Count;
    
    if (!mFunction) FatalError();

    for (i = 0; i < mCallParameters->size(); i++)
        (*mCallParameters)[i].Delete();
    mCallParameters->clear();
    
    mCallParameters->resize(mFunction->CallParameters().size());
    for (i = 0; i < mCallParameters->size(); i++)
    {
        (*mCallParameters)[i].Init();
        (*mCallParameters)[i].
            SetType(mFunction->CallParameters()[i].GetType());

        Count = mFunction->CallParameters()[i].GetCount();
        (*mCallParameters)[i].Identifiers().resize(Count);
        for (C_INT32 j = 0; j < Count; j++)
            (*mCallParameters)[i].Identifiers()[j] = NULL;
    }
}

void CStep::SetIdentifiers()
{
    pair < C_INT32, C_INT32 > Tuple;
    
    C_INT32 i;
    
    for (i = 0; i < mSubstrates->size(); i++)
    {
        Tuple = mFunction->FindIdentifier((*mSubstrates)[i].mIdentifierName);

        if (Tuple.first < 0 || Tuple.second < 0) FatalError();
        if ((*mCallParameters)[Tuple.first].GetType() 
            != CCallParameter::VECTOR_DOUBLE) FatalError();
                                                     
        (*mCallParameters)[Tuple.first].Identifiers()[Tuple.second] =
            (*mSubstrates)[i].mpMetabolite->GetConcentration();
    }
    
    for (i = 0; i < mProducts->size(); i++)
    {
        Tuple = mFunction->FindIdentifier((*mProducts)[i].mIdentifierName);

        if (Tuple.first < 0 || Tuple.second < 0) FatalError();
        if ((*mCallParameters)[Tuple.first].GetType ()
            != CCallParameter::VECTOR_DOUBLE) FatalError();
                                                     
        (*mCallParameters)[Tuple.first].Identifiers()[Tuple.second] =
            (*mProducts)[i].mpMetabolite->GetConcentration();
    }

    for (i = 0; i < mModifiers->size(); i++)
    {
        Tuple = mFunction->FindIdentifier((*mModifiers)[i].mIdentifierName);

        if (Tuple.first < 0 || Tuple.second < 0) FatalError();
        if ((*mCallParameters)[Tuple.first].GetType()
            != CCallParameter::VECTOR_DOUBLE) FatalError();
                                                     
        (*mCallParameters)[Tuple.first].Identifiers()[Tuple.second] =
            (*mModifiers)[i].mpMetabolite->GetConcentration();
    }

    for (i = 0; i < mParameters->size(); i++)
    {
        Tuple = mFunction->FindIdentifier((*mParameters)[i].mIdentifierName);

        if (Tuple.first < 0 || Tuple.second < 0) FatalError();
        if ((*mCallParameters)[Tuple.first].GetType()
            != CCallParameter::VECTOR_DOUBLE) FatalError();
                                                     
        (*mCallParameters)[Tuple.first].Identifiers()[Tuple.second] =
            &(*mParameters)[i].mValue;
    }
}

void CStep::CheckIdentifiers()
{
    for (C_INT32 i = 0; i < mCallParameters->size(); i++)
    {
        for (C_INT32 j = 0; j < (*mCallParameters)[i].Identifiers().size(); j++)
            if (!(*mCallParameters)[i].Identifiers()[j]) FatalError();
    }
}

void CStep::Compile(CCopasiVector < CMetab * > &metabolites)
{
    InitIdentifiers();
    SetIdentifiers();
    CheckIdentifiers();
}

C_INT32 CStep::LoadNew(CReadConfig & configbuffer)
{
    C_INT32 Fail = 0;
    C_INT32 Size;
    C_INT32 i;
    
    if (Fail = configbuffer.GetVariable("Substrates", "C_INT32", &Size))
        return Fail;
    mSubstrates->resize(Size);
    for (i=0; i < Size; i++)
    {
//        Size = snprintf(Name, sizeof(Name), "Subs%d", i);
//        if (Size < 0 || sizeof(Name) - 1 < Size) FatalError();

        if (Fail = configbuffer.GetVariable("Identifier", "string",
                                            &(*mSubstrates)[i].mIdentifierName))
            return Fail;
        if (Fail = configbuffer.GetVariable("Metabolite", "string",
                                            &(*mSubstrates)[i].mMetaboliteName))
            return Fail;
        if (Fail = configbuffer.GetVariable("Compartment", "string",
                                            &(*mSubstrates)[i].mCompartmentName))
            return Fail;
    }
    
    if (Fail = configbuffer.GetVariable("Products", "C_INT32", &Size))
        return Fail;
    mProducts->resize(Size);
    for (i=0; i < Size; i++)
    {
        if (Fail = configbuffer.GetVariable("Identifier", "string",
                                            &(*mProducts)[i].mIdentifierName))
            return Fail;
        if (Fail = configbuffer.GetVariable("Metabolite", "string",
                                            &(*mProducts)[i].mMetaboliteName))
            return Fail;
        if (Fail = configbuffer.GetVariable("Compartment", "string",
                                            &(*mProducts)[i].mCompartmentName))
            return Fail;
    }

    if (Fail = configbuffer.GetVariable("Modifiers", "C_INT32", &Size))
        return Fail;
    mModifiers->resize(Size);
    for (i = 0; i < Size; i++)
    {
        if (Fail = configbuffer.GetVariable("Identifier", "string",
                                            &(*mModifiers)[i].mIdentifierName))
            return Fail;
        if (Fail = configbuffer.GetVariable("Metabolite", "string",
                                            &(*mModifiers)[i].mMetaboliteName))
            return Fail;
        if (Fail = configbuffer.GetVariable("Compartment", "string",
                                            &(*mModifiers)[i].mCompartmentName))
            return Fail;
    }

    if (Fail = configbuffer.GetVariable("Constants", "C_INT32", &Size))
        return Fail;
    mParameters->resize(Size);
    for (i = 0; i < Size; i++)
    {
        if (Fail = configbuffer.GetVariable("Identifier", "string",
                                            &(*mParameters)[i].mIdentifierName))
            return Fail;
        if (Fail = configbuffer.GetVariable("Value", "C_FLOAT64",
                                            &(*mParameters)[i].mValue))
            return Fail;
    }
    
    return Fail;
}

C_INT32 CStep::LoadOld(CReadConfig & configbuffer)
{
    C_INT32 Fail = 0;
    C_INT32 Size;

    if (Fail = configbuffer.GetVariable("Substrates", "C_INT32", &Size))
        return Fail;
    mSubstrates->resize(Size);
    
    if (Fail = configbuffer.GetVariable("Products", "C_INT32", &Size))
        return Fail;
    mProducts->resize(Size);

    if (Fail = configbuffer.GetVariable("Modifiers", "C_INT32", &Size))
        return Fail;
    mModifiers->resize(Size);

    if (Fail = configbuffer.GetVariable("Constants", "C_INT32", &Size))
        return Fail;
    mParameters->resize(Size);
    return Fail;
}

CStep::CId2Metab::CId2Metab() {}

CStep::CId2Metab::~CId2Metab() {}

CStep::CId2Param::CId2Param() {}

CStep::CId2Param::~CId2Param() {}
