// CChemEqElement
//
// A class describing an element of a chemical equation
// (C) Stefan Hoops 2001
//

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "utilities/CCopasiVector.h"
#include "utilities/CCopasiException.h"
#include "utilities/utility.h"
#include "CChemEqElement.h"
#include "CCompartment.h"

CChemEqElement::CChemEqElement(const std::string & name,
                               const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Chemical Equation Element"),
    mMetaboliteName(),
    mMultiplicity(0),
    mpMetabolite(NULL)
{CONSTRUCTOR_TRACE;}

CChemEqElement::CChemEqElement(const CChemEqElement & src,
                               const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mMetaboliteName(src.mMetaboliteName),
    mMultiplicity(src.mMultiplicity),
    mpMetabolite(src.mpMetabolite)
{CONSTRUCTOR_TRACE;}

CChemEqElement::~CChemEqElement() {DESTRUCTOR_TRACE;}

void CChemEqElement::cleanup() {}

void CChemEqElement::setMetabolite(CMetab & metabolite)
{
  mpMetabolite = &metabolite;
  mMetaboliteName = mpMetabolite->getName();
}

const CMetab & CChemEqElement::getMetabolite() const
  {
    if (!mpMetabolite)
      fatalError();

    return *mpMetabolite;
  }

void CChemEqElement::setMetaboliteName(const std::string & metaboliteName)
{mMetaboliteName = metaboliteName;}

const std::string & CChemEqElement::getMetaboliteName() const
  {return mMetaboliteName;}

void CChemEqElement::setMultiplicity(const C_FLOAT64 multiplicity)
{mMultiplicity = multiplicity;}

void CChemEqElement::addToMultiplicity(const C_FLOAT64 multiplicity)
{mMultiplicity += multiplicity;}

C_FLOAT64 CChemEqElement::getMultiplicity() const
  {
    return mMultiplicity;
  }

void CChemEqElement::compile(const CCopasiVectorN < CCompartment > & compartments)
{
  unsigned C_INT32 i, imax = compartments.size();

  for (i = 0; i < imax; i++)
    if (compartments[i]->getMetabolites().getIndex(mMetaboliteName) != C_INVALID_INDEX)
      break;

  if (i < imax)
    mpMetabolite = compartments[i]->getMetabolites()[mMetaboliteName];
  else if (mpMetabolite)
    mMetaboliteName = mpMetabolite->getName();
  else
    mpMetabolite = NULL;
}

std::string CChemEqElement::writeElement() const
  {
    if (mMultiplicity == 1.0)
      return mMetaboliteName;
    else
      return StringPrint("%g * %s", mMultiplicity, mMetaboliteName.c_str());
  }
