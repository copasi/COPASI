// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

#include <vector>
#include <limits>
#include <cmath>
#include <stdlib.h>

#include "copasi/copasi.h"

#include "CExperimentObjectMap.h"

#include "copasi/math/CMathContainer.h"
#include "copasi/utilities/utility.h"
#include "copasi/CopasiDataModel/CDataModel.h"

CExperimentObjectMap::CExperimentObjectMap(const std::string & name,
    const CDataContainer * pParent):
  CCopasiParameterGroup(name, pParent),
  mObjects(0),
  mLastColumn(0)
{initializeParameter();}

CExperimentObjectMap::CExperimentObjectMap(const CExperimentObjectMap & src,
    const CDataContainer * pParent):
  CCopasiParameterGroup(src, pParent),
  mObjects(src.mObjects),
  mLastColumn(src.mLastColumn)
{initializeParameter();}

CExperimentObjectMap::CExperimentObjectMap(const CCopasiParameterGroup & group,
    const CDataContainer * pParent):
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

  elements::iterator itColumn = beginIndex();
  elements::iterator endColumn = endIndex();

  if (itColumn != endColumn &&
      dynamic_cast< CCopasiParameterGroup * >(*itColumn) == NULL) // We have an old data format.
    {
      CCopasiParameterGroup New(getObjectName());

      for (; itColumn != endColumn; ++itColumn)
        {
          CCopasiParameterGroup * pGroup = New.assertGroup((*itColumn)->getObjectName());
          pGroup->assertParameter("Object CN", CCopasiParameter::Type::CN, (*itColumn)->getValue< CRegisteredCommonName >());
        }

      clear();
      operator=(New);
    }

  for (itColumn = beginIndex(); itColumn != endColumn; ++itColumn)
    if (((*itColumn) = elevate<CDataColumn, CCopasiParameterGroup>(*itColumn)) == NULL)
      success = false;

  return success;
}

const CExperimentObjectMap & CExperimentObjectMap::operator=(const CCopasiParameterGroup & rhs)
{
  if (static_cast< CCopasiParameterGroup * >(this) == &rhs) return * this;

  CCopasiParameterGroup::operator=(rhs);
  initializeParameter();

  return *this;
}

bool CExperimentObjectMap::setNumCols(const size_t & numCols)
{
  if (numCols == size())
    return true;

  // We only clear the vector of parameter. We do not destroy the parameter they are still
  // accessible through CDataContainer::mObjects and thus will be automatically destroyed.
  clear();

  bool success = true;

  for (size_t col = 0; col < numCols; col++)
    {
      CCopasiParameterGroup * pGrp = assertGroup(StringPrint("%d", col));

      // assertGroup() adds only newly created groups to mValue.pGROUP. We need to add the existing
      // ones.
      if (size() < col + 1)
        static_cast< elements * >(mpValue)->push_back(pGrp);

      success &= (elevate<CDataColumn, CCopasiParameterGroup>(pGrp) != NULL);
    }

  return success;
}

size_t CExperimentObjectMap::getLastNotIgnoredColumn() const
{
  elements::iterator itColumn = beginIndex();
  elements::iterator endColumn = endIndex();

  C_INT32 LastNotIgnored = -1;

  for (; itColumn != endColumn; ++itColumn)
    if (static_cast< CDataColumn * >(*itColumn)->getRole() != CExperiment::ignore)
      {
        C_INT32 index = strtol(static_cast< CDataColumn * >(*itColumn)->getObjectName().c_str(), NULL, 10);

        if (index > LastNotIgnored) LastNotIgnored = index;
      }

  return LastNotIgnored;
}

// virtual
const std::string & CExperimentObjectMap::getName(const size_t & index) const
{
  static const std::string NoName("");

  const CDataColumn * pColumn =
    dynamic_cast< const CDataColumn * >(getGroup(StringPrint("%d", index)));

  if (pColumn)
    return pColumn->getObjectName();
  else
    return NoName;
}

