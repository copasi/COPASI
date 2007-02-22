// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CArrow.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/02/22 17:30:44 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef ARROW_H_
#define ARROW_H_

#include "layout/CLBase.h"
#include "layout/CLCurve.h"

class arrow
  {
  private:
    CLLineSegment line;
    CLPoint endPoint;
    C_FLOAT64 arrowLength;
    C_FLOAT64 arrowWidth;
  public:
    arrow(){endPoint = CLPoint(0.0, 0.0);arrowLength = 20.0; arrowWidth = 10.0;}
    arrow(CLLineSegment l, C_FLOAT64 x, C_FLOAT64 y)
    {
      line = l;
      endPoint = CLPoint(x, y);
      arrowLength = 20.0;
      arrowWidth = 10.0;
    }

    CLPoint getStartOfLine() {return line.getStart();}
    CLPoint getEndOfLine() {return line.getEnd();}
    C_FLOAT64 getArrowWidth(){return arrowWidth;}
    C_FLOAT64 getArrowLength(){return arrowLength;}
    void zoom(C_FLOAT64 zoomFactor);
  };

#endif /*ARROW_H_*/
