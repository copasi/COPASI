/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperimentObjectMap.cpp,v $
  $Revision: 1.13.24.1 $
  $Name:  $
  $Author: gauges $
  $Date: 2008/11/06 08:06:19 $
  End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <vector>
#include <limits>
#include <math.h>

#include <stdlib.h>

#include "copasi.h"

#include "CExperimentObjectMap.h"

#include "utilities/utility.h"

CExperimentObjectMap::CExperimentObjectMap(const std::string & name,
    const CCopasiContainer * pParent):
    CCopasiParameterGroup(name, pParent),
    mObjects(0),
    mLastColumn(0)
{initializeParameter();}

CExperimentObjectMap::CExperimentObjectMap(const CExperimentObjectMap & src,
    const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mObjects(src.mObjects),
    mLastColumn(src.mLastColumn)
{initializeParameter();}

CExperimentObjectMap::CExperimentObjectMap(const CCopasiParameterGroup & group,
    const CCopasiContainer * pParent):
    CCopasiParameterGroup(group, pParent),
    mObjects(0),
    mLastColumn(0)
{initializeParameter();}

CExperimentObjectMap::~CExperimentObjectMap() {}

void CExperimentObjectMap::initializeParameter()
{
  elevateChildren();
}

bool CExperimentObjectMap::elevateChildren()
{
  bool success = true;

  std::vector<CCopasiParameter *>::iterator itColumn = mValue.pGROUP->begin();
  std::vector<CCopasiParameter *>::iterator endColumn = mValue.pGROUP->end();

  if (itColumn != endColumn &&
      dynamic_cast< CCopasiParameterGroup * >(*itColumn) == NULL) // We have an old data format.
    {
      CCopasiParameterGroup New(getObjectName());
      for (; itColumn != endColumn; ++itColumn)
        {
          CCopasiParameterGroup * pGroup = New.assertGroup((*itColumn)->getObjectName());
          pGroup->assertParameter("Object CN", CCopasiParameter::CN, *(*itColumn)->getValue().pCN);
        }

      clear();
      *this = New;
    }

  for (itColumn = mValue.pGROUP->begin(); itColumn != endColumn; ++itColumn)
    if (((*itColumn) = elevate<CDataColumn, CCopasiParameterGroup>(*itColumn)) == NULL)
      success = false;

  return success;
}

bool CExperimentObjectMap::setNumCols(const unsigned C_INT32 & numCols)
{
  if (numCols == mValue.pGROUP->size())
    return true;

  mValue.pGROUP->clear();

  bool success = true;

  for (unsigned C_INT32 col = 0; col < numCols; col++)
    success &= (elevate<CDataColumn, CCopasiParameterGroup>(assertGroup(StringPrint("%d", col))) != NULL);

  return success;
}

unsigned C_INT32 CExperimentObjectMap::getLastNotIgnoredColumn() const
  {
    std::vector<CCopasiParameter *>::iterator itColumn = mValue.pGROUP->begin();
    std::vector<CCopasiParameter *>::iterator endColumn = mValue.pGROUP->end();

    C_INT32 LastNotIgnored = -1;

    for (; itColumn != endColumn; ++itColumn)
      if (static_cast< CDataColumn * >(*itColumn)->getRole() != CExperiment::ignore)
        {
          C_INT32 index = strtol(static_cast< CDataColumn * >(*itColumn)->getObjectName().c_str(), NULL, 10);

          if (index > LastNotIgnored) LastNotIgnored = index;
        }

    return LastNotIgnored;
  }

bool CExperimentObjectMap::setRole(const unsigned C_INT32 & index,
                                   const CExperiment::Type & role)
{
  CDataColumn * pColumn =
    dynamic_cast< CDataColumn * >(getGroup(StringPrint("%d", index)));

  if (pColumn)
    return pColumn->setRole(role);
  else
    return false;
}

CExperiment::Type CExperimentObjectMap::getRole(const unsigned C_INT32 & index) const
  {
    const CDataColumn * pColumn =
      dynamic_cast< const CDataColumn * >(getGroup(StringPrint("%d", index)));

    if (pColumn)
      return pColumn->getRole();
    else
      return CExperiment::ignore;
  }

bool CExperimentObjectMap::setObjectCN(const unsigned C_INT32 & index,
                                       const std::string & CN)
{
  CDataColumn * pColumn =
    dynamic_cast< CDataColumn * >(getGroup(StringPrint("%d", index)));

  if (pColumn)
    return pColumn->setObjectCN((CCopasiObjectName) CN);
  else
    return false;
}

std::string CExperimentObjectMap::getObjectCN(const unsigned C_INT32 & index) const
  {
    const CDataColumn * pColumn =
      dynamic_cast< const CDataColumn * >(getGroup(StringPrint("%d", index)));

    if (pColumn)
      return pColumn->getObjectCN();
    else
      return "";
  }

bool CExperimentObjectMap::setWeight(const unsigned C_INT32 & index,
                                     const C_FLOAT64 & weight)
{
  CDataColumn * pColumn =
    dynamic_cast< CDataColumn * >(getGroup(StringPrint("%d", index)));

  if (pColumn)
    return pColumn->setWeight(weight);
  else
    return false;
}

C_FLOAT64 CExperimentObjectMap::getWeight(const unsigned C_INT32 & index) const
  {
    const CDataColumn * pColumn =
      dynamic_cast< const CDataColumn * >(getGroup(StringPrint("%d", index)));

    if (pColumn)
      return pColumn->getWeight();
    else
      return std::numeric_limits<C_FLOAT64>::quiet_NaN();
  }

C_FLOAT64 CExperimentObjectMap::getDefaultWeight(const unsigned C_INT32 & index) const
  {
    const CDataColumn * pColumn =
      dynamic_cast< const CDataColumn * >(getGroup(StringPrint("%d", index)));

    if (pColumn)
      return pColumn->getDefaultWeight();
    else
      return std::numeric_limits<C_FLOAT64>::quiet_NaN();
  }

bool CExperimentObjectMap::compile(const std::vector< CCopasiContainer * > listOfContainer)
{
  unsigned C_INT32 i, imax = size();
  unsigned C_INT32 Column;

  // We need to find out the size of the object map
  if (imax == 0)
    mLastColumn = C_INVALID_INDEX;
  else
    {
      mLastColumn = strtoul(getName(0).c_str(), NULL, 0);

      for (i = 1; i < imax; i++)
        {
          Column = strtoul(getName(i).c_str(), NULL, 0);
          if (mLastColumn < Column)
            mLastColumn = Column;
        }
    }

  mObjects.resize(mLastColumn + 1);
  mObjects = NULL;

  CCopasiObject * pObject = NULL;
  std::string CN;
  for (i = 0; i < imax; i++)
    {
      if ((CN = getObjectCN(i)) == "") continue;

      if ((pObject =
             CCopasiContainer::ObjectFromName(listOfContainer, CN)) != NULL &&
          pObject->isValueDbl())
        {
          Column = strtoul(getName(i).c_str(), NULL, 0);
          mObjects[Column] = pObject;
        }
      else
        return false;
    }

  return true;
}

const CVector< CCopasiObject * > & CExperimentObjectMap::getMappedObjects() const
{return mObjects;}

const unsigned C_INT32 & CExperimentObjectMap::getLastColumn() const
  {return mLastColumn;}

CExperimentObjectMap::CDataColumn::CDataColumn(const std::string & name,
    const CCopasiContainer * pParent) :
    CCopasiParameterGroup(name, pParent),
    mpRole(NULL),
    mpObjectCN(NULL),
    mpWeight(NULL)
{
  initializeParameter();
}

CExperimentObjectMap::CDataColumn::CDataColumn(const CDataColumn & src,
    const CCopasiContainer * pParent) :
    CCopasiParameterGroup(src, pParent),
    mpRole(NULL),
    mpObjectCN(NULL),
    mpWeight(NULL)
{
  initializeParameter();
}

CExperimentObjectMap::CDataColumn::CDataColumn(const CCopasiParameterGroup & group,
    const CCopasiContainer * pParent) :
    CCopasiParameterGroup(group, pParent),
    mpRole(NULL),
    mpObjectCN(NULL),
    mpWeight(NULL)
{
  initializeParameter();
}

CExperimentObjectMap::CDataColumn::~CDataColumn()
{}

void CExperimentObjectMap::CDataColumn::initializeParameter()
{
  mpRole = (CExperiment::Type *)
           assertParameter("Role", CCopasiParameter::UINT, (unsigned C_INT32) CExperiment::ignore)->getValue().pUINT;

  CCopasiParameter * pParm = getParameter("Object CN");
  if (pParm != NULL)
    mpObjectCN = pParm->getValue().pCN;

  pParm = getParameter("Weight");
  if (pParm != NULL)
    mpWeight = pParm->getValue().pUDOUBLE;

  elevateChildren();
}

CExperimentObjectMap::CDataColumn & CExperimentObjectMap::CDataColumn::operator = (const CExperimentObjectMap::CDataColumn & rhs)
{
  *mpRole = *rhs.mpRole;
  setObjectCN(rhs.getObjectCN());
  setWeight(rhs.getWeight());

  return *this;
}

bool CExperimentObjectMap::CDataColumn::elevateChildren()
{return true;}

bool CExperimentObjectMap::CDataColumn::setRole(const CExperiment::Type & role)
{
  *mpRole = role;
  return true;
}

const CExperiment::Type & CExperimentObjectMap::CDataColumn::getRole() const
  {return *mpRole;}

bool CExperimentObjectMap::CDataColumn::setObjectCN(const std::string & objectCN)
{
  if (objectCN == "")
    {
      if (mpObjectCN != NULL)
        {
          removeParameter("Object CN");
          mpObjectCN = NULL;
        }
    }
  else
    {
      if (mpObjectCN != NULL)
        *mpObjectCN = objectCN;
      else
        mpObjectCN =
          assertParameter("Object CN", CCopasiParameter::CN, (CCopasiObjectName) objectCN)->getValue().pCN;
    }

  return true;
}

std::string CExperimentObjectMap::CDataColumn::getObjectCN() const
  {
    if (mpObjectCN != NULL)
      return *mpObjectCN;
    else
      return "";
  }

bool CExperimentObjectMap::CDataColumn::setWeight(const C_FLOAT64 & weight)
{
  if (isnan(weight))
    {
      if (mpWeight != NULL)
        {
          removeParameter("Weight");
          mpWeight = NULL;
        }
      return true;
    }

  C_FLOAT64 DefaultWeight = getDefaultWeight();
  if (weight != DefaultWeight || isnan(DefaultWeight))
    {
      if (mpWeight != NULL)
        *mpWeight = weight;
      else
        mpWeight = assertParameter("Weight", CCopasiParameter::UDOUBLE, weight)->getValue().pUDOUBLE;

      return true;
    }

  if (mpWeight != NULL)
    removeParameter("Weight");

  return true;
}

C_FLOAT64 CExperimentObjectMap::CDataColumn::getWeight() const
  {
    if (mpWeight == NULL)
      return getDefaultWeight();
    else
      return *mpWeight;
  }

C_FLOAT64 CExperimentObjectMap::CDataColumn::getDefaultWeight() const
  {
    if (mpObjectCN == NULL)
      return std::numeric_limits<C_FLOAT64>::quiet_NaN();

    CCopasiParameterGroup *pGroup =
      dynamic_cast< CCopasiParameterGroup * >(getObjectParent());
    if (pGroup == NULL)
      return std::numeric_limits<C_FLOAT64>::quiet_NaN();

    CExperiment *pExperiment =
      dynamic_cast< CExperiment * >(pGroup->getObjectParent());
    if (pExperiment == NULL)
      return std::numeric_limits<C_FLOAT64>::quiet_NaN();

    CCopasiObject * pObject = CCopasiContainer::ObjectFromName(*mpObjectCN);
    if (pObject == NULL)
      return std::numeric_limits<C_FLOAT64>::quiet_NaN();

    return pExperiment->getDefaultWeight(pObject);
  }
