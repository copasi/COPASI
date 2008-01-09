// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptItem.cpp,v $
//   $Revision: 1.26 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/09 14:53:46 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <limits>
#include <math.h>
#include <float.h>
#include <sstream>

#include "copasi.h"

#include "COptItem.h"

#include "randomGenerator/CRandom.h"
#include "report/CCopasiContainer.h"
#include "report/CCopasiObjectName.h"
#include "utilities/CCopasiParameterGroup.h"
#include "utilities/CCopasiMessage.h"
#include "utilities/utility.h"

C_FLOAT64 NaN = std::numeric_limits<C_FLOAT64>::quiet_NaN();

UpdateMethod DoNothing;

CRandom * COptItem::mpRandom = NULL;

COptItem::COptItem(const std::string & name,
                   const CCopasiContainer * pParent):
    CCopasiParameterGroup(name, pParent),
    mpParmObjectCN(NULL),
    mpParmLowerBound(NULL),
    mpParmUpperBound(NULL),
    mpParmStartValue(NULL),
    mpObject(NULL),
    mpMethod(NULL),
    mpObjectValue(NULL),
    mpLowerObject(NULL),
    mpLowerBound(NULL),
    mLowerBound(0.0),
    mpUpperObject(NULL),
    mpUpperBound(NULL),
    mUpperBound(0.0)
{initializeParameter();}

COptItem::COptItem(const COptItem & src,
                   const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mpParmObjectCN(NULL),
    mpParmLowerBound(NULL),
    mpParmUpperBound(NULL),
    mpParmStartValue(NULL),
    mpObject(NULL),
    mpMethod(NULL),
    mpObjectValue(NULL),
    mpLowerObject(NULL),
    mpLowerBound(NULL),
    mLowerBound(0.0),
    mpUpperObject(NULL),
    mpUpperBound(NULL),
    mUpperBound(0.0)
{initializeParameter();}

COptItem::COptItem(const CCopasiParameterGroup & group,
                   const CCopasiContainer * pParent):
    CCopasiParameterGroup(group, pParent),
    mpParmObjectCN(NULL),
    mpParmLowerBound(NULL),
    mpParmUpperBound(NULL),
    mpParmStartValue(NULL),
    mpObject(NULL),
    mpMethod(NULL),
    mpObjectValue(NULL),
    mpLowerObject(NULL),
    mpLowerBound(NULL),
    mLowerBound(0.0),
    mpUpperObject(NULL),
    mpUpperBound(NULL),
    mUpperBound(0.0)
{initializeParameter();}

COptItem::~COptItem()
{}

void COptItem::initializeParameter()
{
  mpParmObjectCN =
    assertParameter("ObjectCN", CCopasiParameter::CN, CCopasiObjectName(""))->getValue().pCN;
  mpParmLowerBound =
    assertParameter("LowerBound", CCopasiParameter::CN, CCopasiObjectName("-inf"))->getValue().pCN;
  mpParmUpperBound =
    assertParameter("UpperBound", CCopasiParameter::CN, CCopasiObjectName("inf"))->getValue().pCN;
  mpParmStartValue =
    assertParameter("StartValue", CCopasiParameter::DOUBLE, NaN)->getValue().pDOUBLE;
}

bool COptItem::setObjectCN(const CCopasiObjectName & objectCN)
{
  const CCopasiObject * pObject = RootContainer.getObject(objectCN);

  if (pObject == NULL || !pObject->isValueDbl())
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 1, objectCN.c_str());
      return false;
    }

  *mpParmObjectCN = objectCN;
  return true;
}

const CCopasiObject * COptItem::getObject() const
  {return mpObject;}

const CCopasiObjectName COptItem::getObjectCN() const
  {return *mpParmObjectCN;}

std::string COptItem::getObjectDisplayName() const
  {
    if (!mpObject && !const_cast<COptItem *>(this)->compile())
      return "Invalid Optimization Item";

    return mpObject->getObjectDisplayName();
  }

bool COptItem::setLowerBound(const CCopasiObjectName & lowerBound)
{
  const CCopasiObject * pObject;

  if (lowerBound[0] == '-' &&
      lowerBound[lowerBound.length() - 1] == '%' &&
      isNumber(lowerBound.substr(1, lowerBound.length() - 2)))
    {
      std::stringstream LowerBound;
      C_FLOAT64 StartValue = getStartValue();

      LowerBound << StartValue + fabs(StartValue) * strtod(lowerBound.c_str(), NULL) / 100.0;
      *mpParmLowerBound = LowerBound.str();

      return true;
    }

  if (lowerBound != "-inf" &&
      !isNumber(lowerBound) &&
      ((pObject = RootContainer.getObject(lowerBound)) == NULL ||
       !pObject->isValueDbl()))
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 2, lowerBound.c_str());
      return false;
    }

  *mpParmLowerBound = lowerBound;
  return true;
}

const std::string COptItem::getLowerBound() const
  {return *mpParmLowerBound;}

