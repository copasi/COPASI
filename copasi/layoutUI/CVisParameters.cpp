// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CVisParameters.cpp,v $
//   $Revision: 1.11 $
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

#include "CVisParameters.h"

const C_FLOAT64 CVisParameters::EPSILON = 1.0E-15f;

const C_INT16 CVisParameters::GLOBAL_SCALING = 0;
const C_INT16 CVisParameters::INDIVIDUAL_SCALING = 1;

const C_INT16 CVisParameters::COLOR_MODE = 0;
const C_INT16 CVisParameters::SIZE_DIAMETER_MODE = 1;
const C_INT16 CVisParameters::SIZE_AREA_MODE = 2;

C_INT16 CVisParameters::DEFAULT_NODE_SIZE = 20;

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
