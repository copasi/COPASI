/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/odepack++/dewset.cpp,v $
   $Revision: 1.2.2.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/06/06 16:15:27 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.
//
// This C++ code is based on an f2c version of the Fortran
// library ODEPACK available at: http://www.netlib.org/odepack/

#include <math.h>

#include "copasi.h"

#include "dewset.h"

/* DECK DEWSET */
/* Subroutine */
C_INT dewset_(C_INT *n, C_INT *itol, double *rtol,
              double *atol, double *ycur, double *ewt)
{
  /* System generated locals */
  C_INT i__1;
  double d__1;

  /* Local variables */
  C_INT i__;

  /* ***BEGIN PROLOGUE  DEWSET */
  /* ***SUBSIDIARY */
  /* ***PURPOSE  Set error weight vector. */
  /* ***TYPE      DOUBLE PRECISION (SEWSET-S, DEWSET-D) */
  /* ***AUTHOR  Hindmarsh, Alan C., (LLNL) */
  /* ***DESCRIPTION */

  /*  This subroutine sets the error weight vector EWT according to */
  /*      EWT(i) = RTOL(i)*ABS(YCUR(i)) + ATOL(i),  i = 1,...,N, */
  /*  with the subscript on RTOL and/or ATOL possibly replaced by 1 above, */
  /*  depending on the value of ITOL. */

  /* ***SEE ALSO  DLSODE */
  /* ***ROUTINES CALLED  (NONE) */
  /* ***REVISION HISTORY  (YYMMDD) */
  /*   791129  DATE WRITTEN */
  /*   890501  Modified prologue to SLATEC/LDOC format.  (FNF) */
  /*   890503  Minor cosmetic changes.  (FNF) */
  /*   930809  Renamed to allow single/double precision versions. (ACH) */
  /* ***END PROLOGUE  DEWSET */
  /* **End */

  /* ***FIRST EXECUTABLE STATEMENT  DEWSET */
  /* Parameter adjustments */
  --ewt;
  --ycur;
  --rtol;
  --atol;

  /* Function Body */
  switch (*itol)
    {
    case 1: goto L10;
    case 2: goto L20;
    case 3: goto L30;
    case 4: goto L40;
    }
L10:
  i__1 = *n;
  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L15: */
      ewt[i__] = rtol[1] * (d__1 = ycur[i__], fabs(d__1)) + atol[1];
    }
  return 0;
L20:
  i__1 = *n;
  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L25: */
      ewt[i__] = rtol[1] * (d__1 = ycur[i__], fabs(d__1)) + atol[i__];
    }
  return 0;
L30:
  i__1 = *n;
  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L35: */
      ewt[i__] = rtol[i__] * (d__1 = ycur[i__], fabs(d__1)) + atol[1];
    }
  return 0;
L40:
  i__1 = *n;
  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L45: */
      ewt[i__] = rtol[i__] * (d__1 = ycur[i__], fabs(d__1)) + atol[i__];
    }
  return 0;
  /* ----------------------- END OF SUBROUTINE DEWSET ---------------------- */
} /* dewset_ */
