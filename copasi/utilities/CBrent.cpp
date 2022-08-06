// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

  double fTol = (fabs(fa) + fabs(fb)) * 0.5 * tol;
  double vTol = (fabs(a) + fabs(b)) * 0.5 * tol;

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

  while ((fabs(b - a) > vTol || fabs(fb - fa) > fTol) &&
         fb != 0.0 &&
         fs != 0.0 &&
         fabs(b - a) > (fabs(b) + fabs(a)) * 50.0 * std::numeric_limits< double >::epsilon())
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
  if (fabs(fa) <= fabs(fb))
    {
      *pRoot = a;
      *pRootValue = fa;
    }
  else
    {
      *pRoot = b;
      *pRootValue = fb;
    }

  return true;
}

// static
bool CBrent::findMinimum(double a,          /* Left border      */
                         double b,          /* Right border      */
                         CBrent::Eval * pF, /* Functor for function under investigation  */
                         double * min,      /* Location of minimum    */
                         double * fmin,     /* Value of minimum     */
                         double tol,        /* Acceptable tolerance    */
                         int maxiter)       /* Maximum number of iterations  */
{
  double x, v, w;                        /* Abscissae, descr. see above  */
  double fx;                             /* f(x)        */
  double fv;                             /* f(v)        */
  double fw;                             /* f(w)        */
  const double r = (3. - sqrt(5.0)) / 2; /* Gold section ratio    */
  int iter;                              /* Iteration counter    */

  const double SQRT_EPSILON = sqrt(std::numeric_limits< double >::epsilon());

  if (tol <= 0)
    return false; /* check input values    */

  if (b <= a)
    return false;

  v = a + r * (b - a);
  fv = (*pF)(v); /* First step - always gold section*/
  x = v;
  w = v;
  fx = fv;
  fw = fv;

  for (iter = 0; iter < maxiter; iter++) /* Main iteration loop    */
    {
      double range = b - a;                              /* Range over which the minimum is */
      double middle_range = (a + b) / 2;                 /* seeked       */
      double tol_act = SQRT_EPSILON * fabs(x) + tol / 3; /* Actual tolerance     */

      double new_step; /* Step at this iteration   */

      if (fabs(x - middle_range) + range / 2 <= 2 * tol_act)
        {
          *min = x;
          *fmin = fx; /* Store the solution    */
          return true;   /* Acceptable approx. is found  */
        }

      /* Obtain the gold section step  */
      new_step = r * (x < middle_range ? b - x : a - x);

      /* Decide if the interpolation  */

      /* can be tried      */
      if (fabs(x - w) >= tol_act) /* If x and w are distinct          */
        {
          /* interpolatiom may be tried  */
          double p; /* Interpolation step is calculated */
          double q; /* as p/q; division operation  */
          double t; /* is delayed until last moment  */

          t = (x - w) * (fx - fv);
          q = (x - v) * (fx - fw);
          p = (x - v) * q - (x - w) * t;
          q = 2 * (q - t);

          if (q > 0.0) /* q was calculated with the   */
            p = -p;    /* opposite sign; make q positive */
          else         /* and assign possible minus to  */
            q = -q;    /* p        */

          if (fabs(p) < fabs(new_step * q) &&  /* If x+p/q falls in [a,b]   */
              p > q * (a - x + 2 * tol_act) && /* not too close to a and   */
              p < q * (b - x - 2 * tol_act))   /* b, and isn't too large   */
            new_step = p / q;                  /* it is accepted     */

          /* If p/q is too large then the  */
          /* gold section procedure can  */
          /* reduce [a,b] range to more  */
          /* extent       */
        }

      if (fabs(new_step) < tol_act) /* Adjust the step to be not less */
        {
          if (new_step > (double) 0) /* than tolerance     */
            new_step = tol_act;
          else
            new_step = -tol_act;
        }

      /* Obtain the next approximation to */
      {
        /* min & reduce the enveloping range*/
        double t = x + new_step; /* Tentative point for the min  */
        double ft = (*pF)(t);

        if (ft <= fx)
          {
            /* t is a better approximation  */
            if (t < x) /* Reduce the range so that   */
              b = x;   /* t would fall within it   */
            else
              a = x;

            v = w;
            w = x;
            x = t; /* Assign the best approx to x  */
            fv = fw;
            fw = fx;
            fx = ft;
          }
        else /* x remains the better approx  */
          {
            if (t < x) /* Reduce the range enclosing x  */
              a = t;
            else
              b = t;

            if (ft <= fw || w == x)
              {
                v = w;
                w = t;
                fv = fw;
                fw = ft;
              }
            else if (ft <= fv || v == x || v == w)
              {
                v = t;
                fv = ft;
              }
          }
      } /* ----- end-of-block -----   */
    }   /* ===== End of loop =====   */

  *min = x;
  *fmin = fx; /* Store the best value    */
  return false;   /* Too many iterations    */
}
