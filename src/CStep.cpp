// CStep 
// 
// Derived from Gepasi's cstep.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Stefan Hoops


#include "copasi.h"
#include "CGlobals.h"
#include "CStep.h"
#include "CCompartment.h"
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
        if (Fail = configbuffer.SetVariable("Compartment", "string",
                                            &(*mSubstrates)[i].mCompartmentName))
            return Fail;
        if (Fail = configbuffer.SetVariable("Metabolite", "string",
                                            &(*mSubstrates)[i].mMetaboliteName))
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
        if (Fail = configbuffer.SetVariable("Compartment", "string",
                                            &(*mProducts)[i].mCompartmentName))
            return Fail;
        if (Fail = configbuffer.SetVariable("Metabolite", "string",
                                            &(*mProducts)[i].mMetaboliteName))
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
        if (Fail = configbuffer.SetVariable("Compartment", "string",
                                            &(*mModifiers)[i].mCompartmentName))
            return Fail;
        if (Fail = configbuffer.SetVariable("Metabolite", "string",
                                            &(*mModifiers)[i].mMetaboliteName))
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

string CStep::GetName() const {return mName;}

string CStep::GetChemEq() const {return mChemEq;}

CBaseFunction & CStep::GetFunction() {return *mFunction;}

C_FLOAT64 CStep::GetFlux() const {return mFlux;}

C_INT16 CStep::IsReversible() const {return (mReversible == TRUE);}

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

    mCallParameters->clear();
    
    mCallParameters->resize(mFunction->CallParameters().size());
    for (i = 0; i < mCallParameters->size(); i++)
    {
        (*mCallParameters)[i].
            SetType(mFunction->CallParameters()[i]->GetType());

        Count = mFunction->CallParameters()[i]->GetCountLow();
        (*mCallParameters)[i].Identifiers().resize(Count);
        for (C_INT32 j = 0; j < Count; j++)
            (*mCallParameters)[i].Identifiers()[j] = NULL;
    }
}

