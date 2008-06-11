// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/BezierCurve.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/06/11 10:14:14 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*!
    \file BezierCurve.h
    \brief Header file of class BezierCurve
 */

#ifndef CBEZIERCURVE_H
#define CBEZIERCURVE_H

#include "copasi.h"

#include <vector>

#include "copasi/layout/CLBase.h"

class BezierCurve
  {
  public:
    BezierCurve();
    BezierCurve(C_INT32 numberOfStepsOnCurve);
    std::vector<CLPoint> curvePts(const std::vector<CLPoint>& pts);

  private:
    C_FLOAT64 t;
    C_INT32 steps;
    C_FLOAT64 dt;

    C_FLOAT64 bernstein(C_INT32 i, C_INT32 n, C_FLOAT64 t);
    CLPoint bezierPt(C_FLOAT64 t, std::vector<CLPoint> pts);
    C_FLOAT64 multiplyFromTo(C_INT32 n1, C_INT32 n2);
    void init();
  };
#endif