std::string CExperimentObjectMap::getNthCnOfType(size_t index, CExperiment::Type role) const
{
  size_t count = 0;

  for (size_t i = 0; i <= getLastColumn(); ++i)
    {
      CExperiment::Type r = getRole(i);

      if (r == role)
        if (count++ == index)
          return getObjectCN(i);
    }

  return std::string();
}

bool CExperimentObjectMap::setRole(const size_t & index,
                                   const CExperiment::Type & role)
{
  CDataColumn * pColumn =
    dynamic_cast< CDataColumn * >(getGroup(StringPrint("%d", index)));

  if (pColumn)
    return pColumn->setRole(role);
  else
    return false;
}

CExperiment::Type CExperimentObjectMap::getRole(const size_t & index) const
{
  const CDataColumn * pColumn =
    dynamic_cast< const CDataColumn * >(getGroup(StringPrint("%d", index)));

  if (pColumn)
    return pColumn->getRole();
  else
    return CExperiment::ignore;
}

bool CExperimentObjectMap::setObjectCN(const size_t & index,
                                       const std::string & CN)
{
  CDataColumn * pColumn =
    dynamic_cast< CDataColumn * >(getGroup(StringPrint("%d", index)));

  if (pColumn)
    return pColumn->setObjectCN((CCommonName) CN);
  else
    return false;
}

std::string CExperimentObjectMap::getObjectCN(const size_t & index) const
{
  const CDataColumn * pColumn =
    dynamic_cast< const CDataColumn * >(getGroup(StringPrint("%d", index)));

  if (pColumn)
    return pColumn->getObjectCN();
  else
    return "";
}

bool CExperimentObjectMap::setScale(const size_t & index,
                                    const C_FLOAT64 & weight)
{
  CDataColumn * pColumn =
    dynamic_cast< CDataColumn * >(getGroup(StringPrint("%d", index)));

  if (pColumn)
    return pColumn->setScale(weight);
  else
    return false;
}

C_FLOAT64 CExperimentObjectMap::getScale(const size_t & index) const
{
  const CDataColumn * pColumn =
    dynamic_cast< const CDataColumn * >(getGroup(StringPrint("%d", index)));

  if (pColumn)
    return pColumn->getScale();
  else
    return std::numeric_limits<C_FLOAT64>::quiet_NaN();
}

C_FLOAT64 CExperimentObjectMap::getDefaultScale(const size_t & index) const
{
  const CDataColumn * pColumn =
    dynamic_cast< const CDataColumn * >(getGroup(StringPrint("%d", index)));

  if (pColumn)
    return pColumn->getDefaultScale();
  else
    return std::numeric_limits<C_FLOAT64>::quiet_NaN();
}

bool CExperimentObjectMap::compile(const CMathContainer * pMathContainer)
{
  size_t i, imax = size();
  size_t Column;

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

  const CDataObject * pObject = NULL;
  std::string CN;

  for (i = 0; i < imax; i++)
    {
      if ((CN = getObjectCN(i)) == "") continue;

      if ((pObject = CObjectInterface::DataObject(pMathContainer->getObjectFromCN(CN))) != NULL &&
          pObject->hasFlag(CDataObject::ValueDbl))
        {
          Column = strtoul(getName(i).c_str(), NULL, 0);
          mObjects[Column] = pObject;
        }
      else
        return false;
    }

  return true;
}

const CVector< const CDataObject * > & CExperimentObjectMap::getDataObjects() const
{return mObjects;}

const size_t & CExperimentObjectMap::getLastColumn() const
{return mLastColumn;}

void CExperimentObjectMap::fixBuild55()
{
  CCopasiParameterGroup::index_iterator it = beginIndex();
  CCopasiParameterGroup::index_iterator end = endIndex();

  for (; it != end; ++it)
    {
      CDataColumn * pColumn = dynamic_cast< CDataColumn * >(*it);

      if (pColumn != NULL)
        {
          pColumn->fixBuild55();
        }
    }
}

