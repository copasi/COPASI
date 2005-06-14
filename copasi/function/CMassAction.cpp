/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CMassAction.cpp,v $
   $Revision: 1.25 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/14 17:43:05 $
   End CVS Header */

/**
 * CMassAction
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#include "copasi.h"
#include "CMassAction.h"
#include "utilities/utility.h"

#define COPASI_TRACE_CONSTRUCTION
CMassAction::CMassAction(const std::string & name,
                         const CCopasiContainer * pParent):
    CFunction(name, pParent)
{
  CONSTRUCTOR_TRACE;
  setType(CFunction::MassAction);
}

CMassAction::CMassAction(const CFunction & src,
                         const CCopasiContainer * pParent):
    CFunction(src, pParent)
{CONSTRUCTOR_TRACE;}

CMassAction::CMassAction(const TriLogic & reversible,
                         const CCopasiContainer * pParent):
    CFunction((reversible == TriTrue) ?
              "Mass action (reversible)" :
              "Mass action (irreversible)",
              pParent,
              CFunction::MassAction)
{
  CONSTRUCTOR_TRACE;
  if (reversible != TriFalse && reversible != TriTrue)
    CCopasiMessage(CCopasiMessage::ERROR, MCMassAction + 1);

  setType(CFunction::MassAction);
  setReversible(reversible);

  getVariables().add("k1",
                     CFunctionParameter::FLOAT64,
                     "PARAMETER");
  getVariables().add("substrate",
                     CFunctionParameter::VFLOAT64,
                     "SUBSTRATE");
  addUsage("SUBSTRATE", 1, CRange::Infinity);

  if (isReversible() == TriTrue)
    {
      // setName("Mass action (reversible)");
      setInfix("k1 * PRODUCT <substrate_i> "
               "- k2 * PRODUCT <product_j>");
      getVariables().add("k2",
                         CFunctionParameter::FLOAT64,
                         "PARAMETER");
      getVariables().add("product",
                         CFunctionParameter::VFLOAT64,
                         "PRODUCT");
      addUsage("PRODUCT", 1, CRange::Infinity);
    }
  else
    {
      // setName("Mass action (irreversible)");
      setInfix("k1 * PRODUCT <substrate_i>");
    }
}
CMassAction::~CMassAction(){DESTRUCTOR_TRACE;}

C_FLOAT64 CMassAction::calcValue(const CCallParameters<C_FLOAT64> & callParameters) const
  {
    unsigned C_INT32 i, imax;
    std::vector<const C_FLOAT64 *>::const_iterator Factor;

    C_FLOAT64 Substrates = 0.0, Products = 0.0;

    imax = callParameters[1].vector->size();   // NoSubstrates
    if (imax)
      {
        Substrates = * callParameters[0].value;           // k1
        Factor = callParameters[1].vector->begin();   // first substr.

        for (i = 0; i < imax; i++)
          Substrates *= **(Factor++);
      }

    if (isReversible() == TriFalse)
      return Substrates;

    imax = callParameters[3].vector->size();   // NoProducts
    if (imax)
      {
        Products = * callParameters[2].value;             // k2
        Factor = callParameters[3].vector->begin();   // first product

        for (i = 0; i < imax; i++)
          Products *= **(Factor++);
      }

    return Substrates - Products;
  }

bool CMassAction::dependsOn(const void * parameter,
                            const CCallParameters<C_FLOAT64> & callParameters) const
  {
    if (parameter == callParameters[0].value) return true;

    std::vector<const C_FLOAT64 *>::const_iterator it;
    std::vector<const C_FLOAT64 *>::const_iterator end;

    it = callParameters[1].vector->begin();
    end = callParameters[1].vector->end();

    for (; it != end; it++) if (parameter == *it) return true;

    if (isReversible() == TriFalse) return false;

    if (parameter == callParameters[2].value) return true;

    it = callParameters[3].vector->begin();
    end = callParameters[3].vector->end();

    for (; it != end; it++) if (parameter == *it) return true;

    return false;
  }

bool CMassAction::compile() {return true;}
