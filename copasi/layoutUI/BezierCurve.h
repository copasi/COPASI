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
    \file BezierCurve.h
    \brief Header file of class BezierCurve
 */

#ifndef CBEZIERCURVE_H
#define CBEZIERCURVE_H

#include "copasi/copasi.h"

#include <vector>

#include "copasi/layout/CLBase.h"

class BezierCurve
{
public:
  BezierCurve();
  BezierCurve(size_t numberOfStepsOnCurve);
  std::vector<CLPoint> curvePts(const std::vector<CLPoint>& pts);

private:
  C_FLOAT64 t;
  size_t steps;
  C_FLOAT64 dt;

  C_FLOAT64 bernstein(C_INT32 i, C_INT32 n, C_FLOAT64 t);
  CLPoint bezierPt(C_FLOAT64 t, std::vector<CLPoint> pts);
  C_FLOAT64 multiplyFromTo(C_INT32 n1, C_INT32 n2);
  void init();
};
#endif
