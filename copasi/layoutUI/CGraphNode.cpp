// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CGraphNode.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/04/13 10:04:43 $
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
          std::cout << "distance: " << distance << "  size: " << msize << std::endl;
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

          //pLastSeg->setEnd(CLPoint());
        }
    }
}

std::ostream & operator<<(std::ostream &os, const CGraphNode & gn)
{
  os << "node key: " << gn.morigNodeKey << "  size: " << gn.msize << std::endl;
  //for (int i=0;i<gn.mConnectedCurveIndices.size();i++)
  // os << gn.mConnectedCurveIndices[i] << std::endl;;

  return os;
}
