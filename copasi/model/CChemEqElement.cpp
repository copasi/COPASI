/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEqElement.cpp,v $
   $Revision: 1.24 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:24:50 $
   End CVS Header */

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
#include "report/CKeyFactory.h"
#include "CMetabNameInterface.h"

CChemEqElement::CChemEqElement(const std::string & name,
                               const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Chemical Equation Element"),
    mMetaboliteKey(),
    mMultiplicity(0)
    //mpMetabolite(NULL)
{CONSTRUCTOR_TRACE;}

CChemEqElement::CChemEqElement(const CChemEqElement & src,
                               const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mMetaboliteKey(src.mMetaboliteKey),
    mMultiplicity(src.mMultiplicity)
    //mpMetabolite(src.mpMetabolite)
{CONSTRUCTOR_TRACE;}

CChemEqElement::~CChemEqElement() {DESTRUCTOR_TRACE;}

void CChemEqElement::cleanup() {}

//void CChemEqElement::setMetabolite(CMetab * pMetabolite)
//{
//  mpMetabolite = pMetabolite;
//  mMetaboliteName = mpMetabolite->getName();
//}

void CChemEqElement::setMetabolite(const std::string & key)
{mMetaboliteKey = key;}

const std::string & CChemEqElement::getMetaboliteKey() const
  {return mMetaboliteKey;}

const CMetab & CChemEqElement::getMetabolite() const
  {return *(CMetab*)(CCopasiContainer*)CKeyFactory::get(mMetaboliteKey);}

void CChemEqElement::setMultiplicity(const C_FLOAT64 multiplicity)
{mMultiplicity = multiplicity;}

void CChemEqElement::addToMultiplicity(const C_FLOAT64 multiplicity)
{mMultiplicity += multiplicity;}

C_FLOAT64 CChemEqElement::getMultiplicity() const
  {
    return mMultiplicity;
  }

void CChemEqElement::compile(const CCopasiVectorN < CCompartment > & compartments)
{/*
        unsigned C_INT32 i, imax = compartments.size();
       
        for (i = 0; i < imax; i++)
          if (compartments[i]->getMetabolites().getIndex(mMetaboliteName) != C_INVALID_INDEX)
            break;
       
        if (i < imax)
          mpMetabolite = compartments[i]->getMetabolites()[mMetaboliteName];
        else if (mpMetabolite)
          mMetaboliteName = mpMetabolite->getName();
        else
          mpMetabolite = NULL;*/
}
