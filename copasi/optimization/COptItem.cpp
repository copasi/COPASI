// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <algorithm>
#include <limits>
#include <cmath>
#include <sstream>
#include <stdlib.h>

#include "copasi/copasi.h"

#include "COptItem.h"

#include "copasi/math/CMathObject.h"
#include "copasi/randomGenerator/CRandom.h"
#include "copasi/core/CDataContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/utilities/CCopasiParameterGroup.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/utilities/utility.h"

C_FLOAT64 NaN = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

COptItem::COptItem(const CDataContainer * pParent,
                   const std::string & name)
  : CCopasiParameterGroup(name, pParent)
  , mpParmObjectCN(NULL)
  , mpParmLowerBound(NULL)
  , mpParmUpperBound(NULL)
  , mpParmStartValue(NULL)
  , mpObject(NULL)
  , mpObjectValue(NULL)
  , mpLowerObject(NULL)
  , mpLowerBound(NULL)
  , mLowerBound(0.0)
  , mpUpperObject(NULL)
  , mpUpperBound(NULL)
  , mUpperBound(0.0)
  , mLastStartValue(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
  , mInterval(1.0)
  , mDependentItems()
  , mUpdateInterval()
{
  initializeParameter();
}

COptItem::COptItem(const COptItem & src,
                   const CDataContainer * pParent)
  : CCopasiParameterGroup(src, (pParent != NULL) ? pParent : static_cast< const CDataContainer * >(src.getObjectDataModel()))
  , mpParmObjectCN(NULL)
  , mpParmLowerBound(NULL)
  , mpParmUpperBound(NULL)
  , mpParmStartValue(NULL)
  , mpObject(NULL)
  , mpObjectValue(NULL)
  , mpLowerObject(NULL)
  , mpLowerBound(NULL)
  , mLowerBound(0.0)
  , mpUpperObject(NULL)
  , mpUpperBound(NULL)
  , mUpperBound(0.0)
  , mLastStartValue(src.mLastStartValue)
  , mInterval(src.mInterval)
  , mDependentItems(src.mDependentItems)
  , mUpdateInterval(src.mUpdateInterval)
{
  initializeParameter();
}

COptItem::COptItem(const CCopasiParameterGroup & group,
                   const CDataContainer * pParent)
  : CCopasiParameterGroup(group, (pParent != NULL) ? pParent : static_cast< const CDataContainer * >(group.getObjectDataModel()))
  , mpParmObjectCN(NULL)
  , mpParmLowerBound(NULL)
  , mpParmUpperBound(NULL)
  , mpParmStartValue(NULL)
  , mpObject(NULL)
  , mpObjectValue(NULL)
  , mpLowerObject(NULL)
  , mpLowerBound(NULL)
  , mLowerBound(0.0)
  , mpUpperObject(NULL)
  , mpUpperBound(NULL)
  , mUpperBound(0.0)
  , mLastStartValue(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
  , mInterval(1.0)
  , mDependentItems()
  , mUpdateInterval()
{
  initializeParameter();
}

COptItem::~COptItem()
{}

// virtual
void COptItem::calculateValue()
{
  // The size of the interval.
  mInterval = *mpUpperBound - *mpLowerBound;
  // std::cout << getObjectDisplayName() << ": " << mInterval << std::endl;
}

// virtual
void * COptItem::getValuePointer() const
{
  return const_cast< C_FLOAT64 * >(&mInterval);
}

void COptItem::initializeParameter()
{
  mpParmObjectCN = assertParameter("ObjectCN", CCopasiParameter::Type::CN, CCommonName(""));
  mpParmLowerBound = assertParameter("LowerBound", CCopasiParameter::Type::CN, CCommonName("1e-06"));
  mpParmUpperBound = assertParameter("UpperBound", CCopasiParameter::Type::CN, CCommonName("1e+06"));
  mpParmStartValue = assertParameter("StartValue", CCopasiParameter::Type::DOUBLE, NaN);
}

bool COptItem::setObjectCN(const CCommonName & objectCN)
{
  const CDataObject * pObject = CObjectInterface::DataObject(getObjectFromCN(objectCN));

  if (pObject == NULL || !pObject->hasFlag(CDataObject::ValueDbl))
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 1, objectCN.c_str());
      return false;
    }

  *mpParmObjectCN = objectCN;
  return true;
}

const CObjectInterface * COptItem::getObject() const
{return mpObject;}

const CCommonName COptItem::getObjectCN() const
{return *mpParmObjectCN;}

