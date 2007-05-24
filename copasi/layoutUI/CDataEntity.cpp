// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CDataEntity.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/05/24 20:02:29 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <float.h>
#include <algorithm>

#include "CDataEntity.h"

CDataEntity::CDataEntity()
{
  mTime = 0.0;
}

CDataEntity::CDataEntity(C_FLOAT64 t)
{
  mTime = t;
}

CDataEntity::CDataEntity(const CDataEntity & cDat)
{
  mTime = cDat.mTime;
  //mSpeciesValueMap = std::map<std::string, C_FLOAT64> (cDat);
  //copy((cDat.mSpeciesValueMap).begin(),(cDat.mSpeciesValueMap).end(),mSpeciesValueMap.begin());
  mSpeciesValueMap.insert(cDat.mSpeciesValueMap.begin(), cDat.mSpeciesValueMap.end());
}

void CDataEntity::putValueForSpecies(std::string nodeKey, C_FLOAT64 value)
{
  mSpeciesValueMap.insert(std::pair<std::string, C_FLOAT64>
                          (nodeKey, value));
  //std::cout << "put: " << nodeKey << "  : " << value << "  into map" << std::endl;
}

// return concentration value for a certain reactant, specified by a key, returns -MAX C_FLOAT64, if key is not present in map
C_FLOAT64 CDataEntity::getValueForSpecies(std::string nodeKey)
{
  //std::cout << "look for key: " << nodeKey << std::endl;
  std::map<std::string, C_FLOAT64>::iterator it;
  //it = mSpeciesValueMap.begin();
  //std::cout << "first element: " << (*it).first << "  " << (*it).second << std::endl;
  it = mSpeciesValueMap.find(nodeKey);
  if (it != mSpeciesValueMap.end())
    return (*it).second;
  else
    return - DBL_MAX;
}
