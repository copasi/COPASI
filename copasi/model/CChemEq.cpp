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
  compileChemEqElements(mSubstrates, compartments);
  compileChemEqElements(mProducts, compartments);
  compileChemEqElements(mModifiers, compartments);
  compileChemEqElements(mBalances, compartments);
}

bool CChemEq::setChemicalEquation(const std::string & chemicalEquation)
{
  std::string Substrates, Products, Modifiers;

  cleanup();
  //mChemicalEquation = chemicalEquation;

  mReversible = splitChemEq(chemicalEquation, Substrates, Products, Modifiers);

  setChemEqElements(mSubstrates, Substrates);

  setChemEqElements(mProducts, Products);

  setChemEqElements(mBalances, Substrates, CChemEq::SUBSTRATE);
  setChemEqElements(mBalances, Products);

  // PRODUCTS is default and only menioned because another parameter
  // follows. True tells the method to look for " " as separator
  // (instead of " + ").
  setChemEqElements(mModifiers, Modifiers, CChemEq::PRODUCT, true);

  return mReversible;
}

const std::string CChemEq::getChemicalEquation() const
  {
    std::string ChemicalEquation;
    unsigned C_INT32 j;

    for (j = 0; j < mSubstrates.size(); j++)
      {
        if (j)
          ChemicalEquation += " + ";

        ChemicalEquation += mSubstrates[j]->writeElement();
      }

    if (mReversible)
      ChemicalEquation += " = ";
    else
      ChemicalEquation += " -> ";

    for (j = 0; j < mProducts.size(); j++)
      {
        if (j)
          ChemicalEquation += " + ";

        ChemicalEquation += mProducts[j]->writeElement();
      }

    if (mModifiers.size())
      {
        ChemicalEquation += ";";

        for (j = 0; j < mModifiers.size(); j++)
          {
            ChemicalEquation += " ";
            ChemicalEquation += mModifiers[j]->getMetaboliteName();
          }
      }

    return ChemicalEquation;
  }

const std::string CChemEq::getChemicalEquationConverted() const
  {
    std::string ChemicalEquation;
    unsigned C_INT32 j, k, kmax;

    for (j = 0; j < mSubstrates.size(); j++)
      {
        if (j)
          ChemicalEquation += " + ";

        kmax = (unsigned C_INT32) mSubstrates[j]->getMultiplicity(); // TODO: integer multiplicity?

        for (k = 0; k < kmax; k++)
          {
            if (k)
              ChemicalEquation += " + ";

            ChemicalEquation += mSubstrates[j]->getMetaboliteName();
          }
      }

    if (mReversible)
      ChemicalEquation += " = ";
    else
      ChemicalEquation += " -> ";

    for (j = 0; j < mProducts.size(); j++)
      {
        if (j)
          ChemicalEquation += " + ";

        kmax = (unsigned C_INT32) mProducts[j]->getMultiplicity();

        for (k = 0; k < kmax; k++)
          {
            if (k)
              ChemicalEquation += " + ";

            ChemicalEquation += mProducts[j]->getMetaboliteName();
          }
      }

    if (mModifiers.size())
      {
        ChemicalEquation += ";";

        for (j = 0; j < mModifiers.size(); j++)
          {
            ChemicalEquation += " ";
            ChemicalEquation += mModifiers[j]->getMetaboliteName();
          }
      }

    return ChemicalEquation;
  }

const CCopasiVector < CChemEqElement > & CChemEq::getSubstrates() const
  {return mSubstrates;}

const CCopasiVector < CChemEqElement > & CChemEq::getProducts() const
  {return mProducts;}

const CCopasiVector < CChemEqElement > & CChemEq::getModifiers() const
  {return mModifiers;}

const CCopasiVector < CChemEqElement > & CChemEq::getBalances() const
  {return mBalances;}

void CChemEq::addMetaboliteByName(const std::string & name, const C_FLOAT64 mult, const MetaboliteRole role)
{
  CChemEqElement element;
  element.setMetaboliteName(name);
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
}

void CChemEq::addMetabolite(CMetab & metab, const C_FLOAT64 mult, const MetaboliteRole role)
{
  CChemEqElement element;
  element.setMetabolite(metab);
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
}

