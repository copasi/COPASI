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
  cleanupChemEqElements(mSubstrates);
  cleanupChemEqElements(mProducts);
  cleanupChemEqElements(mBalances);
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

  /* :TODO: we should construct this out of mSubstrates ans mProducts */
  mChemicalEquation = chemicalEquation;
  
  /* :TODO: we should construct this out of mBalances */
  mChemicalEquationConverted = chemicalEquation;
}

const string & CChemEq::getChemicalEquation() const
{return mChemicalEquation;}

const string & CChemEq::getChemicalEquationConverted() const
{return mChemicalEquationConverted;}

const vector < CChemEqElement * > & CChemEq::getSubstrates()
{return mSubstrates;}

const vector < CChemEqElement * > & CChemEq::getProducts()
{return mProducts;}

const vector < CChemEqElement * > & CChemEq::getBalances()
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

void CChemEq::addElement(vector < CChemEqElement * > & structure,
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
      structure.push_back(Element);
    }
  else if (role == CChemEq::SUBSTRATE) 
    structure[i]->addToMultiplicity(- element.getMultiplicity());
  else
    structure[i]->addToMultiplicity(element.getMultiplicity());
}

void CChemEq::setSubstrates(const string & left)
{
  setChemEqElements(mSubstrates, left, CChemEq::SUBSTRATE);
}
  
void CChemEq::setProducts(const string & right)
{
  setChemEqElements(mProducts, right);
}

void CChemEq::setBalances(const string & left, const string & right)
{
  setChemEqElements(mBalances, left, CChemEq::SUBSTRATE);
  setChemEqElements(mBalances, right);
}

void CChemEq::setChemEqElements(vector < CChemEqElement * > & elements,
				const string & reaction,
				CChemEq::MetaboliteRole role)
{
  string::size_type pos = 0;

  while (pos != string::npos)
    addElement(elements, extractElement(reaction, pos), role);
}

void CChemEq::cleanupChemEqElements(vector < CChemEqElement * > & elements)
{
  for (unsigned C_INT32 i=0; i<elements.size(); i++)
    free(elements[i]);
  elements.clear();
}

void CChemEq::splitChemEq(string & left, string & right) const
{
  string::size_type equal = 0;
    
  equal = mChemicalEquation.find("=");
  if (equal == string::npos) 
    {
      equal = mChemicalEquation.find("->");
      right = mChemicalEquation.substr(equal+2);
    }
  else
    right = mChemicalEquation.substr(equal+1);
  left = mChemicalEquation.substr(0,equal);
  
  return;
}

void 
CChemEq::compileChemEqElements(vector < CChemEqElement * > & elements,
			       vector < CMetab * > & metabolites)
{
  unsigned C_INT32 i, imax = elements.size();
  
  for (i=0; i<imax; i++)
    elements[i]->compile(metabolites);
}
