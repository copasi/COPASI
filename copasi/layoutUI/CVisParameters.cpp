// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CVisParameters.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/08/31 10:57:41 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CVisParameters.h"

const C_INT16 CVisParameters::GLOBAL_SCALING = 0;
const C_INT16 CVisParameters::INDIVIDUAL_SCALING = 1;

const C_INT16 CVisParameters::COLOR_MODE = 0;
const C_INT16 CVisParameters::SIZE_DIAMETER_MODE = 1;
const C_INT16 CVisParameters::SIZE_AREA_MODE = 2;

CVisParameters::CVisParameters()
{
  init();
}

void CVisParameters::init()
{
  minNodeSize = 10.0;
  maxNodeSize = 100.0;
  //numberOfSteps = 0;
  stepsPerSecond = 10;
  scalingMode = CVisParameters::INDIVIDUAL_SCALING;
  mappingMode = CVisParameters::SIZE_DIAMETER_MODE;
  //mappingMode = CVisParameters::COLOR_MODE;
  animationRunning = false;
}