CExperimentObjectMap::CDataColumn::CDataColumn(const std::string & name,
    const CDataContainer * pParent) :
  CCopasiParameterGroup(name, pParent),
  mpRole(NULL),
  mpObjectCN(NULL),
  mpScale(NULL)
{
  initializeParameter();
}

CExperimentObjectMap::CDataColumn::CDataColumn(const CDataColumn & src,
    const CDataContainer * pParent) :
  CCopasiParameterGroup(src, pParent),
  mpRole(NULL),
  mpObjectCN(NULL),
  mpScale(NULL)
{
  initializeParameter();
}

CExperimentObjectMap::CDataColumn::CDataColumn(const CCopasiParameterGroup & group,
    const CDataContainer * pParent) :
  CCopasiParameterGroup(group, pParent),
  mpRole(NULL),
  mpObjectCN(NULL),
  mpScale(NULL)
{
  initializeParameter();
}

CExperimentObjectMap::CDataColumn::~CDataColumn()
{}

void CExperimentObjectMap::CDataColumn::initializeParameter()
{
  mpRole = (CExperiment::Type *) assertParameter("Role", CCopasiParameter::Type::UINT, (unsigned C_INT32) CExperiment::ignore);

  CCopasiParameter * pParm = getParameter("Object CN");

  if (pParm != NULL)
    mpObjectCN = &pParm->getValue< CRegisteredCommonName >();

  pParm = getParameter("Weight");

  if (pParm != NULL)
    mpScale = &pParm->getValue< C_FLOAT64 >();

  elevateChildren();
}

CExperimentObjectMap::CDataColumn & CExperimentObjectMap::CDataColumn::operator = (const CExperimentObjectMap::CDataColumn & rhs)
{
  *mpRole = *rhs.mpRole;
  setObjectCN(rhs.getObjectCN());
  setScale(rhs.getScale());

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
          assertParameter("Object CN", CCopasiParameter::Type::CN, (CCommonName) objectCN);
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

bool CExperimentObjectMap::CDataColumn::setScale(const C_FLOAT64 & weight)
{
  if (std::isnan(weight))
    {
      if (mpScale != NULL)
        {
          removeParameter("Weight");
          mpScale = NULL;
        }

      return true;
    }

  C_FLOAT64 DefaultWeight = getDefaultScale();

  if (weight != DefaultWeight || std::isnan(DefaultWeight))
    {
      if (mpScale != NULL)
        *mpScale = weight;
      else
        mpScale = assertParameter("Weight", CCopasiParameter::Type::UDOUBLE, weight);

      return true;
    }

  if (mpScale != NULL)
    {
      removeParameter("Weight");
      mpScale = NULL;
    }

  return true;
}

C_FLOAT64 CExperimentObjectMap::CDataColumn::getScale() const
{
  if (mpScale == NULL)
    return getDefaultScale();
  else
    return *mpScale;
}

C_FLOAT64 CExperimentObjectMap::CDataColumn::getDefaultScale() const
{
  if (mpObjectCN == NULL)
    return std::numeric_limits<C_FLOAT64>::quiet_NaN();

  CCopasiParameterGroup *pGroup =
    dynamic_cast< CCopasiParameterGroup * >(getObjectParent());

  if (pGroup == NULL)
    return std::numeric_limits<C_FLOAT64>::quiet_NaN();

  const CExperiment *pExperiment =
    dynamic_cast<const CExperiment * >(pGroup->getObjectParent());

  if (pExperiment == NULL)
    return std::numeric_limits<C_FLOAT64>::quiet_NaN();

  CObjectInterface::ContainerList ListOfContainer;
  ListOfContainer.push_back(getObjectDataModel());

  const CDataObject * pObject = CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(ListOfContainer, *mpObjectCN));

  if (pObject == NULL)
    return std::numeric_limits<C_FLOAT64>::quiet_NaN();

  return pExperiment->getDefaultScale(pObject);
}

void CExperimentObjectMap::CDataColumn::fixBuild55()
{
  if (mpScale != NULL)
    {
      *mpScale *= *mpScale;
    }
}
