// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/BezierCurve.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/09/13 17:37:43 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <math.h>

#include "BezierCurve.h"

BezierCurve::BezierCurve()
{
  init();
}

BezierCurve::BezierCurve(C_INT32 numberOfStepsOnCurve)
{
  steps = numberOfStepsOnCurve;
  t = 1.0 / steps;
}

void BezierCurve::init()
{
  steps = 100;
  dt = 0.01;
}

std::vector<CLPoint> BezierCurve::curvePts(const std::vector<CLPoint>& pts)
{
  C_FLOAT64 x;
  C_FLOAT64 y;
  std::vector<CLPoint>points;
  points = std::vector<CLPoint>();

  C_FLOAT64 t = this->dt;

  C_INT32 i;
  C_INT32 n = pts.size() - 1;
  C_INT32 count;
  for (count = 1; count < this->steps;count++)
    {
      x = 0.0;
      y = 0.0;
      for (i = 0;i <= n;i++)
        {
          x += bernstein(i, n, t) * pts[i].getX();
          y += bernstein(i, n, t) * pts[i].getY();
        }
      points.push_back(CLPoint(x, y));
      t += dt;
    }

  return points;
}

C_FLOAT64 BezierCurve::bernstein(C_INT32 i, C_INT32 n, C_FLOAT64 t)
{

  // first compute n over i
  C_FLOAT64 top = multiplyFromTo (n - i + 1, n);
  C_FLOAT64 bottom = multiplyFromTo (1, i);

  return (top / bottom * pow(t, (C_FLOAT64)i) * pow(1.0 - t, (C_FLOAT64)n - i));
}

CLPoint BezierCurve::bezierPt(C_FLOAT64 t, std::vector<CLPoint> pts)
{
  C_INT32 i;
  C_FLOAT64 x = 0.0;
  C_FLOAT64 y = 0.0;

  C_INT32 n = pts.size() - 1;

  for (i = 0;i <= n;i++)
    {
      x += bernstein(i, n, t) * pts[i].getX();
      y += bernstein(i, n, t) * pts[i].getY();
    }

  return CLPoint(x, y);
}

// compute product n1 * (n1+1) * ... * n2
// n2 > n1 !!!  else returns 1
C_FLOAT64 BezierCurve::multiplyFromTo(C_INT32 n1, C_INT32 n2)
{
  C_INT32 i;
  C_FLOAT64 prod = 1;

  if (n2 >= n1)
    {
      for (i = n1; i <= n2; i++)
        prod *= (C_FLOAT64)i;
    }

  return prod;
}
