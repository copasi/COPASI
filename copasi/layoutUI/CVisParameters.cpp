// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CVisParameters.cpp,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/10/06 15:51:45 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CVisParameters.h"

const C_FLOAT64 CVisParameters::EPSILON = 1.0E-15f;

C_INT16 CVisParameters::DEFAULT_NODE_SIZE = 40;

CVisParameters::CVisParameters()
{
  init();
}

void CVisParameters::init()
{
  mMinNodeSize = 10.0;
  mMaxNodeSize = 100.0;
  mStepsPerSecond = 10;
  mScalingMode = CVisParameters::INDIVIDUAL_SCALING;
  mMappingMode = CVisParameters::SIZE_DIAMETER_MODE;
  mAnimationRunning = false;
}
