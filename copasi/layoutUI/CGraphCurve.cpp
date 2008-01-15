// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CGraphCurve.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2008/01/15 09:51:40 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CGraphCurve.h"

CGraphCurve::CGraphCurve()
    : CLCurve()
{
  mHasArrow = false;
}

CGraphCurve::CGraphCurve(const CLCurve & c)
    : CLCurve(c)
{
  mHasArrow = false;
}

CGraphCurve::CGraphCurve(const CGraphCurve & c)
    : CLCurve(c)
{
  mHasArrow = c.mHasArrow;
  mArrow = c.mArrow;
  mRole = c.mRole;
}

void CGraphCurve::scale (const double & scaleFactor)
{
  unsigned int i; // scale all segments
  for (i = 0;i < mCurveSegments.size();i++)
    {
      mCurveSegments[i].scale(scaleFactor);
    }

  if (mHasArrow)
    mArrow.scale(scaleFactor);
}

void CGraphCurve::invertOrderOfPoints()
{
  std::cout << " invertOrderOfPoints for " << mCurveSegments.size() << " segments" << std::endl;
  unsigned int i; // invert order of points in each segment
  CLPoint h; // puffer variable
  for (i = 0;i < mCurveSegments.size();i++)
    {
      h = mCurveSegments[i].getStart();
      mCurveSegments[i].setStart(mCurveSegments[i].getEnd());
      mCurveSegments[i].setEnd(h);
      if (mCurveSegments[i].isBezier())
        {
          h = mCurveSegments[i].getBase1();
          mCurveSegments[i].setBase1(mCurveSegments[i].getBase2());
          mCurveSegments[i].setBase2(h);
        }
    }

  // now invert order of segments
  reverse(mCurveSegments.begin(), mCurveSegments.end());

  if (mHasArrow)
  {} //???}
