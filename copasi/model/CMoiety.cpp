#include <stdio.h>
#include <math.h>

#include "copasi.h"
#include "utilities/CCopasiMessage.h"
#include "CMoiety.h"
#include "CCompartment.h"
#include "utilities/utilities.h"

CMoiety::CMoiety() {}

CMoiety::CMoiety(const string & name) {mName = name;}

CMoiety::~CMoiety() {}

void CMoiety::add(C_FLOAT64 value,
                  CMetab & metabolite)
{
  ELEMENT element;
  element.mValue = value;
  element.mMetab = &metabolite;
        
  mEquation.push_back(element);
}

void CMoiety::add(C_FLOAT64 value,
                  CMetab * metabolite)
{
  ELEMENT element;
  element.mValue = value;
  element.mMetab = metabolite;
        
  mEquation.push_back(element);
}

void CMoiety::cleanup() {mEquation.clear();}

void CMoiety::cleanup(const string & name)
{
  unsigned C_INT32 i;

  for (i = 0; i < mEquation.size(); i++)
    if (mEquation[i].mMetab->getName() == name) break;
    
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

C_FLOAT64 CMoiety::dependentNumber()
{
  C_FLOAT64 Number = mINumber;
    
  for(unsigned C_INT32 i=1; i < mEquation.size(); i++)
    Number -= mEquation[i].mValue * 
      *mEquation[i].mMetab->getConcentration() * 
      mEquation[i].mMetab->getCompartment()->getVolume();
    
  return Number;
}

string CMoiety::getName() const {return mName;}

string CMoiety::getDescription() const
{
  string Description;
    
  for(unsigned C_INT32 i=0; i < mEquation.size(); i++)
    {
      if (i) 
        {
	  if (mEquation[i].mValue < 0.0)
	    Description += " - ";
	  else
	    Description += " + ";
        }
      if (fabs(mEquation[i].mValue) != 1.0)
	Description += StringPrint("%3.1f * ", fabs(mEquation[i].mValue));
      Description += mEquation[i].mMetab->getName();
    }
  return Description;
}

void CMoiety::setName(const string name) {mName = name;}

void CMoiety::setInitialValue()
{
  mINumber = 0.0;
    
  for (unsigned C_INT32 i=0; i<mEquation.size(); i++)
    mINumber += mEquation[i].mValue *
      mEquation[i].mMetab->getInitialNumber();

  return;
}

/**
 * Return the number value Wei Sun
 */
C_FLOAT64 CMoiety::getNumber() const
{
  return mNumber;
}

/**
 *	Returns the address of mNumber
 */
void * CMoiety::getNumberAddr()
{
  return &mNumber;
}

