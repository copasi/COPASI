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

/*!
    \file CArrow.h
    \brief Header file of class CArrow
 */

#ifndef ARROW_H_
#define ARROW_H_

#include "copasi/layout/CLBase.h"
#include "copasi/layout/CLCurve.h"

class CArrow
{
private:
  CLLineSegment line;
  CLPoint endPoint;
  C_FLOAT64 arrowLength;
  C_FLOAT64 arrowWidth;
public:
  CArrow() {endPoint = CLPoint(0.0, 0.0); arrowLength = 12.0; arrowWidth = 5.0;}
  CArrow(CLLineSegment l, C_FLOAT64 x, C_FLOAT64 y, C_FLOAT64 currentZoomFactor);

  CLPoint getStartOfLine() {return line.getStart();}
  CLPoint getEndOfLine() {return line.getEnd();}
  CLLineSegment getLine() {return line;}
  void setLine(CLLineSegment l) {line = l;}
  CLPoint getPoint() {return endPoint;}
  void setPoint(CLPoint p) {endPoint = p;}
  C_FLOAT64 getArrowWidth() {return arrowWidth;}
  C_FLOAT64 getArrowLength() {return arrowLength;}
  void scale(C_FLOAT64 zoomFactor);
private:
  void scaleHeadSize(C_FLOAT64 zoomFactor);
  void scalePosition(C_FLOAT64 zoomFactor);
};

#endif /*ARROW_H_*/