const CChemEqElement & CChemEq::findElementByName(const std::string & name,
    const MetaboliteRole role) const
  {
    static CChemEqElement Element;

    unsigned C_INT32 i, imax;

    if ((role == NOROLE) || (role == SUBSTRATE))
      {
        imax = mSubstrates.size();
        for (i = 0; i < imax; ++i)
          if (mSubstrates[i]->getMetaboliteName() == name) return *(mSubstrates[i]);
      }

    if ((role == NOROLE) || (role == PRODUCT))
      {
        imax = mProducts.size();
        for (i = 0; i < imax; ++i)
          if (mProducts[i]->getMetaboliteName() == name) return *(mProducts[i]);
      }

    if ((role == NOROLE) || (role == MODIFIER))
      {
        imax = mModifiers.size();
        for (i = 0; i < imax; ++i)
          if (mModifiers[i]->getMetaboliteName() == name) return *(mModifiers[i]);
      }

    return Element;
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

CChemEqElement CChemEq::extractElement(const std::string & input,
                                       std::string::size_type & pos) const
  {
    CChemEqElement Element;
    std::string Value;

    std::string::size_type Start = input.find_first_not_of(" ", pos);
    std::string::size_type End = input.find(" + ", Start);
    std::string::size_type Multiplier = input.find("*", Start);
    std::string::size_type NameStart;
    std::string::size_type NameEnd;

    if (Multiplier == std::string::npos || Multiplier > End)
      {
        NameStart = Start;
        Element.setMultiplicity(1.0);
      }
    else
      {
        NameStart = input.find_first_not_of(" ", Multiplier + 1);
        Value = input.substr(Start, Multiplier - Start);
        Element.setMultiplicity(atof(Value.c_str()));
      }

    NameEnd = input.find_first_of(" ", NameStart);

    if (NameStart != std::string::npos)
      Element.setMetaboliteName(input.substr(NameStart, NameEnd - NameStart));
    else
      Element.setMetaboliteName("");

    pos = (End == std::string::npos) ? End : End + 3;

    return Element;
  }

CChemEqElement CChemEq::extractModifier(const std::string & input,
                                        std::string::size_type & pos) const
  {
    CChemEqElement Element;
    std::string Value;

    std::string::size_type Start = input.find_first_not_of(" ", pos);
    std::string::size_type End = input.find(" ", Start);

    if (Start != std::string::npos)
      Element.setMetaboliteName(input.substr(Start, End - Start));
    else
      Element.setMetaboliteName("");

    Element.setMultiplicity(0.0);

    pos = (End == std::string::npos) ? End : End + 1;

    return Element;
  }

void CChemEq::addElement(CCopasiVector < CChemEqElement > & structure,
                         const CChemEqElement & element,
                         CChemEq::MetaboliteRole role)
{
  unsigned C_INT32 i;

  std::string Name = element.getMetaboliteName();

  if (Name == "")
    return; // don´t add empty element

  for (i = 0; i < structure.size(); i++)
    if (Name == structure[i]->getMetaboliteName())
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

void CChemEq::setChemEqElements(CCopasiVector < CChemEqElement >
                                & elements,
                                const std::string & reaction,
                                CChemEq::MetaboliteRole role,
                                const bool modif)
{
  std::string::size_type pos = 0;

  while (pos != std::string::npos)
    {
      if (!modif)
        addElement(elements, extractElement(reaction, pos), role);
      else
        addElement(elements, extractModifier(reaction, pos), role);
    }
}

#ifdef XXXX
void CChemEq::cleanupChemEqElements(std::vector < CChemEqElement * > & elements)
{
  for (unsigned C_INT32 i = 0; i < elements.size(); i++)
    free(elements[i]);

  elements.clear();
}

#endif // XXXX

bool CChemEq::splitChemEq(const std::string & input,
                          std::string & left, std::string & right, std::string & mod) const
  {
    std::string::size_type equal = std::string::npos;
    std::string rightTmp;
    bool reversibility;
    std::string Separator[] = {"->", "=", ""};
    unsigned C_INT32 i = 0;

    while (*Separator != "" && equal == std::string::npos)
      equal = input.find(Separator[i++]);

    if (equal == std::string::npos)
      fatalError();

    if (input.substr(equal, 1) == "=")
      reversibility = true;
    else
      reversibility = false;

    left = input.substr(0, equal);

    rightTmp = input.substr(equal + (Separator[--i].length()));

    equal = rightTmp.find(";");
    if (equal == std::string::npos)
    {right = rightTmp; mod = ""; return reversibility;}

    right = rightTmp.substr(0, equal);
    mod = rightTmp.substr(equal + 1);

    return reversibility;
  }

void CChemEq::compileChemEqElements(CCopasiVector < CChemEqElement > & elements,
                                    const CCopasiVectorN < CCompartment > & compartments)
{
  unsigned C_INT32 i, imax = elements.size();

  for (i = 0; i < imax; i++)
    elements[i]->compile(compartments);
}

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

void CChemEq::reverse()
{
  CCopasiVector<CChemEqElement> dummy;
  dummy = mSubstrates;
  mSubstrates = mProducts;
  mProducts = dummy;
}

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
    for (i = 0, ccc = 0; i < imax; ++i)
      ccc += floor((*tmpVector)[i]->getMultiplicity());

    return ccc;
  }
