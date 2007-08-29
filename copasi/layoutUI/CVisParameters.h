// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CVisParameters.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/08/29 17:34:57 $
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

    C_FLOAT64 minNodeSize;
    C_FLOAT64 maxNodeSize;

    //C_INT32 numberOfSteps;

    C_INT16 stepsPerSecond;

    C_INT16 scalingMode;

    bool animationRunning;

    CVisParameters();

  private:
    void init();

    //static void init();
  };
#endif
