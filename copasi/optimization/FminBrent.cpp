/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/FminBrent.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/07/19 15:02:50 $
   End CVS Header */

#include <math.h>
#include <float.h>

#include "FminBrent.h"

#define SQRT_EPSILON sqrt(DBL_EPSILON)
int FMinBrent(double a,                /* Left border      */
              double b,                /* Right border      */
              double (*f)(double x),   /* Function under investigation  */
              double *min,             /* Location of minimum    */
              double *fmin,            /* Value of minimum     */
              double tol,              /* Acceptable tolerance    */
              int maxiter)            /* Maximum number of iterations  */
{
  double x, v, w;                       /* Abscissae, descr. see above  */
  double fx;                          /* f(x)        */
  double fv;                          /* f(v)        */
  double fw;                          /* f(w)        */
  const double r = (3. - sqrt(5.0)) / 2;  /* Gold section ratio    */
  int iter;                           /* Iteration counter    */

  if (tol <= 0) return 1;            /* check input values    */
  if (b <= a) return 2;

  v = a + r * (b - a); fv = (*f)(v);     /* First step - always gold section*/
  x = v; w = v;
  fx = fv; fw = fv;

  for (iter = 0; iter < maxiter; iter++) /* Main iteration loop    */
    {
      double range = b - a;             /* Range over which the minimum is */
      double middle_range = (a + b) / 2;  /* seeked       */
      double tol_act =                 /* Actual tolerance     */
        SQRT_EPSILON * fabs(x) + tol / 3;
      double new_step;                /* Step at this iteration   */

      if (fabs(x - middle_range) + range / 2 <= 2*tol_act)
        {
          *min = x; *fmin = fx;       /* Store the solution    */
          return 0;                   /* Acceptable approx. is found  */
        }
      /* Obtain the gold section step  */
      new_step = r * (x < middle_range ? b - x : a - x);

      /* Decide if the interpolation  */
      /* can be tried      */
      if (fabs(x - w) >= tol_act)     /* If x and w are distinct          */
        {/* interpolatiom may be tried  */
          double p;                   /* Interpolation step is calculated */
          double q;                   /* as p/q; division operation  */
          double t;                   /* is delayed until last moment  */

          t = (x - w) * (fx - fv);
          q = (x - v) * (fx - fw);
          p = (x - v) * q - (x - w) * t;
          q = 2 * (q - t);

          if (q > 0.0)               /* q was calculated with the   */
            p = -p;                   /* opposite sign; make q positive */
          else                        /* and assign possible minus to  */
            q = -q;                   /* p        */

          if (fabs(p) < fabs(new_step*q) &&  /* If x+p/q falls in [a,b]   */
               p > q*(a - x + 2*tol_act) &&       /* not too close to a and   */
               p < q*(b - x - 2*tol_act))      /* b, and isn't too large   */
            new_step = p / q;                 /* it is accepted     */
          /* If p/q is too large then the  */
          /* gold section procedure can  */
          /* reduce [a,b] range to more  */
          /* extent       */
        }

      if (fabs(new_step) < tol_act)   /* Adjust the step to be not less */
        if (new_step > (double)0)     /* than tolerance     */
          new_step = tol_act;
        else
          new_step = -tol_act;
      /* Obtain the next approximation to */
      {/* min & reduce the enveloping range*/
        register double t = x + new_step;  /* Tentative point for the min  */
        register double ft = (*f)(t);
        if (ft <= fx)
          {/* t is a better approximation  */
            if (t < x)                /* Reduce the range so that   */
              b = x;                   /* t would fall within it   */
            else
              a = x;

            v = w; w = x; x = t;     /* Assign the best approx to x  */
            fv = fw; fw = fx; fx = ft;
          }
        else                           /* x remains the better approx  */
          {
            if (t < x)                /* Reduce the range enclosing x  */
              a = t;
            else
              b = t;

            if (ft <= fw || w == x)
              {
                v = w; w = t;
                fv = fw; fw = ft;
              }
            else
              if (ft <= fv || v == x || v == w)
                {
                  v = t;
                  fv = ft;
                }
          }
      }                                /* ----- end-of-block -----   */
    }                                  /* ===== End of loop =====   */

  *min = x; *fmin = fx;                /* Store the best value    */
  return 3;                            /* Too many iterations    */
}
