// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CSimSummaryInfo.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/05/10 18:14:22 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CSIMSUMMARYINFO_H_
#define CSIMSUMMARYINFO_H_

#include <string>

#include "copasi.h"

class CSimSummaryInfo
  {
  private:
    C_INT32 mNumberOfSteps;
    C_FLOAT64 mTotalTime;

  public:
    CSimSummaryInfo();
  };

#endif
