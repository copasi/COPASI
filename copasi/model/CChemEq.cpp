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

// CChemEqElement
//
// A class describing an element of a chemical equation
// (C) Stefan Hoops 2001
//

#include <cmath>

#include "copasi/copasi.h"
#include "CChemEq.h"
#include "copasi/utilities/CReadConfig.h"
#include "copasi/core/CDataVector.h"
#include "CMetabNameInterface.h"
#include "CCompartment.h"

CChemEq::CChemEq(const std::string & name,
                 const CDataContainer * pParent):
  CDataContainer(name, pParent, "Chemical Equation"),
  mReversible(false),
  mSubstrates("Substrates", this),
  mProducts("Products", this),
  mModifiers("Modifiers", this),
  mBalances("Balances", this)
{CONSTRUCTOR_TRACE;}

CChemEq::CChemEq(const CChemEq & src,
                 const CDataContainer * pParent):
  CDataContainer(src, pParent),
  mReversible(src.mReversible),
  mSubstrates(src.mSubstrates, this),
  mProducts(src.mProducts, this),
  mModifiers(src.mModifiers, this),
  mBalances(src.mBalances, this)
{CONSTRUCTOR_TRACE;}

CChemEq::~CChemEq() {cleanup(); DESTRUCTOR_TRACE;}

void CChemEq::cleanup()
{
  mSubstrates.cleanup();
  mProducts.cleanup();
  mModifiers.cleanup();
  mBalances.cleanup();
}

const CDataVector < CChemEqElement > & CChemEq::getSubstrates() const
{return mSubstrates;}

const CDataVector < CChemEqElement > & CChemEq::getProducts() const
{return mProducts;}

const CDataVector < CChemEqElement > & CChemEq::getModifiers() const
{return mModifiers;}

const CDataVector < CChemEqElement > & CChemEq::getBalances() const
{return mBalances;}

void CChemEq::setReversibility(const bool & reversible)
{
  mReversible = reversible;
}

const bool & CChemEq::getReversibility() const
{return mReversible;}

