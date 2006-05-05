/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperimentObjectMap.cpp,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/05/05 16:25:00 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <vector>
#include <limits>

#include "copasi.h"

#include "CExperimentObjectMap.h"
#include "utilities/utility.h"

CExperimentObjectMap::CExperimentObjectMap(const std::string & name,
    const CCopasiContainer * pParent):
    CCopasiParameterGroup(name, pParent),
    mObjects(0),
    mLastColumn(0)
{}

CExperimentObjectMap::CExperimentObjectMap(const CExperimentObjectMap & src,
    const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mObjects(src.mObjects),
    mLastColumn(src.mLastColumn)
{}

CExperimentObjectMap::CExperimentObjectMap(const CCopasiParameterGroup & group,
    const CCopasiContainer * pParent):
    CCopasiParameterGroup(group, pParent),
    mObjects(0),
    mLastColumn(0)
{}

CExperimentObjectMap::~CExperimentObjectMap() {}

bool CExperimentObjectMap::addObjectCN(const unsigned C_INT32 & index,
                                       const std::string & CN)
{
  std::string Index = StringPrint("%d", index);
  if (getParameter(Index)) return false;

  return addParameter(Index, CCopasiParameter::CN, (CCopasiObjectName) CN);
}

bool CExperimentObjectMap::removeObjectCN(const unsigned C_INT32 & index)
{return removeParameter(StringPrint("%d", index));}

bool CExperimentObjectMap::setObjectCN(const unsigned C_INT32 & index,
                                       const std::string & CN)
{
  CCopasiParameter * pParm = getParameter(StringPrint("%d", index));
  if (pParm)
    return pParm->setValue((CCopasiObjectName) CN);
  else
    return addObjectCN(index, CN);
}

std::string CExperimentObjectMap::getObjectCN(const unsigned C_INT32 & index) const
  {
    const CCopasiParameter * pParm = getParameter(StringPrint("%d", index));
    if (pParm)
      return *pParm->getValue().pCN;
    else
      return "";
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

  for (i = 0; i < imax; i++)
    {
      if ((pObject =
             CCopasiContainer::ObjectFromName(listOfContainer,
                                              *getValue(i).pCN)) != NULL &&
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
