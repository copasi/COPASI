/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/odepack++/dmnorm.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/02/17 15:18:55 $
   End CVS Header */

#include <math.h>

#include <algorithm>

#include "copasi.h"

/* DECK DMNORM */
double dmnorm_(C_INT *n, double *v, double *w)
{
  /* System generated locals */
  C_INT i__1;
  double ret_val, d__1, d__2, d__3;

  /* Local variables */
  C_INT i__;
  double vm;

  /* ----------------------------------------------------------------------- */
  /* This function routine computes the weighted max-norm */
  /* of the vector of length N contained in the array V, with weights */
  /* contained in the array w of length N: */
  /*   DMNORM = MAX(i=1,...,N) ABS(V(i))*W(i) */
  /* ----------------------------------------------------------------------- */
  /* Parameter adjustments */
  --w;
  --v;

  /* Function Body */
  vm = 0.;
  i__1 = *n;
  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L10: */
      /* Computing MAX */
      d__2 = vm, d__3 = (d__1 = v[i__], fabs(d__1)) * w[i__];
      vm = std::max(d__2, d__3);
    }
  ret_val = vm;
  return ret_val;
  /* ----------------------- End of Function DMNORM ------------------------ */
} /* dmnorm_ */
