// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CArrow.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/03/02 10:56:33 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CArrow.h"

// scale line segment (curve) and end point, a curve (with basepoints will not be scaled correclty)
void CArrow::scale(C_FLOAT64 zoomFactor)
{
  this->arrowWidth *= zoomFactor;
  this->arrowLength *= zoomFactor;

  this->line.scale(zoomFactor);
  // scale start and end Point
  //  CLPoint p1 = this->line.getStart();
  //  CLPoint p2 = this->line.getEnd();
  //
  //  p1.setX(p1.getX() * zoomFactor);
  //  p1.setY(p1.getY() * zoomFactor);
  //  p2.setX(p2.getX() * zoomFactor);
  //  p2.setY(p2.getY() * zoomFactor);

  // now scale end point
  this->endPoint.setX(this->endPoint.getX() * zoomFactor);
  this->endPoint.setY(this->endPoint.getY() * zoomFactor);
}
