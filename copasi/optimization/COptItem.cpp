/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptItem.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/21 20:34:20 $
   End CVS Header */

#include <float.h>

#include "copasi.h"

#include "COptItem.h"
#include "report/CCopasiContainer.h"
#include "report/CCopasiObjectName.h"
#include "utilities/CCopasiParameterGroup.h"
#include "utilities/CCopasiMessage.h"
#include "utilities/utility.h"

COptItem::COptItem(CCopasiParameterGroup & group) :
    mpGroup(&group),
    mpMethod(NULL),
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
    mpMethod(src.mpMethod),
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

bool COptItem::initialize(const CCopasiObjectName & objectCN)
{
  mpGroup->clear();

  mpGroup->addParameter("ObjectCN", CCopasiParameter::CN, (CCopasiObjectName) objectCN);
  mpGroup->addParameter("LowerBound", CCopasiParameter::CN, (CCopasiObjectName) "-inf");
  mpGroup->addParameter("LowerRelation", CCopasiParameter::STRING, (std::string) "<=");
  mpGroup->addParameter("UpperBound", CCopasiParameter::CN, (CCopasiObjectName) "inf");
  mpGroup->addParameter("UpperRelation", CCopasiParameter::STRING, (std::string) "<=");

  return isValid();
}

bool COptItem::setObjectCN(const CCopasiObjectName & objectCN)
{
  const CCopasiObject * pObject = RootContainer.getObject(objectCN);
  if (pObject == NULL || !pObject->isValueDbl())
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 1, objectCN.c_str());
      return false;
    }

  return mpGroup->setValue(0, objectCN);
}

const CCopasiObjectName COptItem::getObjectCN() const
  {return * mpGroup->getValue(0).pCN;}

bool COptItem::setLowerBound(const CCopasiObjectName & lowerBound)
{
  const CCopasiObject * pObject;

  if (lowerBound != "-inf" &&
      !isNumber(lowerBound) &&
      ((pObject = RootContainer.getObject(lowerBound)) == NULL ||
       !pObject->isValueDbl()))
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 2, lowerBound.c_str());
      return false;
    }

  return mpGroup->setValue(1, lowerBound);
}

const std::string COptItem::getLowerBound() const
  {return * mpGroup->getValue(1).pCN;}

bool COptItem::setLowerRelation(const std::string & lowerRel)
{
  if (lowerRel != "<" && lowerRel != "<=")
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 4, lowerRel.c_str());
      return false;
    }

  return mpGroup->setValue(2, lowerRel);
}

const std::string COptItem::getLowerRelation() const
  {return * mpGroup->getValue(2).pSTRING;}

bool COptItem::setUpperBound(const CCopasiObjectName & upperBound)
{
  const CCopasiObject * pObject;

  if (upperBound != "inf" &&
      !isNumber(upperBound) &&
      ((pObject = RootContainer.getObject(upperBound)) == NULL ||
       !pObject->isValueDbl()))
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 3, upperBound.c_str());
      return false;
    }

  return mpGroup->setValue(3, upperBound);
}

const std::string COptItem::getUpperBound() const
  {return * mpGroup->getValue(3).pCN;}

bool COptItem::setUpperRelation(const std::string & upperRel)
{
  if (upperRel != "<" && upperRel != "<=")
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 4, upperRel.c_str());
      return false;
    }

  return mpGroup->setValue(4, upperRel);
}

const std::string COptItem::getUpperRelation() const
  {return * mpGroup->getValue(4).pSTRING;}

UpdateMethod * COptItem::getUpdateMethod() const
  {return mpMethod;}

bool COptItem::isValid() const
  {
    CCopasiParameter * pParameter;

    pParameter = (CCopasiParameter *) mpGroup->getParameter(0);
    if (!pParameter || pParameter->getObjectName() != "ObjectCN") return false;

    pParameter = (CCopasiParameter *) mpGroup->getParameter(1);
    if (!pParameter || pParameter->getObjectName() != "LowerBound") return false;

    pParameter = (CCopasiParameter *) mpGroup->getParameter(2);
    if (!pParameter || pParameter->getObjectName() != "LowerRelation") return false;

    pParameter = (CCopasiParameter *) mpGroup->getParameter(3);
    if (!pParameter || pParameter->getObjectName() != "UpperBound") return false;

    pParameter = (CCopasiParameter *) mpGroup->getParameter(4);
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

bool COptItem::compile(const std::vector< CCopasiContainer * > listOfContainer)
{
  std::string Bound;
  const CCopasiObject *pObject;

  mpMethod = NULL;
  mpObjectValue = NULL;
  if ((pObject =
         CCopasiContainer::ObjectFromName(listOfContainer,
                                          getObjectCN())) != NULL &&
      pObject->isValueDbl())
    mpObjectValue = (C_FLOAT64 *) pObject->getReference();
  if (!mpObjectValue)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 1, getObjectCN().c_str());
      return false;
    }
  mpMethod = pObject->getUpdateMethod();

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
  else if ((pObject =
              CCopasiContainer::ObjectFromName(listOfContainer,
                                               Bound)) != NULL &&
           pObject->isValueDbl())
    mpLowerBound = (C_FLOAT64 *) pObject->getReference();
  if (!mpLowerBound) return false;
  {
    CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 2, Bound.c_str());
    return false;
  }

  if (getLowerRelation() == "<") mpLowerRel = less;
  else mpLowerRel = lessOrEqual;

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
  else if ((pObject =
              CCopasiContainer::ObjectFromName(listOfContainer,
                                               Bound)) != NULL &&
           pObject->isValueDbl())
    mpUpperBound = (C_FLOAT64 *) pObject->getReference();
  if (!mpUpperBound)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 3, Bound.c_str());
      return false;
    }

  if (getUpperRelation() == "<") mpUpperRel = less;
  else mpUpperRel = lessOrEqual;

  return true;
}

C_INT32 COptItem::checkConstraint() const
  {
    if (!mpLowerRel(*mpLowerBound, *mpObjectValue)) return - 1;
    if (!mpUpperRel(*mpObjectValue, *mpUpperBound)) return 1;
    return 0;
  }

C_INT32 COptItem::checkConstraint(const C_FLOAT64 & value) const
  {
    if (!mpLowerRel(*mpLowerBound, value)) return - 1;
    if (!mpUpperRel(value, *mpUpperBound)) return 1;
    return 0;
  }

bool COptItem::checkLowerBound(const C_FLOAT64 & value) const
{return mpLowerRel(*mpLowerBound, value);}

bool COptItem::checkUpperBound(const C_FLOAT64 & value) const
  {return mpUpperRel(value, *mpUpperBound);}

bool COptItem::less(const C_FLOAT64 & val1, const C_FLOAT64 & val2)
{return (val1 < val2);}

bool COptItem::lessOrEqual(const C_FLOAT64 & val1, const C_FLOAT64 & val2)
{return (val1 <= val2);}

const C_FLOAT64 * COptItem::getObjectValue() const
  {return mpObjectValue;}