bool COptItem::setUpperBound(const CCopasiObjectName & upperBound)
{
  const CCopasiObject * pObject;

  if (upperBound[0] == '+' &&
      upperBound[upperBound.length() - 1] == '%' &&
      isNumber(upperBound.substr(1, upperBound.length() - 2)))
    {
      std::stringstream UpperBound;
      C_FLOAT64 StartValue = getStartValue();

      UpperBound << StartValue + fabs(StartValue) * strtod(upperBound.c_str(), NULL) / 100.0;
      *mpParmUpperBound = UpperBound.str();

      return true;
    }

  if (upperBound != "inf" &&
      !isNumber(upperBound) &&
      ((pObject = RootContainer.getObject(upperBound)) == NULL ||
       !pObject->isValueDbl()))
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 3, upperBound.c_str());
      return false;
    }

  *mpParmUpperBound = upperBound;
  return true;
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
        CCopasiObject * pObject = CCopasiContainer::ObjectFromName(getObjectCN());
        if (pObject != NULL)
          return * (C_FLOAT64 *) pObject->getValuePointer();

        return NaN;
      }

    return *mpObjectValue;
  }

C_FLOAT64 COptItem::getRandomValue(CRandom * pRandom)
{
  C_FLOAT64 RandomValue;

  if (mpLowerBound == NULL ||
      mpUpperBound == NULL) compile();

  if (mpLowerBound == NULL ||
      mpUpperBound == NULL)
    {
      RandomValue = NaN;
      return RandomValue;
    }

  if (pRandom == NULL)
    {
      if (mpRandom == NULL)
        mpRandom = CRandom::createGenerator();
      pRandom = mpRandom;
    }

  C_FLOAT64 mn = *mpLowerBound;
  C_FLOAT64 mx = *mpUpperBound;

  C_FLOAT64 la;

  try
    {
      // First determine the location of the intervall
      // Secondly determine whether to distribute the parameter linearly or not
      // depending on the location and act uppon it.
      if (0.0 <= mn) // the interval [mn, mx) is in [0, inf)
        {
          la = log10(mx) - log10(std::max(mn, DBL_MIN));

          if (la < 1.8 || !(mn > 0.0)) // linear
            RandomValue = mn + pRandom->getRandomCC() * (mx - mn);
          else
            RandomValue = pow(10.0, log10(std::max(mn, DBL_MIN)) + la * pRandom->getRandomCC());
        }
      else if (mx > 0) // 0 is in the interval (mn, mx)
        {
          la = log10(mx) + log10(-mn);

          if (la < 3.6) // linear
            RandomValue = mn + pRandom->getRandomCC() * (mx - mn);
          else
            {
              C_FLOAT64 mean = (mx + mn) * 0.5;
              C_FLOAT64 sigma = std::min(DBL_MAX, mx - mn) / 3.0;

              do
                {
                  RandomValue = pRandom->getRandomNormal(mean, sigma);
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

          la = log10(mx) - log10(std::max(mn, DBL_MIN));

          if (la < 1.8 || !(mn > 0.0)) // linear
            RandomValue = - (mn + pRandom->getRandomCC() * (mx - mn));
          else
            RandomValue = - pow(10.0, log10(std::max(mn, DBL_MIN)) + la * pRandom->getRandomCC());
        }
    }

  catch (...)
    {
      RandomValue = (mx + mn) * 0.5;
    }

  return RandomValue;
}

UpdateMethod * COptItem::getUpdateMethod() const
  {return mpMethod;}

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

bool COptItem::compile(const std::vector< CCopasiContainer * > listOfContainer)
{
  std::string Bound;

  mpMethod = &DoNothing;
  mpObjectValue = &NaN;

  if ((mpObject =
         CCopasiContainer::ObjectFromName(listOfContainer,
                                          getObjectCN())) != NULL &&
      mpObject->isValueDbl())
    mpObjectValue = (C_FLOAT64 *) mpObject->getValuePointer();
  if (mpObjectValue == &NaN)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 1, getObjectCN().c_str());
      return false;
    }
  mpMethod = mpObject->getUpdateMethod();

  mpLowerObject = NULL;
  mpLowerBound = NULL;
  Bound = getLowerBound();
  if (Bound == "-inf")
    {
      mLowerBound = - DBL_MAX;
      mpLowerBound = &mLowerBound;
    }
  else if (isNumber(Bound))
    {
      mLowerBound = strtod(Bound.c_str(), NULL);
      mpLowerBound = &mLowerBound;
    }
  else if ((mpLowerObject =
              CCopasiContainer::ObjectFromName(listOfContainer,
                                               Bound)) != NULL &&
           mpLowerObject->isValueDbl())
    mpLowerBound = (C_FLOAT64 *) mpLowerObject->getValuePointer();
  if (!mpLowerBound)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 2, Bound.c_str());
      return false;
    }

  mpUpperObject = NULL;
  mpUpperBound = NULL;
  Bound = getUpperBound();
  if (Bound == "inf")
    {
      mUpperBound = DBL_MAX;
      mpUpperBound = &mUpperBound;
    }
  else if (isNumber(Bound))
    {
      mUpperBound = strtod(Bound.c_str(), NULL);
      mpUpperBound = &mUpperBound;
    }
  else if ((mpUpperObject =
              CCopasiContainer::ObjectFromName(listOfContainer,
                                               Bound)) != NULL &&
           mpUpperObject->isValueDbl())
    mpUpperBound = (C_FLOAT64 *) mpUpperObject->getValuePointer();
  if (!mpUpperBound)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 3, Bound.c_str());
      return false;
    }

  if (!mpUpperObject && !mpLowerObject && *mpUpperBound < *mpLowerBound)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 4, *mpLowerBound, *mpUpperBound);
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

      default:
        return 0.0;
        break;
      }
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

std::ostream &operator<<(std::ostream &os, const COptItem & o)
{
  if (!o.mpObject && const_cast<COptItem *>(&o)->compile())
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

  return os;
}
