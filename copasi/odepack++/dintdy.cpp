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
#include <string>

#include <algorithm>

#include "copasi/copasi.h"

#include "CInternalSolver.h"
#include "Cxerrwd.h"

#define dls001_1 (mdls001_._1)
#define dls001_2 (mdls001_._2)
#define dls001_3 (mdls001_._3)

#define dlsa01_1 (mdlsa01_._1)
#define dlsa01_2 (mdlsa01_._2)
#define dlsa01_3 (mdlsa01_._3)

double d_sign(const double & a, const double & b);

static double c_b34 = 0.0;

static C_INT c__0 = 0;
static C_INT c__1 = 1;
static C_INT c__2 = 2;
static C_INT c__30 = 30;
static C_INT c__51 = 51;
static C_INT c__52 = 52;
static C_INT c__60 = 60;

#define pow_di(__x, __n) pow(*__x, (double) *__n)

/* DECK DINTDY */
/* Subroutine */
C_INT CInternalSolver::dintdy_(double *t, const C_INT *k, double *yh,
                               C_INT *nyh, double *dky, C_INT *iflag)
{
  /* System generated locals */
  C_INT yh_dim1, yh_offset, i__1, i__2;
  double d__1;

  /* Local variables */
  double c__;
  C_INT i__, j;
  double r__, s;
  C_INT ic, jb, jj;
  double tp;
  C_INT jb2, jj1, jp1;
  std::string msg;

  /* ***BEGIN PROLOGUE  DINTDY */
  /* ***SUBSIDIARY */
  /* ***PURPOSE  Interpolate solution derivatives. */
  /* ***TYPE      DOUBLE PRECISION (SINTDY-S, DINTDY-D) */
  /* ***AUTHOR  Hindmarsh, Alan C., (LLNL) */
  /* ***DESCRIPTION */

  /*  DINTDY computes interpolated values of the K-th derivative of the */
  /*  dependent variable vector y, and stores it in DKY.  This routine */
  /*  is called within the package with K = 0 and T = TOUT, but may */
  /*  also be called by the user for any K up to the current order. */
  /*  (See detailed instructions in the usage documentation.) */

  /*  The computed values in DKY are gotten by interpolation using the */
  /*  Nordsieck history array YH.  This array corresponds uniquely to a */
  /*  vector-valued polynomial of degree NQCUR or less, and DKY is set */
  /*  to the K-th derivative of this polynomial at T. */
  /*  The formula for DKY is: */
  /*               q */
  /*   DKY(i)  =  sum  c(j,K) * (T - tn)**(j-K) * h**(-j) * YH(i,j+1) */
  /*              j=K */
  /*  where  c(j,K) = j*(j-1)*...*(j-K+1), q = NQCUR, tn = TCUR, h = HCUR. */
  /*  The quantities  nq = NQCUR, l = nq+1, N = NEQ, tn, and h are */
  /*  communicated by COMMON.  The above sum is done in reverse order. */
  /*  IFLAG is returned negative if either K or T is out of bounds. */

  /* ***SEE ALSO  DLSODE */
  /* ***ROUTINES CALLED  XERRWD */
  /* ***COMMON BLOCKS    DLS001 */
  /* ***REVISION HISTORY  (YYMMDD) */
  /*   791129  DATE WRITTEN */
  /*   890501  Modified prologue to SLATEC/LDOC format.  (FNF) */
  /*   890503  Minor cosmetic changes.  (FNF) */
  /*   930809  Renamed to allow single/double precision versions. (ACH) */
  /*   010418  Reduced size of Common block /DLS001/. (ACH) */
  /*   031105  Restored 'own' variables to Common block /DLS001/, to */
  /*           enable interrupt/restart feature. (ACH) */
  /*   050427  Corrected roundoff decrement in TP. (ACH) */
  /* ***END PROLOGUE  DINTDY */
  /* **End */

  /* ***FIRST EXECUTABLE STATEMENT  DINTDY */
  /* Parameter adjustments */
  yh_dim1 = *nyh;
  yh_offset = 1 + yh_dim1;
  yh -= yh_offset;
  --dky;

  /* Function Body */
  *iflag = 0;

  if (*k < 0 || *k > dls001_1.nq)
    {
      goto L80;
    }

  d__1 = fabs(dls001_1.tn) + fabs(dls001_1.hu);
  tp = dls001_1.tn - dls001_1.hu - dls001_1.uround * 100. * d_sign(d__1, dls001_1.hu);

  if ((*t - tp) * (*t - dls001_1.tn) > 0.)
    {
      goto L90;
    }

  s = (*t - dls001_1.tn) / dls001_1.h__;
  ic = 1;

  if (*k == 0)
    {
      goto L15;
    }

  jj1 = dls001_1.l - *k;
  i__1 = dls001_1.nq;

  for (jj = jj1; jj <= i__1; ++jj)
    {
      /* L10: */
      ic *= jj;
    }

L15:
  c__ = (double) ic;
  i__1 = dls001_1.n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L20: */
      dky[i__] = c__ * yh[i__ + dls001_1.l * yh_dim1];
    }

  if (*k == dls001_1.nq)
    {
      goto L55;
    }

  jb2 = dls001_1.nq - *k;
  i__1 = jb2;

  for (jb = 1; jb <= i__1; ++jb)
    {
      j = dls001_1.nq - jb;
      jp1 = j + 1;
      ic = 1;

      if (*k == 0)
        {
          goto L35;
        }

      jj1 = jp1 - *k;
      i__2 = j;

      for (jj = jj1; jj <= i__2; ++jj)
        {
          /* L30: */
          ic *= jj;
        }

L35:
      c__ = (double) ic;
      i__2 = dls001_1.n;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          /* L40: */
          dky[i__] = c__ * yh[i__ + jp1 * yh_dim1] + s * dky[i__];
        }

      /* L50: */
    }

  if (*k == 0)
    {
      return 0;
    }

L55:
  i__1 = -(*k);
  r__ = pow_di(&dls001_1.h__, &i__1);
  i__1 = dls001_1.n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L60: */
      dky[i__] = r__ * dky[i__];
    }

  return 0;

L80:
  msg = "DINTDY-  K (=I1) illegal      ";
  mxerrwd(msg, &c__30, &c__51, &c__0, &c__1, k, &c__0, &c__0, &c_b34, &
          c_b34, (C_INT)80);
  *iflag = -1;
  return 0;
L90:
  msg = "DINTDY-  T (=R1) illegal      ";
  mxerrwd(msg, &c__30, &c__52, &c__0, &c__0, &c__0, &c__0, &c__1, t, &c_b34,
          (C_INT)80);
  msg = "      T not in interval TCUR - HU (= R1) to TCUR (=R2)      ";
  mxerrwd(msg, &c__60, &c__52, &c__0, &c__0, &c__0, &c__0, &c__2, &tp, &
          dls001_1.tn, (C_INT)80);
  *iflag = -2;
  return 0;
  /* ----------------------- END OF SUBROUTINE DINTDY ---------------------- */
} /* dintdy_ */
