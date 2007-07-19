// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CVisParameters.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/07/19 14:33:55 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CVISPARAMETERS_H
#define CVISPARAMETERS_H

#include "copasi.h"

class CVisParameters
  {
  public:
    static const C_INT16 GLOBAL_SCALING;
    static const C_INT16 INDIVIDUAL_SCALING;

    static C_FLOAT64 minNodeSize;
    static C_FLOAT64 maxNodeSize;

    static C_INT32 numberOfSteps;

    static C_INT16 stepsPerSecond;

    static bool animationRunning;

    CVisParameters();

    //static void init();
  };
#endif
