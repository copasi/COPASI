// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLCurve.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/16 10:13:26 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CLCurve.h"

#include "sbml/layout/Curve.h"

CLCurve::CLCurve(const CLCurve & c)
    : CLBase(c),
    mCurveSegments(c.mCurveSegments)
{}

CLCurve::CLCurve(const Curve & sbmlcurve)
    : CLBase(sbmlcurve),
    mCurveSegments()
{
  //TODO
}

std::vector<CLLineSegment*> mCurveSegments;

CLCurve::~CLCurve()
{}

void CLCurve::addCurveSegment(CLLineSegment & ls)
{
  mCurveSegments.push_back(ls);
}
