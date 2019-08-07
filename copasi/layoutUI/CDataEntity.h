// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CDATAENTITY_H
#define CDATAENTITY_H

#include <string>
#include <map>

#include "copasi/copasi.h"

class CDataEntity
{
private:
  C_FLOAT64 mTime;
  std::map<std::string, C_FLOAT64> mSpeciesValueMap;
  std::map<std::string, C_FLOAT64> mOrigValueMap;

public:
  CDataEntity();
  CDataEntity(C_FLOAT64 t);
  CDataEntity(const CDataEntity & src);

  void putValueForSpecies(std::string nodeKey, C_FLOAT64 value);
  void putOrigValueForSpecies(std::string nodeKey, C_FLOAT64 value);

  C_FLOAT64 getValueForSpecies(std::string nodeKey);
  C_FLOAT64 getOrigValueForSpecies(std::string nodeKey);
  size_t getNumberOfElements() {return mSpeciesValueMap.size();}
  C_FLOAT64 getTime() {return mTime;}
  friend std::ostream & operator<<(std::ostream &os, const CDataEntity & gn);
};
#endif
