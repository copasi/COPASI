/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CMassAction.cpp,v $
   $Revision: 1.32 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/12/07 10:55:59 $
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
                     CFunctionParameter::PARAMETER);
  getVariables().add("substrate",
                     CFunctionParameter::VFLOAT64,
                     CFunctionParameter::SUBSTRATE);
  //addUsage("SUBSTRATE", 1, CRange::Infinity);

  if (isReversible() == TriTrue)
    {
      // setName("Mass action (reversible)");
      setInfix("k1 * PRODUCT <substrate_i> "
               "- k2 * PRODUCT <product_j>");
      getVariables().add("k2",
                         CFunctionParameter::FLOAT64,
                         CFunctionParameter::PARAMETER);
      getVariables().add("product",
                         CFunctionParameter::VFLOAT64,
                         CFunctionParameter::PRODUCT);
      //addUsage("PRODUCT", 1, CRange::Infinity);
    }
  else
    {
      // setName("Mass action (irreversible)");
      setInfix("k1 * PRODUCT <substrate_i>");
    }
}
CMassAction::~CMassAction(){DESTRUCTOR_TRACE;}

const C_FLOAT64 & CMassAction::calcValue(const CCallParameters<C_FLOAT64> & callParameters)
{
  CCallParameters<C_FLOAT64>::const_iterator Factor;
  CCallParameters<C_FLOAT64>::const_iterator End;

  mValue = 0.0;

  Factor = callParameters[1].vector->begin();
  End = callParameters[1].vector->end();
  if (Factor != End)
    {
      mValue = *callParameters[0].value   // k1
               * *(Factor++)->value;      // first substrate.

      while (Factor != End)
        mValue *= *(Factor++)->value;
    }

  if (isReversible() == TriFalse)
    return mValue;

  C_FLOAT64 Products = 0.0;

  Factor = callParameters[3].vector->begin();
  End = callParameters[3].vector->end();
  if (Factor != End)
    {
      Products = *callParameters[2].value // k2
                 * *(Factor++)->value;    // first product.

      while (Factor != End)
        Products *= *(Factor++)->value;
    }

  return mValue -= Products;
}

bool CMassAction::dependsOn(const C_FLOAT64 * parameter,
                            const CCallParameters<C_FLOAT64> & callParameters) const
  {
    if (parameter == callParameters[0].value) return true;

    CCallParameters<C_FLOAT64>::const_iterator it;
    CCallParameters<C_FLOAT64>::const_iterator end;

    it = callParameters[1].vector->begin();
    end = callParameters[1].vector->end();

    for (; it != end; it++) if (parameter == it->value) return true;

    if (isReversible() != TriTrue) return false;

    if (parameter == callParameters[2].value) return true;

    it = callParameters[3].vector->begin();
    end = callParameters[3].vector->end();

    for (; it != end; it++) if (parameter == it->value) return true;

    return false;
  }

bool CMassAction::compile() {return true;}
