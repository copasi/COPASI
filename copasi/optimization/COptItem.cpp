/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptItem.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/01/20 20:41:42 $
   End CVS Header */

#include <float.h>

#include "copasi.h"

#include "COptItem.h"
#include "report/CCopasiContainer.h"
#include "report/CCopasiObjectName.h"
#include "utilities/CCopasiParameterGroup.h"

#include "utilities/utility.h"

COptItem::COptItem(CCopasiParameterGroup & group) :
    mpGroup(&group),
    mpObjectValue(NULL),
    mpLowerBound(NULL),
    mLowerBound(0.0),
    mpLowerRel(NULL),
    mpUpperBound(NULL),
    mUpperBound(0.0),
    mpUpperRel(NULL)
{}

COptItem::COptItem(COptItem & src) :
    mpGroup(src.mpGroup),
    mpObjectValue(src.mpObjectValue),
    mpLowerBound(src.mpLowerBound),
    mLowerBound(src.mLowerBound),
    mpLowerRel(src.mpLowerRel),
    mpUpperBound(src.mpUpperBound),
    mUpperBound(src.mUpperBound),
    mpUpperRel(src.mpUpperRel)
{}

COptItem::~COptItem()
{}

bool COptItem::setObjectCN(const CCopasiObjectName & objectCN)
{
  const CCopasiObject * pObject = RootContainer.getObject(objectCN);
  if (!pObject || !pObject->isValueDbl()) return false;

  return mpGroup->setValue(0, (const std::string) objectCN);
}

const CCopasiObjectName COptItem::getObjectCN() const
{return *(std::string*) mpGroup->getValue(0);}

bool COptItem::setLowerBound(const std::string & lowerBound)
{
  const CCopasiObject * pObject = RootContainer.getObject(lowerBound);

  if (lowerBound != "-inf" &&
      !isNumber(lowerBound) &&
      (!pObject || !pObject->isValueDbl())) return false;

  return mpGroup->setValue(1, lowerBound);
}

const std::string COptItem::getLowerBound() const
{return *(std::string*) mpGroup->getValue(1);}

bool COptItem::setLowerRelation(const std::string & lowerRel)
{
  if (lowerRel != "<" && lowerRel != "<=") return false;

  return mpGroup->setValue(2, lowerRel);
}

const std::string COptItem::getLowerRelation() const
{return *(std::string*) mpGroup->getValue(2);}

bool COptItem::setUpperBound(const std::string & upperBound)
{
  const CCopasiObject * pObject = RootContainer.getObject(upperBound);

  if (upperBound != "inf" &&
      !isNumber(upperBound) &&
      (!pObject || !pObject->isValueDbl())) return false;

  return mpGroup->setValue(3, upperBound);
}

const std::string COptItem::getUpperBound() const
{return *(std::string*) mpGroup->getValue(3);}

bool COptItem::setUpperRelation(const std::string & upperRel)
{
  if (upperRel != "<" && upperRel != "<=") return false;

  return mpGroup->setValue(4, upperRel);
}

const std::string COptItem::getUpperRelation() const
{return *(std::string*) mpGroup->getValue(4);}

bool COptItem::isValid() const
  {
    CCopasiParameter * pParameter;

    pParameter = (CCopasiParameter *) mpGroup->getValue(0);
    if (!pParameter || pParameter->getObjectName() != "ObjectCN") return false;

    pParameter = (CCopasiParameter *) mpGroup->getValue(1);
    if (!pParameter || pParameter->getObjectName() != "LowerBound") return false;

    pParameter = (CCopasiParameter *) mpGroup->getValue(2);
    if (!pParameter || pParameter->getObjectName() != "LowerRelation") return false;

    pParameter = (CCopasiParameter *) mpGroup->getValue(3);
    if (!pParameter || pParameter->getObjectName() != "UpperBound") return false;

    pParameter = (CCopasiParameter *) mpGroup->getValue(4);
    if (!pParameter || pParameter->getObjectName() != "UpperRelation") return false;

    COptItem *pTmp = const_cast<COptItem *>(this);

    if (!pTmp->setObjectCN(getObjectCN())) return false;
    if (!pTmp->setLowerBound(getLowerBound())) return false;
    if (!pTmp->setLowerRelation(getLowerRelation())) return false;
    if (!pTmp->setUpperBound(getUpperBound())) return false;
    if (!pTmp->setUpperRelation(getUpperRelation())) return false;

    return true;
  }

bool COptItem::isValid(CCopasiParameterGroup & group)
{
  COptItem tmp(group);
  return tmp.isValid();
}

bool COptItem::compile()
{
  std::string Bound;
  const CCopasiObject *pObject;

  if ((pObject = RootContainer.getObject(getObjectCN())) != NULL &&
      pObject->isValueDbl())
    mpObjectValue = (C_FLOAT64 *) pObject->getReference();

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
  else if ((pObject = RootContainer.getObject(Bound)) != NULL &&
           pObject->isValueDbl())
    mpLowerBound = (C_FLOAT64 *) pObject->getReference();
  else return false;

  if (getLowerRelation() == "<") mpLowerRel = less;
  else mpLowerRel = lessOrEqual;

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
  else if ((pObject = RootContainer.getObject(Bound)) != NULL &&
           pObject->isValueDbl())
    mpUpperBound = (C_FLOAT64 *) pObject->getReference();
  else return false;

  if (getUpperRelation() == "<") mpUpperRel = less;
  else mpUpperRel = lessOrEqual;

  return true;
}

C_INT32 COptItem::checkConstraint(const C_FLOAT64 & value)
{
  if (!mpLowerRel(*mpLowerBound, value)) return - 1;
  if (!mpUpperRel(value, *mpUpperBound)) return 1;
  return 0;
}

bool COptItem::checkLowerBound(const C_FLOAT64 & value)
{return mpLowerRel(*mpLowerBound, value);}

bool COptItem::checkUpperBound(const C_FLOAT64 & value)
{return mpUpperRel(value, *mpUpperBound);}

bool COptItem::less(const C_FLOAT64 & val1, const C_FLOAT64 & val2)
{return (val1 < val2);}

bool COptItem::lessOrEqual(const C_FLOAT64 & val1, const C_FLOAT64 & val2)
{return (val1 <= val2);}

C_FLOAT64 * COptItem::getObjectValue()
{return mpObjectValue;}

C_FLOAT64 * COptItem::getLowerBoundValue()
{return mpLowerBound;}

C_FLOAT64 * COptItem::getUpperBoundValue()
{return mpUpperBound;}
