#include "CMassAction.h"
#include "CNodeK.h"

CMassAction::CMassAction()
{SetType(CBaseFunction::BUILTIN);}

CMassAction::CMassAction(C_INT16 reversible)
{
    SetType(CBaseFunction::BUILTIN);
    SetReversible(reversible);
    
    CBaseCallParameter *Substrates = new CBaseCallParameter;
    Substrates->SetType(CCallParameter::VECTOR_DOUBLE);
    Substrates->SetCount(1,CRange::UNSPECIFIED);
    Substrates->IdentifierTypes().push_back(N_SUBSTRATE);
    Substrates->IdentifierTypes().push_back(N_KCONSTANT);
    CallParameters().push_back(Substrates);

    CBaseIdentifier *ks = new CBaseIdentifier;
    ks->SetName("ks");
    ks->SetType(N_KCONSTANT);
    Substrates->Identifiers().push_back(ks);

    if (reversible)
    {
        SetName("Mass action (reversible)");
        SetDescription("ks * PRODUCT <substrate_i> "
                       "- kp * PRODUCT <product_j>");

        CBaseCallParameter *Products = new CBaseCallParameter;
        Products->SetType(CCallParameter::VECTOR_DOUBLE);
        Products->SetCount(1,CRange::UNSPECIFIED);
        Products->IdentifierTypes().push_back(N_PRODUCT);
        Products->IdentifierTypes().push_back(N_KCONSTANT);
        CallParameters().push_back(Products);

        CBaseIdentifier *kp = new CBaseIdentifier;
        kp->SetName("kp");
        kp->SetType(N_KCONSTANT);
        Products->Identifiers().push_back(kp);
    }
    else
    {
        SetName("Mass action (irreversible)");
        SetDescription("ks * PRODUCT <substrate_i>");
    }
}

CMassAction::~CMassAction() {Delete();}

C_FLOAT64 CMassAction::CalcValue(vector < CCallParameter > & callParameters)
{
    C_FLOAT64 Products = 1.0, Substrates = 1.0;
    C_INT32 i;
    
    for (i = 0; i < callParameters[0].Identifiers().size(); i++)
        Substrates *= *(C_FLOAT64 *) callParameters[0].Identifiers()[i];

    if (IsReversible()) return Substrates;
    
    for (i = 0; i < callParameters[1].Identifiers().size(); i++)
        Products *= *(C_FLOAT64 *) callParameters[1].Identifiers()[i];
    
    return Substrates - Products;
}

pair < C_INT32, C_INT32 > CMassAction::FindIdentifier(const string & name)
{
    pair < C_INT32, C_INT32 > Tuple(-1, -1);
    string::size_type subscript;
    
    if ("ks" == name) 
    {
        Tuple.first = 0;
        Tuple.second = 0;
        return Tuple;
    }
    
    if ("kp" == name && IsReversible()) 
    {
        Tuple.first = 1;
        Tuple.second = 0;
        return Tuple;
    }
    
    subscript = name.find("_");
    string Type  = name.substr(0,subscript);
    string Index = name.substr(subscript+1);
    Tuple.second = atoi(Index.c_str()) + 1;
    
    if (Type == "substrate")
    {
        Tuple.first = 0;
        return Tuple;
    }
    
    if (Type == "product" && IsReversible())
    {
        Tuple.first = 1;
        return Tuple;
    }
    
    Tuple.second = -1;
    return Tuple;
}
                     
