// CChemEqElement
//
// A class describing an element of a chemical equation
// (C) Stefan Hoops 2001
//

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "CChemEq.h"
#include "utilities/readwrite.h"
#include "utilities/CCopasiVector.h"

CChemEq::CChemEq(const std::string & name,
                 const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Chemical Equation"),
    mChemicalEquation(),
    mChemicalEquationConverted(),
    mSubstrates("Substrates", this),
    mProducts("Products", this),
    mBalances("Balances", this)
{CONSTRUCTOR_TRACE;}

CChemEq::CChemEq(const CChemEq & src,
                 const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mChemicalEquation(src.mChemicalEquation),
    mChemicalEquationConverted(src.mChemicalEquationConverted),
    mSubstrates(src.mSubstrates, this),
    mProducts(src.mProducts, this),
    mBalances(src.mBalances, this)
{CONSTRUCTOR_TRACE;}

CChemEq::~CChemEq(){cleanup(); DESTRUCTOR_TRACE;}

void CChemEq::cleanup()
{
  mSubstrates.cleanup();
  mProducts.cleanup();
  mBalances.cleanup();
}

void CChemEq::compile(const CCopasiVectorN < CCompartment > & compartments)
{
  compileChemEqElements(mSubstrates, compartments);
  compileChemEqElements(mProducts, compartments);
  compileChemEqElements(mBalances, compartments);
}

bool CChemEq::setChemicalEquation(const std::string & chemicalEquation)
{
  std::string Substrates, Products;
  bool reversible;

  cleanup();
  mChemicalEquation = chemicalEquation;

  reversible = splitChemEq(Substrates, Products);

  setChemEqElements(mSubstrates, Substrates);

  setChemEqElements(mProducts, Products);

  setChemEqElements(mBalances, Substrates, CChemEq::SUBSTRATE);
  setChemEqElements(mBalances, Products);

  writeChemicalEquation();
  writeChemicalEquationConverted();
  return reversible;
}

const std::string & CChemEq::getChemicalEquation() const
  {
    return mChemicalEquation;
  }

const std::string & CChemEq::getChemicalEquationConverted() const
  {
    return mChemicalEquationConverted;
  }

const CCopasiVector < CChemEqElement > & CChemEq::getSubstrates() const
  {
    return mSubstrates;
  }

const CCopasiVector < CChemEqElement > & CChemEq::getProducts() const
  {
    return mProducts;
  }

const CCopasiVector < CChemEqElement > & CChemEq::getBalances() const
  {
    return mBalances;
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
                                CChemEq::MetaboliteRole role)
{
  std::string::size_type pos = 0;

  while (pos != std::string::npos)
    addElement(elements, extractElement(reaction, pos), role);
}

#ifdef XXXX
void CChemEq::cleanupChemEqElements(std::vector < CChemEqElement * > & elements)
{
  for (unsigned C_INT32 i = 0; i < elements.size(); i++)
    free(elements[i]);

  elements.clear();
}

#endif // XXXX

bool CChemEq::splitChemEq(std::string & left, std::string & right) const
  {
    std::string::size_type equal = std::string::npos;
    bool reversibility;
    std::string Separator[] = {"->", "=", ""};
    unsigned C_INT32 i = 0;

    while (*Separator != "" && equal == std::string::npos)
      equal = mChemicalEquation.find(Separator[i++]);

    if (equal == std::string::npos)
      fatalError();

    if (mChemicalEquation.substr(equal, 1) == "=")
      reversibility = true;
    else
      reversibility = false;
    right = mChemicalEquation.substr(equal + (Separator[--i].length()));

    left = mChemicalEquation.substr(0, equal);

    return reversibility;
  }

void CChemEq::compileChemEqElements(CCopasiVector < CChemEqElement > & elements,
                                    const CCopasiVectorN < CCompartment > & compartments)
{
  unsigned C_INT32 i, imax = elements.size();

  for (i = 0; i < imax; i++)
    elements[i]->compile(compartments);
}

void CChemEq::writeChemicalEquation()
{
  std::string::size_type equal = std::string::npos;
  std::string Separator[] = {"->", "=>", "=", ""};
  unsigned C_INT32 i = 0, j;

  while (Separator[i] != "" && equal == std::string::npos)
    equal = mChemicalEquation.find(Separator[i++]);

  if (equal == std::string::npos)
    fatalError();

  mChemicalEquation.erase();

  for (j = 0; j < mSubstrates.size(); j++)
    {
      if (j)
        mChemicalEquation += " + ";

      mChemicalEquation += mSubstrates[j]->writeElement();
    }

  mChemicalEquation += " " + Separator[--i] + " ";

  for (j = 0; j < mProducts.size(); j++)
    {
      if (j)
        mChemicalEquation += " + ";

      mChemicalEquation += mProducts[j]->writeElement();
    }
}

void CChemEq::writeChemicalEquationConverted()
{
  std::string::size_type equal = std::string::npos;
  std::string Separator[] = {"->", "=>", "=", ""};
  unsigned C_INT32 i = 0, j, k, kmax;

  while (Separator[i] != "" && equal == std::string::npos)
    equal = mChemicalEquation.find(Separator[i++]);

  if (equal == std::string::npos)
    fatalError();

  mChemicalEquationConverted.erase();

  for (j = 0; j < mSubstrates.size(); j++)
    {
      if (j)
        mChemicalEquationConverted += " + ";

      kmax = (unsigned C_INT32) mSubstrates[j]->getMultiplicity();

      for (k = 0; k < kmax; k++)
        {
          if (k)
            mChemicalEquationConverted += " + ";

          mChemicalEquationConverted += mSubstrates[j]->getMetaboliteName();
        }
    }

  mChemicalEquationConverted += " " + Separator[--i] + " ";

  for (j = 0; j < mProducts.size(); j++)
    {
      if (j)
        mChemicalEquationConverted += " + ";

      kmax = (unsigned C_INT32) mProducts[j]->getMultiplicity();

      for (k = 0; k < kmax; k++)
        {
          if (k)
            mChemicalEquationConverted += " + ";

          mChemicalEquationConverted += mProducts[j]->getMetaboliteName();
        }
    }
}

bool CChemEq::initialized() const
  {
    return !mChemicalEquation.empty();
  }

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
