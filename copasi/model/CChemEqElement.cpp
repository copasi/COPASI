// CChemEqElement
// 
// A class describing an element of a chemical equation
// (C) Stefan Hoops 2001
//


#include "copasi.h"
#include "CChemEqElement.h"
#include "utilities/utilities.h"

CChemEqElement::CChemEqElement() {mpMetabolite = NULL;}

CChemEqElement::CChemEqElement(const CChemEqElement & src)
{
  mMetaboliteName = src.mMetaboliteName;
  mCompartmentName = src.mCompartmentName;
  mMultiplicity = src.mMultiplicity;
  mpMetabolite = src.mpMetabolite;
}

CChemEqElement::~CChemEqElement() {;}

void CChemEqElement::setMultiplicity(const C_FLOAT64 multiplicity)
{mMultiplicity = multiplicity;}

C_FLOAT64 CChemEqElement::getMultiplicity() const
{return mMultiplicity;}

void CChemEqElement::setMetabolite(CMetab & metabolite)
{mpMetabolite = &metabolite;}

CMetab & CChemEqElement::getMetabolite() 
{
  if (!mpMetabolite) fatalError();
  return *mpMetabolite;
}

void CChemEqElement::setMetaboliteName(const string & metaboliteName) 
{mMetaboliteName = metaboliteName;}

const string & CChemEqElement::getMetaboliteName() const 
{return mMetaboliteName;}

void CChemEqElement::setCompartmentName(const string & compartmentName) 
{mCompartmentName = compartmentName;}

const string & CChemEqElement::getCompartmentName() const 
{return mCompartmentName;}

void CChemEqElement::addToMultiplicity(const C_FLOAT64 multiplicity)
{mMultiplicity += multiplicity;}

void CChemEqElement::compile(vector < CMetab * > & metabolites)
{
  unsigned C_INT32 i, imax = metabolites.size();
  
  mpMetabolite = NULL;
  
  for (i=0; i<imax; i++)
    if (mMetaboliteName == metabolites[i]->getName())
      {
	mpMetabolite = metabolites[i];
	break;
      }

  if (i >= imax) fatalError();
}

string CChemEqElement::writeElement() const
{
  if (mMultiplicity == 1.0) 
    return mMetaboliteName;
  else
    return StringPrint("%.0lf * %s", mMultiplicity, mMetaboliteName.c_str());
}

