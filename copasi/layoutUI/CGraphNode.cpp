// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CGraphNode.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/04/26 16:57:57 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <math.h>

#include "copasi.h"

#include "CGraphNode.h"
#include "layout/CLBase.h"

CGraphNode::CGraphNode(const std::string & name,
                       const CCopasiContainer * pParent)
    : CLMetabGlyph(name, pParent)
{
  msize = 20.0;
  morigNodeKey = "";
}

CGraphNode::CGraphNode(const CLMetabGlyph & src,
                       const CCopasiContainer * pParent)
    : CLMetabGlyph(src, pParent)
{
  msize = 20.0;
  morigNodeKey = src.getKey();
}

CGraphNode::CGraphNode(const CGraphNode & src,
                       const CCopasiContainer * pParent)
    : CLMetabGlyph(src, pParent)
{
  msize = src.msize;
  morigNodeKey = src.morigNodeKey;
}

void CGraphNode::setSize(C_FLOAT64 newSize, std::vector<CLCurve> *viewerCurves)
{
  this->msize = newSize;
  // now change corresponding end point(s) of attached curves)
  for (int i = 0;i < mConnectedCurveIndices.size();i++)
    {
      CLCurve *pCurve = &((*viewerCurves)[mConnectedCurveIndices[i]]);
      if (pCurve != NULL)
        {
          //std::cout << "curve in node: " << this->morigNodeKey << std::endl;
          CLLineSegment* pLastSeg = pCurve->getSegmentAt(pCurve->getNumCurveSegments() - 1); // get pointer to last segment
          // move end point of segment along the line from the circle center(=from) to either the start point (line segment) or the second base point (bezier) (=to)
          // so that it lies on the border of the circle
          //std::cout << "1. last segment: " << *pLastSeg << std::endl;
          CLPoint to;
          if (pLastSeg->isBezier())
            to = pLastSeg->getBase2();
          else
            to = pLastSeg->getEnd();
          CLPoint from = CLPoint(this->getX() + (this->getWidth() / 2.0), this->getY() + (this->getHeight() / 2.0)); // center of bounding box and also of circle
          C_FLOAT64 distance = sqrt(((to.getX() - from.getX()) * (to.getX() - from.getX())) + ((to.getY() - from.getY()) * (to.getY() - from.getY())));
          //std::cout << "distance: " << distance << "  size: " << msize << std::endl;
          pLastSeg->setEnd(CLPoint(from.getX() + ((to.getX() - from.getX()) / distance * msize / 2.0),
                                   from.getY() + ((to.getY() - from.getY()) / distance * msize / 2.0)));
          // std::cout << "2. last segment: " << *pLastSeg << std::endl;
        }
    }
}
void CGraphNode::adaptCurvesForRectangles(std::vector<CLCurve> *viewerCurves)
{
  for (int i = 0;i < mConnectedCurveIndices.size();i++)
    {
      CLCurve *pCurve = &((*viewerCurves)[mConnectedCurveIndices[i]]);
      if (pCurve != NULL)
        {
          // move end point of segment to the border of the bounding rectangle of the node
          CLLineSegment* pLastSeg = pCurve->getSegmentAt(pCurve->getNumCurveSegments() - 1); // get pointer to last segment
          CLPoint to = pLastSeg->getEnd();
          CLPoint pointOnRect = getPointOnRectangle(this->getBoundingBox(), pLastSeg->getEnd());
          pLastSeg->setEnd(pointOnRect);
        }
    }
}

// looks for the best point to make a line between a given point p and a rectangle r.
// The point to connect to should always lie on the border of the rectangle and, more specifically
// on the middle of one of the border lines
CLPoint CGraphNode::getPointOnRectangle(CLBoundingBox r, CLPoint p)
{
  CLPoint onpoint;
  CLPoint q = r.getPosition();
  q.setX(r.getPosition().getX() + r.getDimensions().getWidth()); // q is now top right point of rectangle
  CLPoint center; // center of rectangle
  center.setX(r.getPosition().getX() + (r.getDimensions().getWidth() / 2.0));
  center.setY(r.getPosition().getY() + (r.getDimensions().getHeight() / 2.0)); //

  C_FLOAT64 qAngle = atan((q.getY() - center.getY()) / (q.getX() - center.getX()));
  C_FLOAT64 pAngle = atan((p.getY() - center.getY()) / (p.getX() - center.getX()));

  //std::cout << "center: " << center << std::endl;
  //std::cout << "p: " << p << std::endl;
  //std::cout << "qangle: " << qAngle << "  pangle: " << pAngle << std::endl;

  if (fabs(pAngle) < fabs(qAngle))
    {// intersection point is left or right side
      if (p.getX() > center.getX()) // right side
        onpoint = CLPoint(q.getX(), center.getY());
      else // left side
        onpoint = CLPoint(r.getPosition().getX(), center.getY());
    }
  else
    {//intersection point is top or bottom side
      if (p.getY() > center.getY()) // top side
        onpoint = CLPoint(center.getX(), r.getPosition().getY() + r.getDimensions().getHeight());
      else // bottom side
        onpoint = CLPoint(center.getX(), r.getPosition().getY());
    }
  //std::cout << "onpoint: " << onpoint << std::endl;
  //std::cout << "-------------" << std::endl;
  return onpoint;
}

std::ostream & operator<<(std::ostream &os, const CGraphNode & gn)
{
  os << "node key: " << gn.morigNodeKey << "  size: " << gn.msize << std::endl;
  //for (int i=0;i<gn.mConnectedCurveIndices.size();i++)
  // os << gn.mConnectedCurveIndices[i] << std::endl;;

  return os;
}
