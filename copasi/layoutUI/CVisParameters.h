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

#ifndef CVISPARAMETERS_H
#define CVISPARAMETERS_H

#include "copasi/copasi.h"

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