std::string COptItem::getObjectDisplayName() const
{
  if (mpObject == NULL)
    {
      const CDataObject * pObject = CObjectInterface::DataObject(getObjectFromCN(*mpParmObjectCN));

      if (pObject != NULL &&
          pObject->getValuePointer() != NULL)
        return pObject->getObjectDisplayName();

      return "Invalid Optimization Item";
    }

  return mpObject->getObjectDisplayName();
}

bool COptItem::setLowerBound(const CCommonName & lowerBound)
{
  if (lowerBound[0] == '-' &&
      lowerBound[lowerBound.length() - 1] == '%' &&
      isNumber(lowerBound.substr(1, lowerBound.length() - 2)))
    {
      std::stringstream LowerBound;
      C_FLOAT64 StartValue = getStartValue();

      LowerBound << StartValue + fabs(StartValue) * strToDouble(lowerBound.c_str(), NULL) / 100.0;
      *mpParmLowerBound = LowerBound.str();

      return true;
    }
  else
    {
      *mpParmLowerBound = lowerBound;
    }

  return compileLowerBound(CDataContainer::EmptyList);
}

const std::string COptItem::getLowerBound() const
{return *mpParmLowerBound;}

bool COptItem::setUpperBound(const CCommonName & upperBound)
{
  if (upperBound[0] == '+' &&
      upperBound[upperBound.length() - 1] == '%' &&
      isNumber(upperBound.substr(1, upperBound.length() - 2)))
    {
      std::stringstream UpperBound;
      C_FLOAT64 StartValue = getStartValue();

      UpperBound << StartValue + fabs(StartValue) * strToDouble(upperBound.c_str(), NULL) / 100.0;
      *mpParmUpperBound = UpperBound.str();

      return true;
    }
  else
    {
      *mpParmUpperBound = upperBound;
    }

  return compileUpperBound(CDataContainer::EmptyList);
}

const std::string COptItem::getUpperBound() const
{return *mpParmUpperBound;}

bool COptItem::setStartValue(const C_FLOAT64 & value)
{
  *mpParmStartValue = value;

  return true;
}

const C_FLOAT64 & COptItem::getStartValue() const
{
  if (!std::isnan(*mpParmStartValue))
    return *mpParmStartValue;

  if (mpObjectValue == NULL)
    {
      const CDataObject * pObject = CObjectInterface::DataObject(getObjectFromCN(*mpParmObjectCN));

      if (pObject != NULL &&
          pObject->getValuePointer() != NULL)
        return *(C_FLOAT64 *) pObject->getValuePointer();

      return NaN;
    }

  return *mpObjectValue;
}

const C_FLOAT64 & COptItem::getLastStartValue() const
{
  return mLastStartValue;
}

void COptItem::rememberStartValue()
{
  mLastStartValue = getStartValue();
}

C_FLOAT64 COptItem::getRandomValue(CRandom & Random) const
{
  C_FLOAT64 RandomValue;

  if (mpLowerBound == NULL ||
      mpUpperBound == NULL)
    {
      const_cast< COptItem * >(this)->compile(CObjectInterface::ContainerList());
    }

  if (mpLowerBound == NULL ||
      mpUpperBound == NULL)
    {
      RandomValue = NaN;
      return RandomValue;
    }

  C_FLOAT64 mn = *mpLowerBound;
  C_FLOAT64 mx = *mpUpperBound;

  C_FLOAT64 la;

  try
    {
      // First determine the location of the interval
      // Secondly determine whether to distribute the parameter linearly or not
      // depending on the location and act upon it.
      if (0.0 <= mn) // the interval [mn, mx) is in [0, inf)
        {
          la = log10(mx) - log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min()));

          if (la < 1.8 || !(mn > 0.0)) // linear
            RandomValue = mn + Random.getRandomCC() * (mx - mn);
          else
            RandomValue = pow(10.0, log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min())) + la * Random.getRandomCC());
        }
      else if (mx > 0) // 0 is in the interval (mn, mx)
        {
          la = log10(mx) + log10(-mn);

          if (la < 3.6) // linear
            RandomValue = mn + Random.getRandomCC() * (mx - mn);
          else
            {
              C_FLOAT64 mean = (mx + mn) * 0.5;
              C_FLOAT64 sigma = std::min(std::numeric_limits< C_FLOAT64 >::max(), mx - mn) / 3.0;

              do
                {
                  RandomValue = Random.getRandomNormal(mean, sigma);
                }
              while ((RandomValue < mn) || (RandomValue > mx));
            }
        }
      else // the interval (mn, mx] is in (-inf, 0]
        {
          // Switch lower and upper bound and change sign, i.e.,
          // we can treat it similarly as location 1:
          mx = - *mpLowerBound;
          mn = - *mpUpperBound;

          la = log10(mx) - log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min()));

          if (la < 1.8 || !(mn > 0.0)) // linear
            RandomValue = - (mn + Random.getRandomCC() * (mx - mn));
          else
            RandomValue = - pow(10.0, log10(std::max(mn, std::numeric_limits< C_FLOAT64 >::min())) + la * Random.getRandomCC());
        }
    }

  catch (...)
    {
      RandomValue = (mx + mn) * 0.5;
    }

  return RandomValue;
}

