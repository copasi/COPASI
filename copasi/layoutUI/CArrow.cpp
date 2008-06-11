// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CArrow.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/06/11 10:15:40 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*!
    \file CArrow.cpp
    \brief Implementation file of class CArrow
 */

#include "CArrow.h"
#include <iostream>

CArrow::CArrow(CLLineSegment l, C_FLOAT64 x, C_FLOAT64 y, C_FLOAT64 currentZoomFactor)
{
  line = l;
  endPoint = CLPoint(x, y);
  arrowLength = 12.0;
  arrowWidth = 5.0;
  scaleHeadSize(currentZoomFactor);
}

// scale line segment (curve) and end point, a curve (with basepoints) will not be scaled correctly
void CArrow::scale(C_FLOAT64 zoomFactor)
{
  this->scaleHeadSize(zoomFactor);
  this->scalePosition(zoomFactor);
}

void CArrow::scalePosition(C_FLOAT64 zoomFactor)
{
  this->line.scale(zoomFactor);
  this->endPoint.setX(this->endPoint.getX() * zoomFactor);
  this->endPoint.setY(this->endPoint.getY() * zoomFactor);
}

void CArrow::scaleHeadSize(C_FLOAT64 zoomFactor)
{
  this->arrowWidth *= zoomFactor;
  this->arrowLength *= zoomFactor;
}
