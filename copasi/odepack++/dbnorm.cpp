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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//
// This C++ code is based on an f2c conversion of the Fortran
// library ODEPACK available at: http://www.netlib.org/odepack/

#include <cmath>

#include <algorithm>

#include "copasi/copasi.h"

#include "dbnorm.h"

/* DECK DBNORM */
double dbnorm_(C_INT *n, double *a, C_INT *nra, C_INT *ml,
               C_INT *mu, double *w)
{
  /* System generated locals */
  C_INT a_dim1, a_offset, i__1, i__2;
  double ret_val, d__1, d__2;

  /* Local variables */
  C_INT i__, j, i1;
  double an;
  C_INT jhi, jlo;
  double sum;

  /* ----------------------------------------------------------------------- */
  /* This function computes the norm of a banded N by N matrix, */
  /* stored in the array A, that is consistent with the weighted max-norm */
  /* on vectors, with weights stored in the array W. */
  /* ML and MU are the lower and upper half-bandwidths of the matrix. */
  /* NRA is the first dimension of the A array, NRA .ge. ML+MU+1. */
  /* In terms of the matrix elements a(i,j), the norm is given by: */
  /*   DBNORM = MAX(i=1,...,N) (W(i) * Sum(j=1,...,N) ABS(a(i,j))/W(j)) */
  /* ----------------------------------------------------------------------- */
  /* Parameter adjustments */
  --w;
  a_dim1 = *nra;
  a_offset = 1 + a_dim1;
  a -= a_offset;

  /* Function Body */
  an = 0.;
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i1 = i__ + *mu + 1;
      /* Computing MAX */
      i__2 = i__ - *ml;
      jlo = std::max(i__2, (C_INT)1);
      /* Computing MIN */
      i__2 = i__ + *mu;
      jhi = std::min(i__2, *n);
      i__2 = jhi;

      for (j = jlo; j <= i__2; ++j)
        {
          /* L10: */
          sum += (d__1 = a[i1 - j + j * a_dim1], fabs(d__1)) / w[j];
        }

      /* Computing MAX */
      d__1 = an, d__2 = sum * w[i__];
      an = std::max(d__1, d__2);
      /* L20: */
    }

  ret_val = an;
  return ret_val;
  /* ----------------------- End of Function DBNORM ------------------------ */
} /* dbnorm_ */
