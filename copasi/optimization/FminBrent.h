/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/FminBrent.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/07/19 15:02:50 $
   End CVS Header */

#ifndef COAPSI_FminBrent
#define COAPSI_FminBrent

/**
 *
 * Adapted by Pedro Mendes to suit Gepasi's optimisation framework
 * 9 Aug 1997 
 *
 **ORIGINAL**in**netlib**********************************************
 *        C math library
 * function FMINBR - one-dimensional search for a function minimum
 *  over the given range
 *
 * Input
 * double FminBrent(a, b, f, min, fmin, tol, maxiter)
 * @param double a;              Minimum will be seeked for over
 * @param double b;              a range [a,b], a being < b.
 * @param double (*f)(double x); Name of the function whose minimum
 *                               will be seeked for
 * @param double *min,           Location of minimum (output)
 * @param double *fmin,          Value of minimum (ouput)
 * @param double tol;            Acceptable tolerance for the minimum
 *                               location. It have to be positive
 *                               (e.g. may be specified as EPSILON)
 * @param int maxiter            Maximum number of iterations
 *
 * Output
 *      Fminbr returns an estimate for the minimum location with accuracy
 *      3*SQRT_EPSILON*abs(x) + tol.
 *      The function always obtains a local minimum which coincides with
 *      the global one only if a function under investigation being
 *      unimodular.
 *      If a function being examined possesses no local minimum within
 *      the given range, Fminbr returns 'a' (if f(a) < f(b)), otherwise
 *      it returns the right range boundary value b.
 *
 * @ return int (0: success, 1: negative tolerance, 2: b < a 3: iteration limit exceeded)
 *
 * Algorithm
 *      G.Forsythe, M.Malcolm, C.Moler, Computer methods for mathematical
 *      computations. M., Mir, 1980, p.202 of the Russian edition
 *
 *      The function makes use of the "gold section" procedure combined with
 *      the parabolic interpolation.
 *      At every step program operates three abscissae - x,v, and w.
 *      x - the last and the best approximation to the minimum location,
 *          i.e. f(x) <= f(a) or/and f(x) <= f(b)
 *          (if the function f has a local minimum in (a,b), then the both
 *          conditions are fulfiled after one or two steps).
 *      v,w are previous approximations to the minimum location. They may
 *      coincide with a, b, or x (although the algorithm tries to make all
 *      u, v, and w distinct). Points x, v, and w are used to construct
 *      interpolating parabola whose minimum will be treated as a new
 *      approximation to the minimum location if the former falls within
 *      [a,b] and reduces the range enveloping minimum more efficient than
 *      the gold section procedure. 
 *      When f(x) has a second derivative positive at the minimum location
 *      (not coinciding with a or b) the procedure converges superlinearly
 *      at a rate order about 1.324
 *
 ************************************************************************
 */
int FminBrent(double a,               /* Left border      */
              double b,               /* Right border      */
              double (*f)(double x),  /* Function under investigation  */
              double *min,            /* Location of minimum    */
              double *fmin,           /* Value of minimum     */
              double tol,             /* Acceptable tolerance    */
              int maxiter);          /* Maximum number of iterations  */

#endif // COAPSI_FminBrent
