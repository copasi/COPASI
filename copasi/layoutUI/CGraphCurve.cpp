// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CGraphCurve.cpp,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2008/01/31 13:58:42 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <algorithm>

#include "copasi.h"

#include "CGraphCurve.h"
#include "BezierCurve.h"
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
    {// exchange line segment and end point
      CLLineSegment lastSeg = mCurveSegments[mCurveSegments.size() - 1];
      CLPoint p = lastSeg.getEnd();
      if (lastSeg.isBezier())
        {
          BezierCurve *bezier = new BezierCurve();
          std::vector<CLPoint> pts = std::vector<CLPoint>();
          pts.push_back(lastSeg.getStart());
          pts.push_back(lastSeg.getBase1());
          pts.push_back(lastSeg.getBase2());
          pts.push_back(lastSeg.getEnd());
          std::vector<CLPoint> bezierPts = bezier->curvePts(pts);
          C_INT32 num = bezierPts.size();
          CLLineSegment segForArrow = CLLineSegment(bezierPts[num - 2], bezierPts[num - 1]);
          mArrow.setLine(segForArrow);
          mArrow.setPoint(CLPoint(bezierPts[num - 1].getX(), bezierPts[num - 1].getY()));
          //ar = new CArrow(segForArrow, bezierPts[num - 1].getX(), bezierPts[num - 1].getY(), this->currentZoom);
        }
      else
        {
          mArrow.setLine(lastSeg);
          mArrow.setPoint(CLPoint(p.getX(), p.getY()));
        }
      //ar = new CArrow(lastSeg, p.getX(), p.getY(), this->currentZoom);
    }
}
