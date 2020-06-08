// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/copasi.h"
#include "CMassAction.h"
#include "copasi/utilities/utility.h"

// static
const char * CMassAction::Infix[] =
{"k1*PRODUCT<substrate_i>-k2*PRODUCT<product_j>", "k1*PRODUCT<substrate_i>"};

CMassAction::CMassAction(const std::string & name,
                         const CDataContainer * pParent):
  CFunction(name, pParent, CEvaluationTree::MassAction)
{}

CMassAction::CMassAction(const CFunction & src,
                         const CDataContainer * pParent):
  CFunction(src, pParent)
{}

CMassAction::CMassAction(const TriLogic & reversible,
                         const CDataContainer * pParent):
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

CIssue CMassAction::setInfix(const std::string & infix)
{
  mValidity.clear();

  if (infix == "k1*PRODUCT<substrate_i>-k2*PRODUCT<product_j>")
    setReversible(TriTrue);
  else if (infix == "k1*PRODUCT<substrate_i>")
    setReversible(TriFalse);
  else
    {
      mValidity.add(CIssue(CIssue::eSeverity::Error, CIssue::eKind::ExpressionInvalid));
      return mValidity.getFirstWorstIssue();
    }

  CFunction::setInfix(infix);
  getVariables().cleanup();

  getVariables().add("k1",
                     CFunctionParameter::DataType::FLOAT64,
                     CFunctionParameter::Role::PARAMETER);
  getVariables().add("substrate",
                     CFunctionParameter::DataType::VFLOAT64,
                     CFunctionParameter::Role::SUBSTRATE);

  if (isReversible() == TriTrue)
    {
      getVariables().add("k2",
                         CFunctionParameter::DataType::FLOAT64,
                         CFunctionParameter::Role::PARAMETER);
      getVariables().add("product",
                         CFunctionParameter::DataType::VFLOAT64,
                         CFunctionParameter::Role::PRODUCT);
    }

  return mValidity.getFirstWorstIssue();
}

CIssue CMassAction::compile()
{
  return mValidity.getFirstWorstIssue();
}

#include "copasi/utilities/copasimathml.h"

// virtual
std::string CMassAction::writeMathML(const std::vector< std::vector< std::string > > & variables,
                                     bool /* expand */, bool /* fullExpand */) const
{
  std::ostringstream out;

  bool rev = (isReversible() == TriTrue);

  if (rev)
    out << "<mfenced>" << std::endl;

  out << "<mrow>" << std::endl;

  out << variables[0][0] << std::endl;

  size_t i, imax = variables[1].size();

  for (i = 0; i < imax; ++i)
    {
      out << "<mo>&CenterDot;</mo>" << std::endl;
      out << variables[1][i] << std::endl;
    }

  if (rev)
    {
      out << "<mo>-</mo>" << std::endl;
      out << variables[2][0] << std::endl;

      size_t i, imax = variables[3].size();

      for (i = 0; i < imax; ++i)
        {
          out << "<mo>&CenterDot;</mo>" << std::endl;
          out << variables[3][i] << std::endl;
        }
    }

  out << "</mrow>" << std::endl;

  if (rev)
    out << "</mfenced>" << std::endl;

  return out.str();
}
