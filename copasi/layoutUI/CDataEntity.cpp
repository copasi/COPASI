// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CDataEntity.cpp,v $
//   $Revision: 1.15 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/04/23 21:10:43 $
// End CVS Header

// Copyright (C) 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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
  std::map<std::string, C_FLOAT64>::iterator it;

  it = mSpeciesValueMap.find(nodeKey);

  if (it != mSpeciesValueMap.end())
    return (*it).second;
  else
    return - std::numeric_limits< C_FLOAT64 >::max();
}

C_FLOAT64 CDataEntity::getOrigValueForSpecies(std::string nodeKey)
{
  std::map<std::string, C_FLOAT64>::iterator it;
  it = mOrigValueMap.find(nodeKey);

  if (it != mOrigValueMap.end())
    return (*it).second;
  else
    return - std::numeric_limits< C_FLOAT64 >::max();
}

std::ostream & operator<<(std::ostream &os, const CDataEntity & de)
{
  os << "time: " << de.mTime << "  size: " << std::endl;
  std::map<std::string, C_FLOAT64>::const_iterator it1;
  std::map<std::string, C_FLOAT64>::const_iterator it2;

  for (it1 = de.mSpeciesValueMap.begin() ; it1 != de.mSpeciesValueMap.end() ; it1++)
    {
      it2 = de.mOrigValueMap.find((*it1).first);

      if (it2 != de.mOrigValueMap.end())
        os << (*it1).first << "  : " << (*it1).second << "  orig: " << (*it2).second << std::endl;
      else
        os << (*it1).first << "  : " << (*it1).second << "  orig: not found" << std::endl;
    }

  //for (int i=0;i<gn.mConnectedCurveIndices.size();i++)
  // os << gn.mConnectedCurveIndices[i] << std::endl;;

  return os;
}
