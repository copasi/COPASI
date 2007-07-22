// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CSimSummaryInfo.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/07/22 19:17:42 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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
    C_INT32 mNumberOfSteps;
    C_INT32 mNumberOfReactants;
    C_FLOAT64 mTotalTime;
    C_FLOAT64 mMaxOverallConcentration;

    std::map<std::string, C_FLOAT64> minMap; // contains the minimum value for each reactant
    std::map<std::string, C_FLOAT64> maxMap; // contains the maximum value for each reactant

  public:
    CSimSummaryInfo();
    CSimSummaryInfo(C_INT32 steps, C_INT32 numReactants, C_FLOAT32 time);

    C_FLOAT64 getTotalTime(){return this->mTotalTime;}
    C_INT32 getNumberOfSteps(){return this->mNumberOfSteps;}
    C_INT32 getNumberOfReactants(){return this->mNumberOfReactants;}

    C_FLOAT64 getMaxOverallConcentration(){return this->mMaxOverallConcentration;}
    C_FLOAT64 getMinOverallConcentration(){return 0.0;}
    void setMaxOverallConcentration(C_FLOAT64 max){this->mMaxOverallConcentration = max;}

    void storeMax(std::string ndKey, C_FLOAT64 maxR);
    void storeMin(std::string ndKey, C_FLOAT64 minR);

    C_FLOAT64 getMaxForSpecies(std::string ndKey);
    C_FLOAT64 getMinForSpecies(std::string ndKey);

    friend std::ostream & operator<<(std::ostream &os, const CSimSummaryInfo & inf);
  };

#endif
