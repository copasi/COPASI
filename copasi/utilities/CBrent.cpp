// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <cmath>
#include <limits>
#include <algorithm>

#include "CBrent.h"

// virtual
CBrent::Eval::~Eval()
{}

// virtual
double CBrent::Eval::operator()(const double & /* value */)
{
  return std::numeric_limits< double >::quiet_NaN();
}

// static
bool CBrent::findRoot(double a,            // Left border
                      double b,            // Right border
                      CBrent::Eval * pF,   // Call back for function evaluation
                      double * pRoot,      // Location of root
                      double * pRootValue, // Value at root
                      double tol)          // Acceptable tolerance
{
  double fa = (*pF)(a);
  double fb = (*pF)(b);

  if (fa * fb > 0)
    return false;

  if (fabs(fa) < fabs(fb))
    {
      double tmp = a;
      a = b;
      b = tmp;

      tmp = fa;
      fa = fb;
      fb = tmp;
    }

  double c = a;
  double fc = fa;
  double s;
  double fs = fb;
  double d;

  bool mflag = true;

  while (fabs(b - a) > tol && fb != 0.0 && fs != 0.0)
    {
      if (fa != fc && fb != fc)
        {
          // inverse quadratic interpolation
          s = (a * fb * fc) / ((fa - fb) * (fa - fc))
              + (b * fa * fc) / ((fb - fa) * (fb - fc))
              + (c * fa * fb) / ((fc - fa) * (fc - fb));
        }
      else
        {
          // secant method
          s = b - fb * (b - a) / (fb - fa);
        }

      if ((s < std::min((3.0 * a + b) / 4.0, b) || std::max((3.0 * a + b) / 4.0, b) < s) ||
          (mflag && fabs(s - b) >= fabs(b - c) / 2.0) ||
          (!mflag && fabs(s - b) >= fabs(c - d) / 2.0) ||
          (mflag && fabs(b - c) < tol) ||
          (!mflag && fabs(c - d) < tol))
        {
          // bisection method
          s = (a + b) / 2.0;
          mflag = true;
        }
      else
        {
          mflag = false;
        }

      fs = (*pF)(s);

      d = c;
      c = b;

      if (fa * fs < 0)
        {
          b = s;
          fb = fs;
        }
      else
        {
          a = s;
          fa = fs;
        }

      if (fabs(fa) < fabs(fb))
        {
          double tmp = a;
          a = b;
          b = tmp;

          tmp = fa;
          fa = fb;
          fb = tmp;
        }
    }

  // return the smaller value of fa and fb
  if (fabs(fa) < fabs(fb))
    {
      *pRoot = a;
      *pRootValue = fa;
    }
  else
    {
      *pRoot = b;
      *pRootValue = fb;
    }

  return 0;
}
