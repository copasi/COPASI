// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CGraphNode.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/04/12 17:33:49 $
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

void CGraphNode::setSize(C_FLOAT64 newSize)
{
  this->msize = newSize;
  // now change corresponding end point(s) of attached curves)
  for (int i = 0;i < mConnectedCurves.size();i++)
    {
      std::cout << "number of segments: " << mConnectedCurves[i]->getNumCurveSegments() << std::endl;
      if ((mConnectedCurves[i]->getNumCurveSegments() > 0) && (mConnectedCurves[i]->getNumCurveSegments() < 10))
        {
          std::cout << "curve in node: " << *mConnectedCurves[i] << std::endl;
          CLLineSegment* plastSeg = mConnectedCurves[i]->getSegmentAt(mConnectedCurves[i]->getNumCurveSegments() - 1); // get pointer to last segment
          // move end point of segment along the line from the circle center(=from) to either the start point (line segment) or the second base point (bezier) (=to)
          // so that it lies on the border of the circle
          std::cout << "last segment: " << plastSeg << std::endl;
          CLPoint to;
          if (plastSeg->isBezier())
            to = plastSeg->getBase2();
          else
            to = plastSeg->getEnd();
          CLPoint from = CLPoint(this->getX(), this->getY());
          C_FLOAT64 distance = sqrt(((to.getX() - from.getX()) * (to.getX() - from.getX())) + ((to.getY() - from.getY()) * (to.getY() - from.getY())));
          plastSeg->setEnd(CLPoint(from.getX() + ((to.getX() - from.getX()) / distance * msize),
                                   from.getY() + ((to.getY() - from.getY()) / distance * msize)));
        }
      else
        std::cout << "broken pointer to node: " << morigNodeKey << std::endl;
    }
}
