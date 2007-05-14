// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CDataEntity.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/05/14 09:51:14 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CDataEntity.h"

CDataEntity::CDataEntity()
{
  mTime = 0.0;
}

CDataEntity::CDataEntity(C_FLOAT64 t)
{
  mTime = t;
}

void CDataEntity::putValueForSpecies(std::string nodeKey, C_FLOAT64 value)
{
  mSpeciesValueMap.insert(std::pair<std::string, C_FLOAT64>
                          (nodeKey, value));
}
