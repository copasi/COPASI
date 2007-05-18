// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CVisParameters.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/05/18 10:13:51 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CVisParameters.h"

const C_INT16 CVisParameters::GLOBAL_SCALING = 0;
const C_INT16 CVisParameters::INDIVIDUAL_SCALING = 1;

CVisParameters::CVisParameters()
{
  //CVisParameters::init();
}

//void CVisParameters::init(){
C_FLOAT64 CVisParameters::minNodeSize = 10.0;
C_FLOAT64 CVisParameters::maxNodeSize = 100.0;
//}
