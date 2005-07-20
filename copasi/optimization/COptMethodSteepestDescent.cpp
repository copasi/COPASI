/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodSteepestDescent.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2005/07/20 05:10:41 $
   End CVS Header */

#include "COptMethod.h"
#include "COptProblem.h"
#include "COptItem.h"

#include "report/CCopasiObjectReference.h"

COptMethodSteepestDescent::COptMethodSteepestDescent(const CCopasiContainer * pParent):
    COptMethod(CCopasiMethod::SteepestDescent, pParent)
    /*, , , // parameters to be initialized*/
{
  addParameter("Maximum Number of Iterations", CCopasiParameter::UINT, (unsigned C_INT32) 100000);
}

COptMethodSteepestDescent::COptMethodSteepestDescent(const COptMethodSteepestDescent & src,
    const CCopasiContainer * pParent): COptMethod(src, pParent) /*, , , // parameters to be initialized*/
{
}

COptMethodSteepestDescent::~COptMethodSteepestDescent()
{
  cleanup();
}

bool COptMethodSteepestDescent::setCallBack(CProcessReport * pCallBack)
{
  CCopasiMethod::setCallBack(pCallBack);

  /*  pCallBack->addItem(...);*/

  return true;
}

bool COptMethodSteepestDescent::optimise()
{
  if (!initialize()) return false;

  int i, j, k;
  double tmp, x0, alpha, mn, md, mx, norm, daux, fmn, fmd, fmx;
  bool calc_grad;
  bool no_convergence;

  // initial point is first guess
  for (i = 0; i < mpOptProblem->getOptItemSize(); i++)
    candp[i] = *(*mpOptItem)[i]->getObjectValue();

  fmx = candx = mpOptProblem->calculate();

  for (j = 0; j < maxiter; j++)
    {
      // calculate the direction of steepest descent
      // by central finite differences
      gradient();
      // minimise the function in this direction
      // find brackets for the minimisation
      //  mn = 0.0; md = 1.0;
      //  mnbrak(&mn, &md, &mx, &fmn, &fmd, &fmx, descent_line);
      // make sure that no parameter will exceed its bounds
      x0 = DBL_MAX;

      for (i = 0; i < mpOptProblem->getOptItemSize(); i++)
        {
          if (fabs(dsd[i]) > DBL_EPSILON)
            {
              if (dsd[i] > 0)
                {
                  tmp = *(*mpOptItem)[i]->getUpperBoundValue();
                }

              else
                {
                  tmp = *(*mpOptItem)[i]->getLowerBoundValue();
                }

              // calculate the size of the largest jump
              tmp = (tmp - candp[i]) / dsd[i];
              // keep it if it is the smallest
              if (tmp < x0) x0 = tmp;
            }
          else dsd[i] = 0.0;
        }

      // we will move at a rate of 1/10 this size
      mn = mx = alpha = 0.0;

      for (k = 0, calc_grad = false; (k < 9) && !calc_grad; k++)
        {
          // set the minimum to the last successful step
          mn = mx;
          fmn = fmx;
          // increment alpha
          alpha += 0.1 * x0;
          // set the maximum to it
          mx = alpha;
          // take one step in that direction
          for (i = 0, norm = 0.0; i < mpOptProblem->getOptItemSize(); i++)
            {
              (*(*mpSetCalculateVariable)[i])(candp[i] + alpha * dsd[i]);
              if ((daux = fabs(alpha * dsd[i])) > norm) norm = daux;
            }
          fmx = mpOptProblem->calculate();

          // if this was an upward step find the minimum
          if (fmx > fmn)
            {
              //md = mn + (mx-mn)/2;
              //Brent(mn, md, mx, descent_line, &alpha, &tmp, 1e-6, 50);
              FMinBrent(mn, mx, &alpha, &tmp, tolerance, 5);
              // take one step in that direction
              for (i = 0, norm = 0.0; i < mpOptProblem->getOptItemSize(); i++)
                {
                  (*(*mpSetCalculateVariable)[i])(candp[i] + alpha * dsd[i]);
                  if ((daux = fabs(alpha * dsd[i])) > norm) norm = daux;
                }
              fmx = mpOptProblem->calculate();
              // time to evaluate the new steepest descent direction
              calc_grad = true;
            }
          // check if this aproximation is good enough
          if (fabs(fmx - candx) < tolerance)
            //   if(norm < tolerance)
            {
              candx = fmx;
              for (i = 0; i < mpOptProblem->getOptItemSize(); i++)
                candp[i] = *(*mpOptItem)[i]->getObjectValue();
              // an acceptable solution
              return true;
            }
        }
      // this is the best approximation thus far
      candx = fmx;
      for (i = 0; i < mpOptProblem->getOptItemSize(); i++)
        candp[i] = *(*mpOptItem)[i]->getObjectValue();
      //if(callback != NULL) callback(candx);
      //if(debug) dump_data(j);
    }
  return false;
}

bool COptMethodSteepestDescent::cleanup()
{
  unsigned C_INT32 i;

  // pdelete all used variables
  return true;
}

bool COptMethodSteepestDescent::initialize()
{
  if (!COptMethod::initialize()) return false;
  maxiter = * getValue("Maximum Number of Iterations").pUINT;
  return true;
}

void COptMethodSteepestDescent::gradient()
{
  unsigned C_INT32 i;

  double y;

  y = mpOptProblem->calculate();

  for (i = 0; i < mpOptProblem->getOptItemSize(); i++)
    {
      if ((*(*mpOptItem)[i]->getObjectValue()) != 0.0)
        {
          (*(*mpSetCalculateVariable)[i])(*(*mpOptItem)[i]->getObjectValue() *1.001);
          dsd[i] = (y - mpOptProblem->calculate()) / ((*(*mpOptItem)[i]->getObjectValue()) * 0.001);
        }

      else
        {
          (*(*mpSetCalculateVariable)[i])(1e-7);
          dsd[i] = (y - mpOptProblem->calculate()) / 1e-7;
        }

      (*(*mpSetCalculateVariable)[i])(*(*mpOptItem)[i]->getObjectValue());
    }
}

double COptMethodSteepestDescent::DescentLine(double x)
{
  for (int i = 0; i < mpOptProblem->getOptItemSize(); i++)
    (*(*mpSetCalculateVariable)[i])(candp[i] + x * dsd[i]);
  return mpOptProblem->calculate();
}

int COptMethodSteepestDescent::FMinBrent(double a,                 /* Left border      */
    double b,                 /* Right border      */

    double *min,              /* Location of minimum    */
    double *fmin,             /* Value of minimum     */
    double tol,               /* Acceptable tolerance    */
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

  v = a + r * (b - a); fv = DescentLine(v);     /* First step - always gold section*/
  x = v; w = v;
  fx = fv; fw = fv;

  for (iter = 0; iter < maxiter; iter++) /* Main iteration loop    */
    {
      double range = b - a;             /* Range over which the minimum is */
      double middle_range = (a + b) / 2;  /* seeked       */
      double tol_act =                  /* Actual tolerance     */
        sqrt(DBL_EPSILON) * fabs(x) + tol / 3;
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

          if (fabs(p) < fabs(new_step*q) &&   /* If x+p/q falls in [a,b]   */
              p > q*(a - x + 2*tol_act) &&        /* not too close to a and   */
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
        register double ft = DescentLine(t);
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
