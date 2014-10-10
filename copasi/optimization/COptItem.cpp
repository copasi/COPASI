// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"

#include "COptItem.h"

#include "math/CMathObject.h"
#include "randomGenerator/CRandom.h"
#include "report/CCopasiContainer.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiObjectName.h"
#include "utilities/CCopasiParameterGroup.h"
#include "utilities/CCopasiMessage.h"
#include "utilities/utility.h"

C_FLOAT64 NaN = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

COptItem::COptItem(const CCopasiContainer * pParent,
                   const std::string & name):
  CCopasiParameterGroup(name, pParent),
  mpParmObjectCN(NULL),
  mpParmLowerBound(NULL),
  mpParmUpperBound(NULL),
  mpParmStartValue(NULL),
  mpObject(NULL),
  mpObjectValue(NULL),
  mpLowerObject(NULL),
  mpLowerBound(NULL),
  mLowerBound(0.0),
  mpUpperObject(NULL),
  mpUpperBound(NULL),
  mUpperBound(0.0),
  mLastStartValue(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
{initializeParameter();}

COptItem::COptItem(const COptItem & src,
                   const CCopasiContainer * pParent):
  CCopasiParameterGroup(src, (pParent != NULL) ? pParent : src.getObjectDataModel()),
  mpParmObjectCN(NULL),
  mpParmLowerBound(NULL),
  mpParmUpperBound(NULL),
  mpParmStartValue(NULL),
  mpObject(NULL),
  mpObjectValue(NULL),
  mpLowerObject(NULL),
  mpLowerBound(NULL),
  mLowerBound(0.0),
  mpUpperObject(NULL),
  mpUpperBound(NULL),
  mUpperBound(0.0),
  mLastStartValue(src.mLastStartValue)
{initializeParameter();}

COptItem::COptItem(const CCopasiParameterGroup & group,
                   const CCopasiContainer * pParent):
  CCopasiParameterGroup(group, (pParent != NULL) ? pParent : group.getObjectDataModel()),
  mpParmObjectCN(NULL),
  mpParmLowerBound(NULL),
  mpParmUpperBound(NULL),
  mpParmStartValue(NULL),
  mpObject(NULL),
  mpObjectValue(NULL),
  mpLowerObject(NULL),
  mpLowerBound(NULL),
  mLowerBound(0.0),
  mpUpperObject(NULL),
  mpUpperBound(NULL),
  mUpperBound(0.0),
  mLastStartValue(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
{initializeParameter();}

COptItem::~COptItem()
{}

void COptItem::initializeParameter()
{
  mpParmObjectCN =
    assertParameter("ObjectCN", CCopasiParameter::CN, CCopasiObjectName(""))->getValue().pCN;
  mpParmLowerBound =
    assertParameter("LowerBound", CCopasiParameter::CN, CCopasiObjectName("1e-06"))->getValue().pCN;
  mpParmUpperBound =
    assertParameter("UpperBound", CCopasiParameter::CN, CCopasiObjectName("1e+06"))->getValue().pCN;
  mpParmStartValue =
    assertParameter("StartValue", CCopasiParameter::DOUBLE, NaN)->getValue().pDOUBLE;
}

bool COptItem::setObjectCN(const CCopasiObjectName & objectCN)
{
  const CCopasiObject * pObject = CObjectInterface::DataObject(getObjectFromCN(objectCN));

  if (pObject == NULL || !pObject->isValueDbl())
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 1, objectCN.c_str());
      return false;
    }

  *mpParmObjectCN = objectCN;
  return true;
}

const CObjectInterface * COptItem::getObject() const
{return mpObject;}

const CCopasiObjectName COptItem::getObjectCN() const
{return *mpParmObjectCN;}

std::string COptItem::getObjectDisplayName() const
{
  if (!mpObject && !const_cast<COptItem *>(this)->compile(CObjectInterface::ContainerList()))
    return "Invalid Optimization Item";

  return mpObject->getObjectDisplayName();
}

bool COptItem::setLowerBound(const CCopasiObjectName & lowerBound)
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

  return compileLowerBound(CCopasiContainer::EmptyList);
}

const std::string COptItem::getLowerBound() const
{return *mpParmLowerBound;}

bool COptItem::setUpperBound(const CCopasiObjectName & upperBound)
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

  return compileUpperBound(CCopasiContainer::EmptyList);
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
  if (!isnan(*mpParmStartValue))
    return *mpParmStartValue;

  if (mpObjectValue == NULL)
    {
      const CCopasiObject * pObject = CObjectInterface::DataObject(getObjectFromCN(getObjectCN()));

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

C_FLOAT64 COptItem::getRandomValue(CRandom & Random)
{
  C_FLOAT64 RandomValue;

  if (mpLowerBound == NULL ||
      mpUpperBound == NULL)
    {
      compile(CObjectInterface::ContainerList());
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

  if (!pTmp->setObjectCN(getObjectCN())) return false;

  if (!pTmp->setLowerBound(getLowerBound())) return false;

  if (!pTmp->setUpperBound(getUpperBound())) return false;

  return true;
}

bool COptItem::isValid(CCopasiParameterGroup & group)
{
  COptItem tmp(group);

  return tmp.isValid();
}

bool COptItem::compile(CObjectInterface::ContainerList listOfContainer)
{
  clearDirectDependencies();

  std::string Bound;

  mpObjectValue = &NaN;
  const CCopasiObject * pDataObject;

  listOfContainer.push_back(getObjectDataModel());

  if ((mpObject = CObjectInterface::GetObjectFromCN(listOfContainer, getObjectCN())) != NULL &&
      (pDataObject = CObjectInterface::DataObject(mpObject)) != NULL &&
      pDataObject->isValueDbl())
    mpObjectValue = (C_FLOAT64 *) mpObject->getValuePointer();

  if (mpObjectValue == &NaN)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 1, getObjectCN().c_str());
      return false;
    }

  if (!compileLowerBound(listOfContainer))
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 2, mpParmLowerBound->c_str());
      return false;
    }

  if (!compileUpperBound(listOfContainer))
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 2, mpParmUpperBound->c_str());
      return false;
    }

  if (!mpUpperObject && !mpLowerObject && *mpUpperBound < *mpLowerBound)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 4, *mpLowerBound, *mpUpperBound, mpObject->getObjectDisplayName().c_str());
      return false;
    }

  if (isnan(*mpParmStartValue))
    *mpParmStartValue = *mpObjectValue;

  return true;
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
{return *mpLowerBound <= value;}

bool COptItem::checkUpperBound(const C_FLOAT64 & value) const
{return value <= *mpUpperBound;}

const C_FLOAT64 * COptItem::getObjectValue() const
{return mpObjectValue;}

bool COptItem::compileLowerBound(const CObjectInterface::ContainerList & listOfContainer)
{
  const CCopasiObject * pDataObject;

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
           pDataObject->isValueDbl())
    {
      mpLowerBound = (C_FLOAT64 *) mpLowerObject->getValuePointer();
    }

  return mpLowerBound != NULL;
}

bool COptItem::compileUpperBound(const CObjectInterface::ContainerList & listOfContainer)
{
  const CCopasiObject * pDataObject;

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
           pDataObject->isValueDbl())
    {
      mpUpperBound = (C_FLOAT64 *) mpUpperObject->getValuePointer();
    }

  return mpUpperBound != NULL;
}

std::ostream &operator<<(std::ostream &os, const COptItem & o)
{
  if (!o.mpObject && const_cast<COptItem *>(&o)->compile(CObjectInterface::ContainerList()))
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
