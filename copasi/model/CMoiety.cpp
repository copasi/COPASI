#include <stdio.h>
#include <math.h>

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "utilities/CCopasiMessage.h"
#include "CMoiety.h"
#include "CCompartment.h"
#include "utilities/utilities.h"

CMoiety::CMoiety()
{
  CONSTRUCTOR_TRACE;
}

CMoiety::CMoiety(const CMoiety & src)
{
  CONSTRUCTOR_TRACE;
  mName = src.mName;
  mNumber = src.mNumber;
  mINumber = src.mINumber;
  mEquation = CCopasiVector < CChemEqElement >(src.mEquation);
}

CMoiety::CMoiety(const string & name)
{
  CONSTRUCTOR_TRACE;
  mName = name;
}

CMoiety::~CMoiety()
{
  DESTRUCTOR_TRACE;
}

void CMoiety::add
  (C_FLOAT64 value, CMetab & metabolite)
  {
    CChemEqElement * element = new CChemEqElement;
    element->setMultiplicity(value);
    element->setMetabolite(metabolite);

    mEquation.add(element);
  }

void CMoiety::add
  (C_FLOAT64 value, CMetab * metabolite)
  {
    add
      (value, *metabolite);
  }

void CMoiety::cleanup()
{
  mEquation.cleanup();
}

C_FLOAT64 CMoiety::dependentNumber()
{
  mNumber = mINumber;

  for (unsigned C_INT32 i = 1; i < mEquation.size(); i++)
    mNumber -= mEquation[i]->getMultiplicity() *
               mEquation[i]->getMetabolite().getNumberDbl();

  return mNumber;
}

C_FLOAT64 CMoiety::dependentRate()
{
  C_FLOAT64 Rate = 0.0;

  for (unsigned C_INT32 i = 1; i < mEquation.size(); i++)
    Rate -= mEquation[i]->getMultiplicity() *
            mEquation[i]->getMetabolite().getRate() *
            mEquation[i]->getMetabolite().getCompartment()->getVolumeInv();

  return Rate * mEquation[0]->getMetabolite().getCompartment()->getVolume();
}

string CMoiety::getName() const
  {
    return mName;
  }

string CMoiety::getDescription() const
  {
    string Description;
    for (unsigned C_INT32 i = 0; i < mEquation.size(); i++)
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

void CMoiety::setName(const string name)
{
  mName = name;
}

void CMoiety::setInitialValue()
{
  mINumber = 0;

  for (unsigned C_INT32 i = 0; i < mEquation.size(); i++)
    mINumber += mEquation[i]->getMultiplicity() *
                mEquation[i]->getMetabolite().getInitialNumberDbl();
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
 * Returns the address of mNumber
 */
void * CMoiety::getNumberAddr()
{
  return &mINumber;
}

/**
 * Saves in Gepasi 3.21 format
 */
C_INT32 CMoiety::saveOld(CWriteConfig & configBuffer)
{
  C_INT32 c = 0, t = 7, Fail = 0;

  Fail = configBuffer.setVariable("Metabolite", "string", (void *) & mEquation);
  if (Fail)
    return Fail;
  // we write mNumber instead of concentration, which is ok because Gepasi recalculates this itself
  Fail = configBuffer.setVariable("Concentration", "C_FLOAT64", (void *) & mNumber);
  if (Fail)
    return Fail;
  Fail = configBuffer.setVariable("Compartment", "C_INT32", (void *) & c);
  if (Fail)
    return Fail;
  Fail = configBuffer.setVariable("Type", "C_INT32", (void *) & t);
  return Fail;
}