bool COptItem::isValid() const
{
  COptItem *pTmp = const_cast<COptItem *>(this);

  if (!pTmp->setObjectCN(*mpParmObjectCN)) return false;

  if (!pTmp->setLowerBound(getLowerBound())) return false;

  if (!pTmp->setUpperBound(getUpperBound())) return false;

  return true;
}

bool COptItem::isValid(CCopasiParameterGroup & group)
{
  COptItem tmp(group, NO_PARENT);

  return tmp.isValid();
}

bool COptItem::compile(CObjectInterface::ContainerList listOfContainer)
{
  bool success = true;
  mPrerequisits.clear();
  mDependentItems.clear();

  std::string Bound;

  mpObjectValue = &NaN;
  const CDataObject * pDataObject;

  listOfContainer.push_back(getObjectDataModel());

  if ((mpObject = CObjectInterface::GetObjectFromCN(listOfContainer, *mpParmObjectCN)) != NULL &&
      (pDataObject = CObjectInterface::DataObject(mpObject)) != NULL &&
      pDataObject->hasFlag(CDataObject::ValueDbl))
    mpObjectValue = (C_FLOAT64 *) mpObject->getValuePointer();

  if (mpObjectValue == &NaN)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 1, mpParmObjectCN->c_str());
      success = false;
    }

  if (compileLowerBound(listOfContainer))
    {
      if (mpLowerObject != NULL)
        {
          mPrerequisits.insert(mpLowerObject);
        }
    }
  else
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 2, mpParmLowerBound->c_str());
      success = false;
    }

  if (compileUpperBound(listOfContainer))
    {
      if (mpUpperObject != NULL)
        {
          mPrerequisits.insert(mpUpperObject);
        }
    }
  else
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 2, mpParmUpperBound->c_str());
      success = false;
    }

  // We can only access the lower and upper numbers if the compile succeeded so far.
  if (success && !mpUpperObject && !mpLowerObject && *mpUpperBound < *mpLowerBound)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 4, *mpLowerBound, *mpUpperBound, mpObject->getObjectDisplayName().c_str());
      success = false;
    }

  if (std::isnan(*mpParmStartValue))
    *mpParmStartValue = *mpObjectValue;

  return success;
}

C_INT32 COptItem::checkConstraint() const
{
  if (*mpLowerBound > *mpObjectValue) return - 1;

  if (*mpObjectValue > *mpUpperBound) return 1;

  return 0;
}

C_FLOAT64 COptItem::getConstraintViolation() const
{
  switch (checkConstraint())
    {
      case - 1:
        return *mpLowerBound - *mpObjectValue;
        break;

      case 1:
        return *mpObjectValue - *mpUpperBound;
        break;
    }

  return 0.0;
}

C_INT32 COptItem::checkConstraint(const C_FLOAT64 & value) const
{
  if (*mpLowerBound > value) return - 1;

  if (value > *mpUpperBound) return 1;

  return 0;
}

bool COptItem::checkLowerBound(const C_FLOAT64 & value) const
{
  return *mpLowerBound <= value;
}

bool COptItem::checkUpperBound(const C_FLOAT64 & value) const
{
  return value <= *mpUpperBound;
}

bool COptItem::checkInterval() const
{
  return *mpLowerBound <= *mpUpperBound;
}

