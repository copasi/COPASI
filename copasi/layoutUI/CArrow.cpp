// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CArrow.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/02/22 17:30:44 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CArrow.h"

// scale line segment (curve) and end point, a curve (with basepoints will not be scaled correclty)
void arrow::zoom(C_FLOAT64 zoomFactor)
{
  this->arrowWidth *= zoomFactor;
  this->arrowLength *= zoomFactor;

  // scale start and end Point
  CLPoint p1 = this->line.getStart();
  CLPoint p2 = this->line.getEnd();

  p1.setX(p1.getX() * zoomFactor);
  p1.setY(p1.getY() * zoomFactor);
  p2.setX(p2.getX() * zoomFactor);
  p2.setY(p2.getY() * zoomFactor);

  // now scale end point
  this->endPoint.setX(this->endPoint.getX() * zoomFactor);
  this->endPoint.setY(this->endPoint.getY() * zoomFactor);
}
