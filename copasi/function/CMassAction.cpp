#include "CMassAction.h"
#include "CNodeK.h"

CMassAction::CMassAction()
{setType(CBaseFunction::BUILTIN);}

CMassAction::CMassAction(C_INT16 reversible)
{
  setType(CBaseFunction::BUILTIN);
  setReversible(reversible);
    
  CBaseCallParameter *Substrates = new CBaseCallParameter;
  Substrates->setType(CCallParameter::VECTOR_DOUBLE);
  Substrates->setCount(1,CRange::UNSPECIFIED);
  Substrates->identifierTypes().push_back(N_SUBSTRATE);
  Substrates->identifierTypes().push_back(N_KCONSTANT);
  callParameters().push_back(Substrates);

  CBaseIdentifier *ks = new CBaseIdentifier;
  ks->setName("ks");
  ks->setType(N_KCONSTANT);
  Substrates->identifiers().push_back(ks);

  if (reversible)
    {
      setName("Mass action (reversible)");
      setDescription("ks * PRODUCT <substrate_i> "
		     "- kp * PRODUCT <product_j>");

      CBaseCallParameter *Products = new CBaseCallParameter;
      Products->setType(CCallParameter::VECTOR_DOUBLE);
      Products->setCount(1,CRange::UNSPECIFIED);
      Products->identifierTypes().push_back(N_PRODUCT);
      Products->identifierTypes().push_back(N_KCONSTANT);
      callParameters().push_back(Products);

      CBaseIdentifier *kp = new CBaseIdentifier;
      kp->setName("kp");
      kp->setType(N_KCONSTANT);
      Products->identifiers().push_back(kp);
    }
  else
    {
      setName("Mass action (irreversible)");
      setDescription("ks * PRODUCT <substrate_i>");
    }
}

CMassAction::~CMassAction() {cleanup();}

C_FLOAT64 
CMassAction::calcValue(const vector < CCallParameter > & callParameters) const
{
  C_FLOAT64 Products = 1.0, Substrates = 1.0;
  unsigned C_INT32 i;
    
  for (i = 0; i < callParameters[0].identifiers().size(); i++)
    Substrates *= *(C_FLOAT64 *) callParameters[0].identifiers()[i];

  if (!isReversible()) return Substrates;
    
  for (i = 0; i < callParameters[1].identifiers().size(); i++)
    Products *= *(C_FLOAT64 *) callParameters[1].identifiers()[i];
    
  return Substrates - Products;
}

pair < C_INT32, C_INT32 > CMassAction::findIdentifier(const string & name) const
{
  pair < C_INT32, C_INT32 > Tuple(-1, -1);
  string::size_type subscript;
    
  if ("ks" == name) 
    {
      Tuple.first = 0;
      Tuple.second = 0;
      return Tuple;
    }
    
  if ("kp" == name && isReversible()) 
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
    
  if (Type == "product" && isReversible())
    {
      Tuple.first = 1;
      return Tuple;
    }
    
  Tuple.second = -1;
  return Tuple;
}
                     
