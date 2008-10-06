// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CVisParameters.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/10/06 15:51:46 $
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

    static C_INT16 DEFAULT_NODE_SIZE;

    enum SCALING_MODE
    {
      GLOBAL_SCALING,
      INDIVIDUAL_SCALING
    };

    enum MAPPING_MODE
    {
      COLOR_MODE,
      SIZE_DIAMETER_MODE,
      SIZE_AREA_MODE
    };

    double mMinNodeSize;
    double mMaxNodeSize;

    int mStepsPerSecond;

    SCALING_MODE mScalingMode;

    MAPPING_MODE mMappingMode;

    bool mAnimationRunning;

    CVisParameters();

  private:
    void init();

    //static void init();
  };
#endif
