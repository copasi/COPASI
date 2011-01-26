// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CMassAction.cpp,v $
//   $Revision: 1.41.4.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/26 21:10:12 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CMassAction
 *
 * Created for COPASI by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#include "copasi.h"
#include "CMassAction.h"
#include "utilities/utility.h"

// static
const char * CMassAction::Infix[] =
  {"k1*PRODUCT<substrate_i>-k2*PRODUCT<product_j>", "k1*PRODUCT<substrate_i>"};

CMassAction::CMassAction(const std::string & name,
                         const CCopasiContainer * pParent):
    CFunction(name, pParent, CEvaluationTree::MassAction)
{}

CMassAction::CMassAction(const CFunction & src,
                         const CCopasiContainer * pParent):
    CFunction(src, pParent)
{}

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

  if (reversible == TriTrue)
    setInfix(Infix[0]);
  else
    setInfix(Infix[1]);
}

CMassAction::~CMassAction() {DESTRUCTOR_TRACE;}

const C_FLOAT64 & CMassAction::calcValue(const CCallParameters<C_FLOAT64> & callParameters)
{
  CCallParameters<C_FLOAT64>::const_iterator pCallParameters = callParameters.begin();

  CCallParameters<C_FLOAT64>::const_iterator Factor = (pCallParameters + 1)->vector->begin();
  CCallParameters<C_FLOAT64>::const_iterator End = (pCallParameters + 1)->vector->end();

  mValue = 0.0;

  if (Factor != End)
    {
      mValue = *(pCallParameters + 0)->value   // k1
               * *(Factor++)->value;      // first substrate.

      while (Factor != End)
        mValue *= *(Factor++)->value;
    }

  if (isReversible() == TriFalse)
    return mValue;

  C_FLOAT64 Products = 0.0;

  Factor = (pCallParameters + 3)->vector->begin();
  End = (pCallParameters + 3)->vector->end();

  if (Factor != End)
    {
      Products = *(pCallParameters + 2)->value // k2
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

bool CMassAction::setInfix(const std::string & infix)
{
  if (infix == "k1*PRODUCT<substrate_i>-k2*PRODUCT<product_j>")
    setReversible(TriTrue);
  else if (infix == "k1*PRODUCT<substrate_i>")
    setReversible(TriFalse);
  else
    return false;

  CFunction::setInfix(infix);
  getVariables().cleanup();

  getVariables().add("k1",
                     CFunctionParameter::FLOAT64,
                     CFunctionParameter::PARAMETER);
  getVariables().add("substrate",
                     CFunctionParameter::VFLOAT64,
                     CFunctionParameter::SUBSTRATE);

  if (isReversible() == TriTrue)
    {
      getVariables().add("k2",
                         CFunctionParameter::FLOAT64,
                         CFunctionParameter::PARAMETER);
      getVariables().add("product",
                         CFunctionParameter::VFLOAT64,
                         CFunctionParameter::PRODUCT);
    }

  return true;
}

bool CMassAction::compile()
{
  mUsable = true;
  return true;
}

#include "utilities/copasimathml.h"

void CMassAction::writeMathML(std::ostream & out,
                              const std::vector<std::vector<std::string> > & env,
                              bool /* expand */,
                              bool /* fullExpand */,
                              size_t l) const
{
  bool rev = (isReversible() == TriTrue);

  if (rev)
    out << SPC(l) << "<mfenced>" << std::endl;

  out << SPC(l) << "<mrow>" << std::endl;

  out << SPC(l + 1) << env[0][0] << std::endl;

  size_t i, imax = env[1].size();

  for (i = 0; i < imax; ++i)
    {
      out << SPC(l + 1) << "<mo>&CenterDot;</mo>" << std::endl;
      out << SPC(l + 1) << env[1][i] << std::endl;
    }

  if (rev)
    {
      out << SPC(l + 1) << "<mo>-</mo>" << std::endl;
      out << SPC(l + 1) << env[2][0] << std::endl;

      size_t i, imax = env[3].size();

      for (i = 0; i < imax; ++i)
        {
          out << SPC(l + 1) << "<mo>&CenterDot;</mo>" << std::endl;
          out << SPC(l + 1) << env[3][i] << std::endl;
        }
    }

  out << SPC(l) << "</mrow>" << std::endl;

  if (rev)
    out << SPC(l) << "</mfenced>" << std::endl;
}