bool COptItem::checkIsInitialValue() const
{
  if (dynamic_cast< const CMathObject * >(mpObject)
      && !static_cast< const CMathObject * >(mpObject)->isInitialValue())
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 10, mpObject->getObjectDisplayName().c_str());
      return false;
    }

  if (dynamic_cast< const CMathObject * >(mpLowerObject)
      && !static_cast< const CMathObject * >(mpLowerObject)->isInitialValue())
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 11, mpObject->getObjectDisplayName().c_str(), mpLowerObject->getObjectDisplayName().c_str());
      return false;
    }

  if (dynamic_cast< const CMathObject * >(mpUpperObject)
      && !static_cast< const CMathObject * >(mpUpperObject)->isInitialValue())
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 12, mpObject->getObjectDisplayName().c_str(), mpUpperObject->getObjectDisplayName().c_str());
      return false;
    }

  return true;
}

void COptItem::updatePrerequisites(const std::vector< COptItem * > & influencingIntervals)
{
  ObjectSet Original = mPrerequisits;
  mPrerequisits.clear();

  std::vector< COptItem * >::const_iterator it = influencingIntervals.begin();
  std::vector< COptItem * >::const_iterator end = influencingIntervals.end();

  for (COptItem * pOptItem : influencingIntervals)
    if (Original.find(pOptItem->getObject()) != Original.end())
      {
        mPrerequisits.insert(pOptItem);
      }
}

const C_FLOAT64 * COptItem::getObjectValue() const
{
  return mpObjectValue;
}

bool COptItem::compileLowerBound(const CObjectInterface::ContainerList & listOfContainer)
{
  const CDataObject * pDataObject;

  mpLowerObject = NULL;
  mpLowerBound = NULL;

  if (*mpParmLowerBound == "-inf")
    {
      mLowerBound = - std::numeric_limits< C_FLOAT64 >::max();
      mpLowerBound = &mLowerBound;
    }
  else if (isNumber(*mpParmLowerBound))
    {
      mLowerBound = strToDouble(mpParmLowerBound->c_str(), NULL);
      mpLowerBound = &mLowerBound;
    }
  else if ((mpLowerObject = CObjectInterface::GetObjectFromCN(listOfContainer, *mpParmLowerBound)) != NULL &&
           (pDataObject = CObjectInterface::DataObject(mpLowerObject)) != NULL &&
           pDataObject->hasFlag(CDataObject::ValueDbl))
    {
      mpLowerBound = (C_FLOAT64 *) mpLowerObject->getValuePointer();
    }

  return mpLowerBound != NULL;
}

bool COptItem::compileUpperBound(const CObjectInterface::ContainerList & listOfContainer)
{
  const CDataObject * pDataObject;

  mpUpperObject = NULL;
  mpUpperBound = NULL;

  if (*mpParmUpperBound == "inf")
    {
      mUpperBound = std::numeric_limits< C_FLOAT64 >::max();
      mpUpperBound = &mUpperBound;
    }
  else if (isNumber(*mpParmUpperBound))
    {
      mUpperBound = strToDouble(mpParmUpperBound->c_str(), NULL);
      mpUpperBound = &mUpperBound;
    }
  else if ((mpUpperObject = CObjectInterface::GetObjectFromCN(listOfContainer, *mpParmUpperBound)) != NULL &&
           (pDataObject = CObjectInterface::DataObject(mpUpperObject)) != NULL &&
           pDataObject->hasFlag(CDataObject::ValueDbl))
    {
      mpUpperBound = (C_FLOAT64 *) mpUpperObject->getValuePointer();
    }

  return mpUpperBound != NULL;
}

std::ostream &operator<<(std::ostream &os, const COptItem & o)
{
  if (o.mpObject == NULL && !const_cast<COptItem *>(&o)->compile(CObjectInterface::ContainerList()))
    return os << "Invalid Optimization Item";

  if (o.mpLowerObject)
    os << o.mpLowerObject->getObjectDisplayName();
  else
    os << o.getLowerBound();

  os << " <= ";
  os << o.mpObject->getObjectDisplayName();
  os << " <= ";

  if (o.mpUpperObject)
    os << o.mpUpperObject->getObjectDisplayName();
  else
    os << o.getUpperBound();

  os << "; Start Value = " << o.getStartValue();

  return os;
}

bool COptItem::influencesIntervals() const
{
  return mDependentItems.size() > 0;
}

void COptItem::setIntervalUpdateSequence(const CCore::CUpdateSequence & updateSequence)
{
  mUpdateInterval = updateSequence;
}

const CCore::CUpdateSequence & COptItem::getIntervalUpdateSequence() const
{
  return mUpdateInterval;
}

void COptItem::addDependentItem(COptItem * pDependentItem)
{
  mDependentItems.insert(pDependentItem);
}

const std::set< COptItem * > & COptItem::getDependentItems() const
{
  return mDependentItems;
}
