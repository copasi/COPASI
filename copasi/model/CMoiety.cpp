#include <stdio.h>
#include <math.h>

#include "copasi.h"
#include "utilities/CCopasiMessage.h"
#include "CMoiety.h"
#include "CCompartment.h"
#include "utilities/utilities.h"

CMoiety::CMoiety() {}

CMoiety::CMoiety(const CMoiety & src) 
{
  mName = src.mName;
  mNumber = src.mNumber;
  mINumber = src.mINumber;
  mEquation = CCopasiVector < CChemEqElement >(src.mEquation);
}

CMoiety::CMoiety(const string & name) {mName = name;}

CMoiety::~CMoiety() {}

void CMoiety::add(C_FLOAT64 value, CMetab & metabolite)
{
  CChemEqElement * element = new CChemEqElement;
  element->setMultiplicity(value);
  element->setMetabolite(metabolite);
        
  mEquation.add(element);
}

void CMoiety::add(C_FLOAT64 value, CMetab * metabolite)
{add(value, *metabolite);}

void CMoiety::cleanup() {mEquation.cleanup();}

#ifdef XXXX
void CMoiety::cleanup(const string & name)
{
  unsigned C_INT32 i;

  for (i = 0; i < mEquation.size(); i++)
    if (mEquation[i].getName() == name) break;
    
  if (i == mEquation.size()) fatalError();

  cleanup(i);
}

void CMoiety::cleanup(C_INT32 index)
{
  mEquation.erase(&mEquation[index], &mEquation[index+1]);
}

void CMoiety::change(C_INT32 index,
		     C_FLOAT64 value)
{
  mEquation[index].mValue = value;
}

void CMoiety::change(const string & name,
		     C_FLOAT64 value)
{
  unsigned C_INT32 i;

  for (i = 0; i < mEquation.size(); i++)
    if (mEquation[i].mMetab->getName() == name) break;
    
  if (i == mEquation.size()) fatalError();

  change(i, value);
}
#endif // XXXX

C_FLOAT64 CMoiety::dependentNumber()
{
  mNumber = mINumber;
    
  for(unsigned C_INT32 i=1; i < mEquation.size(); i++)
    mNumber -= mEquation[i]->getMultiplicity() * 
      mEquation[i]->getMetabolite().getNumber();
    
  return mNumber;
}

string CMoiety::getName() const {return mName;}

string CMoiety::getDescription() const
{
  string Description;
    
  for(unsigned C_INT32 i=0; i < mEquation.size(); i++)
    {
      if (i) 
        {
	  if (mEquation[i]->getMultiplicity() < 0.0)
	    Description += " - ";
	  else
	    Description += " + ";
        }
      if (fabs(mEquation[i]->getMultiplicity()) != 1.0)
	Description += StringPrint("%3.1f * ", 
				   fabs(mEquation[i]->getMultiplicity()));
      Description += mEquation[i]->getMetaboliteName();
      Description += "{" + mEquation[i]->getCompartmentName() + "}";
    }
  return Description;
}

void CMoiety::setName(const string name) {mName = name;}

void CMoiety::setInitialValue()
{
  mINumber = 0.0;
    
  for (unsigned C_INT32 i=0; i<mEquation.size(); i++)
    mINumber += mEquation[i]->getMultiplicity() *
      mEquation[i]->getMetabolite().getInitialNumber();

  return;
}

/**
 * Return the number value Wei Sun
 */
C_FLOAT64 CMoiety::getNumber() const
{
  return mINumber;
}

/**
 *	Returns the address of mNumber
 */
void * CMoiety::getNumberAddr()
{
  return &mINumber;
}

