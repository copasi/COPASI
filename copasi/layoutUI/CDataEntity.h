// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CDataEntity.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/05/14 11:11:48 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CDATAENTITY_H
#define CDATAENTITY_H

#include <string>
#include <map>

#include "copasi.h"

class CDataEntity
  {
  private:
    C_FLOAT64 mTime;
    std::map<std::string, C_FLOAT64> mSpeciesValueMap;

  public:
    CDataEntity();
    CDataEntity(C_FLOAT64 t);

    void putValueForSpecies(std::string nodeKey, C_FLOAT64 value);
    C_FLOAT64 getValueForSpecies(std::string nodeKey);
  };
#endif
