// CChemEqElement
// 
// A class describing an element of a chemical equation
// (C) Stefan Hoops 2001
//

#include "copasi.h"
#include "CChemEq.h"

CChemEq::CChemEq(){};

CChemEq::CChemEq(const CChemEq & src)
{
  mChemicalEquation = src.mChemicalEquation;
  mChemicalEquationConverted = src.mChemicalEquationConverted;
  mSubstrates = src.mSubstrates;
  mProducts = src.mProducts;
  mBalances = src.mBalances;
}

CChemEq::~CChemEq(){cleanup();}

void CChemEq::cleanup()
{
  mSubstrates.cleanup();
  mProducts.cleanup();
  mBalances.cleanup();
}

void CChemEq::compile(CCopasiVectorN < CCompartment > & compartments)
{
  compileChemEqElements(mSubstrates, compartments);
  compileChemEqElements(mProducts, compartments);
  compileChemEqElements(mBalances, compartments);
}

void CChemEq::setChemicalEquation(const string & chemicalEquation)
{
  string Substrates, Products;

  mChemicalEquation = chemicalEquation;

  splitChemEq(Substrates, Products);

  setChemEqElements(mSubstrates, Substrates);

  setChemEqElements(mProducts, Products);

  setChemEqElements(mBalances, Substrates, CChemEq::SUBSTRATE);
  setChemEqElements(mBalances, Products);

  writeChemicalEquation();
  writeChemicalEquationConverted();
}

const string & CChemEq::getChemicalEquation() const
{return mChemicalEquation;}

const string & CChemEq::getChemicalEquationConverted() const
{return mChemicalEquationConverted;}

const CCopasiVector < CChemEqElement > & CChemEq::getSubstrates()
{return mSubstrates;}

const CCopasiVector < CChemEqElement > & CChemEq::getProducts()
{return mProducts;}

const CCopasiVector < CChemEqElement > & CChemEq::getBalances()
{return mBalances;}

CChemEqElement CChemEq::extractElement(const string & input, 
				       string::size_type & pos) const
{
  CChemEqElement Element;
  string Value;
    
  string::size_type Start = input.find_first_not_of(" ", pos);
  string::size_type End = input.find("+", Start);
  string::size_type Multiplier = input.find("*", Start);
  string::size_type NameStart;
  string::size_type NameEnd;
    
  if (Multiplier == string::npos || Multiplier > End)
    {
      NameStart = Start;
      Element.setMultiplicity(1.0);
    }
  else
    {
      NameStart = input.find_first_not_of(" ",Multiplier+1);
      Value = input.substr(Start, Multiplier - Start);
      Element.setMultiplicity(atof(Value.c_str()));
    }
    
  NameEnd = input.find_first_of(" +", NameStart);
  if (NameStart != string::npos)
    Element.setMetaboliteName(input.substr(NameStart, NameEnd - NameStart));

  pos = (End == string::npos) ? End: End+1;
  return Element;
}

void CChemEq::addElement(CCopasiVector < CChemEqElement > & structure,
			 const CChemEqElement & element,
			 CChemEq::MetaboliteRole role)
{
  unsigned C_INT32 i;
 
  string Name = element.getMetaboliteName();
  for (i=0; i < structure.size(); i++)
    if (Name == structure[i]->getMetaboliteName()) break;
    
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
				const string & reaction,
				CChemEq::MetaboliteRole role)
{
  string::size_type pos = 0;

  while (pos != string::npos)
    addElement(elements, extractElement(reaction, pos), role);
}

#ifdef XXXX
void CChemEq::cleanupChemEqElements(vector < CChemEqElement * > & elements)
{
  for (unsigned C_INT32 i=0; i<elements.size(); i++)
    free(elements[i]);
  elements.clear();
}
#endif // XXXX

void CChemEq::splitChemEq(string & left, string & right) const
{
  string::size_type equal = string::npos;
  string Separator[] = {"->", "=>", "=", ""};
  unsigned C_INT32 i=0;
  
  while (*Separator != "" && equal == string::npos)
      equal = mChemicalEquation.find(Separator[i++]);
  if (equal == string::npos) fatalError();
      
  right = mChemicalEquation.substr(equal+(Separator[--i].length()));
  left = mChemicalEquation.substr(0,equal);
  
  return;
}

void 
CChemEq::compileChemEqElements(CCopasiVector < CChemEqElement > & elements,
			       CCopasiVectorN < CCompartment > & compartments)
{
  unsigned C_INT32 i, imax = elements.size();
  
  for (i=0; i<imax; i++)
    elements[i]->compile(compartments);
}

void CChemEq::writeChemicalEquation()
{
  string::size_type equal = string::npos;
  string Separator[] = {"->", "=>", "=", ""};
  unsigned C_INT32 i=0, j;
  
  while (Separator[i] != "" && equal == string::npos)
      equal = mChemicalEquation.find(Separator[i++]);
  if (equal == string::npos) fatalError();
  
  mChemicalEquation.erase();
  
  for (j=0; j<mSubstrates.size(); j++)
    {
      if (j) mChemicalEquation += " + ";
      mChemicalEquation += mSubstrates[j]->writeElement();
    }

  mChemicalEquation += " " + Separator[--i] + " ";

  for (j=0; j<mProducts.size(); j++)
    {
      if (j) mChemicalEquation += " + ";
      mChemicalEquation += mProducts[j]->writeElement();
    }
  
}

void CChemEq::writeChemicalEquationConverted()
{
  string::size_type equal = string::npos;
  string Separator[] = {"->", "=>", "=", ""};
  unsigned C_INT32 i=0, j, k, kmax;
  
  while (Separator[i] != "" && equal == string::npos)
      equal = mChemicalEquation.find(Separator[i++]);
  if (equal == string::npos) fatalError();

  mChemicalEquationConverted.erase();
  
  for (j=0; j<mSubstrates.size(); j++)
    {
      if (j) mChemicalEquationConverted += " + ";
      kmax = (unsigned C_INT32) mSubstrates[j]->getMultiplicity();
      
      for (k=0; k<kmax; k++)
	{
	  if (k) mChemicalEquationConverted += " + ";
	  mChemicalEquationConverted += mSubstrates[j]->getMetaboliteName();
	}
    }

  mChemicalEquationConverted += " " + Separator[--i] + " ";

  for (j=0; j<mProducts.size(); j++)
    {
      if (j) mChemicalEquation += " + ";
      kmax = (unsigned C_INT32) mProducts[j]->getMultiplicity();
      
      for (k=0; k<kmax; k++)
	{
	  if (k) mChemicalEquationConverted += " + ";
	  mChemicalEquationConverted += mProducts[j]->getMetaboliteName();
	}
    }
}