void CStep::SetIdentifiers()
{
    pair < C_INT32, C_INT32 > Tuple;
    
    C_INT32 i, j;
    C_INT32 OldSize;
    
    for (i = 0; i < mSubstrates->size(); i++)
    {
        if ((*mSubstrates)[i].mIdentifierName == "") continue;
        
        Tuple = mFunction->FindIdentifier((*mSubstrates)[i].mIdentifierName);

        if (Tuple.first < 0 || Tuple.second < 0) FatalError();
        if ((*mCallParameters)[Tuple.first].GetType() 
            != CCallParameter::VECTOR_DOUBLE) FatalError();

        if ((OldSize = (*mCallParameters)[Tuple.first].Identifiers().size()) <
            Tuple.second + 1)
        {
            (*mCallParameters)[Tuple.first].Identifiers().
                resize(Tuple.second + 1);
            for( j = OldSize; j < Tuple.second + 1; j++)
                (*mCallParameters)[Tuple.first].Identifiers()[j] = NULL;
        }
        
        (*mCallParameters)[Tuple.first].Identifiers()[Tuple.second] =
            (*mSubstrates)[i].mpMetabolite->GetConcentration();
    }
    
    for (i = 0; i < mProducts->size(); i++)
    {
        if ((*mProducts)[i].mIdentifierName == "") continue;
        
        Tuple = mFunction->FindIdentifier((*mProducts)[i].mIdentifierName);

        if (Tuple.first < 0 || Tuple.second < 0) FatalError();
        if ((*mCallParameters)[Tuple.first].GetType ()
            != CCallParameter::VECTOR_DOUBLE) FatalError();
                                                     
        if ((OldSize = (*mCallParameters)[Tuple.first].Identifiers().size())
            < Tuple.second + 1)
        {
            (*mCallParameters)[Tuple.first].Identifiers().
                resize(Tuple.second + 1);
            for( j = OldSize; j < Tuple.second + 1; j++)
                (*mCallParameters)[Tuple.first].Identifiers()[j] = NULL;
        }
        
        (*mCallParameters)[Tuple.first].Identifiers()[Tuple.second] =
            (*mProducts)[i].mpMetabolite->GetConcentration();
    }

    for (i = 0; i < mModifiers->size(); i++)
    {
        if ((*mModifiers)[i].mIdentifierName == "") continue;
        
        Tuple = mFunction->FindIdentifier((*mModifiers)[i].mIdentifierName);

        if (Tuple.first < 0 || Tuple.second < 0) FatalError();
        if ((*mCallParameters)[Tuple.first].GetType()
            != CCallParameter::VECTOR_DOUBLE) FatalError();
                                                     
        if ((OldSize = (*mCallParameters)[Tuple.first].Identifiers().size())
            < Tuple.second + 1)
        {
            (*mCallParameters)[Tuple.first].Identifiers().
                resize(Tuple.second + 1);
            for( j = OldSize; j < Tuple.second + 1; j++)
                (*mCallParameters)[Tuple.first].Identifiers()[j] = NULL;
        }
        
        (*mCallParameters)[Tuple.first].Identifiers()[Tuple.second] =
            (*mModifiers)[i].mpMetabolite->GetConcentration();
    }

    for (i = 0; i < mParameters->size(); i++)
    {
        if ((*mParameters)[i].mIdentifierName == "") continue;
        
        Tuple = mFunction->FindIdentifier((*mParameters)[i].mIdentifierName);

        if (Tuple.first < 0 || Tuple.second < 0) FatalError();
        if ((*mCallParameters)[Tuple.first].GetType()
            != CCallParameter::VECTOR_DOUBLE) FatalError();
                                                     
        if ((OldSize = (*mCallParameters)[Tuple.first].Identifiers().size())
            < Tuple.second + 1)
        {
            (*mCallParameters)[Tuple.first].Identifiers().
                resize(Tuple.second + 1);
            for( j = OldSize; j < Tuple.second + 1; j++)
                (*mCallParameters)[Tuple.first].Identifiers()[j] = NULL;
        }
        
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

void CStep::Compile(const CCopasiVector < CCompartment > * compartments)
{
    C_INT32 i;
    
    for (i = 0; i < mSubstrates->size(); i++)
        (*mSubstrates)[i].mpMetabolite = 
            &(*compartments)[(*mSubstrates)[i].mCompartmentName].
            Metabolites()[(*mSubstrates)[i].mMetaboliteName];
    
    for (i = 0; i < mProducts->size(); i++)
        (*mProducts)[i].mpMetabolite = 
            &(*compartments)[(*mProducts)[i].mCompartmentName].
            Metabolites()[(*mProducts)[i].mMetaboliteName];
    
    for (i = 0; i < mModifiers->size(); i++)
        (*mModifiers)[i].mpMetabolite = 
            &(*compartments)[(*mModifiers)[i].mCompartmentName].
            Metabolites()[(*mModifiers)[i].mMetaboliteName];
    
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
        if (Fail = configbuffer.GetVariable("Identifier", "string",
                                            &(*mSubstrates)[i].mIdentifierName))
            return Fail;
        if (Fail = configbuffer.GetVariable("Compartment", "string",
                                            &(*mSubstrates)[i].mCompartmentName))
            return Fail;
        if (Fail = configbuffer.GetVariable("Metabolite", "string",
                                            &(*mSubstrates)[i].mMetaboliteName))
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
        if (Fail = configbuffer.GetVariable("Compartment", "string",
                                            &(*mProducts)[i].mCompartmentName))
            return Fail;
        if (Fail = configbuffer.GetVariable("Metabolite", "string",
                                            &(*mProducts)[i].mMetaboliteName))
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
        if (Fail = configbuffer.GetVariable("Compartment", "string",
                                            &(*mModifiers)[i].mCompartmentName))
            return Fail;
        if (Fail = configbuffer.GetVariable("Metabolite", "string",
                                            &(*mModifiers)[i].mMetaboliteName))
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
    string name;
    
    C_INT32 Fail = 0;
    C_INT32 Size;
    C_INT32 i;
    C_INT32 index;

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

    for (i = 0; i < mSubstrates->size(); i++)
    {
        name = StringPrint("Subs%d", i);
        configbuffer.GetVariable(name, "C_INT32", &index);

        if (mFunction->GetName().substr(0,11) == "Mass action")
            (*mSubstrates)[i].mIdentifierName = StringPrint("substrate_%d", i);
        else if (mFunction->CallParameters()[0]->Identifiers(N_SUBSTRATE).size()
                < i + 1)
            (*mSubstrates)[i].mIdentifierName = "";
        else
            (*mSubstrates)[i].mIdentifierName = mFunction->CallParameters()[0]->
                Identifiers(N_SUBSTRATE)[i]->GetName();
        
        (*mSubstrates)[i].mMetaboliteName = 
            Copasi.OldMetabolites[index].GetName();
    }
    
    for (i = 0; i < mProducts->size(); i++)
    {
        name = StringPrint("Prod%d", i);
        configbuffer.GetVariable(name, "C_INT32", &index);
        
        if (mFunction->GetName().substr(0,11) == "Mass action")
            (*mProducts)[i].mIdentifierName = StringPrint("product_%d", i);
        else if (mFunction->CallParameters()[0]->Identifiers(N_PRODUCT).size()
                < i + 1)
            (*mProducts)[i].mIdentifierName = "";
        else
            (*mProducts)[i].mIdentifierName = mFunction->CallParameters()[0]->
                Identifiers(N_PRODUCT)[i]->GetName();
        
        (*mProducts)[i].mMetaboliteName = 
            Copasi.OldMetabolites[index].GetName();
    }
    
    for (i = 0; i < mModifiers->size(); i++)
    {
        name = StringPrint("Modf%d", i);
        configbuffer.GetVariable(name, "C_INT32", &index);
        
        if (mFunction->CallParameters()[0]->Identifiers(N_MODIFIER).size()
                < i + 1)
            (*mModifiers)[i].mIdentifierName = "";
        else
            (*mModifiers)[i].mIdentifierName = mFunction->CallParameters()[0]->
                Identifiers(N_MODIFIER)[i]->GetName();

        (*mModifiers)[i].mMetaboliteName = 
            Copasi.OldMetabolites[index].GetName();
    }
    
    for (i = 0; i < mParameters->size(); i++)
    {
        name = StringPrint("Param%d", i);
        configbuffer.GetVariable(name, "C_FLOAT64", 
                                 &(*mParameters)[i].mValue);
        if (mFunction->GetName().substr(0,11) == "Mass action")
        {
            if (i)
                (*mParameters)[i].mIdentifierName = "kp";
            else
                (*mParameters)[i].mIdentifierName = "ks";
        }
        else if (mFunction->CallParameters()[0]->Identifiers(N_KCONSTANT).size()
                < i + 1)
            (*mParameters)[i].mIdentifierName = "";
        else
            (*mParameters)[i].mIdentifierName = mFunction->CallParameters()[0]->
            Identifiers(N_KCONSTANT)[i]->GetName();
    }
    
        
    return Fail;
}

CStep::CId2Metab::CId2Metab() {}

CStep::CId2Metab::~CId2Metab() {}

CStep::CId2Param::CId2Param() {}

CStep::CId2Param::~CId2Param() {}

vector < CStep::ELEMENT > CStep::GetChemStructure() const
{
    vector < ELEMENT > Structure;
    ELEMENT Element;
    
    string Left;
    string Right;
    
    string::size_type equal = 0;
    string::size_type pos = 0;
    
    equal = mChemEq.find("=");
    if (equal == string::npos) 
    {
        equal = mChemEq.find("->");
        Right = mChemEq.substr(equal+2);
    }
    else
        Right = mChemEq.substr(equal+1);
    Left = mChemEq.substr(0,equal);

    while (pos != string::npos)
    {
        Element = ExtractElement(Left, pos);
        Element.mValue *= -1.0; 
        AddElement(Element, Structure);
    }
    
    pos = 0;
    while (pos != string::npos)
    {
        Element = ExtractElement(Right, pos);
        AddElement(Element, Structure);
    }
    
    return Structure;
}

CStep::ELEMENT CStep::ExtractElement(const string & input, 
                              string::size_type & pos) const
{
    ELEMENT Element;
    string Value;
    
    string::size_type Start = input.find_first_not_of(" ", pos);
    string::size_type End = input.find("+", Start);
    string::size_type Multiplier = input.find("*", Start);
    string::size_type NameStart;
    string::size_type NameEnd;
    
    if (Multiplier == string::npos || Multiplier > End)
    {
        NameStart = Start;
        Element.mValue = 1.0;
    }
    else
    {
        NameStart = input.find_first_not_of(" ",Multiplier+1);
        Value = input.substr(Start, Multiplier - Start);
        Element.mValue = atof(Value.c_str());
    }
    
    NameEnd = input.find_first_of(" +", NameStart);
    Element.mName = input.substr(NameStart, NameEnd - NameStart);

    pos = (End == string::npos) ? End: End+1;
    return Element;
}

void CStep::AddElement(const ELEMENT & element,
                       vector < ELEMENT > & structure) const
{
    C_INT32 i;

    for (i=0; i < structure.size(); i++)
        if (element.mName == structure[i].mName) break;
    
    if (i >= structure.size()) 
        structure.push_back(element);
    else
        structure[i].mValue += element.mValue;
}

void CStep::Old2New(const vector < CMetab* > & metabolites)
{
    C_INT32 i, j;
    
    for (i = 0; i < mSubstrates->size(); i++)
    {
        for (j = 0; j < metabolites.size(); j++)
            if (metabolites[j]->GetName() ==
                (*mSubstrates)[i].mMetaboliteName) break;
        (*mSubstrates)[i].mCompartmentName =
            metabolites[j]->GetCompartment()->GetName();
    }
    
    for (i = 0; i < mProducts->size(); i++)
    {
        for (j = 0; j < metabolites.size(); j++)
            if (metabolites[j]->GetName() ==
                (*mProducts)[i].mMetaboliteName) break;
        (*mProducts)[i].mCompartmentName =
            metabolites[j]->GetCompartment()->GetName();
    }
    
    for (i = 0; i < mModifiers->size(); i++)
    {
        for (j = 0; j < metabolites.size(); j++)
            if (metabolites[j]->GetName() ==
                (*mModifiers)[i].mMetaboliteName) break;
        (*mModifiers)[i].mCompartmentName =
            metabolites[j]->GetCompartment()->GetName();
    }
}

C_FLOAT64 CStep::Calculate() 
{
    return mFunction->CalcValue(*mCallParameters);
}


