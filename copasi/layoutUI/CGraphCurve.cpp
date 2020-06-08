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

#include <algorithm>

#include "copasi/copasi.h"

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

void CGraphCurve::scale(const double & scaleFactor)
{
  unsigned int i; // scale all segments

  for (i = 0; i < mvCurveSegments.size(); i++)
    {
      mvCurveSegments[i].scale(scaleFactor);
    }

  if (mHasArrow)
    mArrow.scale(scaleFactor);
}

void CGraphCurve::invertOrderOfPoints()
{
  unsigned int i; // invert order of points in each segment
  CLPoint h; // puffer variable

  for (i = 0; i < mvCurveSegments.size(); i++)
    {
      h = mvCurveSegments[i].getStart();
      mvCurveSegments[i].setStart(mvCurveSegments[i].getEnd());
      mvCurveSegments[i].setEnd(h);

      if (mvCurveSegments[i].isBezier())
        {
          h = mvCurveSegments[i].getBase1();
          mvCurveSegments[i].setBase1(mvCurveSegments[i].getBase2());
          mvCurveSegments[i].setBase2(h);
        }
    }

  // now invert order of segments
  std::reverse(mvCurveSegments.begin(), mvCurveSegments.end());

  if (mHasArrow)
    {
      // exchange line segment and end point
      CLLineSegment lastSeg = mvCurveSegments[mvCurveSegments.size() - 1];
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
          size_t num = bezierPts.size();
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
