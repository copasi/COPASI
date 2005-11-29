/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMoiety.cpp,v $
   $Revision: 1.32 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/29 17:28:12 $
   End CVS Header */

#include <stdio.h>
#include "mathematics.h"

#include "copasi.h"
#include "utilities/CCopasiMessage.h"
#include "CMoiety.h"
#include "CCompartment.h"
#include "utilities/CReadConfig.h"
#include "utilities/CCopasiVector.h"
#include "utilities/utility.h"
#include "CMetabNameInterface.h"

#include "report/CKeyFactory.h"//By G

CMoiety::CMoiety(const std::string & name,
                 const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Moiety"),
    mKey(GlobalKeys.add("Moiety", this)),              //By G
    mNumber(0),
    mINumber(0),
    mEquation()
{CONSTRUCTOR_TRACE;}

CMoiety::CMoiety(const CMoiety & src,
                 const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("Moiety", this)),              //By G
    mNumber(src.mNumber),
    mINumber(src.mINumber),
    mEquation(src.mEquation)
{CONSTRUCTOR_TRACE;}

CMoiety::~CMoiety()
{
  GlobalKeys.remove(mKey);
  DESTRUCTOR_TRACE;
}

void CMoiety::add(C_FLOAT64 value, CMetab * pMetabolite)
{
  std::pair<C_FLOAT64, CMetab *> element;

  element.first = value;
  element.second = pMetabolite;

  mEquation.push_back(element);
}

void CMoiety::cleanup() {mEquation.clear();}

C_FLOAT64 CMoiety::dependentNumber()
{
  mNumber = mINumber;

  for (unsigned C_INT32 i = 1; i < mEquation.size(); i++)
    mNumber -=
      mEquation[i].first * mEquation[i].second->getNumber();

  return mNumber;
}

/*C_FLOAT64 CMoiety::dependentRate()
{
  C_FLOAT64 Rate = 0.0;
 
  for (unsigned C_INT32 i = 1; i < mEquation.size(); i++)
    Rate -= mEquation[i].first *
            mEquation[i].second->getConcentrationRate() *
            mEquation[i].second->getCompartment()->getVolumeInv();  //TODO::check!!!!
 
  return Rate * mEquation[0].second->getCompartment()->getVolume();
}*/ //seems to be unused

const std::string & CMoiety::getKey() const {return mKey;} //By G

//const std::string & CMoiety::getName() const {return getObjectName();}

/*std::string CMoiety::getDescription() const
  {
    std::string Description;
    for (unsigned C_INT32 i = 0; i < mEquation.size(); i++)
      {
        if (i)
          {
            if (mEquation[i].first < 0.0)
              Description += " - ";
            else
              Description += " + ";
          }
        if (fabs(mEquation[i].first) != 1.0)
          Description += StringPrint("%3.1f * ",
                                     fabs(mEquation[i].first));
        Description += mEquation[i].second->getObjectName();
        //Description += "{" + mEquation[i]->getCompartmentName() + "}";
        Description += "{" + mEquation[i].second->getCompartment()->getObjectName() + "}";
      }
    return Description;
  }*/

std::string CMoiety::getDescription(const CModel * model) const
  {
    std::string Description;
    for (unsigned C_INT32 i = 0; i < mEquation.size(); i++)
      {
        if (i)
          {
            if (mEquation[i].first < 0.0)
              Description += " - ";
            else
              Description += " + ";
          }
        if (fabs(mEquation[i].first) != 1.0)
          Description += StringPrint("%3.1f * ",
                                     fabs(mEquation[i].first));
        Description += CMetabNameInterface::getDisplayName(model, *mEquation[i].second);
      }
    return Description;
  }

bool CMoiety::setName(const std::string name)
{
  return setObjectName(name);
}

void CMoiety::setInitialValue()
{
  mINumber = 0;

  for (unsigned C_INT32 i = 0; i < mEquation.size(); i++)
    mINumber += mEquation[i].first *
                mEquation[i].second->getInitialNumber();
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
/*C_INT32 CMoiety::saveOld(CWriteConfig & configBuffer)
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
}*/
