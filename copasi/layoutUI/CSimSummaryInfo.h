// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CSimSummaryInfo.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:29:16 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CSIMSUMMARYINFO_H_
#define CSIMSUMMARYINFO_H_

#include <string>
#include <map>

#include "copasi.h"

class CSimSummaryInfo
{
private:
  size_t mNumberOfSteps;
  size_t mNumberOfReactants;
  C_FLOAT64 mTotalTime;
  C_FLOAT64 mMaxOverallConcentration;

  std::map<std::string, C_FLOAT64> minMap; // contains the minimum value for each reactant
  std::map<std::string, C_FLOAT64> maxMap; // contains the maximum value for each reactant

public:
  CSimSummaryInfo();
  CSimSummaryInfo(size_t steps, size_t numReactants, C_FLOAT32 time);

  C_FLOAT64 getTotalTime() {return this->mTotalTime;}
  size_t getNumberOfSteps() {return this->mNumberOfSteps;}
  size_t getNumberOfReactants() {return this->mNumberOfReactants;}

  C_FLOAT64 getMaxOverallConcentration() {return this->mMaxOverallConcentration;}
  C_FLOAT64 getMinOverallConcentration() {return 0.0;}
  void setMaxOverallConcentration(C_FLOAT64 max) {this->mMaxOverallConcentration = max;}

  void storeMax(std::string ndKey, C_FLOAT64 maxR);
  void storeMin(std::string ndKey, C_FLOAT64 minR);

  C_FLOAT64 getMaxForSpecies(std::string ndKey);
  C_FLOAT64 getMinForSpecies(std::string ndKey);

  friend std::ostream & operator<<(std::ostream &os, const CSimSummaryInfo & inf);
};

#endif
