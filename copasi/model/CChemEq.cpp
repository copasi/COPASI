/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEq.cpp,v $
   $Revision: 1.37 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/03 20:47:19 $
   End CVS Header */

// CChemEqElement
//
// A class describing an element of a chemical equation
// (C) Stefan Hoops 2001
//

#define  COPASI_TRACE_CONSTRUCTION

#include <math.h>
#include "copasi.h"
#include "CChemEq.h"
#include "utilities/readwrite.h"
#include "utilities/CCopasiVector.h"
#include "CMetabNameInterface.h"

CChemEq::CChemEq(const std::string & name,
                 const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Chemical Equation"),
    mReversible(false),
    mSubstrates("Substrates", this),
    mProducts("Products", this),
    mModifiers("Modifiers", this),
    mBalances("Balances", this)
{CONSTRUCTOR_TRACE;}

CChemEq::CChemEq(const CChemEq & src,
                 const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mReversible(src.mReversible),
    mSubstrates(src.mSubstrates, this),
    mProducts(src.mProducts, this),
    mModifiers(src.mModifiers, this),
    mBalances(src.mBalances, this)
{CONSTRUCTOR_TRACE;}

CChemEq::~CChemEq(){cleanup(); DESTRUCTOR_TRACE;}

void CChemEq::cleanup()
{
  mSubstrates.cleanup();
  mProducts.cleanup();
  mModifiers.cleanup();
  mBalances.cleanup();
}

void CChemEq::compile(const CCopasiVectorN < CCompartment > & compartments)
{
  //  compileChemEqElements(mSubstrates, compartments);
  //  compileChemEqElements(mProducts, compartments);
  //  compileChemEqElements(mModifiers, compartments);
  //  compileChemEqElements(mBalances, compartments);
}

const CCopasiVector < CChemEqElement > & CChemEq::getSubstrates() const
  {return mSubstrates;}

const CCopasiVector < CChemEqElement > & CChemEq::getProducts() const
  {return mProducts;}

const CCopasiVector < CChemEqElement > & CChemEq::getModifiers() const
  {return mModifiers;}

const CCopasiVector < CChemEqElement > & CChemEq::getBalances() const
  {return mBalances;}

bool CChemEq::addMetabolite(const std::string & key, const C_FLOAT64 mult, const MetaboliteRole role)
{
  CChemEqElement element;
  element.setMetabolite(key);
  element.setMultiplicity(mult);

  switch (role)
    {
    case CChemEq::SUBSTRATE:
      addElement(mSubstrates, element);
      addElement(mBalances, element, CChemEq::SUBSTRATE);
      break;
    case CChemEq::PRODUCT:
      addElement(mProducts, element);
      addElement(mBalances, element);
      break;
    case CChemEq::MODIFIER:
      addElement(mModifiers, element);
      break;
    default:
      fatalError();
      break;
    }

  return true;
}

unsigned C_INT32 CChemEq::getCompartmentNumber() const
  {
    unsigned C_INT32 i, imax = mBalances.size();
    unsigned C_INT32 j, jmax;
    unsigned C_INT32 Number;
    std::vector<const CCompartment *> Compartments;

    for (i = 0, Number = 0; i < imax; i++)
      {
        for (j = 0, jmax = Compartments.size(); j < jmax; j++)
          if (Compartments[j] == mBalances[i]->getMetabolite().getCompartment())
            break;

        if (j == jmax)
          {
            Number ++;
            Compartments.push_back(mBalances[i]->getMetabolite().getCompartment());
          }
      }

    return Number;
  }

void CChemEq::addElement(CCopasiVector < CChemEqElement > & structure,
                         const CChemEqElement & element,
                         CChemEq::MetaboliteRole role)
{
  unsigned C_INT32 i;

  std::string key = element.getMetaboliteKey();

  if (key == "")
    return; // don´t add empty element

  for (i = 0; i < structure.size(); i++)
    if (key == structure[i]->getMetaboliteKey())
      break;

  if (i >= structure.size())
    {
      CChemEqElement * Element = new CChemEqElement(element);

      if (role == CChemEq::SUBSTRATE)
        Element->setMultiplicity(- Element->getMultiplicity());

      structure.add(Element);
    }
  else if (role == CChemEq::SUBSTRATE)
    structure[i]->addToMultiplicity(- element.getMultiplicity());
  else
    structure[i]->addToMultiplicity(element.getMultiplicity());
}

/*void CChemEq::compileChemEqElements(CCopasiVector < CChemEqElement > & elements,
                                    const CCopasiVectorN < CCompartment > & compartments)
{
  unsigned C_INT32 i, imax = elements.size();
 
  for (i = 0; i < imax; i++)
    elements[i]->compile(compartments);
}*/

/*bool CChemEq::initialized() const
  {
    return !mChemicalEquation.empty();
  }*/

const CCompartment* CChemEq::CheckAndGetFunctionCompartment() const
  {
    // check initialized() and compiled

    const CCompartment* comp = NULL;
    unsigned C_INT32 i, imax;

    if (mSubstrates.size() > 0)
      {
        comp = mSubstrates[0]->getMetabolite().getCompartment();
        imax = mSubstrates.size();
        for (i = 1; i < imax; i++)
          if (comp != mSubstrates[i]->getMetabolite().getCompartment())
          {CCopasiMessage(CCopasiMessage::ERROR, MCChemEq + 2);} // substs in different compartments
        return comp; // all substrates are in the same compartment
      }
    else if (mProducts.size() > 0)
      {
        comp = mProducts[0]->getMetabolite().getCompartment();
        imax = mProducts.size();
        for (i = 1; i < imax; i++)
          if (comp != mProducts[i]->getMetabolite().getCompartment())
          {CCopasiMessage(CCopasiMessage::ERROR, MCChemEq + 3);}  // products in different compartments
        return comp; // all products are in the same compartment
      }
    else
      {
        CCopasiMessage(CCopasiMessage::ERROR, MCChemEq + 1); // error: no subs. and no product
        return NULL;
      }
  }

#ifdef xxxx
void CChemEq::reverse()
{
  CCopasiVector<CChemEqElement> dummy;
  dummy = mSubstrates;
  mSubstrates = mProducts;
  mProducts = dummy;
}
#endif

C_INT32 CChemEq::getMolecularity(const MetaboliteRole role) const
  {
    const CCopasiVector<CChemEqElement> * tmpVector;

    switch (role)
      {
      case CChemEq::SUBSTRATE:
        tmpVector = &mSubstrates;
        break;
      case CChemEq::PRODUCT:
        tmpVector = &mProducts;
        break;
      case CChemEq::MODIFIER:
        tmpVector = &mModifiers;
        break;
      default:
        fatalError();
        break;
      }

    C_INT32 ccc, i, imax = tmpVector->size();
    ccc = 0;
    for (i = 0; i < imax; ++i)
      ccc += (C_INT32)floor((*tmpVector)[i]->getMultiplicity());

    return ccc;
  }

std::ostream & operator<<(std::ostream &os, const CChemEq & d)
{
  os << "CChemEq:" << std::endl;
  //os << "   mChemicalEquation:          " << d.getChemicalEquation() << std::endl;
  //os << "   mChemicalEquationConverted: " << d.getChemicalEquationConverted() << std::endl;

  os << "   mSubstrates:" << std::endl;
  os << d.mSubstrates;
  os << "   mProducts:" << std::endl;
  os << d.mProducts;
  os << "   mBalances:" << std::endl;
  os << d.mBalances;

  os << "----CChemEq" << std::endl;
  return os;
}
