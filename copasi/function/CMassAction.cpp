/**
 * CMassAction
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#include "copasi.h"
#include "CMassAction.h"


#define COPASI_TRACE_CONSTRUCTION
CMassAction::CMassAction() : CFunction() 
{
  CONSTRUCTOR_TRACE;
  setType(CFunction::MassAction);
}

CMassAction::CMassAction(const CMassAction & src) : CFunction(src) 
{CONSTRUCTOR_TRACE;}

CMassAction::CMassAction(const TriLogic & reversible) : CFunction()
{
  CONSTRUCTOR_TRACE;
  if (reversible != TriFalse && reversible != TriTrue)
    CCopasiMessage(CCopasiMessage::ERROR, MCMassAction + 1);

  setType(CFunction::MassAction);
  setReversible(reversible);

  getParameters().add("k1", 
                      CFunctionParameter::FLOAT64, 
                      "PARAMETER");
  getParameters().add("substrate", 
                      CFunctionParameter::VFLOAT64, 
                      "SUBSTRATE");

  if (isReversible() == TriTrue)
    {
      setName("Mass action (reversible)");
      setDescription("k1 * PRODUCT <substrate_i> "
                     "- k2 * PRODUCT <product_j>");
      getParameters().add("k2", 
                          CFunctionParameter::FLOAT64, 
                          "PARAMETER");
      getParameters().add("product",
                          CFunctionParameter::VFLOAT64,
                          "PRODUCT");
    }
  else
    {
      setName("Mass action (irreversible)");
      setDescription("k1 * PRODUCT <substrate_i>");
    }
}

CMassAction::~CMassAction(){DESTRUCTOR_TRACE;}

unsigned C_INT32 CMassAction::getParameterPosition(const string & name)
{
  if (isReversible() != TriFalse && isReversible() != TriTrue)
    CCopasiMessage(CCopasiMessage::ERROR, MCMassAction + 1);

  if (name == "k1") return 0;
  if (name.substr(0,strlen("substrate")) == "substrate") return 1;
  if (name == "k2" && 
      isReversible() == TriTrue) return 2;
  if (name.substr(0,strlen("product")) == "product" && 
      isReversible() == TriTrue) return 3;
  
  return (unsigned C_INT32) -1;
}

C_FLOAT64 CMassAction::calcValue(const CCallParameters & callParameters) const
{
  unsigned C_INT32 i, imax;
  C_FLOAT64 **Factor;
  C_FLOAT64 Substrates = 0.0, Products = 0.0;

  imax = ((vector<C_FLOAT64 *> *)callParameters[1])->size();   // NoSubstrates
  if (imax)
    {
      Substrates = *(C_FLOAT64 *) callParameters[0];           // k1
      Factor =
        ((vector<C_FLOAT64*>*)callParameters[1])->begin();     // first substr.

      for (i = 0; i < imax; i++)
        Substrates *= **(Factor++); 
    }
  
  if (isReversible() == TriFalse) return Substrates;
  
  imax = ((vector<C_FLOAT64 *> *)callParameters[3])->size();   // NoProducts
  if (imax)
    {
      Products = *(C_FLOAT64 *) callParameters[2];             // k2
      Factor =
        ((vector<C_FLOAT64*>*)callParameters[3])->begin();     // first product
  
      for (i = 0; i < imax; i++)
        Products *= **(Factor++);
    }
  
  return Substrates - Products;
}
