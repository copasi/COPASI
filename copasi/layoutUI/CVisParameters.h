// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CVisParameters.h,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2008/04/14 10:24:03 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CVISPARAMETERS_H
#define CVISPARAMETERS_H

#include "copasi.h"

class CVisParameters
  {
  public:
    static const C_FLOAT64 EPSILON;

    static const C_INT16 GLOBAL_SCALING;
    static const C_INT16 INDIVIDUAL_SCALING;

    static const C_INT16 COLOR_MODE;
    static const C_INT16 SIZE_DIAMETER_MODE;
    static const C_INT16 SIZE_AREA_MODE;

    static C_INT16 DEFAULT_NODE_SIZE;

    C_FLOAT64 minNodeSize;
    C_FLOAT64 maxNodeSize;

    //C_INT32 numberOfSteps;

    C_INT16 stepsPerSecond;

    C_INT16 scalingMode;

    C_INT16 mappingMode;

    bool animationRunning;

    CVisParameters();

  private:
    void init();

    //static void init();
  };
#endif