bool CChemEq::addMetabolite(const std::string & key, const C_FLOAT64 multiplicity, const MetaboliteRole & role)
{
  CChemEqElement element;
  element.setMetabolite(key);
  element.setMultiplicity(multiplicity);

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

size_t CChemEq::getCompartmentNumber() const
{
  return getCompartments().size();
}

std::set< const CCompartment * > CChemEq::getCompartments() const
{
  const CCompartment * pCompartment = NULL;
  std::set< const CCompartment * > Compartments;

  // We go through the substrates, products, and modifiers;
  CDataVector < CChemEqElement >::const_iterator it = mSubstrates.begin();
  CDataVector < CChemEqElement >::const_iterator end = mSubstrates.end();

  for (; it != end; ++it)
    {
      if (it->getMetabolite() != NULL &&
          (pCompartment = it->getMetabolite()->getCompartment()) != NULL)
        {
          Compartments.insert(pCompartment);
        }
    }

  it = mProducts.begin();
  end = mProducts.end();

  for (; it != end; ++it)
    {
      if (it->getMetabolite() != NULL &&
          (pCompartment = it->getMetabolite()->getCompartment()) != NULL)
        {
          Compartments.insert(pCompartment);
        }
    }

  it = mModifiers.begin();
  end = mModifiers.end();

  for (; it != end; ++it)
    {
      if (it->getMetabolite() != NULL &&
          (pCompartment = it->getMetabolite()->getCompartment()) != NULL)
        {
          Compartments.insert(pCompartment);
        }
    }

  return Compartments;
}

const CCompartment * CChemEq::getLargestCompartment() const
{
  size_t indexSubstrates = C_INVALID_INDEX;
  size_t indexProducts = C_INVALID_INDEX;
  size_t i, imax;

  C_FLOAT64 tmp, maxVol = -1.0;

  for (i = 0, imax = mSubstrates.size(); i < imax; i++)
    {
      if (!mSubstrates[i].getMetabolite()) continue;

      tmp = mSubstrates[i].getMetabolite()->getCompartment()->getValue();

      if (tmp > maxVol)
        {
          maxVol = tmp;
          indexSubstrates = i;
        }
    }

  for (i = 0, imax = mProducts.size(); i < imax; i++)
    {
      if (!mProducts[i].getMetabolite()) continue;

      tmp = mProducts[i].getMetabolite()->getCompartment()->getValue();

      if (tmp > maxVol)
        {
          maxVol = tmp;
          indexProducts = i;
        }
    }

  if (indexProducts != C_INVALID_INDEX)
    return mProducts[indexProducts].getMetabolite()->getCompartment();

  if (indexSubstrates != C_INVALID_INDEX)
    return mSubstrates[indexSubstrates].getMetabolite()->getCompartment();

  return NULL;
}

void CChemEq::addElement(CDataVector < CChemEqElement > & structure,
                         const CChemEqElement & element,
                         CChemEq::MetaboliteRole role)
{
  size_t i;

  std::string key = element.getMetaboliteKey();

  if (key == "")
    return; // don�t add empty element

  for (i = 0; i < structure.size(); i++)
    if (key == structure[i].getMetaboliteKey())
      break;

  if (i >= structure.size())
    {
      CChemEqElement * Element = new CChemEqElement(element, NO_PARENT);

      if (role == CChemEq::SUBSTRATE)
        Element->setMultiplicity(- Element->getMultiplicity());

      structure.add(Element, true);
    }
  else if (role == CChemEq::SUBSTRATE)
    structure[i].addToMultiplicity(- element.getMultiplicity());
  else
    structure[i].addToMultiplicity(element.getMultiplicity());
}

size_t CChemEq::getMolecularity(const MetaboliteRole role) const
{
  const CDataVector<CChemEqElement> * tmpVector = NULL;

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

  size_t ccc, i, imax = tmpVector->size();
  ccc = 0;

  for (i = 0; i < imax; ++i)
    ccc += (size_t) floor((*tmpVector)[i].getMultiplicity());

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

/**
 * Sets the stoichiometry of the chemical element that corresponds to the
 * given metabolite and role to the new value.
 * The role has to be either CChemEqElement::SUBSTRATE or
 * CChemEqElement::PRODUCT.
 * If the role is invalid, the multiplicity if negative or if the element for
 * the metabolite and role can not be found in the chemical equation, false is returned and
 * nothing is changed.
 */
bool CChemEq::setMultiplicity(const CMetab* pMetab, C_FLOAT64 newMult, MetaboliteRole role)
{
  bool result = true;

  // check if the multiplicity and the role are valid
  if (pMetab == NULL || newMult <= 0 || !(role == CChemEq::SUBSTRATE || role == CChemEq::PRODUCT))
    {
      result = false;
    }
  else
    {
      // find the corresponding chemical element
      std::string key = pMetab->getKey();
      CDataVector<CChemEqElement>::iterator it, endit;

      if (role == CChemEq::SUBSTRATE)
        {
          it = this->mSubstrates.begin();
          endit = this->mSubstrates.end();
        }
      else
        {
          it = this->mProducts.begin();
          endit = this->mProducts.end();
        }

      while (it != endit)
        {
          if (it->getMetaboliteKey() == key)
            {
              break;
            }

          ++it;
        }

      if (it == endit)
        {
          result = false;
        }
      else
        {
          // set the new multiplicity and update the balances
          C_FLOAT64 diff = newMult - it->getMultiplicity();

          // we only make changes if there actually is a difference
          if (fabs(diff) > 1e-9)
            {
              // we have to add the difference between the new and the old
              // multiplicity to the balances
              it->setMultiplicity(newMult);
              // copy the element
              CChemEqElement tmp(*it, NO_PARENT);
              // set the difference of the multiplicities
              // as the multiplicity of the copy
              tmp.setMultiplicity(diff);
              // update the balances
              this->addElement(this->mBalances, tmp, role);
            }
        }
    }

  return result;
}
