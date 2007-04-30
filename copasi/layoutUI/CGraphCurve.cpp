// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CGraphCurve.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/04/30 11:00:56 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CGraphCurve.h"

CLGraphCurve::CLGraphCurve()
    : CLCurve()
{
  mKey = "";
  hasArrow = false;
}

CLGraphCurve::CLGraphCurve(const CLCurve & c)
    : CLCurve(c)
{}
