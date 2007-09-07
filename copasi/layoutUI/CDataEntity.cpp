// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CDataEntity.cpp,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/09/07 16:12:24 $
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

CDataEntity::CDataEntity(const CDataEntity & src):
    mTime(src.mTime),
    mSpeciesValueMap(src.mSpeciesValueMap),
    mOrigValueMap(src.mOrigValueMap)
{}

void CDataEntity::putValueForSpecies(std::string nodeKey, C_FLOAT64 value)
{
  mSpeciesValueMap.erase(nodeKey); // delete old value
  mSpeciesValueMap.insert(std::pair<std::string, C_FLOAT64>
                          (nodeKey, value));
  //std::cout << "put: " << nodeKey << "  : " << value << "  into map" << std::endl;
}

void CDataEntity::putOrigValueForSpecies(std::string nodeKey, C_FLOAT64 value)
{
  mOrigValueMap.erase(nodeKey); // delete old value
  mOrigValueMap.insert(std::pair<std::string, C_FLOAT64>
                       (nodeKey, value));
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

C_FLOAT64 CDataEntity::getOrigValueForSpecies(std::string nodeKey)
{
  std::map<std::string, C_FLOAT64>::iterator it;
  it = mOrigValueMap.find(nodeKey);
  if (it != mOrigValueMap.end())
    return (*it).second;
  else
    return - DBL_MAX;
}
