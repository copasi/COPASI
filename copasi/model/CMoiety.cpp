/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMoiety.cpp,v $
   $Revision: 1.34.2.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/01/10 14:12:07 $
   End CVS Header */

#include <stdio.h>
#include <float.h>
#include "mathematics.h"

#include "copasi.h"
#include "CMoiety.h"
#include "CCompartment.h"
#include "CMetabNameInterface.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"//By G

#include "utilities/CCopasiMessage.h"
#include "utilities/CReadConfig.h"
#include "utilities/CCopasiVector.h"
#include "utilities/utility.h"

CMoiety::CMoiety(const std::string & name,
                 const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Moiety"),
    mKey(GlobalKeys.add("Moiety", this)),                 //By G
    mNumber(0),
    mINumber(0),
    mEquation()
{
  initObjects();
  CONSTRUCTOR_TRACE;
}

CMoiety::CMoiety(const CMoiety & src,
                 const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("Moiety", this)),                 //By G
    mNumber(src.mNumber),
    mINumber(src.mINumber),
    mEquation(src.mEquation)
{
  initObjects();
  CONSTRUCTOR_TRACE;
}

CMoiety::~CMoiety()
{
  GlobalKeys.remove(mKey);
  DESTRUCTOR_TRACE;
}

void CMoiety::initObjects()
{
  addObjectReference("Value", mINumber, CCopasiObject::ValueDbl);
  return;
}

void CMoiety::add(C_FLOAT64 value, CMetab * pMetabolite)
{
  std::pair<C_FLOAT64, CMetab *> element;

  element.first = value;
  element.second = pMetabolite;

  pMetabolite->addMoiety(this);

  mEquation.push_back(element);
}

void CMoiety::cleanup() {mEquation.clear();}

bool CMoiety::refreshDependentNumber()
{
  mNumber = mINumber;

  std::vector< std::pair< C_FLOAT64, CMetab * > >::iterator it = mEquation.begin() + 1;
  std::vector< std::pair< C_FLOAT64, CMetab * > >::iterator end = mEquation.end();
  for (; it != end; ++it)
    mNumber -= it->first * it->second->getNumber();

  return true;
}

C_FLOAT64 CMoiety::dependentNumber()
{
  refreshDependentNumber();
  return mNumber;
}

const std::string & CMoiety::getKey() const {return mKey;} //By G

std::string CMoiety::getDescription(const CModel * model) const
  {
    std::string Description;

    std::vector< std::pair< C_FLOAT64, CMetab * > >::const_iterator it = mEquation.begin();
    std::vector< std::pair< C_FLOAT64, CMetab * > >::const_iterator end = mEquation.end();
    for (; it != end; ++it)
      {
        if (it != mEquation.begin())
          {
            if (it->first < 0.0)
              Description += " - ";
            else
              Description += " + ";
          }
        if (fabs(it->first) > 1.0 + 100 * DBL_EPSILON ||
            fabs(it->first) < 1.0 - 100 * DBL_EPSILON)
          Description += StringPrint("%g * ", fabs(it->first));

        Description += CMetabNameInterface::getDisplayName(model, *it->second);
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

  std::vector< std::pair< C_FLOAT64, CMetab * > >::iterator it = mEquation.begin();
  std::vector< std::pair< C_FLOAT64, CMetab * > >::iterator end = mEquation.end();
  for (; it != end; ++it)
    mINumber += it->first * it->second->getInitialNumber();

  return;
}

/**
 * Return the number value Wei Sun
 */
C_FLOAT64 CMoiety::getNumber() const
  {
    return mINumber;
  }
