/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperimentObjectMap.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/09/23 19:12:16 $
   End CVS Header */

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

void CExperimentObjectMap::initializeParameter() {}

bool CExperimentObjectMap::addObject(const std::string & CN,
                                     const unsigned C_INT32 & column)
{
  std::string Column = StringPrint("%d", column);
  if (getParameter(Column)) return false;

  return addParameter(Column, CCopasiParameter::CN, CN);
}

bool CExperimentObjectMap::removeObject(const std::string & CN)
{
  unsigned C_INT32 i, imax = size();

  for (i = 0; i < imax; i++)
    if (*getValue(i).pCN == CN) break;

  if (i == imax) return false;

  return removeParameter(i);
}

bool CExperimentObjectMap::compile(const std::vector< CCopasiContainer * > listOfContainer)
{
  bool success = true;

  unsigned C_INT32 i, imax = size();
  unsigned C_INT32 Column;

  // We need to find out the size of the object map
  for (i = 0; i < imax; i++)
    {
      Column = strtoul(getName(i).c_str(), NULL, 0);
      if (mLastColumn < Column)
        mLastColumn = Column;
    }

  mObjects.resize(mLastColumn);
  mObjects = NULL;

  CCopasiObject * pObject = NULL;

  mLastColumn = 0;
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
