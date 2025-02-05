// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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

#include "CSimSummaryInfo.h"

CSimSummaryInfo::CSimSummaryInfo()
{
  mNumberOfSteps = 0;
  mNumberOfReactants = 0;
  mTotalTime = 0.0;
  mMaxOverallConcentration = 0.0;
}

CSimSummaryInfo::CSimSummaryInfo(size_t steps, size_t numReactants, C_FLOAT32 time)
{
  mNumberOfSteps = steps;
  mNumberOfReactants = numReactants;
  mTotalTime = time;
  mMaxOverallConcentration = 0.0;
}

void CSimSummaryInfo::storeMax(std::string ndKey, C_FLOAT64 maxR)
{
  maxMap.insert(std::pair<std::string, C_FLOAT64>
                (ndKey, maxR));
}

void CSimSummaryInfo::storeMin(std::string ndKey, C_FLOAT64 minR)
{
  minMap.insert(std::pair<std::string, C_FLOAT64>
                (ndKey, minR));
}

C_FLOAT64 CSimSummaryInfo::getMaxForSpecies(std::string ndKey)
{
  std::map<std::string, C_FLOAT64>::const_iterator iter = maxMap.find(ndKey);

  if (iter != maxMap.end())
    return (*iter).second;
  else
    return 0.0;
}

C_FLOAT64 CSimSummaryInfo::getMinForSpecies(std::string ndKey)
{
  std::map<std::string, C_FLOAT64>::const_iterator iter = minMap.find(ndKey);

  if (iter != minMap.end())
    return (*iter).second;
  else
    return 0.0;
}

std::ostream & operator<<(std::ostream &os, const CSimSummaryInfo & inf)
{
  os << "number of steps: " << inf.mNumberOfSteps << "\n";
  os << "number of reactants: " << inf.mNumberOfReactants << "\n";
  os << "total time: " << inf.mTotalTime << "\n";
  os << "maximum overall concentration: " << inf.mMaxOverallConcentration << "\n";
  os << "range  of values for species: " << "\n";

  std::map<std::string, C_FLOAT64>::const_iterator iter = inf.maxMap.begin();
  std::map<std::string, C_FLOAT64>::const_iterator iter2 = inf.minMap.begin();

  while ((iter != inf.maxMap.end()) && (iter2 != inf.minMap.end()))
    {
      os << " node: " << iter->first << " : [" << iter2->second;
      os << " - " << iter->second << "]" << "\n";
      iter2++;
      iter++;
    }

  return os;
}
