/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptItem.cpp,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/12 17:54:58 $
   End CVS Header */

#include <float.h>

#include "copasi.h"

#include "COptItem.h"
#include "report/CCopasiContainer.h"
#include "report/CCopasiObjectName.h"
#include "utilities/CCopasiParameterGroup.h"
#include "utilities/CCopasiMessage.h"
#include "utilities/utility.h"

COptItem::COptItem(const std::string & name,
                   const CCopasiContainer * pParent):
    CCopasiParameterGroup(name, pParent),
    mpParmObjectCN(NULL),
    mpParmLowerBound(NULL),
    mpParmUpperBound(NULL),
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

  mpMethod = NULL;
  mpObjectValue = NULL;
  if ((mpObject =
         CCopasiContainer::ObjectFromName(listOfContainer,
                                          getObjectCN())) != NULL &&
      mpObject->isValueDbl())
    mpObjectValue = (C_FLOAT64 *) mpObject->getReference();
  if (!mpObjectValue)
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
    mpLowerBound = (C_FLOAT64 *) mpLowerObject->getReference();
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
    mpUpperBound = (C_FLOAT64 *) mpUpperObject->getReference();
  if (!mpUpperBound)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 3, Bound.c_str());
      return false;
    }

  return true;
}

C_INT32 COptItem::checkConstraint() const
  {
    if (*mpLowerBound > *mpObjectValue) return - 1;
    if (*mpObjectValue > *mpUpperBound) return 1;
    return 0;
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

bool COptItem::less(const C_FLOAT64 & val1, const C_FLOAT64 & val2)
{return (val1 < val2);}

bool COptItem::lessOrEqual(const C_FLOAT64 & val1, const C_FLOAT64 & val2)
{return (val1 <= val2);}

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
